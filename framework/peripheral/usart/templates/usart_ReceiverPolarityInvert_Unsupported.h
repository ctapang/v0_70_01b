/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_ReceiverPolarityInvert_Unsupported.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReceiverPolarityInvert
    and its Variant : Unsupported
    For following APIs :
        PLIB_USART_ExistsReceiverPolarityInvert
        PLIB_USART_ReceiverPolarityInvertDisable
        PLIB_USART_ReceiverPolarityInvertEnable

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

#ifndef _USART_RECEIVERPOLARITYINVERT_UNSUPPORTED_H
#define _USART_RECEIVERPOLARITYINVERT_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  USART_ExistsReceiverPolarityInvert_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ExistsReceiverPolarityInvert

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ExistsReceiverPolarityInvert function.
*/

PLIB_TEMPLATE bool USART_ExistsReceiverPolarityInvert_Unsupported( USART_MODULE_ID index )
{
    return false;
}


//******************************************************************************
/* Function :  USART_ReceiverPolarityInvertDisable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ReceiverPolarityInvertDisable 

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ReceiverPolarityInvertDisable function.
*/

PLIB_TEMPLATE void USART_ReceiverPolarityInvertDisable_Unsupported( USART_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USART_ReceiverPolarityInvertDisable");
}


//******************************************************************************
/* Function :  USART_ReceiverPolarityInvertEnable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ReceiverPolarityInvertEnable 

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ReceiverPolarityInvertEnable function.
*/

PLIB_TEMPLATE void USART_ReceiverPolarityInvertEnable_Unsupported( USART_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USART_ReceiverPolarityInvertEnable");
}


#endif /*_USART_RECEIVERPOLARITYINVERT_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

