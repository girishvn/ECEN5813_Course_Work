/**
 * @file logger.h
 * @brief An abstraction of a logger queue using a circ buf structure
 *
 * This header defines the logger queue structure as well as the public interface and functions to the buffer
 *
 * @author Girish Narayanswamy
 * @date April 20, 2018
 * @version 1.0
 *
 */

#include "circbuf.h"

#ifndef SOURCE_LOGGER_QUEUE_H_
#define SOURCE_LOGGER_QUEUE_H_

CB_e LQ_init(CB_t ** LQ, size_t size);

CB_e LQ_destroy(CB_t ** CQ);

CB_e LQ_buffer_add_item(CB_t ** LQ, uint8_t data);

CB_e LQ_buffer_remove_item(CB_t ** LQ, uint8_t * storedData);

int LQ_is_full(CB_t ** LQ);

int LQ_is_empty(CB_t ** LQ);

CB_e LQ_peek(CB_t ** LQ, size_t offset, uint8_t * storedData);

#endif /* SOURCE_LOGGER_QUEUE_H_ */
