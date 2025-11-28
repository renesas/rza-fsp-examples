/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates typical use of the RIIC slave HAL module APIs.
    The project initializes RIIC slave and RIIC master module with standard rate and is made interfaced with loop-back mechanism.
    It performs Slave read and write operation continuously once initialization is successful. On successful I2C transaction
    (6 bytes), Data transceived is compared. Led blinks on data match else it is turned ON as sign of failure.
    Output message for both corresponding slave operations is displayed on Terminal Emulator.
    Any API/event failure message is also displayed.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack.
    
2. Hardware Requirements:
    1 Board RZ/A3UL Evaluation Board Kit.
    1 PMOD LED.

3. Hardware Settings (for both) : 
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
           SW3    : 1-2
           SW4    : 1-2
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

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.
    (4) Connect the pin SDA (RIIC1_SDA ; PMOD1 Pin4) and pin SCL (RIIC1_SCL ; PMOD1 Pin3) between 2 board : Master board and Slave Board
        Connect PMOD LED to PMOD0 (pin 7-12) on both boards. 

Note:
	(1) Need to run the example on Slave Board first, then run the example on Master board.
	    Make sure the slave board in operation when start running master board.
