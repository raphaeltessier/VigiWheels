#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "interfaces/msg/servo_cam_order.hpp"
#include "interfaces/msg/cam_pos_order.hpp"

#include "std_srvs/srv/empty.hpp"

#include "../include/servo_cam/servo_cam_node.h"

using namespace std;
using placeholders::_1;


class servo_cam : public rclcpp::Node {

public:
    servo_cam()
    : Node("servo_cam_node")
    {
        //publisher
        publisher_servo_cam_order_= this->create_publisher<interfaces::msg::ServoCamOrder>("servo_cam_order", 10);

    
        //suscriber
        subscription_motors_feedback_ = this->create_subscription<interfaces::msg::CamPosOrder>(
        "cam_pos_order", 10, std::bind(&servo_cam::camPosOrderCallback, this, _1));


        //periodic function
        timer_ = this->create_wall_timer(PERIOD_UPDATE_CMD, std::bind(&servo_cam::updateCmd, this));
        
        RCLCPP_INFO(this->get_logger(), "servo_cam_node READY");
    }

    
private:
   
    /* Update mode and pwm from cam pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/cam_pos_order" topic
    * 
    */
    void camPosOrderCallback(const interfaces::msg::CamPosOrder & pos_cmd){
        mode = pos_cmd.mode;
        pwm_cmd = pos_cmd.cam_pwm;
    }



 //periodic function ---------------------------------------------------

     void updateCmd(){

        auto servoOrder = interfaces::msg::ServoCamOrder();


        

     }
   
    // ---- Private variables ----

    //General variables

        


    //Publishers
    rclcpp::Publisher<interfaces::msg::ServoCamOrder>::SharedPtr publisher_servo_cam_order_;

    //Suscribers
    rclcpp::Subscription<interfaces::msg::CamPosOrder>::SharedPtr subscription_cam_pos_order_; 

    //Timer
    rclcpp::TimerBase::SharedPtr timer_;




};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<servo_cam>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}

