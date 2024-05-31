/***********************************************************************************************************************
 * File Name    : net_thread_entry.c
 * Description  : This file contains the User Application code for the Ethernet + TCP/IP
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
#include "net_thread.h"
#include "FreeRTOS_IP.h"
#include "FreeRTOS_IP_Private.h"
#include "FreeRTOS_Sockets.h"
#include "FreeRTOSConfig.h"
#include "common_utils.h"
#include "usr_app.h"
#include "r_gether.h"
#include "common_data.h"

/* Domain for the DNS Host lookup is used in this Example Project.
 * The project can be built with different *gp_domain_name to validate the DNS client
 */
static char * gp_domain_name = USR_TEST_DOMAIN_NAME;

/* IP address of the PC or any Device on the LAN/WAN where the Ping request is sent.
 * Note: Users needs to change this according to the LAN settings of your Test PC or device
 * when running this project.
 */

static char * gp_remote_ip_address = USR_TEST_PING_IP;

#if (ipconfigUSE_DHCP != 0)

/* DHCP populates these IP address, Sub net mask and Gateway Address. So start with this is zeroed out values
 * The MAC address is Test MAC address.
 */
static uint8_t ucMACAddress[6]       = {RESET_VALUE};
static uint8_t ucIPAddress[4]        = {RESET_VALUE};
static uint8_t ucNetMask[4]          = {RESET_VALUE};
static uint8_t ucGatewayAddress[4]   = {RESET_VALUE};
static uint8_t ucDNSServerAddress[4] = {RESET_VALUE};

#else

/* Static IP configuration, when DHCP mode is not used for the Example Project.
 * This needs to be populated by the user according to the Network Settings of your LAN.
 * This sample address taken from the LAN where it is tested. This is different for different LAN.
 * get the Address using the PC IPconfig details.
 */
static uint8_t ucMACAddress[6]       = {0x00, 0x11, 0x33, 0x55, 0x77, 0x99};
static uint8_t ucIPAddress[4]        = {192, 168, 9, 112};
static uint8_t ucNetMask[4]          = {255, 255, 255, 0};
static uint8_t ucGatewayAddress[4]   = {192, 168, 9, 1};
static uint8_t ucDNSServerAddress[4] = {8, 8, 8, 8};
#endif


#if( ipconfigUSE_DHCP != 0 )
    IPV4Parameters_t xNd = {RESET_VALUE, RESET_VALUE, RESET_VALUE, {RESET_VALUE, RESET_VALUE}, RESET_VALUE, RESET_VALUE};
#endif

static uint32_t usr_print_ability               = RESET_VALUE;
uint32_t        dhcp_in_use                     = RESET_VALUE;
uint32_t        usr_ping_count                  = RESET_VALUE;
ping_data_t     ping_data                       = {RESET_VALUE, RESET_VALUE, RESET_VALUE};
uint32_t        timer_counter                   = RESET_VALUE;
ping_status_t   ping_status[USR_PING_COUNT + 1] = {RESET_VALUE};

static char const * const link_status[] = {
 "10Mbps Half Duplex\r\n"
,"10Mbps Full Duplex\r\n"
,"100Mbps Half Duplex\r\n"
,"100Mbps Full Duplex\r\n"
,"1000Mbps Half Duplex\r\n"
,"1000Mbps Full Duplex\r\n"
,"Illegal Value\r\n"
,"Illegal Value\r\n"
};

/*******************************************************************************************************************//**
 * @brief      Generates 32 bit Random number
 * @param[in]  void
 * @retval     Random Number
 **********************************************************************************************************************/
uint32_t ulRand ()
{
    /* example of a 32-bit random number generator.
     * Here rand() returns a 15-bit number. so create 32 bit Random number using 15 bit rand()
     */
    uint32_t ulResult = (uint32_t)(
        ((((uint32_t) rand()) & 0x7fffuL)) |
        ((((uint32_t) rand()) & 0x7fffuL) << 15) |
        ((((uint32_t) rand()) & 0x0003uL) << 30));

    return ulResult;
}

/*******************************************************************************************************************//**
 * @brief      Generates 32 sequence number
 * @param[in]  Source IP, Source Port, Destination IP and Destination Port.
 * @retval     Sequence Number
 **********************************************************************************************************************/
uint32_t ulApplicationGetNextSequenceNumber (uint32_t ulSourceAddress,
                                             uint16_t usSourcePort,
                                             uint32_t ulDestinationAddress,
                                             uint16_t usDestinationPort)
{

    /* Here we need to get random number for the sequence number.
     * This is just for testing purpose, so software rand() is okay.
     * This can also be tied to the TRNG.
     */
    return (ulSourceAddress + ulDestinationAddress + usSourcePort + usDestinationPort) && ulRand();
}

/*******************************************************************************************************************//**
 * @brief      Send ICMP Ping request  based on the user input IP Address.
 * @param[in]  IP address to Ping
 * @retval     Sequence Number
 **********************************************************************************************************************/
BaseType_t vSendPing (const char * pcIPAddress)
{
    uint32_t ulIPAddress = RESET_VALUE;

    /*
     * The pcIPAddress parameter holds the destination IP address as a string in
     * decimal dot notation (for example, â€œ192.168.0.200â€�). Convert the string into
     * the required 32-bit format.
     */
    ulIPAddress = FreeRTOS_inet_addr(pcIPAddress);

    /*
     * Send a ping request containing 8 data bytes. Wait (in the Blocked state) a
     * maximum of 100ms for a network buffer into which the generated ping request
     * can be written and sent.
     */
    return FreeRTOS_SendPingRequest(ulIPAddress, BYTES_DATA_SEND, 100 / portTICK_PERIOD_MS);
}

/*******************************************************************************************************************//**
 * @brief      User Hook for the Ping Reply. vApplicationPingReplyHook() is called by the TCP/IP
 *             stack when the stack receives a ping reply.
 * @param[in]  Ping reply status and Identifier
 * @retval     None
 **********************************************************************************************************************/
void vApplicationPingReplyHook (ePingReplyStatus_t eStatus, uint16_t usIdentifier)
{
    switch (eStatus)
    {
        /* A valid ping reply has been received */
        case eSuccess:
        {
            ping_status[usIdentifier].status = PING_SUCCESS;
            break;
        }

        /* A reply was received but it was not valid. */
        case eInvalidData:
        default:
        {
            ping_status[usIdentifier].status = INVALID_DATA;
            break;
        }
    }
    ping_status[usIdentifier].id   = usIdentifier;
    ping_status[usIdentifier].time = timer_counter;
}

/*******************************************************************************************************************//**
 * @brief      This is the User Thread for the EP.
 * @param[in]  Thread specific parameters
 * @retval     None
 **********************************************************************************************************************/
void net_thread_entry (void * pvParameters)
{
    BaseType_t         status  = pdFALSE;
    fsp_pack_version_t version = {RESET_VALUE};

    FSP_PARAMETER_NOT_USED(pvParameters);

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Open UART Driver */
    g_uart0.p_api->open(g_uart0.p_ctrl, g_uart0.p_cfg);

    /* Copy GUI settings to application */
    memcpy(ucMACAddress, gp_freertos_ether->p_cfg->p_mac_address, sizeof(ucMACAddress));

    /* Example Project information printed on the RTT */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);

    /* Prints the Ethernet Configuration prior to the IP Init*/
    APP_PRINT(ETH_PREINIT);
    print_ipconfig();

    /* FreeRTOS IP Initialization: This init initializes the IP stack  */
    status = FreeRTOS_IPInit(ucIPAddress, ucNetMask, ucGatewayAddress, ucDNSServerAddress, ucMACAddress);

    if (pdFALSE == status)
    {
        APP_ERR_PRINT("FreeRTOS_IPInit Failed");
        APP_ERR_TRAP(status);
    }

    APP_PRINT(ETH_POSTINIT);

    while (true)
    {
        /* Check if Both the Ethernet Link and IP link are UP */
        if (SUCCESS == isNetworkUp())
        {
            /* usr_print_ability is added to avoid multiple UP messages or Down Messages repeating*/
            if (!(PRINT_UP_MSG_DISABLE & usr_print_ability))
            {
                uint32_t connection_status;
                APP_PRINT("\r\nNetwork is Up");
                usr_print_ability |= PRINT_UP_MSG_DISABLE;
                usr_print_ability &= (uint32_t)~PRINT_DOWN_MSG_DISABLE;
                if(g_gether_phy1_cfg.channel==0)
                {
                    connection_status = (R_EMAC0->CXR32 >> 1) & 0x7;
                }
                else
                {
                    connection_status = (R_EMAC1->CXR32 >> 1) & 0x7;
                }
                APP_PRINT("\r\nConnecton: %s\r\n",link_status[connection_status]);
            }

            if (!(PRINT_NWK_USR_MSG_DISABLE & usr_print_ability))
            {
#if (ipconfigUSE_DHCP != 0)

                /* Display the New IP credentials obtained from the DHCP server */
                updateDhcpResponseToUsr();
#endif

                /* Updated IP credentials on to the console */
                print_ipconfig();

                /*DNS lookup for the Domain name requested. This is Synchronous Activity */
                dnsQuerryFunc(gp_domain_name);
            }

            if (!(PRINT_NWK_USR_MSG_DISABLE & usr_print_ability))
            {
                APP_PRINT(ETH_CHECK_CONNECT);
                APP_PRINT("\r\nPinging %s with %d bytes of data:", (char *) gp_remote_ip_address, BYTES_DATA_SEND);
            }

            while (usr_ping_count < USR_PING_COUNT)
            {
                /* Send a ICMP Ping request to the requested IP address
                 * USR_PING_COUNT is used in this Example Project
                 * For Continuous testing the count can be increased to bigger number
                 */
                timer_counter = 0;
                uint32_t request_num;
                request_num = (uint32_t) vSendPing((char *) gp_remote_ip_address);

                if( request_num == pdFAIL )
                {
                    /* The ping could not be sent because a network buffer could not be
                    obtained within 100ms of FreeRTOS_SendPingRequest() being called. */
                    ping_data.lost++;
                }
                else
                {
                    /* The ping was sent. */
                    ping_data.sent++;

                    /* Wait 500ms for a reply. */
                    while ((timer_counter < 500) && (ping_status[request_num].status == NO_PING))
                    {
                        vTaskDelay(1);
                        timer_counter++;
                    }

                    /* If a ping reply was received?*/
                    if (ping_status[request_num].status == NO_PING)
                    {
                        /* No Ping reply or too long. */
                        if (timer_counter >= 500)
                        {
                            ping_data.lost++;
                            APP_PRINT("\r\nRequest timed out!");
                        }
                    }
                    else
                    {
                        /* Was it a reply to the ping just sent? */
                        if (request_num == ping_status[request_num].id)
                        {
                            /* This was a reply to the request just sent. */
                            ping_data.received++;
                            switch (ping_status[request_num].status)
                            {
                                case PING_SUCCESS:
                                {
                                    APP_PRINT("\r\nReply from %s: bytes=%d time=%dms",
                                            (char *) gp_remote_ip_address,
                                            BYTES_DATA_SEND,
                                            ping_status[request_num].time);
                                    break;
                                }
                                case INVALID_DATA:
                                {
                                    APP_PRINT("\r\nReply from %s: Invalid Data, time=%dms",
                                            (char *) gp_remote_ip_address,
                                            ping_status[request_num].time);
                                    break;
                                }
                                default:
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
                usr_ping_count++;
            }

            vTaskDelay(500);
            if (!(PRINT_NWK_USR_MSG_DISABLE & usr_print_ability))
            {
                print_pingResult();
                usr_print_ability |= PRINT_NWK_USR_MSG_DISABLE;
            }
        }
        else
        {
            if (!(PRINT_DOWN_MSG_DISABLE & usr_print_ability))
            {
                APP_PRINT("\r\nNetwork is Down");
                usr_print_ability |= PRINT_DOWN_MSG_DISABLE;
                usr_print_ability &= (uint32_t)~PRINT_UP_MSG_DISABLE;
                usr_print_ability &= (uint32_t)~PRINT_NWK_USR_MSG_DISABLE;
                usr_ping_count       = RESET_VALUE;
                ping_data.sent     = RESET_VALUE;
                ping_data.received = RESET_VALUE;
                ping_data.lost     = RESET_VALUE;
#if (0)
                IPStackEvent_t              xNetworkDownEvent;
                xNetworkDownEvent.eEventType = eNetworkDownEvent;
                xSendEventStructToIPTask(&xNetworkDownEvent, 0);
#endif
            }
            else
            {
                APP_PRINT(".");
                fflush( stdout );
            }
        }

        vTaskDelay(100);
    }
}

/*******************************************************************************************************************//**
 * @brief      This is the User Hook for the DHCP Response. xApplicationDHCPHook() is called by DHCP Client Code when DHCP
 *             handshake messages are exchanged from the Server.
 * @param[in]  Different Phases of DHCP Phases and the Offered IP Address
 * @retval     Returns DHCP Answers.
 **********************************************************************************************************************/
#if (ipconfigUSE_DHCP != 0)
eDHCPCallbackAnswer_t xApplicationDHCPHook (eDHCPCallbackPhase_t eDHCPPhase, uint32_t ulIPAddress)
{
    eDHCPCallbackAnswer_t eReturn = eDHCPContinue;

    /*
     * This hook is called in a couple of places during the DHCP process, as identified by the eDHCPPhase parameter.
     */
    switch (eDHCPPhase)
    {
        case eDHCPPhasePreDiscover:
        {
            /*
             *  A DHCP discovery is about to be sent out.  eDHCPContinue is returned to allow the discovery to go out.
             *  If eDHCPUseDefaults had been returned instead then the DHCP process would be stopped and the statically
             *  configured IP address would be used.
             *  If eDHCPStopNoChanges had been returned instead then the DHCP process would be stopped and whatever the
             *  current network configuration was would continue to be used.
             */
            break;
        }

        case eDHCPPhasePreRequest:
        {
            /* An offer has been received from the DHCP server, and the offered IP address is passed in the ulIPAddress
             * parameter.
             */

            /*
             * The sub-domains donâ€™t match, so continue with the DHCP process so the offered IP address is used.
             */

            /* Update the Structure, the DHCP state Machine is not updating this */
            xNd.ulIPAddress = ulIPAddress;
            dhcp_in_use = 1;
            break;
        }

        default:
        {
            /*
             * Cannot be reached, but set eReturn to prevent compiler warnings where compilers are disposed to generating one.
             */
            break;
        }
    }

    return eReturn;
}

#endif

/*******************************************************************************************************************//**
 * @brief      Find a maximum time from ping data.
 * @param[in]  Ping data structure.
 * @retval     Returns a maximum ping time.
 **********************************************************************************************************************/
uint32_t max_time (ping_status_t pings_status[])
{
    uint32_t max = RESET_VALUE;
    for (uint8_t i = 0; i <= USR_PING_COUNT; i++)
    {
        if ((pings_status[i].status != NO_PING) && (max < pings_status[i].time))
        {
            max = pings_status[i].time;
        }
    }
    return max;
}
/*******************************************************************************************************************//**
 * @brief      Find a minimum time from ping data.
 * @param[in]  Ping data structure.
 * @retval     Returns a minimum ping time.
 **********************************************************************************************************************/
uint32_t min_time (ping_status_t pings_status[])
{
    uint32_t min = 0xffffffff;
    for (uint8_t i = 0; i <= USR_PING_COUNT; i++)
    {
        if ((pings_status[i].status != NO_PING) && (min > pings_status[i].time))
        {
            min = pings_status[i].time;
        }
    }
    return min;
}
/*******************************************************************************************************************//**
 * @brief      Calculate average time from ping data.
 * @param[in]  Ping data structure.
 * @retval     Returns average ping time.
 **********************************************************************************************************************/
uint32_t average_time (ping_status_t pings_status[])
{
    uint32_t average = 0;
    for ( uint8_t i = 0; i <= USR_PING_COUNT; i++)
    {
        if (pings_status[i].status != NO_PING)
        {
            average += pings_status[i].time;
        }
    }
    average = average/USR_PING_COUNT;
    return average;
}

/*******************************************************************************************************************//**
 * @brief      Prints the Ping response on to the RTT console
 * @param[in]  void
 * @retval     None
 **********************************************************************************************************************/
void print_pingResult (void)
{
    APP_PRINT("\r\n\r\nPing Statistics for %s:", (char *) gp_remote_ip_address);
    APP_PRINT("\r\n  Packets: Sent = %02d, Received = %02d, Lost = %d (%d%% loss)\r\n",
              ping_data.sent,
              ping_data.received,
              ping_data.lost,
              ping_data.lost*100/ping_data.sent);
    APP_PRINT("\r\nApproximate round trip times in milli-seconds:");
    APP_PRINT("\r\n  Maximum = %dms, Minimum = %dms, Average = %dms\r\n",
              max_time(ping_status),
              min_time(ping_status),
              average_time(ping_status));
}

/*******************************************************************************************************************//**
 * @brief      Creates and prints the the IP configuration to display on the RTT console
 * @param[in]  void
 * @retval     None
 **********************************************************************************************************************/
void print_ipconfig (void)
{
#if (ipconfigUSE_DHCP != 0)
    if (dhcp_in_use)
    {
        ucNetMask[3] = (uint8_t) ((xNd.ulNetMask & 0xFF000000) >> 24);
        ucNetMask[2] = (uint8_t) ((xNd.ulNetMask & 0x00FF0000) >> 16);
        ucNetMask[1] = (uint8_t) ((xNd.ulNetMask & 0x0000FF00) >> 8);
        ucNetMask[0] = (uint8_t) (xNd.ulNetMask & 0x000000FF);

        ucGatewayAddress[3] = (uint8_t) ((xNd.ulGatewayAddress & 0xFF000000) >> 24);;
        ucGatewayAddress[2] = (uint8_t) ((xNd.ulGatewayAddress & 0x00FF0000) >> 16);
        ucGatewayAddress[1] = (uint8_t) ((xNd.ulGatewayAddress & 0x0000FF00) >> 8);
        ucGatewayAddress[0] = (uint8_t) (xNd.ulGatewayAddress & 0x000000FF);

        ucDNSServerAddress[3] = (uint8_t)((xNd.ulDNSServerAddresses[0] & 0xFF000000)>> 24);
        ucDNSServerAddress[2] = (uint8_t)((xNd.ulDNSServerAddresses[0] & 0x00FF0000)>> 16);
        ucDNSServerAddress[1] = (uint8_t)((xNd.ulDNSServerAddresses[0] & 0x0000FF00)>> 8);
        ucDNSServerAddress[0] = (uint8_t)(xNd.ulDNSServerAddresses[0] & 0x000000FF);

        ucIPAddress[3] = (uint8_t)((xNd.ulIPAddress & 0xFF000000) >> 24);
        ucIPAddress[2] = (uint8_t)((xNd.ulIPAddress & 0x00FF0000) >> 16);
        ucIPAddress[1] = (uint8_t)((xNd.ulIPAddress & 0x0000FF00) >> 8);
        ucIPAddress[0] = (uint8_t)(xNd.ulIPAddress & 0x000000FF);
    }
#endif
    APP_PRINT("\r\nEthernet adapter for Renesas "KIT_NAME ":\r\n");

    APP_PRINT("\tDescription . . . . . . . . . . . : Renesas "KIT_NAME " Ethernet\r\n");
    APP_PRINT("\tPhysical Address. . . . . . . . . : %02x-%02x-%02x-%02x-%02x-%02x\r\n",
              ucMACAddress[0],
              ucMACAddress[1],
              ucMACAddress[2],
              ucMACAddress[3],
              ucMACAddress[4],
              ucMACAddress[5]);
    APP_PRINT("\tDHCP Enabled. . . . . . . . . . . : %s\r\n", dhcp_in_use ? "Yes" : "No");
    APP_PRINT("\tIPv4 Address. . . . . . . . . . . : %d.%d.%d.%d\r\n",
              ucIPAddress[0],
              ucIPAddress[1],
              ucIPAddress[2],
              ucIPAddress[3]);
    APP_PRINT("\tSubnet Mask . . . . . . . . . . . : %d.%d.%d.%d\r\n",
              ucNetMask[0],
              ucNetMask[1],
              ucNetMask[2],
              ucNetMask[3]);
    APP_PRINT("\tDefault Gateway . . . . . . . . . : %d.%d.%d.%d\r\n",
              ucGatewayAddress[0],
              ucGatewayAddress[1],
              ucGatewayAddress[2],
              ucGatewayAddress[3]);
    APP_PRINT("\tDNS Servers . . . . . . . . . . . : %d.%d.%d.%d\r\n",
              ucDNSServerAddress[0],
              ucDNSServerAddress[1],
              ucDNSServerAddress[2],
              ucDNSServerAddress[3]);
}

/*******************************************************************************************************************//**
 * @brief      DNS Query for the requested Domain name.  Uses the FreeRTOS Client API  FreeRTOS_gethostbyname
 *             to get the IP address for the domain name
 * @param[in]  Domain name
 * @retval     None
 **********************************************************************************************************************/
void dnsQuerryFunc (char * domain)
{
    uint32_t ulIPAddress = RESET_VALUE;
    int8_t   cBuffer[16] = {RESET_VALUE};

    /* Lookup the IP address of the FreeRTOS.org website. */
    ulIPAddress = FreeRTOS_gethostbyname((char *) domain);

    if (ulIPAddress != 0)
    {
        /* Convert the IP address to a string. */
        FreeRTOS_inet_ntoa(ulIPAddress, (char *) cBuffer);

        /* Print out the IP address obtained from the DNS lookup. */
        APP_PRINT("\r\nDNS Lookup for \"%s\" is      : %s  \r\n", domain, cBuffer);
    }
    else
    {
        APP_PRINT("\r\nDNS Lookup failed for \"%s\" \r\n", domain);
    }
}

/*******************************************************************************************************************//**
 * @brief      This Function checks the Network status (Both Ethernet and IP Layer). If the Network is down
 *             the Application will not send any data on the network.
 * @param[in]  None
 * @retval     Network Status
 **********************************************************************************************************************/
uint32_t isNetworkUp (void)
{
    fsp_err_t  eth_link_status = FSP_ERR_NOT_OPEN;
    BaseType_t networkUp       = pdFALSE;
    uint32_t   network_status  = (IP_LINK_UP | ETHERNET_LINK_UP);

#if (ipconfigUSE_DHCP != 0)
    if(!dhcp_in_use)
    {
        return IP_LINK_DOWN;
    }
#endif

    networkUp       = FreeRTOS_IsNetworkUp();
    eth_link_status = R_GETHER_LinkProcess(gp_freertos_ether->p_ctrl);

    if ((FSP_SUCCESS == eth_link_status) && (pdTRUE == networkUp))
    {
        return network_status;
    }
    else
    {
        if (FSP_SUCCESS != eth_link_status)
        {
            network_status |= ETHERNET_LINK_DOWN;
        }
        else if (FSP_SUCCESS == eth_link_status)
        {
            network_status |= ETHERNET_LINK_UP;
        }

        if (pdTRUE != networkUp)
        {
            network_status |= IP_LINK_DOWN;
        }
        else if (pdTRUE == networkUp)
        {
            network_status |= IP_LINK_UP;
        }

        return network_status;
    }
}

/*******************************************************************************************************************//**
 * @brief      Update the DHCP info to the User data structure.
 * @param[in]  None
 * @retval     None
 **********************************************************************************************************************/
#if (ipconfigUSE_DHCP != 0)
void updateDhcpResponseToUsr (void)
{
    if (dhcp_in_use)
    {
        xNd.ulNetMask = FreeRTOS_GetNetmask();
        xNd.ulGatewayAddress = FreeRTOS_GetGatewayAddress();
        xNd.ulDNSServerAddresses[0] = FreeRTOS_GetDNSServerAddress();
    }
}

#endif

/*******************************************************************************************************************//**
 * @brief      DHCP Hook function to populate the user defined Host name for the Kit.
 * @param[in]  None
 * @retval     Hostname
 **********************************************************************************************************************/
#if (ipconfigDHCP_REGISTER_HOSTNAME == 1)
const char * pcApplicationHostnameHook (void)
{
    return KIT_NAME;
}

#endif
void vApplicationIPNetworkEventHook( eIPCallbackEvent_t eNetworkEvent )
{
static BaseType_t xTasksAlreadyCreated = pdFALSE;

    /* Both eNetworkUp and eNetworkDown events can be processed here. */
    if( eNetworkEvent == eNetworkUp )
    {
        /* Create the tasks that use the TCP/IP stack if they have not already
        been created. */
        if( xTasksAlreadyCreated == pdFALSE )
        {
            /*
             * For convenience, tasks that use FreeRTOS-Plus-TCP can be created here
             * to ensure they are not created before the network is usable.
             */

            xTasksAlreadyCreated = pdTRUE;
        }
    }
}
