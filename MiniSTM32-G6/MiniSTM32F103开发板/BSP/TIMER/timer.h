#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103开发板
//定时器驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2017/5/25
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
extern TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 

typedef __IO uint16_t vu16;

extern vu16 USART1_RX_STA;   						//接收数据状态

//vu16 USART1_RX_STA=0;   

//#define NOTE_DO  261 // C4
//#define NOTE_RE  293 // D4
//#define NOTE_MI  329 // E4
//#define NOTE_FA  349 // F4
//#define NOTE_SOL 392 // G4
//#define NOTE_LA  440 // A4
//#define NOTE_SI  493 // B4



typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

void TIM3_Init(u16 arr,u16 psc);
void TIM3_IRQHandler(void);

void TIM2_Init(u16 arr,u16 psc);
void TIM2_IRQHandler(void);

void MX_TIM4_Init(void);
void Set_TIM4_Frequency(uint32_t frequency, uint32_t duty_cycle);
void Play_Note(uint32_t frequency, uint32_t duty_cycle);
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

void Error_Handler(void);
void Timer_Init(void);

#endif





