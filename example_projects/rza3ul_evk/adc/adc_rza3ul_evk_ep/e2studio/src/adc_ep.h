/***********************************************************************************************************************
 * File Name    : adc_ep.h
 * Description  : Contains data structures and functions used in adc_ep.c/.h.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * Copyright [2022] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#ifndef ADC_EP_H_
#define ADC_EP_H_

/*******************************************************************************************************************//**
 * @ingroup adc_ep
 * @{
 **********************************************************************************************************************/

/* Macros for Commands to be received through RTT inputs */
#define SCAN_START       (0x01)
#define SCAN_STOP        (0x02)

/* Macro for default buff size for reading through RTT */
#define BUFF_SIZE         (0x0F)

/* Macros for checking the deviation in adc values */
#define TEMPERATURE_DEVIATION_LIMIT       (0x04)

/* Macro for indexing buffer. used to read the bytes received from RTT input */
#define BUFF_INDEX       (0x00)

/* Macro to provide delay in read adc data*/
#define ADC_READ_DELAY        (0x01)

/* Macro to set value to output voltage control*/
#define VREFADCG_VALUE    (0x03)

/* Macro to set value to enable VREFADC output*/
#define VREFADCG_ENABLE   (0x03)

#define SHIFT_BY_ONE     (0x01)
#define SHIFT_BY_THREE   (0x03)

/* Macros for menu options to be displayed */
#define MENUOPTION1       "\r\nMENU to Select\r\n"
#define MENUOPTION2       "Press 1 to Start ADC Scan\r\n"
#define MENUOPTION3       "Press 2 to Stop ADC Scan(Only for Repeat mode)\r\n"
#define MENUOPTION4       "User Input :"


#define BANNER_7          "\r\nThe project initializes the ADC in single scan or repeat scan mode \
                           \r\nbased on user selection in RZ/A3UL configuration. Once initialized, user can start \
                           \r\nthe ADC scan and also stop the scan (in the case of repeat scan mode)\
                           \r\nusing Tera Term by sending commands. Results are also displayed on Tera Term.\r\n"

/* Reading the commands from RTT input and process it*/
fsp_err_t read_process_input_from_TeraTerm(void);

/* Read the adc data available */
fsp_err_t adc_read_data(void);

/* close the open adc module  */
void deinit_adc_module(void);

/** @} */
#endif /* ADC_EP_H_ */
