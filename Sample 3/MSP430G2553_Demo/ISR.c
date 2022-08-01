/*
 * ISR.c
 *
 *  Created on: July 30, 2022
 *  Author: Josh McCready
 */
#include "ISR.h"
/******************************************************************************
*
* ISR.c scoped variables
*
******************************************************************************/
uint8_t ActiveBlinkSemaphor = 0;
uint8_t LedBlinkCount = 0;
/*********************************g*********************************************
*
* isr_timerA0()
*
******************************************************************************/
#pragma vector = TIMER0_A0_VECTOR // 0x176
__interrupt void isr_timerA0(void)
{
    if (ActiveBlinkSemaphor & (LedBlinkCount < LED_BLINK_COUNT_MAX))
    {
        P1OUT |= BIT0; // Toggle LED GPIO for blink
        LedBlinkCount++;
    }
    else
    {
        ActiveBlinkSemaphor = 0;
        LedBlinkCount = 0;
    }
    TACCTL0 &= ~CCIFG;      // Clear Interrupt Flag
    return;
}

/*********************************g*********************************************
*
* isr_timerA1()
*
******************************************************************************/
#pragma vector = TIMER0_A1_VECTOR //0xBB
__interrupt void isr_timerA1(void)
{
    if (ActiveBlinkSemaphor & (LedBlinkCount < LED_BLINK_COUNT_MAX))
    {
        P1OUT &= ~BIT0; // Toggle LED GPIO for blink
        LedBlinkCount++;
    }
    else
    {
        ActiveBlinkSemaphor = 0;
        LedBlinkCount = 0;
    }
    TACCTL1 &= ~CCIFG;      // Clear Interrupt Flag
    return;
}

/*********************************g*********************************************
*
* isr_port1()
*
******************************************************************************/
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void isr_port1(void)
{
    if (~ActiveBlinkSemaphor)
    {
        // Toggle GPIO pin connected to LED1 (should go on to off based on default)
        P1OUT &= ~BIT0;

        // Set LED duration timer to 0
        TACTL |= TACLR; // Clear_timer_A
        TACTL = TASSEL0 + ID0 + ID1 + MC0; // Reset other stuff that clears with TACLR.

        // Set LED blink count to 0
        LedBlinkCount = 0x00;

        // Set Active Blink to True
        ActiveBlinkSemaphor = 1;
    }
    // Interrupt triggers on P1.3 Press -  P1.3 IFG cleared
    P1IFG &= ~BIT3;
}
