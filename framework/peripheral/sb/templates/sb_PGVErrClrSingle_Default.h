/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrClrSingle_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrClrSingle
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrClrSingle
        PLIB_SB_PGVErrorClearSingle

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

#ifndef _SB_PGVERRCLRSINGLE_DEFAULT_H
#define _SB_PGVERRCLRSINGLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_ECLRS_VREG(index)
    _SB_T1_ECLRS_VREG(index)
    _SB_T2_ECLRS_VREG(index)
    _SB_T3_ECLRS_VREG(index)
    _SB_T4_ECLRS_VREG(index)
    _SB_T5_ECLRS_VREG(index)
    _SB_T6_ECLRS_VREG(index)
    _SB_T7_ECLRS_VREG(index)
    _SB_T8_ECLRS_VREG(index)
    _SB_T9_ECLRS_VREG(index)
    _SB_T10_ECLRS_VREG(index)
    _SB_T11_ECLRS_VREG(index)
    _SB_T12_ECLRS_VREG(index)
    _SB_T13_ECLRS_VREG(index)

  MASKs: 
    _SB_T0_ECLRS_MASK(index)
    _SB_T1_ECLRS_MASK(index)
    _SB_T2_ECLRS_MASK(index)
    _SB_T3_ECLRS_MASK(index)
    _SB_T4_ECLRS_MASK(index)
    _SB_T5_ECLRS_MASK(index)
    _SB_T6_ECLRS_MASK(index)
    _SB_T7_ECLRS_MASK(index)
    _SB_T8_ECLRS_MASK(index)
    _SB_T9_ECLRS_MASK(index)
    _SB_T10_ECLRS_MASK(index)
    _SB_T11_ECLRS_MASK(index)
    _SB_T12_ECLRS_MASK(index)
    _SB_T13_ECLRS_MASK(index)

  POSs: 
    _SB_T0_ECLRS_POS(index)
    _SB_T1_ECLRS_POS(index)
    _SB_T2_ECLRS_POS(index)
    _SB_T3_ECLRS_POS(index)
    _SB_T4_ECLRS_POS(index)
    _SB_T5_ECLRS_POS(index)
    _SB_T6_ECLRS_POS(index)
    _SB_T7_ECLRS_POS(index)
    _SB_T8_ECLRS_POS(index)
    _SB_T9_ECLRS_POS(index)
    _SB_T10_ECLRS_POS(index)
    _SB_T11_ECLRS_POS(index)
    _SB_T12_ECLRS_POS(index)
    _SB_T13_ECLRS_POS(index)

  LENs: 
    _SB_T0_ECLRS_LEN(index)
    _SB_T1_ECLRS_LEN(index)
    _SB_T2_ECLRS_LEN(index)
    _SB_T3_ECLRS_LEN(index)
    _SB_T4_ECLRS_LEN(index)
    _SB_T5_ECLRS_LEN(index)
    _SB_T6_ECLRS_LEN(index)
    _SB_T7_ECLRS_LEN(index)
    _SB_T8_ECLRS_LEN(index)
    _SB_T9_ECLRS_LEN(index)
    _SB_T10_ECLRS_LEN(index)
    _SB_T11_ECLRS_LEN(index)
    _SB_T12_ECLRS_LEN(index)
    _SB_T13_ECLRS_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrClrSingle_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrClrSingle

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrClrSingle function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrClrSingle_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorClearSingle_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorClearSingle 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorClearSingle function.
*/

PLIB_TEMPLATE bool SB_PGVErrorClearSingle_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_BIT_READ(_SB_T0_ECLRS_VREG(index) + ((0x400 * target) >> 2), _SB_T0_ECLRS_POS(index));
}


#endif /*_SB_PGVERRCLRSINGLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

