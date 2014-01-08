/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGRegRdPerm_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGRegRdPerm
    and its Variant : Default
    For following APIs :
        PLIB_SB_PGRegionReadPermSet
        PLIB_SB_PGRegionReadPermClear
        PLIB_SB_ExistsPGRegRdPerm

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

#ifndef _SB_PGREGRDPERM_DEFAULT_H
#define _SB_PGREGRDPERM_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_R0_RD_GRP0_VREG(index)
    _SB_T0_R0_RD_GRP1_VREG(index)
    _SB_T0_R0_RD_GRP2_VREG(index)
    _SB_T0_R0_RD_GRP3_VREG(index)
    _SB_T0_R1_RD_GRP0_VREG(index)
    _SB_T0_R1_RD_GRP1_VREG(index)
    _SB_T0_R1_RD_GRP2_VREG(index)
    _SB_T0_R1_RD_GRP3_VREG(index)
    _SB_T1_R0_RD_GRP0_VREG(index)
    _SB_T1_R0_RD_GRP1_VREG(index)
    _SB_T1_R0_RD_GRP2_VREG(index)
    _SB_T1_R0_RD_GRP3_VREG(index)
    _SB_T1_R2_RD_GRP0_VREG(index)
    _SB_T1_R2_RD_GRP1_VREG(index)
    _SB_T1_R2_RD_GRP2_VREG(index)
    _SB_T1_R2_RD_GRP3_VREG(index)
    _SB_T1_R3_RD_GRP0_VREG(index)
    _SB_T1_R3_RD_GRP1_VREG(index)
    _SB_T1_R3_RD_GRP2_VREG(index)
    _SB_T1_R3_RD_GRP3_VREG(index)
    _SB_T1_R4_RD_GRP0_VREG(index)
    _SB_T1_R4_RD_GRP1_VREG(index)
    _SB_T1_R4_RD_GRP2_VREG(index)
    _SB_T1_R4_RD_GRP3_VREG(index)
    _SB_T1_R5_RD_GRP0_VREG(index)
    _SB_T1_R5_RD_GRP1_VREG(index)
    _SB_T1_R5_RD_GRP2_VREG(index)
    _SB_T1_R5_RD_GRP3_VREG(index)
    _SB_T1_R6_RD_GRP0_VREG(index)
    _SB_T1_R6_RD_GRP1_VREG(index)
    _SB_T1_R6_RD_GRP2_VREG(index)
    _SB_T1_R6_RD_GRP3_VREG(index)
    _SB_T1_R7_RD_GRP0_VREG(index)
    _SB_T1_R7_RD_GRP1_VREG(index)
    _SB_T1_R7_RD_GRP2_VREG(index)
    _SB_T1_R7_RD_GRP3_VREG(index)
    _SB_T1_R8_RD_GRP0_VREG(index)
    _SB_T1_R8_RD_GRP1_VREG(index)
    _SB_T1_R8_RD_GRP2_VREG(index)
    _SB_T1_R8_RD_GRP3_VREG(index)
    _SB_T2_R0_RD_GRP0_VREG(index)
    _SB_T2_R0_RD_GRP1_VREG(index)
    _SB_T2_R0_RD_GRP2_VREG(index)
    _SB_T2_R0_RD_GRP3_VREG(index)
    _SB_T2_R1_RD_GRP0_VREG(index)
    _SB_T2_R1_RD_GRP1_VREG(index)
    _SB_T2_R1_RD_GRP2_VREG(index)
    _SB_T2_R1_RD_GRP3_VREG(index)
    _SB_T2_R2_RD_GRP0_VREG(index)
    _SB_T2_R2_RD_GRP1_VREG(index)
    _SB_T2_R2_RD_GRP2_VREG(index)
    _SB_T2_R2_RD_GRP3_VREG(index)
    _SB_T3_R0_RD_GRP0_VREG(index)
    _SB_T3_R0_RD_GRP1_VREG(index)
    _SB_T3_R0_RD_GRP2_VREG(index)
    _SB_T3_R0_RD_GRP3_VREG(index)
    _SB_T3_R1_RD_GRP0_VREG(index)
    _SB_T3_R1_RD_GRP1_VREG(index)
    _SB_T3_R1_RD_GRP2_VREG(index)
    _SB_T3_R1_RD_GRP3_VREG(index)
    _SB_T3_R2_RD_GRP0_VREG(index)
    _SB_T3_R2_RD_GRP1_VREG(index)
    _SB_T3_R2_RD_GRP2_VREG(index)
    _SB_T3_R2_RD_GRP3_VREG(index)
    _SB_T4_R0_RD_GRP0_VREG(index)
    _SB_T4_R0_RD_GRP1_VREG(index)
    _SB_T4_R0_RD_GRP2_VREG(index)
    _SB_T4_R0_RD_GRP3_VREG(index)
    _SB_T4_R2_RD_GRP0_VREG(index)
    _SB_T4_R2_RD_GRP1_VREG(index)
    _SB_T4_R2_RD_GRP2_VREG(index)
    _SB_T4_R2_RD_GRP3_VREG(index)
    _SB_T5_R0_RD_GRP0_VREG(index)
    _SB_T5_R0_RD_GRP1_VREG(index)
    _SB_T5_R0_RD_GRP2_VREG(index)
    _SB_T5_R0_RD_GRP3_VREG(index)
    _SB_T5_R1_RD_GRP0_VREG(index)
    _SB_T5_R1_RD_GRP1_VREG(index)
    _SB_T5_R1_RD_GRP2_VREG(index)
    _SB_T5_R1_RD_GRP3_VREG(index)
    _SB_T5_R2_RD_GRP0_VREG(index)
    _SB_T5_R2_RD_GRP1_VREG(index)
    _SB_T5_R2_RD_GRP2_VREG(index)
    _SB_T5_R2_RD_GRP3_VREG(index)
    _SB_T6_R0_RD_GRP0_VREG(index)
    _SB_T6_R0_RD_GRP1_VREG(index)
    _SB_T6_R0_RD_GRP2_VREG(index)
    _SB_T6_R0_RD_GRP3_VREG(index)
    _SB_T6_R1_RD_GRP0_VREG(index)
    _SB_T6_R1_RD_GRP1_VREG(index)
    _SB_T6_R1_RD_GRP2_VREG(index)
    _SB_T6_R1_RD_GRP3_VREG(index)
    _SB_T7_R0_RD_GRP0_VREG(index)
    _SB_T7_R0_RD_GRP1_VREG(index)
    _SB_T7_R0_RD_GRP2_VREG(index)
    _SB_T7_R0_RD_GRP3_VREG(index)
    _SB_T7_R1_RD_GRP0_VREG(index)
    _SB_T7_R1_RD_GRP1_VREG(index)
    _SB_T7_R1_RD_GRP2_VREG(index)
    _SB_T7_R1_RD_GRP3_VREG(index)
    _SB_T8_R0_RD_GRP0_VREG(index)
    _SB_T8_R0_RD_GRP1_VREG(index)
    _SB_T8_R0_RD_GRP2_VREG(index)
    _SB_T8_R0_RD_GRP3_VREG(index)
    _SB_T8_R1_RD_GRP0_VREG(index)
    _SB_T8_R1_RD_GRP1_VREG(index)
    _SB_T8_R1_RD_GRP2_VREG(index)
    _SB_T8_R1_RD_GRP3_VREG(index)
    _SB_T9_R0_RD_GRP0_VREG(index)
    _SB_T9_R0_RD_GRP1_VREG(index)
    _SB_T9_R0_RD_GRP2_VREG(index)
    _SB_T9_R0_RD_GRP3_VREG(index)
    _SB_T9_R1_RD_GRP0_VREG(index)
    _SB_T9_R1_RD_GRP1_VREG(index)
    _SB_T9_R1_RD_GRP2_VREG(index)
    _SB_T9_R1_RD_GRP3_VREG(index)
    _SB_T10_R0_RD_GRP0_VREG(index)
    _SB_T10_R0_RD_GRP1_VREG(index)
    _SB_T10_R0_RD_GRP2_VREG(index)
    _SB_T10_R0_RD_GRP3_VREG(index)
    _SB_T11_R0_RD_GRP0_VREG(index)
    _SB_T11_R0_RD_GRP1_VREG(index)
    _SB_T11_R0_RD_GRP2_VREG(index)
    _SB_T11_R0_RD_GRP3_VREG(index)
    _SB_T11_R1_RD_GRP0_VREG(index)
    _SB_T11_R1_RD_GRP1_VREG(index)
    _SB_T11_R1_RD_GRP2_VREG(index)
    _SB_T11_R1_RD_GRP3_VREG(index)
    _SB_T12_R0_RD_GRP0_VREG(index)
    _SB_T12_R0_RD_GRP1_VREG(index)
    _SB_T12_R0_RD_GRP2_VREG(index)
    _SB_T12_R0_RD_GRP3_VREG(index)
    _SB_T13_R0_RD_GRP0_VREG(index)
    _SB_T13_R0_RD_GRP1_VREG(index)
    _SB_T13_R0_RD_GRP2_VREG(index)
    _SB_T13_R0_RD_GRP3_VREG(index)

  MASKs: 
    _SB_T0_R0_RD_GRP0_MASK(index)
    _SB_T0_R0_RD_GRP1_MASK(index)
    _SB_T0_R0_RD_GRP2_MASK(index)
    _SB_T0_R0_RD_GRP3_MASK(index)
    _SB_T0_R1_RD_GRP0_MASK(index)
    _SB_T0_R1_RD_GRP1_MASK(index)
    _SB_T0_R1_RD_GRP2_MASK(index)
    _SB_T0_R1_RD_GRP3_MASK(index)
    _SB_T1_R0_RD_GRP0_MASK(index)
    _SB_T1_R0_RD_GRP1_MASK(index)
    _SB_T1_R0_RD_GRP2_MASK(index)
    _SB_T1_R0_RD_GRP3_MASK(index)
    _SB_T1_R2_RD_GRP0_MASK(index)
    _SB_T1_R2_RD_GRP1_MASK(index)
    _SB_T1_R2_RD_GRP2_MASK(index)
    _SB_T1_R2_RD_GRP3_MASK(index)
    _SB_T1_R3_RD_GRP0_MASK(index)
    _SB_T1_R3_RD_GRP1_MASK(index)
    _SB_T1_R3_RD_GRP2_MASK(index)
    _SB_T1_R3_RD_GRP3_MASK(index)
    _SB_T1_R4_RD_GRP0_MASK(index)
    _SB_T1_R4_RD_GRP1_MASK(index)
    _SB_T1_R4_RD_GRP2_MASK(index)
    _SB_T1_R4_RD_GRP3_MASK(index)
    _SB_T1_R5_RD_GRP0_MASK(index)
    _SB_T1_R5_RD_GRP1_MASK(index)
    _SB_T1_R5_RD_GRP2_MASK(index)
    _SB_T1_R5_RD_GRP3_MASK(index)
    _SB_T1_R6_RD_GRP0_MASK(index)
    _SB_T1_R6_RD_GRP1_MASK(index)
    _SB_T1_R6_RD_GRP2_MASK(index)
    _SB_T1_R6_RD_GRP3_MASK(index)
    _SB_T1_R7_RD_GRP0_MASK(index)
    _SB_T1_R7_RD_GRP1_MASK(index)
    _SB_T1_R7_RD_GRP2_MASK(index)
    _SB_T1_R7_RD_GRP3_MASK(index)
    _SB_T1_R8_RD_GRP0_MASK(index)
    _SB_T1_R8_RD_GRP1_MASK(index)
    _SB_T1_R8_RD_GRP2_MASK(index)
    _SB_T1_R8_RD_GRP3_MASK(index)
    _SB_T2_R0_RD_GRP0_MASK(index)
    _SB_T2_R0_RD_GRP1_MASK(index)
    _SB_T2_R0_RD_GRP2_MASK(index)
    _SB_T2_R0_RD_GRP3_MASK(index)
    _SB_T2_R1_RD_GRP0_MASK(index)
    _SB_T2_R1_RD_GRP1_MASK(index)
    _SB_T2_R1_RD_GRP2_MASK(index)
    _SB_T2_R1_RD_GRP3_MASK(index)
    _SB_T2_R2_RD_GRP0_MASK(index)
    _SB_T2_R2_RD_GRP1_MASK(index)
    _SB_T2_R2_RD_GRP2_MASK(index)
    _SB_T2_R2_RD_GRP3_MASK(index)
    _SB_T3_R0_RD_GRP0_MASK(index)
    _SB_T3_R0_RD_GRP1_MASK(index)
    _SB_T3_R0_RD_GRP2_MASK(index)
    _SB_T3_R0_RD_GRP3_MASK(index)
    _SB_T3_R1_RD_GRP0_MASK(index)
    _SB_T3_R1_RD_GRP1_MASK(index)
    _SB_T3_R1_RD_GRP2_MASK(index)
    _SB_T3_R1_RD_GRP3_MASK(index)
    _SB_T3_R2_RD_GRP0_MASK(index)
    _SB_T3_R2_RD_GRP1_MASK(index)
    _SB_T3_R2_RD_GRP2_MASK(index)
    _SB_T3_R2_RD_GRP3_MASK(index)
    _SB_T4_R0_RD_GRP0_MASK(index)
    _SB_T4_R0_RD_GRP1_MASK(index)
    _SB_T4_R0_RD_GRP2_MASK(index)
    _SB_T4_R0_RD_GRP3_MASK(index)
    _SB_T4_R2_RD_GRP0_MASK(index)
    _SB_T4_R2_RD_GRP1_MASK(index)
    _SB_T4_R2_RD_GRP2_MASK(index)
    _SB_T4_R2_RD_GRP3_MASK(index)
    _SB_T5_R0_RD_GRP0_MASK(index)
    _SB_T5_R0_RD_GRP1_MASK(index)
    _SB_T5_R0_RD_GRP2_MASK(index)
    _SB_T5_R0_RD_GRP3_MASK(index)
    _SB_T5_R1_RD_GRP0_MASK(index)
    _SB_T5_R1_RD_GRP1_MASK(index)
    _SB_T5_R1_RD_GRP2_MASK(index)
    _SB_T5_R1_RD_GRP3_MASK(index)
    _SB_T5_R2_RD_GRP0_MASK(index)
    _SB_T5_R2_RD_GRP1_MASK(index)
    _SB_T5_R2_RD_GRP2_MASK(index)
    _SB_T5_R2_RD_GRP3_MASK(index)
    _SB_T6_R0_RD_GRP0_MASK(index)
    _SB_T6_R0_RD_GRP1_MASK(index)
    _SB_T6_R0_RD_GRP2_MASK(index)
    _SB_T6_R0_RD_GRP3_MASK(index)
    _SB_T6_R1_RD_GRP0_MASK(index)
    _SB_T6_R1_RD_GRP1_MASK(index)
    _SB_T6_R1_RD_GRP2_MASK(index)
    _SB_T6_R1_RD_GRP3_MASK(index)
    _SB_T7_R0_RD_GRP0_MASK(index)
    _SB_T7_R0_RD_GRP1_MASK(index)
    _SB_T7_R0_RD_GRP2_MASK(index)
    _SB_T7_R0_RD_GRP3_MASK(index)
    _SB_T7_R1_RD_GRP0_MASK(index)
    _SB_T7_R1_RD_GRP1_MASK(index)
    _SB_T7_R1_RD_GRP2_MASK(index)
    _SB_T7_R1_RD_GRP3_MASK(index)
    _SB_T8_R0_RD_GRP0_MASK(index)
    _SB_T8_R0_RD_GRP1_MASK(index)
    _SB_T8_R0_RD_GRP2_MASK(index)
    _SB_T8_R0_RD_GRP3_MASK(index)
    _SB_T8_R1_RD_GRP0_MASK(index)
    _SB_T8_R1_RD_GRP1_MASK(index)
    _SB_T8_R1_RD_GRP2_MASK(index)
    _SB_T8_R1_RD_GRP3_MASK(index)
    _SB_T9_R0_RD_GRP0_MASK(index)
    _SB_T9_R0_RD_GRP1_MASK(index)
    _SB_T9_R0_RD_GRP2_MASK(index)
    _SB_T9_R0_RD_GRP3_MASK(index)
    _SB_T9_R1_RD_GRP0_MASK(index)
    _SB_T9_R1_RD_GRP1_MASK(index)
    _SB_T9_R1_RD_GRP2_MASK(index)
    _SB_T9_R1_RD_GRP3_MASK(index)
    _SB_T10_R0_RD_GRP0_MASK(index)
    _SB_T10_R0_RD_GRP1_MASK(index)
    _SB_T10_R0_RD_GRP2_MASK(index)
    _SB_T10_R0_RD_GRP3_MASK(index)
    _SB_T11_R0_RD_GRP0_MASK(index)
    _SB_T11_R0_RD_GRP1_MASK(index)
    _SB_T11_R0_RD_GRP2_MASK(index)
    _SB_T11_R0_RD_GRP3_MASK(index)
    _SB_T11_R1_RD_GRP0_MASK(index)
    _SB_T11_R1_RD_GRP1_MASK(index)
    _SB_T11_R1_RD_GRP2_MASK(index)
    _SB_T11_R1_RD_GRP3_MASK(index)
    _SB_T12_R0_RD_GRP0_MASK(index)
    _SB_T12_R0_RD_GRP1_MASK(index)
    _SB_T12_R0_RD_GRP2_MASK(index)
    _SB_T12_R0_RD_GRP3_MASK(index)
    _SB_T13_R0_RD_GRP0_MASK(index)
    _SB_T13_R0_RD_GRP1_MASK(index)
    _SB_T13_R0_RD_GRP2_MASK(index)
    _SB_T13_R0_RD_GRP3_MASK(index)

  POSs: 
    _SB_T0_R0_RD_GRP0_POS(index)
    _SB_T0_R0_RD_GRP1_POS(index)
    _SB_T0_R0_RD_GRP2_POS(index)
    _SB_T0_R0_RD_GRP3_POS(index)
    _SB_T0_R1_RD_GRP0_POS(index)
    _SB_T0_R1_RD_GRP1_POS(index)
    _SB_T0_R1_RD_GRP2_POS(index)
    _SB_T0_R1_RD_GRP3_POS(index)
    _SB_T1_R0_RD_GRP0_POS(index)
    _SB_T1_R0_RD_GRP1_POS(index)
    _SB_T1_R0_RD_GRP2_POS(index)
    _SB_T1_R0_RD_GRP3_POS(index)
    _SB_T1_R2_RD_GRP0_POS(index)
    _SB_T1_R2_RD_GRP1_POS(index)
    _SB_T1_R2_RD_GRP2_POS(index)
    _SB_T1_R2_RD_GRP3_POS(index)
    _SB_T1_R3_RD_GRP0_POS(index)
    _SB_T1_R3_RD_GRP1_POS(index)
    _SB_T1_R3_RD_GRP2_POS(index)
    _SB_T1_R3_RD_GRP3_POS(index)
    _SB_T1_R4_RD_GRP0_POS(index)
    _SB_T1_R4_RD_GRP1_POS(index)
    _SB_T1_R4_RD_GRP2_POS(index)
    _SB_T1_R4_RD_GRP3_POS(index)
    _SB_T1_R5_RD_GRP0_POS(index)
    _SB_T1_R5_RD_GRP1_POS(index)
    _SB_T1_R5_RD_GRP2_POS(index)
    _SB_T1_R5_RD_GRP3_POS(index)
    _SB_T1_R6_RD_GRP0_POS(index)
    _SB_T1_R6_RD_GRP1_POS(index)
    _SB_T1_R6_RD_GRP2_POS(index)
    _SB_T1_R6_RD_GRP3_POS(index)
    _SB_T1_R7_RD_GRP0_POS(index)
    _SB_T1_R7_RD_GRP1_POS(index)
    _SB_T1_R7_RD_GRP2_POS(index)
    _SB_T1_R7_RD_GRP3_POS(index)
    _SB_T1_R8_RD_GRP0_POS(index)
    _SB_T1_R8_RD_GRP1_POS(index)
    _SB_T1_R8_RD_GRP2_POS(index)
    _SB_T1_R8_RD_GRP3_POS(index)
    _SB_T2_R0_RD_GRP0_POS(index)
    _SB_T2_R0_RD_GRP1_POS(index)
    _SB_T2_R0_RD_GRP2_POS(index)
    _SB_T2_R0_RD_GRP3_POS(index)
    _SB_T2_R1_RD_GRP0_POS(index)
    _SB_T2_R1_RD_GRP1_POS(index)
    _SB_T2_R1_RD_GRP2_POS(index)
    _SB_T2_R1_RD_GRP3_POS(index)
    _SB_T2_R2_RD_GRP0_POS(index)
    _SB_T2_R2_RD_GRP1_POS(index)
    _SB_T2_R2_RD_GRP2_POS(index)
    _SB_T2_R2_RD_GRP3_POS(index)
    _SB_T3_R0_RD_GRP0_POS(index)
    _SB_T3_R0_RD_GRP1_POS(index)
    _SB_T3_R0_RD_GRP2_POS(index)
    _SB_T3_R0_RD_GRP3_POS(index)
    _SB_T3_R1_RD_GRP0_POS(index)
    _SB_T3_R1_RD_GRP1_POS(index)
    _SB_T3_R1_RD_GRP2_POS(index)
    _SB_T3_R1_RD_GRP3_POS(index)
    _SB_T3_R2_RD_GRP0_POS(index)
    _SB_T3_R2_RD_GRP1_POS(index)
    _SB_T3_R2_RD_GRP2_POS(index)
    _SB_T3_R2_RD_GRP3_POS(index)
    _SB_T4_R0_RD_GRP0_POS(index)
    _SB_T4_R0_RD_GRP1_POS(index)
    _SB_T4_R0_RD_GRP2_POS(index)
    _SB_T4_R0_RD_GRP3_POS(index)
    _SB_T4_R2_RD_GRP0_POS(index)
    _SB_T4_R2_RD_GRP1_POS(index)
    _SB_T4_R2_RD_GRP2_POS(index)
    _SB_T4_R2_RD_GRP3_POS(index)
    _SB_T5_R0_RD_GRP0_POS(index)
    _SB_T5_R0_RD_GRP1_POS(index)
    _SB_T5_R0_RD_GRP2_POS(index)
    _SB_T5_R0_RD_GRP3_POS(index)
    _SB_T5_R1_RD_GRP0_POS(index)
    _SB_T5_R1_RD_GRP1_POS(index)
    _SB_T5_R1_RD_GRP2_POS(index)
    _SB_T5_R1_RD_GRP3_POS(index)
    _SB_T5_R2_RD_GRP0_POS(index)
    _SB_T5_R2_RD_GRP1_POS(index)
    _SB_T5_R2_RD_GRP2_POS(index)
    _SB_T5_R2_RD_GRP3_POS(index)
    _SB_T6_R0_RD_GRP0_POS(index)
    _SB_T6_R0_RD_GRP1_POS(index)
    _SB_T6_R0_RD_GRP2_POS(index)
    _SB_T6_R0_RD_GRP3_POS(index)
    _SB_T6_R1_RD_GRP0_POS(index)
    _SB_T6_R1_RD_GRP1_POS(index)
    _SB_T6_R1_RD_GRP2_POS(index)
    _SB_T6_R1_RD_GRP3_POS(index)
    _SB_T7_R0_RD_GRP0_POS(index)
    _SB_T7_R0_RD_GRP1_POS(index)
    _SB_T7_R0_RD_GRP2_POS(index)
    _SB_T7_R0_RD_GRP3_POS(index)
    _SB_T7_R1_RD_GRP0_POS(index)
    _SB_T7_R1_RD_GRP1_POS(index)
    _SB_T7_R1_RD_GRP2_POS(index)
    _SB_T7_R1_RD_GRP3_POS(index)
    _SB_T8_R0_RD_GRP0_POS(index)
    _SB_T8_R0_RD_GRP1_POS(index)
    _SB_T8_R0_RD_GRP2_POS(index)
    _SB_T8_R0_RD_GRP3_POS(index)
    _SB_T8_R1_RD_GRP0_POS(index)
    _SB_T8_R1_RD_GRP1_POS(index)
    _SB_T8_R1_RD_GRP2_POS(index)
    _SB_T8_R1_RD_GRP3_POS(index)
    _SB_T9_R0_RD_GRP0_POS(index)
    _SB_T9_R0_RD_GRP1_POS(index)
    _SB_T9_R0_RD_GRP2_POS(index)
    _SB_T9_R0_RD_GRP3_POS(index)
    _SB_T9_R1_RD_GRP0_POS(index)
    _SB_T9_R1_RD_GRP1_POS(index)
    _SB_T9_R1_RD_GRP2_POS(index)
    _SB_T9_R1_RD_GRP3_POS(index)
    _SB_T10_R0_RD_GRP0_POS(index)
    _SB_T10_R0_RD_GRP1_POS(index)
    _SB_T10_R0_RD_GRP2_POS(index)
    _SB_T10_R0_RD_GRP3_POS(index)
    _SB_T11_R0_RD_GRP0_POS(index)
    _SB_T11_R0_RD_GRP1_POS(index)
    _SB_T11_R0_RD_GRP2_POS(index)
    _SB_T11_R0_RD_GRP3_POS(index)
    _SB_T11_R1_RD_GRP0_POS(index)
    _SB_T11_R1_RD_GRP1_POS(index)
    _SB_T11_R1_RD_GRP2_POS(index)
    _SB_T11_R1_RD_GRP3_POS(index)
    _SB_T12_R0_RD_GRP0_POS(index)
    _SB_T12_R0_RD_GRP1_POS(index)
    _SB_T12_R0_RD_GRP2_POS(index)
    _SB_T12_R0_RD_GRP3_POS(index)
    _SB_T13_R0_RD_GRP0_POS(index)
    _SB_T13_R0_RD_GRP1_POS(index)
    _SB_T13_R0_RD_GRP2_POS(index)
    _SB_T13_R0_RD_GRP3_POS(index)

  LENs: 
    _SB_T0_R0_RD_GRP0_LEN(index)
    _SB_T0_R0_RD_GRP1_LEN(index)
    _SB_T0_R0_RD_GRP2_LEN(index)
    _SB_T0_R0_RD_GRP3_LEN(index)
    _SB_T0_R1_RD_GRP0_LEN(index)
    _SB_T0_R1_RD_GRP1_LEN(index)
    _SB_T0_R1_RD_GRP2_LEN(index)
    _SB_T0_R1_RD_GRP3_LEN(index)
    _SB_T1_R0_RD_GRP0_LEN(index)
    _SB_T1_R0_RD_GRP1_LEN(index)
    _SB_T1_R0_RD_GRP2_LEN(index)
    _SB_T1_R0_RD_GRP3_LEN(index)
    _SB_T1_R2_RD_GRP0_LEN(index)
    _SB_T1_R2_RD_GRP1_LEN(index)
    _SB_T1_R2_RD_GRP2_LEN(index)
    _SB_T1_R2_RD_GRP3_LEN(index)
    _SB_T1_R3_RD_GRP0_LEN(index)
    _SB_T1_R3_RD_GRP1_LEN(index)
    _SB_T1_R3_RD_GRP2_LEN(index)
    _SB_T1_R3_RD_GRP3_LEN(index)
    _SB_T1_R4_RD_GRP0_LEN(index)
    _SB_T1_R4_RD_GRP1_LEN(index)
    _SB_T1_R4_RD_GRP2_LEN(index)
    _SB_T1_R4_RD_GRP3_LEN(index)
    _SB_T1_R5_RD_GRP0_LEN(index)
    _SB_T1_R5_RD_GRP1_LEN(index)
    _SB_T1_R5_RD_GRP2_LEN(index)
    _SB_T1_R5_RD_GRP3_LEN(index)
    _SB_T1_R6_RD_GRP0_LEN(index)
    _SB_T1_R6_RD_GRP1_LEN(index)
    _SB_T1_R6_RD_GRP2_LEN(index)
    _SB_T1_R6_RD_GRP3_LEN(index)
    _SB_T1_R7_RD_GRP0_LEN(index)
    _SB_T1_R7_RD_GRP1_LEN(index)
    _SB_T1_R7_RD_GRP2_LEN(index)
    _SB_T1_R7_RD_GRP3_LEN(index)
    _SB_T1_R8_RD_GRP0_LEN(index)
    _SB_T1_R8_RD_GRP1_LEN(index)
    _SB_T1_R8_RD_GRP2_LEN(index)
    _SB_T1_R8_RD_GRP3_LEN(index)
    _SB_T2_R0_RD_GRP0_LEN(index)
    _SB_T2_R0_RD_GRP1_LEN(index)
    _SB_T2_R0_RD_GRP2_LEN(index)
    _SB_T2_R0_RD_GRP3_LEN(index)
    _SB_T2_R1_RD_GRP0_LEN(index)
    _SB_T2_R1_RD_GRP1_LEN(index)
    _SB_T2_R1_RD_GRP2_LEN(index)
    _SB_T2_R1_RD_GRP3_LEN(index)
    _SB_T2_R2_RD_GRP0_LEN(index)
    _SB_T2_R2_RD_GRP1_LEN(index)
    _SB_T2_R2_RD_GRP2_LEN(index)
    _SB_T2_R2_RD_GRP3_LEN(index)
    _SB_T3_R0_RD_GRP0_LEN(index)
    _SB_T3_R0_RD_GRP1_LEN(index)
    _SB_T3_R0_RD_GRP2_LEN(index)
    _SB_T3_R0_RD_GRP3_LEN(index)
    _SB_T3_R1_RD_GRP0_LEN(index)
    _SB_T3_R1_RD_GRP1_LEN(index)
    _SB_T3_R1_RD_GRP2_LEN(index)
    _SB_T3_R1_RD_GRP3_LEN(index)
    _SB_T3_R2_RD_GRP0_LEN(index)
    _SB_T3_R2_RD_GRP1_LEN(index)
    _SB_T3_R2_RD_GRP2_LEN(index)
    _SB_T3_R2_RD_GRP3_LEN(index)
    _SB_T4_R0_RD_GRP0_LEN(index)
    _SB_T4_R0_RD_GRP1_LEN(index)
    _SB_T4_R0_RD_GRP2_LEN(index)
    _SB_T4_R0_RD_GRP3_LEN(index)
    _SB_T4_R2_RD_GRP0_LEN(index)
    _SB_T4_R2_RD_GRP1_LEN(index)
    _SB_T4_R2_RD_GRP2_LEN(index)
    _SB_T4_R2_RD_GRP3_LEN(index)
    _SB_T5_R0_RD_GRP0_LEN(index)
    _SB_T5_R0_RD_GRP1_LEN(index)
    _SB_T5_R0_RD_GRP2_LEN(index)
    _SB_T5_R0_RD_GRP3_LEN(index)
    _SB_T5_R1_RD_GRP0_LEN(index)
    _SB_T5_R1_RD_GRP1_LEN(index)
    _SB_T5_R1_RD_GRP2_LEN(index)
    _SB_T5_R1_RD_GRP3_LEN(index)
    _SB_T5_R2_RD_GRP0_LEN(index)
    _SB_T5_R2_RD_GRP1_LEN(index)
    _SB_T5_R2_RD_GRP2_LEN(index)
    _SB_T5_R2_RD_GRP3_LEN(index)
    _SB_T6_R0_RD_GRP0_LEN(index)
    _SB_T6_R0_RD_GRP1_LEN(index)
    _SB_T6_R0_RD_GRP2_LEN(index)
    _SB_T6_R0_RD_GRP3_LEN(index)
    _SB_T6_R1_RD_GRP0_LEN(index)
    _SB_T6_R1_RD_GRP1_LEN(index)
    _SB_T6_R1_RD_GRP2_LEN(index)
    _SB_T6_R1_RD_GRP3_LEN(index)
    _SB_T7_R0_RD_GRP0_LEN(index)
    _SB_T7_R0_RD_GRP1_LEN(index)
    _SB_T7_R0_RD_GRP2_LEN(index)
    _SB_T7_R0_RD_GRP3_LEN(index)
    _SB_T7_R1_RD_GRP0_LEN(index)
    _SB_T7_R1_RD_GRP1_LEN(index)
    _SB_T7_R1_RD_GRP2_LEN(index)
    _SB_T7_R1_RD_GRP3_LEN(index)
    _SB_T8_R0_RD_GRP0_LEN(index)
    _SB_T8_R0_RD_GRP1_LEN(index)
    _SB_T8_R0_RD_GRP2_LEN(index)
    _SB_T8_R0_RD_GRP3_LEN(index)
    _SB_T8_R1_RD_GRP0_LEN(index)
    _SB_T8_R1_RD_GRP1_LEN(index)
    _SB_T8_R1_RD_GRP2_LEN(index)
    _SB_T8_R1_RD_GRP3_LEN(index)
    _SB_T9_R0_RD_GRP0_LEN(index)
    _SB_T9_R0_RD_GRP1_LEN(index)
    _SB_T9_R0_RD_GRP2_LEN(index)
    _SB_T9_R0_RD_GRP3_LEN(index)
    _SB_T9_R1_RD_GRP0_LEN(index)
    _SB_T9_R1_RD_GRP1_LEN(index)
    _SB_T9_R1_RD_GRP2_LEN(index)
    _SB_T9_R1_RD_GRP3_LEN(index)
    _SB_T10_R0_RD_GRP0_LEN(index)
    _SB_T10_R0_RD_GRP1_LEN(index)
    _SB_T10_R0_RD_GRP2_LEN(index)
    _SB_T10_R0_RD_GRP3_LEN(index)
    _SB_T11_R0_RD_GRP0_LEN(index)
    _SB_T11_R0_RD_GRP1_LEN(index)
    _SB_T11_R0_RD_GRP2_LEN(index)
    _SB_T11_R0_RD_GRP3_LEN(index)
    _SB_T11_R1_RD_GRP0_LEN(index)
    _SB_T11_R1_RD_GRP1_LEN(index)
    _SB_T11_R1_RD_GRP2_LEN(index)
    _SB_T11_R1_RD_GRP3_LEN(index)
    _SB_T12_R0_RD_GRP0_LEN(index)
    _SB_T12_R0_RD_GRP1_LEN(index)
    _SB_T12_R0_RD_GRP2_LEN(index)
    _SB_T12_R0_RD_GRP3_LEN(index)
    _SB_T13_R0_RD_GRP0_LEN(index)
    _SB_T13_R0_RD_GRP1_LEN(index)
    _SB_T13_R0_RD_GRP2_LEN(index)
    _SB_T13_R0_RD_GRP3_LEN(index)

*/


//******************************************************************************
/* Function :  SB_PGRegionReadPermSet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionReadPermSet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionReadPermSet function.
*/

PLIB_TEMPLATE void SB_PGRegionReadPermSet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , PLIB_SB_REGION_PG readPerm )
{
    if (readPerm & REGION_PG_0) {
        _SFR_BIT_SET(_SB_T0_R0_RD_GRP0_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP0_POS(index));
    }
    if (readPerm & REGION_PG_1) {
        _SFR_BIT_SET(_SB_T0_R0_RD_GRP1_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP1_POS(index));
    }
    if (readPerm & REGION_PG_2) {
        _SFR_BIT_SET(_SB_T0_R0_RD_GRP2_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP2_POS(index));
    }
    if (readPerm & REGION_PG_3) {
        _SFR_BIT_SET(_SB_T0_R0_RD_GRP3_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP3_POS(index));
    }
}


//******************************************************************************
/* Function :  SB_PGRegionReadPermClear_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionReadPermClear 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionReadPermClear function.
*/

PLIB_TEMPLATE void SB_PGRegionReadPermClear_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , PLIB_SB_REGION_PG readPerm )
{
    if (readPerm & REGION_PG_0) {
        _SFR_BIT_CLEAR(_SB_T0_R0_RD_GRP0_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP0_POS(index));
    }
    if (readPerm & REGION_PG_1) {
        _SFR_BIT_CLEAR(_SB_T0_R0_RD_GRP1_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP1_POS(index));
    }
    if (readPerm & REGION_PG_2) {
        _SFR_BIT_CLEAR(_SB_T0_R0_RD_GRP2_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP2_POS(index));
    }
    if (readPerm & REGION_PG_3) {
        _SFR_BIT_CLEAR(_SB_T0_R0_RD_GRP3_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_RD_GRP3_POS(index));
    }
}


//******************************************************************************
/* Function :  SB_ExistsPGRegRdPerm_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGRegRdPerm

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGRegRdPerm function.
*/

PLIB_TEMPLATE bool SB_ExistsPGRegRdPerm_Default( SB_MODULE_ID index )
{
    return true;
}


#endif /*_SB_PGREGRDPERM_DEFAULT_H*/

/******************************************************************************
 End of File
*/

