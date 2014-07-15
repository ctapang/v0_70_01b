/*******************************************************************************
  Generic USB device function driver header file

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_generic.h

  Summary:
    Generic USB device function driver header

  Description:
    Generic USB device function driver header file
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#ifndef _USB_DEVICE_GENERIC_H
#define _USB_DEVICE_GENERIC_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/
#include <stdint.h>
#include <stdbool.h>
#include "system/common/sys_common.h"
#include "system/common/sys_module.h"
#include "driver/driver_common.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "system_config.h"




// *****************************************************************************
/* Generic USB device function driver callback function.

  Summary:
    Pointer to a structure that holds generic driver callback functions.

  Description:
    The application must use this pointer while registering the function driver
    with the function registration table.

  Remarks:
    None.
*/

extern USB_DEVICE_FUNCTION_DRIVER genFuncDriver;


// *****************************************************************************
/* Return type of the application callback function.

  Summary:
    The return type of the application callback function.

  Description:
   

  Remarks:
    Also see,
    USB_DEVICE_GENERIC_EVENT_HANDLER
*/

typedef void USB_DEVICE_GENERIC_EVENT_RESPONSE;


// *****************************************************************************
/* Generic driver transfer handle.

  Summary:
    Data-type of the generic driver transfer handle.

  Description:
    

  Remarks:
    Also see,
       USB_DEVICE_GENERIC_EndpointRead
       USB_DEVICE_GENERIC_EndpointWrite
*/

typedef uintptr_t USB_DEVICE_GENERIC_TRANSFER_HANDLE;


// *****************************************************************************
/* Data-type for USB device generic driver index.

  Summary:
    Data-type for USB device generic driver index.

  Description:
    

  Remarks:
    None.
*/

typedef SYS_MODULE_INDEX USB_DEVICE_GENERIC_INDEX;


// *****************************************************************************
/* USB device generic function driver transfer flags.

  Summary:
    Enumerated data-type that identifies the USB device generic function
    driver's transfer flag.

  Description:
    

  Remarks:
    Also see,
       USB_DEVICE_GENERIC_EndpointWrite

*/

typedef enum 
{
    /* Transfer flag that specifies no special request */
    USB_DEVICE_GENERIC_TRANSFER_FLAG_NONE 
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_IRP_FLAG_DATA_PENDING /*DOM-IGNORE-END*/,

    /* Transfer flag that specifies the generic driver to complete the
       transfer */
    USB_DEVICE_GENERIC_TRANSFER_FLAG_DATA_COMPLETE 
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_IRP_FLAG_DATA_COMPLETE /*DOM-IGNORE-END*/
}USB_DEVICE_GENERIC_TRANSFER_FLAG;




typedef enum 
{

     /* Control transfer data stage is received from host to device */
    USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_SETUP_REQUEST
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_CONTROL_SETUP_REQUEST /*DOM-IGNORE-END*/,

    /* Control transfer data stage is received from host to device */
    USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_CONTROL_DATA_RECEIVED /*DOM-IGNORE-END*/,

    /* Control transfer data stage is transmitted from device to host */
    USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_DATA_SENT
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_CONTROL_DATA_SENT /*DOM-IGNORE-END*/,

    /* Control transfer was aborted. Application must stop any remaining activities
     * on control transfers */
    USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_ABORTED
            /*DOM-IGNORE-BEGIN*/ = USB_DEVICE_CONTROL_TRANSFER_ABORTED /*DOM-IGNORE-END*/,

    /* This event indicates that USB_DEVICE_GENERIC_EndpointWrite() function
     * completed a data transfer from device to host. */
    USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE,

     /* This event indicates that USB_DEVICE_GENERIC_EndpointRead() function
     * completed a data transfer from host to device. */
    USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE

} USB_DEVICE_GENERIC_EVENT;


// *****************************************************************************
/* Data assocated with USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE event.

  Summary:
    The data-type that holds the event data associated with
    USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE event.


  Description:
    

  Remarks:
    None.
*/

typedef struct 
{
    /* data size transmitted */
    unsigned int dataSize;

    /* Pointer to data buffer */
    uint8_t * data;

    /* Status */
    USB_DEVICE_IRP_STATUS status;

    /* Transfer handle */
    USB_DEVICE_GENERIC_TRANSFER_HANDLE transferHandle;

}USB_DEVICE_GENERIC_EVENT_DATA_ENDPOINT_WRITE_COMPLETE;


// *****************************************************************************
/*  Data assocated with USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE event.

  Summary:
    The data-type that holds the event data associated with
    USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE event.

  Description:
    

  Remarks:
    None.
*/

typedef struct 
{
    /* data size received */
    unsigned int dataSize;

    /* Pointer to data buffer */
    uint8_t * data;

    /* Status */
    USB_DEVICE_IRP_STATUS status;

     /* Transfer handle */
    USB_DEVICE_GENERIC_TRANSFER_HANDLE transferHandle;

}USB_DEVICE_GENERIC_EVENT_DATA_ENDPOINT_READ_COMPLETE;


// *****************************************************************************
/*  Data assocated with 
    USB_DEVICE_GENERIC_EVENT_DATA_CONTROL_TRANSFER_SETUP_REQUEST event.

  Summary:
    The data-type that holds the event data associated with
    USB_DEVICE_GENERIC_EVENT_DATA_CONTROL_TRANSFER_SETUP_REQUEST event.

  Description:
    

  Remarks:
    None.
*/

typedef struct 
{
    /* Format of setup packet from table 9-2 of USB 2.0 spec */
    uint8_t bmRequestType; 
    uint8_t bRequest; 
    uint16_t wValue; 
    uint16_t wIndex; 
    uint16_t wLength;
    
}USB_DEVICE_GENERIC_EVENT_DATA_CONTROL_TRANSFER_SETUP_REQUEST;


// *****************************************************************************
/* Possible results of Generic Driver operations.

  Summary:
    The enumerated data-type that idnetifies the possible
    result of an operation.

  Description:


  Remarks:
    None.
*/

typedef enum
{
   /* Queue is full */
    USB_DEVICE_GENERIC_RESULT_QUEUE_FULL
    /*DOM-IGNORE-BEGIN*/ = USB_ERROR_DEVICE_IRP_IN_USE /*DOM-IGNORE-END*/,

    /* No Error */
    USB_DEVICE_GENERIC_RESULT_OK
            /*DOM-IGNORE-BEGIN*/ = USB_ERROR_NONE /*DOM-IGNORE-END*/,

    /* Endpoint not configured */
    USB_DEVICE_GENERIC_RESULT_ENDPOINT_NOT_CONFIGURED
            /*DOM-IGNORE-BEGIN*/ = USB_ERROR_ENDPOINT_NOT_CONFIGURED /*DOM-IGNORE-END*/,

    /* One or more parameter/s of the function is invalid */
    USB_DEVICE_GENERIC_RESULT_PARAMETER_INVALID 
            /*DOM-IGNORE-BEGIN*/ = USB_ERROR_PARAMETER_INVALID /*DOM-IGNORE-END*/

} USB_DEVICE_GENERIC_RESULT ;

// *****************************************************************************
/*  Event Data.

  Summary:
    Union that holds event data for different generic driver events.

  Description:
    

  Remarks:
    None.
*/

typedef union 
{
    /* Data associated with USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE event */
    USB_DEVICE_GENERIC_EVENT_DATA_ENDPOINT_WRITE_COMPLETE endpointWriteComplete;

     /* Data associated with USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE event */
    USB_DEVICE_GENERIC_EVENT_DATA_ENDPOINT_READ_COMPLETE endpointReadComplete;

    /* Data associated with USB_DEVICE_GENERIC_EVENT_DATACONTROL*/
    USB_DEVICE_GENERIC_EVENT_DATA_CONTROL_TRANSFER_SETUP_REQUEST *ptrSetupRequest;

}USB_DEVICE_GENERIC_EVENT_DATA;

// *****************************************************************************
/* USB device generic function driver event handle.

  Summary:
    The data-type that defines the signature of the event callback function.

  Description:
    The application provided event callback function must be of this data-type.

  Remarks:
    None.
*/


typedef USB_DEVICE_GENERIC_EVENT_RESPONSE (* USB_DEVICE_GENERIC_EVENT_HANDLER) (
                                                                        USB_DEVICE_GENERIC_INDEX instanceIndex,
                                                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                                                                        USB_DEVICE_GENERIC_EVENT event,
                                                                        USB_DEVICE_GENERIC_EVENT_DATA * eventData,
                                                                        uintptr_t userData );

//******************************************************************************
/* Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStall
                                        ( USB_DEVICE_GENERIC_INDEX iGEN,
                                                         USB_ENDPOINT endpoint )

  Summary:
    This function stalls the requested endpoint.

  Description:


  Precondition:
    USB device layer must be initialized.

  Parameters:
    iGEN        - USB device generic function driver instance ID.
    endpoint    - Endpoint address.

  Returns:
    See USB_DEVICE_GENERIC_RESULT

  Example:
    <code>

     
    </code>

  Remarks:
    None.
*/


USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStall ( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_ENDPOINT endpoint );


//******************************************************************************
/* Function:
    bool USB_DEVICE_GENERIC_EndpointStallStatusGet( USB_DEVICE_GENERIC_INDEX iGEN,
                                                USB_ENDPOINT endpoint );

  Summary:
    USB Generic function driver library function that returns true if STALL is enabled
    on the endpoint.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    iGEN        - USB generic function driver instance ID.
    endpoint    - endpoint address.

  Returns:
    true if endpoint is stalled.

  Example:
    <code>

      

    </code>

  Remarks:
    None.
*/

bool USB_DEVICE_GENERIC_EndpointStallStatusGet( USB_DEVICE_GENERIC_INDEX iGEN,
                                                USB_ENDPOINT endpoint );


//******************************************************************************
/* Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStallClear
                                               ( USB_DEVICE_GENERIC_INDEX iGEN,
                                                        USB_ENDPOINT endpoint )

  Summary:
    Clears STALL on the endpoint.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    iGEN       - Generic driver instance index.
    endpoint   - Endpoint address for which the stall has to be cleared.

  Returns:
    See USB_DEVICE_GENERIC_RESULT.

  Example:
    <code>

      
    </code>

  Remarks:
    None.
*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStallClear( USB_DEVICE_GENERIC_INDEX iGEN,
                                                 USB_ENDPOINT endpoint );


//******************************************************************************
/* Function:
    bool USB_DEVICE_GENERIC_EndpointIsEnabled(
                                    USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_ENDPOINT endpoint );

  Summary:
     This function returns true if the requested endpoint is enabled.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    iGEN           - USB generic driver function driver instance ID.
    endpoint       - endpoint address.

  Returns:
    true if endpoint is enabled.

  Example:
    <code>

      

    </code>

  Remarks:
    None.
*/

bool USB_DEVICE_GENERIC_EndpointIsEnabled( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_ENDPOINT endpoint );


//******************************************************************************
/* Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointWrite( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                            USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize,
                                            USB_DEVICE_GENERIC_TRANSFER_FLAG flags );

  Summary:
    This function allows the application client to transfer data from device to
    host on the requested endpoint.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    iGEN              - USB generic function driver instance ID.
    transferHandle    - Pointer to transfer handle.
    endpoint          - endpoint address
    buffer            - Buffer pointer
    bufferSize        - Buffer size
    flags             - Flag that specifies this function whether to end the
                        transfer with a short packet or not.
  Returns:
    See USB_DEVICE_GENERIC_RESULT.

  Example:
    <code>

      


    </code>

  Remarks:
    None.
*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointWrite( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                            USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize,
                                            USB_DEVICE_GENERIC_TRANSFER_FLAG flags );


//******************************************************************************
/* Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointRead( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                           USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize );

  Summary:
    Reads data received from host on the requested endpoint.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    iGEN              - USB generic function driver instance ID.
    transferHandle    - Pointer to transfer handle.
    endpoint          - endpoint address
    buffer            - Buffer pointer
    bufferSize        - Buffer size

  Returns:
    See USB_DEVICE_GENERIC_RESULT.

  Example:
    <code>

     

    </code>

  Remarks:
    None.
*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointRead( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                           USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize );


//******************************************************************************
/* Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EventHandlerSet( USB_DEVICE_GENERIC_INDEX iGEN ,
                                                      USB_DEVICE_GENERIC_EVENT_HANDLER eventHandler );

  Summary:
    This function allows the application client to register event handler
    callback with the generic function driver library.

  Description:


  Precondition:
    USB device layer be initialized.

  Parameters:
    instanceIndex   - USB Generic function driver instance ID.
    eventHandler    - Pointer to application event handler callback function.

  Returns:
    See USB_DEVICE_GENERIC_RESULT.

  Example:
    <code>

      
    </code>

  Remarks:
    None.
*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EventHandlerSet( USB_DEVICE_GENERIC_INDEX iGEN ,
                                                      USB_DEVICE_GENERIC_EVENT_HANDLER eventHandler,
                                                       uintptr_t userData );



#endif // _USB_DEVICE_GENERIC_H

/*******************************************************************************
 End of File
*/


