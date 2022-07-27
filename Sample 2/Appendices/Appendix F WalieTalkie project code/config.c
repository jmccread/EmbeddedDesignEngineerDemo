/*
 * config.c
 *
 *  Created on: Nov 19, 2015
 *      Author: Josh
 */

/******************************************
 *  ____    ____   ____  ____   _____     *
 * |_   \  /   _| |_  _||_  _| |_   _|    *
 *   |   \/   |     \ \  / /     | |      *
 *   | |\  /| |      > `' <      | |   _  *
 *  _| |_\/_| |_   _/ /'`\ \_   _| |__/ | *
 * |_____||_____| |____||____| |________| *
 *                                        *
 ******************************************/

/**
 * author: 	Joshua McCready
 * email:	jmccread@umich.edu
 * date:	07/23/2014
 */

/************************************************************
* Includes
************************************************************/
#include "config.h"
#include "main.h"
/************************************************************
* Declarations
************************************************************/


/************************************************************
*
* init.c
*
************************************************************/
void init(void) {

	// Keep interrupts off for now ...
	__disable_interrupt();
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

	P1OUT  =  0xFF;
	P2OUT  =  0xFF;
	P3OUT  =  0xFF;
	P4OUT  =  0xFF;
	P5OUT  =  0XFF;
	P6OUT  =  0xFF;

	BCSCTL2 = SELM_0 | DIVM_0 | DIVS_0;
	if (CALBC1_16MHZ != 0xFF) {
		__delay_cycles(100000);
		DCOCTL = 0x00;
		BCSCTL1 = CALBC1_16MHZ;     /* Set DCO to 16MHz */
		DCOCTL = CALDCO_16MHZ;
	}
	BCSCTL1 |= XT2OFF | DIVA_0;
	BCSCTL3 = XT2S_0 | LFXT1S_0 | XCAP_1;

	init_GPIO();
	init_ADC12();
	init_DAC12();
	init_USCI_A1_UART();
	TBCCTL0 = CCIE;
	TBCCR0 = 4800;
	TBCTL = TBCLGRP_0 | CNTL_0 | TBSSEL_2 | ID_0 | MC_1;
}
void init_GPIO(void)
{
	// Initialize LED output
	#ifdef DEBUG
		P6DIR |= 0x01;  		// Set LED to OUT
		P6OUT &= 0xFE; 			// Set LED to be off but don't change other outputs
	#else
		P5DIR |= 0x01;  		// Set LED to OUT
		P5OUT &= 0xFE; 		    // Set LED to be off but don't change other outputs
	#endif

	// Initialize Buttons as inputs
	#ifdef DEBUG
		P6DIR |= 0x00;  		// Set BUT to IN
	#else
		P1REN |= BIT3+BIT4;
		P1OUT |= BIT3+BIT4;
		P1DIR &= ~(BIT3+BIT4);  		// Set Button inputs to be inputs
		P1IE |= 0x01; 			// Enables interrupts on port 1
		P1IES |= BIT3+BIT4;  		// Sets buttons to be active low
		P1IFG &= 0x00;  			// Reset all interrupt flags

		P6SEL |= 0x01;          // select A0 as mic input voltage;
	#endif

}

/************************************************************
*
* ADC12
*
************************************************************/
void init_ADC12(void)
{
	//#ifdef DEBUG
	 ADC12CTL0 = ADC12ON+REF2_5V+REFON;        // Setup ADC12
	  ADC12CTL1 = CONSEQ_2+SHS_1;               // Timer triggers sampling
	  ADC12MCTL0 = INCH_0+ SREF_0;
	  //ADC12MCTL0 = INCH_0+ SREF_1;
	  ADC12IE = 0x0001;                         // Enable ADC12IFG.0


	  TACCR0 = 1500;                            // Delay to allow Ref to settle
	  TACCTL0 |= CCIE;                          // Compare-mode interrupt.
	  TACTL = TASSEL_1 | MC_1;                  // TACLK = ACLK, Up mode.
	  __bis_SR_register(LPM3_bits + GIE);       // Wait for delay, Enable interrupts
	  TACCTL0 &= ~CCIE;                         // Disable timer

	  P2SEL |= BIT3;                            // Set for Timer A1
	  P2DIR |= 0x08;
	  TACCR0 = 4800;                             // Init TACCR0 w/ sample prd=CCR0+1
	  TACCR1 = 4;                               // Trig for ADC12 sample & convert
	  TACCTL1 = OUTMOD_3;                       // Set/reset
	  TACTL = TACLR | MC_1 | TASSEL_2;          // ACLK, clear TAR, up mode
	return;
}

/************************************************************
*
* USCI UARTA1
*
************************************************************/

void init_USCI_A1_UART(void)
{
	P3SEL |= BIT6 + BIT7;
	P3DIR |= BIT6;
	// 256000
	/*
    UCA1CTL1 |= UCSWRST;
    UCA1CTL0 = UCMODE_1;
    UCA1CTL1 = UCSSEL_2 | UCSWRST;
    UCA1MCTL = UCBRF_0 | UCBRS_4;
    UCA1BR0 = 62;
    UCA1CTL1 &= ~UCSWRST;
    UC1IE |= UCA1RXIE+UCA1TXIE;
    */

	// 115200

    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 = UCSSEL_2 | UCSWRST;
    UCA1MCTL = UCBRF_0 | UCBRS_7;
    UCA1BR0 = 138;
    UCA1CTL1 &= ~UCSWRST;
    UC1IE |= UCA1TXIE + UCA1RXIE;

	//230400
	/*
    UCA1CTL1 |= UCSWRST;
    UCA1CTL1 = UCSSEL_2 | UCSWRST;
    UCA1MCTL = UCBRF_0 | UCBRS_4;
    UCA1BR0 = 69;
    UCA1CTL1 &= ~UCSWRST;
    UC1IE |= UCA1TXIE | UCA1RXIE;
    */
	/*
	// 56700
	UCA1CTL1 |= UCSWRST;
	UCA1CTL1 = UCSSEL_2 | UCSWRST;
	UCA1MCTL = UCBRF_0 | UCBRS_7;
	UCA1BR0 = 21;
	UCA1BR1 = 1;
	UCA1CTL1 &= ~UCSWRST;
	UC1IE |= UCA1TXIE | UCA1RXIE;
	*/
    /*
	//38700
	UCA1CTL1 |= UCSWRST;
	UCA1CTL1 = UCSSEL_2 | UCSWRST;
	UCA1MCTL = UCBRF_0 | UCBRS_6;
	UCA1BR0 = 160;
	UCA1BR1 = 1;
	UCA1CTL1 &= ~UCSWRST;
	UC1IE |= UCA1TXIE | UCA1RXIE; */
    return;
}

/*
 *  ======== DAC12_graceInit ========
 *  Initialize MSP430 12-bit Digital to Analog Converter
 */
void init_DAC12(void)
{
    /* disable DAC12_0CTL during calibration */
    DAC12_0CTL &= ~DAC12ENC;

    /* DAC12_0CTL Register */
    DAC12_0CTL = DAC12SREF_0 | DAC12RES | DAC12LSEL_0 | DAC12IR | DAC12AMP_7;

    /* start calibration */
    DAC12_0CTL |= DAC12CALON;

    /* wait for calibration to complete */
    while(DAC12_0CTL & DAC12CALON);

    /* enable DAC12_0CTL */
    DAC12_0CTL |= DAC12ENC;

    /* disable DAC12_1CTL during calibration */
    DAC12_1CTL &= ~DAC12ENC;

    /* DAC12_1CTL Register */
    DAC12_1CTL = DAC12SREF_0 | DAC12LSEL_1 | DAC12AMP_0;

    /* start calibration */
    DAC12_1CTL |= DAC12CALON;

    /* wait for calibration to complete */
    while(DAC12_1CTL & DAC12CALON);

    /* enable DAC12_1CTL */
    DAC12_1CTL |= DAC12ENC;
	return;
}

/************************************************************
*
* delay function
*
************************************************************/
void delay_ms(uint16_t delay_ms) {
  uint16_t start =  data.ms_counter;
  uint16_t t_left = 60000- start;
  if (delay_ms< t_left)
    {
    while(data.ms_counter < (start+delay_ms));
    }
  else if (delay_ms> t_left)
    {
    while (!(data.ms_counter == (delay_ms-t_left)));
    }
  return;
  }

/*************************************************************************************
 * Function:        Update_time
 *
 * PreCondition:    None
 *
 * Input:           Pointers to the variables that make up real time H:M:S
 *                  set_time, pointer indicating that there has been a new
 *                  real time measurement
 *
 * Output:          Float containing total elapsed time recorded by the system timer
 *
 * Side Effects:    Modifies the data pointed to by input pointers
 *
 * Overview:        Creates a real time clock using system resources. If there is no
 *                  GPS available (ie if all are 0, meaning an empty string) then
 *                  behavior is simply a rolling counter
 *                  If there has been a new real time measurement then the log time is
 *                  set to real time
 *                  If there has been no new measurement then the system functions like
 *                  a rolling counter
 *
 *                  Always returns the total elapsed time according to the system timer
 *
 *
 * Note:
*************************************************************************************/
float update_time(uint8_t * H, uint8_t * M, float * S)
{
	float update = (data.tick_counter - data.last_tick) * SYSTEM_TIMER_PERIOD * 0.000001;

	// Avoid over-writing previous timestamp with bad data
	*S = *S + update;

	if( (*S) >= 60)
	{
	*S = *S-60;
	*M = *M + 1;
	}
	if ( *M ==  60 )
	{
	*M = 0 ;
	*H = *H + 1;
	}
	if ( *H == 24)
	{
	*H = 0;
	}
	data.last_tick = data.tick_counter;
	return  (float) ((float)data.tick_counter * SYSTEM_TIMER_PERIOD * 0.000001);
}











