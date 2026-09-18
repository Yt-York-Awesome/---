#include "key.h"
#include "usart.h"
#include <stdio.h> 
#include "tim.h"
#include "gpio.h"

volatile uint16_t key_value = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  static uint32_t last_interrupt_time = 0;
  uint32_t interrupt_time = HAL_GetTick();
    switch (GPIO_Pin)
    {
      case GPIO_PIN_4:
		  if (interrupt_time - last_interrupt_time > 50) // 200ms 防抖
		  {
			key_value = 4;
		  }

        break;
      case GPIO_PIN_5:
		  if (interrupt_time - last_interrupt_time > 50) // 200ms 防抖
		  {
			key_value = 3;
		  }

        break;
      case GPIO_PIN_6:
	  if (interrupt_time - last_interrupt_time > 50) // 200ms 防抖
		  {
			key_value = 2;
		  }
      
        break;
      case GPIO_PIN_7:
		  if (interrupt_time - last_interrupt_time > 50) // 200ms 防抖
		  {
			key_value = 1;
		  }
        
        break;
      default:
        key_value = 0;
        break;
    }
  last_interrupt_time = interrupt_time;
}


/*
unsigned char IsKey1Pressed(void)
{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==GPIO_PIN_RESET)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==GPIO_PIN_RESET)
			{
				while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7)==GPIO_PIN_RESET)
				{
					return 1;
				}
			}
			else
			{
				return 0;
			}
		}
		else
			{
				return 0;
			}
			return 0;
}

unsigned char IsKey2Pressed(void)
{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6)==GPIO_PIN_RESET)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_6)==GPIO_PIN_RESET)
			{

				return 2;

			}
			else
			{
				return 0;
			}
		}
		else
			{
				return 0;
			}
			return 0;
}

unsigned char IsKey3Pressed(void)
{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==GPIO_PIN_RESET)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==GPIO_PIN_RESET)
			{
				while(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_5)==GPIO_PIN_RESET)
				{
					return 3 ;
				}
			}
			else
			{
				return 0;
			}
		}
		else
			{
				return 0;
			}
			return 0;
}

unsigned char IsKey4Pressed(void)
{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)==GPIO_PIN_RESET)
		{
			HAL_Delay(10);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_4)==GPIO_PIN_RESET)
			{

				return 4;				
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		return 0;
}


unsigned char KeyScan(void)
{
	unsigned char KEY = 0;
	
	KEY = IsKey1Pressed();
	if(KEY != 0)
	{
		return KEY;
	}
	
	KEY = IsKey2Pressed();
	if(KEY != 0)
	{
		return KEY;
	}
//	return KEY;
	
	KEY = IsKey3Pressed();
	if(KEY != 0)
	{
		return KEY;
	}
	
	KEY = IsKey4Pressed();
	if(KEY != 0)
	{
		return KEY;
	}
	return 0; // 如果没有按键按下，返回0
}
*/


