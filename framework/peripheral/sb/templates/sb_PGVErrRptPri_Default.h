/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrRptPri_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrRptPri
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrRptPri
        PLIB_SB_PGVErrorReportPrimaryEnable
        PLIB_SB_PGVErrorReportPrimaryDisable

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

#ifndef _SB_PGVERRRPTPRI_DEFAULT_H
#define _SB_PGVERRRPTPRI_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_ERRP_VREG(index)
    _SB_T1_ERRP_VREG(index)
    _SB_T2_ERRP_VREG(index)
    _SB_T3_ERRP_VREG(index)
    _SB_T4_ERRP_VREG(index)
    _SB_T5_ERRP_VREG(index)
    _SB_T6_ERRP_VREG(index)
    _SB_T7_ERRP_VREG(index)
    _SB_T8_ERRP_VREG(index)
    _SB_T9_ERRP_VREG(index)
    _SB_T10_ERRP_VREG(index)
    _SB_T11_ERRP_VREG(index)
    _SB_T12_ERRP_VREG(index)
    _SB_T13_ERRP_VREG(index)

  MASKs: 
    _SB_T0_ERRP_MASK(index)
    _SB_T1_ERRP_MASK(index)
    _SB_T2_ERRP_MASK(index)
    _SB_T3_ERRP_MASK(index)
    _SB_T4_ERRP_MASK(index)
    _SB_T5_ERRP_MASK(index)
    _SB_T6_ERRP_MASK(index)
    _SB_T7_ERRP_MASK(index)
    _SB_T8_ERRP_MASK(index)
    _SB_T9_ERRP_MASK(index)
    _SB_T10_ERRP_MASK(index)
    _SB_T11_ERRP_MASK(index)
    _SB_T12_ERRP_MASK(index)
    _SB_T13_ERRP_MASK(index)

  POSs: 
    _SB_T0_ERRP_POS(index)
    _SB_T1_ERRP_POS(index)
    _SB_T2_ERRP_POS(index)
    _SB_T3_ERRP_POS(index)
    _SB_T4_ERRP_POS(index)
    _SB_T5_ERRP_POS(index)
    _SB_T6_ERRP_POS(index)
    _SB_T7_ERRP_POS(index)
    _SB_T8_ERRP_POS(index)
    _SB_T9_ERRP_POS(index)
    _SB_T10_ERRP_POS(index)
    _SB_T11_ERRP_POS(index)
    _SB_T12_ERRP_POS(index)
    _SB_T13_ERRP_POS(index)

  LENs: 
    _SB_T0_ERRP_LEN(index)
    _SB_T1_ERRP_LEN(index)
    _SB_T2_ERRP_LEN(index)
    _SB_T3_ERRP_LEN(index)
    _SB_T4_ERRP_LEN(index)
    _SB_T5_ERRP_LEN(index)
    _SB_T6_ERRP_LEN(index)
    _SB_T7_ERRP_LEN(index)
    _SB_T8_ERRP_LEN(index)
    _SB_T9_ERRP_LEN(index)
    _SB_T10_ERRP_LEN(index)
    _SB_T11_ERRP_LEN(index)
    _SB_T12_ERRP_LEN(index)
    _SB_T13_ERRP_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrRptPri_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrRptPri

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrRptPri function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrRptPri_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorReportPrimaryEnable_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorReportPrimaryEnable 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorReportPrimaryEnable function.
*/

PLIB_TEMPLATE void SB_PGVErrorReportPrimaryEnable_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    _SFR_BIT_SET(_SB_T0_ERRP_VREG(index) + ((0x400 * target) >> 2), _SB_T0_ERRP_POS(index));
}


//******************************************************************************
/* Function :  SB_PGVErrorReportPrimaryDisable_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorReportPrimaryDisable 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorReportPrimaryDisable function.
*/

PLIB_TEMPLATE void SB_PGVErrorReportPrimaryDisable_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    _SFR_BIT_CLEAR(_SB_T0_ERRP_VREG(index) + ((0x400 * target) >> 2), _SB_T0_ERRP_POS(index));
}


#endif /*_SB_PGVERRRPTPRI_DEFAULT_H*/

/******************************************************************************
 End of File
*/

