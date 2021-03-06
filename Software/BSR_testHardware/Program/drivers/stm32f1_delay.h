/* #include "stm32f1_delay.h" */

#ifndef __STM32F1_DELAY_H
#define __STM32F1_DELAY_H

#include "stm32f1xx_hal.h"
/*====================================================================================================*/
/*====================================================================================================*/
#define delay_ms(__ms)  HAL_Delay(__ms)
void delay_us( __IO uint32_t vCnt_us );
/*====================================================================================================*/
/*====================================================================================================*/
#endif	 
