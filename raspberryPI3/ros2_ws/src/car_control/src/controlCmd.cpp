/* This file contains the function that calculate the PWM of each wheel according to the speed that needs to be reached
*/

#include "rclcpp/rclcpp.hpp"
#include <functional>
#include "../include/car_control/controlCmd.h"

using namespace std;

// Speed variables
float leftPwmCmd ;
float rightPwmCmd ;
float speedErrorLeft ;
float speedErrorRight ;

void calculateRPMAuto(float cmd_RearSpeed, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd,
            float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight){
    
    // Calcul of the error for gain Kp
    speedErrorLeft = cmd_RearSpeed - currentRPM_L;
    speedErrorRight = cmd_RearSpeed - currentRPM_R;

    // Calcul of the error for gain Ki
    sumIntegralLeft += speedErrorLeft;
    sumIntegralRight += speedErrorRight;

    // Calcul of the command to be sent to each motor (right and left)
    leftPwmCmd = min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
    rightPwmCmd = min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
    leftPwmCmd += 50;
    rightPwmCmd += 50;

    leftRearPwmCmd = leftPwmCmd;
    rightRearPwmCmd = rightPwmCmd;
}

void calculateRPMManual(float requestedThrottle, bool reverse, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd,
            float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight){

    // Calcul of the command to be sent to each motor (right and left)
    if (reverse){
        // Calcul of the error for gain Kp
        speedErrorLeft = cmd_RearSpeed - currentRPM_L;
        speedErrorRight = cmd_RearSpeed - currentRPM_R;

        // Calcul of the error for gain Ki
        sumIntegralLeft += speedErrorLeft;
        sumIntegralRight += speedErrorRight;
        
        //requestedThrottle : [0 ; 1] => PWM : [50 -> 0] (reverse)
        leftRearPwmCmd = 50 - 50*requestedThrottle;    
        rightRearPwmCmd = 50 - 50*requestedThrottle; 
        leftPwmCmd-= min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
        rightPwmCmd-= min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
    } else {
        // Calcul of the error for gain Kp
        speedErrorLeft = cmd_RearSpeed - currentRPM_L;
        speedErrorRight = cmd_RearSpeed - currentRPM_R;

        // Calcul of the error for gain Ki
        sumIntegralLeft += speedErrorLeft;
        sumIntegralRight += speedErrorRight;
        
        //requestedThrottle : [0 ; 1] => PWM : [50 -> 100] (forward)
        leftRearPwmCmd = 50 + 50*requestedThrottle;
        rightRearPwmCmd = 50 + 50*requestedThrottle; 
        leftPwmCmd += min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
        rightPwmCmd += min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
    }


    leftRearPwmCmd = leftPwmCmd;
    rightRearPwmCmd = rightPwmCmd;
}

