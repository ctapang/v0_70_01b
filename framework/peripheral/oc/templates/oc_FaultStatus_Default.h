/*******************************************************************************
  OC Peripheral Library Template Implementation

  File Name:
    oc_FaultStatus_Default.h

  Summary:
    OC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : FaultStatus
    and its Variant : Default
    For following APIs :
        PLIB_OC_FaultHasOccurred
        PLIB_OC_ExistsFaultStatus

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

#ifndef _OC_FAULTSTATUS_DEFAULT_H
#define _OC_FAULTSTATUS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OC_FAULT_STATUS_VREG(index)

  MASKs: 
    _OC_FAULT_STATUS_MASK(index)

  POSs: 
    _OC_FAULT_STATUS_POS(index)

  LENs: 
    _OC_FAULT_STATUS_LEN(index)

*/


//******************************************************************************
/* Function :  OC_FaultHasOccurred_Default

  Summary:
    Implements Default variant of PLIB_OC_FaultHasOccurred 

  Description:
    This template implements the Default variant of the PLIB_OC_FaultHasOccurred function.
*/

PLIB_TEMPLATE bool OC_FaultHasOccurred_Default( OC_MODULE_ID index )
{
    return (_SFR_BIT_READ(_OC_FAULT_STATUS_VREG(index),_OC_FAULT_STATUS_POS(index)));
}


//******************************************************************************
/* Function :  OC_ExistsFaultStatus_Default

  Summary:
    Implements Default variant of PLIB_OC_ExistsFaultStatus

  Description:
    This template implements the Default variant of the PLIB_OC_ExistsFaultStatus function.
*/

PLIB_TEMPLATE bool OC_ExistsFaultStatus_Default( OC_MODULE_ID index )
{
    return true;
}


#endif /*_OC_FAULTSTATUS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

