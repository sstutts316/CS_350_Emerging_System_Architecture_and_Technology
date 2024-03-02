/*
 * Copyright (c) 2015-2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== uartecho.c ========
 */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

/* Driver Header files */
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

/* Driver configuration */
#include "ti_drivers_config.h"

/* Define states for the state machine */
typedef enum {
    IDLE,        // Waiting for a command
    COMMAND_READY // Command received and ready for processing
} CommandState;

/* Define commands */
typedef enum {
    CMD_UNKNOWN, // Command not recognized
    CMD_ON,      // Turn LED on
    CMD_OFF      // Turn LED off
} Command;

/* Command buffer and index */
char cmdBuffer[10]; // Adjust size as needed
int cmdIndex = 0;

/* Function prototype */
Command parseCommand(const char *cmd);

/*
 *  ======== mainThread ========
 */
void *mainThread(void *arg0)
{
    char input;
    CommandState state = IDLE;

    UART_Handle uart;
    UART_Params uartParams;

    /* Initialize drivers */
    GPIO_init();
    UART_init();

    /* Configure the LED pin */
    GPIO_setConfig(CONFIG_GPIO_LED_0, GPIO_CFG_OUT_STD | GPIO_CFG_OUT_LOW);

    /* Create and configure UART */
    UART_Params_init(&uartParams);
    uartParams.writeDataMode = UART_DATA_BINARY;
    uartParams.readDataMode = UART_DATA_BINARY;
    uartParams.readReturnMode = UART_RETURN_FULL;
    uartParams.baudRate = 115200;
    uart = UART_open(CONFIG_UART_0, &uartParams);
    if (uart == NULL) {
        while (1); // UART_open() failed
    }

    /* Main loop */
    while (1) {
        UART_read(uart, &input, 1); // Read one character at a time
        UART_write(uart, &input, 1); // Echo the character back to the UART

        // Process input character
        if (input == '\n' || input == '\r') { // Command termination
            if (cmdIndex > 0) { // There's a command to process
                cmdBuffer[cmdIndex] = '\0'; // Null-terminate the command
                state = COMMAND_READY;
            }
        } else if (cmdIndex < sizeof(cmdBuffer) - 1) { // Avoid buffer overflow
            cmdBuffer[cmdIndex++] = tolower((unsigned char) input); // Store lowercase character
        }

        // State machine for handling commands
        switch (state) {
            case COMMAND_READY:
                {
                    Command cmd = parseCommand(cmdBuffer);
                    switch (cmd) {
                        case CMD_ON:
                            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_ON);
                            break;
                        case CMD_OFF:
                            GPIO_write(CONFIG_GPIO_LED_0, CONFIG_GPIO_LED_OFF);
                            break;
                        default:
                            // Handle unknown command
                            break;
                    }

                    // Reset for next command
                    cmdIndex = 0;
                    state = IDLE;
                }
                break;

            default:
                // Remain in IDLE state until a command is ready
                break;
        }
    }
}

/* Parse input string and return the corresponding command */
Command parseCommand(const char *cmd) {
    if (strcmp(cmd, "on") == 0) {
        return CMD_ON;
    } else if (strcmp(cmd, "off") == 0) {
        return CMD_OFF;
    }
    return CMD_UNKNOWN;
}
