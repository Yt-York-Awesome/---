#ifndef __PAGE_H
#define __PAGE_H

#include <stdint.h>
#include "stm32f1xx_hal.h"
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

#define COMPASS_UPDATE_TIME 10

extern float zyt;

extern float zyt1;


void Key_controls(void);//按键加减
void total(void);   //总函数
void Humidity_regulation(void);			//湿度调节	
void PageTemperatureHumidityProcess(u8 Flag) ;//温湿度显示
void Voice(void);
void Raindrop_control(void) ;
void weendu(void);	
void JIDIANQIKZHI(void);		//继电器控制
void Flame_control(void); ////火焰检测
void Fixed_display(void);
typedef unsigned char u8;
// 人体红外处理页面
void PageinfraredProcess(void) ;
#endif

