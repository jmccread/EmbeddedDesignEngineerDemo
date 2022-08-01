/*
 * config.h
 *
 *  Created on: Jul 30, 2022
 *      Author: Lenovo
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/****************************************************************************************
* Includes
****************************************************************************************/
#include <msp430.h>
#include <stdint.h>
extern void init_GPIO();
extern void init_BCM();
extern void init_Timer_A();
extern void config(void);

#endif /* CONFIG_H_ */
