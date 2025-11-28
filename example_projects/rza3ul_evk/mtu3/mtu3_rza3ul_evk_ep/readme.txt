/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates typical use of MTU3 HAL module APIs.
    User has the provision to input value as per displayed menu through a terminal application to select different MTU3 
    supported modes(Periodic, PWM, One-Shot). 
    In periodic mode, user can enter the time period within the permitted ranges to change the frequency of the user LED. 
    In PWM mode, user can enter the duty cycle within the specified range to adjust the intensity of the user LED. 
    In One-Shot mode, output will be displayed on a terminal application. 
    Any failure will also be displayed on a terminal application.

2. Hardware Requirement:
    External Hardware : Pmod LED

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
    (4) Connect PMOD0 PIN7-12 on SMRAC Carrier Board and Pmod LED.

NOTE: 
    1.Timer period range in millisecond as EP configuration: 
        - RZ/A3UL    --    (1 to 1342) ms 

    2.Operation is not guaranteed for any user input value other than integer(i.e. float, char, special char) through
      a terminal application.