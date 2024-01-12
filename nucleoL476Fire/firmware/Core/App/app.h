/*
 * app.h
 *
 *  Created on: Nov 23, 2023
 *      Author: Johann Courand
 */

#ifndef APP_H_
#define APP_H_

#include "stm32l4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "cmsis_os2.h"
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

extern osMutexId_t uartMutex;
extern osThreadId_t senderThreadId;
extern osThreadId_t receiverThreadId;

extern const osThreadAttr_t senderTask_attributes;

void sending_data_uart(void *argument);
void receiving_data_uart();
void update_CCR_timer_PWM(uint32_t cmd_angle_deg, TIM_HandleTypeDef * htim);

#endif /* APP_H_ */
