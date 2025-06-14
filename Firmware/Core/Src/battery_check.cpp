/*
 * battery_check.cpp
 *
 *  Created on: Jun 4, 2025
 *      Author: jacka
 */

#include "battery_check.h"

/**
 * @brief Constructor for the BATTERY_CHECK class.
 * @details Initializes the FSM to the S0_INIT state.
 */
BATTERY_CHECK::BATTERY_CHECK():state(S0_INIT)
{

}

/**
 * @brief Executes one iteration of the battery check FSM.
 * @details Uses ADC readings to determine battery voltage level. If voltage falls
 *          below a threshold (~10.05V), an indicator LED is turned on. When the
 *          voltage rises above a recovery threshold (~10.20V), the LED is turned off.
 *          This ensures that the LED won't be constantly switching back and forth when
 *          the battery voltage decreases.
 */
void BATTERY_CHECK::run(void)
{
    // Execute control logic based on current FSM state
    switch(state)
    {
        case S0_INIT:
            // Initialize ADC reading and move to monitoring state
	    raw = 0;
            state = S1_CHECK_ADC;
            break;

        case S1_CHECK_ADC:
            // Read battery voltage using ADC
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
            raw = HAL_ADC_GetValue(&hadc1);

            // If voltage is too low, activate LED indicator and transition to warning state
            if (raw <= 3300) {
                // Turn LED ON (PB12 high)
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
                state = S2_BATTERY_LOW;
	    }
            break;

        case S2_BATTERY_LOW:
            // Continue monitoring battery voltage
            HAL_ADC_Start(&hadc1);
            HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
            raw = HAL_ADC_GetValue(&hadc1);

            // If voltage has recovered, turn off LED and return to monitoring state
            if (raw >= 3350) {
                // Turn LED OFF (PB12 low)
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
                state = S1_CHECK_ADC;
	    }
            break;

        default:
            // Fail-safe: reset state and turn off LED
	    raw = 0;
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    }
}
