/*
 * pin_mode.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: leo-0
 */

#include "pin_mode.h"
#include "tm4c123gh6pm.h"

typedef unsigned long ulong;
typedef unsigned short ushort;

static void check_pin_protection( GPIO_pins pin, ushort pin_number, ulong port_addr );

void GPIO_pin_mode( GPIO_pins pin, GPIO_mode mode )
{
	ulong port;
	ulong pin_number;
	ulong port_addr;

	ulong AFSEL;
	ulong AMSEL;
	ulong DEN;
	ulong PCTL;
	ulong DIR;
	ulong PULL;

	ulong ON;
	ulong OFF;

	ulong delay;

	// identify the port and the pin - ex. F3
	get_GPIO_pin_info( pin, &port, &pin_number, &port_addr );

	// calculate pin value
	ON  = ( 1 << pin_number );
	OFF = ~ON;

	// enable clock for this port
	SYSCTL_RCGCGPIO_R |= (1 << port);
	// you must delay for 4 cycles to stablize
	delay = SYSCTL_RCGC2_R;

	// check if this pin is locked, if so, unlock them;
	check_pin_protection( pin, pin_number, port_addr );

	// AFSEL
	AFSEL = port_addr + GPIO_AFSEL;
	GPIO_VALUE(AFSEL) &= OFF;

	// PCTL
	PCTL = port_addr + GPIO_PCTL;
	GPIO_VALUE(PCTL) &= OFF;

	// AMSEL
	AMSEL = port_addr + GPIO_AMSEL;
	GPIO_VALUE(AMSEL) &= OFF;

	// DEN
	DEN = port_addr + GPIO_DEN;
	GPIO_VALUE(DEN) |= ON;

	// DIR
	DIR = port_addr + GPIO_DIR;

	switch( mode )
	{
		case IN:
			GPIO_VALUE(DIR) &= OFF;
			break;

		case OUT:
			GPIO_VALUE(DIR) |= ON;
			break;

		case IN_PULLUP:
			PULL = port_addr + GPIO_PUR;
			GPIO_VALUE(PULL) |= ON;
			GPIO_VALUE(DIR)  &= OFF;
			break;

		case IN_PULLDOWN:
			PULL = port_addr + GPIO_PDR;
			GPIO_VALUE(PULL) |= ON;
			GPIO_VALUE(DIR)  &= OFF;
			break;
	}
}

// we have 6 ports that could be protected ( locked )
// C(0-3), D7, F0
void check_pin_protection( GPIO_pins pin, ushort pin_number, ulong port_addr )
{
	switch(pin)
	{
		case F0:
		case D7:
		case C0:
		case C1:
		case C2:
		case C3:
			GPIO_VALUE( port_addr + GPIO_LOCK ) = 0x4C4F434B;
			GPIO_VALUE( port_addr + GPIO_CR ) = ( 1 << pin_number );
			break;
		default:
			return;
	}
}
