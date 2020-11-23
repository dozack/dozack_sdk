/*
 * arm_systick.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef ARM_SYSTICK_H_
#define ARM_SYSTICK_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*arm_systick_callback_t)(void *context, uint32_t arg);

uint64_t arm_systick_millis(void);

void arm_systick_delay(uint32_t delay_ms);

void arm_systick_notify(arm_systick_callback_t callback, void *context);

void arm_systick_initialize(unsigned int priority);

void arm_systick_enable(void);

void arm_systick_disable(void);

extern void Systick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* ARM_SYSTICK_H_ */
