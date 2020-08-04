/**
 * @file system.h
 * @date Jul 21, 2020
 * @author Zoltan Dolensky
 * @brief 
 */
#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    SYSTEM_CLOCK_MSI = 0,
    SYSTEM_CLOCK_HSI,
    SYSTEM_CLOCK_PLL
} system_clock_t;

system_clock_t system_get_clock_source (void);
uint32_t system_get_clock_frequency (void);
void system_init (void);
void system_hsi16_enable (void);
void system_hsi16_disable (void);
void system_pll_enable (void);
void system_pll_disable (void);
void system_reset (void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_H_ */
