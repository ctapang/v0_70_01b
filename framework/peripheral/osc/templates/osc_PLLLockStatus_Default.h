/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_PLLLockStatus_Default.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PLLLockStatus
    and its Variant : Default
    For following APIs :
        PLIB_OSC_ExistsPLLLockStatus
        PLIB_OSC_PLLIsLocked

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

#ifndef _OSC_PLLLOCKSTATUS_DEFAULT_H
#define _OSC_PLLLOCKSTATUS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_OSC_LOCK_STATUS_USB_VREG(index)
    _OSC_OSC_LOCK_STATUS_SYS_VREG(index)

  MASKs: 
    _OSC_OSC_LOCK_STATUS_USB_MASK(index)
    _OSC_OSC_LOCK_STATUS_SYS_MASK(index)

  POSs: 
    _OSC_OSC_LOCK_STATUS_USB_POS(index)
    _OSC_OSC_LOCK_STATUS_SYS_POS(index)

  LENs: 
    _OSC_OSC_LOCK_STATUS_USB_LEN(index)
    _OSC_OSC_LOCK_STATUS_SYS_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsPLLLockStatus_Default

  Summary:
    Implements Default variant of PLIB_OSC_ExistsPLLLockStatus

  Description:
    This template implements the Default variant of the PLIB_OSC_ExistsPLLLockStatus function.
*/

PLIB_TEMPLATE bool OSC_ExistsPLLLockStatus_Default( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_PLLIsLocked_Default

  Summary:
    Implements Default variant of PLIB_OSC_PLLIsLocked 

  Description:
    This template implements the Default variant of the PLIB_OSC_PLLIsLocked function.
*/

PLIB_TEMPLATE bool OSC_PLLIsLocked_Default( OSC_MODULE_ID index , OSC_PLL_SELECT pllselect )
{
    if (pllselect == OSC_PLL_USB)
    {
        return _SFR_BIT_READ(_OSC_OSC_LOCK_STATUS_USB_VREG(index),
                            _OSC_OSC_LOCK_STATUS_USB_POS(index) );
    }
    return _SFR_BIT_READ(_OSC_OSC_LOCK_STATUS_SYS_VREG(index),
                             _OSC_OSC_LOCK_STATUS_SYS_POS(index) );
}


#endif /*_OSC_PLLLOCKSTATUS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

