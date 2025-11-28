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
	
    (2) Connect the EK board and PC with USB type C cable through port DEBUG1.