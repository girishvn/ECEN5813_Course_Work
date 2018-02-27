/**
 * @file arch_arm32.c
 * @brief Source code for arch_arm32
 *
 * This source file provides the implementation of all functions
 * called in arch_arm32.h
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */
#include "arch_arm32.h"

__attribute__((always_inline)) inline uint32_t ARM32_AIRCR_get_endianness_setting()
{
    return ((__AIRCR & __AIRCR_ENDIANNESS_MASK) >> __AIRCR_ENDIANNESS_OFFSET);
}
