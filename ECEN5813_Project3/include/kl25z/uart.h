/*
* @file uart.h
* @brief Creating a UART interface in order to have a method of transmitting and receiving data to development board
* @author Karros Huang & Girish Narayanswamy
* @date 3/3/2017
*/

#include "circbuf.h"


#ifndef SOURCE_UART_H_
#define SOURCE_UART_H_

#define BUSCLK 48000000 // BUS_CLK
#define BAUD 38400 // define UART baud rate here

CB_d CB; /* create global instance of circular buffer */
uint32_t demo_Array_len = 0;
uint8_t* demoPointer;
uint8_t demoArray[1000];
uint8_t demoTransferFlag = 0;

/*
 * @brief Configures UART
 * Enables and sets up UART0 to communicate through the USB
 * @param none
 *
 * @return VOID
 */
void UART_configure();

/*
 * @brief Sends a single byte through UART0 TX device
 * Checks to make sure the TX Buffer is empty, and if it is, it sends a single byte through UART0 TX device
 * @param tx_data pointer to an 8bit data to be sent
 *
 * @return VOID
 */
void UART_send(uint8_t* tx_data);

/*
 * @brief Sends multiple bytes through UART0 TX device
 * Takes an 8bit pointer to a string of bytes, checks to make sure the TX Buffer is empty, and if it is, it sends a single byte that the pointer is currently pointing at through UART0 TX device. Then the pointer increments and sends the next bytes. Process repeats for the length of the string
 * @param tx_block_data pointer to the beginning of an 8bit string to be sent
 *
 * @return VOID
 */
void UART_send_n(uint8_t* tx_block_data, uint32_t length);

/*
 * @brief Receives a single byte of data, should block until character is received
 * Waits for the RX Buffer to be completely populated, and then it transfers it into a local variable
 * @param rx_data pointer to a variable to hold the received data
 *
 * @return byte of data that was sent
 */
uint8_t UART_receive(uint8_t* rx_data);

/*
 * @brief Receives a number of bytes on the UART
 *
 * @param rx_block_data pointer to memory location to place data that is being received
 * @param length number of items to receive
 *
 * @return the pointer to the received array of bytes
 */
uint8_t* UART_receive_n(uint8_t* rx_block_data, uint32_t length);

/*
 * @brief Handles receive and Transmit interrupts and clears their associated flag when completed but only if they were set
 *
 * @param none
 *
 * @return VOID
 */
//void UART0_IRQHandler();


void demo_AddItem(uint8_t Data);

#endif /* SOURCE_UART_H_ */
