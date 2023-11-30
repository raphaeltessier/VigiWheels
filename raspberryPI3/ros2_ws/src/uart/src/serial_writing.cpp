#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/emergency_alert_fire.hpp"
#include "interfaces/msg/servo_cam_order.hpp"


#define SERIAL_PORT_1 "/dev/ttyACM0"
#define SERIAL_PORT_2 "/dev/ttyACM1"
#define BAUD_RATE B115200
#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 1
#define VTIME_MULTIPLIER 10

#define FIRE_ID 'f'
#define CAM_ID 'c'

class SerialWritingNode : public rclcpp::Node 
{
public:
    SerialWritingNode() : Node("Serial_writing_node"), serial_port_(-1)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Serial Writing Node !");
        
        initSerialPort();
        
        //timer_ = this->create_wall_timer(std::chrono::milliseconds(250), std::bind(&SerialWritingNode::EmergencyAlertFireCallBack, this)); 
        subscription_emergency_alert = this->create_subscription<interfaces::msg::EmergencyAlertFire>("emergency_alert", 10, std::bind(&SerialWritingNode::EmergencyAlertFireCallBack, this, std::placeholders::_1));


        subscription_servo_cam_order_ = this->create_subscription<interfaces::msg::ServoCamOrder>(
        "servo_cam_order", 10, std::bind(&SerialWritingNode::sendServoCamOrderCallback, this, _1));
    
    }

    ~SerialWritingNode()
    {
        cleanupSerialPort();
    }

private:
    void initSerialPort()
    {
        for (const char *port : {SERIAL_PORT_1, SERIAL_PORT_2}) 
        {
            // Open the serial port
            serial_port_ = open(port, O_RDWR);
            if (serial_port_ != -1)
            {
                RCLCPP_INFO(this->get_logger(), "Opened serial port: %s", port);
                break;
            }
        }

        if (serial_port_ == -1) 
        {
            perror("Error opening serial port");
            return;
        }

        // Set up serial port
        if (setupSerialPort(serial_port_) != 0) 
        {
            cleanupSerialPort();  // Close the serial port if setup fails
            return;
        }
    }

    int setupSerialPort(int serial_port) 
    {
        // Configure serial port
        struct termios tty;
        if (tcgetattr(serial_port, &tty) != 0)
        {
            perror("Error from tcgetattr");
            close(serial_port);
            return 1;
        }

        // Set serial port parameters
        cfsetispeed(&tty, BAUD_RATE);
        cfsetospeed(&tty, BAUD_RATE);
        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cflag &= ~PARENB;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CSIZE;
        tty.c_cflag |= CS8;
        tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        tty.c_iflag &= ~(IXON | IXOFF | IXANY);
        tty.c_oflag &= ~OPOST;

        // Set read timeout
        tty.c_cc[VTIME] = TIMEOUT_SECONDS * VTIME_MULTIPLIER;
        tty.c_cc[VMIN] = BUFFER_SIZE;

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) 
        {
            perror("Error from tcsetattr");
            close(serial_port);
            return 1;
        }

        return 0;
    }

    void cleanupSerialPort() 
    {
        if (serial_port_ != -1)
        {
            // Close the serial port
            close(serial_port_);
            RCLCPP_INFO(this->get_logger(), "Closed serial port");
        }
    }

    void EmergencyAlertFireCallBack(const interfaces::msg::EmergencyAlertFire & msg)
    {
       uart_sending_uint8(FIRE_ID, uint8_t(msg.fire_detected));

    }


    /* Send angle servo cam order via CAN bus [callback function]
    * This function is called when a message is published on the "/system_check" topic
    */
    int sendServoCamOrderCallback (const interfaces::msg::ServoCamOrder & servoOrder) {
        uart_sending_uint8(CAM_ID, servoOrder.servo_cam_angle);
  
    }


    void uart_sending_uint8(char id, uint_8 value) {
        if (serial_port_ == -1) 
        {
            RCLCPP_ERROR(this->get_logger(), "Serial port is not open");
            return;
        }

        char tx[8]; 
        snprintf(tx, sizeof(tx), "#%c=%04u", id, value); //8

        int bytes_written = write(serial_port_, tx, strlen(tx));

        if (bytes_written == -1) 
        {
            perror("Error writing to serial port");
        }

        RCLCPP_DEBUG(this->get_logger(), "Data send : %s\n", tx); 



    }

    int counter_; 
    std::shared_ptr<rclcpp::TimerBase> timer_;
    rclcpp::Subscription<interfaces::msg::EmergencyAlertFire>::SharedPtr subscription_emergency_alert;
    rclcpp::Subscription<interfaces::msg::ServoCamOrder>::SharedPtr subscription_servo_cam_order_;
    int serial_port_;
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<SerialWritingNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
