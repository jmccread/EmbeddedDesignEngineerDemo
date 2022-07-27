/*
 * telem_points.h
 *
 *  Created on: Nov 19, 2015
 *      Author: Josh
 */

#ifndef TELEM_POINTS_H_
#define TELEM_POINTS_H_

// Global data capture struct
#define size_data_str      512
#define size_photo_V       15
#define size_adc_temp      5
#define size_mtr_telem     3

// Struct to add telemetry points from EPS, BMP, etc.
typedef struct {
  uint32_t      tick_counter;                      // counts the total number of ticks of the system timer
  uint32_t      last_tick;                        // Used for updating time
  uint16_t      ms_counter;                       // Count of TA0 triggers up to 6000 for delay function
  char          data_str[size_data_str];          // String to be printed to SD card


  /******************************************************************************
  * Data derived from GPS and 32.7168 kHz crystal, reference point for
  * measurements which might occur at different times
  ******************************************************************************/
  uint8_t h_HF;     // Hours for high frequency measurement
  uint8_t m_HF;     // Minutes " "
  float s_HF;       // Accurate second count from high frequency measurements
  float HF_t_elap;
  uint8_t new_gps_HF;

  uint8_t new_gps_COM;
  } data_struct;

#endif /* TELEM_POINTS_H_ */
