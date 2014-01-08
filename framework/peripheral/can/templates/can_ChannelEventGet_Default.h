/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_ChannelEventGet_Default.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChannelEventGet
    and its Variant : Default
    For following APIs :
        PLIB_CAN_ChannelEventGet
        PLIB_CAN_ChannelEventClear
        PLIB_CAN_ExistsChannelEvent

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _CAN_CHANNELEVENTGET_DEFAULT_H
#define _CAN_CHANNELEVENTGET_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_EVENT_FLAG_TXNFULL_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_TXHALF_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_TXEMPTY_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_RXOVFL_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_RXFULL_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_RXHALF_CHANNEL0_VREG(index)
    _CAN_EVENT_FLAG_RXNEMPTY_CHANNEL0_VREG(index)
    _CAN_EVENT_GET_CHANNEL0_VREG(index)

  MASKs: 
    _CAN_EVENT_FLAG_TXNFULL_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_TXHALF_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_TXEMPTY_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_RXOVFL_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_RXFULL_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_RXHALF_CHANNEL0_MASK(index)
    _CAN_EVENT_FLAG_RXNEMPTY_CHANNEL0_MASK(index)
    _CAN_EVENT_GET_CHANNEL0_MASK(index)

  POSs: 
    _CAN_EVENT_FLAG_TXNFULL_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_TXHALF_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_TXEMPTY_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_RXOVFL_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_RXFULL_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_RXHALF_CHANNEL0_POS(index)
    _CAN_EVENT_FLAG_RXNEMPTY_CHANNEL0_POS(index)
    _CAN_EVENT_GET_CHANNEL0_POS(index)

  LENs: 
    _CAN_EVENT_FLAG_TXNFULL_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_TXHALF_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_TXEMPTY_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_RXOVFL_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_RXFULL_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_RXHALF_CHANNEL0_LEN(index)
    _CAN_EVENT_FLAG_RXNEMPTY_CHANNEL0_LEN(index)
    _CAN_EVENT_GET_CHANNEL0_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_ChannelEventGet_Default

  Summary:
    Implements Default variant of PLIB_CAN_ChannelEventGet 

  Description:
    This template implements the Default variant of the PLIB_CAN_ChannelEventGet function.
*/

PLIB_TEMPLATE CAN_CHANNEL_EVENT CAN_ChannelEventGet_Default( CAN_MODULE_ID index , CAN_CHANNEL channel )
{
    SFR_TYPE *channelEventControlReg;

    PLIB_ASSERT( (channel  <= CAN_CHANNEL31),   "Channel number more than limit" );

    // Get the address of the first register. We will can calculate other using index.
    channelEventControlReg = (SFR_TYPE *)_CAN_EVENT_FLAG_TXNFULL_CHANNEL0_VREG(index);

    // Use channel 0 position as it matches for all.
    return _SFR_FIELD_READ(&channelEventControlReg[16 * channel],
                           0x3FF,
                           _CAN_EVENT_FLAG_RXNEMPTY_CHANNEL0_POS(index) );
}


//******************************************************************************
/* Function :  CAN_ChannelEventClear_Default

  Summary:
    Implements Default variant of PLIB_CAN_ChannelEventClear 

  Description:
    This template implements the Default variant of the PLIB_CAN_ChannelEventClear function.
*/

PLIB_TEMPLATE void CAN_ChannelEventClear_Default( CAN_MODULE_ID index , CAN_CHANNEL channel , CAN_CHANNEL_EVENT events )
{
    SFR_TYPE *channelEventControlReg;

    PLIB_ASSERT( (channel  <= CAN_CHANNEL31),   "Channel number more than limit" );

    // Get the address of the first register. We will can calculate other using index.
    channelEventControlReg = (SFR_TYPE *)_CAN_EVENT_FLAG_TXNFULL_CHANNEL0_VREG(index);

    // Use channel 0 position as it matches for all.
    channelEventControlReg[16 * channel] &= ~events;              
}


//******************************************************************************
/* Function :  CAN_ExistsChannelEvent_Default

  Summary:
    Implements Default variant of PLIB_CAN_ExistsChannelEvent

  Description:
    This template implements the Default variant of the PLIB_CAN_ExistsChannelEvent function.
*/

PLIB_TEMPLATE bool CAN_ExistsChannelEvent_Default( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_CHANNELEVENTGET_DEFAULT_H*/

/******************************************************************************
 End of File
*/

