/*
 * pins.h
 *
 *  Created on: Jun 11, 2016
 *      Author: leo-0
 */

#ifndef SRC_PINS_H_
#define SRC_PINS_H_

//#include "tm4c123gh6pm.h"
#include <stdint.h>

#define GPIO_PINS_COL_LEN 8
#define GPIO_VALUE(address) (*((volatile uint32_t *)( address )))

typedef enum GPIO_pins
{
	A0, A1, A2, A3, A4, A5, A6, A7,
	B0, B1, B2, B3, B4, B5, B6, B7,
	C0, C1, C2, C3, C4, C5, C6, C7,
	D0, D1, D2, D3, D4, D5, D6, D7,
	E0, E1, E2, E3, E4, E5, E6, E7,
	F0, F1, F2, F3, F4, F5, F6, F7,
}GPIO_pins;

typedef struct Port_info
{
	uint32_t port;
	uint32_t pin_number;
	uint32_t port_addr;
} Port_info;

void get_GPIO_pin_info( GPIO_pins pin, uint32_t* port, uint32_t* pin_number,
							uint32_t* port_addr );

static const uint32_t GPIO_ports_addr[] = {
		0x40004000, // PORTA
		0x40005000, // PORTB
		0x40006000, // PORTC
		0x40007000, // PORTD
		0x40024000, // PORTE
		0x40025000, // PORTF
};

typedef enum GPIO_state
{
	LOW,
	HIGH,
} GPIO_state;

typedef enum GPIO_mode
{
	IN,
	OUT,
	IN_PULLUP,
	IN_PULLDOWN,
} GPIO_mode;

typedef enum GPIO_pull_mode
{
	UP,
	DOWN,
} GPIO_pull_mode;

typedef enum GPIO_properties
{
	GPIO_DATA  = 0x3FC,
	GPIO_DIR   = 0x400,
	GPIO_AFSEL = 0x420,
	GPIO_PUR   = 0x510,
	GPIO_PDR   = 0x514,
	GPIO_DEN   = 0x51C,
	GPIO_LOCK  = 0x520,
	GPIO_CR    = 0x524,
	GPIO_AMSEL = 0x528,
	GPIO_PCTL  = 0x52C,
} GPIO_properties;

#endif /* SRC_PINS_H_ */
