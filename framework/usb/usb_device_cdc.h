/*******************************************************************************
  USB Device CDC Function Driver Interface

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_cdc.h

  Summary:
    USB Device CDC Function Driver Interface

  Description:
    This file describes the USB Device CDC Function Driver interface.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _USB_DEVICE_CDC_H
#define _USB_DEVICE_CDC_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "../../apps/Harmony4AvalonGen2.X/system_config.h"
#include "usb_common.h"
#include "usb_chapter_9.h"
#include "usb_device.h"
#include "usb_cdc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Types
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* USB Device CDC Function Driver Index

  Summary:
    USB Device CDC Function Driver Index

  Description:
    This uniquely identifies a CDC Function Driver instance.

  Remarks:
    None.
*/

typedef uintptr_t USB_DEVICE_CDC_INDEX;

// *****************************************************************************
/* USB Device CDC Function Driver Control Transfer Handle

  Summary:
    USB Device CDC Function Driver Control Transfer Handle

  Description:
    This is returned by the CDC function driver event handler and should be used 
    by the application while responding to CDC function driver control transfer
    requests.

  Remarks:
    None.
*/

typedef USB_DEVICE_CONTROL_TRANSFER_HANDLE USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE;

// *****************************************************************************
/* USB Device CDC Function Driver Initialization Data Structure

  Summary:
    USB Device CDC Function Driver Initialization Data Structure

  Description:
    This data structure must be defined for every instance of the CDC function 
    driver. It is passed to the CDC function driver, by the Device Layer,
    at the time of initialization. The funcDriverInit member of the 
    Device Layer Function Driver registration table entry must point to this
    data structure for an instance of the CDC function driver. 

  Remarks:
    The queue sizes that are specified in this data strcture are also affected
    by the USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED configuration macro.
*/

typedef struct 
{
    /* Size of the read queue for this instance
     * of the CDC function driver */
    size_t queueSizeRead;
    
    /* Size of the write queue for this instance
     * of the CDC function driver */
    size_t queueSizeWrite;

    /* Size of the serial state notification
     * queue size*/
    size_t queueSizeSerialStateNotification;
}
USB_DEVICE_CDC_INIT;


// *****************************************************************************
/* USB Device CDC Function Driver Control Transfer Status

  Summary:
    USB Device CDC Function Driver Control Transfer Status

  Description:
    This flag is used along with the USB_DEVICE_CDC_ControlStatus() function to 
    indicate success or failure of a CDC class specific control transfer request.

  Remarks:
    None.
*/

typedef enum
{
    /* The application must use this flag when the data
     * received through the USB_DEVICE_CDC_ControlReceive() function
     * was accepted. Using this flag causes the status stage of
     * the associated control transfer to be completed. */

    USB_DEVICE_CDC_CONTROL_STATUS_OK /*DOM-IGNORE-BEGIN*/ 
        = USB_DEVICE_CONTROL_STATUS_OK,/*DOM-IGNORE-END*/

    /* The application must use this flag when
     * the control request was not supported or the data received
     * using the USB_DEVICE_CDC_ControlReceive() function was not
     * accepted. Using this flag causes the status stage of the
     * associated control transfer to be stalled.  */
 
    USB_DEVICE_CDC_CONTROL_STATUS_ERROR /*DOM-IGNORE-BEGIN*/
        = USB_DEVICE_CONTROL_STATUS_ERROR/*DOM-IGNORE-END*/

}USB_DEVICE_CDC_CONTROL_STATUS;

// *****************************************************************************
/* USB Device CDC Function Driver Events

  Summary:
    USB Device CDC Function Driver Events

  Description:
    These events are specific to the USB Device CDC Function Driver instance.
    Each event description contains details about the  parameters passed with
    event. The contents of pData depends on the generated event.
    
    Events associated with the CDC Function Driver Specific Control Transfers 
    require application response and will be generated along with a CDC
    Control Transfer Handle. This allows the application to respond to the CDC
    function driver control transfer requests. The application should respond to
    these events by using the USB_DEVICE_CDC_ControlReceive(),
    USB_DEVICE_CDC_ControlSend() and USB_DEVICE_CDC_ControlStatus() functions.
    
    Calling the USB_DEVICE_CDC_ControlStatus() function with a
    USB_DEVICE_CDC_CONTROL_STATUS_ERROR will stall the control transfer request.
    The application would do this if the control transfer request is not
    supported. Calling the USB_DEVICE_CDC_ControlStatus() function with a
    USB_DEVICE_CDC_CONTROL_STATUS_OK will complete the status stage of the
    control transfer request. The application would do this if the control
    transfer request is supported 
    
    The following code snippet shows an example of a possible event handling
    scheme.

    <code>
    
    // This code example shows all CDC Function Driver events 
    // and a possible scheme for handling these events. In this example
    // event responses are not deferred.

    USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING setLineCodingData;
    USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING getLineCodingData;
    USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE * controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK * breakData;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

                // In this case, the application should read the line coding
                // data that is sent by the host. The application must use the
                // USB_DEVICE_CDC_ControlReceive() function to receive the 
                // data.

                USB_DEVICE_CDC_ControlReceive(usbDeviceHandle, controlTransferHandle
                                    &setLineCodingData, 
                                    sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));
                break;

            case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

                // In this case, the application should send the line coding
                // data to the host. The application must send the 
                // USB_DEVICE_CDC_ControlSend() function to send the data.

                USB_DEVICE_CDC_ControlSend(usbDeviceHandle, controlTransferHandle
                                    &getLineCodingData, 
                                    sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));
                break;

            case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:
                
                // In this case, pData should be interpreted as a
                // USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE pointer type.  The
                // application acknowledges the parameters by calling the
                // USB_DEVICE_CDC_ControlStatus() function with the
                // USB_DEVICE_CDC_CONTROL_STATUS_OK option.
             
                controlLineStateData =
                        (USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE *)pData;
                
                // controlLineStateData->dtr contains the DTR information
                // controlLineStateData->carrier contains the carrier state
                // information

                USB_DEVICE_CDC_ControlStatus(usbDeviceHandle, controlTransferHandle, 
                                                USB_DEVICE_CDC_CONTROL_STATUS_OK);   

                break;

            case USB_DEVICE_CDC_EVENT_SEND_BREAK:
               
                // In this case, pData should be interpreted as a
                // USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK pointer type.  The
                // application acknowledges the parameters by calling the
                // USB_DEVICE_CDC_ControlStatus() function with the
                // USB_DEVICE_CDC_CONTROL_STATUS_OK option.
                
                breakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData; 
                //breakData->duration is the break duration.
                
                USB_DEVICE_ControlStatus(usbDeviceHandle, controlTransferHandle, 
                                                        USB_DEVICE_CDC_CONTROL_STATUS_OK);
                
                break;

            case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

                // This event indicates the data send request associated with
                // the latest USB_DEVICE_CDC_ControlSend() function was
                // completed.  The application could use this event to track
                // the completion of the USB_DEVICE_CDC_EVENT_GET_LINE_CODING
                // request. The application would then typically complete the
                // status stage of the control transfer by calling the
                // USB_DEVICE_CDC_ControlStatus() function as shown here.

                USB_DEVICE_CDC_ControlStatus(usbDeviceHandle, controlTransferHandle, 
                                                    USB_DEVICE_CDC_CONTROL_STATUS_OK);

                break;

            case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

                // This event indicates the data that was requested using the
                // USB_DEVICE_CDC_ControlReceive() function is available for the
                // application to peruse. The application could use this event
                // to track the completion of the
                // USB_DEVICE_CDC_EVENT_SET_LINE_CODING_EVENT event. The
                // application can then either accept the line coding data (as
                // shown here) or decline it by using the
                // USB_DEVICE_CDC_CONTROL_STATUS_ERROR flag in the
                // USB_DEVICE_CDC_ControlStatus() function.
                
                USB_DEVICE_CDC_ControlStatus(usbDeviceHandle, controlTransferHandle, 
                                                    USB_DEVICE_CDC_CONTROL_STATUS_OK);

                break;
            
            case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:
                
                // This event indicates that a CDC Write Transfer request has
                // completed.  pData should be interpreted as a 
                // USB_DEVICE_CDC_EVENT_DATA_WRITE_COMPLETE pointer type. This
                // contains the transfer handle of the write transfer that
                // completed and amount of data that was written.
 
                break;

            case USB_DEVICE_CDC_EVENT_READ_COMPLETE:
                
                // This event indicates that a CDC Read Transfer request has
                // completed.  pData should be interpreted as a 
                // USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE pointer type. This
                // contains the transfer handle of the read transfer that
                // completed and amount of data that was written.
           
                break;
            
            case USB_DEVICE_CDC_EVENT_SERIAL_STATE_NOTIFICATION_COMPLETE:

                // This event indicates that a CDC Serial State Notification
                // Send request has completed. pData should be interpreted as as
                // a
                // USB_DEVICE_CDC_EVENT_DATA_SERIAL_STATE_NOTIFICATION_COMPLETE
                // pointer type. This will contain the transfer handle
                // associated with the send request and the amount of data that
                // was sent.     

            break

             default:
                break;
         }

        return(USB_DEVICE_CDC_EVENT_RESPONSE_NONE);
    }
    </code>


  Remarks:
    Some of the events allow the application to defer responses. This allows the
    application some time to obtain the response data rather than having to
    respond to the event immediately. Note that a USB host will typically wait
    for event response for a finite time duration before timing out and
    cancelling the event and associated transactions. Even when deferring
    response, the application must respond promptly if such timeouts have to be
    avoided.
*/

typedef enum
{
    /* This event occurs when the host issues a SET LINE CODING command.
       The application must provide a USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING
       data structure to the device layer to receive the line coding data that
       the host will provide. The application must provide the buffer by calling
       the USB_DEVICE_CDC_ControlReceive() function either in the event handler
       or in the application (outside the event handler function).  The
       application must use the controlTransferHandle parameter provided in the
       event while calling USB_DEVICE_CDC_ControlReceive() function. The pData
       parameter will be NULL. The application can use the
       USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED event to track
       completion of the command. */

    USB_DEVICE_CDC_EVENT_SET_LINE_CODING,

    /* This event occurs when the host issues a GET LINE CODING command.
       The application must provide a USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING
       data structure to the device layer that contains the line coding data
       to be provided to the host. The application must provide the buffer by
       calling the USB_DEVICE_CDC_ControlSend() function either in the event
       handler or in the application (outside the event handler
       function). The application must use the controlTransferHandle parameter
       provided in the event while calling USB_DEVICE_CDC_ControlSend() function.
       The size of the buffer is indicated by the length parameter. The
       application can use the USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT
       event to track completion of the command. */
       
    USB_DEVICE_CDC_EVENT_GET_LINE_CODING,

    /* This event occurs when the host issues a SET CONTROL LINE STATE command.
       The application must interpret the pData parameter as
       USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE pointer type. This data
       structure contains the control line state data. The application can
       then use the USB_DEVICE_CDC_ControlStatus() function to indicate
       acceptance or rejection of the command. The
       USB_DEVICE_CDC_ControlStatus() function can be called from the event
       handler or in the application (out of the event handler context).
       The application should use the controlTransferHandle while calling
       the USB_DEVICE_CDC_ControlStatus() function. */
       
    USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE,

    /* This event occurs when the host issues a SEND BREAK command. The
       application must interpret the pData parameter as a
       USB_DEVICE_CDC_EVENT_SEND_BREAK_DATA pointer type. This data structure
       contains the break duration data. The application can then use the
       USB_DEVICE_CDC_ControlStatus() function to indicate acceptance of
       rejection of the command. The USB_DEVICE_CDC_ControlStatus() function can
       be called from the event handler or in the application (out of the
       event handler context). The application should use the
       controlTransferHandle while calling the USB_DEVICE_CDC_ControlStatus()
       function. */

    USB_DEVICE_CDC_EVENT_SEND_BREAK,

    /* This event occurs when a write operation scheduled by calling the
       USB_DEVICE_CDC_Write() function has completed. The pData parameter should
       be interpreted as a USB_DEVICE_CDC_EVENT_DATA_WRITE_COMPLETE pointer
       type. This will contain the transfer handle associated with the
       completed write transfer and the amount of data written. */ 

    USB_DEVICE_CDC_EVENT_WRITE_COMPLETE,

    /* This event occurs when a read operation scheduled by calling the
       USB_DEVICE_CDC_Read() function has completed. The pData parameter should
       be interpreted as a USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE pointer
       type. This will contain the transfer handle associated with the
       completed read transfer and the amount of data read. */

    USB_DEVICE_CDC_EVENT_READ_COMPLETE,

    /* This event occurs when a serial state notification scheduled using the
       USB_DEVICE_CDC_SerialDataSend() function, was sent to the host. The
       pData parameter should be interpreted as a
       USB_DEVICE_CDC_EVENT_DATA_SERIAL_STATE_NOTIFICATION_COMPLETE pointer type
       and will contain the transfer handle associated with the completed send
       transfer and the amount of data sent. */

    USB_DEVICE_CDC_EVENT_SERIAL_STATE_NOTIFICATION_COMPLETE,

    /* This event occurs when the data stage of a control read transfer has
       completed. This event would occur after the application uses the
       USB_DEVICE_CDC_ControlSend() function to respond to the
       USB_DEVICE_CDC_EVENT_GET_LINE_CODING event. */

    USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT,

    /* This event occurs when the data stage of a control write transfer has
       completed. This would occur after the application would respond
       with a USB_DEVICE_CDC_ControlReceive() function to the
       USB_DEVICE_CDC_EVENT_SET_LINE_CODING_EVENT and the data has been
       received. */

    USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED,

} 
USB_DEVICE_CDC_EVENT;

// *****************************************************************************
/* USB Device CDC Function Driver Event Handler Response Type

  Summary:
    USB Device CDC Function Driver Event Callback Response Type

  Description:
    This is the return type of the CDC Function Driver event handler.

  Remarks:
    None.
*/

typedef void USB_DEVICE_CDC_EVENT_RESPONSE;

// *****************************************************************************
/* USB Device CDC Function Driver Event Handler Response None  

  Summary:
    USB Device CDC Function Driver Event Handler Response Type None.

  Description:
    This is the definition of the CDC Function Driver Event Handler Response
    Type none.

  Remarks:
    Intentionally defined to be empty.
*/

#define USB_DEVICE_CDC_EVENT_RESPONSE_NONE

// *****************************************************************************
/* USB Device CDC Event Handler Function Pointer Type.

  Summary:
    USB Device CDC Event Handler Function Pointer Type.

  Description:
    This data type defines the required function signature of the USB Device CDC
    Function Driver event handling callback function. The application must
    register a pointer to a CDC Function Driver events handling function who's
    function signature (parameter and return value types) match the types
    specified by this function pointer in order to receive event call backs from
    the CDC Function Driver. The function driver will invoke this function with
    event relevant parameters. The description of the event handler function
    parameters is given here.

    instanceIndex           - Instance index of the CDC Function Driver that generated the 
                              event.
    
    event                   - Type of event generated.
    
    controlTransferHandle   - Control Transfer Handle for CDC function driver
                              events that require application response. The 
                              application should use this handle when calling the 
                              USB CDC Device Control Transfer functions to 
                              respond to the events.
    
    pData                   - This parameter should be type casted to a event specific
                              pointer type based on the event that has occurred. Refer 
                              to the USB_DEVICE_CDC_EVENT enumeration description for
                              more details.
    
    context                 - Value identifying the context of the application that 
                              was registered along with the event handling function.

  Remarks:
    None.
*/

typedef USB_DEVICE_CDC_EVENT_RESPONSE (*USB_DEVICE_CDC_EVENT_HANDLER)
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_EVENT event,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * pData,
    uintptr_t context
);


// *****************************************************************************
/* USB Device CDC Event Set Break Data Type.

  Summary:
    USB Device CDC Event Set Break Data Type.

  Description:
    This defines the data type of the data generated to the CDC event
    handler on a USB_DEVICE_CDC_EVENT_SEND_BREAK event.

    The SEND_BREAK command is described in section 6.3.13 of the PSTN120.pdf
    document.  This document is part of the CDC specification download available
    on the USB.org website:
    http://www.usb.org/developers/devclass_docs/CDC1.2_WMC1.1_012011.zip

  Remarks:
    None.
*/

typedef struct 
{
    uint16_t duration;
}
USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK;


// *****************************************************************************
/* USB Device CDC Event Set Line Coding Data Type.

  Summary:
    USB Device CDC Event Set Line Coding Data Type.

  Description:
    This defines the data type of the data generated to the CDC event
    handler on a USB_DEVICE_CDC_EVENT_SET_LINE_CODING event.

    The valid values for the members of this structure are defined in table 17
    of the PSTN120.pdf document.  This document is part of the CDC specification
    download available on the USB.org website:
    http://www.usb.org/developers/devclass_docs/CDC1.2_WMC1.1_012011.zip

  Remarks:
    None.
*/

typedef USB_CDC_LINE_CODING USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING;

// *****************************************************************************
/* USB Device CDC Event Get Line Coding Data Type.

  Summary:
    USB Device CDC Event Get Line Coding Data Type.

  Description:
    This type defines the data type of the data that the user needs to respond
    with as a result of a USB_DEVICE_CDC_EVENT_GET_LINE_CODING event.  This data
    is sent to the host via the USB_DEVICE_ControlWrite() function.

    The valid values for the members of this structure are defined in table 17
    of the PSTN120.pdf document.  This document is part of the CDC specification
    download available on the USB.org website:
    http://www.usb.org/developers/devclass_docs/CDC1.2_WMC1.1_012011.zip
 
  Remarks:
    None.
*/

typedef USB_CDC_LINE_CODING USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING;

// *****************************************************************************
/* USB Device CDC Event Set Control Line State Data Type.

  Summary:
    USB Device CDC Event Set Line Coding Data Type.

  Description:
    This defines the data type of the data that should be provided to the
    function driver via the USB_DEVICE_CDC_ControlReceive() function when the
    function driver generates USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE event.

  Remarks:
    None.
*/

typedef USB_CDC_CONTROL_LINE_STATE  USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE;


// *****************************************************************************
/* USB Device CDC Serial State Notification Data Type.

  Summary:
    USB Device Serial State Notification Data Type.

  Description:
    This defines the data type for the CDC Serial State. This data is sent
    to the host over the CDC notification interface.

  Remarks:
    None.
*/

typedef USB_CDC_SERIAL_STATE USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA;


// *****************************************************************************
/* USB Device CDC Transfer Flags

  Summary:
    USB Device CDC Function Driver Transfer Flags

  Description:
    These flags are used to indicate status of the pending data while sending
    data to the host by using the USB_DEVICE_CDC_Write() function.

  Remarks:
    The relevance of the specified flag depends on the size of the buffer. Refer
    to the individual flag descriptions for more details.
*/

typedef enum 
{
    /* This flag indicates there is no further data to be sent in this transfer
       and that the transfer should end. If the size of the transfer is a
       multiple of the maximum packet size for related endpoint configuration,
       the function driver will send a zero length packet to indicate end of the
       transfer to the host. */

    USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE /* DOM-IGNORE-BEGIN */ = (1<<0) /* DOM-IGNORE-END */,

    /* This flag indicates there is more data to be sent in this transfer. If
       the size of the transfer is a multiple of the maximum packet size for the
       related endpoint configuration, the function driver will not send a zero
       length packet. If the size of the transfer is greater than (but not a
       multiple of) the maximum packet size, the function driver will only send
       maximum packet size amount of data. If the size of the transfer is
       greater than endpoint size but not an exact multiple of endpoint size,
       only the closest endpoint size multiple bytes of data will be sent. This
       flag should not be specified if the size of the transfer is less than
       maximum packet size. */

    USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING /* DOM-IGNORE-BEGIN */ = (1<<1) /* DOM-IGNORE-END */
}
USB_DEVICE_CDC_TRANSFER_FLAGS;

// *****************************************************************************
/* USB Device CDC Function Driver Transfer Handle Definition
 
  Summary:
    USB Device CDC Function Driver Transfer Handle Definition.

  Description:
    This definition defines a USB Device CDC Function Driver Transfer Handle. A
    Transfer Handle is owned by the application but its value is modified by the
    USB_DEVICE_CDC_Write(), USB_DEVICE_CDC_Read() and the
    USB_DEVICE_CDC_SerialStateDataSend functions. The transfer handle is valid
    for the life time of the transfer and expires when the transfer related
    event had occurred.

  Remarks:
    None.
*/

typedef uintptr_t USB_DEVICE_CDC_TRANSFER_HANDLE;

// *****************************************************************************
/* USB Device CDC Function Driver Invalid Transfer Handle Definition
 
  Summary:
    USB Device CDC Function Driver Invalid Transfer Handle Definition.

  Description:
    This definition defines a USB Device CDC Function Driver Invalid Transfer 
    Handle. A Invalid Transfer Handle is returned by the USB_DEVICE_CDC_Write(),
    USB_DEVICE_CDC_Read() and the USB_DEVICE_CDC_SerialStateNotificationSend()
    functions when the request was not successful.

  Remarks:
    None.
*/

#define USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID  ((USB_DEVICE_CDC_TRANSFER_HANDLE)(-1))

// *****************************************************************************
/* USB Device CDC Function Driver USB Device CDC Result enumeration.
 
  Summary:
    USB Device CDC Function Driver USB Device CDC Result enumeration.

  Description:
    This enumeration lists the possible USB Device CDC Function Driver operation
    results. These values are returned by USB Device CDC Library functions.

  Remarks:
    None.
 */

typedef enum
{
    /* The operation was successful */
    USB_DEVICE_CDC_RESULT_OK /* DOM-IGNORE-BEGIN */ = USB_ERROR_NONE /* DOM-IGNORE-END */,

    /* The transfer size is invalid. Refer to the description
     * of the read or write function for more details */
    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID 
        /* DOM-IGNORE-BEGIN */ = USB_ERROR_IRP_SIZE_INVALID /* DOM-IGNORE-END */,

    /* The transfer queue is full and no new transfers can be
     * scheduled */
    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL 
        /* DOM-IGNORE-BEGIN */ = USB_ERROR_IRP_QUEUE_FULL /* DOM-IGNORE-END */,

    /* The specified instance is not provisioned in the system */
    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID
        /* DOM-IGNORE-BEGIN */ = USB_ERROR_DEVICE_FUNCTION_INSTANCE_INVALID /* DOM-IGNORE-END */,

    /* The specified instance is not configured yet */
    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED 
        /* DOM-IGNORE-BEGIN */ = USB_ERROR_ENDPOINT_NOT_CONFIGURED /* DOM-IGNORE-END */,

    /* The event handler provided is NULL */
    USB_DEVICE_CDC_RESULT_ERROR_PARAMETER_INVALID 
        /* DOM-IGNORE-BEGIN */ = USB_ERROR_PARAMETER_INVALID /* DOM-IGNORE-END */,

    /* The control transfer was aborted */
    USB_DEVICE_CDC_RESULT_ERROR_CONTROL_TRANSFER_FAILED 
        /* DOM-IGNORE-BEGIN*/ = USB_ERROR_DEVICE_CONTROL_TRANSFER_FAILED /*DOM-IGNORE-END*/
                                                                             
}
USB_DEVICE_CDC_RESULT;


// *****************************************************************************
/* USB Device CDC Function Driver Read and Write Complete Event Data.
 
  Summary:
    USB Device CDC Function Driver Read and Write Complete Event Data.

  Description:
    This data type defines the data structure returned by the driver along with
    USB_DEVICE_CDC_EVENT_READ_COMPLETE and USB_DEVICE_CDC_EVENT_WRITE_COMPLETE
    events.

  Remarks:
    None.
*/

typedef struct
{
    /* Transfer handle associated with this
     * read or write request */
    USB_DEVICE_CDC_TRANSFER_HANDLE handle;

    /* Indicates the amount of data (in bytes) that was
     * read or written */
    size_t length;
} 
USB_DEVICE_CDC_EVENT_DATA_WRITE_COMPLETE, 
USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE,
USB_DEVICE_CDC_EVENT_DATA_SERIAL_STATE_NOTIFICATION_COMPLETE ;


// *****************************************************************************
// *****************************************************************************
// Section: CDC Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_EventHandlerSet (
                USB_DEVICE_CDC_INDEX instance 
                USB_DEVICE_CDC_EVENT_HANDLER eventHandler 
                uintptr_t context);


  Summary:
    This function registers a event handler for the specified CDC function
    driver instance. 

  Description:
    This function registers a event handler for the specified CDC function
    driver instance. This function should be called by the client when it
    receives a SET CONFIGURATION event from the device layer. A event handler
    must be registered for function driver to respond to function driver
    specific commands. If the event handler is not registered, the device layer
    will stall function driver specific commands and the USB device may not
    function. 
    
  Precondition:
    This function should be called when the function driver has been initialized
    as a result of a set configuration.

  Parameters:
    instance  - Instance of the CDC Function Driver.
    eventHandler - A pointer to event handler function.
    context - Application specific context that is returned in the event handler.

  Returns:
    USB_DEVICE_CDC_RESULT_OK - The operation was successful
    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does 
    not exist.
    USB_DEVICE_CDC_RESULT_ERROR_PARAMETER_INVALID - The eventHandler parameter is 
    NULL
    
  Example:
    <code>
    // This code snippet shows an example registering an event handler. Here
    // the application specifies the context parameter as a pointer to an
    // application object (appObject) that should be associated with this 
    // instance of the CDC function driver.
    
    USB_DEVICE_CDC_RESULT result;
    
    USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler 
    (
        USB_DEVICE_CDC_INDEX instanceIndex ,
        USB_DEVICE_CDC_EVENT event ,
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle
        void* pData, uintptr_t context 
    )
    {
        // Event Handling comes here

        switch(event) 
        {
            ...
        }

        return(USB_DEVICE_CDC_EVENT_RESPONSE_NONE);


    }

    result = USB_DEVICE_CDC_EventHandlerSet ( 0 ,&APP_EventHandler, (uintptr_t) &appObject);

    if(USB_DEVICE_CDC_RESULT_OK != result)
    {
        SYS_ASSERT ( false , "invalid event handler function" );
    }
  
    </code>

  Remarks:
    None.

 */

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_EventHandlerSet 
( 
    USB_DEVICE_CDC_INDEX instanceIndex ,
    USB_DEVICE_CDC_EVENT_HANDLER eventHandler,
    uintptr_t context
);


// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Write 
    (   
        USB_DEVICE_CDC_INDEX instance, 
        USB_CDC_DEVICE_TRANSFER_HANDLE * transferHandle, 
        const void * data, size_t size, 
        USB_DEVICE_CDC_TRANSFER_FLAGS flags 
    );

  Summary:
    This function requests a data write to the USB Device CDC Function Driver 
    Layer.

  Description:
    This function requests a data write to the USB Device CDC Function Driver
    Layer. The function places a requests with driver, the request will get
    serviced as data is requested by the USB Host. A handle to the request is
    returned in the transferHandle parameter. The termination of the request is
    indicated by the USB_DEVICE_CDC_EVENT_WRITE_COMPLETE event. The amount of
    data written and the transfer handle associated with the request is returned
    along with the event in writeCompleteData member of the pData parameter in
    the event handler. The transfer handle expires when event handler for the
    USB_DEVICE_CDC_EVENT_WRITE_COMPLETE exits.  If the read request could not be
    accepted, the function returns an error code and transferHandle will contain
    the value USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID.

    The behavior of the write request depends on the flags and size parameter.
    If the application intends to send more data in a request, then it should
    use the USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING flag. If there is no
    more data to be sent in the request, the application must use the
    USB_DEVICE_CDC_EVENT_WRITE_COMPLETE flag. This is explained in more detail
    here:
    
    - If size is a multiple of maxPacketSize and flag is set as
    USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE, the write function will append
    a Zero Length Packet (ZLP) to complete the transfer. 
    
    - If size is a multiple of maxPacketSize and flag is set as
    USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING, the write function will
    not append a ZLP and hence will not complete the transfer. 
    
    - If size is greater than but not a multiple of maxPacketSize and
    flags is set as USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE, the write
    function schedules (length/maxPacketSize) packets and one packet for the
    residual data. 
    
    - If size is greater than but not a multiple of maxPacketSize and flags is
    set as USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING, the write
    function schedules (size/maxPacketSize) packets only. 
    
    - If size is less than maxPacketSize and flag is set as
    USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE, the write function schedules
    one packet. 
    
    - If size is less than maxPacketSize and flag is set as
    USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING, the write function
    returns an error code and sets the transferHandle parameter to 
    USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID.

    Completion of the write transfer is indicated by the 
    USB_DEVICE_CDC_EVENT_WRITE_COMPLETE event. The amount of data written along
    with the transfer handle is returned along with the event.
   
  Precondition:
    The function driver should have been configured.

  Parameters:
    instance  - USB Device CDC Function Driver instance.

    transferHandle - Pointer to a USB_DEVICE_CDC_TRANSFER_HANDLE type of
                     variable. This variable will contain the transfer handle
                     in case the write request was  successful.

    data - pointer to the data buffer that contains the data to written.

    size - Size of the data buffer. Refer to the description section for more
           details on how the size affects the transfer.

    flags - Flags that indicate whether the transfer should continue or end.
            Refer to the description for more details.

  Returns:

    USB_DEVICE_CDC_RESULT_OK - The write request was successful. transferHandle
    contains a valid transfer handle.
    
    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - internal request queue 
    is full. The write request could not be added.

    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID - The specified transfer
    size and flag parameter are invalid.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED - The specified 
    instance is not configured yet.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance
    was not provisioned in the application and is invalid.

  Example:
    <code>
    // Below is a set of examples showing various conditions trying to
    // send data with the Write() command.  
    //
    // This assumes that driver was opened successfully.
    // Assume maxPacketSize is 64.
    
    USB_DEVICE_CDC_TRANSFER_HANDLE transferHandle;
    USB_DEVICE_CDC_RESULT writeRequestHandle;
    USB_DEVICE_CDC_INDEX instance;

    //-------------------------------------------------------
    // In this example we want to send 34 bytes only.

    writeRequestResult = USB_DEVICE_CDC_Write(instance,
                            &transferHandle, data, 34, 
                            USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

    if(USB_DEVICE_CDC_RESULT_OK != writeRequestResult)
    {
        //Do Error handling here
    }

    //-------------------------------------------------------
    // In this example we want to send 64 bytes only.
    // This will cause a ZLP to be sent.

    writeRequestResult = USB_DEVICE_CDC_Write(instance,
                            &transferHandle, data, 64, 
                            USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

    if(USB_DEVICE_CDC_RESULT_OK != writeRequestResult)
    {
        //Do Error handling here
    }

    //-------------------------------------------------------
    // This example will return an error because size is less
    // than maxPacketSize and the flag indicates that more
    // data is pending.

    writeRequestResult = USB_DEVICE_CDC_Write(instanceHandle,
                            &transferHandle, data, 32, 
                            USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING);

    //-------------------------------------------------------
    // In this example we want to place a request for a 70 byte transfer.
    // The 70 bytes will be sent out in a 64 byte transaction and a 6 byte
    // transaction completing the transfer.

    writeRequestResult = USB_DEVICE_CDC_Write(instanceHandle,
                            &transferHandle, data, 70, 
                            USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

    if(USB_DEVICE_CDC_RESULT_OK != writeRequestResult)
    {
        //Do Error handling here
    }

    //-------------------------------------------------------
    // In this example we want to place a request for a 70 bytes to be sent but
    // that we don't end the transfer as more data is coming. 64 bytes of the
    // 70 will be sent out and the USB_DEVICE_CDC_EVENT_WRITE_COMPLETE with 64
    // bytes. This indicates that the extra 6 bytes weren't sent because it
    // would cause the end of the transfer. Thus the user needs add these 6
    // bytes back to the buffer for the next group of data that needs to be sent
    // out.

    writeRequestResult = USB_DEVICE_CDC_Write(instanceHandle,
                            &transferHandle, data, 70, 
                            USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING);

    if(USB_DEVICE_CDC_RESULT_OK != writeRequestResult)
    {
        //Do Error handling here
    }

    // The completion of the write request will be indicated by the 
    // USB_DEVICE_CDC_EVENT_WRITE_COMPLETE event.

    </code>

  Remarks:
    None.


*/

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Write
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle,
    const void * data, size_t size, 
    USB_DEVICE_CDC_TRANSFER_FLAGS flags
);


// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Read 
    (
        USB_DEVICE_CDC_INDEX instance, 
        USB_CDC_DEVICE_TRANSFER_HANDLE * transferHandle,
        void * data, size_t size);

  Summary:
    This function requests a data read from the USB Device CDC Function Driver 
    Layer.

  Description:
    This function requests a data read from the USB Device CDC Function Driver
    Layer. The function places a requests with driver, the request will get
    serviced as data is made available by the USB Host. A handle to the request
    is returned in the transferHandle parameter. The termination of the request
    is indicated by the USB_DEVICE_CDC_EVENT_READ_COMPLETE event. The amount of
    data read and the transfer handle associated with the request is returned
    along with the event in the pData parameter of the event handler. The
    transfer handle expires when event handler for the
    USB_DEVICE_CDC_EVENT_READ_COMPLETE exits. If the read request could not be
    accepted, the function returns an error code and transferHandle will contain
    the value USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID.

    If the size parameter is not a multiple of maxPacketSize or is 0, the
    function returns USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID in transferHandle
    and returns an error code as a return value. If the size parameter is a
    multiple of maxPacketSize and the host send less than maxPacketSize data in
    any transaction, the transfer completes and the function driver will issue a
    USB_DEVICE_CDC_EVENT_READ_COMPLETE event along with the
    USB_DEVICE_CDC_EVENT_READ_COMPLETE_DATA data structure. If the size
    parameter is a multiple of maxPacketSize and the host sends maxPacketSize
    amount of data, and total data received does not exceed size, then the
    function driver will wait for the next packet. 
    
  Precondition:
    The function driver should have been configured.

  Parameters:
    instance  - USB Device CDC Function Driver instance.
    transferHandle - Pointer to a USB_DEVICE_CDC_TRANSFER_HANDLE type of
                     variable. This variable will contain the transfer handle
                     in case the read request was  successful.
    data - pointer to the data buffer where read data will be stored.
    size - Size of the data buffer. Refer to the description section for more
           details on how the size affects the transfer.

  Returns:
    USB_DEVICE_CDC_RESULT_OK - The read request was successful. transferHandle
    contains a valid transfer handle.
    
    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - internal request queue 
    is full. The write request could not be added.

    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID - The specified transfer
    size was not a mulitple of endpoint size or is 0.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED - The specified 
    instance is not configured yet.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance
    was not provisioned in the application and is invalid.

  Example:
    <code>
    // Shows an example of how to read. This assumes that
    // driver was opened successfully.

    USB_DEVICE_CDC_TRANSFER_HANDLE transferHandle;
    USB_DEVICE_CDC_RESULT readRequestResult;
    USB_DEVICE_CDC_HANDLE instanceHandle;

    readRequestResult = USB_DEVICE_CDC_Read(instanceHandle,
                            &transferHandle, data, 128);

    if(USB_DEVICE_CDC_RESULT_OK != readRequestResult)
    {
        //Do Error handling here
    }

    // The completion of the read request will be indicated by the 
    // USB_DEVICE_CDC_EVENT_READ_COMPLETE event.

    </code>

  Remarks:
    None.

*/
USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Read
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle,
    void * data, size_t size
);

// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_SerialStateNotificationSend
    (
        USB_DEVICE_CDC_INDEX instanceIndex,
        USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle,
        USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA * notificationData
    );
    
  Summary:
    This function schedules a request to send serial state notification to the host.

  Description:
    This function places a request to send serial state notificatin data to the
    host. The function will place the request with the driver, the request will
    get serviced when the data is requested by the USB host.  A handle to the
    request is returned in the transferHandle parameter. The termination of the
    request is indicated by the
    USB_DEVICE_CDC_EVENT_SERIAL_STATE_NOTIFICATION_COMPLETE event. The amount of
    data transmitted and the transfer handle associated with the request is
    returned along with the event in the serialStateNotificationCompleteData
    member of pData paramter of the event handler. The transfer handle expires
    when the event handler for the
    USB_DEVICE_CDC_EVENT_SERIAL_STATE_NOTIFICATION_COMPLETE event exits. If the
    send request could not be accepted, the function returns an error code and
    transferHandle will contain the value
    USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID.

  Precondition:
    The function driver should have been configured

  Parameters:
    instance  - USB Device CDC Function Driver instance.
    transferHandle  - Pointer to a output only variable that will contain transfer
                      handle.
    notificationData - USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA type of
                       notification data to be sent to the host.

  Returns:
    USB_DEVICE_CDC_RESULT_OK - The request was successful. transferHandle
    contains a valid transfer handle.
    
    USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - Internal request queue 
    is full. The request could not be added.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED - The specified 
    instance is not configured yet.

    USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance
    was not provisioned in the application and is invalid.

  Example:
    <code>

    USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA notificationData;
    
    // This application function could possibly update the notificationData
    // data structure.

    APP_UpdateNotificationData(&notificationData);

    // Now send the updated notification data to the host.

    result = USB_DEVICE_CDC_SerialStateNotificationSend
                (instanceIndex, &transferHandle, &notificationData);
    
    if(USB_DEVICE_CDC_RESULT_OK != result)
    {
        // Error handling here. The transferHandle will contain
        // USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID in this case.
    } 
    
    </code>

  Remarks:
    None.


 */

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_SerialStateNotificationSend 
( 
    USB_DEVICE_CDC_INDEX instanceIndex ,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle ,
    USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA * notificationData
);

// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlSend
    (
        USB_DEVICE_CDC_INDEX instanceIndex,
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        void * data, size_t size   
    );
    
  Summary:
    This function allows the application to respond to the CDC function driver
    specific control transfer requests. It allows the application to send data
    to the host in the data stage of the control transfer.

  Description:
    This function allows the application to respond to the CDC function driver
    specific control transfer requests. It allows the application to send data
    to the host in the data stage of the control transfer. For example, the
    USB_DEVICE_CDC_EVENT_GET_LINE_CODING event requires a control transfer
    response. The function can be called in the CDC Function Driver event
    handler or can be called outside the event handler. Calling this function
    outside the event handler defers the response to the event. This allows the
    application to prepare the response data out of the event handler context,
    especially if the data is not readily available. Note however, that there
    are timing considerations when responding to the control transfer.
    Exceeding the response time will cause the host to cancel the control
    transfer and may cause USB host to reject the device. The application must
    use the control transfer handle that was generated along with the event as
    the controlTransferHandle. 

  Precondition:
    This function should only be called in response to a CDC function driver
    event that requires a control transfer response.

  Parameters:
    instance  - USB Device CDC Function Driver instance.

    controlTransferHandle  - Control Transfer handle for the control transfer.

    data -  Data that represents the data stage of the control transfer.

    size - size (in bytes) of the data to sent.

  Returns:
    USB_DEVICE_CDC_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.
    
    USB_DEVICE_CDC_RESULT_OK - The request was successful.

  Example:
    <code>

    // ------------------------------------------------------------------
    // In this example, the application responds to the GET LINE CODING
    // with in the event handler. The application uses the 
    // USB_DEVICE_CDC_ControlSend() function to do this. 
    // ------------------------------------------------------------------
   
    USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING getLineCodingData;
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

                // In this case, the application should send the line coding
                // data to the host. The application must use the 
                // USB_DEVICE_CDC_ControlSend() function to send the data.

                USB_DEVICE_CDC_ControlSend(instanceIndex, controlTransferHandle
                                    &getLineCodingData, 
                                    sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));
                break;
         }
    }

    // --------------------------------------------------------------------
    // In this example, the application defers the response to the
    // event. This is done by calling the USB_DEVICE_CDC_ControlSend()
    // function after the event handler exits.
    // --------------------------------------------------------------------

    USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING getLineCodingData;
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE thisControlTransferHandle;
    bool sendLineCodingToHost;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

                // In this case, the application should send the line coding
                // data to the host. The application does not call
                // USB_DEVICE_CDC_ControlSend() function
                // in the event handler, because it does not have the line
                // coding data ready.

                thisControlTransferHandle = controlTransferHandle;
                sendLineCodingToHost = true;

                break;
         }
    }

    // This is outside the event handler.

    if(sendLineCodingToHost)
    {
        // The application fetches the line coding from the
        // an EEPROM.

        GetLineCodingFromEEPROM(&getLineCoding);

        USB_DEVICE_CDC_ControlSend(instanceIndex, thisControlTransferHandle
                            &getLineCodingData, 
                            sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));
    }
    
    </code>

  Remarks:
    None.

 */

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlSend
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * data, size_t size   
);
 
// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlReceive
    (
        USB_DEVICE_CDC_INDEX instanceIndex,
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        void * data, size_t size   
    );
    
  Summary:
    This function allows the application to respond to the CDC function driver
    specific control transfer requests. It allows the application to receive data
    from the host in the data stage of the control transfer.

  Description:
    This function allows the application to respond to the CDC function driver
    specific control transfer requests. It allows the application to receive
    data from the host in the data stage of the control transfer. For example,
    the USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING event requires a control
    transfer response. The function can be called in the CDC Function Driver
    event handler or can be called outside the event handler. Calling this
    function outside the event handler defers the response to the event. This
    allows the application to prepare the data buffer out of the event handler
    context, especially if the data buffer to receive the data is not readily
    available. Note however, that there are timing considerations when
    responding to the control transfer. Exceeding the response time will cause
    the host to cancel the control transfer and may cause USB host to reject the
    device. The application must use the control transfer handle that was
    generated along with the event as the controlTransferHandle. 

  Precondition:
    This function should only be called in response to a CDC function driver
    event that requires a control transfer response.

  Parameters:
    instance  - USB Device CDC Function Driver instance.

    controlTransferHandle  - Control Transfer handle for the control transfer.

    data -  Data buffer to receive the data stage of the control transfer.

    size - size (in bytes) of the data to sent.

  Returns:
    USB_DEVICE_CDC_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.
    
    USB_DEVICE_CDC_RESULT_OK - The request was successful.

  Example:
    <code>

    // ------------------------------------------------------------------
    // In this example, the application responds to the SET LINE CODING
    // with in the event handler. The application uses the 
    // USB_DEVICE_CDC_ControlReceive() function to do this. 
    // ------------------------------------------------------------------
   
    USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING setLineCodingData;
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

                // In this case, the application should receive the line coding
                // data from the host. The application must use the 
                // USB_DEVICE_CDC_ControlReceive() function to receive the data.

                USB_DEVICE_CDC_ControlReceive(instanceIndex, controlTransferHandle
                                    &setLineCodingData, 
                                    sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));
                break;
         }
    }

    // --------------------------------------------------------------------
    // In this example, the application defers the response to the
    // event. This is done by calling the USB_DEVICE_CDC_ControlReceive()
    // function after the event handler exits.
    // --------------------------------------------------------------------

    USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING setLineCodingData;
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE thisControlTransferHandle;
    bool sendLineCodingToHost;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

                // In this case, the application should send the line coding
                // data to the host. The application must responds to the 
                // event outside the event handler because the data buffer is
                // not available.

                thisControlTransferHandle = controlTransferHandle;
                getLineCodingFromHost = true;

                break;
         }
    }


    if(getLineCodingFromHost)
    {
        // The application allocates a buffer using an arbitrary function
        // Note that this happens after the event handler exits.

        setLineCoding = AllocateMemoryBuffer();

        USB_DEVICE_CDC_ControlReceive(instanceIndex, thisControlTransferHandle
                            &setLineCodingData, 
                            sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));
    }
    
    </code>

  Remarks:
    None.

 */


USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlReceive
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    void * data, size_t size   
);
 
// *****************************************************************************
/* Function:
    USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlStatus
    (
        USB_DEVICE_CDC_INDEX instanceIndex,
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        USB_DEVICE_CDC_CONTROL_STATUS status
    );
    
  Summary:
    This function allows the application to complete the status stage of the 
    the CDC Function Driver specific control transfer request.

  Description:
    This function allows the application to complete the status stage of the the
    CDC Function Driver specific control transfer request. The application can
    either accept the data stage or stall it. Calling this function with status
    set to USB_DEVICE_CDC_CONTROL_STATUS_OK will acknowledge the status stage of
    the control transfer. The control transfer can be stalled by setting the
    status parameter to USB_DEVICE_CDC_CONTROL_STATUS_ERROR. The function can be
    called in the CDC Function Driver event handler or can be called outside the
    event handler. Calling this function outside the event handler defers the
    response to the event. This allows the application to analyze the event
    response outside the event handler. Note however, that there are timing
    considerations when responding to the control transfer. Exceeding the
    response time will cause the host to cancel the control transfer and may
    cause USB host to reject the device. The application must use the control
    transfer handle that was generated along with the event as the
    controlTransferHandle. The application must be aware of events and
    associated control transfers that do or do not require data stages.
    Incorrect usage of the USB_DEVICE_CDC_ControlStatus() function could cause
    the device function to be non-compliant.

  Precondition:
    This function should only be called in response to a CDC function driver
    event that requires a control transfer response. 

  Parameters:
    instance  - USB Device CDC Function Driver instance.

    controlTransferHandle  - Control Transfer handle for the control transfer.

    status - Set to USB_DEVICE_CDC_CONTROL_STATUS_OK to acknowledge the
    control transfer. Set to USB_DEVICE_CDC_CONTROL_STATUS_ERROR to stall the
    transfer.

  Returns:
    USB_DEVICE_CDC_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.
    
    USB_DEVICE_CDC_RESULT_OK - The request was successful.

  Example:
    <code>

    // ------------------------------------------------------------------
    // In this code example, the application responds to the the 
    // SEND BREAK event in the event handler.
    // ------------------------------------------------------------------
   
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK * sendBreakData;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_SEND_BREAK:

                // The application can check if the break duration is supported.
                
                sendBreakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData;

                if(IsBreakDurationSupported(sendBreakData->duration))
                {
                    USB_DEVICE_CDC_ControlStatus(instanceIndex, 
                            controlTransferHandle, USB_DEVICE_CDC_CONTROL_STATUS_OK);
                }
                else
                {
                    // If the break duration is not supported the application
                    // can stall it.

                    USB_DEVICE_CDC_ControlStatus(instanceIndex, 
                            controlTransferHandle, USB_DEVICE_CDC_CONTROL_STATUS_ERROR);
                }       
                break;
         }
    }

    // --------------------------------------------------------------------
    // In this example, the application defers the response to the 
    // SEND BREAK event. The application responds to the event  
    // after the event handler exits.
    // --------------------------------------------------------------------

    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE thisControlTransferHandle;
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK * sendBreakData;
    uint16_t breakDuration;
    bool sendBreakEvent;

    USB_DEVICE_CDC_EVENT_RESPONSE USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX instanceIndex, 
        USB_DEVICE_CDC_EVENT event, 
        USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_CDC_EVENT_SEND_BREAK:

                // Get the break duration.
                
                sendBreakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData;
                breakDuration = sendBreakData->duration
                sendBreakEvent = true;
                break;
         }
    }

    if(sendBreakData)
    {
        // The application checks if the duration is supported
        // Note that this occurs after the event handler has exited.
        
        if(IsBreakDurationSupported(breakDuration))
        {
            USB_DEVICE_CDC_ControlStatus(instanceIndex, 
                    controlTransferHandle, USB_DEVICE_CDC_CONTROL_STATUS_OK);
        }
        else
        {
            // If the break duration is not supported the application
            // can stall it.

            USB_DEVICE_CDC_ControlStatus(instanceIndex, 
                    controlTransferHandle, USB_DEVICE_CDC_CONTROL_STATUS_ERROR);
        }       
    
    }
    
    </code>

  Remarks:
    None.

 */


USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlStatus
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    USB_DEVICE_CDC_CONTROL_STATUS status
);
 



#endif

