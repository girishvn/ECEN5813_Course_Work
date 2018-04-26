/**
 * @file GPIO.h
 * @brief An abstraction for GPIO interface on the KL25Z
 *
 * Creating a GPIO interface in order to have a method of toggling GPIO pins to a development board
 *
 * @author Girish Narayanswamy
 * @date March 3, 2018
 * @version 1.0
 *
 */

#include "MKL25Z4.h"

#ifndef SOURCE_GPIO_H_
#define SOURCE_GPIO_H_

#define RGB_RED_PIN			18
#define RGB_GREEN_PIN     	19
#define RGB_BLUE_PIN      	01

#define RGB_RED_ON()		(PORTB_Clear( RGB_RED_PIN ))
#define RGB_RED_OFF()		(PORTB_Set( RGB_RED_PIN ))
#define RGB_RED_TOGGLE()	(PORTB_Toggle( RGB_RED_PIN ))
#define RGB_GREEN_ON()		(PORTB_Clear( RGB_GREEN_PIN ))
#define RGB_GREEN_OFF()		(PORTB_Set( RGB_GREEN_PIN ))
#define RGB_GREEN_TOGGLE()	(PORTB_Toggle( RGB_GREEN_PIN ))
#define RGB_BLUE_ON()		(PORTD_Clear( RGB_BLUE_PIN ))
#define RGB_BLUE_OFF()		(PORTD_Set( RGB_BLUE_PIN ))
#define RGB_BLUE_TOGGLE()	(PORTD_Toggle( RGB_BLUE_PIN ))


/*
 * @brief Configures GPIO pins
 *
 * Sets PORT B pin 18 & 19, and PORT D pin 1 to output direction and digital low. Enables Sys clock and sets the respective pins into GPIO mode.
 *
 * @param none
 *
 * @return VOID
 */
void GPIO_Configure();

/*
 * @brief Toggle red LED
 *
 * Turns red LED on or off whenever it's called
 *
 * @param none
 *
 * @return VOID
 */
void Toggle_Red_LED();

/*
 * @brief Sets port B pin X Data output bit to 1
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTB_Set(uint8_t bit_num);

/*
 * @brief Sets port D pin X Data output bit to 1
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTD_Set(uint8_t bit_num);

/*
 * @brief Sets port B pin X Data output bit to 0
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTB_Clear(uint8_t bit_num);

/*
 * @brief Sets port B pin X Data output bit to 0
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTD_Clear(uint8_t bit_num);

/*
 * @brief Flips port B pin X Data output bit
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTB_Toggle(uint8_t bit_num);

/*
 * @brief Flips port D pin X Data output bit
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void PORTD_Toggle(uint8_t bit_num);

/*
 * @brief Flips port D pin X Data output bit
 *
 * @param bit_num corresponding register bit for pin location
 *
 * @return VOID
 */
void GPIO_nrf_init();

#endif /* SOURCE_GPIO_H_ */
