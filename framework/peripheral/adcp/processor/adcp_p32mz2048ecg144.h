/* Created by plibgen $Revision: 1.29 $ */

#ifndef _ADCP_P32MZ2048ECG144_H
#define _ADCP_P32MZ2048ECG144_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/peripheral_common_32bit.h"

/* Default definition used for all API dispatch functions */
#ifndef INLINE_API
    #define INLINE_API extern inline
#endif

/* Default definition used for all other functions */
#ifndef INLINE
    #define INLINE extern inline
#endif

typedef enum {

    ADCP_ID_1 = 0,
    ADCP_NUMBER_OF_MODULES

} ADCP_MODULE_ID;

typedef enum {

    ADCP_VREF_AVDD_AVSS = 0,
    ADCP_VREF_VREFP_AVSS = 1,
    ADCP_VREF_AVDD_VREFN = 2,
    ADCP_VREF_VREFP_VREFN = 3

} ADCP_VREF_SOURCE;

typedef enum {

    ADCP_CLK_SRC_NONE = 0,
    ADCP_CLK_SRC_SYSCLK = 1,
    ADCP_CLK_SRC_RFCLK3 = 2,
    ADCP_CLK_SRC_FRC = 3

} ADCP_CLOCK_SOURCE;

typedef enum {

    ADCP_CLASS12_AN0 = 0,
    ADCP_CLASS12_AN1 = 1,
    ADCP_CLASS12_AN2 = 2,
    ADCP_CLASS12_AN3 = 3,
    ADCP_CLASS12_AN4 = 4,
    ADCP_CLASS12_AN5 = 5,
    ADCP_CLASS12_AN6 = 6,
    ADCP_CLASS12_AN7 = 7,
    ADCP_CLASS12_AN8 = 8,
    ADCP_CLASS12_AN9 = 9,
    ADCP_CLASS12_AN10 = 10,
    ADCP_CLASS12_AN11 = 11

} ADCP_CLASS12_INPUT_ID;

typedef enum {

    ADCP_SH0 = 0,
    ADCP_SH1 = 1,
    ADCP_SH2 = 2,
    ADCP_SH3 = 3,
    ADCP_SH4 = 4,
    ADCP_SH5 = 5

} ADCP_SH_ID;

typedef enum {

    ADCP_DSH0 = 0,
    ADCP_DSH1 = 1,
    ADCP_DSH2 = 2,
    ADCP_DSH3 = 3,
    ADCP_DSH4 = 4

} ADCP_DSH_ID;

typedef enum {

    ADCP_SH_MODE_SINGLE_ENDED_UNIPOLAR = 0,
    ADCP_SH_MODE_SINGLE_ENDED_TWOS_COMP = 1,
    ADCP_SH_MODE_DIFFERENTIAL_UNIPOLAR = 2,
    ADCP_SH_MODE_DIFFERENTIAL_TWOS_COMP = 3

} ADCP_SH_MODE;

typedef enum {

    ADCP_SCAN_TRG_SRC_NONE = 0,
    ADCP_SCAN_TRG_SRC_SOFTWARE = 1,
    ADCP_SCAN_TRG_SRC_INT0 = 4,
    ADCP_SCAN_TRG_SRC_TMR1_MATCH = 5,
    ADCP_SCAN_TRG_SRC_TMR3_MATCH = 6,
    ADCP_SCAN_TRG_SRC_TMR5_MATCH = 7,
    ADCP_SCAN_TRG_SRC_OCMP1 = 8,
    ADCP_SCAN_TRG_SRC_OCMP3 = 9,
    ADCP_SCAN_TRG_SRC_OCMP5 = 10,
    ADCP_SCAN_TRG_SRC_COMP1_COUT = 11,
    ADCP_SCAN_TRG_SRC_COMP2_COUT = 12

} ADCP_SCAN_TRG_SRC;

typedef enum {

    ADCP_TRG_SRC_NONE = 0,
    ADCP_TRG_SRC_SOFTWARE = 1,
    ADCP_TRG_SRC_SCAN_TRG = 3,
    ADCP_TRG_SRC_INT0 = 4,
    ADCP_TRG_SRC_TMR1_MATCH = 5,
    ADCP_TRG_SRC_TMR3_MATCH = 6,
    ADCP_TRG_SRC_TMR5_MATCH = 7,
    ADCP_TRG_SRC_OCMP1 = 8,
    ADCP_TRG_SRC_OCMP3 = 9,
    ADCP_TRG_SRC_OCMP5 = 10,
    ADCP_TRG_SRC_COMP1_COUT = 11,
    ADCP_TRG_SRC_COMP2_COUT = 12

} ADCP_TRG_SRC;

typedef enum {

    ADCP_AN0 = 0,
    ADCP_AN1 = 1,
    ADCP_AN2 = 2,
    ADCP_AN3 = 3,
    ADCP_AN4 = 4,
    ADCP_AN5 = 5,
    ADCP_AN6 = 6,
    ADCP_AN7 = 7,
    ADCP_AN8 = 8,
    ADCP_AN9 = 9,
    ADCP_AN10 = 10,
    ADCP_AN11 = 11,
    ADCP_AN12 = 12,
    ADCP_AN13 = 13,
    ADCP_AN14 = 14,
    ADCP_AN15 = 15,
    ADCP_AN16 = 16,
    ADCP_AN17 = 17,
    ADCP_AN18 = 18,
    ADCP_AN19 = 19,
    ADCP_AN20 = 20,
    ADCP_AN21 = 21,
    ADCP_AN22 = 22,
    ADCP_AN23 = 23,
    ADCP_AN24 = 24,
    ADCP_AN25 = 25,
    ADCP_AN26 = 26,
    ADCP_AN27 = 27,
    ADCP_AN28 = 28,
    ADCP_AN29 = 29,
    ADCP_AN30 = 30,
    ADCP_AN31 = 31,
    ADCP_AN32 = 32,
    ADCP_AN33 = 33,
    ADCP_AN34 = 34,
    ADCP_AN35 = 35,
    ADCP_AN36 = 36,
    ADCP_AN37 = 37,
    ADCP_AN38 = 38,
    ADCP_AN39 = 39,
    ADCP_AN40 = 40,
    ADCP_AN41 = 41,
    ADCP_AN42 = 42,
    ADCP_IVREF = 43,
    ADCP_ITEMP = 44

} ADCP_INPUT_ID;

typedef enum {

    ADCP_DCMP1 = 0,
    ADCP_DCMP2 = 1,
    ADCP_DCMP3 = 2,
    ADCP_DCMP4 = 3,
    ADCP_DCMP5 = 4,
    ADCP_DCMP6 = 5

} ADCP_DCMP_ID;

typedef enum {

    ADCP_ODFLTR1 = 0,
    ADCP_ODFLTR2 = 1,
    ADCP_ODFLTR3 = 2,
    ADCP_ODFLTR4 = 3,
    ADCP_ODFLTR5 = 4,
    ADCP_ODFLTR6 = 5

} ADCP_ODFLTR_ID;

typedef enum {

    ADCP_ODFLTR_4X = 0,
    ADCP_ODFLTR_16X = 1,
    ADCP_ODFLTR_64X = 2,
    ADCP_ODFLTR_256X = 3,
    ADCP_ODFLTR_2X = 4,
    ADCP_ODFLTR_8X = 5,
    ADCP_ODFLTR_32X = 6,
    ADCP_ODFLTR_128X = 7

} ADCP_ODFLTR_SAMPLE_RATIO;

INLINE SFR_TYPE* _ADCP_AD_DATA0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DATA0;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_ENABLE_CONTROL_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SCAN_TRIG_SRC_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EARLY_INT_ENABLE_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_STOP_IN_IDLE_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FRACTIONAL_MODE_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CLOCK_DIVIDER_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CLOCK_SRC_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_LOW_POWER_ENABLE_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_BOOST_VREF_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CLASS23_SH_SAMPLE_TIME_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_READY_STATUS_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_REQ_CNVRT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON3;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_VOLTAGE_REF_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON3;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_REQ_CNVRT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON3;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GLOBAL_SW_TRIGGER_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON3;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CALIBRATE_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CON3;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH0_ALT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH1_ALT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH2_ALT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH3_ALT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH4_ALT_INPUT_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH0_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH1_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH2_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH3_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH4_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_SH5_MODE_SELECT_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1IMOD;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_2_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_3_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_4_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_5_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_6_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_7_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_8_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_9_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_10_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_11_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_12_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_13_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_14_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_15_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_16_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_17_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_18_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_19_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_20_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_21_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_22_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_23_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_24_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_25_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_26_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_27_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_28_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_29_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_30_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_31_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_32_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_33_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_34_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_35_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_36_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_37_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_38_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_39_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_40_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_41_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_42_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_43_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_GROUP_INT_ENABLE_44_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1GIRQEN2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_2_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_3_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_4_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_5_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_6_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_7_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_8_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_9_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_10_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_11_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_12_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_13_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_14_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_15_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_16_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_17_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_18_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_19_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_20_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_21_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_22_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_23_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_24_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_25_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_26_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_27_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_28_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_29_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_30_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_31_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_32_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_33_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_34_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_35_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_36_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_37_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_38_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_39_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_40_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_41_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_42_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_43_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CHANNEL_SCAN_ENABLE_44_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CSS2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_2_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_3_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_4_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_5_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_6_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_7_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_8_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_9_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_10_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_11_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_12_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_13_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_14_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_15_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_16_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_17_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_18_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_19_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_20_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_21_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_22_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_23_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_24_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_25_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_26_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_27_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_28_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_29_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_30_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_31_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_32_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_33_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_34_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_35_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_36_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_37_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_38_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_39_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_40_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_41_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_42_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_43_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DATA_READY_44_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1DSTAT2;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_ON_LESS_THAN_LOW1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_ON_LESS_THAN_HIGH1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_EVENT_DETECTED1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DCMP_GLOBAL_INT_ENABLE1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DCMP_ENABLE1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_ANALOG_INPUT_ID1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPCON1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_2_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_3_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_4_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_5_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_6_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_7_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_8_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_9_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_10_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_11_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_12_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_13_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_14_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_15_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_16_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_17_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_18_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_19_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_20_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_21_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_22_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_23_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_24_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_25_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_26_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_27_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_28_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_29_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_30_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CMP_ENABLE_31_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMPEN1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DCMP_HIGH_LIMIT1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMP1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_DCMP_LO_LIMIT1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CMP1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_ENABLE1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_OVERSAMPLING1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_GLOBAL_IRQ_ENABLE1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_DATA_READY1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_CHANNEL_ID1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_FILTER_DATA1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1FLTR1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_TRIGGER_SOURCE0_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1TRG1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_TRIGGER_SOURCE1_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1TRG1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_TRIGGER_SOURCE2_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1TRG1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_TRIGGER_SOURCE3_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1TRG1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _ADCP_CALIBRATION_DATA_VREG(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return &AD1CAL1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _ADCP_AD_DATA0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DATA0_DATA_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ENABLE_CONTROL_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADCEN_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FILTRDLY_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SCAN_TRIG_SRC_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_STRGSRC_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EARLY_INT_ENABLE_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_EIE_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_STOP_IN_IDLE_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADSIDL_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FRACTIONAL_MODE_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FRACT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_DIVIDER_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCDIV_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_SRC_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCSEL_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_LOW_POWER_ENABLE_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_LOWPWR_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_BOOST_VREF_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_BOOST_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLASS23_SH_SAMPLE_TIME_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_SAMC_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_READY_STATUS_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCRDY_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_ADINSEL_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_VOLTAGE_REF_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_VREFSEL_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_RQCONVRT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GLOBAL_SW_TRIGGER_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_GSWTRG_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATE_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_CAL_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_ALT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0ALT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_ALT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1ALT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_ALT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2ALT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_ALT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3ALT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_ALT_INPUT_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4ALT_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH5_MODE_SELECT_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH5MOD_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN0_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN1_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_2_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN2_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_3_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN3_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_4_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN4_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_5_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN5_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_6_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN6_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_7_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN7_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_8_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN8_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_9_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN9_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_10_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN10_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_11_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN11_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_12_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN12_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_13_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN13_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_14_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN14_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_15_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN15_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_16_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN16_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_17_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN17_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_18_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN18_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_19_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN19_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_20_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN20_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_21_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN21_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_22_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN22_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_23_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN23_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_24_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN24_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_25_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN25_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_26_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN26_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_27_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN27_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_28_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN28_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_29_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN29_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_30_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN30_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_31_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN31_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_32_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN32_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_33_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN33_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_34_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN34_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_35_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN35_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_36_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN36_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_37_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN37_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_38_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN38_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_39_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN39_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_40_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN40_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_41_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN41_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_42_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN42_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_43_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN43_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_44_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN44_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS0_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS1_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_2_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS2_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_3_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS3_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_4_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS4_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_5_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS5_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_6_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS6_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_7_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS7_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_8_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS8_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_9_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS9_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_10_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS10_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_11_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS11_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_12_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS12_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_13_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS13_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_14_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS14_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_15_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS15_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_16_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS16_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_17_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS17_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_18_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS18_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_19_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS19_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_20_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS20_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_21_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS21_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_22_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS22_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_23_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS23_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_24_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS24_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_25_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS25_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_26_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS26_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_27_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS27_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_28_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS28_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_29_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS29_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_30_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS30_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_31_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS31_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_32_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS32_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_33_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS33_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_34_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS34_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_35_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS35_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_36_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS36_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_37_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS37_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_38_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS38_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_39_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS39_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_40_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS40_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_41_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS41_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_42_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS42_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_43_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS43_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_44_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS44_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY0_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY1_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_2_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY2_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_3_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY3_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_4_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY4_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_5_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY5_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_6_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY6_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_7_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY7_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_8_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY8_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_9_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY9_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_10_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY10_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_11_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY11_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_12_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY12_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_13_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY13_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_14_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY14_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_15_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY15_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_16_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY16_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_17_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY17_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_18_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY18_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_19_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY19_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_20_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY20_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_21_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY21_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_22_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY22_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_23_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY23_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_24_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY24_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_25_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY25_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_26_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY26_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_27_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY27_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_28_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY28_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_29_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY29_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_30_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY30_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_31_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY31_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_32_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY32_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_33_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY33_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_34_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY34_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_35_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY35_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_36_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY36_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_37_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY37_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_38_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY38_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_39_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY39_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_40_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY40_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_41_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY41_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_42_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY42_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_43_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY43_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_44_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY44_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_LOW1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOLO_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOHI_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_HIGH1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHILO_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHIHI_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEBTWN_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_DETECTED1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPED_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_GLOBAL_INT_ENABLE1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPGIEN_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_ENABLE1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_ENDCMP_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ANALOG_INPUT_ID1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_AINID_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE0_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE1_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_2_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE2_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_3_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE3_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_4_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE4_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_5_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE5_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_6_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE6_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_7_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE7_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_8_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE8_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_9_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE9_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_10_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE10_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_11_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE11_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_12_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE12_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_13_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE13_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_14_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE14_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_15_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE15_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_16_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE16_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_17_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE17_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_18_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE18_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_19_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE19_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_20_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE20_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_21_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE21_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_22_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE22_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_23_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE23_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_24_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE24_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_25_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE25_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_26_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE26_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_27_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE27_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_28_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE28_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_29_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE29_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_30_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE30_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_31_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE31_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_HIGH_LIMIT1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPHI_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_LO_LIMIT1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPLO_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_ENABLE1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFEN_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_OVERSAMPLING1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_OVRSAM_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_GLOBAL_IRQ_ENABLE1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFGIEN_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA_READY1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFRDY_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_CHANNEL_ID1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_CHNLID_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_FLTRDATA_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE0_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC0_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE1_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC1_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE2_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC2_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE3_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC3_MASK;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATION_DATA_MASK(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return (SFR_DATA)-1;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_AD_DATA0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DATA0_DATA_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ENABLE_CONTROL_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADCEN_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FILTRDLY_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SCAN_TRIG_SRC_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_STRGSRC_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EARLY_INT_ENABLE_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_EIE_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_STOP_IN_IDLE_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADSIDL_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FRACTIONAL_MODE_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FRACT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_DIVIDER_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCDIV_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_SRC_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCSEL_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_LOW_POWER_ENABLE_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_LOWPWR_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_BOOST_VREF_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_BOOST_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLASS23_SH_SAMPLE_TIME_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_SAMC_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_READY_STATUS_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCRDY_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_ADINSEL_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_VOLTAGE_REF_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_VREFSEL_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_RQCONVRT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GLOBAL_SW_TRIGGER_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_GSWTRG_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATE_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_CAL_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_ALT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0ALT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_ALT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1ALT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_ALT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2ALT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_ALT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3ALT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_ALT_INPUT_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4ALT_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH5_MODE_SELECT_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH5MOD_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN0_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN1_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_2_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN2_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_3_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN3_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_4_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN4_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_5_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN5_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_6_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN6_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_7_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN7_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_8_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN8_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_9_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN9_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_10_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN10_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_11_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN11_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_12_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN12_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_13_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN13_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_14_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN14_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_15_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN15_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_16_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN16_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_17_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN17_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_18_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN18_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_19_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN19_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_20_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN20_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_21_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN21_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_22_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN22_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_23_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN23_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_24_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN24_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_25_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN25_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_26_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN26_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_27_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN27_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_28_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN28_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_29_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN29_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_30_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN30_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_31_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN31_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_32_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN32_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_33_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN33_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_34_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN34_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_35_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN35_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_36_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN36_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_37_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN37_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_38_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN38_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_39_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN39_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_40_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN40_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_41_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN41_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_42_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN42_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_43_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN43_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_44_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN44_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS0_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS1_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_2_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS2_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_3_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS3_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_4_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS4_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_5_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS5_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_6_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS6_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_7_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS7_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_8_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS8_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_9_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS9_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_10_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS10_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_11_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS11_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_12_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS12_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_13_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS13_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_14_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS14_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_15_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS15_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_16_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS16_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_17_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS17_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_18_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS18_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_19_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS19_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_20_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS20_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_21_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS21_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_22_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS22_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_23_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS23_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_24_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS24_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_25_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS25_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_26_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS26_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_27_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS27_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_28_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS28_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_29_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS29_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_30_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS30_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_31_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS31_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_32_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS32_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_33_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS33_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_34_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS34_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_35_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS35_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_36_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS36_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_37_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS37_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_38_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS38_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_39_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS39_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_40_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS40_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_41_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS41_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_42_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS42_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_43_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS43_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_44_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS44_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY0_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY1_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_2_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY2_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_3_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY3_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_4_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY4_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_5_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY5_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_6_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY6_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_7_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY7_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_8_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY8_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_9_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY9_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_10_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY10_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_11_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY11_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_12_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY12_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_13_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY13_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_14_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY14_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_15_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY15_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_16_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY16_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_17_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY17_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_18_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY18_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_19_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY19_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_20_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY20_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_21_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY21_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_22_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY22_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_23_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY23_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_24_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY24_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_25_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY25_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_26_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY26_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_27_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY27_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_28_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY28_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_29_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY29_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_30_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY30_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_31_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY31_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_32_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY32_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_33_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY33_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_34_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY34_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_35_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY35_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_36_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY36_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_37_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY37_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_38_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY38_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_39_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY39_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_40_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY40_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_41_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY41_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_42_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY42_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_43_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY43_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_44_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY44_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_LOW1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOLO_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOHI_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_HIGH1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHILO_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHIHI_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEBTWN_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_DETECTED1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPED_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_GLOBAL_INT_ENABLE1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPGIEN_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_ENABLE1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_ENDCMP_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ANALOG_INPUT_ID1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_AINID_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE0_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE1_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_2_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE2_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_3_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE3_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_4_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE4_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_5_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE5_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_6_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE6_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_7_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE7_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_8_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE8_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_9_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE9_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_10_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE10_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_11_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE11_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_12_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE12_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_13_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE13_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_14_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE14_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_15_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE15_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_16_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE16_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_17_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE17_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_18_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE18_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_19_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE19_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_20_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE20_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_21_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE21_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_22_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE22_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_23_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE23_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_24_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE24_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_25_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE25_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_26_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE26_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_27_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE27_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_28_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE28_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_29_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE29_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_30_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE30_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_31_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE31_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_HIGH_LIMIT1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPHI_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_LO_LIMIT1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPLO_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_ENABLE1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFEN_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_OVERSAMPLING1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_OVRSAM_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_GLOBAL_IRQ_ENABLE1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFGIEN_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA_READY1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFRDY_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_CHANNEL_ID1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_CHNLID_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_FLTRDATA_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE0_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC0_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE1_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC1_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE2_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC2_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE3_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC3_POSITION;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATION_DATA_POS(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return (SFR_DATA)0;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_AD_DATA0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DATA0_DATA_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ENABLE_CONTROL_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADCEN_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_OVERSAMP_DIG_FLTR_SAMP_TIME_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FILTRDLY_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SCAN_TRIG_SRC_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_STRGSRC_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EARLY_INT_ENABLE_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_EIE_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_STOP_IN_IDLE_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_ADSIDL_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FRACTIONAL_MODE_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON1_FRACT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_DIVIDER_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCDIV_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLOCK_SRC_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCSEL_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_LOW_POWER_ENABLE_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_LOWPWR_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_BOOST_VREF_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_BOOST_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CLASS23_SH_SAMPLE_TIME_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_SAMC_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_READY_STATUS_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON2_ADCRDY_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_ADINSEL_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_VOLTAGE_REF_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_VREFSEL_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_REQ_CNVRT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_RQCONVRT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GLOBAL_SW_TRIGGER_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_GSWTRG_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATE_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CON3_CAL_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_ALT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0ALT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_ALT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1ALT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_ALT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2ALT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_ALT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3ALT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_ALT_INPUT_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4ALT_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH0_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH0MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH1_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH1MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH2_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH2MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH3_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH3MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH4_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH4MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_SH5_MODE_SELECT_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1IMOD_SH5MOD_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN0_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN1_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_2_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN2_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_3_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN3_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_4_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN4_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_5_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN5_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_6_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN6_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_7_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN7_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_8_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN8_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_9_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN9_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_10_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN10_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_11_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN11_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_12_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN12_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_13_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN13_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_14_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN14_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_15_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN15_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_16_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN16_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_17_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN17_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_18_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN18_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_19_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN19_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_20_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN20_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_21_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN21_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_22_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN22_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_23_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN23_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_24_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN24_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_25_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN25_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_26_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN26_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_27_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN27_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_28_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN28_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_29_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN29_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_30_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN30_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_31_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN1_AGIEN31_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_32_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN32_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_33_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN33_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_34_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN34_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_35_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN35_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_36_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN36_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_37_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN37_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_38_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN38_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_39_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN39_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_40_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN40_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_41_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN41_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_42_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN42_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_43_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN43_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_GROUP_INT_ENABLE_44_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1GIRQEN2_AGIEN44_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS0_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS1_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_2_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS2_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_3_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS3_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_4_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS4_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_5_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS5_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_6_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS6_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_7_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS7_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_8_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS8_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_9_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS9_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_10_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS10_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_11_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS11_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_12_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS12_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_13_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS13_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_14_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS14_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_15_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS15_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_16_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS16_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_17_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS17_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_18_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS18_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_19_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS19_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_20_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS20_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_21_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS21_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_22_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS22_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_23_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS23_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_24_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS24_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_25_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS25_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_26_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS26_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_27_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS27_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_28_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS28_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_29_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS29_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_30_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS30_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_31_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS1_CSS31_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_32_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS32_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_33_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS33_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_34_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS34_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_35_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS35_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_36_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS36_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_37_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS37_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_38_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS38_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_39_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS39_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_40_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS40_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_41_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS41_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_42_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS42_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_43_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS43_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CHANNEL_SCAN_ENABLE_44_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CSS2_CSS44_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY0_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY1_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_2_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY2_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_3_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY3_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_4_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY4_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_5_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY5_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_6_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY6_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_7_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY7_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_8_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY8_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_9_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY9_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_10_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY10_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_11_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY11_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_12_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY12_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_13_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY13_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_14_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY14_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_15_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY15_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_16_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY16_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_17_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY17_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_18_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY18_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_19_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY19_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_20_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY20_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_21_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY21_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_22_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY22_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_23_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY23_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_24_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY24_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_25_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY25_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_26_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY26_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_27_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY27_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_28_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY28_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_29_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY29_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_30_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY30_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_31_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT1_ARDY31_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_32_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY32_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_33_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY33_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_34_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY34_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_35_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY35_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_36_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY36_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_37_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY37_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_38_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY38_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_39_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY39_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_40_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY40_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_41_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY41_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_42_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY42_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_43_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY43_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DATA_READY_44_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1DSTAT2_ARDY44_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_LOW1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOLO_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IELOHI_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_LESS_THAN_HIGH1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHILO_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEHIHI_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_IEBTWN_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_EVENT_DETECTED1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPED_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_GLOBAL_INT_ENABLE1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_DCMPGIEN_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_ENABLE1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_ENDCMP_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_ANALOG_INPUT_ID1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPCON1_AINID_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE0_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE1_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_2_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE2_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_3_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE3_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_4_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE4_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_5_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE5_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_6_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE6_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_7_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE7_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_8_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE8_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_9_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE9_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_10_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE10_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_11_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE11_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_12_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE12_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_13_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE13_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_14_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE14_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_15_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE15_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_16_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE16_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_17_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE17_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_18_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE18_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_19_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE19_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_20_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE20_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_21_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE21_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_22_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE22_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_23_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE23_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_24_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE24_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_25_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE25_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_26_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE26_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_27_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE27_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_28_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE28_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_29_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE29_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_30_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE30_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CMP_ENABLE_31_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMPEN1_CMPE31_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_HIGH_LIMIT1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPHI_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_DCMP_LO_LIMIT1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1CMP1_ADCMPLO_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_ENABLE1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFEN_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_OVERSAMPLING1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_OVRSAM_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_GLOBAL_IRQ_ENABLE1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFGIEN_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA_READY1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_AFRDY_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_CHANNEL_ID1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_CHNLID_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_FILTER_DATA1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1FLTR1_FLTRDATA_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE0_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC0_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE1_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC1_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE2_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC2_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_TRIGGER_SOURCE3_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return _AD1TRG1_TRGSRC3_LENGTH;
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _ADCP_CALIBRATION_DATA_LEN(ADCP_MODULE_ID i)
{
    switch (i) {
        case ADCP_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/adcp_EnableControl_Default.h"
#include "../templates/adcp_Calibration_Default.h"
#include "../templates/adcp_Configuration_Default.h"
#include "../templates/adcp_LowPowerControl_Default.h"
#include "../templates/adcp_ReadyStatus_Default.h"
#include "../templates/adcp_InputSelect_Default.h"
#include "../templates/adcp_ModeSelect_Default.h"
#include "../templates/adcp_ChannelScan_Default.h"
#include "../templates/adcp_Triggering_Default.h"
#include "../templates/adcp_ConversionResults_Default.h"
#include "../templates/adcp_DigitalComparator_Default.h"
#include "../templates/adcp_OsampDigitalFilter_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_ADCP_Enable(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_Enable_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_Disable(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_Disable_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsEnableControl(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsEnableControl_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_CalibrationStart(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_CalibrationStart_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsCalibration(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsCalibration_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_Configure(ADCP_MODULE_ID index, ADCP_VREF_SOURCE voltageRefSelect, bool boostVref, bool fractionalOutputOn, bool stopInIdle, ADCP_CLOCK_SOURCE adcClockSource, int8_t adcClockDivider, int8_t oversampleDigFilterSamTime, int8_t earlyIntEnable, int8_t class2and3SampleTime)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_Configure_Default(index, voltageRefSelect, boostVref, fractionalOutputOn, stopInIdle, adcClockSource, adcClockDivider, oversampleDigFilterSamTime, earlyIntEnable, class2and3SampleTime);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsConfiguration(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsConfiguration_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_LowPowerStateEnter(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_LowPowerStateEnter_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_LowPowerStateExit(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_LowPowerStateExit_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_LowPowerStateGet(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_LowPowerStateGet_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_ADCP_ExistsLowPowerControl(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsLowPowerControl_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_ADCP_ModuleIsReady(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ModuleIsReady_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_ADCP_ExistsReadyStatus(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsReadyStatus_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_AlternateInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_AlternateInputSelect_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_DefaultInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_DefaultInputSelect_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsInputSelect(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsInputSelect_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_SHModeSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id, ADCP_SH_MODE mode)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_SHModeSelect_Default(index, id, mode);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsModeSelect(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsModeSelect_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_ChannelScanConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable, ADCP_SCAN_TRG_SRC triggerSource)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_ChannelScanConfigure_Default(index, lowEnable, highEnable, triggerSource);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsChannelScan(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsChannelScan_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_Class12TriggerConfigure(ADCP_MODULE_ID index, ADCP_CLASS12_INPUT_ID inputId, ADCP_TRG_SRC triggerSource)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_Class12TriggerConfigure_Default(index, inputId, triggerSource);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_GlobalSoftwareTrigger(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_GlobalSoftwareTrigger_Default(index);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_IndividualTrigger(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_IndividualTrigger_Default(index, inputId);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsTriggering(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsTriggering_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API AN_READY PLIB_ADCP_ResultReady(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ResultReady_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (AN_READY)0;
    }
}

INLINE_API int32_t PLIB_ADCP_ResultGet(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ResultGet_Default(index, inputId);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int32_t)0;
    }
}

INLINE_API void PLIB_ADCP_ResultReadyGrpIntConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_ResultReadyGrpIntConfigure_Default(index, lowEnable, highEnable);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_ExistsConversionResults(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsConversionResults_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_DigCmpConfig(ADCP_MODULE_ID index, ADCP_DCMP_ID id, bool globalIntEnable, bool inBetweenOrEqual, bool greaterEqualHi, bool lessThanHi, bool greaterEqualLo, bool lessThanLo, uint32_t inputEnable, int32_t hiLimit, int32_t loLimit)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_DigCmpConfig_Default(index, id, globalIntEnable, inBetweenOrEqual, greaterEqualHi, lessThanHi, greaterEqualLo, lessThanLo, inputEnable, hiLimit, loLimit);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_DigCmpEnable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_DigCmpEnable_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_DigCmpDisable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_DigCmpDisable_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API int16_t PLIB_ADCP_DigCmpAIdGet(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_DigCmpAIdGet_Default(index, id);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int16_t)0;
    }
}

INLINE_API bool PLIB_ADCP_ExistsDigCmp(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsDigCmp_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_ADCP_OsampDigFilterConfig(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id, ADCP_INPUT_ID inputId, ADCP_ODFLTR_SAMPLE_RATIO oversampleRatio, bool globalIntEnable)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_OsampDigFilterConfig_Default(index, id, inputId, oversampleRatio, globalIntEnable);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_OsampDigFilterEnable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_OsampDigFilterEnable_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_ADCP_OsampDigFilterDisable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            ADCP_OsampDigFilterDisable_Default(index, id);
            break;
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_ADCP_OsampDigFilterDataRdy(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_OsampDigFilterDataRdy_Default(index, id);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int16_t PLIB_ADCP_OsampDigFilterDataGet(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_OsampDigFilterDataGet_Default(index, id);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int16_t)0;
    }
}

INLINE_API bool PLIB_ADCP_ExistsOsampDigFilter(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_ID_1 :
            return ADCP_ExistsOsampDigFilter_Default(index);
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
