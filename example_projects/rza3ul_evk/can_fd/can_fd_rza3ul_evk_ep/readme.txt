/***********************************************************************************************************************
 * Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
 *
 * This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
 * be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
 * Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
 * the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
 * intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
 * copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
 * THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
 * TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
 * INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
 * SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
 * TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
 * DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
 * INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
 * LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
 **********************************************************************************************************************/

1. Project Overview:
    The example project shows the operation of CAN-FD running on Renesas RZ MCUs using channel 0 and channel 1 on board. 
	On pressing any key on the Terminal Emulator, data is transmitted from one channel to other.
    On 1st transmission, Channel 0 transmits data to Channel 1. Channel 1 displays the received data.
    On 2nd transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data.
	then Channel 0 changes CAN frame to CANFD frame and updates data
	On 3rd transmission, Channel 0 transmits updated data to Channel 1. Channel 1 displays the received data.
	then Channel 1 changes CAN frame to CANFD frame and updates data to transmits back to Channel 0 as ACK.
	On 4th transmission, Channel 1 transmits updated data to Channel 0 as ACK. Channel 0 displays the received data
	
2. Hardware Requirement:
     Board RZ/A3UL Evaluation Board Kit- must have IC15 (to support CAN port) is on the carrier board.
     PMOD LED

3. Hardware settings:
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
           SW1-2 : OFF
         - SW1-3 : OFF

        <<Setting for Carrier board>>
         - SW1    : Don't care
           SW2    : Don't care
           SW3    : Don't care
           SW4    : Don't care
           SW5    : Don't care
           SW6    : Don't care
           SW7    : 1-2
           SW8    : 1-2
           SW11-1 : OFF
           SW11-2 : OFF
           SW11-3 : OFF
         - SW11-4 : ON

         - CN4    : Jumper connects 1-3
                    Jumper connects 2-4

     (2) Connect the J-Link Base and the connector on the SMARC Module Board with JTAG cable.
         When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
     (3) Connect PMOD0 PIN7-12 on SMARC Carrier Board and PMOD LED.
         Connect CN15 to CN16 (CAN_H, CAN_L, GND)
     (4) Connect (CN14) on Smarc Carrier Board with PC through USB Type-microB Connector.
