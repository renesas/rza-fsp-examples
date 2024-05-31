/***********************************************************************************************************************
* Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
* This software is supplied by Renesas Electronics America Inc. and may only be used with products of Renesas Electronics Corp.
* and its affiliates (“Renesas”).  No other uses are authorized.  This software is protected under all applicable laws, 
* including copyright laws.
* Renesas reserves the right to change or discontinue this software.
* THE SOFTWARE IS DELIVERED TO YOU “AS IS,” AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND TO THE FULLEST EXTENT 
* PERMISSIBLE UNDER APPLICABLE LAW,DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY, INCLUDING WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE SOFTWARE.  TO THE MAXIMUM 
* EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE (OR ANY PERSON 
* OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER, INCLUDING, WITHOUT LIMITATION, 
* ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES;
* ANY LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF 
* THE POSSIBILITY OF SUCH LOSS,DAMAGES, CLAIMS OR COSTS.
* **********************************************************************************************************************/

1. Project Overview:
     This Example Projects demonstrates the basic functionalities of the USB_PCDC driver on Renesas RZA MCUs based on Renesas FSP 
      - On power up or RESET, all LEDs on PMOD LED start blinking at 1Hz
      - Press BTN0 button of PMOD BUTTON to change the blinking frequency of the PMOD LED. 
        With every press BTN0 button, the frequency will switch from 1 Hz to 5 Hz to 10 Hz and cycle back.
      - Open the serial port of the device using Terminal Emulator and press Enter key (keyboard on host PC). 
         + Press 1: Show kit information (show kit name, blinking frequency).
         + Press 2: Show URLs to user visit.

2. Hardware Requirement: 
      1 Board RZ/A3UL Evaluation Board Kit 
      1 PMOD LED 
      1 PMOD BUTTON 

3. Hardware Settings : 
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
      (2) Connect the J-Link Base and the connector on the SMRAC Module Board with JTAG cable
          When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required
      (3) Connect PMOD LED to PMOD 0 (PIN 7 -> PIN 12)
      (4) Connect PMOD BUTTON to PMOD 1 (PIN 7 -> PIN 12)
      (5) Connect USB0 (OTG)-CN11 on board to PC via Micro-USB device cable.