#include <msp430.h>
#include "main.h"
/*
 * main.c
*/
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    data_struct data;
    init();
    __enable_interrupt();
    while(1)
    {
#ifdef DEBUG
    	switch (P6IN & BIT1)
		{
		case (BIT1):
			ADC12CTL0 &= ~ENC;
			UC1IE &= ~UCA1TXIE;
			break;
		case 0x0:
			ADC12CTL0 |= ENC;
			UC1IE |= UCA1TXIE;
			break;
		}
#else
    	// Turn off the ADC unless one or both buttons a pressed
    	switch (P1IN & (BIT3 + BIT4))
    	{
    	case (BIT3):
			ADC12CTL0 |= ENC;
			break;
    	case (BIT4):
			ADC12CTL0 |= ENC;
    		break;
    	case (BIT3+BIT4):
			ADC12CTL0 &= ~ENC;
    		P5OUT &= ~BIT0;
			break;
    	case 0x0:
    		ADC12CTL0 |= ENC;
    		break;
    	}
#endif
    	/*
    	switch (UC1IFG & (UCA1RXIFG + UCA1TXIFG))
    	    	{
    	    	case (UCA1RXIFG):
					rbuffer_putchar(&UART_RX, UCA1RXBUF);
					//DAC12_0DAT = 0x00FF&((uint16_t)UCA1RXBUF);
					P5OUT ^= BIT0;
					UC1IFG &= ~ UCA1RXIFG;
    				break;
    	    	case (UCA1TXIFG):
					while (rbuffer_count(&UART_TX))
					 {
						UCA1TXBUF =rbuffer_getchar(&UART_TX);
						Wait_for_UART_Not_Busy(MCLK_SPD);
					 }
					UC1IFG &= ~ UCA1TXIFG;
    	    		break;
    	    	case ( UCA1TXIFG + UCA1RXIFG):
						rbuffer_putchar(&UART_RX, UCA1RXBUF);
						//DAC12_0DAT = 0x00FF&((uint16_t)UCA1RXBUF);
						P5OUT ^= BIT0;
						UC1IFG &= ~ UCA1RXIFG;

    				break;
    	    	case 0x0:
    	    		break;
    	    	}*/

	}
}

