#ifndef __controlCmd_H
#define __controlCmd_H

#include <cstdint>
#include <stdint.h>
#include <string.h>


#define KP_right 0.85
#define KI_right 3.5
#define KP_left 0.85
#define KI_left 3.5
#define Te 0.0001   //Frequency of iteration PI control :1ms
#define gainRPM 65   //Maximum value RPM of each motor based on motors_feedback topic



/**
 * @file        controlCmd.h
 * @details     Contains two functions for auto mode in order to control the angular speed of rear wheels
 * @author      Aishya Costa & Aissatou Sylla
 * @date        02/12/2023 
 */


/**
* @details Calculates the PWM of the left motor based on a wanted speed in RPM for Auto mode. 
*           Takes into account the motor feedback to control the command pwm for the left rear wheel.
* @param 
*    consigne_Speed_Left [0;1] -> requested instruction of speed for left motor
*    reverse -> reverse or not
*    leftRearPwmCmd-> PWM command for sending to the left motor
*    currentRPM_L -> left motor feedback value read before calling the function 
*    lastError_L -> static error of last iteration
*    correctedValue_L -> corrected value from last iteration
*/

void calculateRPM_Left_Auto(float consigne_Speed_Left, bool reverse_Auto, uint8_t& leftRearPwmCmd,
            float currentRPM_L, float& lastError_L, float& correctedValue_L);
            

/**
* @details Calculates the PWM of the right motor based on a wanted speed in RPM for Auto mode. 
*           Takes into account the motor feedback to control the command pwm for the right rear wheel.
* @param 
*    consigne_Speed_Right [0;1] -> requested instruction of speed for right motor
*    reverse -> reverse or not
*    rightRearPwmCmd-> PWM command for sending to the right motor
*    currentRPM_R -> right motor feedback value read before calling the function 
*    lastError_R -> static error of last iteration
*    correctedValue_R -> corrected value from last iteration
*/


void calculateRPM_Right_Auto(float consigne_Speed_Right, bool reverse_Auto, uint8_t& rightRearPwmCmd,
                            float currentRPM_R, float& lastError_R, float& correctedValue_R);



#endif 