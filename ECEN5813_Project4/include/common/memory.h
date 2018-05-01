/**
 * @file memory.h
 * @brief An abstraction for memory sets, allocations, and frees
 *
 * This header file provides an abstraction of memory sets, allocations, and frees via function calls
 *
 * @author Girish Narayanswamy
 * @date April 1, 2018
 * @version 2.0
 *
 */

#ifndef SOURCE_MEMORY_H_
#define SOURCE_MEMORY_H_

#include <stdint.h>  /* include standard data types */
#include <stddef.h> /* include size_t and NULL type */

/**
 * @brief Moves a piece of memory from one place to another
 *
 * Given a pointer to a memory location and a length, this will move a piece of memory, of given length, from the given
 * source to the given destination
 *
 * @param src pointer to the source to move data from
 * @param dst pointer to the destination to move data to
 * @param length number of bytes to move from the source to the destination
 *
 * @return pointer to the destination that data was moved to
 */
uint8_t * my_memmove(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Copies a piece of memory from one place to another
 *
 * Given a pointer to a memory location and a length, this will cpoy a piece of memory, of given length, from the given
 * source to the given destination
 *
 * @param src pointer to the source to copy data from
 * @param dst pointer to the destination to copy data to
 * @param length number of bytes to copy from the source to the destination
 *
 * @return pointer to the destination that data was copied to
 */
uint8_t * my_memcpy(uint8_t * src, uint8_t * dst, size_t length);

/**
 * @brief Sets all values at a memory location
 *
 * Given a pointer to a memory location and a length, this will set all memory locations to the given value for the
 * given number of bytes
 *
 * @param src pointer to the source to set values to
 * @param length number of bytes to set a value to
 * @param value the value to set all byte sized memory locations to
 *
 * @return pointer to the source where values were set
 */
uint8_t * my_memset(uint8_t * src, size_t length, uint8_t value);

/**
 * @brief Sets all values at a memory location to zero using DMA
 *
 * Given a pointer to a memory location and a length, this will set all memory locations to zero for the
 * given number of bytes. Memory is set via DMA to free up processor time (ideal for large mem sets)
 *
 * @param src pointer to the source to set to zero
 * @param length number of bytes to set to zero
 * @param size value of 0, 1, 2 that defines the byte transfer size, see header for size defs
 *
 * @return pointer to the source where values were set
 */
uint8_t * my_memzero(uint8_t * src, size_t length);

/**
 * @brief Reverse the order of all bytes at a memory location
 *
 * Given a pointer to a memory location and a length, this will set all memory locations to zero for the
 * given number of bytes
 *
 * @param src pointer to the source to reverse from
 * @param length number of bytes to set to reverse
 *
 * @return pointer to the source where the reverse began
 */
uint8_t * my_reverse(uint8_t * src, size_t length);

/**
 * @brief Allocates memory for a given number of words
 *
 * Given a length, this will dynamically allocate memory for that many words
 *
 * @param length number of words to allocate in dynamic memory
 *
 * @return pointer to the start of the allocated memory if successful, or Null pointer if unsuccessful
 */
int32_t * reserve_words(size_t length);

/**
 * @brief Frees memory given a pointer
 *
 * Given a pointer to a dynamically allocated piece of memory, this will free that memory
 *
 * @param src pointer to the dynamically allocated memory to free
 *
 * @return 0 if free was successful, 1 is free was not successful
 */
uint8_t free_words(uint32_t * src);

#endif /* SOURCE_MEMORY_H_ */
