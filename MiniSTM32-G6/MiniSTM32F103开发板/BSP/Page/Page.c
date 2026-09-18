#include "page.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"
#include "demo.h"
#include "dht11.h"
#include <string.h>
#include "./BSP/KEY/key.h"
#include <stdlib.h>
#include "./ESP8266/bsp_esp8266.h"
#include "./ESP8266/bsp_esp8266_mqtt.h"
#include "JSQ.h"
#include "stm32f1xx.h"
#include "bsp_debug_usart.h"
#include "stm32f1xx_hal.h" // 根据你的 MCU 包含相应的 HAL 头文件
#include "./SYSTEM/delay/delay.h"
#include <math.h>
#include "dht11.h"
#include "./BSP/LED/led.h"
#include "stm32f1xx_it.h"
#include "timer.h"
#include "direct.h"

//// 发送灯开关
char led0[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"led\\\":0}}\",1,0";
char led1[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"led\\\":1}}\",1,0";

//text全组
char text20[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":20}}\",1,0";//温度增加
char text21[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":21}}\",1,0";//温度减少
char text22[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":22}}\",1,0";//湿度增加
char text23[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":23}}\",1,0";//湿度减少
char text24[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":24}}\",1,0";//风扇开
char text25[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":25}}\",1,0";//风扇关
char text26[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":26}}\",1,0";//加湿器开
char text27[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":27}}\",1,0";//加湿器关
char text28[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":28}}\",1,0";//开灯
char text29[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":29}}\",1,0";//关灯
char text10[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":10}}\",1,0";//就医开
char text11[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":11}}\",1,0";//就医关
char text12[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":12}}\",1,0";//报警开
char text13[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":13}}\",1,0";//报警关
char text14[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":14}}\",1,0";//救火开
char text15[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":15}}\",1,0";//救火关
char text30[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":30}}\",1,0";//自动控制开
char text31[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":31}}\",1,0";//自动控制关
char text32[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":32}}\",1,0";//温度刷新
char text33[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":33}}\",1,0";//开窗
char text34[] = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"text\\\":34}}\",1,0";//关窗
		
int key;

uint8_t parame; 

uint8_t temperature;//温度
uint8_t humidity;//湿度

uint8_t Tx_str1[] = "hello world!\r\n";
uint8_t Tx_str2[] = "LED1 Open!\r\n";
uint8_t Tx_str3[] = "LED1 Closed!\r\n";
uint8_t Rx_dat=0;

static float lost_temperature = 0.0;
static float lost_humidity = 0.0;

uint8_t temperature;//温度
uint8_t humidity;//湿度


float  zyt=20.0f;//按键实际值
float  zyt1=56.0f;//按键实际值
float  zyt2=46.0f;//按键实际值
 
char  atr[64];//温度实际值储存数组
char  btr[64];//湿度实际值储存数组
char  ctr[50];//按键实际值储存数组
char  dtr[50];//按键实际值储存数组
char  etr[50];//按键实际值储存数组

int key;

void Fixed_display(void) 
{
	atk_md0240_clear(ATK_MD0240_CYAN); // 清屏
	
	atk_md0240_ShowChinese(80, 20, "智能家居", ATK_MD0240_BLACK, ATK_MD0240_CYAN, 24, 0);
	atk_md0240_ShowChinese(10, 80, "室内温度", ATK_MD0240_RED, ATK_MD0240_CYAN, 24, 0);
	atk_md0240_ShowChinese(10, 120, "室内湿度", ATK_MD0240_RED, ATK_MD0240_CYAN, 24, 0);
	atk_md0240_ShowChinese(10, 180, "设置温度", ATK_MD0240_BLUE, ATK_MD0240_CYAN, 24, 0);
	atk_md0240_ShowChinese(10, 210, "湿度上限", ATK_MD0240_BLUE, ATK_MD0240_CYAN, 24, 0);
	atk_md0240_ShowChinese(10, 240, "湿度下限", ATK_MD0240_BLUE, ATK_MD0240_CYAN, 24, 0);

	// 显示温湿度数据
	atk_md0240_draw_circle(180, 80, 2, ATK_MD0240_RED);
	atk_md0240_show_string(180, 80, "C", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
	atk_md0240_show_string(130, 80, "  ", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
	
	atk_md0240_show_string(180, 120, "%", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
	atk_md0240_show_string(200, 120, "RH", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
	atk_md0240_show_string(130, 120, "  ", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);


	atk_md0240_draw_circle(180,182,2,ATK_MD0240_BLUE);
	atk_md0240_show_string(180, 180, "C", ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	
	
	atk_md0240_show_string(180, 210, "%", ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	atk_md0240_show_string(195, 210, "RH", ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	atk_md0240_show_string(180, 240, "%", ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	atk_md0240_show_string(195, 240, "RH", ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
}

void PageTemperatureHumidityProcess(u8 Flag) 
{
    // 读取温湿度数据
    dht11_read_data(&temperature, &humidity);
    float temperature_float = (float)temperature;
    float humidity_float = (float)humidity;

    // 检查当前读取值与上次读取值是否相同
    if (lost_temperature != temperature_float || lost_humidity != humidity_float)
    {
        // 更新上一次的温湿度值
        lost_temperature = temperature_float; 
        lost_humidity = humidity_float;

        // 清除湿度区域
        atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 湿度区域
    }

    // 显示温度和湿度
    sprintf((char *)atr, "%2.f", temperature_float);
    sprintf((char *)btr, "%2.f", humidity_float);
    // 显示设置温度和湿度
	sprintf(ctr, "%2.f", zyt);
	sprintf(dtr, "%2.f", zyt1);
	sprintf(etr, "%2.f", zyt2);
	
    atk_md0240_show_string(130, 80, atr, ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
    atk_md0240_show_string(130, 120, btr, ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
	
	atk_md0240_show_string(130, 180,ctr , ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	atk_md0240_show_string(130, 210,dtr , ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);
	atk_md0240_show_string(130, 240,etr , ATK_MD0240_LCD_FONT_24, ATK_MD0240_BLUE);

}



void Key_controls(void)
{
    key = key_scan(0);  // 获取按键状态
    
    if (key == 1) // 湿度减
    {
        zyt1 -= 1.0;

        atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 刷新湿度显示区域
    }
    else if (key == 2) // 湿度加
    {
        zyt1 += 1.0;

        atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN);
    }
    else if (key == 3) // 温度减
    {
        zyt -= 1.0;

        atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN);
    }
    else if (key == 4) // 温度加
    {
        zyt += 1.0;

        atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN);
    }
    
    key = 0;  // 重置按键状态
}


void JIDIANQIKZHI(void)		//继电器控制
{

	if (temperature>zyt) 
	{	
		JI1gao();	//继电器1开，加温	
		JI2di();			
		
	} 
	else if (temperature<zyt) 
	{
		JI2gao();	//继电器2开，降温
		JI1di();	
	} 
	else
	{
		JI1di();	
		JI2di();			
	}
	



}
void Humidity_regulation()		//湿度调节
{

	if (humidity>zyt1) 
	{
		HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_SET);		//3010风扇开
		//JSQ_KAI();					//加湿器			
	} 
	else if (humidity<zyt2) 
	{
			JSQ_KAI();					//加湿器

	} 
	else
	{
		JSQ_GUAN();
		
		HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_RESET);		//3010风扇关
		//加湿器，除湿3010风扇，，全关
		
	}

}


// 人体红外处理页面
void PageinfraredProcess(void) 
{
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
    {
		atk_md0240_display_on();
		//atk_md0240_display_off();		
		//HAL_Delay(60000);
		//ledguan();	
		TIM3_Init(999, 7199);

		//TIM3_Init(9999, 7199); 
    }
    else 
    {
		//atk_md0240_display_off();
		//atk_md0240_display_on();
		//ledkai();		
		
    }


}

// 雨滴处理
void Raindrop_control(void) 
{
    if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == 0)
    {
		TUOGUAN();
		
    }
    else 
    {

    }
	
}



void Flame_control(void) //火焰检测
{	
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)
    {
		ESP8266_Cmd(text14, "OK", NULL, 2000);
		
    }
    else if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1)
    {

    }
 
}

///**
//  * @brief  ESP8266 发送DHT11数据函数
//  * @param  无
//  * @retval 无
//  */
//void ESP8266_SendDHT11DataTest(void)
//{
//    //读取温湿度
//		 if (dht11_read_data(&temperature, &humidity)) // 假设 DHT11_Read 是读取温湿度的函数
//		{
//			// 构造发送命令
//			char temp_cmd[256]; // 增加缓冲区大小以容纳更大的字符串
//			snprintf(temp_cmd, sizeof(temp_cmd),
//					 "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"temp\\\":%.2d,\\\"humidity\\\":%.2d}}\",1,0",
//					 temperature, humidity);
//			
//			// 发送数据到 ESP8266
//			if (ESP8266_Cmd(temp_cmd, "OK", NULL, 2000)) 
//			{
//				//printf("温度: %.2f, 湿度: %.2f 发送成功\r\n", temperature, humidity);
//			} 
//		}
//}


void Voice(void)	//语音
{
	if(HAL_UART_Receive_IT(&UartHandle,&Rx_dat,1) == HAL_OK)
	{
		
		 if(Rx_dat == 0xA1)
		 {			 
			zyt += 1.0; 	
			 atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); 
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//加温
	 
		 }
		 else  if(Rx_dat == 0xA2)
		 {
			zyt -= 1.0; 	
			atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); 		 
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//	减温	
				
		 } 	
		else if(Rx_dat == 0xA3)
		 {

			zyt2 += 1.0; 	
			 atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); 
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//加湿
	 
		 }
		 else  if(Rx_dat == 0xA4)
		 {
			zyt2 -= 1.0; 	
			atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); 			 
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//	减湿				 
		 } 		
		 
		 
		 else if(Rx_dat == 0xA5)
		 {
			FANKAI();
			ESP8266_Cmd(text24, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//开风扇
	 
		 }		
		 
		 else if(Rx_dat == 0xA6)
		 {
			FANGUAN();
			  ESP8266_Cmd(text25, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//关风扇	 
		 }	
		 
		 else if(Rx_dat == 0xA7)
		 {
			JSQ_KAI();
			  ESP8266_Cmd(text26, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//开加湿器	 
		 }	
		 
		 else if(Rx_dat == 0xA8)
		 {
			JSQ_GUAN();
			  ESP8266_Cmd(text27, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//关加湿器
	 
		 }	
		 	
		 
		 else if(Rx_dat == 0xA9)
		 {
			 ledkai();
			  ESP8266_Cmd(text28, "OK", NULL, 2000);	
			//HAL_UART_Transmit(&UartHandle,Tx_str2,sizeof(Tx_str2),10000);//开灯	
	 
		 }
		 		 
		 else  if(Rx_dat == 0xAA)
		 {
			ledguan();
			  ESP8266_Cmd(text29, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);///关灯				 
		 }	
		 else  if(Rx_dat == 0xAB)
		 {
			ESP8266_Cmd(text12, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		我要报警 
		 } 	
		 else  if(Rx_dat == 0xAC)
		 {
			ESP8266_Cmd(text13, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		关闭报警		 
		 } 	
		 else  if(Rx_dat == 0xAD)
		 {
			ESP8266_Cmd(text10, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		我要就医|		 
		 } 			 
		 else  if(Rx_dat == 0xAE)
		 {
			 ESP8266_Cmd(text11, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		关闭就医		 
		 } 	
		 else  if(Rx_dat == 0xAF)
		 {
			ESP8266_Cmd(text14, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		着火了|快救火		 
		 } 	
		 else  if(Rx_dat == 0xBB)
		 {
			ESP8266_Cmd(text15, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		关闭救火		 
		 }
		 else  if(Rx_dat == 0xBC)
		 {
				TUOGUAN();
			  ESP8266_Cmd(text33, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		开窗		 
		 }
		 else  if(Rx_dat == 0xBD)
		 {
				TUOGUAN();
			 	  ESP8266_Cmd(text34, "OK", NULL, 2000);
			//HAL_UART_Transmit(&UartHandle,Tx_str3,sizeof(Tx_str3),10000);//		关窗		 
		 }

		 
	}

}

void total(void)  									//总函数
{	
	ESP8266_MQTT_RECV(&parame);						//网络控制
	
	Voice();										//语音
	
	Raindrop_control();								// 雨滴处理	
	
	PageTemperatureHumidityProcess(1);				//温湿显示

	JIDIANQIKZHI();									//继电器控制
	
	PageinfraredProcess();							//人体红外处理页面

	Humidity_regulation();							//加湿器3010调节

	Flame_control();								//火焰控制
			
}



