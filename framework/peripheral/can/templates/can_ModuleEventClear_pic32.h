/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_ModuleEventClear_pic32.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ModuleEventClear
    and its Variant : pic32
    For following APIs :
        PLIB_CAN_ModuleEventClear
        PLIB_CAN_ExistsModuleEventClear

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

#ifndef _CAN_MODULEEVENTCLEAR_PIC32_H
#define _CAN_MODULEEVENTCLEAR_PIC32_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_MODULE_EVENT_GET1_VREG(index)
    _CAN_MODULE_EVENT_GET2_VREG(index)
    _CAN_MODULE_EVENT_GET3_VREG(index)
    _CAN_MODULE_EVENT_GET4_VREG(index)
    _CAN_MODULE_EVENT_GET5_VREG(index)
    _CAN_MODULE_EVENT_GET6_VREG(index)
    _CAN_MODULE_EVENT_GET7_VREG(index)

  MASKs: 
    _CAN_MODULE_EVENT_GET1_MASK(index)
    _CAN_MODULE_EVENT_GET2_MASK(index)
    _CAN_MODULE_EVENT_GET3_MASK(index)
    _CAN_MODULE_EVENT_GET4_MASK(index)
    _CAN_MODULE_EVENT_GET5_MASK(index)
    _CAN_MODULE_EVENT_GET6_MASK(index)
    _CAN_MODULE_EVENT_GET7_MASK(index)

  POSs: 
    _CAN_MODULE_EVENT_GET1_POS(index)
    _CAN_MODULE_EVENT_GET2_POS(index)
    _CAN_MODULE_EVENT_GET3_POS(index)
    _CAN_MODULE_EVENT_GET4_POS(index)
    _CAN_MODULE_EVENT_GET5_POS(index)
    _CAN_MODULE_EVENT_GET6_POS(index)
    _CAN_MODULE_EVENT_GET7_POS(index)

  LENs: 
    _CAN_MODULE_EVENT_GET1_LEN(index)
    _CAN_MODULE_EVENT_GET2_LEN(index)
    _CAN_MODULE_EVENT_GET3_LEN(index)
    _CAN_MODULE_EVENT_GET4_LEN(index)
    _CAN_MODULE_EVENT_GET5_LEN(index)
    _CAN_MODULE_EVENT_GET6_LEN(index)
    _CAN_MODULE_EVENT_GET7_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_ModuleEventClear_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ModuleEventClear 

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ModuleEventClear function.
*/

PLIB_TEMPLATE void CAN_ModuleEventClear_pic32( CAN_MODULE_ID index , CAN_MODULE_EVENT flags )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  CAN_ExistsModuleEventClear_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ExistsModuleEventClear

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ExistsModuleEventClear function.
*/

PLIB_TEMPLATE bool CAN_ExistsModuleEventClear_pic32( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_MODULEEVENTCLEAR_PIC32_H*/

/******************************************************************************
 End of File
*/

