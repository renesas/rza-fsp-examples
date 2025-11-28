/***********************************************************************************************************************
 * File Name    : usr_app.h
 * Description  : Contains macros, data structures and functions used  in the Application
 ***********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#ifndef USR_APP_H_
#define USR_APP_H_

#if (ipconfigUSE_DHCP != 0)
 #include "FreeRTOS_DHCP.h"
#endif

#define USR_TEST_DOMAIN_NAME         "www.google.com"
#define USR_TEST_PING_IP             "8.8.8.8"
#define USR_PING_COUNT               (10)
#define BYTES_DATA_SEND              (8)
#define KIT_NAME                     "RZ/A3UL-SMARC"

#define SUCCESS                      (0)
#define PRINT_UP_MSG_DISABLE         (0x01UL)
#define PRINT_DOWN_MSG_DISABLE       (0x02UL)
#define PRINT_NWK_USR_MSG_DISABLE    (0x04UL)

#define ETHERNET_LINK_DOWN           (0x01)
#define ETHERNET_LINK_UP             (0x00)
#define IP_LINK_DOWN                 (0x02)
#define IP_LINK_UP                   (0x00)

#define ETH_PREINIT         "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Ethernet adapter Configuration for Renesas "KIT_NAME ": Pre IP Init       \r\n"            \
                            "--------------------------------------------------------------------------------\r\n\r\n"

#define ETH_POSTINIT        "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Ethernet adapter Configuration for Renesas "KIT_NAME ": Post IP Init       \r\n"           \
                            "--------------------------------------------------------------------------------\r\n\r\n"

#define ETH_CHECK_CONNECT   "\r\n\r\n--------------------------------------------------------------------------------\r\n" \
                            "Check the connection for Renesas "KIT_NAME"      \r\n"                                     \
                            "--------------------------------------------------------------------------------\r\n\r\n"

typedef struct st_ping_data
{
    uint32_t sent;                     // Ping Request
    uint32_t received;                 // Ping Response
    uint32_t lost;                     // Ping failure
} ping_data_t;

typedef enum e_ping_reply_status
{
    NO_PING      = 0,
    PING_SUCCESS = 1,
    INVALID_DATA = 2,
} ping_reply_status_t;

typedef struct st_ping_status
{
    uint32_t               id;
    uint32_t               time;       //Current ping time in microsecond.
    ping_reply_status_t    status;
} ping_status_t;

#if (ipconfigUSE_DHCP != 0)
void update_dhcp_response_to_usr(void);

#endif

#if (ipconfigUSE_DHCP != 0)
eDHCPCallbackAnswer_t xApplicationDHCPHook(eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress);

#endif

#if (ipconfigDHCP_REGISTER_HOSTNAME == 1)

/* DHCP has an option for clients to register their hostname.  It doesn't
 * have much use, except that a device can be found in a router along with its
 * name. If this option is used the callback below must be provided by the
 * application writer to return a const string, denoting the device's name. */
const char * pcApplicationHostnameHook(void);

#endif                                 /* ipconfigDHCP_REGISTER_HOSTNAME */

uint32_t ulApplicationGetNextSequenceNumber(uint32_t ulSourceAddress,
                                            uint16_t usSourcePort,
                                            uint32_t ulDestinationAddress,
                                            uint16_t usDestinationPort);
uint32_t   ul_rand();
uint32_t   is_network_up(void);
BaseType_t v_send_ping(const char * pcIPAddress);
void       print_ipconfig(void);
void       print_ping_result(void);
void       dns_querry_func(char * domain_name);
uint32_t   max_time (ping_status_t pings_status[]);
uint32_t   min_time (ping_status_t pings_status[]);
uint32_t   average_time (ping_status_t pings_status[]);

#endif /* USR_APP_H_ */