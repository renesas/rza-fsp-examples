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