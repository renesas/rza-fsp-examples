/***********************************************************************************************************************
 * File Name    : adc_ep.h
 * Description  : Contains data structures and functions used in adc_ep.c/.h.
 **********************************************************************************************************************/
/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#ifndef ADC_EP_H_
#define ADC_EP_H_

/*******************************************************************************************************************//**
 * @ingroup adc_ep
 * @{
 **********************************************************************************************************************/

/* Macros for Commands to be received through Terminal Emulator inputs */
#define SCAN_START       (0x01)
#define SCAN_STOP        (0x02)

/* Macro for default buff size for reading through Terminal Emulator */
#define BUFF_SIZE         (0x0F)

/* Macros for checking the deviation in adc values */
#define TEMPERATURE_DEVIATION_LIMIT       (0x04)

/* Macro for indexing buffer. used to read the bytes received from Terminal Emulator input */
#define BUFF_INDEX       (0x00)

/* Macro to provide delay in read adc data*/
#define ADC_READ_DELAY        (0x01)

/* Macro to set value to output voltage control*/
#define VREFADCG_VALUE    (0x03)

/* Macro to set value to enable VREFADC output*/
#define VREFADCG_ENABLE   (0x03)

#define SHIFT_BY_ONE     (0x01)
#define SHIFT_BY_THREE   (0x03)
#define BIT_SHIFT_8        (8u)
#define BIT_SHIFT_12      (12u)
#define BIT_SHIFT_15      (15u)
#define ADC_12_BIT      (4096u)
#define ADC_16_BIT     (32768u)
#define V_ref            (3.3f)
#define ADC_H_LMT       (3103u)
#define ADC_L_LMT       (1241u)

/* Macros for menu options to be displayed */
#define MENUOPTION1       "\r\nMENU to Select\r\n"
#define MENUOPTION2       "Press 1 to Start ADC Scan\r\n"
#define MENUOPTION3       "Press 2 to Stop ADC Scan(Only for Repeat mode)\r\n"
#define MENUOPTION4       "User Input :"

#define BANNER            "\r\nThe project initializes the ADC in single scan or repeat scan mode \
                           \r\nbased on user selection in RZ/A3UL configuration. Once initialized, user can start \
                           \r\nthe ADC scan and also stop the scan (in the case of repeat scan mode)\
                           \r\nusing Tera Term by sending commands. Results are also displayed on Tera Term.\r\n"

/* Reading the commands from Terminal Emulator input and process it*/
fsp_err_t read_process_input_from_teraterm(void);

/* Read the adc data available */
fsp_err_t adc_read_data(void);

/* close the open adc module  */
void deinit_adc_module(void);

/** @} */
#endif /* ADC_EP_H_ */