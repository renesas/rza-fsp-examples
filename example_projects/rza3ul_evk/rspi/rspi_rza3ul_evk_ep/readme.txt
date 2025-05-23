/*
 * Copyright [2020-2025] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 */

1. Project Overview:
    The example project demonstrates the typical use of the RSPI HAL module APIs.
    The project configure RSPI channels (Channel 1 and Channel 0) in Master and Slave mode.
    Once the module is initialised and the channels are configured,
    Master and Slave can transmit and receive data based on commands from user sent through Terminal Emulator.

    This project supports the DMAC feature. In cases where this feature is not used in the application,
    please invalid the DMAC feature by the following steps.
    - Set DMAC Support to Disabled on the main stack of the driver in FSP Configuration. 
    - Remove the DMAC sub stacks that linked to the main stack .

2. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)

    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

    Hardware connections:

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
           SW5    : 1-2
           SW6    : 1-2
           SW7    : 1-2
           SW8    : 1-2
           SW11-1 : OFF
           SW11-2 : OFF
           SW11-3 : OFF
         - SW11-4 : ON

         - CN4    : Jumper connects 1-3
                    Jumper connects 2-4

    (2) Connect the J-Link Base and the connector on the SMRAC Module Board with JTAG cable.
        When connecting the conversion adapter "J-Link 9-pin Cortex-M Adapter" made by SEGGER will be required.
    (3) Connect with PC through USB Type-microB Connector (CN14) on Smarc Carrier Board.
    (4) Connect pins with jamper as follows.

        PMOD1 (SMARC Carrier Board)     PMOD0 (SMARC Carrier Board)
        ------------------              ------------------
        |6  5  4  3  2  1|              |6  5  4  3  2  1|
        |12 11 10 9  8  7|              |12 11 10 9  8  7|
        ------------------              ------------------
		            
        MISO  ----> P4_2(PMOD0 PIN3) - P2_3(PMOD1 PIN8)
        MOSI  ----> P4_1(PMOD0 PIN2) - P2_2(PMOD1 PIN7)
        CK    ----> P4_0(PMOD0 PIN4) - P1_0(PMOD0 PIN8)
        SSL   ----> P4_3(PMOD0 PIN1) - P1_3(PMOD0 PIN9)
  
NOTE: 
    User is expected to enter data of size not exceeding 64 bytes. As RSPI bit width is set to 32 bits, 
    each 4 bytes of user data input will be transferred in single RSPI transmission.
    The bytes sent for master should be bigger than the bytes sent for slave when using WriteRead operation.
    Operation is not guaranteed for any user input value other than integer, char(i.e. float, special char) 
    through Terminal Emulator.
﻿