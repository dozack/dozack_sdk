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
  /* Enable flash prefetch mode */
  FLASH->ACR |= FLASH_ACR_PRFTEN;
  RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
  /* Detect reset cause */
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
  /* Enable access to backup registers */
  PWR->CR1 |= PWR_CR1_DBP;
  RCC->CSR |= RCC_CSR_RMVF;
  RCC->CSR &= ~RCC_CSR_RMVF;
  _system.lseclk = lseclk;
  /* Enable lse if present */
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
  /* Enable lsi if lse not present */
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
  /* Configure rtc if not already */
  if (!(RCC->BDCR & RCC_BDCR_RTCEN))
  {
    /* Set rtc clock source */
    if (!_system.lseclk)
    {
      RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_RTCSEL) | (RCC_BDCR_RTCSEL_1 | RCC_BDCR_RTCEN);
    }
    else
    {
      RCC->BDCR = (RCC->BDCR & ~RCC_BDCR_RTCSEL) | (RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCEN);
    }
    /* Unlock rtc */
    RTC->WPR = 0xca;
    RTC->WPR = 0x53;
    RTC->ISR |= RTC_ISR_INIT;
    while (!(RTC->ISR & RTC_ISR_INITF));
    /* Bypass shadow registers to get actual information */
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
  /* Clear interrupt flags and lock rtc */
  RTC->ISR &= ~(RTC_ISR_WUTF | RTC_ISR_ALRBF | RTC_ISR_ALRAF);
  RTC->WPR = 0x00;
  /* Disable watchdogs during debug session */
  DBGMCU->APB1FZR1 |= (DBGMCU_APB1FZR1_DBG_IWDG_STOP | DBGMCU_APB1FZR1_DBG_WWDG_STOP);
  /* Actual clock is 4 mhz (msi) */
  _system.sysclk = SystemCoreClock;
  /* Set voltage range 2 */
  PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;
  while (PWR->SR2 & PWR_SR2_VOSF);
  /* Disable backup domain access */
  PWR->CR1 &= ~PWR_CR1_DBP;
  RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
  /* Confgure pll allowing 80 mhz sysclk */
  RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLSRC) | RCC_PLLCFGR_PLLSRC_HSI;
  RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLR);
  RCC->PLLCFGR = (RCC->PLLCFGR & ~RCC_PLLCFGR_PLLN) | (RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_1);
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN;
  /* Enable systick counter */
  arm_systick_enable();
  __set_PRIMASK(primask);
}

void system_sysclk_pll(void) {
  /* Already running from pll */
  if (_system.hsi16)
  {
    return;
  }
  else
  {
    /* Enable hsi */
    system_hsi16_enable();
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    /* Set flash latency to 4 wait states */
    FLASH->ACR = (FLASH->ACR & ~FLASH_ACR_LATENCY) | FLASH_ACR_LATENCY_4WS;
    /* Disable systick and interrupts */
    arm_systick_disable();
    __disable_irq();
    /* Switch to voltage range 1 */
    PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_0;
    while (PWR->SR2 & PWR_SR2_VOSF);
    /* Enable pll and wait for its startup */
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));
    /* Switch clock source to pll */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
    SystemCoreClock = 80000000;
    _system.sysclk = SystemCoreClock;
    /* Enable interrupts and systick */
    __enable_irq();
    arm_systick_enable();
    RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
  }
}

void system_sysclk_msi(void) {
  /* Already running from msi */
  if (!_system.hsi16)
  {
    return;
  }
  else
  {
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;
    /* Disable systick and interrupts */
    arm_systick_disable();
    __disable_irq();
    /* Switch clock source to msi */
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_MSI;
    /* Disable pll */
    RCC->CR &= ~RCC_CR_PLLON;
    while (RCC->CR & RCC_CR_PLLRDY);
    SystemCoreClock = 4000000;
    _system.sysclk = SystemCoreClock;
    /* Enable interrupts and systick */
    __enable_irq();
    arm_systick_enable();
    /* Reset flash latency */
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    /* Disable hsi */
    system_hsi16_disable();
    /* Switch to voltage range 2 */
    PWR->CR1 = (PWR->CR1 & ~PWR_CR1_VOS) | PWR_CR1_VOS_1;
    while (PWR->SR2 & PWR_SR2_VOSF);
    RCC->APB1ENR1 &= ~RCC_APB1ENR1_PWREN;
  }
}

void system_lsi_enable(void) {
  uint32_t primask = __get_PRIMASK();
  __disable_irq();
  RCC->CSR |= RCC_CSR_LSION;
  while (!(RCC->CSR & RCC_CSR_LSIRDY));
  _system.lsi = 1;
  __set_PRIMASK(primask);
}

void system_lsi_disable(void) {
  uint32_t primask = __get_PRIMASK();
  __disable_irq();
  RCC->CSR &= ~RCC_CSR_LSION;
  while (RCC->CSR & RCC_CSR_LSIRDY);
  _system.lsi = 0;
  __set_PRIMASK(primask);
}

void system_hsi16_enable(void) {
  uint32_t primask = __get_PRIMASK();
  __disable_irq();
  RCC->CR |= RCC_CR_HSION;
  while (!(RCC->CR & RCC_CR_HSION));
  _system.hsi16 = 1;
  __set_PRIMASK(primask);
}

void system_hsi16_disable(void) {
  uint32_t primask = __get_PRIMASK();
  __disable_irq();
  RCC->CR &= ~RCC_CR_HSION;
  while (RCC->CR & RCC_CR_HSION);
  _system.hsi16 = 0;
  __set_PRIMASK(primask);
}

void system_mco_configure(unsigned int mode, unsigned int divider) {
  uint32_t primask = __get_PRIMASK();
  uint32_t mcopre = 0;
  __disable_irq();
  RCC->CFGR &= ~(RCC_CFGR_MCOSEL | RCC_CFGR_MCOPRE);
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

void system_dfu(void) {

}

