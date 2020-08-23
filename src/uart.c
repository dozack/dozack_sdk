#include "stdio.h"
#include "string.h"

#include "uart.h"
#include "gpio.h"
#include "system.h"

typedef struct {
    uart_t *instances[UART_INSTANCE_COUNT];
} uart_driver_t;

static uart_driver_t _uart;

static USART_TypeDef *const _uart_USART[UART_INSTANCE_COUNT] = {
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    LPUART1};

static const IRQn_Type _uart_IRQn[UART_INSTANCE_COUNT] = {
    USART1_IRQn,
    USART2_IRQn,
    USART3_IRQn,
    UART4_IRQn,
    UART5_IRQn,
    LPUART1_IRQn, };

static void _uart_interrupt(uart_t *uart) {
    USART_TypeDef *_uart = uart->hw;
    uint32_t events, rx_index, rx_count, rx_total, rx_size, rx_write;
    uint8_t rx_data;
    events = 0;
}

bool uart_init(uart_t *uart, unsigned int instance, const uart_pins_t *pins, unsigned int priority, unsigned int mode) {
    if (instance >= UART_INSTANCE_COUNT)
    {
        return false;
    }
    uart->hw = _uart_USART[instance];
    uart->state = UART_STATE_INIT;
    uart->instance = instance;
    uart->interrupt = _uart_IRQn[instance];
    uart->priority = priority;
    uart->pins = *pins;
    uart->callback = NULL;
    uart->context = NULL;
    uart->events = 0;
    uart->mode = mode;
    _uart.instances[instance] = uart;
    return true;

}

bool uart_deinit(uart_t *uart) {
    if (uart->state != UART_STATE_INIT)
    {
        return false;
    }
    _uart.instances[uart->instance] = NULL;
    uart->state = UART_STATE_NONE;
    return true;
}

bool uart_enable(uart_t *uart, uint8_t *rx_data, uint16_t rx_size, uint32_t btr, uint32_t opt, uart_callback_t cb, void *ctx, uint32_t ev) {
    if (uart->state != UART_STATE_INIT)
    {
        return false;
    }
    if ((rx_data == NULL) || (rx_size < 16))
    {
        return false;
    }
    uart->rx_data = rx_data;
    uart->rx_size = rx_size;
    uart->rx_read = 0;
    uart->rx_write = 0;
    uart->rx_index = 0;
    uart->rx_event = 0;
    uart->rx_count = 0;
    if (uart->instance != UART_INSTANCE_LPUART1)
    {
        system_hsi16_enable();
    }
    switch (uart->instance) {
        case UART_INSTANCE_USART1:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_USART1SEL) | RCC_CCIPR_USART1SEL_1);
            break;
        case UART_INSTANCE_USART2:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_USART2SEL) | RCC_CCIPR_USART2SEL_1);
            break;
        case UART_INSTANCE_USART3:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_USART3SEL) | RCC_CCIPR_USART3SEL_1);
            break;
        case UART_INSTANCE_UART4:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_UART4SEL) | RCC_CCIPR_UART4SEL_1);
            break;
        case UART_INSTANCE_UART5:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_UART5SEL) | RCC_CCIPR_UART5SEL_1);
            break;
        case UART_INSTANCE_LPUART1:
            RCC->CCIPR = ((RCC->CCIPR & ~RCC_CCIPR_USART1SEL) | (RCC_CCIPR_LPUART1SEL_0 | RCC_CCIPR_LPUART1SEL_1));
            break;
        default:
            return false;
    }
    uart->state = UART_STATE_BUSY;
    if (!uart_configure(uart, btr, opt))
    {
        uart->state = UART_STATE_INIT;
        return false;
    }
    uart->state = UART_STATE_READY;
    uart_notify(uart, cb, ctx, ev);
    NVIC_SetPriority(uart->interrupt, uart->priority);
    NVIC_EnableIRQ(uart->interrupt);
    return true;
}

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

