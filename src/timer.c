/*
 * timer.c
 *
 *  Created on: Aug 15, 2020
 *      Author: zdole
 */

#include "timer.h"
#include "system.h"
#include "stm32l4xx.h"

static const uint16_t _timer_prescaler_lookup[] = {
    3,
    15,
    79};

void timer_init(void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM6EN;
}

void timer_start(void) {
    TIM6->PSC = _timer_prescaler_lookup[0];

    TIM6->CNT = 0;

    TIM6->EGR = TIM_EGR_UG;

    TIM6->CR1 |= TIM_CR1_CEN;
}

uint16_t timer_get_microseconds(void) {
    return TIM6->CNT;
}

void timer_delay(uint16_t microseconds) {
    uint16_t usec = timer_get_microseconds() + microseconds;

    while (timer_get_microseconds() < usec);
}

void timer_clear(void) {
    TIM6->CNT = 0;
}

void timer_stop(void) {
    TIM6->CR1 &= ~TIM_CR1_CEN;
}

