#include <vector>
#include <cmath> 
#include "rclcpp/rclcpp.hpp"

#include "interfaces/msg/fire_sensor.hpp"
#include "interfaces/msg/emergency_alert_fire.hpp"

class ProcessingDataFireNode : public rclcpp::Node
{
public:
    ProcessingDataFireNode() : Node("processing_data_fire_node"), fireIsDetected{false},  FrontRightSensor{false}, FrontLeftSensor{false}, RearRightSensor{false}, RearLeftSensor{false} , window_size_{100}, counter_{0}
    {
        RCLCPP_INFO(this->get_logger(), "Hello Processing Data Fire Node !");
        buffer_.resize(window_size_, 0);
        subscription_data_fire = this->create_subscription<interfaces::msg::FireSensor>("data_fire", 10, std::bind(&ProcessingDataFireNode::dataFireCallBack, this, std::placeholders::_1));
        publisher_processing_data = this->create_publisher<interfaces::msg::EmergencyAlertFire>("emergency_alert", 10);
        timer_proccesing_data = this->create_wall_timer(std::chrono::milliseconds(250), bind(&ProcessingDataFireNode::sendEmergencyAltert, this)); 
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

            if (lowerThreshold < 150) 
            {
                return 1; // Fire detected
            }
            else 
            {
                return 0; // No fire detected
            }
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

        for (int value : buffer_) 
        {
            sumSquaredDifferences += std::pow(value - average, 2);
        }
        return std::sqrt(sumSquaredDifferences / window_size_);
    }

    void dataFireCallBack(const interfaces::msg::FireSensor & msg)
    {
        int result1 = processSensorData(msg.ir_sensor1); //Avant Droit 
        bool result2 = msg.ir_sensor2; //Avant Gauche 
        int result3 = processSensorData(msg.ir_sensor3); //Arrière Gauche 
        int result4 = msg.ir_sensor4; //Arrière Droit 
    
        if (result1 == 1)
        {
            FrontRightSensor = true; 
            fireIsDetected = true; 
        }
        else if (result2 == 1)
        {
            FrontLeftSensor = true; 
            fireIsDetected = true; 
        }
        else if (result3 == 1)
        {
            RearLeftSensor = true; 
            fireIsDetected = true; 
        }
        else if (result4 == 1)
        {
            RearRightSensor = true; 
            fireIsDetected = true; 
        }
        else
        {
            fireIsDetected = false; 
        }
    } 

    void sendEmergencyAltert()
    {
        auto msg = interfaces::msg::EmergencyAlertFire();
        msg.fire_detected = fireIsDetected;
        msg.ir_front_right = FrontRightSensor; 
        msg.ir_front_left = FrontLeftSensor; 
        msg.ir_rear_right = RearRightSensor; 
        msg.ir_rear_left = RearLeftSensor; 
        publisher_processing_data->publish(msg);
    }

    bool fireIsDetected; 
    bool FrontRightSensor; 
    bool FrontLeftSensor; 
    bool RearRightSensor; 
    bool RearLeftSensor; 
    size_t window_size_;
    size_t counter_;
    std::vector<int> buffer_;
    std::shared_ptr<rclcpp::Publisher<interfaces::msg::EmergencyAlertFire>> publisher_processing_data;
    std::shared_ptr<rclcpp::TimerBase> timer_proccesing_data;
    rclcpp::Subscription<interfaces::msg::FireSensor>::SharedPtr subscription_data_fire;
};

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv); 

    auto Node = std::make_shared<ProcessingDataFireNode>(); 

    rclcpp::spin(Node);  
    rclcpp::shutdown();   
}