#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "interfaces/msg/servo_cam_order.hpp"
#include "interfaces/msg/cam_pos_order.hpp"
#include "interfaces/msg/manometer_info.hpp"

#include "std_srvs/srv/empty.hpp"

#include "../include/servo_cam/servo_cam_node.h"

using namespace std;
using placeholders::_1;

//take command from cam_pos_order and send angle info to the can node to be transmit to nucleo F106


class servo_cam : public rclcpp::Node {

public:
    servo_cam()
    : Node("servo_cam_node")
    {
        //publisher
        publisher_servo_cam_order_= this->create_publisher<interfaces::msg::ServoCamOrder>("servo_cam_order", 10);

    
        //suscriber
        subscription_cam_pos_order_ = this->create_subscription<interfaces::msg::CamPosOrder>(
        "cam_pos_order", 10, std::bind(&servo_cam::camPosOrderCallback, this, _1));

        subscription_manometer_order_ = this->create_subscription<interfaces::msg::ManometerInfo>(
        "manometer_detected", 10, std::bind(&servo_cam::ImagePosCallback, this, _1));


        //periodic function
        timer_ = this->create_wall_timer(PERIOD_UPDATE_CMD, std::bind(&servo_cam::updateCmd, this));
        

        // Set PWM frequency and duty cycle



        RCLCPP_INFO(this->get_logger(), "servo_cam_node READY");
    }

    
private:



    /* Update mode and pwm from cam pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/cam_pos_order" topic
    * 
    */
    void camPosOrderCallback(const interfaces::msg::CamPosOrder & pos_cmd){
        mode = pos_cmd.mode; // 0 : fixed ; 1 : scan
        requested_angle = pos_cmd.cam_angle;
    }


    /* Update image position for mode 2 from image pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/ManometerInfo" topic
    * 
    */
    void ImagePosCallback(const interfaces::msg::ManometerInfo & pos_image){
        x1 = pos_image.x1;
        x2 = pos_image.x2;
        mano_update = 1;
    }


 //periodic function, see servo_cam_node.h to set period -> 100ms
    // to update the angular positon of the camera to scan

    void updateCmd(){

        auto servoOrder = interfaces::msg::ServoCamOrder();

        if (mode == 1) {
            command_angle = command_angle + sens;
            if (command_angle >= 180) {
                command_angle = 180;
                sens = -sens;
            }
            else if (command_angle <= 0) {
                command_angle = 0;
                sens = -sens;
            }
            
        }
        else if (mode == 2){
            if (mano_update) {
                float mean = (x1 + x2)/2 -320;
                float correction = mean*FOV/RESOLUTION;
                command_angle += int(correction);
                if (command_angle >= 180) {command_angle = 180;} //saturation
                else if (command_angle <= 0) {command_angle = 0;} //saturation
            }

        }

        else {
            command_angle = requested_angle;
        }


        servoOrder.servo_cam_angle = command_angle;



        publisher_servo_cam_order_->publish(servoOrder);

        

     }
   
    // ---- Private variables ----

    //General variables
        int mode = 0;
        int requested_angle;
        int command_angle = 90; //[0, 180]
        int sens = PAS_SCAN; //{-10; 10}
        bool mano_update = 0;

        float x1;
        float x2;

        float facteur = RESOLUTION/FOV;



        
        


    //Publishers
    rclcpp::Publisher<interfaces::msg::ServoCamOrder>::SharedPtr publisher_servo_cam_order_;

    //Suscribers
    rclcpp::Subscription<interfaces::msg::CamPosOrder>::SharedPtr subscription_cam_pos_order_;
    rclcpp::Subscription<interfaces::msg::ManometerInfo>::SharedPtr subscription_manometer_order_;  

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

