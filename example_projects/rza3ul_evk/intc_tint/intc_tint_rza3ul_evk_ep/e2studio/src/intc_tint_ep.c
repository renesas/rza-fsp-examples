/***********************************************************************************************************************
 * File Name    : intc_tint_ep.c
 * Description  : Contains function definition.
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
#include "intc_tint_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup intc_tint_ep
 * @{
 **********************************************************************************************************************/

/* Boolean flag to determine switch is pressed or not.*/
volatile bool g_sw_press = false;

/*******************************************************************************************************************//**
 * @brief       This functions initializes TINT module.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful open of INTC TINT module
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t intc_tint_init(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open INTC TINT driver */
    err = R_INTC_TINT_ExternalIrqOpen(&g_external_tint_ctrl, &g_external_tint_cfg);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC TINT Open failure message */
        APP_ERR_PRINT ("**R_INTC_TINT_ExternalIrqOpen API FAILED**\r\n\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function enables external interrupt for specified channel.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful enable of INTC TINT driver
 * @retval      Any Other Error code apart from FSP_SUCCESS  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t intc_tint_enable(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Enable INTC TINT driver */
    err = R_INTC_TINT_ExternalIrqEnable(&g_external_tint_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC TINT Enable failure message */
        APP_ERR_PRINT ("**R_INTC_TINT_ExternalIrqEnable API FAILED**\r\n\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function closes opened TINT module before the project ends up in an Error Trap.
 * @param[IN]   None
 * @retval      None
 **********************************************************************************************************************/
void intc_tint_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close INTC TINT module */
    err = R_INTC_TINT_ExternalIrqClose(&g_external_tint_ctrl);
    /* Handle error */
    if (FSP_SUCCESS != err)
    {
        /* INTC TINT Close failure message */
        APP_ERR_PRINT("**R_INTC_TINT_ExternalIrqClose API FAILED**\r\n\r\n");
    }
}

/*******************************************************************************************************************//**
 * @brief      User defined external irq callback.
 * @param[IN]  p_args
 * @retval     None
 **********************************************************************************************************************/
void tint_ep_callback(external_irq_callback_args_t *p_args)
{
    /* Make sure it's the right interrupt*/
    if(USER_SW_TINT_NUMBER == p_args->channel)
    {
        g_sw_press = true;
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup intc_tint_ep)
 **********************************************************************************************************************/