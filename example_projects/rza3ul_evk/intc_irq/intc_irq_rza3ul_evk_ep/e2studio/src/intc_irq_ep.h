/***********************************************************************************************************************
 * File Name    : intc_irq_ep.h
 * Description  : Contains Macros and function declarations.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef INTC_IRQ_EP_H_
#define INTC_IRQ_EP_H_

/* External IRQ channel*/
#define USER_SW_IRQ_NUMBER        (0x02)        /* Channel 2 */
#define EP_INFO    "This Example Project demonstrates the functionality of INTC_IRQ \r\n" \
                   "driver. On pressing the user push button, an external IRQ is \r\n" \
                   "triggered, which toggles Pmod LED. \r\n\r\n"

/* Function declaration */
fsp_err_t intc_irq_init(void);
fsp_err_t intc_irq_enable(void);
void intc_irq_deinit(void);

#endif /* INTC_IRQ_EP_H_ */