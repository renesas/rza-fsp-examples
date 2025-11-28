/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
  The example project demonstrates the use of WDT module with the collaboration of module IRQ, GTM, WDT and button/led. 
  The operation of this EP is as below:
	- Start GTM timer having a callback every 1 second, to refresh WDT and blink the led (LD0 on PMOD LED).
	- If the button BTN0 (on PMOD BUTTON) is pressed, IRQ is triggered, the LED (LD0 on PMOD LED) is OFF and program is 
    exit.

2. Hardware Requirement:
    External Hardware : PMOD LED; PMOD BUTTON

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)
	
    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

    Hardware Connection:

    (1) Connect the UART port (CN14) on RZ/A3UL to the PC using a micro-USB cable.
    (2) Connect the PMOD BUTTON to PMOD1 pin7 → 12.
    (3) Connect the PMOD LED to PMOD0 pin7 → 12.

    <<Setting for Module board>>
    - SW1-1 : OFF 
      SW1-2 : Don't care
    - SW1-3 : OFF

    <<Setting for Carrier board>>
    - SW1    : Don't care
      SW2    : Don't care
      SW3    : Don't care
      SW4    : Don't care
      SW5    : 3-2
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
    (4) Connect the PMOD BUTTON to PMOD1 pin7 → 12.
    (5) Connect the PMOD LED to PMOD0 pin7 → 12.
