/*
 * nordic.h
 *
 *  Created on: Apr 7, 2018
 *      Author: karroshuang
 */

#ifndef SOURCE_NORDIC_H_
#define SOURCE_NORDIC_H_

#include <stddef.h>
#include "GPIO.h"
#include "SPI.h"

#define NRF_CHIP_ENABLE (GPIOC->PCOR |= 1<<9) /* Set CS pin low to enable SPI transfer*/
#define NRF_CHIP_DISABLE (GPIOC->PSOR |= 1<<9) /* Set CS pin to high to end SPI transfer*/


/*Used Nordic Commands as defined in the Reference Sheet*/
#define NRF_READ_CMD (0x00)
#define NRF_WRITE_CMD (0x20)
#define NRF_FLUSH_TX_CMD (0xE1)
#define NRF_FLUSH_RX_CMD (0xE2)


/*Used Nordic Registers as defined inthe Reference Sheet*/
#define NRF_CONFIG_REG (0x00)
#define NRF_RF_CH_REG (0x05)
#define NRF_RF_SETUP_REG (0x06)
#define NRF_STATUS_REG (0x07)
#define NRF_TX_ADDR_REG (0x10)
#define NRF_FIFO_STATUS_REG (0x17)

/*Nordic Masks*/
#define NRF_POWER_UP (1)
#define NRF_POWER_DOWN (0)
#define NRF_NOP (0xFF)
#define NRF_POWER_UP_MASK (0x02)

/**
 * @brief Reads a register in the nordic chip and returns the value stored in the register
 *
 * Reads a register in the nordic chip and returns the value stored in the register
 *
 * @param uint8 variable that holds the register address
 *
 * @return uint8 variable that holds the read register's data
 */
uint8_t nrf_read_register(uint8_t reg_address);

//writes to a register in the nordic chip

/**
 * @brief Writes to a register in the nordic chip
 *
 * Writes to a register in the nordic chip
 *
 * @param uint8 variable that holds the register address
 * @param uint8 variable that holds the data to write into the register
 *
 * @return void
 */
void nrf_write_register(uint8_t reg_address, uint8_t value);

/**
 * @brief Reads the status register of the nordic chip
 *
 * Reads the status register of the nordic chip
 *
 * @param void
 *
 * @return uint8 variable that holds the status register's data
 */
uint8_t nrf_read_status();

/**
 * @brief Writes to the config register of the nordic chip
 *
 * Writes to the config register of the nordic chip
 *
 * @param uint8 variable that holds the data to write into the configuration register
 *
 * @return void
 */
void nrf_write_config(uint8_t config);

/**
 * @brief Reads the configuration register of the nordic chip
 *
 * Reads the configuration register of the nordic chip
 *
 * @param void
 *
 * @return uint8 variable that holds the configuration register's data
 */
uint8_t nrf_read_config();

/**
 * @brief Reads the rf setup register of the nordic chip
 *
 * Reads the rf setup register of the nordic chip
 *
 * @param void
 *
 * @return uint8 variable that holds the rf register's data
 */
uint8_t nrf_read_rf_setup();

/**
 * @brief Writes to the rf setup register of the nordic chip
 *
 * Writes to the rf setup register of the nordic chip
 *
 * @param uint8 variable that holds the configuration to write into the rf register
 *
 * @return void
 */
void nrf_write_rf_setup(uint8_t config);

/**
 * @brief Reads the rf CH register of the nordic chip
 *
 * Reads the rf CH register of the nordic chip
 *
 * @param void
 *
 * @return uint8 variable that holds the rf_ch register's data
 */
uint8_t nrf_read_rf_ch();

/**
 * @brief Writes to the rf CH register of the nordic chip
 *
 * Writes to the rf CH register of the nordic chip
 *
 * @param uint8 variable that holds the channel to write into the rf ch register
 *
 * @return void
 */
void nrf_write_rf_ch(uint8_t channel);

/**
 * @brief Reads the 5 bytes of the TX Address register
 *
 * Reads the 5 bytes of the TX Address register
 *
 * @param uint8 variable that holds the address of the data that's going to be stored
 *
 * @return void
 */
void nrf_read_TX_ADDR(uint8_t * address);

/**
 * @brief Writes the 5 bytes of the TX Address register
 *
 * Writes the 5 bytes of the TX Address register
 *
 * @param uint8 variable that holds the pointer to the data to write into the TX_ADDR register
 *
 * @return void
 */
void nrf_write_TX_ADDR(uint8_t * tx_addr);

/**
 * @brief Reads the fifo status register of the nordic chip
 *
 * Reads the fifo status register of the nordic chip
 *
 * @param void
 *
 * @return void
 */
uint8_t nrf_read_fifo_status();

//sends the command flush TX to the nordic chip
/**
 * @brief Sends the command flush TX to the nordic chip
 *
 * Sends the command flush TX to the nordic chip
 *
 * @param void
 *
 * @return void
 */
void nrf_flush_tx_fifo();

/**
 * @Sends the command flush RX to the nordic chip
 *
 * Sends the command flush RX to the nordic chip
 *
 * @param void
 *
 * @return void
 */
void nrf_flush_rx_fifo();

/**
 * @brief shows functionality of all nrf functions
 *
 * @param void
 *
 * @return 0 if succesful, -1 if error
 */
uint8_t nrf_SPI_test(void);


#endif /* SOURCE_NORDIC_H_ */

