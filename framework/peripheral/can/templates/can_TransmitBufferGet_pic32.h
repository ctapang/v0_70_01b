/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_TransmitBufferGet_pic32.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TransmitBufferGet
    and its Variant : pic32
    For following APIs :
        PLIB_CAN_TransmitBufferGet
        PLIB_CAN_ExistsTransmitBufferGet

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

#ifndef _CAN_TRANSMITBUFFERGET_PIC32_H
#define _CAN_TRANSMITBUFFERGET_PIC32_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_TX_RX_USER_ADDRESS_CHANNEL0_VREG(index)

  MASKs: 
    _CAN_TX_RX_USER_ADDRESS_CHANNEL0_MASK(index)

  POSs: 
    _CAN_TX_RX_USER_ADDRESS_CHANNEL0_POS(index)

  LENs: 
    _CAN_TX_RX_USER_ADDRESS_CHANNEL0_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_TransmitBufferGet_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_TransmitBufferGet 

  Description:
    This template implements the pic32 variant of the PLIB_CAN_TransmitBufferGet function.
*/

PLIB_TEMPLATE CAN_TX_MSG_BUFFER * CAN_TransmitBufferGet_pic32( CAN_MODULE_ID index , CAN_CHANNEL channel )
{
    SFR_TYPE *ChannelTranBuffer;

    PLIB_ASSERT( (channel  <= CAN_CHANNEL31),   "Channel number more than Maximum" );

    // Get the address of the first register. We will can calculate other using index.
    ChannelTranBuffer = (SFR_TYPE *)_CAN_TX_RX_USER_ADDRESS_CHANNEL0_VREG(index);

    /* TODO: Add address conversion */
    //return _SFR_READ(&ChannelTranBuffer[16 * channel]);
}


//******************************************************************************
/* Function :  CAN_ExistsTransmitBufferGet_pic32

  Summary:
    Implements pic32 variant of PLIB_CAN_ExistsTransmitBufferGet

  Description:
    This template implements the pic32 variant of the PLIB_CAN_ExistsTransmitBufferGet function.
*/

PLIB_TEMPLATE bool CAN_ExistsTransmitBufferGet_pic32( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_TRANSMITBUFFERGET_PIC32_H*/

/******************************************************************************
 End of File
*/

