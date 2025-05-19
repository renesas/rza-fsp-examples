/***********************************************************************************************************************
 * File Name    : sdhi_ep.h
 * Description  : Contains data structures and functions used in sdhi_thread_entry.c
 **********************************************************************************************************************/
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

#ifndef SDHI_EP_H_
#define SDHI_EP_H_

/* Macros used in sdhi Example Project */
#define EP_INFO        "This example project demonstrates basic functionalities of sdhi \r\n"\
                       "driver with FreeRTOS+FAT file system on Renesas RZ/A MPU based on Renesas FSP.\r\n"\
                       "FreeRTOS+FAT uses the underlying Block media driver which utilizes SDHI driver to perform\r\n"\
                       "file operations on the SD Card devices.\r\n"\
                       "Error and info messages will be printed on Terminal Emulator.\r\n\r\n"

#define SDHI_EP_NOTE   "Please remove and re-insert the SD Card after executing Safely Remove & \r\n"\
                       "Initialize FreeRTOS+FAT command"

#define FILE_NAME               "rza_sdhi.txt"    // File name
#define WRITE_MODE              "w"               // File Write mode
#define READ_MODE               "r"               // File Read mode

#define BUFFER_SIZE_DOWN        (16)              // Size of the buffer for terminal input to target from host (Usually keyboard input) (Default: 16)
#define SD_WRITE                (1u)              // Terminal Emulator Input selection for write operation
#define SD_FORMAT               (2u)              // Terminal Emulator Input selection for format operation
#define SAFELY_EJECT_SD_CARD    (3u)              // Terminal Emulator Input selection for safely eject operation
#define SD_DISPLAY_CWD          (4u)              // To display CWD content
#define SD_INIT                 (5u)              // Terminal Emulator Input selection for Re-initialization of SDHI
                                                  // Valid only after Safely_Eject option is executed.

#define BUFFER_SIZE             (10240u)          // The number of elements to read
#define FF_FS_ADD_FAILURE       (0)
#define ASCII_CHAR_A            (65)

/* SDHI Menu options */
#define SDHI_MENU              "\r\nSD Card Menu options\r\n"\
                                "1. Write 10k data from app_buffer to "FILE_NAME" file\r\n"\
                                "2. Format SD Card Device\r\n"\
                                "3. Safely Remove the SD Card\r\n"\
                                "4. Display content of Current Working Directory\r\n"\
                                "5. Initialize FreeRTOS+FAT (Valid only after Safely_Eject option is executed)\r\n"

#endif /* SDHI_EP_H_ */
