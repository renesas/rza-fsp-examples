/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
1. Project Overview:
     This Example Projects demonstrates the basic functionalities of the USB_PCDC driver on Renesas RZA MPUs based on Renesas FSP 
      - On power up or RESET, all LEDs on USER LED start blinking at 1Hz
      - Press SW1 button on Board to change the blinking frequency of the USER LED. 
        With every press SW1 button, the frequency will switch from 1 Hz to 5 Hz to 10 Hz and cycle back.
      - Open the serial port of the device using Terminal Emulator and press Enter key (keyboard on host PC). 
         + Press 1: Show kit information (show kit name, blinking frequency).
         + Press 2: Show URLs to user visit.
 
2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     2 Cable USB A to USB C
 
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

    (2) Connect USB HIGH SPEED on Board with PC through Cable USB A to USB C
    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.