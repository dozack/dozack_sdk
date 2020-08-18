/*
 * scheduler.c
 *
 *  Created on: Aug 15, 2020
 *      Author: zdole
 */

#include "scheduler.h"
#include "system.h"

static struct {
    struct {
        tick_t tick_exec;
        void (*task)(void*);
        void *param;
    } pool[SCHEDULER_MAX_TASKS];
    tick_t tick_spin;
    scheduler_task_id_t current_task_id;
    scheduler_task_id_t max_task_id;
} _scheduler;

void scheduler_init(void) {
    memset(&_scheduler, 0, sizeof(_scheduler));
}

void scheduler_run(void) {
    static scheduler_task_id_t *task_id = &_scheduler.current_task_id;

    while (true) {
        _scheduler.tick_spin = tick_get();

        for (*task_id = 0; *task_id <= _scheduler.max_task_id; (*task_id)++) {
            if (_scheduler.pool[*task_id].task != NULL) {
                if (_scheduler.tick_spin >= _scheduler.pool[*task_id].tick_exec) {
                    _scheduler.pool[*task_id].tick_exec = TICK_INFINITE;
                    _scheduler.pool[*task_id].task(_scheduler.pool[*task_id].param);
                }
            }
        }
    }
}

scheduler_task_id_t scheduler_register_task(void (*task)(void*), void *param, tick_t tick) {
    for (scheduler_task_id_t i = 0; i < SCHEDULER_MAX_TASKS; i++) {
        if (_scheduler.pool[i].task == NULL) {
            _scheduler.pool[i].tick_exec = tick;
            _scheduler.pool[i].task = task;
            _scheduler.pool[i].param = param;

            if (_scheduler.max_task_id < i) {
                _scheduler.max_task_id = i;
            }
            return i;
        }

    }

    /* TODO - handle error there */

    return 0;
}

void scheduler_unregister_task(scheduler_task_id_t task_id) {
    _scheduler.pool[task_id].task = NULL;

    if (_scheduler.max_task_id == task_id) {
        for (scheduler_task_id_t i = task_id; i > 0; i--) {
            if (_scheduler.pool[i].task != NULL) {
                _scheduler.max_task_id = i;
                return;
            }
        }
    }
}

scheduler_task_id_t scheduler_get_current_task_id(void) {
    return _scheduler.current_task_id;
}

tick_t scheduler_get_spin_tick(void) {
    return _scheduler.tick_spin;
}

void scheduler_plan_now(scheduler_task_id_t task_id) {
    _scheduler.pool[task_id].tick_exec = 0;
}

void scheduler_plan_absolute(scheduler_task_id_t task_id, tick_t tick) {
    _scheduler.pool[task_id].tick_exec = tick;
}

void scheduler_plan_relative(scheduler_task_id_t task_id, tick_t tick) {
    _scheduler.pool[task_id].tick_exec = _scheduler.tick_spin + tick;
}

void scheduler_plan_from_now(scheduler_task_id_t task_id, tick_t tick) {
    _scheduler.pool[task_id].tick_exec = tick_get() + tick;
}

void scheduler_plan_current_now(void) {
    _scheduler.pool[_scheduler.current_task_id].tick_exec = 0;
}

void scheduler_plan_current_absolute(tick_t tick) {
    _scheduler.pool[_scheduler.current_task_id].tick_exec = tick;
}

void scheduler_plan_current_relative(tick_t tick) {
    _scheduler.pool[_scheduler.current_task_id].tick_exec = _scheduler.tick_spin + tick;
}

void scheduler_plan_current_from_now(tick_t tick) {
    _scheduler.pool[_scheduler.current_task_id].tick_exec = tick_get() + tick;
}
