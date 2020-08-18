/*
 * fifo.h
 *
 *  Created on: Aug 17, 2020
 *      Author: zdole
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "common.h"

typedef struct {
    void *buffer;

    uint32_t size;

    uint32_t head;

    uint32_t tail;
} fifo_t;

#ifdef __cplusplus
extern "C" {
#endif

void fifo_init(fifo_t *obj, void *buffer, uint32_t size);

void fifo_purge(fifo_t *obj);

uint32_t fifo_write(fifo_t *obj, const void *buffer, uint32_t length);

uint32_t fifo_read(fifo_t *obj, void *buffer, uint32_t length);

uint32_t fifo_irq_write(fifo_t *obj, const void *buffer, uint32_t length);

uint32_t fifo_irq_read(fifo_t *obj, void *buffer, uint32_t length);

bool fifo_is_empty(fifo_t *obj);

#ifdef __cplusplus
}
#endif

#endif /* FIFO_H_ */
