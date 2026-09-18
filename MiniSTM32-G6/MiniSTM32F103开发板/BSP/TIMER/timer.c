#include "timer.h"
#include "./BSP/ATK_MD0240/atk_md0240.h"

#include "stm32f1xx_hal.h"
#include "page.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F103开发板
//定时器中断驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2018/6/26
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
TIM_HandleTypeDef  htim2;
vu16 USART1_RX_STA = 0;  // 变量定义


// 定义全局变量
TIM_HandleTypeDef TIM2_Handler;      // 定时器句柄
uint16_t counter = 0;          // 中断计数器

volatile   uint8_t QS = 0;            // 状态标志

//通用定时器3中断初始化
//arr：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器3!
void TIM3_Init(u16 arr, u16 psc)
{  
    // 使能 TIM3 时钟
    __HAL_RCC_TIM3_CLK_ENABLE(); 
    
    // 配置定时器3的初始化结构体
    TIM3_Handler.Instance = TIM3;                          
    TIM3_Handler.Init.Prescaler = psc;                     // 设置分频系数
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;    // 向上计数模式
    TIM3_Handler.Init.Period = arr;                        // 自动重装载值
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    TIM3_Handler.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    // 初始化定时器
    if (HAL_TIM_Base_Init(&TIM3_Handler) != HAL_OK) {
        // 错误处理
        Error_Handler();
    }
    
    // 启动定时器3，并开启更新中断
    if (HAL_TIM_Base_Start_IT(&TIM3_Handler) != HAL_OK) {
        // 错误处理
        Error_Handler();
    }

    // 配置中断优先级
    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);    
    HAL_NVIC_EnableIRQ(TIM3_IRQn);  
}




//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
    static uint16_t counter = 0;  // 用于计数中断次数

    if(__HAL_TIM_GET_FLAG(&TIM3_Handler,TIM_FLAG_UPDATE) != RESET)    // 更新中断
    {
        __HAL_TIM_CLEAR_IT(&TIM3_Handler,TIM_IT_UPDATE);            // 清除中断
        
        counter++;  // 每次中断加1

        if (counter >= 600)  // 假设定时器每10ms中断一次，6000次大约是60秒
        {
           // ledguan();  // 关闭灯
			atk_md0240_display_off();
            counter = 0;  // 计数器清零
            __HAL_TIM_DISABLE(&TIM3_Handler);  // 关闭定时器
        }
    }
}




void Timer_Init(void)
{
    // 假设使用 TIM2 作为定时器
    TIM_HandleTypeDef htim2;
    __HAL_RCC_TIM2_CLK_ENABLE();
    
    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 8000 - 1; // 假设系统时钟为 8MHz，10ms 中断
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 10 - 1;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&htim2);
    
    // 启用定时器中断
    HAL_TIM_Base_Start_IT(&htim2);
    HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&htim2);
}




/* USER CODE BEGIN 0 */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

/* USER CODE END 0 */

TIM_HandleTypeDef htim4;

/* TIM4 init function */
void MX_TIM4_Init(void)
{
	
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 71; // 计数器时钟分频
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数
  htim4.Init.Period = 999; // 自动重载值
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE; // 自动重载预加载
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1; // PWM模式1
  sConfigOC.Pulse = 0; // PWM脉冲宽度
  sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW; // 输出极性
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE; // 快速模式
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  
  HAL_TIM_MspPostInit(&htim4);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{
  if(tim_pwmHandle->Instance==TIM4)
  {
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();
  }
}

void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{
  if(timHandle->Instance==TIM4)
  {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB9     ------> TIM4_CH4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{
  if(tim_pwmHandle->Instance==TIM4)
  {
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();
  }
}

/* USER CODE BEGIN 1 */

void Set_TIM4_Frequency(uint32_t frequency, uint32_t duty_cycle)
{
    uint32_t arr = (SystemCoreClock / (htim4.Init.Prescaler + 1)) / frequency - 1;
    __HAL_TIM_SET_AUTORELOAD(&htim4, arr);
    uint32_t pulse = (arr + 1) * duty_cycle / 100; // 根据占空比计算脉冲值
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, pulse);
}

void Play_Note(uint32_t frequency, uint32_t duty_cycle)
{
    Set_TIM4_Frequency(frequency, duty_cycle);
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
}

/* USER CODE END 1 */







