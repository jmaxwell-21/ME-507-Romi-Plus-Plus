/*
 * bluetooth.h
 *
 *  Created on: Jun 3, 2025
 *      Author: jacka
 */

#ifndef INC_BLUETOOTH_H_
#define INC_BLUETOOTH_H_

/**
 * @file bluetooth.h
 * @brief Bluetooth command handler for robot control.
 * @details This file declares the BLUETOOTH class, which implements a finite state
 *          machine that processes commands received via a Bluetooth module (HC-05).
 *          It translates commands into motor setpoints for directional control.
 */

#include <stdint.h>

/// @brief Velocity setpoint (in encoder counts/sec) received via Bluetooth.
extern int32_t V;

/**
 * @class BLUETOOTH
 * @brief Finite State Machine for Bluetooth-based control input.
 * @details Converts ASCII command characters received via UART into
 *          motor setpoints for directional movement.
 */
class BLUETOOTH
{
public:
    /**
     * @enum state_t
     * @brief Represents all possible states in the Bluetooth FSM.
     */
	typedef enum state
	{
	        S0_INIT,     ///< Initialization state
	        S1_STOP,     ///< Stop motors
	        SF_FORWARD,  ///< Move forward
	        SB_BACKWARD, ///< Move backward
	        SR_RIGHT,    ///< Turn right
		SL_LEFT      ///< Turn left
	} state_t;

    /**
     * @brief Constructor for the BLUETOOTH class.
     */
	BLUETOOTH();

    /**
     * @brief Executes one iteration of the Bluetooth FSM.
     * @details Updates motor setpoints based on current state and command.
     */
	void run(void);

    /**
     * @brief Sets the most recent command character received over Bluetooth.
     * @param cmd Single character representing a motion command.
     */
	void set_command(char cmd);  // Called from interrupt handler

    /**
     * @brief Retrieves the motor 1 setpoint based on last command.
     * @return Signed 16-bit motor setpoint value for motor 1.
     */
	int16_t get_M1_set(void);

    /**
     * @brief Retrieves the motor 2 setpoint based on last command.
     * @return Signed 16-bit motor setpoint value for motor 2.
     */
	int16_t get_M2_set(void);

private:
	state_t state;    ///< Current FSM state
	char command;     ///< Most recent command character received
	int16_t M1_set;   ///< Setpoint for motor 1
	int16_t M2_set;   ///< Setpoint for motor 2
};

#endif /* INC_BLUETOOTH_H_ */
