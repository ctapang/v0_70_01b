/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrInitID_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrInitID
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrInitID
        PLIB_SB_PGVErrorInitiatorID

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

#ifndef _SB_PGVERRINITID_DEFAULT_H
#define _SB_PGVERRINITID_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_INITID_VREG(index)
    _SB_T1_INITID_VREG(index)
    _SB_T2_INITID_VREG(index)
    _SB_T3_INITID_VREG(index)
    _SB_T4_INITID_VREG(index)
    _SB_T5_INITID_VREG(index)
    _SB_T6_INITID_VREG(index)
    _SB_T7_INITID_VREG(index)
    _SB_T8_INITID_VREG(index)
    _SB_T9_INITID_VREG(index)
    _SB_T10_INITID_VREG(index)
    _SB_T11_INITID_VREG(index)
    _SB_T12_INITID_VREG(index)
    _SB_T13_INITID_VREG(index)

  MASKs: 
    _SB_T0_INITID_MASK(index)
    _SB_T1_INITID_MASK(index)
    _SB_T2_INITID_MASK(index)
    _SB_T3_INITID_MASK(index)
    _SB_T4_INITID_MASK(index)
    _SB_T5_INITID_MASK(index)
    _SB_T6_INITID_MASK(index)
    _SB_T7_INITID_MASK(index)
    _SB_T8_INITID_MASK(index)
    _SB_T9_INITID_MASK(index)
    _SB_T10_INITID_MASK(index)
    _SB_T11_INITID_MASK(index)
    _SB_T12_INITID_MASK(index)
    _SB_T13_INITID_MASK(index)

  POSs: 
    _SB_T0_INITID_POS(index)
    _SB_T1_INITID_POS(index)
    _SB_T2_INITID_POS(index)
    _SB_T3_INITID_POS(index)
    _SB_T4_INITID_POS(index)
    _SB_T5_INITID_POS(index)
    _SB_T6_INITID_POS(index)
    _SB_T7_INITID_POS(index)
    _SB_T8_INITID_POS(index)
    _SB_T9_INITID_POS(index)
    _SB_T10_INITID_POS(index)
    _SB_T11_INITID_POS(index)
    _SB_T12_INITID_POS(index)
    _SB_T13_INITID_POS(index)

  LENs: 
    _SB_T0_INITID_LEN(index)
    _SB_T1_INITID_LEN(index)
    _SB_T2_INITID_LEN(index)
    _SB_T3_INITID_LEN(index)
    _SB_T4_INITID_LEN(index)
    _SB_T5_INITID_LEN(index)
    _SB_T6_INITID_LEN(index)
    _SB_T7_INITID_LEN(index)
    _SB_T8_INITID_LEN(index)
    _SB_T9_INITID_LEN(index)
    _SB_T10_INITID_LEN(index)
    _SB_T11_INITID_LEN(index)
    _SB_T12_INITID_LEN(index)
    _SB_T13_INITID_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrInitID_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrInitID

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrInitID function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrInitID_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorInitiatorID_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorInitiatorID 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorInitiatorID function.
*/

PLIB_TEMPLATE PLIB_SB_INIT_ID SB_PGVErrorInitiatorID_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_FIELD_READ(_SB_T0_INITID_VREG(index) + ((0x400 * target) >> 2), _SB_T0_INITID_MASK(index), _SB_T0_INITID_POS(index));
}


#endif /*_SB_PGVERRINITID_DEFAULT_H*/

/******************************************************************************
 End of File
*/

