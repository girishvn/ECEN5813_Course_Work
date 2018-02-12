/**
 * @file arch_arm32.h
 * @brief An abstraction that contain ARM architecture specific functionality
 *
 * This header defines an ARM Core CPU access macro to read system endianness from the AIRCR register
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */

#ifndef ECEN5813PROJ2_ARCH_ARM32_H
#define ECEN5813PROJ2_ARCH_ARM32_H

#include <stdint.h>

#define __SCB_ADDRESS (uint32_t *) 0xE000ED00
#define __AIRCR_ADDRESS_OFFSET 0x0C
#define __AIRCR *(__SCB_ADDRESS + __AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET 15
#define __AIRCR_ENDIANNESS_MASK 0x00008000

/**
 * @brief Converts the current configured endianness from big to little or little to big
 *
 * Takes a pointer to memory and iterates byte by byte through half the specified length, swapping each
 * byte with it's corresponding opposite position
 *
 * @param data Pointer to start of the memory location
 * @param type_length Size of the memory that stores the variable in bytes
 *
 * @return 0 for for no swap error, -1 for swap error
 */
        uint32_t ARM32_AIRCR_get_endianness_setting();


#endif //ECEN5813PROJ2_ARCH_ARM32_H

