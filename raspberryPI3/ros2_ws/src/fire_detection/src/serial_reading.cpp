#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "my_robot_interfaces/msg/hardware_status.hpp"

#define SERIAL_PORT "/dev/ttyACM1"
#define BAUD_RATE B115200
#define BUFFER_SIZE 256
#define EXPECTED_BYTES 30  // Change this to the desired number of bytes


class SerialReadingNode : public rclcpp::Node
{
public: 
    SerialReadingNode() : Node("Serial_reading_node")
    {
        RCLCPP_INFO(this->get_logger(), "Hello Serial Reading Node !"); 
                publisher_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("data_fire", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(250), bind(&SerialReadingNode::serialCommunication, this)); 
    }
private: 

    int serialCommunication()
    {
        // Open the serial port
        int serial_port = open(SERIAL_PORT, O_RDWR);
        if (serial_port == -1) 
        {
            perror("Error opening serial port");
            return 1;
        }

        // Configure serial port
        struct termios tty;
        if(tcgetattr(serial_port, &tty) != 0)
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
        tty.c_cc[VTIME] = 1; // 0.1 seconds timeout
        tty.c_cc[VMIN] = EXPECTED_BYTES;

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0) 
        {
            perror("Error from tcsetattr");
            close(serial_port);
            return 1;
        }

        // Read from serial port in a loop
        char read_buf[BUFFER_SIZE];
        while (1) 
        {
            memset(read_buf, '\0', sizeof(read_buf));
            int num_bytes = read(serial_port, read_buf, sizeof(read_buf));

            if (num_bytes < 0) 
            {
                perror("Error reading");
                break;
            }

            sscanf(read_buf, "IR_SENSOR1=%d|IR_SENSOR2=%d", &ir_sensor1_value, &ir_sensor2_value);

            //RCLCPP_INFO(this->get_logger(), "IR_SENSOR1 = %d", ir_sensor1_value);

            auto msg = my_robot_interfaces::msg::HardwareStatus(); 
            msg.ir_sensor_1 = ir_sensor1_value; 
            msg.ir_sensor_2 = ir_sensor2_value; 
            publisher_->publish(msg);

            // if (num_bytes == EXPECTED_BYTES)
            // {
            //     auto message = example_interfaces::msg::String(); 
            //     message.data = std::string("Received message: ") + read_buf;
            //     RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
               
            //     publisher_->publish(message);
            // }          
        }

        // Close the serial port
        close(serial_port);

        return 0; 
    }

    int ir_sensor1_value;
    int ir_sensor2_value;

    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr publisher_; 
    //rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_; 

}; 

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv); 

    auto Node = std::make_shared<SerialReadingNode>(); 

    rclcpp::spin(Node);  
    rclcpp::shutdown();  
}