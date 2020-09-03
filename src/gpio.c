/*
 * gpio.c
 *
 *  Created on: Aug 7, 2020
 *      Author: zdole
 */
#include "gpio.h"

uint32_t gpio_pin_read(uint32_t pin) {
  GPIO_TypeDef *gpio;
  uint32_t group, index;
  group = (pin & GPIO_PIN_GROUP_MASK) >> GPIO_PIN_GROUP_SHIFT;
  index = (pin & GPIO_PIN_INDEX_MASK) >> GPIO_PIN_INDEX_SHIFT;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  return ((gpio->IDR >> index) & 1);
}

void gpio_pin_write(uint32_t pin, uint32_t data) {
  GPIO_TypeDef *gpio;
  uint32_t group, index;
  group = (pin & GPIO_PIN_GROUP_MASK) >> GPIO_PIN_GROUP_SHIFT;
  index = (pin & GPIO_PIN_INDEX_MASK) >> GPIO_PIN_INDEX_SHIFT;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  if (data)
  {
    gpio->BSRR = (1 << index);
  }
  else
  {
    gpio->BRR = (1 << index);
  }
}

void gpio_pin_configure(uint32_t pin, uint32_t mode) {
  GPIO_TypeDef *gpio;
  uint32_t group, index, afsel;
  afsel = (pin >> 8) & 0xf;
  group = (pin >> 4) & 0x7;
  index = (pin >> 0) & 0xf;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN << group;
  gpio->MODER |= (0x3 << (index << 1));
#if defined STM32L476xx
  gpio->ASCR &= ~(0x1 << index);
#endif
  gpio->OTYPER = ((gpio->OTYPER & ~(0x1 << index)) | (((mode & GPIO_OTYPE_MASK) >> GPIO_OTYPE_SHIFT) << (index << 1)));
  gpio->OSPEEDR = ((gpio->OSPEEDR & ~(0x3 << (index << 1))) | (((mode & GPIO_OSPEED_MASK) >> GPIO_OSPEED_SHIFT) << (index << 1)));
  gpio->PUPDR = ((gpio->PUPDR & ~(0x3 << (index << 1))) | (((mode & GPIO_PUPD_MASK) >> GPIO_PUPD_SHIFT) << (index << 1)));
  gpio->AFR[index >> 3] = ((gpio->AFR[index >> 3] & ~(0xf << ((index & 0x7) << 2))) | (afsel << ((index & 7) << 2)));
  if ((mode & GPIO_MODE_MASK) == GPIO_MODE_ANALOG)
  {
#if defined STM32L476xx
    if (mode & GPIO_ANALOG_SWITCH)
    {
      gpio->ASCR |= (0x1 << index);
    }
#endif
  }
  else
  {
    gpio->MODER = ((gpio->MODER & ~(0x3 << (index << 1))) | (((mode & GPIO_MODE_MASK) >> GPIO_MODE_SHIFT) << (index << 1)));
  }
}

void gpio_pin_input(uint32_t pin) {
  GPIO_TypeDef *gpio;
  uint32_t group, index;
  group = (pin & GPIO_PIN_GROUP_MASK) >> GPIO_PIN_GROUP_SHIFT;
  index = (pin & GPIO_PIN_INDEX_MASK) >> GPIO_PIN_INDEX_SHIFT;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  gpio->MODER = ((gpio->MODER & ~(0x3 << (index << 1))) | ((GPIO_MODE_INPUT >> GPIO_MODE_SHIFT) << (index << 1)));
}

void gpio_pin_output(uint32_t pin) {
  GPIO_TypeDef *gpio;
  uint32_t group, index;
  group = (pin & GPIO_PIN_GROUP_MASK) >> GPIO_PIN_GROUP_SHIFT;
  index = (pin & GPIO_PIN_INDEX_MASK) >> GPIO_PIN_INDEX_SHIFT;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  gpio->MODER = ((gpio->MODER & ~(0x3 << (index << 1))) | ((GPIO_MODE_OUTPUT >> GPIO_MODE_SHIFT) << (index << 1)));
}

void gpio_pin_alternate(uint32_t pin) {
  GPIO_TypeDef *gpio;
  uint32_t group, index;
  group = (pin & GPIO_PIN_GROUP_MASK) >> GPIO_PIN_GROUP_SHIFT;
  index = (pin & GPIO_PIN_INDEX_MASK) >> GPIO_PIN_INDEX_SHIFT;
  gpio = (GPIO_TypeDef*) (GPIOA_BASE + ((GPIOB_BASE - GPIOA_BASE) * group));
  gpio->MODER = ((gpio->MODER & ~(0x3 << (index << 1))) | ((GPIO_MODE_ALTERNATE >> GPIO_MODE_SHIFT) << (index << 1)));
}

