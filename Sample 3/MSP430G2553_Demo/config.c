/*
 * config.c
 *
 *  Created on: Jul 30, 2022
 *      Author: Joshua McCready
 */

/****************************************************************************************
* Includes
****************************************************************************************/
#include "config.h"

// See Product guide 8.1 for further details
void init_GPIO(void)
{
    // Set Port 1 to be used for I/O and not peripherals
    P1SEL = 0b0;
    P1SEL2 = 0b0;

    //Initialize other ports because the compiler/CCS is smarter than me :P
    P2SEL = 0b0;
    P2SEL2 = 0b0;

    P3SEL = 0b0;
    P3SEL2 = 0b0;

    // Configure GPIO Pin 1.3 for push button
    P1IE |= BIT3;                             // P1.3 interrupt enabled
    P1IES |= BIT3;                            // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;                           // P1.3 IFG cleared


    // Configure GPIO Pin 1.0 (red) or 1.6 (green) for led blink
    P1DIR |= BIT6 + BIT0; // Set BIT6 of P1DIR to 1 for green led and BIT0 for red led
    P1OUT |= BIT6 + BIT0; // Set the red and green Led to be On by default

    return;
}

void init_BCM(void)
{
    // The LaunchPad I have has a watch crystal soldered on - so this can be used as the source for ACLK, however its use results
    // in a Low/high Frequency Oscillator Fault Flag, so the onboard oscillator will be used.

    /* BCSCTL1: */
    BCSCTL1 = DIVA0 + DIVA1; // Make Clock frequency slower to reduce power

    // BCSCTL2 - MCLK, Don't care

    /* BCSCTL3 */
    BCSCTL3 = LFXT1S1; // ~12 kHz VLO - must use due to fault with crystal
    return;
}

void init_Timer_A(void)
{
    // Timer_A is source from the ACLK setup above
    // TACCR0 can be used to stop or start the timer - may be useful in isrs
    // Timer Control Mode - Setup to be an Up Counter

    /*
     * Timer A effective frequency: f_eff = 12 kHz / 8 DIVAx / 8 IDx = 750 Hz
     * Blink Period = 0.5 s
     * Timer A Up Count =  750 cycles / s * 0.5 s = 0x177 (0x5DC)
     * TACCR0 compare register for count (total counts = TACCR0+1)
     * -> TACCR0 = 0x176 for 1/2 second Blink Period (on + off)
     * -> TACCR1 = 0xBB based on toggle output mode
    */

    /*
     * The Output Mode for the Timer may be used to toggle the LED a number of times
     * based on the rising edge of the Timer reaching the TACCRO/1 register values.
     * Set the registers symetrically to achieve an 50% duty cycle on to off
     */

    /* TACTL */
    TACTL = TASSEL0 + ID0 + ID1 + MC0;
    // Source is ACLK + Make Clock frequency slower to reduce power + the timer counts up to TACCR0.


    /* TACCTL0 */
    TACCTL0 |=  CCIE + CM0; // Enable Interrupts + set Compare mode 0 (rising edge)
    TACCTL0 &= ~CAP;  // Set to Compare mode
    TA0CCR0 = 0x176;

    // TACCTL1
    TACCTL1 |= CCIE + CM0; // Same as above
    TACCTL1 &= ~CAP;
    TA0CCR1 = 0xBB;
    return;
}



void config(void)
{
    init_GPIO();
    init_BCM();
    init_Timer_A();
    return;
}
