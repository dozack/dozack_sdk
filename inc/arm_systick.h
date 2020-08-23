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

uint64_t systick_millis(void);
uint64_t systick_micros(void);
void systick_delay(uint32_t delay_ms);
void systick_initialize(unsigned int priority);
void systick_enable(void);
void systick_disable(void);

extern void Systick_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* ARM_SYSTICK_H_ */
