/*******************************************************************************
  POWER Peripheral Library Template Implementation

  File Name:
    power_DeepSleepPORStatus_Default.h

  Summary:
    POWER PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DeepSleepPORStatus
    and its Variant : Default
    For following APIs :
        PLIB_POWER_ExistsDeepSleepPowerOnReset
        PLIB_POWER_DeepSleepPowerOnResetStatus

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

#ifndef _POWER_DEEPSLEEPPORSTATUS_DEFAULT_H
#define _POWER_DEEPSLEEPPORSTATUS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _POWER_DEEP_SLEEP_POR_STATUS_VREG(index)

  MASKs: 
    _POWER_DEEP_SLEEP_POR_STATUS_MASK(index)

  POSs: 
    _POWER_DEEP_SLEEP_POR_STATUS_POS(index)

  LENs: 
    _POWER_DEEP_SLEEP_POR_STATUS_LEN(index)

*/


//******************************************************************************
/* Function :  POWER_ExistsDeepSleepPowerOnReset_Default

  Summary:
    Implements Default variant of PLIB_POWER_ExistsDeepSleepPowerOnReset

  Description:
    This template implements the Default variant of the PLIB_POWER_ExistsDeepSleepPowerOnReset function.
*/

PLIB_TEMPLATE bool POWER_ExistsDeepSleepPowerOnReset_Default( POWER_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  POWER_DeepSleepPowerOnResetStatus_Default

  Summary:
    Implements Default variant of PLIB_POWER_DeepSleepPowerOnResetStatus 

  Description:
    This template implements the Default variant of the PLIB_POWER_DeepSleepPowerOnResetStatus function.
*/

PLIB_TEMPLATE bool POWER_DeepSleepPowerOnResetStatus_Default( POWER_MODULE_ID index )
{
    /* TODO  */
}


#endif /*_POWER_DEEPSLEEPPORSTATUS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

