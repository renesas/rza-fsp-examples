/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates the erase and write functionalities of the SPI flash device on RZ/A3M MPU based
    on Renesas FSP.
    The sample code is executed by selecting the menu number on the console.
    In main menu, user selects operation for the flash device.
        1. Erase and verify.
        2. Write random data and verify.
    And then, user inputs the target address and size.
    After, the sample code execute the operation and show the result.
    LED blinks while running the project.

2. Hardware Requirements:
    None

3. Hardware Settings:
    Boot Mode:
    Boot mode 4 (3.3-V Single or Quad serial NOR flash memory)

    Board:
    EK-RZ/A3M (Exec with DDR SDRAM)

    Hardware Connection:

    (1) Set for DIP switches and jumpers as follow.

         - SW5-1 : OFF 
           SW5-2 : OFF
           SW5-3 : OFF
           SW5-4 : OFF
           SW5-5 : OFF
         - SW4-1 : OFF 
           SW4-2 : OFF
           SW4-3 : OFF
           SW4-4 : OFF
           SW4-5 : OFF
         - J9    : Jumper connects 2-3

     (2) Connect the EK-RZ/A3M and PC with USB type C cable through port DEBUG1.
