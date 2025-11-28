/***********************************************************************************************************************
 * File Name    : mtu3_timer.h
 * Description  : Contains Macros and function declarations.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef MTU3_TIMER_H_
#define MTU3_TIMER_H_

/* Macros definitions */
#define MTU3_MAX_PERCENT          (100U)          /* Max Duty Cycle percentage */
#define BUF_SIZE                  (16U)           /* Size of buffer for input data */
#define PERIODIC_MODE_TIMER       (1U)            /* To perform MTU3 Timer in Periodic mode */
#define PWM_MODE_TIMER            (2U)            /* To perform MTU3 Timer in PWM mode */
#define ONE_SHOT_MODE_TIMER       (3U)            /* To perform MTU3 Timer in ONE-SHOT mode */
#define INITIAL_VALUE             ('\0')
#define TIMER_UNITS_MILLISECONDS  (1000U)         /* timer unit in millisecond */
#define CLOCK_TYPE_SPECIFIER      (1ULL)          /* type specifier */

#define MTU3_MAX_PERIOD_COUNT     (0XFFFF)        /* Max Period Count for 16-bit Timer */

#define MTU3_CH1_DIV_1024         (10U)           /* P0CLK divided by 1024 (ch1) */

#define PERIODIC_MODE	   (1U)                   /* To check status of MTU3 Timer in Periodic mode */
#define PWM_MODE	       (2U)                   /* To check status of MTU3 Timer in PWM mode */
#define ONE_SHOT_MODE      (3U)                   /* To check status of MTU3 Timer in ONE-SHOT mode */

#define EP_INFO    "The project initializes MTU3 module in Periodic, PWM or One-shot\r\n"\
		"mode based on user input from the displayed menu options.\r\n\r\n"\
		"In periodic mode, user can enter the time period within the\r\n"\
		"permitted ranges to change the frequency of the user LED.\r\n\r\n"\
		"In PWM mode, user can enter the duty cycle within the specified\r\n"\
		"range to adjust the intensity of the user LED.\r\n\r\n"\
		"In ONE SHOT mode, Output will be displayed on terminal application\r\n"\
		"when timer expires.\r\n\r\n"

/* Function declaration */
fsp_err_t init_mtu3_timer(timer_ctrl_t * const p_timer_ctl, timer_cfg_t const * const p_timer_cfg, uint8_t timer_mode);
fsp_err_t start_mtu3_timer (timer_ctrl_t * const p_timer_ctl);
fsp_err_t set_timer_duty_cycle(uint8_t duty_cycle_percent);
uint32_t  process_input_data(void);
void deinit_mtu3_timer(timer_ctrl_t * const p_timer_ctl);
void print_timer_menu(void);

#endif /* MTU3_TIMER_H_ */