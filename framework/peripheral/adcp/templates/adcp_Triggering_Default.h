/*******************************************************************************
  ADCP Peripheral Library Template Implementation

  File Name:
    adcp_Triggering_Default.h

  Summary:
    ADCP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Triggering
    and its Variant : Default
    For following APIs :
        PLIB_ADCP_Class12TriggerConfigure
        PLIB_ADCP_GlobalSoftwareTrigger
        PLIB_ADCP_IndividualTrigger
        PLIB_ADCP_ExistsTriggering

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

#ifndef _ADCP_TRIGGERING_DEFAULT_H
#define _ADCP_TRIGGERING_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADCP_GLOBAL_SW_TRIGGER_VREG(index)
    _ADCP_REQ_CNVRT_INPUT_SELECT_VREG(index)
    _ADCP_REQ_CNVRT_VREG(index)
    _ADCP_TRIGGER_SOURCE0_VREG(index)

  MASKs: 
    _ADCP_GLOBAL_SW_TRIGGER_MASK(index)
    _ADCP_REQ_CNVRT_INPUT_SELECT_MASK(index)
    _ADCP_REQ_CNVRT_MASK(index)
    _ADCP_TRIGGER_SOURCE0_MASK(index)

  POSs: 
    _ADCP_GLOBAL_SW_TRIGGER_POS(index)
    _ADCP_REQ_CNVRT_INPUT_SELECT_POS(index)
    _ADCP_REQ_CNVRT_POS(index)
    _ADCP_TRIGGER_SOURCE0_POS(index)

  LENs: 
    _ADCP_GLOBAL_SW_TRIGGER_LEN(index)
    _ADCP_REQ_CNVRT_INPUT_SELECT_LEN(index)
    _ADCP_REQ_CNVRT_LEN(index)
    _ADCP_TRIGGER_SOURCE0_LEN(index)

 */


//******************************************************************************

/* Function :  ADCP_Class12TriggerConfigure_Default

  Summary:
    Implements Default variant of PLIB_ADCP_Class12TriggerConfigure 

  Description:
    This template implements the Default variant of the PLIB_ADCP_Class12TriggerConfigure function.
 */

PLIB_TEMPLATE void ADCP_Class12TriggerConfigure_Default(ADCP_MODULE_ID index, ADCP_CLASS12_INPUT_ID inputId, ADCP_TRG_SRC triggerSource) {
    _SFR_FIELD_WRITE(_ADCP_TRIGGER_SOURCE0_VREG(index)+ (inputId / 4),
            _ADCP_TRIGGER_SOURCE0_MASK(index) << ((inputId % 4) * _ADCP_TRIGGER_SOURCE1_POS(index)),
            _ADCP_TRIGGER_SOURCE1_POS(index) * (inputId % 4),
            triggerSource);
}


//******************************************************************************

/* Function :  ADCP_GlobalSoftwareTrigger_Default

  Summary:
    Implements Default variant of PLIB_ADCP_GlobalSoftwareTrigger 

  Description:
    This template implements the Default variant of the PLIB_ADCP_GlobalSoftwareTrigger function.
 */

PLIB_TEMPLATE void ADCP_GlobalSoftwareTrigger_Default(ADCP_MODULE_ID index) {
    _SFR_BIT_WRITE(_ADCP_GLOBAL_SW_TRIGGER_VREG(index),_ADCP_GLOBAL_SW_TRIGGER_POS(index),1);
}


//******************************************************************************

/* Function :  ADCP_IndividualTrigger_Default

  Summary:
    Implements Default variant of PLIB_ADCP_IndividualTrigger 

  Description:
    This template implements the Default variant of the PLIB_ADCP_IndividualTrigger function.
 */

PLIB_TEMPLATE void ADCP_IndividualTrigger_Default(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId) {
    _SFR_FIELD_WRITE(_ADCP_REQ_CNVRT_INPUT_SELECT_VREG(index),
            _ADCP_REQ_CNVRT_INPUT_SELECT_MASK(index),
            _ADCP_REQ_CNVRT_INPUT_SELECT_POS(index),
            inputId);
    _SFR_BIT_WRITE(_ADCP_REQ_CNVRT_VREG(index),
            _ADCP_REQ_CNVRT_POS(index),
            1);
}


//******************************************************************************

/* Function :  ADCP_ExistsTriggering_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ExistsTriggering

  Description:
    This template implements the Default variant of the PLIB_ADCP_ExistsTriggering function.
 */

PLIB_TEMPLATE bool ADCP_ExistsTriggering_Default(ADCP_MODULE_ID index) {
    return true;
}


#endif /*_ADCP_TRIGGERING_DEFAULT_H*/

/******************************************************************************
 End of File
 */

