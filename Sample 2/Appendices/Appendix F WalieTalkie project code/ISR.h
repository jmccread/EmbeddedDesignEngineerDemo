/*
 * ISR.h
 *
 *  Created on: Nov 19, 2015
 *      Author: Josh
 */

#ifndef ISR_H_
#define ISR_H_

#include "main.h"
#include "drivers_MSP/rbuffer.h"
/****************************************************************************************
* Prototypes and ISRs
****************************************************************************************/
uint8_t Wait_for_UART_Not_Busy();

__interrupt void Port_1(void);
__interrupt void isr_timerA0(void);
__interrupt void isr_timerB0(void);
__interrupt void ADC12_ISR (void);
__interrupt void USCI_A1_TX_ISR(void);
__interrupt void USCI_A1_RX_ISR(void);

extern rbuffer_t UART_RX;
extern rbuffer_t UART_TX;
#endif /* ISR_H_ */
