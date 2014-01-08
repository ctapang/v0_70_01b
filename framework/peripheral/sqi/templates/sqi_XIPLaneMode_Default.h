/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPLaneMode_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPLaneMode
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPLaneModeSet
        PLIB_SQI_ExistsXIPLaneMode

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

#ifndef _SQI_XIPLANEMODE_DEFAULT_H
#define _SQI_XIPLANEMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_DATA_LANE_MODE_VREG(index)
    _SQI_DUMMY_LANE_MODE_VREG(index)
    _SQI_MODE_LANES_VREG(index)
    _SQI_ADDRESS_LANE_MODE_VREG(index)
    _SQI_CMD_LANE_MODE_OR_XCON1_VREG(index)

  MASKs:
    _SQI_DATA_LANE_MODE_MASK(index)
    _SQI_DUMMY_LANE_MODE_MASK(index)
    _SQI_MODE_LANES_MASK(index)
    _SQI_ADDRESS_LANE_MODE_MASK(index)
    _SQI_CMD_LANE_MODE_OR_XCON1_MASK(index)

  POSs:
    _SQI_DATA_LANE_MODE_POS(index)
    _SQI_DUMMY_LANE_MODE_POS(index)
    _SQI_MODE_LANES_POS(index)
    _SQI_ADDRESS_LANE_MODE_POS(index)
    _SQI_CMD_LANE_MODE_OR_XCON1_POS(index)

  LENs:
    _SQI_DATA_LANE_MODE_LEN(index)
    _SQI_DUMMY_LANE_MODE_LEN(index)
    _SQI_MODE_LANES_LEN(index)
    _SQI_ADDRESS_LANE_MODE_LEN(index)
    _SQI_CMD_LANE_MODE_OR_XCON1_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_XIPLaneModeSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPLaneModeSet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPLaneModeSet function.
*/

PLIB_TEMPLATE void SQI_XIPLaneModeSet_Default( SQI_MODULE_ID index ,
											   SQI_LANE_MODE dataLanes ,
											   SQI_LANE_MODE dummyLanes ,
											   SQI_LANE_MODE modeLanes ,
											   SQI_LANE_MODE addrLanes ,
											   SQI_LANE_MODE cmdLanes )
{
	_SFR_FIELD_WRITE (_SQI_DATA_LANE_MODE_VREG(index),
					  _SQI_DATA_LANE_MODE_MASK(index),
					  _SQI_DATA_LANE_MODE_POS(index),
					  dataLanes);
	_SFR_FIELD_WRITE (_SQI_DUMMY_LANE_MODE_VREG(index),
					  _SQI_DUMMY_LANE_MODE_MASK(index),
					  _SQI_DUMMY_LANE_MODE_POS(index),
					  dummyLanes);
	_SFR_FIELD_WRITE (_SQI_MODE_LANE_MODE_VREG(index),
					  _SQI_MODE_LANE_MODE_MASK(index),
					  _SQI_MODE_LANE_MODE_POS(index),
					  modeLanes);
	_SFR_FIELD_WRITE (_SQI_ADDRESS_LANE_MODE_VREG(index),
					  _SQI_ADDRESS_LANE_MODE_MASK(index),
					  _SQI_ADDRESS_LANE_MODE_POS(index),
					  addrLanes);
	_SFR_FIELD_WRITE (_SQI_CMD_LANE_MODE_VREG(index),
					  _SQI_CMD_LANE_MODE_MASK(index),
					  _SQI_CMD_LANE_MODE_POS(index),
					  cmdLanes);

}


//******************************************************************************
/* Function :  SQI_ExistsXIPLaneMode_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPLaneMode

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPLaneMode function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPLaneMode_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPLANEMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

