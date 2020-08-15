/*
 * tests.h
 *
 *  Created on: Aug 4, 2020
 *      Author: zdole
 */

#ifndef TESTS_H_
#define TESTS_H_

#ifdef __cplusplus
extern "C" {
#endif

void tests_run(void);

void tests_system(void);

void tests_exti(void);

void tests_gpio(void);

void tests_scheduler(void);

#ifdef __cplusplus
}
#endif

#endif /* TESTS_H_ */
