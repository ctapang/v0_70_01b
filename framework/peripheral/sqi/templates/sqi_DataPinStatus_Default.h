/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_DataPinStatus_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DataPinStatus
    and its Variant : Default
    For following APIs :
        PLIB_SQI_DataLineStatus
        PLIB_SQI_ExistsDataPinStatus

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

#ifndef _SQI_DATAPINSTATUS_DEFAULT_H
#define _SQI_DATAPINSTATUS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_D3_PIN_STATUS_VREG(index)
    _SQI_D2_PIN_STATUS_VREG(index)
    _SQI_D1_PIN_STATUS_VREG(index)
    _SQI_D0_PIN_STATUS_VREG(index)

  MASKs:
    _SQI_D3_PIN_STATUS_MASK(index)
    _SQI_D2_PIN_STATUS_MASK(index)
    _SQI_D1_PIN_STATUS_MASK(index)
    _SQI_D0_PIN_STATUS_MASK(index)

  POSs:
    _SQI_D3_PIN_STATUS_POS(index)
    _SQI_D2_PIN_STATUS_POS(index)
    _SQI_D1_PIN_STATUS_POS(index)
    _SQI_D0_PIN_STATUS_POS(index)

  LENs:
    _SQI_D3_PIN_STATUS_LEN(index)
    _SQI_D2_PIN_STATUS_LEN(index)
    _SQI_D1_PIN_STATUS_LEN(index)
    _SQI_D0_PIN_STATUS_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_DataLineStatus_Default

  Summary:
    Implements Default variant of PLIB_SQI_DataLineStatus

  Description:
    This template implements the Default variant of the PLIB_SQI_DataLineStatus function.
*/

PLIB_TEMPLATE bool SQI_DataLineStatus_Default( SQI_MODULE_ID index , uint8_t dataPin )
{
	switch (dataPin)
	{
		case 3:
			return (bool) _SFR_BIT_READ (_SQI_D3_PIN_STATUS_VREG(index),
								_SQI_D3_PIN_STATUS_POS(index));
		break;
		case 2:
			return (bool) _SFR_BIT_READ (_SQI_D2_PIN_STATUS_VREG(index),
										 _SQI_D2_PIN_STATUS_POS(index));
		break;
		case 1:
			return (bool) _SFR_BIT_READ (_SQI_D1_PIN_STATUS_VREG(index),
										 _SQI_D1_PIN_STATUS_POS(index));
		break;
		case 0:
			return (bool) _SFR_BIT_READ (_SQI_D0_PIN_STATUS_VREG(index),
										 _SQI_D0_PIN_STATUS_POS(index));
		break;
		default:
			return (bool) _SFR_BIT_READ (_SQI_D0_PIN_STATUS_VREG(index),
										 _SQI_D0_PIN_STATUS_POS(index));
	}
}


//******************************************************************************
/* Function :  SQI_ExistsDataPinStatus_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsDataPinStatus

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsDataPinStatus function.
*/

PLIB_TEMPLATE bool SQI_ExistsDataPinStatus_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_DATAPINSTATUS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

