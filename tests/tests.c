/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "tests.h"
void tests_run (void) {
    tests_system();
}

#include "system.h"
void tests_system (void) {
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
