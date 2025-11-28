/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

1. Project Overview:
    The example project demonstrates the use of the FreeRTOS + TCP Module with Ethernet.
    The example project demonstrates the usage of FreeRTOS DHCP Client, DNS Client and ICMP code.
    - This Example Project has 2 modes for the user:
    1. DHCP Mode, where the IP credentials are obtained from the DHCP Server on the Network.
    2. Static IP Address mode, where in the Static IP address can be configured for the Ethernet based on 
       the Availability of free address in the LAN.
    Besides this example also checks, calculates, and shows the send and response time between 
    the target board and server.
    NOTE: User is expected to enter the static IP address according to the network settings of the LAN.
	  For example, set up Static IP Configuration in g_rm_freertos_plus_tcp0 -> FreeRTOS+TCP Wrapper to r_gether as below:
		static uint8_t ucMACAddress[6]       = {0x00, 0x11, 0x33, 0x55, 0x77, 0x99};
		static uint8_t ucIPAddress[4]        = {192, 168, 3, 109};
		static uint8_t ucNetMask[4]          = {255, 255, 255, 0};
		static uint8_t ucGatewayAddress[4]   = {192, 168, 3, 1};
		static uint8_t ucDNSServerAddress[4] = {8, 8, 8, 8};
          In case of DHCP, User just needs to run the application and DHCP client will communicate 
          to the DHCP server and gets the IP address.

    NOTE: While running the application using DHCP or Static Address mode, 
          The following settings needs to be done in the configurator.     
          The same projects can be used for both the settings.
    
    DHCP mode
      At FreeRTOS+TCP config stack change to table below:
      +----------------------------------+-----------+
      | FreeRTOS+TCP                     | Static IP |
      +----------------------------------+-----------+
      | Use DHCP                         | Enable    |
      +----------------------------------+-----------+
      | DHCP Register Hostname           | Enable    |
      +----------------------------------+-----------+
      | DHCP Uses Unicast                | Enable    |
      +----------------------------------+-----------+
      | DHCP Send Discover After Auto IP | Enable    |
      +----------------------------------+-----------+
      | DHCP callback function           | Enable    |
      +----------------------------------+-----------+

    Static IP Address mode
      After run DHCP Mode we change IPv4 Address, Subnet Mask, Default Gateway, DNS Servers for Static IP config 
      depending DHCP config printed at the console.
      At FreeRTOS+TCP config stack change to table below:
      +----------------------------------+-----------+
      | FreeRTOS+TCP                     | Static IP |
      +----------------------------------+-----------+
      | Use DHCP                         | Disable   |
      +----------------------------------+-----------+
      | DHCP Register Hostname           | Disable   |
      +----------------------------------+-----------+
      | DHCP Uses Unicast                | Disable   |
      +----------------------------------+-----------+
      | DHCP Send Discover After Auto IP | Disable   |
      +----------------------------------+-----------+
      | DHCP callback function           | Disable   |
      +----------------------------------+-----------+

2. Hardware Requirement:
    External Hardware : None

3. Hardware settings:
    Boot Mode:
    Boot mode 3 (1.8-V Single, Quad, or Octal serial flash memory)
	
    Board:
    RZ/A3UL Evaluation Board Kit QSPI Edition  (Exec with DDR SDRAM)
    RZ/A3UL Evaluation Board Kit QSPI Edition  (eXecute-In-Place)
    RZ/A3UL Evaluation Board Kit OCTAL Edition (eXecute-In-Place)

    Hardware Connection:

    (1) Connect the UART port (CN14) on RZ/A3UL to the PC using a micro-USB cable.
    (2) Connect the Ethernet port 1 on RZ/A3UL to the public router using a LAN cable.

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
    (4) Connect the Ethernet port 1 on RZ/A3UL to the public router using a LAN cable.