/*
 * arm.h
 *
 *  Created on: Sep 4, 2020
 *      Author: zoltan
 */

#include "stdint.h"

#ifndef ARM_H_
#define ARM_H_

#ifdef __cplusplus
 extern "C" {
#endif

static inline void arm_core_yield(void) {
  __asm__ volatile ("wfe; sev; wfe");
}

int arm_core_priority(void);

void arm_core_udelay(uint32_t udelay);

#include "arm_pendsv.h"
#include "arm_systick.h"

#ifdef __cplusplus
}
#endif

#endif /* ARM_H_ */
