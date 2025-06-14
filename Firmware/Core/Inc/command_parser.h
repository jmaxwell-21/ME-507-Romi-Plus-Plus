/*
 * command_parser.h
 *
 *  Created on: Jun 10, 2025
 *      Author: jacka
 */

#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

/**
 * @file command_parser.h
 * @brief Header for UART command parsing module.
 * @details Provides a C++ class for interpreting control messages received via
 *          DMA UART from an external controller. Includes setpoint extraction
 *          for motors and heading.
 */

#include "stm32f4xx_hal.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Maximum buffer size for incoming UART command stream.
#define BUFFER_SIZE 64

/// @brief DMA-compatible receive buffer for UART.
extern uint8_t rx_buffer[BUFFER_SIZE];

/// @brief Current write index into rx_buffer.
extern uint8_t buffer_index;

/// @brief Flag indicating a complete command is available.
extern volatile uint8_t command_ready;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/**
 * @class COMMAND_PARSER
 * @brief Parses incoming UART command messages into motor and heading setpoints.
 * @details Extracts and interprets hex-encoded values for motor speeds and robot heading,
 *          and manages control mode switching.
 */
class COMMAND_PARSER {
public:
    /**
     * @brief Constructor for the command parser.
     */
    COMMAND_PARSER();

    /**
     * @brief Parses the command buffer to extract motor and heading setpoints.
     */
    void parse();

    /**
     * @brief Retrieves the parsed setpoint for motor 1.
     * @return Signed 16-bit value representing motor 1 setpoint.
     */
    int16_t get_M1_set() const;

    /**
     * @brief Retrieves the parsed setpoint for motor 2.
     * @return Signed 16-bit value representing motor 2 setpoint.
     */
    int16_t get_M2_set() const;

    /**
     * @brief Retrieves the parsed heading setpoint.
     * @return Signed 16-bit value representing heading setpoint.
     */
    int16_t get_headset() const;

    /**
     * @brief Retrieves the parsed operating mode.
     * @return Character indicating the mode (e.g., 'B', 'H', etc.).
     */
    char get_mode() const;

private:
    int16_t M1_set;     ///< Motor 1 setpoint
    int16_t M2_set;     ///< Motor 2 setpoint
    int16_t headset;    ///< Heading setpoint
    char mode;          ///< Parsed mode character

    /**
     * @brief Converts four hex characters to a signed 16-bit integer.
     * @param c1 First hex character
     * @param c2 Second hex character
     * @param c3 Third hex character
     * @param c4 Fourth hex character
     * @param valid Pointer to int set to 1 if conversion was valid
     * @return Parsed signed 16-bit integer
     */
    int16_t hex4_to_int16(char c1, char c2, char c3, char c4, int* valid);

    /**
     * @brief Converts a single hex character to its integer value.
     * @param c Hex character (0-9, A-F, a-f)
     * @return Integer value (0-15) or -1 if invalid
     */
    int hex_char_to_val(char c);

    /**
     * @brief Converts two hex characters to a signed 8-bit integer.
     * @param high High nibble character
     * @param low Low nibble character
     * @param valid Pointer to int set to 1 if conversion was valid
     * @return Parsed signed 8-bit integer
     */
    int8_t hex_to_signed(char high, char low, int* valid);
};

#endif

#endif /* INC_COMMAND_PARSER_H_ */
