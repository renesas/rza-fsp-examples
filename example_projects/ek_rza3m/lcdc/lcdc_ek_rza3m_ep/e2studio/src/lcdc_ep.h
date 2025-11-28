/***********************************************************************************************************************
 * File Name    : lcdc_ep.h
 * Description  : Contains declarations of data structures used in hal_entry.c.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef LCDC_EP_H_
#define LCDC_EP_H_

#define EP_INFO  "The Example Project demonstrates the basic functionalities of LCDC device driver\r\n"\
                 "on Renesas RZA MPUs based on Renesas FSP. On successful initialization of LCDC module,\r\n"\
                 "the example will be able to read the display resolution and frame buffer set in the LCDC module\r\n"\
                 "and draw color bands to cover the screen of external LCD connected to RZA MPUs.\r\n"\
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
