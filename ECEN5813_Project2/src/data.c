/**
 * @file data.c
 * @brief Source code for platform
 *
 * This source file provides the implementation of all functions
 * called in platform.h
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */

#if defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif

#include "data.h"
#include "platform.h"

void print_cstd_types_sizes()
{
#ifdef VERBOSE
    size_t temp;

    temp = sizeof(char);
    PRINTF("sizeof(char) = %zu\n", temp);

    temp = sizeof(short);
    PRINTF("sizeof(short) = %zu\n", temp);

    temp = sizeof(int);
    PRINTF("sizeof(int) = %zu\n",  temp);

    temp = sizeof(long);
    PRINTF("sizeof(long) = %zu\n", temp);

    temp = sizeof(double);
    PRINTF("sizeof(double) = %zu\n", temp);

    temp = sizeof(float);
    PRINTF("sizeof(float) = %zu\n", temp);

    temp = sizeof(unsigned char);
    PRINTF("sizeof(unsigned char) = %zu\n", temp);

    temp = sizeof(unsigned int);
    PRINTF("sizeof(unsigned int) = %zu\n", temp);

    temp =  sizeof(unsigned long);
    PRINTF("sizeof(unsigned long) = %zu\n", temp);

    temp = sizeof(signed char);
    PRINTF("sizeof(signed char) = %zu\n", temp);

    temp = sizeof(signed int);
    PRINTF("sizeof(signed int) = %zu\n", temp);

    temp = sizeof(signed long);
    PRINTF("sizeof(signed long) = %zu\n", temp);
#endif
    return;
}

void print_stdint_type_sizes()
{
#ifdef VERBOSE
    size_t temp;

    temp = sizeof(int8_t);
    PRINTF("sizeof(int8_t) = %zu\n", temp);

    temp = sizeof(uint8_t);
    PRINTF("sizeof(uint8_t) = %zu\n", temp);

    temp = sizeof(int16_t);
    PRINTF("sizeof(int16_t) = %zu\n", temp);

    temp = sizeof(uint16_t);
    PRINTF("sizeof(uint16_t) = %zu\n", temp);

    temp = sizeof(int32_t);
    PRINTF("sizeof(int32_t) = %zu\n", temp);

    temp = sizeof(uint32_t);
    PRINTF("sizeof(uint32_t) = %zu\n", temp);

    temp = sizeof(uint_fast8_t);
    PRINTF("sizeof(uint_fast8_t) = %zu\n", temp);

    temp = sizeof(uint_fast16_t);
    PRINTF("sizeof(uint_fast16_t) = %zu\n", temp);

    temp = sizeof(uint_fast32_t);
    PRINTF("sizeof(uint_fast32_t) = %zu\n", temp);

    temp = sizeof(uint_least8_t);
    PRINTF("sizeof(uint_least8_t) = %zu\n", temp);

    temp = sizeof(uint_least16_t);
    PRINTF("sizeof(signed int) = %zu\n", temp);

    temp = sizeof(uint_least32_t);
    PRINTF("sizeof(uint_least32_t) = %zu\n", temp);

    temp = sizeof(size_t);
    PRINTF("sizeof(size_t) = %zu\n", temp);

    temp = sizeof(ptrdiff_t);
    PRINTF("sizeof(ptrdiff_t) = %zu\n", temp);
#endif
    return;
}

void print_pointer_sizes(){
#ifdef VERBOSE
    size_t temp;

    temp = (int)sizeof(char*);
    PRINTF("sizeof(char*) = %zu\n", temp);

    temp = (int)sizeof(short*);
    PRINTF("sizeof(short*) = %zu\n", temp);

    temp = (int)sizeof(int*);
    PRINTF("sizeof(int*) = %zu\n", temp);

    temp = (int)sizeof(long*);
    PRINTF("sizeof(long*) = %zu\n", temp);

    temp = (int)sizeof(double*);
    PRINTF("sizeof(double*) = %zu\n", temp);

    temp = (int)sizeof(float*);
    PRINTF("sizeof(float*) = %zu\n", temp);

    temp = (int)sizeof(void*);
    PRINTF("sizeof(void*) = %zu\n", temp);

    temp = (int)sizeof(int8_t*);
    PRINTF("sizeof(int8_t*) = %zu\n", temp);

    temp = (int)sizeof(int16_t*);
    PRINTF("sizeof(uint_least8_t) = %zu\n", temp);

    temp = (int)sizeof(int32_t*);
    PRINTF("sizeof(signed int) = %zu\n", temp);

    temp = (int)sizeof(char**);
    PRINTF("sizeof(uint_least32_t) = %zu\n", temp);

    temp = (int)sizeof(int**);
    PRINTF("sizeof(size_t) = %zu\n", temp);

    temp = (int)sizeof(void**);
    PRINTF("sizeof(ptrdiff_t) = %zu\n", temp);
#endif
    return;
}

int32_t swap_data_endianness(uint8_t* data, size_t type_length)
{
    /*Fault Protection for Malformed Arrays*/
    if(type_length < 0){
        return SWAP_ERROR;
    }
    if(data == NULL){
        return SWAP_ERROR;
    }
    /*Begin Swapping*/
    uint8_t temp;
    uint32_t i;
    for(i = 0; i < type_length/2; i++) { /*Loop through half the array b/c each end is grabbed per iteration*/
        temp = *(data + i); /*assigning beginning index value to temp*/
        *(data + i) = *(data + (type_length - 1 - i)); /*swap beginning with ending*/
        *(data + (type_length - 1 - i)) = temp; /*swap ending with beginning*/
    }
    return SWAP_NO_ERROR;
}

uint32_t determine_endianness()
{
    uint32_t var = 0xDEADBEEF; /* 32 bit variable stored in memory */
    uint8_t* ptr = (uint8_t *) (&var); /* 8-bit pointer pointing to the beginning of the variable */

    if(*ptr == 0xDE){
        return BIG_ENDIAN;
    }
    else if(*ptr == 0xEF){
        return LITTLE_ENDIAN;
    }
    else{
        return 2;
    }
}
