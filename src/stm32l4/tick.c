/*
 * tick.c
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#include "tick.h"
#include "irq.h"
#include "stm32l4xx.h"

static tick_t _tick_counter = 0;

tick_t tick_get(void) {
    tick_t tick;

    irq_disable();

    tick = _tick_counter;

    irq_enable();

    return tick;
}

void tick_wait(tick_t delay) {
    tick_t timeout = tick_get() + delay;

    while (tick_get() < timeout);
}

void tick_increment_irq(tick_t delta) {
    _tick_counter += delta;
}
