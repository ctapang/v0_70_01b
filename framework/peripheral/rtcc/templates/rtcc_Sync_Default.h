/*******************************************************************************
  RTCC Peripheral Library Template Implementation

  File Name:
    rtcc_Sync_Default.h

  Summary:
    RTCC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Sync
    and its Variant : Default
    For following APIs :
        PLIB_RTCC_RTCSyncStatusGet
        PLIB_RTCC_ExistsSynchronization

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

#ifndef _RTCC_SYNC_DEFAULT_H
#define _RTCC_SYNC_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _RTCC_SYNC_VREG(index)

  MASKs: 
    _RTCC_SYNC_MASK(index)

  POSs: 
    _RTCC_SYNC_POS(index)

  LENs: 
    _RTCC_SYNC_LEN(index)

*/


//******************************************************************************
/* Function :  RTCC_RTCSyncStatusGet_Default

  Summary:
    Implements Default variant of PLIB_RTCC_RTCSyncStatusGet 

  Description:
    This template implements the Default variant of the PLIB_RTCC_RTCSyncStatusGet function.
*/

PLIB_TEMPLATE bool RTCC_RTCSyncStatusGet_Default( RTCC_MODULE_ID index )
{
    return _SFR_BIT_READ( _RTCC_SYNC_VREG( index ), 
	                      _RTCC_SYNC_POS( index ) );
}


//******************************************************************************
/* Function :  RTCC_ExistsSynchronization_Default

  Summary:
    Implements Default variant of PLIB_RTCC_ExistsSynchronization

  Description:
    This template implements the Default variant of the PLIB_RTCC_ExistsSynchronization function.
*/

PLIB_TEMPLATE bool RTCC_ExistsSynchronization_Default( RTCC_MODULE_ID index )
{
    return true;
}


#endif /*_RTCC_SYNC_DEFAULT_H*/

/******************************************************************************
 End of File
*/

