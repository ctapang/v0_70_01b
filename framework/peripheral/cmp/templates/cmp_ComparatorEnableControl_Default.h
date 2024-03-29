/*******************************************************************************
  CMP Peripheral Library Template Implementation

  File Name:
    cmp_ComparatorEnableControl_Default.h

  Summary:
    CMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ComparatorEnableControl
    and its Variant : Default
    For following APIs :
        PLIB_CMP_ExistsEnableControl
        PLIB_CMP_Enable
        PLIB_CMP_Disable

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

#ifndef _CMP_COMPARATORENABLECONTROL_DEFAULT_H
#define _CMP_COMPARATORENABLECONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CMP_CMP_ENABLE_CONTROL_VREG(index)

  MASKs: 
    _CMP_CMP_ENABLE_CONTROL_MASK(index)

  POSs: 
    _CMP_CMP_ENABLE_CONTROL_POS(index)

  LENs: 
    _CMP_CMP_ENABLE_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  CMP_ExistsEnableControl_Default

  Summary:
    Implements Default variant of PLIB_CMP_ExistsEnableControl

  Description:
    This template implements the Default variant of the PLIB_CMP_ExistsEnableControl function.
*/

PLIB_TEMPLATE bool CMP_ExistsEnableControl_Default( CMP_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  CMP_Enable_Default

  Summary:
    Implements Default variant of PLIB_CMP_Enable 

  Description:
    This template implements the Default variant of the PLIB_CMP_Enable function.
*/

PLIB_TEMPLATE void CMP_Enable_Default( CMP_MODULE_ID index )
{
    _SFR_BIT_SET(_CMP_CMP_ENABLE_CONTROL_VREG(index),  _CMP_CMP_ENABLE_CONTROL_POS(index));
}


//******************************************************************************
/* Function :  CMP_Disable_Default

  Summary:
    Implements Default variant of PLIB_CMP_Disable 

  Description:
    This template implements the Default variant of the PLIB_CMP_Disable function.
*/

PLIB_TEMPLATE void CMP_Disable_Default( CMP_MODULE_ID index )
{
    /* TODO  */
	_SFR_BIT_CLEAR(_CMP_CMP_ENABLE_CONTROL_VREG(index), _CMP_CMP_ENABLE_CONTROL_POS(index));
}


#endif /*_CMP_COMPARATORENABLECONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

