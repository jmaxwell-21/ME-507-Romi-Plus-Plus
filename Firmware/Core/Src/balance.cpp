/*
 * balance.cpp
 *
 *  Created on: Jun 11, 2025
 *      Author: jacka
 */

#include "balance.h"

/**
 * @brief Constructor for the BALANCE class.
 * @details Initializes the FSM to the S0_INIT state.
 */
BALANCE::BALANCE():state(S0_INIT)
{

}

/**
 * @brief Retrieves the calculated effort for motor 1.
 * @return Motor 1 effort as a signed 32-bit integer.
 */
int32_t BALANCE::get_M1_eff() { return M1_eff; }

/**
 * @brief Retrieves the calculated effort for motor 2.
 * @return Motor 2 effort as a signed 32-bit integer.
 */
int32_t BALANCE::get_M2_eff() { return M2_eff; }

/**
 * @brief Executes one iteration of the balance FSM.
 * @details This function handles state transitions and PID-based control
 *          logic using IMU data to maintain robot balance.
 */
void BALANCE::run(void)
{
    // Execute control logic based on current FSM state
    switch(state)
    {
        case S0_INIT:
            // Initialization: set filter, control gains, and default values
	    angle = 0.0f;
	    level = 0.0f;
	    balance_on = 1;
	    filtered_angle = 0.0f;
	    alpha = 0.1f;

	    Kp = 160;
	    Ki = 2.0f;
	    Kd = 8.0f;
	    ctrl = 0.0f;

            state = S1_IDLE;
            break;

        case S1_IDLE:
            // Idle: read angle, wait for user input to activate balancing
	    ReadData(&BNO055, SENSOR_EULER);
	    angle = BNO055.Euler.Z;
	    last_time = micros();

	    error = 0.0f;
	    prev_error = 0.0f;
	    error_diff = 0.0f;
	    error_sum = 0.0f;

	    M1_eff = 0;
	    M2_eff = 0;

	    if (USER) {
		USER = 0;
		balance_on = 1;
		printf("Entering Balance Mode");
	    }

	    if (balance_on == 1){
		state = S2_RUN;
	    }
            break;

        case S2_RUN:
            // Active: run balance control loop using filtered angle and PID
	    ReadData(&BNO055, SENSOR_EULER);
	    angle = (float)BNO055.Euler.Z;
	    printf("IMU Angle: %0.2f\r\n", angle);

	    // Low-pass filter (Exponential Moving Average)
	    filtered_angle = alpha * angle + (1.0f - alpha) * filtered_angle;

	    now = micros();
	    dt = (float)(now - last_time) / 1000000.0f;
	    last_time = now;

	    error = level - filtered_angle;
	    error_sum += error * dt;

	    // Anti-windup clamp on integral term
	    // I forgot that I had this here. Removing it may allow for more aggressive integral control
	    if (error_sum > 1000.0f) error_sum = 1000.0f;
	    if (error_sum < -1000.0f) error_sum = -1000.0f;

	    error_diff = (error - prev_error) / dt;
	    prev_error = error;

	    // PID control computation
	    ctrl = (Kp * error) + (Ki * error_sum) + (Kd * error_diff);

	    printf("Control Effort: %ld\r\n", (int32_t)ctrl);

	    M1_eff = ctrl;
	    M2_eff = ctrl;

	    if (USER) {
		USER = 0;
		balance_on = 0;
		printf("Leaving Balance Mode");
	    }

	    if (balance_on == 0){
		state = S1_IDLE;
	    }
            break;

        default:
            // Fallback/reset case
	    M1_eff = 0;
	    M2_eff = 0;
	    ctrl = 0;
	    balance_on = 0;
    }

}
