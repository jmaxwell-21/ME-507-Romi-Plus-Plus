/*
 * bno055_init.h
 *
 *  Created on: Jun 5, 2025
 *      Author: jacka
 */

#ifndef INC_BNO055_INIT_H_
#define INC_BNO055_INIT_H_

/**
 * @file bno055_init.h
 * @brief BNO055 IMU initialization interface.
 * @details Provides function prototype for initializing the BNO055 sensor.
 *          Also declares a buffer for storing sensor offset calibration data.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "BNO055_STM32.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>   // for printf
#include <stdint.h>

/**
 * @brief Initializes the BNO055 IMU sensor and applies configuration.
 * @details This function sets up sensor mode, units, and optional calibration offsets.
 */
void Sensor_Init(void);

/**
 * @brief Array storing sensor offset and calibration data.
 * @details Contains 22 bytes used to apply or retrieve sensor calibration.
 */
extern uint8_t OffsetDatas[22];

#ifdef __cplusplus
}
#endif

#endif /* INC_BNO055_INIT_H_ */
