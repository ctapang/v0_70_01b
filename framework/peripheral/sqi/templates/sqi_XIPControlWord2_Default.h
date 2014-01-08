/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPControlWord2_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPControlWord2
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPControlWord2Set
        PLIB_SQI_XIPControlWord2Get
        PLIB_SQI_ExistsXIPControlWord2

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

#ifndef _SQI_XIPCONTROLWORD2_DEFAULT_H
#define _SQI_XIPCONTROLWORD2_DEFAULT_H

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
/* Function :  SQI_XIPControlWord2Set_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPControlWord2Set

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPControlWord2Set function.
*/

PLIB_TEMPLATE void SQI_XIPControlWord2Set_Default( SQI_MODULE_ID   index ,
												   SQI_CS_NUM	   devSelect ,
												   SQI_MODE_BYTES  modeBytes ,
												   uint8_t		   modeCode )
{
	_SFR_WRITE (_SQI_XIP_MODE_CODE_OR_XCON2_VREG(index),
				devSelect << 10 |
				modeBytes << 8 |
				modeCode);
}


//******************************************************************************
/* Function :  SQI_XIPControlWord2Get_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPControlWord2Get

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPControlWord2Get function.
*/

PLIB_TEMPLATE uint32_t SQI_XIPControlWord2Get_Default( SQI_MODULE_ID   index )
{
	return (uint32_t) _SFR_READ (_SQI_XIP_MODE_CODE_OR_XCON2_VREG(index));
}


//******************************************************************************
/* Function :  SQI_ExistsXIPControlWord2_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPControlWord2

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPControlWord2 function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPControlWord2_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPCONTROLWORD2_DEFAULT_H*/

/******************************************************************************
 End of File
*/

