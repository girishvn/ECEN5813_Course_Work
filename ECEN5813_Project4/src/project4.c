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
#include "conversion.h"

#ifdef KL25ZUSE
#include "SPI.h"
#include "rtc.h"
#include "GPIO.h"
#include "uart.h"
#include "nordic.h"
#endif

/*************************************************************************************************************************/

uint32_t alphaCount = 0;  /* Counts the number of alphabetical characters */
uint32_t numCount = 0;	/* Counts the number of numerical characters */
uint32_t punctCount = 0;	/* Counts the number of punctual characters */
uint32_t miscCount = 0;	/* Counts the number of misc. characters */

void printData()
{
	/* Initialize Arrays to Hold ASCII Characters*/
	uint8_t alphaASCII[10];
	uint8_t numASCII[10];
	uint8_t punctASCII[10];
	uint8_t miscASCII[10];

	/* Logging Total Alphabetical Characters*/
	uint8_t alphaASCLength = my_itoa(alphaCount, alphaASCII, 10);
	LOG_EVENT(DATA_ALPHA_COUNT, PROJECTFOUR, alphaASCII, alphaASCLength, CB);

	/* Logging Total Numerical Characters*/
	uint8_t numASCLength = my_itoa(numCount, numASCII, 10);
	LOG_EVENT(DATA_NUMERIC_COUNT, PROJECTFOUR, numASCII, numASCLength, CB);

	/* Logging Total Punctuation Characters*/
	uint8_t punctASCLength = my_itoa(punctCount, punctASCII, 10);
	LOG_EVENT(DATA_PUNCTUATION_COUNT, PROJECTFOUR, punctASCII, punctASCLength, CB);

	/* Logging Total Miscellaneous Characters*/
	miscCount--;
	uint8_t miscASCLength = my_itoa(miscCount, miscASCII, 10);
	LOG_EVENT(DATA_MISC_COUNT, PROJECTFOUR, miscASCII, miscASCLength, CB);

	/* Reset Buffer and data */
	numCount = 0;
	alphaCount = 0;
	punctCount = 0;
	miscCount = 0;

	LOG_EVENT(DATA_ANALYSIS_COMPLETED, PROJECTFOUR, NULL, 0x00, CB);
}

void processData()
{
	LOG_EVENT(DATA_ANALYSIS_STARTED, PROJECTFOUR, NULL, 0x00, CB);
	uint8_t Data;

	while(CB_buffer_remove_item(CB,&Data) != CB_buff_empty_err)
	{
		if((Data >= 'a' && Data <= 'z') || (Data >= 'A' && Data <= 'Z'))  /*Received data is a Alphabet character*/
		{
			alphaCount++;
		}
		else if(Data >= '0' && Data <= '9') /*Received data is a numerical character*/
		{
			numCount++;
		}
		else if(Data == '!' || Data == '.' || Data == ',' || Data == '?' || /*Received data is a Punctual character. 0x27 = "'"*/
				Data == '"' || Data == ';' || Data == ':' || Data == 0x27 ||
				Data == '-' || Data == '(' || Data == ')' || Data == '[' ||
				Data == ']' || Data == '{' || Data == '}')
		{
		  punctCount++;
		}
		else if(Data == ' ') /*Don't count white spaces*/
		{
			continue;
		}
		else /*Received data is a miscellaneous character*/
		{
			miscCount++;
		}

		UART_send(&Data); /* print out to log */
	}
	printData();
}

#if defined(BBBUSE) || defined(HOSTUSE)
void printdataHost()
{
    PRINTF("Total Alphabetical Characters: %d\n", (int)alphaCount);
    PRINTF("Total Numerical Characters: %d\n", (int)numCount);
    PRINTF("Total Punctual Characters: %d\n", (int)punctCount);
    PRINTF("Total Miscellaneous Characters: %d\n", (int)miscCount);

	/* Reset Buffer and data */
	numCount = 0;
	alphaCount = 0;
	punctCount = 0;
	miscCount = 0;
}

void processDataHost(uint8_t *dataPointer)
{
    while(dataPointer != '\0') { /* \0 is the terminator symbol for an array */
        if (*dataPointer != ' ') { /*Don't count white spaces */
            CB_buffer_add_item(CB, *dataPointer);
            if (CB_is_full(CB)) { /*If the buffer is full, process the data so it can write more data in*/
                processData();
            }
        }
        dataPointer++;
    }
}
#endif

/*************************************************************************************************************************/


uint8_t project4(void)
{
#ifdef KL25ZUSE
	__enable_irq(); /* Enable global interrupts */
#endif

	CB = (CB_t **)malloc(sizeof(CB_t *)); /* to keep hard fault handler from crashing program */
	LQ_init(CB, 500); /* init buffer */

	/* init KL25Z modules */
#ifdef KL25ZUSE
	UART_configure(); /* Configure UART */
	LOG_FLUSH();
	GPIO_Configure(); /* GPIO config */
	SPI_init(); /* spi init */
	rtc_init(); /* rtc init */
#endif

	/* initial logging info */
#ifdef LOGGING
	LOG_EVENT(LOGGER_INITIALZED, PROJECTFOUR, NULL, 0x00, CB); /* logger init */

	uint8_t sysInfo[] = "ECEN5813_Project4";
	LOG_EVENT((uint8_t) SYSTEM_ID, (uint8_t) PROJECTFOUR, sysInfo, 17, CB); /* system info */

	uint8_t sysVersion[] = "PROJECT4_v1.0";
	LOG_EVENT((uint8_t) SYSTEM_VERSION, (uint8_t) PROJECTFOUR, sysVersion, 13, CB); /* system info */

	LOG_EVENT(SYSTEM_INITIALIZED, PROJECTFOUR, NULL, 0x00, CB); /* system init */
#endif

/* program flow, execute spi test and mem profiling */
#ifdef KL25ZUSE
	if(nrf_SPI_test() != 0) return -1; /* test spi comm with nordic chip */
#endif

	memProfiler(); /* profile for memory array */


	processData(); /* process data and get function metrics / info */

#ifdef KL25ZUSE
	/* get core information */
	uint32_t sp = __get_MSP();
#endif

#ifdef LOGGING
	uint8_t infoStr[] = "Will_flush_and_coredump_before_infinite_loop";
	LOG_EVENT(INFO, PROJECTFOUR, infoStr, 44, CB);

#ifdef KL25ZUSE
	uint8_t strPtr[12];
	uint8_t strLen = my_itoa(sp, strPtr, 10);
	LOG_EVENT(CORE_DUMP, PROJECTFOUR, strPtr, strLen, CB);
#endif

	LOG_EVENT(SYSTEM_HALTED, PROJECTFOUR, NULL, 0x00, CB); /* system init */

	LOG_FLUSH(); /* flush before end of function */
#endif
	while(1); /* infinite loop */

}
