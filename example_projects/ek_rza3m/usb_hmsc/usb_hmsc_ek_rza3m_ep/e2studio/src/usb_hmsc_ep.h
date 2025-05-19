/***********************************************************************************************************************
 * File Name    : usb_hmsc_ep.h
 * Description  : Contains data structures and functions used in usb_hmsc_ep.h.
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

#ifndef USB_HMSC_EP_H_
#define USB_HMSC_EP_H_

/* Macros used in usb_hmsc Example Project */
#define EP_INFO        "\r\nThis example project demonstrates basic functionalities of USB Host Mass Storage Class\r\n"\
                       "(HMSC) driver with FreeRTOS+FAT file system on Renesas RZA MPUs based on Renesas FSP.\r\n"\
                       "FreeRTOS+FAT uses the underlying Block media driver which utilizes USB HMSC driver to perform\r\n"\
                       "file operations on the USB storage devices.\r\n"\
                       "Error and info messages will be printed on Tera Term.\r\n"

#define FILE_NAME               "rza_usb.txt"      // File name
#define WRITE_MODE              "w"               // File Write mode
#define READ_MODE               "r"               // File Read mode

#define USB_WRITE               (1u)              // Terminal Emulator Input selection for write operation
#define USB_FORMAT              (2u)              // Terminal Emulator Input selection for format operation
#define USB_SAFELY_EJECT        (3u)              // Terminal Emulator Input selection for safely eject operation
#define USB_INIT                (4u)              // Terminal Emulator Input selection for Re-initialization of USB
                                                  // Valid only after Safely_Eject option is executed.

#define WRITE_ITEM_SIZE         (10240u)          // The number of elements to read
#define SUCCESS                 (0)
#define READ_WRITE_FAILURE      (0)
#define ASCII_CHAR_A            (65)

/* USB Drive HMSC Menu options */
#define USB_HMSC_MENU           "\r\nUSB HMSC Menu options\r\n"\
                                "\r\n 1. Write 10k data from app_buffer to rza_usb.txt file\r\n"\
                                "\r\n 2. Format USB Drive\r\n"\
                                "\r\n 3. Safely Eject the USB Drive\r\n"\
                                "\r\n 4. Initialize FreeRTOS+FAT (Valid only after Safely_Eject option is executed)\r\n"

/* Global Variables */
static uint8_t g_file_data[WRITE_ITEM_SIZE]    USB_BUFFER_PLACE_IN_SECTION;   /* Data(10k) to write to file */
static uint8_t g_read_buffer[WRITE_ITEM_SIZE]  USB_BUFFER_PLACE_IN_SECTION;   /* Variable to store the data read from file */


extern FF_Disk_t g_my_disk;                                      /* Pointer to store FreeRTOS+FAT disk structure */
/* Function Declarations */
void process_usb_operation(uint8_t p_input_buffer);     /* Processes USB operations */
void usb_write_operation(void);                         /* Performs USB write operation */
void usb_read_operation(void);                          /* Performs USB read operation */
void format_usb_device(void);                           /* Performs USB format operation */
bool check_usb_connection(void);                        /* Checks the USB connection status */
void usb_safely_eject(void);                            /* Performs USB Safely disconnect operation */
void update_buffer(void);                               /* Update write buffer with data and clear read buffer */
fsp_err_t usb_init(void);                               /* Initialize USB HMSC device */
void fat_clean_up(void);                                /* Closes FreeRTOS+FAT */

#endif /* USB_HMSC_EP_H_ */
