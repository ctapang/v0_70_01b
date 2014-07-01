/**************************************************************************
 USB Device Layer Implementation

  Company:
    Microchip Technology Inc.
    
  File Name:
    usb_device.c
    
  Summary:
    This file contains implementations of both private and public functions
    of the USB Device Layer.
    
  Description:
    This file contains the USB device layer implementation.
  **************************************************************************/

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



#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "system/common/sys_module.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "system_config.h"
#include "usb/usb_device.h"

#include "usb/src/usb_device_local.h"

/*******************************************************************************
  Validate the following macros
*/
#if ( USB_DEVICE_MAX_INSTANCES == 0 )
    #error( " USB_DEVICE_MAX_INSTANCES must be > 0 ");
#endif

#if ( USB_DEVICE_MAX_CLIENTS == 0 )
    #error( " USB_DEVICE_MAX_CLIENTS must be > 0 ");
#endif 



typedef struct __attribute__ ((packed))
{
    uint8_t bLength;
    uint8_t bDescriptorType;
}USB_DEVICE_SERVICE_DESCRIPTOR_HEAD;




// *****************************************************************************
/* Device layer instance objects.

  Summary:
    Holds all of the variables required by the instance.

  Description:
    This structure holds all of the variables required by the instance.

  Remarks:
    None.
*/

static USB_DEVICE_INSTANCE_STRUCT usbDeviceInstance[USB_DEVICE_MAX_INSTANCES];

// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects that are available on the device.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the Client state of the instance.

  Remarks:
    None.
*/

static USB_DEVICE_CLIENT_STRUCT usbDeviceClients[USB_DEVICE_MAX_INSTANCES][USB_DEVICE_MAX_CLIENTS + 1];

// IRP Allocation

static bool firstAllocation = true;

void InitIRP(USB_DEVICE_IRP_LOCAL * irp)
{
    irp->next = NULL;
    irp->previous = NULL;
    irp->nPendingBytes = 0;
    irp->status = USB_DEVICE_IRP_STATUS_ALLOCATED;
}

void UnlinkIRP(USB_DEVICE_IRP_LOCAL * irp)
{
    if (irp->next != NULL)
        irp->next->previous = irp->previous;
    if (irp->previous != NULL)
        irp->previous->next = irp->next;
}

USB_DEVICE_IRP_LOCAL * SearchForFirstAvailable(USB_DEVICE_IRP_LOCAL * irpBase)
{
    int maxIRP = 2 * DRV_USB_MAX_QUEUE_LENGTH * DRV_USB_ENDPOINTS_NUMBER;
    USB_DEVICE_IRP_LOCAL * irp = irpBase;
    USB_DEVICE_IRP_LOCAL * retIRP = NULL;
    DRV_USB_DEVICE_ENDPOINT_OBJ * endpointObj;

    int i, j;
    for (j = 0; j < maxIRP; j++, irp++)
    {
        if (irp->status == USB_DEVICE_IRP_STATUS_FREE)
        {
            UnlinkIRP(irp);
            InitIRP(irp);
            retIRP = irp;
            break;
        }
    }
    SYS_ASSERT((retIRP != NULL), "ran out of IRPs");
    return retIRP;
}


static void _USB_DEVICE_Ep0ReceiveCompleteCallback( USB_DEVICE_IRP * handle );
static void _USB_DEVICE_Ep0TransmitCompleteCallback(USB_DEVICE_IRP * handle);

void InitializeAllIRPs( USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance )
{
    int i;
    int maxIRP = 2 * DRV_USB_MAX_QUEUE_LENGTH * DRV_USB_ENDPOINTS_NUMBER;
 
    USB_DEVICE_IRP_LOCAL * irp = (USB_DEVICE_IRP_LOCAL * )usbDeviceThisInstance->irpEp0Tx;
    for (i = 0; i < maxIRP; i++, irp++)
    {
        irp->callback = &_USB_DEVICE_Ep0TransmitCompleteCallback;
        irp->userData = (uintptr_t)usbDeviceThisInstance;
        irp->flags = USB_DEVICE_IRP_FLAG_DEVICE_TO_HOST;
        irp->status = USB_DEVICE_IRP_STATUS_FREE;
    }

    irp = (USB_DEVICE_IRP_LOCAL * )usbDeviceThisInstance->irpEp0Rx;
    for (i = 0; i < maxIRP; i++, irp++)
    {
        irp->data = usbDeviceThisInstance->ep0RxBuffer;
        irp->size = USB_DEVICE_EP0_BUFFER_SIZE;
        irp->flags = USB_DEVICE_IRP_FLAG_HOST_TO_DEVICE;
        irp->status = USB_DEVICE_IRP_STATUS_FREE;
        irp->callback = &_USB_DEVICE_Ep0ReceiveCompleteCallback;
        irp->userData = (uintptr_t)usbDeviceThisInstance;
    }
}

USB_DEVICE_IRP_LOCAL * allocationHistory[100];
int hix = 0;

USB_DEVICE_IRP * USB_DEVICE_AllocateIRP
(
    USB_DEVICE_HANDLE deviceHandle,
    const char direction
)
{
    USB_DEVICE_INSTANCE_STRUCT * device = (USB_DEVICE_INSTANCE_STRUCT *)deviceHandle;

    bool interruptWasEnabled = MutexOpen();
    
    if (firstAllocation)
    {
        firstAllocation = false;
        InitializeAllIRPs(device);
        int i;
        for (i = 0; i < 100; i++)
            allocationHistory[i] = NULL;
    }

    // scan IRPs looking for first available one

    int j;
    USB_DEVICE_IRP_LOCAL * irp = NULL;
    if (direction == 'T')
    {
        irp = SearchForFirstAvailable((USB_DEVICE_IRP_LOCAL * )device->irpEp0Tx);
        //SYS_ASSERT((irp != NULL), "Cannot allocate Tx IRP");
        if (irp == NULL)
            goto RETNULL;
        irp->callback = &_USB_DEVICE_Ep0TransmitCompleteCallback;
        irp->flags = USB_DEVICE_IRP_FLAG_DEVICE_TO_HOST;
    }
    else if (direction == 'R')
    {
        irp = SearchForFirstAvailable((USB_DEVICE_IRP_LOCAL * )device->irpEp0Rx);
        SYS_ASSERT((irp != NULL), "Cannot allocate Rx IRP");
        irp->data = device->ep0RxBuffer;
        irp->size = USB_DEVICE_EP0_BUFFER_SIZE;
        irp->callback = &_USB_DEVICE_Ep0ReceiveCompleteCallback;
        irp->flags = USB_DEVICE_IRP_FLAG_HOST_TO_DEVICE;
    }
    else SYS_ASSERT(false, "invalid second parameter");

    irp->userData = deviceHandle;
    //irp->flags |= USB_DEVICE_IRP_FLAG_DATA_COMPLETE;
    irp->status = USB_DEVICE_IRP_STATUS_ALLOCATED;

    RETNULL:
    if(hix < 100)
        allocationHistory[hix++] = irp;
    else
        hix = 0;
    MutexClose(interruptWasEnabled);

    return (USB_DEVICE_IRP *)irp;
}

// *****************************************************************************
/* Function:
    static USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_ControlTransferHandler(
                                                SYS_MODULE_INDEX iUSBDev,
                                                USB_DEVICE_CONTROL_TRANSFER_STATE transferState,
                                                SETUP_PKT* setupPkt,
                                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlXferDataObj
                                                )

  Summary:
    USB device layer's own control trasfer handler.
    
  Description:
    This function processes the setup packet.

  Precondition:
    None.

  Parameters:
    iUSBDev             -   Device layer index.
    setupPkt            -   Pointer to the setup packet.
    transfer state      -   Control transfer state.
    controlXferDataObj  -   Control transfer data object.
 
  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

static void  _USB_DEVICE_ControlTransferHandler(    USB_DEVICE_CONTROL_TRANSFER_HANDLE xferhandle,
                                                    SYS_MODULE_INDEX handlerIndex,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT transferEvent,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * eventData );


// *****************************************************************************
/* Function:
    static USB_DEVICE_CONTROL_TRANSFER_RESULT
             _USB_DEVICE_ProcessStandardSetRequests(USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                            SETUP_PKT *setupPkt,
                                            USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes the standard "set" requests.
    
  Description:
    This function processes the standard "set" requests.

  Precondition:
    None.

  Parameters:

    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

static void _USB_DEVICE_ProcessStandardSetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                            USB_SETUP_PACKET * setupPkt);


// *****************************************************************************
/* Function:
   static USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_ProcessStandardGetRequests(
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                SETUP_PKT* setupPkt,
                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes the standard "get" requests.
    
  Description:
    This function processes the standard "get" requests.

  Precondition:
    None.

  Parameters:
    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

static void _USB_DEVICE_ProcessStandardGetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                                    USB_SETUP_PACKET * setupPkt );


// *****************************************************************************
/* Function:
    static void _USB_DEVICE_ProcessOtherRequests(
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                SETUP_PKT *setupPkt,
                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes "other" requests.
    
  Description:
    This function processes "other" requests.

  Precondition:
    None.

  Parameters:
    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

static void _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            USB_SETUP_PACKET * setupPkt );


// *****************************************************************************
/* Function:
    static void _USB_DEVICE_EventHandler(void* referenceHandle,
            DRV_USB_CLIENT_STATUS eventType, DRV_USB_EVENT_DATA * eventData )   

  Summary:
    Handles the events originating from the USB Controller driver.

  Description:
    This function is registered into the USB Controller driver as a callback
    function. The USB Controller driver calls this function in case of events
    from the USB Controller driver.
    
  Precondition:
    None.

  Parameters:
    referenceHandle           - USB device instance
    eventType                 - Event type
    eventData                 - Data associated with the event
  

  Returns:
    None. 

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

void _USB_DEVICE_EventHandler(uintptr_t referenceHandle,
            DRV_USB_EVENT eventType, void * eventData );


/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastEventToClients
       ( USB_DEVICE_EVENT event, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )

  Summary:
    Broadcasts events to the application client.

  Description:
    This function broadcasts device layer events to all application level clients.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance

  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    None.
*/

static void _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData,
                               USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance );


/******************************************************************************
  Function:
    static void _USB_DEVICE_PerformFunctionDriverRoutines(USB_DEVICE_EVENT event,
                                    USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )


  Summary:
    Calls all function driver routines here.

  Description:
    Deinitialization routines and task routines of the function driver
    are called here.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance

  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    None.
*/

static void _USB_DEVICE_BroadcastControlXferEventsToAppClients( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                         SYS_MODULE_INDEX handlerIndex,
                                                         USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                         void * eventData);


/******************************************************************************
    Tx Endpoint constants
*/

static const USB_ENDPOINT controlEndpointTx = 0x80;


/******************************************************************************
    Endpoint constants
*/

static const USB_ENDPOINT controlEndpointRx  = 0x00;


/******************************************************************************
  Function:
    static void USB_DEVICE_Tasks( SYS_MODULE_OBJ devLayerObj )

  Summary:
    Calls all USB device layer tasks.

  Description:
    This function internally calls all USB Device layer tasks.

  Remarks:
    None.
*/

void USB_DEVICE_Tasks( SYS_MODULE_OBJ devLayerObj )
{
    USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance;
    uint8_t count;

    // Assert object is valid.
    SYS_ASSERT((devLayerObj != SYS_MODULE_OBJ_INVALID), "Invalid Module Obj");    
      
    // Get this instance of USB device layer.
    usbDeviceThisInstance = &usbDeviceInstance[devLayerObj];
       
    uint16_t maxFunctionCounts = usbDeviceThisInstance->registeredFuncDriverCount;
    USB_DEVICE_FUNC_REGISTRATION_TABLE * funcRegTable = usbDeviceThisInstance->registeredFuncDrivers;
    uint8_t speed = usbDeviceThisInstance->usbSpeed ;
    uint16_t configValue = usbDeviceThisInstance->activeConfiguration ;

    // Proceed only if this instance is in initialized state.
    if( usbDeviceThisInstance->usbDeviceInstanceState <= SYS_STATUS_UNINITIALIZED )
    {
        // Instance is not yet initialized. Just do a return.
        return;                
    }
    
    for(count = 0; count < maxFunctionCounts; count++ )
    {
        if( (funcRegTable->speed & speed) && (funcRegTable->configurationValue == configValue))
        {
            if(usbDeviceInstance->usbDeviceState == USB_DEVICE_STATE_CONFIGURED)
            {
                if( funcRegTable->driver->tasks != NULL)
                {
                    funcRegTable->driver->tasks( funcRegTable->funcDriverIndex );
                }                
            }
        }
        funcRegTable++;
    }
   
}


// *****************************************************************************
/* Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT
                      USB_DEVICE_ControlSend( USB_DEVICE_HANDLE usbDeviceHandle,
                            USB_DEVICE_CONTROL_TRANSFER_HANDLE controlXferHandle,
                            uint8_t *  data, size_t length )

  Summary:
    Sends data stage of the control transfer from device to host.

  Description:

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    -   USB device handle returned by USB_DEVICE_Open().
    controlXferHandle  -   Control transfer handle that is returned by the
                           in bus event callback function.
    data               -   Pointer to buffer that holds data.
    length             -   Size in bytes.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED -
          If control transfer is failed due to host aborting the previous
    control transfer.

    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS -
          Control endpoint is successfully armed with data buffer.


  Example:
    <code>

    </code>

  Remarks:

*/

//debug
int ct = 0, dt = 0;

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlSend( USB_DEVICE_HANDLE usbDeviceHandle,
                            void *  data, size_t length )
{
     USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance = (USB_DEVICE_INSTANCE_STRUCT *)usbDeviceHandle;

     ct++;
     
     USB_DEVICE_IRP * irpHandle = USB_DEVICE_AllocateIRP(usbDeviceHandle, 'T');
     irpHandle->data = data;
     irpHandle->size = (unsigned int )length;

     if (USB_ERROR_NONE == DRV_USB_DEVICE_IRPSubmit( usbDeviceThisInstance->usbCDHandle ,
                                     controlEndpointTx ,
                                     irpHandle))
         return USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS;
     else
         return USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED;
}


// *****************************************************************************
/* Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT
                      USB_DEVICE_ControlReceive( USB_DEVICE_HANDLE usbDeviceHandle,
                            USB_DEVICE_CONTROL_TRANSFER_HANDLE controlXferHandle,
                            void *  data, size_t length)

  Summary:
    Receives data stage of the control transfer from host to device.

  Description:

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    -   USB device handle returned by USB_DEVICE_Open().
    controlXferHandle  -   Control transfer handle that is returned by
                           bus event callback function.
    data               -   Pointer to buffer that holds data.
    length             -   Size in bytes.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED -
          If control transfer is failed due to host aborting the previous
    control transfer.

    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS -
          Control endpoint is successfully armed with data buffer.


*/

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlReceive( USB_DEVICE_HANDLE handle,
                                USB_DEVICE_CONTROL_TRANSFER_HANDLE controlXferHandle,
                                void *  data, size_t length )
{
     USB_DEVICE_CONTROL_TRANSFER_STRUCT * pControlTransfer;

     pControlTransfer = &( ((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->controlTransfer );
     pControlTransfer->rxBuffer = data ;
     pControlTransfer->rxDataCount = 0;
     pControlTransfer->expectedRxDataCount = length ;

     return USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS;
}


// *****************************************************************************
/* Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlStatus
                       ( USB_DEVICE_HANDLE hClient,
                         USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                         USB_DEVICE_CONTROL_STATUS status )

  Summary:
    Initiates status stage of the control transfer.

  Description:

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle        -   USB device handle returned by USB_DEVICE_Open().
    controlTransferHandle  -   Control transfer handle that is returned by
                               bus event callback function.
    status             -   USB_DEVICE_CONTROL_STATUS_SEND_ZLP/
                           USB_DEVICE_CONTROL_STATUS_STALL

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED -
          If control transfer is failed due to host aborting the previous
    control transfer.

    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS -
          Control endpoint is successfully armed with data buffer.


  Example:
    <code>

    </code>

  Remarks:

*/

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlStatus( USB_DEVICE_HANDLE usbDeviceHandle,
                               USB_DEVICE_CONTROL_STATUS status)
{
    USB_DEVICE_IRP * irpHandle;
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance = ( USB_DEVICE_INSTANCE_STRUCT *)usbDeviceHandle;
    
    usbDeviceThisInstance->controlTransfer.inProgress = false;
   
    if(USB_DEVICE_CONTROL_STATUS_ERROR == status)
    {
        // Stall both EP0 Rx and Tx
        
        DRV_USB_DEVICE_EndpointStall(usbDeviceThisInstance->usbCDHandle , controlEndpointTx);        
       // DRV_USB_DEVICE_EndpointStall(usbDeviceThisInstance->usbCDHandle , controlEndpointRx);
    }
    else
    {
        // Submit the IRP to send ZLP.

        dt++;
        
        irpHandle = USB_DEVICE_AllocateIRP(usbDeviceHandle, 'T');
        irpHandle->data = NULL;
        irpHandle->size = 0;
        //irpHandle->flags = 0x80;

        if (USB_ERROR_NONE == DRV_USB_DEVICE_IRPSubmit( usbDeviceThisInstance->usbCDHandle ,
                                        controlEndpointTx ,
                                        irpHandle))
            return USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS;
        else
            return USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED;
    }

    return USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS;
}

/******************************************************************************
  Function:
    static void _USB_DEVICE_Ep0ReceiveCompleteCallback( USB_DEVICE_IRP * handle )

  Summary:
    Control receive complete callback.

  Description:
    This callback is called when either data/setup packet is received
   on the control endpoint.

  Parameters:
    handle - IRP handle.

  Returns:
    None.

*/

static void _USB_DEVICE_Ep0ReceiveCompleteCallback( USB_DEVICE_IRP * irpHandle )
{
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance;  
    USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent = USB_DEVICE_CONTROL_TRANSFER_NO_EVENT;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer;

    SYS_ASSERT((irpHandle != NULL), "Invalid Control Rx IRP");

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_ABORTED)
    {
        return;
    }
    
    usbDeviceThisInstance = (USB_DEVICE_INSTANCE_STRUCT *)irpHandle->userData;

    controlTransfer = &usbDeviceThisInstance->controlTransfer;


    // Something is received on EP0.
    if(irpHandle->status == USB_DEVICE_IRP_STATUS_SETUP)
    {
        
        if( controlTransfer->inProgress )
        {
            // Abort any previous transfer
            controlTransfer->handler( 
                                        controlTransfer->handle,
                                        controlTransfer->handlerIndex,
                                       USB_DEVICE_CONTROL_TRANSFER_ABORTED ,
                                       NULL );
        }
        // Mark the control transfer as "in progress".
        controlTransfer->inProgress = true;

        // Now change the transfer handler back to USB device layer handler.
        controlTransfer->handler = &_USB_DEVICE_ControlTransferHandler;
        
        controlTransfer->handlerIndex = usbDeviceThisInstance->usbDevLayerIndex;

        controlEvent = USB_DEVICE_CONTROL_SETUP_REQUEST; 
        
       
    }
    else if( irpHandle->size == 0)
    {
        // ZLP received. This marks the completion of control transfer.
        // Inform the handler.
        controlTransfer->inProgress = false;

        controlEvent = USB_DEVICE_CONTROL_DATA_SENT;
       
    }
    else if( irpHandle->size &&  controlTransfer->inProgress )
    {
        // We are in the data stage of the control transfer.
        // See if the control transfer handler was expecting the data.      

        if(controlTransfer->rxDataCount <  controlTransfer->expectedRxDataCount)
        {
            // Copy the rx buffer to control transfer handler given driver buffer and advance the buffer.
            memcpy(&usbDeviceThisInstance->controlTransfer.rxBuffer[controlTransfer->rxDataCount],
                usbDeviceThisInstance->ep0RxBuffer, irpHandle->size );

            controlTransfer->rxDataCount += irpHandle->size;
        }
        if(controlTransfer->rxDataCount >=  controlTransfer->expectedRxDataCount)
        {
            controlEvent = USB_DEVICE_CONTROL_DATA_RECEIVED;
           
        }
    }

    if(controlEvent)
    {

         controlTransfer->handler(  controlTransfer->handle,
                                    controlTransfer->handlerIndex,
                                    controlEvent ,
                                    (USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA *)usbDeviceThisInstance->ep0RxBuffer);
    }


     USB_DEVICE_IRP * irp = USB_DEVICE_AllocateIRP((USB_DEVICE_HANDLE)usbDeviceThisInstance, 'R');
     irp->size = USB_DEVICE_EP0_BUFFER_SIZE;

     /* Submit IRP to endpoint 0 to receive the setup packet */
     (void)DRV_USB_DEVICE_IRPSubmit( usbDeviceThisInstance->usbCDHandle,
                                         controlEndpointRx ,
                                         irp);
    
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_Ep0TransmitCompleteCallback( void * handle)

  Summary:
    EP0 transmit complete callback.

  Description:
    This function is called by the controller driver after the completing the
    EP0 transmit.

  Parameters:
     handle - IRP handle.

  Returns:
    None.

*/

static void _USB_DEVICE_Ep0TransmitCompleteCallback(USB_DEVICE_IRP * irpHandle)
{
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer;

    SYS_ASSERT((irpHandle != NULL), "Invalid Control Tx IRP");

    controlTransfer = &usbDeviceInstance->controlTransfer;


    usbDeviceThisInstance = (USB_DEVICE_INSTANCE_STRUCT *)irpHandle->userData;

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_ABORTED)
    {
        return;
    }

    if(usbDeviceThisInstance->setAddressPending)
    {
        DRV_USB_DEVICE_AddressSet(usbDeviceThisInstance->usbCDHandle, usbDeviceThisInstance->deviceAddress);
        usbDeviceThisInstance->setAddressPending = false;
    }

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_COMPLETED)
    {
        if( irpHandle->size == 0 )
        {
            // Just completed transmitting ZLP.
            controlTransfer->inProgress = false;
        }
    }
}


/******************************************************************************
  Function:
    SYS_MODULE_OBJ USB_DEVICE_Initialize(const SYS_MODULE_INDEX index, 
                                       const SYS_MODULE_INIT * const initData)

  Summary:
    Initializes the required USB device layer state machines.

  Description:
    This function initializes the required state machines of the USB device layer.

  Remarks:
    None.
*/

SYS_MODULE_OBJ USB_DEVICE_Initialize(const SYS_MODULE_INDEX index, 
                                        const SYS_MODULE_INIT * const initData)
{
    USB_DEVICE_INIT *deviceInit;
    USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance;
    DRV_USB_INIT drvUsbInit;
    SYS_MODULE_OBJ drvObj;
    USB_DEVICE_IRP * irpEp0Rx;
    USB_DEVICE_IRP * irpEp0Tx;
         
    // Copy init data to local variable.
    deviceInit = (USB_DEVICE_INIT *)initData;
    
    // Make sure the index is with in range.
    SYS_ASSERT( ( ( index >= 0 ) && ( index < USB_DEVICE_MAX_INSTANCES ) ), 
                      " USB Device Layer: Invalid index or value assigned to USB_DEVICE_MAX_INSTANCES ");
    
    // Make sure that initData is not NULL.
    SYS_ASSERT( (deviceInit != NULL) ,"InitData passed is NULL" );
    
     // Make sure that master descriptor table is not NULL.
    SYS_ASSERT( (deviceInit->usbMasterDescriptor != NULL) ,"USB master descriptor table passed is NULL" );

    // Get this instance of USB device layer.
    usbDeviceThisInstance = &usbDeviceInstance[index];

    //InitializeAllIRPs(usbDeviceThisInstance);
      
    //Initialize this instance.        
    usbDeviceThisInstance->usbDeviceInstanceState = SYS_STATUS_READY;
    
    // Save the "self" index for future use    
    usbDeviceThisInstance->usbDevLayerIndex = index;
    
    // Set the device state to unconfigured.
    usbDeviceThisInstance->usbDeviceState = USB_DEVICE_STATE_DETACHED;
    
    // Initialize the instance structure.
    usbDeviceThisInstance->ptrMasterDescTable =  deviceInit->usbMasterDescriptor;
    usbDeviceThisInstance->registeredFuncDriverCount =    deviceInit->registeredFuncCount;
    usbDeviceThisInstance->registeredFuncDrivers     =    deviceInit->registeredFunctions;

    // Initialize remote wakeup to 0 (not supported)
    usbDeviceThisInstance->remoteWakeupStatus = 0;

    drvUsbInit.interruptSource = deviceInit->interruptSource ;
    drvUsbInit.moduleInit = deviceInit->moduleInit ;
    drvUsbInit.operationMode = USB_OPMODE_DEVICE ;
    drvUsbInit.stopInIdle = deviceInit->stopInIdle ;
    drvUsbInit.suspendInSleep = deviceInit->suspendInSleep ;
    drvUsbInit.usbID = deviceInit->usbID ;
    drvUsbInit.operationSpeed = deviceInit->deviceSpeed ;
    drvUsbInit.endpointTable = deviceInit->endpointTable;
 

    drvObj = DRV_USB_Initialize(index, (SYS_MODULE_INIT *)&drvUsbInit);

    SYS_ASSERT((drvObj != SYS_MODULE_OBJ_INVALID ), "USB Device Layer: Driver obj is NULL ");
    
    // Reset set address flag.
    usbDeviceThisInstance->setAddressPending = false;
   
    // Open the driver handle.
    usbDeviceThisInstance->usbCDHandle = DRV_USB_Open( index,
                                                        DRV_IO_INTENT_EXCLUSIVE|DRV_IO_INTENT_NONBLOCKING|DRV_IO_INTENT_READWRITE);
    
    SYS_ASSERT( ( DRV_HANDLE_INVALID != usbDeviceThisInstance->usbCDHandle ),
                                    "USB Device Layer: Bad handle returned from driver");
        
    // Register a callback with the driver.
    DRV_USB_ClientEventCallBackSet(usbDeviceThisInstance->usbCDHandle,
                                             (uintptr_t)usbDeviceThisInstance,
                                            &_USB_DEVICE_EventHandler);

    // Open 1st client of the device layer.
    // The 1st client of the device layer is used by all function drivers.
    usbDeviceClients[index][0].clientState = DRV_CLIENT_STATUS_READY;
    usbDeviceClients[index][0].usbDeviceInstance = usbDeviceThisInstance;
    // Save the internal client handle for function drivers.
    usbDeviceInstance[index].hClientInternalOperation = (USB_DEVICE_HANDLE)&usbDeviceClients[index][0];

    //DRV_USB_DEVICE_Attach(usbDeviceThisInstance->usbCDHandle);

    return index;

}    

/******************************************************************************
  Function:
    CLIENT_HANDLE USB_DEVICE_Open( const SYS_MODULE_INDEX index,
                                const DRV_IO_INTENT    intent )

  Summary:
    Opens the specific module instance and returns a handle.

  Description:
    This function opens the USB device layer for use by any client module and
    provides a handle that must be provided to any of the other device layer 
    operations to identify the caller and the instance of the driver/hardware module.

  Parameters:
    index           - Identifier for the instance to be initialized
    intent          - Zero or more of the values from the enumeration
                      DRV_IO_INTENT ORed together to indicate the intended use
                      of the driver
  Returns:
    If successful, the routine returns a valid open-instance handle.
    If an error occurs, the return value is DRV_HANDLE_INVALID.
*/

CLIENT_HANDLE USB_DEVICE_Open(const SYS_MODULE_INDEX index, const DRV_IO_INTENT  intent )
{
    uint8_t i;
    CLIENT_HANDLE retValue = DRV_HANDLE_INVALID;
    USB_DEVICE_CLIENT_STRUCT* usbDeviceThisClient;

     // Make sure the index is with in range.
    SYS_ASSERT( ( ( index >= 0 ) && ( index < USB_DEVICE_MAX_INSTANCES ) ), 
                      " USB Device Layer: Invalid index or value assigned to USB_DEVICE_MAX_INSTANCES ");
    
    // Check if the instance is initialized.   
    SYS_ASSERT( ( usbDeviceInstance[index].usbDeviceInstanceState > SYS_STATUS_UNINITIALIZED ),
                         "USB_DEVICE_Initialize() is not yet called for this instance");

    if( intent & ( DRV_IO_INTENT_NONBLOCKING | DRV_IO_INTENT_SHARED ) )
    {
        /* The driver only supports this mode */

        SYS_ASSERT(false, "Device layer supports non blocking and shared access only");
        return DRV_HANDLE_INVALID;
    }
   
	for(i = 0; i < USB_DEVICE_MAX_CLIENTS + 1; i++)
    {
        // Copy this local client.
        usbDeviceThisClient = (USB_DEVICE_CLIENT_STRUCT *)&usbDeviceClients[index][i];

        // Check for a free handle.
        if( usbDeviceThisClient->clientState == DRV_CLIENT_STATUS_CLOSED )
        {
            // Ready the client.
            usbDeviceThisClient->clientState = DRV_CLIENT_STATUS_READY;
            // Link the instance index.
            usbDeviceThisClient->usbDeviceInstance = &usbDeviceInstance[index];
            retValue = (CLIENT_HANDLE)usbDeviceThisClient;
            break;
        }    
    }  
    
    // This assert means, you may have to increase the value of USB_DEVICE_MAX_CLIENTS,
    // or close unused handles.
    SYS_ASSERT( ( DRV_HANDLE_INVALID != retValue ),
                "USB device layer: No free client handles");
        
    // All the handles are occupied.     
    return(retValue);   
}    


// *****************************************************************************
/* Function:
    void USB_DEVICE_Close( CLIENT_HANDLE usbDevHandle )

  Summary:
    Closes an opened instance of the USB device layer.

  Description:
    This function closes an opened instance of the USB device layer, invalidating the
    handle.

  Parameters:
    handle       - A valid open instance handle, returned from USB_DEVICE_Open

  Returns:
    None.


*/

void USB_DEVICE_Close(CLIENT_HANDLE hClient )
{
    USB_DEVICE_CLIENT_HANDLE usbClientHandle;
    
    // Check the handle.
    SYS_ASSERT( ( DRV_HANDLE_INVALID != hClient ), "Invalid client handle");
    
    // Close the handle.
    usbClientHandle = (USB_DEVICE_CLIENT_HANDLE)hClient;
    
    // close the handle.
    usbClientHandle->clientState = DRV_CLIENT_STATUS_CLOSED;
    
}    

// *****************************************************************************
/* Function:
    DRV_CLIENT_STATUS USB_DEVICE_ClientStatus
                                             ( USB_DEVICE_HANDLE usbDevHandle )

  Summary:
    Gets the current client-specific status of the USB device layer.

  Description:
    This function gets the client-specfic status of the USB device layer associated
    with the specified handle.

  Precondition:
    The USB_DEVICE_Initialize function must have been called. USB_DEVICE_Open must
    have been called to obtain a valid opened device handle.

  Parameters:
    handle       - A valid open instance handle, returned from USB_DEVICE_Open

  Returns:
    A value of enum type DRV_CLIENT_STATUS describing the current status of 
    the USB device layer.
*/

DRV_CLIENT_STATUS USB_DEVICE_ClientStatus( CLIENT_HANDLE hHandle )
{
    USB_DEVICE_CLIENT_STRUCT* devClientHandle;
    
    devClientHandle = (USB_DEVICE_CLIENT_STRUCT*)hHandle;  
    
    // Return the state of the client.  
    return( devClientHandle->clientState ); 
}


// *****************************************************************************
/* Function:
    SYS_STATUS USB_DEVICE_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the USB device layer.

  Description:
    This function provides the current status of the USB device layer.

  Precondition:
    The USB_DEVICE_Initialize function must have been called before calling this
    function.

  Parameters:
    object  - Driver object handle, returned from the USB_DEVICE_Initialize routine

  Returns:
    SYS_STATUS_READY          - Indicates that the device is busy with a
                                previous system level operation and cannot start
                                another

                                Note: Any value greater than SYS_STATUS_READY is
                                also a normal running state in which the device
                                is ready to accept new operations.

    SYS_STATUS_BUSY           - Indicates that the device is busy with a
                                previous system level operation and cannot start
                                another

    SYS_STATUS_UNINITIALIZED  - Indicates that the device has never been initialized

    SYS_STATUS_ERROR          - Indicates that the device is in an error state

                                Note:  Any value less than SYS_STATUS_ERROR is
                                also an error state.  
*/

SYS_STATUS USB_DEVICE_Status( SYS_MODULE_OBJ object )
{
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX)object;
    
    SYS_ASSERT( ( object == SYS_MODULE_OBJ_INVALID ), "Handle is invalid");
    
   return( usbDeviceInstance[index].usbDeviceInstanceState );
}    
  
    
/******************************************************************************
  Function:
    USB_ERROR USB_DEVICE_EventCallBackSet(CLIENT_HANDLE hHandle,
                                       const USB_DEVICE_CALLBACK *callBackFunc)

  Summary:
    Sets up the callback function that will be called in case of an
    event from the USB device layer.

  Description:
    This function sets up the callback funtion. This callback function 
    will be called when an event occurs in the USB device layer.

  Parameters:
    hHandle           - Device layer handle that is returned from
                        the funtion USB_DEVICE_Open
                        
    callBackFunc      - Call back function that should be called in case
                        of an event
   
  Returns:
    If successful, this function returns the error status "USB_ERROR_OK".
*/

USB_ERROR USB_DEVICE_EventCallBackSet(CLIENT_HANDLE hHandle, const USB_DEVICE_CALLBACK callBackFunc)
{
    
    USB_DEVICE_CLIENT_STRUCT* devClientHandle;    
    
    SYS_ASSERT( ( DRV_HANDLE_INVALID != hHandle ), "USB Device Layer: Handle passed is invalid" );
        
    devClientHandle = (USB_DEVICE_CLIENT_STRUCT*)hHandle;    
       
    // Check if this handle is in a ready state.
    if(devClientHandle->clientState == DRV_CLIENT_STATUS_READY)
    {    
        // Register the callback function.
        devClientHandle->callBackFunc = callBackFunc;
        
        // Return OK
         return (USB_ERROR_NONE);
    }   
    else
    {
        // Return failed
        return (USB_ERROR_CLIENT_NOT_READY);
    }
}   

/******************************************************************************
  Function:
    uint16_t USB_DEVICE_GetConfigurationValue(CLIENT_HANDLE *hHandle)

  Summary:
    Gets the configuration selected by the Host.

  Description:
    This function gets the current active USB configuration.

  Parameters:
    hHandle - Client handle that is returned by USB_DEVICE_Open
   
  Returns:
    Present active configuration of the device.
*/

uint8_t USB_DEVICE_GetConfigurationValue(CLIENT_HANDLE hHandle)
{
    USB_DEVICE_CLIENT_STRUCT * devClientHandle;

    devClientHandle = (USB_DEVICE_CLIENT_STRUCT*)hHandle;

    // Check if client is opened.
    SYS_ASSERT( ( devClientHandle->clientState == DRV_CLIENT_STATUS_READY ),
                                                     "Client is not yet opened");


    return(devClientHandle->usbDeviceInstance->activeConfiguration);
}


/******************************************************************************
  Function:
    USB_SPEED USB_DEVICE_GetDeviceSpeed(CLIENT_HANDLE *hHandle)

  Summary:
    Gets the speed on which the device has enumerated.

  Description:
    This function gets the speed on which the device has enumerated.

  Parameters:
    hHandle - Client handle that is returned by USB_DEVICE_Open
   
  Returns:
    USB speed.
*/

USB_SPEED USB_DEVICE_GetDeviceSpeed(CLIENT_HANDLE hHandle)
{
    USB_DEVICE_CLIENT_STRUCT* devClientHandle;
    
    devClientHandle = (USB_DEVICE_CLIENT_STRUCT*)hHandle;

    // Check if client is opened.
    SYS_ASSERT( ( devClientHandle->clientState == DRV_CLIENT_STATUS_READY ),
                                                     "Client is not yet opened");

    return(devClientHandle->usbDeviceInstance->usbSpeed);
}


// *****************************************************************************
/* Function:
    void USB_DEVICE_Reinitialize( SYS_MODULE_OBJ usbDeviceObj,
                                  const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes the USB device layer.

  Description:
    This function reinitializes the USB device layer.

  Parameters:
    usbDeviceObj    - Driver object handle, returned by USB_DEVICE_Initialize
    init            - Pointer to a data structure containing any data necessary
                      to reinitialize the USB device layer

  Returns:
    None.
*/

void USB_DEVICE_Reinitialize ( SYS_MODULE_OBJ usbDeviceObj,
                                        const SYS_MODULE_INIT * const init )
{
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX)usbDeviceObj;
    
    SYS_ASSERT( ( usbDeviceObj != SYS_MODULE_OBJ_INVALID ), "Handle is invalid");
    
    // Check if this instance is initialized already.
    SYS_ASSERT( ( usbDeviceInstance[index].usbDeviceInstanceState > SYS_STATUS_UNINITIALIZED ),
                               " This USB device instance is not yet initialized ");
    
    // Deinitialize
    USB_DEVICE_Deinitialize( usbDeviceObj );    
    // Go for re-initialization.
    USB_DEVICE_Initialize( index, init );
    
}    


// *****************************************************************************
/* Function:
    void USB_DEVICE_Deinitialize ( SYS_MODULE_OBJ usbDeviceobj)

  Summary:
    Deinitializes the specified instance of the USB device layer.

  Description:
    This function deinitializes the specified instance of the USB device layer, 
    disabling its operation (and any hardware) and invalidates all of the internal data.

  Parameters:
    usbDeviceObj    - USB Device Layer object handle, returned by USB_DEVICE_Initialize

  Returns:
    None.
  
*/

void USB_DEVICE_Deinitialize ( SYS_MODULE_OBJ usbDeviceObj )
{
    uint8_t client;
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance;
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX)usbDeviceObj;

    usbDeviceThisInstance = ( USB_DEVICE_INSTANCE_STRUCT *)&usbDeviceInstance[index];

    //Just invalidate the handle.
    usbDeviceThisInstance->usbDeviceInstanceState =  SYS_STATUS_UNINITIALIZED;
    
    
    // Invalidate all clients.
    for( client = 0; client < USB_DEVICE_MAX_CLIENTS + 1; client++ )
    {
        usbDeviceClients[index][client].clientState = DRV_CLIENT_STATUS_CLOSED ;
    }

    DRV_USB_Deinitialize(USB_DEVICE_INDEX_0);
}


// *****************************************************************************
/* Function:
    void _USB_DEVICE_DeInitializeAllFunctionDrivers(
                                USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance )

  Summary:
    Deinitializes all function drivers that are presently loaded
    for the selected configuration.

  Description:
    

  Parameters:
    usbDeviceInstance    - Pointer to this USB device instance.

  Returns:
    None.

*/

void _USB_DEVICE_DeInitializeAllFunctionDrivers(
                                USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance )
{
    uint8_t count = 0;
    uint16_t maxFunctionCounts = usbDeviceInstance->registeredFuncDriverCount;
    USB_DEVICE_FUNC_REGISTRATION_TABLE * funcRegTable = usbDeviceInstance->registeredFuncDrivers;
    uint8_t speed = usbDeviceInstance->usbSpeed ;
    uint16_t configValue = usbDeviceInstance->activeConfiguration ;


    for(count = 0; count < maxFunctionCounts; count++ )
    {
        if( (funcRegTable->speed & speed) && (funcRegTable->configurationValue == configValue))
        {
            if( funcRegTable->driver->deInitialize != NULL)
            {
                    funcRegTable->driver->deInitialize( funcRegTable->funcDriverIndex );               
            }           
        }
        funcRegTable++;
    }
    
}

/******************************************************************************
  Function:
    void _USB_DEVICE_EventHandler(void* referenceHandle,
        DRV_USB_CLIENT_STATUS eventType, DRV_USB_EVENT_DATA * eventData )

  Summary:
    Handles the events originating from the USB Controller driver.

  Description:
    This function is registered into the USB Controller driver as a callback
    function. The USB Controller driver calls this function in case of events
    from the USB Controller driver.

  Parameters:
    referenceHandle           - pointer to USB device instance
    eventType                 - Event type
    eventData                 - ponter to data associated with the event
    
  Returns:
    None.
*/

/**************************************************
 * The DRV_USB_DEVICE_EndpointDisableAll() function
 * is really the DRV_USB_DEVICE_EndpointDisable()
 * function called with a special parameter.
 **************************************************/
#define DRV_USB_DEVICE_EndpointDisableAll(x)  DRV_USB_DEVICE_EndpointDisable(x, _DRV_USB_DEVICE_ENDPOINT_ALL)


void _USB_DEVICE_EventHandler( uintptr_t referenceHandle,
            DRV_USB_EVENT eventType, void * eventData )
{
    
    USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance;
    USB_MASTER_DESCRIPTOR * ptrMasterDescTable;
    unsigned char err;
             
    usbDeviceInstance = (USB_DEVICE_INSTANCE_STRUCT *)referenceHandle;
    
    // Handle events, only if this instance is in initialized state.
    if( usbDeviceInstance->usbDeviceInstanceState <= SYS_STATUS_UNINITIALIZED )
    {
        // Instance is deInited. Just do a return.
        // Doing just return, will cause the driver to send ZLPs for set packets.
        // This is a known thing and must be caught during debuggging.
        return;                
    }
    
    switch(eventType)
    {
	case DRV_USB_EVENT_RESET_DETECT:

            // Cancel any IRP already submitted in the RX direction.
            DRV_USB_DEVICE_IRPCancelAll( usbDeviceInstance->usbCDHandle,
                                        controlEndpointRx );
            
            // Disable all endpoints except for EP0.
            DRV_USB_DEVICE_EndpointDisableAll(usbDeviceInstance->usbCDHandle);

             // Deinit all function drivers.
            _USB_DEVICE_DeInitializeAllFunctionDrivers ( usbDeviceInstance );

      
            // Host has issued a reset.
            // If the control endpoint is already opened, close it.
            /* Enable EP0 endpoint in rx direction */
            (void)DRV_USB_DEVICE_EndpointEnable( usbDeviceInstance->usbCDHandle,
                                                  controlEndpointRx, // fixed bug, was Tx
                                                  USB_TRANSFER_TYPE_CONTROL,
                                                  USB_DEVICE_EP0_BUFFER_SIZE);

            USB_DEVICE_IRP * irp = USB_DEVICE_AllocateIRP((USB_DEVICE_HANDLE)usbDeviceInstance, 'R');
            /* Submit IRP to endpoint 0 to receive the setup packet */
            (void)DRV_USB_DEVICE_IRPSubmit( usbDeviceInstance->usbCDHandle,
                                         controlEndpointRx ,
                                         irp);
           					
            // Change device state to Default
            usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_DEFAULT;
			
            // Reset means chirping has already happened. So, we must be knowing the speed.
            // get the speed and save it for future.
            usbDeviceInstance->usbSpeed = DRV_USB_DEVICE_CurrentSpeedGet(usbDeviceInstance->usbCDHandle);

            // Get the master descriptor table entry.
            ptrMasterDescTable = usbDeviceInstance->ptrMasterDescTable;

            // Now we know the speed. So for this speed get the pointer that
            // points to correct group of configurations.
            if( usbDeviceInstance->usbSpeed == USB_SPEED_HIGH )
            {
                usbDeviceInstance->configDescriptorsPtr
                    = ptrMasterDescTable->ptrHighSpeedConfigDescriptor;
                // Also get the max configurations available in this group.
                usbDeviceInstance->maxConfigs =
                    ptrMasterDescTable->highSpeedConfigDescriptorCount;
            }
            else
            {
                // Classic speeds (full/low speed)
                usbDeviceInstance->configDescriptorsPtr
                    = ptrMasterDescTable->ptrConfigDescriptor;

                // Get the maximum configurations available in this group.
                usbDeviceInstance->maxConfigs =
                    ptrMasterDescTable->configDescriptorCount;
            }

            // Invalidate the current active configuration
            usbDeviceInstance->activeConfiguration = 0;

            break;

        case DRV_USB_EVENT_RESUME_DETECT:
            // USB device resumed.
            // Restore the device state to previous state.
            usbDeviceInstance->usbDeviceState = usbDeviceInstance->usbDevStatePriorSuspend;
            break;

        case DRV_USB_EVENT_IDLE_DETECT:
            // This means USB device is suspended.
            // Save the device state. Once the device resumes device has to fall back
            // to its previous state.
            usbDeviceInstance->usbDevStatePriorSuspend = usbDeviceInstance->usbDeviceState;
            // Set the device state to "Suspended"
            usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_SUSPENDED;
            break;
       

        case DRV_USB_EVENT_SOF_DETECT:
            break;

        case DRV_USB_EVENT_ERROR:
            if (eventData != NULL)
                err = *(unsigned char *)eventData;
            break;
  
        default:
            // Nothing to do for all other cases.
            eventType = 0;
            break;
        
    }

    if(eventType)
    {
        
        // Broadcast event to application.
        /* Inform the clients about the event */
        _USB_DEVICE_BroadcastEventToClients( eventType, NULL,
                                          usbDeviceInstance );
    }
}    


/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessSetupPacket(SETUP_PKT* setupPkt,
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the setup packet received from the USB Controller driver.

  Description:
    This function processes the setup packet received from the USB Controller 
    driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer
   
  Returns:
    None.
    
*/

static void  _USB_DEVICE_ControlTransferHandler(    
                                                    USB_DEVICE_CONTROL_TRANSFER_HANDLE xferhandle,
                                                    SYS_MODULE_INDEX handlerIndex,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT transferEvent,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * eventData )
{
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance =
                    (USB_DEVICE_INSTANCE_STRUCT *)&usbDeviceInstance[handlerIndex];
    
    USB_SETUP_PACKET * setupPkt = ( USB_SETUP_PACKET *) eventData;
   
    if( transferEvent == USB_DEVICE_CONTROL_SETUP_REQUEST )
    {
        // Cancel any IRP that is in the pipe.
        DRV_USB_DEVICE_IRPCancelAll( usbDeviceInstance->usbCDHandle,
                                                        controlEndpointTx );

        if(setupPkt->bmRequestType == ( USB_SETUP_DIRN_HOST_TO_DEVICE |
                                        USB_SETUP_TYPE_STANDARD |
                                        USB_SETUP_RECIPIENT_DEVICE  ) )
        {
            // Serve standard SET requests
            _USB_DEVICE_ProcessStandardSetRequests( usbDeviceThisInstance, setupPkt );
        }
        else if( setupPkt->bmRequestType == ( USB_SETUP_DIRN_DEVICE_TO_HOST |
                                             USB_SETUP_TYPE_STANDARD |
                                             USB_SETUP_RECIPIENT_DEVICE ) )
        {

            // Serve standard GET requests
            _USB_DEVICE_ProcessStandardGetRequests( usbDeviceThisInstance, setupPkt );
        }
        else
        {
            // Serve any requests that is not "standard" type and whose
            // recipient is not "device". (Any request whose recipient is interface/endpoint
            // must be handled by the function driver. This is because function driver has all the information
            // about endpoint and interface)
            _USB_DEVICE_ProcessOtherRequests( usbDeviceThisInstance, setupPkt);
        }
    }   
}          


/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessStandardGetRequests(SETUP_PKT* setupPkt,
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the standard "get" requests received from the USB Controller driver.

  Description:
    This function processes the standard "get" requests received from the USB 
    Controller driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer
   
  Returns:
    None.
    
*/

static void _USB_DEVICE_ProcessStandardGetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                                    USB_SETUP_PACKET * setupPkt )
{
 
    USB_CONFIGURATION_DESCRIPTOR* lConfigDescriptor = NULL;
    uint8_t* stringDesc;
    uint16_t size = 0;
    void*  pData = NULL;
    uint8_t index;
   
    USB_MASTER_DESCRIPTOR * ptrMasterDescTable ;

    // Copy the Master decriptor table to a local pointer.
    ptrMasterDescTable = usbDeviceInstance->ptrMasterDescTable ; 
    
    if(setupPkt->bRequest == USB_REQUEST_GET_DESCRIPTOR)
    {
        switch(setupPkt->bDescriptorType)
        {
            case USB_DESCRIPTOR_DEVICE:
                if(usbDeviceInstance->usbSpeed == USB_SPEED_HIGH)
                {
                    // high speed descriptor.
                    SYS_ASSERT( ( ptrMasterDescTable->ptrHighSpeedDeviceDescriptor != NULL ),
                                                              "High speed device descriptor is NULL" );
                    // pointer to high speed device descriptor.
                    pData = ( (uint8_t*) ptrMasterDescTable->ptrHighSpeedDeviceDescriptor );
                }
                else
                {
                    // Full/low speed descriptor.
                    SYS_ASSERT( ( ptrMasterDescTable->ptrDeviceDescriptor != NULL ),
                                                            "Full/Low speed device descriptor is NULL");
                    // full/low speed device descriptor pointeusbDeviceInstance->ptrMasterDescTabler.
                    pData = ( (uint8_t*) ptrMasterDescTable->ptrDeviceDescriptor );
                }
                // Total size of the device descriptor (Its always 18).
                size = 18;
                break;
                
            case USB_DESCRIPTOR_CONFIGURATION:                
                // Get correct pointer to the descriptor based on config value.
                // setupPkt->bDscIndex indicates the host requested configuration index.
                // Make sure that the requested configuration index is with in the limits.
                if( (setupPkt->bDscIndex) < usbDeviceInstance->maxConfigs )
                {
                    lConfigDescriptor =
                        ( USB_CONFIGURATION_DESCRIPTOR* )usbDeviceInstance->configDescriptorsPtr[setupPkt->bDscIndex];
                    // Assert that pointer is not NULL
                    SYS_ASSERT( ( lConfigDescriptor != NULL ),
                        "USB Device Layer: Invalid pointer to configuration descriptor");
                    // Total Size of the descriptor to be sent to Host.
                    size = lConfigDescriptor->wTotalLength;
                  
                }
                pData  = (uint8_t *)lConfigDescriptor;
                break;
            
            case USB_DESCRIPTOR_DEVICE_QUALIFIER:
                if( usbDeviceInstance->usbSpeed == USB_SPEED_HIGH )
                {
                    // For high speed, respond with the other speed (full speed) device_qualifier.
                    pData  = (uint8_t*) ptrMasterDescTable->ptrFullSpeedDeviceQualifier;
                }
                else
                {
                    // For full speed, repond with the other speed (high speed) device_qualifier. 
                    pData  = ((uint8_t*) ptrMasterDescTable->ptrHighSpeedDeviceQualifier );
                } 
                          
                // Size of device_qualifier descriptor is always 10.
                size = 10;
                break;
            
                
            case USB_DESCRIPTOR_STRING:
                index = setupPkt->bDscIndex;
                // Check the string descriptor index
                if(setupPkt->bDscIndex < ptrMasterDescTable->stringDescCount )
                {
                    // Get correct string descriptor   
                    stringDesc = (uint8_t*)( ptrMasterDescTable->ptrStringDesc[setupPkt->bDscIndex] );
                    
                    // Prepare the response
                    pData = (uint8_t *)stringDesc;
                
                    // Length of the string is the first byte in the setring descriptor.
                    size = stringDesc[0];
                }                                   
                break;
                
            default:
                
                break;
        } 
    }
    else if (setupPkt->bRequest == USB_REQUEST_GET_CONFIGURATION)
    {
        pData = (uint8_t *)&usbDeviceInstance->activeConfiguration;
        size = 1;
    }
    else if (setupPkt->bRequest == USB_REQUEST_GET_STATUS)
    {
        usbDeviceInstance->getStatusResponse.status = 0;
        usbDeviceInstance->getStatusResponse.selfPowered = usbDeviceInstance->selfPowered;
        usbDeviceInstance->getStatusResponse.remoteWakeup = usbDeviceInstance->remoteWakeupStatus;
        pData = (uint8_t *)&usbDeviceInstance->getStatusResponse;
        size = 2;
    }

   
    if(pData == NULL)
    {
        // STALL the transfer
        USB_DEVICE_ControlStatus(  (USB_DEVICE_HANDLE)usbDeviceInstance,
                                    USB_DEVICE_CONTROL_STATUS_ERROR );
    }
    else
    {
        // Limit the size.
        if( size > setupPkt->wLength )
        {
            size = setupPkt->wLength;
        }

        // Prepare data stage
        USB_DEVICE_ControlSend( (USB_DEVICE_HANDLE)usbDeviceInstance,
                                pData,
                                size );
    }
}


/******************************************************************************
  Function:
    static USB_DEVICE_FUNC_REGISTRATION_TABLE *
            _USB_DEVICE_GetFunctionDriverEntryByInterface(  uint8_t interfaceNumber,
                                USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance )

  Summary:
    This function gets the correct entry in the function driver registration
    table for a given interface.

  Description:
    

  Parameters:
    interfaceNumber         - Interface number.
    usbDeviceThisInstance   - This instance of the USB device layer.

  Returns:
    Pointer to the function registration table entry.

*/

USB_DEVICE_FUNC_REGISTRATION_TABLE * _USB_DEVICE_GetFunctionDriverEntryByInterface(  uint8_t interfaceNumber,
                                            USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance )
{
    uint8_t count;
    uint16_t maxFunctionCounts = usbDeviceThisInstance->registeredFuncDriverCount;
    USB_DEVICE_FUNC_REGISTRATION_TABLE * funcRegTable = usbDeviceThisInstance->registeredFuncDrivers;
    uint8_t speed = usbDeviceThisInstance->usbSpeed ;
    uint8_t configValue = usbDeviceThisInstance->activeConfiguration ;

    for(count = 0; count < maxFunctionCounts; count++ )
    {
        if( (funcRegTable->speed & speed) && (funcRegTable->configurationValue == configValue)
                && ( interfaceNumber >= funcRegTable->interfaceNumber ) &&
                (interfaceNumber < ( funcRegTable->interfaceNumber + funcRegTable->numberOfInterfaces )))
        {
            // Found a correct driver.
            return(funcRegTable);
        }
        funcRegTable++;
    }
    return NULL;
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_ConfigureDevice( USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance )

  Summary:
    This function configures the device. 

  Description:
    The initialization of all the function drivers and opening of all endpoints
    are done here.

  Parameters:
    interfaceNumber         - Interface number.
    usbDeviceThisInstance   - This instance of the USB device layer.

  Returns:
    None.

*/

static void _USB_DEVICE_ConfigureDevice( USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance )
{

    uint16_t parsedLength= 0;
    uint16_t confTotalLength;
    uint8_t * pDescriptor = usbDeviceInstance->pActiveConfigDesc;
    uint8_t descriptorType;
    uint8_t interfaceNumber = 0;
    uint8_t alternateSetting = 0;
    USB_DEVICE_FUNC_REGISTRATION_TABLE * pFunctionRegTable = NULL;
   
    confTotalLength = ((USB_CONFIGURATION_DESCRIPTOR *)pDescriptor)->wTotalLength;

    while(parsedLength < confTotalLength)
    {
        descriptorType = ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bDescriptorType;
        if(descriptorType == USB_DESCRIPTOR_INTERFACE)
        {
            pFunctionRegTable = NULL;
            interfaceNumber = ((USB_INTERFACE_DESCRIPTOR * )pDescriptor)->bInterfaceNumber;
            alternateSetting = ((USB_INTERFACE_DESCRIPTOR * )pDescriptor)->bAlternateSetting;
            // Find out which function driver owns this interface in the function registration table
            pFunctionRegTable = _USB_DEVICE_GetFunctionDriverEntryByInterface( interfaceNumber ,
                                                                                    usbDeviceThisInstance);
        } 
        if( pFunctionRegTable != NULL )
        {
            pFunctionRegTable->driver->initializeByDescriptor(pFunctionRegTable->funcDriverIndex,
                                                  usbDeviceThisInstance->hClientInternalOperation,
                                                  pFunctionRegTable->funcDriverInit,
                                                  interfaceNumber, alternateSetting,
                                                  descriptorType, pDescriptor);
        }

        parsedLength += ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bLength;
        pDescriptor += ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bLength;
    }
}



/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessStandardSetRequests(SETUP_PKT* setupPkt,
    DRV_USB_XFER_HANDLE hTransfer, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the standard "set" requests received from the USB Controller driver.

  Description:
    This function processes the standard "set" requests received from the USB 
    Controller driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer
   
  Returns:
    None.
    
*/
   
static void _USB_DEVICE_ProcessStandardSetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                            USB_SETUP_PACKET * setupPkt)
{   
    uint8_t count;
    USB_DEVICE_EVENT_DATA eventData;
  
    switch(setupPkt->bRequest)
    {
        case USB_REQUEST_SET_ADDRESS:
            //Got set address command. Change the address only after responding to the current request.
            usbDeviceInstance->setAddressPending = true;            
            usbDeviceInstance->deviceAddress = setupPkt->bDevADR;
            break;
       
        case USB_REQUEST_SET_CONFIGURATION:
            // Device falls back to addressed state if configuration value is 0, and 
            // if the device is already in configured state.
            if((setupPkt->wValue == 0) && (usbDeviceInstance->usbDeviceState == USB_DEVICE_STATE_CONFIGURED))
            {
                // Configuration value 0 means, host is trying to deconfigure the device.
                // Set a event here. USB device layer task will deinitialize the function drivers later.
                usbDeviceInstance->event = USB_DEVICE_EVENT_DECONFIGURED;
                 // Deinit all function drivers.
                _USB_DEVICE_DeInitializeAllFunctionDrivers ( usbDeviceInstance );
                // Change the current active configuration to Zero
                usbDeviceInstance->activeConfiguration = 0;
                // Change the state to Addressed  
                usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_ADDRESSED;    
            }  
            else
            {
                // Proceed only if new configuration value is different from
                // current configuration value.
                if( usbDeviceInstance->activeConfiguration != (uint8_t)setupPkt->wValue)
                {
                     for(count = 0; count < usbDeviceInstance->maxConfigs; count++)
                     {
                        // 5th byte in the configuration descriptor table specifies the
                        // configuration value.
                        if( usbDeviceInstance->configDescriptorsPtr[count][5] == setupPkt->bConfigurationValue )
                        {
                            // Got a configuration match. Get the pointer to configuration
                            // descriptor. We have to pass this to function driver, so that
                            // function driver can parse configuration descriptor and get the required info.
                            usbDeviceInstance->pActiveConfigDesc = usbDeviceInstance->configDescriptorsPtr[count];
                        }
                     }

                    // Save the current active configuration.
                    // This may be required for clients to know which configuration is presently active.
                    usbDeviceInstance->activeConfiguration = (uint8_t)setupPkt->wValue;
                    
                    // Initialize all function drivers and change to configured state only if 
                    // all function drivers are initialized successfully.
                    //USB_DEVICE_SERVICE_ParseDescriptor(usbDeviceInstance->pActiveConfigDesc, &_USB_DEVICE_ConfigureDevice, usbDeviceInstance);
                    _USB_DEVICE_ConfigureDevice(usbDeviceInstance);
                    
                    // Change the state to configured.
                    usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_CONFIGURED;
                    // Set an event, so that application and function drivers are informed
                    // about the same.
                    eventData.eventConfigured.configurationValue = (uint8_t)setupPkt->wValue;
                    eventData.eventConfigured.speed = usbDeviceInstance->usbSpeed;
                    _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT_CONFIGURED, &eventData,
                                                        usbDeviceInstance );
                    
                }
            }     
            break;
       
        default:
            // Respond with a request error.
            // Stall the endpoint.
             // Stall the EP0 TX.
            USB_DEVICE_ControlStatus( (USB_DEVICE_HANDLE) usbDeviceInstance,
                                      USB_DEVICE_CONTROL_STATUS_ERROR);
            break;
    }

    // Send ZLP
    USB_DEVICE_ControlStatus( (USB_DEVICE_HANDLE) usbDeviceInstance,
                              USB_DEVICE_CONTROL_STATUS_OK);
}


/******************************************************************************
  Function:
    static USB_DEVICE_CONTROL_TRANSFER_STATE _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            SETUP_PKT* setupPkt,
                            USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlXferData)

  Summary:
    Processes the setup requests that are not targeted to the device but to endpoint/interface.
   

  Description:
    This funcion processes the setup reequests that are not targeted to the device.
    This function handles endpoint and interface specific setup packets.
    The interface specific setup packets are forwarded to function drivers or
    handled by the endpoint.

  Parameters:
    usbDeviceInstance  - This instance of the USB device layer
    setupPkt           - Setup packet buffer
    controlXferData    - Control transfer data object
  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS - if the setup packet is processed..
    
*/
static void _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            USB_SETUP_PACKET * setupPkt )
{
    USB_DEVICE_FUNC_REGISTRATION_TABLE * lFuncDriverRegTable;
    USB_ENDPOINT usbEndpoint;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer = &usbDeviceInstance->controlTransfer;
    USB_DEVICE_CONTROL_STATUS controlStatus = USB_DEVICE_CONTROL_STATUS_ERROR;
    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA eventData;

    if ( setupPkt->Recipient == USB_SETUP_RECIPIENT_ENDPOINT )
    {
        usbEndpoint = setupPkt->bEPID;

        if( setupPkt->DataDir == USB_SETUP_DIRN_HOST_TO_DEVICE )
        {
            if( setupPkt->bRequest == USB_REQUEST_CLEAR_FEATURE )
            {
                if( setupPkt->wValue == USB_FEATURE_SELECTOR_ENDPOINT_HALT )
                {
                    //TBD: Implement device state check here.
                    DRV_USB_DEVICE_EndpointStallClear(usbDeviceInstance->usbCDHandle, usbEndpoint );
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
                else if( setupPkt->wValue == USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP )
                {
                    // Remote wakeup disabled.
                    usbDeviceInstance->remoteWakeupStatus
                                            = USB_DEVICE_REMOTE_WAKEUP_DISABLED ;
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
            }
            else if (setupPkt->bRequest == USB_REQUEST_SET_FEATURE )
            {
                if( setupPkt->wValue == USB_FEATURE_SELECTOR_ENDPOINT_HALT )
                {
                    usbEndpoint = setupPkt->bEPID;
                    DRV_USB_DEVICE_EndpointStall(usbDeviceInstance->usbCDHandle,
                                                                usbEndpoint );
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
                else if( setupPkt->wValue == USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP )
                {
                    usbDeviceInstance->remoteWakeupStatus
                                            = USB_DEVICE_REMOTE_WAKEUP_ENABLED ;
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
            }

            USB_DEVICE_ControlStatus( (USB_DEVICE_HANDLE) usbDeviceInstance,
                                      controlStatus );
        }
        else if( setupPkt->bRequest == USB_REQUEST_GET_STATUS )
        {
            usbDeviceInstance->getStatusResponse.status = 0x00;
            usbDeviceInstance->getStatusResponse.endPointHalt
                    =  DRV_USB_DEVICE_EndpointIsStalled(usbDeviceInstance->usbCDHandle, usbEndpoint );

            USB_DEVICE_ControlSend( (USB_DEVICE_HANDLE) usbDeviceInstance,
                                    (uint8_t *)&usbDeviceInstance->getStatusResponse,
                                    2 );
                       
        }        
    }
    else 
    {
        // This is a function driver /vendor specific setup packet.
         // Check which function driver has to handle this setup packet.

        lFuncDriverRegTable = _USB_DEVICE_GetFunctionDriverEntryByInterface( setupPkt->bIntfID, usbDeviceInstance);

        eventData.setupRequest = setupPkt;
        
        if( (lFuncDriverRegTable != NULL)
                && (lFuncDriverRegTable->driver->controlTransferNotification != NULL))
        {
            // Save the callback and index for future use.
            // Here we change the handler to function driver specific handler.
            // All further control transfer stage must be handled by the
            // function driver control transfer handler.
            controlTransfer->handler = (void *)lFuncDriverRegTable->driver->controlTransferNotification;
            controlTransfer->handlerIndex = lFuncDriverRegTable->funcDriverIndex;
                              
            // This function driver owns the setup packet.
            controlTransfer->handler( controlTransfer->handle,
                                      controlTransfer->handlerIndex,
                                      USB_DEVICE_CONTROL_SETUP_REQUEST,
                                                              &eventData);
        }
        else
        {
            controlTransfer->handler = (void *)&_USB_DEVICE_BroadcastControlXferEventsToAppClients;
            controlTransfer->handlerIndex = usbDeviceInstance->usbDevLayerIndex ;
            //let app clients handle the setup packet.
            _USB_DEVICE_BroadcastControlXferEventsToAppClients( controlTransfer->handle,
                                                                controlTransfer->handlerIndex,
                                                                USB_DEVICE_CONTROL_SETUP_REQUEST,
                                                                &eventData);
        }
    }        
}    


/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastEventToClients
       ( USB_DEVICE_EVENT event, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )

  Summary:
    Broadcasts events to the application client.

  Description:
    This function broadcasts device layer events to all application level clients.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance.

  Returns:
    None.

*/

static void _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData,
                                 USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )
{
    uint16_t count;
    USB_DEVICE_CLIENT_STRUCT * usbDeviceClientPtr;

    // Inform all application layer clients about the event.
    for(count = 1; count < USB_DEVICE_MAX_CLIENTS+1; count++)
    {
        // Copy the client to local pointer.
        usbDeviceClientPtr = &usbDeviceClients[ usbDeviceInstance->usbDevLayerIndex ][count];

        if( usbDeviceClientPtr->clientState == DRV_CLIENT_STATUS_READY)
        {
            if( usbDeviceClientPtr->callBackFunc != NULL)
            {
                // Pass event to application
                usbDeviceClientPtr->callBackFunc(event, eventData);
            }
        }
    }
}


/******************************************************************************
  Function:
    USB_DEVICE_REMOTE_WAKEUP_STATUS USB_DEVICE_RemoteWakeupIsEnabled
                                                    ( USB_DEVICE_HANDLE handle )

  Summary:
    This functon returns the status of remote wakeup capability of the device.

  Description:
    

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance.

  Returns:
    None.

*/

USB_DEVICE_REMOTE_WAKEUP_STATUS USB_DEVICE_RemoteWakeupIsEnabled
                                                    ( USB_DEVICE_HANDLE handle )
{

    return (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->remoteWakeupStatus);
}


/******************************************************************************
  Function:
    void USB_DEVICE_PowerStateSet( USB_DEVICE_HANDLE handle,
                                                USB_DEVICE_POWER_STATE state)

  Summary:
    Sets the power state of the device.

  Description:
    

  Parameters:
    handle            - USB device handle.
    state             - Power state that indicates either the device is
                        self powered or bus powered.

  Returns:
    None.

*/

void USB_DEVICE_PowerStateSet( USB_DEVICE_HANDLE handle,
                               USB_DEVICE_POWER_STATE state)
{
    (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->selfPowered) = state;
}


/******************************************************************************
  Function:
    USB_ERROR USB_DEVICE_ControlEventCallBackSet( CLIENT_HANDLE handle,
                     const USB_DEVICE_CONTROL_TRANSFER_CALLBACK callBackFunc )

  Summary:
    Aplication clients sets the callback to capture the control events.

  Description:


  Parameters:
    handle            - USB device handle
    callBackFunc      - Callback function

  Returns:
    USB error code.

*/

USB_ERROR USB_DEVICE_ControlEventCallBackSet( CLIENT_HANDLE handle,
                     const USB_DEVICE_CONTROL_TRANSFER_CALLBACK callBackFunc )
{
    ((USB_DEVICE_CLIENT_STRUCT *)handle)->controlTransferEventCallback = callBackFunc;
    return USB_ERROR_NONE;
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastControlXferEventsToAppClients
                                   ( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                 SYS_MODULE_INDEX handlerIndex,
                                       USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                            void * eventData)

  Summary:
    This function broadcasts control transfer events to application clients.

  Description:


  Parameters:
    handle            - USB device handle
    handlerIndex      - Index
    event             - Event
    eventData         - Event data

  Returns:
    None.

*/

static void _USB_DEVICE_BroadcastControlXferEventsToAppClients( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                         SYS_MODULE_INDEX handlerIndex,
                                                         USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                         void * eventData)
{
    uint8_t count;
    USB_DEVICE_CLIENT_STRUCT * client = &usbDeviceClients[handlerIndex][1];
    for( count = 1; count < USB_DEVICE_MAX_CLIENTS; count++)
    {
        if( (client->clientState == DRV_CLIENT_STATUS_READY)
                && (client->controlTransferEventCallback != NULL) )
        {
            client->controlTransferEventCallback(client->usbDeviceInstance->controlTransfer.handle,
                                                 event, eventData );
            
            client++;
        }
    }
}

// *****************************************************************************
/* Function:
    void USB_DEVICE_ResumeStart( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    This function will start the resume signalling.

  Description:


  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    - Client's driver handle (returned from USB_DEVICE_Open)

  Returns:
    None.

  Example:
    <code>


    </code>

  Remarks:
    None.
*/

void USB_DEVICE_ResumeStart( USB_DEVICE_HANDLE handle )
{
    // Call controller driver API here.
    
}


// *****************************************************************************
/* Function:
    void USB_DEVICE_ResumeStop ( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    This function will stop the resume signalling.

  Description:


  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    - Client's driver handle (returned from USB_DEVICE_Open)

  Returns:
    None.

  Example:
    <code>


    </code>

  Remarks:
    None.
*/

void USB_DEVICE_ResumeStop( USB_DEVICE_HANDLE handle )
{
    // Call controller driver API here.

}
/********************End of file********************************/
