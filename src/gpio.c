/*
 * gpio.c
 *
 *  Created on: Aug 7, 2020
 *      Author: zdole
 */

#include "irq.h"
#include "gpio.h"
#include "stm32l4xx.h"

GPIO_TypeDef *const _gpio_port[] = {
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG};

static const uint32_t _gpio_port_en[] = {
    RCC_AHB2ENR_GPIOAEN,
    RCC_AHB2ENR_GPIOBEN,
    RCC_AHB2ENR_GPIOCEN,
    RCC_AHB2ENR_GPIODEN,
    RCC_AHB2ENR_GPIOEEN,
    RCC_AHB2ENR_GPIOFEN,
    RCC_AHB2ENR_GPIOGEN};

void gpio_enable_port(gpio_port_t port) {
    RCC->AHB2ENR |= _gpio_port_en[port];
}

void gpio_set_pull(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull) {
    uint32_t _pin_mask = 0x3 << (pin << 1);
    irq_disable();
    _gpio_port[port]->PUPDR &= ~_pin_mask;
    _gpio_port[port]->PUPDR |= pull << (pin * 2);
    irq_enable();
}

gpio_pull_t gpio_get_pull(gpio_port_t port, gpio_pin_t pin) {
    uint32_t _pin_mask = 0x3 << (pin << 1);
    return (gpio_pull_t) ((_gpio_port[port]->PUPDR & _pin_mask) >> (pin * 2));
}

void gpio_set_mode(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode) {
    uint32_t _pin_mask = 0x3 << (pin << 1);
    irq_disable();
    if (mode == GPIO_MODE_OUTPUT_OD) {
        _gpio_port[port]->OTYPER |= 0x1 << pin;
        mode = GPIO_MODE_OUTPUT;
    }
    else if ((_gpio_port[port]->OTYPER & (0x1 << pin) >> pin)) {
        _gpio_port[port]->OTYPER &= ~(0x1 << pin);
    }
    else if (mode == GPIO_MODE_ALTERNATE) {
        _gpio_port[port]->OSPEEDR |= _pin_mask;
    }
    else if (mode != GPIO_MODE_ALTERNATE
            && ((_gpio_port[port]->OSPEEDR & _pin_mask) >> (pin << 1))) {
        _gpio_port[port]->OSPEEDR &= ~_pin_mask;
    }
    _gpio_port[port]->MODER &= ~_pin_mask;
    _gpio_port[port]->MODER |= mode << (pin << 1);
    irq_enable();
}

gpio_mode_t gpio_get_mode(gpio_port_t port, gpio_pin_t pin) {
    uint32_t _pin_mask = 0x3 << (pin << 1);
    gpio_mode_t _mode = (_gpio_port[port]->MODER & _pin_mask) >> (pin << 1);

    if (_mode == GPIO_MODE_OUTPUT && ((_gpio_port[port]->OTYPER & (1 << pin)) >> pin)) {
        _mode = GPIO_MODE_OUTPUT_OD;
    }
    return _mode;
}

void gpio_set_alternate(gpio_port_t port, gpio_pin_t pin, gpio_alternate_t alternate) {
    uint8_t _index = 0;
    if (pin > GPIO_PIN_7) {
        pin -= 8;
        _index += 1;
    }
    uint32_t _pin_mask = 0xf << (pin << 2);
    _gpio_port[port]->AFR[_index] &= ~_pin_mask;
    _gpio_port[port]->AFR[_index] |= alternate << (pin << 2);
}

gpio_alternate_t gpio_get_alternate(gpio_port_t port, gpio_pin_t pin) {
    uint8_t _index = 0;
    if (pin > GPIO_PIN_7) {
        pin -= 8;
        _index += 1;
    }
    uint32_t _pin_mask = 0xf << (pin << 2);
    return (gpio_alternate_t) (_gpio_port[port]->AFR[_index] & _pin_mask) >> (pin << 2);
}

bool gpio_get_input(gpio_port_t port, gpio_pin_t pin) {
    return (bool) ((_gpio_port[port]->IDR & (0x1 << pin)) >> pin);
}

void gpio_set_output(gpio_port_t port, gpio_pin_t pin, bool output) {
    uint32_t _pin_mask = 1 << pin;
    if (!output) {
        _pin_mask <<= 16;
    }
    _gpio_port[port]->BSRR |= _pin_mask;
}

bool gpio_get_output(gpio_port_t port, gpio_pin_t pin) {
    return (bool) ((_gpio_port[port]->ODR & (0x1 << pin)) >> pin);
}

void gpio_toggle_output(gpio_port_t port, gpio_pin_t pin) {
    uint32_t _pin_mask = 1 << pin;
    _gpio_port[port]->ODR ^= _pin_mask;
}
