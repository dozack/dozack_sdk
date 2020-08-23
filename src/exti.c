/*
 * exti.c
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#include "exti.h"

static bool _exti_initialized = false;

static struct {
    exti_line_t line;
    void (*callback)(exti_line_t, void*);
    void *param;
} _exti_driver[16];

static inline void _exti_irq_handler(void);

void exti_register(exti_line_t line, exti_edge_t edge, void (*callback)(exti_line_t, void*),
                   void *param) {

    uint32_t pin_;
    uint32_t mask;
    uint8_t port = line >> 4;

    uint8_t pin = line - (port << 4);

    __disable_irq();

    _exti_driver[pin].line = line;
    _exti_driver[pin].callback = callback;
    _exti_driver[pin].param = param;

    if (!_exti_initialized) {
        _exti_initialized = true;

        RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

        NVIC_EnableIRQ(EXTI0_IRQn);
        NVIC_SetPriority(EXTI0_IRQn, 1);
        NVIC_EnableIRQ(EXTI1_IRQn);
        NVIC_SetPriority(EXTI1_IRQn, 1);
        NVIC_EnableIRQ(EXTI2_IRQn);
        NVIC_SetPriority(EXTI2_IRQn, 1);
        NVIC_EnableIRQ(EXTI3_IRQn);
        NVIC_SetPriority(EXTI3_IRQn, 1);
        NVIC_EnableIRQ(EXTI4_IRQn);
        NVIC_SetPriority(EXTI4_IRQn, 1);
        NVIC_EnableIRQ(EXTI9_5_IRQn);
        NVIC_SetPriority(EXTI9_5_IRQn, 1);
        NVIC_EnableIRQ(EXTI15_10_IRQn);
        NVIC_SetPriority(EXTI15_10_IRQn, 1);
    }

    pin_ = pin >> 2;
    mask = (0xf << ((pin & 3) << 2));

    SYSCFG->EXTICR[pin_] &= ~mask;

    mask = (port << ((pin & 3) << 2));

    SYSCFG->EXTICR[pin_] |= mask;

    mask = 1 << pin;

    switch (edge) {
        case EXTI_EDGE_FALLING:
            EXTI->FTSR1 |= mask;
            EXTI->RTSR1 &= ~mask;
            break;
        case EXTI_EDGE_RISING:
            EXTI->FTSR1 &= mask;
            EXTI->RTSR1 |= mask;
            break;
        case EXTI_EDGE_RISING_FALLING:
            EXTI->RTSR1 |= mask;
            EXTI->RTSR1 |= mask;
            break;
        default:
            return;
    }

    EXTI->IMR1 |= mask;

    __enable_irq();
}

void exti_unregister(exti_line_t line) {
    uint32_t port = line >> 4;

    uint8_t pin = line - (port << 4);

    uint32_t mask = 1 << pin;

    __disable_irq();

    if (line == _exti_driver[pin].line) {
        EXTI->IMR1 &= ~mask;

        EXTI->PR1 = mask;
    }

    __enable_irq();
}

static inline void _exti_irq_handler(void) {
    if (EXTI->PR1 & 0x0001) {
        EXTI->PR1 = 0x0001;
        _exti_driver[0].callback(_exti_driver[0].line, _exti_driver[0].param);
        return;
    }
    if (EXTI->PR1 & 0x0002) {
        EXTI->PR1 = 0x0002;
        _exti_driver[1].callback(_exti_driver[1].line, _exti_driver[1].param);
        return;
    }
    if (EXTI->PR1 & 0x0004) {
        EXTI->PR1 = 0x0004;
        _exti_driver[2].callback(_exti_driver[2].line, _exti_driver[2].param);
        return;
    }
    if (EXTI->PR1 & 0x0008) {
        EXTI->PR1 = 0x0008;
        _exti_driver[3].callback(_exti_driver[3].line, _exti_driver[3].param);
        return;
    }
    if (EXTI->PR1 & 0x0010) {
        EXTI->PR1 = 0x0010;
        _exti_driver[4].callback(_exti_driver[4].line, _exti_driver[4].param);
        return;
    }
    if (EXTI->PR1 & 0x0020) {
        EXTI->PR1 = 0x0020;
        _exti_driver[5].callback(_exti_driver[5].line, _exti_driver[5].param);
        return;
    }
    if (EXTI->PR1 & 0x0040) {
        EXTI->PR1 = 0x0040;
        _exti_driver[6].callback(_exti_driver[6].line, _exti_driver[6].param);
        return;
    }
    if (EXTI->PR1 & 0x0080) {
        EXTI->PR1 = 0x0080;
        _exti_driver[7].callback(_exti_driver[7].line, _exti_driver[7].param);
        return;
    }
    if (EXTI->PR1 & 0x0100) {
        EXTI->PR1 = 0x0100;
        _exti_driver[8].callback(_exti_driver[8].line, _exti_driver[8].param);
        return;
    }
    if (EXTI->PR1 & 0x0200) {
        EXTI->PR1 = 0x0200;
        _exti_driver[9].callback(_exti_driver[9].line, _exti_driver[9].param);
        return;
    }
    if (EXTI->PR1 & 0x0400) {
        EXTI->PR1 = 0x0400;
        _exti_driver[10].callback(_exti_driver[10].line, _exti_driver[10].param);
        return;
    }
    if (EXTI->PR1 & 0x0800) {
        EXTI->PR1 = 0x0800;
        _exti_driver[11].callback(_exti_driver[11].line, _exti_driver[11].param);
        return;
    }
    if (EXTI->PR1 & 0x1000) {
        EXTI->PR1 = 0x1000;
        _exti_driver[12].callback(_exti_driver[12].line, _exti_driver[12].param);
        return;
    }
    if (EXTI->PR1 & 0x2000) {
        EXTI->PR1 = 0x2000;
        _exti_driver[13].callback(_exti_driver[13].line, _exti_driver[13].param);
        return;
    }
    if (EXTI->PR1 & 0x4000) {
        EXTI->PR1 = 0x4000;
        _exti_driver[14].callback(_exti_driver[14].line, _exti_driver[14].param);
        return;
    }
    if (EXTI->PR1 & 0x8000) {
        EXTI->PR1 = 0x8000;
        _exti_driver[15].callback(_exti_driver[15].line, _exti_driver[15].param);
        return;
    }
}

void EXTI0_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI1_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI2_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI3_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI4_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI9_5_IRQHandler(void) {
    _exti_irq_handler();
}

void EXTI15_10_IRQHandler(void) {
    _exti_irq_handler();
}
