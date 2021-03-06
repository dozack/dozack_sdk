/**
 * @file system.h
 * @date Jul 21, 2020
 * @author Zoltan Dolensky
 * @brief 
 */
#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "stdbool.h"
#include "stdlib.h"
#include "arm_systick.h"

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief All available peripherals
 */
enum {
  SYSTEM_PERIPH_FLASH = 0,
  SYSTEM_PERIPH_SRAM1,
  SYSTEM_PERIPH_SRAM2,
  SYSTEM_PERIPH_DMA1,
  SYSTEM_PERIPH_DMA2,
  SYSTEM_PERIPH_GPIOA,
  SYSTEM_PERIPH_GPIOB,
  SYSTEM_PERIPH_GPIOC,
  SYSTEM_PERIPH_GPIOD,
  SYSTEM_PERIPH_GPIOE,
  SYSTEM_PERIPH_GPIOF,
  SYSTEM_PERIPH_GPIOG,
  SYSTEM_PERIPH_GPIOH,
  SYSTEM_PERIPH_ADC,
  SYSTEM_PERIPH_DAC,
  SYSTEM_PERIPH_USB,
  SYSTEM_PERIPH_USART1,
  SYSTEM_PERIPH_USART2,
  SYSTEM_PERIPH_USART3,
  SYSTEM_PERIPH_UART4,
  SYSTEM_PERIPH_UART5,
  SYSTEM_PERIPH_LPUART1,
  SYSTEM_PERIPH_I2C1,
  SYSTEM_PERIPH_I2C2,
  SYSTEM_PERIPH_I2C3,
  SYSTEM_PERIPH_SPI1,
  SYSTEM_PERIPH_SPI2,
  SYSTEM_PERIPH_SPI3,
  SYSTEM_PERIPH_CAN1,
  SYSTEM_PERIPH_QSPI,
  SYSTEM_PERIPH_SDMMC1,
  SYSTEM_PERIPH_SAI1,
  SYSTEM_PERIPH_SAI2,
  SYSTEM_PERIPH_DFSDM1,
  SYSTEM_PERIPH_TIM1,
  SYSTEM_PERIPH_TIM2,
  SYSTEM_PERIPH_TIM3,
  SYSTEM_PERIPH_TIM4,
  SYSTEM_PERIPH_TIM5,
  SYSTEM_PERIPH_TIM6,
  SYSTEM_PERIPH_TIM7,
  SYSTEM_PERIPH_TIM8,
  SYSTEM_PERIPH_TIM15,
  SYSTEM_PERIPH_TIM16,
  SYSTEM_PERIPH_TIM17,
  SYSTEM_PERIPH_LPTIM1,
  SYSTEM_PERIPH_LPTIM2,
  SYSTEM_PERIPH_COUNT
};

/**
 * @brief System reset causes
 */
#define SYSTEM_RESET_POWERON          0x00
#define SYSTEM_RESET_EXTERNAL         0x01
#define SYSTEM_RESET_SOFTWARE         0x02
#define SYSTEM_RESET_WATCHDOG         0x03
#define SYSTEM_RESET_BROWNOUT         0x04
#define SYSTEM_RESET_FIREWALL         0x05
#define SYSTEM_RESET_OTHER            0x06
#define SYSTEM_RESET_STANDBY          0x07

/**
 * @brief Microcontroller clock output modes
 */
#define SYSTEM_MCO_MODE_NONE          0x00
#define SYSTEM_MCO_MODE_SYSCLK        0x01
#define SYSTEM_MCO_MODE_MSI           0x02
#define SYSTEM_MCO_MODE_HSI16         0x03
#define SYSTEM_MCO_MODE_HSE           0x04
#define SYSTEM_MCO_MODE_PLL           0x05
#define SYSTEM_MCO_MODE_LSI           0x06
#define SYSTEM_MCO_MODE_LSE           0x07

void system_peripheral_reset(unsigned int peripheral);
void system_peripheral_enable(unsigned int peripheral);
void system_peripheral_disable(unsigned int peripheral);
void system_initialize(uint32_t lseclk);
void system_sysclk_pll(void);
void system_sysclk_msi(void);
void system_lsi_enable(void);
void system_lsi_disable(void);
void system_hsi16_enable(void);
void system_hsi16_disable(void);
void system_mco_configure(unsigned int mode, unsigned int divider);
uint32_t system_reset_cause(void);
uint32_t system_lseclk(void);
uint32_t system_sysclk(void);
void system_reset(void);
void system_dfu(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H_ */
