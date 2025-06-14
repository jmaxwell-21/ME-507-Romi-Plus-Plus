/*
 * command_parser.cpp
 *
 *  Created on: Jun 10, 2025
 *      Author: jacka
 */

#include <command_parser.h>
#include <cstring>
#include <cstdio>
#include <math.h>

/**
 * @brief Constructor for COMMAND_PARSER.
 * @details Initializes all member variables to default values.
 */
COMMAND_PARSER::COMMAND_PARSER()
    : M1_set(0), M2_set(0), headset(0), mode(0) {}

/**
 * @brief Converts a single hexadecimal character to its integer value.
 * @param c Hexadecimal character (0–9, A–F, a–f)
 * @return Integer value from 0 to 15, or -1 if invalid.
 */
int COMMAND_PARSER::hex_char_to_val(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

/**
 * @brief Converts two hex characters to a signed 8-bit integer.
 * @param high High nibble character.
 * @param low Low nibble character.
 * @param valid Pointer to an int set to 1 if valid conversion, else 0.
 * @return Signed 8-bit integer.
 */
int8_t COMMAND_PARSER::hex_to_signed(char high, char low, int* valid) {
    int hi = hex_char_to_val(high);
    int lo = hex_char_to_val(low);

    if (hi < 0 || lo < 0) {
        *valid = 0;
        return 0;
    }

    *valid = 1;
    int val = (hi << 4) | lo;
    if (val > 127) val -= 256;

    return static_cast<int8_t>(val);
}

/**
 * @brief Converts four hex characters to a signed 16-bit integer (two's complement).
 * @param c1–c4 Hexadecimal characters from MSB to LSB.
 * @param valid Pointer to an int set to 1 if valid conversion, else 0.
 * @return Signed 16-bit integer.
 */
int16_t COMMAND_PARSER::hex4_to_int16(char c1, char c2, char c3, char c4, int* valid) {
    int h1 = hex_char_to_val(c1);
    int h2 = hex_char_to_val(c2);
    int h3 = hex_char_to_val(c3);
    int h4 = hex_char_to_val(c4);

    if (h1 < 0 || h2 < 0 || h3 < 0 || h4 < 0) {
        *valid = 0;
        return 0;
    }

    *valid = 1;
    uint16_t val = (h1 << 12) | (h2 << 8) | (h3 << 4) | h4;

    return (val > 0x7FFF) ? static_cast<int16_t>(val - 0x10000) : static_cast<int16_t>(val);
}

/**
 * @brief Parses the received command buffer.
 * @details Decodes motor or heading control messages depending on the leading mode character.
 * Supported modes:
 * - 'A': M1/M2 duty cycle (signed 8-bit hex)
 * - 'B': M1/M2 duty cycle (signed 8-bit hex)
 * - 'C': Reserved
 * - 'D': Heading (16-bit hex) + motor effort (8-bit hex)
 */
void COMMAND_PARSER::parse() {
    if (command_ready) {
        command_ready = 0;
        char mode_char = rx_buffer[0];
        mode = mode_char;

        if (mode_char == 'A' && buffer_index >= 5) {
            int validA1, validA2;
            int8_t M1 = hex_to_signed(rx_buffer[1], rx_buffer[2], &validA1);
            int8_t M2 = hex_to_signed(rx_buffer[3], rx_buffer[4], &validA2);

            if (validA1 && validA2) {
                M1_set = M1 * 100;
                M2_set = M2 * 100;
                printf("Motor 1 Duty Cycle: %d | Motor 2 Duty Cycle: %d\r\n", M1, M2);
            } else {
                printf("Invalid hex values: %c%c %c%c\r\n", rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4]);
            }
        }
        else if (mode_char == 'B' && buffer_index >= 5) {
            int validB1, validB2;
            int8_t M1 = hex_to_signed(rx_buffer[1], rx_buffer[2], &validB1);
            int8_t M2 = hex_to_signed(rx_buffer[3], rx_buffer[4], &validB2);

            if (validB1 && validB2) {
                M1_set = M1 * 100;
                M2_set = M2 * 100;
                printf("Motor 1 Duty Cycle: %d | Motor 2 Duty Cycle: %d\r\n", M1, M2);
            } else {
                printf("Invalid hex values: %c%c %c%c\r\n", rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4]);
            }
        }
        else if (mode_char == 'C' && buffer_index >= 5) {
            // TODO: Implement mode C functionality
            printf("Mode C: stub\r\n");
        }
        else if (mode_char == 'D' && buffer_index >= 7) {
            int valid_heading, valid_motorD;
            int16_t h = hex4_to_int16(rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4], &valid_heading);
            float h_deg = ((float)h / 10.0f) * (180.0f / (float)M_PI);
            int8_t motor = hex_to_signed(rx_buffer[5], rx_buffer[6], &valid_motorD);

            if (valid_heading && valid_motorD) {
                headset = h_deg;
                M1_set = motor * 100;
                M2_set = motor * 100;
                printf("Mode D - Heading: %d | Motor Effort: %d\r\n", headset, motor);
            } else {
                printf("Invalid Mode D values: %c%c%c%c %c%c\r\n",
                       rx_buffer[1], rx_buffer[2], rx_buffer[3], rx_buffer[4],
                       rx_buffer[5], rx_buffer[6]);
            }
        }
        else {
            printf("Unknown or too-short command. Mode: %c | Length: %d\r\n", mode_char, buffer_index);
        }

        // Reset buffer for next command
        buffer_index = 0;
        memset(rx_buffer, 0, BUFFER_SIZE);
    }
}

// Accessors

/**
 * @brief Gets the parsed motor 1 setpoint.
 * @return Motor 1 effort in encoder units.
 */
int16_t COMMAND_PARSER::get_M1_set() const { return M1_set; }

/**
 * @brief Gets the parsed motor 2 setpoint.
 * @return Motor 2 effort in encoder units.
 */
int16_t COMMAND_PARSER::get_M2_set() const { return M2_set; }

/**
 * @brief Gets the parsed heading setpoint.
 * @return Heading setpoint in degrees.
 */
int16_t COMMAND_PARSER::get_headset() const { return headset; }

/**
 * @brief Gets the mode character from the last command.
 * @return Mode character ('A', 'B', 'C', 'D', etc.)
 */
char COMMAND_PARSER::get_mode() const { return mode; }
