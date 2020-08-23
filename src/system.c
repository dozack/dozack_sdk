/**
 * @file system.c
 * @date Jul 21, 2020
 * @author Zoltan Dolensky
 * @brief 
 */

#include "system.h"

static volatile uint32_t *const _system_RSTR[SYSTEM_PERIPH_COUNT] = {
    &RCC->AHB1RSTR, /* SYSTEM_PERIPH_FLASH */
    NULL, /* SYSTEM_PERIPH_SRAM1 */
    NULL, /* SYSTEM_PERIPH_SRAM2 */
    &RCC->AHB1RSTR, /* SYSTEM_PERIPH_DMA1 */
    &RCC->AHB1RSTR, /* SYSTEM_PERIPH_DMA2 */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOA */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOB */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOC */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOD */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOE */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOF */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOG */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_GPIOH */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_ADC */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_DAC */
    &RCC->AHB2RSTR, /* SYSTEM_PERIPH_USB */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_USB */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_USART1 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_USART2 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_USART3 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_UART4 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_UART5 */
    &RCC->APB1RSTR2, /* SYSTEM_PERIPH_LPUART1 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_I2C1 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_I2C2 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_SPI1 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_SPI2 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_SPI3 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_CAN1 */
    &RCC->AHB3RSTR, /* SYSTEM_PERIPH_QSPI */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_SDMMC1 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_SAI1 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_SAI2 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_DFSDM1 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_TIM1 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM2 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM3 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM4 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM5 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM6 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_TIM7 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_TIM8 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_TIM15 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_TIM16 */
    &RCC->APB2RSTR, /* SYSTEM_PERIPH_TIM17 */
    &RCC->APB1RSTR1, /* SYSTEM_PERIPH_LPTIM1 */
    &RCC->APB1RSTR2, /* SYSTEM_PERIPH_LPTIM2 */
};

static uint32_t const _system_RSTMSK[SYSTEM_PERIPH_COUNT] = {
    RCC_AHB1RSTR_FLASHRST, /* SYSTEM_PERIPH_FLASH */
    0, /* SYSTEM_PERIPH_SRAM1 */
    0, /* SYSTEM_PERIPH_SRAM2 */
    RCC_AHB1RSTR_DMA1RST, /* SYSTEM_PERIPH_DMA1 */
    RCC_AHB1RSTR_DMA2RST, /* SYSTEM_PERIPH_DMA2 */
    RCC_AHB2RSTR_GPIOARST, /* SYSTEM_PERIPH_GPIOA */
    RCC_AHB2RSTR_GPIOBRST, /* SYSTEM_PERIPH_GPIOB */
    RCC_AHB2RSTR_GPIOCRST, /* SYSTEM_PERIPH_GPIOC */
    RCC_AHB2RSTR_GPIODRST, /* SYSTEM_PERIPH_GPIOD */
    RCC_AHB2RSTR_GPIOERST, /* SYSTEM_PERIPH_GPIOE */
    RCC_AHB2RSTR_GPIOFRST, /* SYSTEM_PERIPH_GPIOF */
    RCC_AHB2RSTR_GPIOGRST, /* SYSTEM_PERIPH_GPIOG */
    RCC_AHB2RSTR_GPIOHRST, /* SYSTEM_PERIPH_GPIOH */
    RCC_AHB2RSTR_ADCRST, /* SYSTEM_PERIPH_ADC */
    RCC_APB1RSTR1_DAC1RST, /* SYSTEM_PERIPH_DAC */
    RCC_AHB2RSTR_OTGFSRST, /* SYSTEM_PERIPH_USB */
    RCC_APB2RSTR_USART1RST, /* SYSTEM_PERIPH_USART1 */
    RCC_APB1RSTR1_USART2RST, /* SYSTEM_PERIPH_USART2 */
    RCC_APB1RSTR1_USART3RST, /* SYSTEM_PERIPH_USART3 */
    RCC_APB1RSTR1_UART4RST, /* SYSTEM_PERIPH_UART4 */
    RCC_APB1RSTR1_UART5RST, /* SYSTEM_PERIPH_UART5 */
    RCC_APB1RSTR2_LPUART1RST, /* SYSTEM_PERIPH_LPUART1 */
    RCC_APB1RSTR1_I2C1RST, /* SYSTEM_PERIPH_I2C1 */
    RCC_APB1RSTR1_I2C2RST, /* SYSTEM_PERIPH_I2C2 */
    RCC_APB1RSTR1_I2C3RST, /* SYSTEM_PERIPH_I2C3 */
    RCC_APB2RSTR_SPI1RST, /* SYSTEM_PERIPH_SPI1 */
    RCC_APB1RSTR1_SPI2RST, /* SYSTEM_PERIPH_SPI2 */
    RCC_APB1RSTR1_SPI3RST, /* SYSTEM_PERIPH_SPI3 */
    RCC_APB1RSTR1_CAN1RST, /* SYSTEM_PERIPH_CAN1 */
    RCC_AHB3RSTR_QSPIRST, /* SYSTEM_PERIPH_QSPI */
    RCC_APB2RSTR_SDMMC1RST, /* SYSTEM_PERIPH_SDMMC1 */
    RCC_APB2RSTR_SAI1RST, /* SYSTEM_PERIPH_SAI1 */
    RCC_APB2RSTR_SAI2RST, /* SYSTEM_PERIPH_SAI2 */
    RCC_APB2RSTR_DFSDM1RST, /* SYSTEM_PERIPH_DFSDM1 */
    RCC_APB2RSTR_TIM1RST, /* SYSTEM_PERIPH_TIM1 */
    RCC_APB1RSTR1_TIM2RST, /* SYSTEM_PERIPH_TIM2 */
    RCC_APB1RSTR1_TIM3RST, /* SYSTEM_PERIPH_TIM3 */
    RCC_APB1RSTR1_TIM4RST, /* SYSTEM_PERIPH_TIM4 */
    RCC_APB1RSTR1_TIM5RST, /* SYSTEM_PERIPH_TIM5 */
    RCC_APB1RSTR1_TIM6RST, /* SYSTEM_PERIPH_TIM6 */
    RCC_APB1RSTR1_TIM7RST, /* SYSTEM_PERIPH_TIM7 */
    RCC_APB2RSTR_TIM8RST, /* SYSTEM_PERIPH_TIM8 */
    RCC_APB2RSTR_TIM15RST, /* SYSTEM_PERIPH_TIM15 */
    RCC_APB2RSTR_TIM16RST, /* SYSTEM_PERIPH_TIM16 */
    RCC_APB2RSTR_TIM17RST, /* SYSTEM_PERIPH_TIM17 */
    RCC_APB1RSTR1_LPTIM1RST, /* SYSTEM_PERIPH_LPTIM1 */
    RCC_APB1RSTR2_LPTIM2RST, /* SYSTEM_PERIPH_LPTIM2 */
};

static volatile uint32_t *const _system_ENR[SYSTEM_PERIPH_COUNT] = {
    &RCC->AHB1ENR, /* SYSTEM_PERIPH_FLASH */
    NULL, /* SYSTEM_PERIPH_SRAM1 */
    NULL, /* SYSTEM_PERIPH_SRAM2 */
    &RCC->AHB1ENR, /* SYSTEM_PERIPH_DMA1 */
    &RCC->AHB1ENR, /* SYSTEM_PERIPH_DMA2 */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOA */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOB */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOC */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOD */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOE */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOF */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOG */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_GPIOH */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_ADC */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_DAC */
    &RCC->AHB2ENR, /* SYSTEM_PERIPH_USB */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_USART1 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_USART2 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_USART3 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_UART4 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_UART5 */
    &RCC->APB1ENR2, /* SYSTEM_PERIPH_LPUART1 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_I2C1 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_I2C2 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_I2C3 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_SPI1 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_SPI2 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_SPI3 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_CAN1 */
    &RCC->AHB3ENR, /* SYSTEM_PERIPH_QSPI */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_SDMMC1 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_SAI1 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_SAI2 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_DFSDM1 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_TIM1 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM2 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM3 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM4 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM5 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM6 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_TIM7 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_TIM8 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_TIM15 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_TIM16 */
    &RCC->APB2ENR, /* SYSTEM_PERIPH_TIM17 */
    &RCC->APB1ENR1, /* SYSTEM_PERIPH_LPTIM1 */
    &RCC->APB1ENR2, /* SYSTEM_PERIPH_LPTIM2 */
};

static uint32_t const _system_ENMSK[SYSTEM_PERIPH_COUNT] = {
    RCC_AHB1ENR_FLASHEN, /* SYSTEM_PERIPH_FLASH */
    0, /* SYSTEM_PERIPH_SRAM1 */
    0, /* SYSTEM_PERIPH_SRAM2 */
    RCC_AHB1ENR_DMA1EN, /* SYSTEM_PERIPH_DMA1 */
    RCC_AHB1ENR_DMA2EN, /* SYSTEM_PERIPH_DMA2 */
    RCC_AHB2ENR_GPIOAEN, /* SYSTEM_PERIPH_GPIOA */
    RCC_AHB2ENR_GPIOBEN, /* SYSTEM_PERIPH_GPIOB */
    RCC_AHB2ENR_GPIOCEN, /* SYSTEM_PERIPH_GPIOC */
    RCC_AHB2ENR_GPIODEN, /* SYSTEM_PERIPH_GPIOD */
    RCC_AHB2ENR_GPIOEEN, /* SYSTEM_PERIPH_GPIOE */
    RCC_AHB2ENR_GPIOFEN, /* SYSTEM_PERIPH_GPIOF */
    RCC_AHB2ENR_GPIOGEN, /* SYSTEM_PERIPH_GPIOG */
    RCC_AHB2ENR_GPIOHEN, /* SYSTEM_PERIPH_GPIOH */
    RCC_AHB2ENR_ADCEN, /* SYSTEM_PERIPH_ADC */
    RCC_APB1ENR1_DAC1EN, /* SYSTEM_PERIPH_DAC */
    RCC_AHB2ENR_OTGFSEN, /* SYSTEM_PERIPH_USB */
    RCC_APB2ENR_USART1EN, /* SYSTEM_PERIPH_USART1 */
    RCC_APB1ENR1_USART2EN, /* SYSTEM_PERIPH_USART2 */
    RCC_APB1ENR1_USART3EN, /* SYSTEM_PERIPH_USART3 */
    RCC_APB1ENR1_UART4EN, /* SYSTEM_PERIPH_UART4 */
    RCC_APB1ENR1_UART5EN, /* SYSTEM_PERIPH_UART5 */
    RCC_APB1ENR2_LPUART1EN, /* SYSTEM_PERIPH_LPUART1 */
    RCC_APB1ENR1_I2C1EN, /* SYSTEM_PERIPH_I2C1 */
    RCC_APB1ENR1_I2C2EN, /* SYSTEM_PERIPH_I2C2 */
    RCC_APB1ENR1_I2C3EN, /* SYSTEM_PERIPH_I2C3 */
    RCC_APB2ENR_SPI1EN, /* SYSTEM_PERIPH_SPI1 */
    RCC_APB1ENR1_SPI2EN, /* SYSTEM_PERIPH_SPI2 */
    RCC_APB1ENR1_SPI3EN, /* SYSTEM_PERIPH_SPI3 */
    RCC_APB1ENR1_CAN1EN, /* SYSTEM_PERIPH_CAN1 */
    RCC_AHB3ENR_QSPIEN, /* SYSTEM_PERIPH_QSPI */
    RCC_APB2ENR_SDMMC1EN, /* SYSTEM_PERIPH_SDMMC1 */
    RCC_APB2ENR_SAI1EN, /* SYSTEM_PERIPH_SAI1 */
    RCC_APB2ENR_SAI2EN, /* SYSTEM_PERIPH_SAI2 */
    RCC_APB2ENR_DFSDM1EN, /* SYSTEM_PERIPH_DFSDM1 */
    RCC_APB2ENR_TIM1EN, /* SYSTEM_PERIPH_TIM1 */
    RCC_APB1ENR1_TIM2EN, /* SYSTEM_PERIPH_TIM2 */
    RCC_APB1ENR1_TIM3EN, /* SYSTEM_PERIPH_TIM3 */
    RCC_APB1ENR1_TIM4EN, /* SYSTEM_PERIPH_TIM4 */
    RCC_APB1ENR1_TIM5EN, /* SYSTEM_PERIPH_TIM5 */
    RCC_APB1ENR1_TIM6EN, /* SYSTEM_PERIPH_TIM6 */
    RCC_APB1ENR1_TIM7EN, /* SYSTEM_PERIPH_TIM7 */
    RCC_APB2ENR_TIM8EN, /* SYSTEM_PERIPH_TIM8 */
    RCC_APB2ENR_TIM15EN, /* SYSTEM_PERIPH_TIM15 */
    RCC_APB2ENR_TIM16EN, /* SYSTEM_PERIPH_TIM16 */
    RCC_APB2ENR_TIM17EN, /* SYSTEM_PERIPH_TIM17 */
    RCC_APB1ENR1_LPTIM1EN, /* SYSTEM_PERIPH_LPTIM1 */
    RCC_APB1ENR2_LPTIM2EN, /* SYSTEM_PERIPH_LPTIM2 */
};

typedef struct {
    uint32_t reset;
    uint32_t lseclk;
#if 0
    uint32_t hseclk;
#endif
    uint32_t sysclk;
    uint8_t lock;
    uint8_t mco;
    uint8_t lsi;
    uint8_t hsi16;
} system_device_t;

static system_device_t _system;

void system_peripheral_reset(unsigned int peripheral) {
    *_system_RSTR[peripheral] |= _system_RSTMSK[peripheral];
    *_system_RSTR[peripheral] &= ~_system_RSTMSK[peripheral];
}

void system_peripheral_enable(unsigned int peripheral) {
    *_system_ENR[peripheral] |= _system_ENMSK[peripheral];
}

void system_peripheral_disable(unsigned int peripheral) {
    *_system_ENR[peripheral] &= ~_system_ENMSK[peripheral];
}

void system_initialize(uint32_t lseclk) {
    uint32_t primask = __get_PRIMASK();
    uint32_t timeout = 0;
    __disable_irq();
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    if (PWR->SR1 & PWR_SR1_SBF)
    {
        _system.reset = SYSTEM_RESET_STANDBY;
    }
    else
    {
        _system.reset = SYSTEM_RESET_POWERON;
        if (RCC->CSR & (RCC_CSR_LPWRRSTF | RCC_CSR_OBLRSTF))
        {
            _system.reset = SYSTEM_RESET_OTHER;
        }
        else if (RCC->CSR & RCC_CSR_FWRSTF)
        {
            _system.reset = SYSTEM_RESET_FIREWALL;
        }
        else if (RCC->CSR & (RCC_CSR_IWDGRSTF | RCC_CSR_WWDGRSTF))
        {
            _system.reset = SYSTEM_RESET_WATCHDOG;
        }
        else if (RCC->CSR & RCC_CSR_BORRSTF)
        {
            _system.reset = SYSTEM_RESET_BROWNOUT;
        }
        else if (RCC->CSR & RCC_CSR_SFTRSTF)
        {
            _system.reset = SYSTEM_RESET_SOFTWARE;
        }
        else if (RCC->CSR & RCC_CSR_PINRSTF)
        {
            _system.reset = SYSTEM_RESET_EXTERNAL;
        }
    }
    PWR->CR1 |= PWR_CR1_DBP;
    FLASH->ACR |= FLASH_ACR_PRFTEN;
    RCC->CSR |= RCC_CSR_RMVF;
    RCC->CSR &= ~RCC_CSR_RMVF;
    _system.lseclk = lseclk;
    if (lseclk)
    {
        if (!(RCC->BDCR & RCC_BDCR_LSEON))
        {
            RCC->BDCR |= RCC_BDCR_LSEDRV;
            RCC->BDCR |= RCC_BDCR_LSEON;

            timeout = 0;

            while (!(RCC->BDCR & RCC_BDCR_LSERDY))
            {
                if (++timeout >= 1000000)
                {
                    _system.lseclk = 0;
                    RCC->BDCR &= ~RCC_BDCR_LSEON;
                    break;
                }
            }
        }
    }
    if (!_system.lseclk)
    {
        RCC->CSR |= RCC_CSR_LSION;
        while (!(RCC->CSR & RCC_CSR_LSIRDY));
        _system.lsi = 1;
    }
    else
    {
        RCC->CSR &= ~RCC_CSR_LSION;
    }
    if (!(RCC->BDCR & RCC_BDCR_RTCEN))
    {
        if (!_system.lseclk)
        {
            RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_RTCSEL) | (RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCEN);
        }
        else
        {
            RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_RTCSEL) | (RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCEN);
        }
        RTC->WPR = 0xca;
        RTC->WPR = 0x53;
        RTC->ISR |= RTC_ISR_INIT;

        while (!(RTC->ISR & RTC_ISR_INITF))
        {
        }

        RTC->CR = RTC_CR_BYPSHAD;

        if (!_system.lseclk)
        {
            RTC->PRER = 0x000000ff;
            RTC->PRER |= 0x007c0000;
        }
        else
        {
            RTC->PRER = 0x000000ff;
            RTC->PRER |= 0x007f0000;
        }

        RTC->ISR &= ~RTC_ISR_INIT;
    }
    RTC->ISR &= ~(RTC_ISR_WUTF | RTC_ISR_ALRBF | RTC_ISR_ALRAF);
    RTC->WPR = 0x00;
    DBGMCU->APB1FZR1 |= (DBGMCU_APB1FZR1_DBG_IWDG_STOP | DBGMCU_APB1FZR1_DBG_WWDG_STOP);
#if 1
    DBGMCU->CR |= DBGMCU_CR_DBG_STANDBY | DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_SLEEP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_RTC_STOP | DBGMCU_APB1FZR1_DBG_TIM2_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM3_STOP | DBGMCU_APB1FZR1_DBG_TIM4_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM5_STOP | DBGMCU_APB1FZR1_DBG_TIM6_STOP;
    DBGMCU->APB1FZR1 |= DBGMCU_APB1FZR1_DBG_TIM7_STOP | DBGMCU_APB1FZR1_DBG_LPTIM1_STOP;
    DBGMCU->APB1FZR2 |= DBGMCU_APB1FZR2_DBG_LPTIM2_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM15_STOP | DBGMCU_APB2FZ_DBG_TIM16_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM17_STOP | DBGMCU_APB2FZ_DBG_TIM1_STOP;
    DBGMCU->APB2FZ |= DBGMCU_APB2FZ_DBG_TIM8_STOP;
#endif
    SystemCoreClock = 4000000;
    _system.sysclk = SystemCoreClock;
    PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;
    while (PWR->SR2 & PWR_SR2_VOSF);

    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLSRC) | RCC_PLLCFGR_PLLSRC_HSI;
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLR) | RCC_PLLCFGR_PLLR_0;
    RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLN) | (RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_1);
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;

#if 0
    SysTick->LOAD = 4000 - 1;
    SysTick->VAL = 0;
    SysTick->CTRL |= _systick
    SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
#endif
    PWR->CR1 &= ~PWR_CR1_DBP;
    RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
    __set_PRIMASK(primask);
    systick_enable();
}

void system_sysclk_pll(void) {
    if (_system.hsi16)
    {
        return;
    }
    else
    {
        RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
        systick_disable();
        __disable_irq();
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_0;
        system_hsi16_enable();
        RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SWS) | RCC_CFGR_SWS_PLL;
#if 0
        SysTick->LOAD = 80000 - 1;
#endif
        SystemCoreClock = 80000000;
        _system.sysclk = SystemCoreClock;
        __enable_irq();
        systick_enable();
        RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
    }
}

void system_sysclk_msi(void) {
    if (!_system.hsi16)
    {
        return;
    }
    else
    {
        RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
        systick_disable();
        __disable_irq();
        RCC->CFGR = (RCC->CR & ~RCC_CFGR_SWS) | RCC_CFGR_SWS_MSI;
        RCC->CR &= ~RCC_CR_PLLON;
        while (RCC->CR & RCC_CR_PLLRDY);
        FLASH->ACR &= FLASH_ACR_LATENCY;
        FLASH->ACR;
        system_hsi16_disable();
#if 0
        SysTick->LOAD = 4000 - 1;
#endif
        SystemCoreClock = 4000000;
        _system.sysclk = SystemCoreClock;
        __enable_irq();
        systick_enable();
        PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;
        RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
    }
}

void system_lsi_enable(void) {
    uint32_t primask = __get_PRIMASK();
    uint32_t lsi = _system.lsi;
    __disable_irq();
    if (!lsi)
    {
        RCC->CSR |= RCC_CSR_LSION;
        while (!(RCC->CSR & RCC_CSR_LSIRDY));
    }
    _system.lsi = ++lsi;
    __set_PRIMASK(primask);
}

void system_lsi_disable(void) {
    uint32_t primask = __get_PRIMASK();
    uint32_t lsi = --_system.lsi;
    __disable_irq();
    if (!lsi)
    {
        RCC->CSR &= ~RCC_CSR_LSION;
        while (RCC->CSR & RCC_CSR_LSIRDY);
    }
    _system.lsi = lsi;
    __set_PRIMASK(primask);
}

void system_hsi16_enable(void) {
    uint32_t primask = __get_PRIMASK();
    uint32_t hsi = _system.hsi16;
    __disable_irq();
    if (!hsi)
    {
        RCC->CR |= RCC_CR_HSION;
        while (!(RCC->CR & RCC_CR_HSION));
    }
    _system.hsi16 = ++hsi;
    __set_PRIMASK(primask);
}

void system_hsi16_disable(void) {
    uint32_t primask = __get_PRIMASK();
    uint32_t hsi = --_system.hsi16;
    __disable_irq();
    if (!hsi)
    {
        RCC->CR &= ~RCC_CR_HSION;
        while (RCC->CR & RCC_CR_HSION);
    }
    _system.hsi16 = hsi;
    __set_PRIMASK(primask);
}

void system_mco_configure(unsigned int mode, unsigned int divider) {
    uint32_t primask = __get_PRIMASK();
    uint32_t mcopre = 0;
    __disable_irq();
    RCC->CFGR &= ~(RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE);

    if (_system.mco != mode)
    {
        switch (_system.mco) {
            case SYSTEM_MCO_MODE_NONE:
            case SYSTEM_MCO_MODE_SYSCLK:
            case SYSTEM_MCO_MODE_MSI:
#if 0
            case SYSTEM_MCO_MODE_HSE:
#endif
            case SYSTEM_MCO_MODE_PLL:
            case SYSTEM_MCO_MODE_LSE:
                break;
            case SYSTEM_MCO_MODE_LSI:
                system_lsi_disable();
                break;
            case SYSTEM_MCO_MODE_HSI16:
                system_hsi16_disable();
                break;
        }

        _system.mco = mode;

        switch (_system.mco) {
            case SYSTEM_MCO_MODE_NONE:
            case SYSTEM_MCO_MODE_SYSCLK:
            case SYSTEM_MCO_MODE_MSI:
#if 0
            case SYSTEM_MCO_MODE_HSE:
#endif
            case SYSTEM_MCO_MODE_PLL:
            case SYSTEM_MCO_MODE_LSE:
                break;
            case SYSTEM_MCO_MODE_LSI:
                system_lsi_enable();
                break;
            case SYSTEM_MCO_MODE_HSI16:
                system_hsi16_enable();
                break;
        }
    }
    if (divider <= 1)
    {
        mcopre = RCC_CFGR_MCOPRE_DIV1;
    }
    else if (divider <= 2)
    {
        mcopre = RCC_CFGR_MCOPRE_DIV2;
    }
    else if (divider <= 4)
    {
        mcopre = RCC_CFGR_MCOPRE_DIV4;
    }
    else if (divider <= 8)
    {
        mcopre = RCC_CFGR_MCOPRE_DIV8;
    }
    else
    {
        mcopre = RCC_CFGR_MCOPRE_DIV16;
    }
    RCC->CFGR |= ((mode << RCC_CFGR_MCOSEL_Pos) | mcopre);
    __set_PRIMASK(primask);
}

uint32_t system_reset_cause(void) {
    return _system.reset;
}

uint32_t system_lseclk(void) {
    return _system.lseclk;
}

uint32_t system_sysclk(void) {
    return _system.sysclk;
}

void system_reset(void) {
    NVIC_SystemReset();
}

void system_dfu(void);

void system_lock_aquire(void) {
    _system.lock += 1;
}

void system_lock_release(void) {
    _system.lock -= 1;
}

