/*
 * PLL.c
 *
 *  Created on: Jun 20, 2016
 *      Author: leo-0
 */

#include "PLL.h"

#define EXTRN_OSC_MHZ 16

#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))

void set_clock_speed( ClockSpeed clk )
{
	set_clock_speed_manual( EXTRN_OSC_MHZ, clk );
}

void set_clock_speed_manual( uint32_t XTAL, uint16_t SYSDIV2 )
{
	/* 1- RCC2 - enable RCC2
	 * 2- RCC2 - use PLL ( external oscillator ) or internall oscillator
	 * 3- RCC  - clear XTAL in RCC
	 * 4- RCC  - set XTAL to the specific oscillator speed (ex. 16 MHZ)
	 * 5- choose the source of oscillation OSCSRC2
	 * 6-
	 */

	/* USERCC2 - clock configure 2 - activate RCC2
	 * bit-31
	 */
	SYSCTL_RCC2_R |= 0x80000000;

	/* BYPASS2 - multiplexer 2x1 switcher
	* 0 -> use PLL
	* 1 -> use internall oscillator
	* bit-11
	*/
	SYSCTL_RCC2_R |= 0x800;

	/* specify the crystal frequency in the four XTAL bits
	* bits 10-6
	* XTAL is in RCC not RCC2
	* first : clear the required bits
	* second: set XTALL
	*/
	SYSCTL_RCC_R = ( SYSCTL_RCC_R & ~0x7C0 ) | (XTAL << 6);

	/* OSCSRC2 - multiplexer 4x1 switcher
	 * choose the main oscillator
	 * bits 6-4
	 * 00  -> main oscillator
	 * 01  -> intenal oscillator
	 * 10  -> intenal oscillator / 4
	 * 11  -> low freq internal oscillator
	 * 111 -> activate 32.768 KHz internall or external oscillator
	 */
	 SYSCTL_RCC2_R &= ~0x70;

	/* PWRDN2 - multiplexer 2x1 switcher
	 * activate PLL
	 * bit-13
	 * 1 -> PLL is off
	 * 0 -> PLL is on
	 */
	SYSCTL_RCC2_R &= ~0x2000;

	/* SYSDIV2 - System Clock Divisor
	 * 400 MHz / (SYSDIV2 + 1)
	 * bits 28-22
	 * NOTE: LSB -> least signficent bit
	 * first  : clear the required bits
	 * second : set SYSDIV2
	 */
	SYSCTL_RCC2_R = (SYSCTL_RCC2_R & ~0x1FC00000) | ( SYSDIV2 << 22 );

	/* PLLRIS register - Raw Interrupt Status -
	 * wait for PLL to stabilize
	 * bit-6
	 * 1 -> means that PLL is stabilized and is ready to use
	 */
	while( (SYSCTL_RIS_R & 0x40) == 0x0 );

	/* BYPASS2 - multiplexer 2x1 switcher
	 * 0 -> use PLL
	 * 1 -> use internall oscillator
	 * bit-11
	 */
	SYSCTL_RCC2_R &= ~0x800;
}
