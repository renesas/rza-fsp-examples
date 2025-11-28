/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
1. Project Overview:
    The example project demonstrates the typical use of the RSPI HAL module APIs.
    The project configure RSPI channels (Channel 1 and Channel 0) in Master and Slave mode.
    Once the module is initialised and the channels are configured,
    Master and Slave can transmit and receive data based on commands from user sent through Terminal Emulator.

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

    (2) Connect pins with jumper on J1 of EK-RZ/A3M Board as follows.
	
	     Master                         Slave	
        P1_2 (RSPI1_CK)      -->        P4_5 (RSPI0_CK)
	P1_4 (RSPI1_MISO)    -->	P5_1 (RSPI0_MISO)
	P1_3 (RSPI1_MOSI)    -->	P5_0 (RSPI0_MOSI)
	P2_0 (RSPI1_SSL)     -->	P5_2 (RSPI0_SSL)

    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.