/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    Project initializes 2 DMAC transfer instances. Upon successful initialization, a menu option is displayed.
    On selecting 1 from menu option, GTM generates 100ms interrupt to tringer a transfer from the source buffer
    to port control register for 60 times indicated by LED blinking for 60 times.
    On selecting 2 from menu ontion, DMAC (runs in Block mode) transfers data from the MTU counter register to
    destination which gets printed to Terminal Emulator.

2. Hardware Requirements:
    Board RZ/A3UL Evaluation Board Kit
    1 PMOD LED for each board

3. Hardware Settings (for both):
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

    (2) Connect the J-Link Base and the connector on the SMRAC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.
    (4) Connect PMOD LED to PMOD0 (pin 7-12).