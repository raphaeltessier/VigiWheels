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
float consigneRPM;
float gainRPM =65; //Valeur maximale RPM du moteur d'une roue
float alpha;

void calculateRPMAuto(float consigneMotor, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd,
            float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight){
    
    //Transformation consigne to RPM
    consigneRPM = gainRPM * consigneMotor;
    
    // Calcul of the error for gain Kp
    speedErrorLeft = consigneRPM - currentRPM_L;
    speedErrorRight = consigneRPM - currentRPM_R;

    // Calcul of the error for gain Ki
    sumIntegralLeft += speedErrorLeft;
    sumIntegralRight += speedErrorRight;

    // Calcul of the command to be sent to each motor (right and left)
    leftPwmCmd = min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
    rightPwmCmd = min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
    leftPwmCmd += 50;
    rightPwmCmd += 50;

    //Affectation de valeurs PWM pour les 2 moteurs des roues
    leftRearPwmCmd = leftPwmCmd;
    rightRearPwmCmd = rightPwmCmd;
}

void calculateRPMManual(float requestedThrottle, bool reverse, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd,
            float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight){


        //Transformation consigne to RPM
        consigneRPM = gainRPM * requestedThrottle;

        // Calcul of the command to be sent to each motor (right and left)
        // Calcul of the error for gain Kp
        speedErrorLeft = consigneRPM - currentRPM_L;
        speedErrorRight = consigneRPM - currentRPM_R;

        // Calcul of the error for gain Ki
        sumIntegralLeft += speedErrorLeft;
        sumIntegralRight += speedErrorRight;
        
        if(reverse){
        
            //requestedThrottle : [0 ; 1] => PWM : [50 -> 0] (reverse)
            
            leftPwmCmd = min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
            rightPwmCmd = min( max(0.0, (speedErrorRight * 0.8 + sumIntegralRight * KI)), 50.0);
            leftPwmCmd = 50 - leftPwmCmd;    
            rightPwmCmd = 50 - rightPwmCmd; 
        }
        else{

            //requestedThrottle : [0 ; 1] => PWM : [50 -> 100] (forward)
            leftPwmCmd = min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
            rightPwmCmd = min( max(0.0, (speedErrorRight * 0.8 + sumIntegralRight * KI)), 50.0);
            leftPwmCmd += 50;
            rightPwmCmd += 50;
        }

    //Affectation de valeurs PWM pour les 2 moteurs des roues
    leftRearPwmCmd = leftPwmCmd;
    rightRearPwmCmd = rightPwmCmd;
}

