#ifndef _key_H
#define _key_H

#include "stm32f1xx_hal.h"

extern volatile uint16_t key_value;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
/*
#define KEY4 		HAL_GPIO_ReadPin(GPIOC,GPIO_Pin_4) //PB4
#define KEY3		HAL_GPIO_ReadPin(GPIOC,GPIO_Pin_5)	//B5
#define KEY2		HAL_GPIO_ReadPin(GPIOC,GPIO_Pin_6) //B6
#define KEY1 		HAL_GPIO_ReadPin(GPIOC,GPIO_Pin_7)	//B7

unsigned char IsKey1Pressed(void);
unsigned char IsKey2Pressed(void);
unsigned char IsKey3Pressed(void);
unsigned char IsKey4Pressed(void);


unsigned char KeyScan(void);

*/

#endif
