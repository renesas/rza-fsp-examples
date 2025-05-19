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

#ifndef DA7212_DATA_H
#define DA7212_DATA_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
/* ==== Register Setting Value ==== */
/* CIF_CTRL (0x1D) */
#define DA7212_SOFT_RESET_VAL           (0x80U)
/* DIG_ROUTING_DAI (0x21) */
#define DA7212_DIG_ROUTING_DAI_INI_VAL      (0x10U)
#define DA7212_DIG_ROUTING_DAI_L_SRC_BIT    (0x03U)
#define DA7212_DIG_ROUTING_DAI_R_SRC_BIT    (0x30U)
#define DA7212_DIG_ROUTING_DAI_R_SRC_DAI    (0x30U)
#define DA7212_DIG_ROUTING_DAI_R_SRC_ADC    (0x00U)
#define DA7212_DIG_ROUTING_DAI_L_SRC_DAI    (0x02U)
#define DA7212_DIG_ROUTING_DAI_L_SRC_ADC    (0x00U)
/* SR (0x22) */
#define DA7212_SR_INI_VAL                   (0x0AU)
#define DA7212_SR_BIT                       (0x0FU)
#define DA7212_SR_48kHz                     (0x0BU)
#define DA7212_SR_44_1kHz                   (0x0AU)
/* REFERENCES (0x23) */
#define DA7212_REFERENCES_INI_VAL           (0x80U)
#define DA7212_REFERENCES_VMIDFSTDISCHG_BIT (0x20U)
#define DA7212_REFERENCES_VMIDFSTCHG_BIT    (0x10U)
#define DA7212_REFERENCES_BIAS_EN_BIT       (0x08U)
#define DA7212_REFERENCES_VMIDFSTDISCHG_ON  (0x20U)
#define DA7212_REFERENCES_VMIDFSTCHG_ON     (0x10U)
#define DA7212_REFERENCES_BIAS_EN_ON        (0x08U)
/* PLL_CTRL (0x27) */
#define DA7212_PLL_CTRL_INI_VAL             (0x0C)
#define DA7212_PLL_CTRL_EN_BIT              (0x80)
#define DA7212_PLL_CTRL_SRM_EN_BIT          (0x40)
#define DA7212_PLL_CTRL_32K_MODE_BIT        (0x20)
#define DA7212_PLL_CTRL_MCLK_SQR_EN_BIT     (0x10)
#define DA7212_PLL_CTRL_INDIV_BIT           (0x0C)
#define DA7212_PLL_CTRL_INDIV_20_40         (0x08)
/* DAI_CLK_MODE (0x28) */
#define DA7212_DAI_CLK_MODE_INI_VAL         (0x01U)
#define DA7212_DAI_CLK_MODE_CLK_EN_BIT      (0x80U)
#define DA7212_DAI_CLK_MODE_WCLK_POL_BIT    (0x08U)
#define DA7212_DAI_CLK_MODE_CLK_POL_BIT     (0x04U)
#define DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_BIT  (0x03U)
#define DA7212_DAI_CLK_MODE_CLK_EN_ON       (0x80U)
#define DA7212_DAI_CLK_MODE_WCLK_POL_INV    (0x08U)
#define DA7212_DAI_CLK_MODE_CLK_POL_INV     (0x04U)
#define DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_32  (0x00U)
#define DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_64  (0x01U)
#define DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_128 (0x02U)
#define DA7212_DAI_CLK_MODE_BCLKS_PER_WCLK_256 (0x03U)
/* DAI_CTRL (0x29) */
#define DA7212_DAI_CTRL_INI_VAL             (0x08U)
#define DA7212_DAI_CTRL_EN_BIT              (0x80U)
#define DA7212_DAI_CTRL_OE_BIT              (0x40U)
#define DA7212_DAI_CTRL_TDM_EN_BIT          (0x20U)
#define DA7212_DAI_CTRL_MONO_EN_BIT         (0x10U)
#define DA7212_DAI_CTRL_WL_LEN_BIT          (0x0CU)
#define DA7212_DAI_CTRL_FORMAT_BIT          (0x03U)
#define DA7212_DAI_CTRL_EN_ON               (0x80U)
#define DA7212_DAI_CTRL_OE_ON               (0x40U)
#define DA7212_DAI_CTRL_WL_LEN_16           (0x00U)
#define DA7212_DAI_CTRL_WL_LEN_20           (0x04U)
#define DA7212_DAI_CTRL_WL_LEN_24           (0x08U)
#define DA7212_DAI_CTRL_WL_LEN_32           (0x0CU)
/* DIG_ROUTING_DAC (0x2A) */
#define DA7212_DIG_ROUTING_DAC_INI_VAL      (0x32U)
#define DA7212_DIG_ROUTING_DAC_R_MONO_BIT   (0x80U)
#define DA7212_DIG_ROUTING_DAC_R_SRC_BIT    (0x30U)
#define DA7212_DIG_ROUTING_DAC_L_MONO_BIT   (0x08U)
#define DA7212_DIG_ROUTING_DAC_L_SRC_BIT    (0x03U)
#define DA7212_DIG_ROUTING_DAC_R_MONO_MIX   (0x80U)
#define DA7212_DIG_ROUTING_DAC_R_SRC_MONO   (0x30U)
#define DA7212_DIG_ROUTING_DAC_R_SRC_ADC_L  (0x00U)
#define DA7212_DIG_ROUTING_DAC_L_MONO_MIX   (0x08U)
#define DA7212_DIG_ROUTING_DAC_L_SRC_MONO   (0x02U)
#define DA7212_DIG_ROUTING_DAC_L_SRC_ADC_L  (0x00U)
/* ALC_CTRL1 (0x2B) */
#define DA7212_ALC_CTRL1_INI_VAL            (0x00U)
#define DA7212_ALC_CTRL1_R_EN_ON            (0x80U)
#define DA7212_ALC_CTRL1_AUTO_CALIB_EN_ON   (0x10U)
#define DA7212_ALC_CTRL1_L_EN_ON            (0x08U)
#define DA7212_ALC_CTRL1_SYNC_MODE_ON       (0x02U)
#define DA7212_ALC_CTRL1_OFST_EN_ON         (0x01U)
/* MIXIN_L_SELECT (0x32) */
#define DA7212_MIXIN_L_SELECT_INI_VAL       (0x00U)
#define DA7212_MIXIN_L_SELECT_MIC1_SEL_MIX  (0x02U)
/* MIXIN_L_GAIN (0x34) */
#define DA7212_MIXIN_L_GAIN_INI_VAL         (0x03U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_BIT    (0x0FU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_N4_5   (0x00U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_N3     (0x01U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_N1_5   (0x02U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_0      (0x03U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P1_5   (0x04U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P3     (0x05U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P4_5   (0x06U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P6     (0x07U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P7_5   (0x08U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P9     (0x09U)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P10_5  (0x0AU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P12    (0x0BU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P13_5  (0x0CU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P15    (0x0DU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P16_5  (0x0EU)
#define DA7212_MIXIN_L_GAIN_AMP_GAIN_P18    (0x0FU)
/* ADC_L_GAIN (0x36) */
#define DA7212_ADC_L_GAIN_INI_VAL           (0x6FU)
#define DA7212_ADC_L_GAIN_DIG_GAIN_BIT      (0x7FU)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N83_25   (0x00U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N72_75   (0x14U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N63_00   (0x1BU)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N53_25   (0x28U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N42_00   (0x37U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N33_00   (0x43U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N23_25   (0x50U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_N13_50   (0x5DU)
#define DA7212_ADC_L_GAIN_DIG_GAIN_0_00     (0x6FU)
#define DA7212_ADC_L_GAIN_DIG_GAIN_P6_00    (0x77U)
#define DA7212_ADC_L_GAIN_DIG_GAIN_P12_00   (0x7FU)
/* ADC_FILTERS1 (0x38) */
#define DA7212_ADC_FILTERS1_INI_VAL         (0x80U)
#define DA7212_ADC_FILTERS1_HPF_EN_BIT      (0x80U)
#define DA7212_ADC_FILTERS1_AUD_HPF_CRN_BIT (0x30U)
#define DA7212_ADC_FILTERS1_VC_EN_BIT       (0x08U)
#define DA7212_ADC_FILTERS1_VC_HPF_CRN_BIT  (0x07U)
#define DA7212_ADC_FILTERS1_HPF_EN_OFF      (0x00U)
#define DA7212_ADC_FILTERS1_VC_EN_ON        (0x08U)
/* MIC_1_GAIN (0x39) */
#define DA7212_MIC_1_GAIN_INI_VAL           (0x01U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_BIT      (0x07U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_N6DB     (0x00U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_0DB      (0x01U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_6DB      (0x02U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_12DB     (0x03U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_18DB     (0x04U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_24DB     (0x05U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_30DB     (0x06U)
#define DA7212_MIC_1_GAIN_AMP_GAIN_36DB     (0x07U)
/* DAC_L_GAIN (0x45) */
#define DA7212_DAC_L_GAIN_INI_VAL           (0x6FU)
#define DA7212_DAC_L_GAIN_BIT               (0x7FU)
#define DA7212_DAC_L_GAIN_N77_25DB          (0x08U)
#define DA7212_DAC_L_GAIN_N36DB             (0x3FU)
#define DA7212_DAC_L_GAIN_N12DB             (0x5FU)
#define DA7212_DAC_L_GAIN_P6DB              (0x77U)
#define DA7212_DAC_L_GAIN_P12DB             (0x7FU)
/* DAC_R_GAIN (0x46) */
#define DA7212_DAC_R_GAIN_INI_VAL           (0x6FU)
#define DA7212_DAC_R_GAIN_BIT               (0x7FU)
#define DA7212_DAC_R_GAIN_N77_25DB          (0x08U)
#define DA7212_DAC_R_GAIN_N36DB             (0x3FU)
#define DA7212_DAC_R_GAIN_N12DB             (0x5FU)
#define DA7212_DAC_R_GAIN_P6DB              (0x77U)
#define DA7212_DAC_R_GAIN_P12DB             (0x7FU)
/* CP_CTRL (0x47) */
#define DA7212_CP_CTRL_INI_VAL              (0x61U)
#define DA7212_CP_CTRL_EN_BIT               (0x80U)
#define DA7212_CP_CTRL_SMLL_SWCH_FRQ_EN_BIT (0x40U)
#define DA7212_CP_CTRL_MCHRG_BIT            (0x30U)
#define DA7212_CP_CTRL_MOD_BIT              (0x0CU)
#define DA7212_CP_CTRL_ANLG_LVL_BIT         (0x03U)
#define DA7212_CP_CTRL_EN_ON                (0x80U)
#define DA7212_CP_CTRL_SMLL_SWCH_FRQ_EN_ON  (0x40U)
#define DA7212_CP_CTRL_MCHRG_MOD            (0x00U)
#define DA7212_CP_CTRL_MCHRG_PGA            (0x10U)
#define DA7212_CP_CTRL_MCHRG_DAC            (0x20U)
#define DA7212_CP_CTRL_MCHRG_OUT            (0x30U)
#define DA7212_CP_CTRL_MOD_STNBY            (0x00U)
#define DA7212_CP_CTRL_MOD_CPVDD_2          (0x80U)
#define DA7212_CP_CTRL_MOD_CPVDD_1          (0xC0U)
#define DA7212_CP_CTRL_ANLG_LVL_NONFEEDBCK  (0x00U)
#define DA7212_CP_CTRL_ANLG_LVL_BOOST       (0x01U)
#define DA7212_CP_CTRL_ANLG_LVL_CYCLE       (0x02U)
/* HP_L_GAIN (0x48) */
#define DA7212_HP_L_GAIN_INI_VAL            (0x39U)
#define DA7212_HP_L_GAIN_BIT                (0x3FU)
#define DA7212_HP_L_GAIN_N57DB              (0x00U)
#define DA7212_HP_L_GAIN_N20DB              (0x25U)
#define DA7212_HP_L_GAIN_P3DB               (0x3CU)
#define DA7212_HP_L_GAIN_P6DB               (0x3FU)
/* HP_R_GAIN (0x49) */
#define DA7212_HP_R_GAIN_INI_VAL            (0x39U)
#define DA7212_HP_R_GAIN_BIT                (0x3FU)
#define DA7212_HP_R_GAIN_N57DB              (0x00U)
#define DA7212_HP_R_GAIN_N20DB              (0x25U)
#define DA7212_HP_R_GAIN_P3DB               (0x3CU)
#define DA7212_HP_R_GAIN_P6DB               (0x3FU)
/* MIXOUT_L_SELECT (0x4B) */
#define DA7212_MIXOUT_L_SELECT_INI_VAL      (0x00U)
#define DA7212_MIXOUT_L_SELECT_DAC_L_ON     (0x08U)
#define DA7212_MIXOUT_L_SELECT_MIXIN_L_ON   (0x02U)
/* MIXOUT_R_SELECT (0x4C) */
#define DA7212_MIXOUT_R_SELECT_INI_VAL      (0x00U)
#define DA7212_MIXOUT_R_SELECT_DAC_R_ON     (0x08U)
#define DA7212_MIXOUT_R_SELECT_MIXIN_L_ON   (0x04U)
/* SYSTEM_MODES_INPUT (0x50) */
#define DA7212_SYSTEM_MODES_INPUT_INI_VAL   (0x00U)
#define DA7212_SYSTEM_MODES_INPUT_ADC_L_ON  (0x40U)
#define DA7212_SYSTEM_MODES_INPUT_MIXIN_L_ON (0x10U)
#define DA7212_SYSTEM_MODES_INPUT_MIC_1_ON  (0x04U)
#define DA7212_SYSTEM_MODES_INPUT_MD_SUB_ON (0x01U)
/* SYSTEM_MODES_OUTPUT (0x51) */
#define DA7212_SYSTEM_MODES_OUTPUT_INI_VAL  (0x00U)
#define DA7212_SYSTEM_MODES_OUTPUT_DAC_R_ON (0x80U)
#define DA7212_SYSTEM_MODES_OUTPUT_DAC_L_ON (0x40U)
#define DA7212_SYSTEM_MODES_OUTPUT_HP_R_ON  (0x20U)
#define DA7212_SYSTEM_MODES_OUTPUT_HP_L_ON  (0x10U)
#define DA7212_SYSTEM_MODES_OUTPUT_LINE_ON  (0x08U)
#define DA7212_SYSTEM_MODES_OUTPUT_MD_SUB_ON (0x01U)
/* MICBIAS_CTRL (0x62) */
#define DA7212_MICBIAS_CTRL_INI_VAL         (0x11U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_EN_BIT (0x80U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_LVL_BIT (0x30U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_EN_BIT (0x08U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_LVL_BIT (0x03U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_EN_ON  (0x80U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_EN_OFF (0x00U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_LVL_16 (0x00U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_LVL_22 (0x10U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_LVL_25 (0x20U)
#define DA7212_MICBIAS_CTRL_MICBIAS2_LVL_30 (0x30U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_EN_ON  (0x08U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_EN_OFF (0x00U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_LVL_16 (0x00U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_LVL_22 (0x01U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_LVL_25 (0x02U)
#define DA7212_MICBIAS_CTRL_MICBIAS1_LVL_30 (0x03U)
/* MIC_1_CTRL (0x63) */
#define DA7212_MIC_1_CTRL_INI_VAL           (0x40U)
#define DA7212_MIC_1_CTRL_AMP_EN_BIT        (0x80U)
#define DA7212_MIC_1_CTRL_AMP_MUTE_EN_BIT   (0x40U)
#define DA7212_MIC_1_CTRL_AMP_IN_SEL_BIT    (0x0CU)
#define DA7212_MIC_1_CTRL_AMP_EN_ON         (0x80U)
#define DA7212_MIC_1_CTRL_AMP_EN_OFF        (0x00U)
#define DA7212_MIC_1_CTRL_AMP_MUTE_EN_OFF   (0x00U)
#define DA7212_MIC_1_CTRL_AMP_MUTE_EN_ON    (0x40U)
#define DA7212_MIC_1_CTRL_AMP_IN_SEL_PEND   (0x04U)
/* MIXIN_L_CTRL (0x65) */
#define DA7212_MIXIN_L_CTRL_INI_VAL         (0x40U)
#define DA7212_MIXIN_L_CTRL_AMP_EN_BIT      (0x80U)
#define DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_BIT (0x40U)
#define DA7212_MIXIN_L_CTRL_AMP_RMP_EN_BIT  (0x20U)
#define DA7212_MIXIN_L_CTRL_AMP_ZC_EN_BIT   (0x10U)
#define DA7212_MIXIN_L_CTRL_MIX_EN_BIT      (0x08U)
#define DA7212_MIXIN_L_CTRL_AMP_EN_ON       (0x80U)
#define DA7212_MIXIN_L_CTRL_AMP_MUTE_EN_OFF (0x00U)
#define DA7212_MIXIN_L_CTRL_AMP_RMP_EN_ON   (0x20U)
#define DA7212_MIXIN_L_CTRL_MIX_EN_ON       (0x08U)
/* ADC_L_CTRL (0x67) */
#define DA7212_ADC_L_CTRL_INI_VAL           (0x40U)
#define DA7212_ADC_L_CTRL_EN_BIT            (0x80U)
#define DA7212_ADC_L_CTRL_MUTE_BIT          (0x40U)
#define DA7212_ADC_L_CTRL_RMP_EN_BIT        (0x20U)
#define DA7212_ADC_L_CTRL_EN_ON             (0x80U)
#define DA7212_ADC_L_CTRL_EN_OFF            (0x00U)
#define DA7212_ADC_L_CTRL_MUTE_ON           (0x40U)
#define DA7212_ADC_L_CTRL_MUTE_OFF          (0x00U)
#define DA7212_ADC_L_CTRL_RMP_EN_ON         (0x20U)
#define DA7212_ADC_L_CTRL_RMP_EN_OFF        (0x00U)
/* DAC_L_CTRL (0x69) */
#define DA7212_DAC_L_CTRL_INI_VAL           (0x48U)
#define DA7212_DAC_L_CTRL_EN_BIT            (0x80U)
#define DA7212_DAC_L_CTRL_MUTE_BIT          (0x40U)
#define DA7212_DAC_L_CTRL_RMP_EN_BIT        (0x20U)
#define DA7212_DAC_L_CTRL_EN_ON             (0x80U)
#define DA7212_DAC_L_CTRL_MUTE_OFF          (0x00U)
#define DA7212_DAC_L_CTRL_RMP_EN_ON         (0x20U)
/* DAC_R_CTRL (0x6A) */
#define DA7212_DAC_R_CTRL_INI_VAL           (0x40U)
#define DA7212_DAC_R_CTRL_EN_BIT            (0x80U)
#define DA7212_DAC_R_CTRL_MUTE_BIT          (0x40U)
#define DA7212_DAC_R_CTRL_RMP_EN_BIT        (0x20U)
#define DA7212_DAC_R_CTRL_EN_ON             (0x80U)
#define DA7212_DAC_R_CTRL_MUTE_OFF          (0x00U)
#define DA7212_DAC_R_CTRL_RMP_EN_ON         (0x20U)
/* HP_L_CTRL (0x6B) */
#define DA7212_HP_L_CTRL_INI_VAL            (0x41U)
#define DA7212_HP_L_CTRL_AMP_EN_BIT         (0x80U)
#define DA7212_HP_L_CTRL_AMP_MUTE_BIT       (0x40U)
#define DA7212_HP_L_CTRL_AMP_RMP_EN_BIT     (0x20U)
#define DA7212_HP_L_CTRL_AMP_ZC_EN_BIT      (0x10U)
#define DA7212_HP_L_CTRL_AMP_AMP_OE_BIT     (0x08U)
#define DA7212_HP_L_CTRL_AMP_MIN_GAIN_EN_BIT (0x04U)
#define DA7212_HP_L_CTRL_AMP_EN_ON          (0x80U)
#define DA7212_HP_L_CTRL_AMP_MUTE_OFF       (0x00U)
#define DA7212_HP_L_CTRL_AMP_AMP_OE_ON      (0x08U)
/* HP_R_CTRL (0x6C) */
#define DA7212_HP_R_CTRL_INI_VAL            (0x40U)
#define DA7212_HP_R_CTRL_AMP_EN_BIT         (0x80U)
#define DA7212_HP_R_CTRL_AMP_MUTE_BIT       (0x40U)
#define DA7212_HP_R_CTRL_AMP_RMP_EN_BIT     (0x20U)
#define DA7212_HP_R_CTRL_AMP_ZC_EN_BIT      (0x10U)
#define DA7212_HP_R_CTRL_AMP_AMP_OE_BIT     (0x08U)
#define DA7212_HP_R_CTRL_AMP_MIN_GAIN_EN_BIT (0x04U)
#define DA7212_HP_R_CTRL_AMP_EN_ON          (0x80U)
#define DA7212_HP_R_CTRL_AMP_MUTE_OFF       (0x00U)
#define DA7212_HP_R_CTRL_AMP_AMP_OE_ON      (0x08U)
/* LINE_CTRL (0x6D) */
#define DA7212_LINE_CTRL_INI_VAL            (0x40U)
#define DA7212_LINE_CTRL_AMP_EN_BIT         (0x80U)
#define DA7212_LINE_CTRL_AMP_MUTE_BIT       (0x40U)
#define DA7212_LINE_CTRL_AMP_RMP_EN_BIT     (0x20U)
#define DA7212_LINE_CTRL_AMP_AMP_OE_BIT     (0x08U)
#define DA7212_LINE_CTRL_AMP_MIN_GAIN_EN_BIT (0x04U)
#define DA7212_LINE_CTRL_AMP_EN_ON          (0x80U)
#define DA7212_LINE_CTRL_AMP_MUTE_OFF       (0x00U)
#define DA7212_LINE_CTRL_AMP_AMP_OE_ON      (0x08U)
/* IO_CTRL (0x91) */
#define DA7212_IO_CTRL_INI_VAL              (0x00U)
#define DA7212_IO_CTRL_IO_VOL_LVL_HIGH      (0x01U)
/* Beep settings for debugging */
/* TONE_GEN_CFG1 */
#define DA7212_TONE_GEN_CFG1_INI_VAL        (0x00)
#define DA7212_TONE_GEN_CFG1_STRT_STP_ON    (0x80)
#define DA7212_TONE_GEN_CFG1_DMTF_EN_ON     (0x10)
#define DA7212_TONE_GEN_CFG1_DMTF_REG_VAL   (0x01)
/*TONE_GEN_CYCLES*/
#define DA7212_TONE_GEN_CYCLES_INI_VAL      (0x00)
#define DA7212_TONE_GEN_CYCLES_BEEP_CYCLES_VAL  (0x06)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/


/***********************************************************************************************************************
 * Private function prototypes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Global Variables
 **********************************************************************************************************************/
enum{
    DA7212_REG_STATUS1,
    DA7212_REG_PLL_STATUS,
    DA7212_REG_AUX_L_GAIN_STATUS,
    DA7212_REG_AUX_R_GAIN_STATUS,
    DA7212_REG_MIC_1_GAIN_STATUS,
    DA7212_REG_MIC_2_GAIN_STATUS,
    DA7212_REG_MIXIN_L_GAIN_STATUS,
    DA7212_REG_MIXIN_R_GAIN_STATUS,
    DA7212_REG_ADC_L_GAIN_STATUS,
    DA7212_REG_ADC_R_GAIN_STATUS,
    DA7212_REG_DAC_L_GAIN_STATUS,
    DA7212_REG_DAC_R_GAIN_STATUS,
    DA7212_REG_HP_L_GAIN_STATUS,
    DA7212_REG_HP_R_GAIN_STATUS,
    DA7212_REG_LINE_GAIN_STATUS,
    DA7212_REG_CIF_CTRL,
    DA7212_REG_DIG_ROUTING_DAI,
    DA7212_REG_SR,
    DA7212_REG_REFERENCES,
    DA7212_REG_PLL_FRAC_TOP,
    DA7212_REG_PLL_FRAC_BOT,
    DA7212_REG_PLL_INTEGER,
    DA7212_REG_PLL_CTRL,
    DA7212_REG_DAI_CLK_MODE,
    DA7212_REG_DAI_CTRL,
    DA7212_REG_DIG_ROUTING_DAC,
    DA7212_REG_ALC_CTRL1,
    DA7212_REG_AUX_L_GAIN,
    DA7212_REG_AUX_R_GAIN,
    DA7212_REG_MIXIN_L_SELECT,
    DA7212_REG_MIXIN_R_SELECT,
    DA7212_REG_MIXIN_L_GAIN,
    DA7212_REG_MIXIN_R_GAIN,
    DA7212_REG_ADC_L_GAIN,
    DA7212_REG_ADC_R_GAIN,
    DA7212_REG_ADC_FILTERS1,
    DA7212_REG_MIC_1_GAIN,
    DA7212_REG_MIC_2_GAIN,
    DA7212_REG_DAC_FILTERS5,
    DA7212_REG_DAC_FILTERS2,
    DA7212_REG_DAC_FILTERS3,
    DA7212_REG_DAC_FILTERS4,
    DA7212_REG_DAC_FILTERS1,
    DA7212_REG_DAC_L_GAIN,
    DA7212_REG_DAC_R_GAIN,
    DA7212_REG_CP_CTRL,
    DA7212_REG_HP_L_GAIN,
    DA7212_REG_HP_R_GAIN,
    DA7212_REG_LINE_GAIN,
    DA7212_REG_MIXOUT_L_SELECT,
    DA7212_REG_MIXOUT_R_SELECT,
    DA7212_REG_SYSTEM_MODES_INPUT,
    DA7212_REG_SYSTEM_MODES_OUTPUT,
    DA7212_REG_AUX_L_CTRL,
    DA7212_REG_DA7212_REG_AUX_R_CTRL,
    DA7212_REG_MICBIAS_CTRL,
    DA7212_REG_MIC_1_CTRL,
    DA7212_REG_MIC_2_CTRL,
    DA7212_REG_MIXIN_L_CTRL,
    DA7212_REG_MIXIN_R_CTRL,
    DA7212_REG_ADC_L_CTRL,
    DA7212_REG_ADC_R_CTRL,
    DA7212_REG_DAC_L_CTRL,
    DA7212_REG_DAC_R_CTRL,
    DA7212_REG_HP_L_CTRL,
    DA7212_REG_HP_R_CTRL,
    DA7212_REG_LINE_CTRL,
    DA7212_REG_MIXOUT_L_CTRL,
    DA7212_REG_MIXOUT_R_CTRL,
    DA7212_REG_MIXED_SAMPLE_MODE,
    DA7212_REG_LDO_CTRL,
    DA7212_REG_IO_CTRL,
    DA7212_REG_GAIN_RAMP_CTRL,
    DA7212_REG_MIC_CONFIG,
    DA7212_REG_PC_COUNT,
    DA7212_REG_CP_VOL_THRESHOLD1,
    DA7212_REG_CP_DELAY,
    DA7212_REG_CP_DETECTOR,
    DA7212_REG_DAI_OFFSET,
    DA7212_REG_DIG_CTRL,
    DA7212_REG_ALC_CTRL2,
    DA7212_REG_ALC_CTRL3,
    DA7212_REG_ALC_NOISE,
    DA7212_REG_ALC_TARGET_MIN,
    DA7212_REG_ALC_THRESHOLD_MAX,
    DA7212_REG_ALC_GAIN_LIMITS,
    DA7212_REG_ALC_ANA_GAIN_LIMITS,
    DA7212_REG_ALC_ANTICLIP_CTRL,
    DA7212_REG_ALC_ANTICLIP_LEVEL,
    DA7212_REG_ALC_OFFSET_AUTO_M_L,
    DA7212_REG_ALC_OFFSET_AUTO_U_L,
    DA7212_REG_ALC_OFFSET_MAN_M_L,
    DA7212_REG_ALC_OFFSET_MAN_U_L,
    DA7212_REG_ALC_OFFSET_AUTO_M_R,
    DA7212_REG_ALC_OFFSET_AUTO_U_R,
    DA7212_REG_ALC_OFFSET_MAN_M_R,
    DA7212_REG_ALC_OFFSET_MAN_U_R,
    DA7212_REG_ALC_CIC_OP_LVL_CTRL,
    DA7212_REG_ALC_CIC_OP_LVL_DATA,
    DA7212_REG_DAC_NG_SETUP_TIME,
    DA7212_REG_DAC_NG_OFF_THRESHOLD,
    DA7212_REG_DAC_NG_ON_THRESHOLD,
    DA7212_REG_DAC_NG_CTRL,
    DA7212_REG_TONE_GEN_CFG1,
    DA7212_REG_TONE_GEN_CFG2,
    DA7212_REG_TONE_GEN_CYCLES,
    DA7212_REG_TONE_GEN_FREQ1_L,
    DA7212_REG_TONE_GEN_FREQ1_U,
    DA7212_REG_TONE_GEN_FREQ2_L,
    DA7212_REG_TONE_GEN_FREQ2_U,
    DA7212_REG_TONE_GEN_ON_PER,
    DA7212_REG_TONE_GEN_OFF_PER,
    DA7212_REG_SYSTEM_STATUS,
    DA7212_REG_SYSTEM_ACTIVE,
    DA7212_REG_MAX
};
static const uint8_t da7212_reg_addr[DA7212_REG_MAX]=
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

static inline uint8_t da7212_hp_lr_gain_db(int8_t db)
{
    if (db > 6)
    {
        db = 6;
    }
    else if (db < -57)
    {
        db = -57;
    }
    else
    {
        ;
    }

    return (uint8_t) ((int8_t)DA7212_HP_L_GAIN_INI_VAL + db);
}

#endif                                 /* DA7212_DATA_H */
