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

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hal_data.h"
#include <unistd.h>
#include <stdio.h>
#include "da7212.h"
#include "da7212_data.h"
#include "common_utils.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

#define DEFAULT_GAIN_HEADPHONE_DB (-20) /* -57db -- +6db */

//#define DEBUG_A3M_DEV_BOARD
#define AUDIO_EVENT_FLAG_I2C_ABRT   (0x00000001UL)
#define AUDIO_EVENT_FLAG_I2C_RXCP   (0x00000002UL)
#define AUDIO_EVENT_FLAG_I2C_TXCP   (0x00000004UL)
#define AUDIO_EVENT_FLAG_I2C_ERR    (0x00000008UL)
#define AUDIO_EVENT_FLAG_I2C_MASK   (AUDIO_EVENT_FLAG_I2C_ABRT|AUDIO_EVENT_FLAG_I2C_RXCP|AUDIO_EVENT_FLAG_I2C_TXCP|AUDIO_EVENT_FLAG_I2C_ERR)
#define DA7212_I2C_WAIT             (500)

/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/
static void da7212_send_data(i2c_master_instance_t *p_i2c, uint8_t addr, uint8_t data);
static void da7212_setup_data( i2c_master_instance_t *p_i2c );
static void da7212_i2c_open(i2c_master_instance_t *p_i2c);
static void da7212_i2c_close(i2c_master_instance_t *p_i2c);
static fsp_err_t da7212_i2c_wait_cb(void);
static volatile i2c_master_event_t cb_event = I2C_MASTER_EVENT_ABORTED;

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/
static uint8_t da7212_reg_data;
static uint8_t calboffset_data = 0x01;

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 * da7212_init
 **********************************************************************************************************************/
void da7212_init( i2c_master_instance_t *p_i2c )
{
    /* open i2c */
    da7212_i2c_open(p_i2c);

    /* set initialize data */
    da7212_setup_data(p_i2c);

    /* close i2c */
    da7212_i2c_close(p_i2c);
}

static void da7212_setup_data( i2c_master_instance_t *p_i2c )
{
    /* Soft reset */
    da7212_reg_data = 0x00;
    da7212_reg_data = DA7212_SOFT_RESET_VAL;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_CIF_CTRL], da7212_reg_data);

    /* set DIG_ROUTING_DAI */
    da7212_reg_data = DA7212_DIG_ROUTING_DAI_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DIG_ROUTING_DAI_L_SRC_BIT | DA7212_DIG_ROUTING_DAI_R_SRC_BIT));
    da7212_reg_data |= (DA7212_DIG_ROUTING_DAI_R_SRC_ADC | DA7212_DIG_ROUTING_DAI_L_SRC_ADC);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DIG_ROUTING_DAI], da7212_reg_data);

    /* set sample rate */
    da7212_reg_data = DA7212_SR_INI_VAL;
    da7212_reg_data &= (uint8_t)(~DA7212_SR_BIT);
    da7212_reg_data |= DA7212_SR_48kHz;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_SR], da7212_reg_data);

    /* set PLL_CTRL */
    da7212_reg_data = DA7212_PLL_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_PLL_CTRL_INDIV_BIT));
    da7212_reg_data |= DA7212_PLL_CTRL_INDIV_20_40;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_PLL_CTRL], da7212_reg_data);

    /* set DAI_CLK_MODE */
    da7212_reg_data = DA7212_DAI_CLK_MODE_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAI_CLK_MODE_CLK_EN_BIT | DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_BIT));
    da7212_reg_data |= (DA7212_DAI_CLK_MODE_CLK_EN_ON | DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_32);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAI_CLK_MODE], da7212_reg_data);

    /* set DAI_CTRL */
    da7212_reg_data = DA7212_DAI_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAI_CTRL_EN_BIT | DA7212_DAI_CTRL_OE_BIT | DA7212_DAI_CTRL_WL_LEN_BIT));
    da7212_reg_data |= (DA7212_DAI_CTRL_EN_ON | DA7212_DAI_CTRL_OE_ON | DA7212_DAI_CTRL_WL_LEN_16);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAI_CTRL], da7212_reg_data);

    /* set DIG_ROUTING_DAC */
    da7212_reg_data = DA7212_DIG_ROUTING_DAC_INI_VAL;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DIG_ROUTING_DAC], da7212_reg_data);

    /* set DAC_L_GAIN */
    da7212_reg_data = DA7212_DAC_L_GAIN_INI_VAL;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAC_L_GAIN], da7212_reg_data);

    /* set DAC_R_GAIN */
    da7212_reg_data = DA7212_DAC_R_GAIN_INI_VAL;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAC_R_GAIN], da7212_reg_data);

    /* set HP_L_GAIN */
    da7212_reg_data = DA7212_HP_L_GAIN_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_L_GAIN_BIT));
    da7212_reg_data |= da7212_hp_lr_gain_db(DEFAULT_GAIN_HEADPHONE_DB);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_HP_L_GAIN], da7212_reg_data);

    /* set HP_R_GAIN */
    da7212_reg_data = DA7212_HP_R_GAIN_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_R_GAIN_BIT));
    da7212_reg_data |= da7212_hp_lr_gain_db(DEFAULT_GAIN_HEADPHONE_DB);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_HP_R_GAIN], da7212_reg_data);

    /* set MIXOUT_L_SELECT */
    da7212_reg_data = DA7212_MIXOUT_L_SELECT_INI_VAL;
    da7212_reg_data |= DA7212_MIXOUT_L_SELECT_DAC_L_ON;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIXOUT_L_SELECT], da7212_reg_data);

    /* set MIXOUT_R_SELECT */
    da7212_reg_data = DA7212_MIXOUT_R_SELECT_INI_VAL;
    da7212_reg_data |= DA7212_MIXOUT_R_SELECT_DAC_R_ON;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIXOUT_R_SELECT], da7212_reg_data);

    /* set SYSTEM_MODES_OUTPUT */
    da7212_reg_data = DA7212_SYSTEM_MODES_OUTPUT_INI_VAL;

    da7212_reg_data |= (DA7212_SYSTEM_MODES_OUTPUT_DAC_R_ON | DA7212_SYSTEM_MODES_OUTPUT_DAC_L_ON | DA7212_SYSTEM_MODES_OUTPUT_HP_R_ON
                      | DA7212_SYSTEM_MODES_OUTPUT_HP_L_ON | DA7212_SYSTEM_MODES_OUTPUT_LINE_ON | DA7212_SYSTEM_MODES_OUTPUT_MD_SUB_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_SYSTEM_MODES_OUTPUT], da7212_reg_data);

    /* set DAC_L_CTRL */
    da7212_reg_data = DA7212_DAC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAC_L_CTRL_EN_BIT | DA7212_DAC_L_CTRL_MUTE_BIT | DA7212_DAC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_DAC_L_CTRL_EN_ON | DA7212_DAC_L_CTRL_MUTE_OFF | DA7212_DAC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAC_L_CTRL], da7212_reg_data);

    /* set DAC_R_CTRL */
    da7212_reg_data = DA7212_DAC_R_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAC_R_CTRL_EN_BIT | DA7212_DAC_R_CTRL_MUTE_BIT | DA7212_DAC_R_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_DAC_R_CTRL_EN_ON | DA7212_DAC_R_CTRL_MUTE_OFF | DA7212_DAC_R_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_DAC_R_CTRL], da7212_reg_data);

    /* set CP_CTRL */
    da7212_reg_data = DA7212_CP_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_CP_CTRL_EN_BIT));
    da7212_reg_data |= (DA7212_CP_CTRL_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_CP_CTRL], da7212_reg_data);

    /* set HP_L_CTRL */
    da7212_reg_data = DA7212_HP_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_L_CTRL_AMP_EN_BIT | DA7212_HP_L_CTRL_AMP_MUTE_BIT | DA7212_HP_L_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_HP_L_CTRL_AMP_AMP_OE_BIT ));
    da7212_reg_data |= (DA7212_HP_L_CTRL_AMP_EN_ON | DA7212_HP_L_CTRL_AMP_MUTE_OFF | DA7212_HP_L_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_HP_L_CTRL], da7212_reg_data);

    /* set HP_R_CTRL */
    da7212_reg_data = DA7212_HP_R_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_R_CTRL_AMP_EN_BIT | DA7212_HP_R_CTRL_AMP_MUTE_BIT | DA7212_HP_R_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_HP_R_CTRL_AMP_AMP_OE_BIT ));
    da7212_reg_data |= (DA7212_HP_R_CTRL_AMP_EN_ON | DA7212_HP_R_CTRL_AMP_MUTE_OFF | DA7212_HP_R_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_HP_R_CTRL], da7212_reg_data);

    /* set LINE_CTRL */
    da7212_reg_data = DA7212_LINE_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_LINE_CTRL_AMP_EN_BIT | DA7212_LINE_CTRL_AMP_MUTE_BIT | DA7212_LINE_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_LINE_CTRL_AMP_AMP_OE_BIT | DA7212_LINE_CTRL_AMP_MIN_GAIN_EN_BIT ));
    da7212_reg_data |= (DA7212_LINE_CTRL_AMP_EN_ON | DA7212_LINE_CTRL_AMP_MUTE_OFF | DA7212_LINE_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_LINE_CTRL], da7212_reg_data);


    /* set IO_CTRL */
    da7212_reg_data = DA7212_TONE_GEN_CYCLES_INI_VAL;
    da7212_reg_data |= DA7212_IO_CTRL_IO_VOL_LVL_HIGH;
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_IO_CTRL], da7212_reg_data);

    //Input set up
    // set REFERENCES
    da7212_reg_data = DA7212_REFERENCES_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_REFERENCES_BIAS_EN_BIT));
    da7212_reg_data |= (DA7212_REFERENCES_BIAS_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_REFERENCES], da7212_reg_data);

    // set MICBIAS_CTRL
    da7212_reg_data = DA7212_MICBIAS_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MICBIAS_CTRL_MICBIAS1_EN_BIT));
    da7212_reg_data |= (DA7212_MICBIAS_CTRL_MICBIAS1_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MICBIAS_CTRL], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_ON | DA7212_MIC_1_CTRL_AMP_MUTE_EN_OFF | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_OFF | DA7212_MIC_1_CTRL_AMP_MUTE_EN_ON | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);

    // set MIXIN_L_CTRL
    da7212_reg_data = DA7212_MIXIN_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIXIN_L_CTRL_AMP_EN_BIT | DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_BIT | DA7212_MIXIN_L_CTRL_AMP_RMP_EN_BIT | DA7212_MIXIN_L_CTRL_MIX_EN_BIT));
    da7212_reg_data |= (DA7212_MIXIN_L_CTRL_AMP_EN_ON | DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_OFF | DA7212_MIXIN_L_CTRL_AMP_RMP_EN_ON | DA7212_MIXIN_L_CTRL_MIX_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIXIN_L_CTRL], da7212_reg_data);

    // set MIXIN_L_SELECT
    da7212_reg_data = DA7212_MIXIN_L_SELECT_INI_VAL;
    da7212_reg_data |= (DA7212_MIXIN_L_SELECT_MIC1_SEL_MIX);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIXIN_L_SELECT], da7212_reg_data);

    // set ADC_L_CTRL
    da7212_reg_data = DA7212_ADC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_L_CTRL_EN_BIT | DA7212_ADC_L_CTRL_MUTE_BIT | DA7212_ADC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_L_CTRL_EN_ON | DA7212_ADC_L_CTRL_MUTE_ON | DA7212_ADC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_ADC_L_CTRL], da7212_reg_data);

    // set ALC_CTRL1
    da7212_reg_data = DA7212_ALC_CTRL1_INI_VAL;
    da7212_reg_data |= (DA7212_ALC_CTRL1_AUTO_CALIB_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_ALC_CTRL1], da7212_reg_data);

    while(calboffset_data)
    {
        uint8_t send_data[1];
        fsp_err_t err;

        send_data[0] = da7212_reg_addr[DA7212_REG_ALC_CTRL1];

        // Access register
        err = p_i2c->p_api->write(p_i2c->p_ctrl, send_data, sizeof(send_data), true);
        if(FSP_SUCCESS != err)
        {
            printf("[DA7212] I2C write failed.(%d)\r\n", err);
        }

        err = da7212_i2c_wait_cb();
        if(FSP_SUCCESS != err)
        {
            printf("da7212_i2c_wait_cb failed (%d)\r\n", err);
        }

        // Read data
        err = p_i2c->p_api->read(p_i2c->p_ctrl, &calboffset_data, sizeof(calboffset_data), false);
        if(FSP_SUCCESS != err)
        {
            printf("[DA7212] I2C read failed.(%d)\r\n", err);
        }
        err = da7212_i2c_wait_cb();
        if(FSP_SUCCESS != err)
        {
            printf("da7212_i2c_wait_cb failed (%d)\r\n", err);
        }

    }
    // set ALC_CTRL1
    da7212_reg_data = DA7212_ALC_CTRL1_INI_VAL;
    da7212_reg_data |= (DA7212_ALC_CTRL1_R_EN_ON | DA7212_ALC_CTRL1_L_EN_ON | DA7212_ALC_CTRL1_SYNC_MODE_ON | DA7212_ALC_CTRL1_OFST_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_ALC_CTRL1], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_ON | DA7212_MIC_1_CTRL_AMP_MUTE_EN_OFF | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);
    // set ADC_L_CTRL
    da7212_reg_data = DA7212_ADC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_L_CTRL_EN_BIT | DA7212_ADC_L_CTRL_MUTE_BIT | DA7212_ADC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_L_CTRL_EN_ON | DA7212_ADC_L_CTRL_MUTE_OFF | DA7212_ADC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_ADC_L_CTRL], da7212_reg_data);

    // set SYSTEM_MODES_INPUT
    da7212_reg_data = DA7212_SYSTEM_MODES_INPUT_INI_VAL;
    da7212_reg_data |= ( DA7212_SYSTEM_MODES_INPUT_MIXIN_L_ON | DA7212_SYSTEM_MODES_INPUT_MIC_1_ON | DA7212_SYSTEM_MODES_INPUT_ADC_L_ON
                       | DA7212_SYSTEM_MODES_INPUT_MD_SUB_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_SYSTEM_MODES_INPUT], da7212_reg_data);

    // set ADC_FILTERS1
    da7212_reg_data = DA7212_ADC_FILTERS1_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_FILTERS1_HPF_EN_BIT | DA7212_ADC_FILTERS1_VC_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_FILTERS1_HPF_EN_OFF | DA7212_ADC_FILTERS1_VC_EN_ON);
    da7212_send_data(p_i2c, da7212_reg_addr[DA7212_REG_ADC_FILTERS1], da7212_reg_data);

}

static void da7212_send_data(i2c_master_instance_t *p_i2c, uint8_t addr, uint8_t data)
{
    uint8_t send_data[2];
    fsp_err_t err;

    send_data[0] = addr;
    send_data[1] = data;
    err = p_i2c->p_api->write(p_i2c->p_ctrl, send_data, sizeof(send_data), false);
    if(FSP_SUCCESS != err)
    {
        printf("[DA7212] I2C write failed.(%d)\r\n", err);
    }

    err = da7212_i2c_wait_cb();
    if (FSP_SUCCESS != err)
    {
        printf("da7212_i2c_wait_cb failed (%d)\r\n", err);
    }
}
void da7212_i2c_callback( i2c_master_callback_args_t *p_arg )
{
    if (NULL != p_arg)
    {
        /* capture callback event for validating the i2c transfer event*/
        cb_event = p_arg->event;
    }
}

static void da7212_i2c_open(i2c_master_instance_t *p_i2c)
{
    fsp_err_t err;

    /* open i2c */
    err = p_i2c->p_api->open(p_i2c->p_ctrl, p_i2c->p_cfg);
    if( FSP_SUCCESS != err )
    {
        printf("[DA7212] I2C open failed.(%d)\r\n", err);
        return;
    }
}

static void da7212_i2c_close(i2c_master_instance_t *p_i2c)
{
    fsp_err_t err;

    /* close i2c */
    err = p_i2c->p_api->close(p_i2c->p_ctrl);
    if(FSP_SUCCESS != err)
    {
        printf("[DA7212] I2C close failed.(%d)\r\n", err);
    }
}
static fsp_err_t da7212_i2c_wait_cb( void )
{
      uint32_t local_time_out = UINT32_MAX;

        /* resetting call back event capture variable */
      cb_event = (i2c_master_event_t)RESET_VALUE;

        do
        {
            /* This is to avoid infinite  loop */
            --local_time_out;

            if(0 == local_time_out)
            {
                return FSP_ERR_TRANSFER_ABORTED;
            }

        }while(cb_event == 0);

        if(cb_event != I2C_MASTER_EVENT_ABORTED)
        {
            cb_event = (i2c_master_event_t)RESET_VALUE;  // Make sure this is always Reset before return
            return FSP_SUCCESS;
        }

        cb_event = (i2c_master_event_t)RESET_VALUE; // Make sure this is always Reset before return
        return FSP_ERR_TRANSFER_ABORTED;
    }
