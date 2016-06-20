/*
 * pins.c
 *
 *  Created on: Jun 11, 2016
 *      Author: leo-0
 */

#include "pins.h"

#define GPIO_PINS_COL_LEN 8

void get_GPIO_pin_info( GPIO_pins pin, uint32_t* port, uint32_t* pin_number,
							uint32_t* port_addr )
{
	*port		= pin / GPIO_PINS_COL_LEN;
	*pin_number = pin % GPIO_PINS_COL_LEN;
	*port_addr  = GPIO_ports_addr[*port];
}
