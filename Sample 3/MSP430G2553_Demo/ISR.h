/*
 * ISR.h
 *
 *  Created on: July 30, 2022
 *      Author: Josh
 */

#ifndef ISR_H_
#define ISR_H_

#include <msp430.h>
#include <stdint.h>


#define LED_BLINK_COUNT_MAX 0x06
/****************************************************************************************
* Prototypes and ISRs
****************************************************************************************/
//__interrupt void isr_timerA0(void);
__interrupt void isr_timerA0(void);
__interrupt void isr_timerA1(void);
__interrupt void isr_port1(void);

//__interrupt void Port_1(void);
#endif /* ISR_H_ */
