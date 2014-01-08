/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_SyncClockSource_Default.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SyncClockSource
    and its Variant : Default
    For following APIs :
        PLIB_USART_ExistsSyncClockSource
        PLIB_USART_SyncClockSourceSelect

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

#ifndef _USART_SYNCCLOCKSOURCE_DEFAULT_H
#define _USART_SYNCCLOCKSOURCE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USART_SYNC_CLOCK_SOURCE_VREG(index)

  MASKs: 
    _USART_SYNC_CLOCK_SOURCE_MASK(index)

  POSs: 
    _USART_SYNC_CLOCK_SOURCE_POS(index)

  LENs: 
    _USART_SYNC_CLOCK_SOURCE_LEN(index)

*/


//******************************************************************************
/* Function :  USART_ExistsSyncClockSource_Default

  Summary:
    Implements Default variant of PLIB_USART_ExistsSyncClockSource

  Description:
    This template implements the Default variant of the PLIB_USART_ExistsSyncClockSource function.
*/

PLIB_TEMPLATE bool USART_ExistsSyncClockSource_Default( USART_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  USART_SyncClockSourceSelect_Default

  Summary:
    Implements Default variant of PLIB_USART_SyncClockSourceSelect 

  Description:
    This template implements the Default variant of the PLIB_USART_SyncClockSourceSelect function.
*/

PLIB_TEMPLATE void USART_SyncClockSourceSelect_Default( USART_MODULE_ID index , USART_SYNC_CLOCK_SOURCE source )
{
    /* TODO  */
}


#endif /*_USART_SYNCCLOCKSOURCE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

