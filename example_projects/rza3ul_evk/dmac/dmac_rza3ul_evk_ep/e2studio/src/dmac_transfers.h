/***********************************************************************************************************************
 * File Name    : dmac_transfers.h
 * Description  : Contains data structures and functions used in dmac_transfers.h
 **********************************************************************************************************************/
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

#ifndef DMAC_TRANSFERS_H_
#define DMAC_TRANSFERS_H_

#define NEW_LINE    ('\n')    // new line character
#define NULL_CHAR   ('\0')    // end of string character

#define EP_INFO    "\r\nProject initializes 2 DMAC transfer instances.Upon successful\r\n" \
                     "initialization,a menu option is displayed. On selecting 1 from menu \r\n" \
                     "option,GTM generates 100ms interrupt to trigger a transfer from the \r\n" \
                     "source buffer to port control register for 60 times indicated by LED \r\n" \
                     "blinking for 60 times. On selecting 2 from menu option,DMAC (runs in \r\n" \
                     "Block mode) transfers data from the MTU counter register to destination \r\n"\
                     "which gets printed to Terminal Emulator. \r\n\r\n"


#define MENU        "\r\nPress 1 to transfer source array to LED Port in normal mode.\
                     \rPress 2 to transfer MTU current timer value.\n"

/* Perform transfer led blink operation */
void transfer_led_blink_operation(void);

/* Perform transfer mtu3 timer operation  */
void transfer_mtu_value(void);

#endif
