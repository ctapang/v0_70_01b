/*******************************************************************************
  USB DEVICE AUDIO Function Driver Interface

  Company:
    Microchip Technology Incorporated

  File Name:
    usb_device_audio.h

  Summary:
    USB Device AUDIO function Driver Interface 

  Description:
    This file describes the USB Device AUDIO Function Driver interface. 
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

#ifndef _USB_DEVICE_AUDIO_H
#define _USB_DEVICE_AUDIO_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include "system_config.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "usb/usb_audio.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* USB Device Audio Function Driver Index

  Summary:
    USB Device Audio Function Driver Index

  Description:
    This uniquely identifies a Audio Function Driver instance.

  Remarks:
    None.
*/

typedef uintptr_t USB_DEVICE_AUDIO_INDEX;

// *****************************************************************************
/* USB Device Audio Function Driver Control Transfer Handle

  Summary:
    USB Device Audio Function Driver Control Transfer Handle

  Description:
    This is returned by the Audio function driver event handler and should be used 
    by the application while responding to Audio function driver control transfer
    requests.

  Remarks:
    None.
*/

typedef USB_DEVICE_CONTROL_TRANSFER_HANDLE USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE;

// *****************************************************************************
/* USB Device Audio Function Driver Control Transfer Status

  Summary:
    USB Device Audio Function Driver Control Transfer Status

  Description:
    This flag is used along with the USB_DEVICE_AUDIO_ControlStatus() function to 
    indicate success or failure of an Audio class specific control transfer request.

  Remarks:
    None.
*/

typedef enum
{
    /* The application must use this flag when the data
     * received through the USB_DEVICE_AUDIO_ControlReceive() function
     * was accepted. Using this flag causes the status stage of
     * the associated control transfer to be completed. */

    USB_DEVICE_AUDIO_CONTROL_STATUS_OK /*DOM-IGNORE-BEGIN*/ 
        = USB_DEVICE_CONTROL_STATUS_OK,/*DOM-IGNORE-END*/

    /* The application must use this flag when
     * the control request was not supported or the data received
     * using the USB_DEVICE_AUDIO_ControlReceive() function was not
     * accepted. Using this flag causes the status stage of the
     * associated control transfer to be stalled.  */
 
    USB_DEVICE_AUDIO_CONTROL_STATUS_ERROR /*DOM-IGNORE-BEGIN*/
        = USB_DEVICE_CONTROL_STATUS_ERROR/*DOM-IGNORE-END*/

}USB_DEVICE_AUDIO_CONTROL_STATUS;

// *****************************************************************************
/* USB Device Audio Function Driver Events

  Summary:
    USB Device Audio Function Driver Events
  Description:
    These events are specific to the USB Device Audio Function Driver instance.
    Each event description contains details about the  parameters passed with
    event. The contents of pData depends on the generated event.
	
	Events associated with the Audio Function Driver Specific Control Transfers 
    require application response and will be generated along with an Audio
    Control Transfer Handle. This allows the application to respond to the Audio
    function driver control transfer requests. The application should respond to
    these events by using the USB_DEVICE_AUDIO_ControlReceive(),
    USB_DEVICE_AUDIO_ControlSend() and USB_DEVICE_AUDIO_ControlStatus() functions.
    
    Calling the USB_DEVICE_AUDIO_ControlStatus() function with a
    USB_DEVICE_AUDIO_CONTROL_STATUS_ERROR will stall the control transfer request.
    The application would do this if the control transfer request is not
    supported. Calling the USB_DEVICE_AUDIO_ControlStatus() function with a
    USB_DEVICE_AUDIO_CONTROL_STATUS_OK will complete the status stage of the
    control transfer request. The application would do this if the control
    transfer request is supported. 
    
    The following code snippet shows an example of a possible event handling
    scheme.
    
    <code>
    
    // This code example shows all USB Audio Function Driver possible events
    // and a possible scheme for handling these events. In this case
    // event responses are not deferred.
    void APP_AudioEventCallback
    (
        USB_DEVICE_AUDIO_INDEX iAudio ,
        USB_DEVICE_AUDIO_EVENT event ,
        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        uint8_t interfaceNum ,
        uint8_t interfaceAltrntSettng ,
        unsigned short int dataLength
    )
    {
        UINT audioCodecWrite =0;
        if ( iAudio == 0 )
        {
            switch (event)
            {
                case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE:
                    audioCodecWrite = AK4645AWrite ( pCodecHandle ,( AudioStereo* ) rxBuffer , pCodecHandle-\>frameSize );
                    AK4645AAdjustSampleRateTx ( pCodecHandle );
                    appData.state = APP_SUBMIT_RX_REQUEST;
                break;
                case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE:
                case USB_DEVICE_AUDIO_EVENT_MIDI_WRITE_COMPLETE:
                case USB_DEVICE_AUDIO_EVENT_MIDI_READ_COMPLETE:
                break;
    
                case USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING:
                    if (interfaceAltrntSettng == 0)
                    {
                        AK4645ADACMute(pCodecHandle, TRUE);
                        AK4645ABufferClear(pCodecHandle);
                        appData.state = APP_IDLE;
                        USB_DEVICE_AUDIO_IRPCancelAll(0);
                        appData.currentInterfaceAlternateSetting = 0;
                    }
                    else if(interfaceAltrntSettng == 1)
                    {
                        AK4645ADACMute(pCodecHandle, FALSE);
                        appData.state =  APP_SUBMIT_RX_REQUEST;
                        appData.currentInterfaceAlternateSetting = 1;
                    }
                break;
                case USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVE_COMPLETED:
                    USB_DEVICE_ControlStatus(appData.usbDevHandle,controlTransferHandle, USB_DEVICE_CONTROL_STATUS_SEND_ZLP );
                    if (appData.currentInterfaceAlternateSetting == 1)
                    AK4645ADACMute(pCodecHandle, DACMute);
                break;
                case  USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_SEND_COMPLETED:
                break;
                default:
                    SYS_ASSERT ( false , "Invalid callback" );
                break;
            } //end of switch ( callback )
        }//end of if  if ( iAudio == 0 )
    }//end of function APP_AudioEventCallback
    
    </code>
  Remarks:
    Some of the events allow the application to defer responses. This
    allows the application some time to obtain the response data rather
    than having to respond to the event immediately. Note that a USB host
    will typically will wait for event response for a finite time duration
    before timing out and cancelling the event and associated transactions.
    Even when deferring response, the application must respond promptly if
    such timeouts have to be avoided.                                                                                         
  *****************************************************************************************************************************/
typedef enum
{
    /* This event occurs  when  a  write  operation  scheduled  by  calling  the
       USB_DEVICE_AUDIO_Write() function has completed.  The pData member  in  the
       event  handler  will  point  to  USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE_DATA
       type.  */
    USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE ,

       /* This event  occurs  when  a  read  operation  scheduled  by  calling  the
       USB_DEVICE_AUDIO_Read() function has completed.  The pData  member  in  the
       event handler will point to USB_DEVICE_AUDIO_EVENT_READ_COMPLETE_DATA type.
       */
    USB_DEVICE_AUDIO_EVENT_READ_COMPLETE ,

    /* USB spec allows Devices to have multiple alternate settings for the same interface.
          This event occurs when Host trying set an alternate setting for an interface
          present in this audio function. The callback function
          USB_DEVICE_AUDIO_EVENT_CALLBACK  also sends Interface Number and Alternate setting
          number when this event occurs. An application need to take necessary action
          based on the interface alternate setting. */
    USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING,

     /* This event occurs when the data stage of a control write transfer has
        completed. This would occur after the application would respond
        with a USB_DEVICE_ControlReceive() function to a control write request
        from Host. This event notifies the application that the data is recived from
        Host and is available at the location passed by the USB_DEVICE_ControlReceive()
        function. The application should respond to Host with Zero Length Packet by calling
        USB_DEVICE_ControlStatus() function.
     */

    USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVED,

    /* This event occurs when the data stage of a control read transfer has
       completed. This event would occur after the application uses the
       USB_DEVICE_ControlSend() function to respond to an entity request
       recived from Host. */
    USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_SENT,

    USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED

} USB_DEVICE_AUDIO_EVENT;
// *****************************************************************************
/* USB Device Audio Function Driver Event Handler Response Type

  Summary:
    USB Device Audio Function Driver Event Callback Response Type

  Description:
    This is the return type of the Audio Function Driver event handler.

  Remarks:
    None.
*/

typedef void USB_DEVICE_AUDIO_EVENT_RESPONSE;
// *****************************************************************************
/* USB Device Audio Function Driver Event Handler Response None  

  Summary:
    USB Device Audio Function Driver Event Handler Response Type None.

  Description:
    This is the definition of the Audio Function Driver Event Handler Response
    Type none.

  Remarks:
    Intentionally defined to be empty.
*/

#define USB_DEVICE_AUDIO_EVENT_RESPONSE_NONE

// *****************************************************************************
/* USB Device Audio Event Handler Function Pointer Type.

  Summary:
    USB Device Audio Event Handler Function Pointer Type.

  Description:
    This data type defines the required function signature USB Device Audio
    Function Driver event handling callback function. The application must
    register a pointer to an Audio Function Driver events handling function who's
    function signature (parameter and return value types) match the types
    specified by this function pointer in order to receive event call backs from
    the Audio Function Driver. The function driver will invoke this function with
    event relevant parameters. The description of the event handler function
    parameters is given here.

    instanceIndex           - Instance index of the Audio Function Driver that generated the
                              event.

    event                   - Type of event generated.

    controlTransferHandle   - Control Transfer Handle for Audio function driver
                              events that require application response. The
                              application should use this handle when the
                              USB Audio Device Control Transfer functions to
                              respond to the events.

    pData                   - This parameter should be type casted to a event specific
                              pointer type based on the event that has occurred. Refer
                              to the USB_DEVICE_AUDIO_EVENT enumeration description for
                              more details.

    context                 - Value identifying the context of the application that
                              registered the event handling function.

  Remarks:
    None.
*/
typedef USB_DEVICE_AUDIO_EVENT_RESPONSE (*USB_DEVICE_AUDIO_EVENT_HANDLER )
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * pData,
    uintptr_t context
);

// *****************************************************************************
/* USB Device Audio Function Driver Transfer Handle Definition

  Summary:
    USB Device Audio Function Driver Transfer Handle Definition.

  Description:
    This definition defines a USB Device Audio Function Driver Transfer Handle.
    A Transfer Handle is owned by the application but its value is modified by
    the USB_DEVICE_AUDIO_Write() and USB_DEVICE_AUDIO_Read() functions. The
    transfer handle is valid for the life time of the transfer and expires
    when the transfer related event had occurred.

  Remarks:
    None.
*/

typedef uintptr_t USB_DEVICE_AUDIO_TRANSFER_HANDLE;

// *****************************************************************************
/* USB Device Audio Function Driver Invalid Transfer Handle Definition
 
  Summary:
    USB Device Audio Function Driver Invalid Transfer Handle Definition.

  Description:
    This definition defines a USB Device Audio Function Driver Invalid Transfer 
    Handle.  A Invalid Transfer Handle is returned by the USB_DEVICE_Audio_Write()
    and USB_DEVICE_Audio_Read() functions when the request was not successful.

  Remarks:
    None.
*/

#define USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID  ((USB_DEVICE_AUDIO_TRANSFER_HANDLE)(-1))

// *****************************************************************************

/* USB Device Audio Function Driver USB Device Audio Result enumeration.

  Summary:
    USB Device Audio Function Driver USB Device Audio Result enumeration.

  Description:
    This enumeration lists the possible USB Device Audio Function Driver operation
    results. These values are returned by the USB_DEVICE_AUDIO_Write() and
    USB_DEVICE_AUDIO_Read() functions.

  Remarks:
    None.
 */

typedef enum
{
    /* The operation was successful */
    USB_DEVICE_AUDIO_RESULT_OK /* DOM-IGNORE-BEGIN */ = USB_ERROR_NONE /* DOM-IGNORE-END */,

    /* The transfer size is invalid. Refer to the description of the read or write function for more details */
    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_SIZE_INVALID /* DOM-IGNORE-BEGIN */ = USB_ERROR_IRP_SIZE_INVALID /* DOM-IGNORE-END */,

    /* The transfer queue is full and no new transfers can be scheduled */
    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL /* DOM-IGNORE-BEGIN */ = USB_ERROR_IRP_QUEUE_FULL /* DOM-IGNORE-END */,

    /* The specified instance is not provisioned in the system */
    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID /* DOM-IGNORE-BEGIN */ = USB_ERROR_DEVICE_FUNCTION_INSTANCE_INVALID /* DOM-IGNORE-END */,

    /* The specified instance is not configured yet */
    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_NOT_CONFIGURED /* DOM-IGNORE-BEGIN */ = USB_ERROR_ENDPOINT_NOT_CONFIGURED /* DOM-IGNORE-END */,

    /* The event handler provided is NULL */
    USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_HANDLER  /* DOM-IGNORE-BEGIN */ =  USB_ERROR_PARAMETER_INVALID /* DOM-IGNORE-END */,
	/* The control transfer was aborted */
    USB_DEVICE_AUDIO_RESULT_ERROR_CONTROL_TRANSFER_FAILED
        /* DOM-IGNORE-BEGIN*/ = USB_ERROR_DEVICE_CONTROL_TRANSFER_FAILED /*DOM-IGNORE-END*/,
		
    /* Interface number passed to the read or write function is invalid. */
    USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_INTERFACE_ID /* DOM-IGNORE-BEGIN */ = - 13 /* DOM-IGNORE-END */,

    USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_BUFFER /* DOM-IGNORE-BEGIN */ = -14 /* DOM-IGNORE-END */


}
USB_DEVICE_AUDIO_RESULT;


typedef enum
{
    USB_DEVICE_AUDIO_INTERFACE_STREAM_UNDEFINED=0,
    USB_DEVICE_AUDIO_INTERFACE_STREAM_AUDIO,
    USB_DEVICE_AUDIO_INTERFACE_STREAM_MIDI,
    USB_DEVICE_AUDIO_INTERFACE_FEEDBACK,

}USB_DEVICE_AUDIO_INTERFACE_TYPE;

typedef enum
{
    USB_DEVICE_AUDIO_INSTANCE_NOT_INITIALIZED = 0,
    USB_DEVICE_AUDIO_INSTANCE_INITIALIZED,
    USB_DEVICE_AUDIO_INSTANCE_OPENED,      
    USB_DEVICE_AUDIO_INSTANCE_CLOSED

}USB_DEVICE_AUDIO_INSTANCE_STATE;


// *****************************************************************************
/* USB Device Audio Function Driver Read and Write Complete Event Data.

  Summary:
    USB Device Audio Function Driver Read and Write Complete Event Data.

  Description:
    This data type defines the data structure returned by the driver along with
    USB_DEVICE_AUDIO_EVENT_READ_COMPLETE and USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE
    events.

  Remarks:
    None.
*/

typedef struct
{
    /* Transfer handle associated with this
     * read or write request */
    USB_DEVICE_AUDIO_TRANSFER_HANDLE handle;

    /* Indicates the amount of data (in bytes) that was
     * read or written */
    uint16_t length;
}
USB_DEVICE_AUDIO_EVENT_DATA_WRITE_COMPLETE,
USB_DEVICE_AUDIO_EVENT_DATA_READ_COMPLETE;

// *****************************************************************************
/* USB Device Audio Function Driver IRP object.

  Summary:
    USB Device Audio Function Driver IRP object.

  Description:
    IRP object used by the Audio to service application requests.

  Remarks:
    None.
*/
typedef struct
{

   USB_DEVICE_IRP irp;

   USB_DEVICE_AUDIO_INDEX iAudio;

}USB_DEVICE_AUDIO_IRP_OBJECT;


typedef struct
{
    /* End point address */
    uint8_t epAddr;

    /* End point maximum payload */
    uint16_t epMaxPacketSize;

    /*  IRP object Q per end point */
    USB_DEVICE_AUDIO_IRP_OBJECT irpObject[USB_DEVICE_AUDIO_QUEUE_SIZE];

}USB_DEVICE_AUDIO_EP_INSTANCE;


typedef struct
{
    /* number of end-points in this interface */
    uint8_t numEndPoints;

    /* end points associated with this interface */
    USB_DEVICE_AUDIO_EP_INSTANCE isoDataEp;

    USB_DEVICE_AUDIO_EP_INSTANCE isoSyncEp;

}USB_DEVICE_AUDIO_STREAMING_INTERFACE_ALTERNATE_SETTING;

typedef struct
{

    /* interface number */
    uint8_t interfaceNum;

    USB_DEVICE_AUDIO_INTERFACE_TYPE infType;

    /* currently active alternate setting */
    uint8_t activeSetting;

    USB_DEVICE_AUDIO_STREAMING_INTERFACE_ALTERNATE_SETTING  alterntSetting[USB_DEVICE_AUDIO_MAX_ALTERNATE_SETTING];

}USB_DEVICE_AUDIO_STREAMING_INTERFACE;



typedef struct
{
    /* control interface number */
    uint8_t bControlInterfaceNum;

    /* number of streaming interfaces */
    uint8_t numStreamingInf;

    /* Audio spec in BCD 0x100 or 0x200 */
    uint16_t bcdADC;

    /* optional interrupt ep info */
    USB_DEVICE_AUDIO_EP_INSTANCE intEp[1];

    /* presence or absence of the interrupt EP */
    bool isIntEpExists;

    USB_DEVICE_AUDIO_STREAMING_INTERFACE streamInf[USB_DEVICE_AUDIO_MAX_STREAMING_INTERFACES];

}USB_DEVICE_AUDIO_INTERFACE_COLLECTION;




typedef struct
{
    /* device layer instance associated with this function driver instance */
    USB_DEVICE_HANDLE devLayerHandle;;

    /* instance index */
    USB_DEVICE_AUDIO_INDEX audioIndex;

    USB_DEVICE_AUDIO_INTERFACE_COLLECTION infCollection;

    /* Current state of the function driver instance */
    USB_DEVICE_AUDIO_INSTANCE_STATE state;

    /* Application callback */
    USB_DEVICE_AUDIO_EVENT_HANDLER appEventCallBack;
   
      /* Application user data */
    uintptr_t userData;

}USB_DEVICE_AUDIO_INSTANCE;


typedef struct
{
    uint8_t interfaceNumber;
    uint8_t interfaceAlternateSettting;
} USB_DEVICE_AUDIO_INTERFACE_INFO;

// *****************************************************************************
// *****************************************************************************
// Section: USB Device Audio Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
      USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_EventHandlerSet
      (
          USB_DEVICE_AUDIO_INDEX instance ,
          USB_DEVICE_AUDIO_EVENT_HANDLER eventHandler ,
          uintptr_t context
      );
    
  Summary:
    This function registers an event handler for the specified Audio function
    driver instance. 
  Description:
    <align justify>
    This function registers a event handler for the specified Audio function
    driver instance. This function should be called by the client when it 
    receives a SET CONFIGURATION event from the device layer. A event handler
    must be registered for function driver to respond to function driver 
    specific commands. If the event handler is not registered, the device
    layer will stall function driver specific commands and the USB device
    may not function.
    </align>
   Precondition:
    This function should be called when the function driver has been initialized
    as a result of a set configuration.
	
  Parameters:
    instance  - Instance of the Audio Function Driver.
    eventHandler - A pointer to event handler function.
    context - Application specific context that is returned in the event handler.
  
  Return:
    USB_DEVICE_AUDIO_RESULT_OK - The operation was successful
    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID - The specified instance does 
    not exist.
    USB_DEVICE_AUDIO_RESULT_ERROR_INVALID_HANDLER - The eventHandler parameter is 
    NULL
  Example:
    <code>
    // This code snippet shows an example registering an event handler. Here
    // the application specifies the context parameter as a pointer to an
    // application object (appObject) that should be associated with this 
    // instance of the Audio function driver.
    
    USB_DEVICE_AUDIO_RESULT result;
    
    USB_DEVICE_AUDIO_EVENT_RESPONSE APP_USBDeviceAUDIOEventHandler 
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex ,
        USB_DEVICE_AUDIO_EVENT event ,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle
        void* pData, uintptr_t context 
    )
    {
        // Event Handling comes here

        switch(event) 
        {
            ...
        }

        return(USB_DEVICE_AUDIO_EVENT_RESPONSE_NONE);


    }

    result = USB_DEVICE_AUDIO_EventHandlerSet ( 0 ,&APP_EventHandler, (uintptr_t) &appObject);

    if(USB_DEVICE_AUDIO_RESULT_OK != result)
    {
        SYS_ASSERT ( false , "invalid event handler function" );
    }
  
    </code>

  Remarks:
    None.

 */
USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_EventHandlerSet
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT_HANDLER eventHandler ,
    uintptr_t context
);
/**************************************************************************
  Function:
       USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Write
       (
           USB_DEVICE_AUDIO_INDEX instance ,
           USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
           uint8_t interfaceNum ,
           void * data ,
           size_t size
       );
  Summary:
    This function requests a data write to the USB Device Audio Function
    Driver Layer.
  Description:
    <align justify>
    This function requests a data write to the USB Device Audio Function
    Driver Layer. The function places a requests with driver, the request
    will get serviced as data is requested by the USB Host. A handle to the
    request is returned in the transferHandle parameter. The termination of
    the request is indicated by the USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE
    event. The amount of data written and the transfer handle associated
    with the request is returned along with the event in writeCompleteData 
	member of the pData parameter in the event handler. 
	
	The  transfer  handle  expires when  event  handler  for  the  
	USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE   exits. If the  read  request
	could  not  be  accepted,  the  function  returns  an error  code  and 
	transferHandle  will contain the value USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID.
    </align>
  Precondition:
    The function driver should have been configured.
    Parameters:
    instance -        USB Device Audio Function Driver instance.
    transferHandle -  Pointer to a USB_DEVICE_AUDIO_TRANSFER_HANDLE type of
                      variable. This variable will contain the transfer
                      handle in case the write request was successful.
    interfaceNum -    The USB Audio streaming interface number on which the
                      write request is to placed.
    data  -           pointer to the data buffer contains the data to be written.
    size -            Size of the data buffer. Refer to the description section
                      for more details on how the size affects the transfer.
  Return:
    USB_DEVICE_AUDIO_RESULT_OK - The read request was successful. transferHandle
    contains a valid transfer handle.

    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL - internal request queue
    is full. The write request could not be added.

    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_SIZE_INVALID - The specified transfer
    size was not a mulitple of endpoint size or is 0.

    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_NOT_CONFIGURED - The specified
    instance is not configured yet.

    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID - The specified instance
    was not provisioned in the application and is invalid.
  Example:
    <code>
    // Shows an example of how to write. This assumes that
    // driver was opened successfully.
       USB_DEVICE_AUDIO_INDEX iAudio;
        USB_DEVICE_AUDIO_TRANSFER_HANDLE transferHandle;
        unit8_t interfaceNumber;
        unit8_t txBuffer[192];
        USB_DEVICE_AUDIO_RESULT writeRequestResult;
        iAudio = 0; //specify the Audio Function driver instance number.
        interfaceNumber = 1; //Specify the Audio Streaming interface number.
    
        writeRequestResult = USB_DEVICE_AUDIO_Write
                             (
                                iAudio,
                                &transferHandle,
                                interfaceNumber,
                                &txBuffer
                                192
                              );

    if(USB_DEVICE_AUDIO_RESULT_OK != writeRequestResult)
    {
        //Do Error handling here
    }

    // The completion of the write request will be indicated by the
    // USB_DEVICE_AUDIO_EVENT_Write_COMPLETE event.
    </code>
  Remarks:
    None                                                                   
  **************************************************************************/
USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Write
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
    uint8_t interfaceNum ,
    void * data ,
    size_t size
);

/***************************************************************************
  Function:
       USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Read
       (
           USB_DEVICE_AUDIO_INDEX iAudio ,
           USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
           uint8_t interfaceNum ,
           void * data ,
           size_t size
       );
  Summary:
    This function requests a data read from the USB Device Audio Function
    Driver Layer.
  Description:
    <align justify>
    This function requests a data read from the USB Device Audio Function
    Driver Layer. The function places a requests with driver, the request
    will get serviced as data is made available by the USB Host. A handle
    to the request is returned in the transferHandle parameter. The
    termination of the request is indicated by the
    USB_DEVICE_AUDIO_EVENT_READ_COMPLETE event. The amount of data read and
    the transfer handle associated with the request is returned along with
    the event. The transfer handle expires when event handler for the
    USB_DEVICE_AUDIO_EVENT_READ_COMPLETE exits. If the read request could
    not be accepted, the function returns an error code and transferHandle
    will contain the value USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID.
    </align>
  Conditions:
    The function driver should have been configured.
  Input:
    instance -        USB Device Audio Function Driver instance.
    transferHandle -  Pointer to a USB_DEVICE_AUDIO_TRANSFER_HANDLE type of
                      variable. This variable will contain the transfer
                      handle in case the read request was successful.
    interfaceNum -    The USB Audio streaming interface number on which read
                      request is to placed.
    data  -           pointer to the data buffer where read data will be stored.
    size -            Size of the data buffer. Refer to the description section
                      for more details on how the size affects the transfer.
    Return:
    USB_DEVICE_AUDIO_RESULT_OK - The read request was successful. transferHandle
    contains a valid transfer handle.

    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_QUEUE_FULL - internal request queue
    is full. The write request could not be added.

    USB_DEVICE_AUDIO_RESULT_ERROR_TRANSFER_SIZE_INVALID - The specified transfer
    size was not a mulitple of endpoint size or is 0.

    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_NOT_CONFIGURED - The specified
    instance is not configured yet.

    USB_DEVICE_AUDIO_RESULT_ERROR_INSTANCE_INVALID - The specified instance
    was not provisioned in the application and is invalid.
    Example:
        <code>
    // Shows an example of how to read. This assumes that
    // driver was opened successfully.
    USB_DEVICE_AUDIO_INDEX iAudio;
    USB_DEVICE_AUDIO_TRANSFER_HANDLE transferHandle;
    unit8_t interfaceNumber;
    unit8_t rxBuffer[192];
    USB_DEVICE_AUDIO_RESULT readRequestResult; 
    iAudio = 0; //specify the Audio Function driver instance number.
    interfaceNumber = 1; //Specify the Audio Streaming interface number.
    readRequestResult = USB_DEVICE_AUDIO_Read
                        (
                            iAudio,
                            &transferHandle,
                            interfaceNumber,
                            &rxBuffer,
                            192
                        );

    if(USB_DEVICE_AUDIO_RESULT_OK != readRequestResult)
    {
        //Do Error handling here
    }

    // The completion of the read request will be indicated by the
    // USB_DEVICE_AUDIO_EVENT_READ_COMPLETE event.
    </code>
    Remarks:
    None                                                                    
  ***************************************************************************/
USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_Read
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_TRANSFER_HANDLE* transferHandle,
    uint8_t interfaceNum ,
    void * data ,
    size_t size
);




// *****************************************************************************
/* Function:
    USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlSend
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        void * data, size_t size
    );

  Summary:
    This function allows the application to respond to the Audio function driver
    specific control transfer requests. It allows the application to send data
    to the host in the data stage of the control transfer.

  Description:
    This function allows the application to respond to the Audio  function  driver
    specific control transfer requests.  It allows the application to send  data
    to the host in the data stage of the control  transfer.   For  example, if 
    the Host requests current Volume settings to Device,  then the Device needs
    to send a control  transfer data to the Host. The function can be called  in
    the  Audio  Function  Driver  event handler or can be called outside the
    event handler.  Calling  this  function outside the event handler defers the
    response to the event. This allows the application to prepare the response
    data out of the event  handler  context, especially if the data is not
    readily available.  Note however,  that  there are  timing  considerations
    when  responding  to  the   control   transfer. Exceeding the response time
    will  cause  the  host  to  cancel  the  control transfer and may cause USB
    host to reject the device.  The application  must use the control transfer
    handle that was generated along with the  event  as the controlTransferHandle.

  Precondition:
    This function should only be called in response to a Audio function driver
    event that requires a control transfer response.

  Parameters:
    instance  - USB Device Audio Function Driver instance.
    controlTransferHandle  - Control Transfer handle for the control transfer.
    data -  Data that represents the data stage of the control transfer.
    size - size (in bytes) of the data to sent.

  Returns:
    USB_DEVICE_AUDIO_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.

    USB_DEVICE_AUDIO_RESULT_OK - The request was successful.

  Example:
    <code>

    // ------------------------------------------------------------------
    // In this example, the application responds to am Audio Control request
    // with in the event handler. The application uses the
    // USB_DEVICE_AUDIO_ControlSend() function to do this.
    // ------------------------------------------------------------------
    uint8_t DACMute = 1; // Holds the status of Mute Control
    USB_DEVICE_AUDIO_EVENT_RESPONSE USBDeviceAudioEventHandler
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex,
        USB_DEVICE_AUDIO_EVENT event,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        USB_DEVICE_AUDIO_EVENT_DATA * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED:
                //In this example we have received a Get Mute request from the Host.

                // Typcast the recived data into interface request.
                controlRequest = (USB_AUDIO_CONTROL_INTERFACE_REQUEST*) pData;

                //check entity ID (Note: Entity IDs are specified in the USB device descriptor.
                switch(controlRequest->entityID)
                {
                    case  APP_ID_FEATURE_UNIT :
                    featureRequest = (USB_AUDIO_FEATURE_CONTROL_REQUEST*)pData;
                    switch(featureRequest->controlSelector)
                    {
                        case USB_AUDIO_FCS_MUTE_CONTROL:
                        {
                            if(featureRequest->bRequest ==  USB_AUDIO_CSRC_GET_CUR)
                            {
                                 // In this case, the application should send the current mute
                                //  status to the host. The application must send the
                                // USB_DEVICE_AUDIO_ControlSend() function to send the data.
                                USB_DEVICE_AUDIO_ControlSend(iAudio, controlHandle, (uint8_t *)&DACMute, 1 );
                            }
                        }
                        break;
                     }
                     break;
         }
    break;
    }

  Remarks:
    None.

 */

USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlSend
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * data, size_t size
);

// *****************************************************************************
/* Function:
    USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlReceive
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        void * data, size_t size
    );

  Summary:
    This function allows the application to respond to the Audio function driver
    specific control transfer requests. It allows the application to receive data
    from the host in the data stage of the control transfer.

  Description:
    This function allows the application to respond to the Audio  function  driver
    specific control transfer requests.  It allows the  application  to  receive
    data from the host in the data stage of the control transfer.

    For example,when the Host wants to set current Volume settings to Device, the
    Host first sends a SETUP packet to the Device indicating that it intedns to 
    set Volume. After receving the SETUP packet the Device should be prepared to
    recieve cuurent Volume from Host. Application should make use of 
    USB_DEVICE_AUDIO_ControlReceive() function to receive data from the Host in 
    such cases. The function can be called in the Audio Function Driver event
    handler or can be called outside the event handler. Calling this function
    outside the event handler defers the response to the event. This allows the
    application to prepare the data buffer out of the event handler context,
    especially if the data buffer to receive the data is not readily available.
    Note however, that there are timing considerations when responding to the
    control transfer. Exceeding the response time will cause the host to cancel
    the control transfer and may cause USB host to reject the device. The
    application must use the control transfer handle that was generated along with
    the event as the controlTransferHandle.
	

  Precondition:
    This function should only be called in response to a Audio function driver
    event that requires a control transfer response.

  Parameters:
    instance  - USB Device Audio Function Driver instance.
    controlTransferHandle  - Control Transfer handle for the control transfer.
    data -  Data buffer to receive the data stage of the control transfer.
    size - size (in bytes) of the data to sent.

  Returns:
    USB_DEVICE_AUDIO_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.

    USB_DEVICE_AUDIO_RESULT_OK - The request was successful.

  Example:
    <code>

    // ------------------------------------------------------------------
    // In this example, the application receives current Mute info
    // with in the event handler. The application uses the
    // USB_DEVICE_AUDIO_ControlReceive() function to do this.
    // ------------------------------------------------------------------
    uint8_t DACMute = 1; // Holds the status of Mute Control
    USB_DEVICE_AUDIO_EVENT_RESPONSE USBDeviceAudioEventHandler
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex,
        USB_DEVICE_AUDIO_EVENT event,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        USB_DEVICE_AUDIO_EVENT_DATA * pData,
        uintptr_t userData
    )
    {
        switch(event)
        {
            case USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED:
                //In this example we have received a Set Mute request from the Host.

                // Typcast the recived data into interface request.
                controlRequest = (USB_AUDIO_CONTROL_INTERFACE_REQUEST*) pData;

                //check entity ID (Note: Entity IDs are specified in the USB device descriptor.
                switch(controlRequest->entityID)
                {
                    case  APP_ID_FEATURE_UNIT :
                    featureRequest = (USB_AUDIO_FEATURE_CONTROL_REQUEST*)pData;
                    switch(featureRequest->controlSelector)
                    {
                        case USB_AUDIO_FCS_MUTE_CONTROL:
                        {
                            if(featureRequest->bRequest ==  USB_AUDIO_CSRC_SET_CUR)
                            {
                                //A control write transfer recived from Host. Now recieve data from Host.
                                USB_DEVICE_AUDIO_ControlReceive(iAudio, controlHandle,(uint8_t *) &DACMute, 1 );
                            }
                        }
                        break;
                     }
                     break;
         }
    break;

     case USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVED:
        USB_DEVICE_ControlStatus(appData.usbDevHandle,controlTransferHandle, USB_DEVICE_CONTROL_STATUS_OK );
        if (appData.currentInterfaceAlternateSetting == 1)
        AK4953ADACMute(pCodecHandle, DACMute);
     break;
    }
  Remarks:
    None.

 */


USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlReceive
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    void * data, size_t size
);

// *****************************************************************************
/* Function:
    USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlStatus
    (
        USB_DEVICE_AUDIO_INDEX instanceIndex,
        USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE * controlTransferHandle,
        USB_DEVICE_AUDIO_CONTROL_STATUS status
    );

  Summary:
    This function allows the application to complete the status stage of the
    the Audio Function Driver specific control transfer request.

  Description:
    This function allows the application to complete the status stage of the the
    Audio Function Driver specific control transfer request.  The application  can
    either accept the data stage or stall it. Calling this function with status
    set to USB_DEVICE_AUDIO_CONTROL_STATUS_OK will acknowledge the status stage of
    the control transfer.  The control transfer can be stalled  by  setting  the
    status parameter to USB_DEVICE_AUDIO_CONTROL_STATUS_STALL.  The  function  can
    be called in the  Audio  Function  Driver  event  handler  or  can  be  called
    outside  the  event  handler.   Calling  this  function  outside  the  event
    handler defers the response to  the  event.   This  allows  the  application
    to analyze the event response outside  the  event  handler.   Note  however,
    that  there  are  timing  considerations  when  responding  to  the  control
    transfer.  Exceeding the  response  time  will  cause  the  host  to  cancel
    the control transfer and may cause USB  host  to  reject  the  device.   The
    application  must  use  the  control  transfer  handle  that  was  generated
    along with the event as the  controlTransferHandle.   The  application  must
    be aware of events and associated  control  transfers  that  do  or  do  not
    require data stages.  Incorrect usage of the  USB_DEVICE_AUDIO_ControlStatus()
    function  could   cause   the   device   function   to   be   non-compliant.

  Precondition:
    This function should only be called in response to a Audio function driver
    event that requires a control transfer response.

  Parameters:
    instance  - USB Device Audio Function Driver instance.
    controlTransferHandle  - Control Transfer handle for the control transfer.
    status - Set to USB_DEVICE_AUDIO_CONTROL_STATUS_OK to acknowledge the
    control transfer. Set to USB_DEVICE_AUDIO_CONTROL_STATUS_STALL to stall the
    transfer.

  Returns:
    USB_DEVICE_AUDIO_RESULT_ERROR_CONTROL_TRANSFER_FAILED - The request was not
    successful because the USB host cancelled the control transfer.

    USB_DEVICE_AUDIO_RESULT_OK - The request was successful.

  Example:
    <code>

  Remarks:
    None.

 */


USB_DEVICE_AUDIO_RESULT USB_DEVICE_AUDIO_ControlStatus
(
    USB_DEVICE_AUDIO_INDEX instanceIndex,
    USB_DEVICE_AUDIO_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    USB_DEVICE_AUDIO_CONTROL_STATUS status
);

 



#endif // _USB_DEVICE_AUDIO_H

/*******************************************************************************
 End of File
********************************************************************************/


