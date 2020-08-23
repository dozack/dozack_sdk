/*
 * uart.h
 *
 *  Created on: Aug 18, 2020
 *      Author: zdole
 */

#ifndef UART_H_
#define UART_H_

#include "stdbool.h"

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    UART_INSTANCE_USART1 = 0,
    UART_INSTANCE_USART2,
    UART_INSTANCE_USART3,
    UART_INSTANCE_UART4,
    UART_INSTANCE_UART5,
    UART_INSTANCE_LPUART1,
    UART_INSTANCE_COUNT
};

#if 0
#define UART_MODE_TX_DMA             0x00000001
#define UART_MODE_RX_DMA             0x00000002
#define UART_MODE_TX_DMA_SECONDARY   0x00000004
#define UART_MODE_RX_DMA_SECONDARY   0x00000008
#endif

#define UART_OPTION_STOP_MASK        0x0000000f
#define UART_OPTION_STOP_SHIFT       0
#define UART_OPTION_STOP_1           0x00000000
#define UART_OPTION_STOP_1_5         0x00000001
#define UART_OPTION_STOP_2           0x00000002

#define UART_OPTION_PARITY_MASK      0x000000f0
#define UART_OPTION_PARITY_SHIFT     4
#define UART_OPTION_PARITY_NONE      0x00000000
#define UART_OPTION_PARITY_ODD       0x00000010
#define UART_OPTION_PARITY_EVEN      0x00000020

#define UART_OPTION_DATA_SIZE_MASK   0x00000f00
#define UART_OPTION_DATA_SIZE_SHIFT  8
#define UART_OPTION_DATA_SIZE_7      0x00000000
#define UART_OPTION_DATA_SIZE_8      0x00000100
#define UART_OPTION_DATA_SIZE_9      0x00000200

#define UART_OPTION_CTS              0x00001000
#define UART_OPTION_RTS              0x00002000
#define UART_OPTION_DE_MODE          0x00004000
#define UART_OPTION_DE_ACTIVE_LOW    0x00000000
#define UART_OPTION_DE_ACTIVE_HIGH   0x00008000
#define UART_OPTION_LIN_MODE         0x00010000
#define UART_OPTION_LIN_BREAK_SHORT  0x00000000
#define UART_OPTION_LIN_BREAK_LONG   0x00020000
#define UART_OPTION_HALF_DUPLEX_MODE 0x00040000
#define UART_OPTION_RX_INVERT        0x00080000
#define UART_OPTION_TX_INVERT        0x00100000
#define UART_OPTION_DATA_INVERT      0x00200000

#define UART_EVENT_IDLE              0x00000001
#define UART_EVENT_BREAK             0x00000002
#define UART_EVENT_NOISE             0x00000004
#define UART_EVENT_PARITY            0x00000008
#define UART_EVENT_FRAMING           0x00000010
#define UART_EVENT_OVERRUN           0x00000020
#define UART_EVENT_TIMEOUT           0x20000000
#define UART_EVENT_RECEIVE           0x40000000
#define UART_EVENT_TRANSMIT          0x80000000

typedef void (*uart_callback_t)(void *context, uint32_t events);

#define UART_STATE_NONE              0
#define UART_STATE_INIT              1
#define UART_STATE_BUSY              2
#define UART_STATE_READY             3
#define UART_STATE_TRANSMIT          4
#define UART_STATE_BREAK             5

typedef struct {
    uint16_t rx;
    uint16_t tx;
    uint16_t cts;
    uint16_t rts_de;
} uart_pins_t;

typedef struct {
    USART_TypeDef *hw;
    volatile uint8_t state;
    uint8_t instance;
    uint8_t interrupt;
    uint8_t priority;
    uint8_t mode;
    uart_pins_t pins;
    uart_callback_t callback;
    void *context;
    volatile uint32_t events;
    const uint8_t *tx_data;
    uint16_t tx_count;
    volatile uint16_t tx_size;
    uint8_t rx_fifo[16];
    uint8_t *rx_data;
    uint16_t rx_size;
    uint16_t rx_read;
    uint16_t rx_write;
    uint16_t rx_index;
    uint16_t rx_event;
    volatile uint32_t rx_count;
/* TODO - DMA transfer */
} uart_t;

bool uart_init(uart_t *uart, unsigned int instance, const uart_pins_t *pins, unsigned int priority, unsigned int mode);
bool uart_deinit(uart_t *uart);
bool uart_enable(uart_t *uart, uint8_t *rx_data, uint16_t rx_size, uint32_t btr, uint32_t opt, uart_callback_t cb, void *ctx, uint32_t ev);
bool uart_disable(uart_t *uart);
bool uart_configure(uart_t *uart, uint32_t btr, uint32_t opt);
bool uart_notify(uart_t *uart, uart_callback_t cb, void *context, uint32_t events);
unsigned int uart_receive(uart_t *uart, uint8_t *rx_data, uint16_t rx_count);
unsigned int uart_count(uart_t *uart);
int uart_check(uart_t *uart);
bool uart_transmit(uart_t *uart, const uint8_t *tx_data, uint16_t tx_count);
bool uart_send_break(uart_t *uart);
bool uart_done(uart_t *uart);
void uart_poll(uart_t *uart);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
