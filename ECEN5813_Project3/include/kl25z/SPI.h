/*
 * SPI.h
 *
 *  Created on: Apr 7, 2018
 *      Author: karroshuang
 */

#ifndef SOURCE_SPI_H_
#define SOURCE_SPI_H_

#include "GPIO.h"
#include <stddef.h>

/**
 * @brief Initialize SPI port for communication w/ Nordic chip
 *
 * Initialize SPI port for communication w/ Nordic chip
 *
 * @param void
 *
 * @return void
 */
void SPI_init();

/**
 * @brief Read a single byte over the SPI interface
 *
 * Read a single byte over the SPI interface
 *
 * @param void
 *
 * @return uint8_t variable that holds the data read from the SPI buffer
 */
uint8_t SPI_read_byte();

/**
 * @brief Write a single byte over the SPI interface
 *
 * Write a single byte over the SPI interface
 *
 * @param uint8_t variable that holds the data to write into the SPI buffer
 *
 * @return void
 */
void SPI_write_byte(uint8_t byte);

/**
 * @brief Send a packet of bytes over the SPI interface
 *
 * Send a packet of bytes over the SPI interface
 *
 * @param pointer variable that points to the start of the address that holds the data to write into the SPI buffer
 * @param uint8_t variable that holds the length of the packet to write into the SPI buffer
 *
 * @return void
 */
void SPI_send_packet(uint8_t* p, size_t length);

/**
 * @brief Blocks until SPI transmit buffer has completed transmitting
 *
 * Blocks until SPI transmit buffer has completed transmitting
 *
 * @param void
 *
 * @return void
 */
__attribute__((always_inline)) inline void SPI_flush();


#endif /* SOURCE_SPI_H_ */
