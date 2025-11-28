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


/* macro definition */
/* for on board LED */
#define LED_ON             (BSP_IO_LEVEL_HIGH)
#define LED_OFF            (BSP_IO_LEVEL_LOW)

/* MACRO for checking if two buffers are equal */
#define BUFF_EQUAL         (0U)

/* buffer size for slave and master data */
#define BUF_LEN            (0x06)

/* Human eye noticeable LED toggle delay */
#define TOGGLE_DELAY       (0x3E8)


#define EP_INFO    "This EP demonstrates RIIC slave operation using two I2C channels.\r\n" \
        "It performs Slave read and write operation continuously once initialization  \r\n" \
        "is successful. On successful I2C transaction(6 bytes), Data transceived is  \r\n"\
        "compared. Led blinks on data match else it is turned ON as sign of failure. \r\n" \
        "For both cases corresponding slave operation message is displayed on Terminal Emulator. \r\n"\
        "Any API/event failure message is also displayed.\r\n\r\n"

/*
 *  Global functions
 */
fsp_err_t init_i2c_driver(void);
fsp_err_t process_slave_writeread(void);
void deinit_i2c_driver(void);
void set_led(bsp_io_level_t led_state);


#endif /* I2C_SLAVE_H_ */
