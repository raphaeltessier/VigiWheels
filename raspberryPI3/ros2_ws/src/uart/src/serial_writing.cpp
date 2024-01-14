#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <thread>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/emergency_alert_fire.hpp"
#include "interfaces/msg/servo_cam_order.hpp"
#include "interfaces/msg/pressure_level.hpp"

#define SERIAL_PORT_1 "/dev/ttyACM0"
#define SERIAL_PORT_2 "/dev/ttyACM1"
#define BAUD_RATE B115200
#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 1
#define VTIME_MULTIPLIER 10

#define FIRE_ID 'f'
#define CAM_ID 'c'

using namespace std;
using placeholders::_1;

class SerialWritingNode : public rclcpp::Node
{
public:
    SerialWritingNode() : Node("Serial_writing_node"), serial_port_(-1), serial_error_logged_(false)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Serial Writing Node!");

        initSerialPort();

        subscription_emergency_alert = this->create_subscription<interfaces::msg::EmergencyAlertFire>(
            "emergency_alert", 10, std::bind(&SerialWritingNode::emergencyAlertFireCallback, this, std::placeholders::_1));

        subscription_servo_cam_order_ = this->create_subscription<interfaces::msg::ServoCamOrder>(
            "servo_cam_order", 10, std::bind(&SerialWritingNode::sendServoCamOrderCallback, this, _1));

        subscription_pressure_alert = this->create_subscription<interfaces::msg::PressureLevel>(
            "pressure_level", 10, std::bind(&SerialWritingNode::alertPressureCallback, this, std::placeholders::_1));
     }
    

    ~SerialWritingNode()
    {
        cleanupSerialPort();
    }

private:
    void initSerialPort()
    {
        // Check if the serial port is already open
        if (serial_port_ != -1)
        {
            // Close the serial port before reopening
            cleanupSerialPort();
        }

        // Try both serial ports
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
            if (!serial_error_logged_)
            {
                RCLCPP_ERROR(this->get_logger(), "Error opening serial port");
                serial_error_logged_ = true;
            }
            return;
        }

        // Set up serial port
        if (setupSerialPort(serial_port_) != 0)
        {
            cleanupSerialPort();
            return;
        }
    }

    int setupSerialPort(int serial_port)
    {
        // Configure serial port
        struct termios tty;
        if (tcgetattr(serial_port, &tty) != 0)
        {
            if (!serial_error_logged_)
            {
                RCLCPP_ERROR(this->get_logger(), "Error from tcgetattr");
                serial_error_logged_ = true;
            }
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
            if (!serial_error_logged_)
            {
                RCLCPP_ERROR(this->get_logger(), "Error from tcsetattr");
                serial_error_logged_ = true;
            }
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
            RCLCPP_WARN(this->get_logger(), "Closed serial port");
            serial_port_ = -1; // Reset the file descriptor
            serial_error_logged_ = false; // Reset the error flag when closing the serial port
        }
    }

    void emergencyAlertFireCallback(const interfaces::msg::EmergencyAlertFire &msg)
    {
        // Check if the serial port is open
        if (serial_port_ == -1)
        {
            // Reinitialize the serial port if it is closed
            initSerialPort();
            return;
        }

        char tx[9];
        snprintf(tx, sizeof(tx), "#fire=%u\n", msg.fire_detected);


        // Write to serial port
        int bytes_written = write(serial_port_, tx, strlen(tx));

        if (bytes_written == -1)
        {
            // Check if the error is ENXIO (No such device or address), indicating a potential unplugging of the USB device
            if (errno == ENXIO)
            {
                if (!serial_error_logged_)
                {
                    RCLCPP_WARN(this->get_logger(), "Error writing: %s. Reinitializing serial port.", strerror(errno));
                    serial_error_logged_ = true;
                }
                initSerialPort();
            }
            else
            {
                if (!serial_error_logged_)
                {
                    RCLCPP_ERROR(this->get_logger(), "Error writing to serial port");
                    serial_error_logged_ = true;
                }
                cleanupSerialPort();
            }
        }
        else
        {
            //RCLCPP_INFO(this->get_logger(), "Data sent: %s", tx);
        }
    }

    void alertPressureCallback(const interfaces::msg::PressureLevel &msg)
    {
        // Check if the serial port is open
        if (serial_port_ == -1)
        {
            // Reinitialize the serial port if it is closed
            initSerialPort();
            return;
        }

        if(strcmp(msg.level.c_str(), "High") == 0)
        {
            pressure_detection = true; 
        }
        else 
        {
            pressure_detection = false; 
        }

        char tx[20];  
        snprintf(tx, sizeof(tx), "#pressure=%u\n", pressure_detection); 


        // Write to serial port
        int bytes_written = write(serial_port_, tx, strlen(tx));

        if (bytes_written == -1)
        {
            // Check if the error is ENXIO (No such device or address), indicating a potential unplugging of the USB device
            if (errno == ENXIO)
            {
                if (!serial_error_logged_)
                {
                    RCLCPP_WARN(this->get_logger(), "Error writing: %s. Reinitializing serial port.", strerror(errno));
                    serial_error_logged_ = true;
                }
                initSerialPort();
            }
            else
            {
                if (!serial_error_logged_)
                {
                    RCLCPP_ERROR(this->get_logger(), "Error writing to serial port");
                    serial_error_logged_ = true;
                }
                cleanupSerialPort();
            }
        }
        else
        {
            //RCLCPP_INFO(this->get_logger(), "Data sent: %s", tx);
        }
    }

    /* Send angle servo cam order via CAN bus [callback function]
     * This function is called when a message is published on the "/system_check" topic
     */
    void sendServoCamOrderCallback(const interfaces::msg::ServoCamOrder &servoOrder)
    {
        uart_sending_uint8(CAM_ID, servoOrder.servo_cam_angle);
    }

    void uart_sending_uint8(char id, uint8_t value)
    {
        if (serial_port_ == -1)
        {
            RCLCPP_ERROR(this->get_logger(), "Serial port is not open");
            return;
        }

        char tx[10];
        snprintf(tx, sizeof(tx), "#%c=%04u\n", id, value); //8

        int bytes_written = write(serial_port_, tx, strlen(tx));

        if (bytes_written == -1)
        {
            perror("Error writing to serial port");
        }

        RCLCPP_DEBUG(this->get_logger(), "Data send : %s\n", tx);
    }
    rclcpp::Subscription<interfaces::msg::PressureLevel>::SharedPtr subscription_pressure_alert;
    rclcpp::Subscription<interfaces::msg::EmergencyAlertFire>::SharedPtr subscription_emergency_alert;
    rclcpp::Subscription<interfaces::msg::ServoCamOrder>::SharedPtr subscription_servo_cam_order_;
    bool pressure_detection; 
    int serial_port_;
    bool serial_error_logged_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<SerialWritingNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}

