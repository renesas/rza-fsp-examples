/***********************************************************************************************************************
 * File Name    : common_init.h
 * Description  : Common init functions.
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

#include "hal_data.h"

#define BLINK_FREQ_1HZ              (49999999)
#define BLINK_FREQ_5HZ              (9999999)
#define BLINK_FREQ_10HZ             (4999999)

#define KIT_INFO                    ('1')
#define NEXT_STEPS                  ('2')
#define CARRIAGE_RETURN             ('\r')

#define NUM_STRING_DESCRIPTOR       (7U)

extern bsp_leds_t g_bsp_leds;

#define APP_PRINT(fn_, ...)      (printf((fn_), ##__VA_ARGS__))

#define APP_ERR_PRINT(fn_, ...)  if(LVL_ERR)\
        printf("\r[ERR] In Function: %s",(fn_),##__VA_ARGS__);

#define APP_ERR_TRAP(err)        if(err) {\
        printf("\r\nReturned Error Code: 0x%x  \r\n", err);\
        __asm__ volatile("brk 0x0\n");} /* trap upon the error  */

fsp_err_t common_init(void);
void turn_led_error (void);
