/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the SSI HAL module APIs.
    The project transfers sample audio data from source buffer to destination buffer by connecting Tx and Rx pins 
    and compares the transferred data of two buffers. 
    The result of comparison will be displayed on Terminal Emulator.
	
    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disable on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack .

    Steps to enable again the DMAC feature after disabled it:
    - Set DMAC Support to Enable on the main stack of the driver in FSP Configuration. 
    - Add Transfer Driver on r_dmac in the DMAC sub stacks that linked to the main stack
    - In the g_transfer0 SSIF_DMA_TX0, set DMA Activation Request Source Select to Requested by a transfer destination module
    - In the g_transfer1 SSIF_DMA_RX0, set DMA Activation Request Source Select to Requested by a transfer source module

2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     1 USB type C cable

3. Hardware settings:
    Boot Mode:
    Boot mode 4 (3.3-V Single or Quad serial NOR flash memory)
	
    Board:
    EK-RZ/A3M NOR Boot (Exec with DDR SDRAM)

    Hardware Connection:

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

    - JP9   : 1-2 open

    (2) Connect P2_0 (J1) and P8_0 (J2).
	
    (3) Connect the EK board and PC with USB type C cable through port DEBUG1.