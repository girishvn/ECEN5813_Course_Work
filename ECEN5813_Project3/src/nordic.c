/*
 * nordic.c
 *
 *  Created on: Apr 7, 2018
 *      Author: karroshuang
 */
#include "nordic.h"


uint8_t nrf_read_register(uint8_t reg_address){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t data = 0;
	reg_address &= 0x1F; /*Mask out lower 5 bits of register address parameter*/
	cmd = NRF_READ_CMD | reg_address; /*Set Read Cmd Byte to be sent to NRF*/

	/*Begin Reading the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send read register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
	data = SPI_read_byte();  /* Returns data of the specified register */
	data = SPI_read_byte();
	NRF_CHIP_DISABLE;

	return data;
}

void nrf_write_register(uint8_t reg_address, uint8_t value){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t garbage = 0;
	reg_address &= 0x1F; /*Mask out lower 5 bits of register address parameter*/
	cmd = NRF_WRITE_CMD | reg_address; /*Set Write Cmd Byte to be sent to NRF*/

	/*Begin Writing the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(value); /* Write data to the specified register */
	garbage = SPI_read_byte(); /* Shift out garbage data out of SPI data buffer after a value has been written to register */

	NRF_CHIP_DISABLE;
}

uint8_t nrf_read_status(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t status = 0;

	/*Begin Reading the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */

	NRF_CHIP_DISABLE;

	return status;
}

void nrf_write_config(uint8_t config){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t garbage =0;
	byte = NRF_WRITE_CMD | NRF_CONFIG_REG;

	/*Begin Writing the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(config); /*Write the configuration data into the configuration register*/
	garbage = SPI_read_byte(); /* Shift out garbage data out of SPI data buffer after a value has been written to register */

	NRF_CHIP_DISABLE;

}

uint8_t nrf_read_config(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t data = 0;
	cmd = NRF_READ_CMD | NRF_CONFIG_REG;

	/*Begin Reading the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the config register */
	data = SPI_read_byte();  /* Return data of the configuration register*/
	NRF_CHIP_DISABLE;

	return data;
}

uint8_t nrf_read_rf_setup(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t data = 0;
	cmd = NRF_READ_CMD | NRF_RF_SETUP_REG;

	/*Begin Reading the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
	data = SPI_read_byte();  /* Return data of the configuration register */
	data = SPI_read_byte();  /* Return data of the configuration register */

	NRF_CHIP_DISABLE;

	return data;
}

void nrf_write_rf_setup(uint8_t config){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t garbage = 0;
	cmd = NRF_WRITE_CMD | NRF_RF_SETUP_REG;

	/*Begin Writing the NRF rf_setup Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send read register command to NRF*/
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(config); /*Write the configuration data into the rf_setup register*/
	garbage = SPI_read_byte(); /* Shift out garbage data out of SPI data buffer after a value has been written to rf_setup register */

	NRF_CHIP_DISABLE;
}

uint8_t nrf_read_rf_ch(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t data = 0;
	SPI0->S &= ~(0x80);
	cmd = NRF_READ_CMD | NRF_RF_CH_REG;

	/*Begin reading the NRF rf_ch Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
	data = SPI_read_byte();  /* Return data of the rf_ch register */
	data = SPI_read_byte();  /* Return data of the rf_ch register */

	NRF_CHIP_DISABLE;

	return data;
}

void nrf_write_rf_ch(uint8_t channel){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t garbage = 0;
	cmd = NRF_WRITE_CMD | NRF_RF_CH_REG;

	/*Begin Writing the NRF rf_ch Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte(); /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(channel); /* Write channel to the rf_ch register */
	garbage = SPI_read_byte(); /* Shift out garbage data out of SPI data buffer after a value has been written to rf_ch register */

	NRF_CHIP_DISABLE;
}

void nrf_read_TX_ADDR(uint8_t * address){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t read_array[5] = {0};
	uint8_t cmd = 0;
	uint8_t status = 0;
	cmd = NRF_READ_CMD | NRF_TX_ADDR_REG;

	/*Begin Reading the NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	/*Iterate and read through all 5 bytes of the tx register*/
	for (int i=0; i<5; i++)
	{
		SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
		*(address+i) = SPI_read_byte();  /* Read a single byte of the tx_address register and store it in the address array*/
		*(address+i) = SPI_read_byte();  /* Read a single byte of the tx_address register and store it in the address array*/
		read_array[i] = *(address+i);
	}

	NRF_CHIP_DISABLE;
}

void nrf_write_TX_ADDR(uint8_t * tx_addr){
	/*Initializing and Setting up Parameters to Read TX_ADDR Register*/
	uint8_t cmd = 0;
	uint8_t status = 0;
	uint8_t garbage = 0;
	cmd = NRF_WRITE_CMD | NRF_TX_ADDR_REG;

	/*Begin Writing the TX_ADDR NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	/*Iterate and read through all 5 bytes of the tx register*/
	for (int i=0; i<5; i++)
	{
		SPI_write_byte(*(tx_addr+i));  /* Writes a single byte to the tx_addr register */
		garbage = SPI_read_byte();  /* Read garbage data out of SPI data buffer after a value has been written to NRF tx_addr register*/
	}

	NRF_CHIP_DISABLE;
}

uint8_t nrf_read_fifo_status(){
	/*Initializing and Setting up Parameters to Read fifo status Register*/
	uint8_t cmd =0;
	uint8_t status = 0;
	uint8_t data = 0;
	cmd = NRF_READ_CMD | NRF_FIFO_STATUS_REG;

	/*Begin Writing the FIFO_STATUS NRF Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(cmd); /*Send write register command to NRF*/
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */
	SPI_write_byte(NRF_NOP);  /* Write NOP in order to shift out data in the specified register */
	data = SPI_read_byte();  /* Returns the data of the fifo status register */
	data = SPI_read_byte();  /* Returns the data of the fifo status register */

	NRF_CHIP_DISABLE;

	return data;

}

void nrf_flush_tx_fifo(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t status = 0;

	/*Begin flushing the tx Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(NRF_FLUSH_TX_CMD);
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */

	NRF_CHIP_DISABLE;
}

void nrf_flush_rx_fifo(){
	/*Initializing and Setting up Parameters to Read NRF Register*/
	uint8_t status =0;

	/*Begin Flushing the rx_fifo Register*/
	NRF_CHIP_ENABLE;

	SPI_write_byte(NRF_FLUSH_RX_CMD);
	status = SPI_read_byte();  /* Status register bytes are shifted out when a command is transmitted */

	NRF_CHIP_DISABLE;
}
