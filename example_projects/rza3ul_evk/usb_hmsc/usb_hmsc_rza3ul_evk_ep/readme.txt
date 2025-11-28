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
    N/A
	
3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad serial flash memory)
	
    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)

    Note: RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place) is not supported in rza-fsp-example v3.5

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
    (4) Connect USB with USB 1 (Host) of Carrier Board.