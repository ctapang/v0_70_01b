/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_ReceiveLatch_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReceiveLatch
    and its Variant : Default
    For following APIs :
        PLIB_SQI_ReceiveLatchEnable
        PLIB_SQI_ReceiveLatchDisable
        PLIB_SQI_ReceiveLatchGet
        PLIB_SQI_ExistsReceiveLatch

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

#ifndef _SQI_RECEIVELATCH_DEFAULT_H
#define _SQI_RECEIVELATCH_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_RECEIVE_DATA_LATCH_CONTROL_VREG(index)

  MASKs:
    _SQI_RECEIVE_DATA_LATCH_CONTROL_MASK(index)

  POSs:
    _SQI_RECEIVE_DATA_LATCH_CONTROL_POS(index)

  LENs:
    _SQI_RECEIVE_DATA_LATCH_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_ReceiveLatchEnable_Default

  Summary:
    Implements Default variant of PLIB_SQI_ReceiveLatchEnable

  Description:
    This template implements the Default variant of the PLIB_SQI_ReceiveLatchEnable function.
*/

PLIB_TEMPLATE void SQI_ReceiveLatchEnable_Default( SQI_MODULE_ID index )
{
	_SFR_BIT_WRITE (_SQI_RECEIVE_DATA_LATCH_CONTROL_VREG(index),
					_SQI_RECEIVE_DATA_LATCH_CONTROL_POS(index),
					1);
}


//******************************************************************************
/* Function :  SQI_ReceiveLatchDisable_Default

  Summary:
    Implements Default variant of PLIB_SQI_ReceiveLatchDisable

  Description:
    This template implements the Default variant of the PLIB_SQI_ReceiveLatchDisable function.
*/

PLIB_TEMPLATE void SQI_ReceiveLatchDisable_Default( SQI_MODULE_ID index )
{
	_SFR_BIT_WRITE (_SQI_RECEIVE_DATA_LATCH_CONTROL_VREG(index),
					_SQI_RECEIVE_DATA_LATCH_CONTROL_POS(index),
					0);
}


//******************************************************************************
/* Function :  SQI_ReceiveLatchGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_ReceiveLatchGet

  Description:
    This template implements the Default variant of the PLIB_SQI_ReceiveLatchGet function.
*/

PLIB_TEMPLATE bool SQI_ReceiveLatchGet_Default( SQI_MODULE_ID index )
{
	return (bool) _SFR_BIT_READ (_SQI_RECEIVE_DATA_LATCH_CONTROL_VREG(index),
								 _SQI_RECEIVE_DATA_LATCH_CONTROL_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsReceiveLatch_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsReceiveLatch

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsReceiveLatch function.
*/

PLIB_TEMPLATE bool SQI_ExistsReceiveLatch_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_RECEIVELATCH_DEFAULT_H*/

/******************************************************************************
 End of File
*/

