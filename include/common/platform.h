/**
 * @file platform.h
 * @brief An abstraction that chooses between which platform specific lower level functions to use
 *
 * This header file creates an independent layer to switch between
 * which platform specific lower level functions to use, as well as print useful architecture sizes.
 *
 * @author Karros Huang
 * @date Feb. 1, 2018
 * @version 1.0
 *
 */
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdint.h> /* include standard int types */
#include <stddef.h> /* include NULL and size_t */

#define LITTLE_ENDIAN (0)
#define BIG_ENDIAN (1)
#define SWAP_NO_ERROR (0)
#define SWAP_ERROR (-1)

//#define PRINTF printf /* IS THIS RIGHT??? */
#define PRINTF(...)

/**
 * @brief Reports the size of all C-standard types
 *
 * Stores the size of some C-standard type definition in a temporary variable of size_t
 * and prints the size in bytes.

 * @return void
 */
        void print_cstd_types_sizes();

/**
 * @brief Reports the size of all standard integer types
 *
 * Stores the size of some standard integer type definition in a temporary variable of size_t
 * and prints the size in bytes.

 * @return void
 */
        void print_stdint_type_sizes();

/**
 * @brief Reports the size of all pointer types
 *
 * Stores the size of some pointer type definition in a temporary variable of size_t
 * and prints the size in bytes.

 * @return void
 */
        void print_pointer_sizes();

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
        int32_t swap_data_endianness(uint8_t* data, size_t type_length);

/**
 * @brief Reports the current endianness configuration of the program
 *
 * Creates a 32 bit hexadecimal value 0xDEADBEEF, and assigns a pointer to the first byte of the variable.
 * If the variable prints 0xEF it is little endian, or if it prints 0xDE it is big endian
 *

 * @return 0 for little endian, 1 for big endian
 */
        uint32_t determine_endianness();
#endif /* __PLATFORM_H__ */



