/*
 * encoder.h
 *
 *  Created on: May 27, 2025
 *      Author: jacka
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

/**
 * @file encoder.h
 * @brief Quadrature encoder interface for STM32 timers.
 * @details Provides data structures and functions for tracking position, velocity,
 *          and delta counts using hardware timers configured in encoder mode.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "time_utils.h"
#include <stm32f4xx_hal.h>

/**
 * @struct encoder_t
 * @brief Structure for tracking encoder state and motion data.
 * @details Contains hardware timer reference, historical state, and
 *          calculated speed in counts per second (CPS).
 */
typedef struct {
    TIM_HandleTypeDef *htim;  /**< Pointer to hardware timer configured for encoder mode */
    int32_t last_count;       /**< Previous timer counter value */
    int32_t position;         /**< Cumulative position in encoder counts */
    uint32_t last_time_us;    /**< Timestamp of last update in microseconds */
    int32_t delta;            /**< Count delta since last update */
    float speed_cps;          /**< Calculated speed in counts per second */
} encoder_t;

/**
 * @brief Initializes an encoder structure with a given timer.
 * @param encoder Pointer to encoder structure.
 * @param htim Pointer to initialized TIM_HandleTypeDef configured for encoder mode.
 */
void encoder_init(encoder_t *encoder, TIM_HandleTypeDef *htim);

/**
 * @brief Updates the encoder's internal position, delta, and speed.
 * @param encoder Pointer to encoder structure.
 */
void encoder_update(encoder_t *encoder);

/**
 * @brief Returns the current position (accumulated counts) of the encoder.
 * @param encoder Pointer to encoder structure.
 * @return Signed 32-bit position count.
 */
int32_t encoder_getposition(encoder_t *encoder);

/**
 * @brief Returns the most recent change in encoder count.
 * @param encoder Pointer to encoder structure.
 * @return Signed 32-bit count delta since last update.
 */
int32_t encoder_getdelta(encoder_t *encoder);

/**
 * @brief Returns the current speed in counts per second.
 * @param encoder Pointer to encoder structure.
 * @return Speed in CPS (counts per second).
 */
float encoder_getspeed(encoder_t *encoder);

/**
 * @brief Resets encoder position and delta tracking.
 * @param encoder Pointer to encoder structure.
 */
void encoder_reset(encoder_t *encoder);

#ifdef __cplusplus
}
#endif

#endif /* INC_ENCODER_H_ */
