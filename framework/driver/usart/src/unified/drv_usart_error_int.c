/*******************************************************************************
  USART Driver implementation of the Error Tasks routine

  Company:
    Microchip Technology Inc.

  FileName:
    drv_usart_error_int.c

  Summary:
    USART Driver implementation of the Error Tasks routine

  Description:
    This file implements the routine to handle error interrupt
    While building the driver from source, use this file in the build if part
    supports generating error interrupt.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "usart/src/drv_usart_local.h"


/*******************************************************************************
  Function:
    void DRV_USART_TasksError ( SYS_MODULE_OBJ object)

  Summary:
    Maintains the driver's error state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal error state
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.
*/

void  _DRV_USART_MAKE_NAME ( TasksError )(  _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object ) )
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver Object is invalid" ) ;

    /* This state is encountered when an error interrupt has occured.
       or an error has occured during read. */

    if (PLIB_USART_ReceiverOverrunHasOccured ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj, moduleId) ) ))
    {
        PLIB_USART_ReceiverOverrunErrorClear ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj, moduleId) ) ) ;
    }

    _DRV_USART_InterruptSourceStatusClear( _DRV_USART_GET_INT_SRC_ERROR(_DRV_USART_OBJ(dObj, errorInterruptSource)) );

} /* DRV_USART_TasksError */


/*******************************************************************************
 End of File
*/
