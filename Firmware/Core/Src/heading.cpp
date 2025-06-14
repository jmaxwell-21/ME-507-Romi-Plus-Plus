/*
 * heading.cpp
 *
 *  Created on: Jun 8, 2025
 *      Author: jacka
 */

#include "heading.h"

/**
 * @brief Constructor for the HEADING class.
 * @details Initializes FSM state to S0_INIT.
 */
HEADING::HEADING():state(S0_INIT)
{

}

/**
 * @brief Returns the current motor 1 effort calculated by the heading controller.
 * @return Signed 32-bit PWM effort value for motor 1.
 */
int32_t HEADING::get_M1_eff() { return M1_eff; }

/**
 * @brief Returns the current motor 2 effort calculated by the heading controller.
 * @return Signed 32-bit PWM effort value for motor 2.
 */
int32_t HEADING::get_M2_eff() { return M2_eff; }

/**
 * @brief Executes one iteration of the heading control FSM.
 * @details Based on IMU Euler angle data and a commanded heading setpoint,
 *          calculates a control effort using PID logic and outputs motor efforts.
 */
void HEADING::run(void)
{
    switch(state)
    {
        case S0_INIT:
            // Initialization state: zero internal variables and set PID gains
	    angle = 0;
	    prev_angle = 0;
	    position = 0;
	    headset = 0;
	    delta = 0;

	    Kp = 130;
	    Ki = 250;
	    Kd = 0;
	    ctrl = 0;

            state = S1_IDLE;
            break;

        case S1_IDLE:
            // Read IMU and reset state; wait for mode 'D' to activate heading control
	    ReadData(&BNO055, SENSOR_EULER);
	    prev_angle = BNO055.Euler.X;
	    last_time = micros();

	    error = 0;
	    prev_error = 0;
	    error_diff = 0;
	    error_sum = 0;

	    M1_eff = 0;
	    M2_eff = 0;

	    if (parser.get_mode() == 'D') {
		state = S2_RUN;
	    }
            break;

        case S2_RUN:
            // Active heading control state
	    ReadData(&BNO055, SENSOR_EULER);
	    angle = BNO055.Euler.X;

	    // Handle wraparound for angle delta
	    delta = angle - prev_angle;
	    if (delta > 180) delta -= 360;
	    else if (delta < -180) delta += 360;

	    position += delta;
	    prev_angle = angle;

	    printf("IMU Position: %ld\r\n", position);

	    // Reset heading alignment if user presses the button
	    if (USER) {
	        USER = 0;
	        position = headset;
	        prev_angle = BNO055.Euler.X;
	        printf("Heading reset: position = %ld\r\n", position);
	    }

	    now = micros();
	    dt = now - last_time;
	    last_time = now;

	    headset = parser.get_headset();

	    // PID Control Calculations
	    error = headset - position;
	    error_sum += error * dt;

	    // Anti-windup clamp
	    if (error_sum > 1500000000) error_sum = 1500000000;
	    if (error_sum < -1500000000) error_sum = -1500000000;

	    ctrl = (Kp * (float)error)
	         + (Ki * (float)error_sum / 1000000.0f)
	         + (Kd * (float)error_diff * 1000000.0f / (float)dt);

	    printf("Control Effort: %ld\r\n", (int32_t)ctrl);

	    // Assign opposing motor efforts to rotate robot toward heading
	    M1_eff = -ctrl;
	    M2_eff = ctrl;

	    // Return to idle state if mode has changed
	    if (parser.get_mode() != 'D') {
		state = S1_IDLE;
	    }
            break;

        default:
            // Failsafe/default case
	    break;
    }
}
