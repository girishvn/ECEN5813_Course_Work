/**
 * @file memory.c
 * @brief Implementation of the memory.h file
 *
 * This source file holds implementations for memory abstraction functions from the memory.h file
 *
 * @author Girish Narayanswamy & Karros Huang
 * @date April 1, 2018
 * @version 2.0
 *
 */

#include "memory.h"
#include <stdlib.h> /* includes malloc and free */

uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length)
{
    /* variable declarations */
    size_t i; /* iterator variable */


    /* error and exception checking */
    if(src == NULL || dst == NULL) /* checking for bad pointer access */
    {
        return NULL;
    }

    /* mem move */
    if(src > dst) /* first scenario src > dst in mem */
    {
        for(i = 0; i < length; i++)
        {
            *(dst + i) = *(src + i); /* move byte from source to destination */
        }
    }
    else if(src < dst) /* second scenario src < dst in mem */
    {
        for(i = length; i > 0; i--)
        {
            *(dst + i - 1) = *(src + i - 1); /* move byte from source to destination */
        }
    }

    return dst; /* return pointer to destination */
}

uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length)
{
    /* variable declarations */
    size_t i; /* iterator variable */

    /* error and exception checking */
    if(src == NULL || dst == NULL) /* checking for bad pointer access */
    {
        return NULL;
    }

    if(dst < src && (dst + length) >= src) /* overlap of dst and src */
    {
      return NULL;
    }

    if(src < dst && (src + length) >= dst) /* overlap of src and dst */
    {
      return NULL;
    }

    /* mem copy */
    if(src != dst) /* no reason to copy if the memory location is the same */
    {
      for(i = 0; i < length; i++)
      {
          *(dst + i) = *(src + i); /* copy byte from source to destination */
      }
    }

    return dst;
}

uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value)
{
    /* variable declarations */
    size_t i; /* iterator variable */

    /* error and exception checking */
    if(src == NULL) /* checking for bad pointer access */
    {
        return NULL;
    }

    /* mem set */
    for(i = 0; i < length; i++)
    {
        *(src + i) = value; /* set value to byte */
    }

    return src;
}

uint8_t * my_memzero(uint8_t * src, size_t length)
{
    /* variable declarations */
    size_t i; /* iterator variable */

    /* error and exception checking */
    if(src == NULL) /* checking for bad pointer access */
    {
        return NULL;
    }

    /* mem set */
    for(i = 0; i < length; i++)
    {
        *(src + i) = 0; /* set byte to zero */
    }

    return src;
}

uint8_t * my_reverse(uint8_t * src, size_t length)
{
    /* variable declarations */
    size_t i; /* iterator variable */
    uint8_t temp; /* temp variable */

    /* error and exception checking */
    if(src == NULL) /* checking for bad pointer access */
    {
        return NULL;
    }

    /* mem reverse */
    for(i = 0; i < length/2; i++) /* iterate through array to reverse values */
    {
        temp = *(src + i); /* value stored as temp */
        *(src + i) = *(src + length - i - 1); /* swap values to be reversed */
        *(src + length - i - 1) = temp;
    }

    return src;
}

int32_t * reserve_words(size_t length)
{
    /* variable declarations */
    int32_t * newMem = NULL; /* pointer to assign memory to */

    /* mem reserve */
    newMem = (int32_t *) malloc(length * sizeof(void *));

    return newMem; /* returns pointer, or automatically NULL if malloc fails */
}

uint8_t free_words(uint32_t * src)
{
    free(src);
    if(src == NULL)
    {
        return 0; /* pointer memory freed */
    }
    else{
        return 1; /* pointer not freed */
    }
}
