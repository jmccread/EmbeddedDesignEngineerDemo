#include <msp430.h> 
#include "config.h"
#include "ISR.h"

/*********************************g*********************************************
*
* main()
*
******************************************************************************/
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	config();
	__bis_SR_register(LPM3_bits + GIE);             // Enter LPM3 w/interrupt
	return;
}
