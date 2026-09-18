#include "direct.h"


void gpio_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    Fan_GPIO_CLK_ENABLE();  //风扇     
    Ren_GPIO_CLK_ENABLE(); 	//人体红外  
	DUO_GPIO_CLK_ENABLE();	//舵机
	YV_GPIO_CLK_ENABLE(); //雨滴
    JI1_GPIO_CLK_ENABLE(); 	//继电器1
    JI2_GPIO_CLK_ENABLE(); 	//继电器2
	HUO_GPIO_CLK_ENABLE(); /* 火焰*/
	
	
    gpio_init_struct.Pin = Fan_GPIO_PIN;             //风扇          
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;                 
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;             
    HAL_GPIO_Init(Fan_GPIO_PORT, &gpio_init_struct) ;       
	
	gpio_init_struct.Pin = Ren_GPIO_PIN;                   //人体红外         
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                 
    gpio_init_struct.Pull = GPIO_PULLDOWN;                      
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;             
    HAL_GPIO_Init(Ren_GPIO_PORT, &gpio_init_struct);
	
//	gpio_init_struct.Pin = DUO_GPIO_PIN;                       /* 舵机引脚 */
//    gpio_init_struct.Mode = GPIO_MODE_INPUT;                    /* 输入 */
//    gpio_init_struct.Pull = GPIO_PULLUP;                        /* 上拉 */
//    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;              /* 高速 */
//    HAL_GPIO_Init(DUO_GPIO_PORT, &gpio_init_struct);           /* 引脚模式设置,上拉输入 */

	gpio_init_struct.Pin = DUO_GPIO_PIN;                       /* 舵机引脚 */
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;               /* 推挽输出 */
	gpio_init_struct.Pull = GPIO_NOPULL;                       /* 不上拉 */
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;             /* 高速 */
	HAL_GPIO_Init(DUO_GPIO_PORT, &gpio_init_struct);           /* 引脚模式设置 */


	gpio_init_struct.Pin = YV_GPIO_PIN;                      //雨滴
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                   
    gpio_init_struct.Pull = GPIO_PULLUP;                       
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;           
    HAL_GPIO_Init(YV_GPIO_PORT, &gpio_init_struct);          

	gpio_init_struct.Pin = JI1_GPIO_PIN;                       // 继电器1
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;               // 设置为推挽输出模式
	gpio_init_struct.Pull = GPIO_NOPULL;                        // 不使用上拉或下拉
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;              
	HAL_GPIO_Init(JI1_GPIO_PORT, &gpio_init_struct);          // 继电器初始化
	  
	gpio_init_struct.Pin = JI2_GPIO_PIN;                       // 继电器2
	gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;               // 设置为推挽输出模式
	gpio_init_struct.Pull = GPIO_NOPULL;                        // 不使用上拉或下拉
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;              
	HAL_GPIO_Init(JI2_GPIO_PORT, &gpio_init_struct);          // 继电器初始化

	gpio_init_struct.Pin = HUO_GPIO_PIN;                     // 火焰传感器引脚
	gpio_init_struct.Mode = GPIO_MODE_INPUT;                 // 配置为输入模式
	gpio_init_struct.Pull = GPIO_NOPULL;                     // 无上拉下拉
	gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;            // 设置 GPIO 速度为低
	HAL_GPIO_Init(HUO_GPIO_PORT, &gpio_init_struct);         // 初始化火焰传感器引脚
        


	HAL_GPIO_WritePin(JI1_GPIO_PORT, JI1_GPIO_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(JI2_GPIO_PORT, JI2_GPIO_PIN, GPIO_PIN_RESET);
	
	
}

void TUOGUAN(void) //舵机
{
		HAL_GPIO_WritePin(DUO_GPIO_PORT, DUO_GPIO_PIN, GPIO_PIN_RESET);
		HAL_Delay(2000); 
		HAL_GPIO_WritePin(DUO_GPIO_PORT, DUO_GPIO_PIN, GPIO_PIN_SET);
}

void JI1gao(void)
{
	HAL_GPIO_WritePin(JI1_GPIO_PORT, JI1_GPIO_PIN, GPIO_PIN_SET);

}

void JI1di(void)
{
	HAL_GPIO_WritePin(JI1_GPIO_PORT, JI1_GPIO_PIN, GPIO_PIN_RESET);

}

void JI2gao(void)
{
	HAL_GPIO_WritePin(JI2_GPIO_PORT, JI2_GPIO_PIN, GPIO_PIN_SET);

}

void JI2di(void)
{
	HAL_GPIO_WritePin(JI2_GPIO_PORT, JI2_GPIO_PIN, GPIO_PIN_RESET);

}

void FANKAI(void)
{
		HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_SET);		//3010风扇开

}

void FANGUAN(void)
{
	HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_RESET);

}
	



