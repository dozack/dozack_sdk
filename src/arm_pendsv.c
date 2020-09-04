/*
 * arm_pendsv.c
 *
 *  Created on: Sep 3, 2020
 *      Author: zoltan
 */
#include "stdlib.h"
#include "arm.h"

#include "stm32l4xx.h"

typedef struct {
  arm_pendsv_routine_t routine;
  void *context;
  uint32_t arg;
} arm_pendsv_entry_t;

typedef struct {
  volatile arm_pendsv_entry_t *pendsv_read;
  volatile arm_pendsv_entry_t *pendsv_write;
  arm_pendsv_entry_t entry_data[ARM_PENDSV_MAX_ENTRIES];
} arm_pendsv_driver_t;

static arm_pendsv_driver_t _arm_pendsv;

extern volatile arm_pendsv_routine_t* arm_pendsv_enqueue(arm_pendsv_routine_t routine, void *context, uint32_t arg) {
  volatile arm_pendsv_entry_t *pendsv_write, *pendsv_write_next;
  /* Iterate driver buffer and store entry to actual index */
  do
  {
    /* Load actual and next entry*/
    pendsv_write = _arm_pendsv.pendsv_write;
    pendsv_write_next = pendsv_write + 1;
    /* Check for entry buffer overflow */
    if (pendsv_write_next == &_arm_pendsv.entry_data[ARM_PENDSV_MAX_ENTRIES])
    {
      /* Entry buffer overflow, set pointer to buffer start */
      pendsv_write_next = &_arm_pendsv.entry_data[0];
    }
    /* Check for stored entry duplicity */
    if (pendsv_write_next == _arm_pendsv.pendsv_read)
    {
      /* Duplicit entry, return NULL */
      return NULL;
    }
  }
  while (!(__atomic_compare_exchange_n((volatile uint32_t*) &_arm_pendsv.pendsv_write, (uint32_t*) &pendsv_write, (uint32_t) pendsv_write_next, 0,
  __ATOMIC_RELAXED, __ATOMIC_RELAXED)));
  /* Store entry parameters */
  pendsv_write->routine = routine;
  pendsv_write->context = context;
  pendsv_write->arg = arg;
  /* Trigger PendSV interrupt */
  SCB->ICSR = SCB_ICSR_PENDSVSET_Msk;
  return &pendsv_write->routine;
}

static __attribute__((used)) void arm_pendsv_dequeue() {
  volatile arm_pendsv_entry_t *pendsv_read;
  arm_pendsv_routine_t routine;
  void *context;
  uint32_t arg;
  /* Get pointer to actual entry */
  pendsv_read = _arm_pendsv.pendsv_read;
  /* Iterate and execute all pending entries */
  while (pendsv_read != _arm_pendsv.pendsv_write)
  {
    routine = pendsv_read->routine;
    context = pendsv_read->context;
    arg = pendsv_read->arg;
    /* Load next entry */
    pendsv_read++;
    /* Check for entry buffer overflow */
    if (pendsv_read == &_arm_pendsv.entry_data[ARM_PENDSV_MAX_ENTRIES])
    {
      /* Entry buffer overflow, set pointer to buffer start */
      pendsv_read = &_arm_pendsv.entry_data[0];
    }
    /* Store and execute next entry */
    _arm_pendsv.pendsv_read = pendsv_read;
    (*routine)(context, arg);
  }
}

void arm_pendsv_initialize(void) {
  /* Load first entry */
  _arm_pendsv.pendsv_read = &_arm_pendsv.entry_data[0];
  _arm_pendsv.pendsv_write = &_arm_pendsv.entry_data[0];
  /* Set lowest priority for PendSV */
  NVIC_SetPriority(PendSV_IRQn, ((1 << __NVIC_PRIO_BITS) - 1));
}

extern void PendSV_Handler(void) {
  /* Call dequeue function */
  arm_pendsv_dequeue();
}
