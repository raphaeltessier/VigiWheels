#ifndef __controlCmd_H
#define __controlCmd_H

#include <cstdint>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define KP 1.00
#define KI 0.1
#define Te pow(10,-3)
#define gainRPM 65.00   //Maximum value RPM of each motor based on motors_feedback topic

//Necessary constants for corrector
double double_constante_correcteur_moteurA = (KI * Te + 2* KP)/ 2;
double double_constante_correcteur_moteurB = (KI * Te - 2* KP)/ 2;

//Speed variables
float speedErrorLeft ;
float speedErrorRight ;
float consigneRPM ;

/**
 * @file        controlCmd.h
 * @details     Contains two functions for manual and auto mode in order to control the angular rotation of rear wheels
 * @author      Aishya Costa 
 * @date        18/11/2023 
 */


/**
* @details Calculates separately both PWM of the motors right and left based on a wanted speed in RPM for Auto mode. 
*           Takes into account the motor feedback left rpm and right rpm and control the command pwm motor right and left.
* @param 
*    consigne [0;1] -> requested consigne of speed for both wheels 
*    leftRearPwmCmd & rightRearPwmCmd -> PWM commands for sending to both motors
*    currentRPM_L & currentRP_R -> motor feedback values read before calling the function 
*    sumIntegralLeft & sunIntegralRight -> cumulative error value for calculating integral command for both motors
*    
*/

void calculateRPMAuto(float consigneMotor, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd, 
                    float currentRPM_L, float currentRPM_R, float& lastError_L, float& lastError_R,
                    float& correctedValue_L, float& correctedValue_R);


/**
* @details Calculates separately both PWM of the motors right and left based on a wanted speed in RPM for Manual mode. 
*           Takes into account the motor feedback left rpm and right rpm and control the command pwm motor right and left.
* @param 
*    requestedThrottle [0;1] -> requested consigne of speed for both wheels given by Joystick
*    reverse -> going backward 
*    leftRearPwmCmd & rightRearPwmCmd -> PWM commands for sending to both motors
*    currentRPM_L & currentRP_R -> motor feedback values read before calling the function 
*    sumIntegralLeft & sunIntegralRight -> cumulative error value for calculating integral command for both motors
*    
*/

void calculateRPMManual(float requestedThrottle, bool reverse, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd, 
                    float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight);

#endif 