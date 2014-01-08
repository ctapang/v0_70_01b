/*******************************************************************************
 USB CDC Class Function Driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_cdc.c

  Summary:
    USB CDC class function driver.

  Description:
    USB CDC class function driver.
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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_device_cdc.h"
#include "usb/src/usb_device_cdc_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* CDC Device function driver structure

  Summary:
    Defines the function driver structure required for the device layer.

  Description:
    This data type defines the function driver structure required for the
    device layer.

  Remarks:
    This structure is private to the USB stack.
 */

USB_DEVICE_FUNCTION_DRIVER cdcFuncDriver =
{

    /* CDC init function */
    .initializeByDescriptor         = _USB_DEVICE_CDC_Initialization ,

    /* CDC de-init function */
    .deInitialize                   = _USB_DEVICE_CDC_Deinitialization ,

    /* EP0 activity callback */
    .controlTransferNotification    = _USB_DEVICE_CDC_ControlTransferHandler,

    /* CDC tasks function */
    .tasks                          = NULL
        
};

// *****************************************************************************
/* CDC Device IRPs

  Summary:
    Array of CDC Device IRP. 

  Description:
    Array of CDC Device IRP. This array of IRP will be shared by read, write and
    notification data requests.

  Remarks:
    This array is private to the USB stack.
 */

USB_DEVICE_IRP gUSBDeviceCDCIRP[USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED];

// *****************************************************************************
/* CDC Instance structure

  Summary:
    Defines the CDC instance(s).

  Description:
    This data type defines the CDC instance(s). The number of instances is
    defined by the application using USB_DEVICE_CDC_INSTANCES_NUMBER.

  Remarks:
    This structure is private to the CDC.
 */
USB_DEVICE_CDC_INSTANCE gUSBDeviceCDCInstance[USB_DEVICE_CDC_INSTANCES_NUMBER];

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************




// *****************************************************************************
// *****************************************************************************
// Section: USB DEVICE stack internal functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void USB_DEVICE_CDC_Initialization ( SYS_MODULE_INDEX iCDC ,
                                     DRV_HANDLE deviceHandle ,
                                     void* initData ,
                                     uint8_t infNum ,
                                     uint8_t altSetting ,
                                     uint8_t descType ,
                                     uint8_t * pDesc )

  Remarks:
    See prototype in usb_device_cdc_local.h.
 */

void _USB_DEVICE_CDC_Initialization 
( 
    SYS_MODULE_INDEX iCDC ,
    USB_DEVICE_HANDLE deviceHandle ,
    void* initData ,
    uint8_t infNum ,
    uint8_t altSetting ,
    uint8_t descType ,
    uint8_t * pDesc 
)
{
    /* avoid unused warning */
    ( void ) ( altSetting );
    ( void ) ( initData );
    uint8_t epAddress;
    uint8_t epDir;
    uint16_t maxPacketSize;
    USB_DEVICE_CDC_INSTANCE * thisCDCInstance;
    USB_DEVICE_CDC_INIT * cdcInit;
    USB_ENDPOINT_DESCRIPTOR *pEPDesc;
    USB_INTERFACE_DESCRIPTOR *pInfDesc;
    USB_DEVICE_CDC_ENDPOINT * deviceCDCEndpoint;
 
    /* check the validity of the function driver index */
    if (iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER)
    {
        /* Assert on invalid CDC index */
        SYS_ASSERT ( false , "Invalid CDC instance number" );
        return;
    }

    thisCDCInstance = &gUSBDeviceCDCInstance[iCDC];

    /* Initialize the queue sizes. This code may run several times
     * but then we dont expect the queue sizes to change.*/
    
    cdcInit = ((USB_DEVICE_CDC_INIT *)initData);
    thisCDCInstance->queueSizeWrite = cdcInit->queueSizeWrite;
    thisCDCInstance->queueSizeRead = cdcInit->queueSizeRead;
    thisCDCInstance->queueSizeSerialStateNotification = 
            cdcInit->queueSizeSerialStateNotification;
    thisCDCInstance->currentQSizeWrite = 0;
    thisCDCInstance->currentQSizeRead = 0;
    thisCDCInstance->currentQSizeSerialStateNotification = 0;

    /* check the type of descriptor passed by device layer */
    switch ( descType )
    {
        /* interface descriptor passed */
        case USB_DESCRIPTOR_INTERFACE:
            {
                pInfDesc = ( USB_INTERFACE_DESCRIPTOR * )pDesc;

                /* Preserve the device layer handle */
                thisCDCInstance->deviceHandle = deviceHandle;

                /* check if this is notification(communication) interface */
                if ( ( pInfDesc->bInterfaceClass == USB_CDC_COMMUNICATIONS_INTERFACE_CLASS_CODE ) &&
                        ( pInfDesc->bInterfaceSubClass == USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL ) )
                {
                    /* Save the notification interface number */
                    thisCDCInstance->notificationInterface.interfaceNum = infNum;
                }

                /* data interface */
                else if ( ( pInfDesc->bInterfaceClass == USB_CDC_DATA_INTERFACE_CLASS_CODE ) )
                {
                    /* save the data interface number */
                    thisCDCInstance->dataInterface.interfaceNum = infNum;
                }

                else
                {
                    /* Ignore anything else */
                    SYS_ASSERT ( false , "Invalid interface presented to CDC " );
                }

                break;
            }

            /* endpoint descriptor passed */
        case USB_DESCRIPTOR_ENDPOINT:
            {

                pEPDesc = ( USB_ENDPOINT_DESCRIPTOR* ) pDesc;

                /* save the ep address */
                epAddress = pEPDesc->bEndpointAddress;

                /* get the direction */
                epDir = ( epAddress & 0x80 ) ? 
                    ( USB_DEVICE_CDC_ENDPOINT_TX ) : ( USB_DEVICE_CDC_ENDPOINT_RX );

                /* save max packet size */
                maxPacketSize = ( ( USB_ENDPOINT_DESCRIPTOR* ) pDesc )->wMaxPacketSize;

                if ( pEPDesc->transferType == USB_TRANSFER_TYPE_BULK )
                {
                    /* This is a data interface endpoint */

                    deviceCDCEndpoint = &thisCDCInstance->dataInterface.endpoint[epDir];
                }
                else if( pEPDesc->transferType == USB_TRANSFER_TYPE_INTERRUPT)
                {
                    /* This is notification endpoint */

                    deviceCDCEndpoint = &thisCDCInstance->notificationInterface.endpoint[epDir];
                }
                else
                {
                    /* We cannot support ny other type of endpoint for now */

                    SYS_ASSERT ( false , "EP type is not supported by CDC " );
                    break;

                }

                /* save ep address to the data interface */
                deviceCDCEndpoint->address = epAddress;

                /* save max packet size to the data interface */
                deviceCDCEndpoint->maxPacketSize = maxPacketSize;

                /* enable the endpoint */
                USB_DEVICE_EndpointEnable ( deviceHandle ,
                        epAddress ,
                        pEPDesc->transferType ,
                        maxPacketSize );

                /* Indicate that the endpoint is configured */
                deviceCDCEndpoint->isConfigured = true;

                break;
            }

        case USB_CDC_DESC_CS_INTERFACE:
            {
                /*TBD*/
                break;
            }

        default:
            /* Unsupported descriptor type */
            break;

    }

}

void _USB_DEVICE_CDC_EndpointDisable
(
    USB_DEVICE_HANDLE deviceHandle, 
    USB_DEVICE_CDC_ENDPOINT * deviceCDCEndpoint
)
{
    if(deviceCDCEndpoint->isConfigured)
    {
        USB_DEVICE_IRPCancelAll(deviceHandle, deviceCDCEndpoint->address);
        USB_DEVICE_EndpointDisable(deviceHandle, deviceCDCEndpoint->address);
        deviceCDCEndpoint->isConfigured = false;
    }
}


/******************************************************************************
  Function:
    void USB_DEVICE_CDC_Deinitialization ( SYS_MODULE_INDEX iCDC )

  Remarks:
    See prototype in usb_device_cdc_local.h.
 */

void _USB_DEVICE_CDC_Deinitialization ( SYS_MODULE_INDEX iCDC )
{
    /* Cancel all IRPs on the owned endpoints and then 
     * disable the endpoint */

    USB_DEVICE_HANDLE deviceHandle;
    USB_DEVICE_CDC_ENDPOINT * deviceCDCEndpoint;

    if(iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER)
    {
        SYS_ASSERT(false," Invalid instance");
        return;
    } 

    deviceHandle = gUSBDeviceCDCInstance[iCDC].deviceHandle;

    deviceCDCEndpoint = &gUSBDeviceCDCInstance[iCDC].dataInterface.endpoint[0];
    _USB_DEVICE_CDC_EndpointDisable(deviceHandle, deviceCDCEndpoint);
    
    deviceCDCEndpoint = &gUSBDeviceCDCInstance[iCDC].dataInterface.endpoint[1];
    _USB_DEVICE_CDC_EndpointDisable(deviceHandle, deviceCDCEndpoint);
    
    deviceCDCEndpoint = &gUSBDeviceCDCInstance[iCDC].notificationInterface.endpoint[0];
    _USB_DEVICE_CDC_EndpointDisable(deviceHandle, deviceCDCEndpoint);
    
    deviceCDCEndpoint = &gUSBDeviceCDCInstance[iCDC].notificationInterface.endpoint[1];
    _USB_DEVICE_CDC_EndpointDisable(deviceHandle, deviceCDCEndpoint);
    
}


/******************************************************************************
  Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_CDC_ControlTransferHandler
    (
         SYS_MODULE_INDEX iCDC ,
         USB_DEVICE_CONTROL_TRANSFER_STATE controlTransferState ,
         SETUP_PKT* setupPktBuffer ,
         USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * bObj
    )

  Remarks:
    See prototype in usb_device_cdc_local.h.
 */

void _USB_DEVICE_CDC_ControlTransferHandler 
(
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle ,
    SYS_MODULE_INDEX iCDC ,
    USB_DEVICE_CONTROL_TRANSFER_EVENT controlTransferEvent,
    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * controlTransferEventData
)
{
    USB_DEVICE_HANDLE deviceHandle;
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    /* Check the validity of the function driver index */
    if (iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER)
    {
        /* invalid CDC index */
        SYS_ASSERT ( false , "Invalid CDC index" );
        return;
    }

    /* Get a local reference */
    thisCDCDevice = &gUSBDeviceCDCInstance[iCDC];

    /* Get the Device Layer handle */
    deviceHandle = thisCDCDevice->deviceHandle;

    switch (controlTransferEvent)
    {
        /* Setup packet received */

        case USB_DEVICE_CONTROL_SETUP_REQUEST:

            /* This means we have a setup packet for this interface */

            if(!(controlTransferEventData->setupRequest->bmRequestType & USB_CDC_REQUEST_CLASS_SPECIFIC))
            {
                /* This means this is not a class specific request.
                 * We stall this request */

                USB_DEVICE_ControlStatus(deviceHandle, controlTransferHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
            }
            else
            {
                /* Check if the requests belong to the ACM sub class */
                switch(controlTransferEventData->setupRequest->bRequest)
                {
                    case USB_CDC_REQUEST_SET_LINE_CODING:
                    case USB_CDC_REQUEST_GET_LINE_CODING:
                    case USB_CDC_REQUEST_SET_CONTROL_LINE_STATE:
                    case USB_CDC_REQUEST_SEND_BREAK:
                    case USB_CDC_REQUEST_SEND_ENCAPSULATED_COMMAND:
                    case USB_CDC_REQUEST_GET_ENCAPSULATED_RESPONSE:

                        /* These are ACM requests */

                        _USB_DEVICE_CDC_ACMSetUpPacketHandler(iCDC, thisCDCDevice, 
                                controlTransferEventData, controlTransferHandle);

                        break;
                    default:
                        /* This is an un-supported request */
                        USB_DEVICE_ControlStatus(deviceHandle, controlTransferHandle, 
                                USB_DEVICE_CONTROL_STATUS_ERROR);
                        break;
                }
            }

            break;

        case USB_DEVICE_CONTROL_DATA_RECEIVED:

            /* A control transfer data stage is complete. Send
             * this event to application */

            if(thisCDCDevice->appEventCallBack != NULL)
            {
                thisCDCDevice->appEventCallBack(iCDC, 
                        USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED,
                        controlTransferHandle, NULL, thisCDCDevice->userData );
            }

            break;

        case USB_DEVICE_CONTROL_DATA_SENT:

            /* A control transfer data stage is complete. Send
             * this event to application */

            if(thisCDCDevice->appEventCallBack != NULL)
            {
                thisCDCDevice->appEventCallBack(iCDC, 
                        USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT,
                        controlTransferHandle, NULL, thisCDCDevice->userData );
            }

        default:
            break;
    }
}

void _USB_DEVICE_CDC_SerialStateSendIRPCallback (USB_DEVICE_IRP * irp )
{
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    /* This function is called when a CDC Write IRP has
     * terminated */
    
    USB_DEVICE_CDC_EVENT_DATA_SERIAL_STATE_NOTIFICATION_COMPLETE serialStateEventData;

    /* The user data field of the IRP contains the CDC instance
     * that submitted this IRP */
    thisCDCDevice = &gUSBDeviceCDCInstance[irp->userData];

    /* populate the event handler for this transfer */
    serialStateEventData.handle = ( USB_DEVICE_CDC_TRANSFER_HANDLE ) irp;

    /* update the size written */
    serialStateEventData.length = irp->size;

    /* Reduce the queue size */

    thisCDCDevice->currentQSizeSerialStateNotification --;

    /* valid application event handler present? */
    if ( thisCDCDevice->appEventCallBack )
    {
        /* inform the application */
        thisCDCDevice->appEventCallBack ( (USB_DEVICE_CDC_INDEX)(irp->userData) , 
                   USB_DEVICE_CDC_EVENT_SERIAL_STATE_NOTIFICATION_COMPLETE ,
                   (USB_DEVICE_CONTROL_TRANSFER_HANDLE)0, &serialStateEventData,
                   thisCDCDevice->userData);
    }

}

void _USB_DEVICE_CDC_ReadIRPCallback (USB_DEVICE_IRP * irp )
{
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    /* This function is called when a CDC Write IRP has
     * terminated */
    
    USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE readEventData;

    /* The user data field of the IRP contains the CDC instance
     * that submitted this IRP */
    thisCDCDevice = &gUSBDeviceCDCInstance[irp->userData];

    /* populate the event handler for this transfer */
    readEventData.handle = ( USB_DEVICE_CDC_TRANSFER_HANDLE ) irp;

    /* update the size written */
    readEventData.length = irp->size;

    /* update the queue size */
    thisCDCDevice->currentQSizeRead --;

    /* valid application event handler present? */
    if ( thisCDCDevice->appEventCallBack )
    {
        /* inform the application */
        thisCDCDevice->appEventCallBack ( (USB_DEVICE_CDC_INDEX)(irp->userData) , 
                   USB_DEVICE_CDC_EVENT_READ_COMPLETE , 
                   (USB_DEVICE_CONTROL_TRANSFER_HANDLE)0, &readEventData,
                   thisCDCDevice->userData);
    }

}


void _USB_DEVICE_CDC_WriteIRPCallback (USB_DEVICE_IRP * irp )
{
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    /* This function is called when a CDC Write IRP has
     * terminated */
    
    USB_DEVICE_CDC_EVENT_DATA_WRITE_COMPLETE writeEventData;

    /* The user data field of the IRP contains the CDC instance
     * that submitted this IRP */
    thisCDCDevice = &gUSBDeviceCDCInstance[irp->userData];

    /* populate the event handler for this transfer */
    writeEventData.handle = ( USB_DEVICE_CDC_TRANSFER_HANDLE ) irp;

    /* update the size written */
    writeEventData.length = irp->size;

    /* Update the queue size*/
    thisCDCDevice->currentQSizeWrite --;

    /* valid application event handler present? */
    if ( thisCDCDevice->appEventCallBack )
    {
        /* inform the application */
        thisCDCDevice->appEventCallBack ( (USB_DEVICE_CDC_INDEX)(irp->userData) , 
                   USB_DEVICE_CDC_EVENT_WRITE_COMPLETE , 
                   (USB_DEVICE_CONTROL_TRANSFER_HANDLE)0, &writeEventData,
                   thisCDCDevice->userData);
    }

}


// *****************************************************************************
// *****************************************************************************
// Section: CDC Interface Function Definitions
// *****************************************************************************
// *****************************************************************************


USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Read 
(
    USB_DEVICE_CDC_INDEX iCDC ,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle ,
    void * data , size_t size
)
{
    unsigned int cnt;
    unsigned int remainder;
    USB_DEVICE_IRP * irp;
    USB_DEVICE_CDC_ENDPOINT * endpoint;
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    /* Check the validity of the function driver index */
    
    if (  iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER  )
    {
        /* Invalid CDC index */
        SYS_ASSERT(false, "Invalid CDC Device Index");
        return USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID;
    }

    thisCDCDevice = &gUSBDeviceCDCInstance[iCDC];
    endpoint = &thisCDCDevice->dataInterface.endpoint[USB_DEVICE_CDC_ENDPOINT_RX];
    *transferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Check if the endpoint is configured */
    if(!(endpoint->isConfigured))
    {
        /* This means that the endpoint is not configured yet */
        SYS_ASSERT(false, "Endpoint not configured");
        return (USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED);
    }

    /* For read the size should be a multiple of endpoint size*/
    remainder = size % endpoint->maxPacketSize;

    if((size == 0) || (remainder != 0))
    {
        /* Size is not valid */
        SYS_ASSERT(false, "Invalid size in IRP read");
        return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID);
    }

    /* Make sure that we are with in the queue size for this instance */
    if(thisCDCDevice->currentQSizeRead >= thisCDCDevice->queueSizeRead)
    {
        SYS_ASSERT(false, "Read Queue is full");
        return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);
    }

    // OSAL: Mutex Get

    /* loop and find a free IRP in the Q */
    for ( cnt = 0; cnt < USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED; cnt ++ )
    {
        if(gUSBDeviceCDCIRP[cnt].status <
                (USB_DEVICE_IRP_STATUS)USB_DEVICE_IRP_FLAG_DATA_PENDING)
        {
            /* This means the IRP is free. Configure the IRP
             * update the current queue size and then submit */

            irp = &gUSBDeviceCDCIRP[cnt];
            irp->data = data;
            irp->size = size;
            irp->userData = (uintptr_t) iCDC;
            irp->callback = _USB_DEVICE_CDC_ReadIRPCallback;
            thisCDCDevice->currentQSizeRead ++;
            *transferHandle = (USB_DEVICE_CDC_TRANSFER_HANDLE)irp;
            USB_DEVICE_IRPSubmit(thisCDCDevice->deviceHandle, 
                    endpoint->address, irp);

            //OSAL: Mutex Release

            return(USB_DEVICE_CDC_RESULT_OK);

        }
    }

    // OSAL: Mutex Release

    /* If here means we could not find a spare IRP */
    return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);

}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_Write 
(
    USB_DEVICE_CDC_INDEX iCDC ,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle ,
    const void * data , size_t size ,
    USB_DEVICE_CDC_TRANSFER_FLAGS flags 
)
{
    unsigned int cnt;
    unsigned int remainder;
    USB_DEVICE_IRP * irp;
    USB_DEVICE_IRP_FLAG irpFlag = 0;
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;
    USB_DEVICE_CDC_ENDPOINT * endpoint;

    /* Check the validity of the function driver index */
    
    if (  iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER  )
    {
        /* Invalid CDC index */
        SYS_ASSERT(false, "Invalid CDC Device Index");
        return USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID;
    }

    /* Initialize the transfer handle, get the instance object
     * and the transmit endpoint */

    * transferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    thisCDCDevice = &gUSBDeviceCDCInstance[iCDC];
    endpoint = &thisCDCDevice->dataInterface.endpoint[USB_DEVICE_CDC_ENDPOINT_TX];

    if(!(endpoint->isConfigured))
    {
        /* This means that the endpoint is not configured yet */
        SYS_ASSERT(false, "Endpoint not configured");
        return (USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED);
    }

    if(size == 0) 
    {
        /* Size cannot be zero */
        return (USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID);
    }

    /* Check the flag */

    if(flags & USB_DEVICE_CDC_TRANSFER_FLAGS_MORE_DATA_PENDING)
    {
        if(size < endpoint->maxPacketSize)
        {
            /* For a data pending flag, we must atleast get max packet
             * size worth data */

            return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_SIZE_INVALID);
        }

        remainder = size % endpoint->maxPacketSize;
        
        if(remainder != 0)
        {
            size -= remainder;
        }

        irpFlag = USB_DEVICE_IRP_FLAG_DATA_PENDING;
    }
    else if(flags & USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE)
    {
        irpFlag = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
    }

    if(thisCDCDevice->currentQSizeWrite >= thisCDCDevice->queueSizeWrite)
    {
        SYS_ASSERT(false, "Write Queue is full");
        return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);
    }

    // OSAL: Mutex Get

    /* loop and find a free IRP in the Q */
    for ( cnt = 0; cnt < USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED; cnt ++ )
    {
        if(gUSBDeviceCDCIRP[cnt].status < 
                (USB_DEVICE_IRP_STATUS)USB_DEVICE_IRP_FLAG_DATA_PENDING)
        {
            /* This means the IRP is free */

            irp         = &gUSBDeviceCDCIRP[cnt];
            irp->data   = (void *)data;
            irp->size   = size;
            
            irp->userData   = (uintptr_t) iCDC;
            irp->callback   = _USB_DEVICE_CDC_WriteIRPCallback;
            irp->flags      = irpFlag; 

            thisCDCDevice->currentQSizeWrite++;
            *transferHandle = (USB_DEVICE_CDC_TRANSFER_HANDLE)irp;

            USB_DEVICE_IRPSubmit(thisCDCDevice->deviceHandle, 
                    endpoint->address, irp);

            //OSAL: Mutex Release

            return(USB_DEVICE_CDC_RESULT_OK);

        }
    }

    // OSAL: Mutex Release

    /* If here means we could not find a spare IRP */
    return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);

}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_EventHandlerSet 
(
    USB_DEVICE_CDC_INDEX iCDC ,
    USB_DEVICE_CDC_EVENT_HANDLER eventHandler,
    uintptr_t userData

)
{
    /* Check the validity of the function driver index */
    if (( iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER ) )
    {
        /* invalid CDC index */
        return USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID;
    }

    /* Check if the given event handler is valid */
    if ( eventHandler )
    {
        /* update the event handler for this instance */
        gUSBDeviceCDCInstance[iCDC].appEventCallBack = eventHandler;
        gUSBDeviceCDCInstance[iCDC].userData = userData;

        /* return success */
        return USB_DEVICE_CDC_RESULT_OK;
    }

    else
    {
        /* invalid event handler passed */
        return USB_DEVICE_CDC_RESULT_ERROR_PARAMETER_INVALID;
    }

}

uint16_t USB_DEVICE_CDC_ReadPacketSizeGet ( USB_DEVICE_CDC_INDEX iCDC )
{
    /* check the validity of the function driver index */
    if ( ( iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER ) )
    {
        /* Invalid CDC index */
        SYS_ASSERT ( false , "Invalid CDC index" );
        return (0);
    }

    /* max read packet size for this instance */
    return (gUSBDeviceCDCInstance[iCDC].dataInterface
            .endpoint[USB_DEVICE_CDC_ENDPOINT_RX].maxPacketSize );

}

uint16_t USB_DEVICE_CDC_WritePacketSizeGet ( USB_DEVICE_CDC_INDEX iCDC )
{
    /* check the validity of the function driver index */
    if ( ( iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER ) )
    {
        /* Invalid CDC index */
        SYS_ASSERT ( false , "Invalid CDC index" );
        return (0);
    }

    /* max read packet size for this instance */
    return (gUSBDeviceCDCInstance[iCDC].dataInterface.
            endpoint[USB_DEVICE_CDC_ENDPOINT_TX].maxPacketSize );
}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_SerialStateSend 
(
    USB_DEVICE_CDC_INDEX iCDC ,
    USB_DEVICE_CDC_TRANSFER_HANDLE * transferHandle ,
    USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA * notificationData 
)
{

    unsigned int cnt;
    USB_DEVICE_IRP * irp;
    USB_DEVICE_CDC_ENDPOINT * endpoint;
    USB_DEVICE_CDC_INSTANCE * thisCDCDevice;

    *transferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;

    /* Check the validity of the function driver index */
    
    if (  iCDC >= USB_DEVICE_CDC_INSTANCES_NUMBER  )
    {
        /* Invalid CDC index */
        SYS_ASSERT(false, "Invalid CDC Device Index");
        return USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_INVALID;
    }

    thisCDCDevice = &gUSBDeviceCDCInstance[iCDC];
    endpoint = &thisCDCDevice->notificationInterface.endpoint[USB_DEVICE_CDC_ENDPOINT_TX];

    if(!(endpoint->isConfigured))
    {
        /* This means that the endpoint is not configured yet */
        SYS_ASSERT(false, "Endpoint not configured");
        return (USB_DEVICE_CDC_RESULT_ERROR_INSTANCE_NOT_CONFIGURED);
    }

    if(thisCDCDevice->currentQSizeSerialStateNotification >=
            thisCDCDevice->queueSizeSerialStateNotification)
    {
        SYS_ASSERT(false, "Serial State Notification Send Queue is full");
        return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);
    }

    // OSAL: Mutex Get

    /* loop and find a free IRP in the Q */
    for ( cnt = 0; cnt < USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED; cnt ++ )
    {
        if(gUSBDeviceCDCIRP[cnt].status < (USB_DEVICE_IRP_STATUS)USB_DEVICE_IRP_FLAG_DATA_PENDING)
        {
            /* This means the IRP is free */

            irp = &gUSBDeviceCDCIRP[cnt];
            irp->data = notificationData;
            irp->size = sizeof(USB_DEVICE_CDC_SERIAL_STATE_NOTIFICATION_DATA);
            irp->userData = (uintptr_t) iCDC;
            irp->callback = _USB_DEVICE_CDC_SerialStateSendIRPCallback;
            irp->flags = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
            thisCDCDevice->currentQSizeSerialStateNotification ++;
            *transferHandle = (USB_DEVICE_CDC_TRANSFER_HANDLE) irp;
            USB_DEVICE_IRPSubmit(thisCDCDevice->deviceHandle, 
                    endpoint->address, irp);

            //OSAL: Mutex Release

            return(USB_DEVICE_CDC_RESULT_OK);

        }
    }

    // OSAL: Mutex Release

    /* If here means we could not find a spare IRP */
    return(USB_DEVICE_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL);

}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlSend
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    void * data, size_t size
)
{
    return ((USB_DEVICE_CDC_RESULT)
            (USB_DEVICE_ControlSend
            (gUSBDeviceCDCInstance[instanceIndex].deviceHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlReceive
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * data, size_t size   
)
{
    return ((USB_DEVICE_CDC_RESULT)
            (USB_DEVICE_ControlReceive
            (gUSBDeviceCDCInstance[instanceIndex].deviceHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_CDC_RESULT USB_DEVICE_CDC_ControlStatus
(
    USB_DEVICE_CDC_INDEX instanceIndex,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    USB_DEVICE_CDC_CONTROL_STATUS status
)
{
    return((USB_DEVICE_CDC_RESULT)
            (USB_DEVICE_ControlStatus
            (gUSBDeviceCDCInstance[instanceIndex].deviceHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            (USB_DEVICE_CONTROL_STATUS)(status))));
}

/*******************************************************************************
 End of File
 */
