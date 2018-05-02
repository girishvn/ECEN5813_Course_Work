/*
 * logger.h
 *
 *  Created on: Apr 30, 2018
 *      Author: girishnarayanswamy
 */

#ifndef SOURCE_LOGGER_H_
#define SOURCE_LOGGER_H_

#include "stdint.h"
#include "circbuf.h"

typedef struct /* log item structure */
{
	uint8_t logID;
	uint8_t moduleID;
	uint32_t timeStamp;
	uint8_t logLength;
	uint8_t * payload;
	uint32_t checkSum;
}binLog_t;

typedef enum /* binary logger event type enumeration */
{
	SYSTEM_ID = 0x00,
	SYSTEM_VERSION,
	LOGGER_INITIALZED,
	GPIO_INITIALZED,
	SYSTEM_INITIALIZED,
	SYSTEM_HALTED,
	INFO,
	WARNING,
	ERROR,
	PROFILING_STARTED,
	PROFILING_RESULT,
	PROFILING_COMPLETED,
	DATA_RECEIVED,
	DATA_ANALYSIS_STARTED,
	DATA_ALPHA_COUNT,
	DATA_NUMERIC_COUNT,
	DATA_PUNCTUATION_COUNT,
	DATA_MISC_COUNT,
	DATA_ANALYSIS_COMPLETED,
	HEARTBEAT,
	CORE_DUMP
}binLog_e;


typedef enum /* binary logger file ID enumeration */
{
	CIRCBUF = 0x00,
	CONVERSION,
	DMA,
	GPIO,
	LOGGER,
	LOGGERQUEUE,
	MAIN,
	MEMORY,
	NORDIC,
	PROFILING,
	PROJECTFOUR,
	SPI,
	TIMER,
	UART,
	RTCLOCK,
	PROF_STDSET,
	PROF_MYSET,
	PROF_DMASET,
	PROF_STDMV,
	PROF_MYMV,
	PROF_DMAMV,
}fileID_e;

/* BLOCKING LOG FUNCTIONS */

/* Wrapper functions */
void LOG_RAW_DATA(uint8_t * data, uint32_t length);

void LOG_RAW_STRING(uint8_t * string);

void LOG_RAW_INT(int32_t integer);

void LOG_FLUSH(void);

void LOG_RAW_ITEM(binLog_t * logItem);


/* KL25Z Functions */
void log_data(uint8_t * data, uint32_t length);

void log_string(uint8_t * string);

void log_integer(int32_t integer);

void log_flush(void);

void log_item(binLog_t * logItem);

/* BBB Functions */
void log_data_printf(uint8_t * data, uint32_t length);

void log_string_printf(uint8_t * string);

void log_integer_printf(int32_t integer);

void log_flush_printf(void);

void log_item_printf(binLog_t * logItem);

/* NON-BLOCKING LOG FUNCTIONS */

/* Wrapper function */
void LOG_EVENT(binLog_e logID, uint8_t moduleID, uint8_t * payload, uint8_t payloadLen, CB_t ** LQ);

void LOG_ITEM(binLog_t * logItem, CB_t ** CB);

uint32_t GEN_CHECK_SUM(binLog_t * logItem);

uint32_t GET_RTC_TIME(void);


#endif /* SOURCE_LOGGER_H_ */
