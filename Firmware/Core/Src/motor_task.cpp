/*
 * motor_task.cpp
 *
 *  Created on: Jun 2, 2025
 *      Author: jacka
 */

#include "motor_task.h"

/**
 * @brief Constructor for the MOTOR_TASK class.
 * @details Initializes the FSM state and configures motor and encoder objects.
 */
MOTOR_TASK::MOTOR_TASK() : state(S0_INIT),
motor1{ .duty = 0, .htim = &htim1, .ch_A = TIM_CHANNEL_1, .ch_B = TIM_CHANNEL_2 },
motor2{ .duty = 0, .htim = &htim5, .ch_A = TIM_CHANNEL_1, .ch_B = TIM_CHANNEL_2 }
{

}

/**
 * @brief Checks whether the motor task should be running.
 * @return True if any setpoints or efforts from control modules are non-zero.
 */
bool MOTOR_TASK::should_run() {
    return (parser.get_M1_set() != 0) ||
           (parser.get_M2_set() != 0) ||
           (bluetooth.get_M1_set() != 0) ||
           (bluetooth.get_M2_set() != 0) ||
           (heading.get_M1_eff() != 0.0f) ||
           (heading.get_M2_eff() != 0.0f) ||
           (balance.get_M1_eff() != 0.0f) ||
           (balance.get_M2_eff() != 0.0f);
}

/**
 * @brief Executes one iteration of the MOTOR_TASK FSM.
 * @details Manages motor state transitions, runs PID control using encoder feedback,
 *          and integrates control efforts from balance and heading modules.
 */
void MOTOR_TASK::run(void)
{
    switch (state)
    {
        case S0_INIT:
            // Initialize motors and encoders
            motor_enable(&motor1);
            motor_enable(&motor2);
            M1_set = 0;
            M2_set = 0;
            motor_set_duty(&motor1, M1_set);
            motor_set_duty(&motor2, M2_set);

            encoder_init(&encoder1, &htim3);
            encoder_init(&encoder2, &htim4);
            encoder_reset(&encoder1);
            encoder_reset(&encoder2);

            // Set PID gains
            Kp1 = 1.2;
            Ki1 = 6;
            Kd1 = 0.0f;
            Kp2 = 1.2;
            Ki2 = 6;
            Kd2 = 0.0f;

            state = S1_IDLE;
            break;

        case S1_IDLE:
            // Motors idle and waiting for activity
            motor_set_duty(&motor1, 0);
            motor_set_duty(&motor2, 0);

            encoder_update(&encoder1);
            encoder_update(&encoder2);
            last_time = micros();

            // Reset PID state
            error1 = error2 = prev_error1 = prev_error2 = 0;
            error_diff1 = error_diff2 = 0;
            error_sum1 = error_sum2 = 0;

            if (should_run()) {
                state = S2_RUN;
            }
            break;

        case S2_RUN:
            // Get setpoints: prefer parser over Bluetooth
            M1_set = (parser.get_M1_set() != 0) ? parser.get_M1_set() : bluetooth.get_M1_set();
            M2_set = (parser.get_M2_set() != 0) ? parser.get_M2_set() : bluetooth.get_M2_set();

            encoder_update(&encoder1);
            encoder_update(&encoder2);

            now = micros();
            dt = now - last_time;
            if (dt == 0) dt = 1;
            last_time = now;

            // Calculate PID error terms
            error1 = M1_set - encoder_getspeed(&encoder1);
            error2 = M2_set - encoder_getspeed(&encoder2);

            error_sum1 += error1 * dt;
            error_sum2 += error2 * dt;

            // Anti-windup clamp
            if (error_sum1 > 1500000000) error_sum1 = 1500000000;
            if (error_sum1 < -1500000000) error_sum1 = -1500000000;
            if (error_sum2 > 1500000000) error_sum2 = 1500000000;
            if (error_sum2 < -1500000000) error_sum2 = -1500000000;

            error_diff1 = error1 - prev_error1;
            error_diff2 = error2 - prev_error2;
            prev_error1 = error1;
            prev_error2 = error2;

            // PID control output
            M1_eff = (Kp1 * (float)error1)
                   + (Ki1 * (float)error_sum1 / 1000000.0f)
                   + (Kd1 * (float)error_diff1 * 1000000.0f / (float)dt);

            M2_eff = (Kp2 * (float)error2)
                   + (Ki2 * (float)error_sum2 / 1000000.0f)
                   + (Kd2 * (float)error_diff2 * 1000000.0f / (float)dt);

            // Add control efforts from heading and balance FSMs
            M1_eff += heading.get_M1_eff();
            M2_eff += heading.get_M2_eff();
            M1_eff += balance.get_M1_eff();
            M2_eff += balance.get_M2_eff();

            // Clamp output effort to safe range
            M1_eff = std::max(-4799.0f, std::min(M1_eff, (float)4799.0f));
            M2_eff = std::max(-4799.0f, std::min(M2_eff, (float)4799.0f));

            motor_set_duty(&motor1, (int32_t)M1_eff);
            motor_set_duty(&motor2, (int32_t)M2_eff);

            if (!should_run()) {
                state = S1_IDLE;
            }
            break;

        default:
            motor_disable(&motor1);
            motor_disable(&motor2);
    }
}
