/***********************************************************************************************************************
 * File Name    : common_utils.h
 * Description  : Contains macros, data structures and functions used  common to the EP
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 * Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

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

#define BIT_SHIFT_8         (8u)
#define SIZE_64             (64u)
#define LVL_ERR             (1u)        /* error conditions   */
#define RESET_VALUE         (0x00)
#define KIT_NAME            "RZ/A3UL-SMARC"
#define EP_VERSION          "3.0"
#define MODULE_NAME         "Ethernet using FreeRTOS+TCP"
#define BANNER_INFO         "********************************************************************************\r\n"    \
                            "*   Renesas FSP Example Project for "MODULE_NAME " Module         *\r\n"                 \
                            "*   Example Project Version %s                                                *\r\n"     \
                            "*   Flex Software Pack Version  %d.%d.%d                                          *\r\n" \
                            "********************************************************************************\r\n"    \
                            "Refer to readme.txt file for more details on Example Project and              \r\n"      \
                            "RZA FSP Documentation for more information about "MODULE_NAME                            \
                            "                    \r\n"                                                                \
                            "\r\n********************************************************************************\r\n"

#define ETH_PREINIT         "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Ethernet adapter Configuration for Renesas "KIT_NAME ": Pre IP Init       \r\n"            \
                            "--------------------------------------------------------------------------------\r\n\r\n"

#define ETH_POSTINIT        "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Ethernet adapter Configuration for Renesas "KIT_NAME ": Post IP Init       \r\n"           \
                            "--------------------------------------------------------------------------------\r\n\r\n"

#define ETH_CHECK_CONNECT   "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Check the connection for Renesas "KIT_NAME"      \r\n"                                     \
                            "--------------------------------------------------------------------------------\r\n\r\n"

#define SEGGER_INDEX       (0)

#define PRINTF_BUS_SIZE    (2048)

#define APP_PRINT(fn_, ...)        (printf((fn_), ##__VA_ARGS__))

#define APP_ERR_PRINT(fn_, ...)    if (LVL_ERR) { \
        printf("[ERR] In Function: %s(), %s", __FUNCTION__, (fn_), ## __VA_ARGS__);}

#define APP_ERR_TRAP(err)          if (err) {                      \
        printf("\r\nReturned Error Code: 0x%x  \r\n", (unsigned int)err); \
        __asm("BKPT #0\n");}           /* trap upon the error  */

#endif                                 /* COMMON_UTILS_H_ */