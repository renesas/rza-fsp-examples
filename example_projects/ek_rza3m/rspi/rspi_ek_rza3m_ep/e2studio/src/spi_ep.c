/***********************************************************************************************************************
 * File Name    : spi_ep.c
 * Description  : Contains data structures and functions used in spi_ep.c.
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
#include "spi_ep.h"

/*******************************************************************************************************************//**
 * @addtogroup spi_ep
 * @{
 **********************************************************************************************************************/

/*
 * private function declarations
 */
static void error_print(void);

/* Wait counter for wait operation monitoring */
static volatile uint32_t g_wait_count = MAX_COUNT;

/* Event flags for master and slave */
static volatile spi_event_t g_master_event_flag;    // Master Transfer Event completion flag
static volatile spi_event_t g_slave_event_flag;     // Slave Transfer Event completion flag

/* SPI module buffers for Master and Slave */
static uint32_t g_master_tx_buff[BUFF_LEN] __attribute__((section("UNCACHED_BSS")));   // Master Transmit Buffer
static uint32_t g_master_rx_buff[BUFF_LEN] __attribute__((section("UNCACHED_BSS")));   // Master Receive Buffer
static uint32_t g_slave_tx_buff[BUFF_LEN] __attribute__((section("UNCACHED_BSS")));    // Slave Transmit Buffer
static uint32_t g_slave_rx_buff[BUFF_LEN] __attribute__((section("UNCACHED_BSS")));    // Slave Receive Buffer

/*******************************************************************************************************************//**
 * @brief       This functions initializes SPI master and slave modules.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful open of SPI module
 * @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful open
 **********************************************************************************************************************/
fsp_err_t spi_init(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status

    /* Open/Initialize SPI Master module */
    err = R_RSPI_Open (&g_spi_master_ctrl, &g_spi_master_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* SPI Master Failure message */
        APP_ERR_PRINT("** R_RSPI_Open API for SPI Master failed **\r\n");
        return err;
    }

    /* Open/Initialize SPI Slave module */
    err = R_RSPI_Open (&g_spi_slave_ctrl, &g_spi_slave_cfg);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* Close SPI master */
        if ( (FSP_SUCCESS != R_RSPI_Close(&g_spi_master_ctrl)))
        {
            /* SPI Master Close Failure message */
            APP_ERR_PRINT("** R_RSPI_Close API for SPI Master failed **\r\n");
        }
        /* SPI Slave Failure message */
        APP_ERR_PRINT("** R_RSPI_Open API for SPI Master failed **\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief This function demos both R_RSPI_Write() and R_RSPI_Read() individually.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful SPI Write and SPI Read
 * @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful Write and Read
 **********************************************************************************************************************/
fsp_err_t spi_write_and_read(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status
    uint32_t num_bytes = RESET_VALUE;  // Number of bytes read by SEGGER real-time-terminal

    /* Cleaning buffers */
    memset(&g_master_tx_buff[0], NULL_CHAR, sizeof(g_master_tx_buff));
    memset(&g_master_rx_buff[0], NULL_CHAR, sizeof(g_master_rx_buff));
    memset(&g_slave_rx_buff[0], NULL_CHAR, sizeof(g_slave_rx_buff));

    /* Input to master buffer */
    APP_PRINT("Enter text input for Master buffer. Data size should not exceed 64 bytes.\r\n");
    while (BYTES_RECEIVED_ZERO == num_bytes)
    {
        if (APP_CHECK_DATA)
        {
            APP_READ((unsigned char*)g_master_tx_buff);
            APP_PRINT("Input data: %s\r\n\r\n" , (char *)g_master_tx_buff);

            num_bytes =  (uint32_t)strlen((char *)g_master_tx_buff);
            if(BYTES_RECEIVED_ZERO == num_bytes)
            {
                APP_PRINT("No Input\r\n\r\n");
            }
        }
    }
    /* Terminal Emulator user input data 1 byte at a time. SPI transfers the data 4 bytes at a time.
     * With the below logic, we will calculate how many length of data has to be transferred. */
    if(num_bytes % BITS_TO_BYTES != RESET_VALUE)
    {
        num_bytes = (num_bytes/BITS_TO_BYTES) + 1U;
    }
    else
    {
        num_bytes = num_bytes/BITS_TO_BYTES;
        g_master_tx_buff[num_bytes] = RESET_VALUE;
    }

    /* Slave receive data from Master */
    err = R_RSPI_Read(&g_spi_slave_ctrl, g_slave_rx_buff, num_bytes, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if(err != FSP_SUCCESS)
    {
        APP_ERR_PRINT("Slave R_RSPI_Read() failed\r\n");
        return err;
    }

    /* Master send data to Slave */
    err = R_RSPI_Write(&g_spi_master_ctrl, g_master_tx_buff, num_bytes, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Master R_RSPI_Write() failed\r\n");
        return err;
    }

    /* Wait until master write and slave read complete */
    while((SPI_EVENT_TRANSFER_COMPLETE != g_master_event_flag)||(SPI_EVENT_TRANSFER_COMPLETE != g_slave_event_flag))
    {
        g_wait_count--;
        if (MIN_COUNT >= g_wait_count)
        {
            /* Return time out error if SPI operation fails to complete */
            err = FSP_ERR_TIMEOUT;
            APP_ERR_PRINT("SPI module blocked in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else if ((SPI_EVENT_TRANSFER_ABORTED == g_master_event_flag) || (SPI_EVENT_TRANSFER_ABORTED == g_slave_event_flag))
        {
            err = FSP_ERR_TRANSFER_ABORTED;
            APP_ERR_PRINT("SPI module blocked in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else
        {
            /* Do nothing */
        }

    }
    g_wait_count = MAX_COUNT;

    g_master_event_flag = (spi_event_t) RESET_VALUE;  // Reseting master_event flag
    g_slave_event_flag  = (spi_event_t) RESET_VALUE;  // Reseting slave_event flag

    /* Display Master to Slave transmission */
    APP_PRINT("Master transmitted user input data to Slave\r\n\r\n");

    /* Slave send data to Master */
    err = R_RSPI_Write(&g_spi_slave_ctrl, g_slave_rx_buff, num_bytes, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Slave R_RSPI_Write() failed\r\n");
        return err;
    }

    /* Master receive data from Slave */
    err = R_RSPI_Read(&g_spi_master_ctrl, g_master_rx_buff, num_bytes, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Master R_RSPI_Read() failed\r\n");
        return err;
    }

    /* Wait until slave write and master read complete */
    while((SPI_EVENT_TRANSFER_COMPLETE != g_master_event_flag)||(SPI_EVENT_TRANSFER_COMPLETE != g_slave_event_flag))
    {
        /* Time out operation if SPI operation fails to complete */
        g_wait_count--;
        if(MIN_COUNT >= g_wait_count)
        {
            err = FSP_ERR_TIMEOUT;
            APP_ERR_PRINT("SPI module blocked in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else if ((SPI_EVENT_TRANSFER_ABORTED == g_master_event_flag) || (SPI_EVENT_TRANSFER_ABORTED == g_slave_event_flag))
        {
            err = FSP_ERR_TRANSFER_ABORTED;
            APP_ERR_PRINT("SPI module blocked in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else
        {
            /* Do nothing */
        }
    }
    g_wait_count = MAX_COUNT;

    g_master_event_flag = (spi_event_t) RESET_VALUE;  // Reseting master_event flag
    g_slave_event_flag  = (spi_event_t) RESET_VALUE;  // Reseting slave_event flag

    /* Display Slave to Master transmission */
    APP_PRINT("Slave transmitted the data back to Master\r\n\r\n");

    /* Check whether transmitted data is equal to received data */
    if(BUFF_EQUAL == memcmp(g_master_tx_buff, g_master_rx_buff, num_bytes))
    {
        /* Display Master's received data on Terminal Emulator */
        APP_PRINT("Master received data: %s\r\n\r\n" , (char *)g_master_rx_buff);
    }
    else
    {
        /* Return Parity error in case of data mismatch */
        err = FSP_ERR_SPI_PARITY;
        APP_PRINT("Received data does not match with transmitted Data.\r\n\r\n");
        error_print();
        return err;
    }

    /* Delay of one second for user to verify the output */
    R_BSP_SoftwareDelay(DELAY_ONE_SEC, BSP_DELAY_UNITS_SECONDS);
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function demos R_RSPI_WriteRead() for both Master and Slave simultaneously.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  Upon successful Write and Read for both Master and Slav
 * @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful Write and Read
 **********************************************************************************************************************/
fsp_err_t spi_write_read(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status
    /* Number of bytes read by SEGGER real-time-terminal for master and slave inputs */
    uint32_t num_bytes_master = RESET_VALUE;
    uint32_t num_bytes_slave = RESET_VALUE;

    /* Cleaning buffers */
    memset(&g_master_tx_buff[0], NULL_CHAR, sizeof(g_master_tx_buff));
    memset(&g_master_rx_buff[0], NULL_CHAR, sizeof(g_master_rx_buff));
    memset(&g_slave_tx_buff[0], NULL_CHAR, sizeof(g_slave_tx_buff));
    memset(&g_slave_rx_buff[0], NULL_CHAR, sizeof(g_slave_rx_buff));

    /* Input to master buffer */
    APP_PRINT("Enter text input for Master buffer. Data size should not exceed 64 bytes.\r\n");
    while (BYTES_RECEIVED_ZERO == num_bytes_master)
    {
        if (APP_CHECK_DATA)
        {
            APP_READ((unsigned char*)g_master_tx_buff);
            APP_PRINT("Input data: %s\r\n\r\n" , (char *)g_master_tx_buff);
            num_bytes_master = (uint32_t)strlen((char *)g_master_tx_buff);

            if(BYTES_RECEIVED_ZERO == num_bytes_master)
            {
                APP_PRINT("No Input\r\n\r\n");
            }
        }
    }
    /* Terminal Emulator user input data 1 byte at a time. SPI transfers the data 4 bytes at a time.
     * With the below logic, we will calculate how many length of data has to be transferred. */
    if(num_bytes_master % BITS_TO_BYTES != RESET_VALUE)
    {
        num_bytes_master = (num_bytes_master/BITS_TO_BYTES) + 1U;
    }
    else
    {
        num_bytes_master = num_bytes_master/BITS_TO_BYTES;
        g_master_tx_buff[num_bytes_master] = RESET_VALUE;
    }

    /* Input to slave buffer */
    APP_PRINT("Enter text input for Slave buffer. Data size should not exceed 64 bytes.\r\n");
    while (BYTES_RECEIVED_ZERO == num_bytes_slave)
    {
        if (APP_CHECK_DATA)
        {
            APP_READ((unsigned char*)g_slave_tx_buff);
            APP_PRINT("Input data: %s\r\n\r\n" , (char *)g_slave_tx_buff);
            num_bytes_slave = (uint32_t)strlen((char *)g_slave_tx_buff);
            if(BYTES_RECEIVED_ZERO == num_bytes_slave)
            {
                APP_PRINT("No Input\r\n\r\n");
            }
        }
    }

    /* Terminal Emulator user input data 1 byte at a time. SPI transfers the data 4 bytes at a time.
     * With the below logic, we will calculate how many length of data has to be transferred. */
    if(num_bytes_slave % BITS_TO_BYTES != RESET_VALUE)
    {
        num_bytes_slave = (num_bytes_slave/BITS_TO_BYTES) + 1U;
    }
    else
    {
        num_bytes_slave = num_bytes_slave/BITS_TO_BYTES;
        g_slave_tx_buff[num_bytes_slave] = RESET_VALUE;
    }

    /* Slave send data to Master and receive data from Master */
    err = R_RSPI_WriteRead(&g_spi_slave_ctrl, g_slave_tx_buff, g_slave_rx_buff, num_bytes_master, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Slave R_RSPI_WriteRead() failed\r\n");
        return err;
    }

    /* Master send data to Slave and receive data from Slave */
    err = R_RSPI_WriteRead(&g_spi_master_ctrl, g_master_tx_buff, g_master_rx_buff, num_bytes_master, SPI_BIT_WIDTH_32_BITS);
    /* Error handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Master R_RSPI_WriteRead() failed\r\n");
        return err;
    }

    /* Wait until master and slave WriteRead() complete */
    while((SPI_EVENT_TRANSFER_COMPLETE != g_master_event_flag)||(SPI_EVENT_TRANSFER_COMPLETE != g_slave_event_flag))
    {
        /* Timer out operation if SPI operation fails to complete */
        g_wait_count--;
        if (MIN_COUNT >= g_wait_count)
        {
            err = FSP_ERR_TIMEOUT;
            APP_ERR_PRINT("SPI module failed in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else if ((SPI_EVENT_TRANSFER_ABORTED == g_master_event_flag) || (SPI_EVENT_TRANSFER_ABORTED == g_slave_event_flag))
        {
            err = FSP_ERR_TRANSFER_ABORTED;
            APP_ERR_PRINT("SPI module failed in Write/Read operation.\r\n\r\n");
            error_print();
            return err;
        }
        else
        {
            /* Do nothing */
        }
    }
    g_wait_count = MAX_COUNT;

    g_master_event_flag = (spi_event_t) RESET_VALUE;  // Reseting master_event flag
    g_slave_event_flag  = (spi_event_t) RESET_VALUE;  // Reseting slave_event flag

    /* Display Master to Slave and Slave to Master transmission */
    APP_PRINT("Master buffer data transmitted to Slave\r\n\r\n");
    APP_PRINT("Slave buffer data transmitted to Master\r\n\r\n");

    /* Check whether Slave transmitted data is equal to Master received data */
    if(BUFF_EQUAL == memcmp(g_slave_tx_buff, g_master_rx_buff, num_bytes_master))
    {
        /* Display Master's received data on Terminal Emulator */
        APP_PRINT("Master received data: %s\r\n\r\n", (char *)g_master_rx_buff);
    }
    else
    {
        /* Return Parity error in case of data mismatch */
        err = FSP_ERR_SPI_PARITY;
        APP_ERR_PRINT("Master received data does not match with Slave transmitted Data.\r\n\r\n");
        error_print();
        return err;
    }

    /* Check whether Master transmitted data is equal to Slave received data */
    if(BUFF_EQUAL == memcmp(g_master_tx_buff, g_slave_rx_buff, num_bytes_master))
    {
        /* Display Slave's received data on Terminal Emulator */
        APP_PRINT("Slave received data: %s\r\n\r\n", (char *)g_slave_rx_buff);
    }
    else
    {
        /* Return Parity error in case of data mismatch */
        err = FSP_ERR_SPI_PARITY;
        APP_ERR_PRINT("Slave received data does not match with Master transmitted Data.\r\n\r\n");
        error_print();
        return err;
    }

    /* Delay of one second for user to verify the output */
    R_BSP_SoftwareDelay(DELAY_ONE_SEC, BSP_DELAY_UNITS_SECONDS);
    return FSP_SUCCESS;
}

/*******************************************************************************************************************//**
 * @brief This function close both SPI Master and Slave modules.
 * @param[IN]   None
 * @retval      FSP_SUCCESS                  SPI module closed successfully
 * @retval      Any Other Error code apart from FSP_SUCCES  Unsuccessful close
 **********************************************************************************************************************/
fsp_err_t spi_exit_demo(void)
{
    fsp_err_t err = FSP_SUCCESS;     // Error status

    /* Closing SPI Master module */
    err = R_RSPI_Close(&g_spi_master_ctrl);
    /* Error Handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Master R_RSPI_Close() failed\r\n");
        return err;
    }

    /* Closing SPI Slave module */
    err = R_RSPI_Close(&g_spi_slave_ctrl);
    /* Error Handle */
    if(FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("Slave R_RSPI_Close() failed\r\n");
    }
    return err;
}

/*******************************************************************************************************************//**
 * @brief Master SPI callback function.
 * @param[in]  p_args
 * @retval     None
 **********************************************************************************************************************/
void spi_master_callback(spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_master_event_flag = SPI_EVENT_TRANSFER_COMPLETE;
    }
    else
    {
        g_master_event_flag = SPI_EVENT_TRANSFER_ABORTED;
    }
}

/*******************************************************************************************************************//**
 * @brief Slave SPI callback function.
 * @param[in]  p_args
 * @retval     None
 **********************************************************************************************************************/
void spi_slave_callback(spi_callback_args_t * p_args)
{
    if (SPI_EVENT_TRANSFER_COMPLETE == p_args->event)
    {
        g_slave_event_flag = SPI_EVENT_TRANSFER_COMPLETE;
    }
    else
    {
        g_slave_event_flag = SPI_EVENT_TRANSFER_ABORTED;
    }
}

/*******************************************************************************************************************//**
 * @brief This function prints the error message.
 * @param[IN]   None
 * @retval      None
 **********************************************************************************************************************/
static void error_print(void)
{
    APP_PRINT("Error in configuration or connection.\r\n\r\n");
    APP_PRINT("Reset the MPU...\r\n\r\n");
}

/*******************************************************************************************************************//**
 * @brief This function closes all the opened SPI modules before the project ends up in an Error Trap.
 * @param[IN]   None
 * @retval      None
 **********************************************************************************************************************/
void spi_clean_up(void)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Close SPI module */
    err = R_RSPI_Close(&g_spi_master_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* SPI Close failure message */
        APP_ERR_PRINT("** R_RSPI_Close API for master failed **\r\n");
    }

    err = R_RSPI_Close(&g_spi_slave_ctrl);
    /* handle error */
    if (FSP_SUCCESS != err)
    {
        /* SPI Close failure message */
        APP_ERR_PRINT("** R_RSPI_Close API for slave failed **\r\n");
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup spi_ep)
 **********************************************************************************************************************/
