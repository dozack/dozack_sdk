/*
 * scheduler.h
 *
 *  Created on: Aug 15, 2020
 *      Author: zdole
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "tick.h"
#include "common.h"

#ifndef SHEDULER_MAX_TASKS
#define SCHEDULER_MAX_TASKS 32
#endif

typedef uint32_t scheduler_task_id_t;

#ifdef __cplusplus
extern "C" {
#endif

void scheduler_init(void);

void scheduler_run(void);

scheduler_task_id_t scheduler_register_task(void (*task)(void*), void *param, tick_t tick);

void scheduler_unregister_task(scheduler_task_id_t task_id);

scheduler_task_id_t scheduler_get_current_task_id(void);

tick_t scheduler_get_spin_tick(void);

void scheduler_plan_now(scheduler_task_id_t task_id);

void scheduler_plan_absolute(scheduler_task_id_t task_id, tick_t tick);

void scheduler_plan_relative(scheduler_task_id_t task_id, tick_t tick);

void scheduler_plan_from_now(scheduler_task_id_t task_id, tick_t tick);

void scheduler_plan_current_now(void);

void scheduler_plan_current_absolute(tick_t tick);

void scheduler_plan_current_relative(tick_t tick);

void scheduler_plan_current_from_now(tick_t tick);

#ifdef __cplusplus
}
#endif

#endif /* SCHEDULER_H_ */
