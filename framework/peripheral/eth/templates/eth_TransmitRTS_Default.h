/*******************************************************************************
  ETH Peripheral Library Template Implementation

  File Name:
    eth_TransmitRTS_Default.h

  Summary:
    ETH PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : TransmitRTS
    and its Variant : Default
    For following APIs :
        PLIB_ETH_TxRTSEnable
        PLIB_ETH_TxRTSDisable
        PLIB_ETH_TxRTSIsEnabled
        PLIB_ETH_ExistsTransmitRTS

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

#ifndef _ETH_TRANSMITRTS_DEFAULT_H
#define _ETH_TRANSMITRTS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _ETH_TX_REQUEST_TO_SEND_VREG(index)

  MASKs:
    _ETH_TX_REQUEST_TO_SEND_MASK(index)

  POSs:
    _ETH_TX_REQUEST_TO_SEND_POS(index)

  LENs:
    _ETH_TX_REQUEST_TO_SEND_LEN(index)

*/


//******************************************************************************
/* Function :  ETH_TxRTSEnable_Default

  Summary:
    Implements Default variant of PLIB_ETH_TxRTSEnable

  Description:
    This template implements the Default variant of the PLIB_ETH_TxRTSEnable function.
*/

PLIB_TEMPLATE void ETH_TxRTSEnable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_SET(_ETH_TX_REQUEST_TO_SEND_VREG(index),_ETH_TX_REQUEST_TO_SEND_POS(index));
}


//******************************************************************************
/* Function :  ETH_TxRTSDisable_Default

  Summary:
    Implements Default variant of PLIB_ETH_TxRTSDisable

  Description:
    This template implements the Default variant of the PLIB_ETH_TxRTSDisable function.
*/

PLIB_TEMPLATE void ETH_TxRTSDisable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_ETH_TX_REQUEST_TO_SEND_VREG(index),_ETH_TX_REQUEST_TO_SEND_POS(index));
}


//******************************************************************************
/* Function :  ETH_TxRTSIsEnabled_Default

  Summary:
    Implements Default variant of PLIB_ETH_TxRTSIsEnabled

  Description:
    This template implements the Default variant of the PLIB_ETH_TxRTSIsEnabled function.
*/

PLIB_TEMPLATE bool ETH_TxRTSIsEnabled_Default( ETH_MODULE_ID index )
{
    return (bool)_SFR_BIT_READ(_ETH_TX_REQUEST_TO_SEND_VREG(index),_ETH_TX_REQUEST_TO_SEND_POS(index));

}


//******************************************************************************
/* Function :  ETH_ExistsTransmitRTS_Default

  Summary:
    Implements Default variant of PLIB_ETH_ExistsTransmitRTS

  Description:
    This template implements the Default variant of the PLIB_ETH_ExistsTransmitRTS function.
*/

PLIB_TEMPLATE bool ETH_ExistsTransmitRTS_Default( ETH_MODULE_ID index )
{
    return true;
}


#endif /*_ETH_TRANSMITRTS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

