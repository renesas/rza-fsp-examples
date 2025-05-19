/***********************************************************************************************************************
 * File Name    : transfer_initialise.c
 * Description  : Contains data structures and functions used in transfer_initialise.c
 **********************************************************************************************************************/
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

#include "common_utils.h"
#include "transfer_initialise.h"
#include "stdbool.h"

/*******************************************************************************************************************//**
 * @addtogroup transfer_initialise

 * @{
 **********************************************************************************************************************/

/* Destination array to which the DMAC writes MTU3 timer values */
uint32_t g_dest_data[DATA_SIZE];

/* Variable to flag for printing data on Tera Term */
volatile bool send_data_to_console_flag = false;

/* Source data that will be transferred by the DMAC g_transfer_led_blink     .
 * This data will be tran to IOPORT P11 register,
 * which specifies the input/output statesferred of a pin.
 * The register is a 8-bit register - bits[8:0] = output level (high/low)
 * The User LEDs on board are connected to I/O pins
 * Direction output is configured in "Pins configuration",
 * pin [1] high, pin [0] low state
 */
uint8_t  g_source_data[SOURCE_DATA_SIZE]=
{
 0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,
 0x00,0x10,0x00,0x10
};

/*******************************************************************************************************************//**
 *  @brief      Initializing dmac transfer instance based on transfer unit and enable for transfer
 *  @param[in]  p_transfer_ctl       Transfer instance control structure
 *  @param[in]  p_transfer_cfg       Transfer instance configuration structure
 *  @retval     FSP_SUCCESS          On successful initialization of dmac_tranfer
 *  @retval     Any Other Error code apart from FSP_SUCCESS if Unsuccessful open or enable
 **********************************************************************************************************************/
fsp_err_t dmac_transfer_init(dmac_instance_ctrl_t *const p_transfer_ctl,
        transfer_cfg_t const *const p_transfer_cfg)
{
    /* Variable to help handle error codes */
    fsp_err_t fsp_err = FSP_SUCCESS;
    /* Open the transfer instance */
    fsp_err = R_DMAC_Open(p_transfer_ctl, p_transfer_cfg);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("**R_DMAC_Open API for transfer failed ** \r\n");
        return fsp_err;
    }
    /* Enable transfer for the configured activation source*/
    fsp_err = R_DMAC_Enable(p_transfer_ctl);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        fsp_err_t err = FSP_SUCCESS;
        /* In case of DMAC_open is successful and enabling fails, requires a immediate cleanup.
         * Since, cleanup for dmac open is done here, cleanup in dmac_transfer_deinit for open is not required */
        err = R_DMAC_Close(p_transfer_ctl);
        /* handle error */
        if (FSP_SUCCESS != err)
        {
            /* DMAC Close failure message */
            APP_ERR_PRINT("** R_DMAC_Close for transfer API failed **  \r\n");
        }
    }
    return fsp_err;
}

/*******************************************************************************************************************//**
 *  @brief     Deinitializing dmac transfer instance based on transfer unit and enable for transfer
 *  @param[in] p_transfer_ctl       Transfer instance control structure
 *  @retval    None
 **********************************************************************************************************************/
void dmac_transfer_deinit(dmac_instance_ctrl_t *const p_transfer_ctl)
{
    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = R_DMAC_Close(p_transfer_ctl);
    /* handle error */
    if (FSP_SUCCESS != fsp_err)
    {
        /* DMAC Close failure message */
        APP_ERR_PRINT("** R_DMAC_Close for transfer API failed **  \r\n");
    }
}

/*******************************************************************************************************************//**
 *  @brief          start dmac transfer
 *  @param[in]      transfer_ctrl_t
 *  @retval         FSP_SUCCESS      Upon successful start of dmac
 *  @retval         Any Other Error code apart from FSP_SUCCESS is  Unsuccessful  start
 **********************************************************************************************************************/
fsp_err_t dmac_transfer_software_start(transfer_ctrl_t * const p_transfer_ctrl)
{

    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Start DMAC transfer by software */
    fsp_err = R_DMAC_SoftwareStart(p_transfer_ctrl, TRANSFER_START_MODE_SINGLE);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("\r\nDMAC dmac transfer software start failed.\n");
    }
    return fsp_err;
}

/*******************************************************************************************************************//**
 *  @brief       Print dmac data transfered by g_transfer_mtu_value on User Tera Term input
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
void dmac_transfer_print_data(void)
{

    APP_PRINT("\r\n*** Data transfered through g_transfer_mtu_value *** \r\n");
    APP_PRINT("Data[0]=%05d\r\n", (int)g_dest_data[0]);
    APP_PRINT("Data[1]=%05d\r\n", (int)g_dest_data[1]);
    APP_PRINT("Data[2]=%05d\r\n", (int)g_dest_data[2]);
    APP_PRINT("Data[3]=%05d\r\n", (int)g_dest_data[3]);
    APP_PRINT("Data[4]=%05d\r\n", (int)g_dest_data[4]);
    APP_PRINT("Data[5]=%05d\r\n", (int)g_dest_data[5]);
    APP_PRINT("Data[6]=%05d\r\n", (int)g_dest_data[6]);
    APP_PRINT("Data[7]=%05d\r\n", (int)g_dest_data[7]);
    APP_PRINT("-------------\n");
}

/*******************************************************************************************************************//**
 *  @brief       Set the source and destination address for the DMAC transfer instance
 *  @param[IN]   p_config       Transfer instance configuration structure
 *  @param[IN]   p_src          Source address
 *  @param[IN]   p_dest         Destination address
 *  @retval      None
 **********************************************************************************************************************/
void set_transfer_dst_src_address(transfer_cfg_t const * const p_config,
        void const * volatile p_src, void const * volatile p_dest )
{
    p_config->p_info->p_src = (void *) p_src;
    p_config->p_info->p_dest = (void *) p_dest;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup transfer_initialise)
 **********************************************************************************************************************/