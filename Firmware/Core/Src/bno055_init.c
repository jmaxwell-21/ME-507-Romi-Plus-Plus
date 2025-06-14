/*
 * bno055_init.c
 *
 *  Created on: Jun 5, 2025
 *      Author: jacka
 */

#include "bno055_init.h"

/**
 * @brief Calibration offsets used to initialize BNO055 sensor.
 * @details Pre-collected sensor offsets to avoid re-calibration on every startup.
 *          If initialization parameters change, these offsets may become invalid.
 */
uint8_t OffsetDatas[22] = {
    0xEA, 0xFF, 0xE6, 0xFF, 0xE6, 0xFF, 0x28, 0x00,
    0x94, 0x02, 0x54, 0x01, 0xFD, 0xFF, 0xFF, 0xFF,
    0x00, 0x00, 0xE8, 0x03, 0x90, 0x02
};

/**
 * @brief Initializes the BNO055 IMU sensor and applies offset data.
 * @details Configures the BNO055 with normal operating mode, Android orientation,
 *          and unit settings. Applies hard-coded offset values for faster startup.
 *          Optional re-calibration section is provided but commented out.
 */
void Sensor_Init(void)
{
	BNO_Status_t Status = {0};

	// Init structure definition section
	BNO055_Init_t BNO055_InitStruct = {0};

	// Reset BNO055 device
	ResetBNO055();

	/*============================ *BNO055 Initialization* ============================*/

	BNO055_InitStruct.ACC_Range = Range_16G;                  // Accelerometer range
	BNO055_InitStruct.Axis = 0x24;                            // Axis remap value (see datasheet)
	BNO055_InitStruct.Axis_sign = 0x03;                       // Axis sign config (see datasheet)
	BNO055_InitStruct.Clock_Source = CLOCK_EXTERNAL;          // Use external crystal
	BNO055_InitStruct.Mode = BNO055_NORMAL_MODE;              // Power mode
	BNO055_InitStruct.OP_Modes = NDOF_FMC_OFF;                // Operating mode
	BNO055_InitStruct.Unit_Sel = (UNIT_ORI_ANDROID | UNIT_TEMP_CELCIUS | UNIT_EUL_DEG | UNIT_GYRO_DPS | UNIT_ACC_MS2);
	                                                           // Unit configuration
	BNO055_Init(BNO055_InitStruct);

	//------------------BNO055 Calibration------------------

	/**
	 * @note This writes previously stored sensor offsets directly to the IMU,
	 *       bypassing manual calibration. This is useful for consistent startup behavior.
	 */
	setSensorOffsets(OffsetDatas);

	/*=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= Optional Calibration Routine =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
	// Uncomment if re-calibration is needed, e.g., after changing hardware layout or init params

//	if(Calibrate_BNO055())
//	{
//		getSensorOffsets(OffsetDatas);
//
//		// Code for printing the offset data
//		printf("Calibration offsets:\r\n");
//		for (int i = 0; i < 22; i++) {
//		    printf("0x%02X ", OffsetDatas[i]);
//		    if ((i + 1) % 8 == 0) printf("\r\n");
//		}
//		printf("\r\n");
//
//	}
//	else
//	{
//		printf("Sensor calibration failed.\r\nFailed to retrieve offset data\r\n");
//	}

	// Print sensor system status and diagnostics
	Check_Status(&Status);
	printf("Selftest Result: %d\t", Status.STresult);
	printf("System Status: %d\t", Status.SYSStatus);
	printf("System Error: %d\r\n", Status.SYSError);
}
