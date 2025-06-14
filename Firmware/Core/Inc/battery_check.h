/*
 * battery_check.h
 *
 *  Created on: Jun 4, 2025
 *      Author: jacka
 */

#ifndef INC_BATTERY_CHECK_H_
#define INC_BATTERY_CHECK_H_

/**
 * @file battery_check.h
 * @brief Header for the BATTERY_CHECK class that monitors battery voltage of a 3S LiPo battery using the ADC.
 * @details Defines a finite state machine that checks battery level and signals
 *          a low voltage condition using GPIO indicators.
 */

#include <stm32f4xx_hal.h>
#include <stdint.h>

/// @brief External reference to the ADC handle used for battery sensing.
extern ADC_HandleTypeDef hadc1;

/**
 * @class BATTERY_CHECK
 * @brief A finite state machine for monitoring battery voltage.
 * @details Uses ADC readings to determine if battery voltage is too low and
 *          triggers an indicator if necessary.
 */
class BATTERY_CHECK
{
public:
    /**
     * @enum state_t
     * @brief States of the battery check FSM.
     */
	typedef enum state
	{
		S0_INIT,         ///< Initialization state
		S1_CHECK_ADC,    ///< Check ADC for battery level
		S2_BATTERY_LOW   ///< Battery is below acceptable threshold
	} state_t;

    /**
     * @brief Constructor for the BATTERY_CHECK class.
     */
	BATTERY_CHECK();

    /**
     * @brief Executes one iteration of the battery check FSM.
     * @details Reads ADC value and determines if battery is low.
     */
	void run(void);

private:
	state_t state;  ///< Current FSM state
	uint16_t raw;   ///< Last raw ADC reading of battery voltage
};

#endif /* INC_BATTERY_CHECK_H_ */
