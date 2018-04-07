/*
 * project3.c
 *
 *  Created on: Apr 7, 2018
 *      Author: karroshuang
 */
#include "project3.h"

void project3(){
	/*Initializations*/
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();
	__enable_irq(); /* Enable global interrupts */
	GPIO_nrf_init();
	while(1){
		Toggle_Red_LED();
		for(int i = 0; i < 1000000; i++){
			__asm("nop");  //in CW tools use asm("nop");
		}
	}
}

