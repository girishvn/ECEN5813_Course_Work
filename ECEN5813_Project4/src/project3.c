/**
 * @file project3.c
 * @brief Implementation of the project3.h file
 *
 * This source file holds a the logic program flow for project 3 for PES EcEN 5813
 *
 * @author Girish Narayanswamy
 * @date April 10 2018
 * @version 1.0
 *
 */

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

#include "project3.h"
#include "profiling.h"
#include "circbuf.h"

#ifdef KL25ZUSE
#include "nordic.h"
#include "dma.h"
#endif


uint8_t project3(void)
{
	CB = (CB_t **)malloc(sizeof(CB_t *)); /* to keep hard fault handler from crashing program */
	CB_init(CB, 32); /* init buffer */

#ifdef KL25ZUSE
	if(nrf_SPI_test() != 0) return -1; /* test spi comm with nordic chip */
#endif

	memProfiler(); /* profile for memory array */

	while(1); /* infinite loop */

}
