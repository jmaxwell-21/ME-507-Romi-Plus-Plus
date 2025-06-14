/*
 * uart_dma_idle.c
 *
 *  Created on: Jun 9, 2025
 *      Author: jacka
 */

#include "uart_dma_idle.h"
#include <string.h>
#include <stdio.h>

/// @brief Static pointer to the UART handle used for DMA + idle detection.
static UART_HandleTypeDef *huart_ptr = NULL;

/**
 * @brief Initializes UART reception using DMA and enables idle line interrupt.
 * @param huart Pointer to the UART handle to configure.
 * @details Starts the DMA reception and enables UART idle line detection to
 *          trigger when a message has ended. Assumes a '\r\n' terminated protocol.
 */
void UART_DMA_IDLE_Init(UART_HandleTypeDef *huart)
{
    huart_ptr = huart;
    HAL_UART_Receive_DMA(huart_ptr, rx_buffer, BUFFER_SIZE);
    __HAL_UART_ENABLE_IT(huart_ptr, UART_IT_IDLE);
}

/**
 * @brief Interrupt handler for UART idle line detection with DMA.
 * @param huart Pointer to the UART handle triggering the interrupt.
 * @details Stops DMA temporarily, calculates received length, and checks for a
 *          complete command (terminated by "\r\n"). If found, sets `command_ready`.
 */
void UART_DMA_IDLE_IRQHandler(UART_HandleTypeDef *huart)
{
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        HAL_UART_DMAStop(huart);

        uint16_t dma_remaining = __HAL_DMA_GET_COUNTER(huart->hdmarx);
        uint16_t received_len = BUFFER_SIZE - dma_remaining;

        // Look for a complete command ending with \r\n
        for (uint16_t i = 0; i < received_len - 1; i++)
        {
            if (rx_buffer[i] == '\r' && rx_buffer[i+1] == '\n')
            {
                buffer_index = i;  // Exclude \r\n
                command_ready = 1;
                break;
            }
        }

        // Restart DMA reception
        HAL_UART_Receive_DMA(huart, rx_buffer, BUFFER_SIZE);
    }
}
