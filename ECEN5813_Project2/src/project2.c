/*
 * project2.c
 *
 *  Created on: Mar 4, 2018
 *      Author: karroshuang
 */

#include "project2.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuf.h"
#include "uart.h"
#include "GPIO.h"
#include "conversion.h"
#include "MKL25Z4.h"

uint32_t alphaCount = 0;  /* Counts the number of alphabetical characters */
uint32_t numCount = 0;	/* Counts the number of numerical characters */
uint32_t punctCount = 0;	/* Counts the number of punctual characters */
uint32_t miscCount = 0;	/* Counts the number of misc. characters */

void printData()
{
	/* Initialize Arrays to Hold ASCII Characters*/
	uint8_t EOLchar[1] = {0x0D};
	uint8_t alphaASCII[10];
	uint8_t numASCII[10];
	uint8_t punctASCII[10];
	uint8_t miscASCII[10];

	/* Displaying Total Alphabetical Characters*/
	uint8_t alphaArray[] = "Total Alphabetical Characters: ";
	uint32_t alphaLength = 31;
	uint8_t* alphaA = alphaArray;
	UART_send_n(alphaA, alphaLength);
	uint8_t alphaASCLength = my_itoa(alphaCount, alphaASCII, 10);
	UART_send_n(alphaASCII, alphaASCLength);
	UART_send(EOLchar);

	/* Displaying Total Numerical Characters*/
	uint8_t numArray[] = "Total Numerical Characters: ";
	uint32_t numLength = 28;
	uint8_t* numA = numArray;
	UART_send_n(numA, numLength);
	uint8_t numASCLength = my_itoa(numCount, numASCII, 10);
	UART_send_n(numASCII, numASCLength);
	UART_send(EOLchar);

	/* Displaying Total Punctuation Characters*/
	uint8_t punctArray[] = "Total Punctual Characters: ";
	uint32_t punctLength = 27;
	uint8_t* punctA = punctArray;
	UART_send_n(punctA, punctLength);
	uint8_t punctASCLength = my_itoa(punctCount, punctASCII, 10);
	UART_send_n(punctASCII, punctASCLength);
	UART_send(EOLchar);

	/* Displaying Total Miscellaneous Characters*/
	uint8_t miscArray[] = "Total Miscellaneous Characters: ";
	uint32_t miscLength = 32;
	uint8_t* miscA = miscArray;
	UART_send_n(miscA, miscLength);
	uint8_t miscASCLength = my_itoa(miscCount, miscASCII, 10);
	UART_send_n(miscASCII, miscASCLength);
	UART_send(EOLchar);

	/* Reset Buffer and data */
	numCount = 0;
	alphaCount = 0;
	punctCount = 0;
	miscCount = 0;
}

void processData()
{
	uint8_t Data;

	while(CB_buffer_remove_item(&CB,&Data) != CB_buff_empty_err)
	{
		if((Data >= 'a' && Data <= 'z') || (Data >= 'A' && Data <= 'Z')){ /*Received data is a Alphabet character*/
		  alphaCount++;
		}
		else if(Data >= '0' && Data <= '9'){ /*Received data is a numerical character*/
		  numCount++;
		}
		else if(Data == '!' || Data == '.' || Data == ',' || Data == '?' || /*Received data is a Punctual character. 0x27 = "'"*/
				Data == '"' || Data == ';' || Data == ':' || Data == 0x27 ||
				Data == '-' || Data == '(' || Data == ')' || Data == '[' ||
				Data == ']' || Data == '{' || Data == '}'){
		  punctCount++;
		}
		else if(Data == 10){ /*If Received data is the new line (terminator) print all the data out */
			  printData();
		  }
		else{ /*Received data is a miscellaneous character*/
		  miscCount++;
		}
	}
}

void project2(){
	__enable_irq(); /* Enable global interrupts */
	CB_init(&CB,32); /* initialize circular buffer CB */
	UART_configure(); /* Configure UART */
	uint8_t Data;
	while(1){
		CB_peek(&CB,0,&Data);
		if(CB_is_full(&CB) || Data == 0x0A){ /*If the buffer is full, process the data so it can write more data in, or if the last data in the buffer is the terminator, print and dump it*/
			processData();
		}
	}
}
