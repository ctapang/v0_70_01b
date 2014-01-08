/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPNumberOfDummyBytes_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPNumberOfDummyBytes
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPDummyBytesSet
        PLIB_SQI_XIPDummyBytesGet
        PLIB_SQI_ExistsXIPNumberOfDummyBytes

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

#ifndef _SQI_XIPNUMBEROFDUMMYBYTES_DEFAULT_H
#define _SQI_XIPNUMBEROFDUMMYBYTES_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_NUMBER_OF_DUMMY_BYTES_VREG(index)

  MASKs:
    _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index)

  POSs:
    _SQI_NUMBER_OF_DUMMY_BYTES_POS(index)

  LENs:
    _SQI_NUMBER_OF_DUMMY_BYTES_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_XIPDummyBytesSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPDummyBytesSet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPDummyBytesSet function.
*/

PLIB_TEMPLATE void SQI_XIPDummyBytesSet_Default( SQI_MODULE_ID index , SQI_DUMMY_BYTES bytes )
{
	switch (bytes)
	{
		case DUMMY_BYTES_7:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_7);
		break;
		case DUMMY_BYTES_6:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_6);
		break;
		case DUMMY_BYTES_5:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_5);
		case DUMMY_BYTES_4:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_4);
		break;
		case DUMMY_BYTES_3:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_3);
		break;
		case DUMMY_BYTES_2:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_2);
		break;
		case DUMMY_BYTES_1:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_1);
		break;
		case DUMMY_BYTES_0:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_0);
		break;
		default:
			_SFR_FIELD_WRITE (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							  _SQI_NUMBER_OF_DUMMY_BYTES_POS(index),
							  DUMMY_BYTES_2);
	}
}


//******************************************************************************
/* Function :  SQI_XIPDummyBytesGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPDummyBytesGet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPDummyBytesGet function.
*/

PLIB_TEMPLATE SQI_DUMMY_BYTES SQI_XIPDummyBytesGet_Default( SQI_MODULE_ID index )
{
	return _SFR_FIELD_READ (_SQI_NUMBER_OF_DUMMY_BYTES_VREG(index),
							_SQI_NUMBER_OF_DUMMY_BYTES_MASK(index),
							_SQI_NUMBER_OF_DUMMY_BYTES_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsXIPNumberOfDummyBytes_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPNumberOfDummyBytes

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPNumberOfDummyBytes function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPNumberOfDummyBytes_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPNUMBEROFDUMMYBYTES_DEFAULT_H*/

/******************************************************************************
 End of File
*/

