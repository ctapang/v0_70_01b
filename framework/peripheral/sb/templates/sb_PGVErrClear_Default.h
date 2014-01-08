/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrClear_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrClear
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrClear
        PLIB_SB_PGVErrorMulti
        PLIB_SB_PGVErrorCode
        PLIB_SB_PGVErrorLogClearSingle
        PLIB_SB_PGVErrorLogClearMulti

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

#ifndef _SB_PGVERRCLEAR_DEFAULT_H
#define _SB_PGVERRCLEAR_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_MULTI_VREG(index)
    _SB_T1_MULTI_VREG(index)
    _SB_T2_MULTI_VREG(index)
    _SB_T3_MULTI_VREG(index)
    _SB_T4_MULTI_VREG(index)
    _SB_T5_MULTI_VREG(index)
    _SB_T6_MULTI_VREG(index)
    _SB_T7_MULTI_VREG(index)
    _SB_T8_MULTI_VREG(index)
    _SB_T9_MULTI_VREG(index)
    _SB_T10_MULTI_VREG(index)
    _SB_T11_MULTI_VREG(index)
    _SB_T12_MULTI_VREG(index)
    _SB_T13_MULTI_VREG(index)
    _SB_T0_CODE_VREG(index)
    _SB_T1_CODE_VREG(index)
    _SB_T2_CODE_VREG(index)
    _SB_T3_CODE_VREG(index)
    _SB_T4_CODE_VREG(index)
    _SB_T5_CODE_VREG(index)
    _SB_T6_CODE_VREG(index)
    _SB_T7_CODE_VREG(index)
    _SB_T8_CODE_VREG(index)
    _SB_T9_CODE_VREG(index)
    _SB_T10_CODE_VREG(index)
    _SB_T11_CODE_VREG(index)
    _SB_T12_CODE_VREG(index)
    _SB_T13_CODE_VREG(index)

  MASKs: 
    _SB_T0_MULTI_MASK(index)
    _SB_T1_MULTI_MASK(index)
    _SB_T2_MULTI_MASK(index)
    _SB_T3_MULTI_MASK(index)
    _SB_T4_MULTI_MASK(index)
    _SB_T5_MULTI_MASK(index)
    _SB_T6_MULTI_MASK(index)
    _SB_T7_MULTI_MASK(index)
    _SB_T8_MULTI_MASK(index)
    _SB_T9_MULTI_MASK(index)
    _SB_T10_MULTI_MASK(index)
    _SB_T11_MULTI_MASK(index)
    _SB_T12_MULTI_MASK(index)
    _SB_T13_MULTI_MASK(index)
    _SB_T0_CODE_MASK(index)
    _SB_T1_CODE_MASK(index)
    _SB_T2_CODE_MASK(index)
    _SB_T3_CODE_MASK(index)
    _SB_T4_CODE_MASK(index)
    _SB_T5_CODE_MASK(index)
    _SB_T6_CODE_MASK(index)
    _SB_T7_CODE_MASK(index)
    _SB_T8_CODE_MASK(index)
    _SB_T9_CODE_MASK(index)
    _SB_T10_CODE_MASK(index)
    _SB_T11_CODE_MASK(index)
    _SB_T12_CODE_MASK(index)
    _SB_T13_CODE_MASK(index)

  POSs: 
    _SB_T0_MULTI_POS(index)
    _SB_T1_MULTI_POS(index)
    _SB_T2_MULTI_POS(index)
    _SB_T3_MULTI_POS(index)
    _SB_T4_MULTI_POS(index)
    _SB_T5_MULTI_POS(index)
    _SB_T6_MULTI_POS(index)
    _SB_T7_MULTI_POS(index)
    _SB_T8_MULTI_POS(index)
    _SB_T9_MULTI_POS(index)
    _SB_T10_MULTI_POS(index)
    _SB_T11_MULTI_POS(index)
    _SB_T12_MULTI_POS(index)
    _SB_T13_MULTI_POS(index)
    _SB_T0_CODE_POS(index)
    _SB_T1_CODE_POS(index)
    _SB_T2_CODE_POS(index)
    _SB_T3_CODE_POS(index)
    _SB_T4_CODE_POS(index)
    _SB_T5_CODE_POS(index)
    _SB_T6_CODE_POS(index)
    _SB_T7_CODE_POS(index)
    _SB_T8_CODE_POS(index)
    _SB_T9_CODE_POS(index)
    _SB_T10_CODE_POS(index)
    _SB_T11_CODE_POS(index)
    _SB_T12_CODE_POS(index)
    _SB_T13_CODE_POS(index)

  LENs: 
    _SB_T0_MULTI_LEN(index)
    _SB_T1_MULTI_LEN(index)
    _SB_T2_MULTI_LEN(index)
    _SB_T3_MULTI_LEN(index)
    _SB_T4_MULTI_LEN(index)
    _SB_T5_MULTI_LEN(index)
    _SB_T6_MULTI_LEN(index)
    _SB_T7_MULTI_LEN(index)
    _SB_T8_MULTI_LEN(index)
    _SB_T9_MULTI_LEN(index)
    _SB_T10_MULTI_LEN(index)
    _SB_T11_MULTI_LEN(index)
    _SB_T12_MULTI_LEN(index)
    _SB_T13_MULTI_LEN(index)
    _SB_T0_CODE_LEN(index)
    _SB_T1_CODE_LEN(index)
    _SB_T2_CODE_LEN(index)
    _SB_T3_CODE_LEN(index)
    _SB_T4_CODE_LEN(index)
    _SB_T5_CODE_LEN(index)
    _SB_T6_CODE_LEN(index)
    _SB_T7_CODE_LEN(index)
    _SB_T8_CODE_LEN(index)
    _SB_T9_CODE_LEN(index)
    _SB_T10_CODE_LEN(index)
    _SB_T11_CODE_LEN(index)
    _SB_T12_CODE_LEN(index)
    _SB_T13_CODE_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrClear_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrClear

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrClear function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrClear_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorMulti_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorMulti 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorMulti function.
*/

PLIB_TEMPLATE bool SB_PGVErrorMulti_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_BIT_READ(_SB_T0_MULTI_VREG(index) + ((0x400 * target) >> 2), _SB_T0_MULTI_POS(index));
}


//******************************************************************************
/* Function :  SB_PGVErrorCode_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorCode 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorCode function.
*/

PLIB_TEMPLATE PLIB_SB_ERROR SB_PGVErrorCode_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_FIELD_READ(_SB_T0_CODE_VREG(index) + ((0x400 * target) >> 2), _SB_T0_CODE_MASK(index), _SB_T0_CODE_POS(index));
}


//******************************************************************************
/* Function :  SB_PGVErrorLogClearSingle_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorLogClearSingle 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorLogClearSingle function.
*/

PLIB_TEMPLATE void SB_PGVErrorLogClearSingle_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    _SFR_FIELD_WRITE(_SB_T0_CODE_VREG(index) + ((0x400 * target) >> 2), _SB_T0_CODE_MASK(index), _SB_T0_CODE_POS(index), 0xF); 
}


//******************************************************************************
/* Function :  SB_PGVErrorLogClearMulti_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorLogClearMulti 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorLogClearMulti function.
*/

PLIB_TEMPLATE void SB_PGVErrorLogClearMulti_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    _SFR_BIT_WRITE(_SB_T0_MULTI_VREG(index) + ((0x400 * target) >> 2), _SB_T0_MULTI_POS(index), 1);
    _SFR_FIELD_WRITE(_SB_T0_CODE_VREG(index) + ((0x400 * target) >> 2), _SB_T0_CODE_MASK(index), _SB_T0_CODE_POS(index), 0); 
}


#endif /*_SB_PGVERRCLEAR_DEFAULT_H*/

/******************************************************************************
 End of File
*/

