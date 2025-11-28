/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the function of r_adc_c driver.
    The example project demonstrates the typical use of the ADC HAL module APIs.
    The project initializes the ADC in single scan or repeat scan mode based on user selection in RZ/A3UL configuration.
    Once initialized, user can initiate the ADC scan and also stop the scan (in the case of repeat scan mode) using 
    Tera Term by sending commands.
    Result and ADC status is displayed on the Tera Term.
	
2. Hardware Requirement:
    External Hardware : External Variable Power Supply Unit (Rheostats 10K).

3. Hardware settings:
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
    (4) Connect CN1 CH0 (ADC_CH0) on SMRAC Module Board and External Variable Power Supply Unit (Rheostats 10K).