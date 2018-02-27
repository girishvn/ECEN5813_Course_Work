/**
 * @file arch_arm32.h
 * @brief An abstraction that contain ARM architecture specific functionality
 *
 * This header defines an ARM Core CPU access macro to read system endianness from the AIRCR register
 *
 * @author Karros Huang & Girish Narayanswamy
 * @date Feb. 26, 2018
 * @version 2.0
 *
 */

#ifndef __ARCH_ARM32_H__
#define __ARCH_ARM32_H__

#include <stdint.h>

#define __SCB_ADDRESS (uint32_t *) 0xE000ED00

#define __AIRCR_ADDRESS_OFFSET 0x0C
#define __AIRCR *(__SCB_ADDRESS + __AIRCR_ADDRESS_OFFSET)
#define __AIRCR_ENDIANNESS_OFFSET 0x0F
#define __AIRCR_ENDIANNESS_MASK 0x00008000

#define __CPUID_ADDRESS_OFFSET 0x00
#define __CPUID *(__SCB_ADDRESS + __CPUID_ADDRESS_OFFSET)
#define __CPUID_PART_NO_OFFSET 0x04
#define __CPUID_PART_NO_MASK 0x0000FFF0

#define __CCR_ADDRESS_OFFSET 0x0E
#define __CCR *(__SCB_ADDRESS + __CCR_ADDRESS_OFFSET)
#define __CCR_STK_ALIGNMENT_OFFSET 0x09
#define __CCR_STK_ALIGNMENT_MASK 0x00000200
#define __CCR_UNALIGNED_ACCESS_TRAP_OFFSET 0x03
#define __CCR_UNALIGNED_ACCESS_TRAP_MASK 0x00000008
#define __CCR_DIVIDE_BY_ZERO_TRAP_OFFSET 0x04
#define __CCR_DIVIDE_BY_ZERO_TRAP_MASK 0x00000010

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
uint32_t ARM32_AIRCR_get_endianness_setting(void);

/**
 * @brief Reads and returns the current stack alignment value
 *
 * Accesses the ARM Configuration and Control Register (CCR), reads the stack alignment value
 * and returns that value
 *
 * @return 0 for 4-byte alignment or 1 for 8-byte alignment
 */
uint32_t ARM32_CCR_get_stack_alignment(void);

/**
 * @brief Reads and returns the arm processor part number
 *
 * Accesses the ARM CPUID register, reads the part number value
 * and returns that value
 *
 * Not applicable for the arm cortex M0
 *
 * @return the 12 bit part number
 */
uint32_t ARM32_CPUID_get_part_number(void);

/**
 * @brief Sets up a divide by 0 trap
 *
 * Accesses the ARM Configuration and Control Register (CCR), and writes a 1 to the DIV_0_TRAP bit location
 *
 * @return 0 else -1 for error
 */
uint32_t ARM32_CCR_enable_divide_by_zero_trap(void);

/**
 * @brief Sets up a unaligned memory trap
 *
 * Accesses the ARM Configuration and Control Register (CCR), and writes a 1 to the UNALIGN_TRP bit location
 *
 * @return 0 else -1 for error
 */
uint32_t ARM32_CCR_enable_unaligned_access_trap(void);

/**
 * @brief Performs an unaligned access
 *
 * Performs an unaligned memory access in order to trigger a trap on the MCU.
 * It does not return a UsageFault Exception and triggers automatically on the exception
 *
 * @return 0 else -1 for error
 */
void ARM32_create_unaligned_access_trap(void);

/**
 * @brief Performs a divide by zero
 *
 * Performs an divide by zero in order to trigger a trap on the MCU.
 * It does not return a UsageFault Exception and triggers automatically on the exception
 *
 * @return 0 else -1 for error
 */
void ARM32_create_divide_by_zero_trap(void);

#endif //__ARCH_ARM32_H__

