#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/fire_sensor.hpp"

#define SERIAL_PORT_1 "/dev/ttyACM0"
#define SERIAL_PORT_2 "/dev/ttyACM1"
#define SERIAL_PORT_3 "/dev/ttyACM2"
#define SERIAL_PORT_4 "/dev/ttyACM3"
#define BAUD_RATE B115200
#define BUFFER_SIZE 100
#define TIMEOUT_SECONDS 1
#define VTIME_MULTIPLIER 10
#define START_OF_FRAME '#'
#define END_OF_FRAME '\n'

class SerialReadingNode : public rclcpp::Node
{
public:
    SerialReadingNode() : Node("serial_reading_node"), serial_port_(-1), serial_error_logged_(false)
    {
        RCLCPP_INFO(this->get_logger(), "Hello Serial Reading Node!");

        initSerialPort();

        publisher_serial_reading = this->create_publisher<interfaces::msg::FireSensor>("data_fire", 10);
        timer_serial_reading = this->create_wall_timer(std::chrono::milliseconds(250), std::bind(&SerialReadingNode::serialCommunication, this));
    }

    ~SerialReadingNode()
    {
        cleanupSerialPort();
    }

private:
    int setupSerialPort(int serial_port)
    {
        // Configure serial port
        struct termios tty;
        if (tcgetattr(serial_port, &tty) != 0)
        {
            if (!serial_error_logged_)
            {
                perror("Error from tcgetattr");
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
            serial_port_ = -1;            // Reset the file descriptor
            serial_error_logged_ = false; // Reset the error flag when closing the serial port
        }
    }

    void initSerialPort()
    {
        if (serial_port_ != -1)
        {
            // Close the serial port before reopening
            cleanupSerialPort();
        }

        // Try both serial ports
        for (const char *port : {SERIAL_PORT_1, SERIAL_PORT_2, SERIAL_PORT_3, SERIAL_PORT_4})
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

        // Reset the error flag when the serial port is successfully opened
        serial_error_logged_ = false;
    }

    void serialCommunication()
    {
        // Check if the serial port is open
        if (serial_port_ == -1)
        {
            // Reinitialize the serial port if it is closed
            initSerialPort();
            return;
        }

        int frame_started = false;
        int frame_ended = false;
        int i = 0;
        char rx[BUFFER_SIZE];

        // Sensor values
        int ir_sensor1_value, ir_sensor2_value, ir_sensor3_value, ir_sensor4_value;
        int smoke_sensor1_value, smoke_sensor2_value;

        char buf;

        // Read from serial port
        while (frame_ended == false)
        {
            // Read one byte at a time
            ssize_t bytesRead = read(serial_port_, &buf, 1);

            // Check for error or end of file
            if (bytesRead < 0)
            {
                // Check if the error is ENXIO (No such device or address), indicating a potential unplugging of the USB device
                if (errno == ENXIO)
                {
                    if (!serial_error_logged_)
                    {
                        RCLCPP_WARN(this->get_logger(), "Error reading: %s. Reinitializing serial port.", strerror(errno));
                        serial_error_logged_ = true;
                    }
                    initSerialPort();
                    return;
                }

                if (!serial_error_logged_)
                {
                    RCLCPP_ERROR(this->get_logger(), "Error reading");
                    serial_error_logged_ = true;
                }
                cleanupSerialPort();
                return;
            }
            else if (bytesRead == 0)
            {
                // End of file (USB device unplugged)
                if (!serial_error_logged_)
                {
                    RCLCPP_WARN(this->get_logger(), "End of file. Reinitializing serial port.");
                    serial_error_logged_ = true;
                }
                initSerialPort();
                return;
            }

            // Check for start of frame
            if (!frame_started && buf == START_OF_FRAME)
            {
                frame_started = true;
                i = 0;
            }
            // Check for end of frame
            else if (frame_started && buf == END_OF_FRAME)
            {
                frame_started = false;
                frame_ended = true;
                rx[i] = '\0';

                // Check frame length before processing
                if (strlen(rx) <= 90)
                {
                    if (!serial_error_logged_)
                    {
                        RCLCPP_WARN(this->get_logger(), "Received frame is too short. Ignoring the frame.");
                        serial_error_logged_ = true;
                    }
                }
                else
                {
                    // Print received byte
                    //RCLCPP_INFO(this->get_logger(), "Received Data: %s", rx);

                    // Process the complete frame (e.g., parse and publish)
                    sscanf(rx, "IR_SENSOR1=%d|IR_SENSOR2=%d|IR_SENSOR3=%d|IR_SENSOR4=%d|SMOKE_SENSOR1=%d|SMOKE_SENSOR2=%d",
                           &ir_sensor1_value, &ir_sensor2_value, &ir_sensor3_value, &ir_sensor4_value, &smoke_sensor1_value, &smoke_sensor2_value);

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
            // Store bytes in the frame buffer
            else if (frame_started)
            {
                if (i < BUFFER_SIZE - 1) // Ensure there is space in the buffer
                {
                    rx[i] = buf;
                    i++;
                }
                else
                {
                    if (!serial_error_logged_)
                    {
                        RCLCPP_WARN(this->get_logger(), "Buffer overflow detected. Frame will be ignored.");
                        serial_error_logged_ = true;
                    }
                    frame_started = false;
                }
            }
        }
    }

    int serial_port_;
    bool serial_error_logged_;
    std::shared_ptr<rclcpp::Publisher<interfaces::msg::FireSensor>> publisher_serial_reading;
    std::shared_ptr<rclcpp::TimerBase> timer_serial_reading;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<SerialReadingNode>();

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
