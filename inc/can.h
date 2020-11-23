/*
 * can.h
 *
 *  Created on: Sep 4, 2020
 *      Author: zoltan
 */

#ifndef CAN_H_
#define CAN_H_

#include "stdbool.h"
#include "stddef.h"
#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Bitrate values for 80 mhz sysclk
 */
#define CAN_BITRATE_10_KBPS     0x001c01f3 /*!< prescaler = 499 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_20_KBPS     0x001c00f9 /*!< prescaler = 249 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_50_KBPS     0x001c0031 /*!< prescaler = 049 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_100_KBPS    0x001c0014 /*!< prescaler = 039 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_125_KBPS    0x001c0027 /*!< prescaler = 039 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_250_KBPS    0x001c0014 /*!< prescaler = 019 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_500_KBPS    0x001c0009 /*!< prescaler = 009 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */
#define CAN_BITRATE_1000_KBPS   0x001c0004 /*!< prescaler = 004 | tseg1 = 12 | tseg2 = 1 | sjw = 0 | sample point = 87.5% */

#define CAN_STATE_NONE          0x00
#define CAN_STATE_INIT          0x01
#define CAN_STATE_ERROR         0x02
#define CAN_STATE_BUSY          0x03
#define CAN_STATE_READY         0x04
#define CAN_STATE_TRANSMIT      0x05

#define CAN_EVENT_TRANSMIT_OK   0x01
#define CAN_EVENT_TRANSMIT_ERR  0x02
#define CAN_EVENT_RECEIVE       0x02
#define CAN_EVENT_RECEIVE_FULL  0x04
#define CAN_EVENT_RECEIVE_OVR   0x08
#define CAN_EVENT_BUS_ERROR     0x10

typedef void (*can_callback_t)(void *context, uint32_t event);

typedef struct {
  uint32_t id;
  uint8_t dlc;
  uint8_t data[8];
} can_message_t;

typedef struct {
  uint32_t id_mask;
  uint8_t bank;
  uint8_t mode;
  uint8_t scale;
  uint8_t fifo;
  uint8_t enabled;
} can_filter_t;

typedef struct {
  uint32_t rxd;
  uint32_t txd;
} can_pins_t;

typedef struct {
  CAN_TypeDef *hw;
  can_pins_t pins;
  uint32_t priority;
  volatile uint8_t state;
  uint32_t error;
  can_callback_t callback;
  void *context;
  uint32_t events;
} can_t;

bool can_create(can_t *can, can_pins_t *pins, unsigned int tx_prio, unsigned int rx_prio, unsigned int sce_prio);

bool can_destroy(can_t *can);

bool can_enable(can_t *can, uint32_t bitrate, can_callback_t callback, void *context, uint32_t events);

bool can_disable(can_t *can);

bool can_configure(can_t *can, uint32_t bitrate);

bool can_notify(can_t *can, can_callback_t callback, void *context, uint32_t events);

bool can_receive(can_t *can, can_message_t *msg);

bool can_transmit(can_t *can, can_message_t *msg);

bool can_set_mode(can_t *can, uint32_t mode);

bool can_configure_filter(can_t *can, can_filter_t *filter);

bool can_message_pending(void);

extern void CAN1_TX_IRQHandler(void);
extern void CAN1_RX0_IRQHandler(void);
extern void CAN1_RX1_IRQHandler(void);
extern void CAN1_SCE_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* CAN_H_ */
