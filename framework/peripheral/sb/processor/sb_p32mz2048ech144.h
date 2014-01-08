/* Created by plibgen $Revision: 1.29 $ */

#ifndef _SB_P32MZ2048ECH144_H
#define _SB_P32MZ2048ECH144_H

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

    SB_ID_0 = 0,
    SB_NUMBER_OF_MODULES

} SB_MODULE_ID;

typedef enum {

    PLIB_SB_INIT_ID_CPU_LRS = 0x1,
    PLIB_SB_INIT_ID_CPU_HI = 0x02,
    PLIB_SB_INIT_ID_DMA1_RD_LRS = 0x03,
    PLIB_SB_INIT_ID_DMA1_RD_HI = 0x04,
    PLIB_SB_INIT_ID_DMA1_WR_LRS = 0x05,
    PLIB_SB_INIT_ID_DMA1_WR_HI = 0x06,
    PLIB_SB_INIT_ID_USB1 = 0x07,
    PLIB_SB_INIT_ID_ETH1_RD = 0x08,
    PLIB_SB_INIT_ID_ETH1_WR = 0x09,
    PLIB_SB_INIT_ID_CAN1 = 0x0A,
    PLIB_SB_INIT_ID_CAN2 = 0x0B,
    PLIB_SB_INIT_ID_SQI1 = 0x0C,
    PLIB_SB_INIT_ID_FLASH_CTL = 0x0D

} PLIB_SB_INIT_ID;

typedef enum {

    PLIB_SB_PG_INITIATOR_CPU = 0x0,
    PLIB_SB_PG_INITIATOR_DMA1 = 0x04,
    PLIB_SB_PG_INITIATOR_USB1 = 0x08,
    PLIB_SB_PG_INITIATOR_CAN1 = 0x0C,
    PLIB_SB_PG_INITIATOR_CAN2 = 0x0E,
    PLIB_SB_PG_INITIATOR_ETH1 = 0x10,
    PLIB_SB_PG_INITIATOR_SQI1 = 0x14,
    PLIB_SB_PG_INITIATOR_FLASH_CTL = 0x16

} PLIB_SB_PG_INITIATOR;

typedef enum {

    PLIB_SB_TGT_ID_T0 = 0x0,
    PLIB_SB_TGT_ID_T1 = 0x01,
    PLIB_SB_TGT_ID_T2 = 0x02,
    PLIB_SB_TGT_ID_T3 = 0x03,
    PLIB_SB_TGT_ID_T4 = 0x04,
    PLIB_SB_TGT_ID_T5 = 0x05,
    PLIB_SB_TGT_ID_T6 = 0x06,
    PLIB_SB_TGT_ID_T7 = 0x07,
    PLIB_SB_TGT_ID_T8 = 0x08,
    PLIB_SB_TGT_ID_T9 = 0x09,
    PLIB_SB_TGT_ID_T10 = 0x0A,
    PLIB_SB_TGT_ID_T11 = 0x0B,
    PLIB_SB_TGT_ID_T12 = 0x0C,
    PLIB_SB_TGT_ID_T13 = 0x0D

} PLIB_SB_TGT_ID;

typedef enum {

    PLIB_SB_T0_REGION_0 = 0x0000,
    PLIB_SB_T0_REGION_1 = 0x0001,
    PLIB_SB_T1_REGION_0 = 0x0100,
    PLIB_SB_T1_REGION_2 = 0x0102,
    PLIB_SB_T1_REGION_3 = 0x0103,
    PLIB_SB_T1_REGION_4 = 0x0104,
    PLIB_SB_T1_REGION_5 = 0x0105,
    PLIB_SB_T1_REGION_6 = 0x0106,
    PLIB_SB_T1_REGION_7 = 0x0107,
    PLIB_SB_T1_REGION_8 = 0x0109,
    PLIB_SB_T2_REGION_0 = 0x0200,
    PLIB_SB_T2_REGION_1 = 0x0201,
    PLIB_SB_T2_REGION_2 = 0x0202,
    PLIB_SB_T3_REGION_0 = 0x0300,
    PLIB_SB_T3_REGION_1 = 0x0301,
    PLIB_SB_T3_REGION_2 = 0x0302,
    PLIB_SB_T4_REGION_0 = 0x0400,
    PLIB_SB_T4_REGION_2 = 0x0402,
    PLIB_SB_T5_REGION_0 = 0x0500,
    PLIB_SB_T5_REGION_1 = 0x0501,
    PLIB_SB_T5_REGION_2 = 0x0502,
    PLIB_SB_T6_REGION_0 = 0x0600,
    PLIB_SB_T6_REGION_1 = 0x0601,
    PLIB_SB_T7_REGION_0 = 0x0700,
    PLIB_SB_T7_REGION_1 = 0x0701,
    PLIB_SB_T8_REGION_0 = 0x0800,
    PLIB_SB_T8_REGION_1 = 0x0801,
    PLIB_SB_T9_REGION_0 = 0x0900,
    PLIB_SB_T9_REGION_1 = 0x0901,
    PLIB_SB_T10_REGION_0 = 0x0A00,
    PLIB_SB_T11_REGION_0 = 0x0B00,
    PLIB_SB_T11_REGION_1 = 0x0B01,
    PLIB_SB_T12_REGION_0 = 0x0C00,
    PLIB_SB_T13_REGION_0 = 0x0D00

} PLIB_SB_TGT_REGION;

typedef enum {

    PLIB_SB_ERROR_NONE = 0x0,
    PLIB_SB_ERROR_PGV = 0x01

} PLIB_SB_ERROR;

typedef enum {

    REGION_PG_0 = 0x00,
    REGION_PG_1 = 0x02,
    REGION_PG_2 = 0x04,
    REGION_PG_3 = 0x08

} PLIB_SB_REGION_PG;

typedef enum {

    PLIB_SB_INIT_PG_0 = 0x00,
    PLIB_SB_INIT_PG_1 = 0x01,
    PLIB_SB_INIT_PG_2 = 0x02,
    PLIB_SB_INIT_PG_3 = 0x03

} PLIB_SB_INIT_PG;

typedef enum {

    PRIORITY_LRS = 0x00,
    PRIORITY_HI = 0x01

} PLIB_SB_ARB_POLICY;

typedef enum {

    PLIB_SB_OCP_CMD_IDLE = 0x00,
    PLIB_SB_OCP_CMD_WRITE = 0x01,
    PLIB_SB_OCP_CMD_READ = 0x02,
    PLIB_SB_OCP_CMD_READEX = 0x03,
    PLIB_SB_OCP_CMD_WRITE_NON_POST = 0x05,
    PLIB_SB_OCP_CMD_BROADCAST = 0x07

} PLIB_SB_OCP_CMD_CODE;

INLINE SFR_TYPE* _SB_T0_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_PGV_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBFLAG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T0_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT0WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R2_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R3_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD3;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R4_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD4;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R5_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD5;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R6_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD6;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R7_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD7;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1REG8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T1_R8_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT1RD8;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T2_R2_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT2WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T3_R2_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT3WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T4_R2_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT4WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5REG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5RD2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T5_R2_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT5WR2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T6_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT6WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T7_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT7WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T8_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT8WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T9_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT9WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T10_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT10WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11REG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11RD1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T11_R1_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT11WR1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T12_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT12WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_MULTI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_CODE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_INITID_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_REGION_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_CMD_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_GRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ELOG2;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_ERRP_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ECON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_ECLRS_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ECLRS;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_ECLRM_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13ECLRM;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_BASE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_SIZE_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13REG0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_RD_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_RD_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_RD_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_RD_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13RD0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_WR_GRP0_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_WR_GRP1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_WR_GRP2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_T13_R0_WR_GRP3_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &SBT13WR0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_CPU_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_DMA_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_USB_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_CAN1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_CAN2_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_ETH_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_SQI1_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGPG_FC_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGPG;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGCON_DMAPRI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGCON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SB_CFGCON_EXLPRI_VREG(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return &CFGCON;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _SB_T0_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T0PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T1PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T2PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T3PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T4PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T5PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T6PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T7PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T8PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T9PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T10PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T11PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T12PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_PGV_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T13PGV_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ECON_ERRP_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_MULTI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_MULTI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CODE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CODE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_INITID_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_INITID_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_REGION_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_REGION_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CMD_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CMD_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_GRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ERRP_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRS_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRM_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)-1;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_BASE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_BASE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_SIZE_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_SIZE_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP0_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP0_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP1_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP2_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP3_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP3_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CPU_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CPUPG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_DMA_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_DMAPG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_USB_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_USBPG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN1PG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN2_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN2PG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_ETH_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_ETHPG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_SQI1_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_SQI1PG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_FC_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_FCPG_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_DMAPRI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_DMAPRI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_EXLPRI_MASK(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_CPUPRI_MASK;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T0PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T1PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T2PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T3PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T4PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T5PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T6PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T7PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T8PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T9PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T10PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T11PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T12PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_PGV_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T13PGV_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ECON_ERRP_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_MULTI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_MULTI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CODE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CODE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_INITID_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_INITID_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_REGION_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_REGION_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CMD_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CMD_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_GRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ERRP_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRS_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRM_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)0;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_BASE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_BASE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_SIZE_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_SIZE_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP0_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP0_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP1_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP2_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP3_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP3_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CPU_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CPUPG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_DMA_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_DMAPG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_USB_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_USBPG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN1PG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN2_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN2PG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_ETH_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_ETHPG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_SQI1_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_SQI1PG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_FC_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_FCPG_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_DMAPRI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_DMAPRI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_EXLPRI_POS(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_CPUPRI_POSITION;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T0PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T1PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T2PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T3PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T4PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T5PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T6PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T7PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T8PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T9PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T10PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T11PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T12PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_PGV_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBFLAG_T13PGV_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T0_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT0WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1ECON_ERRP_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG2_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R2_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1WR2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG3_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R3_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD3_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG4_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R4_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD4_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG5_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R5_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD5_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG6_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R6_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD6_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG7_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R7_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD7_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1REG8_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T1_R8_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT1RD8_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2REG2_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2RD2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T2_R2_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT2WR2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3REG2_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3RD2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T3_R2_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT3WR2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4REG2_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4RD2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T4_R2_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT4WR2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5REG2_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5RD2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T5_R2_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT5WR2_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T6_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT6WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T7_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT7WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T8_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT8WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T9_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT9WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T10_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT10WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11REG1_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11RD1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T11_R1_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT11WR1_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T12_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT12WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_MULTI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_MULTI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CODE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CODE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_INITID_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_INITID_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_REGION_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_REGION_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_CMD_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13ELOG1_CMD_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_GRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ERRP_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRS_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_ECLRM_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_BASE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_BASE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_SIZE_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13REG0_SIZE_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_RD_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13RD0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP0_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP0_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP1_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP2_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_T13_R0_WR_GRP3_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _SBT13WR0_GROUP3_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CPU_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CPUPG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_DMA_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_DMAPG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_USB_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_USBPG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN1PG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_CAN2_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_CAN2PG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_ETH_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_ETHPG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_SQI1_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_SQI1PG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGPG_FC_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGPG_FCPG_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_DMAPRI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_DMAPRI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SB_CFGCON_EXLPRI_LEN(SB_MODULE_ID i)
{
    switch (i) {
        case SB_ID_0 :
            return _CFGCON_CPUPRI_LENGTH;
        case SB_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/sb_PGVErrStatus_Default.h"
#include "../templates/sb_PGVErrClear_Default.h"
#include "../templates/sb_PGVErrInitID_Default.h"
#include "../templates/sb_PGVErrRegion_Default.h"
#include "../templates/sb_PGVErrCmdCode_Default.h"
#include "../templates/sb_PGVErrPG_Default.h"
#include "../templates/sb_PGVErrRptPri_Default.h"
#include "../templates/sb_PGVErrClrSingle_Default.h"
#include "../templates/sb_PGVErrClrMulti_Default.h"
#include "../templates/sb_PGRegAddr_Default.h"
#include "../templates/sb_PGRegSize_Default.h"
#include "../templates/sb_PGRegRdPerm_Default.h"
#include "../templates/sb_PGRegWrPerm_Default.h"
#include "../templates/sb_InitPermGrp_Default.h"
#include "../templates/sb_CPUPriority_Default.h"
#include "../templates/sb_DMAPriority_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_SB_ExistsPGVErrStatus(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrStatus_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_PGVErrorStatus(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorStatus_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrClear(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrClear_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_PGVErrorMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorMulti_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_ERROR PLIB_SB_PGVErrorCode(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorCode_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_ERROR)0;
    }
}

INLINE_API void PLIB_SB_PGVErrorLogClearSingle(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGVErrorLogClearSingle_Default(index, target);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SB_PGVErrorLogClearMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGVErrorLogClearMulti_Default(index, target);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrInitID(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrInitID_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_INIT_ID PLIB_SB_PGVErrorInitiatorID(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorInitiatorID_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_INIT_ID)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrRegion(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrRegion_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_SB_PGVErrorRegion(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorRegion_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrCmdCode(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrCmdCode_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_OCP_CMD_CODE PLIB_SB_PGVErrorCommandCode(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorCommandCode_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_OCP_CMD_CODE)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrPG(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrPG_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_SB_PGVErrorPermissionGroup(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorPermissionGroup_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrRptPri(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrRptPri_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_PGVErrorReportPrimaryEnable(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGVErrorReportPrimaryEnable_Default(index, target);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SB_PGVErrorReportPrimaryDisable(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGVErrorReportPrimaryDisable_Default(index, target);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrClrSingle(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrClrSingle_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_PGVErrorClearSingle(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorClearSingle_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGVErrClrMulti(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGVErrClrMulti_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_PGVErrorClearMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGVErrorClearMulti_Default(index, target);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_PGRegionAddrSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, uint32_t phys_addr)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionAddrSet_Default(index, region, phys_addr);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SB_PGRegionAddrGet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGRegionAddrGet_Default(index, region);
        case SB_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGRegAddr(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGRegAddr_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_PGRegionSizeSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, uint32_t size)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionSizeSet_Default(index, region, size);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SB_PGRegionSizeGet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region)
{
    switch (index) {
        case SB_ID_0 :
            return SB_PGRegionSizeGet_Default(index, region);
        case SB_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SB_ExistsPGRegSize(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGRegSize_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_PGRegionReadPermSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG readPerm)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionReadPermSet_Default(index, region, readPerm);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SB_PGRegionReadPermClear(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG readPerm)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionReadPermClear_Default(index, region, readPerm);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsPGRegRdPerm(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGRegRdPerm_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_PGRegionWritePermSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG writePerm)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionWritePermSet_Default(index, region, writePerm);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SB_PGRegionWritePermClear(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG writePerm)
{
    switch (index) {
        case SB_ID_0 :
            SB_PGRegionWritePermClear_Default(index, region, writePerm);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsPGRegWrPerm(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsPGRegWrPerm_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SB_ExistsInitPermGrp(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsInitPermGrp_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_InitPermGrpSet(SB_MODULE_ID index, PLIB_SB_PG_INITIATOR initiator, PLIB_SB_INIT_PG pg)
{
    switch (index) {
        case SB_ID_0 :
            SB_InitPermGrpSet_Default(index, initiator, pg);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsCPUPriority(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsCPUPriority_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_CPUPrioritySet(SB_MODULE_ID index, PLIB_SB_ARB_POLICY priority)
{
    switch (index) {
        case SB_ID_0 :
            SB_CPUPrioritySet_Default(index, priority);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SB_ExistsDMAPriority(SB_MODULE_ID index)
{
    switch (index) {
        case SB_ID_0 :
            return SB_ExistsDMAPriority_Default(index);
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SB_DMAPrioritySet(SB_MODULE_ID index, PLIB_SB_ARB_POLICY priority)
{
    switch (index) {
        case SB_ID_0 :
            SB_DMAPrioritySet_Default(index, priority);
            break;
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
