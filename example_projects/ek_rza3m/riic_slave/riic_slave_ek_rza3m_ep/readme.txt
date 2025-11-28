/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates typical use of the RIIC slave HAL module APIs.
    The project initializes RIIC slave and RIIC master module with standard rate
    and is made interfaced with loop-back mechanism. It performs Slave read and 
    write operation continuously once initialization is successful. On successful 
    I2C transaction (6 bytes), Data transceived is compared. Led blinks on data 
    match else it is turned ON as sign of failure. Output message for both 
    corresponding slave operations is displayed on Terminal Emulator. Any API/event
    failure message is also displayed.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack .

2. Hardware Requirement:
    1 Board RZ/A3M Evaluation Kit.
    1 Cable USB A to USB C.

3. Hardware Settings:
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
    
    (2) Connect SDA pins and SCL pins between 2 channels

        |Pin Header J2 (Board)  |     Pin Header J1 (Board)|
        |-----------------------|--------------------------|
        |  Pin 14|---SDA0  <----|---->  SDA1---|Pin 2|     |
        |  Pin 16|---SCL0  <----|---->  SCL1---|Pin 4|     |
        |-----------------------|--------------------------|

    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.