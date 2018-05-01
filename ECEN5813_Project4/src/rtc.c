/*
 * rtc.c
 *
 *  Created on: May 1, 2018
 *      Author: karroshuang
 */

#include "GPIO.h"
#include "MKL25Z4.h"
#include "rtc.h"

uint32_t RTC_seconds;

void rtc_init(){
	NVIC_EnableIRQ(RTC_Seconds_IRQn);

	/*Enable CLK for RTC*/
	MCG->C1 |= MCG_C1_IRCLKEN(1); /* Enables the internal reference clock for use as MCGIRCLK */
	MCG->C2 &= ~MCG_C2_IRCS(1); /* Slow internal reference clock selected */

	/*Set PTC1 as RTC_CLKIN & set 32kHz clock as source*/
	SIM->SOPT1 &= SIM_SOPT1_OSC32KSEL(2); /*Select the 32 kHz clock source for RTC from RTC_CLKIN*/
	PORTC->PCR[1] = PORT_PCR_MUX(1); /*Configures PORTC PIN1 into RTC_CLKIN mode*/

	/*Set PTC3 as RTC_CLKOUT & set the MCGIRCLK clock as output */
	SIM->SOPT2 |= SIM_SOPT2_CLKOUTSEL(4); /*Selects the clock to output on the CLKOUT from MCGIRCLK*/
	PORTC->PCR[3] = PORT_PCR_MUX(5); /*Configures PORTC PIN3 into CLKOUT mode*/

	/*Enable software access and interrupts to the RTC module.*/
	SIM->SCGC6 |= SIM_SCGC6_RTC(1); /*Access and interrupts to the RTC module enabled */

	/*Reset and Clear RTC Registers*/
	RTC->CR = RTC_CR_SWR(1); /*Resets all RTC registers except for the SWR bit */
	RTC->CR &= ~RTC_CR_SWR(1); /*Reset the SWR Bit back to 0*/
	if (RTC->SR & RTC_SR_TIF_MASK){ /*After RTC is reset, time invalid bit is set and needs to be cleared*/
	   RTC->TSR = 0x00000000; /*TIF Register is reset back to 0 when TSR register is written to*/
	}

	/*Set RTC compensation interval to be accurately measuring seconds based on 32.768 kHz clk*/
	RTC->TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xFF);

	/*Enable seconds interrupt from RTC module and enable the IRQ*/
	RTC->IER = 0x00;  /*Clear IER register*/
	RTC->IER |= RTC_IER_TSIE(1); /*Seconds interrupt is enabled*/
	RTC->SR |= RTC_SR_TCE(1); /*Time counter is enabled*/

}

void RTC_Seconds_IRQHandler(){
	RGB_RED_TOGGLE(); /*Heart Beat Simulator*/
	RTC_seconds = (uint32_t) RTC->TSR; /*Update RTC_seconds variable from register*/
}


