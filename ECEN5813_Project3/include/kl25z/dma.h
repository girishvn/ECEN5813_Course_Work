/**
 * @file dma.h
 * @brief An abstraction for dma memory sets, and moves
 *
 * This header file provides an abstraction of memory sets, and moves via function calls
 *
 * @author Girish Narayanswamy
 * @date April 1, 2018
 * @version 1.0
 *
 */

#ifndef SOURCE_DMA_H_
#define SOURCE_DMA_H_

#include <stdint.h>  /* include standard data types */
#include <stddef.h> /* include size_t and NULL type */

/* defines for DMA transfer size */
#define DMASIZE32 0x00
#define DMASIZE16 0x02
#define DMASIZE8 0x01
#define DMAMAXBYTENUM 0x0FFFFF

#define INCREMENT 0x01
#define NONINCREMENT 0x00

/* times for systick profilings */
//uint32_t dmaStart = 0; /* test values, unsused */
//uint32_t dmaEnd = 0;

uint8_t dmaTransfer = 0x00; /* global val to show if transfer is done*/

/**
 * @brief Initializes DMA peripheral module
 *
 * Given a pointer to a source and destination memory location, a length, a transfer size, and a increment value (T/F)
 * , this will configure the DMA for a memory tranfer
 *
 * @param src pointer to the source to move data from
 * @param dst pointer to the destination to move data to
 * @param length number of bytes to move from the source to the destination
 * @param size (1, 2, 4 bytes) of transfer partions
 * @param srcInc a boolean that specifies whether the source should increment after each block transfer
 *
 * @return pointer to the destination that data was moved to
 */
uint8_t dmaInit(uint8_t * src, uint8_t * dst, size_t length, uint8_t size, uint8_t srcInc);

/**
 * @brief Moves a piece of memory from one place to another using DMA
 *
 * Given a pointer to a memory location and a length, this will move a piece of memory, of given length, from the given
 * source to the given destination. Memory is moved via DMA to free up processor time (ideal for large mem transfers)
 *
 * @param src pointer to the source to move data from
 * @param dst pointer to the destination to move data to
 * @param length number of bytes to move from the source to the destination
 * @param size (1, 2, 4 bytes) of transfer partions
 *
 * @return pointer to the destination that data was moved to
 */
uint8_t * memmove_dma(uint8_t * src, uint8_t * dst, size_t length, uint8_t size);

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
uint8_t * memset_dma(uint8_t * mem, size_t length, uint8_t value);

#endif /* SOURCE_DMA_H_ */
