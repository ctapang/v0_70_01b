/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGRegWrPerm_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGRegWrPerm
    and its Variant : Default
    For following APIs :
        PLIB_SB_PGRegionWritePermSet
        PLIB_SB_PGRegionWritePermClear
        PLIB_SB_ExistsPGRegWrPerm

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/

//DOM-IGNORE-END

#ifndef _SB_PGREGWRPERM_DEFAULT_H
#define _SB_PGREGWRPERM_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_R0_WR_GRP0_VREG(index)
    _SB_T0_R0_WR_GRP1_VREG(index)
    _SB_T0_R0_WR_GRP2_VREG(index)
    _SB_T0_R0_WR_GRP3_VREG(index)
    _SB_T0_R1_WR_GRP0_VREG(index)
    _SB_T0_R1_WR_GRP1_VREG(index)
    _SB_T0_R1_WR_GRP2_VREG(index)
    _SB_T0_R1_WR_GRP3_VREG(index)
    _SB_T1_R2_WR_GRP0_VREG(index)
    _SB_T1_R2_WR_GRP1_VREG(index)
    _SB_T1_R2_WR_GRP2_VREG(index)
    _SB_T1_R2_WR_GRP3_VREG(index)
    _SB_T2_R0_WR_GRP0_VREG(index)
    _SB_T2_R0_WR_GRP1_VREG(index)
    _SB_T2_R0_WR_GRP2_VREG(index)
    _SB_T2_R0_WR_GRP3_VREG(index)
    _SB_T2_R1_WR_GRP0_VREG(index)
    _SB_T2_R1_WR_GRP1_VREG(index)
    _SB_T2_R1_WR_GRP2_VREG(index)
    _SB_T2_R1_WR_GRP3_VREG(index)
    _SB_T2_R2_WR_GRP0_VREG(index)
    _SB_T2_R2_WR_GRP1_VREG(index)
    _SB_T2_R2_WR_GRP2_VREG(index)
    _SB_T2_R2_WR_GRP3_VREG(index)
    _SB_T3_R0_WR_GRP0_VREG(index)
    _SB_T3_R0_WR_GRP1_VREG(index)
    _SB_T3_R0_WR_GRP2_VREG(index)
    _SB_T3_R0_WR_GRP3_VREG(index)
    _SB_T3_R1_WR_GRP0_VREG(index)
    _SB_T3_R1_WR_GRP1_VREG(index)
    _SB_T3_R1_WR_GRP2_VREG(index)
    _SB_T3_R1_WR_GRP3_VREG(index)
    _SB_T3_R2_WR_GRP0_VREG(index)
    _SB_T3_R2_WR_GRP1_VREG(index)
    _SB_T3_R2_WR_GRP2_VREG(index)
    _SB_T3_R2_WR_GRP3_VREG(index)
    _SB_T4_R0_WR_GRP0_VREG(index)
    _SB_T4_R0_WR_GRP1_VREG(index)
    _SB_T4_R0_WR_GRP2_VREG(index)
    _SB_T4_R0_WR_GRP3_VREG(index)
    _SB_T4_R2_WR_GRP0_VREG(index)
    _SB_T4_R2_WR_GRP1_VREG(index)
    _SB_T4_R2_WR_GRP2_VREG(index)
    _SB_T4_R2_WR_GRP3_VREG(index)
    _SB_T5_R0_WR_GRP0_VREG(index)
    _SB_T5_R0_WR_GRP1_VREG(index)
    _SB_T5_R0_WR_GRP2_VREG(index)
    _SB_T5_R0_WR_GRP3_VREG(index)
    _SB_T5_R1_WR_GRP0_VREG(index)
    _SB_T5_R1_WR_GRP1_VREG(index)
    _SB_T5_R1_WR_GRP2_VREG(index)
    _SB_T5_R1_WR_GRP3_VREG(index)
    _SB_T5_R2_WR_GRP0_VREG(index)
    _SB_T5_R2_WR_GRP1_VREG(index)
    _SB_T5_R2_WR_GRP2_VREG(index)
    _SB_T5_R2_WR_GRP3_VREG(index)
    _SB_T6_R0_WR_GRP0_VREG(index)
    _SB_T6_R0_WR_GRP1_VREG(index)
    _SB_T6_R0_WR_GRP2_VREG(index)
    _SB_T6_R0_WR_GRP3_VREG(index)
    _SB_T6_R1_WR_GRP0_VREG(index)
    _SB_T6_R1_WR_GRP1_VREG(index)
    _SB_T6_R1_WR_GRP2_VREG(index)
    _SB_T6_R1_WR_GRP3_VREG(index)
    _SB_T7_R0_WR_GRP0_VREG(index)
    _SB_T7_R0_WR_GRP1_VREG(index)
    _SB_T7_R0_WR_GRP2_VREG(index)
    _SB_T7_R0_WR_GRP3_VREG(index)
    _SB_T7_R1_WR_GRP0_VREG(index)
    _SB_T7_R1_WR_GRP1_VREG(index)
    _SB_T7_R1_WR_GRP2_VREG(index)
    _SB_T7_R1_WR_GRP3_VREG(index)
    _SB_T8_R0_WR_GRP0_VREG(index)
    _SB_T8_R0_WR_GRP1_VREG(index)
    _SB_T8_R0_WR_GRP2_VREG(index)
    _SB_T8_R0_WR_GRP3_VREG(index)
    _SB_T8_R1_WR_GRP0_VREG(index)
    _SB_T8_R1_WR_GRP1_VREG(index)
    _SB_T8_R1_WR_GRP2_VREG(index)
    _SB_T8_R1_WR_GRP3_VREG(index)
    _SB_T9_R0_WR_GRP0_VREG(index)
    _SB_T9_R0_WR_GRP1_VREG(index)
    _SB_T9_R0_WR_GRP2_VREG(index)
    _SB_T9_R0_WR_GRP3_VREG(index)
    _SB_T9_R1_WR_GRP0_VREG(index)
    _SB_T9_R1_WR_GRP1_VREG(index)
    _SB_T9_R1_WR_GRP2_VREG(index)
    _SB_T9_R1_WR_GRP3_VREG(index)
    _SB_T10_R0_WR_GRP0_VREG(index)
    _SB_T10_R0_WR_GRP1_VREG(index)
    _SB_T10_R0_WR_GRP2_VREG(index)
    _SB_T10_R0_WR_GRP3_VREG(index)
    _SB_T11_R0_WR_GRP0_VREG(index)
    _SB_T11_R0_WR_GRP1_VREG(index)
    _SB_T11_R0_WR_GRP2_VREG(index)
    _SB_T11_R0_WR_GRP3_VREG(index)
    _SB_T11_R1_WR_GRP0_VREG(index)
    _SB_T11_R1_WR_GRP1_VREG(index)
    _SB_T11_R1_WR_GRP2_VREG(index)
    _SB_T11_R1_WR_GRP3_VREG(index)
    _SB_T12_R0_WR_GRP0_VREG(index)
    _SB_T12_R0_WR_GRP1_VREG(index)
    _SB_T12_R0_WR_GRP2_VREG(index)
    _SB_T12_R0_WR_GRP3_VREG(index)
    _SB_T13_R0_WR_GRP0_VREG(index)
    _SB_T13_R0_WR_GRP1_VREG(index)
    _SB_T13_R0_WR_GRP2_VREG(index)
    _SB_T13_R0_WR_GRP3_VREG(index)

  MASKs: 
    _SB_T0_R0_WR_GRP0_MASK(index)
    _SB_T0_R0_WR_GRP1_MASK(index)
    _SB_T0_R0_WR_GRP2_MASK(index)
    _SB_T0_R0_WR_GRP3_MASK(index)
    _SB_T0_R1_WR_GRP0_MASK(index)
    _SB_T0_R1_WR_GRP1_MASK(index)
    _SB_T0_R1_WR_GRP2_MASK(index)
    _SB_T0_R1_WR_GRP3_MASK(index)
    _SB_T1_R2_WR_GRP0_MASK(index)
    _SB_T1_R2_WR_GRP1_MASK(index)
    _SB_T1_R2_WR_GRP2_MASK(index)
    _SB_T1_R2_WR_GRP3_MASK(index)
    _SB_T2_R0_WR_GRP0_MASK(index)
    _SB_T2_R0_WR_GRP1_MASK(index)
    _SB_T2_R0_WR_GRP2_MASK(index)
    _SB_T2_R0_WR_GRP3_MASK(index)
    _SB_T2_R1_WR_GRP0_MASK(index)
    _SB_T2_R1_WR_GRP1_MASK(index)
    _SB_T2_R1_WR_GRP2_MASK(index)
    _SB_T2_R1_WR_GRP3_MASK(index)
    _SB_T2_R2_WR_GRP0_MASK(index)
    _SB_T2_R2_WR_GRP1_MASK(index)
    _SB_T2_R2_WR_GRP2_MASK(index)
    _SB_T2_R2_WR_GRP3_MASK(index)
    _SB_T3_R0_WR_GRP0_MASK(index)
    _SB_T3_R0_WR_GRP1_MASK(index)
    _SB_T3_R0_WR_GRP2_MASK(index)
    _SB_T3_R0_WR_GRP3_MASK(index)
    _SB_T3_R1_WR_GRP0_MASK(index)
    _SB_T3_R1_WR_GRP1_MASK(index)
    _SB_T3_R1_WR_GRP2_MASK(index)
    _SB_T3_R1_WR_GRP3_MASK(index)
    _SB_T3_R2_WR_GRP0_MASK(index)
    _SB_T3_R2_WR_GRP1_MASK(index)
    _SB_T3_R2_WR_GRP2_MASK(index)
    _SB_T3_R2_WR_GRP3_MASK(index)
    _SB_T4_R0_WR_GRP0_MASK(index)
    _SB_T4_R0_WR_GRP1_MASK(index)
    _SB_T4_R0_WR_GRP2_MASK(index)
    _SB_T4_R0_WR_GRP3_MASK(index)
    _SB_T4_R2_WR_GRP0_MASK(index)
    _SB_T4_R2_WR_GRP1_MASK(index)
    _SB_T4_R2_WR_GRP2_MASK(index)
    _SB_T4_R2_WR_GRP3_MASK(index)
    _SB_T5_R0_WR_GRP0_MASK(index)
    _SB_T5_R0_WR_GRP1_MASK(index)
    _SB_T5_R0_WR_GRP2_MASK(index)
    _SB_T5_R0_WR_GRP3_MASK(index)
    _SB_T5_R1_WR_GRP0_MASK(index)
    _SB_T5_R1_WR_GRP1_MASK(index)
    _SB_T5_R1_WR_GRP2_MASK(index)
    _SB_T5_R1_WR_GRP3_MASK(index)
    _SB_T5_R2_WR_GRP0_MASK(index)
    _SB_T5_R2_WR_GRP1_MASK(index)
    _SB_T5_R2_WR_GRP2_MASK(index)
    _SB_T5_R2_WR_GRP3_MASK(index)
    _SB_T6_R0_WR_GRP0_MASK(index)
    _SB_T6_R0_WR_GRP1_MASK(index)
    _SB_T6_R0_WR_GRP2_MASK(index)
    _SB_T6_R0_WR_GRP3_MASK(index)
    _SB_T6_R1_WR_GRP0_MASK(index)
    _SB_T6_R1_WR_GRP1_MASK(index)
    _SB_T6_R1_WR_GRP2_MASK(index)
    _SB_T6_R1_WR_GRP3_MASK(index)
    _SB_T7_R0_WR_GRP0_MASK(index)
    _SB_T7_R0_WR_GRP1_MASK(index)
    _SB_T7_R0_WR_GRP2_MASK(index)
    _SB_T7_R0_WR_GRP3_MASK(index)
    _SB_T7_R1_WR_GRP0_MASK(index)
    _SB_T7_R1_WR_GRP1_MASK(index)
    _SB_T7_R1_WR_GRP2_MASK(index)
    _SB_T7_R1_WR_GRP3_MASK(index)
    _SB_T8_R0_WR_GRP0_MASK(index)
    _SB_T8_R0_WR_GRP1_MASK(index)
    _SB_T8_R0_WR_GRP2_MASK(index)
    _SB_T8_R0_WR_GRP3_MASK(index)
    _SB_T8_R1_WR_GRP0_MASK(index)
    _SB_T8_R1_WR_GRP1_MASK(index)
    _SB_T8_R1_WR_GRP2_MASK(index)
    _SB_T8_R1_WR_GRP3_MASK(index)
    _SB_T9_R0_WR_GRP0_MASK(index)
    _SB_T9_R0_WR_GRP1_MASK(index)
    _SB_T9_R0_WR_GRP2_MASK(index)
    _SB_T9_R0_WR_GRP3_MASK(index)
    _SB_T9_R1_WR_GRP0_MASK(index)
    _SB_T9_R1_WR_GRP1_MASK(index)
    _SB_T9_R1_WR_GRP2_MASK(index)
    _SB_T9_R1_WR_GRP3_MASK(index)
    _SB_T10_R0_WR_GRP0_MASK(index)
    _SB_T10_R0_WR_GRP1_MASK(index)
    _SB_T10_R0_WR_GRP2_MASK(index)
    _SB_T10_R0_WR_GRP3_MASK(index)
    _SB_T11_R0_WR_GRP0_MASK(index)
    _SB_T11_R0_WR_GRP1_MASK(index)
    _SB_T11_R0_WR_GRP2_MASK(index)
    _SB_T11_R0_WR_GRP3_MASK(index)
    _SB_T11_R1_WR_GRP0_MASK(index)
    _SB_T11_R1_WR_GRP1_MASK(index)
    _SB_T11_R1_WR_GRP2_MASK(index)
    _SB_T11_R1_WR_GRP3_MASK(index)
    _SB_T12_R0_WR_GRP0_MASK(index)
    _SB_T12_R0_WR_GRP1_MASK(index)
    _SB_T12_R0_WR_GRP2_MASK(index)
    _SB_T12_R0_WR_GRP3_MASK(index)
    _SB_T13_R0_WR_GRP0_MASK(index)
    _SB_T13_R0_WR_GRP1_MASK(index)
    _SB_T13_R0_WR_GRP2_MASK(index)
    _SB_T13_R0_WR_GRP3_MASK(index)

  POSs: 
    _SB_T0_R0_WR_GRP0_POS(index)
    _SB_T0_R0_WR_GRP1_POS(index)
    _SB_T0_R0_WR_GRP2_POS(index)
    _SB_T0_R0_WR_GRP3_POS(index)
    _SB_T0_R1_WR_GRP0_POS(index)
    _SB_T0_R1_WR_GRP1_POS(index)
    _SB_T0_R1_WR_GRP2_POS(index)
    _SB_T0_R1_WR_GRP3_POS(index)
    _SB_T1_R2_WR_GRP0_POS(index)
    _SB_T1_R2_WR_GRP1_POS(index)
    _SB_T1_R2_WR_GRP2_POS(index)
    _SB_T1_R2_WR_GRP3_POS(index)
    _SB_T2_R0_WR_GRP0_POS(index)
    _SB_T2_R0_WR_GRP1_POS(index)
    _SB_T2_R0_WR_GRP2_POS(index)
    _SB_T2_R0_WR_GRP3_POS(index)
    _SB_T2_R1_WR_GRP0_POS(index)
    _SB_T2_R1_WR_GRP1_POS(index)
    _SB_T2_R1_WR_GRP2_POS(index)
    _SB_T2_R1_WR_GRP3_POS(index)
    _SB_T2_R2_WR_GRP0_POS(index)
    _SB_T2_R2_WR_GRP1_POS(index)
    _SB_T2_R2_WR_GRP2_POS(index)
    _SB_T2_R2_WR_GRP3_POS(index)
    _SB_T3_R0_WR_GRP0_POS(index)
    _SB_T3_R0_WR_GRP1_POS(index)
    _SB_T3_R0_WR_GRP2_POS(index)
    _SB_T3_R0_WR_GRP3_POS(index)
    _SB_T3_R1_WR_GRP0_POS(index)
    _SB_T3_R1_WR_GRP1_POS(index)
    _SB_T3_R1_WR_GRP2_POS(index)
    _SB_T3_R1_WR_GRP3_POS(index)
    _SB_T3_R2_WR_GRP0_POS(index)
    _SB_T3_R2_WR_GRP1_POS(index)
    _SB_T3_R2_WR_GRP2_POS(index)
    _SB_T3_R2_WR_GRP3_POS(index)
    _SB_T4_R0_WR_GRP0_POS(index)
    _SB_T4_R0_WR_GRP1_POS(index)
    _SB_T4_R0_WR_GRP2_POS(index)
    _SB_T4_R0_WR_GRP3_POS(index)
    _SB_T4_R2_WR_GRP0_POS(index)
    _SB_T4_R2_WR_GRP1_POS(index)
    _SB_T4_R2_WR_GRP2_POS(index)
    _SB_T4_R2_WR_GRP3_POS(index)
    _SB_T5_R0_WR_GRP0_POS(index)
    _SB_T5_R0_WR_GRP1_POS(index)
    _SB_T5_R0_WR_GRP2_POS(index)
    _SB_T5_R0_WR_GRP3_POS(index)
    _SB_T5_R1_WR_GRP0_POS(index)
    _SB_T5_R1_WR_GRP1_POS(index)
    _SB_T5_R1_WR_GRP2_POS(index)
    _SB_T5_R1_WR_GRP3_POS(index)
    _SB_T5_R2_WR_GRP0_POS(index)
    _SB_T5_R2_WR_GRP1_POS(index)
    _SB_T5_R2_WR_GRP2_POS(index)
    _SB_T5_R2_WR_GRP3_POS(index)
    _SB_T6_R0_WR_GRP0_POS(index)
    _SB_T6_R0_WR_GRP1_POS(index)
    _SB_T6_R0_WR_GRP2_POS(index)
    _SB_T6_R0_WR_GRP3_POS(index)
    _SB_T6_R1_WR_GRP0_POS(index)
    _SB_T6_R1_WR_GRP1_POS(index)
    _SB_T6_R1_WR_GRP2_POS(index)
    _SB_T6_R1_WR_GRP3_POS(index)
    _SB_T7_R0_WR_GRP0_POS(index)
    _SB_T7_R0_WR_GRP1_POS(index)
    _SB_T7_R0_WR_GRP2_POS(index)
    _SB_T7_R0_WR_GRP3_POS(index)
    _SB_T7_R1_WR_GRP0_POS(index)
    _SB_T7_R1_WR_GRP1_POS(index)
    _SB_T7_R1_WR_GRP2_POS(index)
    _SB_T7_R1_WR_GRP3_POS(index)
    _SB_T8_R0_WR_GRP0_POS(index)
    _SB_T8_R0_WR_GRP1_POS(index)
    _SB_T8_R0_WR_GRP2_POS(index)
    _SB_T8_R0_WR_GRP3_POS(index)
    _SB_T8_R1_WR_GRP0_POS(index)
    _SB_T8_R1_WR_GRP1_POS(index)
    _SB_T8_R1_WR_GRP2_POS(index)
    _SB_T8_R1_WR_GRP3_POS(index)
    _SB_T9_R0_WR_GRP0_POS(index)
    _SB_T9_R0_WR_GRP1_POS(index)
    _SB_T9_R0_WR_GRP2_POS(index)
    _SB_T9_R0_WR_GRP3_POS(index)
    _SB_T9_R1_WR_GRP0_POS(index)
    _SB_T9_R1_WR_GRP1_POS(index)
    _SB_T9_R1_WR_GRP2_POS(index)
    _SB_T9_R1_WR_GRP3_POS(index)
    _SB_T10_R0_WR_GRP0_POS(index)
    _SB_T10_R0_WR_GRP1_POS(index)
    _SB_T10_R0_WR_GRP2_POS(index)
    _SB_T10_R0_WR_GRP3_POS(index)
    _SB_T11_R0_WR_GRP0_POS(index)
    _SB_T11_R0_WR_GRP1_POS(index)
    _SB_T11_R0_WR_GRP2_POS(index)
    _SB_T11_R0_WR_GRP3_POS(index)
    _SB_T11_R1_WR_GRP0_POS(index)
    _SB_T11_R1_WR_GRP1_POS(index)
    _SB_T11_R1_WR_GRP2_POS(index)
    _SB_T11_R1_WR_GRP3_POS(index)
    _SB_T12_R0_WR_GRP0_POS(index)
    _SB_T12_R0_WR_GRP1_POS(index)
    _SB_T12_R0_WR_GRP2_POS(index)
    _SB_T12_R0_WR_GRP3_POS(index)
    _SB_T13_R0_WR_GRP0_POS(index)
    _SB_T13_R0_WR_GRP1_POS(index)
    _SB_T13_R0_WR_GRP2_POS(index)
    _SB_T13_R0_WR_GRP3_POS(index)

  LENs: 
    _SB_T0_R0_WR_GRP0_LEN(index)
    _SB_T0_R0_WR_GRP1_LEN(index)
    _SB_T0_R0_WR_GRP2_LEN(index)
    _SB_T0_R0_WR_GRP3_LEN(index)
    _SB_T0_R1_WR_GRP0_LEN(index)
    _SB_T0_R1_WR_GRP1_LEN(index)
    _SB_T0_R1_WR_GRP2_LEN(index)
    _SB_T0_R1_WR_GRP3_LEN(index)
    _SB_T1_R2_WR_GRP0_LEN(index)
    _SB_T1_R2_WR_GRP1_LEN(index)
    _SB_T1_R2_WR_GRP2_LEN(index)
    _SB_T1_R2_WR_GRP3_LEN(index)
    _SB_T2_R0_WR_GRP0_LEN(index)
    _SB_T2_R0_WR_GRP1_LEN(index)
    _SB_T2_R0_WR_GRP2_LEN(index)
    _SB_T2_R0_WR_GRP3_LEN(index)
    _SB_T2_R1_WR_GRP0_LEN(index)
    _SB_T2_R1_WR_GRP1_LEN(index)
    _SB_T2_R1_WR_GRP2_LEN(index)
    _SB_T2_R1_WR_GRP3_LEN(index)
    _SB_T2_R2_WR_GRP0_LEN(index)
    _SB_T2_R2_WR_GRP1_LEN(index)
    _SB_T2_R2_WR_GRP2_LEN(index)
    _SB_T2_R2_WR_GRP3_LEN(index)
    _SB_T3_R0_WR_GRP0_LEN(index)
    _SB_T3_R0_WR_GRP1_LEN(index)
    _SB_T3_R0_WR_GRP2_LEN(index)
    _SB_T3_R0_WR_GRP3_LEN(index)
    _SB_T3_R1_WR_GRP0_LEN(index)
    _SB_T3_R1_WR_GRP1_LEN(index)
    _SB_T3_R1_WR_GRP2_LEN(index)
    _SB_T3_R1_WR_GRP3_LEN(index)
    _SB_T3_R2_WR_GRP0_LEN(index)
    _SB_T3_R2_WR_GRP1_LEN(index)
    _SB_T3_R2_WR_GRP2_LEN(index)
    _SB_T3_R2_WR_GRP3_LEN(index)
    _SB_T4_R0_WR_GRP0_LEN(index)
    _SB_T4_R0_WR_GRP1_LEN(index)
    _SB_T4_R0_WR_GRP2_LEN(index)
    _SB_T4_R0_WR_GRP3_LEN(index)
    _SB_T4_R2_WR_GRP0_LEN(index)
    _SB_T4_R2_WR_GRP1_LEN(index)
    _SB_T4_R2_WR_GRP2_LEN(index)
    _SB_T4_R2_WR_GRP3_LEN(index)
    _SB_T5_R0_WR_GRP0_LEN(index)
    _SB_T5_R0_WR_GRP1_LEN(index)
    _SB_T5_R0_WR_GRP2_LEN(index)
    _SB_T5_R0_WR_GRP3_LEN(index)
    _SB_T5_R1_WR_GRP0_LEN(index)
    _SB_T5_R1_WR_GRP1_LEN(index)
    _SB_T5_R1_WR_GRP2_LEN(index)
    _SB_T5_R1_WR_GRP3_LEN(index)
    _SB_T5_R2_WR_GRP0_LEN(index)
    _SB_T5_R2_WR_GRP1_LEN(index)
    _SB_T5_R2_WR_GRP2_LEN(index)
    _SB_T5_R2_WR_GRP3_LEN(index)
    _SB_T6_R0_WR_GRP0_LEN(index)
    _SB_T6_R0_WR_GRP1_LEN(index)
    _SB_T6_R0_WR_GRP2_LEN(index)
    _SB_T6_R0_WR_GRP3_LEN(index)
    _SB_T6_R1_WR_GRP0_LEN(index)
    _SB_T6_R1_WR_GRP1_LEN(index)
    _SB_T6_R1_WR_GRP2_LEN(index)
    _SB_T6_R1_WR_GRP3_LEN(index)
    _SB_T7_R0_WR_GRP0_LEN(index)
    _SB_T7_R0_WR_GRP1_LEN(index)
    _SB_T7_R0_WR_GRP2_LEN(index)
    _SB_T7_R0_WR_GRP3_LEN(index)
    _SB_T7_R1_WR_GRP0_LEN(index)
    _SB_T7_R1_WR_GRP1_LEN(index)
    _SB_T7_R1_WR_GRP2_LEN(index)
    _SB_T7_R1_WR_GRP3_LEN(index)
    _SB_T8_R0_WR_GRP0_LEN(index)
    _SB_T8_R0_WR_GRP1_LEN(index)
    _SB_T8_R0_WR_GRP2_LEN(index)
    _SB_T8_R0_WR_GRP3_LEN(index)
    _SB_T8_R1_WR_GRP0_LEN(index)
    _SB_T8_R1_WR_GRP1_LEN(index)
    _SB_T8_R1_WR_GRP2_LEN(index)
    _SB_T8_R1_WR_GRP3_LEN(index)
    _SB_T9_R0_WR_GRP0_LEN(index)
    _SB_T9_R0_WR_GRP1_LEN(index)
    _SB_T9_R0_WR_GRP2_LEN(index)
    _SB_T9_R0_WR_GRP3_LEN(index)
    _SB_T9_R1_WR_GRP0_LEN(index)
    _SB_T9_R1_WR_GRP1_LEN(index)
    _SB_T9_R1_WR_GRP2_LEN(index)
    _SB_T9_R1_WR_GRP3_LEN(index)
    _SB_T10_R0_WR_GRP0_LEN(index)
    _SB_T10_R0_WR_GRP1_LEN(index)
    _SB_T10_R0_WR_GRP2_LEN(index)
    _SB_T10_R0_WR_GRP3_LEN(index)
    _SB_T11_R0_WR_GRP0_LEN(index)
    _SB_T11_R0_WR_GRP1_LEN(index)
    _SB_T11_R0_WR_GRP2_LEN(index)
    _SB_T11_R0_WR_GRP3_LEN(index)
    _SB_T11_R1_WR_GRP0_LEN(index)
    _SB_T11_R1_WR_GRP1_LEN(index)
    _SB_T11_R1_WR_GRP2_LEN(index)
    _SB_T11_R1_WR_GRP3_LEN(index)
    _SB_T12_R0_WR_GRP0_LEN(index)
    _SB_T12_R0_WR_GRP1_LEN(index)
    _SB_T12_R0_WR_GRP2_LEN(index)
    _SB_T12_R0_WR_GRP3_LEN(index)
    _SB_T13_R0_WR_GRP0_LEN(index)
    _SB_T13_R0_WR_GRP1_LEN(index)
    _SB_T13_R0_WR_GRP2_LEN(index)
    _SB_T13_R0_WR_GRP3_LEN(index)

*/


//******************************************************************************
/* Function :  SB_PGRegionWritePermSet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionWritePermSet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionWritePermSet function.
*/

PLIB_TEMPLATE void SB_PGRegionWritePermSet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , PLIB_SB_REGION_PG writePerm )
{
    if (writePerm & REGION_PG_0) {
        _SFR_BIT_SET(_SB_T0_R0_WR_GRP0_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP0_POS(index));
    }
    if (writePerm & REGION_PG_1) {
        _SFR_BIT_SET(_SB_T0_R0_WR_GRP1_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP1_POS(index));
    }
    if (writePerm & REGION_PG_2) {
        _SFR_BIT_SET(_SB_T0_R0_WR_GRP2_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP2_POS(index));
    }
    if (writePerm & REGION_PG_3) {
        _SFR_BIT_SET(_SB_T0_R0_WR_GRP3_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP3_POS(index));
    }
}


//******************************************************************************
/* Function :  SB_PGRegionWritePermClear_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionWritePermClear 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionWritePermClear function.
*/

PLIB_TEMPLATE void SB_PGRegionWritePermClear_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , PLIB_SB_REGION_PG writePerm )
{
    if (writePerm & REGION_PG_0) {
        _SFR_BIT_CLEAR(_SB_T0_R0_WR_GRP0_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP0_POS(index));
    }
    if (writePerm & REGION_PG_1) {
        _SFR_BIT_CLEAR(_SB_T0_R0_WR_GRP1_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP1_POS(index));
    }
    if (writePerm & REGION_PG_2) {
        _SFR_BIT_CLEAR(_SB_T0_R0_WR_GRP2_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP2_POS(index));
    }
    if (writePerm & REGION_PG_3) {
        _SFR_BIT_CLEAR(_SB_T0_R0_WR_GRP3_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_WR_GRP3_POS(index));
    }
}


//******************************************************************************
/* Function :  SB_ExistsPGRegWrPerm_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGRegWrPerm

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGRegWrPerm function.
*/

PLIB_TEMPLATE bool SB_ExistsPGRegWrPerm_Default( SB_MODULE_ID index )
{
    return true;
}


#endif /*_SB_PGREGWRPERM_DEFAULT_H*/

/******************************************************************************
 End of File
*/

