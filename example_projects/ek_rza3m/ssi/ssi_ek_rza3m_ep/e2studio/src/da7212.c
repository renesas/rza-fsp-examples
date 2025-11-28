/*
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 * 
 * SPDX-License-Identifier: BSD-3-Clause
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
const uint8_t g_da7212_reg_addr[DA7212_REG_MAX]=
{
    0x02,   /* STATUS1 */
    0x03,   /* PLL_STATUS */
    0x04,   /* AUX_L_GAIN_STATUS */
    0x05,   /* AUX_R_GAIN_STATUS */
    0x06,   /* MIC_1_GAIN_STATUS */
    0x07,   /* MIC_2_GAIN_STATUS */
    0x08,   /* MIXIN_L_GAIN_STATUS */
    0x09,   /* MIXIN_R_GAIN_STATUS */
    0x0A,   /* ADC_L_GAIN_STATUS */
    0x0B,   /* ADC_R_GAIN_STATUS */
    0x0C,   /* DAC_L_GAIN_STATUS */
    0x0D,   /* DAC_R_GAIN_STATUS */
    0x0E,   /* HP_L_GAIN_STATUS */
    0x0F,   /* HP_R_GAIN_STATUS */
    0x10,   /* LINE_GAIN_STATUS */
    0x1D,   /* CIF_CTRL */
    0x21,   /* DIG_ROUTING_DAI */
    0x22,   /* SR */
    0x23,   /* REFERENCES */
    0x24,   /* PLL_FRAC_TOP */
    0x25,   /* PLL_FRAC_BOT */
    0x26,   /* PLL_INTEGER */
    0x27,   /* PLL_CTRL */
    0x28,   /* DAI_CLK_MODE */
    0x29,   /* DAI_CTRL */
    0x2A,   /* DIG_ROUTING_DAC */
    0x2B,   /* ALC_CTRL1 */
    0x30,   /* AUX_L_GAIN */
    0x31,   /* AUX_R_GAIN */
    0x32,   /* MIXIN_L_SELECT */
    0x33,   /* MIXIN_R_SELECT */
    0x34,   /* MIXIN_L_GAIN */
    0x35,   /* MIXIN_R_GAIN */
    0x36,   /* ADC_L_GAIN */
    0x37,   /* ADC_R_GAIN */
    0x38,   /* ADC_FILTERS1 */
    0x39,   /* MIC_1_GAIN */
    0x3A,   /* MIC_2_GAIN */
    0x40,   /* DAC_FILTERS5 */
    0x41,   /* DAC_FILTERS2 */
    0x42,   /* DAC_FILTERS3 */
    0x43,   /* DAC_FILTERS4 */
    0x44,   /* DAC_FILTERS1 */
    0x45,   /* DAC_L_GAIN */
    0x46,   /* DAC_R_GAIN */
    0x47,   /* CP_CTRL */
    0x48,   /* HP_L_GAIN */
    0x49,   /* HP_R_GAIN */
    0x4A,   /* LINE_GAIN */
    0x4B,   /* MIXOUT_L_SELECT */
    0x4C,   /* MIXOUT_R_SELECT */
    0x50,   /* SYSTEM_MODES_INPUT */
    0x51,   /* SYSTEM_MODES_OUTPUT */
    0x60,   /* AUX_L_CTRL */
    0x61,   /* AUX_R_CTRL */
    0x62,   /* MICBIAS_CTRL */
    0x63,   /* MIC_1_CTRL */
    0x64,   /* MIC_2_CTRL */
    0x65,   /* MIXIN_L_CTRL */
    0x66,   /* MIXIN_R_CTRL */
    0x67,   /* ADC_L_CTRL */
    0x68,   /* ADC_R_CTRL */
    0x69,   /* DAC_L_CTRL */
    0x6A,   /* DAC_R_CTRL */
    0x6B,   /* HP_L_CTRL */
    0x6C,   /* HP_R_CTRL */
    0x6D,   /* LINE_CTRL */
    0x6E,   /* MIXOUT_L_CTRL */
    0x6F,   /* MIXOUT_R_CTRL */
    0x84,   /* MIXED_SAMPLE_MODE */
    0x90,   /* LDO_CTRL */
    0x91,   /* IO_CTRL */
    0x92,   /* GAIN_RAMP_CTRL */
    0x93,   /* MIC_CONFIG */
    0x94,   /* PC_COUNT */
    0x95,   /* CP_VOL_THRESHOLD1 */
    0x96,   /* CP_DELAY */
    0x97,   /* CP_DETECTOR */
    0x98,   /* DAI_OFFSET */
    0x99,   /* DIG_CTRL */
    0x9A,   /* ALC_CTRL2 */
    0x9B,   /* ALC_CTRL3 */
    0x9C,   /* ALC_NOISE */
    0x9D,   /* ALC_TARGET_MIN */
    0x9E,   /* ALC_THRESHOLD_MAX */
    0x9F,   /* ALC_GAIN_LIMITS */
    0xA0,   /* ALC_ANA_GAIN_LIMITS */
    0xA1,   /* ALC_ANTICLIP_CTRL */
    0xA2,   /* ALC_ANTICLIP_LEVEL */
    0xA3,   /* ALC_OFFSET_AUTO_M_L */
    0xA4,   /* ALC_OFFSET_AUTO_U_L */
    0xA6,   /* ALC_OFFSET_MAN_M_L */
    0xA7,   /* ALC_OFFSET_MAN_U_L */
    0xA8,   /* ALC_OFFSET_AUTO_M_R */
    0xA9,   /* ALC_OFFSET_AUTO_U_R */
    0xAB,   /* ALC_OFFSET_MAN_M_R */
    0xAC,   /* ALC_OFFSET_MAN_U_R */
    0xAD,   /* ALC_CIC_OP_LVL_CTRL */
    0xAE,   /* ALC_CIC_OP_LVL_DATA */
    0xAF,   /* DAC_NG_SETUP_TIME */
    0xB0,   /* DAC_NG_OFF_THRESHOLD */
    0xB1,   /* DAC_NG_ON_THRESHOLD */
    0xB2,   /* DAC_NG_CTRL */
    0xB4,   /* TONE_GEN_CFG1 */
    0xB5,   /* TONE_GEN_CFG2 */
    0xB6,   /* TONE_GEN_CYCLES */
    0xB7,   /* TONE_GEN_FREQ1_L */
    0xB8,   /* TONE_GEN_FREQ1_U */
    0xB9,   /* TONE_GEN_FREQ2_L */
    0xBA,   /* TONE_GEN_FREQ2_U */
    0xBB,   /* TONE_GEN_ON_PER */
    0xBC,   /* TONE_GEN_OFF_PER */
    0xE0,   /* SYSTEM_STATUS */
    0xFD    /* SYSTEM_ACTIVE */
};


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
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_CIF_CTRL], da7212_reg_data);

    /* set DIG_ROUTING_DAI */
    da7212_reg_data = DA7212_DIG_ROUTING_DAI_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DIG_ROUTING_DAI_L_SRC_BIT | DA7212_DIG_ROUTING_DAI_R_SRC_BIT));
    da7212_reg_data |= (DA7212_DIG_ROUTING_DAI_R_SRC_ADC | DA7212_DIG_ROUTING_DAI_L_SRC_ADC);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DIG_ROUTING_DAI], da7212_reg_data);

    /* set sample rate */
    da7212_reg_data = DA7212_SR_INI_VAL;
    da7212_reg_data &= (uint8_t)(~DA7212_SR_BIT);
    da7212_reg_data |= DA7212_SR_48kHz;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_SR], da7212_reg_data);

    /* set PLL_CTRL */
    da7212_reg_data = DA7212_PLL_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_PLL_CTRL_INDIV_BIT));
    da7212_reg_data |= DA7212_PLL_CTRL_INDIV_20_40;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_PLL_CTRL], da7212_reg_data);

    /* set DAI_CLK_MODE */
    da7212_reg_data = DA7212_DAI_CLK_MODE_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAI_CLK_MODE_CLK_EN_BIT | DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_BIT));
    da7212_reg_data |= (DA7212_DAI_CLK_MODE_CLK_EN_ON | DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_32);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAI_CLK_MODE], da7212_reg_data);

    /* set DAI_CTRL */
    da7212_reg_data = DA7212_DAI_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAI_CTRL_EN_BIT | DA7212_DAI_CTRL_OE_BIT | DA7212_DAI_CTRL_WL_LEN_BIT));
    da7212_reg_data |= (DA7212_DAI_CTRL_EN_ON | DA7212_DAI_CTRL_OE_ON | DA7212_DAI_CTRL_WL_LEN_16);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAI_CTRL], da7212_reg_data);

    /* set DIG_ROUTING_DAC */
    da7212_reg_data = DA7212_DIG_ROUTING_DAC_INI_VAL;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DIG_ROUTING_DAC], da7212_reg_data);

    /* set DAC_L_GAIN */
    da7212_reg_data = DA7212_DAC_L_GAIN_INI_VAL;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAC_L_GAIN], da7212_reg_data);

    /* set DAC_R_GAIN */
    da7212_reg_data = DA7212_DAC_R_GAIN_INI_VAL;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAC_R_GAIN], da7212_reg_data);

    /* set HP_L_GAIN */
    da7212_reg_data = DA7212_HP_L_GAIN_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_L_GAIN_BIT));
    da7212_reg_data |= da7212_hp_lr_gain_db(DEFAULT_GAIN_HEADPHONE_DB);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_HP_L_GAIN], da7212_reg_data);

    /* set HP_R_GAIN */
    da7212_reg_data = DA7212_HP_R_GAIN_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_R_GAIN_BIT));
    da7212_reg_data |= da7212_hp_lr_gain_db(DEFAULT_GAIN_HEADPHONE_DB);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_HP_R_GAIN], da7212_reg_data);

    /* set MIXOUT_L_SELECT */
    da7212_reg_data = DA7212_MIXOUT_L_SELECT_INI_VAL;
    da7212_reg_data |= DA7212_MIXOUT_L_SELECT_DAC_L_ON;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIXOUT_L_SELECT], da7212_reg_data);

    /* set MIXOUT_R_SELECT */
    da7212_reg_data = DA7212_MIXOUT_R_SELECT_INI_VAL;
    da7212_reg_data |= DA7212_MIXOUT_R_SELECT_DAC_R_ON;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIXOUT_R_SELECT], da7212_reg_data);

    /* set SYSTEM_MODES_OUTPUT */
    da7212_reg_data = DA7212_SYSTEM_MODES_OUTPUT_INI_VAL;

    da7212_reg_data |= (DA7212_SYSTEM_MODES_OUTPUT_DAC_R_ON | DA7212_SYSTEM_MODES_OUTPUT_DAC_L_ON | DA7212_SYSTEM_MODES_OUTPUT_HP_R_ON
                      | DA7212_SYSTEM_MODES_OUTPUT_HP_L_ON | DA7212_SYSTEM_MODES_OUTPUT_LINE_ON | DA7212_SYSTEM_MODES_OUTPUT_MD_SUB_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_SYSTEM_MODES_OUTPUT], da7212_reg_data);

    /* set DAC_L_CTRL */
    da7212_reg_data = DA7212_DAC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAC_L_CTRL_EN_BIT | DA7212_DAC_L_CTRL_MUTE_BIT | DA7212_DAC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_DAC_L_CTRL_EN_ON | DA7212_DAC_L_CTRL_MUTE_OFF | DA7212_DAC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAC_L_CTRL], da7212_reg_data);

    /* set DAC_R_CTRL */
    da7212_reg_data = DA7212_DAC_R_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_DAC_R_CTRL_EN_BIT | DA7212_DAC_R_CTRL_MUTE_BIT | DA7212_DAC_R_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_DAC_R_CTRL_EN_ON | DA7212_DAC_R_CTRL_MUTE_OFF | DA7212_DAC_R_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_DAC_R_CTRL], da7212_reg_data);

    /* set CP_CTRL */
    da7212_reg_data = DA7212_CP_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_CP_CTRL_EN_BIT));
    da7212_reg_data |= (DA7212_CP_CTRL_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_CP_CTRL], da7212_reg_data);

    /* set HP_L_CTRL */
    da7212_reg_data = DA7212_HP_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_L_CTRL_AMP_EN_BIT | DA7212_HP_L_CTRL_AMP_MUTE_BIT | DA7212_HP_L_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_HP_L_CTRL_AMP_AMP_OE_BIT ));
    da7212_reg_data |= (DA7212_HP_L_CTRL_AMP_EN_ON | DA7212_HP_L_CTRL_AMP_MUTE_OFF | DA7212_HP_L_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_HP_L_CTRL], da7212_reg_data);

    /* set HP_R_CTRL */
    da7212_reg_data = DA7212_HP_R_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_HP_R_CTRL_AMP_EN_BIT | DA7212_HP_R_CTRL_AMP_MUTE_BIT | DA7212_HP_R_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_HP_R_CTRL_AMP_AMP_OE_BIT ));
    da7212_reg_data |= (DA7212_HP_R_CTRL_AMP_EN_ON | DA7212_HP_R_CTRL_AMP_MUTE_OFF | DA7212_HP_R_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_HP_R_CTRL], da7212_reg_data);

    /* set LINE_CTRL */
    da7212_reg_data = DA7212_LINE_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_LINE_CTRL_AMP_EN_BIT | DA7212_LINE_CTRL_AMP_MUTE_BIT | DA7212_LINE_CTRL_AMP_RMP_EN_BIT
                                 | DA7212_LINE_CTRL_AMP_AMP_OE_BIT | DA7212_LINE_CTRL_AMP_MIN_GAIN_EN_BIT ));
    da7212_reg_data |= (DA7212_LINE_CTRL_AMP_EN_ON | DA7212_LINE_CTRL_AMP_MUTE_OFF | DA7212_LINE_CTRL_AMP_AMP_OE_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_LINE_CTRL], da7212_reg_data);


    /* set IO_CTRL */
    da7212_reg_data = DA7212_TONE_GEN_CYCLES_INI_VAL;
    da7212_reg_data |= DA7212_IO_CTRL_IO_VOL_LVL_HIGH;
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_IO_CTRL], da7212_reg_data);

    //Input set up
    // set REFERENCES
    da7212_reg_data = DA7212_REFERENCES_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_REFERENCES_BIAS_EN_BIT));
    da7212_reg_data |= (DA7212_REFERENCES_BIAS_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_REFERENCES], da7212_reg_data);

    // set MICBIAS_CTRL
    da7212_reg_data = DA7212_MICBIAS_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MICBIAS_CTRL_MICBIAS1_EN_BIT));
    da7212_reg_data |= (DA7212_MICBIAS_CTRL_MICBIAS1_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MICBIAS_CTRL], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_ON | DA7212_MIC_1_CTRL_AMP_MUTE_EN_OFF | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_OFF | DA7212_MIC_1_CTRL_AMP_MUTE_EN_ON | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);

    // set MIXIN_L_CTRL
    da7212_reg_data = DA7212_MIXIN_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIXIN_L_CTRL_AMP_EN_BIT | DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_BIT | DA7212_MIXIN_L_CTRL_AMP_RMP_EN_BIT | DA7212_MIXIN_L_CTRL_MIX_EN_BIT));
    da7212_reg_data |= (DA7212_MIXIN_L_CTRL_AMP_EN_ON | DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_OFF | DA7212_MIXIN_L_CTRL_AMP_RMP_EN_ON | DA7212_MIXIN_L_CTRL_MIX_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIXIN_L_CTRL], da7212_reg_data);

    // set MIXIN_L_SELECT
    da7212_reg_data = DA7212_MIXIN_L_SELECT_INI_VAL;
    da7212_reg_data |= (DA7212_MIXIN_L_SELECT_MIC1_SEL_MIX);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIXIN_L_SELECT], da7212_reg_data);

    // set ADC_L_CTRL
    da7212_reg_data = DA7212_ADC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_L_CTRL_EN_BIT | DA7212_ADC_L_CTRL_MUTE_BIT | DA7212_ADC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_L_CTRL_EN_ON | DA7212_ADC_L_CTRL_MUTE_ON | DA7212_ADC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_ADC_L_CTRL], da7212_reg_data);

    // set ALC_CTRL1
    da7212_reg_data = DA7212_ALC_CTRL1_INI_VAL;
    da7212_reg_data |= (DA7212_ALC_CTRL1_AUTO_CALIB_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_ALC_CTRL1], da7212_reg_data);

    while(calboffset_data)
    {
        uint8_t send_data[1];
        fsp_err_t err;

        send_data[0] = g_da7212_reg_addr[DA7212_REG_ALC_CTRL1];

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
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_ALC_CTRL1], da7212_reg_data);

    // set MIC_1_CTRL
    da7212_reg_data = DA7212_MIC_1_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_MIC_1_CTRL_AMP_EN_BIT | DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT | DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT));
    da7212_reg_data |= (DA7212_MIC_1_CTRL_AMP_EN_ON | DA7212_MIC_1_CTRL_AMP_MUTE_EN_OFF | DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_MIC_1_CTRL], da7212_reg_data);
    // set ADC_L_CTRL
    da7212_reg_data = DA7212_ADC_L_CTRL_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_L_CTRL_EN_BIT | DA7212_ADC_L_CTRL_MUTE_BIT | DA7212_ADC_L_CTRL_RMP_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_L_CTRL_EN_ON | DA7212_ADC_L_CTRL_MUTE_OFF | DA7212_ADC_L_CTRL_RMP_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_ADC_L_CTRL], da7212_reg_data);

    // set SYSTEM_MODES_INPUT
    da7212_reg_data = DA7212_SYSTEM_MODES_INPUT_INI_VAL;
    da7212_reg_data |= ( DA7212_SYSTEM_MODES_INPUT_MIXIN_L_ON | DA7212_SYSTEM_MODES_INPUT_MIC_1_ON | DA7212_SYSTEM_MODES_INPUT_ADC_L_ON
                       | DA7212_SYSTEM_MODES_INPUT_MD_SUB_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_SYSTEM_MODES_INPUT], da7212_reg_data);

    // set ADC_FILTERS1
    da7212_reg_data = DA7212_ADC_FILTERS1_INI_VAL;
    da7212_reg_data &= (uint8_t)(~(DA7212_ADC_FILTERS1_HPF_EN_BIT | DA7212_ADC_FILTERS1_VC_EN_BIT));
    da7212_reg_data |= (DA7212_ADC_FILTERS1_HPF_EN_OFF | DA7212_ADC_FILTERS1_VC_EN_ON);
    da7212_send_data(p_i2c, g_da7212_reg_addr[DA7212_REG_ADC_FILTERS1], da7212_reg_data);

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
