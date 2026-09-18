#include "JSQ.h"

void JSQ_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    JSQ_GPIO_CLK_ENABLE();                                     /* KEY0时钟使能 */

    gpio_init_struct.Pin = JSQ_GPIO_PIN;                       
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                 
    gpio_init_struct.Pull = GPIO_NOPULL;                      
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;             
    HAL_GPIO_Init(JSQ_GPIO_PORT, &gpio_init_struct);           


}


void JSQ_KAI(void)    //加湿器开
{
	HAL_GPIO_WritePin(JSQ_GPIO_PORT, JSQ_GPIO_PIN, GPIO_PIN_SET);
	
}

void JSQ_GUAN(void)  //加湿器关
{

	HAL_GPIO_WritePin(JSQ_GPIO_PORT, JSQ_GPIO_PIN, GPIO_PIN_RESET);

}



