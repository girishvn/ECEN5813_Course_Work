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

/**
 * @brief Initialize log queue buffer
 *
 * Dynamically allocates space for a circular buffer, and initializes CB struct members
 * Allocates both the CB buffer and control structure on the heap
 *
 * @param pointer to LQ to init
 * @param size of uint8_t blocks for circular buffer
 *
 * @return a CB status enumeration value based on the init of the CB
 */
CB_e LQ_init(CB_t ** LQ, size_t size);

/**
 * @brief Destroy log queue
 *
 * Dynamically free space for a circular buffer, and free CB struct
 * Free both the CB buffer and control structure from the heap
 *
 * @param pointer to circular buffer to init
 *
 * @return a CB status enumeration value based on the destroy of the CB
 */
CB_e LQ_destroy(CB_t ** CQ);

/**
 * @brief Add a data item to the LQ
 *
 * Takes a pointer to the CB and adds a data member to the spot after head
 *
 * @param pointer to circular buffer to add to
 *
 * @return a CB status enumeration value based on the added item of the CB
 */
CB_e LQ_buffer_add_item(CB_t ** LQ, uint8_t data);

/**
 * @brief Remove a data item from the LQ
 *
 * Takes a pointer to the CB and removes a data member from the tail into a uint8_t * ptr value.
 * The tail is properly moved after
 *
 * @param pointer to circular buffer to remove from
 * @param ptr value to store removed data
 *
 * @return a CB status enumeration value based on the added item of the CB
 */
CB_e LQ_buffer_remove_item(CB_t ** LQ, uint8_t * storedData);

/**
 * @brief Returns whether the buffer is full or not
 *
 * An inline function that returns whether the buffer is full
 *
 * @param pointer to circular buffer to remove from
 *
 * @return 0 if not full, 1 if full
 */
int LQ_is_full(CB_t ** LQ);

/**
 * @brief Returns whether the buffer is empty or not
 *
 * An inline function that returns whether the buffer is empty
 *
 * @param pointer to circular buffer to remove from
 *
 * @return 0 if not empty, 1 if empty
 */
int LQ_is_empty(CB_t ** LQ);

/**
 * @brief Peek a data value in the CB relative to the head
 *
 * Takes a pointer to the CB and peeks at a value in the buffer an offset distance from the head.
 *
 * @param pointer to circular buffer to remove from
 * @param an offset from the head
 * @param a pointer to store the peeked value into.
 *
 * @return a CB status enumeration value based on the added item of the CB
 */
CB_e LQ_peek(CB_t ** LQ, size_t offset, uint8_t * storedData);

#endif /* SOURCE_LOGGER_QUEUE_H_ */
