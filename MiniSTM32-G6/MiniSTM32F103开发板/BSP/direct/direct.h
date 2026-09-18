#ifndef __direct_H
#define __direct_H

#include <stdint.h>
#include "stm32f1xx_hal.h"

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;


#define Fan_GPIO_PORT                  GPIOA		
#define Fan_GPIO_PIN                   GPIO_PIN_6
#define Fan_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* 风扇 */


#define Ren_GPIO_PORT                  GPIOB
#define Ren_GPIO_PIN                   GPIO_PIN_5
#define Ren_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 人体红外 */

#define DUO_GPIO_PORT                  GPIOC		
#define DUO_GPIO_PIN                   GPIO_PIN_9
#define DUO_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 舵机 */

#define YV_GPIO_PORT                   GPIOA		
#define YV_GPIO_PIN                    GPIO_PIN_2
#define YV_GPIO_CLK_ENABLE()           do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* 雨滴 */

#define JI1_GPIO_PORT                  GPIOB		
#define JI1_GPIO_PIN                   GPIO_PIN_0
#define JI1_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 继电器1 */
	
#define JI2_GPIO_PORT                  GPIOB		
#define JI2_GPIO_PIN                   GPIO_PIN_1
#define JI2_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* 继电器2 */

#define HUO_GPIO_PORT                  GPIOC		
#define HUO_GPIO_PIN                   GPIO_PIN_3
#define HUO_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)   /* 火焰*/

typedef unsigned char u8;

void gpio_init(void);


void TUOGUAN(void) ;

void JI1gao(void);
void JI2gao(void);
void JI1di(void);
void JI2di(void);

void FANKAI(void);

void FANGUAN(void);

#endif

