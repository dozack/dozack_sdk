/*
 * rtc.h
 *
 *  Created on: Aug 22, 2020
 *      Author: zdole
 */

#ifndef RTC_H_
#define RTC_H_

#include "stm32l4xx.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RTC_TIME_MASK_SECOND     0x0001
#define RTC_TIME_MASK_MINUTE     0x0002
#define RTC_TIME_MASK_HOUR       0x0004
#define RTC_TIME_MASK_DAY        0x0008
#define RTC_TIME_MASK_MONTH      0x0010
#define RTC_TIME_MASK_YEAR       0x0020

typedef struct {
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t ticks;
} rtc_time_t;

typedef struct {
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint16_t ticks;
} rtc_sync_t;

typedef void (*rtc_callback_t)(void *context);

void rtc_configure(unsigned int priority);
void rtc_set_time(unsigned int mask, const rtc_time_t *ptime);
void rtc_get_time(rtc_time_t *ptime);
void rtc_get_sync(rtc_sync_t *psync);
void rtc_wakeup(uint32_t timeout);
void rtc_on_sync(rtc_callback_t callback, void *context);
void rtc_write_backup(unsigned int index, uint32_t data);
uint32_t rtc_read_backup(unsigned int index);

#ifdef __cplusplus
}
#endif

#endif /* RTC_H_ */
