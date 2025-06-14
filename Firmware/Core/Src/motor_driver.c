/*
 * motor_driver.c
 *
 *  Created on: Apr 17, 2025
 *      Author: jacka
 */

#include "motor_driver.h"

/// @brief Threshold below which motor effort is ignored (to overcome stiction).
#define MOTOR_DEADZONE_PWM 300

/**
 * @brief Enables both PWM channels for the motor.
 * @param p_mot Pointer to motor object to enable.
 * @details Starts the timer's PWM outputs on the assigned motor channels.
 */
void motor_enable(motor_t* p_mot) {
	HAL_TIM_PWM_Start(p_mot->htim, p_mot->ch_A);  // Start Timer Channel A
	HAL_TIM_PWM_Start(p_mot->htim, p_mot->ch_B);  // Start Timer Channel B
}

/**
 * @brief Disables both PWM channels for the motor.
 * @param p_mot Pointer to motor object to disable.
 * @details Stops the timer's PWM outputs on the assigned motor channels.
 */
void motor_disable(motor_t* p_mot) {
	HAL_TIM_PWM_Stop(p_mot->htim, p_mot->ch_A);   // Stop Timer Channel A
	HAL_TIM_PWM_Stop(p_mot->htim, p_mot->ch_B);   // Stop Timer Channel B
}

/**
 * @brief Sets the PWM duty cycle for a motor.
 * @param p_mot Pointer to motor object.
 * @param duty Signed value representing the duty cycle (positive = forward, negative = reverse).
 * @details Saturates the input duty cycle to match the timer auto-reload (ARR) value.
 *          Enforces a deadzone below which effort is ignored. Uses two complementary
 *          PWM channels to drive H-bridge outputs.
 */
void motor_set_duty(motor_t* p_mot, int32_t duty) {
    // Get the auto-reload value (ARR) for max PWM range
    int32_t AR = p_mot->htim->Init.Period;

    // Clamp duty cycle to valid range [-AR, AR]
    if (duty > AR) duty = AR;
    if (duty < -AR) duty = -AR;

    // Deadzone filtering
    int32_t abs_duty = (duty < 0) ? -duty : duty;
    if (abs_duty < MOTOR_DEADZONE_PWM) {
        duty = 0;
        abs_duty = 0;
    }

    // Store current duty cycle in struct
    p_mot->duty = duty;

    // Determine PWM pulse width (absolute value of duty)
    uint32_t pulse = (duty > 0) ? duty : -duty;

    if (duty > 0) {
        // Forward direction
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_A, pulse);
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_B, 0);
    }
    else if (duty < 0) {
        // Reverse direction
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_A, 0);
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_B, pulse);
    }
    else {
        // Motor stopped
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_A, 0);
        __HAL_TIM_SET_COMPARE(p_mot->htim, p_mot->ch_B, 0);
    }
}
