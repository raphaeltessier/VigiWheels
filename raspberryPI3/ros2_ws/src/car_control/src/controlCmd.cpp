/**
 * @file        controlCmd.cpp
 * @details     Contains two functions for manual and auto mode in order to control the angular rotation of rear wheels
 * @author      Aishya Costa 
 * @date        18/11/2023 
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
float gainRPM =65; //Maximum value RPM of each motor based on motors_feedback topic
float alpha;
double double_corrected_final_value_left;
double double_corrected_final_value_right;

void calculateRPMAuto(float consigneMotor, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd,
            float currentRPM_L, float currentRPM_R, float& lastError_L, float& lastError_R, float& correctedValue_L, 
            float& correctedValue_R){

    //Necessary constants
    double double_constante_correcteur_moteurA = (KI * Te + 2* KP)/ 2;
    double double_constante_correcteur_moteurB = (KI * Te - 2* KP)/ 2;
    
    //Transformation consigne to RPM
    consigneRPM = gainRPM * consigneMotor;
    
    // Calcul of the error for gain Kp
    speedErrorLeft = consigneRPM - currentRPM_L;
    speedErrorRight = consigneRPM - currentRPM_R;

    //Calcul of corrected value 
    correctedValue_L = correctedValue_L + double_constante_correcteur_moteurA * speedErrorLeft 
                    + double_constante_correcteur_moteurB * lastError_L;
    correctedValue_R = correctedValue_R + double_constante_correcteur_moteurA * speedErrorRight 
                    + double_constante_correcteur_moteurB* lastError_R;

    // Calcul of the command to be sent to each motor (right and left)
    
    double_corrected_final_value_right = correctedValue_R;

    if (correctedValue_L > 50)
        double_corrected_final_value_left = 50;
    else if (correctedValue_L < -50)
        double_corrected_final_value_left = -50;
    else
        double_corrected_final_value_left = correctedValue_L;
    
    if (correctedValue_R > 50)
        double_corrected_final_value_right = 50;
    else if (correctedValue_R < -50)
        double_corrected_final_value_right = -50;
    else
        double_corrected_final_value_right = correctedValue_R;


    //Update the PWM values of both motors after command
    leftRearPwmCmd = double_corrected_final_value_left + 50;
    rightRearPwmCmd = double_corrected_final_value_right + 50;

    // Calcul of the error for gain Ki
    lastError_L = speedErrorLeft;
    lastError_R = speedErrorRight;

/**/    //Protection against synchronisation between two wheels
//    if (abs(leftRearPwmCmd - rightRearPwmCmd) >5){
//        rightRearPwmCmd = leftRearPwmCmd;
//    }
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
            rightPwmCmd = min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
            leftPwmCmd = 50 - leftPwmCmd;    
            rightPwmCmd = 50 - rightPwmCmd; 
        }
        else{

            //requestedThrottle : [0 ; 1] => PWM : [50 -> 100] (forward)
            leftPwmCmd = min( max(0.0, (speedErrorLeft * KP + sumIntegralLeft * KI)), 50.0);
            rightPwmCmd = min( max(0.0, (speedErrorRight * KP + sumIntegralRight * KI)), 50.0);
            leftPwmCmd += 50;
            rightPwmCmd += 50;
        }

    //Update the PWM values of both motors after command
    leftRearPwmCmd = leftPwmCmd;
    rightRearPwmCmd = rightPwmCmd;

    //Protection against synchronisation between two wheels
//    if (abs(leftRearPwmCmd - rightRearPwmCmd) >5){
//        rightRearPwmCmd = leftRearPwmCmd;
//    }
}

