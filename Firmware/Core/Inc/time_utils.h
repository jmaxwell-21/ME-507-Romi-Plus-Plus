/*
 * time_utils.h
 *
 *  Created on: May 27, 2025
 *      Author: jacka
 */

#ifndef INC_TIME_UTILS_H_
#define INC_TIME_UTILS_H_

/**
 * @file time_utils.h
 * @brief Utility functions for microsecond-level timing.
 * @details Provides lightweight timing utilities based on hardware timers,
 *          useful for precise control loop execution and delay functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f4xx_hal.h>
#include <stdint.h>

/**
 * @brief Returns the number of microseconds since the timer started.
 * @return Elapsed time in microseconds as a 32-bit unsigned integer.
 * @note Requires a configured timer (e.g., TIM2) running at 1 MHz.
 */
uint32_t micros(void);

/**
 * @brief Delays execution for a specified number of microseconds.
 * @param us Delay duration in microseconds.
 * @note Busy-wait implementation; not RTOS-friendly.
 */
void delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* INC_TIME_UTILS_H_ */
