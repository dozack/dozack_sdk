/*
 * tests.c
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "arm.h"
#include "can.h"

#if 0
uint8_t temp_buffer[64] = {
  0 };
uint8_t idx = 0;

void uart_callback(void *context, uint32_t events) {
  uart_t *uart = (uart_t*) context;
  if (events & UART_EVENT_OVERRUN)
  {

  }
  if (events & UART_EVENT_RECEIVE)
  {
    uart_receive(uart, &temp_buffer[idx++], 1);
    if (idx >= 64)
    {
      idx = 0;
    }
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
#endif

can_t can_phy;

can_pins_t can_pins = {
  .txd = GPIO_PIN_PB9_CAN1_TX,
  .rxd = GPIO_PIN_PB8_CAN1_RX };

can_message_t can_msg = {
  .id = 0xf7,
  .dlc = 8,
  .data = {
    0x01,
    0x23,
    0x45,
    0x67,
    0x89,
    0xab,
    0xcd,
    0xef } };

void can_callback(void *context, uint32_t events) {

}

void tests_run(void) {
  system_initialize(32768);
  arm_pendsv_initialize();
  arm_systick_initialize(1);

  uint32_t pin_config = (GPIO_MODE_ALTERNATE | GPIO_OTYPE_PUSHPULL | GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH);
  gpio_pin_configure(GPIO_PIN_PA8_MCO, pin_config);

  system_mco_configure(SYSTEM_MCO_MODE_SYSCLK, 8);

  system_sysclk_pll();

  uint32_t events = (CAN_EVENT_TRANSMIT_OK | CAN_EVENT_TRANSMIT_ERR | CAN_EVENT_RECEIVE | CAN_EVENT_RECEIVE_FULL | CAN_EVENT_RECEIVE_OVR);
  can_create(&can_phy, &can_pins, 12, 11, 10);
  can_enable(&can_phy, CAN_BITRATE_500_KBPS, &can_callback, &can_phy, events);
  uint8_t i = 10;
  do
  {
    can_transmit(&can_phy, &can_msg);
    arm_systick_delay(100);
  }
  while (1);

#if 0
  system_peripheral_enable(SYSTEM_PERIPH_GPIOA);

  gpio_pin_output(GPIO_PIN_PA5);

  pin_config = (GPIO_MODE_OUTPUT | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_PUPD_PULLDOWN);
  gpio_pin_configure(GPIO_PIN_PA5, pin_config);

  uint32_t i = 10;
  do
  {
    gpio_pin_write(GPIO_PIN_PA5, 1);
    arm_core_udelay(100000);
    gpio_pin_write(GPIO_PIN_PA5, 0);
    arm_systick_delay(1000);
  }
  while (i-- > 0);

  uint32_t uart_events = (UART_EVENT_TRANSMIT | UART_EVENT_RECEIVE | UART_EVENT_OVERRUN);
  uart_create(&uart2, UART_INSTANCE_USART2, &uart2_pins, 10, 0);
  uart_enable(&uart2, &rx_[0], sizeof(rx_), 115200, &uart_callback, UART_NOTIFY_MODE_SINGLE, &uart2, uart_events);
#endif

}
