/*
 * timer.h
 *
 *  Created on: Aug 15, 2020
 *      Author: zdole
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(void);

void timer_start(void);

uint16_t timer_get_microseconds(void);

void timer_delay(uint16_t microseconds);

void timer_clear(void);

void timer_stop(void);

#ifdef __cplusplus
}
#endif

#endif /* TIMER_H_ */
