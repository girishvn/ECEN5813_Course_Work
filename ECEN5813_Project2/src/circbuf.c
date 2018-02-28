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

    CB = (CB_t *)malloc(sizeof(CB_t)); /* allocate control structure on the heap */

    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    if(size <= 0)
    {
        return CB_no_length_err;
    }

    CB->CB_buff = (uint8_t *)malloc(size*sizeof(uint8_t)); /* allocate buffer memory on the heap */

    /* Error checking */
    if(CB->CB_buff == NULL)
    {
        return CB_null_ptr_err;
    }

    /* Populate CB members */
    CB->CB_head = CB->CB_buff;
    CB->CB_tail = CB->CB_buff;
    CB->CB_size = size;
    CB->CB_count = 0;

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

    /* Destroy CB */
    free(CB->CB_buff); /* free buffer memory off the heap */
    free(CB); /* free control structure off the heap */

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

    *storedData = *CB->CB_tail;
    CB->CB_count--;

    if(CB->CB_tail == CB->CB_buff + CB->CB_size - 1)
    {
        CB->CB_tail = CB->CB_buff;
    }
    else
    {
        CB->CB_tail++;
    }

    return CB_success;

}

__attribute__((always_inline)) inline int CB_is_full(CB_t * CB)
{
    return (CB->CB_count == CB->CB_size);
}

__attribute__((always_inline)) inline int CB_is_empty(CB_t * CB)
{
    return (CB->CB_count == 0);
}

CB_e CB_peek(CB_t * CB, size_t offset, uint8_t * storedData)
{
    /* Error checking */
    if(CB == NULL)
    {
        return CB_null_ptr_err;
    }

    //dont know what to write here
}
