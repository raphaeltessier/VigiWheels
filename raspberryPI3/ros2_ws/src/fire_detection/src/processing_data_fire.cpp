#include <vector>
#include <cmath> 
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "interfaces/msg/fire_sensor.hpp"


class ProcessingDataFireNode : public rclcpp::Node
{
public:
    ProcessingDataFireNode() : Node("processing_data_fire_node"), window_size_{100}, counter_{0}
    {
        buffer_.resize(window_size_, 0);
        subscription_processing_data = this->create_subscription<interfaces::msg::FireSensor>("data_fire", 10, std::bind(&ProcessingDataFireNode::dataFireCallBack, this, std::placeholders::_1)
        );
    }

private:
    int processSensorData(int sensorValue)
    {
        if (counter_ < window_size_) 
        {
            buffer_[counter_] = sensorValue;
            counter_++;
            return 0; // Not enough data for processing
        } 
        else 
        {
            // Update the buffer with the new sensor value
            buffer_[counter_ % window_size_] = sensorValue;
            counter_++;

            // Calculate the moving average
            double movingAverage = calculateMovingAverage();

            // Calculate the standard deviation
            double standardDeviation = calculateStandardDeviation();

            // Set dynamic thresholds
            double lowerThreshold = movingAverage - 2 * standardDeviation;

            if (lowerThreshold < 100) 
            {
                return 1; // Fire detected
            }
            else 
            {
                return 0; // No fire detected
            }
        }
    }

    void dataFireCallBack(const interfaces::msg::FireSensor & msg)
    {
        int result1 = processSensorData(msg.ir_sensor1);
        int result2 = msg.ir_sensor2; 
        //int result3 = processSensorData(msg.ir_sensor3);
        //int result4 = msg.ir_sensor4; 
    
        if (result1 == 1 || result2 == 1) 
        {
            RCLCPP_INFO(this->get_logger(), "Fire detected!");
        }
    }   

    double calculateMovingAverage() const
    {
        double sum = 0.0;
        for (int value : buffer_) {
            sum += value;
        }
        return sum / window_size_;
    }

    double calculateStandardDeviation() const
    {
        double sumSquaredDifferences = 0.0;
        double average = calculateMovingAverage();

        for (int value : buffer_) {
            sumSquaredDifferences += std::pow(value - average, 2);
        }

        return std::sqrt(sumSquaredDifferences / window_size_);
    }

    size_t window_size_;
    size_t counter_;
    std::vector<int> buffer_;
    rclcpp::Subscription<interfaces::msg::FireSensor>::SharedPtr subscription_processing_data;
};

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv); 

    auto Node = std::make_shared<ProcessingDataFireNode>(); 

    rclcpp::spin(Node);  
    rclcpp::shutdown();   
}