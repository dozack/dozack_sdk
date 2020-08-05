/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "tests.h"
void tests_run(void) {
    tests_system();

    tests_exti();
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

#include "exti.h"
void tests_exti(void) {
    exti_register(EXTI_LINE_PG12, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PG12);
    exti_register(EXTI_LINE_PB12, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PB12);
    exti_register(EXTI_LINE_PA15, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PA15);
    exti_register(EXTI_LINE_PB15, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PB15);
    exti_register(EXTI_LINE_PC0, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PC0);
    exti_register(EXTI_LINE_PD0, EXTI_EDGE_RISING, NULL, NULL);
    exti_unregister(EXTI_LINE_PD0);

}
