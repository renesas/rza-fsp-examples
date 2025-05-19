/***********************************************************************************************************************
 * File Name    : gt911.c
 * Description  : Contains data structures and functions setup gt911 used in mipi_dsi_ep.c.
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

#include "hal_data.h"
#include "common_utils.h"
#include "gt911.h"

/*******************************************************************************************************************//**
 * @addtogroup gt911
 * @{
 **********************************************************************************************************************/

/* global variable */
volatile i2c_master_event_t    g_i2c_master_event;

/* User defined functions */
static fsp_err_t wait_for_i2c_event (i2c_master_event_t event);
static fsp_err_t gt911_i2c_write(uint8_t *buf, uint32_t len);
static fsp_err_t gt911_i2c_read(uint8_t *buf, uint32_t len);

/*******************************************************************************************************************//**
 *  @brief       This function is used to read data from gt911 device.
 *  @param[out]  status      : Store status register returned over I2C.
 *  @param[out]  points      : Store co-ordinate values returned over I2C.
 *  @param[in]  num_points      : Store buffer data.
 *  @retval      FSP_SUCCESS : Upon successful operation, otherwise: failed
 **********************************************************************************************************************/
fsp_err_t gt911_get_status(uint8_t* status, coord_t * points, uint32_t num_points)
{
    /* Buffer to read status along with co-ordinates for 5 touchpoints as mentioned in
     * GT911 Programming Guide. */
    uint8_t g_i2c_rx_buffer[1 + (sizeof(gt911_point_payload_t)) * 5];
    fsp_err_t err = FSP_SUCCESS;
    uint8_t   g_i2c_tx_buffer[BUFFER_LENGTH] = {RESET_VALUE};

    g_i2c_tx_buffer[0] = (GTP_READ_COOR_ADDR & 0xFF00) >> 8;
    g_i2c_tx_buffer[1] = (GTP_READ_COOR_ADDR & 0xFF);
    g_i2c_tx_buffer[2] = RESET_VALUE;

    memset(&g_i2c_rx_buffer[0], 0, sizeof(g_i2c_rx_buffer));

    /* Read buffer status */
    err = gt911_i2c_write ((uint8_t*) &g_i2c_tx_buffer[0], GTP_ADDR_LENGTH);
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** gt911_i2c_write function FAILED ** \r\n");
    }

    err = gt911_i2c_read (g_i2c_rx_buffer, sizeof(g_i2c_rx_buffer));
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** gt911_i2c_read function FAILED ** \r\n");
    }

    /* Copy in the number of points expected by the upper layer */
    *status = g_i2c_rx_buffer[0];

    if (num_points >= 5)
    {
        memcpy(&points[4], &g_i2c_rx_buffer[1 + sizeof(gt911_point_payload_t)*4 + 1], sizeof(coord_t));
    }
    if (num_points >= 4)
    {
        memcpy(&points[3], &g_i2c_rx_buffer[1 + sizeof(gt911_point_payload_t)*3 + 1], sizeof(coord_t));
    }
    if (num_points >= 3)
    {
        memcpy(&points[2], &g_i2c_rx_buffer[1 + sizeof(gt911_point_payload_t)*2 + 1], sizeof(coord_t));
    }
    if (num_points >= 2)
    {
        memcpy(&points[1], &g_i2c_rx_buffer[1 + sizeof(gt911_point_payload_t)*1 + 1], sizeof(coord_t));
    }
    if (num_points >= 1)
    {
        memcpy(&points[0], &g_i2c_rx_buffer[1 + sizeof(gt911_point_payload_t)*0 + 1], sizeof(coord_t));
    }


    /* Clear buffer status*/
    err = gt911_i2c_write ((uint8_t*) &g_i2c_tx_buffer[0], (GTP_ADDR_LENGTH + 1));
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** gt911_i2c_write function FAILED ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 *  @brief       This function is used to write data to the i2c slave device.
 *
 *  @param[in]   buf[0~1]    : write start address.
 *  @param[in]   buf[2~len-1]: write data buffer
 *  @param[in]   len         : length of data buffer.
 *  @retval      FSP_SUCCESS : Upon successful operation, otherwise: failed
 **********************************************************************************************************************/
static fsp_err_t gt911_i2c_write(uint8_t *buf, uint32_t len)
{
    fsp_err_t err = FSP_SUCCESS;

    /* write data to the i2c slave device */
    g_i2c_master_event = I2C_MASTER_EVENT_ABORTED;
    err = R_RIIC_MASTER_Write (&g_i2c_master_ctrl, buf, len, false);
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** RIIC MASTER_Write API FAILED ** \r\n");
    }

    /* Wait until write transmission complete */
    err = wait_for_i2c_event (I2C_MASTER_EVENT_TX_COMPLETE);
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** I2C master event timeout ** \r\n");
    }


    return err;
}

/*******************************************************************************************************************//**
 *  @brief       This function is used to read data from the i2c slave device.
 *
 *  @param[in]   buf[0~1]    : read start address.
 *  @param[in]   buf[2~len-1]: read data buffer.
 *  @param[in]   len         : length of data buffer.
 *  @retval      FSP_SUCCESS : Upon successful operation, otherwise: failed
 **********************************************************************************************************************/
static fsp_err_t gt911_i2c_read(uint8_t *buf, uint32_t len)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Read data back from the I2C slave */
    g_i2c_master_event = I2C_MASTER_EVENT_ABORTED;
    err = R_RIIC_MASTER_Read(&g_i2c_master_ctrl, buf, len, false);
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** RIIC MASTER_Read API FAILED  ** \r\n");
    }

    /* Wait until write receive complete */
    err = wait_for_i2c_event (I2C_MASTER_EVENT_RX_COMPLETE);
    if (err != FSP_SUCCESS)
    {
        APP_ERR_PRINT(" ** I2C master event timeout ** \r\n");
    }

    return err;
}

/*******************************************************************************************************************//**
 * @brief       This function is used to Wait for i2c event.
 *
 * @param[in]   event       : Expected events
 * @retval      FSP_SUCCESS : Upon successful operation, otherwise: failed
 **********************************************************************************************************************/
static fsp_err_t wait_for_i2c_event (i2c_master_event_t event)
{
    uint32_t timeout = R_FSP_SystemClockHzGet(FSP_PRIV_CLOCK_ICLK) / 10;
    while (timeout-- && (g_i2c_master_event != event))
    {
        ;
    }
    return timeout ? FSP_SUCCESS : FSP_ERR_TIMEOUT;
}

/*******************************************************************************************************************//**
 * @brief      Callback functions for i2c master interrupts
 *
 * @param[in]  p_args    Callback arguments
 * @retval     none
 **********************************************************************************************************************/
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        g_i2c_master_event = p_args->event;
    }
}
/*******************************************************************************************************************//**
 * @} (end addtogroup gt911)
 **********************************************************************************************************************/
