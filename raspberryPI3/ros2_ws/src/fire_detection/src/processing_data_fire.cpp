#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
#include "interfaces/msg/fire_sensor.hpp"

class ProcessingDataFireNode : public rclcpp::Node
{
public: 
    ProcessingDataFireNode() : Node("processing_data_fire_node") 
    {
        subscription_processing_data = this->create_subscription<interfaces::msg::FireSensor>("data_fire", 10, bind(&ProcessingDataFireNode::dataFireCallBack, this, std::placeholders::_1)); 
    }
private: 

    void dataFireCallBack(const interfaces::msg::FireSensor & msg)
    {
        ir_sensor1_value = msg.ir_sensor1;
        ir_sensor2_value = msg.ir_sensor2;
        ir_sensor3_value = msg.ir_sensor3;
        ir_sensor4_value = msg.ir_sensor4;
        smoke_sensor1_value = msg.smoke_sensor1;
        smoke_sensor2_value = msg.smoke_sensor2; 

        if(ir_sensor2_value == 1 && ir_sensor1_value <= 350)
        {
            RCLCPP_INFO(get_logger(), "A fire is detected!");
        }
        else
        {
            RCLCPP_INFO(get_logger(), "Everything is fine!");
        }
    }
    
    int ir_sensor1_value;
    int ir_sensor2_value;
    int ir_sensor3_value;
    int ir_sensor4_value;
    int smoke_sensor1_value;
    int smoke_sensor2_value;

    rclcpp::Subscription<interfaces::msg::FireSensor>::SharedPtr subscription_processing_data;
}; 

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv); 

    auto Node = std::make_shared<ProcessingDataFireNode>(); 

    rclcpp::spin(Node);  
    rclcpp::shutdown();   
}