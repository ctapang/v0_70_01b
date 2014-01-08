/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_DataFormat_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DataFormat
    and its Variant : Default
    For following APIs :
        PLIB_SQI_DataFormatSet
        PLIB_SQI_DataFormatGet
        PLIB_SQI_ExistsDataFormat

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

#ifndef _SQI_DATAFORMAT_DEFAULT_H
#define _SQI_DATAFORMAT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_DATA_FORMAT_CONTROL_VREG(index)

  MASKs:
    _SQI_DATA_FORMAT_CONTROL_MASK(index)

  POSs:
    _SQI_DATA_FORMAT_CONTROL_POS(index)

  LENs:
    _SQI_DATA_FORMAT_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_DataFormatSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_DataFormatSet

  Description:
    This template implements the Default variant of the PLIB_SQI_DataFormatSet function.
*/

PLIB_TEMPLATE void SQI_DataFormatSet_Default( SQI_MODULE_ID index , SQI_DATA_FORMAT dataformat )
{
	switch (dataformat)
	{
		case SQI_DATA_FORMAT_LSBF:
			_SFR_BIT_WRITE (_SQI_DATA_FORMAT_CONTROL_VREG(index),
							_SQI_DATA_FORMAT_CONTROL_POS(index),
							SQI_DATA_FORMAT_LSBF);
		break;
		case SQI_DATA_FORMAT_MSBF:
			_SFR_BIT_WRITE (_SQI_DATA_FORMAT_CONTROL_VREG(index),
							_SQI_DATA_FORMAT_CONTROL_POS(index),
							SQI_DATA_FORMAT_MSBF);
		break;
		default:
			_SFR_BIT_WRITE (_SQI_DATA_FORMAT_CONTROL_VREG(index),
							_SQI_DATA_FORMAT_CONTROL_POS(index),
							SQI_DATA_FORMAT_MSBF);
	}
}


//******************************************************************************
/* Function :  SQI_DataFormatGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_DataFormatGet

  Description:
    This template implements the Default variant of the PLIB_SQI_DataFormatGet function.
*/

PLIB_TEMPLATE SQI_DATA_FORMAT SQI_DataFormatGet_Default( SQI_MODULE_ID index )
{
	return _SFR_BIT_READ (_SQI_DATA_FORMAT_CONTROL_VREG(index),
						  _SQI_DATA_FORMAT_CONTROL_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsDataFormat_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsDataFormat

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsDataFormat function.
*/

PLIB_TEMPLATE bool SQI_ExistsDataFormat_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_DATAFORMAT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

