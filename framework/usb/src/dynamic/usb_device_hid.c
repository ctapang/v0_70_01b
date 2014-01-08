/*******************************************************************************
  USB HID Function Driver

  Company:
    Microchip  Technology Inc.

  File Name:
    usb_device_hid.c

  Summary:
    USB HID function driver
  
  Description:
    USB HID function driver
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include "usb/usb_device_hid.h"
#include "usb/usb_device.h"
#include "system/common/sys_common.h"

/* Allocate a global pool of IRPs*/
static USB_DEVICE_IRP gUSBDeviceHIDIRP[USB_DEVICE_HID_QUEUE_DEPTH_COMBINED];

/* This is the function driver initialize function called by te
 device layer when the device is configured. */
static void _USB_DEVICE_HID_InitializeByDescriptorType
(
    SYS_MODULE_INDEX iHID,
    USB_DEVICE_HANDLE usbDeviceHandle,
    void* funcDriverInit, 
    uint8_t intfNumber,
    uint8_t altSetting,
    uint8_t descriptorType, 
    uint8_t * pDescriptor
);

/* This function is called when the device layer deinitializes the
 function driver when the device is reset or the configuration is
 changed. */
static void _USB_DEVICE_HID_DeInitialize(SYS_MODULE_INDEX iHID);

/* This function handles the function driver specific control
 transfers. */
static void _USB_DEVICE_HID_ControlTransferHandler
(
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
    SYS_MODULE_INDEX iHID,
    USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData
);

// *****************************************************************************
/* HID Device function driver function structure

  Summary:
    Defines the function driver structure required by the device layer.

  Description:
    This data type defines the function driver structure required by the
    device layer

  Remarks:
    This structure is private to the USB stack.
*/
USB_DEVICE_FUNCTION_DRIVER hidFuncDriver =
{
    .initializeByDescriptor = &_USB_DEVICE_HID_InitializeByDescriptorType,
    .deInitialize = &_USB_DEVICE_HID_DeInitialize,
    .tasks = NULL,
    .controlTransferNotification = &_USB_DEVICE_HID_ControlTransferHandler
};

// *****************************************************************************
/* HID flags.

  Summary:
   Flags for tracking internal status.

  Description:
    

  Remarks:
    This structure is internal to the HID function driver.
*/

typedef union _USB_DEVICE_HID_FLAGS
{
    struct
    {
        uint8_t interfaceReady:1;
        uint8_t interruptEpTxReady:1;
        uint8_t interruptEpRxReady:1;
    };
    uint8_t allFlags;
}USB_DEVICE_HID_FLAGS;

// *****************************************************************************
/* HID instance structure.

  Summary:
    Identifies the HID instance.

  Description:
    This type identifies the HID instance.

  Remarks:
    This structure is internal to the HID function driver.
*/

typedef struct _USB_DEVICE_HID_INSTANCE {

    USB_DEVICE_HID_FLAGS flags;
    USB_DEVICE_HANDLE devLayerHandle;
    USB_DEVICE_HID_INIT * hidFuncInit;
    USB_DEVICE_HID_EVENT_HANDLER appCallBack;
    uintptr_t userData;
    bool ignoreControlEvents;
    USB_ENDPOINT endpointTx;
    uint16_t endpointTxSize;
    USB_ENDPOINT endpointRx;
    uint16_t endpointRxSize;
    size_t currentTxQueueSize;
    size_t currentRxQueueSize;
}
USB_DEVICE_HID_INSTANCE;

/***************************************
 * Array of USB HID Instances
 ****************************************/
static USB_DEVICE_HID_INSTANCE
    gUsbDeviceHidInstance[USB_DEVICE_HID_INSTANCES_NUMBER];

/******************************************************************************
  Function:
static void _USB_DEVICE_HID_InitializeByDescriptorType
(
    SYS_MODULE_INDEX iHID,
    USB_DEVICE_HANDLE usbDeviceHandle,
    void* funcDriverInit, 
    uint8_t intfNumber,
    uint8_t altSetting,
    uint8_t descriptorType, 
    uint8_t * pDescriptor
);

  Summary:
    This function will initialize the HID function driver by interface.

  Description:

  Parameters:
    iHID            - HID instance index
    usbDeviceHandle - USB device handle
    funcDriverInit  - Function driver init structure
    intfNumber      - Interface number
    descriptorType  - Descriptor type
    pDescriptor     - Pointer to the descriptor.

  Returns:
    None.

*/

static void _USB_DEVICE_HID_InitializeByDescriptorType
(
    SYS_MODULE_INDEX iHID,
    USB_DEVICE_HANDLE usbDeviceHandle,
    void* funcDriverInit,
    uint8_t intfNumber,
    uint8_t altSetting,
    uint8_t descriptorType,
    uint8_t * pDescriptor
)
{
    /* This function is called by the device layer when it
     * initializes the HID function driver. The device layer
     * passes descriptors to this function and the function
     * driver uses these to initialize itself */

    USB_ENDPOINT_DESCRIPTOR * epDescriptor = ( USB_ENDPOINT_DESCRIPTOR *)pDescriptor;
    USB_DEVICE_HID_INSTANCE * hidInstance = &gUsbDeviceHidInstance[iHID];
   
    SYS_ASSERT(altSetting == 0, "USB Device HID: HID supports only one setting \
                                and does not support alternate settings.\
                                 Check configuration descriptors ");

    switch(descriptorType )
    {
        case USB_DESCRIPTOR_ENDPOINT:
            // Device layer has configured and opened an endpoint.
            // We just have to save the endpoint and arm if necessary.

            if( epDescriptor->transferType == USB_TRANSFER_TYPE_INTERRUPT )
            {
                if(epDescriptor->dirn == USB_DATA_DIRECTION_DEVICE_TO_HOST)
                {
                   // Save the Tx endpoint information.
                    hidInstance->endpointTx = epDescriptor->bEndpointAddress;
                    hidInstance->endpointTxSize =  epDescriptor->wMaxPacketSize;

                    // Open the endpoint.
                    USB_DEVICE_EndpointEnable(usbDeviceHandle,
                    hidInstance->endpointTx, USB_TRANSFER_TYPE_INTERRUPT,
                                                  epDescriptor->wMaxPacketSize);
                    
                    // Indicate that TX endpoint is ready.
                    hidInstance->flags.interruptEpTxReady = 1;

                    // Initialize the current TX queue size.
                    hidInstance->currentTxQueueSize = 0;
                }
                else
                {
                    // Direction is OUT
                    hidInstance->endpointRx = epDescriptor->bEndpointAddress;
                    hidInstance->endpointRxSize =  epDescriptor->wMaxPacketSize;

                    // Open the endpoint.
                    USB_DEVICE_EndpointEnable(usbDeviceHandle,
                    hidInstance->endpointRx, USB_TRANSFER_TYPE_INTERRUPT,
                                                  epDescriptor->wMaxPacketSize);

                    // Indicate that the RX endpoint is ready.
                    hidInstance->flags.interruptEpRxReady = 1;

                    // Initialize the current RX queue size.
                    hidInstance->currentRxQueueSize = 0;
                }
            }
            else
            {
                SYS_ASSERT( false, "USB DEVICE HID: HID does not support \
                                    anything other than interrupt endpoints.\
                                    Please check the descriptors.");
            }
            break;
       
        case USB_DESCRIPTOR_INTERFACE:
           
            // Just mark interface as ready.
            hidInstance->flags.interfaceReady = 1;
            hidInstance->devLayerHandle = usbDeviceHandle;
            hidInstance->hidFuncInit = funcDriverInit;

            break;

        default:
            break;
    }
 }

/******************************************************************************
  Function:
    static void _USB_DEVICE_HID_ReportSendCallBack(USB_DEVICE_IRP * handle)

  Summary:
    Callback function that gets called after the report is sent
    to host.

  Description:
    This callback forwards the event to application callback function.

  Parameters:
    handle - IRP handle

  Returns:
    None.

*/

static void _USB_DEVICE_HID_ReportSendCallBack(USB_DEVICE_IRP * irpTx)
{
    /* This function is called when a Report Send IRP has
     * terminated */
    USB_DEVICE_HID_INDEX iHID = irpTx->userData;
    USB_DEVICE_HID_EVENT_DATA_REPORT_SENT reportSent;
    USB_DEVICE_HID_INSTANCE * thisHIDInstance = &gUsbDeviceHidInstance[iHID];

    /* Update the current transmit queue size */
    thisHIDInstance->currentTxQueueSize --;

    /* Check if a event handler callback is registered and
     * send the event*/
    if(thisHIDInstance->appCallBack != NULL)
    {
        reportSent.length = irpTx->size;
        reportSent.handle = ( USB_DEVICE_HID_TRANSFER_HANDLE )irpTx;

        thisHIDInstance->appCallBack
        (
            iHID,
            USB_DEVICE_HID_EVENT_REPORT_SENT, 
            0,  /* Control transfer handle is null for this event */
            &reportSent,
            thisHIDInstance->userData
        );
    }    
}

/******************************************************************************
  Function:
    USB_DEVICE_HID_RESULT USB_DEVICE_HID_ReportSend(SYS_MODULE_INDEX iHID,
                                USB_DEVICE_HID_TRANSFER_HANDLE * transferHandle,
                                uint8_t * buffer, size_t size)

  Summary:
    This function submits the application given buffer to HID function driver
    to send the report from device to host.

  Description:
    

  Parameters:
    iHID            - HID index
    transferHandle  - Transfer handle
    buffer          - Pointer to buffer that contains report.
    size            - report size.

  Returns:
    None.

*/

USB_DEVICE_HID_RESULT USB_DEVICE_HID_ReportSend
(
    USB_DEVICE_HID_INDEX iHID,
    USB_DEVICE_HID_TRANSFER_HANDLE * transferHandle,
    void * buffer, size_t size)
{
    size_t count;
    USB_DEVICE_IRP * irp = NULL;
    USB_DEVICE_HID_INSTANCE * thisHIDInstance;

    /* Set the transfer handle to invalid */
    *transferHandle = USB_DEVICE_HID_TRANSFER_HANDLE_INVALID;

    /* Check if we have a valid instance index */
    if( (iHID < 0) || ( iHID > USB_DEVICE_HID_INSTANCES_NUMBER) )
    {
        SYS_ASSERT(false, "HID instance is not valid");
        return USB_DEVICE_HID_RESULT_ERROR_INSTANCE_INVALID ;
    }

    /* Create a local reference */
    thisHIDInstance = &gUsbDeviceHidInstance[iHID];

    /* Check if the endpoint was configured */
    if(!thisHIDInstance->flags.interruptEpTxReady )
    {
        SYS_ASSERT(false, "HID Transmit endpoint not configured");
        return USB_DEVICE_HID_RESULT_ERROR_INSTANCE_NOT_CONFIGURED;
    }

    /* Check if the Transmit queue is full */
    if(thisHIDInstance->currentTxQueueSize >= 
            thisHIDInstance->hidFuncInit->queueSizeReportSend)
    {
        SYS_ASSERT(false,"Transmit Queue is full");
        return USB_DEVICE_HID_RESULT_ERROR_TRANSFER_QUEUE_FULL;
    }
    
    // Check which IRP is free
    for(count = 0; count < USB_DEVICE_HID_QUEUE_DEPTH_COMBINED; count++)
    {
         if(gUSBDeviceHIDIRP[count].status
                 <= USB_DEVICE_IRP_STATUS_COMPLETED_SHORT)
         {
             /* This means we have free IRP. Populate
              * the IRP */
        
             irp =&gUSBDeviceHIDIRP[count];
             irp->size = size;
             irp->data = buffer;
             irp->callback = &_USB_DEVICE_HID_ReportSendCallBack;
             irp->userData = iHID;
             irp->flags = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
             (*transferHandle) = ( USB_DEVICE_HID_TRANSFER_HANDLE )irp;
             thisHIDInstance->currentTxQueueSize ++;

             /* Submit the IRP and return */
             return(USB_DEVICE_IRPSubmit( thisHIDInstance->devLayerHandle,
                                  thisHIDInstance->endpointTx,
                                  irp));
         }
    }

    /* We could not find a free IRP */
    SYS_ASSERT(false,"Transmit Queue is full");
    return USB_DEVICE_HID_RESULT_ERROR_TRANSFER_QUEUE_FULL;

}


/******************************************************************************
  Function:
    static void _USB_DEVICE_HID_ReportReceiveCallBack(void * handle)

  Summary:
    Callback function that gets called after the report is received
    from host.

  Description:
    This callback forwards the event to application callback function.

  Parameters:
    handle - IRP handle

  Returns:
    None.

*/

void _USB_DEVICE_HID_ReportReceiveCallBack(USB_DEVICE_IRP * irpRx)
{
    SYS_MODULE_INDEX iHID = irpRx->userData;
    USB_DEVICE_HID_INSTANCE * thisHIDInstance = &gUsbDeviceHidInstance[iHID];
    USB_DEVICE_HID_EVENT_DATA_REPORT_RECEIVED reportReceived;

    /* Update the receive queue size */
    thisHIDInstance->currentRxQueueSize --;

    /* Check if an application event handler callback is
     * avaialable and then send the event to the application. */
    if(thisHIDInstance->appCallBack)
    {
        reportReceived.length = irpRx->size;
        reportReceived.handle =
                (USB_DEVICE_CONTROL_TRANSFER_HANDLE)irpRx;

        thisHIDInstance->appCallBack
        (
            iHID,
            USB_DEVICE_HID_EVENT_REPORT_RECEIVED,
            0, /* Control Transfer Handle is NULL for this event */
            &reportReceived,
            thisHIDInstance->userData 
        );
    }
}


/******************************************************************************
  Function:
    USB_DEVICE_HID_RESULT USB_DEVICE_HID_ReportReceive(SYS_MODULE_INDEX iHID,
                                                 uint8_t * buffer, size_t size)

  Summary:
    This function submits the buffer to HID function driver to
    receive a report from host.

  Description:
    

  Parameters:
    iHID            - HID instance
    buffer          - Pointer to buffer
    size            - Buffer size

  Returns:
    None.

*/

USB_DEVICE_HID_RESULT USB_DEVICE_HID_ReportReceive
(
    USB_DEVICE_HID_INDEX iHID,
    USB_DEVICE_HID_TRANSFER_HANDLE * transferHandle,
    void * buffer, size_t size)
{

    size_t count = 0;
    USB_DEVICE_IRP * irp;
    USB_DEVICE_HID_INSTANCE * thisHIDInstance;

    /* Set the transfer handle to invalid */
    *transferHandle = USB_DEVICE_HID_TRANSFER_HANDLE_INVALID;

    /* Check if we have a valid instance index */
    if( (iHID < 0) || ( iHID > USB_DEVICE_HID_INSTANCES_NUMBER) )
    {
        SYS_ASSERT(false, "HID instance is not valid");
        return USB_DEVICE_HID_RESULT_ERROR_INSTANCE_INVALID ;
    }

    /* Create a local reference */
    thisHIDInstance = &gUsbDeviceHidInstance[iHID];

    /* Check if the endpoint was configured */
    if(!thisHIDInstance->flags.interruptEpRxReady )
    {
        SYS_ASSERT(false, "HID Receive endpoint not configured");
        return USB_DEVICE_HID_RESULT_ERROR_INSTANCE_NOT_CONFIGURED;
    }

    /* Check if the Receive queue is full */
    if(thisHIDInstance->currentRxQueueSize >=
            thisHIDInstance->hidFuncInit->queueSizeReportReceive)
    {
        SYS_ASSERT(false,"Receive Queue is full");
        return USB_DEVICE_HID_RESULT_ERROR_TRANSFER_QUEUE_FULL;
    }

    /* Search for a free IRP*/
    for(count = 0; count < USB_DEVICE_HID_QUEUE_DEPTH_COMBINED; count++)
    {
         if( gUSBDeviceHIDIRP[count].status <=
                 USB_DEVICE_IRP_STATUS_COMPLETED_SHORT)
         {
             /* We have found a free IRP. Populate the IRP
              * and then submit it*/
             irp = &gUSBDeviceHIDIRP[count];
             irp->size = size;
             irp->callback = &_USB_DEVICE_HID_ReportReceiveCallBack;
             irp->data = buffer;
             irp->flags = USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
             irp->userData = iHID;
             thisHIDInstance->currentRxQueueSize ++;
             (* transferHandle) = ( USB_DEVICE_CONTROL_TRANSFER_HANDLE )irp;
             return (USB_DEVICE_IRPSubmit( thisHIDInstance->devLayerHandle,
                                           thisHIDInstance->endpointRx,
                                           irp));
         }
    }

    /* We could not find a free IRP */
    SYS_ASSERT(false,"Receive Queue is full");
    return USB_DEVICE_HID_RESULT_ERROR_TRANSFER_QUEUE_FULL;

}


/******************************************************************************
  Function:
    static void _USB_DEVICE_HID_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iHID,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        void * pEventData )

  Summary:
    Handles all HID related control transfers.

  Description:


  Parameters:
    controlHandle   - Control Handle
    iHID            - HID index
    controlEvent    - Control event
    pEventData      - Event related data

  Returns:
    None.

*/

static void _USB_DEVICE_HID_ControlTransferHandler
(
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
    SYS_MODULE_INDEX iHID,
    USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData
)
{
    USB_DEVICE_HID_INSTANCE *hidThisInstance;
    USB_SETUP_PACKET * setupPkt;
    USB_DEVICE_HID_EVENT_DATA_SET_IDLE setIdle;
    USB_DEVICE_HID_EVENT_DATA_GET_IDLE getIdle;
    USB_DEVICE_HID_EVENT_DATA_SET_DESCRIPTOR setDescriptor;
    USB_DEVICE_HID_EVENT_DATA_GET_REPORT getReport;
    USB_DEVICE_HID_EVENT_DATA_SET_REPORT setReport;
    USB_DEVICE_HID_EVENT_DATA_SET_PROTOCOL setProtocol;
    
    hidThisInstance = &gUsbDeviceHidInstance[iHID] ;

    if(controlEvent == USB_DEVICE_CONTROL_SETUP_REQUEST)
    {
        setupPkt = pEventData->setupRequest;
        hidThisInstance->ignoreControlEvents = false;
        if( setupPkt->bmRequestType & USB_SETUP_RECIPIENT_INTERFACE)
        {
            switch(setupPkt->bRequest)
            {
                case USB_REQUEST_GET_DESCRIPTOR:          
                    
                    /* The HID Get Descriptor request is handled by the
                     * function driver itself. This event is not sent to the
                     * application. The function driver responds with a
                     * control send. */

                    USB_DEVICE_ControlSend(hidThisInstance->devLayerHandle,
                            controlHandle,
                            hidThisInstance->hidFuncInit->hidReportDescriptor,
                            hidThisInstance->hidFuncInit->hidReportDescriptorSize);

                    // Ignore further control transfer events.
                    hidThisInstance->ignoreControlEvents = true;
                    break;

                case USB_HID_REQUESTS_SET_IDLE:

                    /* Set Idle event is sent to the application */
                    setIdle.duration = setupPkt->W_Value.byte.HB;
                    setIdle.reportID = setupPkt->W_Value.byte.LB;

                    hidThisInstance->appCallBack(iHID, 
                            USB_DEVICE_HID_EVENT_SET_IDLE, 
                            controlHandle,
                            &setIdle,
                            hidThisInstance->userData );
                    break;

                case USB_REQUEST_SET_DESCRIPTOR:

                    /* Set Descriptor event is sent to the application */

                    setDescriptor.descriptorIndex = setupPkt->W_Value.byte.LB;
                    setDescriptor.descriptorLength = setupPkt->W_Length.Val;
                    setDescriptor.descriptorType = setupPkt->W_Value.byte.HB;

                    hidThisInstance->appCallBack(iHID, 
                            USB_DEVICE_HID_EVENT_SET_DESCRIPTOR, 
                            controlHandle,
                            &setDescriptor,
                            hidThisInstance->userData);
                    break;

                default:
                    USB_DEVICE_ControlStatus( hidThisInstance->devLayerHandle,
                            controlHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
            }                   
        }
        else if( ( setupPkt->bmRequestType & USB_SETUP_TYPE_CLASS ) &&
                ( hidThisInstance->appCallBack != NULL ) )
        {
            switch( setupPkt->bRequest )
            {
                case  USB_HID_REQUESTS_GET_REPORT:

                    /* Get Report event is sent to the application */
                    getReport.reportType = setupPkt->W_Value.byte.HB;
                    getReport.reportID = setupPkt->W_Value.byte.LB;
                    getReport.reportLength = setupPkt->wLength;

                    hidThisInstance->appCallBack(iHID,
                            USB_DEVICE_HID_EVENT_GET_REPORT,
                            controlHandle,
                            &getReport,
                            hidThisInstance-> userData);
                    break;

                case USB_HID_REQUESTS_GET_IDLE:

                    /* Get Idle event is sent to the host */
                    getIdle.reportID = setupPkt->W_Value.byte.LB;

                    hidThisInstance->appCallBack(iHID,
                            USB_DEVICE_HID_EVENT_GET_IDLE,
                            controlHandle,
                            &getIdle,
                            hidThisInstance->userData);
                    break;

                case USB_HID_REQUESTS_GET_PROTOCOL:

                    /* Get Protocol event is sent to the application. There
                     * is no event data in this case. */

                    hidThisInstance->appCallBack(iHID, 
                            USB_DEVICE_HID_EVENT_GET_PROTOCOL, 
                            controlHandle, NULL,
                            hidThisInstance->userData);
                    break;

                case USB_HID_REQUESTS_SET_REPORT:

                    /* Set Report event is sent to the application */
                    setReport.reportType = setupPkt->W_Value.byte.HB;
                    setReport.reportID = setupPkt->W_Value.byte.LB;
                    setReport.reportLength = setupPkt->wLength;

                    hidThisInstance->appCallBack(iHID, 
                            USB_DEVICE_HID_EVENT_SET_REPORT, 
                            controlHandle, &setReport,
                            hidThisInstance->userData );
                    break;

                case USB_HID_REQUESTS_SET_PROTOCOL:

                    /* Set Protocol event is sent to the application */
                    setProtocol.protocol = setupPkt->wValue;

                    hidThisInstance->appCallBack(iHID, 
                            USB_DEVICE_HID_EVENT_SET_PROTOCOL, 
                            controlHandle, &setProtocol,
                            hidThisInstance->userData );
                    break;

                default:
                    
                    /* Stall anything that we cannot handle */
                    USB_DEVICE_ControlStatus( hidThisInstance->devLayerHandle,
                            controlHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
                    break;
            }
        }
        else
        {
            /* Stall anything that we cannot handle */
            USB_DEVICE_ControlStatus( hidThisInstance->devLayerHandle,
                    controlHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
        }
    }
    else if ((hidThisInstance->ignoreControlEvents == false) &&
            ( hidThisInstance->appCallBack != NULL))
    {
        /* These are control transfer related events */
        hidThisInstance->appCallBack(iHID, 
                controlEvent, controlHandle, NULL, hidThisInstance->userData);
    }
    
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_HID_DeInitialize(SYS_MODULE_INDEX iHID)

  Summary:
     Deinitializes an instance of the HID.

  Description:


  Parameters:
    iHID            - HID index    

  Returns:
    None.

*/

static void _USB_DEVICE_HID_DeInitialize(SYS_MODULE_INDEX iHID)
{
    USB_DEVICE_HID_INSTANCE * hidInstance = &gUsbDeviceHidInstance[iHID];

    USB_DEVICE_IRPCancelAll( hidInstance->devLayerHandle,
                                hidInstance->endpointTx );
    USB_DEVICE_IRPCancelAll( hidInstance->devLayerHandle,
                                hidInstance->endpointRx );
    

    USB_DEVICE_EndpointDisable(  hidInstance->devLayerHandle,
                                hidInstance->endpointTx);
    USB_DEVICE_EndpointDisable(  hidInstance->devLayerHandle,
                                hidInstance->endpointRx);
    
    hidInstance->flags.allFlags = 0;   

}


/******************************************************************************
  Function:
    USB_DEVICE_HID_RESULT USB_DEVICE_HID_EventHandlerSet (  USB_DEVICE_HID_INDEX iHID ,
                                        USB_DEVICE_HID_EVENT_HANDLER eventHandler )

  Summary:
    Allows application to register a callback handle.

  Description:


  Parameters:
    iHID            - HID index
    eventHandler    - Application callback event handler.
  Returns:
    None.

*/

USB_DEVICE_HID_RESULT USB_DEVICE_HID_EventHandlerSet
(
    USB_DEVICE_HID_INDEX iHID ,
    USB_DEVICE_HID_EVENT_HANDLER eventHandler,
    uintptr_t userData
)
{
    USB_DEVICE_HID_INSTANCE * thisHIDInstance;

    /* Check if we have a valid instance */
    if( (iHID < 0) || ( iHID > USB_DEVICE_HID_INSTANCES_NUMBER) )
    {
        SYS_ASSERT(false, "Invalid HID Instance");
        return USB_DEVICE_HID_RESULT_ERROR_INSTANCE_INVALID ;
    }

    /* Check if we have valid event handler*/
    if(eventHandler == NULL)
    {
        SYS_ASSERT(false, "Event Handler is NULL");
        return USB_DEVICE_HID_RESULT_ERROR_PARAMETER_INVALID;
    }

    thisHIDInstance = &gUsbDeviceHidInstance[iHID];

    thisHIDInstance->appCallBack = eventHandler;
    thisHIDInstance->userData = userData;
    
    return USB_DEVICE_HID_RESULT_OK;    
}

USB_DEVICE_HID_RESULT USB_DEVICE_HID_ControlSend
(
    USB_DEVICE_HID_INDEX instanceIndex,
    USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE  controlTransferHandle,
    void * data, size_t size
)
{
    return ((USB_DEVICE_HID_RESULT)
            (USB_DEVICE_ControlSend
            (gUsbDeviceHidInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_HID_RESULT USB_DEVICE_HID_ControlReceive
(
    USB_DEVICE_HID_INDEX instanceIndex,
    USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * data, size_t size
)
{
    return ((USB_DEVICE_HID_RESULT)
            (USB_DEVICE_ControlReceive
            (gUsbDeviceHidInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            data, size)));
}

USB_DEVICE_HID_RESULT USB_DEVICE_HID_ControlStatus
(
    USB_DEVICE_HID_INDEX instanceIndex,
    USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    USB_DEVICE_HID_CONTROL_STATUS status
)
{
    return((USB_DEVICE_HID_RESULT)
            (USB_DEVICE_ControlStatus
            (gUsbDeviceHidInstance[instanceIndex].devLayerHandle,
            (USB_DEVICE_CONTROL_TRANSFER_HANDLE)(controlTransferHandle),
            (USB_DEVICE_CONTROL_STATUS)(status))));
}


/******************************************************************************/













