/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrStatus_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrStatus
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrStatus
        PLIB_SB_PGVErrorStatus

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

#ifndef _SB_PGVERRSTATUS_DEFAULT_H
#define _SB_PGVERRSTATUS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_PGV_VREG(index)
    _SB_T1_PGV_VREG(index)
    _SB_T2_PGV_VREG(index)
    _SB_T3_PGV_VREG(index)
    _SB_T4_PGV_VREG(index)
    _SB_T5_PGV_VREG(index)
    _SB_T6_PGV_VREG(index)
    _SB_T7_PGV_VREG(index)
    _SB_T8_PGV_VREG(index)
    _SB_T9_PGV_VREG(index)
    _SB_T10_PGV_VREG(index)
    _SB_T11_PGV_VREG(index)
    _SB_T12_PGV_VREG(index)
    _SB_T13_PGV_VREG(index)

  MASKs: 
    _SB_T0_PGV_MASK(index)
    _SB_T1_PGV_MASK(index)
    _SB_T2_PGV_MASK(index)
    _SB_T3_PGV_MASK(index)
    _SB_T4_PGV_MASK(index)
    _SB_T5_PGV_MASK(index)
    _SB_T6_PGV_MASK(index)
    _SB_T7_PGV_MASK(index)
    _SB_T8_PGV_MASK(index)
    _SB_T9_PGV_MASK(index)
    _SB_T10_PGV_MASK(index)
    _SB_T11_PGV_MASK(index)
    _SB_T12_PGV_MASK(index)
    _SB_T13_PGV_MASK(index)

  POSs: 
    _SB_T0_PGV_POS(index)
    _SB_T1_PGV_POS(index)
    _SB_T2_PGV_POS(index)
    _SB_T3_PGV_POS(index)
    _SB_T4_PGV_POS(index)
    _SB_T5_PGV_POS(index)
    _SB_T6_PGV_POS(index)
    _SB_T7_PGV_POS(index)
    _SB_T8_PGV_POS(index)
    _SB_T9_PGV_POS(index)
    _SB_T10_PGV_POS(index)
    _SB_T11_PGV_POS(index)
    _SB_T12_PGV_POS(index)
    _SB_T13_PGV_POS(index)

  LENs: 
    _SB_T0_PGV_LEN(index)
    _SB_T1_PGV_LEN(index)
    _SB_T2_PGV_LEN(index)
    _SB_T3_PGV_LEN(index)
    _SB_T4_PGV_LEN(index)
    _SB_T5_PGV_LEN(index)
    _SB_T6_PGV_LEN(index)
    _SB_T7_PGV_LEN(index)
    _SB_T8_PGV_LEN(index)
    _SB_T9_PGV_LEN(index)
    _SB_T10_PGV_LEN(index)
    _SB_T11_PGV_LEN(index)
    _SB_T12_PGV_LEN(index)
    _SB_T13_PGV_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrStatus_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrStatus

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrStatus function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrStatus_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorStatus_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorStatus 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorStatus function.
*/
PLIB_TEMPLATE bool SB_PGVErrorStatus_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_BIT_READ(_SB_T0_PGV_VREG(index), target);
}


#endif /*_SB_PGVERRSTATUS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

