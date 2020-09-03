/*
 * fifo.h
 *
 *  Created on: Aug 17, 2020
 *      Author: zdole
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdbool.h"

#include "stm32l4xx.h"

typedef struct {
  void *buffer;
  unsigned int size;
  unsigned int head;
  unsigned int tail;
} fifo_t;

#ifdef __cplusplus
extern "C" {
#endif

void fifo_init(fifo_t *obj, void *buffer, unsigned int size);

void fifo_purge(fifo_t *obj);

unsigned intfifo_write(fifo_t *obj, const void *buffer, unsigned int length);

unsigned intfifo_read(fifo_t *obj, void *buffer, unsigned int length);

unsigned intfifo_irq_write(fifo_t *obj, const void *buffer, unsigned int length);

unsigned intfifo_irq_read(fifo_t *obj, void *buffer, unsigned int length);

bool fifo_is_empty(fifo_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_H_ */
