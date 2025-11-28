/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the INTC IRQ module APIs
    The project initializes the IRQ interrupt in Interrupt Controller 
    User is requested to press the push button to trigger the external irq and this then will start toggling of user LED.

2. Hardware Requirement:
    1 Board RZ/A3M Evaluation Kit.
    1 Cable USB A to USB C.

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
    
    (2) Connect DEBUG1 on Board with PC through Cable USB A to USB C.