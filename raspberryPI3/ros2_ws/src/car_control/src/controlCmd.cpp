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
float consigne_RPM ;


void calculateRPM_Left_Auto(float consigne_Motor, uint8_t& leftRear_PwmCmd,
            float currentRPM_L, float& lastError_L, float& correctedValue_L)
            {

    //Transformation consigne to RPM
    consigne_RPM = gainRPM * consigne_Motor;
    
    // Calcul of the error for gain Kp
    speedError_Left = consigne_RPM - currentRPM_L;

    //Calcul of corrected value 
    correctedValue_L = correctedValue_L + float_constante_correcteur_moteurA_left * speedError_Left + float_constante_correcteur_moteurB_left * lastError_L;
    

    // Calcul of the command to be sent to each motor (right and left)

    if (correctedValue_L >100)
        correctedValue_L= 100;
    else if (correctedValue_L < 0)
        correctedValue_L = 0;
    
    
    
    if (correctedValue_L >= 0 && correctedValue_L < 50)
     leftRear_PwmCmd = correctedValue_L+ 50;

    if (correctedValue_L >50 && correctedValue_L <=100)
     leftRear_PwmCmd = correctedValue_L - 50;
   
    //Update the PWM values of both motors after command
    leftRear_PwmCmd = correctedValue_L+ 50;

    leftRear_PwmCmd = correctedValue_L- 50;
    

    // Calcul of the error for gain Ki
    lastError_L = speedError_Left;
   

}
void calculateRPM_Right_Auto(float consigne_Motor, , uint8_t& rightRear_PwmCmd,
                            float currentRPM_R, float& lastError_R, float& correctedValue_R)
    {

    //Transformation consigne to RPM
    consigne_RPM = gainRPM * consigne_Motor;
    
    // Calcul of the error for gain Kp

    speedError_Right = consigne_RPM - currentRPM_R;

    //Calcul of corrected value 
    correctedValue_R = correctedValue_R + float_constante_correcteur_moteurA_right * speedErrorRight + float_constante_correcteur_moteurB_right* lastError_R;

    // Calcul of the command to be sent to each motor (right and left)

    
    if (correctedValue_R > 50)
        correctedValue_R = 50;
    else if (correctedValue_R < -50)
        correctedValue_R = -50;


    //Update the PWM values of both motors after command
    if (correctedValue_R >= 0 && correctedValue_R < 50)
    rightRear_PwmCmd = correctedValue_R+ 50;
     if (correctedValue_R > 50 && correctedValue_R <= 100)
    rightRear_PwmCmd = correctedValue_R- 50;

    // Calcul of the error for gain Ki
    
    lastError_R = speedError_Right;

}
/*
/*
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
*/
