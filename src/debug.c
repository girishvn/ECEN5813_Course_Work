/**
 * @file debug.c
 * @brief Source code for debug
 *
 * This source file provides the implementation of all functions
 * called in debug.h
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */

#include "debug.h"
#include "platform.h"

void print_array(uint8_t* start, uint32_t length){
#ifdef VERBOSE
    uint32_t i;
   // uint8_t key;
    for(i = 0; i < length; i++){
        //key = *start;
        PRINTF("%x", (*start));
        start++;
    }
#endif
    return;
}
