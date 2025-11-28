/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
1. Project Overview:
    This Example Project demonstrates the basic functionalities of LCDC device driver
    on Renesas RZ/A3M MPUs based on Renesas FSP. On successful initialization of LCDC module,
    the EP will be able to read the display resolution and frame buffer set in the LCDC module and
    draw color bands to cover the entire screen of external LCD connected to RZA MPUs.
    API Failure messages will be displayed on Terminal Emulator.
 
2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     1 Cable USB A to USB C
     1 MIPI Graphics Expansion Board 2 Version 1 (APP_LCD_EK_MIPI_2)
 
3. Hardware settings:
    Boot Mode:
    Boot mode 4 (3.3-V Single or Quad serial NOR flash memory)
 
    Board:
    EK-RZ/A3M NOR Boot (Exec with DDR SDRAM)

4.  Hardware Connection:
 
    (1) Set for DIP switches and jumper as follow.
 
    - SW4-1 : Don't care 
      SW4-2 : Don't care
      SW4-3 : Don't care
      SW4-4 : Don't care
      SW4-5 : OFF
 
    - SW5-1 : OFF 
      SW5-2 : OFF
      SW5-3 : Don't care
      SW5-4 : OFF
      SW5-5 : Don't care
 
    - JP9   : Link pins 2-3

    (2) Connect MIPI Graphics Expansion Board 2 Version 1 (APP_LCD_EK_MIPI_2) to J32 on Board.
    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.

Note : User can also view the raw image in memory monitor of the e2studio IDE using the address of g_framebuffer
       and specifying the resolution.