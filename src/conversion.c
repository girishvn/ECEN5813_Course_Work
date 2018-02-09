#include "conversion.h"
#include <stddef.h> /* include NULL type */

/**
 * @file conversion.c
 * @brief Implementation of the memory.h file
 *
 * This source file holds implementations for function which convert between ASCII and integer type data
 *
 * @author Girish Narayanswamy
 * @date February 3 2018
 * @version 1.0
 *
 */

uint8_t my_itoa(int32_t data, uint8_t * ptr, uint32_t base)
{
    /* Variable declarations */
    uint8_t length = 2; /* length of ASCII characters need to represent data, min 2: 1's place and '\0' */
    uint8_t sign = 0; /* 1 or 0 value representing sign, 1 is -, 0 is + */
    uint8_t i; /* iterator variable in ASCII char assignment for loop */
    int32_t tmpData; /* used to calculate number of ASCII chars needed, and determine specific ASCII values */
    uint8_t tmpChar; /* variable to store ASCII val to store in ptr */

    /* Error and exception checking */
    if(ptr == NULL || base < 2 || base > 16) /* checking for bad pointer access and bad input base */
    {
        return 0; /* return error */
    }

    /* Determine sign */
    if(data < 0)
    {
        length++; /* additional length char for '-' */
        sign = 1; /* negative value */
        data = (-1) * data; /* data will, from here, refer to the magnitude of the input data */
    }

    /*
     * Following line accounts for exception with single digit outputs:
     * eg. data = 3 and data = 0 need 2 chars (1 digit char and 1 null terminator char).
     * However without below line, data = 3 case would enter the while loop
     * Length would be set to 3 chars instead of the needed 2 chars
     */
    tmpData = data / base; /* val used in while loop to count chars */

    /* Determine max number of needed ASCII characters */
    while(tmpData > 0) /* if more than 1 digit char needed */
    {
        tmpData = tmpData / base;
        length++; /* increase number of ASCII chars needed */
    }

    /* Placing ASCII characters in ptr memory location */
    if(sign == 1) /* add '-' character if negative number */
    {
        tmpChar = (uint8_t)('-');
        *ptr = tmpChar;
    }

    *(ptr + length - 1) = (uint8_t)('\0'); /* add string null terminator */

    tmpData = data; /* reset tmpData to data to determine specific ASCII digit values */

    for(i = (uint8_t)(length - 1); i > 0 + sign; i--) /* add digit characters */
    {

        tmpChar = (uint8_t)(tmpData % base); /* get char value 0 - F */
        tmpData = tmpData / base; /* divide by to move to next digit */

        if(tmpChar < 10) /* char between 0 and 9 */
        {
            tmpChar =  tmpChar + (uint8_t)('0');
        }
        else /* char between A and F */
        {
            tmpChar = (uint8_t)(tmpChar + (uint8_t)('A' - 10));
        }

        *(ptr + i - 1) = tmpChar; /* set character to char value */
    }

    return (uint8_t)(length - sign - 1); /* return total number of digits stored in at ptr */
}

int32_t my_atoi(uint8_t * ptr, uint8_t digits, uint32_t base)
{
    uint8_t i; /* iterator variable */
    uint8_t sign = 0; /* 1 or 0 value representing sign, 1 is -, 0 is + */
    int32_t data = 0; /* a variable to help calculate the number of ASCII characters needed */
    uint8_t tmpChar; /* temp variable that store the ASCII value of a digit*/
    int32_t multVal = 1; /* val that represents the digits magnitude. eg. 1's 10's 100's etc. */
    uint8_t length = (uint8_t)(digits + 1); /* total number of characters needed : digits + null terminator */

    /* error and exception checking */
    if(ptr == NULL || base < 2 || base > 16) /* checking for bad pointer access and bad input base */
    {
        return 0; /* return error */
    }

    /* determine sign */
    if(*ptr == (uint8_t)('-')) /* if negative character exists */
    {
        sign = 1; /* set sign to negative */
        length++; /* increment length to take into account '-' char */
    }

    /* parse through ASCII chars least sig to most sig (start one place to the left o \0) */
    for(i = (uint8_t)(length - 1); i > 0 + sign; i --)
    {
        tmpChar  = *(ptr + i - 1); /* grab ASCII val of char digit at pointer */

        if(tmpChar < (uint8_t)':') /* char between 0 and 9 */
        {
            tmpChar =  tmpChar - (uint8_t)('0'); /* mask ASCII value to integer value */
        }
        else /* char between A and F */
        {
            tmpChar = tmpChar - (uint8_t)('A' - 10); /* mask ASCII values A - F to 10 - 15 integer val */
        }

        data = data + (tmpChar * multVal); /* increment data by adding digit x  order of magnitude val */
        multVal = multVal * base; /* increase order of magnitude to next digit place */

    }

    /* sign data correctly */
    if(sign == 1) /* if negative */
    {
        data = (-1) * data; /* make value negative */
    }

    return data; /* return signed integer data */
}
