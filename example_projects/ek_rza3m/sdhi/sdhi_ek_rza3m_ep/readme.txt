/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    This example project demonstrates basic functionalities of sdhi driver with FreeRTOS+FAT file system on Renesas
    RZ/A3M MPU based on Renesas FSP. FreeRTOS+FAT uses the underlying Block media driver.
    The Block media driver utilizes SDHI driver to perform file operations on the SD Card.
    Error and info messages will be printed on Terminal Emulator.

2. Hardware Requirements:
    1 Board RZ/A3M Evaluation Kit
    1 USB type C cable
    External Hardware : Micro SD Card

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
    - J15   : 2-3 connected
    
    (2) Connect the EK board and PC with USB type C cable through port DEBUG1.
    (3) Insert micro sd card into card slot(J11) on the EK-RZ/A3M.

NOTE:
0. SD channel 0 is supported.
1. Format the SD Card as FAT32 before performing any operation.
2. Data written can also be manually verified in file rza_sdhi.txt.
3. User is expected to execute "safely remove SD Card" option before removing SD Card else further file operations may fail and
   SD Card data may get corrupted.
4. User has to remove and re-insert the SD Card after executing the "safely remove SD Card" & "Initialize FreeRTOS+FAT" option.
5. If SD Card is removed without "safely remove SD Card" option, user is recommended to perform "safely remove SD Card" and
   "Initialize FreeRTOS+FAT" commands in sequence. This will make sure no operations fails after unexpected removal of SD Card.
6. Operation is not guaranteed for any user input value other than integer, char(i.e. float, special char) through
   Terminal Emulator input.