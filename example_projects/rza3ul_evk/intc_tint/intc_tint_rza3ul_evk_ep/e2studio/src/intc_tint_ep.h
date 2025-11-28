/***********************************************************************************************************************
 * File Name    : intc_tint_ep.h
 * Description  : Contains Macros and function declarations.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef INTC_TINT_EP_H_
#define INTC_TINT_EP_H_

/* TINT channel */
#define USER_SW_TINT_NUMBER        (0x18)        /* Channel 24 */
#define EP_INFO    "This Example Project demonstrates the functionality of INTC_TINT driver.\r\n" \
    "On pressing the user push button, an external IRQ is triggered, which toggles PMOD LED.\r\n\r\n"

/* Function declaration */
fsp_err_t intc_tint_init(void);
fsp_err_t intc_tint_enable(void);
void intc_tint_deinit(void);

#endif /* INTC_TINT_EP_H_ */