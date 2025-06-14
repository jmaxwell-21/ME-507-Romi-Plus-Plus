/*
 * motor_driver.h
 *
 *  Created on: Apr 17, 2025
 *      Author: jacka
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

/**
 * @file motor_driver.h
 * @brief Low-level motor control interface for STM32 using PWM.
 * @details Defines the motor object and provides function prototypes to control
 *          motor direction and speed through timer-based PWM outputs.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx_hal.h> // Include HAL functions

/**
 * @struct motor_t
 * @brief Struct representing a DC motor controlled by two PWM channels.
 * @details Stores duty cycle, timer handle, and output channels used to set motor speed and direction.
 */
typedef struct {
    int32_t  duty;              /**< Signed duty cycle value (-100% to +100%) scaled to timer period */
    TIM_HandleTypeDef* htim;    /**< Pointer to the timer used for PWM generation */
    uint32_t ch_A;              /**< Timer channel A for one motor lead */
    uint32_t ch_B;              /**< Timer channel B for the other motor lead */
} motor_t;

/**
 * @brief Sets the PWM duty cycle to control motor speed and direction.
 * @param p_mot Pointer to motor object.
 * @param duty Signed duty cycle (-timer period to +timer period).
 */
void motor_set_duty(motor_t* p_mot, int32_t duty);

/**
 * @brief Enables PWM output to the motor by starting both channels.
 * @param p_mot Pointer to motor object.
 */
void motor_enable(motor_t* p_mot);

/**
 * @brief Disables PWM output to the motor.
 * @param p_mot Pointer to motor object.
 */
void motor_disable(motor_t* p_mot);

#ifdef __cplusplus
}
#endif

#endif /* INC_MOTOR_DRIVER_H_ */
