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
 * @brief Variable to hold profiled time data
 *
 * Used to store values in profile function, and printed in report function
 */

/* variables to hold time vals */
uint32_t stdMemSet[4] = {0, 0, 0, 0};
uint32_t myMemSet[4] = {0, 0, 0, 0};
uint32_t stdMemMv[4] = {0, 0, 0, 0};
uint32_t myMemMv[4] = {0, 0, 0, 0};
#ifdef KL25ZUSE
uint32_t myDMAMemSet[4] = {0, 0, 0, 0};
uint32_t myDMAMemMv[4] = {0, 0, 0, 0};
/*uint32_t dmaInitTime = 0;*/ /*for test to check init time overhead for dma */
#endif

uint32_t stackUsage = 0;

/*
 * @brief Strings to print
 *
 * Various strings printed in profiling report
 */
uint8_t titleLen = 17;
uint8_t title[] = "PROFILING REPORT\n";

uint8_t setTitleLen = 30;
uint8_t setTitle[] = "MEM SET PROFILING INFORMATION\n";

uint8_t stdSetLen = 50;
uint8_t stdSetTitle[] = "Std Mem Set Profiling Information (In Clk Cycles)\n";

uint8_t mySetLen = 49;
uint8_t mySetTitle[] = "My Mem Set Profiling Information (In Clk Cycles)\n";

uint8_t mySetDMALen = 50;
uint8_t mySetDMATitle[] = "DMA Mem Set Profiling Information (In Clk Cycles)\n";

uint8_t mvTitleLen = 31;
uint8_t mvTitle[] = "MEM MOVE PROFILING INFORMATION\n";

uint8_t stdMvLen = 49;
uint8_t stdMvTitle[] = "Std Mem Mv Profiling Information (In Clk Cycles)\n";

uint8_t myMvLen = 48;
uint8_t myMvTitle[] = "My Mem Mv Profiling Information (In Clk Cycles)\n";

uint8_t myMvDMALen = 50;
uint8_t myMvDMATitle[] = "DMA Mem Mv Profiling Information (In Clk Cycles)\n";

uint8_t bytes10Len = 10;
uint8_t bytes10[] = "10 Bytes: ";

uint8_t bytes100Len = 14;
uint8_t bytes100[] = " | 100 Bytes: ";

uint8_t bytes1000Len = 15;
uint8_t bytes1000[] = " | 1000 Bytes: ";

uint8_t bytes5000Len = 15;
uint8_t bytes5000[] = " | 5000 Bytes: ";

uint8_t lineEndLen = 1;
uint8_t lineEnd[] = "\n";

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
