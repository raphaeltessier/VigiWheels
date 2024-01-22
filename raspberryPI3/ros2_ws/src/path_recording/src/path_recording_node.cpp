#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <fstream>
#include <ctime>
#include <string.h> 

#include "interfaces/msg/cam_pos_order.hpp"
#include "interfaces/msg/joystick_order.hpp"
#include "interfaces/msg/obstacles_order.hpp"


#include "std_srvs/srv/empty.hpp"

#include "../include/path_recording/path_recording_node.h"

using namespace std;
using namespace std::chrono;
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

        subscription_obstacles_order_ = this->create_subscription<interfaces::msg::ObstaclesOrder>(
        "obstacles_order", 10, std::bind(&path_recording::obstaclesOrderCallback, this, _1));


        RCLCPP_INFO(this->get_logger(), "path_node READY");
    }

    
private:

    /* Update front and rear obstacles prensence from Obstacles_order  :
    *
    * This function is called when a message is published on the "/mobstacles_order" topic
    * 
    */
    void obstaclesOrderCallback(const interfaces::msg::ObstaclesOrder & obstacles_order){
        obstacles_front = obstacles_order.front_object;
        obstacles_rear = obstacles_order.rear_object;
    }

    /* Update mode and pwm from cam pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/cam_pos_order" topic
    * 
    */
    void camPosOrderCallback(const interfaces::msg::CamPosOrder & pos_cmd){
        if (recording) {
            time_span_cam = duration_cast<duration<double>>(steady_clock::now() - t_start); //compute timing of the callback
            cam_data << time_span_cam.count() << " " << (int)pos_cmd.mode << " " << pos_cmd.turn_cam << endl; //store data in txt file
            
        }

    }


    /* Update start, mode, requestedThrottle, requestedSteerAngle and reverse from joystick order [callback function]  :
    *
    * This function is called when a message is published on the "/joystick_order" topic
    * 
    */
    void joystickOrderCallback(const interfaces::msg::JoystickOrder & joyOrder){
        if (joyOrder.record_path && !prev_buttonX && (!recording) && joyOrder.start && (joyOrder.mode == 0)) {
            //run the record if request and start and manual mode, when rising edge of record request
            if (startRecord() != -1) {
                recording = true;
                RCLCPP_INFO(this->get_logger(), "Start recording, record will stop when pushing X, changing mode, or detecting obstacle");
            }
        }
        else if (((joyOrder.record_path && !prev_buttonX) || (!joyOrder.start) || (joyOrder.mode != 0) || 
                                    (joyOrder.reverse && obstacles_rear) || (!joyOrder.reverse && obstacles_front)) && recording ){ 
            //stop the record if request or stop or autonomous/calibrating mode
            stopRecording();
            recording = false;
            RCLCPP_INFO(this->get_logger(), "Record stopped");

        }
        else if (recording) {
            time_span_car = duration_cast<duration<double>>(steady_clock::now() - t_start); //compute timing of the callback
            car_data << time_span_car.count() << " " << joyOrder.throttle << " " << joyOrder.steer <<  " " << joyOrder.reverse << endl; //store data in txt file
            
        }




        prev_buttonX = joyOrder.record_path;
    }


    //start two ofstream flux in /home/pi/path/DD-MM-YYYY_HH-MM-SS_cam.txt (and _car)
    int startRecord() {
        string date = getDate();
        string name_car = "/home/pi/path/memory/" + date + "_car.txt";
        string name_cam = "/home/pi/path/memory/" + date + "_cam.txt";

        car_data.open(name_car.c_str(), ofstream::out | ofstream::app);
        cam_data.open(name_cam.c_str(), ofstream::out | ofstream::app);
        
        if(!car_data || !cam_data) {
            RCLCPP_ERROR(this->get_logger(), "Error while creating saving files");
            recording = false;
            return -1;
        }
        else {
            ofstream to_run;
            to_run.open("/home/pi/path/file_to_run.txt", ofstream::out | ofstream::trunc); //open fil where name of instruction file is store
            if(to_run) {
                to_run << date << flush;
                to_run.close();
            }
            else {
                RCLCPP_ERROR(this->get_logger(), "Error while editing record path in file_to_run");
            }

            string msg = "Camera command will be save in " + name_cam;
            RCLCPP_INFO(this->get_logger(), msg.c_str());
            msg = "Camera command will be save in " + name_car;
            RCLCPP_INFO(this->get_logger(), msg.c_str());

            t_start = steady_clock::now();
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
        auto today = system_clock::now();
        time_t now_c = system_clock::to_time_t(today);
        tm * ptm = localtime(&now_c);
        char buffer[20];
        strftime(buffer, 20, "%d-%m-%Y_%H-%M-%S", ptm); 
        return buffer;
    }
        



   
    // ---- Private variables ----

    //General variables
    bool recording = false;
    bool prev_buttonX = false;

    //obstacles variables
    bool obstacles_front;
    bool obstacles_rear;

    //Car variables
    bool reverse;    

    
    //timing data
    steady_clock::time_point t_start;
    duration<double> time_span_car;
    duration<double> time_span_cam;
        
        


    //Publishers

    //Suscribers
    rclcpp::Subscription<interfaces::msg::CamPosOrder>::SharedPtr subscription_cam_pos_order_;
    rclcpp::Subscription<interfaces::msg::JoystickOrder>::SharedPtr subscription_joystick_order_;
    rclcpp::Subscription<interfaces::msg::ObstaclesOrder>::SharedPtr subscription_obstacles_order_; 

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

