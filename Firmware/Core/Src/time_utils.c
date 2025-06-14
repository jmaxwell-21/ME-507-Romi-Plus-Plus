/*
 * time_utils.c
 *
 *  Created on: May 27, 2025
 *      Author: jacka
 */

#include "time_utils.h"

/// @brief Timer handle for microsecond-level timing (typically TIM2).
extern TIM_HandleTypeDef htim2;

/**
 * @brief Returns the number of microseconds since TIM2 was started.
 * @details Reads the current counter value from the TIM2 peripheral.
 * @return Current microsecond timestamp as a 32-bit unsigned integer.
 */
uint32_t micros(void) {
    return __HAL_TIM_GET_COUNTER(&htim2);
}

/**
 * @brief Delays the program execution for a specified number of microseconds.
 * @param us Number of microseconds to delay.
 * @details Uses a busy-wait loop based on the `micros()` counter.
 * @note Not suitable for power-sensitive applications or inside ISRs.
 */
void delay_us(uint32_t us) {
    uint32_t start = micros();
    while ((micros() - start) < us) {
        // Tight loop until target time is reached
    }
}
