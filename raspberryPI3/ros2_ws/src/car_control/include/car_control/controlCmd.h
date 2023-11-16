#ifndef __controlCmd_H
#define __controlCmd_H

#include <cstdint>
#include <stdint.h>
#include <string.h>

#define KP 1.50
#define KI 0.01

/* Calculate the both PWM of the motors right and left based on a wanted speed in RPM 
*   Takes into account the motor feedback left rpm and right rpm and control the command pwm motor right and left
*   Mode Auto
*/
void calculateRPMAuto(float consigneMotor, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd, 
                    float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight);

/* Calculate the both PWM of the motors right and left based on the throttle of the joystick
*   Takes into account the motor feedback left rpm and right rpm and control the command pwm motor right and left
*   Mode Manual
*/
void calculateRPMManual(float requestedThrottle, bool reverse, uint8_t& leftRearPwmCmd, uint8_t& rightRearPwmCmd, 
                    float currentRPM_L, float currentRPM_R, float& sumIntegralLeft, float& sumIntegralRight);

#endif 