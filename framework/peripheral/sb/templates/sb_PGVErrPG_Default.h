/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrPG_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrPG
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrPG
        PLIB_SB_PGVErrorPermissionGroup

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

#ifndef _SB_PGVERRPG_DEFAULT_H
#define _SB_PGVERRPG_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_GRP_VREG(index)
    _SB_T1_GRP_VREG(index)
    _SB_T2_GRP_VREG(index)
    _SB_T3_GRP_VREG(index)
    _SB_T4_GRP_VREG(index)
    _SB_T5_GRP_VREG(index)
    _SB_T6_GRP_VREG(index)
    _SB_T7_GRP_VREG(index)
    _SB_T8_GRP_VREG(index)
    _SB_T9_GRP_VREG(index)
    _SB_T10_GRP_VREG(index)
    _SB_T11_GRP_VREG(index)
    _SB_T12_GRP_VREG(index)
    _SB_T13_GRP_VREG(index)

  MASKs: 
    _SB_T0_GRP_MASK(index)
    _SB_T1_GRP_MASK(index)
    _SB_T2_GRP_MASK(index)
    _SB_T3_GRP_MASK(index)
    _SB_T4_GRP_MASK(index)
    _SB_T5_GRP_MASK(index)
    _SB_T6_GRP_MASK(index)
    _SB_T7_GRP_MASK(index)
    _SB_T8_GRP_MASK(index)
    _SB_T9_GRP_MASK(index)
    _SB_T10_GRP_MASK(index)
    _SB_T11_GRP_MASK(index)
    _SB_T12_GRP_MASK(index)
    _SB_T13_GRP_MASK(index)

  POSs: 
    _SB_T0_GRP_POS(index)
    _SB_T1_GRP_POS(index)
    _SB_T2_GRP_POS(index)
    _SB_T3_GRP_POS(index)
    _SB_T4_GRP_POS(index)
    _SB_T5_GRP_POS(index)
    _SB_T6_GRP_POS(index)
    _SB_T7_GRP_POS(index)
    _SB_T8_GRP_POS(index)
    _SB_T9_GRP_POS(index)
    _SB_T10_GRP_POS(index)
    _SB_T11_GRP_POS(index)
    _SB_T12_GRP_POS(index)
    _SB_T13_GRP_POS(index)

  LENs: 
    _SB_T0_GRP_LEN(index)
    _SB_T1_GRP_LEN(index)
    _SB_T2_GRP_LEN(index)
    _SB_T3_GRP_LEN(index)
    _SB_T4_GRP_LEN(index)
    _SB_T5_GRP_LEN(index)
    _SB_T6_GRP_LEN(index)
    _SB_T7_GRP_LEN(index)
    _SB_T8_GRP_LEN(index)
    _SB_T9_GRP_LEN(index)
    _SB_T10_GRP_LEN(index)
    _SB_T11_GRP_LEN(index)
    _SB_T12_GRP_LEN(index)
    _SB_T13_GRP_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrPG_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrPG

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrPG function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrPG_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorPermissionGroup_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorPermissionGroup 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorPermissionGroup function.
*/

PLIB_TEMPLATE int SB_PGVErrorPermissionGroup_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_FIELD_READ(_SB_T0_GRP_VREG(index) + ((0x400 * target) >> 2), _SB_T0_GRP_MASK(index), _SB_T0_GRP_POS(index)); 
}


#endif /*_SB_PGVERRPG_DEFAULT_H*/

/******************************************************************************
 End of File
*/

