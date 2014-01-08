/*******************************************************************************
  OC Peripheral Library Template Implementation

  File Name:
    oc_TriggerControl_Default.h

  Summary:
    OC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TriggerControl
    and its Variant : Default
    For following APIs :
        PLIB_OC_TriggerSet
        PLIB_OC_TriggerClear
        PLIB_OC_ExistsTriggerControl

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _OC_TRIGGERCONTROL_DEFAULT_H
#define _OC_TRIGGERCONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OC_TRIG_CONTROL_VREG(index)

  MASKs: 
    _OC_TRIG_CONTROL_MASK(index)

  POSs: 
    _OC_TRIG_CONTROL_POS(index)

  LENs: 
    _OC_TRIG_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  OC_TriggerSet_Default

  Summary:
    Implements Default variant of PLIB_OC_TriggerSet 

  Description:
    This template implements the Default variant of the PLIB_OC_TriggerSet function.
*/

PLIB_TEMPLATE void OC_TriggerSet_Default( OC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  OC_TriggerClear_Default

  Summary:
    Implements Default variant of PLIB_OC_TriggerClear 

  Description:
    This template implements the Default variant of the PLIB_OC_TriggerClear function.
*/

PLIB_TEMPLATE void OC_TriggerClear_Default( OC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  OC_ExistsTriggerControl_Default

  Summary:
    Implements Default variant of PLIB_OC_ExistsTriggerControl

  Description:
    This template implements the Default variant of the PLIB_OC_ExistsTriggerControl function.
*/

PLIB_TEMPLATE bool OC_ExistsTriggerControl_Default( OC_MODULE_ID index )
{
    return true;
}


#endif /*_OC_TRIGGERCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

