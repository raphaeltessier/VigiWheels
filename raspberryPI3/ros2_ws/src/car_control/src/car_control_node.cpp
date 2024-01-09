#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "interfaces/msg/motors_order.hpp"
#include "interfaces/msg/motors_feedback.hpp"
#include "interfaces/msg/steering_calibration.hpp"
#include "interfaces/msg/joystick_order.hpp"
#include "interfaces/msg/obstacles_order.hpp"

#include "std_srvs/srv/empty.hpp"

#include "../include/car_control/steeringCmd.h"
#include "../include/car_control/propulsionCmd.h"
#include "../include/car_control/car_control_node.h"
#include "../include/car_control/controlCmd.h"

using namespace std;
using placeholders::_1;


class car_control : public rclcpp::Node {

public:
    car_control()
    : Node("car_control_node")
    {
        start = false;
        mode = 0;
        requestedThrottle = 0;
        requestedSteerAngle = 0;
    

        publisher_can_= this->create_publisher<interfaces::msg::MotorsOrder>("motors_order", 10);

        publisher_steeringCalibration_ = this->create_publisher<interfaces::msg::SteeringCalibration>("steering_calibration", 10);

        

        subscription_joystick_order_ = this->create_subscription<interfaces::msg::JoystickOrder>(
        "joystick_order", 10, std::bind(&car_control::joystickOrderCallback, this, _1));

        subscription_motors_feedback_ = this->create_subscription<interfaces::msg::MotorsFeedback>(
        "motors_feedback", 10, std::bind(&car_control::motorsFeedbackCallback, this, _1));

        subscription_steering_calibration_ = this->create_subscription<interfaces::msg::SteeringCalibration>(
        "steering_calibration", 10, std::bind(&car_control::steeringCalibrationCallback, this, _1));

        subscription_obstacles_order_ = this->create_subscription<interfaces::msg::ObstaclesOrder>(
        "obstacles_order", 10, std::bind(&car_control::obstaclesOrderCallback, this, _1));


        

        server_calibration_ = this->create_service<std_srvs::srv::Empty>(
                            "steering_calibration", std::bind(&car_control::steeringCalibration, this, std::placeholders::_1, std::placeholders::_2));

        timer_ = this->create_wall_timer(PERIOD_UPDATE_CMD, std::bind(&car_control::updateCmd, this));


        
        RCLCPP_INFO(this->get_logger(), "car_control_node READY");
    }

    
private:

    /* Update start, mode, requestedThrottle, requestedSteerAngle and reverse from joystick order [callback function]  :
    *
    * This function is called when a message is published on the "/joystick_order" topic
    * 
    */
    void joystickOrderCallback(const interfaces::msg::JoystickOrder & joyOrder) {

        if (joyOrder.start != start){
            start = joyOrder.start;

            if (start)
                RCLCPP_INFO(this->get_logger(), "START");
            else 
                RCLCPP_INFO(this->get_logger(), "STOP");
        }
        

        if (joyOrder.mode != mode && joyOrder.mode != -1){ //if mode change
            mode = joyOrder.mode;

            if (mode==0){
                RCLCPP_INFO(this->get_logger(), "Switching to MANUAL Mode");
            }else if (mode==1){
                RCLCPP_INFO(this->get_logger(), "Switching to AUTONOMOUS Mode");
            }else if (mode==2){
                RCLCPP_INFO(this->get_logger(), "Switching to STEERING CALIBRATION Mode");
                startSteeringCalibration();
            }
        }
        
        if (mode == 0 && start){  //if manual mode -> update requestedThrottle, requestedSteerAngle and reverse from joystick order
            requestedThrottle = joyOrder.throttle;
            requestedSteerAngle = joyOrder.steer;
            reverse = joyOrder.reverse;
        }
    }


    /* Update front and rear obstacles prensence from Obstacles_order  :
    *
    * This function is called when a message is published on the "/mobstacles_order" topic
    * 
    */
    void obstaclesOrderCallback(const interfaces::msg::ObstaclesOrder & obstacles_order){
        obstacles_front = obstacles_order.front_object;
        obstacles_rear = obstacles_order.rear_object;
    }



 
    /* Update currentAngle, left_rear from motors feedback [callback function]  :

    *
    * This function is called when a message is published on the "/motors_feedback" topic
    * 
    */
    void motorsFeedbackCallback(const interfaces::msg::MotorsFeedback & motorsFeedback){
        currentAngle = motorsFeedback.steering_angle;
        leftRearSpeedFeedback = motorsFeedback.left_rear_speed;
        rightRearSpeedFeedback = motorsFeedback.right_rear_speed;
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
            to_run.getline(c_root, 20); //reading instruction txt file name
            to_run.close();

            string name = "/home/pi/path/memory/" + string(c_name) + "_car.txt";
            file.open(name.c_str());//opening instruction file for the car

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


    /* Update PWM commands : leftRearPwmCmd, rightRearPwmCmd, steeringPwmCmd
    *
    * This function is called periodically by the timer [see PERIOD_UPDATE_CMD in "car_control_node.h"]
    * 
    * In MANUAL mode, the commands depends on :
    * - requestedThrottle, reverse, requestedSteerAngle [from joystick orders]
    * - currentAngle [from motors feedback]
    * - current RPM Speed of both motors 
    * 
    * In Auto mode, the commands depend on :
    * - consigne_Speed_Left/ consigne_Speed_Right, reverse_Auto [variables to be used by Nav2]
    * - current RPM Speed of both motors 
    * - static error of last iteration
    * - commanded value of last iteration
    */
    void updateCmd(){

        auto motorsOrder = interfaces::msg::MotorsOrder();

        if ((car_mode != 1 || !car_start) && playing) { //stop replay mode 
                playing = false;
                file.close();
        }

        if (!start){    //Car stopped
            leftRearPwmCmd = STOP;
            rightRearPwmCmd = STOP;
            steeringPwmCmd = STOP;

        }else{ //Car started

            if (mode == 1  && !playing) { //start replay mode
                if (startPlaying() != -1) {
                    playing = true;
                }
            }

            else if (playing) {
                duration<double> time_span = duration_cast<duration<double>>(steady_clock::now() - t_start);
                if (time_span.count() >= time_stamp) { //if timing is ok 
                    file >> requestedThrottle >> requestedSteerAngle >> reverse; //update command
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

            if (playing || mode == 0) {
                if ((reverse && obstacles_rear) | (!reverse && obstacles_front)){  // si obstacle dans notre direction

                    leftRearPwmCmd = STOP;
                    rightRearPwmCmd = STOP;
                    steeringPwmCmd = STOP;

                }
                else{
                    calculateRPM_Left_Auto(requestedThrottle, reverse, leftRearPwmCmd, leftRearSpeedFeedback,
                    lastError_L, correctedValue_L);

                    calculateRPM_Right_Auto(requestedThrottle, reverse, rightRearPwmCmd, rightRearSpeedFeedback,
                    lastError_R, correctedValue_R );

                        
                }
                steeringCmd(requestedSteerAngle,currentAngle, steeringPwmCmd);

            
                
            }
        }


        //Send order to motors
        motorsOrder.left_rear_pwm = leftRearPwmCmd;
        motorsOrder.right_rear_pwm = rightRearPwmCmd;
        motorsOrder.steering_pwm = steeringPwmCmd;

        publisher_can_->publish(motorsOrder);
    }


    /* Start the steering calibration process :
    *
    * Publish a calibration request on the "/steering_calibration" topic
    */
    void startSteeringCalibration(){

        auto calibrationMsg = interfaces::msg::SteeringCalibration();
        calibrationMsg.request = true;

        RCLCPP_INFO(this->get_logger(), "Sending calibration request .....");
        publisher_steeringCalibration_->publish(calibrationMsg);
    }


    /* Function called by "steering_calibration" service
    * 1. Switch to calibration mode
    * 2. Call startSteeringCalibration function
    */
    void steeringCalibration([[maybe_unused]] std_srvs::srv::Empty::Request::SharedPtr req,
                            [[maybe_unused]] std_srvs::srv::Empty::Response::SharedPtr res)
    {

        mode = 2;    //Switch to calibration mode
        RCLCPP_WARN(this->get_logger(), "Switching to STEERING CALIBRATION Mode");
        startSteeringCalibration();
    }
    

    /* Manage steering calibration process [callback function]  :
    *
    * This function is called when a message is published on the "/steering_calibration" topic
    */
    void steeringCalibrationCallback (const interfaces::msg::SteeringCalibration & calibrationMsg){

        if (calibrationMsg.in_progress == true && calibrationMsg.user_need == false){
        RCLCPP_INFO(this->get_logger(), "Steering Calibration in progress, please wait ....");

        } else if (calibrationMsg.in_progress == true && calibrationMsg.user_need == true){
            RCLCPP_WARN(this->get_logger(), "Please use the buttons (L/R) to center the steering wheels.\nThen, press the blue button on the NucleoF103 to continue");
        
        } else if (calibrationMsg.status == 1){
            RCLCPP_INFO(this->get_logger(), "Steering calibration [SUCCESS]");
            RCLCPP_INFO(this->get_logger(), "Switching to MANUAL Mode");
            mode = 0;    //Switch to manual mode
            start = false;  //Stop car
        
        } else if (calibrationMsg.status == -1){
            RCLCPP_ERROR(this->get_logger(), "Steering calibration [FAILED]");
            RCLCPP_INFO(this->get_logger(), "Switching to MANUAL Mode");
            mode = 0;    //Switch to manual mode
            start = false;  //Stop car
        }
    
    }
    
    // ---- Private variables ----

    //General variables
    bool start;
    int mode;    //0 : Manual    1 : Auto    2 : Calibration

    
    //Motors feedback variables
    float currentAngle;
    float leftRearSpeedFeedback;
    float rightRearSpeedFeedback;


    //obstacles variables
    bool obstacles_front;
    bool obstacles_rear;
    
    
    
    //Manual Mode variables (with joystick control)
    bool reverse;
    float requestedThrottle;
    float requestedSteerAngle;

    //Control variables
    uint8_t leftRearPwmCmd;
    uint8_t rightRearPwmCmd;
    uint8_t steeringPwmCmd;

    //Default consigne in auto mode


    //PI variables for motor

    float correctedValue_L = 0;
    float correctedValue_R = 0;
    float lastError_L = 0;
    float lastError_R = 0;

    //auto mode
    bool playing = false;
    
    //file
    ifstream file;

    //timing data
    steady_clock::time_point t_start;
    duration<double> time_span;
    double time_stamp;

    //Publishers
    rclcpp::Publisher<interfaces::msg::MotorsOrder>::SharedPtr publisher_can_;
    rclcpp::Publisher<interfaces::msg::SteeringCalibration>::SharedPtr publisher_steeringCalibration_;

    //Subscribers
    rclcpp::Subscription<interfaces::msg::JoystickOrder>::SharedPtr subscription_joystick_order_;
    rclcpp::Subscription<interfaces::msg::MotorsFeedback>::SharedPtr subscription_motors_feedback_;
    rclcpp::Subscription<interfaces::msg::SteeringCalibration>::SharedPtr subscription_steering_calibration_;
    rclcpp::Subscription<interfaces::msg::ObstaclesOrder>::SharedPtr subscription_obstacles_order_; 

    //Timer
    rclcpp::TimerBase::SharedPtr timer_;

    //Steering calibration Service
    rclcpp::Service<std_srvs::srv::Empty>::SharedPtr server_calibration_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<car_control>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}
