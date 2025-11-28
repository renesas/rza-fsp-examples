/***********************************************************************************************************************
 * File Name    : common_utils.h
 * Description  : Contains macros, data structures and functions used  common to the EP
 ***********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
 
#ifndef COMMON_UTILS_H_
#define COMMON_UTILS_H_

/* generic headers */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hal_data.h"

extern void app_read(unsigned char* p_data);
extern int app_check_data();

#define SIZE_64      (64u)
#define RESET_VALUE             (0x00)

#define EP_VERSION              "3.6.0"
#define BANNER_INFO             "\r\n********************************************************************************"\
                                "\r\n*   Renesas FSP Example Project for "MODULE_NAME" Module                         *"\
                                "\r\n*   Example Project Version %s                                              *"\
                                "\r\n*   Flex Software Pack Version  %d.%d.%d                                          *"\
                                "\r\n********************************************************************************"\
                                "\r\nRefer to readme.txt file for more details on Example Project and" \
                                "\r\nFSP User's Manual for more information about "MODULE_NAME" driver\r\n"

/* Application printf */
#define APP_PRINT(fn_, ...)       (printf(fn_, ##__VA_ARGS__))

/* Application error */
#define APP_ERR_PRINT(fn_, ...)   (printf(("[ERR] In Function: %s"),fn_, ##__VA_ARGS__))

/* Application error trap */
#define APP_ERR_TRAP(err)  ({ \
        int _err_val = (err); \
        if (_err_val) { \
            printf("\r\nReturned Error Code: 0x%x  \r\n", _err_val); \
            __asm__ volatile("brk 0x0\n"); \
        } \
    })

/* Application read */
#define APP_READ(read_data)      (app_read(read_data))

/* Application check data */
#define APP_CHECK_DATA           (app_check_data())

#endif /* COMMON_UTILS_H_ */
