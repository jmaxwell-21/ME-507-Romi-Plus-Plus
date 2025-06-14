/*
 * printf_retarget.c
 *
 *  Created on: Jun 5, 2025
 *      Author: jacka
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stm32f4xx_hal.h>
#include <stdio.h>  // for printf

/// @brief UART handle used for redirecting printf output.
extern UART_HandleTypeDef huart6;

/**
 * @brief Retargets the `printf()` function to UART.
 * @param file File descriptor (unused, but required for syscall prototype).
 * @param ptr Pointer to data buffer to transmit.
 * @param len Length of data to transmit.
 * @return Number of bytes transmitted.
 *
 * @note This function overrides the `_write` syscall used by `printf()` in newlib,
 *       allowing standard output to be redirected to a UART peripheral (e.g., huart6).
 */
int _write(int file, char *ptr, int len) {
    HAL_UART_Transmit(&huart6, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}

#ifdef __cplusplus
}
#endif
