#include "./ESP8266/bsp_esp8266_mqtt.h"
#include "./ESP8266/bsp_esp8266_test.h"
#include "./ESP8266/bsp_esp8266.h"
#include "page.h"
#include "./BSP/LED/led.h"
#include "JSQ.h"
#include "direct.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"
//const char* cmd0 = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"led\\\":0}}\",1,0";
//const char* cmd1 = "AT+MQTTPUB=0,\"/sys/k1tecyxqV8l/esp-01/thing/event/property/post\",\"{\\\"params\\\":{\\\"led\\\":1}}\",1,0";

//获取天气
char httpRequest[] = "GET /v3/weather/now.json?key=your_key&location=Xian&language=zh-Hans&unit=c HTTP/1.1\r\nHost: api.seniverse.com\r\n\r\n";

int led_value = 0;//led开关值
uint8_t mqtt_flag = 0;//mqtt连接标志

/*
 * 函数名：ESP8266_MQTT_USERCFG
 * 描述  ：WF-ESP8266模块进行MQTT的用户配置
 * 输入  ：无
 * 返回  : 1，配置成功
 *         0，配置失败
 * 调用  ：被外部调用
 */
bool ESP8266_MQTT_USERCFG ( void )
{
	char cStr [300];
	
	sprintf ( cStr, "AT+MQTTUSERCFG=0,1,\"%s\",\"%s\",\"%s\",0,0,\"\"", MQTT_CLIENT_ID,MQTT_USER_NAME,MQTT_PASSWD );
	
	return ESP8266_Cmd ( cStr, "OK", 0, 500 );
	
}

/*
 * 函数名：ESP8266_MQTT_CONN
 * 描述  ：WF-ESP8266模块进行MQTT的连接配置
 * 输入  ：无
 * 返回  : 1，配置成功
 *         0，配置失败
 * 调用  ：被外部调用
 */
bool ESP8266_MQTT_CONN ( void )
{
	char cStr [200];
	
	sprintf ( cStr, "AT+MQTTCONN=0,\"%s\",1883,0", MQTT_BROKERADDRESS );
	
	return ESP8266_Cmd ( cStr, "OK", 0, 500 );
	
}

/*
 * 函数名：ESP8266_MQTT_SUB
 * 描述  ：WF-ESP8266模块进行MQTT的信息订阅
 * 输入  ：无
 * 返回  : 1，配置成功
 *         0，配置失败
 * 调用  ：被外部调用
 */
bool ESP8266_MQTT_SUB ( void )
{
	char cStr [200];
	
	sprintf ( cStr, "AT+MQTTSUB=0,\"%s\",0", MQTT_SUBSCRIBE_TOPIC );
	
	return ESP8266_Cmd ( cStr, "OK", 0, 500 );
	
}

/*
 * 函数名：ESP8266_MQTT_PUB
 * 描述  ：WF-ESP8266模块进行MQTT的信息推送
 * 输入  ：无
 * 返回  : 1，配置成功
 *         0，配置失败
 * 调用  ：被外部调用
 */
bool ESP8266_MQTT_PUB ( uint8_t temp_set,uint8_t humi_set,uint8_t led_value )
{
	char cStr [200];

	sprintf ( cStr, "AT+MQTTPUB=0,\"%s\",\"{\\\"params\\\":{\\\"temp\\\":%d\\,\\\"humi\\\":%d\\,\\\"led\\\":%d\\}\\,\\\"version\\\":\\\"1.0.0\\\"}\",0,0",\
    MQTT_PUBLISH_TOPIC,temp_set,humi_set,led_value );
	
	return ESP8266_Cmd ( cStr, "OK", 0, 500 );
	
}


/*
 * 函数名：ESP8266_MQTT_RECV
 * 描述  ：ESP8266模块接收MQTT传来的数据，并且解析
 * 输入  ：param - 要查找的参数（如 "led"）
 * 返回  : true，成功接收并解析
 *         false，未接收到或解析失败
 * 调用  ：被外部调用
 */

bool ESP8266_MQTT_RECV(uint8_t* param)
{
//    char pRecStr[20] = {0};
    char* found_str = NULL;
    // 检测是否失去连接
    if (ucTcpClosedFlag) {
        mqtt_flag = 0; // mqtt断开
        printf("服务器断开\r\n"); 
        while (1);  
    }

    // 打印接收到的完整信息，便于调试
    printf("\r\n接收到的信息: %s\r\n", strEsp8266_Fram_Record.Data_RX_BUF);

    // 确保字符串以 '\0' 结束
    strEsp8266_Fram_Record.Data_RX_BUF[strEsp8266_Fram_Record.InfBit.FramLength] = '\0';

    // 检查是否包含指定的参数关键字并处理
    // 处理控制指令
    if (strstr(strEsp8266_Fram_Record.Data_RX_BUF, "text:"))
    {
        int command = -1;
        found_str = strstr(strEsp8266_Fram_Record.Data_RX_BUF, "text:");
        if (found_str != NULL)
        {
            sscanf(found_str + strlen("text:"), "%d", &command);
            printf("接收到控制指令：text:%d\n", command);

            // 根据不同的command值执行相应操作
            switch (command)
            {
                case 20:
                    printf("温度增加\n");
					 zyt += 1.0; 		
					atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 湿度区域				
                    // 在这里添加温度增加的操作
                    // adjust_temperature(+1);
                    break;
                case 21:
                    printf("温度减少\n");
					zyt -= 1.0; 	
					atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 湿度区域
                    // 在这里添加温度减少的操作
                    // adjust_temperature(-1);
                    break;
                case 22:
                    printf("湿度增加\n");
					zyt1 += 1.0; 	
					atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 湿度区域
                    // 在这里添加湿度增加的操作
                    // adjust_humidity(+1);
                    break;
                case 23:
                    printf("湿度减少\n");
					zyt1 -= 1.0; 
					atk_md0240_fill_rect(120, 70, 175, 270, ATK_MD0240_CYAN); // 湿度区域				
                    // 在这里添加湿度减少的操作
                    // adjust_humidity(-1);
                    break;
                case 24:
                    printf("风扇开\n");
					HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_SET);
                    // 在这里添加风扇打开的操作
                    break;
                case 25:
                    printf("风扇关\n");
					HAL_GPIO_WritePin(Fan_GPIO_PORT, Fan_GPIO_PIN, GPIO_PIN_RESET);
                    // 在这里添加风扇关闭的操作
                    break;
                case 26:			
                    printf("加湿器开\n");				
					JSQ_KAI();				
                    // 在这里添加加湿器打开的操作                 
                    break;
                case 27:
                    printf("加湿器关\n");				
					JSQ_GUAN();			
                    // 在这里添加加湿器关闭的操作           
                    break;
                case 28:
                    printf("开灯\n");					
					ledkai();
                    // 在这里添加开灯的操作
                    break;
                case 29:
                    printf("关灯\n");
                    // 在这里添加关灯的操作
					ledguan();            
                    break;
                case 10:
                    printf("就医开\n");
                    // 在这里添加就医打开的操作				
                    break;
                case 11:
                    printf("就医关\n");
                    // 在这里添加就医关闭的操作                   
                    break;
                case 12:
                    printf("报警开\n");
                    // 在这里添加报警打开的操作                
                    break;
                case 13:
                    printf("报警关\n");
                    // 在这里添加报警关闭的操作                  
                    break;
                case 14:
                    printf("救火开\n");
                    // 在这里添加救火操作         
                    break;
                case 15:
                    printf("救火关\n");
                    // 在这里添加关闭救火操作
					break;
                case 30:
                    printf("自动开\n");
                    // 在这里添加关闭救火操作
					break;
				case 31:
					printf("自动关\n");
					// 在这里添加关闭救火操作
					break;
				case 32:
					printf("温度刷新\n");
					// 在这里添加关闭救火操作
					break;
				case 33:
					printf("开窗\n");
					TUOGUAN() ;
					// 在这里添加关闭救火操作
					break;
				case 34:
                    printf("关窗\n");
					TUOGUAN() ;
                    // 在这里添加关闭救火操作           
                    break;
                default:
                    printf("未知指令: %d\n", command);
                    break;
            }

            // 清空接收缓冲区
            memset(strEsp8266_Fram_Record.Data_RX_BUF, 0, sizeof(strEsp8266_Fram_Record.Data_RX_BUF));
            strEsp8266_Fram_Record.InfBit.FramLength = 0; // 重置数据长度
            return true;
        }
    }

    return false;
}

////获取天气数据
//void  ESP8266_MQTT_TIANQI()
//{
//	if (ESP8266_Cmd("AT+CIPSTART=\"TCP\",\"api.seniverse.com\",80", "CONNECT", NULL, 2000)) 
//	{
//		// 进入数据模式
//		ESP8266_Cmd("AT+CIPMODE=1", "OK", NULL, 2000);
//		
//		// 准备发送数据
//		if (ESP8266_Cmd("AT+CIPSEND", ">", NULL, 2000)) 
//		{
//			// 准备发送数据
//				USART_printf(USART2, "%s", httpRequest);  // 发送请求
//			HAL_UART_Transmit(&Uart3Handle, (uint8_t *)"\x1A", 1, 1000);  // 发送 Ctrl + Z 以结束数据发送
//		}
//		else 
//		{
//			// 设置失败或未收到 ">" 响应
//		}
//	}
//}


// 主循环或消息接收回调函数中调用
void MQTT_Message_Received_Callback(uint8_t* mqtt_message)
{
    // 将接收到的 MQTT 消息保存到缓冲区中
    strncpy((char*)strEsp8266_Fram_Record.Data_RX_BUF, (char*)mqtt_message, sizeof(strEsp8266_Fram_Record.Data_RX_BUF) - 1);
    // 更新缓冲区中的数据长度
    strEsp8266_Fram_Record.InfBit.FramLength = strlen((char*)mqtt_message);

    // 调用 ESP8266_MQTT_RECV 函数解析并处理接收到的消息
    if (ESP8266_MQTT_RECV( "text" ))
    {
        printf("消息处理成功\n");
    }
    else
    {
        printf("未识别的消息\n");
    }
	
}




