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

        publisher_obstacles_order_= this->create_publisher<interfaces::msg::ObstaclesOrder>("obstacles_order", 10);

    

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
        steer = joyOrder.steer;
        
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

        int dist_left = DIST_DETECT_SIDE_BASE - steer * DIST_DETECT_SIDE_PENTE;
        int dist_right = DIST_DETECT_SIDE_BASE + steer * DIST_DETECT_SIDE_PENTE;

        bool dist_av_is_ok = (front_left > dist_left) & (front_right > dist_right) & (front_center > DIST_DETECT_CENTER);
        bool dist_ar_is_ok = (rear_left > dist_left) & (rear_right > dist_right) & (rear_center > DIST_DETECT_CENTER);


        auto obstaclesOrderMsg = interfaces::msg::ObstaclesOrder();
        
        obstaclesOrderMsg.front_object = !dist_av_is_ok;
        obstaclesOrderMsg.rear_object = !dist_ar_is_ok;
        
        publisher_obstacles_order_->publish(obstaclesOrderMsg);



    
    }


   
    // ---- Private variables ----

    //General variables
        bool reverse = 0;
        int mode = 0;
        float steer = 0;



        


    //Publishers
    rclcpp::Publisher<interfaces::msg::ObstaclesOrder>::SharedPtr publisher_obstacles_order_;

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

