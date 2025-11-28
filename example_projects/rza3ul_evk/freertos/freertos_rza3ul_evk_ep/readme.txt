/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
	The example projects demonstrates Message Queue and Semaphore between tasks and interrupt. Message Queue is 
	demonstrated between Tasks and between Task and interrupt. GTM timer periodically generates interrupt at 1000msec. 
	For first few seconds, messages are shared between Sender and Receiver Tasks and GTM ISR0. Receiver task pends on 
	Message Queue, receives and displays message received on TeraTerm periodically at 500msec. For next few seconds, 
	Semaphore Task waits for sempahore until it is released by GTM ISR1. GTM ISR1 releases semaphore periodically 
	at 1000msec. All the tasks run with equal priority level.

2. Hardware Requirement:
     1 Board RZ/A3UL Evaluation Board Kit

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)
    
4.  Hardware Connection:

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

    (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.