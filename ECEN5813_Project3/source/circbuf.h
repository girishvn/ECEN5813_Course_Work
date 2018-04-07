/**
 * @file circbuf.h
 * @brief An abstraction of a circular buffer structure
 *
 * This header defines the circular buffer structure as well as the public interface and functions to the buffer
 *
 * @author Girish Narayanswamy
 * @date Feb. 26, 2018
 * @version 1.0
 *
 */
#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#define KL25ZCRIT
#include <stdint.h>
#include <stdlib.h>

#ifdef KL25ZCRIT /* critical section protection for KL25Z */

#include "MKL25Z4.h"
#define START_CRITICAL() __enable_irq() /* functions defined in core_cmFunc.h */
#define END_CRITICAL()  __disable_irq() /* functions defined in core_cmFunc.h */

#else /* critical section protection not needed for BBB and HOST */

#define START_CRITICAL()
#define END_CRITICAL()

#endif

/**
 * @brief Control structure to the circular buffer
 *
 * The structure contains variables needed for the function of the circular buffer.
 * This includes, the ptr to the buffer, the head, the tail, the size, and the count of the buffer.
 * These are commented more thoroughly below.
 */

typedef struct
{
    uint8_t * CB_buff; /* The allocated memory for the buffer elements */
    uint8_t * CB_head; /* Pointer to Head of the buffer or newest added item */
    uint8_t * CB_tail; /* Pointer to Tail or oldest item added */
    size_t CB_size; /* Number of items to allocate the buffer for */
    size_t CB_count; /* Current item count in the buffer */
} CB_t;

/**
 * @brief  Circular buffer function status enumeration
 *
 * The enumeration contains status information for the output of the various circular buffer functions.
 * These statuses include, succes, null pointer error, no length error, buffer full error, buffer empty error.
 */

typedef enum
{
    CB_success, /* Success / No Errors */
    CB_null_ptr_err, /* Circular Buffer Null Pointer Errors: Returned if any buffer pointer is a null pointer */
    CB_no_length_err, /* No Length Error: Returned if circular buffer initialize given zero length */
    CB_buff_full_err, /* Buffer Full Error: Returned if attempt to add fails because buffer is full */
    CB_buff_empty_err /* Buffer Empty Error: Returned if attempt to remove fails because buffer is empty */
} CB_e;

/**
 * @brief Initialize circular buffer
 *
 * Dynamically allocates space for a circular buffer, and initializes CB struct members
 * Allocates both the CB buffer and control structure on the heap
 *
 * @param pointer to circular buffer to init
 * @param size of uint8_t blocks for circular buffer
 *
 * @return a CB status enumeration value based on the init of the CB
 */
CB_e CB_init(CB_t * CB, size_t size);

/**
 * @brief Destroy circular buffer
 *
 * Dynamically free space for a circular buffer, and free CB struct
 * Free both the CB buffer and control structure from the heap
 *
 * @param pointer to circular buffer to init
 *
 * @return a CB status enumeration value based on the destroy of the CB
 */
CB_e CB_destroy(CB_t * CB);

/**
 * @brief Add a data item to the CB
 *
 * Takes a pointer to the CB and adds a data member to the spot after head
 *
 * @param pointer to circular buffer to add to
 *
 * @return a CB status enumeration value based on the added item of the CB
 */
CB_e CB_buffer_add_item(CB_t * CB, uint8_t data);

/**
 * @brief Remove a data item from the CB
 *
 * Takes a pointer to the CB and removes a data member from the tail into a uint8_t * ptr value.
 * The tail is properly moved after
 *
 * @param pointer to circular buffer to remove from
 * @param ptr value to store removed data
 *
 * @return a CB status enumeration value based on the added item of the CB
 */
CB_e CB_buffer_remove_item(CB_t * CB, uint8_t * storedData);

/**
 * @brief Returns whether the buffer is full or not
 *
 * An inline function that returns whether the buffer is full
 *
 * @param pointer to circular buffer to remove from
 *
 * @return 0 if not full, 1 if full
 */

int CB_is_full(CB_t * CB);

/**
 * @brief Returns whether the buffer is empty or not
 *
 * An inline function that returns whether the buffer is empty
 *
 * @param pointer to circular buffer to remove from
 *
 * @return 0 if not empty, 1 if empty
 */

int CB_is_empty(CB_t * CB);

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
CB_e CB_peek(CB_t * CB, size_t offset, uint8_t * storedData);


typedef struct
{
    uint8_t length;
    uint8_t * string;
    uint16_t CRC;
} CB_buff_t;

typedef struct
{
    CB_buff_t * CB_buff; /* The allocated memory for the buffer elements */
    CB_buff_t * CB_head; /* Pointer to Head of the buffer or newest added item */
    CB_buff_t * CB_tail; /* Pointer to Tail or oldest item added */
    size_t CB_size; /* Number of items to allocate the buffer for */
    size_t CB_count; /* Current item count in the buffer */
} CB_d;


#endif //__CIRCBUF_H__
