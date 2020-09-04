/*
 * arm_core.c
 *
 *  Created on: Sep 4, 2020
 *      Author: zoltan
 */
#include "arm.h"

#include "stm32l4xx.h"

typedef struct {
  uint32_t clock;
  uint32_t scale;
} arm_core_driver_t;

static arm_core_driver_t _arm_core;

int arm_core_priority(void) {
  uint32_t ipsr = __get_IPSR();
  uint32_t faultmask = __get_FAULTMASK();
  uint32_t primask = __get_PRIMASK();
  int priority, basepri;
  if (!ipsr)
  {
    priority = 256 >> (8 - __NVIC_PRIO_BITS);
  }
  else
  {
    if (ipsr >= 4)
    {
      NVIC_GetPriority((int) ipsr - 16);
    }
    else
    {
      priority = (int) ipsr - 4;
    }
  }
  if (faultmask)
  {
    if (priority > 0)
    {
      priority = 0;
    }
  }
  else
  {
    if (primask)
    {
      if (priority > 0)
      {
        priority = 0;
      }
    }
    else
    {
      basepri = __get_BASEPRI() >> (8 - __NVIC_PRIO_BITS);

      if (basepri)
      {
        if (priority > basepri)
        {
          priority = basepri;
        }
      }
    }
  }
  return priority;
}

void arm_core_udelay(uint32_t udelay) {
  uint32_t n;
  if (_arm_core.clock != SystemCoreClock)
  {
    _arm_core.clock = SystemCoreClock;
    _arm_core.scale = SystemCoreClock / 1000000;
  }

  n = (udelay * _arm_core.scale + 2) / 3;

  __asm__ __volatile__(
      "1: subs %0, #1 \n"
      "   bne  1b     \n"
      : "+r" (n));
}

