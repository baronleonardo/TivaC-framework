/*
 * digital.c
 *
 *  Created on: Jun 14, 2016
 *      Author: leo-0
 */

#include "digital.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"

void digital_write( GPIO_pins pin, GPIO_state state )
{

	uint32_t port;
	uint32_t pin_number;
	uint32_t port_addr;

	uint32_t DATA;

	uint32_t ON;
	uint32_t OFF;

	get_GPIO_pin_info( pin, &port, &pin_number, &port_addr );

	DATA = port_addr + GPIO_DATA;

	ON = ( 1 << pin_number );
	OFF = ~ON;

	// check if the clock is working on that port
//	assert( (SYSCTL_RCGCGPIO_R & ON) == ON );

	if( state == HIGH )
	{
		GPIO_VALUE( DATA ) |= ON;
	}

	else if ( state == LOW )
	{
		GPIO_VALUE( DATA ) &= OFF;
	}
}

GPIO_state digital_read( GPIO_pins pin )
{
		uint32_t port;
		uint32_t pin_number;
		uint32_t port_addr;
		uint32_t DATA;
		uint32_t state;

		get_GPIO_pin_info( pin, &port, &pin_number, &port_addr );

		DATA = port_addr + GPIO_DATA;

		state = GPIO_VALUE( DATA ) & ( 1 << pin_number );

		return state;
}
