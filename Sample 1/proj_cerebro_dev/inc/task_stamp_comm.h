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
 * date:	07/30/2014
 */

/******************************************************************************
* task_measure_high_f.h
******************************************************************************/
#ifndef __task_stamp_comm_
#define __task_stamp_comm_

/********************************************************************************
*
* Includes
*
 *******************************************************************************/
#include "stdint.h"
#include "main.h"
#include "msp430.h"
/********************************************************************************
*
* Definitions
*
 *******************************************************************************/
#define GYRO_IDENT      0x01
#define PHOTO_IDENT     0x02
#define MAG_IDENT       0x03
#define GPS_IDENT       0x04
#define ACC_IDENT       0x05
#define PRESSURE_IDENT  0x06
#define TEMP_IDENT      0x07
#define CMD_IDENT       0x08

/********************************************************************************
*
* Function Prototypes 
*
 *******************************************************************************/
void task_stamp_comm(void);

#endif /*_task_lea_6_h
