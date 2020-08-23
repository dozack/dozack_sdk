/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "system.h"
#include "gpio.h"
void tests_run(void) {
    system_initialize(32768);
    systick_initialize(3);

    system_sysclk_pll();
    system_sysclk_msi();

    system_peripheral_enable(SYSTEM_PERIPH_GPIOA);

    gpio_pin_output(GPIO_PIN_PA5);

    gpio_pin_configure(GPIO_PIN_PA5, (GPIO_MODE_OUTPUT | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_PUPD_PULLDOWN));

    gpio_pin_write(GPIO_PIN_PA5, 1);

    gpio_pin_write(GPIO_PIN_PA5, 0);
}

#if 0
#include "fifo.h"
typedef struct {
    uint8_t byte_;
    uint16_t word_;
    uint32_t long_;
} dummy_t;

static dummy_t _dummy_buffer[4];

fifo_t dummy_fifo;

void tests_fifo(void) {
    fifo_init(&dummy_fifo, _dummy_buffer, sizeof(dummy_fifo));

    dummy_t _dummy_0 = {
        .byte_ = 0x7f,
        .word_ = 0xabcd,
        .long_ = 0xdeadbeef};

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    _dummy_0.byte_ = 0xac;
    _dummy_0.word_ = 0xfffa;
    _dummy_0.long_ = 0xdeadf00d;

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    dummy_t _dummy = {
        0};

    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
}
#endif
