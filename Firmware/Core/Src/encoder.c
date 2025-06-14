/*
 * encoder.c
 *
 *  Created on: May 27, 2025
 *      Author: jacka
 */

#include "encoder.h"

/**
 * @brief Initializes the encoder structure and starts the hardware timer.
 * @param encoder Pointer to encoder structure to initialize.
 * @param htim Pointer to a TIM_HandleTypeDef configured in encoder mode.
 */
void encoder_init(encoder_t *encoder, TIM_HandleTypeDef *htim) {
    encoder->htim = htim;
    encoder->last_count = 0;
    encoder->position = 0;
    encoder->last_time_us = micros();
    encoder->delta = 0;
    encoder->speed_cps = 0.0f;

    HAL_TIM_Encoder_Start(encoder->htim, TIM_CHANNEL_ALL);
}

/**
 * @brief Updates the encoder's delta, position, and speed.
 * @details Computes the count delta between updates and handles overflow.
 *          Speed is calculated in counts per second (CPS).
 * @param encoder Pointer to encoder structure to update.
 */
void encoder_update(encoder_t *encoder) {
    int32_t new_count = (int32_t)__HAL_TIM_GET_COUNTER(encoder->htim);
    uint32_t now = micros();
    int32_t delta = new_count - encoder->last_count;

    // Handle 16-bit counter overflow
    if (delta > 32767) delta -= 65536;
    else if (delta < -32768) delta += 65536;

    encoder->delta = delta;
    encoder->position += delta;

    uint32_t dt_us = now - encoder->last_time_us;
    if (dt_us > 0) {
        encoder->speed_cps = ((float)delta * 1e6f) / (float)dt_us;
    }

    encoder->last_count = new_count;
    encoder->last_time_us = now;
}

/**
 * @brief Retrieves the current encoder position in counts.
 * @param encoder Pointer to encoder structure.
 * @return Current position in encoder counts.
 */
int32_t encoder_getposition(encoder_t *encoder) {
    return encoder->position;
}

/**
 * @brief Retrieves the most recent delta count.
 * @param encoder Pointer to encoder structure.
 * @return Count difference since the last update.
 */
int32_t encoder_getdelta(encoder_t *encoder) {
    return encoder->delta;
}

/**
 * @brief Retrieves the calculated speed in counts per second.
 * @param encoder Pointer to encoder structure.
 * @return Speed in counts per second (CPS).
 */
float encoder_getspeed(encoder_t *encoder) {
    return encoder->speed_cps;
}

/**
 * @brief Resets the encoder's position, delta, and speed.
 * @param encoder Pointer to encoder structure.
 */
void encoder_reset(encoder_t *encoder) {
    encoder->last_count = 0;
    encoder->position = 0;
    encoder->last_time_us = micros();
    encoder->delta = 0;
    encoder->speed_cps = 0.0f;
    __HAL_TIM_SET_COUNTER(encoder->htim, 0);
}
