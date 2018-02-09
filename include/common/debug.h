/**
 * @file debug.h
 * @brief An abstraction for debugging code.
 *
 * This header file provides an abstraction for debugging code
 * and data by calling functions.
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */
#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdint.h>

/**
 * @brief Prints the output of an array
 *
 * Takes a pointer to memory and prints the hex
 * output of bytes given a pointer to a memory location and a
 * length of bytes to print.
 *
 * @param start Pointer to start of the array
 * @param length Length of the array
 *
 * @return void
 */
        void print_array(uint8_t *start, uint32_t length);

#endif /* __DEBUG_H__ */



