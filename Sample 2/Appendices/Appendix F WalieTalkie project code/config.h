/*
 * config.h
 *
 *  Created on: Nov 19, 2015
 *      Author: Josh
 */

#ifndef WALKIE_TALKIE_CONFIG_H_
#define WALKIE_TALKIE_CONFIG_H_

#include "main.h"

/****************************************************************************************
* Defines
****************************************************************************************/

/******************************************************************************
*
* Clock configurations (found in config.c)
*   May be slightly inaccurate due to variable nature of DCO
*
******************************************************************************/
#define MCLK_SPD             16000000 // Hz
#define SMCLK_SPD            16000000 // Hz
#define ACLK_SPD             32768    // Hz

#define SYSTEM_TIMER_RELOAD  33   // for 1 ms ticks, ACLK = ~32.8kHz
#define SYSTEM_TIMER_PERIOD  1007 // 33/(32.768 kHz), given in microseconds
/****************************************************************************************
* Function Prototypes
****************************************************************************************/
extern void init(void);
extern void delay_ms(uint16_t delay_ms);
extern float update_time(uint8_t * H, uint8_t * M, float * S);
extern void init_GPIO();
void init_ADC12(void);
void init_USCI_A1_UART(void);
void init_DAC12(void);
#endif /* WALKIE_TALKIE_CONFIG_H_ */
