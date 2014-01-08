/*******************************************************************************
  USART Driver Feature Variant for Buffer Q support

  Summary:
    USART Driver Feature Variant for Callback function

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature. The functions are available
    because callback feature of the driver is selected.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_bufferq.c
Copyright Â© 2009-2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED â€œAS ISï¿½? WITHOUT WARRANTY OF ANY KIND,
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

#include "drv.h"
#include "usart/src/drv_usart_variant_mapping.h"

// *****************************************************************************
/* Driver Buffer objects.

   Summary:
    Defines the Driver Buffer instances objects

   Description:
    This data type defines the buffer objects. Each buffer object is created
    for each read or write transaction.

   Remarks:
    Not all modes are available on all micro-controllers.
 */

static DRV_USART_BUFFER_OBJECT s_drv_usart_buffer_object[NUMBER_OF_BUFFER_OBJECTS] = { 0 } ;

// *****************************************************************************
/* Driver Buffer Queue objects.

   Summary:
    Defines the Driver Buffer Queue objects

   Description:
    This data type defines the buffer queue objects. Each buffer queue object is
    created for each read or write transaction.

   Remarks:
    Not all modes are available on all micro-controllers.
 */

static QUEUE_ELEMENT_OBJECT    s_drv_usart_queue_element_objects[NUMBER_OF_BUFFER_OBJECTS] = { 0 } ;

// *****************************************************************************
/* static DRV_USART_BUFFER_OBJECT *_DRV_USART_CreateBufferObject( DRV_HANDLE handle )

   Summary:
    Returns the file scope buffer object

   Description:
    Gets the file scope object from s_drv_usart_buffer_object which is
    associated with the read or the write transaction.

   Remarks:
    None
 */

DRV_USART_BUFFER_OBJECT *_DRV_USART_CreateBufferObjectforQ ( const uint8_t *buffer ,
                                                             const uint32_t numbytes ,
                                                             const DRV_IO_BUFFER_TYPES bufferId )
{
    uint8_t i = 0 ;
    DRV_USART_BUFFER_OBJECT *usartBufferObject = NULL ;

    /* Get one of client buffers which is not in use for the read or write
       transactions, a maximum of NUMBER_OF_BUFFER_OBJECTS transactions
       can be queued.
     */

    for (i = 0 ; i < NUMBER_OF_BUFFER_OBJECTS ; i++)
    {
        if (!_DRV_USART_IS_FLAG_SET ( s_drv_usart_buffer_object[i].operationalFlags , DRV_USART_OPERATIONAL_FLAG_IN_USE ))
        {
            usartBufferObject = &s_drv_usart_buffer_object[i] ;
            break ;
        }
    }

    //SYS_ASSERT ( ( usartBufferObject != (DRV_USART_BUFFER_OBJECT *) NULL ) , " Unable to create the buffer Object " ) ;

    //if (usartBufferObject != (DRV_USART_BUFFER_OBJECT *) NULL)
    {
        /* Create the buffer object associated with the usart read/write
           transactions*/
        BUFFER_Initialize ( &usartBufferObject->bufferObject , (void *)buffer , numbytes ,
                            false , bufferId ) ;

        _DRV_USART_SET_FLAG ( usartBufferObject->operationalFlags , DRV_USART_OPERATIONAL_FLAG_IN_USE ) ;
    }

    return usartBufferObject ;
}


// *****************************************************************************
/* static void _DRV_USART_DeleteBufferObject( DRV_USART_BUFFER_OBJECT *bufferObject )

   Summary:
    Returns the file scope buffer object back to the free list

   Description:
    Returns the file scope buffer object back to the free list

   Remarks:
    None
 */

void _DRV_USART_DeleteBufferObject ( DRV_USART_BUFFER_OBJECT *usartBufferObject )
{
    //BUFFER_Reset ( &usartBufferObject->bufferObject ) ;
    //usartBufferObject->bufferObject.buffer = NULL ;
    usartBufferObject->operationalFlags = 0 ;
}



// *****************************************************************************
/* static DRV_USART_BUFFER_OBJECT* _DRV_USART_GetNextBufferObject ( QUEUE_OBJECT *queue )

   Summary:
    Returns the next available buffer object from the queue

   Description:
    Returns the next available buffer object (whose handle is open) from the queue

   Remarks:
    None
 */

DRV_USART_BUFFER_OBJECT* _DRV_USART_GetNextBufferObject ( QUEUE_OBJECT *queue )
{
    QUEUE_ELEMENT_OBJECT    *q_Element      = NULL ;
    DRV_USART_BUFFER_OBJECT *bufferObject   = NULL ;

    q_Element = QUEUE_Front ( queue ) ;

    if (q_Element != (QUEUE_ELEMENT_OBJECT *) NULL)
    {
        bufferObject = (DRV_USART_BUFFER_OBJECT *) q_Element->data ;
    }

    //SYS_ASSERT ( ( bufferObject != (DRV_USART_BUFFER_OBJECT *) NULL ) , " Invalid  buffer Object " ) ;
    if (bufferObject != (DRV_USART_BUFFER_OBJECT *) NULL)
    {
        bufferObject->status = DRV_USART_BUFFER_IN_PROGRESS ;
    }

    return bufferObject ;
}


// *****************************************************************************
/* static void
    _DRV_USART_MarkBufferObjectsClosed ( const DRV_HANDLE handle )

   Summary:
    Marks the buffers associated with the handle as closed.

   Description:
    Marks the buffers associated with the handle as closed, so that when this
    buffer is picked up by the driver's task routine for read or write, it will be
    deleted from the drier queue.

   Remarks:
    None
 */

void _DRV_USART_MarkBufferObjectsClosedQ ( DRV_HANDLE handle  )
{
    uint8_t i = 0 ;
    DRV_USART_BUFFER_OBJECT *usart_bufferObject   = NULL ;

    for (i = 0 ; i < NUMBER_OF_BUFFER_OBJECTS ; i++)
    {
        usart_bufferObject = &s_drv_usart_buffer_object[i] ;
        if (( _DRV_USART_IS_FLAG_SET ( usart_bufferObject->operationalFlags , DRV_USART_OPERATIONAL_FLAG_IN_USE ) ) &&
                ( DRV_USART_CheckBufferObjectHandle ( usart_bufferObject , handle ) ))
        {
            _DRV_USART_SET_FLAG ( usart_bufferObject->operationalFlags , DRV_USART_OPERATIONAL_FLAG_HANDLE_CLOSED ) ;

            break ;
        }
    }
}

void DRV_USART_InitializeQueues(DRV_USART_OBJ_T *hwInstance)
{
    QUEUE_Initialize ( &hwInstance->readQ , NUMBER_OF_BUFFER_OBJECTS , s_drv_usart_queue_element_objects ) ;

    QUEUE_Initialize ( &hwInstance->writeQ , NUMBER_OF_BUFFER_OBJECTS , s_drv_usart_queue_element_objects ) ;
}

/*******************************************************************************
 End of File
*/
