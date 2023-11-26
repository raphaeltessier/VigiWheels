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
extern ADC_HandleTypeDef hadc2;

uint16_t ir_sensor1; // analog port A0
uint16_t ir_sensor2; // digital port D2
uint16_t ir_sensor3; // analog port A1
uint16_t ir_sensor4; // digital port D4
uint16_t smoke_sensor1; // digital port D4
uint16_t smoke_sensor2; // digital port D4

char msg[100];

void reading_analog_sensor(ADC_HandleTypeDef *hadc, uint16_t *sensorValue)
{
    HAL_ADC_Start(hadc);
    HAL_ADC_PollForConversion(hadc, 100);
    *sensorValue = HAL_ADC_GetValue(hadc);
    HAL_ADC_Stop(hadc);
}

void reading_digital_sensor(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t *sensorValue)
{
    *sensorValue = !HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

void reading_sensor_values()
{
    reading_analog_sensor(&hadc1, &ir_sensor1);
    reading_digital_sensor(GPIOA, GPIO_PIN_10, &ir_sensor2);
    reading_analog_sensor(&hadc1, &ir_sensor3);
    reading_digital_sensor(GPIOB, GPIO_PIN_5, &ir_sensor4);
    reading_analog_sensor(&hadc1, &smoke_sensor1);
    reading_analog_sensor(&hadc1, &smoke_sensor2);
}

void sending_data_uart()
{
    reading_sensor_values();

    sprintf(msg, "#IR_SENSOR1=%hu|IR_SENSOR2=%u|IR_SENSOR3=4095|IR_SENSOR4=0|SMOKE_SENSOR1=4095|SMOKE_SENSOR2=4095\r\n", ir_sensor1, ir_sensor2);

    HAL_UART_Transmit(&huart2, (const uint8_t *)msg, strlen(msg), 100);

    HAL_Delay(250);
}
