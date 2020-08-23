/*
 * exti.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef EXTI_H_
#define EXTI_H_

#include "stdbool.h"

#include "stm32l4xx.h"

typedef enum {
    EXTI_LINE_PA0,
    EXTI_LINE_PA1,
    EXTI_LINE_PA2,
    EXTI_LINE_PA3,
    EXTI_LINE_PA4,
    EXTI_LINE_PA5,
    EXTI_LINE_PA6,
    EXTI_LINE_PA7,
    EXTI_LINE_PA8,
    EXTI_LINE_PA9,
    EXTI_LINE_PA10,
    EXTI_LINE_PA11,
    EXTI_LINE_PA12,
    EXTI_LINE_PA13,
    EXTI_LINE_PA14,
    EXTI_LINE_PA15,
    EXTI_LINE_PB0,
    EXTI_LINE_PB1,
    EXTI_LINE_PB2,
    EXTI_LINE_PB3,
    EXTI_LINE_PB4,
    EXTI_LINE_PB5,
    EXTI_LINE_PB6,
    EXTI_LINE_PB7,
    EXTI_LINE_PB8,
    EXTI_LINE_PB9,
    EXTI_LINE_PB10,
    EXTI_LINE_PB11,
    EXTI_LINE_PB12,
    EXTI_LINE_PB13,
    EXTI_LINE_PB14,
    EXTI_LINE_PB15,
    EXTI_LINE_PC0,
    EXTI_LINE_PC1,
    EXTI_LINE_PC2,
    EXTI_LINE_PC3,
    EXTI_LINE_PC4,
    EXTI_LINE_PC5,
    EXTI_LINE_PC6,
    EXTI_LINE_PC7,
    EXTI_LINE_PC8,
    EXTI_LINE_PC9,
    EXTI_LINE_PC10,
    EXTI_LINE_PC11,
    EXTI_LINE_PC12,
    EXTI_LINE_PC13,
    EXTI_LINE_PC14,
    EXTI_LINE_PC15,
    EXTI_LINE_PD0,
    EXTI_LINE_PD1,
    EXTI_LINE_PD2,
    EXTI_LINE_PD3,
    EXTI_LINE_PD4,
    EXTI_LINE_PD5,
    EXTI_LINE_PD6,
    EXTI_LINE_PD7,
    EXTI_LINE_PD8,
    EXTI_LINE_PD9,
    EXTI_LINE_PD10,
    EXTI_LINE_PD11,
    EXTI_LINE_PD12,
    EXTI_LINE_PD13,
    EXTI_LINE_PD14,
    EXTI_LINE_PD15,
    EXTI_LINE_PE0,
    EXTI_LINE_PE1,
    EXTI_LINE_PE2,
    EXTI_LINE_PE3,
    EXTI_LINE_PE4,
    EXTI_LINE_PE5,
    EXTI_LINE_PE6,
    EXTI_LINE_PE7,
    EXTI_LINE_PE8,
    EXTI_LINE_PE9,
    EXTI_LINE_PE10,
    EXTI_LINE_PE11,
    EXTI_LINE_PE12,
    EXTI_LINE_PE13,
    EXTI_LINE_PE14,
    EXTI_LINE_PE15,
    EXTI_LINE_PF0,
    EXTI_LINE_PF1,
    EXTI_LINE_PF2,
    EXTI_LINE_PF3,
    EXTI_LINE_PF4,
    EXTI_LINE_PF5,
    EXTI_LINE_PF6,
    EXTI_LINE_PF7,
    EXTI_LINE_PF8,
    EXTI_LINE_PF9,
    EXTI_LINE_PF10,
    EXTI_LINE_PF11,
    EXTI_LINE_PF12,
    EXTI_LINE_PF13,
    EXTI_LINE_PF14,
    EXTI_LINE_PF15,
    EXTI_LINE_PG0,
    EXTI_LINE_PG1,
    EXTI_LINE_PG2,
    EXTI_LINE_PG3,
    EXTI_LINE_PG4,
    EXTI_LINE_PG5,
    EXTI_LINE_PG6,
    EXTI_LINE_PG7,
    EXTI_LINE_PG8,
    EXTI_LINE_PG9,
    EXTI_LINE_PG10,
    EXTI_LINE_PG11,
    EXTI_LINE_PG12,
    EXTI_LINE_PG13,
    EXTI_LINE_PG14,
    EXTI_LINE_PG15,
} exti_line_t;

typedef enum {
    EXTI_EDGE_RISING = 0,
    EXTI_EDGE_FALLING,
    EXTI_EDGE_RISING_FALLING
} exti_edge_t;

#ifdef __cplusplus
extern "C" {
#endif

void exti_register(exti_line_t line, exti_edge_t edge, void (*callback)(exti_line_t, void*),
                   void *param);

void exti_unregister(exti_line_t line);

#ifdef __cplusplus
}
#endif

#endif /* EXTI_H_ */
