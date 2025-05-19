/***********************************************************************************************************************
 * File Name    : i2c_slave.c
 * Description  : Contains data structures and functions used in i2c_slave.c.
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
#include "i2c_slave.h"
#include "stdbool.h"

/*******************************************************************************************************************//**
 * @addtogroup r_riic_slave_ep
 * @{
 **********************************************************************************************************************/

/*
 * Private Global Variables
 */

/* enumerators to identify Slave event to be processed. */
typedef enum slave
{
    SLAVE_READ  = 1U,
    SLAVE_WRITE = 2U,
    SLAVE_NO_RW = 3U
}slave_transfer_mode_t;

/* Slave transmit buffer */
static uint8_t g_slave_tx_buf[BUF_LEN] __attribute__((section("UNCACHED_BSS")));
/* Slave receive buffer */
static uint8_t g_slave_rx_buf[BUF_LEN] __attribute__((section("UNCACHED_BSS")));

/* capture callback event for Slave and master module */
static volatile i2c_slave_event_t  g_slave_event  = (i2c_slave_event_t)RESET_VALUE;

/* Event flag to identify the slave event.  */
static volatile slave_transfer_mode_t g_slave_RW  = SLAVE_READ;

/* for on board LEDs */
extern bsp_leds_t g_bsp_leds;

/*
 * private functions
 */
static fsp_err_t iic_slave_write(void);
static fsp_err_t iic_slave_read(void);
void led_update(led_state_t led_state);

/*******************************************************************************************************************//**
 * @brief     Initialize RIIC slave driver.
 * @param[IN] None
 * @retval    FSP_SUCCESS       R_RIIC Slave driver opened successfully.
 * @retval    err               Any Other Error code apart from FSP_SUCCES like Unsuccessful Open.
 **********************************************************************************************************************/
fsp_err_t init_i2C_driver(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Open slave I2C channel */
    err = R_RIIC_SLAVE_Open(&g_i2c_slave_ctrl, g_i2c_slave.p_cfg);
    if (FSP_SUCCESS != err)
    {
        /* Display failure message in Terminal Emulator */
        APP_ERR_PRINT ("R_RIIC_SLAVE_Open API failed \r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 *  @brief      performs Slave write read operations and toggle LED on successful operation
 *              else Turn LED ON on failure
 *              If slave i2c transaction failure occurs then it halts the application turning LED ON
 *              as sign of failure. Also displays failure messages in Terminal Emulator.
 *  @retval     FSP_SUCCESS    On successfully R_RIIC_Mater and Slave Write/Read operation.
 *  @retval     err            Any Other Error code apart from FSP_SUCCES  Unsuccessful Write/Read operation.
 **********************************************************************************************************************/
fsp_err_t process_slave_WriteRead(void)
{
    fsp_err_t error = FSP_SUCCESS;

    switch(g_slave_RW)
    {
        case SLAVE_READ:
        {
            /*slave starts reading the data */
            error = iic_slave_read();

            if (FSP_SUCCESS != error)
            {
            /* blink the LED */
            led_update(led_error);

            /* print Tera Term message */
            APP_ERR_PRINT ("** Slave read data operation failed !  **\r\n");
            }
            g_slave_RW = SLAVE_WRITE;
            break;
        }
        case SLAVE_WRITE:
        {
            /* slave starts transmission of data */
            error = iic_slave_write();
            if (FSP_SUCCESS != error)
            {
                /* blink the LED */
                led_update(led_error);

                /* print Tera Term message */
                APP_ERR_PRINT ("** Slave read data operation failed !  **\r\n");
            }
            g_slave_RW = SLAVE_READ ;
            break;
        }
        default:
            break;
    }

    return error;
}

/*******************************************************************************************************************//**
 *  @brief       Perform Slave write operation
 *  @param[in]   None
 *  @retval      FSP_SUCCESS               Slave successfully write all data to master.
 *  @retval      FSP_ERR_TRANSFER_ABORTED  callback event failure
 *  @retval      FSP_ERR_ABORTED           data mismatched occurred.
 *  @retval      FSP_ERR_TIMEOUT           in case of no callback event occurrence
 *  @retval      write_err                 API returned error if any
**********************************************************************************************************************/
static fsp_err_t iic_slave_write(void)
{
    fsp_err_t write_err           = FSP_SUCCESS;
    if( I2C_SLAVE_EVENT_TX_COMPLETE == g_slave_event  )
    {
        led_update(transmitting);

        /* resetting callback event */
        g_slave_event  = (i2c_slave_event_t)RESET_VALUE;

        /* clear the slave tx buffer */
        memset(g_slave_tx_buf, RESET_VALUE, BUF_LEN);
    }

    return write_err;
}

/*******************************************************************************************************************//**
 *  @brief      Perform Slave read operation
 *  @param[in]  None
 *  @retval     FSP_SUCCESS               Slave successfully received all data issued by master.
 *  @retval     FSP_ERR_TRANSFER_ABORTED  callback event failure
 *  @retval     FSP_ERR_ABORTED           data mismatched occurred.
 *  @retval     FSP_ERR_TIMEOUT           in case of no callback event occurrence
 *  @retval     read_err                  API returned error if any
 **********************************************************************************************************************/
static fsp_err_t iic_slave_read(void)
{
    fsp_err_t read_err           = FSP_SUCCESS;
    uint8_t standard_buffer[BUF_LEN] = {0x10, 0x20, 0x30, 0x40, 0x50};

    /* Check slave read complete */
    if( I2C_SLAVE_EVENT_RX_COMPLETE == g_slave_event  )
    {

    /* compare slave read buffer with standard data */
    if ( BUFF_EQUAL == memcmp(g_slave_rx_buf, standard_buffer, BUF_LEN) )
    {
        /* set on the led  */
        led_update(successful);

        APP_PRINT (" ** Slave read operation sucessfully **\r\n");

        /* resetting callback event */
        g_slave_event  = (i2c_slave_event_t)RESET_VALUE;

        /* clear the slave rx buffer */
        memset(g_slave_rx_buf, RESET_VALUE, BUF_LEN);
    }
    else
    {
        read_err = FSP_ERR_NOT_FOUND ;
        led_update(led_error);

        APP_ERR_PRINT ("** Slave read data operation failed !  **\r\n");
    }
    }
    return read_err;
}


/*******************************************************************************************************************//**
 *  @brief        User defined slave callback function.
 *  @param[in]    p_args
 *  @retval       None
 **********************************************************************************************************************/
void i2c_slave_callback(i2c_slave_callback_args_t * p_args)
{
    fsp_err_t err = FSP_SUCCESS;

    if (NULL != p_args)
    {
        switch(p_args->event)
        {
            case I2C_SLAVE_EVENT_RX_REQUEST:
            {
                /* clear the slave rx buffer */
                memset(g_slave_rx_buf, RESET_VALUE, BUF_LEN);

            	/*Perform Slave Read operation*/
                err = R_RIIC_SLAVE_Read(&g_i2c_slave_ctrl, g_slave_rx_buf, BUF_LEN);

                if(FSP_SUCCESS != err)
                {
                	/* Update return error here */
                    APP_ERR_PRINT (" **  R_RIIC_Slave_Read API failed **\r\n");
                }
                break;
            }
            case I2C_SLAVE_EVENT_TX_REQUEST:
            {
                uint8_t standard_buffer[BUF_LEN] = {0x01, 0x02, 0x03, 0x04, 0x05};

                /* update slave rx buffer with standard data*/
                memcpy(g_slave_tx_buf, standard_buffer, BUF_LEN);

                /* Start Slave write the data to master */
                err = R_RIIC_SLAVE_Write(&g_i2c_slave_ctrl, g_slave_tx_buf, BUF_LEN);

                if(FSP_SUCCESS != err)
                {
                   /* Update return error here */
                   APP_ERR_PRINT (" **  R_RIIC_Slave_Write API failed **\r\n");
                }
                break;
            }
            default:
                /* log the event to global variable for any other slave event */
                g_slave_event = p_args->event;
                break;
        }
    }
 }
/*******************************************************************************************************************//**
 * This function is called to do closing of external i2c master and slave module using its HAL level API.
 * @brief     Close the RIIC Master and Slave module. Handle the Error internally with Proper Terminal Emulator Message.
 *            Application handles the rest.
 * @param[in] None
 * @retval    None
 **********************************************************************************************************************/
void deinit_i2c_driver(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* close opened RIIC slave module */
    err = R_RIIC_SLAVE_Close(&g_i2c_slave_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT(" **  R_RIIC_Slave_Close API failed ** \r\n");
    }
}

/*******************************************************************************************************************//**
 * @brief This function updates led state as per operation status
 * @param[in]  led_state      Select LED states according to operations.
 * @retval     None
 **********************************************************************************************************************/
void led_update(led_state_t led_state)
{
    switch(led_state)
    {
        case led_error:
        {
            /* PMOD LED will high to show error state */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED1], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED2], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED3], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED4], BSP_IO_LEVEL_HIGH);
            break;
        }
        case successful:
        {
            R_BSP_SoftwareDelay(WAIT_TIME/5, BSP_DELAY_UNITS_MILLISECONDS);
            /* PMOD LED will blink to show successful state */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED1], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED2], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED3], BSP_IO_LEVEL_HIGH);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED4], BSP_IO_LEVEL_HIGH);

            /* Delay */
            R_BSP_SoftwareDelay(WAIT_TIME/2, BSP_DELAY_UNITS_MILLISECONDS);

            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED1], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED2], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED3], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED4], BSP_IO_LEVEL_LOW);


            break;
        }
        case transmitting:
        {
            /* Set the LED pin state low */
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED1], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED2], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED3], BSP_IO_LEVEL_LOW);
            R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[BSP_LED_LED4], BSP_IO_LEVEL_LOW);

            for(int i = 0; i < 4; i ++)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[i], BSP_IO_LEVEL_HIGH);
                /* Delay */
                R_BSP_SoftwareDelay(WAIT_TIME/10, BSP_DELAY_UNITS_MILLISECONDS);
            }

            for(int j = 0; j < 4; j ++)
            {
                R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t) g_bsp_leds.p_leds[j], BSP_IO_LEVEL_LOW);
                /* Delay */
                R_BSP_SoftwareDelay(WAIT_TIME/10, BSP_DELAY_UNITS_MILLISECONDS);
            }

            break;
        }
        default:
        {
            break;
        }
    }

}
/*******************************************************************************************************************//**
 * @} (end addtogroup  R_RIIC_slave_ep)
 **********************************************************************************************************************/
