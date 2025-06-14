/*
 * bluetooth.cpp
 *
 *  Created on: Jun 3, 2025
 *      Author: jacka
 */

#include "bluetooth.h"

/**
 * @brief Constructor for the BLUETOOTH class.
 * @details Initializes the FSM to the S0_INIT state and motor setpoints to zero.
 */
BLUETOOTH::BLUETOOTH():state(S0_INIT),M1_set(0), M2_set(0)
{

}

/**
 * @brief Sets the most recent command received via Bluetooth.
 * @param cmd Single ASCII character representing the command:
 *        'F' = forward, 'B' = backward, 'L' = left, 'R' = right, 'S' = stop.
 */
void BLUETOOTH::set_command(char cmd) {command = cmd;}

/**
 * @brief Retrieves the setpoint for motor 1.
 * @return Motor 1 velocity setpoint.
 */
int16_t BLUETOOTH::get_M1_set() { return M1_set; }

/**
 * @brief Retrieves the setpoint for motor 2.
 * @return Motor 2 velocity setpoint.
 */
int16_t BLUETOOTH::get_M2_set() { return M2_set; }

/**
 * @brief Executes one iteration of the Bluetooth FSM.
 * @details Translates command characters into motor setpoints by updating internal FSM state.
 */
void BLUETOOTH::run(void)
{
    switch(state)
    {
        case S0_INIT:
            // Initialize to STOP state with default command
	    command = 'S';
            state = S1_STOP;
            break;

        case S1_STOP:
            // Motors stopped until a new command is received
	    M1_set = 0;
	    M2_set = 0;
	    if (command == 'F') {
	        state = SF_FORWARD;
	    }
	    else if (command == 'B') {
	        state = SB_BACKWARD;
	    }
	    else if (command == 'L') {
	        state = SL_LEFT;
	    }
	    else if (command == 'R') {
	        state = SR_RIGHT;
	    }
	    break;

        case SF_FORWARD:
            // Move forward: both motors in forward direction
	    M1_set = V;       // M1 Clockwise
	    M2_set = V;       // M2 Counter-Clockwise
            if (command == 'S') {
                state = S1_STOP;
            }
	    break;

	case SB_BACKWARD:
            // Move backward: both motors in reverse
	    M1_set = -V;      // M1 Counter-Clockwise
	    M2_set = -V;      // M2 Clockwise
            if (command == 'S') {
                state = S1_STOP;
            }
	    break;

	case SR_RIGHT:
            // Turn right: differential speeds in opposite directions
	    M1_set = -V / 2;  // M1 Counter-Clockwise
	    M2_set = V / 2;   // M2 Counter-Clockwise
            if (command == 'S') {
                state = S1_STOP;
            }
	    break;

	case SL_LEFT:
            // Turn left: differential speeds in opposite directions
	    M1_set = V / 2;   // M1 Clockwise
	    M2_set = -V / 2;  // M2 Clockwise
            if (command == 'S') {
                state = S1_STOP;
            }
	    break;

        default:
            // Fail-safe: reset setpoints if in unknown state
	    M1_set = 0;
	    M2_set = 0;
    }
}
