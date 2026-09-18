/**
 ****************************************************************************************************
 * @file        demo.c
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

#include <stdio.h>

#include "demo.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"
#include "./SYSTEM/delay/delay.h"
#include <math.h>
#include "dht11.h"
#include "./BSP/KEY/key.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"

#define PI (float)(3.1415926)

//uint8_t temperature;//温度
//uint8_t humidity;//湿度


//char  atr[64];//温度实际值储存数组
//char  btr[64];//湿度实际值储存数组
//char  ctr[50];//按键实际值储存数组
//char  dtr[50];//按键实际值储存数组

//float  zyt=50.0f;//按键实际值
//float  zyt1=50.0f;//按键实际值
//int key;


static float cube[8][3] = {
    {-16, -16, -16},
    {-16, +16, -16},
    {+16, +16, -16},
    {+16, -16, -16},
    {-16, -16, +16},
    {-16, +16, +16},
    {+16, +16, +16},
    {+16, -16, +16}
};

static uint8_t line_id[24] = {
    1, 2, 2, 3,
    3, 4, 4, 1,
    5, 6, 6, 7,
    7, 8, 8, 5,
    8, 4, 7, 3,
    6, 2, 5, 1
};

/**
 * @brief       计算矩阵乘法
 * @param       a      : 矩阵a
 *              b[3][3]: 矩阵b
 * @retval      计算结果
 */
static float *demo_matconv(float *a, float b[3][3])
{
    float res[3];
    uint8_t res_index;
    uint8_t a_index;
    
    for (res_index=0; res_index<3; res_index++)
    {
        res[res_index] = b[res_index][0] * a[0] + b[res_index][1] * a[1] + b[res_index][2] * a[2];
    }
    
    for (a_index=0; a_index<3; a_index++)
    {
        a[a_index] = res[a_index];
    }
    
    return a;
}

/**
 * @brief       旋转向量
 * @param       point: 需要旋转的向量
 *              x    : X轴旋转量
 *              y    : Y轴旋转量
 *              z    : Z轴旋转量
 * @retval      计算结果
 */
static void demo_rotate(float *point, float x, float y, float z)
{
    float rx[3][3];
    float ry[3][3];
    float rz[3][3];
    
    x /= PI;
    y /= PI;
    z /= PI;
    
    rx[0][0] = cos(x);
    rx[0][1] = 0;
    rx[0][2] = sin(x);
    rx[1][0] = 0;
    rx[1][1] = 1;
    rx[1][2] = 0;
    rx[2][0] = -sin(x);
    rx[2][1] = 0;
    rx[2][2] = cos(x);
    
    ry[0][0] = 1;
    ry[0][1] = 0;
    ry[0][2] = 0;
    ry[1][0] = 0;
    ry[1][1] = cos(y);
    ry[1][2] = -sin(y);
    ry[2][0] = 0;
    ry[2][1] = sin(y);
    ry[2][2] = cos(y);
    
    rz[0][0] = cos(z);
    rz[0][1] = -sin(z);
    rz[0][2] = 0;
    rz[1][0] = sin(z);
    rz[1][1] = cos(z);
    rz[1][2] = 0;
    rz[2][0] = 0;
    rz[2][1] = 0;
    rz[2][2] = 1;
    
    demo_matconv(demo_matconv(demo_matconv(point, rz), ry), rx);
}

/**
 * @brief       演示立方体3D旋转
 * @param       无
 * @retval      无
 */
 void demo_show_cube(void)
{
    uint8_t point_index;
    uint8_t line_index;
    
    for (point_index=0; point_index<8; point_index++)
    {
        demo_rotate(cube[point_index], 0.5f, 0.3f, 0.2f);
    }
    
    for (line_index=0; line_index<24; line_index+=2)
    {
        /* ATK-MD0240模块LCD画线段 */
        atk_md0240_draw_line(   120 + cube[line_id[line_index] - 1][0],
                                148 + cube[line_id[line_index] - 1][1],
                                120 + cube[line_id[line_index + 1] - 1][0],
                                148 + cube[line_id[line_index + 1] - 1][1],
                                ATK_MD0240_BLUE);
    }
    
    delay_ms(100);
    
    atk_md0240_fill(92, 120, 148, 176, ATK_MD0240_WHITE);
}




/**
 * @brief       例程演示入口函数
 * @param       无
 * @retval      无
 */
void demo_run(void)
{
	
	
    /* 初始化ATK-MD0240模块 */
    atk_md0240_init();
    /* ATK-MD024模块LCD清屏 */
    atk_md0240_clear(ATK_MD0240_WHITE);
    /* ATK-MD024模块LCD显示字符串 */
//    atk_md0240_show_string(10, 10, "STM32", ATK_MD0240_LCD_FONT_32, ATK_MD0240_RED);
//    atk_md0240_show_string(10, 42, "ATK-MD0240", ATK_MD0240_LCD_FONT_24, ATK_MD0240_RED);
//    atk_md0240_show_string(10, 66, "ATOM@ALIENTEK", ATK_MD0240_LCD_FONT_16, ATK_MD0240_RED);

  //  while (1)
   // {
        /* 演示立方体3D旋转 */
		//wenduxianshi();
     //  demo_show_cube();
		//	wenduxianshi();
  //  }
}
