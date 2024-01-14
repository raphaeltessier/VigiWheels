#include <vector>
#include <cmath>
#include "rclcpp/rclcpp.hpp"

#include "interfaces/msg/fire_sensor.hpp"
#include "interfaces/msg/emergency_alert_fire.hpp"

class ProcessingDataFireNode : public rclcpp::Node
{
public:

    ProcessingDataFireNode() : Node("processing_data_fire_node"), fireIsDetected{false}, FrontRightIRSensor{false}, FrontLeftIRSensor{false}, RearRightIRSensor{false}, RearLeftIRSensor{false}, RightSmokeSensor{false}, LeftSmokeSensor{false}

    {
        RCLCPP_INFO(this->get_logger(), "Hello Processing Data Fire Node !");
        subscription_data_fire = this->create_subscription<interfaces::msg::FireSensor>("data_fire", 10, std::bind(&ProcessingDataFireNode::dataFireCallBack, this, std::placeholders::_1));
        publisher_processing_data = this->create_publisher<interfaces::msg::EmergencyAlertFire>("emergency_alert", 10);
        timer_proccesing_data = this->create_wall_timer(std::chrono::milliseconds(250), bind(&ProcessingDataFireNode::sendEmergencyAltert, this));
    }

private:

    int processFireSensorData(int sensorValue)
    {
        if (sensorValue < 100)
        {
            return 1; // Fire detected
        }
        else
        {
            return 0; // No fire detected
        }
    }

    int processSmokeSensorData(int sensorValue)

    {
        if (sensorValue > 1000)
        {
            return 1; // Fire detected
        }
        else
        {
            return 0; // No fire detected
        }
    }

    void dataFireCallBack(const interfaces::msg::FireSensor &msg)
    {

        bool result1 = processFireSensorData(msg.ir_sensor1); // Avant Droit
        bool result2 = msg.ir_sensor2;                      // Avant Gauche
        bool result3 = processFireSensorData(msg.ir_sensor3); // Arrière Gauche
        bool result4 = msg.ir_sensor4;                      // Arrière Droite
        bool result5 = processSmokeSensorData(msg.smoke_sensor1);
        bool result6 = processSmokeSensorData(msg.smoke_sensor2);

       
       /*
        std::string logMessage = "Received Data: " +
                                 std::to_string(result1) +
                                 ", " + std::to_string(result2) +
                                 ", " + std::to_string(result3) +
                                 ", " + std::to_string(result4) +
                                 ", " + std::to_string(result5) +
                                 ", " + std::to_string(result6);

        RCLCPP_INFO(this->get_logger(), "%s", logMessage.c_str());
        */ 

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