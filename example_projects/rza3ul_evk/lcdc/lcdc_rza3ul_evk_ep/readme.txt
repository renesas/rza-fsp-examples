/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This Example Project demonstrates the basic functionalities of LCDC device driver
    on Renesas RZ/A3UL MPUs based on Renesas FSP. On successful initialization of LCDC module,
    the EP will be able to read the display resolution and frame buffer set in the LCDC module and
    draw color bands to cover the entire screen of external LCD connected to RZA MPUs.
    API Failure messages will be displayed on Terminal Emulator.

2. Hardware Requirements:
    Board RZ/A3UL Evaluation Board Kit
    Mini HDMI to HDMI Cable
    Parallel to HDMI Conversion board
    Display support HDMI port

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)
    
4   Hardware Connection:
    (1) Set for DIP switches and jumpers as follow.

        <<Setting for Module board>>
         - SW1-1 : OFF 
           SW1-2 : Don't care
         - SW1-3 : OFF

        <<Setting for Carrier board>>
         - SW1    : Don't care
           SW2    : Don't care
           SW3    : Don't care
           SW4    : Don't care
           SW5    : Don't care
           SW6    : Don't care
           SW7    : Don't care
           SW8    : Don't care
           SW11-1 : OFF
           SW11-2 : OFF
           SW11-3 : OFF
         - SW11-4 : ON

         - CN4    : Jumper connects 1-3
                    Jumper connects 2-4

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect (CN14) on Smarc Carrier Board with PC through USB Type-microB Connector
    (4) Connect Parallel to HDMI Conversion board to port CN5 of module board.
    (5) Connect Mini HDMI to HDMI Cable to Parallel to HDMI Conversion board
    (6) Connect Mini HDMI to HDMI Cable to Display support HDMI port

Note : User can also view the raw image in memory monitor of the e2studio IDE using the address of g_framebuffer
       and specifying the resolution.