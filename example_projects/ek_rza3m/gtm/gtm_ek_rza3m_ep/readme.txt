/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the function of GTM driver.
    The project initializes the periodic Timer and one-shot Timer. (UART used to communicate.)
    Using a Terminal Emulator user can provide a value & press enter key to set the period of the User LED on-board.
    The range of input values are displayed on the Terminal Emulator.
    Any failure will also be displayed using Terminal Emulator.

2. Hardware Requirement:
    1 Board RZ/A3M Evaluation Kit
    1 USB type C cable

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

    - JP9   : Jumper open 1-2

    (2) Connect the EK board and PC with USB type C cable through port DEBUG1.