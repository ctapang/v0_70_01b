/*******************************************************************************
  IC Peripheral Library Template Implementation

  File Name:
    ic_CaptureMode_Default.h

  Summary:
    IC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : CaptureMode
    and its Variant : Default
    For following APIs :
        PLIB_IC_ModeSelect
        PLIB_IC_ExistsCaptureMode

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

#ifndef _IC_CAPTUREMODE_DEFAULT_H
#define _IC_CAPTUREMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _IC_CAPTURE_MODE_SELECT_VREG(index)

  MASKs: 
    _IC_CAPTURE_MODE_SELECT_MASK(index)

  POSs: 
    _IC_CAPTURE_MODE_SELECT_POS(index)

  LENs: 
    _IC_CAPTURE_MODE_SELECT_LEN(index)

*/


//******************************************************************************
/* Function :  IC_ModeSelect_Default

  Summary:
    Implements Default variant of PLIB_IC_ModeSelect 

  Description:
    This template implements the Default variant of the PLIB_IC_ModeSelect function.
*/

PLIB_TEMPLATE void IC_ModeSelect_Default( IC_MODULE_ID index , IC_INPUT_CAPTURE_MODES modeSel )
{
    _SFR_FIELD_WRITE(_IC_CAPTURE_MODE_SELECT_VREG(index),_IC_CAPTURE_MODE_SELECT_MASK(index),
					_IC_CAPTURE_MODE_SELECT_POS(index), modeSel);
}


//******************************************************************************
/* Function :  IC_ExistsCaptureMode_Default

  Summary:
    Implements Default variant of PLIB_IC_ExistsCaptureMode

  Description:
    This template implements the Default variant of the PLIB_IC_ExistsCaptureMode function.
*/

PLIB_TEMPLATE bool IC_ExistsCaptureMode_Default( IC_MODULE_ID index )
{
    return true;
}


#endif /*_IC_CAPTUREMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

