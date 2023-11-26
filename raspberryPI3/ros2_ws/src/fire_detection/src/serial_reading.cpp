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
#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 1
#define VTIME_MULTIPLIER 10

class SerialReadingNode : public rclcpp::Node 
{
public:
    SerialReadingNode() : Node("Serial_reading_node")
    {
        publisher_serial_reading = this->create_publisher<interfaces::msg::FireSensor>("data_fire", 10);
        timer_serial_reading = this->create_wall_timer(std::chrono::milliseconds(250), bind(&SerialReadingNode::serialCommunication, this)); 
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
        char frame_buf[BUFFER_SIZE];
        int frame_index = 0;
        bool frame_started = false;

        while (1) 
        {
            memset(read_buf, '\0', sizeof(read_buf));
            int num_bytes = read(serial_port, read_buf, sizeof(read_buf));

            if (num_bytes < 0) 
            {
                perror("Error reading");
                break;
            }

            // Process the received bytes
            for (int i = 0; i < num_bytes; ++i) 
            {
                // Check for frame start
                if (read_buf[i] == '#') 
                {
                    frame_started = true;
                    frame_index = 0;
                    memset(frame_buf, '\0', sizeof(frame_buf));
                }
                // Check for frame end
                else if (frame_started && read_buf[i] == '\n') 
                {
                    frame_started = false;

                    // Process the complete frame (e.g., parse and publish)
                    sscanf(frame_buf, "IR_SENSOR1=%d|IR_SENSOR2=%d|IR_SENSOR3=%d|IR_SENSOR4=%d|SMOKE_SENSOR1=%d|SMOKE_SENSOR2=%d", &ir_sensor1_value, &ir_sensor2_value, &ir_sensor3_value, &ir_sensor4_value, &smoke_sensor1_value, &smoke_sensor2_value);
                }
                // Store bytes in the frame buffer
                else if (frame_started) 
                {
                    frame_buf[frame_index++] = read_buf[i];
                }

                auto msg = interfaces::msg::FireSensor();
                msg.ir_sensor1 = ir_sensor1_value;
                msg.ir_sensor2 = ir_sensor2_value;
                msg.ir_sensor3 = ir_sensor3_value;
                msg.ir_sensor4 = ir_sensor4_value;
                msg.smoke_sensor1 = smoke_sensor1_value;
                msg.smoke_sensor2 = smoke_sensor2_value;
                publisher_serial_reading->publish(msg);
            }
        }
        return 0;
    }

    int ir_sensor1_value;
    int ir_sensor2_value;
    int ir_sensor3_value;
    int ir_sensor4_value;
    int smoke_sensor1_value;
    int smoke_sensor2_value;
    std::shared_ptr<rclcpp::Publisher<interfaces::msg::FireSensor>> publisher_serial_reading;
    std::shared_ptr<rclcpp::TimerBase> timer_serial_reading;
};

int main(int argc, char *argv[]) 
{
    rclcpp::init(argc, argv);

    auto Node = std::make_shared<SerialReadingNode>();

    rclcpp::spin(Node);
    rclcpp::shutdown();
}
