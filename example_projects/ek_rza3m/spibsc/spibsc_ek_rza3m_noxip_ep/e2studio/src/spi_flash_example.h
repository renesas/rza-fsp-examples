/*
 * Copyright [2020-2025] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 */

#ifndef SPI_FLASH_EXAMPLE_H
#define SPI_FLASH_EXAMPLE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/** Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define MODULE_NAME    "SPIBSC"
#define EP_VERSION              "3.5.0"

#define BANNER_1       "\r\n********************************************************************************"\
                       "\r\n*   Renesas FSP Example Project for "MODULE_NAME" Module                              *"\
                       "\r\n*   Example Project Version "EP_VERSION"                                              *"\
                       "\r\n*   Flex Software Pack Version "
#define BANNER_2       "                                           *"
#define BANNER_3       "\r\n********************************************************************************"\
                       "\r\nRefer to readme.txt file for more details on Example Project and" \
                       "\r\nFSP User's Manual for more information about "MODULE_NAME" driver\r\n"

#define EP_INFO        "This example project demonstrates the erase and write functionalities of the SPI flash"\
	                   " device\r\non RZ/A3M MPU based on Renesas FSP. \r\n"\
                       "The sample code is executed by selecting the menu number on the console. \r\n"\
                       "In main menu, user selects operation for the flash device. \r\n"\
                       "    1. Erase and verify.\r\n"\
                       "    2. Write random data and verify.\r\n"\
                       "And then, user inputs the target address and size. \r\n"\
                       "After, the sample code execute the operation and show the result.\r\n"\
					   "LED blinks while running the project.\r\n"

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/
extern void      example_init(void);
extern fsp_err_t example_erase(uint32_t address, uint32_t size);
extern fsp_err_t example_write(const uint8_t * data, uint32_t address, uint32_t size);

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
