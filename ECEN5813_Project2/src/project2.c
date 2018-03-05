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

#include "conversion.h"

#ifndef HOSTUSE
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "uart.h"
#include "GPIO.h"
#include "MKL25Z4.h"
#endif

uint32_t alphaCount = 0;  /* Counts the number of alphabetical characters */
uint32_t numCount = 0;	/* Counts the number of numerical characters */
uint32_t punctCount = 0;	/* Counts the number of punctual characters */
uint32_t miscCount = 0;	/* Counts the number of misc. characters */

void printdataHost(){
    printf("Total Alphabetical Characters: %d\n", (int)alphaCount);
    printf("Total Numerical Characters: %d\n", (int)numCount);
    printf("Total Punctual Characters: %d\n", (int)punctCount);
    printf("Total Miscellaneous Characters: %d\n", (int)miscCount);

	/* Reset Buffer and data */
	numCount = 0;
	alphaCount = 0;
	punctCount = 0;
	miscCount = 0;
}

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

void processDataHost(uint8_t *dataPointer){
    while(*dataPointer != '\0') { /* \0 is the terminator symbol for an array */
        if (*dataPointer != ' ') { /*Don't count white spaces */
            CB_buffer_add_item(&CB, *dataPointer);
            if (CB_is_full(&CB)) { /*If the buffer is full, process the data so it can write more data in*/
                processData();
            }
        }
        dataPointer++;
    }
}

void project2(){
	CB_init(&CB,32); /* initialize circular buffer CB */
#ifdef HOSTUSE
	/*Initializations*/
    uint8_t str1[1000]; /*Initialize array to hold characters that are going to be read in from host machine*/
    uint8_t* dataPtr = str1; /*Initialize pointer to the beginning of the array */

    while(1){
		/*Read in Data from Host Machine*/
		printf("Enter a string (Maximum of 1000 Characters): ");
		gets(str1); /* Reads a line from stdin and stores it into the string pointed to by str */

		/*Process Data*/
		processDataHost(dataPtr);
	    dataPtr = str1; /* Reset the pointer back to the beginning of the string */

		/*Print Statistics*/
		printdataHost();
    }
#else
    /*Initializations*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
	__enable_irq(); /* Enable global interrupts */
	UART_configure(); /* Configure UART */
	uint8_t Data;

	/*Process Data*/
//	uint8_t s = 0xD6;
//	uint8_t* ptr = &s;
	while(1){
//		UART_send(ptr);
		CB_peek(&CB,0,&Data); /*If the buffer is full, process the data so it can write more data in, or if the last data in the buffer is the terminator, print and dump it*/
		if(CB_is_full(&CB) || Data == 0x0A){
			processData();
		}
	}
#endif
}
