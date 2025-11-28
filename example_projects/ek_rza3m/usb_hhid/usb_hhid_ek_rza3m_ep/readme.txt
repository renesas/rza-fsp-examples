/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates basic functionalities of USB HHID driver with FreeRTOS on Renesas RZ/A3M
    MPUs based on Renesas FSP. USB HHID driver configures keyboard as a hhid device. on pressing key from
    the keyboard, received keycode is decoded and displayed on the Terminal Emulator.
    Error and info messages will be printed on Terminal Emulator.

2. Hardware Requirements:
    1 Board RZ/A3M Evaluation Kit.
    1 Cable USB A to USB C.
    1 Hub convert USB C to USB A.
    1 USB PC Keyboard.

3. Hardware settings:
    Boot Mode:
    Boot mode 4 (3.3-V Single or Quad serial NOR flash memory)

    Board:
    EK-RZ/A3M NOR Boot (Exec with DDR SDRAM)

4. Hardware Connection:
    
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

    - JP9   : 1-2 Open
    
    (2) Connect USB PC Keyboard to USB USB HIGH SPEED on board with help of Hub convert USB C to USB A.

    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.