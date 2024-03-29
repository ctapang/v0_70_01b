/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_EnableControl_Default.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : EnableControl
    and its Variant : Default
    For following APIs :
        PLIB_CAN_Enable
        PLIB_CAN_Disable
        PLIB_CAN_ExistsEnableControl

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

#ifndef _CAN_ENABLECONTROL_DEFAULT_H
#define _CAN_ENABLECONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_ENABLE_CONTROL_VREG(index)

  MASKs: 
    _CAN_ENABLE_CONTROL_MASK(index)

  POSs: 
    _CAN_ENABLE_CONTROL_POS(index)

  LENs: 
    _CAN_ENABLE_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_Enable_Default

  Summary:
    Implements Default variant of PLIB_CAN_Enable 

  Description:
    This template implements the Default variant of the PLIB_CAN_Enable function.
*/

PLIB_TEMPLATE void CAN_Enable_Default( CAN_MODULE_ID index )
{
    _SFR_BIT_SET(_CAN_ENABLE_CONTROL_VREG(index),
                     _CAN_ENABLE_CONTROL_POS(index) );
}


//******************************************************************************
/* Function :  CAN_Disable_Default

  Summary:
    Implements Default variant of PLIB_CAN_Disable 

  Description:
    This template implements the Default variant of the PLIB_CAN_Disable function.
*/

PLIB_TEMPLATE void CAN_Disable_Default( CAN_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_CAN_ENABLE_CONTROL_VREG(index),
                     _CAN_ENABLE_CONTROL_POS(index) );
}


//******************************************************************************
/* Function :  CAN_ExistsEnableControl_Default

  Summary:
    Implements Default variant of PLIB_CAN_ExistsEnableControl

  Description:
    This template implements the Default variant of the PLIB_CAN_ExistsEnableControl function.
*/

PLIB_TEMPLATE bool CAN_ExistsEnableControl_Default( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_ENABLECONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

