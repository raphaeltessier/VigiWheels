/*
 * app.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Johann Courand
 */

#include "app.h"

extern UART_HandleTypeDef huart2;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;

uint16_t ir_sensor1; // analog port A0
uint16_t ir_sensor2; // digital port D2
uint16_t ir_sensor3; // analog port A1
uint16_t ir_sensor4; // digital port D4
uint16_t smoke_sensor1; // digital port D4
uint16_t smoke_sensor2; // digital port D4

osMutexId_t uartMutex;
osThreadId_t senderThreadId;
osThreadId_t receiverThreadId;

const osThreadAttr_t senderTask_attributes = {
    .name = "Sender",
    .priority = (osPriority_t) osPriorityHigh,  // Priorité élevée
    .stack_size = 128 * 4  // Taille de la pile
};

#define SIZE_RX 10
#define SIZE_TX 100

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
    reading_digital_sensor(GPIOB, GPIO_PIN_3, &ir_sensor4);
    reading_analog_sensor(&hadc1, &smoke_sensor1);
    reading_analog_sensor(&hadc1, &smoke_sensor2);
}

void sending_data_uart(void *argument)
{
	char tx[SIZE_TX + 1];

    while (1)
    {
        osMutexAcquire(uartMutex, osWaitForever);

        reading_sensor_values();

        sprintf(tx, "#IR_SENSOR1=%hu|IR_SENSOR2=%u|IR_SENSOR3=4095|IR_SENSOR4=0|SMOKE_SENSOR1=4095|SMOKE_SENSOR2=4095\r\n", ir_sensor1, ir_sensor2);

        HAL_UART_Transmit(&huart2, (const uint8_t *)tx, strlen(tx), 100);

        osMutexRelease(uartMutex);

        osDelay(200);
    }
}

void receiving_data_uart(void *argument)
{
    char buf[1];
    char rx[SIZE_RX + 1];

    while (1)
    {
        osMutexAcquire(uartMutex, osWaitForever);

        do
        {
            HAL_UART_Receive(&huart2, (uint8_t *)buf, 1, 100);
        } while (*buf != '#');

        int i = 0;
        do
        {
            HAL_UART_Receive(&huart2, (uint8_t *)buf, 1, 100);
            if (*buf != '#')
            {
                rx[i++] = *buf;
            }
        } while (i < SIZE_RX && (*buf != '0' && *buf != '1'));

        rx[i] = '\0';

        if (strcmp(rx, "fire=1") == 0)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        }
        else if (strcmp(rx, "fire=0") == 0)
        {
            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        } else
        {
            // Error handling for unexpected values
        }

        osMutexRelease(uartMutex);
    }
}
