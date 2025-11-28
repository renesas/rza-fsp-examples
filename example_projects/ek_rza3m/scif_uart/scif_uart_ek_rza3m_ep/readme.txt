/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
1. Project Overview:
    The example project demonstrates the typical use of the UART HAL module APIs.
    The project initializes the UART with Baud rate of 115200 bps and GTM.
    Using a Terminal Emulator user can provide a value & press enter key to set the cycle of the USER LED signal.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack .

2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     1 Cable USB A to USB C
 
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

    (2) Connect DEBUG1 on Board with PC through Cable USB A to USB C.