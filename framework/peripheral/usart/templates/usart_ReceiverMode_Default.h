/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_ReceiverMode_Default.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReceiverMode
    and its Variant : Default
    For following APIs :
        PLIB_USART_ExistsReceiverMode
        PLIB_USART_ReceiverModeSelect

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

#ifndef _USART_RECEIVERMODE_DEFAULT_H
#define _USART_RECEIVERMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USART_RECEIVER_MODE_VREG(index)

  MASKs: 
    _USART_RECEIVER_MODE_MASK(index)

  POSs: 
    _USART_RECEIVER_MODE_POS(index)

  LENs: 
    _USART_RECEIVER_MODE_LEN(index)

*/


//******************************************************************************
/* Function :  USART_ExistsReceiverMode_Default

  Summary:
    Implements Default variant of PLIB_USART_ExistsReceiverMode

  Description:
    This template implements the Default variant of the PLIB_USART_ExistsReceiverMode function.
*/

PLIB_TEMPLATE bool USART_ExistsReceiverMode_Default( USART_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  USART_ReceiverModeSelect_Default

  Summary:
    Implements Default variant of PLIB_USART_ReceiverModeSelect 

  Description:
    This template implements the Default variant of the PLIB_USART_ReceiverModeSelect function.
*/

PLIB_TEMPLATE void USART_ReceiverModeSelect_Default( USART_MODULE_ID index , USART_RECEIVE_MODES mode )
{
    /* TODO  */
}


#endif /*_USART_RECEIVERMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

