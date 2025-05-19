/***********************************************************************************************************************
 * File Name    : usb_hhid_appl.h
 * Description  : Contains data structures and functions used in usb_hhid_appl.h.
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

#ifndef USB_HHID_APPL_H_
#define USB_HHID_APPL_H_

/* macro definition.*/
#define SET_PROTOCOL               (USB_HID_SET_PROTOCOL | USB_HOST_TO_DEV | USB_CLASS | USB_INTERFACE)
#define BOOT_PROTOCOL              (0U)
#define BUFSIZE                    (8U)
#define DATASIZE                   (12U)
#define TASK_DELAY                 (1U)
#define NULL_CHAR                  ('\0')
#define ROW_SIZE                   (40U)
#define COL_SIZE                   (25U)
#define SET_ZERO                   (0x0000)
#define ONE                        (1U)
#define INDEX                      (2U)
#define BUFF_SIZE                  (25U)
#define KEY_MOD_LSHIFT             (0x02)
#define KEY_MOD_RSHIFT             (0x20)



#define EP_INFO        "This example project demonstrates basic functionalities of USB Host Human \r\n"\
                       "Interface Device. Class (HHID) driver with FreeRTOS on Renesas RZA3UL MPU \r\n"\
                       "based on Renesas FSP. USB HHID driver configures keyboard as a hhid device. \r\n"\
                       "On pressing key from the keyboard, received keycode is decoded and displayed \r\n"\
                       "on the Terminal Emulator. \r\n"\
                       "Error and info messages will be printed on Terminal Emulator.\r\n\n\n"

/* Function declaration */
void deinit_usb(void);

#endif /* USB_HHID_APPL_H_ */
