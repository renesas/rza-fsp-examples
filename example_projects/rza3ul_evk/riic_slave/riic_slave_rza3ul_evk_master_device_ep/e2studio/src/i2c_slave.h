/***********************************************************************************************************************
 * File Name    : i2c_slave.h
 * Description  : Contains data structures and functions used in i2c_slave.h
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef I2C_SLAVE_H_
#define I2C_SLAVE_H_

/* Enum to select LED that is to be made high */
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


#define EP_INFO    "This EP demonstrates RIIC slave operation using two I2C channels on 2 boards.\r\n" \
        "It performs Slave read and write operation continuously once initialization  \r\n" \
        "is successful. On successful I2C transaction(6 bytes), Data transceived is  \r\n"\
        "compared. Led blinks on data match else it is turned ON as sign of failure. \r\n" \
        "For both cases corresponding slave operation message is displayed on Terminal Emulator. \r\n"\
        "Any API/event failure message is also displayed.\n\n\n\n\r\n"

/*
 *  Global functions
 */
fsp_err_t init_i2c_driver(void);
fsp_err_t process_slave_writeread(void);
void deinit_i2c_driver(void);
extern void led_update(led_state_t led_state);

#endif /* I2C_SLAVE_H_ */
