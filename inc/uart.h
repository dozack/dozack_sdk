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

/**
 * @addtogroup  uart uart
 *              Peripheral API for Universal asynchronous receiver / transmitter.
 * @{
 */

/**
 * @brief   Enum containing all available UART peripherals.
 */
enum {
  UART_INSTANCE_USART1 = 0, /*<! USART1 */
  UART_INSTANCE_USART2, /*<! USART2 */
  UART_INSTANCE_USART3, /*<! USART3 */
  UART_INSTANCE_UART4, /*<! UART4 */
  UART_INSTANCE_UART5, /*<! UART5 */
  UART_INSTANCE_LPUART1, /*<! LPUART1 */
  UART_INSTANCE_COUNT /*<! Number of all available peripherals (used for lookup tables). */
};

/*
 * @cond
 */
#if 0
#define UART_MODE_TX_DMA             0x01
#define UART_MODE_RX_DMA             0x02
#endif
/**
 * @endcond
 */

#define UART_NOTIFY_MODE_SINGLE      0x01
#define UART_NOTIFY_MODE_CHUNK       0x02
#define UART_NOTIFY_CHUNK_SIZE		   0x10

#define UART_EVENT_IDLE              0x01
#define UART_EVENT_NOISE             0x02
#define UART_EVENT_PARITY            0x04
#define UART_EVENT_FRAMING           0x08
#define UART_EVENT_OVERRUN           0x10
#define UART_EVENT_TIMEOUT           0x20
#define UART_EVENT_RECEIVE           0x40
#define UART_EVENT_TRANSMIT          0x80

#define UART_STATE_NONE              0x00
#define UART_STATE_INIT              0x01
#define UART_STATE_BUSY              0x02
#define UART_STATE_READY             0x03
#define UART_STATE_TRANSMIT          0x04
#define UART_STATE_BREAK             0x05

/**
 * @brief   Callback function type definition.
 */
typedef void (*uart_callback_t)(void *notify_context, uint32_t notify_events);

/**
 * @brief   Structure containing GPIO pin information for UART peripheral.
 */
typedef struct {
  uint16_t rx;
  uint16_t tx;
} uart_pins_t;

/**
 * @brief   Peripheral handle structure
 */
typedef struct {
  USART_TypeDef *hw; /*!< Peripheral memory map. */
  uart_pins_t pins; /*!< Structure with pin configuration. */
  volatile uint8_t state; /*!< Actual state of instance. */
  uint8_t instance; /*!< Index of instance. */
  uint8_t interrupt; /*!< Interrupt index for async transfer. */
  uint8_t priority; /*!< Interrupt priority. */
  uint8_t mode; /*!< Reserved. */
  uint8_t notify_mode; /*!< Notify mode of reception routine. */
  void *notify_context; /*!< Optional callback context. */
  uart_callback_t notify_callback; /*!< Pointer to callback function. */
  volatile uint32_t notify_events; /*!< Notify event filter. */
  const uint8_t *tx_data; /*!< Pointer to data for transmission. */
  uint16_t tx_count; /*!< Number of bytes to transfer. */
  uint8_t *rx_data; /*!< Pointer to buffer for reception. */
  uint16_t tx_done; /*!< Number of transmitted bytes. */
  uint16_t rx_size; /*!< Size of reception buffer. */
  volatile uint16_t rx_done; /*!< Number of received bytes in buffer. */
  uint16_t event_count; /*!< Event counter */
} uart_t;

/**
 * @brief   Create UART instance and assign given values.
 * @param   Pointer to UART structure.
 * @param   Instance index (determine hardware UART channel).
 * @param   Pointer to structure with assigned pins.
 * @param   Interrupt priority for asynchronous transfer.
 * @param   Reserved for future functionality
 * @return  False if wrong instance is selected.
 */
bool uart_create(uart_t *uart, unsigned int instance, const uart_pins_t *pins, unsigned int priority, unsigned int mode);

/**
 * @brief   Get rid of UART instance.
 * @param   Pointer to UART structure.
 * @return  False if instance is busy.
 */
bool uart_destroy(uart_t *uart);

/**
 * @brief   Enable UART instance and initialize it.
 * @param   Pointer to UART structure.
 * @param   Pointer to receive buffer.
 * @param   Receive buffer size in bytes.
 * @param   Communication bitrate.
 * @param   User callback for event processing.
 * @param   Optional - Byte reception callback mode (default UART_NOTIFY_MODE_HALF).
 * @param   Optional callback arg (set to NULL in not used).
 * @param   Event filter setting events triggering notification.
 * @return  True if successfuly executed.
 */
bool uart_enable(uart_t *uart, uint8_t *rxd, uint16_t rxs, uint32_t btr, uart_callback_t cb, uint8_t mode, void *ctx, uint32_t ev);

/**
 * @brief   Disable current instance and deinitialize peripheral.
 * @param   Pointer to UART structure.
 * @return  False if instance is busy.
 */
bool uart_disable(uart_t *uart);

/**
 * @brief   Configure UART peripheral (called in uart_enable(), do not use if possible).
 * @param   Pointer to UART structure.
 * @param   Communication bitrate.
 * @return  True if successfuly executed.
 */
bool uart_configure(uart_t *uart, uint32_t btr);

/**
 * @brief   Register callback, its mode and arguments to instance.
 * @param   Pointer to UART structure.
 * @param   Optional - Byte reception callback mode.
 * @param   User callback for event processing.
 * @param   Optional callback arg..
 * @param   Event callback arg stores which event triggered callback.
 * @return  True if successfuly executed.
 */
bool uart_notify(uart_t *uart, unsigned int mode, uart_callback_t cb, void *context, uint32_t events);

/**
 * @brief   Read bytes from instance buffer
 * @todo    Currently supports receiving reading less or same number of available bytes.
 *          Implement partial data reading (for example if 8 bytes are read and only 4 available, return those 4).
 * @param   Pointer to UART structure.
 * @param   Pointer to data target.
 * @param   Number of bytes to read.
 * @return  Number of bytes read.
 */
unsigned int uart_receive(uart_t *uart, uint8_t *rxd, uint16_t rx_count);

/**
 * @brief   Gets number of available bytes in read buffer
 * @param   Pointer to UART structure.
 * @return  Number of bytes available for reading.
 */
unsigned int uart_count(uart_t *uart);

/**
 * @brief   Non blocking trasmission of data (using interrupts).
 * @param   Pointer to UART structure.
 * @param   Pointer to transmit buffer.
 * @param   Number of bytes to transmit.
 * @return  True if successfuly registered data transmit.
 */
bool uart_transmit_it(uart_t *uart, const uint8_t *tx_data, uint16_t tx_count);

/**
 * @brief   Blocking trasmission of data
 * @todo    Implement this function. :)
 * @param   Pointer to UART structure.
 * @param   Pointer to transmit buffer.
 * @param   Number of bytes to transmit.
 * @param   Timeout in ticks.
 * @return  True if successfuly registered data transmit.
 */
bool uart_transmit_blocking(uart_t *uart, const uint8_t *tx_data, uint16_t tx_count, uint32_t timeout_ticks);

/**
 * @brief   Checks if UART is not busy.
 * @param   Pointer to UART structure.
 * @return  True if no reception or transmit ongoing.
 */
bool uart_ready(uart_t *uart);

/**
 * @brief   Poll UART service, programmatically triggers peripheral interrupt handler.
 * @param   Pointer to UART structure.
 * @return  None
 */
void uart_poll(uart_t *uart);

/**
 * @}
 */

extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void USART3_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void UART5_IRQHandler(void);
extern void LPUART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* UART_H_ */
