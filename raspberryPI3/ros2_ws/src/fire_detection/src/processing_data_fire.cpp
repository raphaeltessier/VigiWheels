#include <vector>
#include <cmath> 
#include "rclcpp/rclcpp.hpp"

#include "interfaces/msg/fire_sensor.hpp"
#include "interfaces/msg/emergency_alert_fire.hpp"

class ProcessingDataFireNode : public rclcpp::Node
{
public:
    ProcessingDataFireNode() : Node("processing_data_fire_node"), fireIsDetected{false},  FrontRightIRSensor{false}, FrontLeftIRSensor{false}, RearRightIRSensor{false}, RearLeftIRSensor{false}, RightSmokeSensor{false}, LeftSmokeSensor{false}, window_size_{100}, counter_{0}
    {
        RCLCPP_INFO(this->get_logger(), "Hello Processing Data Fire Node !");
        buffer_.resize(window_size_, 0);
        subscription_data_fire = this->create_subscription<interfaces::msg::FireSensor>("data_fire", 10, std::bind(&ProcessingDataFireNode::dataFireCallBack, this, std::placeholders::_1));
        publisher_processing_data = this->create_publisher<interfaces::msg::EmergencyAlertFire>("emergency_alert", 10);
        timer_proccesing_data = this->create_wall_timer(std::chrono::milliseconds(250), bind(&ProcessingDataFireNode::sendEmergencyAltert, this)); 
    }

private:
    int processIRSensorData(int sensorValue)
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

    int processSmokeSensorData(int sensorValue)
    {
        if (sensorValue > 800) 
        {
            return 1; // Fire detected
        }
        else 
        {
            return 0; // No fire detected
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
        bool result1 = processIRSensorData(msg.ir_sensor1); //Avant Droit 
        bool result2 = msg.ir_sensor2; //Avant Gauche 
        bool result3 = processIRSensorData(msg.ir_sensor3); //Arrière Gauche 
        bool result4 = msg.ir_sensor4; //Arrière Droit 
        bool result5 = processSmokeSensorData(msg.smoke_sensor1);
        bool result6 = processSmokeSensorData(msg.smoke_sensor2);
    
        if (result1 == 1)
        {
            FrontRightIRSensor = true; 
            fireIsDetected = true; 
        }
        else if (result2 == 1)
        {
            FrontLeftIRSensor = true; 
            fireIsDetected = true; 
        }
        else if (result3 == 1)
        {
            RearLeftIRSensor = true; 
            fireIsDetected = true; 
        }
        else if (result4 == 1)
        {
            RearRightIRSensor = true; 
            fireIsDetected = true; 
        }
        else if (result5 == 1)
        {
            RightSmokeSensor = true; 
            fireIsDetected = true; 
        }
        else if (result6 == 1)
        {
            LeftSmokeSensor = true; 
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
        msg.ir_front_right = FrontRightIRSensor; 
        msg.ir_front_left = FrontLeftIRSensor; 
        msg.ir_rear_right = RearRightIRSensor; 
        msg.ir_rear_left = RearLeftIRSensor; 
        msg.smoke_right = RightSmokeSensor; 
        msg.smoke_left = LeftSmokeSensor; 
        publisher_processing_data->publish(msg);
    }

    bool fireIsDetected; 
    bool FrontRightIRSensor; 
    bool FrontLeftIRSensor; 
    bool RearRightIRSensor; 
    bool RearLeftIRSensor; 
    bool RightSmokeSensor; 
    bool LeftSmokeSensor; 
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