/*
 * heading.h
 *
 *  Created on: Jun 8, 2025
 *      Author: jacka
 */

#ifndef INC_HEADING_H_
#define INC_HEADING_H_

/**
 * @file heading.h
 * @brief FSM class for heading-based robot control using IMU input.
 * @details Defines a finite state machine for maintaining or adjusting the robot's
 *          heading based on IMU data and a heading setpoint received via parser.
 */

#include "command_parser.h"
#include "BNO055_STM32.h"
#include "time_utils.h"
#include <stdint.h>
#include <algorithm>

/// @brief External reference to the command parser.
extern COMMAND_PARSER parser;

/// @brief External reference to BNO055 IMU data structure.
extern BNO055_Sensors_t BNO055;

/// @brief External flag triggered by user button press.
extern volatile bool USER;

/**
 * @class HEADING
 * @brief Finite State Machine for heading control based on IMU data.
 * @details Uses a PID control loop to drive motor efforts to reduce heading error.
 */
class HEADING
{
public:
    /**
     * @enum state_t
     * @brief Enumeration of FSM states for heading control.
     */
	typedef enum state
	{
		S0_INIT,  ///< Initialization state
		S1_IDLE,  ///< Idle state (waiting for control activation)
		S2_RUN    ///< Active heading control loop
	} state_t;

    /**
     * @brief Constructor for the HEADING class.
     */
	HEADING();

    /**
     * @brief Retrieves the motor 1 effort calculated by the heading controller.
     * @return Signed effort for motor 1.
     */
	int32_t get_M1_eff(void);

    /**
     * @brief Retrieves the motor 2 effort calculated by the heading controller.
     * @return Signed effort for motor 2.
     */
	int32_t get_M2_eff(void);

    /**
     * @brief Executes one iteration of the heading FSM and PID controller.
     */
	void run(void);

private:
	state_t state;        ///< Current state of the FSM

	int16_t angle;        ///< Current heading angle
	int16_t prev_angle;   ///< Previous angle for delta calculation
	int32_t headset;      ///< Desired heading setpoint
	int32_t position;     ///< Cumulative heading position
	int16_t delta;        ///< Angle delta between updates

	int32_t M1_eff;       ///< Motor 1 effort output
	int32_t M2_eff;       ///< Motor 2 effort output

	// PID controller parameters
	float Kp;             ///< Proportional gain
	float Ki;             ///< Integral gain
	float Kd;             ///< Derivative gain

	int32_t error;        ///< Current heading error
	int32_t prev_error;   ///< Previous error for derivative calculation
	int32_t error_diff;   ///< Error derivative
	int32_t error_sum;    ///< Error integral sum

	int16_t ctrl;         ///< Final control signal
	uint32_t dt;          ///< Time delta in microseconds
	uint32_t now;         ///< Current timestamp
	uint32_t last_time;   ///< Last update timestamp
};

#endif /* INC_HEADING_H_ */
