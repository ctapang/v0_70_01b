/*******************************************************************************
  ADCP Peripheral Library Template Implementation

  File Name:
    adcp_DigitalComparator_Default.h

  Summary:
    ADCP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DigitalComparator
    and its Variant : Default
    For following APIs :
        PLIB_ADCP_DigCmpConfig
        PLIB_ADCP_DigCmpEnable
        PLIB_ADCP_DigCmpDisable
        PLIB_ADCP_DigCmpAIdGet
        PLIB_ADCP_ExistsDigCmp

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

#ifndef _ADCP_DIGITALCOMPARATOR_DEFAULT_H
#define _ADCP_DIGITALCOMPARATOR_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADCP_EVENT_ON_LESS_THAN_LOW1_VREG(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_VREG(index)
    _ADCP_EVENT_ON_LESS_THAN_HIGH1_VREG(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_VREG(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_VREG(index)
    _ADCP_DCMP_GLOBAL_INT_ENABLE1_VREG(index)
    _ADCP_EVENT_DETECTED1_VREG(index)
    _ADCP_DCMP_ENABLE_CONTROL1_VREG(index)
    _ADCP_ANALOG_INPUT_ID1_VREG(index)
    _ADCP_DCMP_INPUT_ENABLE1_VREG(index)
    _ADCP_DCMP_HIGH_LIMIT1_VREG(index)
    _ADCP_DCMP_LO_LIMIT1_VREG(index)

  MASKs: 
    _ADCP_EVENT_ON_LESS_THAN_LOW1_MASK(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_MASK(index)
    _ADCP_EVENT_ON_LESS_THAN_HIGH1_MASK(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_MASK(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_MASK(index)
    _ADCP_DCMP_GLOBAL_INT_ENABLE1_MASK(index)
    _ADCP_EVENT_DETECTED1_MASK(index)
    _ADCP_DCMP_ENABLE_CONTROL1_MASK(index)
    _ADCP_ANALOG_INPUT_ID1_MASK(index)
    _ADCP_DCMP_INPUT_ENABLE1_MASK(index)
    _ADCP_DCMP_HIGH_LIMIT1_MASK(index)
    _ADCP_DCMP_LO_LIMIT1_MASK(index)

  POSs: 
    _ADCP_EVENT_ON_LESS_THAN_LOW1_POS(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_POS(index)
    _ADCP_EVENT_ON_LESS_THAN_HIGH1_POS(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_POS(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_POS(index)
    _ADCP_DCMP_GLOBAL_INT_ENABLE1_POS(index)
    _ADCP_EVENT_DETECTED1_POS(index)
    _ADCP_DCMP_ENABLE_CONTROL1_POS(index)
    _ADCP_ANALOG_INPUT_ID1_POS(index)
    _ADCP_DCMP_INPUT_ENABLE1_POS(index)
    _ADCP_DCMP_HIGH_LIMIT1_POS(index)
    _ADCP_DCMP_LO_LIMIT1_POS(index)

  LENs: 
    _ADCP_EVENT_ON_LESS_THAN_LOW1_LEN(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_LEN(index)
    _ADCP_EVENT_ON_LESS_THAN_HIGH1_LEN(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_LEN(index)
    _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_LEN(index)
    _ADCP_DCMP_GLOBAL_INT_ENABLE1_LEN(index)
    _ADCP_EVENT_DETECTED1_LEN(index)
    _ADCP_DCMP_ENABLE_CONTROL1_LEN(index)
    _ADCP_ANALOG_INPUT_ID1_LEN(index)
    _ADCP_DCMP_INPUT_ENABLE1_LEN(index)
    _ADCP_DCMP_HIGH_LIMIT1_LEN(index)
    _ADCP_DCMP_LO_LIMIT1_LEN(index)

 */


//******************************************************************************

/* Function :  ADCP_DigCmpConfig_Default

  Summary:
    Implements Default variant of PLIB_ADCP_DigCmpConfig 

  Description:
    This template implements the Default variant of the PLIB_ADCP_DigCmpConfig function.
 */

PLIB_TEMPLATE void ADCP_DigCmpConfig_Default(ADCP_MODULE_ID index, ADCP_DCMP_ID id, bool globalIntEnable, bool inBetweenOrEqual, bool greaterEqualHi, bool lessThanHi, bool greaterEqualLo, bool lessThanLo, uint32_t inputEnable, int32_t hiLimit, int32_t loLimit) {
    _SFR_BIT_WRITE(_ADCP_DCMP_GLOBAL_INT_ENABLE1_VREG(index) + id, _ADCP_DCMP_GLOBAL_INT_ENABLE1_POS(index), globalIntEnable);
    _SFR_BIT_WRITE(_ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_VREG(index) + id, _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW_LESS_THAN_HIGH1_POS(index), inBetweenOrEqual);
    _SFR_BIT_WRITE(_ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_VREG(index) + id, _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_HIGH1_POS(index), greaterEqualHi);
    _SFR_BIT_WRITE(_ADCP_EVENT_ON_LESS_THAN_HIGH1_VREG(index) + id, _ADCP_EVENT_ON_LESS_THAN_HIGH1_POS(index), lessThanHi);
    _SFR_BIT_WRITE(_ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_VREG(index) + id, _ADCP_EVENT_ON_GREATER_THAN_EQUAL_TO_LOW1_POS(index), greaterEqualLo);
    _SFR_BIT_WRITE(_ADCP_EVENT_ON_LESS_THAN_LOW1_VREG(index) + id, _ADCP_EVENT_ON_LESS_THAN_LOW1_POS(index), lessThanLo);
    _SFR_WRITE(_ADCP_CMP_ENABLE_0_VREG(index) + (id * 2), inputEnable);
    _SFR_FIELD_WRITE(_ADCP_DCMP_HIGH_LIMIT1_VREG(index) + (id * 2), _ADCP_DCMP_HIGH_LIMIT1_MASK(index), _ADCP_DCMP_HIGH_LIMIT1_POS(index), hiLimit);
    _SFR_FIELD_WRITE(_ADCP_DCMP_LO_LIMIT1_VREG(index) + (id * 2), _ADCP_DCMP_LO_LIMIT1_MASK(index), _ADCP_DCMP_LO_LIMIT1_POS(index), loLimit);
}


//    _ADCP_EVENT_DETECTED1_VREG(index)
//    _ADCP_DCMP_ENABLE_CONTROL1_VREG(index)
//    _ADCP_ANALOG_INPUT_ID1_VREG(index)



//******************************************************************************

/* Function :  ADCP_DigCmpEnable_Default

  Summary:
    Implements Default variant of PLIB_ADCP_DigCmpEnable 

  Description:
    This template implements the Default variant of the PLIB_ADCP_DigCmpEnable function.
 */

PLIB_TEMPLATE void ADCP_DigCmpEnable_Default(ADCP_MODULE_ID index, ADCP_DCMP_ID id) {
    _SFR_BIT_WRITE(_ADCP_DCMP_ENABLE1_VREG(index) + id, _ADCP_DCMP_ENABLE1_POS(index), 1);
}


//******************************************************************************

/* Function :  ADCP_DigCmpDisable_Default

  Summary:
    Implements Default variant of PLIB_ADCP_DigCmpDisable 

  Description:
    This template implements the Default variant of the PLIB_ADCP_DigCmpDisable function.
 */

PLIB_TEMPLATE void ADCP_DigCmpDisable_Default(ADCP_MODULE_ID index, ADCP_DCMP_ID id) {
    _SFR_BIT_WRITE(_ADCP_DCMP_ENABLE1_VREG(index) + id, _ADCP_DCMP_ENABLE1_POS(index), 0);

}


//******************************************************************************

/* Function :  ADCP_DigCmpAIdGet_Default

  Summary:
    Implements Default variant of PLIB_ADCP_DigCmpAIdGet 

  Description:
    This template implements the Default variant of the PLIB_ADCP_DigCmpAIdGet function.
 */

PLIB_TEMPLATE int16_t ADCP_DigCmpAIdGet_Default(ADCP_MODULE_ID index, ADCP_DCMP_ID id) {
    if (_SFR_BIT_READ(_ADCP_EVENT_DETECTED1_VREG(index) + id, _ADCP_EVENT_DETECTED1_POS(index)) == 1)
        return _SFR_FIELD_READ(_ADCP_ANALOG_INPUT_ID1_VREG(index) + id, _ADCP_ANALOG_INPUT_ID1_MASK(index), _ADCP_ANALOG_INPUT_ID1_POS(index));
    else
        return -1;
}


//******************************************************************************

/* Function :  ADCP_ExistsDigCmp_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ExistsDigCmp

  Description:
    This template implements the Default variant of the PLIB_ADCP_ExistsDigCmp function.
 */

PLIB_TEMPLATE bool ADCP_ExistsDigCmp_Default(ADCP_MODULE_ID index) {
    return true;
}


#endif /*_ADCP_DIGITALCOMPARATOR_DEFAULT_H*/

/******************************************************************************
 End of File
 */

