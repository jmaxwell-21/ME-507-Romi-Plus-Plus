/*
 * uart_dma_idle.h
 *
 *  Created on: Jun 9, 2025
 *      Author: jacka
 */

#ifndef INC_UART_DMA_IDLE_H_
#define INC_UART_DMA_IDLE_H_

/**
 * @file uart_dma_idle.h
 * @brief UART DMA with idle line detection handler.
 * @details Provides support for non-blocking UART reception using DMA with
 *          idle line interrupt to detect end-of-packet or message termination.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/// @brief Maximum receive buffer size for UART DMA.
#define BUFFER_SIZE 64

/// @brief UART DMA receive buffer shared with command parser or control logic.
extern uint8_t rx_buffer[BUFFER_SIZE];

/// @brief Current write index into the rx_buffer.
extern uint8_t buffer_index;

/// @brief Flag set when a full command is received and ready to parse.
extern volatile uint8_t command_ready;

/**
 * @brief Initializes UART DMA reception with idle line detection.
 * @param huart Pointer to UART handle configured for DMA RX.
 */
void UART_DMA_IDLE_Init(UART_HandleTypeDef *huart);

/**
 * @brief UART interrupt handler for idle line detection.
 * @param huart Pointer to UART handle triggering the interrupt.
 * @details Should be called from the HAL_UART_IRQHandler.
 */
void UART_DMA_IDLE_IRQHandler(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* INC_UART_DMA_IDLE_H_ */
