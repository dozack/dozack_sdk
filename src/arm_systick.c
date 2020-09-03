/*
 * arm_systick.c
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */
#include <arm_systick.h>
#include "system.h"

#include "stm32l4xx.h"

typedef struct {
  volatile uint64_t millis;
  uint32_t clock;
  uint32_t cycle;
  uint32_t scale;
} systick_device_t;

static systick_device_t _systick;

uint64_t systick_millis(void) {
  return _systick.millis;
}

uint64_t systick_micros(void) {
  return _systick.millis * 1000;
}

void systick_delay(uint32_t delay_ms) {
  uint64_t millis = _systick.millis;

  while ((_systick.millis - millis) < delay_ms);
}

void systick_initialize(unsigned int priority) {
  NVIC_SetPriority(SysTick_IRQn, priority);
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

void systick_enable(void) {
  uint32_t cycle = 0;
  uint32_t count = 0;

  if (_systick.clock != system_sysclk())
  {
    _systick.clock = system_sysclk();
    _systick.cycle = _systick.clock / 1000;

    cycle = _systick.cycle;
    count = (_systick.cycle - 1) - SysTick->VAL;

    SysTick->VAL = (_systick.cycle - 1) - ((count * _systick.cycle) / cycle);
    SysTick->LOAD = (_systick.cycle - 1);
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
  }
  else
  {
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
  }
}

void systick_disable(void) {
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
  _systick.millis += 1;
}

