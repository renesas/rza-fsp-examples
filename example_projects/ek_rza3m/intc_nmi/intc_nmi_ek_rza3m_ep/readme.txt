/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
 
1. Project Overview:
     The example project demonstrates the typical use of the INTC NMI module APIs.
     The project initializes the NMI interrupt in Interrupt Controller.
     User is requested to press the button on PMOD BUTTON to trigger the external nmi 
     and this then will start toggling of User LED on-board.
 
2. Hardware Requirement:
     1 Board RZ/A3M Evaluation Kit
     1 Cable USB A to USB C
     1 PMOD BUTTON
 
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
 
    - JP9   : Link pins 2-3

    (2) Connect J1 on PMOD BUTTON and J2 on EK-RZ/A3M Board with jump wire as follows.
        
        J1 (PMOD BUTTON)         J2 (EK-RZ/A3M Board)
        1 --- BTN0      <------->  NMI_L
        2 --- BTN1
        3 --- BTN2
	4 --- BTN3
	5 --- GND       <------->  GND
	6 --- VCC       <------->  +3.3V
    (3) Connect DEBUG1 on Board with PC through Cable USB A to USB C.