/**
 * @file project4.c
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

#include "project4.h"
#include "circbuf.h"
#include "logger.h"
#include "logger_queue.h"
#include "stdlib.h"
#include "profiling.h"


#ifdef KL25ZUSE
#include "SPI.h"
#include "rtc.h"
#include "GPIO.h"
#include "uart.h"
#include "nordic.h"
#endif

uint8_t project4(void)
{
#ifdef KL25ZUSE
	__enable_irq(); /* Enable global interrupts */
#endif

	CB = (CB_t **)malloc(sizeof(CB_t *)); /* to keep hard fault handler from crashing program */
	LQ_init(CB, 1000); /* init buffer */

	/* init KL25Z modules */
#ifdef KL25ZUSE
	UART_configure(); /* Configure UART */
	GPIO_Configure(); /* GPIO config */
	SPI_init(); /* spi init */
	rtc_init(); /* rtc init */
#endif

	/* initial logging info */
#ifdef LOGGING
	LOG_EVENT(LOGGER_INITIALZED, PROJECTFOUR, NULL, 0x00, CB); /* logger init */

	uint8_t sysInfo[] = "ECEN5813_Project4";
	LOG_EVENT(SYSTEM_ID, PROJECTFOUR, sysInfo, 17, CB); /* system info */

	uint8_t sysVersion[] = "PROJECT4_v1.0";
	LOG_EVENT(SYSTEM_VERSION, PROJECTFOUR, sysVersion, 13, CB); /* system info */

	LOG_EVENT(SYSTEM_INITIALIZED, PROJECTFOUR, NULL, 0x00, CB); /* system init */
#endif

/* program flow, execute spi test and mem profiling */
#ifdef KL25ZUSE
	if(nrf_SPI_test() != 0) return -1; /* test spi comm with nordic chip */
#endif

	memProfiler(); /* profile for memory array */

#ifdef LOGGING
	LOG_EVENT(SYSTEM_HALTED, PROJECTFOUR, NULL, 0x00, CB); /* system init */
	LOG_FLUSH(); /* flush before end of function */
#endif
	while(1); /* infinite loop */

}
