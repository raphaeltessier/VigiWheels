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
extern TIM_HandleTypeDef htim3;
#define START_OF_FRAME '#'   			// Start of frame delimiter
#define END_OF_FRAME '\n'    			// End of frame delimiter
#define SEPARATOR '='        			// Separator between ID and Value in the frame

#define angle_0_duty_ratio_PWM 2.81
#define angle_180_duty_ratio_PWM 13.13

uint16_t ir_sensor1;        			// Analog port A0 (ADC1 - IN5)
uint16_t ir_sensor2;        			// Digital port D2
uint16_t ir_sensor3;        			// Analog port A1 (ADC1 - IN6)
uint16_t ir_sensor4;        			// Digital port D3
uint16_t smoke_sensor1;					// Analog port A2 (ADC1 - IN9)
uint16_t smoke_sensor2;					// Analog port A3 (ADC1 - IN15)

osMutexId_t uartMutex;
osThreadId_t senderThreadId;
osThreadId_t receiverThreadId;

const osThreadAttr_t senderTask_attributes = {
		.name = "Sender",
		.priority = (osPriority_t)osPriorityHigh,  // High priority
		.stack_size = 128 * 4                       // Stack size
};

#define SIZE_RX 10
#define SIZE_TX 100

TickType_t msToTicks(TickType_t ms)
{
	TickType_t tmp = ms;

	if (ms<(1000/configTICK_RATE_HZ))
		tmp = 1;
	else {
		tmp = ms/(1000/configTICK_RATE_HZ);

		if (ms % (1000/configTICK_RATE_HZ))
			tmp ++;
	}
	return tmp;
}

void reading_analog_ir_sensor1(ADC_HandleTypeDef *hadc, uint16_t *sensorValue)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure and start ADC conversions for A0
	sConfig.Channel = ADC_CHANNEL_5;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	HAL_ADC_Start(&hadc1);

	// Wait for conversion to complete
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	// Read ADC value for A0
    *sensorValue = HAL_ADC_GetValue(hadc);

	// Stop ADC conversions for A0
    HAL_ADC_Stop(hadc);
}

void reading_analog_ir_sensor3(ADC_HandleTypeDef *hadc, uint16_t *sensorValue)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure and start ADC conversions for A1
	sConfig.Channel = ADC_CHANNEL_6;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	HAL_ADC_Start(&hadc1);

	// Wait for conversion to complete
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	// Read ADC value for A0
    *sensorValue = HAL_ADC_GetValue(hadc);

	// Stop ADC conversions for A0
    HAL_ADC_Stop(hadc);
}

void reading_analog_smoke_sensor1(ADC_HandleTypeDef *hadc, uint16_t *sensorValue)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure and start ADC conversions for A0
	sConfig.Channel = ADC_CHANNEL_9;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	HAL_ADC_Start(&hadc1);

	// Wait for conversion to complete
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	// Read ADC value for A0
    *sensorValue = HAL_ADC_GetValue(hadc);

	// Stop ADC conversions for A0
    HAL_ADC_Stop(hadc);
}

void reading_analog_smoke_sensor2(ADC_HandleTypeDef *hadc, uint16_t *sensorValue)
{
	ADC_ChannelConfTypeDef sConfig = {0};

	// Configure and start ADC conversions for A0
	sConfig.Channel = ADC_CHANNEL_15;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_2CYCLES_5;
	sConfig.SingleDiff = ADC_SINGLE_ENDED;
	sConfig.OffsetNumber = ADC_OFFSET_NONE;
	sConfig.Offset = 0;

	HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	HAL_ADC_Start(&hadc1);

	// Wait for conversion to complete
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	// Read ADC value for A0
    *sensorValue = HAL_ADC_GetValue(hadc);

	// Stop ADC conversions for A0
    HAL_ADC_Stop(hadc);
}

// Function to read digital sensor values
void reading_digital_sensor(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint16_t *sensorValue)
{
	*sensorValue = !HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

// Function to read all sensor values
void reading_sensor_values()
{
	reading_analog_ir_sensor1(&hadc1, &ir_sensor1);
	reading_digital_sensor(GPIOA, GPIO_PIN_10, &ir_sensor2);
	reading_analog_ir_sensor3(&hadc1, &ir_sensor3);
	reading_digital_sensor(GPIOB, GPIO_PIN_3, &ir_sensor4);
	reading_analog_smoke_sensor1(&hadc1, &smoke_sensor1);
	reading_analog_smoke_sensor2(&hadc1, &smoke_sensor2);
}

// Frame format: "#[ID]=[Value]|[ID]=[Value]|[ID]=[Value]\n"
void sending_data_uart(void *argument)
{
	char tx[SIZE_TX + 1];

	while (1)
	{
		osMutexAcquire(uartMutex, osWaitForever);

		reading_sensor_values();

		// Create and transmit the frame
		sprintf(tx, "#IR_SENSOR1=%hu|IR_SENSOR2=%u|IR_SENSOR3=%hu|IR_SENSOR4=%u|SMOKE_SENSOR1=%hu|SMOKE_SENSOR2=%hu\n",
				ir_sensor1, ir_sensor2, ir_sensor3, ir_sensor4, smoke_sensor1, smoke_sensor2);

		HAL_UART_Transmit(&huart2, (const uint8_t *)tx, strlen(tx), 100);

		osMutexRelease(uartMutex);

        osDelay(msToTicks(200));
	}
}

// Frame format: "#[ID]=[Value]\n"
void receiving_data_uart()
{
	char buf[1];
	char rx[SIZE_RX + 1];

	while (1)
	{
		osMutexAcquire(uartMutex, osWaitForever);

		// Wait for "START_OF_FRAME"
		do
		{
			HAL_UART_Receive(&huart2, (uint8_t *)buf, 1, 100);
		} while (*buf != START_OF_FRAME);

		// Receive data until "END_OF_FRAME"
		int i = 0;
		do
		{
			HAL_UART_Receive(&huart2, (uint8_t *)buf, 1, 100);
			rx[i++] = *buf;

		} while (*buf != END_OF_FRAME);

		rx[i] = '\0';

		// Extract ID and Value from the received frame
		char *id = strtok(rx, "=");    // ID
		char *value = strtok(NULL, "="); // Value

		// Process based on ID and Value
		if (id != NULL && value != NULL)
		{
			if (strcmp(id, "f") == 0)
			{
				// Handle Fire sensor values
				if (atoi(value) == 1)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
				}
				else if (atoi(value) == 0)
				{
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
				}
				else
				{
					// Handle error
				}
			}
			else if (strcmp(id, "c") == 0)
			{
				// Handle PWM value
				uint32_t cmd_angle = atoi(value);
				update_CCR_timer_PWM(cmd_angle,&htim3);
			}
			else
			{
				// Handle other IDs or report error
			}
		}

		osMutexRelease(uartMutex);
	}
}

void update_CCR_timer_PWM(uint32_t cmd_angle_deg, TIM_HandleTypeDef * htim)
{
	if (cmd_angle_deg < 0)
	{
		cmd_angle_deg = 0;
	} else if (cmd_angle_deg > 180)
	{
		cmd_angle_deg = 180;
	}
	uint32_t ARR_timer = htim->Instance->ARR;

	uint32_t CCR_value_180_deg = angle_180_duty_ratio_PWM*ARR_timer/100; //2100 here
	uint32_t CCR_value_0_deg = angle_0_duty_ratio_PWM*ARR_timer/100; // 450 here

	int CCR_required = (CCR_value_180_deg-CCR_value_0_deg) * cmd_angle_deg / 180 + CCR_value_0_deg;

	if (CCR_required > CCR_value_180_deg)
	{
		CCR_required = CCR_value_180_deg ;
	} else if (CCR_required < CCR_value_0_deg)
	{
		CCR_required = CCR_value_0_deg;
	}
	htim->Instance->CCR1=CCR_required;
}
