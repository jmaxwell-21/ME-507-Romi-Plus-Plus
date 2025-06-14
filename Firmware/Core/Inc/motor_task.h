/*
 * motor_task.h
 *
 *  Created on: Jun 2, 2025
 *      Author: jacka
 */

#ifndef INC_MOTOR_TASK_H_
#define INC_MOTOR_TASK_H_

/**
 * @file motor_task.h
 * @brief Motor control task with feedback and coordination logic.
 * @details Defines the MOTOR_TASK class, which uses encoder feedback and setpoints
 *          from various control modules (Bluetooth, Heading, Balance) to regulate
 *          motor speed and direction using PID control.
 */

#include "motor_driver.h"
#include "encoder.h"
#include "bluetooth.h"
#include "command_parser.h"
#include "heading.h"
#include "balance.h"
#include "time_utils.h"
#include <stdint.h>
#include <algorithm>

/// @brief Timer handle for PWM generation on motor 1.
extern TIM_HandleTypeDef htim1;
/// @brief Timer handle for encoder 1 (e.g., left wheel).
extern TIM_HandleTypeDef htim3;
/// @brief Timer handle for encoder 2 (e.g., right wheel).
extern TIM_HandleTypeDef htim4;
/// @brief Timer handle for motor 2 PWM generation.
extern TIM_HandleTypeDef htim5;

/// @brief Global reference to Bluetooth control FSM.
extern BLUETOOTH bluetooth;

/// @brief Global reference to UART command parser.
extern COMMAND_PARSER parser;

/// @brief Global reference to heading control task.
extern HEADING heading;

/// @brief Global reference to balance control task.
extern BALANCE balance;

/// @brief Global auto-reload value for timers.
extern int32_t AR;

/**
 * @class MOTOR_TASK
 * @brief Finite State Machine for low-level motor control.
 * @details Handles PID control for two motors using encoder feedback.
 *          Receives setpoints from higher-level modules (e.g., balance or heading).
 */
class MOTOR_TASK
{
public:
    /**
     * @enum state_t
     * @brief States for the motor control task FSM.
     */
	typedef enum state
	{
		S0_INIT,  ///< Initialization state
		S1_IDLE,  ///< Idle (standby) state
		S2_RUN    ///< Active motor control loop
	} state_t;

    /**
     * @brief Constructor for the MOTOR_TASK class.
     */
	MOTOR_TASK();

    /**
     * @brief Executes one iteration of the motor control task.
     * @details Updates encoder data, applies PID logic, and adjusts PWM outputs.
     */
	void run(void);

private:
	state_t state;       ///< Current FSM state
	bool should_run();   ///< Internal flag check for determining execution

	// Motor hardware abstraction
	motor_t motor1;      ///< Motor 1 control object
	motor_t motor2;      ///< Motor 2 control object

	float M1_eff;        ///< Control effort for motor 1
	float M2_eff;        ///< Control effort for motor 2

	int16_t M1_set;      ///< Target setpoint for motor 1
	int16_t M2_set;      ///< Target setpoint for motor 2

	// Encoder feedback
	encoder_t encoder1;  ///< Encoder for motor 1
	encoder_t encoder2;  ///< Encoder for motor 2

	// PID gains for motor 1
	float Kp1;           ///< Proportional gain
	float Ki1;           ///< Integral gain
	float Kd1;           ///< Derivative gain

	// PID state variables for motor 1
	int32_t error1;
	int32_t prev_error1;
	int32_t error_diff1;
	int32_t error_sum1;

	// PID gains for motor 2
	float Kp2;
	float Ki2;
	float Kd2;

	// PID state variables for motor 2
	int32_t error2;
	int32_t prev_error2;
	int32_t error_diff2;
	int32_t error_sum2;

	// Timing variables
	uint32_t dt;         ///< Time difference between PID updates (us)
	uint32_t now;        ///< Current time (us)
	uint32_t last_time;  ///< Previous update time (us)
};

#endif /* INC_MOTOR_TASK_H_ */
