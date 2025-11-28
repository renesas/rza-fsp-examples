/***********************************************************************************************************************
 * File Name    : dmac_transfers.c
 * Description  : Contains data structures and functions used in dmac_transfers.c
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "common_utils.h"
#include "dmac_transfers.h"
#include "transfer_initialise.h"
#include "timer_initialise.h"
#include "stdbool.h"

/*******************************************************************************************************************//**
 * @addtogroup dmac_transfers
 * @{
 **********************************************************************************************************************/
/* Source and destination array for DMAC transfer */
extern uint8_t  g_source_data[SOURCE_DATA_SIZE];
extern uint32_t g_dest_data[DATA_SIZE];
volatile uint32_t i = 0 ;
volatile uint8_t c = '.';

/* LED port pin control register for port*/
static volatile uint8_t *p_ioport_pnctrl_register = &R_GPIO->P01;

/* MTU3 counter register */
static volatile uint32_t *p_mtu3_counter_register = &R_MTU8->TCNT;

/* Boolean flag to determine if transfer is complete */
volatile bool b_is_transfer_complete  = false;

/* Source data that will be transferred by the DMAC g_transfer_led_blink     .
 * This data will be tran to IOPORT P11 register,
 * which specifies the input/output statesferred of a pin.
 * The register is a 8-bit register - bits[8:0] = output level (high/low)
 * The User LEDs on board are connected to I/O pins
 * Direction output is configured in "Pins configuration",
 * pin [1] high, pin [0] low state
 */
uint8_t  g_data_buffer[SOURCE_DATA_SIZE]=
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
 *  @brief       Perform transfer led blink operation
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
void transfer_led_blink_operation(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;    // Variable to help handle error codes from functions
    memcpy(&g_source_data, &g_data_buffer, sizeof(g_source_data)); // Copy data from g_data_buffer to g_source_data
    /* Set the Source and Destination Addresses for DMAC g_transfer_led_blink .
     * NOTE: If the source and destination addresses are not set prior to
     * opening the transfer interface, then the open will fail.
     */
    fsp_err = set_transfer_dst_src_address(&g_transfer_led_blink_cfg, (void *)g_source_data, (void *)p_ioport_pnctrl_register, &g_mmu_ctrl);
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("\r\n** set_transfer_dst_src_address failed ** \r\n");
        APP_ERR_TRAP(fsp_err);
        return;
    }
    /* Open and enable dmac g_transfer_led_blink  */
    fsp_err = dmac_transfer_init( &g_transfer_led_blink_ctrl, &g_transfer_led_blink_cfg);
    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        /* Necessary cleanup is already taken care in init function hence no cleanup is required here*/
        APP_ERR_PRINT("** DMAC TRANSFER_LED_BLINK INIT failed ** \r\n");
        APP_ERR_TRAP(fsp_err);
    }

    /* Open and start GTM timer */
    fsp_err = gtm_timer_init();

    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("** GTM Timer INIT failed ** \r\n");
        dmac_transfer_deinit(&g_transfer_led_blink_ctrl);
        APP_ERR_TRAP(fsp_err);
    }

    /* Display information about g_transfer_led_blink transfer on Tera Term display and view on-board LED */
    APP_PRINT("\r\nDMAC g_transfer_led_blink transfer in progress. Wait for 6 second \n");

    /* Wait for g_transfer_led_blink to complete.
     * This boolean flag is set in transfer_gtm_timer_callback
     */
    while(false == b_is_transfer_complete)
    {
        /* wait */
    }

    /* Reset the flag */
    b_is_transfer_complete = false;
    i=0;
    APP_PRINT("\r\nDMAC g_transfer_led_blink transfer completed.\n");
}

/*******************************************************************************************************************//**
 *  @brief       Perform transfer transfer mtu value
 *  @param[IN]   None
 *  @retval      None
 **********************************************************************************************************************/
void transfer_mtu_value(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;    // Variable to help handle error codes from functions

    /* Set the Source and Destination Addresses for DMAC transfer_continuously_operation.
     * NOTE: If the source and destination addresses are not set prior to
     * opening the transfer interface, then the open will  mtu3_timer_init() fail.
     */
    fsp_err = set_transfer_dst_src_address(&g_transfer_mtu_value_cfg, (void *)p_mtu3_counter_register, (void *)g_dest_data, &g_mmu_ctrl);
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("\r\n** set_transfer_dst_src_address failed ** \r\n");
        APP_ERR_TRAP(fsp_err);
        return;
    }
    /* Open and enable dmac transfer_mtu_value */
    fsp_err = dmac_transfer_init(&g_transfer_mtu_value_ctrl, &g_transfer_mtu_value_cfg);
    if (FSP_SUCCESS != fsp_err)
        {
            APP_ERR_PRINT("** DMAC TRANSFER MTU Timer value failed ** \r\n");
            mtu3_timer_deinit();
            dmac_transfer_deinit(&g_transfer_led_blink_ctrl);
            APP_ERR_TRAP(fsp_err);
        }
    /* Open MTU timer and start */
    fsp_err = mtu3_timer_init();

    /* Handle error in-case of failure */
    if (FSP_SUCCESS != fsp_err)
    {
        APP_ERR_PRINT("**  MTU Timer INIT failed ** \r\n");
        dmac_transfer_deinit(&g_transfer_mtu_value_ctrl);
        mtu3_timer_deinit();
        dmac_transfer_deinit(&g_transfer_led_blink_ctrl);
        APP_ERR_TRAP(fsp_err);
    }
}

/*******************************************************************************************************************//**
 *  @brief      transfer_gtm_timer_callback function
 *  @param[in]  callback arguments
 **********************************************************************************************************************/
void transfer_gtm_timer_callback (dmac_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    /* Set boolean flag to print data */
    b_is_transfer_complete  = true;
}

/*******************************************************************************************************************//**
 * @} (end addtogroup dmac_transfers)
 **********************************************************************************************************************/