/**
 * @file conversion.h
 * @brief An abstraction for converting integeres to ASCII.
 *
 * This header file provides an abstraction for converting
 * integers to ASCII via function calls.
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */

#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <stdint.h>

/**
 * @brief Convert data from a standard integer type into an ASCII string.
 *
 * Given a pointer to a char data set, the function will convert a integer
 * of type int32_t and any base, into ASCII characters
 *
 * @param ptr Pointer to a data item
 * @param data Data to be converted
 * @param base Variable that states the base of the data type
 *
 * @return uint8_t ASCII equivalent character.
 */
uint8_t my_itoa(int32_t data, uint8_t *ptr, uint32_t base);

/**
 * @brief Convert data from an ASCII string into a standard integer type.
 *
 * Given a pointer to a char data set, the function will convert a ASCII string
 * of type uint8_t, and any base, into a integer of type int32_t
 *
 * @param ptr Pointer to a data item
 * @param digits to be converted
 * @param base that states the base of the data type
 *
 * @return int32_t standard integer type.
 */
int32_t my_atoi(uint8_t *ptr, uint8_t digits, uint32_t base);

#endif /* __CONVERSION_H__ */
