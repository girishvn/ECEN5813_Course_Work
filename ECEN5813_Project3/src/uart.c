/**
 * @file uart.c
 * @brief Defines UART operation and provides functions for UART operation and initialization
 *
 * @author Karros Huang & Girish Narayanswamy
 * @date March 3 2018
 * @version 1.0
 *
 */

#include "uart.h"
#include "MKL25Z4.h"
#include "circbuf.h"

void UART_configure()
{
	NVIC_EnableIRQ(UART0_IRQn); /*enable UART0 interrupts*/ //GIRISH WHYYY????
	UART0->C2 &= ~(0xB<<2); /*Disable Transmitter and Receiver & Receiver Interrupt*/

	/*Set UART0 RX & TX to PTA1 & PTA2 Respectively*/
	PORTA->PCR[1] |= PORT_PCR_MUX(0x02); /*Set UART0_RX to PTA1*/
	PORTA->PCR[2] |= PORT_PCR_MUX(0x02); /*Set UART0_TX to PTA2*/

	/*Control Register Configurations*/
	UART0->C1 |= 0x00; /*Sets UART0 to 8 bit no parity.*/
	UART0->C3 |= 0x00; /*Ensuring all configurations are default*/
	UART0->S2 |= 0x00; /*More default standard UART Configs*/

	/*Baud Configuration*/
	uint16_t SBR;  /* Variable used to set the SBR field for Baud Config. */
	uint16_t OSR = 8; /* Set oversampling ratio to 8 */
	SBR = BUSCLK/((OSR+1)*BAUD); /* sets 13 bit SBR value based on desired baud rate and system clock frequency */
	SIM->SOPT2 |= (0x01<<26); /*Set to MCGFLLCLK Clock */
	SIM->SCGC4 |= (0x01<<10); /*Enable UART0 CLock Gate*/
	SIM->SCGC5 |= (0x01<<9);
	UART0->BDH = (UART0_BDH_SBR_MASK) & (SBR>>8); /* Mask out upper 5 SBR bits */
	UART0->BDL = (UART0_BDL_SBR_MASK) & (SBR & 0xFF); /* Mask out lower 8 SBR bits */
	UART0->C4 &= (~UART0_C4_OSR_MASK) | OSR; /*Set Over Sampling Ratio Register to 8 */
	UART0->C2 |= (0xB<<2); /*Enable Transmitter and Receiver & Receiver Interrupt*/
}

void UART_send(uint8_t* tx_data)
{
	while(!(UART0->S1 & UART_S1_TDRE_MASK)); /*Wait to push data onto buffer until the buffer is cleared*/
	UART0->D = *tx_data; /*Send the data into the data buffer*/
}

void UART_send_n(uint8_t* tx_block_data, uint32_t length)
{
	uint32_t i;
	for(i = 0;  i < length; i++)
	{
		UART_send(tx_block_data); /*Send a byte of data into the buffer*/
		tx_block_data++; /*Increment the pointer to send the next byte */
	}
	tx_block_data -= length; /*Reset the pointer back to the start of the string */
}

uint8_t UART_receive(uint8_t* rx_data)
{
	while(!(UART0->S1 & UART_S1_RDRF_MASK)); /*Wait in this loop until UART buffer is full*/
	*rx_data = UART0->D; /*Transfer data in UART buffer into a local variable*/
	return *rx_data; /*Return the data*/
}

uint8_t* UART_receive_n(uint8_t* rx_block_data, uint32_t length)
{
	uint32_t i;
	for(i = 0; i < length; i++)
	{
		UART_receive(rx_block_data); /*Receive a byte of data from the buffer*/
		rx_block_data++; /*Increment the pointer to store the next byte*/
	}
	rx_block_data -= length;/*Reset the pointer back to the start of the string*/
	return rx_block_data; /*Return the pointer*/
}

void UART0_IRQHandler()
{
	if(UART0->S1 & UART_S1_RDRF_MASK)
	{
		CB_buffer_add_item(CB,UART0->D); /*Store UART Buffer Data into buffer */
	}
	PORTA->ISFR = 0xFFFF; /*Clear the interrupt Flag*/
}
