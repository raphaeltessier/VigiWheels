#include <stdint.h>
#include <string.h>  
#include <map>

#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>
#include <memory>

#include "sensor_msgs/msg/joy.hpp"
#include "interfaces/msg/joystick_order.hpp"
#include "interfaces/msg/system_check.hpp"
#include "interfaces/msg/cam_pos_order.hpp"


using namespace std;
using placeholders::_1;

#define DEADZONE_LT_RT 0.15  // %
#define DEADZONE_LS_X_LEFT 0.4  // %
#define DEADZONE_LS_X_RIGHT 0.2  // %
#define DEADZONE_RS_X_LEFT 0.4  // %
#define DEADZONE_RS_X_RIGHT 0.2  // %

#define STOP 0
#define CENTER 0


//Turns joystick buttons/axis into system commands
class joystick_to_cmd : public rclcpp::Node {

public:
    joystick_to_cmd()
    : Node("joystick_to_cmd_node")
    {
        mode = 0;
        start = false;
        systemCheckPrintRequest = false;
        reverse = false;
        requestedThrottle = STOP;
        requestedAngle = CENTER;

        record_path = false;

        cam_mode = 0;
        turn_cam = CENTER;
        
        axisMap.insert({"LS_X",0});    //Left Stick axis X  (full left) 1.0 > -1.0 (full right)
        axisMap.insert({"LS_Y",1});    //Left Stick axis Y  (full high) 1.0 > -1.0 (full bottom)
        axisMap.insert({"LT",2});      //LT  (high) 1.0 > -1.0 (bottom)
        axisMap.insert({"RS_X",3});    //Right Stick axis X  (full left) 1.0 > -1.0 (full right)
        axisMap.insert({"RS_Y",4});    //Right Stick axis Y  (full high) 1.0 > -1.0 (full bottom)
        axisMap.insert({"RT",5});      //RT  (high) 1.0 > -1.0 (bottom)
        axisMap.insert({"DPAD_X",6});  //(left) 1.0 > -1.0 (right)
        axisMap.insert({"DPAD_Y",7});  //(hight) 1.0 > -1.0 (bottom)

        buttonsMap.insert({"A",0});
        buttonsMap.insert({"B",1});
        buttonsMap.insert({"Y",2});
        buttonsMap.insert({"X",3});
        buttonsMap.insert({"LB",4});
        buttonsMap.insert({"RB",5});
        buttonsMap.insert({"START",6});
        buttonsMap.insert({"SELECT",7});
        buttonsMap.insert({"XBOX",8});
        buttonsMap.insert({"LS",9});   //Left Stick Button
        buttonsMap.insert({"RS",10});  //Right Stick Button


        publisher_joystick_order_= this->create_publisher<interfaces::msg::JoystickOrder>("joystick_order", 10);
        publisher_system_check_= this->create_publisher<interfaces::msg::SystemCheck>("system_check", 10);
        publisher_cam_pos_order_= this->create_publisher<interfaces::msg::CamPosOrder>("cam_pos_order", 10);


        subscription_joy_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "joy", 10, std::bind(&joystick_to_cmd::joyCallback, this, _1));

        
        RCLCPP_INFO(this->get_logger(), "joystick_to_cmd_node READY");
    }

    
private:

    //Update requestedThrottle, requestedAngle and reverse from the joystick
    void joyCallback(const sensor_msgs::msg::Joy & joy) {

        buttonStart = joy.buttons[buttonsMap.find("START")->second];
        buttonB = joy.buttons[buttonsMap.find("B")->second];    
        buttonA = joy.buttons[buttonsMap.find("A")->second];  
        buttonY = joy.buttons[buttonsMap.find("Y")->second];
        buttonX = joy.buttons[buttonsMap.find("X")->second]; 
        

        axisRT = joy.axes[axisMap.find("RT")->second];      //Motors (go forward)
        axisLT = joy.axes[axisMap.find("LT")->second];      //Motors (go backward)
        axisLS_X = joy.axes[axisMap.find("LS_X")->second];     //Steering
        axisRS_X = joy.axes[axisMap.find("RS_X")->second];     //Turn camera

        if (joy.axes[axisMap.find("DPAD_Y")->second] == -1.0)
            buttonDpadBottom = true;
        else
            buttonDpadBottom = false;

        if (joy.axes[axisMap.find("DPAD_Y")->second] == 1.0)
            buttonDpadTop = true;
        else
            buttonDpadTop= false;

        if (joy.axes[axisMap.find("DPAD_X")->second] == 1.0)
            buttonDpadLeft = true;
        else
            buttonDpadLeft = false;

        if (joy.axes[axisMap.find("DPAD_X")->second] == -1.0)
            buttonDpadRight = true;
        else
            buttonDpadRight = false;
        
        


        //Normalise values
        axisLS_X = -axisLS_X;   //axisLS_X : 1 .. -1  ;  steering_angle : -1 .. 1
        axisRT = (1.0-axisRT)/2.0;  //axisRT : 1 .. -1  ;  throttle : 0 .. 1
        axisLT = (1.0-axisLT)/2.0;  //axisLT : 1 .. -1  ;  throttle : 0 .. 1


        //Select mode (0 : manual ; 1 : autonomous ; 2 : steering calibration)
        if (mode == 2) //Exit steering calibration mode after request has been sent
            mode = -1;
        

        if (buttonA || buttonY || buttonDpadBottom){

            if (buttonY)
                mode = 0;
            else if (buttonA)
                mode = 1;
            else if (buttonDpadBottom && buttonStart){
                mode = 2;
                start = false;
            }
        }

        if (buttonDpadLeft && !systemCheckPrintRequest){ //Request to print the last system check report
            systemCheckPrintRequest = true;

            auto systemCheckMsg = interfaces::msg::SystemCheck();
            systemCheckMsg.print = true;
            publisher_system_check_->publish(systemCheckMsg); //Send print request to system_check_node
        }
        else
            systemCheckPrintRequest = false;


        // ------ Start and Stop ------
        if (buttonB){       // B button -> Stop the car
            start = false;

        }else if (buttonStart && mode !=2){   // Start button -> Start the car    
            start = true;
        }


        // ------ Propulsion ------
        if (axisLT > DEADZONE_LT_RT && axisRT > DEADZONE_LT_RT){  //Incompatible orders : Stop the car
            requestedThrottle = STOP;
            RCLCPP_WARN(this->get_logger(), "Incompatible orders : LT = %f, RT = %f",axisLT,axisRT);

        } else if (axisLT < DEADZONE_LT_RT && axisRT < DEADZONE_LT_RT){ 
            requestedThrottle = STOP;
        
        }else if (axisLT > DEADZONE_LT_RT){ //Move backward
            reverse = true;
            requestedThrottle = axisLT;

        } else if (axisRT > DEADZONE_LT_RT){   //Move forward
            reverse = false;
            requestedThrottle = axisRT;
        }


        // ------ Steering ------
        if (axisLS_X > DEADZONE_LS_X_LEFT && axisLS_X < DEADZONE_LS_X_RIGHT){     //asymmetric deadzone (hardware : joystick LS)
            requestedAngle = CENTER;
        } else {
            requestedAngle = axisLS_X;    
        }

        //recording path
        if (buttonX) {
            record_path = !record_path;
        }

        

        auto joystickOrderMsg = interfaces::msg::JoystickOrder();
        joystickOrderMsg.start = start;
        joystickOrderMsg.mode = mode;
        joystickOrderMsg.throttle = requestedThrottle;
        joystickOrderMsg.steer  = requestedAngle;
        joystickOrderMsg.reverse = reverse;
        joystickOrderMsg.record_path = record_path;

        publisher_joystick_order_->publish(joystickOrderMsg); //Send order to the car_control_node



        //camera 
        if (buttonDpadTop || buttonDpadRight){

            if (buttonDpadTop)
                cam_mode = 0;
            else if (buttonDpadRight)
                cam_mode = 1;
        }

        axisRS_X = -axisRS_X;   //axisLS_X : 1 .. -1  ;  steering_angle : -1 .. 1
        if (axisRS_X > DEADZONE_RS_X_LEFT && axisRS_X < DEADZONE_RS_X_RIGHT){     //asymmetric deadzone (hardware : joystick LS)
            turn_cam = CENTER;
        } else {
            turn_cam = axisRS_X;    
        }

        auto camOrderMsg = interfaces::msg::CamPosOrder();
        camOrderMsg.mode = cam_mode;
        camOrderMsg.turn_cam = turn_cam;

        publisher_cam_pos_order_->publish(camOrderMsg); //Send order to the servo_cam mode

    }

    //Joystick variables
    map<string,int> axisMap;
    map<string,int> buttonsMap;
    bool buttonB, buttonStart, buttonA, buttonY, buttonX, buttonDpadBottom, buttonDpadLeft,buttonDpadRight, buttonDpadTop ;
    
    float axisRT, axisLT, axisLS_X, axisRS_X;

    //General variables
    bool start;
    int mode;
    bool systemCheckPrintRequest;

    bool record_path;
    //Manual mode variables
    float requestedAngle, requestedThrottle;
    bool reverse;

    //Camera variables
    float turn_cam;
    int cam_mode;



    rclcpp::Publisher<interfaces::msg::JoystickOrder>::SharedPtr publisher_joystick_order_;
    rclcpp::Publisher<interfaces::msg::SystemCheck>::SharedPtr publisher_system_check_;
    rclcpp::Publisher<interfaces::msg::CamPosOrder>::SharedPtr publisher_cam_pos_order_;

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_joy_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<joystick_to_cmd>();

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}