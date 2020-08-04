/**
 * @file system.c
 * @date Jul 21, 2020
 * @author Zoltan Dolensky
 * @brief 
 */

#include "system.h"
#include "stm32l4xx.h"

static const uint32_t _system_clock_table[3] = {
        RCC_CFGR_SW_MSI,
        RCC_CFGR_SW_HSI,
        RCC_CFGR_SW_PLL};

static uint32_t _system_hsi16_semaphore;
static uint32_t _system_pll_semaphore;

static void _system_init_flash (void);
static void _system_init_debug (void);
static void _system_init_clock (void);
static void _system_init_power (void);
static void _system_init_rtc (void);
static void _system_switch_clock (system_clock_t clock);

system_clock_t system_get_clock_source (void) {
    if (_system_pll_semaphore) {
        return SYSTEM_CLOCK_PLL;
    }
    else if (_system_hsi16_semaphore) {
        return SYSTEM_CLOCK_HSI;
    }
    else {
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

    _system_init_power();

    _system_init_rtc();
}

static void _system_init_flash (void) {
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    //FLASH->ACR |= FLASH_ACR_LATENCY;
}

static void _system_init_debug (void) {
#if (CONFIG_SYSTEM_DEBUG == 1)
    DBGMCU->CR |= DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_IWDG_STOP | DBGMCU_APB1FZR1_DBG_LPTIM1_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_RTC_STOP | DBGMCU_APB1FZR1_DBG_TIM2_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM3_STOP | DBGMCU_APB1FZR1_DBG_TIM4_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM5_STOP | DBGMCU_APB1FZR1_DBG_TIM6_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM7_STOP | DBGMCU_APB1FZR1_DBG_WWDG_STOP;
    DBGMCU->APB1FZR2 |= DBGMCU_APB1FZR2_DBG_LPTIM2_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM15_STOP | DBGMCU_APB2FZ_DBG_TIM16_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM17_STOP | DBGMCU_APB2FZ_DBG_TIM1_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM8_STOP;
#endif
}

static void _system_init_clock (void) {
    SystemCoreClock = 4000000;

    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;

    PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;

    while (PWR->SR2 & PWR_SR2_VOSF);

    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLSRC) | RCC_PLLCFGR_PLLSRC_HSI;
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLR) | RCC_PLLCFGR_PLLR_0;
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLN) | (RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_1);

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;

    SysTick->LOAD = 4000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |=
    SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

static void _system_init_power (void) {
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
}

static void _system_init_rtc (void) {
    PWR->CR1 |= PWR_CR1_DBP;

    RCC->BDCR |= RCC_BDCR_LSEDRV;

    RCC->BDCR |= RCC_BDCR_LSEON;

    while (!(RCC->BDCR & RCC_BDCR_LSERDY));

    RCC->BDCR |= RCC_BDCR_RTCSEL_0;

    RCC->BDCR |= RCC_BDCR_RTCEN;

    RTC->WPR = 0xca;
    RTC->WPR = 0x53;

    if (RTC->ISR & RTC_ISR_INITS) {
        RTC->ISR |= RTC_ISR_INIT;

        while (!(RTC->ISR & RTC_ISR_INITF));

        RTC->PRER = (0x7f << 16) | 0xff;

        RTC->ISR &= ~RTC_ISR_INIT;
    }

    RTC->CR &= ~RTC_CR_WUTE;

    while (!(RTC->ISR & RTC_ISR_WUTWF));

    RTC->WUTR = 20;

    RTC->ISR &= ~RTC_ISR_WUTF;

    RTC->CR |= RTC_CR_WUTIE;

    RTC->CR |= RTC_CR_WUTE;

    RTC->WPR = 0x00;

    EXTI->IMR1 |= EXTI_IMR1_IM20;

    EXTI->RTSR1 |= EXTI_RTSR1_RT20;

    PWR->CR1 &= ~PWR_CR1_DBP;

    NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

static void _system_switch_clock (system_clock_t clock) {
    /* enter critical section - disable irq */
    __disable_irq();

    uint32_t mask = _system_clock_table[clock];

    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | mask;

    /* leave critical section - enable irq again */
    __enable_irq();
}
void system_hsi16_enable (void) {
    _system_hsi16_semaphore++;

    if (_system_hsi16_semaphore == 1) {
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_0;

        RCC->CR |= RCC_CR_HSION;

        while (!(RCC->CR & RCC_CR_HSIRDY));

        _system_switch_clock(SYSTEM_CLOCK_HSI);

        SysTick->LOAD = 16000 - 1;

        SystemCoreClock = 16000000;
    }
}

void system_hsi16_disable (void) {
    _system_hsi16_semaphore--;

    if (_system_hsi16_semaphore == 0) {
        _system_switch_clock(SYSTEM_CLOCK_MSI);

        RCC->CR &= ~RCC_CR_HSION;

        while (RCC->CR & RCC_CR_HSIRDY);

        SysTick->LOAD = 4000 - 1;

        SystemCoreClock = 4000000;

        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;
    }
}

void system_pll_enable (void) {
    _system_pll_semaphore++;

    if (_system_pll_semaphore == 1) {
        system_hsi16_enable();

        FLASH->ACR |= FLASH_ACR_LATENCY;
        FLASH->ACR;

        RCC->CR |= RCC_CR_PLLON;

        while (!(RCC->CR & RCC_CR_PLLRDY));

        _system_switch_clock(SYSTEM_CLOCK_PLL);

        SysTick->LOAD = 80000 - 1;

        SystemCoreClock = 80000000;
    }
}

void system_pll_disable (void) {
    _system_pll_semaphore--;

    if (_system_pll_semaphore == 0) {
        _system_switch_clock(SYSTEM_CLOCK_HSI);

        RCC->CR &= ~RCC_CR_PLLON;
        while (RCC->CR & RCC_CR_PLLRDY);

        FLASH->ACR &= FLASH_ACR_LATENCY;
        FLASH->ACR;

        system_hsi16_disable();
    }
}

void system_reset (void) {
    NVIC_SystemReset();
}

__attribute__((weak)) void SysTick_Handler (void) {
    RCC->CFGR;
}

void RTC_WKUP_IRQHandler (void) {
    if (RTC->ISR & RTC_ISR_WUTF) {
        PWR->CR1 |= PWR_CR1_DBP;

        RTC->WPR = 0xca;
        RTC->WPR = 0x53;

        RTC->ISR &= ~RTC_ISR_WUTF;

        RTC->WPR = 0x00;

        PWR->CR1 &= ~PWR_CR1_DBP;
    }

    EXTI->PR1 = EXTI_PR1_PIF20;
}

