/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This Example Project demonstrates the basic functionalities of the MIPI DSI device driver on Renesas RZA MPUs based
    on Renesas FSP. On successful initialization of the MIPI DSI module, the EP will display 8-color bars on the MIPI LCD
    (external LCD connected to RZA MPU) using the graphics and MPI-DSI modules in FSP. A user menu will be provided over 
    the Terminal Emulator. User can choose the time to enter Ultra-Low-Power State(ULPS) and touch the screen to exit this
    mode. Status information and error messages will be printed on Terminal Emulator during the execution of the project.

2. Hardware Requirements:
    1 Board RZ/A3M Evaluation Kit.
    1 Cable USB A to USB C.
    1 MIPI Graphics Expansion Board (included in the kit).

3. Hardware Settings:
    Boot Mode:
    Boot mode 4 (3.3-V Single or Quad serial NOR flash memory)

    Board:
    EK-RZ/A3M NOR Boot (Exec with DDR SDRAM)

4. Hardware Connections:
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

    (2) Connect the MIPI Graphics Expansion Board to J32 of EK-RZA3M.

    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.