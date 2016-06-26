/*
 * systick.h
 *
 *  Created on: Jun 21, 2016
 *      Author: leo-0
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "PLL.h"

void systick_init(ClockSpeed MHz);
void systick_clear();
void delay(uint32_t msec);

#endif /* SYSTICK_H_ */
