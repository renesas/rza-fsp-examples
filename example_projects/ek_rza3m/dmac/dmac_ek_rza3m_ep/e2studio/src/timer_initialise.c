/***********************************************************************************************************************
 * File Name    : timer_initialise.c
 * Description  : Contains data structures and functions used in timer_initialise.c
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "timer_initialise.h"

/*******************************************************************************************************************//**
 * @addtogroup timer_initialise
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *  @brief       MTU3 timer initialisation function
 *  @param[IN]   None
 *  @retval      FSP_SUCCESS                  Upon successful open and start of timer
 *  @retval      Any Other Error code apart from FSP_SUCCESS is  Unsuccessful open or start
 **********************************************************************************************************************/
fsp_err_t mtu3_timer_init(void)
{
    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Open the gpt timer */
    fsp_err = R_MTU3_Open(&g_mtu3_ctrl, &g_mtu3_cfg);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("\r\nMTU3 timer open failed. Necessary cleanup is done. \n");
        return fsp_err;
    }

    /* Start MTU3 timer */
    fsp_err = R_MTU3_Start(&g_mtu3_ctrl);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        fsp_err_t err = FSP_SUCCESS;
        err = R_MTU3_Close(&g_mtu3_ctrl);
        /* Handle error in-case of failure */
        if (FSP_SUCCESS != err)
        {
            /* Tera Term failure message */
            APP_ERR_PRINT("MTU3 timer close failed.\n\n");
        }
        /* Tera Term failure message */
        APP_ERR_PRINT("\r\nMTU3 timer start failed. Necessary cleanup is done. \n");
    }
    return fsp_err;
}

/*******************************************************************************************************************//**
 *  @brief      GTM timer initialization function
 *  @param[IN]   None
 *  @retval      FSP_SUCCESS                  Upon successful open and start of timer
 *  @retval      Any Other Error code apart from FSP_SUCCESS is  Unsuccessful open or start
 **********************************************************************************************************************/
fsp_err_t gtm_timer_init(void)
{
    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Open and Configure the GTM timer  */
    fsp_err = R_GTM_Open(&g_timer_ctrl, &g_timer_cfg);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        /* Tera Term failure message */
        APP_ERR_PRINT("GTM timer open failed. Necessary cleanup is done. \n\n");
        return fsp_err;
    }

    /* Start the GTM timer. */
    fsp_err = R_GTM_Start(&g_timer_ctrl);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        fsp_err_t err = FSP_SUCCESS;
        err = R_GTM_Close(&g_timer_ctrl);
        /* Handle error in-case of failure */
        if (FSP_SUCCESS != err)
        {
            /* Tera Term failure message */
            APP_ERR_PRINT("GTM timer close failed.\n");
        }

        /* Tera Term failure message */
        APP_ERR_PRINT("\r\nGTM timer start failed. Necessary cleanup is done. \n");
    }
    return fsp_err;
}

/*******************************************************************************************************************//**
 *  @brief       MTU3 timer deinitialisation function
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
void mtu3_timer_deinit(void)
{
    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Open and Configure the MTU3 timer  */
    fsp_err = R_MTU3_Close(&g_mtu3_ctrl);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        /* Tera Term failure message */
        APP_ERR_PRINT("MTU3 timer close failed.\n\n");
    }
}

/*******************************************************************************************************************//**
 *  @brief       GTM timer deinitialisation function
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
void gtm_timer_deinit(void)
{
    /* Variable to help handle error codes from functions */
    fsp_err_t fsp_err = FSP_SUCCESS;

    /* Open and Configure the GTM timer  */
    fsp_err = R_GTM_Close(&g_timer_ctrl);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        /* Tera Term failure message */
        APP_ERR_PRINT("GTM timer close failed.\n\n");
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup timer_initialise)
 **********************************************************************************************************************/