/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "system.h"
#include "gpio.h"
#include "uart.h"

void uart_callback(void *context, uint32_t events) {
  uart_t *uart = (uart_t*) context;
  if (events & UART_EVENT_OVERRUN)
  {

  }
  if (events & UART_EVENT_RECEIVE)
  {

  }
  if (events & UART_EVENT_TRANSMIT)
  {

  }
}

uart_t uart2 = {
  0 };

uart_pins_t uart2_pins = {
  .tx = GPIO_PIN_PA2_USART2_TX,
  .rx = GPIO_PIN_PA3_USART2_RX };
uint8_t rx_[32];

void tests_run(void) {
  system_initialize(32768);

  uint32_t pin_config = (GPIO_MODE_ALTERNATE | GPIO_OTYPE_PUSHPULL | GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH);
  gpio_pin_configure(GPIO_PIN_PA8_MCO, pin_config);

  system_mco_configure(SYSTEM_MCO_MODE_SYSCLK, 1);

  systick_initialize(3);

  system_sysclk_pll();

  system_peripheral_enable(SYSTEM_PERIPH_GPIOA);

  gpio_pin_output(GPIO_PIN_PA5);

  pin_config = (GPIO_MODE_OUTPUT | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_PUPD_PULLDOWN);
  gpio_pin_configure(GPIO_PIN_PA5, pin_config);

  gpio_pin_write(GPIO_PIN_PA5, 1);

  gpio_pin_write(GPIO_PIN_PA5, 0);

  uint32_t uart_events = (UART_EVENT_TRANSMIT | UART_EVENT_RECEIVE | UART_EVENT_OVERRUN);
  uart_create(&uart2, UART_INSTANCE_USART2, &uart2_pins, 10, 0);
  uart_enable(&uart2, &rx_[0], sizeof(rx_), 115200, &uart_callback, UART_NOTIFY_MODE_SINGLE, &uart2, uart_events);
}

#if 0
#include "fifo.h"
typedef struct {
    uint8_t byte_;
    uint16_t word_;
    uint32_t long_;
} dummy_t;

static dummy_t _dummy_buffer[4];

fifo_t dummy_fifo;

void tests_fifo(void) {
    fifo_init(&dummy_fifo, _dummy_buffer, sizeof(dummy_fifo));

    dummy_t _dummy_0 = {
        .byte_ = 0x7f,
        .word_ = 0xabcd,
        .long_ = 0xdeadbeef};

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    _dummy_0.byte_ = 0xac;
    _dummy_0.word_ = 0xfffa;
    _dummy_0.long_ = 0xdeadf00d;

    fifo_write(&dummy_fifo, &_dummy_0, sizeof(dummy_t));

    dummy_t _dummy = {
        0};

    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
    fifo_read(&dummy_fifo, &_dummy, sizeof(dummy_t));
}
#endif
