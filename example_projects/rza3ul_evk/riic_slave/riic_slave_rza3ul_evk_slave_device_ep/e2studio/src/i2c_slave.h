/***********************************************************************************************************************
 * File Name    : i2c_slave.h
 * Description  : Contains data structures and functions used in i2c_slave.h
 **********************************************************************************************************************/
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

#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

/* Enum to select LD that is to be made high */
typedef enum
{
   led_error = 1,
   successful = 2,
   transmitting = 3,
} led_state_t;

/* MACRO for checking if two buffers are equal */
#define BUFF_EQUAL         (0U)

/* buffer size for slave and master data */
#define BUF_LEN            (0x06)

/* Wait time value */
#define WAIT_TIME          (500U)

/* DELAY 1S */
#define DELAY_1S       (0x3E8)


#define EP_INFO    "This EP demonstrates IIC slave operation using two I2C channels on 2 boards.\r\n" \
        "It performs Slave read and write operation continuously once initialization  \r\n" \
        "is successful. On successful I2C transaction(6 bytes), Data transceived is  \r\n"\
        "compared. Led blinks on data match else it is turned ON as sign of failure. \r\n" \
        "For both cases corresponding slave operation message is displayed on Terminal Emulator. \r\n"\
        "Any API/event failure message is also displayed.\n\n\n\n\r\n"

/*
 *  Global functions
 */
fsp_err_t init_i2C_driver(void);
fsp_err_t process_slave_WriteRead(void);
void deinit_i2c_driver(void);


#endif /* I2C_SLAVE_H_ */
