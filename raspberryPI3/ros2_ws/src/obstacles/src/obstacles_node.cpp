#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "interfaces/msg/ultrasonic.hpp"
#include "interfaces/msg/joystick_order.hpp"

#include "std_srvs/srv/empty.hpp"

#include "../include/obstacles/obstacles_node.h"

using namespace std;
using placeholders::_1;


class obstacles : public rclcpp::Node {

public:
    obstacles()
    : Node("obstacles_node")
    {

        publisher_joystick_order_= this->create_publisher<interfaces::msg::JoystickOrder>("joystick_order", 10);

    

        subscription_joystick_order_ = this->create_subscription<interfaces::msg::JoystickOrder>(
        "joystick_order", 10, std::bind(&obstacles::joystickOrderCallback, this, _1));

        subscription_us_data_ = this->create_subscription<interfaces::msg::Ultrasonic>(
        "us_data", 10, std::bind(&obstacles::ultrasonicFeedbackCallback, this, _1));

        
        RCLCPP_INFO(this->get_logger(), "obstacles_node READY");
    }

    
private:
   
    /* Update mode and reverse from joystick order [callback function]  :
    *
    * This function is called when a message is published on the "/joystick_order" topic
    * 
    */
    void joystickOrderCallback(const interfaces::msg::JoystickOrder & joyOrder) {

        reverse = joyOrder.reverse;
        mode = joyOrder.mode;
        
    }

    /* Update currentAngle from motors feedback [callback function]  :
    *
    * This function is called when a message is published on the "/us_data" topic
    * 
    */
    void ultrasonicFeedbackCallback(const interfaces::msg::Ultrasonic & Ultrasonic){

        int front_left = Ultrasonic.front_left;
        int front_center = Ultrasonic.front_center;
        int front_right = Ultrasonic.front_right;

        int rear_left = Ultrasonic.rear_left;
        int rear_center = Ultrasonic.rear_center;
        int rear_right = Ultrasonic.rear_right;

        bool dist_av_is_ok = (front_left > 100) & (front_right > 100) & (front_center > 100);
        bool dist_ar_is_ok = (rear_left > 100) & (rear_right > 100) & (rear_center > 100);

        if ((reverse & !dist_ar_is_ok) | (!reverse & !dist_av_is_ok)) {

            auto joystickOrderMsg = interfaces::msg::JoystickOrder();
            joystickOrderMsg.start = start;
            joystickOrderMsg.mode = mode;
            joystickOrderMsg.throttle = throttle;
            joystickOrderMsg.steer  = steer;
            joystickOrderMsg.reverse = reverse;
            

            RCLCPP_INFO(this->get_logger(), "obstacles detected");
            publisher_joystick_order_->publish(joystickOrderMsg);

        }


    
    }


   
    // ---- Private variables ----

    //General variables
        bool start = 0;
        bool reverse = 0;
        int mode = 0;
        float throttle = 0.5;
        float steer = 0;



        


    //Publishers
    rclcpp::Publisher<interfaces::msg::JoystickOrder>::SharedPtr publisher_joystick_order_;

    //Subscribers
    rclcpp::Subscription<interfaces::msg::JoystickOrder>::SharedPtr subscription_joystick_order_;
    rclcpp::Subscription<interfaces::msg::Ultrasonic>::SharedPtr subscription_us_data_;


};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<obstacles>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}

