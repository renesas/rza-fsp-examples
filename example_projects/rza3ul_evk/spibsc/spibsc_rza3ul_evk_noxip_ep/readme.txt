/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates the erase and write functionalities of the SPI flash device on RZ/A3UL MPU based
    on Renesas FSP.
    The sample code is executed by selecting the menu number on the console.
    In main menu, user selects operation for the flash device.
        1. Erase and verify.
        2. Write random data and verify.
    And then, user inputs the target address and size.
    After, the sample code execute the operation and show the result.
    LED blinks while running the project.

2. Hardware Requirements:
    External Hardware : Pmod LED

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)

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
