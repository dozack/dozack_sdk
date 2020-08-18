/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "tests.h"
void tests_run(void) {
#if 1
    tests_system();

    tests_gpio();

    tests_fifo();
#endif

#if 0
    tests_exti();


    tests_scheduler();

#endif
}

#include "system.h"
void tests_system(void) {
    uint32_t clk_frq;
    system_clock_t clk_src;

    system_init();

    clk_frq = system_get_clock_frequency();
    clk_src = system_get_clock_source();

    system_hsi16_enable();

    clk_frq = system_get_clock_frequency();
    clk_src = system_get_clock_source();

    system_hsi16_disable();

    system_pll_enable();

    clk_frq = system_get_clock_frequency();
    clk_src = system_get_clock_source();

    system_pll_disable();
}

#include "gpio.h"
void tests_gpio(void) {
    gpio_enable_port(GPIO_PORT_C);

    gpio_mode_t mode;
    gpio_pull_t pull;
    gpio_alternate_t af;
    bool input = false;
    bool output = false;

    gpio_set_mode(GPIO_PORT_C, GPIO_PIN_13, GPIO_MODE_OUTPUT_OD);

    mode = gpio_get_mode(GPIO_PORT_C, GPIO_PIN_13);

    gpio_set_mode(GPIO_PORT_C, GPIO_PIN_13, GPIO_MODE_INPUT);

    mode = gpio_get_mode(GPIO_PORT_C, GPIO_PIN_13);

    gpio_set_pull(GPIO_PORT_C, GPIO_PIN_13, GPIO_PULL_UP);

    pull = gpio_get_pull(GPIO_PORT_C, GPIO_PIN_13);

    gpio_enable_port(GPIO_PORT_A);

    gpio_set_mode(GPIO_PORT_A, GPIO_PIN_9, GPIO_MODE_ALTERNATE);

    gpio_set_mode(GPIO_PORT_A, GPIO_PIN_9, GPIO_MODE_OUTPUT);

    gpio_set_alternate(GPIO_PORT_A, GPIO_PIN_9, GPIO_MODE_ALTERNATE_11);

    af = gpio_get_alternate(GPIO_PORT_A, GPIO_PIN_9);

    input = gpio_get_input(GPIO_PORT_C, GPIO_PIN_13);

    input = gpio_get_input(GPIO_PORT_A, GPIO_PIN_9);

    gpio_set_mode(GPIO_PORT_A, GPIO_PIN_5, GPIO_MODE_OUTPUT);

    gpio_set_output(GPIO_PORT_A, GPIO_PIN_5, !output);

    output = gpio_get_output(GPIO_PORT_A, GPIO_PIN_5);

    gpio_set_output(GPIO_PORT_A, GPIO_PIN_5, !output);

    output = gpio_get_output(GPIO_PORT_A, GPIO_PIN_5);

    gpio_toggle_output(GPIO_PORT_A, GPIO_PIN_5);
    gpio_toggle_output(GPIO_PORT_A, GPIO_PIN_5);
}

#include "tick.h"
#include "irq.h"
#include "exti.h"
void dummy_callback(exti_line_t line, void *param) {
    gpio_toggle_output(GPIO_PORT_A, GPIO_PIN_5);
    tick_wait(500);
    gpio_toggle_output(GPIO_PORT_A, GPIO_PIN_5);
    return;
}

void tests_exti(void) {
    exti_register(EXTI_LINE_PC13, EXTI_EDGE_FALLING, &dummy_callback, NULL);
}

#include "scheduler.h"
scheduler_task_id_t empty;
scheduler_task_id_t id_on;
scheduler_task_id_t id_off;

void empty_task(void *param){
    return;
}

void led_off_task(void* param){
    gpio_set_output(GPIO_PORT_A, GPIO_PIN_5, false);

    scheduler_plan_relative(id_on, 500);
}

void led_on_task(void* param){
    gpio_set_output(GPIO_PORT_A, GPIO_PIN_5, true);

    scheduler_plan_relative(id_off, 500);
}
void tests_scheduler(void){
    scheduler_init();

    id_on = scheduler_register_task(led_on_task, NULL, TICK_INFINITE);
    id_off = scheduler_register_task(led_off_task, NULL, TICK_INFINITE);
    empty = scheduler_register_task(empty_task, NULL, TICK_INFINITE);

    scheduler_unregister_task(empty);
    scheduler_plan_from_now(id_on, 500);
    scheduler_run();
}

#include "fifo.h"
typedef struct {
        uint8_t byte_;
        uint16_t word_;
        uint32_t long_;
}dummy_t;

static dummy_t _dummy_buffer[4];

fifo_t dummy_fifo;

void tests_fifo(void){
    fifo_init(&dummy_fifo, _dummy_buffer, sizeof(dummy_fifo));

    dummy_t _dummy_0 = {
        .byte_ = 0x7f,
        .word_ = 0xabcd,
        .long_ = 0xdeadbeef
    };

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    _dummy_0.byte_ = 0xac;
    _dummy_0.word_ = 0xfffa;
    _dummy_0.long_ = 0xdeadf00d;

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    dummy_t _dummy = {0};

    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
}
