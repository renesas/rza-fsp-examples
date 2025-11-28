/***********************************************************************************************************************
 * File Name    : mipi_dsi_ep.h
 * Description  : Contains data structures and functions used in mipi_dsi_ep.c.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef MIPI_DSI_EP_H_
#define MIPI_DSI_EP_H_

#include "r_mipi_dsi_api.h"

#define MIPI_DSI_DISPLAY_CONFIG_DATA_DELAY_FLAG      ((mipi_dsi_cmd_id_t) 0xF)
#define MIPI_DSI_DISPLAY_CONFIG_DATA_END_OF_TABLE    ((mipi_dsi_cmd_id_t) 0x10)
#define BYTES_PER_PIXEL                              (2)
#define COLOR_BAND_COUNT                             (8)
#define BLUE                                         (0x001F)
#define LIME                                         (0x07E0)
#define RED                                          (0xF800)
#define BLACK                                        (0x0000)
#define WHITE                                        (0xFFFF)
#define YELLOW                                       (0xFFE0)
#define AQUA                                         (0x07FF)
#define MAGENTA                                      (0xF81F)
#define RESET_FLAG                                   (false)
#define SET_FLAG                                     (true)
#define INITIAL_VALUE                                ('\0')
#define SELECT_5S                                    (1U)
#define SELECT_15S                                   (2U)
#define SELECT_30S                                   (3U)
#define SELECT_DISABLE_ULPS                          (4U)
#define GTM_UNITS_SECONDS                            (1)
#define GTM_DESIRED_PERIOD_5SEC                      (5)
#define GTM_DESIRED_PERIOD_15SEC                     (15)
#define GTM_DESIRED_PERIOD_30SEC                     (30)
#define PIN_DISPLAY_INT                              (BSP_IO_PORT_08_PIN_01)
#define PIN_DISPLAY_BACKLIGHT                        (BSP_IO_PORT_10_PIN_02)
#define ENTER_ULPS_DELAY                             (3000000)

#define EP_INFO  "\r\nThis Example Project demonstrates the basic functionalities of the MIPI DSI "\
                  "\r\ndevice driver on Renesas RZA MPUs based on Renesas FSP. On successful initialization "\
                  "\r\nof MIPI DSI module, the EP will display 8-color bars on the MIPI LCD (external LCD"\
                  "\r\nconnected to RZ MPU) using the graphics and MPI-DSI modules in FSP. A user menu "\
                  "\r\nwill be provided over the Terminal Emulator. User can choose the time to enter "\
                  "\r\nUltra-Low-Power State(ULPS) and touch the screen to exit this mode. Status"\
                  "\r\ninformation and error messages will be printed on Terminal Emulator during the"\
                  "\r\nexecution of the project.\r\n\n "

#define MIPI_DSI_MENU               "\r\nSet time to enter Ultra-Low Power State (ULPS):"\
                                    "\r\n1. Input '1' to enter ULPS after 5s."\
                                    "\r\n2. Input '2' to enter ULPS after 15s."\
                                    "\r\n3. Input '3' to enter ULPS after 30s."\
                                    "\r\n4. Input '4' to always display(Default).\r\n"\
                                    "\r\nNote: After entering Ultra Low Power State (ULPS), please touch the screen to"\
                                    "\r\nexit this mode. User input: \r\n\r\n"\

#define MIPI_DSI_INFO_5S            "Enter ULPS after 5 seconds of display\r\n"
#define MIPI_DSI_INFO_15S           "Enter ULPS after 15 seconds of display\r\n"
#define MIPI_DSI_INFO_30S           "Enter ULPS after 30 seconds of display\r\n"
#define MIPI_DSI_INFO_DISABLE_ULPS  "Always display\r\n"

typedef struct
{
    unsigned char        size;
    unsigned char        buffer[10];
    mipi_dsi_cmd_id_t    cmd_id;
    mipi_dsi_cmd_flag_t flags;
} lcd_table_setting_t;

extern const lcd_table_setting_t g_lcd_init_focuslcd[];
void mipi_dsi_push_table (const lcd_table_setting_t *table);
void mipi_dsi_start_display ();
void mipi_dsi_entry(void);
void handle_error (fsp_err_t err,  const char * err_str);

#endif /* MIPI_DSI_EP_H_ */
