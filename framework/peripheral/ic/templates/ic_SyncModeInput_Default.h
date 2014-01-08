/*******************************************************************************
  IC Peripheral Library Template Implementation

  File Name:
    ic_SyncModeInput_Default.h

  Summary:
    IC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SyncModeInput
    and its Variant : Default
    For following APIs :
        PLIB_IC_SyncModeInputSelect
        PLIB_IC_ExistsSyncModeInput

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

#ifndef _IC_SYNCMODEINPUT_DEFAULT_H
#define _IC_SYNCMODEINPUT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _IC_SYNC_MODE_INPUT_VREG(index)

  MASKs: 
    _IC_SYNC_MODE_INPUT_MASK(index)

  POSs: 
    _IC_SYNC_MODE_INPUT_POS(index)

  LENs: 
    _IC_SYNC_MODE_INPUT_LEN(index)

*/


//******************************************************************************
/* Function :  IC_SyncModeInputSelect_Default

  Summary:
    Implements Default variant of PLIB_IC_SyncModeInputSelect 

  Description:
    This template implements the Default variant of the PLIB_IC_SyncModeInputSelect function.
*/

PLIB_TEMPLATE void IC_SyncModeInputSelect_Default( IC_MODULE_ID index , IC_SYNC_MODE_INPUTS input )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  IC_ExistsSyncModeInput_Default

  Summary:
    Implements Default variant of PLIB_IC_ExistsSyncModeInput

  Description:
    This template implements the Default variant of the PLIB_IC_ExistsSyncModeInput function.
*/

PLIB_TEMPLATE bool IC_ExistsSyncModeInput_Default( IC_MODULE_ID index )
{
    return true;
}


#endif /*_IC_SYNCMODEINPUT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

