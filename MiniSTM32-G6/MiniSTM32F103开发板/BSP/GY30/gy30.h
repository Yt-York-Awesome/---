#ifndef __GY302_H
#define __GY302_H
#include "main.h"
#define scl GPIO_PIN_10
#define sda GPIO_PIN_11

#define SlaveAddress 0x46  //ADDR接GND时的器件地址
#define BH1750_PWR_DOWN     0x00 //关闭模块
#define BH1750_PWR_ON       0x01 //打开模块等待测量命令
#define BH1750_RST          0x07 //重置数据寄存器值在PowerOn模式下有效
#define BH1750_CON_H        0x10 // 连续高分辨率模式,1lx,120ms
#define BH1750_CON_H2       0x11 // 连续高分辨率模式.5lx,120ms
#define BH1750_CON_L        0x13 // 连续低分辨率模式,4lx,16ms
#define BH1750_ONE_H        0x20 // 一次高分辨率模式,1lx,120ms,测量后模块转到PowerDown模式
#define BH1750_ONE_H2       0x21 // 一次高分辨率模式,0.5lx,120ms,测量后模块转到PowerDown模式
#define BH1750_ONE_L        0x23 // 一次低分辨率模式,4lx,16ms,测量后模块转到PowerDown模式


void BH1750_Start(void);
void BH1750_Stop(void);
void Init_BH1750(void);
void mread(void);
uint32_t Value_GY30(void);
void delay_1us(uint16_t us);
void Delay_mms(uint16_t tmp);
void BH1750_SendACK(int ack);
int BH1750_RecvACK(void);
void BH1750_SendByte(uint8_t dat);
uint8_t BH1750_RecvByte(void);
int I2C_ReadData(uint8_t slaveAddr, uint8_t regAddr, uint8_t *pData, uint16_t dataLen);
void Single_Write_BH1750(uint8_t REG_Address);

#endif


