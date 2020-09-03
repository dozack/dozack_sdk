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
  LPUART1 };

static const IRQn_Type _uart_IRQn[UART_INSTANCE_COUNT] = {
  USART1_IRQn,
  USART2_IRQn,
  USART3_IRQn,
  UART4_IRQn,
  UART5_IRQn,
  LPUART1_IRQn };

static void _uart_interrupt(uart_t *uart) {
  USART_TypeDef *_uart = uart->hw;
  uint32_t events;
  uint8_t rx_data;
  events = 0;
  /* Byte reception interrupt handler */
  if (_uart->ISR & USART_ISR_RXNE)
  {
    if (_uart->CR1 & USART_CR1_RXNEIE)
    {
      /* Read received byte */
      rx_data = _uart->RDR;
      /* Check if receive buffer is full */
      if (uart->rx_done < uart->rx_size)
      {
        /* Store received byte to receive buffer */
        uart->rx_data[uart->rx_done++] = rx_data;
        /* Check for buffer overflow again */
        if (uart->rx_done >= uart->rx_size)
        {
          /* Reception buffer is full, reset position counter and trigger overrun event */
          uart->rx_done = 0;
          events |= UART_EVENT_OVERRUN;
        }
        if (uart->notify_mode & UART_NOTIFY_MODE_SINGLE)
        {
          /* If UART_NOTIFY_MODE_SINGLE mode is enabled, trigger rx event after every single byte reception */
          events |= UART_EVENT_RECEIVE;
        }
        if (uart->notify_mode & UART_NOTIFY_MODE_CHUNK)
        {
          /* If UART_NOTIFY_MODE_CHUNK mode is enabled, trigger rx event on event counter overflow */
          uart->event_count++;
          if (uart->event_count >= UART_NOTIFY_CHUNK_SIZE)
          {
            uart->event_count = 0;
            events |= UART_EVENT_RECEIVE;
          }
        }
      }
    }
  }
  /* Timeout interrupt handler */
  if (_uart->ISR & USART_ISR_RTOF)
  {
    if (_uart->CR1 & USART_CR1_RTOIE)
    {
      events |= UART_EVENT_TIMEOUT;
    }
    _uart->ICR = USART_ICR_RTOCF;
  }
  /* Byte transmission shift register interrupt handler */
  if (_uart->ISR & USART_ISR_TXE)
  {
    if (_uart->CR1 & USART_CR1_TXEIE)
    {
      uart->tx_done++;
      if (uart->tx_done >= uart->tx_count)
      {
        _uart->CR1 &= ~USART_CR1_TXEIE;
        _uart->CR1 |= USART_CR1_TCIE;
      }
      _uart->TDR = *uart->tx_data++;
    }
  }
  /* Byte transmission complete interrupt handler */
  if (_uart->ISR & USART_ISR_TC)
  {
    _uart->ICR = USART_ICR_TCCF;
    if (_uart->CR1 & USART_CR1_TCIE)
    {
      _uart->CR1 &= ~USART_CR1_TCIE;
      uart->state = UART_STATE_READY;
      events |= UART_EVENT_TRANSMIT;
    }
  }
  /* Other bus flag interrupt handler */
  if (_uart->ISR & (USART_ISR_PE | USART_ISR_FE | USART_ISR_NE | USART_ISR_ORE | USART_ISR_IDLE | USART_ISR_LBDF))
  {
    if (uart->notify_events & (UART_EVENT_IDLE | UART_EVENT_NOISE | UART_EVENT_PARITY | UART_EVENT_FRAMING | UART_EVENT_OVERRUN))
    {
      if (_uart->ISR & USART_ISR_PE)
      {
        events |= UART_EVENT_PARITY;
      }
      if (_uart->ISR & USART_ISR_FE)
      {
        events |= UART_EVENT_FRAMING;
      }
      if (_uart->ISR & USART_ISR_NE)
      {
        events |= UART_EVENT_NOISE;
      }
      if (_uart->ISR & USART_ISR_IDLE)
      {
        events |= UART_EVENT_IDLE;
      }
      if (_uart->ISR & USART_ISR_ORE)
      {
        events |= UART_EVENT_OVERRUN;
      }
    }
    _uart->ICR = (USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NCF | USART_ICR_ORECF | USART_ICR_IDLECF | USART_ICR_LBDCF);
  }
  /* Filter events in actual configuration */
  events &= uart->notify_events;
  /* If some requested events are triggered, jump to callback function */
  if (events)
  {
    (*uart->notify_callback)(uart->notify_context, events);
  }
}

bool uart_create(uart_t *uart, unsigned int instance, const uart_pins_t *pins, unsigned int priority, unsigned int mode) {
  if (instance >= UART_INSTANCE_COUNT)
  {
    return false;
  }
  uart->hw = _uart_USART[instance];
  uart->interrupt = _uart_IRQn[instance];
  uart->priority = priority;
  uart->state = UART_STATE_INIT;
  uart->instance = instance;
  uart->pins = *pins;
  uart->notify_mode = UART_NOTIFY_MODE_SINGLE;
  uart->notify_callback = NULL;
  uart->notify_context = NULL;
  uart->mode = mode;
  uart->notify_events = 0;
  uart->event_count = 0;
  _uart.instances[instance] = uart;
  return true;
}

bool uart_destroy(uart_t *uart) {
  if (uart->state != UART_STATE_INIT)
  {
    return false;
  }
  _uart.instances[uart->instance] = NULL;
  uart->state = UART_STATE_NONE;
  return true;
}

bool uart_enable(uart_t *uart, uint8_t *rx_data, uint16_t rx_size, uint32_t btr, uart_callback_t cb, uint8_t mode, void *ctx, uint32_t ev) {
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
  uart->rx_done = 0;
  if (uart->instance != UART_INSTANCE_LPUART1)
  {
    system_hsi16_enable();
  }
  switch (uart->instance)
  {
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
  if (!uart_configure(uart, btr))
  {
    uart->state = UART_STATE_INIT;
    return false;
  }
  uart->state = UART_STATE_READY;
  uart_notify(uart, mode, cb, ctx, ev);
  NVIC_SetPriority(uart->interrupt, uart->priority);
  NVIC_EnableIRQ(uart->interrupt);
  return true;
}

bool uart_disable(uart_t *uart) {
  USART_TypeDef *_uart = uart->hw;
  if (uart->state != UART_STATE_READY)
  {
    return false;
  }
  uart->notify_events = 0;
  uart->notify_callback = NULL;
  uart->notify_context = NULL;
  _uart->CR1 = 0;
  NVIC_DisableIRQ(uart->interrupt);
  system_peripheral_disable(SYSTEM_PERIPH_USART1 + uart->instance);
  if (uart->instance != UART_INSTANCE_LPUART1)
  {
    system_hsi16_disable();
  }
  if (uart->pins.rx != GPIO_PIN_NONE)
  {
    gpio_pin_configure(uart->pins.rx, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  }
  if (uart->pins.tx != GPIO_PIN_NONE)
  {
    gpio_pin_configure(uart->pins.tx, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  }
  uart->state = UART_STATE_INIT;
  return true;
}

bool uart_configure(uart_t *uart, uint32_t btr) {
  USART_TypeDef *_uart = uart->hw;
  uint32_t cr1, cr2, cr3;
  if ((uart->state != UART_STATE_READY) && (uart->state != UART_STATE_BUSY))
  {
    return false;
  }
  if (btr == 0 || (btr > 9600 && uart->instance == UART_INSTANCE_LPUART1) || (btr > 921600 && uart->instance != UART_INSTANCE_LPUART1))
  {
    return false;
  }
  if (uart->state == UART_STATE_BUSY)
  {
    system_peripheral_enable(SYSTEM_PERIPH_USART1 + uart->instance);
  }
  else
  {
    NVIC_DisableIRQ(uart->interrupt);
  }
  _uart->CR1 = 0;
  cr1 = 0;
  cr2 = 0;
  cr3 = 0;
  if (uart->instance == UART_INSTANCE_LPUART1)
  {
    _uart->BRR = (256 * 32768 + (btr >> 1)) / btr;
  }
  else
  {
    _uart->BRR = ((16000000 + (btr >> 1)) / btr);
  }
  if (uart->pins.tx != GPIO_PIN_NONE)
  {
    gpio_pin_configure(uart->pins.tx, (GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
    cr1 |= USART_CR1_TE;
  }
  if (uart->pins.rx != GPIO_PIN_NONE)
  {
    gpio_pin_configure(uart->pins.rx, (GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
    cr1 |= (USART_CR1_RE | USART_CR1_RXNEIE);
#if 0
        cr1 |= (USART_CR1_RTOIE);
        cr2 |= USART_CR2_RTOEN;
        _uart->RTOR = 32;
#endif
  }
  if (cr1 & USART_CR1_RE)
  {
    if (uart->notify_events & UART_EVENT_IDLE)
    {
      cr1 |= USART_CR1_IDLEIE;
    }

    if (uart->notify_events & (UART_EVENT_OVERRUN | UART_EVENT_FRAMING | UART_EVENT_NOISE))
    {
      cr3 |= USART_CR3_EIE;
    }
  }
  _uart->CR3 = cr3;
  _uart->CR2 = cr2;
  _uart->CR1 = cr1 | USART_CR1_UE;
  _uart->RQR = USART_RQR_RXFRQ;
  _uart->ICR = (USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NCF | USART_ICR_ORECF | USART_ICR_IDLECF | USART_ICR_LBDCF);
  if (uart->state == UART_STATE_READY)
  {
    NVIC_EnableIRQ(uart->interrupt);
  }
  return true;
}

bool uart_notify(uart_t *uart, unsigned int mode, uart_callback_t cb, void *context, uint32_t events) {
  USART_TypeDef *_uart = uart->hw;
  if (uart->state != UART_STATE_READY)
  {
    return false;
  }
  uart->notify_mode = mode;
  uart->notify_events = events;
  uart->notify_callback = cb;
  uart->notify_context = context;
  if (_uart->CR1 & USART_CR1_RE)
  {
    if (uart->notify_events & UART_EVENT_IDLE)
    {
      _uart->CR1 |= USART_CR1_IDLEIE;
    }
    else
    {
      _uart->CR1 &= ~USART_CR1_IDLEIE;
    }

    if (uart->notify_events & (UART_EVENT_OVERRUN | UART_EVENT_FRAMING | UART_EVENT_NOISE))
    {
      _uart->CR3 |= USART_CR3_EIE;
    }
    else
    {
      _uart->CR3 &= ~USART_CR3_EIE;
    }
  }
  return true;
}

unsigned int uart_receive(uart_t *uart, uint8_t *rx_data, uint16_t rx_count) {
  if (uart->state < UART_STATE_READY)
  {
    return -1;
  }
  if (rx_count > uart->rx_done)
  {
    /* TODO - return all available bytes and set new buffer index */
    return -1;
  }
  else
  {
    /* Return requested number of bytes and set new buffer index */
    memcpy(rx_data, &uart->rx_data[(uart->rx_done - rx_count)], rx_count);
    uart->rx_done -= rx_count;
    return rx_count;
  }
}

unsigned int uart_count(uart_t *uart) {
  if (uart->state < UART_STATE_READY)
  {
    return 0;
  }
  return uart->rx_done;
}

bool uart_transmit_it(uart_t *uart, const uint8_t *tx_data, uint16_t tx_count) {
  USART_TypeDef *_uart = uart->hw;
  if (uart->state != UART_STATE_READY)
  {
    return false;
  }
  uart->state = UART_STATE_TRANSMIT;
  _uart->TDR = *tx_data++;
  uart->tx_data = tx_data;
  uart->tx_count = tx_count;
  uart->tx_done = 1;
  if (uart->tx_done == uart->tx_count)
  {
    /* Enable Transfer Complete interrupt for single byte */
    _uart->CR1 |= USART_CR1_TCIE;
  }
  else
  {
    /* Enable TX Empty interrupt for multiple byte transmission */
    _uart->CR1 |= USART_CR1_TXEIE;
  }
  return true;
}

bool uart_ready(uart_t *uart) {
  return (uart->state == UART_STATE_READY);
}

void uart_poll(uart_t *uart) {
  if (uart->state >= UART_STATE_READY)
  {
    _uart_interrupt(uart);
  }
}

void USART1_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_USART1]);
}

void USART2_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_USART2]);
}

void USART3_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_USART3]);
}

void UART4_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_UART4]);
}

void UART5_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_UART5]);
}

void LPUART1_IRQHandler(void) {
  _uart_interrupt(_uart.instances[UART_INSTANCE_LPUART1]);
}

