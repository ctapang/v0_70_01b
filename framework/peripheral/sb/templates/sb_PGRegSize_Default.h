/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGRegSize_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGRegSize
    and its Variant : Default
    For following APIs :
        PLIB_SB_PGRegionSizeSet
        PLIB_SB_PGRegionSizeGet
        PLIB_SB_ExistsPGRegSize

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

#ifndef _SB_PGREGSIZE_DEFAULT_H
#define _SB_PGREGSIZE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_R0_SIZE_VREG(index)
    _SB_T0_R1_SIZE_VREG(index)
    _SB_T1_R0_SIZE_VREG(index)
    _SB_T1_R1_SIZE_VREG(index)
    _SB_T1_R2_SIZE_VREG(index)
    _SB_T1_R3_SIZE_VREG(index)
    _SB_T1_R4_SIZE_VREG(index)
    _SB_T1_R5_SIZE_VREG(index)
    _SB_T1_R6_SIZE_VREG(index)
    _SB_T1_R7_SIZE_VREG(index)
    _SB_T1_R8_SIZE_VREG(index)
    _SB_T2_R0_SIZE_VREG(index)
    _SB_T2_R1_SIZE_VREG(index)
    _SB_T2_R2_SIZE_VREG(index)
    _SB_T3_R0_SIZE_VREG(index)
    _SB_T3_R1_SIZE_VREG(index)
    _SB_T3_R2_SIZE_VREG(index)
    _SB_T4_R0_SIZE_VREG(index)
    _SB_T4_R1_SIZE_VREG(index)
    _SB_T4_R2_SIZE_VREG(index)
    _SB_T5_R0_SIZE_VREG(index)
    _SB_T5_R1_SIZE_VREG(index)
    _SB_T5_R2_SIZE_VREG(index)
    _SB_T6_R0_SIZE_VREG(index)
    _SB_T6_R1_SIZE_VREG(index)
    _SB_T7_R0_SIZE_VREG(index)
    _SB_T7_R1_SIZE_VREG(index)
    _SB_T8_R0_SIZE_VREG(index)
    _SB_T8_R1_SIZE_VREG(index)
    _SB_T9_R0_SIZE_VREG(index)
    _SB_T9_R1_SIZE_VREG(index)
    _SB_T10_R0_SIZE_VREG(index)
    _SB_T11_R0_SIZE_VREG(index)
    _SB_T11_R1_SIZE_VREG(index)
    _SB_T12_R0_SIZE_VREG(index)
    _SB_T13_R0_SIZE_VREG(index)

  MASKs: 
    _SB_T0_R0_SIZE_MASK(index)
    _SB_T0_R1_SIZE_MASK(index)
    _SB_T1_R0_SIZE_MASK(index)
    _SB_T1_R1_SIZE_MASK(index)
    _SB_T1_R2_SIZE_MASK(index)
    _SB_T1_R3_SIZE_MASK(index)
    _SB_T1_R4_SIZE_MASK(index)
    _SB_T1_R5_SIZE_MASK(index)
    _SB_T1_R6_SIZE_MASK(index)
    _SB_T1_R7_SIZE_MASK(index)
    _SB_T1_R8_SIZE_MASK(index)
    _SB_T2_R0_SIZE_MASK(index)
    _SB_T2_R1_SIZE_MASK(index)
    _SB_T2_R2_SIZE_MASK(index)
    _SB_T3_R0_SIZE_MASK(index)
    _SB_T3_R1_SIZE_MASK(index)
    _SB_T3_R2_SIZE_MASK(index)
    _SB_T4_R0_SIZE_MASK(index)
    _SB_T4_R1_SIZE_MASK(index)
    _SB_T4_R2_SIZE_MASK(index)
    _SB_T5_R0_SIZE_MASK(index)
    _SB_T5_R1_SIZE_MASK(index)
    _SB_T5_R2_SIZE_MASK(index)
    _SB_T6_R0_SIZE_MASK(index)
    _SB_T6_R1_SIZE_MASK(index)
    _SB_T7_R0_SIZE_MASK(index)
    _SB_T7_R1_SIZE_MASK(index)
    _SB_T8_R0_SIZE_MASK(index)
    _SB_T8_R1_SIZE_MASK(index)
    _SB_T9_R0_SIZE_MASK(index)
    _SB_T9_R1_SIZE_MASK(index)
    _SB_T10_R0_SIZE_MASK(index)
    _SB_T11_R0_SIZE_MASK(index)
    _SB_T11_R1_SIZE_MASK(index)
    _SB_T12_R0_SIZE_MASK(index)
    _SB_T13_R0_SIZE_MASK(index)

  POSs: 
    _SB_T0_R0_SIZE_POS(index)
    _SB_T0_R1_SIZE_POS(index)
    _SB_T1_R0_SIZE_POS(index)
    _SB_T1_R1_SIZE_POS(index)
    _SB_T1_R2_SIZE_POS(index)
    _SB_T1_R3_SIZE_POS(index)
    _SB_T1_R4_SIZE_POS(index)
    _SB_T1_R5_SIZE_POS(index)
    _SB_T1_R6_SIZE_POS(index)
    _SB_T1_R7_SIZE_POS(index)
    _SB_T1_R8_SIZE_POS(index)
    _SB_T2_R0_SIZE_POS(index)
    _SB_T2_R1_SIZE_POS(index)
    _SB_T2_R2_SIZE_POS(index)
    _SB_T3_R0_SIZE_POS(index)
    _SB_T3_R1_SIZE_POS(index)
    _SB_T3_R2_SIZE_POS(index)
    _SB_T4_R0_SIZE_POS(index)
    _SB_T4_R1_SIZE_POS(index)
    _SB_T4_R2_SIZE_POS(index)
    _SB_T5_R0_SIZE_POS(index)
    _SB_T5_R1_SIZE_POS(index)
    _SB_T5_R2_SIZE_POS(index)
    _SB_T6_R0_SIZE_POS(index)
    _SB_T6_R1_SIZE_POS(index)
    _SB_T7_R0_SIZE_POS(index)
    _SB_T7_R1_SIZE_POS(index)
    _SB_T8_R0_SIZE_POS(index)
    _SB_T8_R1_SIZE_POS(index)
    _SB_T9_R0_SIZE_POS(index)
    _SB_T9_R1_SIZE_POS(index)
    _SB_T10_R0_SIZE_POS(index)
    _SB_T11_R0_SIZE_POS(index)
    _SB_T11_R1_SIZE_POS(index)
    _SB_T12_R0_SIZE_POS(index)
    _SB_T13_R0_SIZE_POS(index)

  LENs: 
    _SB_T0_R0_SIZE_LEN(index)
    _SB_T0_R1_SIZE_LEN(index)
    _SB_T1_R0_SIZE_LEN(index)
    _SB_T1_R1_SIZE_LEN(index)
    _SB_T1_R2_SIZE_LEN(index)
    _SB_T1_R3_SIZE_LEN(index)
    _SB_T1_R4_SIZE_LEN(index)
    _SB_T1_R5_SIZE_LEN(index)
    _SB_T1_R6_SIZE_LEN(index)
    _SB_T1_R7_SIZE_LEN(index)
    _SB_T1_R8_SIZE_LEN(index)
    _SB_T2_R0_SIZE_LEN(index)
    _SB_T2_R1_SIZE_LEN(index)
    _SB_T2_R2_SIZE_LEN(index)
    _SB_T3_R0_SIZE_LEN(index)
    _SB_T3_R1_SIZE_LEN(index)
    _SB_T3_R2_SIZE_LEN(index)
    _SB_T4_R0_SIZE_LEN(index)
    _SB_T4_R1_SIZE_LEN(index)
    _SB_T4_R2_SIZE_LEN(index)
    _SB_T5_R0_SIZE_LEN(index)
    _SB_T5_R1_SIZE_LEN(index)
    _SB_T5_R2_SIZE_LEN(index)
    _SB_T6_R0_SIZE_LEN(index)
    _SB_T6_R1_SIZE_LEN(index)
    _SB_T7_R0_SIZE_LEN(index)
    _SB_T7_R1_SIZE_LEN(index)
    _SB_T8_R0_SIZE_LEN(index)
    _SB_T8_R1_SIZE_LEN(index)
    _SB_T9_R0_SIZE_LEN(index)
    _SB_T9_R1_SIZE_LEN(index)
    _SB_T10_R0_SIZE_LEN(index)
    _SB_T11_R0_SIZE_LEN(index)
    _SB_T11_R1_SIZE_LEN(index)
    _SB_T12_R0_SIZE_LEN(index)
    _SB_T13_R0_SIZE_LEN(index)

*/


//******************************************************************************
/* Function :  SB_PGRegionSizeSet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionSizeSet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionSizeSet function.
*/

PLIB_TEMPLATE void SB_PGRegionSizeSet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region , uint32_t size )
{
    _SFR_FIELD_WRITE(_SB_T0_R0_SIZE_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_SIZE_MASK(index), _SB_T0_R0_SIZE_POS(index), size);
}


//******************************************************************************
/* Function :  SB_PGRegionSizeGet_Default

  Summary:
    Implements Default variant of PLIB_SB_PGRegionSizeGet 

  Description:
    This template implements the Default variant of the PLIB_SB_PGRegionSizeGet function.
*/

PLIB_TEMPLATE uint32_t SB_PGRegionSizeGet_Default( SB_MODULE_ID index , PLIB_SB_TGT_REGION region )
{
    return _SFR_FIELD_READ(_SB_T0_R0_SIZE_VREG(index) + (((0x400 * (region >> 8)) + (0x20 * (region & 0xFF))) >> 2), _SB_T0_R0_SIZE_MASK(index), _SB_T0_R0_SIZE_POS(index));
}


//******************************************************************************
/* Function :  SB_ExistsPGRegSize_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGRegSize

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGRegSize function.
*/

PLIB_TEMPLATE bool SB_ExistsPGRegSize_Default( SB_MODULE_ID index )
{
    return true;
}


#endif /*_SB_PGREGSIZE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

