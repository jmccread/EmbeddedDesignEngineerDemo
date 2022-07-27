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

    switch (DAC_state)
	{
    	case 0: // Oldest should be first
    		DAC12_0DAT = 0X00; //DAC_samples[0];
    		DAC_state = 1;
    		break;
    	case 1:
    		DAC12_0DAT = 0XFFF; //DAC_samples[1];
			DAC_state = 0;
			break;
    	default:
    		break;
	}
	//__bic_SR_register_on_exit(LPM3_bits);
}



/******************************************************************************
*
* Button Input Interrupt
*
******************************************************************************/
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	switch(P1IFG & (BIT3+BIT4))
	{
	case BIT3:
		ADC12CTL0 |= ENC;                      // Enable conversion
	break;

	case (BIT4):
		ADC12CTL0 |= ENC;                      // Enable conversion
	break;

	case (BIT3+BIT4):
		ADC12CTL0 |= ENC;                      // Enable conversion
	break;

	case 0x00:

	break;
	default:
		//Define behavior
	break;
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

    switch (ADC_state)
	{
    	case 0: // Oldest should be first
    		ADC_samples[0] = 0X0FF&(ADC12MEM0>>4);
    		ADC_samples[1] = 0X0F0&(ADC12MEM0<<4);
    		ADC_state = 1;
    		break;
    	case 1:
    		ADC_samples[1] |= 0X00F&(ADC12MEM0>>8);
			ADC_samples[2] = 0X0FF& ADC12MEM0;
			ADC_state = 0;
			UCA1TXBUF = ADC_samples[0];
			break;
    	default:
    		break;
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
switch (UARTA1_TX_state)
	{
		case 0: // Oldest should be first
			UCA1TXBUF = ADC_samples[1];
			Wait_for_UART_Not_Busy();
			UARTA1_TX_state = 1;
			break;
		case 1:
			UCA1TXBUF = ADC_samples[2];
			Wait_for_UART_Not_Busy();
			UARTA1_TX_state = 0;
			break;
		default:
			break;
	}
 P5OUT ^= BIT0;
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
	switch (UARTA1_RX_state)
		{
			case 0: // Oldest should be first
				DAC_samples[0] = (((uint16_t)UCA1RXBUF)<<4)&0x0FF0;
				UARTA1_RX_state = 1;
				break;
			case 1:
				DAC_samples[0] |= (((uint16_t)UCA1RXBUF)>>4) & 0x000F;
				DAC_samples[1] = (((uint16_t)UCA1RXBUF)<<8) & 0x0F00;
				UARTA1_RX_state = 2;
				break;
			case 2:
				DAC_samples[1] |= ((uint16_t)UCA1RXBUF) & 0x00FF;
				UARTA1_RX_state = 0;
				break;
			default:
				break;
		}
	P5OUT ^= BIT0;
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

