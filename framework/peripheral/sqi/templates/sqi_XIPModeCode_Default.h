/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPModeCode_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPModeCode
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPModeCodeSet
        PLIB_SQI_XIPModeCodeGet
        PLIB_SQI_ExistsXIPModeCode

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

#ifndef _SQI_XIPMODECODE_DEFAULT_H
#define _SQI_XIPMODECODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_XIP_MODE_CODE_OR_XCON2_VREG(index)

  MASKs:
    _SQI_XIP_MODE_CODE_OR_XCON2_MASK(index)

  POSs:
    _SQI_XIP_MODE_CODE_OR_XCON2_POS(index)

  LENs:
    _SQI_XIP_MODE_CODE_OR_XCON2_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_XIPModeCodeSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPModeCodeSet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPModeCodeSet function.
*/

PLIB_TEMPLATE void SQI_XIPModeCodeSet_Default( SQI_MODULE_ID index , uint8_t code )
{
	_SFR_FIELD_WRITE (_SQI_XIP_MODE_CODE_OR_XCON2_VREG(index),
					  _SQI_XIP_MODE_CODE_OR_XCON2_MASK(index),
					  _SQI_XIP_MODE_CODE_OR_XCON2_POS(index),
					  code);
}


//******************************************************************************
/* Function :  SQI_XIPModeCodeGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPModeCodeGet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPModeCodeGet function.
*/

PLIB_TEMPLATE uint8_t SQI_XIPModeCodeGet_Default( SQI_MODULE_ID index )
{
	return (uint8_t) _SFR_FIELD_READ (_SQI_XIP_MODE_CODE_OR_XCON2_VREG(index),
					  				  _SQI_XIP_MODE_CODE_OR_XCON2_MASK(index),
					  				  _SQI_XIP_MODE_CODE_OR_XCON2_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsXIPModeCode_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPModeCode

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPModeCode function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPModeCode_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPMODECODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

