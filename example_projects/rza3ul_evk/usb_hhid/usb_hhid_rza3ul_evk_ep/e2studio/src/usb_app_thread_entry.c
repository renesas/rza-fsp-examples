/***********************************************************************************************************************
* Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
*
* This software and documentation are supplied by Renesas Electronics Corporation and/or its affiliates and may only
* be used with products of Renesas Electronics Corp. and its affiliates ("Renesas").  No other uses are authorized.
* Renesas products are sold pursuant to Renesas terms and conditions of sale.  Purchasers are solely responsible for
* the selection and use of Renesas products and Renesas assumes no liability.  No license, express or implied, to any
* intellectual property right is granted by Renesas.  This software is protected under all applicable laws, including
* copyright laws. Renesas reserves the right to change or discontinue this software and/or this documentation.
* THE SOFTWARE AND DOCUMENTATION IS DELIVERED TO YOU "AS IS," AND RENESAS MAKES NO REPRESENTATIONS OR WARRANTIES, AND
* TO THE FULLEST EXTENT PERMISSIBLE UNDER APPLICABLE LAW, DISCLAIMS ALL WARRANTIES, WHETHER EXPLICITLY OR IMPLICITLY,
* INCLUDING WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT, WITH RESPECT TO THE
* SOFTWARE OR DOCUMENTATION.  RENESAS SHALL HAVE NO LIABILITY ARISING OUT OF ANY SECURITY VULNERABILITY OR BREACH.
* TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT WILL RENESAS BE LIABLE TO YOU IN CONNECTION WITH THE SOFTWARE OR
* DOCUMENTATION (OR ANY PERSON OR ENTITY CLAIMING RIGHTS DERIVED FROM YOU) FOR ANY LOSS, DAMAGES, OR CLAIMS WHATSOEVER,
* INCLUDING, WITHOUT LIMITATION, ANY DIRECT, CONSEQUENTIAL, SPECIAL, INDIRECT, PUNITIVE, OR INCIDENTAL DAMAGES; ANY
* LOST PROFITS, OTHER ECONOMIC DAMAGE, PROPERTY DAMAGE, OR PERSONAL INJURY; AND EVEN IF RENESAS HAS BEEN ADVISED OF THE
* POSSIBILITY OF SUCH LOSS, DAMAGES, CLAIMS OR COSTS.
**********************************************************************************************************************/
/******************************************************************************
 * Includes   <System Includes> , "Project Includes"
 ******************************************************************************/

#include <usb_app_thread.h>
#include "usb_hhid_appl.h"
#include "common_utils.h"

/******************************************************************************
 * Macro definitions
******************************************************************************/

/******************************************************************************
 * Private global variables and functions
 ******************************************************************************/
static  uint8_t     g_buf[BUFSIZE] USB_BUFFER_PLACE_IN_SECTION; /* USB Receive data */
static  uint32_t    g_setup_data;
uint16_t            g_mxps;
static  usb_event_info_t    g_event_info;
static fsp_err_t  set_protocol (usb_instance_ctrl_t *p_ctrl, uint8_t protocol, uint8_t device_address);
extern void R_USB_CstdScheduler(void);


/* New Thread entry function */
/* pvParameters contains TaskHandle_t */
void usb_app_thread_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);
    BaseType_t         err_queue     = pdFALSE;
    fsp_err_t err                    = FSP_SUCCESS;
    fsp_pack_version_t version       = {RESET_VALUE};

    /* version get API for FLEX pack information */
    R_FSP_VersionGet(&version);

    /* Example Project information printed on the Console */
    APP_PRINT(BANNER_INFO, EP_VERSION, version.version_id_b.major, version.version_id_b.minor, version.version_id_b.patch);
    APP_PRINT(EP_INFO);

    /* open basic USB driver.*/
    err = R_USB_Open (&g_usb_basic_ctrl, &g_usb_basic_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_USB_Open API FAILED **\r\n");
        while(1);
    }

    while(true)
    {
        /* Scheduler */
        R_USB_CstdScheduler();

        /* Check application state */
        switch (g_event_info.event)
        {
            case USB_STATUS_CONFIGURED :
            {
                APP_PRINT("USB Configured Successfully\r\n");

                /* Get max packet size for the connected HID device. The max packet size is set to the area.
                 * Set the direction (USB_HID_IN/USB_HID_OUT).*/
                err = R_USB_HHID_MaxPacketSizeGet (&g_usb_basic_ctrl, &g_mxps, USB_HID_IN, g_event_info.device_address);
                /* Handle error */
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT ("** R_USB_HHID_MaxPacketSizeGet API FAILED **\r\n");
                    /* Close the opened USB driver and trap error.*/
                    deinit_usb();
                    while(1);
                }

                /* Send the HID request(SetProtocol) to HID device */
                err = set_protocol (&g_usb_basic_ctrl, BOOT_PROTOCOL, g_event_info.device_address);
                /* Handle error */
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT ("** Send the HID request(SetProtocol) to HID device FAILED **\r\n");
                    /* Close the opened USB driver and trap error.*/
                    deinit_usb();
                    while(1);
                }
                g_event_info.event = 1;

                break;
            }

            case USB_STATUS_READ_COMPLETE :
            {
                /* Send data received to queue */
                err_queue = xQueueSend(g_data_queue, &g_buf[RESET_VALUE], portMAX_DELAY);
                /* Handle error */
                if (pdTRUE != err_queue)
                {
                    APP_ERR_PRINT ("Error in sending usb data through queue\r\n\r\n");
                    /* Close the opened USB driver and trap error.*/
                    deinit_usb();
                    while(1);
                }
                /* Send data receive request to hhid device.*/
               err = R_USB_Read (&g_usb_basic_ctrl, g_buf, (uint32_t) g_mxps, g_event_info.device_address);
               /* Handle error */
               if (FSP_SUCCESS != err)
               {
                   APP_ERR_PRINT ("** R_USB_Read API FAILED **\r\n");
                   /* Close the opened USB driver and trap error.*/
                   deinit_usb();
                   while(1);
               }
               g_event_info.event = 1;
               break;
            }

            case USB_STATUS_REQUEST_COMPLETE :
            {
                APP_PRINT("USB Status Request Completed Successfully\r\n");
                if (USB_HID_SET_PROTOCOL == (g_event_info.setup.request_type & USB_BREQUEST))
                {
                    /* Send data receive request to hhid device.*/
                    err = R_USB_Read (&g_usb_basic_ctrl, g_buf, (uint32_t) g_mxps, g_event_info.device_address);
                    /* Handle error */
                    if (FSP_SUCCESS != err)
                    {
                        APP_ERR_PRINT ("** R_USB_Read API FAILED **\r\n");
                        /* Close the opened USB driver and trap error.*/
                        deinit_usb();
                        while(1);
                    }
                    g_event_info.event = 1;
                }
                APP_PRINT("Enter any key as specified from a to z, A to Z, 0 to 9 and any special character \r\non keyboard\r\n\r\n");
                break;
            }
            case USB_STATUS_DETACH:
            {
                 APP_PRINT("USB Removed Successfully\r\n");
                 break;
            }

            default :
            break;
        }
        vTaskDelay(10);
    }
}

/*******************************************************************************************************************//**
 * @brief       Sending SetProtocol request to HID device.
 * @param[IN] : usb_ctrl_t   *p_ctrl : Pointer to usb_instance_ctrl_t structure.
 *            : uint8_t      protocol: Protocol Type
 *            : uint8_t      device_address: Device address that sends this request
 * @retval      FSP_SUCCESS  Upon successful Sending SetProtocol request to HID device.
 * @retval      Any Other Error code apart from FSP_SUCCES on Unsuccessful Sending SetProtocol request to HID device.
 **********************************************************************************************************************/
static fsp_err_t set_protocol(usb_instance_ctrl_t *p_ctrl, uint8_t protocol, uint8_t device_address)
{
    usb_setup_t setup;
    fsp_err_t err = FSP_SUCCESS;

    setup.request_type   = SET_PROTOCOL;  /* bRequestCode:SET_PROTOCOL, bmRequestType */
    setup.request_value  = protocol;      /* wValue: Protocol Type */
    setup.request_index  = SET_ZERO;      /* wIndex:Interface */
    setup.request_length = SET_ZERO;      /* wLength:Zero */

    err = R_USB_HostControlTransfer (p_ctrl, &setup, (uint8_t *) &g_setup_data, device_address); /* Request Control transfer */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_USB_HostControlTransfer API FAILED **\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief     This function is callback for FreeRTOS+HHID.
 * @param[IN]   usb_event_info_t  *p_event_info
 * @param[IN]   usb_hdl_t         handler
 * @param[IN]   usb_onoff_t       on_off
 * @retval      None.
 ***********************************************************************************************************************/
void usb_hhid_callback(usb_event_info_t * p_event_info, usb_hdl_t handler, usb_onoff_t on_off)
{

    FSP_PARAMETER_NOT_USED (handler);
    FSP_PARAMETER_NOT_USED (on_off);

    g_event_info = *p_event_info;
}

/*******************************************************************************************************************//**
 * This function is called to do closing of usb module using its HAL level API.
 * @brief     Close the usb module. Handle the Error internally with Proper Message.
 *            Application handles the rest.
 * @param[IN] None
 * @retval    None
 **********************************************************************************************************************/
void deinit_usb(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* close opened USB module */
    err = R_USB_Close(&g_usb_basic_ctrl);
    /* Handle error */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_USB_Close API FAILED **\r\n");
    }
}
