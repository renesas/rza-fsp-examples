/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the function of GTM driver.
    The project initializes the periodic Timer and one-shot Timer. (UART used to communicate.)
    Using a Terminal Emulator user can provide a value & press enter key to set the period of the Pmod LED signal.
    The range of input values are displayed on the Terminal Emulator.
    Any failure will also be displayed using Terminal Emulator.

2. Hardware Requirement:
    External Hardware : Pmod LED

3. Hardware settings:
    Boot Mode:
     Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
     RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
     RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
     RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

    Hardware Connection:

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

    (2) Connect the J-Link Base and the connector on the SMRAC Module Board with JTAG cable.
         When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.
    (4) Connect PMOD0 PIN7-12 on SMRAC Carrier Board and Pmod LED.