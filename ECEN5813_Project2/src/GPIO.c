#include "GPIO.h"

void GPIO_Configure(){

	/*Enable System Clock for PORT B&D*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB(1);
	SIM->SCGC5 |= SIM_SCGC5_PORTD(1);

	/* Set PCR MUX to GPIO Mode */
	PORTB->PCR[18] = PORT_PCR_MUX(1);
	PORTB->PCR[19] = PORT_PCR_MUX(1);
	PORTD->PCR[1] = PORT_PCR_MUX(1);


	/*Data Direction for LED's set out*/
	GPIOB->PDDR |= (0x03<<18); /*Setting Red and Green LED Direction to Out*/
	GPIOD->PDDR |= (0x01<<1); /*Setting Blue LED Direction to Out*/

	/*Data output for LED's set low*/
	GPIOB->PDOR |= 0x03<<18;	/*Set Output of RED and Green LED Low*/
	GPIOD->PDOR |= 0x01<<1; /*Set Output of Blue LED Low*/
}

void Toggle_Red_LED(){
	GPIOB->PDOR ^= (0x01<<18); /*Flipping the RED LED Output bit to toggle between 0 & 1 */
}

__attribute__((always_inline)) inline void PORTB_Set(uint8_t bit_num){
	GPIOB->PSOR |= (0x01<<bit_num);
}

__attribute__((always_inline)) inline void PORTD_Set(uint8_t bit_num){
	GPIOD->PSOR |= (0x01<<bit_num);
}

__attribute__((always_inline)) inline void PORTB_Clear(uint8_t bit_num){
	GPIOB->PCOR |= (0x01<<bit_num);
}

__attribute__((always_inline)) inline void PORTD_Clear(uint8_t bit_num){
	GPIOD->PCOR |= (0x01<<bit_num);
}

__attribute__((always_inline)) inline void PORTB_Toggle(uint8_t bit_num){
	GPIOB->PTOR |= (0x01<<bit_num);
}

__attribute__((always_inline)) inline void PORTD_Toggle(uint8_t bit_num){
	GPIOD->PTOR |= (0x01<<bit_num);
}
