/**
 * @file system.c
 * @date Jul 21, 2020
 * @author Zoltan Dolensky
 * @brief 
 */

#include "system.h"
#include "stm32l4xx.h"

#define _SYSTEM_DEBUG 1

static const uint32_t system_clock_table[3] = {
RCC_CFGR_SWS_MSI,
RCC_CFGR_SWS_HSI,
RCC_CFGR_SWS_PLL };

static uint32_t _system_hsi16_semaphore;
static uint32_t _system_pll_semaphore;

system_clock_t system_get_clock_source(void) {
	if (_system_pll_semaphore) {
		return SYSTEM_CLOCK_PLL;
	} else if (_system_hsi16_semaphore) {
		return SYSTEM_CLOCK_HSI;
	} else {
		return SYSTEM_CLOCK_MSI;
	}
}

uint32_t system_get_clock_frequency(void) {
	return SystemCoreClock;
}

void system_init(void){
	FLASH->ACR |= FLASH_ACR_PRFTEN;
	FLASH->ACR |= FLASH_ACR_LATENCY;


}

void system_hsi16_enable(void);

void system_hsi16_disable(void);

void system_pll_enable(void);

void system_pll_disable(void);

void system_reset(void) {
	NVIC_SystemReset();
}
