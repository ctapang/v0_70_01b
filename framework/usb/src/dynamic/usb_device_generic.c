/*******************************************************************************
 Generic USB device function driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_generic.c

  Summary:
    Generic USB device function driver

  Description:
    Generic USB device function driver
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
#include "usb/usb_device_generic.h"
#include "usb/usb_device.h"
#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Data Types
// *****************************************************************************
// *****************************************************************************

static void _USB_DEVICE_GENERIC_Initialize (SYS_MODULE_INDEX iGEN, DRV_HANDLE usbClientHandle,
                                    void* funcDriverInit, uint8_t interfaceNumber, uint8_t alternateSetting,
                                    uint8_t descriptorType, uint8_t * pDescriptor );

static void _USB_DEVICE_GENERIC_Deinitialize ( USB_DEVICE_GENERIC_INDEX iGEN );

static void _USB_DEVICE_GENERIC_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iGEN,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData );

void _USB_DEVICE_GENERIC_Tasks(SYS_MODULE_INDEX iGen);

// *****************************************************************************
/* Generic USB device function driver structure

  Summary:
    Defines the function driver structure required for the device layer.

  Description:
    This data type defines the function driver structure required for the
    device layer.

  Remarks:
    This structure is private to the USB stack.
 */
USB_DEVICE_FUNCTION_DRIVER genFuncDriver = {
    /* Generic USB device driver init function
     which gets called by the Device layer recieves set config event*/
    .initializeByDescriptor = &_USB_DEVICE_GENERIC_Initialize,

    /* Generic USB device driver de-init function which
    gets called when the device layer detects a device dettach,
    change in configuration and reset.*/
    .deInitialize = &_USB_DEVICE_GENERIC_Deinitialize ,

    .controlTransferNotification = &_USB_DEVICE_GENERIC_ControlTransferHandler,

    /* Generic USB device driver tasks function */
    .tasks = _USB_DEVICE_GENERIC_Tasks // SYS_MODULE_INDEX

};

// *****************************************************************************
/* Generic USB device instance structure

  Summary:
    This structure holds the instance variable.

  Description:
    

  Remarks:
    This structure is private to  USB stack.
 */
typedef struct _USB_DEVICE_GENERIC_INSTANCE
{
    USB_DEVICE_CLIENT_HANDLE usbClientHandle;
    USB_ENDPOINT endpoints[ USB_DEVICE_GENERIC_MAX_ENDPOINTS * 2 ];
    uint8_t endpointCount;
    USB_DEVICE_GENERIC_EVENT_HANDLER appCallBack;
    uintptr_t userData;
}USB_DEVICE_GENERIC_INSTANCE;


// *****************************************************************************
/* Generic USB device instance structure

  Summary:
    This structure holds the instance variable.

  Description:


  Remarks:
    This structure is private to  USB stack.
 */

static USB_DEVICE_GENERIC_INSTANCE gUsbDeviceGenInstance[USB_DEVICE_GENERIC_MAX_INSTANCES];

// Function
void _USB_DEVICE_GENERIC_Tasks(SYS_MODULE_INDEX iGen)
{
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGen];
    USB_ENDPOINT endPoint;
    DRV_USB_CLIENT_OBJ * clientObj = (DRV_USB_CLIENT_OBJ *)genInstance->usbClientHandle;

    int i;
    if (clientObj != (DRV_USB_CLIENT_OBJ *) DRV_HANDLE_INVALID)
    {
        for(i = 0; i < genInstance->endpointCount; i++)
        {
            endPoint = genInstance->endpoints[i];
        }
    }
}


/******************************************************************************
  Function:
    static void void _USB_DEVICE_GENERIC_InitializeByDescriptorType
                                (SYS_MODULE_INDEX iGEN, DRV_HANDLE usbDeviceHandle,
                                void* funcDriverInit, uint8_t intfNumber, uint8_t altSetting,
                                uint8_t descriptorType, uint8_t * pDescriptor)

  Summary:
    This function will initialize the Generic function driver by interface.

  Description:


  Parameters:
    iGEN            - Generic instance index
    usbDeviceHandle - USB device handle
    funcDriverInit  - Function driver init structure
    intfNumber      - Interface number
    altSetting      - ALternate setting
    descriptorType  - Descriptor type
    pDescriptor     - Pointer to the descriptor.

  Returns:
    None.

*/

void _USB_DEVICE_GENERIC_Initialize (SYS_MODULE_INDEX iGEN, DRV_HANDLE usbClientHandle,
                                    void* funcDriverInit, uint8_t intfNumber, uint8_t altSetting,
                                    uint8_t descriptorType, uint8_t * pDescriptor )
{
    USB_ENDPOINT_DESCRIPTOR * epDescriptor = ( USB_ENDPOINT_DESCRIPTOR *)pDescriptor;
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];



    genInstance->usbClientHandle = (USB_DEVICE_CLIENT_STRUCT *)usbClientHandle;

    if( (descriptorType == USB_DESCRIPTOR_ENDPOINT) && (altSetting == 0) )
    {
    
        // Device layer has configured and opened an endpoint.
        // We just have to open the endpoint and arm if necessary.

        if( ( epDescriptor->transferType >= USB_TRANSFER_TYPE_CONTROL )
                || ( epDescriptor->transferType <= USB_TRANSFER_TYPE_INTERRUPT ))
        {

           // Save the endpoint information.
           genInstance->endpoints[genInstance->endpointCount++] = epDescriptor->bEndpointAddress;
           
            // Open the endpoint.
            USB_DEVICE_EndpointEnable(usbClientHandle, epDescriptor->bEndpointAddress,
                                          epDescriptor->transferType,
                                          epDescriptor->wMaxPacketSize);


        }
        else
        {
            SYS_ASSERT( false, "USB Device generic driver: Illegal transfer type. Check descriptors ");
        }
    }
}


/******************************************************************************
  Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStall 
                ( USB_DEVICE_GENERIC_INDEX iGEN, USB_ENDPOINT endpoint )

  Summary:
    This function will initialize the Generic function driver by interface.

  Description:


  Parameters:
    iGEN            - Generic instance index
    endpoint        - Endpoint to stall

  Returns:
    USB_DEVICE_GENERIC_RESULT

*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStall ( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_ENDPOINT endpoint )
{
     USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];



     return ( USB_DEVICE_EndpointStall( genInstance->usbClientHandle,
                                        endpoint ));

}


/******************************************************************************
  Function:
    bool USB_DEVICE_GENERIC_EndpointIsStalled( USB_DEVICE_GENERIC_INDEX iGEN,
                                                USB_ENDPOINT endpoint )

  Summary:
    Returns true if endpoint is stalled.

  Description:


  Parameters:
    iGEN:  Generid driver index.
    endpoint: Endpoint to check for stall.

  Returns:
   true if endpoint is stalled

*/

bool USB_DEVICE_GENERIC_EndpointIsStalled( USB_DEVICE_GENERIC_INDEX iGEN,
                                                USB_ENDPOINT endpoint )
{
     USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];

     return( USB_DEVICE_EndpointIsStalled( genInstance->usbClientHandle,
                                           endpoint) );
    
}


/******************************************************************************
  Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStallClear
                        ( USB_DEVICE_GENERIC_INDEX iGEN, USB_ENDPOINT endpoint )

  Summary:
   Clears stall on the specified endpoint.

  Description:


  Parameters:
    iGEN:  Generic driver index.
    endpoint: Endpoint to clear the stall.

  Returns:
   USB_DEVICE_GENERIC_RESULT

*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointStallClear( USB_DEVICE_GENERIC_INDEX iGEN,
                                                 USB_ENDPOINT endpoint )
{
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];

    return ( USB_DEVICE_EndpointStallClear( genInstance->usbClientHandle,
                                            endpoint ) );
}


/******************************************************************************
  Function:
    bool USB_DEVICE_GENERIC_EndpointIsEnabled( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_ENDPOINT endpoint )

  Summary:
    Returns true if endpoint is enabled.

  Description:


  Parameters:
    iGEN:  Generic driver index.
    endpoint: Endpoint to check.

  Returns:
   true if endpoint is enabled.

*/

bool USB_DEVICE_GENERIC_EndpointIsEnabled( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_ENDPOINT endpoint )
{
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];

    return ( USB_DEVICE_EndpointIsEnabled( genInstance->usbClientHandle,
                                            endpoint ) );
    
}

/******************************************************************************
  Function:
    void _USB_DEVICE_GENERIC_EndpointWriteCallBack( void * irp )

  Summary:
    Endpoint write callback.

  Description:


  Parameters:
    irp - handle to IRP submitted.

  Returns:
    none.

*/

void _USB_DEVICE_GENERIC_EndpointWriteCallBack( USB_DEVICE_IRP * irp )
{
   USB_DEVICE_GENERIC_EVENT_DATA event; // FIXME: may need to allocate
   USB_DEVICE_GENERIC_INSTANCE * usbGenInstance;
   USB_DEVICE_GENERIC_EVENT eventType = (irp->status == USB_DEVICE_IRP_STATUS_ABORTED) ? 
       USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_ABORTED : USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE;

   usbGenInstance = &gUsbDeviceGenInstance[irp->userData] ;

    if( usbGenInstance->appCallBack != NULL )
    {
        event.endpointWriteComplete.data = irp->data;
        event.endpointWriteComplete.dataSize = irp->size;
        event.endpointWriteComplete.status = irp->status;
        event.endpointWriteComplete.transferHandle = ( USB_DEVICE_GENERIC_TRANSFER_HANDLE )irp;

        usbGenInstance->appCallBack( ( USB_DEVICE_GENERIC_INDEX ) irp->userData,
                                       (USB_DEVICE_CONTROL_TRANSFER_HANDLE)NULL,
                                       eventType,
                                       &event,
                                       (uintptr_t)usbGenInstance->userData);
    }
}


/******************************************************************************
  Function:
    void _USB_DEVICE_GENERIC_EndpointReadCallBack( void * irp )

  Summary:
    Endpoint read callback.

  Description:


  Parameters:
    irp - handle to IRP submitted.

  Returns:
    none.

*/

void _USB_DEVICE_GENERIC_EndpointReadCallBack( USB_DEVICE_IRP * irp )
{
   USB_DEVICE_GENERIC_EVENT_DATA event; // FIXME: may need to allocate
   USB_DEVICE_GENERIC_INSTANCE * usbGenInstance;
   USB_DEVICE_GENERIC_EVENT eventType = (irp->status == USB_DEVICE_IRP_STATUS_ABORTED) ? 
       USB_DEVICE_GENERIC_EVENT_CONTROL_TRANSFER_ABORTED : USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE;

   usbGenInstance = &gUsbDeviceGenInstance[irp->userData] ;

    if( usbGenInstance->appCallBack != NULL )
    {
        event.endpointReadComplete.data = irp->data;
        event.endpointReadComplete.dataSize = irp->size;
        event.endpointReadComplete.status = irp->status;
        event.endpointReadComplete.transferHandle = ( USB_DEVICE_GENERIC_TRANSFER_HANDLE )irp;

        usbGenInstance->appCallBack( ( USB_DEVICE_GENERIC_INDEX ) irp->userData,
                                       (USB_DEVICE_CONTROL_TRANSFER_HANDLE)NULL,
                                       eventType,
                                       &event,
                                       (uintptr_t)usbGenInstance->userData );

    }
}


/******************************************************************************
  Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointWrite( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                            USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize,
                                            USB_DEVICE_GENERIC_TRANSFER_FLAG flags )

  Summary:
    Writes data to endpoint.

  Description:


  Parameters:
    iGEN              - USB generic function driver instance ID.
    transferHandle    - Pointer to transfer handle.
    endpoint          - endpoint address
    buffer            - Buffer pointer
    bufferSize        - Buffer size
    flags             - Flag that specifies this function whether to end the
                        transfer with a short packet or not.

  Returns:
    none.

*/

//debug
int at = 0;

// Declaration of allocation function in usb_device.c
// Normally this should be declared in usb_device.h, but there are complications
// with declaring it there. This is a kludge.
extern USB_DEVICE_IRP * USB_DEVICE_AllocateIRP( USB_DEVICE_INSTANCE_STRUCT * device,
    const char direction );

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointWrite( USB_DEVICE_GENERIC_INDEX iGEN,
                                            USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                            USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize,
                                            USB_DEVICE_GENERIC_TRANSFER_FLAG flags )
{
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];
    USB_DEVICE_CLIENT_STRUCT * clientHandle = (USB_DEVICE_CLIENT_STRUCT *)genInstance->usbClientHandle;

    at++;
    
    USB_DEVICE_IRP * irp = USB_DEVICE_AllocateIRP( (USB_DEVICE_INSTANCE_STRUCT *)clientHandle->usbDeviceInstance, 'T' );
    if (irp == NULL)
        return USB_DEVICE_GENERIC_RESULT_QUEUE_FULL;

    irp->data = buffer;
    irp->size = bufferSize;
    irp->flags |= flags;
    irp->userData = iGEN;
    irp->callback = &_USB_DEVICE_GENERIC_EndpointWriteCallBack;
    (* transferHandle) = ( USB_DEVICE_GENERIC_TRANSFER_HANDLE )irp;
    return (  USB_DEVICE_IRPSubmit( genInstance->usbClientHandle,  // macro call
                                   endpoint, irp ));
}


/******************************************************************************
  Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointRead( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                           USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize )

  Summary:
    Reads data from endpoint.

  Description:


  Parameters:
    iGEN              - USB generic function driver instance ID.
    transferHandle    - Pointer to transfer handle.
    endpoint          - endpoint address
    buffer            - Buffer pointer
    bufferSize        - Buffer size
   

  Returns:
    USB_DEVICE_GENERIC_RESULT

*/

int callCount = 0;

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EndpointRead( USB_DEVICE_GENERIC_INDEX iGEN,
                                           USB_DEVICE_GENERIC_TRANSFER_HANDLE * transferHandle,
                                           USB_ENDPOINT endpoint, uint8_t * buffer, size_t bufferSize )
{
    callCount++;
    
    USB_DEVICE_GENERIC_INSTANCE * genInstance = &gUsbDeviceGenInstance[iGEN];
    USB_DEVICE_CLIENT_STRUCT * clientHandle = (USB_DEVICE_CLIENT_STRUCT *)genInstance->usbClientHandle;
    USB_DEVICE_IRP * irp = USB_DEVICE_AllocateIRP( (USB_DEVICE_INSTANCE_STRUCT *)clientHandle->usbDeviceInstance, 'R' );

    irp->data = buffer;
    irp->size = bufferSize;
    irp->userData = iGEN;
    irp->callback = &_USB_DEVICE_GENERIC_EndpointReadCallBack;
    *transferHandle = (USB_DEVICE_GENERIC_TRANSFER_HANDLE)irp;

    USB_DEVICE_CLIENT_STRUCT * client = ((USB_DEVICE_CLIENT_STRUCT *)genInstance->usbClientHandle);
    SYS_ASSERT(client != NULL, "bad client");
    SYS_ASSERT(client->usbDeviceInstance != NULL, "bad device instance");
    SYS_ASSERT(client->usbDeviceInstance->usbCDHandle != NULL, "bad USB generic handle");
    
    return (  USB_DEVICE_IRPSubmit( client, endpoint, irp ));
    
}

/******************************************************************************
  Function:
    USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EventHandlerSet( USB_DEVICE_GENERIC_INDEX iGEN ,
                                                      USB_DEVICE_GENERIC_EVENT_HANDLER eventHandler )

  Summary:
    Sets callback event handler.

  Description:


  Parameters:
    iGEN              - USB generic function driver instance ID.
    eventHandler      - Event handler callback function.

  Returns:
    USB_DEVICE_GENERIC_RESULT

*/

USB_DEVICE_GENERIC_RESULT USB_DEVICE_GENERIC_EventHandlerSet( USB_DEVICE_GENERIC_INDEX iGEN ,
                                                      USB_DEVICE_GENERIC_EVENT_HANDLER eventHandler,
                                                      uintptr_t userData )
{
    if( (iGEN < 0) || ( iGEN > USB_DEVICE_GENERIC_MAX_INSTANCES) )
    {
        return USB_DEVICE_GENERIC_RESULT_PARAMETER_INVALID ;
    }

    gUsbDeviceGenInstance[iGEN].appCallBack = eventHandler;
    gUsbDeviceGenInstance[iGEN].userData = userData;

    return USB_DEVICE_GENERIC_RESULT_OK;
}

USB_ERROR USB_DEVICE_GENERIC_AppCallbackSet(const USB_DEVICE_CALLBACK callBackFunc)
{
    /* Register a callback with device layer to get event notification (for end point 0) */
    return USB_DEVICE_EventCallBackSet(DRV_HANDLE_INVALID, callBackFunc);
}

/******************************************************************************
  Function:
    static void _USB_DEVICE_GENERIC_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iGEN,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData )

  Summary:
     Handles control transfers

  Description:


  Parameters:
    controlHandle - Control transfer handle
            iGEN  - Generic driver instance ID
    controlEvent  - Control event.
    pEventData    - Event data.

  Returns:
    USB_DEVICE_GENERIC_RESULT

*/

static void _USB_DEVICE_GENERIC_ControlTransferHandler(
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX iGEN,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * pEventData )
{
    USB_DEVICE_GENERIC_INSTANCE * genericInstance;
  
    genericInstance = (USB_DEVICE_GENERIC_INSTANCE *)&gUsbDeviceGenInstance[iGEN] ;

    if( genericInstance->appCallBack != NULL )
    {
        genericInstance->appCallBack( iGEN, controlHandle, controlEvent,(USB_DEVICE_GENERIC_EVENT_DATA *) pEventData,
                                       genericInstance->userData );
    }    
}


/******************************************************************************
  Function:
    void _USB_DEVICE_GENERIC_Deinitialize ( USB_DEVICE_GENERIC_INDEX iGEN )

  Summary:
    Deinitializes the generic driver.

  Description:


  Parameters:
    iGEN - Generic driver index.

  Returns:
 void

*/

void _USB_DEVICE_GENERIC_Deinitialize ( USB_DEVICE_GENERIC_INDEX iGEN )
{
    uint8_t count = 0;
    USB_DEVICE_GENERIC_INSTANCE * genericInstance = 
            (USB_DEVICE_GENERIC_INSTANCE *)&gUsbDeviceGenInstance[iGEN];

    for( count = 0; count < genericInstance->endpointCount; count ++)
    {
        USB_DEVICE_IRPCancelAll( genericInstance->usbClientHandle,
                                 genericInstance->endpoints[count] );
        USB_DEVICE_EndpointDisable( genericInstance->usbClientHandle,
                                    genericInstance->endpoints[count] );
    }

    genericInstance->endpointCount = 0;
}