/*
 * arm_pendsv.h
 *
 *  Created on: Sep 3, 2020
 *      Author: zoltan
 */

#ifndef ARM_PENDSV_H_
#define ARM_PENDSV_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif

#define ARM_PENDSV_MAX_ENTRIES     16

typedef void (*arm_pendsv_routine_t)(void *context, uint32_t arg);

extern volatile arm_pendsv_routine_t* arm_pendsv_enqueue(arm_pendsv_routine_t routine, void *context, uint32_t arg);

void arm_pendsv_initialize(void);

extern void PendSV_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* ARM_PENDSV_H_ */
