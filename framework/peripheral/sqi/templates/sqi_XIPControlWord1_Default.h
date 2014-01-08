/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPControlWord1_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPControlWord1
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPControlWord1Set
        PLIB_SQI_XIPControlWord1Get
        PLIB_SQI_ExistsXIPControlWord1

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

#ifndef _SQI_XIPCONTROLWORD1_DEFAULT_H
#define _SQI_XIPCONTROLWORD1_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_CMD_LANE_MODE_OR_XCON1_VREG(index)

  MASKs:
    _SQI_CMD_LANE_MODE_OR_XCON1_MASK(index)

  POSs:
    _SQI_CMD_LANE_MODE_OR_XCON1_POS(index)

  LENs:
    _SQI_CMD_LANE_MODE_OR_XCON1_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_XIPControlWord1Set_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPControlWord1Set

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPControlWord1Set function.
*/

PLIB_TEMPLATE void SQI_XIPControlWord1Set_Default( SQI_MODULE_ID   index ,
												   SQI_DUMMY_BYTES dummyBytes ,
												   SQI_ADDR_BYTES  addressBytes ,
												   uint8_t	       readOpcode ,
												   SQI_LANE_MODE   dataLaneMode ,
												   SQI_LANE_MODE   dummyLaneMode ,
												   SQI_LANE_MODE   modeCodeLaneMode ,
												   SQI_LANE_MODE   addressLaneMode ,
												   SQI_LANE_MODE   cmdLaneMode )
{
	_SFR_WRITE (_SQI_CMD_LANE_MODE_OR_XCON1_VREG(index),
				dummyBytes << 21 |
				addressBytes << 18 |
				readOpcode << 10 |
				dataLaneMode << 8 |
				dummyLaneMode << 6 |
				modeCodeLaneMode << 4 |
				addressLaneMode << 2 |
				cmdLaneMode);
}


//******************************************************************************
/* Function :  SQI_XIPControlWord1Get_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPControlWord1Get

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPControlWord1Get function.
*/

PLIB_TEMPLATE uint32_t SQI_XIPControlWord1Get_Default( SQI_MODULE_ID   index )
{
	return (uint32_t) _SFR_READ (_SQI_CMD_LANE_MODE_OR_XCON1_VREG(index));
}


//******************************************************************************
/* Function :  SQI_ExistsXIPControlWord1_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPControlWord1

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPControlWord1 function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPControlWord1_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPCONTROLWORD1_DEFAULT_H*/

/******************************************************************************
 End of File
*/

