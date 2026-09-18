/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0240模块测试实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 MiniSTM32 V4开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "demo.h"
#include "dht11.h"
#include "JSQ.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"
#include "page.h"
#include "./ESP8266/bsp_esp8266_test.h"
#include "./ESP8266/bsp_esp8266.h"
#include "./systick/bsp_SysTick.h"
#include "./ESP8266/bsp_esp8266_mqtt.h"
#include "bsp_debug_usart.h"
#include "timer.h"
#include "direct.h"

int main(void)
{
    HAL_Init();                         /* 初始化HAL库 */
	SysTick_Init();
    sys_stm32_clock_init(RCC_PLL_MUL9); /* 设置时钟, 72Mhz */
    delay_init(72);                     /* 延时初始化 */

	DEBUG_USART_Config();				// 这段代码已经在你提供的代码中实现，确保你在主函数中调用了 USART 初始化

	dht11_init(); 
    led_init();                         /* 初始化LED */
	
	gpio_init();
	
    key_init();                         /* 初始化按键 */
    //lcd_init();                         /* 初始化LCD */

	JSQ_init();

	ESP8266_Init ();   	   				/* 初始化WiFi模块使用的接口和外设 */
	
    atk_md0240_init();					/* 初始化ATK-MD0240模块 */

	ESP8266_StaTcpClient_Unvarnish_ConfigTest();  	  /* 连接物联网平台测试 */
	
	//atk_md0240_display_off();

	Fixed_display();	 

	while (1)
	{
		Key_controls();									//按键加减
	
		total();		//总函数
	}
			
}





