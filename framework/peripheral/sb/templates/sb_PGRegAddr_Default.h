/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGRegAddr_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGRegAddr
    and its Variant : Default
    For following APIs :
        PLIB_SB_PGRegionAddrSet
        PLIB_SB_PGRegionAddrGet
        PLIB_SB_ExistsPGRegAddr

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

#ifndef _SB_PGREGADDR_DEFAULT_H
#define _SB_PGREGADDR_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_R0_BASE_VREG(index)
    _SB_T0_R1_BASE_VREG(index)
    _SB_T1_R0_BASE_VREG(index)
    _SB_T1_R1_BASE_VREG(index)
    _SB_T1_R2_BASE_VREG(index)
    _SB_T1_R3_BASE_VREG(index)
    _SB_T1_R4_BASE_VREG(index)
    _SB_T1_R5_BASE_VREG(index)
    _SB_T1_R6_BASE_VREG(index)
    _SB_T1_R7_BASE_VREG(index)
    _SB_T1_R8_BASE_VREG(index)
    _SB_T2_R0_BASE_VREG(index)
    _SB_T2_R1_BASE_VREG(index)
    _SB_T2_R2_BASE_VREG(index)
    _SB_T3_R0_BASE_VREG(index)
    _SB_T3_R1_BASE_VREG(index)
    _SB_T3_R2_BASE_VREG(index)
    _SB_T4_R0_BASE_VREG(index)
    _SB_T4_R1_BASE_VREG(index)
    _SB_T4_R2_BASE_VREG(index)
    _SB_T5_R0_BASE_VREG(index)
    _SB_T5_R1_BASE_VREG(index)
    _SB_T5_R2_BASE_VREG(index)
    _SB_T6_R0_BASE_VREG(index)
    _SB_T6_R1_BASE_VREG(index)
    _SB_T7_R0_BASE_VREG(index)
    _SB_T7_R1_BASE_VREG(index)
    _SB_T8_R0_BASE_VREG(index)
    _SB_T8_R1_BASE_VREG(index)
    _SB_T9_R0_BASE_VREG(index)
    _SB_T9_R1_BASE_VREG(index)
    _SB_T10_R0_BASE_VREG(index)
    _SB_T11_R0_BASE_VREG(index)
    _SB_T11_R1_BASE_VREG(index)
    _SB_T12_R0_BASE_VREG(index)
    _SB_T13_R0_BASE_VREG(index)

  MASKs: 
    _SB_T0_R0_BASE_MASK(index)
    _SB_T0_R1_BASE_MASK(index)
    _SB_T1_R0_BASE_MASK(index)
    _SB_T1_R1_BASE_MASK(index)
    _SB_T1_R2_BASE_MASK(index)
    _SB_T1_R3_BASE_MASK(index)
    _SB_T1_R4_BASE_MASK(index)
    _SB_T1_R5_BASE_MASK(index)
    _SB_T1_R6_BASE_MASK(index)
    _SB_T1_R7_BASE_MASK(index)
    _SB_T1_R8_BASE_MASK(index)
    _SB_T2_R0_BASE_MASK(index)
    _SB_T2_R1_BASE_MASK(index)
    _SB_T2_R2_BASE_MASK(index)
    _SB_T3_R0_BASE_MASK(index)
    _SB_T3_R1_BASE_MASK(index)
    _SB_T3_R2_BASE_MASK(index)
    _SB_T4_R0_BASE_MASK(index)
    _SB_T4_R1_BASE_MASK(index)
    _SB_T4_R2_BASE_MASK(index)
    _SB_T5_R0_BASE_MASK(index)
    _SB_T5_R1_BASE_MASK(index)
    _SB_T5_R2_BASE_MASK(index)
    _SB_T6_R0_BASE_MASK(index)
    _SB_T6_R1_BASE_MASK(index)
    _SB_T7_R0_BASE_MASK(index)
    _SB_T7_R1_BASE_MASK(index)
    _SB_T8_R0_BASE_MASK(index)
    _SB_T8_R1_BASE_MASK(index)
    _SB_T9_R0_BASE_MASK(index)
    _SB_T9_R1_BASE_MASK(index)
    _SB_T10_R0_BASE_MASK(index)
    _SB_T11_R0_BASE_MASK(index)
    _SB_T11_R1_BASE_MASK(index)
    _SB_T12_R0_BASE_MASK(index)
    _SB_T13_R0_BASE_MASK(index)

  POSs: 
    _SB_T0_R0_BASE_POS(index)
    _SB_T0_R1_BASE_POS(index)
    _SB_T1_R0_BASE_POS(index)
    _SB_T1_R1_BASE_POS(index)
    _SB_T1_R2_BASE_POS(index)
    _SB_T1_R3_BASE_POS(index)
    _SB_T1_R4_BASE_POS(index)
    _SB_T1_R5_BASE_POS(index)
    _SB_T1_R6_BASE_POS(index)
    _SB_T1_R7_BASE_POS(index)
    _SB_T1_R8_BASE_POS(index)
    _SB_T2_R0_BASE_POS(index)
    _SB_T2_R1_BASE_POS(index)
    _SB_T2_R2_BASE_POS(index)
    _SB_T3_R0_BASE_POS(index)
    _SB_T3_R1_BASE_POS(index)
    _SB_T3_R2_BASE_POS(index)
    _SB_T4_R0_BASE_POS(index)
    _SB_T4_R1_BASE_POS(index)
    _SB_T4_R2_BASE_POS(index)
    _SB_T5_R0_BASE_POS(index)
    _SB_T5_R1_BASE_POS(index)
    _SB_T5_R2_BASE_POS(index)
    _SB_T6_R0_BASE_POS(index)
    _SB_T6_R1_BASE_POS(index)
    _SB_T7_R0_BASE_POS(index)
    _SB_T7_R1_BASE_POS(index)
    _SB_T8_R0_BASE_POS(index)
    _SB_T8_R1_BASE_POS(index)
    _SB_T9_R0_BASE_POS(index)
    _SB_T9_R1_BASE_POS(index)
    _SB_T10_R0_BASE_POS(index)
    _SB_T11_R0_BASE_POS(index)
    _SB_T11_R1_BASE_POS(index)
    _SB_T12_R0_BASE_POS(index)
    _SB_T13_R0_BASE_POS(index)

  LENs: 
    _SB_T0_R0_BASE_LEN(index)
    _SB_T0_R1_BASE_LEN(index)
    _SB_T1_R0_BASE_LEN(index)
    _SB_T1_R1_BASE_LEN(index)
    _SB_T1_R2_BASE_LEN(index)
    _SB_T1_R3_BASE_LEN(index)
    _SB_T1_R4_BASE_LEN(index)
    _SB_T1_R5_BASE_LEN(index)
    _SB_T1_R6_BASE_LEN(index)
    _SB_T1_R7_BASE_LEN(index)
    _SB_T1_R8_BASE_LEN(index)
    _SB_T2_R0_BASE_LEN(index)
    _SB_T2_R1_BASE_LEN(index)
    _SB_T2_R2_BASE_LEN(index)
    _SB_T3_R0_BASE_LEN(index)
    _SB_T3_R1_BASE_LEN(index)
    _SB_T3_R2_BASE_LEN(index)
    _SB_T4_R0_BASE_LEN(index)
    _SB_T4_R1_BASE_LEN(index)
    _SB_T4_R2_BASE_LEN(index)
    _SB_T5_R0_BASE_LEN(index)
    _SB_T5_R1_BASE_LEN(index)
    _SB_T5_R2_BASE_LEN(index)
    _SB_T6_R0_BASE_LEN(index)
    _SB_T6_R1_BASE_LEN(index)
    _SB_T7_R0_BASE_LEN(index)
    _SB_T7_R1_BASE_LEN(index)
    _SB_T8_R0_BASE_LEN(index)
    _SB_T8_R1_BASE_LEN(index)
    _SB_T9_R0_BASE_LEN(index)
    _SB_T9_R1_BASE_LEN(index)
    _SB_T10_R0_BASE_LEN(index)
    _SB_T11_R0_BASE_LEN(index)
    _SB_T11_R1_BASE_LEN(index)
    _SB_T12_R0_BASE_LEN(index)
    _SB_T13_R0_BASE_LEN(index)

*/


//******************************************************************************
/* Function :  SB_PGRegionAddrSet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionAddrSet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionAddrSet function.
*/

PLIB_TEMPLATE void SB_PGRegionAddrSet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , uint32_t phys_addr )
{
    _SFR_FIELD_WRITE(_SB_T0_R0_BASE_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_BASE_MASK(index), _SB_T0_R0_BASE_POS(index), phys_addr >> 10);
}


//******************************************************************************
/* Function :  SB_PGRegionAddrGet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionAddrGet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionAddrGet function.
*/

PLIB_TEMPLATE uint32_t SB_PGRegionAddrGet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region )
{
    return (_SFR_READ(_SB_T0_R0_BASE_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2)) & 0xFFFFFC00);
}


//******************************************************************************
/* Function :  SB_ExistsPGRegAddr_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGRegAddr

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGRegAddr function.
*/

PLIB_TEMPLATE bool SB_ExistsPGRegAddr_Default( SB_MODULE_ID index )
{
    return true;
}


#endif /*_SB_PGREGADDR_DEFAULT_H*/

/******************************************************************************
 End of File
*/

