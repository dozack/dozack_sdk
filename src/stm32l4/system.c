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
                                               RCC_CFGR_SWS_PLL};

static uint32_t _system_hsi16_semaphore;
static uint32_t _system_pll_semaphore;

void _system_init_flash (void);
void _system_init_debug (void);
void _system_init_clock (void);
void _system_init_rtc (void);

system_clock_t system_get_clock_source (void) {
    if (_system_pll_semaphore)
    {
        return SYSTEM_CLOCK_PLL;
    }
    else if (_system_hsi16_semaphore)
    {
        return SYSTEM_CLOCK_HSI;
    }
    else
    {
        return SYSTEM_CLOCK_MSI;
    }
}

uint32_t system_get_clock_frequency (void) {
    return SystemCoreClock;
}

void system_init (void) {
    _system_init_flash();

    _system_init_debug();

    _system_init_clock();

    _system_init_rtc();
}

void system_hsi16_enable (void);

void system_hsi16_disable (void);

void system_pll_enable (void);

void system_pll_disable (void);

void system_reset (void) {
    NVIC_SystemReset();
}

void _system_init_flash (void) {
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    FLASH->ACR |= FLASH_ACR_LATENCY;
}

void _system_init_debug (void) {
    DBGMCU->CR |= DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_IWDG_STOP | DBGMCU_APB1FZR1_DBG_LPTIM1_STOP
            | DBGMCU_APB1FZR1_DBG_RTC_STOP | DBGMCU_APB1FZR1_DBG_TIM2_STOP
            | DBGMCU_APB1FZR1_DBG_TIM3_STOP | DBGMCU_APB1FZR1_DBG_TIM4_STOP
            | DBGMCU_APB1FZR1_DBG_TIM5_STOP | DBGMCU_APB1FZR1_DBG_TIM6_STOP
            | DBGMCU_APB1FZR1_DBG_TIM7_STOP | DBGMCU_APB1FZR1_DBG_WWDG_STOP;
    DBGMCU->APB1FZR2 |= DBGMCU_APB1FZR2_DBG_LPTIM2_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM15_STOP | DBGMCU_APB2FZ_DBG_TIM16_STOP
            | DBGMCU_APB2FZ_DBG_TIM17_STOP | DBGMCU_APB2FZ_DBG_TIM1_STOP
            | DBGMCU_APB2FZ_DBG_TIM8_STOP;
}

void _system_init_clock (void) {
    SystemCoreClock = 4000000;

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;

    PWR->CR1 |= PWR_CR1_VOS_0;

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSI;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_1;

    SysTick->LOAD = 4000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void _system_init_rtc (void){

}
