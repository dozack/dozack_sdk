/*
 * fifo.c
 *
 *  Created on: Aug 17, 2020
 *      Author: zdole
 */

#include "irq.h"
#include "fifo.h"

void fifo_init(fifo_t *obj, void *buffer, uint32_t size) {
    obj->buffer = buffer;
    obj->size = size;
    obj->head = 0;
    obj->tail = 0;
}

void fifo_purge(fifo_t *obj) {
    obj->head = 0;
    obj->tail = 0;
}

uint32_t fifo_write(fifo_t *obj, const void *buffer, uint32_t length) {
    irq_disable();

    for (uint32_t i = 0; i < length; i++) {
        if ((obj->head + 1) == obj->tail) {
            irq_enable();

            return i;
        }

        if (((obj->head + 1) == obj->size) && (obj->tail == 0)) {
            irq_enable();

            return i;
        }

        *((uint8_t *) obj->buffer + obj->head) = *(uint8_t *) buffer;

        buffer = (uint8_t*) buffer+1;

        obj->head++;

        if (obj->head == obj->size) {
            obj->head = 0;
        }
    }

    irq_enable();

    return length;
}

uint32_t fifo_read(fifo_t *obj, void *buffer, uint32_t length) {
    irq_disable();

    for (uint32_t i = 0; i < length; i++) {
        if (obj->tail != obj->head) {
            *(uint8_t*) buffer = *((uint8_t*) obj->buffer + obj->tail);

            buffer = (uint8_t*) buffer+1;

            obj->tail++;

            if (obj->tail == obj->size) {
                obj->tail = 0;
            }
        }
        else {
            irq_enable();

            return i;
        }
    }

    irq_enable();

    return length;
}

uint32_t fifo_irq_write(fifo_t *obj, const void *buffer, uint32_t length) {
    for (size_t i = 0; i < length; i++) {
        if ((obj->head + 1) == obj->tail) {
            return i;
        }

        if (((obj->head + 1) == obj->size) && (obj->tail == 0)) {
            return i;
        }

        *((uint8_t*) obj->buffer + obj->head) = *(uint8_t*) buffer;

        buffer = (uint8_t*) buffer + 1;

        obj->head++;

        if (obj->head == obj->size) {
            obj->head = 0;
        }
    }

    return length;
}

uint32_t fifo_irq_read(fifo_t *obj, void *buffer, uint32_t length) {
    for (size_t i = 0; i < length; i++) {
        if (obj->tail != obj->head) {
            *(uint8_t*) buffer = *((uint8_t*) obj->buffer + obj->tail);

            buffer = (uint8_t*) buffer + 1;

            obj->tail++;

            if (obj->tail == obj->size) {
                obj->tail = 0;
            }
        }
        else {
            return i;
        }
    }
    return length;
}

bool fifo_is_empty(fifo_t *obj){
    irq_disable();

    bool result = obj->tail == obj->head;

    irq_enable();
}
