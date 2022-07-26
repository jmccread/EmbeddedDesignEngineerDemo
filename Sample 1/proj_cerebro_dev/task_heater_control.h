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
 * author: 	Andrew Wagenmaker
 * email:	ajwagen@umich.edu
 * date:	04/10/2015
 */

/******************************************************************************
* task_measure_high_f.h
******************************************************************************/
#ifndef __task_heater_control_
#define __task_heater_control_

/********************************************************************************
*
* Includes
*
 *******************************************************************************/
#include "main.h"
#include "csk_led.h"
#define THRESH_ALT   20000
#define BURN_DURATION 30.0
/********************************************************************************
*
* Definitions
*
*******************************************************************************/

/********************************************************************************
*
* Function Prototypes 
*
 *******************************************************************************/
void task_heater_control(void);
void task_SHADO(void); 
#endif 