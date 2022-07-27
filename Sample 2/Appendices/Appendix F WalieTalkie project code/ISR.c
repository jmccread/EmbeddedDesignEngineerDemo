/*
 * ISR.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Josh
 */
#include "ISR.h"

/******************************************************************************
*
* GLOBALS
*
******************************************************************************/
uint8_t ADC_samples[3];
uint16_t DAC_samples[2];
uint8_t ADC_state = 0;
uint8_t DAC_state = 0;
uint8_t UARTA1_RX_state = 0;
uint8_t UARTA1_TX_state = 0;
rbuffer_t UART_RX;
rbuffer_t UART_TX;
int x = 0;
uint8_t P = 10;


/******************************************************************************
*
* isr_timerA0() 1 ms ticks
*
******************************************************************************/
#pragma vector = TIMERA0_VECTOR
__interrupt void isr_timerA0(void)
{
	__bic_SR_register_on_exit(LPM3_bits);
 /*
  if (data.ms_counter == 60000)
  {
    data.ms_counter = 0;
  }
  data.ms_counter++;
  data.tick_counter++;*/
}

/******************************************************************************
*
* Timer_B0 Interrupt Service Routine
*
******************************************************************************/
#pragma vector=TIMERB0_VECTOR
__interrupt void isr_timerB0(void)
{
	if(rbuffer_count(&UART_RX))
	{
		DAC12_0DAT = 0x00FF&((uint16_t)rbuffer_getchar(&UART_RX));
	}

}



/******************************************************************************
*
* ADC12
*
******************************************************************************/
// ADC12 interrupt service routine
#pragma vector=ADC12_VECTOR
__interrupt void ADC12_ISR(void)
{
	rbuffer_putchar(&UART_TX, (uint8_t)(ADC12MEM0>>4));
	if (P==rbuffer_count(&UART_TX))
	{
		UCA1TXBUF =rbuffer_getchar(&UART_TX);
	}
}

/********************************************************************************
*
* UART TX ISR
*
 *******************************************************************************/

#pragma vector=USCIAB1TX_VECTOR
__interrupt void USCI_A1_TX_ISR(void)
{
	while (rbuffer_count(&UART_TX))
	 {
		UCA1TXBUF =rbuffer_getchar(&UART_TX);
		Wait_for_UART_Not_Busy(MCLK_SPD);
	 }
	UC1IFG &= ~ UCA1TXIFG;
}

/********************************************************************************
*
* UART RX ISR
*
 *******************************************************************************/
#pragma vector=USCIAB1RX_VECTOR
__interrupt void USCI_A1_RX_ISR(void)
  {
	rbuffer_putchar(&UART_RX, UCA1RXBUF);
	//DAC12_0DAT = 0x00FF&((uint16_t)UCA1RXBUF);
	P5OUT ^= BIT0;
	UC1IFG &= ~ UCA1RXIFG;
 }

/********************************************************************************
*
* UARTA1 TX wait function, replace with something smarter
*
 *******************************************************************************/
uint8_t Wait_for_UART_Not_Busy()
{
  uint32_t ui32_UART_counter = 0;             // I2C busy counter


  //Wait for UART to not be busy.  If it takes too long return an error
  for(ui32_UART_counter = 0; ui32_UART_counter < SMCLK_SPD/1000; ui32_UART_counter++){
    // should return 1 if busy, if !1, only breaks if not busy
    if (!(UCA1STAT & UCBUSY))
      return 0;
   }

  // Throw error once the counter overflows.
  return 1;
}

