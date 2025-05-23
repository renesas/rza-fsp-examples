/***********************************************************************************************************************
* File Name    : i2c_sensor.c
* Description  : Contains data structures and functions used in i2c_sensor.c.
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
#include "i2c_sensor.h"
#include "stdbool.h"
#include "stdint.h"

/*******************************************************************************************************************//**
* @addtogroup r_riic_master_ep
* @{
**********************************************************************************************************************/

/*
* Global Variables
*/

uint8_t measure_enable_payload[MEASURE_PAYLOAD_SIZE] __attribute__((section("UNCACHED_BSS")));
uint8_t adxl_data[SENSOR_DATA_SIZE] __attribute__((section("UNCACHED_BSS")));
uint8_t internal_reg __attribute__((section("UNCACHED_BSS")));
uint8_t reg_address   __attribute__((section("UNCACHED_BSS")))  ;

/* Reading I2C call back event through i2c_Master callback */
static volatile i2c_master_event_t i2c_event = I2C_MASTER_EVENT_ABORTED;

/*
* private function declarations
*/
static fsp_err_t get_device_id(uint8_t *dev_id);
static fsp_err_t validate_i2c_event(void);

/*******************************************************************************************************************//**
*  @brief       initialize RIIC master module and set up PMOD ACL sensor
*  @param[IN]   None
*  @retval      FSP_SUCCESS                  Upon successful open and start of timer
*  @retval      Any Other Error code apart from FSP_SUCCESS is  Unsuccessful open or start
**********************************************************************************************************************/
fsp_err_t init_sensor(void)
{
    fsp_err_t err     = FSP_SUCCESS;
    uint8_t device_id = RESET_VALUE;
    measure_enable_payload[0] =  POWER_CTL_REG;
    measure_enable_payload[1] =  ENABLE_BIT;
    /* opening RIIC master module */
    err = R_RIIC_MASTER_Open(&g_i2c_master_ctrl, &g_i2c_master_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_RIIC_MASTER_Open API failed ** \r\n");
        return err;
    }

    /* Get device ID as a start of communication */
    err =  get_device_id(&device_id);

    /* Verify I2C transaction is successful with PMOD ACL and correct device ID is received */
    if ( (FSP_SUCCESS == err) && (DEVICE_SIGNATURE == device_id) )
    {
        /* Access to POWER_CTL Register (0x2D) and enable measurement  */
        err = R_RIIC_MASTER_Write(&g_i2c_master_ctrl, &measure_enable_payload[0], TWO_BYTE, false);
        if (FSP_SUCCESS == err)
        {
            err = validate_i2c_event();
            /* handle error */
            if(FSP_ERR_TRANSFER_ABORTED == err)
            {
                APP_ERR_PRINT("** POWER_CTL reg I2C write failed!!! ** \r\n");
            }
        }
        /* handle error */
        else
        {
            /* Write API returns itself is not successful */
            APP_ERR_PRINT("** R_RIIC_MASTER_Write API failed ** \r\n");
        }
    }
    /* handle error */
    else
    {
        /* Failed to get Device ID */
        APP_ERR_PRINT("** Error in reading Device ID ** \r\n");
    }
    return err;
}


/*******************************************************************************************************************//**
*  @brief       DeInitialize RIIC master module
*  @param[IN]   None
*  @retval      None
**********************************************************************************************************************/
void deinit_sensor(void)
{
    fsp_err_t err     = FSP_SUCCESS;

    /* close open modules */
    err =  R_RIIC_MASTER_Close (&g_i2c_master_ctrl);

    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_RIIC_MASTER_Close API failed ** \r\n");
    }
}
/*******************************************************************************************************************//**
*  @brief       Read The ACL Sensor data for X,Y and Z axis. And prints the raw data on Terminal Emulator
*  @param[IN]   Array pointer to get the sensor data
*  @retval      FSP_SUCCESS                  Upon successful open and start of timer
*  @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful open or start
**********************************************************************************************************************/
fsp_err_t read_sensor_data(uint8_t *xyz_data)
{
    fsp_err_t err           = FSP_SUCCESS;
    internal_reg = AXIS_DATA;
    memset(adxl_data, 0U, SENSOR_DATA_SIZE);
    if(NULL == xyz_data)
    {
        err = FSP_ERR_INVALID_POINTER;
        APP_ERR_PRINT("** NULL Pointer check fail ** \r\n");
        return err;
    }
    /* Write Accelerometer Data register   */
    err = R_RIIC_MASTER_Write(&g_i2c_master_ctrl, &internal_reg, ONE_BYTE, true);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_RIIC_MASTER_Write API failed ** \r\n");
        return err;
    }
    else
    {
        err = validate_i2c_event();

        /* Performs read operation only when write event is successful, failure part is handled at next stage*/
        if (FSP_SUCCESS == err)
        {
            err = R_RIIC_MASTER_Read(&g_i2c_master_ctrl, &adxl_data[0], DATA_REGISTERS, false);
            /* handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("** R_RIIC_MASTER_Read API failed ** \r\n");
                return err;
            }
            else
            {
                err = validate_i2c_event();
                if (FSP_SUCCESS != err)
                {
                    APP_ERR_PRINT("** Data register, I2C read failed ** \r\n");
                    return err;
                }
            }
        }
        else
        {
            APP_ERR_PRINT("** Accel Data register, I2C write failed ** \r\n");
            return err;
        }

        /*  Read is successful update the x,y,z values and return success */
        for (uint8_t itr = RESET_VALUE; itr < SENSOR_DATA_SIZE; itr++)
        {
            *(xyz_data+itr) = adxl_data[itr];
        }
    }
    return err;
}

/*******************************************************************************************************************//**
*  @brief     Read Device signature/ID from sensor
*
*  @param[in] dev_id                       retrieve PMOD ACL device ID
*
*  @retval    FSP_SUCCESS                  on successful I2C transaction
*             FSP_ERR_INVALID_POINTER      if invalid parameters passed
*             err                          whichever occurs on either API or on I2C event failure
**********************************************************************************************************************/
static fsp_err_t get_device_id(uint8_t *dev_id)
{
    fsp_err_t err         = FSP_SUCCESS;
    reg_address = DEVICE_ID_REG;
    /* Parameter checking */
    if (NULL == dev_id)
    {
        err = FSP_ERR_INVALID_POINTER;
        APP_ERR_PRINT("** NULL Pointer check fail ** \r\n");
        return err;
    }

    /* Send register address to sensor */
    err = R_RIIC_MASTER_Write(&g_i2c_master_ctrl, &reg_address, ONE_BYTE, true);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("** R_RIIC_MASTER_Write API failed ** \r\n");
    }
    else
    {
        err = validate_i2c_event();
        /* handle error */
        if(FSP_ERR_TRANSFER_ABORTED == err)
        {
            APP_ERR_PRINT("** Device ID reg, I2C write failed ** \r\n");
        }
        else
        {
            /* Read only when I2C write and its callback event is successful */
            err  = R_RIIC_MASTER_Read(&g_i2c_master_ctrl, dev_id, ONE_BYTE, false);
            /* handle error */
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("** R_RIIC_MASTER_Read API failed ** \r\n");
                //  Do nothing, the error is returned in the end
            }
            else
            {
                err = validate_i2c_event();
                /* handle error */
                if(FSP_ERR_TRANSFER_ABORTED == err)
                {
                    APP_ERR_PRINT("** Device ID read,  I2C read failed ** \r\n");
                }
            }
        }
    }
    /* On successful I2C transaction with PMOD-ACL return from here */
    return err;
}

/*******************************************************************************************************************//**
*  @brief      User callback function
*  @param[in]  p_args
*  @retval None
**********************************************************************************************************************/
void i2c_master_callback(i2c_master_callback_args_t *p_args)
{
    if (NULL != p_args)
    {
        /* capture callback event for validating the i2c transfer event*/
        i2c_event = p_args->event;
    }
}

/*******************************************************************************************************************//**
*  @brief       Validate i2c receive/transmit  based on required write read operation
*
*  @param[in]   None
*
*  @retval      FSP_SUCCESS                       successful event receiving returns FSP_SUCCESS
*               FSP_ERR_TRANSFER_ABORTED          Either on timeout elapsed or received callback event is
*                                                 I2C_MASTER_EVENT_ABORTED
**********************************************************************************************************************/
static fsp_err_t validate_i2c_event(void)
{
    uint64_t local_time_out = UINT64_MAX;

    /* resetting call back event capture variable */
    i2c_event = (i2c_master_event_t)RESET_VALUE;

    do
    {
        /* This is to avoid infinite  loop */
        --local_time_out;

        if(RESET_VALUE == local_time_out)
        {
            return FSP_ERR_TRANSFER_ABORTED;
        }

    }while(i2c_event == RESET_VALUE);

    if(i2c_event != I2C_MASTER_EVENT_ABORTED)
    {
        i2c_event = (i2c_master_event_t)RESET_VALUE;  // Make sure this is always Reset before return
        return FSP_SUCCESS;
    }

    i2c_event = (i2c_master_event_t)RESET_VALUE; // Make sure this is always Reset before return
    return FSP_ERR_TRANSFER_ABORTED;
}

/*******************************************************************************************************************//**
* @} (end addtogroup r_riic_master_ep)
**********************************************************************************************************************/
