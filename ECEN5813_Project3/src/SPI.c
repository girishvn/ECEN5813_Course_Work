/*
 * SPI.c
 *
 *  Created on: Apr 7, 2018
 *      Author: karroshuang
 */
#include "SPI.h"

void SPI_init(){
	/*Configure GPIO for SPI0 Settings*/
	GPIO_nrf_init();
	/*Configure SPI Settings*/
	SIM->SCGC4 |= SIM_SCGC4_SPI0_MASK;
	SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK; /*Set clock source to be from PLL*/
	SPI0->C1 |= SPI_C1_SPE(1); /*SPI system enabled*/
	SPI0->C1 |= SPI_C1_MSTR(1);/*SPI module configured as a master SPI device*/
//	SPI0->C1 &= ~SPI_C1_CPHA(1);
	SPI0->C2 |= SPI_C2_MODFEN(1); //sets bit 4, MODFEN =1 SS acts as a slave select output

	/*Set SPICLK to 6Mhz*/
	SPI0->BR |= SPI_BR_SPR(0x01); /*Set SPI BAUD Rate divisor to 4*/

}
uint8_t SPI_read_byte(){
	uint8_t Data = 0;
	while (!(SPI0->S && 0x80)); /*Wait until SPI Data Register to be filled*/
	Data = SPI0->D; /*Assign Data Variable to SPI Data register */
	return Data;
}
void SPI_write_byte(uint8_t byte){
	SPI_flush(); /*Wait for SPI Data Register to be Empty*/
	SPI0->D = byte; /*Assign SPI Data register to Data Variable */
	for(int i = 0; i < 300; i ++); /*WHYYYYYYY?????*/
}
void SPI_send_packet(uint8_t* p, size_t length){
	size_t i;
	for (i = 0; i<length; i++){ /*Loop through each byte of the packet*/
		SPI_flush(); /*Wait for SPI Data Register to be Empty*/
		SPI0->D = *(p+i); /*Assign SPI Data register to byte*/
	}
	for(int i = 0; i < 300; i ++); /*WHYYYYYYY?????*/
}
__attribute__((always_inline)) inline void SPI_flush(){
	while (!(SPI0->S && 0x20)); /*Wait for SPI Data Register to be Empty*/
}
