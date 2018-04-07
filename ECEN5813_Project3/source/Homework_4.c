/*
 * Homework_4.c
 *
 *  Created on: Mar 16, 2018
 *      Author: karroshuang
 */
#include "Homework_4.h"
#define CAPTURECOMPAREVAL 37500
#define DUTYPCT 50

uint32_t end;

void Timer_Configure(){
	/*Set System Clock*/
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); /*Set to 48MHz Clock*/
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK; /*Enable clock gate for TPM2*/

	/*Configure TPM2 Module*/
	TPM2->SC = TPM_SC_CMOD(1) | TPM_SC_PS(6); /*LPTPM Counter enabled, Prescaler = 64*/
	TPM2->MOD = 37500; /*Calculated to give a 25ms rate*/
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK; /*Enable Edge PWM Mode on Channel 0*/
	TPM2->CONTROLS[0].CnV = (TPM2 -> MOD * DUTYPCT) / 100; /*Set PWM Duty Cycle*/

	/*Routing LED to timer*/
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable clock gate for port B*/
	PORTB->PCR[18] = PORT_PCR_MUX(3); /*Route Red LED to timer*/
	GPIOB->PDDR = 1 << 18; /*Set Direction out*/
}

void TimerProfile_Configure(){
	SysTick_Config(0xfffff); /*Config SysTick*/
	SIM->SCGC5 |= SIM_SCGC5_PORTA(1); /*Enable Gate Clock for PORTA */
	PORTA->PCR[1] = PORT_PCR_MUX(1); /*PortA Pin 1 GPIO Mode*/
	GPIOA->PDDR |= (0x01<<1); /*Setting PA.1 Direction to Out*/
	GPIOA->PDOR |= 0x01<<1;	/*Set PA.1 to Low*/
	PORTA->PCR[1] |= PORT_PCR_IRQC(9); /*Enable interrupt trigger based on high rising edge*/
	NVIC_EnableIRQ(PORTA_IRQn); /*Enable PORTA interrupts*/
}

void PORTA_IRQHandler(){
	end = SysTick->VAL;
}

void homework4(){
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	/* Add your code here */
	GPIO_Configure();
	Timer_Configure();
	TimerProfile_Configure();
	uint32_t start, cyclesPeriph, cyclesNVIC;
	cyclesPeriph = 83;
	uint8_t *buffer = 0x000000001ffff4f4;

	for(;;) { /* Infinite loop to avoid leaving the main function */
		start = SysTick->VAL;
		GPIOA->PDOR |= (0x01<<3);
		cyclesPeriph = start - end;

		start = SysTick->VAL;
		NVIC_SetPendingIRQ(PORTA_IRQn);
		cyclesNVIC = start - end;
	}
}
