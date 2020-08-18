/*
 * irq.c
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#include "irq.h"
#include "stm32l4xx.h"

static volatile uint32_t _irq_primask = 0;
static volatile uint32_t _irq_disable = 0;

void irq_disable(void) {
    uint32_t primask = __get_PRIMASK();

    __disable_irq();

    if (!_irq_disable) {
        _irq_primask = primask & 1;
    }

    _irq_disable++;
}

void irq_enable(void) {
    if (_irq_disable) {
        _irq_disable--;

        if (!_irq_disable && !_irq_primask) {
            __enable_irq();
        }
    }
}
