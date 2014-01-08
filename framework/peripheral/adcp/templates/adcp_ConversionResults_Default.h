/*******************************************************************************
  ADCP Peripheral Library Template Implementation

  File Name:
    adcp_ConversionResults_Default.h

  Summary:
    ADCP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ConversionResults
    and its Variant : Default
    For following APIs :
        PLIB_ADCP_ResultReady
        PLIB_ADCP_ResultGet
        PLIB_ADCP_ResultReadyGrpIntConfigure
        PLIB_ADCP_ExistsConversionResults

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

#ifndef _ADCP_CONVERSIONRESULTS_DEFAULT_H
#define _ADCP_CONVERSIONRESULTS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADCP_GLOBAL_IRQ_ENABLE_HIGH_VREG(index)
    _ADCP_GLOBAL_IRQ_ENABLE_LOW_VREG(index)
    _ADCP_DATA_READY_STATUS_HIGH_VREG(index)
    _ADCP_DATA_READY_STATUS_LOW_VREG(index)
    _ADCP_AD_DATA0_VREG(index)

  MASKs: 
    _ADCP_GLOBAL_IRQ_ENABLE_HIGH_MASK(index)
    _ADCP_GLOBAL_IRQ_ENABLE_LOW_MASK(index)
    _ADCP_DATA_READY_STATUS_HIGH_MASK(index)
    _ADCP_DATA_READY_STATUS_LOW_MASK(index)
    _ADCP_AD_DATA0_MASK(index)

  POSs: 
    _ADCP_GLOBAL_IRQ_ENABLE_HIGH_POS(index)
    _ADCP_GLOBAL_IRQ_ENABLE_LOW_POS(index)
    _ADCP_DATA_READY_STATUS_HIGH_POS(index)
    _ADCP_DATA_READY_STATUS_LOW_POS(index)
    _ADCP_AD_DATA0_POS(index)

  LENs: 
    _ADCP_GLOBAL_IRQ_ENABLE_HIGH_LEN(index)
    _ADCP_GLOBAL_IRQ_ENABLE_LOW_LEN(index)
    _ADCP_DATA_READY_STATUS_HIGH_LEN(index)
    _ADCP_DATA_READY_STATUS_LOW_LEN(index)
    _ADCP_AD_DATA0_LEN(index)

 */


//******************************************************************************

/* Function :  ADCP_ResultReady_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ResultReady 

  Description:
    This template implements the Default variant of the PLIB_ADCP_ResultReady function.
 */

PLIB_TEMPLATE AN_READY ADCP_ResultReady_Default(ADCP_MODULE_ID index) {
    AN_READY ret_val;
    ret_val.lowWord = _SFR_READ(_ADCP_DATA_READY_0_VREG(index));
    ret_val.highWord = _SFR_READ(_ADCP_DATA_READY_44_VREG(index));
    return ret_val;
}


//******************************************************************************

/* Function :  ADCP_ResultGet_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ResultGet 

  Description:
    This template implements the Default variant of the PLIB_ADCP_ResultGet function.
 */

PLIB_TEMPLATE int32_t ADCP_ResultGet_Default(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId) {
    return _SFR_READ(_ADCP_AD_DATA0_VREG(index) + inputId);
}


//******************************************************************************

/* Function :  ADCP_ResultReadyGrpIntConfigure_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ResultReadyGrpIntConfigure 

  Description:
    This template implements the Default variant of the PLIB_ADCP_ResultReadyGrpIntConfigure function.
 */

PLIB_TEMPLATE void ADCP_ResultReadyGrpIntConfigure_Default(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable) {
    _SFR_WRITE(_ADCP_GROUP_INT_ENABLE_0_VREG(index), lowEnable);
    _SFR_WRITE(_ADCP_GROUP_INT_ENABLE_44_VREG(index), highEnable);
}


//******************************************************************************

/* Function :  ADCP_ExistsConversionResults_Default

  Summary:
    Implements Default variant of PLIB_ADCP_ExistsConversionResults

  Description:
    This template implements the Default variant of the PLIB_ADCP_ExistsConversionResults function.
 */

PLIB_TEMPLATE bool ADCP_ExistsConversionResults_Default(ADCP_MODULE_ID index) {
    return true;
}


#endif /*_ADCP_CONVERSIONRESULTS_DEFAULT_H*/

/******************************************************************************
 End of File
 */

