/***********************************************************************************************************************
 * File Name    : usr_app.h
 * Description  : Contains macros, data structures and functions used  in the Application
 ***********************************************************************************************************************/

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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

#ifndef USR_APP_H_
#define USR_APP_H_

#if (ipconfigUSE_DHCP != 0)
 #include "FreeRTOS_DHCP.h"
#endif

#define USR_TEST_DOMAIN_NAME         "www.freertos.org"
#define USR_TEST_PING_IP             "172.217.160.174"
#define USR_PING_COUNT               (10)
#define BYTES_DATA_SEND              (8)

#define SUCCESS                      (0)
#define PRINT_UP_MSG_DISABLE         (0x01UL)
#define PRINT_DOWN_MSG_DISABLE       (0x02UL)
#define PRINT_NWK_USR_MSG_DISABLE    (0x04UL)

#define ETHERNET_LINK_DOWN           (0x01)
#define ETHERNET_LINK_UP             (0x00)
#define IP_LINK_DOWN                 (0x02)
#define IP_LINK_UP                   (0x00)

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
void updateDhcpResponseToUsr(void);

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
uint32_t   ulRand();
uint32_t   isNetworkUp(void);
BaseType_t vSendPing(const char * pcIPAddress);
void       print_ipconfig(void);
void       print_pingResult(void);
void       dnsQuerryFunc(char * domain_name);
uint32_t   max_time (ping_status_t pings_status[]);
uint32_t   min_time (ping_status_t pings_status[]);
uint32_t   average_time (ping_status_t pings_status[]);

#endif /* USR_APP_H_ */
