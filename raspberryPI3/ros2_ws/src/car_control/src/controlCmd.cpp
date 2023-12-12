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

//Necessary constants for corrector
float float_constante_correcteur_moteurA_left = (KI_left * Te + 2* KP_left)/ 2;
float float_constante_correcteur_moteurB_left = (KI_left * Te - 2* KP_left)/ 2;

float float_constante_correcteur_moteurA_right = (KI_right * Te + 2* KP_right)/ 2;
float float_constante_correcteur_moteurB_right = (KI_right * Te - 2* KP_right)/ 2;

//Speed variables
float speedError_Left ;
float speedError_Right ;
float consigne_RPM_L ;
float consigne_RPM_R;


void calculateRPM_Left_Auto(float consigne_Speed_Left, bool reverse_Auto, uint8_t& leftRearPwmCmd,
            float currentRPM_L, float& lastError_L, float& correctedValue_L)
    {

    //Transformation consigne to RPM
    consigne_RPM_L = gainRPM * consigne_Speed_Left;
    
    // Calcul of the static error
    speedError_Left = consigne_RPM_L - currentRPM_L;

    //Calcul of corrected value 
    correctedValue_L = correctedValue_L + float_constante_correcteur_moteurA_left * speedError_Left + float_constante_correcteur_moteurB_left * lastError_L;
    

    // Saturation [0;50]

    if (correctedValue_L >50)
        correctedValue_L = 50;
    else if (correctedValue_L < 0)
        correctedValue_L = 0;
    
    //Update the PWM values of left motor after command according to reverse or not

    if(!reverse_Auto)
        leftRearPwmCmd = correctedValue_L+ 50;
    else
        leftRearPwmCmd = 50 - correctedValue_L;
    
    // Affectation of the static error for next iteration
    lastError_L = speedError_Left;
   
}

void calculateRPM_Right_Auto(float consigne_Speed_Right, bool reverse_Auto , uint8_t& rightRearPwmCmd,
                            float currentRPM_R, float& lastError_R, float& correctedValue_R)
    {

    //Transformation consigne to RPM
    consigne_RPM_R = gainRPM * consigne_Speed_Right;
    
    // Calcul of the static error
    speedError_Right = consigne_RPM_R - currentRPM_R;

    //Calcul of corrected value 
    correctedValue_R = correctedValue_R + float_constante_correcteur_moteurA_right * speedError_Right + float_constante_correcteur_moteurB_right* lastError_R;

    // Saturation [0;50]

    if (correctedValue_R > 50)
        correctedValue_R = 50;
    else if (correctedValue_R < 0)
        correctedValue_R = 0;


    //Update the PWM values of right motor after command according to reverse or not
    if(!reverse_Auto)
        rightRearPwmCmd = correctedValue_R+ 50;
    else
        rightRearPwmCmd = 50 - correctedValue_R;

    // Affectation of the static error for next iteration
    
    lastError_R = speedError_Right;

}
