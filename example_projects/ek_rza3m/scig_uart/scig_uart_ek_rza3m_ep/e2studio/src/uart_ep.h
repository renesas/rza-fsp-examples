/***********************************************************************************************************************
 * File Name    : uart_ep.h
 * Description  : Contains function declaration of uart_ep.c and Macros.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef UART_EP_H_
#define UART_EP_H_

#include <stdio.h>
#include <stdlib.h>

/* Macro definition */
#define LINEFEED_ASCII            (10u)     /* Line Feed */
#define CARRIAGE_ASCII            (13u)     /* Carriage return */
#define ZERO_ASCII                (48u)     /* ASCII value of zero */
#define NINE_ASCII                (57u)     /* ASCII value for nine */
#define DATA_LENGTH               (5u)      /* Expected Input Data length */
#define UART_ERROR_EVENTS         (UART_EVENT_BREAK_DETECT | UART_EVENT_ERR_OVERFLOW | UART_EVENT_ERR_FRAMING | \
                                    UART_EVENT_ERR_PARITY)    /* UART Error event bits mapped in registers */

/* Function declaration */
fsp_err_t uart_ep_demo(void);
fsp_err_t uart_print_user_msg(uint8_t *p_msg);
fsp_err_t uart_initialize(void);
void deinit_uart(void);

/* Information for module */
#define RESET_VALUE             (0x00)
#define EP_VERSION              "3.6.0"
#define MODULE_NAME             "r_sci_uart"

#define BANNER_1                "\r\n********************************************************************************"
#define BANNER_2                "\r\n*   Renesas FSP Example Project for "MODULE_NAME" Module                          *"
#define BANNER_3                "\r\n*   Example Project Version "EP_VERSION"                                              *"
#define BANNER_4                "\r\n*   Flex Software Pack Version  "
#define BANNER_5                "                                          *"
#define BANNER_6                "\r\n********************************************************************************"
#define BANNER_7                "\r\nRefer to readme.txt file for more details on Example Project and" \
                                "\r\nFSP User's Manual for more information about "MODULE_NAME" driver\r\n"

/* Application error trap */
#define APP_ERR_TRAP(err)  ({ \
        int _err_val = (err); \
        if (_err_val) { \
            printf("\r\nReturned Error Code: 0x%x  \r\n", _err_val); \
            __asm__ volatile("brk 0x0\n"); \
        } \
    })

#endif /* UART_EP_H_ */
