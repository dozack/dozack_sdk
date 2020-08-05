/*
 * irq.h
 *
 *  Created on: Aug 5, 2020
 *      Author: zdole
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

void irq_disable(void);

void irq_enable(void);

#ifdef __cplusplus
}
#endif

#endif /* IRQ_H_ */
