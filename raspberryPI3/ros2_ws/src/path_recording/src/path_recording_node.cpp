#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <fstream>
#include <ctime>
#include <string.h> 

#include "interfaces/msg/cam_pos_order.hpp"
#include "interfaces/msg/joystick_order.hpp"


#include "std_srvs/srv/empty.hpp"

#include "../include/path_recording/path_recording_node.h"

using namespace std;
using placeholders::_1;



class path_recording : public rclcpp::Node {

public:
    path_recording()
    : Node("path_recording_node")
    {
        //publisher

    
        //suscriber
        subscription_cam_pos_order_ = this->create_subscription<interfaces::msg::CamPosOrder>(
        "cam_pos_order", 10, std::bind(&path_recording::camPosOrderCallback, this, _1));

        subscription_joystick_order_ = this->create_subscription<interfaces::msg::JoystickOrder>(
        "joystick_order", 10, std::bind(&path_recording::joystickOrderCallback, this, _1));





        RCLCPP_INFO(this->get_logger(), "path_node READY");
    }

    
private:



    /* Update mode and pwm from cam pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/cam_pos_order" topic
    * 
    */
    void camPosOrderCallback(const interfaces::msg::CamPosOrder & pos_cmd){

    }


    /* Update start, mode, requestedThrottle, requestedSteerAngle and reverse from joystick order [callback function]  :
    *
    * This function is called when a message is published on the "/joystick_order" topic
    * 
    */
    void joystickOrderCallback(const interfaces::msg::JoystickOrder & joyOrder){
        if (joyOrder.record_path && !prev_buttonX && (!recording) && joyOrder.start && (joyOrder.mode == 0)) { 
            //run the record if request and start and manual mode
            recording = true;
            if (startRecord() != -1) {
                RCLCPP_INFO(this->get_logger(), "Start recording : use X button to stop record");
            }
        }
        else if (((joyOrder.record_path && !prev_buttonX) || (!joyOrder.start) || (joyOrder.mode != 0)) && recording ){ 
            //stop the record if request or stop or autonomous/calibrating mode
            stopRecording();
            recording = false;
            RCLCPP_INFO(this->get_logger(), "Record finish");

        }




        prev_buttonX = joyOrder.record_path;
    }


    //start two ofstream flux in /home/pi/path/DD-MM-YYYY_HH-MM-SS_cam.txt (and _car)
    int startRecord() {
        string date = getDate();
        string name_car = "/home/pi/path/" + date + "_car.txt";
        string name_cam = "/home/pi/path/" + date + "_cam.txt";

        car_data.open(name_car.c_str());
        cam_data.open(name_cam.c_str());
        
        if(!car_data || !cam_data) {
            RCLCPP_ERROR(this->get_logger(), "Error while creating saving files");
            recording = false;
            return -1;
        }
        else {
            string msg = "Camera command will be save in " + name_cam;
            RCLCPP_INFO(this->get_logger(), msg.c_str());
            msg = "Camera command will be save in " + name_car;
            RCLCPP_INFO(this->get_logger(), msg.c_str());
            return 0;
        }

    }


    //close the ofstream flux
    void stopRecording () {
        car_data.close();
        cam_data.close();
    }
        
    // return the date in string : "DD-MM-YYYY_HH-MM-SS"
    string getDate() {
        using chrono::system_clock;
        auto today = system_clock::now();
        time_t now_c = chrono::system_clock::to_time_t(today);
        tm * ptm = localtime(&now_c);
        char buffer[20];
        strftime(buffer, 20, "%d-%m-%Y_%H-%M-%S", ptm); 
        return buffer;
    }
        



   
    // ---- Private variables ----

    //General variables
    bool recording = false;
    bool prev_buttonX = false;

        
        


    //Publishers

    //Suscribers
    rclcpp::Subscription<interfaces::msg::CamPosOrder>::SharedPtr subscription_cam_pos_order_;
    rclcpp::Subscription<interfaces::msg::JoystickOrder>::SharedPtr subscription_joystick_order_;

    //fichier stockage
    ofstream car_data;
    ofstream cam_data;


};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<path_recording>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}

