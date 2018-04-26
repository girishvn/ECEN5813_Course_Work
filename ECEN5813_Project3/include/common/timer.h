/**
 * @file timer.h
 * @brief Header for the timer class
 *
 * This source file holds function stubs for the timer class which abstracts timing between the BBB and KL25Z
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date April 1, 2018
 * @version 1.0
 *
 */

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

#include <stdint.h>

/*
 * @brief Configures the system tick timer on the KL25Z
 *
 * Prints, either to consolve via printf, or prints to a serial monitor via UART
 *
 * @param none
 *
 * @return VOID
 */
#ifdef KL25ZUSE
void configureSysTick(void);
#endif

/*
 * @brief Gets the start time
 *
 * Gets the start time, using systick for KL25Z, and time.h for host/BBB
 *
 * @param none
 *
 * @return VOID
 */
uint32_t getStartTime(void);

/*
 * @brief Gets the end time
 *
 * Gets the end time, using systick for KL25Z, and time.h for host/BBB
 *
 * @param none
 *
 * @return VOID
 */
uint32_t getEndTime(void);

/*
 * @brief Gets the end time for a DMA transfer
 *
 * Gets the end time, using systick for KL25Z, from the DMA ISR handler
 *
 * @param none
 *
 * @return VOID
 */
#ifdef KL25ZUSE
uint32_t getEndTimeDMA(void);
#endif

/*
 * @brief Gets the time difference between start and end
 *
 * @param none
 *
 * @return VOID
 */
uint32_t getTimeElapsed(uint32_t start, uint32_t end);

#endif /* SOURCE_TIMER_H_ */
