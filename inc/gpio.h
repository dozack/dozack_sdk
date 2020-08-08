/*
 * gpio.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "common.h"

typedef enum {
    GPIO_PORT_A = 0,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
} gpio_port_t;

typedef enum {
    GPIO_PIN_0 = 0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
    GPIO_PIN_14,
    GPIO_PIN_15,
} gpio_pin_t;

typedef enum {
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
} gpio_pull_t;

typedef enum {
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE,
    GPIO_MODE_ANALOG,
    GPIO_MODE_OUTPUT_OD
} gpio_mode_t;

typedef enum {
    GPIO_MODE_ALTERNATE_0,
    GPIO_MODE_ALTERNATE_1,
    GPIO_MODE_ALTERNATE_2,
    GPIO_MODE_ALTERNATE_3,
    GPIO_MODE_ALTERNATE_4,
    GPIO_MODE_ALTERNATE_5,
    GPIO_MODE_ALTERNATE_6,
    GPIO_MODE_ALTERNATE_7,
    GPIO_MODE_ALTERNATE_8,
    GPIO_MODE_ALTERNATE_9,
    GPIO_MODE_ALTERNATE_10,
    GPIO_MODE_ALTERNATE_11,
    GPIO_MODE_ALTERNATE_12,
    GPIO_MODE_ALTERNATE_13,
    GPIO_MODE_ALTERNATE_14,
    GPIO_MODE_ALTERNATE_15,
} gpio_alternate_t;

#ifdef __cplusplus
extern "C" {
#endif

void gpio_enable_port(gpio_port_t port);

void gpio_set_pull(gpio_port_t port, gpio_pin_t pin, gpio_pull_t pull);

gpio_pull_t gpio_get_pull(gpio_port_t port, gpio_pin_t pin);

void gpio_set_mode(gpio_port_t port, gpio_pin_t pin, gpio_mode_t mode);

gpio_mode_t gpio_get_mode(gpio_port_t port, gpio_pin_t pin);

void gpio_set_alternate(gpio_port_t port, gpio_pin_t pin, gpio_alternate_t alternate);

gpio_alternate_t gpio_get_alternate(gpio_port_t port, gpio_pin_t pin);

bool gpio_get_input(gpio_port_t port, gpio_pin_t pin);

void gpio_set_output(gpio_port_t port, gpio_pin_t pin, bool output);

bool gpio_get_output(gpio_port_t port, gpio_pin_t pin);

void gpio_toggle_output(gpio_port_t port, gpio_pin_t pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H_ */
