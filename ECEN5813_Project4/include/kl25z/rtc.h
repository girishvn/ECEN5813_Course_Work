/*
 * rtc.h
 *
 *  Created on: May 1, 2018
 *      Author: karroshuang
 */

#ifndef SOURCE_RTC_H_
#define SOURCE_RTC_H_

extern uint32_t RTC_seconds;

/**
 * @brief Initialize Real time Clock on KL25Z
 *
 * Initialize Real time Clock on KL25Z
 *
 * @param void
 *
 * @return void
 */
void rtc_init();

#endif /* SOURCE_RTC_H_ */
