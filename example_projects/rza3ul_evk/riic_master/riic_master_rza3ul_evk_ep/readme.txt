/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the typical use of the RIIC master HAL module APIs.
    The project initializes RIIC master module with fast mode and interfaces with PmodACL™ Board for ADXL345.

    On power up after establishing the connection of sensor with RZ/A3UL board, it displays accelerometer axis data on
    Terminal Emulator. Any API/event failure will be displayed on Terminal Emulator.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack .

2. Hardware Requirement:
    External Hardware : Pmod ACL

3. Hardware Settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)
	
    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

    Hardware Connection:
    
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
     
    (2) Connect the J-Link Base and the connector on the SMRAC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.
    (4) Connect Pmod ACL and SMARC Carrier Board as follows.
        Pmod ACL has two on board connectors, J2 is used for I2C communication.

        J2 (Pmod ACL)                   PMOD1 (SMARC Carrier Board)
                                        -------
                                        |1   7|
        ------                          |2   8|
        |1  5|---SCL  --->  RIIC1_SCL---|3   9|
        |2  6|---SDA  --->  RIIC1_SDA---|4  10|
        |3  7|---GND  --->  GND pin  ---|5  11|
        |4  8|---VCC  --->  VCC pin  ---|6  12|
        ------                          -------

        JP1 on Pmod ACL should be set to position 2-3. (Connect SDO/ALTADDR and GND.)
