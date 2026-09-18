#ifndef __JSQ_H
#define __JSQ_H

#include "./SYSTEM/sys/sys.h"


#define JSQ_GPIO_PORT                  GPIOA
#define JSQ_GPIO_PIN                   GPIO_PIN_0
#define JSQ_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PC口时钟使能 */


void JSQ_init(void);
void JSQ_GUAN(void);
void JSQ_KAI(void);


#endif







