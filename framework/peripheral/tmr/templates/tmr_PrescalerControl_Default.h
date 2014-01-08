/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_PrescalerControl_Default.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PrescalerControl
    and its Variant : Default
    For following APIs :
        PLIB_TMR_PrescalerEnable
        PLIB_TMR_PrescalerDisable
        PLIB_TMR_ExistsPrescalerAssignment

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

#ifndef _TMR_PRESCALERCONTROL_DEFAULT_H
#define _TMR_PRESCALERCONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_PRESCALER_CONTROL_VREG(index)

  MASKs: 
    _TMR_PRESCALER_CONTROL_MASK(index)

  POSs: 
    _TMR_PRESCALER_CONTROL_POS(index)

  LENs: 
    _TMR_PRESCALER_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_PrescalerEnable_Default

  Summary:
    Implements Default variant of PLIB_TMR_PrescalerEnable 

  Description:
    This template implements the Default variant of the PLIB_TMR_PrescalerEnable function.
*/

PLIB_TEMPLATE void TMR_PrescalerEnable_Default( TMR_MODULE_ID index )
{
    _SFR_BIT_CLEAR( _TMR_PRESCALER_CONTROL_VREG( index ),
                    _TMR_PRESCALER_CONTROL_POS( index ) );
}


//******************************************************************************
/* Function :  TMR_PrescalerDisable_Default

  Summary:
    Implements Default variant of PLIB_TMR_PrescalerDisable 

  Description:
    This template implements the Default variant of the PLIB_TMR_PrescalerDisable function.
*/

PLIB_TEMPLATE void TMR_PrescalerDisable_Default( TMR_MODULE_ID index )
{
    _SFR_BIT_SET( _TMR_PRESCALER_CONTROL_VREG( index ),
                  _TMR_PRESCALER_CONTROL_POS( index ) );
}


//******************************************************************************
/* Function :  TMR_ExistsPrescalerAssignment_Default

  Summary:
    Implements Default variant of PLIB_TMR_ExistsPrescalerAssignment

  Description:
    This template implements the Default variant of the PLIB_TMR_ExistsPrescalerAssignment function.
*/

PLIB_TEMPLATE bool TMR_ExistsPrescalerAssignment_Default( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_PRESCALERCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

