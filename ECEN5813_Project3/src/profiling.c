/**
 * @file profiling.c
 * @brief Implementation of the profiling.h file
 *
 * This source file holds implementations for function which profile memory time usage for various mem transfer functions
 *
 * @author Girish Narayanswamy
 * @date April 10 2018
 * @version 1.0
 *
 */

#include "profiling.h"
#include "memory.h"
#include "timer.h" /* timer functiosn for kl25 and BBB/host */
#include "platform.h" /* PRINTF def */
#include <string.h> /*std mem mv and set functions */
#include <stdlib.h>

#ifdef KL25ZUSE
#include "dma.h"
#include "uart.h"
#include "MKL25Z4.h"
#include "conversion.h"
#endif

void memProfiler(void)
{
	configureSysTick(); /* setup up sys tick for timing */

	/* setup up source and destination addresses for mem transfers/sets */
	uint8_t * src;
	src = (uint8_t *)malloc(10000*sizeof(uint8_t)); /* allocate array for memory transfers on heap */
	uint8_t * dst = src + (5500); /* set the dst address 5000 off src */

	/* local variables for various byte transfer sizes and for timing */
	size_t byteNum[4] = {10, 100, 1000, 5000}; /* various mem transfer/set sizes */
	uint32_t start; /* start time */
	uint32_t end; /* end time */
	uint8_t i, j; /* for loop iterators */

	for(i = 0; i < 4; i++) /* for loop for iterating between various byteNums */
	{
		for(j = 0; j < 4; j++) /* for loop for averaging test results */
		{
			/* functions to get time vals */
			start = getStartTime();
			memset(src, i, byteNum[i]); /* standard mem set */
			end = getEndTime();
			stdMemSet[i] += getTimeElapsed(start, end);

			start = getStartTime();
			my_memset(src, byteNum[i], 0x00); /* my mem set */
			end = getEndTime();
			myMemSet[i] += getTimeElapsed(start, end);

#ifdef KL25ZUSE
			start = getStartTime();
			memset_dma(src, byteNum[i], i); /* standard mem set */
			end = getEndTimeDMA();
			myDMAMemSet[i] += getTimeElapsed(start, end);

			/*dmaInitTime += (dmaStart - dmaEnd);*/
#endif

			start = getStartTime();
			memmove(dst, src, byteNum[i]); /* standard mem move */
			end = getEndTime();
			stdMemMv[i] += getTimeElapsed(start, end);

			start = getStartTime();
			my_memmove(src, dst, byteNum[i]); /* my mem move */
			end = getEndTime();
			myMemMv[i] += getTimeElapsed(start, end);

#ifdef KL25ZUSE
			start = getStartTime();
			memmove_dma(src, dst, byteNum[i], DMASIZE8);
			end = getEndTimeDMA();
			myDMAMemMv[i] += getTimeElapsed(start, end);
#endif
		}

		/* average time values over 4 test iterations */
		stdMemSet[i] = (uint32_t) (stdMemSet[i] / 4);
		myMemSet[i] = (uint32_t) (myMemSet[i] / 4);
		stdMemMv[i] = (uint32_t) (stdMemMv[i] / 4);
		myMemMv[i] = (uint32_t) (myMemMv[i] / 4);
#ifdef KL25ZUSE
		myDMAMemSet[i] = (uint32_t) (myDMAMemSet[i] / 4);
		myDMAMemMv[i] = (uint32_t) (myDMAMemMv[i] / 4);
		/* dmaInitTime = dmaInitTime / 4; */
#endif
	}

	free(src); /* free src space on stack */

	//stackUsageProfiler(); /* in progress function */

	generateProfileReport();
	return;
}

void stackUsageProfiler(void) /* needs to be finished girish */
{
	uint32_t stackTestVal = 0x4D656D65; /* write "Meme" onto stack */
	uint32_t stackTop = (0x1FFFF000 + 0x00004000);
	uint32_t * val = (uint32_t *)stackTop; /* top of stack */

	while(*val != stackTestVal)
	{
		val++; /* iterate to the next block on the stack */
	}

	stackUsage = stackTop - (uint32_t)val;

	/* search stack */
	return;
}

void generateProfileReport(void)
{
#ifdef KL25ZUSE
	/* uart set up */
	__enable_irq(); /* Enable global interrupts */
	UART_configure(); /* Configure UART */

	uint8_t strPtr[12];
	uint8_t strLen = 0;

	/* main title */
	UART_send_n(title, titleLen);
	UART_send_n(lineEnd, lineEndLen);

	/* set title */
	UART_send_n(setTitle, setTitleLen);
	UART_send_n(lineEnd, lineEndLen);

	/* std set */
	UART_send_n(stdSetTitle, stdSetLen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(stdMemSet[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(stdMemSet[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(stdMemSet[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(stdMemSet[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(stdMemSet[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

	/* my set */
	UART_send_n(mySetTitle, mySetLen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myMemSet[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myMemSet[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(myMemSet[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(myMemSet[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(myMemSet[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

	/* my dma set */
	UART_send_n(mySetDMATitle, mySetDMALen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myDMAMemSet[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(myDMAMemSet[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(myDMAMemSet[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(myDMAMemSet[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

	/* mv title */
	UART_send_n(mvTitle, mvTitleLen);
	UART_send_n(lineEnd, lineEndLen);

	/* std mv */
	UART_send_n(stdMvTitle, stdMvLen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(stdMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(stdMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(stdMemMv[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(stdMemMv[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(stdMemMv[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

	/* my move */
	UART_send_n(myMvTitle, myMvLen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(myMemMv[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(myMemMv[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(myMemMv[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

	/* my dma move */
	UART_send_n(myMvDMATitle, myMvDMALen);
	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myDMAMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes10, bytes10Len);
	strLen = my_itoa(myDMAMemMv[0], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes100, bytes100Len);
	strLen = my_itoa(myDMAMemMv[1], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes1000, bytes1000Len);
	strLen = my_itoa(myDMAMemMv[2], strPtr, 10);
	UART_send_n(strPtr,strLen);

	UART_send_n(bytes5000, bytes5000Len);
	strLen = my_itoa(myDMAMemMv[3], strPtr, 10);
	UART_send_n(strPtr,strLen);
	UART_send_n(lineEnd, lineEndLen);
	UART_send_n(lineEnd, lineEndLen);

#endif

#ifdef BBBUSE
	PRINTF("%s",setTitle);
	PRINTF("%s",lineEnd);

	PRINTF("%s",stdSetTitle);
	PRINTF("%s%d%s%d%s%d%s%d%s",bytes10,stdMemSet[0],bytes100,stdMemSet[1],bytes1000,stdMemSet[2],bytes5000,stdMemSet[3],lineEnd);
	PRINTF("%s",lineEnd);

	PRINTF("%s",mySetTitle);
	PRINTF("%s%d%s%d%s%d%s%d%s",bytes10,myMemSet[0],bytes100,myMemSet[1],bytes1000,myMemSet[2],bytes5000,myMemSet[3],lineEnd);
	PRINTF("%s",lineEnd);

	PRINTF("%s",mvTitle);
	PRINTF("%s",lineEnd);

	PRINTF("%s",stdMvTitle);
	PRINTF("%s%d%s%d%s%d%s%d%s",bytes10,stdMemMv[0],bytes100,stdMemMv[1],bytes1000,stdMemMv[2],bytes5000,stdMemMv[3],lineEnd);
	PRINTF("%s",lineEnd);

	PRINTF("%s",myMvTitle);
	PRINTF("%s%d%s%d%s%d%s%d%s",bytes10,myMemMv[0],bytes100,myMemMv[1],bytes1000,myMemMv[2],bytes5000,myMemMv[3],lineEnd);
#endif

	return;
}
