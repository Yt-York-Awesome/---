#ifndef  __BSP_ESP8266_TEST_H
#define	 __BSP_ESP8266_TEST_H


#include "stm32f1xx.h"


/********************************** 用户需要设置的参数**********************************/
#define      macUser_ESP8266_ApSsid                       "Y"         //要连接的热点的名称
#define      macUser_ESP8266_ApPwd                        "18628636"           //要连接的热点的密钥

//#define      macUser_ESP8266_ApSsid                       "LIU"         //要连接的热点的名称
//#define      macUser_ESP8266_ApPwd                        "12345678"           //要连接的热点的密钥

#define MQTT_BROKERADDRESS "k1acxbvY6MF.iot-as-mqtt.cn-shanghai.aliyuncs.com"   //服务器域名

#define MQTT_CLIENT_ID  "esp-01|securemode=2\\,signmethod=hmacsha1\\,timestamp=1728117265347|"  //客户编号
#define MQTT_USER_NAME  "esp-01&k1tecyxqV8l"                                //用户名
#define MQTT_PASSWD     "7101170FE1CBD9DE31664C1018DC607653EB250A"              //用户密码


#define MQTT_SUBSCRIBE_TOPIC  "/k1tecyxqV8l/esp-01/user/get"    //订阅主题

#define MQTT_PUBLISH_TOPIC    "/sys/k1tecyxqV8l/esp-01/thing/event/property/post"     //消息发布


/********************************** 外部全局变量 ***************************************/
extern volatile uint8_t ucTcpClosedFlag;


/********************************** 测试函数声明 ***************************************/
void ESP8266_StaTcpClient_Unvarnish_ConfigTest(void);
void ESP8266_SendDHT11DataTest(void);

void ESP8266_cesi0(void);
void ESP8266_cesi1(void);
	
#endif /* __BSP_ESP8266_TEST_H */

