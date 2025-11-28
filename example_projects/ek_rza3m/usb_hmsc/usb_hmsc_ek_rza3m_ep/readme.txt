/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    - The sample code accompanying this file shows the operation of USB_HMSC running on Renesas RZ MPUs using RZ/A board, USB.
    - Format the USB driver with FAT32 file system before performing any operation
    - After successful USB connection with PC, the Terminal Emulator shows menu options with 4 options
    - The user select option 1 to write 10K data from app_buffer
    - The user enters data into the Terminal Emulator, and the data is saved to the rza_usb.txt file
    - The user select option 2 to Format USB Driver
    - The user select option 3 to Safely Eject the USB Driver before removing USB
    - The user select option 4 to Initialize FreeRTOS+FAT (Valid only after Safely_Eject option is executed)	
	
2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     1 USB type C cable

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

    - JP9   : 1-2 open

    (2) Connect the Type-C port of EK-RZ/A3M to the hub.
    (3) Connect USB into one of the USB Type-A ports on the hub.
    (4) Connect the EK board and PC with USB type C cable through port DEBUG1.