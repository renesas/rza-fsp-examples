/***********************************************************************************************************************
 * File Name    : timer_initialise.h
 * Description  : Contains data structures and functions used in timer_initialise.c
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef TIMER_INITIALISE_H_
#define TIMER_INITIALISE_H_

/* MTU3 timer initialization function */
fsp_err_t mtu3_timer_init(void);

/* MTU3 timer deinitialisation function */
void mtu3_timer_deinit(void);

/* GTM timer initialization function */
fsp_err_t gtm_timer_init(void);

/* GTM timer deinitialisation function */
void gtm_timer_deinit(void);

#endif