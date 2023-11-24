/*
 * app.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Johann Courand
 */

#include "stm32l4xx_hal.h"
#include "app.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;

uint16_t analog_value_A0;
uint16_t digit_value_D2;

char msg[30];

void reading_infrared_sensor()
{
	// ADC IR_SENSOR_1
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 100);

	analog_value_A0 = HAL_ADC_GetValue(&hadc1);

	// IR_SENSOR_2
	digit_value_D2 = !(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10));


	sprintf(msg, "IR_SENSOR1=%hu|IR_SENSOR2=%u\r\n", analog_value_A0, digit_value_D2);


	HAL_UART_Transmit(&huart2, (const uint8_t *)msg, strlen(msg), 100);

	HAL_Delay(250);
}
