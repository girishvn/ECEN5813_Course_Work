/**
 * @file profiling.h
 * @brief An class for profiling memory transfers
 *
 * This header file provides an a means to profile and report various
 * memory tranfer functions.
 *
 * @author Girish Narayanswamy
 * @date April 10, 2018
 * @version 1.0
 *
 */

#ifndef SOURCE_PROFILING_H_
#define SOURCE_PROFILING_H_

#include <stdint.h>

/*
 * @brief Profiles / times various memory transfers
 *
 * Transfers memory and times the transfers using std, custom, and DMA methods
 *
 * @param VOID
 *
 * @return VOID
 */
void memProfiler(void);

/*
 * @brief Profiles amount of stack used
 *
 * Writes a special character onto the stack and then searchs the stack for that value to determine stac usage
 *
 * @param none
 *
 * @return VOID
 */
void stackUsageProfiler(void);

/*
 * @brief Prints out profiling report
 *
 * Prints, either to consolve via printf, or prints to a serial monitor via UART
 *
 * @param none
 *
 * @return VOID
 */
void generateProfileReport(void);

#endif /* SOURCE_PROFILING_H_ */
