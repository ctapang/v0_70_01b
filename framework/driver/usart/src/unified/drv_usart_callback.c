/*******************************************************************************
  USART Driver Feature Variant for Callback function

  Summary:
    USART Driver Feature Variant for Callback function

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature. The functions are available
    because callback feature of the driver is selected.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_callback .c
Copyright © 2009-2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS�? WITHOUT WARRANTY OF ANY KIND,
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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "usart/src/drv_usart_local.h"

// *****************************************************************************
/******************************************************************************
  Function:
    void DRV_USART_RegisterCallbacks( const DRV_HANDLE handle,
            DRV_USART_CALLBACK myCallback, const DRV_IO_BUFFER_ID bufferId);
 */

void  _DRV_USART_MAKE_NAME ( RegisterCallbacks )
(
        _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
        DRV_USART_CALLBACK myCallback ,
        const DRV_IO_BUFFER_TYPES bufferId )
{
     _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
     _DRV_USART_MC( clientObj = handle ) ;

    if (bufferId & DRV_IO_BUFFER_TYPE_READ)
    {
        _DRV_USART_CLIENT_OBJ(clientObj, ReadCallback) = myCallback ;
    }

    if (bufferId & DRV_IO_BUFFER_TYPE_WRITE)
    {
        _DRV_USART_CLIENT_OBJ(clientObj, WriteCallback) = myCallback ;
    }

}

// *****************************************************************************
/*  void
    _DRV_USART_NotifyReadComplete ( uint8_t moduleIndex)

   Summary:
    Notifies the client that the read completed using the callback function

   Description:
    Notifies the client that the read completed using the callback function

   Remarks:
    None
 */

void _DRV_USART_NotifyReadComplete( DRV_USART_CLIENT_OBJ clientObj )
{
    if (_DRV_USART_CLIENT_OBJ(clientObj, ReadCallback) != (DRV_USART_CALLBACK)NULL)
    {
        DRV_USART_CLIENT_OBJECT *ClientObj = &gDrvUSARTClientObj[clientObj];
        ClientObj->ReadCallback();
        //_DRV_USART_CLIENT_OBJ(clientObj, ReadCallback)(NULL);
        //((&(gDrvUSARTClientObj[clientObj]))->ReadCallback)(NULL);
    }
}


// *****************************************************************************
/*  void
    _DRV_USART_NotifyWriteComplete ( uint8_t moduleIndex)

   Summary:
    Notifies the client that the write completed using the callback function

   Description:
    Notifies the client that the write completed using the callback function

   Remarks:
    None
 */

void _DRV_USART_NotifyWriteComplete( DRV_USART_CLIENT_OBJ clientObj )
{
    if (_DRV_USART_CLIENT_OBJ(clientObj, WriteCallback) != (DRV_USART_CALLBACK)NULL)
    {
        DRV_USART_CLIENT_OBJECT *ClientObj = &gDrvUSARTClientObj[clientObj];
        ClientObj->WriteCallback();

        //_DRV_USART_CLIENT_OBJ(clientObj, WriteCallback) ( NULL );
        //((&(gDrvUSARTClientObj[clientObj]))->WriteCallback)(NULL);

    }
}


/*******************************************************************************
 End of File
*/
