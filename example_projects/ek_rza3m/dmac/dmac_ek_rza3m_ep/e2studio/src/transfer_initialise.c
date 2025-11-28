/***********************************************************************************************************************
 * File Name    : transfer_initialise.c
 * Description  : Contains data structures and functions used in transfer_initialise.c
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "transfer_initialise.h"
#include "stdbool.h"

/*******************************************************************************************************************//**
 * @addtogroup transfer_initialise

 * @{
 **********************************************************************************************************************/

/* Destination array to which the DMAC writes MTU3 timer values */
uint32_t g_dest_data[DATA_SIZE] __attribute__((section("UNCACHED_BSS"), aligned(64)));

/* Source data array located in uncached memory region for DMAC access */
uint8_t g_source_data[SOURCE_DATA_SIZE] __attribute__((section("UNCACHED_BSS"), aligned(64)));

/* Variable to flag for printing data on Tera Term */
volatile bool g_send_data_to_console_flag = false;

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
 *  @param[IN]   p_mmu_ctrl     Pointer to MMU control structure
 *  @retval      FSP_SUCCESS    Address conversion and assignment successful
 **********************************************************************************************************************/
fsp_err_t set_transfer_dst_src_address(transfer_cfg_t const * const p_config,
        void const * volatile p_src, void const * volatile p_dest,
        mmu_ctrl_t * const p_mmu_ctrl)
{
    fsp_err_t err = FSP_SUCCESS;
    uint64_t physical_src = 0;
    uint64_t physical_dest = 0;

    /* Convert virtual source address to physical address */
    err = R_MMU_VAtoPA(p_mmu_ctrl, (uint64_t)p_src, &physical_src);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Convert virtual destination address to physical address */
    err = R_MMU_VAtoPA(p_mmu_ctrl, (uint64_t)p_dest, &physical_dest);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Set the physical addresses for DMAC */
    p_config->p_info->p_src = (void *)physical_src;
    p_config->p_info->p_dest = (void *)physical_dest;

    return err;
}
/*******************************************************************************************************************//**
 * @} (end addtogroup transfer_initialise)
 **********************************************************************************************************************/