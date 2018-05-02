/*
 * logger.c
 *
 *  Created on: Apr 30, 2018
 *      Author: girishnarayanswamy
 */

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include "logger.h"
#include "logger_queue.h"
#include "uart.h"
#include "conversion.h"
#include "platform.h"
#include "rtc.h"

#ifdef BBBUSE
#include "string.h"
#endif

/* BLOCKING LOGGING FUNCTIONS */

/* Wrapper logging functions */
void LOG_RAW_DATA(uint8_t * data, uint32_t length)
{
#ifdef KL25ZUSE
	log_data(data, length);
#else
	log_data_printf(data, length);
#endif

	return;
}

void LOG_RAW_STRING(uint8_t * string)
{
#ifdef KL25ZUSE
	log_string(string);
#else
	log_string_printf(string);
#endif

	return;
}

void LOG_RAW_INT(int32_t integer)
{
#ifdef KL25ZUSE
	log_integer(integer);
#else
	log_integer_printf(integer);
#endif

	LOG_EVENT(LOGGER_INITIALZED, LOGGER, NULL, 0x00, CB); /* logger initialized */

	return;
}

void LOG_FLUSH(void)
{
#ifdef KL25ZUSE
	log_flush();
#else
	log_flush_printf();
#endif

	return;
}

void LOG_RAW_ITEM(binLog_t * logItem)
{
#ifdef KL25ZUSE
	log_item(logItem);
#else
	log_item_printf(logItem);
#endif

	return;
}

/* KL25Z logging functions */
#ifdef KL25ZUSE
void log_data(uint8_t * data, uint32_t length)
{
	UART_send_n(data, length);
	return;
}

void log_string(uint8_t * string)
{
	while(*string != '\0')
	{
		UART_send(string); /*Send a byte of data into the buffer*/
		string++; /*Increment the pointer to send the next byte */
	}
	//tx_block_data -= length; /*Reset the pointer back to the start of the string */ //girish dont need this ??????
	return;
}

void log_integer(int32_t integer)
{
	uint8_t strPtr[12];
	uint8_t strLen = 0;
	strLen = my_itoa(integer, strPtr, 10);
	UART_send_n(strPtr,strLen);

	return;
}

void log_flush(void) //girish
{
	uint8_t dataPtr;

	while(LQ_buffer_remove_item(CB, &dataPtr) != CB_buff_empty_err)
	{
		UART_send(&dataPtr);
	}

	return;
}

void log_item(binLog_t * logItem)
{
	uint8_t spaceChar[] = " ";

	log_integer((uint32_t)logItem->logID);
	log_data(spaceChar,0x01); /* add space */

	log_integer((uint32_t)logItem->moduleID);
	log_data(spaceChar,0x01); /* add space */

	log_integer(logItem->timeStamp);
	log_data(spaceChar,0x01); /* add space */

	log_integer((uint32_t)logItem->logID);
	log_data(spaceChar,0x01); /* add space */

	log_data(logItem->payload, logItem->logLength);
	log_data(spaceChar,0x01); /* add space */

	log_integer(logItem->checkSum);
	log_data(spaceChar,0x01); /* add space */

	return;
}
#endif

/* BBB logging functions */
#if defined(BBBUSE) || defined(HOSTUSE)
void log_data_printf(uint8_t * data, uint32_t length)
{
	while(length > 0)
	{
		printf("%c", (*data));
		data++;
		length--;
	}
	return;
}

void log_string_printf(uint8_t * string)
{
	printf("%s",string);
	return;
}

void log_integer_printf(int32_t integer)
{
	printf("%d",(int) integer);
	return;
}

void log_flush_printf(void)
{
	while(!CB_is_empty(CB)); //girish???????
}

void log_item_printf(binLog_t * logItem)
{
	uint8_t spaceChar[] = " ";

	log_integer_printf((uint32_t)logItem->logID);
	log_data_printf(spaceChar,0x01); /* add space */

	log_integer_printf((uint32_t)logItem->moduleID);
	log_data_printf(spaceChar,0x01); /* add space */

	log_integer_printf(logItem->timeStamp);
	log_data_printf(spaceChar,0x01); /* add space */

	log_integer_printf((uint32_t)logItem->logID);
	log_data_printf(spaceChar,0x01); /* add space */

	log_data_printf(logItem->payload, logItem->logLength);
	log_data_printf(spaceChar,0x01); /* add space */

	log_integer_printf(logItem->checkSum);
	log_data_printf(spaceChar,0x01); /* add space */
}
#endif

/* NON-BLOCKING LOG FUNCTIONS */

/* Wrapper function */
void LOG_EVENT(binLog_e logID, uint8_t moduleID, uint8_t * payload, uint8_t payloadLen, CB_t ** LQ)
{
	binLog_t * item = NULL;
	item = (binLog_t *)malloc(sizeof(binLog_t));

	item->logID = (uint8_t) logID;
	item->moduleID = moduleID;
	item->timeStamp = GET_RTC_TIME(); // girish implement
	item->logLength = payloadLen;
	item->payload = payload;
	item->checkSum = GEN_CHECK_SUM(item);

	LOG_ITEM(item, LQ);
	free(item);
}

void LOG_ITEM(binLog_t * logItem, CB_t ** LQ)
{
	uint8_t i; /* iterator variable */
	uint8_t * dataPtr; /* ptr to push 8 bit vals onto buffer */
	uint8_t endOfLine = (uint8_t)'\n';

	uint8_t strPtr[] = {'0','0'};
	uint8_t strLen = 0;

	strLen = my_itoa(logItem->logID, strPtr, 16); /* log logID */
	if(!strPtr[0]) strPtr[0] = '0';
	if(!strPtr[1]) strPtr[1] = '0';
	if(LQ_buffer_add_item(LQ,strPtr[1])) LOG_FLUSH();
	if(LQ_buffer_add_item(LQ,strPtr[0])) LOG_FLUSH();


	strLen = my_itoa(logItem->moduleID, strPtr, 16); /* log moduleID */
	if(!strPtr[0]) strPtr[0] = '0';
	if(!strPtr[1]) strPtr[1] = '0';
	if(LQ_buffer_add_item(LQ,strPtr[1])) LOG_FLUSH();
	if(LQ_buffer_add_item(LQ,strPtr[0])) LOG_FLUSH();

	dataPtr = (uint8_t *) &logItem->timeStamp; /* log time stamp in 8 individual chars */
	for(i = 0; i < 4; i++)
	{
		strLen = my_itoa(*(dataPtr + 3 - i), strPtr, 16); /* log moduleID */
		if(!strPtr[0]) strPtr[0] = '0';
		if(!strPtr[1]) strPtr[1] = '0';
		if(LQ_buffer_add_item(LQ,strPtr[0])) LOG_FLUSH(); /* log logID */
		if(LQ_buffer_add_item(LQ,strPtr[1])) LOG_FLUSH(); /* log logID */
	}

	strLen = my_itoa(logItem->logLength, strPtr, 16); /* log moduleID */
	if(!strPtr[0]) strPtr[0] = '0';
	if(!strPtr[1]) strPtr[1] = '0';
	if(LQ_buffer_add_item(LQ,strPtr[1])) LOG_FLUSH();
	if(LQ_buffer_add_item(LQ,strPtr[0])) LOG_FLUSH();

	dataPtr = logItem->payload; /* log pay load in x individual bytes */
	for(i = 0; i < logItem->logLength; i++)
	{
		if(LQ_buffer_add_item(LQ,*(dataPtr + i))) LOG_FLUSH();
	}

	dataPtr = (uint8_t *) &logItem->checkSum; /* log time stamp in 8 individual chars */
	for(i = 0; i < 4; i++)
	{
		strLen = my_itoa(*(dataPtr + 3 - i), strPtr, 16); /* log moduleID */
		if(!strPtr[0]) strPtr[0] = '0';
		if(!strPtr[1]) strPtr[1] = '0';
		if(LQ_buffer_add_item(LQ,strPtr[0])) LOG_FLUSH(); /* log logID */
		if(LQ_buffer_add_item(LQ,strPtr[1])) LOG_FLUSH(); /* log logID */
	}

	dataPtr = &endOfLine; /* log end of line after item */
	if(LQ_buffer_add_item(LQ,*dataPtr)) LOG_FLUSH();

	return;
}

uint32_t GEN_CHECK_SUM(binLog_t * logItem)
{
	uint32_t checkSum = 0x00000000;
	uint8_t i; /* iterator variable */

	checkSum += (uint32_t) logItem->logID;
	checkSum += (uint32_t) logItem->moduleID;
	checkSum += logItem->timeStamp;
	checkSum += (uint32_t) logItem->logLength;

	for(i = 0; i < logItem->logLength; i++)
	{
		checkSum += (uint32_t) *(logItem->payload + i);
	}

	return checkSum; /* return checkSum value */
}

uint32_t GET_RTC_TIME(void)
{
#ifdef KL25ZUSE
	return RTC_seconds;
#endif

#if defined(BBBUSE) || defined(HOSTUSE)

#endif
}

