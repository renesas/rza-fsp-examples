/***********************************************************************************************************************
 * File Name    : mtu3_timer.c
 * Description  : Contains function definition.
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

#include "common_utils.h"
#include "mtu3_timer.h"

/*******************************************************************************************************************//**
 * @addtogroup r_mtu3_ep
 * @{
 **********************************************************************************************************************/

/* Boolean flag to determine one-shot mode timer is expired or not.*/
bool volatile g_one_shot_expired  = false;
/* Store Timer open state*/
uint8_t g_timer_open_state        = RESET_VALUE;
/* Boolean flag to set the duty cycle to 0% .*/
bool volatile g_set_duty_cycle_0  = false;

uint32_t g_current_period_counts  = RESET_VALUE;

/*****************************************************************************************************************
 * @brief       Initialize MTU3 timer.
 * @param[in]   p_timer_ctl     Timer instance control structure
 * @param[in]   p_timer_cfg     Timer instance Configuration structure
 * @param[in]   timer_mode      Mode of MTU3 Timer
 * @retval      FSP_SUCCESS     Upon successful open of timer.
 * @retval      Any Other Error code apart from FSP_SUCCES on Unsuccessful open .
 ****************************************************************************************************************/
fsp_err_t init_mtu3_timer(timer_ctrl_t * const p_timer_ctl, timer_cfg_t const * const p_timer_cfg, uint8_t timer_mode)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Initialize MTU3 Timer */
    err = R_MTU3_Open(p_timer_ctl, p_timer_cfg);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT ("** R_MTU3_Open FAILED ** \r\n\r\n");
        return err;
    }
    if(PERIODIC_MODE_TIMER == timer_mode)
    {
        g_timer_open_state = PERIODIC_MODE;
    }
    else if(PWM_MODE_TIMER == timer_mode)
    {
        g_timer_open_state = PWM_MODE;
    }
    else
    {
        g_timer_open_state = ONE_SHOT_MODE;
    }
    return err;
}

/*****************************************************************************************************************
 * @brief       Start MTU3 timers in periodic, one shot, PWM mode.
 * @param[in]   p_timer_ctl     Timer instance control structure
 * @retval      FSP_SUCCESS     Upon successful start of timer.
 * @retval      Any Other Error code apart from FSP_SUCCES on Unsuccessful start .
 ****************************************************************************************************************/
fsp_err_t start_mtu3_timer (timer_ctrl_t * const p_timer_ctl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Starts MTU3 timer */
    err = R_MTU3_Start(p_timer_ctl);
    if (FSP_SUCCESS != err)
    {
        /* In case of mtu3_open is successful and start fails, requires a immediate cleanup.
         * Since, cleanup for MTU3 open is done in start_mtu3_timer,Hence cleanup is not required */
        APP_ERR_PRINT ("** R_MTU3_Start API failed ** \r\n\r\n");
    }
    return err;
}

/*****************************************************************************************************************
 *  @brief       set  duty cycle of PWM timer.
 *  @param[in]   duty_cycle_percent.
 *  @retval      FSP_SUCCESS on correct duty cycle set.
 *  @retval      FSP_INVALID_ARGUMENT on invalid info.
 ****************************************************************************************************************/
fsp_err_t set_timer_duty_cycle(uint8_t duty_cycle_percent)
{
    fsp_err_t err                           = FSP_SUCCESS;
    uint32_t duty_cycle_counts              = RESET_VALUE;
    timer_info_t info                       = {(timer_direction_t)RESET_VALUE, RESET_VALUE, RESET_VALUE};

    /* Get the current period setting. */
    err = R_MTU3_InfoGet(&g_timer_pwm_ctrl, &info);
    if (FSP_SUCCESS != err)
    {
        /* MTU3 Timer InfoGet Failure message */
        APP_ERR_PRINT ("** R_MTU3_InfoGet API failed ** \r\n\r\n");
    }
    else
    {
        /* update period counts locally. */
        g_current_period_counts = info.period_counts;

        /* Calculate the desired duty cycle based on the current period. Note that if the period could be larger than
         * UINT32_MAX / 100, this calculation could overflow. */
        if (100UL == duty_cycle_percent)
        {
            duty_cycle_counts = g_current_period_counts + 2UL;
        }
        else if (0UL == duty_cycle_percent)
        {
            duty_cycle_counts  = 1UL;
            g_set_duty_cycle_0 = true;
        }
        else
        {
            duty_cycle_counts =(uint32_t) ((g_current_period_counts * duty_cycle_percent) / MTU3_MAX_PERCENT);
        }

        /* Duty Cycle Set API set the desired intensity on the PMOD LED */
        err = R_MTU3_DutyCycleSet(&g_timer_pwm_ctrl, duty_cycle_counts, 0);
        if(FSP_SUCCESS != err)
        {
            /* MTU3 Timer DutyCycleSet Failure message */
            /* In case of MTU3_open is successful and DutyCycleSet fails, requires a immediate cleanup.
             * Since, cleanup for MTU3 open is done in timer_duty_cycle_set,Hence cleanup is not required */
            APP_ERR_PRINT ("** R_MTU3_DutyCycleSet API failed ** \r\n\r\n");
        }
    }
    return err;
}

/*****************************************************************************************************************
 *  @brief      Process input string to integer value
 *  @param[in]  None
 *  @retval     integer value of input string.
 ****************************************************************************************************************/
uint32_t process_input_data(void)
{
    unsigned char buf[BUF_SIZE] = {INITIAL_VALUE};
    uint32_t num_bytes          = RESET_VALUE;
    uint32_t value              = RESET_VALUE;

    while (RESET_VALUE == num_bytes)
    {
        if (APP_CHECK_DATA)
        {
            APP_READ(buf);
            num_bytes =  (uint32_t)strlen((char *)buf);
            if (RESET_VALUE == num_bytes)
            {
                APP_PRINT("Invalid Input\r\n");
            }
        }
    }

    /* Conversion from input string to integer value */
    value =  (uint32_t) (atoi((char *)buf));

    return value;
}

/*****************************************************************************************************************
 * @brief      Close the MTU3 HAL driver.
 * @param[in]  p_timer_ctl     Timer instance control structure
 * @retval     None
 ****************************************************************************************************************/
void deinit_mtu3_timer(timer_ctrl_t * const p_timer_ctl)
{
    fsp_err_t err = FSP_SUCCESS;

    /* Timer Close API call*/
    err = R_MTU3_Close(p_timer_ctl);
    if (FSP_SUCCESS != err)
    {
        /* MTU3 Close failure message */
        APP_ERR_PRINT ("** R_MTU3_Close FAILED ** \r\n\r\n");
    }

    /* Reset open state of timer*/
    g_timer_open_state = RESET_VALUE;
}

/*****************************************************************************************************************
 * @brief      Print MTU3 Timer menu option.
 * @param[in]  None
 * @retval     None
 ****************************************************************************************************************/
void print_timer_menu(void)
{
    APP_PRINT ("Menu Options\r\n");
    APP_PRINT ("1. Enter 1 for Periodic mode\r\n");
    APP_PRINT ("2. Enter 2 for PWM mode\r\n");
    APP_PRINT ("3. Enter 3 for one shot mode\r\n");
    APP_PRINT ("User Input:  \r\n\r\n");
}

/*****************************************************************************************************************
 *  @brief      User defined MTU3 callback in one-shot mode
 *  @param[in]  p_args  updates timer event.
 *  @retval     None
 ****************************************************************************************************************/
void user_mtu3_one_shot_callback(timer_callback_args_t * p_args)
{
    if(NULL != p_args)
    {
        if (TIMER_EVENT_COMPARE_A  == p_args->event)
        {
            /* Set boolean flag on one-shot mode timer expired. */
            g_one_shot_expired = true;
        }
    }
}

/*****************************************************************************************************************
 *  @brief      User defined MTU3 callback to set the value of TGRB register to 0.
 *  @param[in]  p_args  updates timer event.
 *  @retval     None
 ****************************************************************************************************************/
void user_mtu3_capture_b_callback(timer_callback_args_t * p_args)
{
    if(NULL != p_args)
    {
        if (TIMER_EVENT_COMPARE_B  == p_args->event)
        {
            if (true == g_set_duty_cycle_0)
            {
                /* Set the value of TGRB register to 0. */
                R_MTU3_DutyCycleSet(&g_timer_pwm_ctrl, g_current_period_counts + 1UL, 0UL);

                /* Reset the flag */
                g_set_duty_cycle_0 = false;
            }
        }
    }
}

/*******************************************************************************************************************//**
 * @} (end addtogroup r_mtu3_ep)
 **********************************************************************************************************************/