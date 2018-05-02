/**
 * @file logger.h
 * @brief An abstraction of a logger class
 *
 * This header defines the interface to logging data about the program
 *
 * @author Girish Narayanswamy
 * @date April 15, 2018
 * @version 2.0
 *
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
	PROJECTFOUR = 0x0a,
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

/**
 * @brief prints data over uart or printf
 *
 * prints raw data
 *
 * @param pointer to data val
 * @param number of bytes to print out
 *
 * @return void
 */
void LOG_RAW_DATA(uint8_t * data, uint32_t length);

/**
 * @brief prints string data over uart or printf
 *
 * prints string data
 *
 * @param pointer to data string
 * @param number of bytes to print out
 *
 * @return void
 */
void LOG_RAW_STRING(uint8_t * string);

/**
 * @brief prints integer data over uart or printf
 *
 * prints integer data
 *
 * @param pointer to data int
 * @param number of bytes to print out
 *
 * @return void
 */
void LOG_RAW_INT(int32_t integer);

/**
 * @brief prints all data in logger buffer
 *
 * prints all data and clears log buffer
 *
 * @param void
 *
 * @return void
 */
void LOG_FLUSH(void);

/**
 * @brief prints entire log item
 *
 * prints log item
 *
 * @param pointer to item struct
 *
 * @return void
 */
void LOG_RAW_ITEM(binLog_t * logItem);


/* KL25Z Functions */

/**
 * @brief prints data over uart or printf
 *
 * prints raw data
 *
 * @param pointer to data val
 * @param number of bytes to print out
 *
 * @return void
 */
void log_data(uint8_t * data, uint32_t length);

/**
 * @brief prints string data over uart or printf
 *
 * prints string data
 *
 * @param pointer to data string
 * @param number of bytes to print out
 *
 * @return void
 */
void log_string(uint8_t * string);

/**
 * @brief prints integer data over uart or printf
 *
 * prints integer data
 *
 * @param pointer to data int
 * @param number of bytes to print out
 *
 * @return void
 */
void log_integer(int32_t integer);

/**
 * @brief prints entire log item
 *
 * prints log item
 *
 * @param pointer to item struct
 *
 * @return void
 */
void log_flush(void);

/**
 * @brief prints entire log item
 *
 * prints log item
 *
 * @param pointer to item struct
 *
 * @return void
 */
void log_item(binLog_t * logItem);

/* BBB Functions */

/**
 * @brief prints data over uart or printf
 *
 * prints raw data
 *
 * @param pointer to data val
 * @param number of bytes to print out
 *
 * @return void
 */
void log_data_printf(uint8_t * data, uint32_t length);

/**
 * @brief prints string data over uart or printf
 *
 * prints string data
 *
 * @param pointer to data string
 * @param number of bytes to print out
 *
 * @return void
 */
void log_string_printf(uint8_t * string);

/**
 * @brief prints integer data over uart or printf
 *
 * prints integer data
 *
 * @param pointer to data int
 * @param number of bytes to print out
 *
 * @return void
 */
void log_integer_printf(int32_t integer);

/**
 * @brief prints entire log item
 *
 * prints log item
 *
 * @param pointer to item struct
 *
 * @return void
 */
void log_flush_printf(void);

/**
 * @brief prints entire log item
 *
 * prints log item
 *
 * @param pointer to item struct
 *
 * @return void
 */
void log_item_printf(binLog_t * logItem);

/* NON-BLOCKING LOG FUNCTIONS */

/* Wrapper function */

/**
 * @brief builds and log item based of input information
 *
 *
 * @param log ID
 * @param module ID
 * @param pointer to payload message
 * @param number of bytes in payload message
 * @param double point to circular buffer/logger queue
 *
 * @return void
 */
void LOG_EVENT(binLog_e logID, uint8_t moduleID, uint8_t * payload, uint8_t payloadLen, CB_t ** LQ);

/**
 * @brief logs an item onto the circular buffer
 *
 *
 * @param pointer to log item to log
 * @param double point to circular buffer/logger queue
 *
 * @return void
 */
void LOG_ITEM(binLog_t * logItem, CB_t ** CB);

/**
 * @brief calculates the checksum for an item data package
 *
 * @param pointer to log item to generate checksum for
 *
 * @return checksum value
 */
uint32_t GEN_CHECK_SUM(binLog_t * logItem);

/**
 * @brief get RTC clock value
 *
 * @param void
 *
 * @return real time in seconds
 */
uint32_t GET_RTC_TIME(void);


#endif /* SOURCE_LOGGER_H_ */
