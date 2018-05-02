/**
 * @file logger_queue.c
 * @brief An implementation file of a logger queue using a circular buffer
 *
 * This file implements the logger queue structure as well as the functions to access and build the buffer
 *
 * @author Girish Narayanswamy
 * @date April 20, 2018
 * @version 1.0
 *
 */

#include "logger_queue.h"
#include "logger.h"

CB_e LQ_init(CB_t ** LQ, size_t size)
{
	return CB_init(LQ, size);
}

CB_e LQ_destroy(CB_t ** LQ)
{
	return CB_destroy(LQ);
}

CB_e LQ_buffer_add_item(CB_t ** LQ, uint8_t data)
{
	return CB_buffer_add_item(LQ, data);
}

CB_e LQ_buffer_remove_item(CB_t ** LQ, uint8_t * storedData)
{
	return CB_buffer_remove_item(LQ, storedData);
}

int LQ_is_full(CB_t ** LQ)
{
#ifdef LOGGING
	uint8_t fullWarning[] = "queue full";
	LOG_EVENT(WARNING, LOGGERQUEUE, fullWarning, 10, CB); /* warning log */
#endif
	return CB_is_full(LQ);
}

int LQ_is_empty(CB_t ** LQ)
{
#ifdef LOGGING
	uint8_t emptyWarning[] = "queue empty";
	LOG_EVENT(WARNING, LOGGERQUEUE, emptyWarning, 11, CB); /* warning log */
#endif
	return CB_is_empty(LQ);
}

CB_e LQ_peek(CB_t ** LQ, size_t offset, uint8_t * storedData)
{
	return CB_peek(LQ, offset, storedData);
}


