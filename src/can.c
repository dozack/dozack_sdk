/*
 * can.c
 *
 *  Created on: Sep 5, 2020
 *      Author: zoltan
 */
#include "arm.h"
#include "can.h"
#include "system.h"
#include "gpio.h"

static can_t *_can_driver = NULL;

static uint32_t _can_find_free_mailbox(can_t *can);

static void _can_interrupt(can_t *can) {
  /* Get hardware handle and read status registers */
  CAN_TypeDef *_can = can->hw;
  uint32_t ier = _can->IER;
  uint32_t msr = _can->MSR;
  uint32_t tsr = _can->TSR;
  uint32_t esr = _can->ESR;
  uint32_t f0 = _can->RF0R;
  uint32_t f1 = _can->RF1R;
  uint32_t events = 0;
  if (ier & CAN_IER_TMEIE)
  {
    if (tsr & CAN_TSR_RQCP0)
    {
      _can->TSR = CAN_TSR_RQCP0;
      if (tsr & CAN_TSR_TXOK0)
      {
        events |= CAN_EVENT_TRANSMIT_OK;
      }
      else
      {
        if (tsr & CAN_TSR_ALST0)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
        if (tsr & CAN_TSR_TERR0)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
      }
    }
    if (tsr & CAN_TSR_RQCP1)
    {
      _can->TSR = CAN_TSR_RQCP1;
      if (tsr & CAN_TSR_TXOK1)
      {
        events |= CAN_EVENT_TRANSMIT_OK;
      }
      else
      {
        if (tsr & CAN_TSR_ALST1)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
        if (tsr & CAN_TSR_TERR1)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
      }
    }
    if (tsr & CAN_TSR_RQCP2)
    {
      _can->TSR = CAN_TSR_RQCP2;
      if (tsr & CAN_TSR_TXOK2)
      {
        events |= CAN_EVENT_TRANSMIT_OK;
      }
      else
      {
        if (tsr & CAN_TSR_ALST2)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
        if (tsr & CAN_TSR_TERR2)
        {
          events |= CAN_EVENT_TRANSMIT_ERR;
        }
      }
    }
  }
  if (ier & CAN_IER_FOVIE0)
  {
    if (f0 & CAN_RF0R_FOVR0)
    {
      events |= CAN_EVENT_RECEIVE_OVR;
      _can->RF0R = CAN_RF0R_FOVR0;
    }
  }
  if (ier & CAN_RF0R_FULL0)
  {
    if (f0 & CAN_RF0R_FULL0)
    {
      events |= CAN_EVENT_RECEIVE_FULL;
      _can->RF0R = CAN_RF0R_FULL0;
    }
  }
  if (ier & CAN_IER_FMPIE0)
  {
    if (f0 % CAN_RF0R_FMP0)
    {
      events |= CAN_EVENT_RECEIVE;
    }
  }
  if (ier & CAN_IER_FOVIE1)
  {
    if (f1 & CAN_RF1R_FOVR1)
    {
      events |= CAN_EVENT_RECEIVE_OVR;
      _can->RF0R = CAN_RF1R_FOVR1;
    }
  }
  if (ier & CAN_RF1R_FULL1)
  {
    if (f1 & CAN_RF1R_FULL1)
    {
      events |= CAN_EVENT_RECEIVE_FULL;
      _can->RF0R = CAN_RF1R_FULL1;
    }
  }
  if (ier & CAN_IER_FMPIE1)
  {
    if (f1 % CAN_RF1R_FMP1)
    {
      events |= CAN_EVENT_RECEIVE;
    }
  }
  if (ier & CAN_IER_SLKIE)
  {
    if (msr & CAN_MSR_SLAKI)
    {
      _can->MSR = CAN_MSR_SLAKI;
    }
  }
  if (ier & CAN_IER_WKUIE)
  {
    if (msr & CAN_MSR_WKUI)
    {
      _can->MSR = CAN_MSR_WKUI;
    }
  }
  if (ier & CAN_IER_ERRIE)
  {
    if (msr & CAN_MSR_ERRI)
    {
      if (ier & CAN_IER_EWGIE)
      {
        if (esr & CAN_ESR_EWGF)
        {
          events |= CAN_EVENT_BUS_ERROR;
        }
      }
      if (ier & CAN_IER_EPVIE)
      {
        if (esr & CAN_ESR_EPVF)
        {
          events |= CAN_EVENT_BUS_ERROR;
        }
      }
      if (ier & CAN_IER_BOFIE)
      {
        if (esr & CAN_ESR_BOFF)
        {
          events |= CAN_EVENT_BUS_ERROR;
        }
      }
      if (ier & CAN_IER_LECIE)
      {
        if (esr & CAN_ESR_LEC)
        {
          events |= CAN_EVENT_BUS_ERROR;
          _can->ESR &= ~CAN_ESR_LEC;
        }
      }
      _can->MSR = CAN_MSR_ERRI;
    }
  }
  events &= can->events;
  if (events)
  {
    arm_pendsv_enqueue(can->callback, can, events);
  }
}

bool can_create(can_t *can, can_pins_t *pins, unsigned int tx_prio, unsigned int rx_prio, unsigned int sce_prio) {
  if (_can_driver != NULL)
  {
    return false;
  }
  /* Assign hardware pointer and pins */
  can->hw = CAN;
  can->pins = *pins;
  /* 31:24 - tx_priority | 23:16 - rx0_priority | 15:8 - reserved | 7:0 - sce_priority */
  can->priority = ((tx_prio << 24) | (rx_prio << 16) | sce_prio);
  can->error = 0;
  can->callback = NULL;
  can->context = NULL;
  can->events = 0;
  /* Enter init state enabling usage of handle */
  can->state = CAN_STATE_INIT;
  _can_driver = can;
  return true;
}

bool can_destroy(can_t *can) {
  /* Check if handle is in init state */
  if (can->state != CAN_STATE_INIT)
  {
    return false;
  }
  /* Set handle state to none disabling its functionality */
  can->state = CAN_STATE_NONE;
  _can_driver = NULL;
  return true;
}

bool can_enable(can_t *can, uint32_t bitrate, can_callback_t callback, void *context, uint32_t events) {
  /* Check if handle is in init state */
  if (can->state != CAN_STATE_INIT)
  {
    return false;
  }
  /* Enter busy state for configuration */
  can->state = CAN_STATE_BUSY;
  if (!can_configure(can, bitrate))
  {
    /* Configuration failed, go back to init state */
    can->state = CAN_STATE_INIT;
    return false;
  }
  /* Handle is configured and ready */
  can->state = CAN_STATE_READY;
  /* Assign callback and its arguments */
  if (!(can_notify(can, callback, context, events)))
  {
    return false;
  }
  /* Set interrupt priority and enable irq */
  NVIC_SetPriority(CAN1_RX0_IRQn, ((can->priority >> 16) & 0xff));
  NVIC_SetPriority(CAN1_SCE_IRQn, ((can->priority & 0xff)));
  NVIC_EnableIRQ(CAN1_RX0_IRQn);
  NVIC_EnableIRQ(CAN1_SCE_IRQn);
  return true;
}

bool can_disable(can_t *can) {
  /* Check if handle is in idle state */
  if (can->state != CAN_STATE_READY)
  {
    return false;
  }
  CAN_TypeDef *_can = can->hw;
  /* Reset assigned notify parameters */
  can->callback = NULL;
  can->context = NULL;
  can->events = 0;
  /* Set hardware to init mode */
  _can->MCR |= CAN_MCR_RESET;
  /* Disable interrupts */
  NVIC_DisableIRQ(CAN1_RX0_IRQn);
  NVIC_DisableIRQ(CAN1_RX1_IRQn);
  NVIC_DisableIRQ(CAN1_TX_IRQn);
  NVIC_DisableIRQ(CAN1_SCE_IRQn);
  /* Disable peripheral */
  system_peripheral_disable(SYSTEM_PERIPH_CAN1);
  /* Set pins to analog */
  if (can->pins.rxd != GPIO_PIN_NONE)
  {
    gpio_pin_configure(can->pins.rxd, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  }
  if (can->pins.txd != GPIO_PIN_NONE)
  {
    gpio_pin_configure(can->pins.txd, (GPIO_PUPD_NONE | GPIO_MODE_ANALOG));
  }
  /* Set handle to init state */
  can->state = CAN_STATE_INIT;
  return true;
}

bool can_configure(can_t *can, uint32_t bitrate) {
  if ((can->state != CAN_STATE_READY) && (can->state != CAN_STATE_BUSY))
  {
    return false;
  }
  if (can->state == CAN_STATE_BUSY)
  {
    /* Peripheral is being initialized */
    system_peripheral_enable(SYSTEM_PERIPH_CAN1);
  }
  else
  {
    /* Peripheral is being reconfigured */
    NVIC_DisableIRQ(CAN1_RX0_IRQn);
    NVIC_DisableIRQ(CAN1_RX1_IRQn);
    NVIC_DisableIRQ(CAN1_TX_IRQn);
    NVIC_DisableIRQ(CAN1_SCE_IRQn);
  }
  /* Configure pins */
  if (can->pins.rxd != GPIO_PIN_NONE)
  {
    gpio_pin_configure(can->pins.rxd, (GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
  }
  if (can->pins.txd != GPIO_PIN_NONE)
  {
    gpio_pin_configure(can->pins.txd, (GPIO_PUPD_NONE | GPIO_OSPEED_VERY_HIGH | GPIO_OTYPE_PUSHPULL | GPIO_MODE_ALTERNATE));
  }
  CAN_TypeDef *_can = can->hw;
  uint32_t mcr, timeout;
  timeout = 20000;
  /* Enter initialization mode */
  _can->MCR |= CAN_MCR_INRQ;
  mcr = (CAN_MCR_INRQ | CAN_MCR_NART | (0x1 << 16));
  while (!(_can->MSR & CAN_MSR_INAK) && --timeout);
  /* Configure peripheral registers */
  _can->MCR = mcr;
  _can->BTR = bitrate;
  /* Set global filter with 29-bit id mask to enable reception of all messages */
  can_filter_t global_filter = {
    .bank = 0,
    .fifo = 0,
    .mode = 0,
    .scale = 1,
    .id_mask = 0x1fffffff,
    .enabled = 1 };
  can_configure_filter(can, &global_filter);
  /* Leave inittialization mode */
  _can->MCR &= ~CAN_MCR_INRQ;
  timeout = 20000;
  while ((_can->MSR & CAN_MSR_INAK) && --timeout);
  if (!timeout)
  {
    return false;
  }
  /* Enable peripheral rx interrupts */
  _can->IER |= (CAN_IER_FMPIE0 | CAN_IER_FMPIE1);
  _can->MSR = 0xffffffff;
  return true;
}

bool can_notify(can_t *can, can_callback_t callback, void *context, uint32_t events) {
  if (can->state != CAN_STATE_READY)
  {
    return false;
  }
  CAN_TypeDef *_can = can->hw;
  /* Assign notify parameters */
  can->events = events;
  can->callback = callback;
  can->context = context;
  uint32_t ier = _can->IER;
  /* Configure interrupt events */
  if (can->events & CAN_EVENT_RECEIVE_FULL)
  {
    /* Receive fifo full event */
    ier |= (CAN_IER_FFIE0 | CAN_IER_FFIE1);
  }
  if (can->events & CAN_EVENT_RECEIVE_OVR)
  {
    /* Receive fifo overrun event */
    ier |= (CAN_IER_FOVIE0 | CAN_IER_FOVIE1);
  }
  if (can->events & CAN_EVENT_BUS_ERROR)
  {
    /* All possible error events */
    ier |= (CAN_IER_EWGIE | CAN_IER_EPVIE | CAN_IER_ERRIE | CAN_IER_BOFIE | CAN_IER_LECIE);
  }
  _can->IER = ier;
  return true;
}

bool can_transmit(can_t *can, can_message_t *msg) {
  if (can->state != CAN_STATE_READY)
  {
    return false;
  }
  if (msg == NULL)
  {
    return false;
  }
  uint32_t mailbox = _can_find_free_mailbox(can);
  if (mailbox > 2)
  {
    return false;
  }
  CAN_TypeDef *_can = can->hw;
  if (msg->id > 0x7ff)
  {
    _can->sTxMailBox[mailbox].TIR = (((msg->id) << CAN_TI0R_EXID_Pos) | CAN_TI0R_IDE);
  }
  else
  {
    _can->sTxMailBox[mailbox].TIR = ((msg->id) << CAN_TI0R_STID_Pos);
  }
  uint32_t data_h = ((msg->data[7] << 24) | (msg->data[6] << 16) | (msg->data[5] << 8) | msg->data[4]);
  uint32_t data_l = ((msg->data[3] << 24) | (msg->data[2] << 16) | (msg->data[1] << 8) | msg->data[0]);
  _can->IER |= CAN_IER_TMEIE;
  _can->sTxMailBox[mailbox].TDTR = (msg->dlc & 0xf);
  _can->sTxMailBox[mailbox].TDHR = data_h;
  _can->sTxMailBox[mailbox].TDLR = data_l;
  _can->sTxMailBox[mailbox].TIR |= CAN_TI0R_TXRQ;
  return true;
}

bool can_configure_filter(can_t *can, can_filter_t *filter) {
  if (filter->bank > 13 || filter->fifo > 1)
  {
    return false;
  }
  CAN_TypeDef *_can = can->hw;
  /* Enter filter init mode */
  _can->FMR |= CAN_FMR_FINIT;
  /* Disable selected filter */
  _can->FA1R &= ~(0x1 << filter->bank);
  /* Set filter mode */
  _can->FM1R |= ((filter->mode & 0x1) << filter->bank);
  /* Set filter scale */
  _can->FS1R |= ((filter->scale & 0x1) << filter->bank);
  /* Assign filter to fifo */
  _can->FFA1R |= ((filter->fifo) & 0x1 << filter->bank);
  /* Assign filter ID and mask */
  _can->sFilterRegister[filter->bank].FR1 = filter->id_mask;
  _can->sFilterRegister[filter->bank].FR2 = filter->id_mask;
  /* Enable filter or leave it disabled */
  _can->FA1R |= ((filter->enabled & 0x1) << filter->bank);
  /* Leave filter initialization mode */
  _can->FMR &= ~CAN_FMR_FINIT;
  return true;
}

static uint32_t _can_find_free_mailbox(can_t *can) {
  CAN_TypeDef *_can = can->hw;
  uint32_t tsr = _can->TSR;
  if (tsr & CAN_TSR_TME)
  {
    return ((tsr & CAN_TSR_CODE) >> CAN_TSR_CODE_Pos);
  }
  else
  {
    return 0xff;
  }
}

void CAN1_TX_IRQHandler(void) {
  _can_interrupt(_can_driver);
}

extern void CAN1_RX0_IRQHandler(void) {
  _can_interrupt(_can_driver);
}

extern void CAN1_RX1_IRQHandler(void) {
  _can_interrupt(_can_driver);
}

extern void CAN1_SCE_IRQHandler(void) {
  _can_interrupt(_can_driver);
}
