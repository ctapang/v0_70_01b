/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrClrMulti_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrClrMulti
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrClrMulti
        PLIB_SB_PGVErrorClearMulti

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

#ifndef _SB_PGVERRCLRMULTI_DEFAULT_H
#define _SB_PGVERRCLRMULTI_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_ECLRM_VREG(index)
    _SB_T1_ECLRM_VREG(index)
    _SB_T2_ECLRM_VREG(index)
    _SB_T3_ECLRM_VREG(index)
    _SB_T4_ECLRM_VREG(index)
    _SB_T5_ECLRM_VREG(index)
    _SB_T6_ECLRM_VREG(index)
    _SB_T7_ECLRM_VREG(index)
    _SB_T8_ECLRM_VREG(index)
    _SB_T9_ECLRM_VREG(index)
    _SB_T10_ECLRM_VREG(index)
    _SB_T11_ECLRM_VREG(index)
    _SB_T12_ECLRM_VREG(index)
    _SB_T13_ECLRM_VREG(index)

  MASKs: 
    _SB_T0_ECLRM_MASK(index)
    _SB_T1_ECLRM_MASK(index)
    _SB_T2_ECLRM_MASK(index)
    _SB_T3_ECLRM_MASK(index)
    _SB_T4_ECLRM_MASK(index)
    _SB_T5_ECLRM_MASK(index)
    _SB_T6_ECLRM_MASK(index)
    _SB_T7_ECLRM_MASK(index)
    _SB_T8_ECLRM_MASK(index)
    _SB_T9_ECLRM_MASK(index)
    _SB_T10_ECLRM_MASK(index)
    _SB_T11_ECLRM_MASK(index)
    _SB_T12_ECLRM_MASK(index)
    _SB_T13_ECLRM_MASK(index)

  POSs: 
    _SB_T0_ECLRM_POS(index)
    _SB_T1_ECLRM_POS(index)
    _SB_T2_ECLRM_POS(index)
    _SB_T3_ECLRM_POS(index)
    _SB_T4_ECLRM_POS(index)
    _SB_T5_ECLRM_POS(index)
    _SB_T6_ECLRM_POS(index)
    _SB_T7_ECLRM_POS(index)
    _SB_T8_ECLRM_POS(index)
    _SB_T9_ECLRM_POS(index)
    _SB_T10_ECLRM_POS(index)
    _SB_T11_ECLRM_POS(index)
    _SB_T12_ECLRM_POS(index)
    _SB_T13_ECLRM_POS(index)

  LENs: 
    _SB_T0_ECLRM_LEN(index)
    _SB_T1_ECLRM_LEN(index)
    _SB_T2_ECLRM_LEN(index)
    _SB_T3_ECLRM_LEN(index)
    _SB_T4_ECLRM_LEN(index)
    _SB_T5_ECLRM_LEN(index)
    _SB_T6_ECLRM_LEN(index)
    _SB_T7_ECLRM_LEN(index)
    _SB_T8_ECLRM_LEN(index)
    _SB_T9_ECLRM_LEN(index)
    _SB_T10_ECLRM_LEN(index)
    _SB_T11_ECLRM_LEN(index)
    _SB_T12_ECLRM_LEN(index)
    _SB_T13_ECLRM_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrClrMulti_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrClrMulti

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrClrMulti function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrClrMulti_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorClearMulti_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorClearMulti 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorClearMulti function.
*/

PLIB_TEMPLATE bool SB_PGVErrorClearMulti_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_BIT_READ(_SB_T0_ECLRM_VREG(index) + ((0x400 * target) >> 2), _SB_T0_ECLRM_POS(index));
}


#endif /*_SB_PGVERRCLRMULTI_DEFAULT_H*/

/******************************************************************************
 End of File
*/

