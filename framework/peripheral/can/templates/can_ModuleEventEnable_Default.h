/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_ModuleEventEnable_Default.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ModuleEventEnable
    and its Variant : Default
    For following APIs :
        PLIB_CAN_ModuleEventEnable
        PLIB_CAN_ModuleEventDisable
        PLIB_CAN_ExistsModuleEventEnable

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

#ifndef _CAN_MODULEEVENTENABLE_DEFAULT_H
#define _CAN_MODULEEVENTENABLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_MODULE_EVENT_ENABLE_IVRIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_WAKIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_CERRIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_SERRIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_RBOVIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_MODIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_CTMRIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_RBIE_VREG(index)
    _CAN_MODULE_EVENT_ENABLE_TBIE_VREG(index)

  MASKs: 
    _CAN_MODULE_EVENT_ENABLE_IVRIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_WAKIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_CERRIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_SERRIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_RBOVIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_MODIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_CTMRIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_RBIE_MASK(index)
    _CAN_MODULE_EVENT_ENABLE_TBIE_MASK(index)

  POSs: 
    _CAN_MODULE_EVENT_ENABLE_IVRIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_WAKIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_CERRIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_SERRIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_RBOVIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_MODIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_CTMRIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_RBIE_POS(index)
    _CAN_MODULE_EVENT_ENABLE_TBIE_POS(index)

  LENs: 
    _CAN_MODULE_EVENT_ENABLE_IVRIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_WAKIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_CERRIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_SERRIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_RBOVIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_MODIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_CTMRIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_RBIE_LEN(index)
    _CAN_MODULE_EVENT_ENABLE_TBIE_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_ModuleEventEnable_Default

  Summary:
    Implements Default variant of PLIB_CAN_ModuleEventEnable 

  Description:
    This template implements the Default variant of the PLIB_CAN_ModuleEventEnable function.
*/

PLIB_TEMPLATE void CAN_ModuleEventEnable_Default( CAN_MODULE_ID index , CAN_MODULE_EVENT flags )
{
    _SFR_FIELD_WRITE(_CAN_MODULE_EVENT_ENABLE_TBIE_VREG(index),
                         (CAN_All_EVENTS << _CAN_MODULE_EVENT_ENABLE_TBIE_POS(index)),
                         _CAN_MODULE_EVENT_ENABLE_TBIE_POS(index) ,
                         flags                      );
}


//******************************************************************************
/* Function :  CAN_ModuleEventDisable_Default

  Summary:
    Implements Default variant of PLIB_CAN_ModuleEventDisable 

  Description:
    This template implements the Default variant of the PLIB_CAN_ModuleEventDisable function.
*/

PLIB_TEMPLATE void CAN_ModuleEventDisable_Default( CAN_MODULE_ID index , CAN_MODULE_EVENT flags )
{
    _SFR_FIELD_CLEAR(_CAN_MODULE_EVENT_ENABLE_TBIE_VREG(index),
                         (CAN_All_EVENTS << _CAN_MODULE_EVENT_ENABLE_TBIE_POS(index)),
                         _CAN_MODULE_EVENT_ENABLE_TBIE_POS(index) ,
                         flags   );
}


//******************************************************************************
/* Function :  CAN_ExistsModuleEventEnable_Default

  Summary:
    Implements Default variant of PLIB_CAN_ExistsModuleEventEnable

  Description:
    This template implements the Default variant of the PLIB_CAN_ExistsModuleEventEnable function.
*/

PLIB_TEMPLATE bool CAN_ExistsModuleEventEnable_Default( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_MODULEEVENTENABLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

