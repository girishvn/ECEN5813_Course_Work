/**
 * @file timer.c
 * @brief Implementation of the timer.h file
 *
 * This source file holds implementations for timer abstraction functions from the timer.h file
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date April 1, 2018
 * @version 1.0
 *
 */

#include "timer.h"

#ifdef KL25ZUSE
#include "MKL25Z4.h"
#include "dma.h"
#endif

#if defined(BBBUSE) || defined(HOSTUSE)
#include <time.h>
#endif

#ifdef KL25ZUSE
void configureSysTick(void)
{
	SysTick->LOAD = SysTick_LOAD_RELOAD_Msk; /* count value == max */
	SysTick->VAL = 0x00000000; /* clears val to 0 */
	SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk); /* use internal core clock, start systick */

	return;
}
#endif

uint32_t getStartTime(void)
{
#ifdef KL25ZUSE
	SysTick->VAL = 0x00000000; /* clears val to 0 */
	return SysTick->VAL;
#endif

#if defined(BBBUSE) || defined(HOSTUSE)
		clock_t timeVal; /* start time */
		timeVal = clock(); /* use clock function from time.h on linux machines */
		return (uint32_t)timeVal;
#endif
	return 0;
}

uint32_t getEndTime(void)
{
#ifdef KL25ZUSE
	return SysTick->VAL; /* grab current val of sys tick */
#endif

#if defined(BBBUSE) || defined(HOSTUSE)
	clock_t timeVal; /* start time */
	timeVal = clock(); /* use clock function from time.h on linux machines */
	return (uint32_t)timeVal;
#endif
	return 0;
}

#ifdef KL25ZUSE
uint32_t getEndTimeDMA(void)
{
	while(dmaTransfer); /* wait while DMA transfer in progress */
	return SysTick->VAL; /* grab current val of sys tick */
}
#endif

uint32_t getTimeElapsed(uint32_t start, uint32_t end)
{
#ifdef KL25ZUSE
	return (start - end);
#endif

#if defined(BBBUSE) || defined(HOSTUSE)
	return (end - start);
#endif
	return 0;
}
