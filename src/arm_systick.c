/*
 * arm_systick.c
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */
#include "arm.h"
#include "system.h"

#include "stm32l4xx.h"

typedef struct {
  volatile uint64_t micros;
  volatile uint64_t millis;
  uint32_t clock;
  uint32_t cycle;
  uint32_t frac;
  uint32_t accum;
  uint32_t scale;
  arm_systick_callback_t callback;
  void *context;
} systick_driver_t;

static systick_driver_t _arm_systick;

uint64_t arm_systick_millis(void) {
  return _arm_systick.millis;
}

uint64_t arm_systick_micros(void) {
  uint64_t micros;
  uint32_t count;
  do
  {
    micros = _arm_systick.micros;
    count = SysTick->VAL;
  }
  while (micros != _arm_systick.micros);
  micros += ((((_arm_systick.cycle - 1) - count) * _arm_systick.scale) >> 22);
  return micros;
}

void arm_systick_delay(uint32_t delay_ms) {
  uint64_t millis = _arm_systick.millis;
  do
  {
    arm_core_yield();
  }
  while ((_arm_systick.millis - millis) < delay_ms);
}

void arm_systick_notify(arm_systick_callback_t callback, void *context) {
  _arm_systick.callback = NULL;
  _arm_systick.context = context;
  _arm_systick.callback = callback;
}

void arm_systick_initialize(unsigned int priority) {
  NVIC_SetPriority(SysTick_IRQn, priority);
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
}

void arm_systick_enable(void) {
  uint32_t cycle = 0;
  uint32_t count = 0;

  if (_arm_systick.clock != system_sysclk())
  {

    _arm_systick.clock = system_sysclk();
    _arm_systick.cycle = _arm_systick.clock / 1000;
    _arm_systick.frac = _arm_systick.clock - (_arm_systick.cycle * 1000);
    _arm_systick.accum = 0;

    cycle = _arm_systick.cycle;
        count = (_arm_systick.cycle - 1) - SysTick->VAL;

    SysTick->VAL = (_arm_systick.cycle - 1) - ((count * _arm_systick.cycle) / cycle);
    SysTick->LOAD = (_arm_systick.cycle - 1);
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);

    _arm_systick.scale = (uint64_t) 4194304000000ull / (uint64_t) _arm_systick.clock;
  }
  else
  {
    SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk);
  }
}

void arm_systick_disable(void) {
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) {
  _arm_systick.micros += 1000;
  _arm_systick.millis += 1;

  if (_arm_systick.frac)
  {
    _arm_systick.accum += _arm_systick.frac;
    if (_arm_systick.accum >= 1000)
    {
      _arm_systick.accum -= 1000;
      SysTick->LOAD = (_arm_systick.cycle - 1) + 1;
    }
    else
    {
      SysTick->LOAD = (_arm_systick.cycle - 1);
    }
  }
  if (_arm_systick.callback)
  {
    arm_pendsv_enqueue((arm_pendsv_routine_t)_arm_systick.callback, _arm_systick.context, _arm_systick.millis);
  }
}

