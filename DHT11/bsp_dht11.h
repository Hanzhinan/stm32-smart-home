#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H
 
#include "tim.h"
#include "main.h"                  // Device header

 
#define BSP_DHT11_PORT		GPIOA
#define BSP_DHT11_PIN		GPIO_PIN_0
 
#define DHT11_OUT_1				HAL_GPIO_WritePin(BSP_DHT11_PORT, BSP_DHT11_PIN, GPIO_PIN_SET)
#define DHT11_OUT_0				HAL_GPIO_WritePin(BSP_DHT11_PORT, BSP_DHT11_PIN, GPIO_PIN_RESET)
 
#define DHT11_IN					HAL_GPIO_ReadPin(BSP_DHT11_PORT, BSP_DHT11_PIN)
 
typedef struct
{
	uint8_t humi_int;				// 湿度的整数部分
	uint8_t humi_deci;	 		// 湿度的小数部分
	uint8_t temp_int;	 			// 温度的整数部分
	uint8_t temp_deci;	 		// 温度的小数部分
	uint8_t check_sum;	 		// 校验和
		                 
} DHT11_Data_TypeDef;
 
uint8_t DHT11_ReadData(DHT11_Data_TypeDef* DHT11_Data);
 
#endif	/* __BSP_DHT11_H */
