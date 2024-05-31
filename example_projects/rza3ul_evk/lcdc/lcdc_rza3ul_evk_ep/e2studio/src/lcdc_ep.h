/***********************************************************************************************************************
 * File Name    : lcdc_ep.h
 * Description  : Contains declarations of data structures used in hal_entry.c.
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

#ifndef LCDC_EP_H_
#define LCDC_EP_H_

#define EP_INFO  "The Example Project demonstrates the basic functionalities of LCDC device driver\r\n"\
                 "on Renesas RZA MCUs based on Renesas FSP. On successful initialization of LCDC module,\r\n"\
                 "the example will be able to read the display resolution and frame buffer set in the LCDC module\r\n"\
                 "and draw color bands to cover the screen of external LCD connected to RZA MCU.\r\n"\
                 "Additionally, API Failure messages will be displayed on Terminal Emulator.\r\n\n\r\n"\

/* RGB 16-bit color format*/
#ifdef DISPLAY_IN_FORMAT_16BITS_RGB565_0
    #define BYTES_PER_PIXEL  (2)       //16 bit format
    #define RED              (0xF800)
    #define GREEN            (0x07E0)
    #define BLUE             (0x001F)
    #define BLACK            (0x0000)
    #define WHITE            (0xFFFF)
    #define YELLOW           (0xFFE0)
    #define MAGENTA          (0xF81F)
    #define CYAN             (0x07FF)
#endif

#define X1_CO_ORDINATE      (0U)
#define Y1_CO_ORDINATE      (0U)
#define COLOR_BAND_COUNT    (8U)
#define INC_DEC_VALUE       (1)


#endif /* LCDC_EP_H_ */
