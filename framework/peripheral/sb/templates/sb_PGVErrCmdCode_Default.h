/*******************************************************************************
  SB Peripheral Library Template Implementation

  File Name:
    sb_PGVErrCmdCode_Default.h

  Summary:
    SB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PGVErrCmdCode
    and its Variant : Default
    For following APIs :
        PLIB_SB_ExistsPGVErrCmdCode
        PLIB_SB_PGVErrorCommandCode

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

#ifndef _SB_PGVERRCMDCODE_DEFAULT_H
#define _SB_PGVERRCMDCODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SB_T0_CMD_VREG(index)
    _SB_T1_CMD_VREG(index)
    _SB_T2_CMD_VREG(index)
    _SB_T3_CMD_VREG(index)
    _SB_T4_CMD_VREG(index)
    _SB_T5_CMD_VREG(index)
    _SB_T6_CMD_VREG(index)
    _SB_T7_CMD_VREG(index)
    _SB_T8_CMD_VREG(index)
    _SB_T9_CMD_VREG(index)
    _SB_T10_CMD_VREG(index)
    _SB_T11_CMD_VREG(index)
    _SB_T12_CMD_VREG(index)
    _SB_T13_CMD_VREG(index)

  MASKs: 
    _SB_T0_CMD_MASK(index)
    _SB_T1_CMD_MASK(index)
    _SB_T2_CMD_MASK(index)
    _SB_T3_CMD_MASK(index)
    _SB_T4_CMD_MASK(index)
    _SB_T5_CMD_MASK(index)
    _SB_T6_CMD_MASK(index)
    _SB_T7_CMD_MASK(index)
    _SB_T8_CMD_MASK(index)
    _SB_T9_CMD_MASK(index)
    _SB_T10_CMD_MASK(index)
    _SB_T11_CMD_MASK(index)
    _SB_T12_CMD_MASK(index)
    _SB_T13_CMD_MASK(index)

  POSs: 
    _SB_T0_CMD_POS(index)
    _SB_T1_CMD_POS(index)
    _SB_T2_CMD_POS(index)
    _SB_T3_CMD_POS(index)
    _SB_T4_CMD_POS(index)
    _SB_T5_CMD_POS(index)
    _SB_T6_CMD_POS(index)
    _SB_T7_CMD_POS(index)
    _SB_T8_CMD_POS(index)
    _SB_T9_CMD_POS(index)
    _SB_T10_CMD_POS(index)
    _SB_T11_CMD_POS(index)
    _SB_T12_CMD_POS(index)
    _SB_T13_CMD_POS(index)

  LENs: 
    _SB_T0_CMD_LEN(index)
    _SB_T1_CMD_LEN(index)
    _SB_T2_CMD_LEN(index)
    _SB_T3_CMD_LEN(index)
    _SB_T4_CMD_LEN(index)
    _SB_T5_CMD_LEN(index)
    _SB_T6_CMD_LEN(index)
    _SB_T7_CMD_LEN(index)
    _SB_T8_CMD_LEN(index)
    _SB_T9_CMD_LEN(index)
    _SB_T10_CMD_LEN(index)
    _SB_T11_CMD_LEN(index)
    _SB_T12_CMD_LEN(index)
    _SB_T13_CMD_LEN(index)

*/


//******************************************************************************
/* Function :  SB_ExistsPGVErrCmdCode_Default

  Summary:
    Implements Default variant of PLIB_SB_ExistsPGVErrCmdCode

  Description:
    This template implements the Default variant of the PLIB_SB_ExistsPGVErrCmdCode function.
*/

PLIB_TEMPLATE bool SB_ExistsPGVErrCmdCode_Default( SB_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  SB_PGVErrorCommandCode_Default

  Summary:
    Implements Default variant of PLIB_SB_PGVErrorCommandCode 

  Description:
    This template implements the Default variant of the PLIB_SB_PGVErrorCommandCode function.
*/

PLIB_TEMPLATE PLIB_SB_OCP_CMD_CODE SB_PGVErrorCommandCode_Default( SB_MODULE_ID index , PLIB_SB_TGT_ID target )
{
    return _SFR_FIELD_READ(_SB_T0_CMD_VREG(index) + ((0x400 * target) >> 2), _SB_T0_CMD_MASK(index), _SB_T0_CMD_POS(index));
}


#endif /*_SB_PGVERRCMDCODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

