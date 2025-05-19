/***********************************************************************************************************************
 * File Name    : common_init.c
 * Description  : Common init function.
 **********************************************************************************************************************/
/*
 * Copyright [2020-2025] Renesas Electronics Corporation and/or its affiliates.  All Rights Reserved.
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
 */

#include "common_init.h"
#include "board_cfg.h"
#include "stdbool.h"

#define NUM_RATES             (sizeof(blink_rates) / sizeof(blink_rates[0]))

int g_curr_led_freq = BLINK_FREQ_1HZ;
static uint32_t cur_rate = 0;

int curr_led_freq = 0;

uint32_t blink_rates[3] = {BLINK_FREQ_1HZ, BLINK_FREQ_5HZ, BLINK_FREQ_10HZ};


void button_irq_callback(external_irq_callback_args_t *p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);

    if(++cur_rate > (NUM_RATES - 1))
        cur_rate = 0;

    R_GTM_PeriodSet(g_blinker.p_ctrl, blink_rates[cur_rate]);

    g_curr_led_freq = (int)blink_rates[cur_rate];
}


static fsp_err_t IRQ_Initialize(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = R_INTC_IRQ_ExternalIrqOpen(g_external_irq.p_ctrl, g_external_irq.p_cfg);
    if(FSP_SUCCESS != fsp_err)
        return fsp_err;

    fsp_err = R_INTC_IRQ_ExternalIrqEnable(g_external_irq.p_ctrl);
    if(FSP_SUCCESS != fsp_err)
        return fsp_err;

    return fsp_err;
}


void periodic_timer_callback(timer_callback_args_t *p_args)
{

    /* Holds level to set for pins */
     static bsp_io_level_t pin_level = BSP_IO_LEVEL_LOW;

     if(TIMER_EVENT_CYCLE_END == p_args->event)
     {
         /* Update all board LEDs */
         for (uint32_t i = 0; i < g_bsp_leds.led_count; i++)
         {
             /* Get pin to toggle */
             uint32_t pin = g_bsp_leds.p_leds[i];

             /* Write to this pin */
             R_BSP_PinWrite((bsp_io_port_pin_t) pin, pin_level);
         }
     }
     /* Toggle level for next write */
     if (BSP_IO_LEVEL_LOW == pin_level)
     {
         pin_level = BSP_IO_LEVEL_HIGH;
     }
     else
     {
         pin_level = BSP_IO_LEVEL_LOW;
     }
}


static fsp_err_t GTM_Initialize(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = R_GTM_Open(g_blinker.p_ctrl, g_blinker.p_cfg);
    {
        if(FSP_SUCCESS != fsp_err)
            return fsp_err;
    }
    fsp_err = R_GTM_PeriodSet(g_blinker.p_ctrl, blink_rates[cur_rate]);
    {
        if(FSP_SUCCESS != fsp_err)
            return fsp_err;
    }

    fsp_err = R_GTM_Start(g_blinker.p_ctrl);
    if(FSP_SUCCESS != fsp_err)
    {
        /* Turn on LED to indicate fatal error */
        turn_led_error();

        /* Close the GTM timer */
        R_GTM_Close(g_blinker.p_ctrl);

        return fsp_err;
    }

    return fsp_err;
}

fsp_err_t common_init(void)
{
    fsp_err_t fsp_err = FSP_SUCCESS;

    fsp_err = GTM_Initialize();
    if(FSP_SUCCESS != fsp_err)
        return fsp_err;

    fsp_err = IRQ_Initialize();
    if(FSP_SUCCESS != fsp_err)
        return fsp_err;

    if(FSP_SUCCESS != fsp_err)
        return fsp_err;

    return fsp_err;
}

void turn_led_error (void)
{
    R_IOPORT_PinWrite(&g_ioport_ctrl, g_bsp_leds.p_leds[BSP_LED_LED1], BSP_IO_LEVEL_HIGH);
    R_IOPORT_PinWrite(&g_ioport_ctrl, g_bsp_leds.p_leds[BSP_LED_LED2], BSP_IO_LEVEL_LOW);
    R_IOPORT_PinWrite(&g_ioport_ctrl, g_bsp_leds.p_leds[BSP_LED_LED3], BSP_IO_LEVEL_HIGH);
}
