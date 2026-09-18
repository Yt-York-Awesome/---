#include "led.h"
void Led(unsigned char index,unsigned char sataus)
{
	if(sataus == 0)
	{
		if(index==1)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, GPIO_PIN_RESET);
		}					
		else if(index==2)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, GPIO_PIN_RESET);
		}					
	}
	if(sataus == 1)
	{				
		if(index==1)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0, GPIO_PIN_SET);
		}					
		else if(index==2)
		{
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1, GPIO_PIN_SET);
		}					
	}
}

