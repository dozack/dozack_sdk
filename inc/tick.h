/*
 * tick.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef TICK_H_
#define TICK_H_

#include "common.h"

#define TICK_INFINITE   (uint64_t)0xffffffffffffffff

typedef uint64_t tick_t;

#ifdef __cplusplus
extern "C" {
#endif

tick_t tick_get(void);

void tick_wait(tick_t delay);

void tick_increment_irq(tick_t delta);

#ifdef __cplusplus
}
#endif

#endif /* TICK_H_ */
