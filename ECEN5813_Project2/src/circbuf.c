/**
 * @file circbuf.c
 * @brief An implementation fle of a circular buffer
 *
 * This file implements the circular buffer structure as well as the functions to access and build the buffer
 *
 * @author Girish Narayanswamy
 * @date Feb. 26, 2018
 * @version 1.0
 *
 */

#include "circbuf.h"

CB_e CB_init(CB_t * CB, size_t size)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    /* Error checking */
    if(size <= 0)
    {
        return CB_no_length_err;
    }

    START_CRITICAL();
    CB->CB_buff = (uint8_t *)malloc(size*sizeof(uint8_t)); /* allocate buffer memory on the heap */

    /* Error checking */
    if(CB->CB_buff == NULL)
    {
        return CB_null_ptr_err;
    }

    /* Populate CB members */
    CB->CB_size = size;
    CB->CB_head = CB->CB_buff + CB->CB_size - 1;
    CB->CB_tail = CB->CB_buff;
    CB->CB_count = 0;
    END_CRITICAL();

    return CB_success;
}

CB_e CB_destroy(CB_t * CB)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    if(CB->CB_buff == NULL)
    {
        return CB_null_ptr_err;
    }

    START_CRITICAL();
    /* Destroy CB */
    free(CB->CB_buff); /* free buffer memory off the heap */
    END_CRITICAL();

    return CB_success;
}

CB_e CB_buffer_add_item(CB_t * CB, uint8_t data)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    if(CB_is_full(CB))
    {
        return CB_buff_full_err;
    }

    START_CRITICAL();
    if(CB->CB_head == CB->CB_buff + CB->CB_size - 1)/* iterate to next open block */
    {
        CB->CB_head = CB->CB_buff;
    }
    else
    {
        CB->CB_head++;
    }

    *CB->CB_head = data;
    CB->CB_count++;
    END_CRITICAL();

    return CB_success;
}

CB_e CB_buffer_remove_item(CB_t * CB, uint8_t * storedData)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    if(CB_is_empty(CB))
    {
        return CB_buff_empty_err;
    }

    START_CRITICAL();
    *storedData = *CB->CB_tail;
    CB->CB_count--;

    if(CB->CB_tail == CB->CB_buff + CB->CB_size - 1) /* wrap around */
    {
        CB->CB_tail = CB->CB_buff;
    }
    else /* else increment */
    {
        CB->CB_tail++;
    }
    END_CRITICAL();

    return CB_success;

}

__attribute__((always_inline)) inline int CB_is_full(CB_t * CB)
{
    return (CB->CB_count == CB->CB_size); /* if full return 1 */
}

__attribute__((always_inline)) inline int CB_is_empty(CB_t * CB)
{
    return (CB->CB_count == 0); /* if empty return 1 */
}

CB_e CB_peek(CB_t * CB, size_t offset, uint8_t * storedData)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    START_CRITICAL();
    if(CB->CB_head - offset >= CB->CB_buff) /* not overflowed to other side of buffer */
    {
        *storedData = *(CB->CB_head - offset);
    }
    else /* overflowed to other side of buffer */
    {
        *storedData = *(CB->CB_head - offset + CB->CB_size);
    }
    END_CRITICAL();

    return CB_success;
}
