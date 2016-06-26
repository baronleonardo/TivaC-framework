/*
 * digital.h
 *
 *  Created on: Jun 14, 2016
 *      Author: leo-0
 */

#ifndef SRC_DIGITAL_H_
#define SRC_DIGITAL_H_

#include "pins.h"

void digital_write( GPIO_pins pin, GPIO_state state );
GPIO_state digital_read( GPIO_pins pin );

#endif /* SRC_DIGITAL_H_ */
