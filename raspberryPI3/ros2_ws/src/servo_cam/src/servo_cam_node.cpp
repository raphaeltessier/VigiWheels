#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>
#include <fstream>
#include <ctime>
#include <string.h>

#include "interfaces/msg/servo_cam_order.hpp"
#include "interfaces/msg/cam_pos_order.hpp"
#include "interfaces/msg/manometer_info.hpp"
#include "interfaces/msg/joystick_order.hpp"

#include "std_srvs/srv/empty.hpp"

#include "../include/servo_cam/servo_cam_node.h"


using namespace std;
using namespace std::chrono;
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

        subscription_joystick_order_ = this->create_subscription<interfaces::msg::JoystickOrder>(
        "joystick_order", 10, std::bind(&servo_cam::joystickOrderCallback, this, _1));

        //periodic function
        timer_ = this->create_wall_timer(PERIOD_UPDATE_CMD, std::bind(&servo_cam::updateCmd, this));
        timer_auto_ = this->create_wall_timer(PERIOD_HIGH_CLK, std::bind(&servo_cam::updateAuto, this));
        

        // Set PWM frequency and duty cycle



        RCLCPP_INFO(this->get_logger(), "servo_cam_node READY");
    }

    
private:



    /* Update mode and pwm from cam pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/cam_pos_order" topic
    * only if mode manual
    * 
    */
    void camPosOrderCallback(const interfaces::msg::CamPosOrder & pos_cmd){
        if (car_mode == 0) {
            if (mode != pos_cmd.mode) {
                mode = pos_cmd.mode; // 0 : manual ; 1 : scan
                if (mode == 0) {
                    RCLCPP_INFO(this->get_logger(), "CAMERA in MANUAL mode");
                }
                else if (mode == 1) {
                    RCLCPP_INFO(this->get_logger(), "CAMERA in SCAN mode");
                }
            }
            turn = pos_cmd.turn_cam;
        }
    }

         //periodic function, see servo_cam_node.h to set period -> 1ms
    // to read the .txt data

    void updateAuto(){

        if (car_mode == 1 && car_start && !playing) { //start replay mode
            if (startPlaying() != -1) {
                playing = true;
            }
        }
        else if ((car_mode != 1 || !car_start) && playing) { //stop replay mode 
            playing = false;
            file.close();
        }
        else if (playing) {
            duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - t_start);
            if (time_span.count() >= time_stamp) { //if timing is ok 
                file >> mode >> turn; //update command
                file.ignore(256, '\n');
                if (!file.eof()) {
                    file >> time_stamp; //update commant timing
                }
                else {
                    playing = false; //close the file at it end
                    file.close();
                }
            }

        }
        

     }

    //open the ifstream
    int startPlaying() {
        ifstream to_run;
        
        to_run.open("/home/pi/path/file_to_run.txt", ifstream::in); //open fil where name of instruction file is store
        if(!to_run) {
            RCLCPP_ERROR(this->get_logger(), "Error while opening save name file");
            return -1;
        }
        else {
            char c_name[20];
            to_run.getline(c_name, 20); //reading instruction txt file name
            to_run.close();

            string name = "/home/pi/path/memory/" + string(c_name) + "_cam.txt";
            file.open(name.c_str());//opening instruction file for the camera

            if(!file) {
                RCLCPP_ERROR(this->get_logger(), "Error while opening record file");
                return -1;
            }
            else {
                string msg = "Start playing " + name;
                RCLCPP_INFO(this->get_logger(), msg.c_str());
                t_start = steady_clock::now(); //get time origin
                if(!file.eof()) {
                    file >> time_stamp; // get first instruction timing
                }
                else {
                    RCLCPP_ERROR(this->get_logger(), "Empty file");
                    return -1;

                }
                return 0;
            }
        }


        

        
        
        
    }

    /* Update mode from joystick order [callback function]  :
    *
    * This function is called when a message is published on the "/joystick_order" topic
    * 
    */
    void joystickOrderCallback(const interfaces::msg::JoystickOrder & joyOrder) {

        car_mode = joyOrder.mode;
        car_start = joyOrder.start;
        }
    

    /* Update image position for follow from image pos order feedback [callback function]  :
    *
    * This function is called when a message is published on the "/ManometerInfo" topic
    * 
    */
    void ImagePosCallback(const interfaces::msg::ManometerInfo & pos_image){
        x1 = pos_image.x1;
        x2 = pos_image.x2;
        mano_update = 1;
    }


 //periodic function, see servo_cam_node.h to set period -> 10ms
    // to update the angular positon of the camera 

    void updateCmd(){

        if (car_start) {
            auto servoOrder = interfaces::msg::ServoCamOrder();
            if (mano_update) { //if we have something to follow
                    mano_update = 0;
                    float mean = (x1 + x2)/2 -320;
                    //float correction = (mean > 0) ? PAS_FOLLOW : (-PAS_FOLLOW);
                    float correction = mean * FOV/RESOLUTION;
                    command_angle += int(correction);
            }
            else if (mode == 0) { //manual mode
            command_angle = command_angle + turn*PAS_MANUAL;

            }
            else if (mode == 1) { //scan mode
                command_angle = command_angle + sens;    
            }

            if (command_angle >= 180) {
                command_angle = 180; //saturation
                sens = -PAS_SCAN; //reverse direction for scan mode
            } 
            else if (command_angle <= 0) {
                command_angle = 0; //saturation
                sens = PAS_SCAN;  //reverse direction for scan mode
            } 

            servoOrder.servo_cam_angle = command_angle;



            publisher_servo_cam_order_->publish(servoOrder);
        }
        

     }



   
   
    // ---- Private variables ----

    //General variables
        int mode = 0;
        int turn = 0;
        int command_angle = 90; //[0, 180]
        int sens = PAS_SCAN; //{-10; 10}
        bool mano_update = 0;

        float x1;
        float x2;

        float facteur = RESOLUTION/FOV;

        int car_mode = 0;
        bool car_start = false;

        bool playing = false;

        double time_stamp;


        //file
        ifstream file;

        //timing data
        steady_clock::time_point t_start;
        duration<double> time_span;


        
        


    //Publishers
    rclcpp::Publisher<interfaces::msg::ServoCamOrder>::SharedPtr publisher_servo_cam_order_;

    //Suscribers
    rclcpp::Subscription<interfaces::msg::CamPosOrder>::SharedPtr subscription_cam_pos_order_;
    rclcpp::Subscription<interfaces::msg::ManometerInfo>::SharedPtr subscription_manometer_order_;  
    rclcpp::Subscription<interfaces::msg::JoystickOrder>::SharedPtr subscription_joystick_order_;

    //Timer
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::TimerBase::SharedPtr timer_auto_;




};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<servo_cam>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}

