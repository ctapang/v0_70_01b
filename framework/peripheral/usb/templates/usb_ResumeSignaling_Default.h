/*******************************************************************************
  USB Peripheral Library Template Implementation

  File Name:
    usb_ResumeSignaling_Default.h

  Summary:
    USB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ResumeSignaling
    and its Variant : Default
    For following APIs :
        PLIB_USB_ResumeSignalingEnable
        PLIB_USB_ResumeSignalingDisable
        PLIB_USB_ExistsResumeSignaling

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

#ifndef _USB_RESUMESIGNALING_DEFAULT_H
#define _USB_RESUMESIGNALING_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USB_RESUME_SIGNALING_ON_VREG(index)

  MASKs: 
    _USB_RESUME_SIGNALING_ON_MASK(index)

  POSs: 
    _USB_RESUME_SIGNALING_ON_POS(index)

  LENs: 
    _USB_RESUME_SIGNALING_ON_LEN(index)

*/


//******************************************************************************
/* Function :  USB_ResumeSignalingEnable_Default

  Summary:
    Implements Default variant of PLIB_USB_ResumeSignalingEnable 

  Description:
    This template implements the Default variant of the PLIB_USB_ResumeSignalingEnable function.
*/

PLIB_TEMPLATE void USB_ResumeSignalingEnable_Default( USB_MODULE_ID index )
{
    _SFR_BIT_SET(_USB_RESUME_SIGNALING_ON_VREG(index),
                 _USB_RESUME_SIGNALING_ON_POS(index) );
}


//******************************************************************************
/* Function :  USB_ResumeSignalingDisable_Default

  Summary:
    Implements Default variant of PLIB_USB_ResumeSignalingDisable 

  Description:
    This template implements the Default variant of the PLIB_USB_ResumeSignalingDisable function.
*/

PLIB_TEMPLATE void USB_ResumeSignalingDisable_Default( USB_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_USB_RESUME_SIGNALING_ON_VREG(index),
                   _USB_RESUME_SIGNALING_ON_POS(index) );
}


//******************************************************************************
/* Function :  USB_ExistsResumeSignaling_Default

  Summary:
    Implements Default variant of PLIB_USB_ExistsResumeSignaling

  Description:
    This template implements the Default variant of the PLIB_USB_ExistsResumeSignaling function.
*/

PLIB_TEMPLATE bool USB_ExistsResumeSignaling_Default( USB_MODULE_ID index )
{
    return true;
}


#endif /*_USB_RESUMESIGNALING_DEFAULT_H*/

/******************************************************************************
 End of File
*/

