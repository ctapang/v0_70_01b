/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_ChannelForReceiveSet_pic32.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChannelForReceiveSet
    and its Variant : pic32
    For following APIs :
        PLIB_CAN_ChannelForReceiveSet
        PLIB_CAN_ExistsChannelForReceiveSet

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

#ifndef _CAN_CHANNELFORRECEIVESET_PIC32_H
#define _CAN_CHANNELFORRECEIVESET_PIC32_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_DIRECTION_SET_CHANNEL0_VREG(index)
    _CAN_FOR_RECV_SET_DONLY_CHANNEL0_VREG(index)
    _CAN_FSIZE_CHANNEL0_VREG(index)

  MASKs: 
    _CAN_DIRECTION_SET_CHANNEL0_MASK(index)
    _CAN_FOR_RECV_SET_DONLY_CHANNEL0_MASK(index)
    _CAN_FSIZE_CHANNEL0_MASK(index)

  POSs: 
    _CAN_DIRECTION_SET_CHANNEL0_POS(index)
    _CAN_FOR_RECV_SET_DONLY_CHANNEL0_POS(index)
    _CAN_FSIZE_CHANNEL0_POS(index)

  LENs: 
    _CAN_DIRECTION_SET_CHANNEL0_LEN(index)
    _CAN_FOR_RECV_SET_DONLY_CHANNEL0_LEN(index)
    _CAN_FSIZE_CHANNEL0_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_ChannelForReceiveSet_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ChannelForReceiveSet 

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ChannelForReceiveSet function.
*/

PLIB_TEMPLATE void CAN_ChannelForReceiveSet_pic32( CAN_MODULE_ID index , CAN_CHANNEL channel , uint32_t channelSize , CAN_RX_DATA_MODE dataOnly )
{
    SFR_TYPE *ChannelRcvSetControlReg;
	
	PLIB_ASSERT( (channel  <= CAN_CHANNEL31),   "Channel number more than Maximum" );
	
	// Get the address of the first register. We will can calculate other using index.
    ChannelRcvSetControlReg = (SFR_TYPE *)_CAN_FOR_RECV_SET_DONLY_CHANNEL0_VREG(index);

    // Use channel 0 position as it matches for all.
    // Set the channel for receive
    _SFR_BIT_CLEAR(&ChannelRcvSetControlReg[16 * channel], _CAN_DIRECTION_SET_CHANNEL0_POS(index));
                                                           
    // We need not find the register again.
    if (dataOnly == CAN_RX_DATA_ONLY)
    {
            _SFR_BIT_SET(&ChannelRcvSetControlReg[16 * channel], _CAN_FOR_RECV_SET_DONLY_CHANNEL0_POS(index));
    }
    else
    {
            _SFR_BIT_CLEAR(&ChannelRcvSetControlReg[16 * channel], _CAN_FOR_RECV_SET_DONLY_CHANNEL0_LEN(index));
    }
    /* Write the FIFO size */
    _SFR_FIELD_WRITE(&ChannelRcvSetControlReg[16 * channel],
                     _CAN_FSIZE_CHANNEL0_MASK(index),
                     _CAN_FSIZE_CHANNEL0_POS(index) ,
                     channelSize );
}


//******************************************************************************
/* Function :  CAN_ExistsChannelForReceiveSet_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ExistsChannelForReceiveSet

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ExistsChannelForReceiveSet function.
*/

PLIB_TEMPLATE bool CAN_ExistsChannelForReceiveSet_pic32( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_CHANNELFORRECEIVESET_PIC32_H*/

/******************************************************************************
 End of File
*/

