#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "interfaces/msg/fire_sensor.hpp"

#define SERIAL_PORT_1 "/dev/ttyACM0"
#define SERIAL_PORT_2 "/dev/ttyACM1"
#define BAUD_RATE B115200
#define BUFFER_SIZE 256
#define EXPECTED_BYTES 30  // Change this to the desired number of bytes
#define TIMEOUT_SECONDS 1
#define VTIME_MULTIPLIER 10

class SerialReadingNode : public rclcpp::Node
{
public:
    SerialReadingNode() : Node("Serial_reading_node"),
                         publisher_(this->create_publisher<interfaces::msg::FireSensor>("data_fire", 10)),
                         timer_(this->create_wall_timer(std::chrono::milliseconds(250), bind(&SerialReadingNode::serialCommunication, this)))
    {
        RCLCPP_INFO(this->get_logger(), "Hello Serial Reading Node !");
    }

private:
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
        tty.c_cc[VTIME] = TIMEOUT_SECONDS * VTIME_MULTIPLIER; // 1 second timeout
        tty.c_cc[VMIN] = EXPECTED_BYTES;

        if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
        {
            perror("Error from tcsetattr");
            close(serial_port);
            return 1;
        }

        return 0;
    }

    void cleanupSerialPort(int serial_port)
    {
        // Close the serial port
        close(serial_port);
    }

    int serialCommunication()
    {
        int serial_port = -1;

        // Try both serial ports
        for (const char *port : {SERIAL_PORT_1, SERIAL_PORT_2})
        {
            // Open the serial port
            serial_port = open(port, O_RDWR);
            if (serial_port != -1)
            {
                RCLCPP_INFO(this->get_logger(), "Opened serial port: %s", port);
                break;
            }
        }

        if (serial_port == -1)
        {
            perror("Error opening serial port");
            return 1;
        }

        // Set up serial port
        if (setupSerialPort(serial_port) != 0)
        {
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

            auto msg = interfaces::msg::FireSensor();
            msg.ir_sensor_1 = ir_sensor1_value;
            msg.ir_sensor_2 = ir_sensor2_value;
            publisher_->publish(msg);
        }

        // Clean up serial port
        cleanupSerialPort(serial_port);

        return 0;
    }

    int ir_sensor1_value;
    int ir_sensor2_value;

    std::shared_ptr<rclcpp::Publisher<interfaces::msg::FireSensor>> publisher_;
    std::shared_ptr<rclcpp::TimerBase> timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto Node = std::make_shared<SerialReadingNode>();

    rclcpp::spin(Node);
    rclcpp::shutdown();
}