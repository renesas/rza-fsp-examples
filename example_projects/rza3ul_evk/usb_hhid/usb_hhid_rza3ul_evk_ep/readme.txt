/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates basic functionalities of USB HHID driver with FreeRTOS on Renesas RZ/A3UL
    MPU based on Renesas FSP. USB HHID driver configures keyboard as a hhid device. on pressing key from
    the keyboard, received keycode is decoded and displayed on the Terminal Emulator.
    Error and info messages will be printed on Terminal Emulator.

2. Hardware Requirements:
    1 USB PC Keyboard 
    1 Board RZ/A3UL Evaluation Board Kit
    1 USB OTG cable

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

4. Hardware Connection:
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
     (3) Connect USB PC Keyboard to USB 0 (OTG) on Carrier board with help of OTG cable.
     (4) Connect (CN14) on Smarc Carrier Board with PC through USB Type-microB Connector.
