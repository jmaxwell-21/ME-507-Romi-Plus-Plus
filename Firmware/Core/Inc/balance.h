/*
 * balance.h
 *
 *  Created on: Jun 11, 2025
 *      Author: jacka
 */

#ifndef INC_BALANCE_H_
#define INC_BALANCE_H_

/**
 * @file balance.h
 * @brief Declaration of the BALANCE class for managing robot balance using  a FSM.
 * @details This header defines a finite state machine (FSM) class for maintaining
 *          balance of a differential drive robot using BNO055 IMU data. It includes
 *          PID control logic and internal state tracking.
 */

#include "BNO055_STM32.h"
#include "time_utils.h"
#include <stdint.h>
#include <algorithm>

/// @brief External reference to BNO055 sensor data structure.
extern BNO055_Sensors_t BNO055;

/// @brief External flag indicating user button press.
extern volatile bool USER;

/**
 * @class BALANCE
 * @brief Finite State Machine class for robot balance control.
 */
class BALANCE
{
// Public methods and members
public:
    /**
     * @enum state_t
     * @brief Represents the states in the balance FSM.
     */
	typedef enum state
	{
		S0_INIT,    ///< Initialization state
		S1_IDLE,    ///< Idle state
		S2_RUN      ///< Running control loop
	} state_t;

    /**
     * @brief Constructor for the BALANCE class.
     */
	BALANCE();

	/**
	 * @brief Returns the motor effort for motor 1.
	 * @return Effort for motor 1 (M1) as a signed 32-bit integer.
	 */
	int32_t get_M1_eff(void);

	/**
	 * @brief Returns the motor effort for motor 2.
	 * @return Effort for motor 2 (M2) as a signed 32-bit integer.
	 */
	int32_t get_M2_eff(void);

	/**
	 * @brief Executes the FSM logic and PID balance control.
	 */
	void run(void);

// Private methods and members
private:
	state_t state;              ///< Current state of the balance FSM

	float angle;                ///< Current pitch angle from IMU
	float level;                ///< Target level angle (typically 0)
	bool balance_on;            ///< Flag indicating if balance control is active
	float filtered_angle;       ///< Low-pass filtered angle for stability
	float alpha;                ///< Filter coefficient

	int32_t M1_eff;             ///< Calculated effort for motor 1
	int32_t M2_eff;             ///< Calculated effort for motor 2

	// PID controller variables
	float Kp;                   ///< Proportional gain
	float Ki;                   ///< Integral gain
	float Kd;                   ///< Derivative gain

	float error;                ///< Current angle error
	float prev_error;           ///< Previous error (for derivative)
	float error_diff;           ///< Difference between current and previous error
	float error_sum;            ///< Accumulated error for integral term
	float ctrl;                 ///< Final PID output control value

	float dt;                   ///< Delta time in seconds
	uint32_t now;               ///< Current timestamp in microseconds
	uint32_t last_time;         ///< Last update timestamp in microseconds
};

#endif /* INC_BALANCE_H_ */
