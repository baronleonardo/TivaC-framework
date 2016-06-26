/*
 * systick.c
 *
 *  Created on: Jun 21, 2016
 *      Author: leo-0
 */

#include "systick.h"

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))
#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable

uint32_t clock_speed = 16 * 1000000;

void systick_init(ClockSpeed MHz)
{
/* bit 0 - ENABLE  - 0 = enable or 1 = disable
 * bit 1 - INTEN   - interupt enable
 * bit 2 - CLK_SRC -
 * 			0 Precision internal oscillator (PIOSC) divided by 4
 * 			1 System clock
 */
	// disable SysTick during setup
	NVIC_ST_CTRL_R &= 0x0;
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
	NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;

	// this part is pased on SYSDIV2 in PLL
	clock_speed = ( 400 / (MHz + 1) ) * 1000000;
}

void systick_clear()
{
	NVIC_ST_CURRENT_R = 0x0;
}

void delay(uint32_t msec)
{
	/* bits 23-0
	 * MHz = number of Mega cycles in one seconds
	 * the next instruction is to set a delay cost msec
	 * what ever the Mhz is
	 * Remember: maximum value for msec is 2^24 * 1 / MHz
	 */
	uint32_t cycles = ( msec * (clock_speed / 1000) ) - 1;
	NVIC_ST_RELOAD_R = cycles;
	systick_clear();

	uint32_t start_time = NVIC_ST_CURRENT_R;
	volatile uint32_t elapsed_time;

	do {
		elapsed_time = (start_time - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
	} while( elapsed_time <= cycles );

	// while( NVIC_ST_CURRENT_R > 4 );
}
