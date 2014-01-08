/**************************************************************************
  Company:
    Microchip Technology Inc.

  File Name:
    usb_host.c

  Summary:
    This file contains implementations of both private and public functions
    of USB Device Layer.

  Description:
    This file contains the USB Host Layer Implementation
  **************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <math.h>
#include "system/common/sys_module.h"
#include "system_config.h"
#include "usb/usb_common.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global data
// *****************************************************************************
// *****************************************************************************
/* All the host controller and devices information */
 USB_HOST_OBJ gUsbHostInfo;
 
// *****************************************************************************
/* USB_HOST_CLIENT_STRUCT

  Summary:
    This structure has client information.

  Description:

  Remarks:

*/
/* USB host layer client object structure */


/* Client state of the instance */
 static USB_HOST_CLIENT_STRUCT usbHostClients
                            [USB_HOST_INSTANCES_NUMBER][USB_HOST_CLIENTS_NUMBER];


// *****************************************************************************
// *****************************************************************************
// Section: USB Host Layer Interface Routines
// *****************************************************************************
// *****************************************************************************

 // *****************************************************************************
/* Function:
      SYS_MODULE_OBJ USB_HOST_Initialize( const SYS_MODULE_INDEX index,
                                           const SYS_MODULE_INIT * const init )

  Summary:
    Initializes the USB Host layer instance for the specified instance index.

  Description:
    This routine initializes the USB Host Layer instance for the specified
    instance index, making it ready for clients to open and use it. The
    initialization data is specified by the init parameter. The intialization
    may fail if the number of host layer objects allocated are insufficient or
    if the specificed host layer instance is already initialized. This function
    also initializes the USB Module driver for host mode operation.  The init
    data structure thus contains information required for driver initialization.
    Note that initializing the Host Layer does not enable its operations. This
    must be done using USB_HOST_OperationEnable() function.

  Precondition:
    None.

  Input:
    index  - Identifier for the instance to be initialized

    init   - Pointer to a USB_HOST_INIT data structure containing data necessary
             to initialize the driver.

  Return:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, returns SYS_MODULE_OBJ_INVALID.

  Example:
    <code>

    // Initializes the host layer for use with PIC32MX devices.
    // We assume that the TPL table is already created and has two
    // entries.

    USB_HOST_TARGET_PERIPHERAL_LIST * tplTable;

    USB_HOST_INIT   usbHostInit;
    SYS_MODULE_OBJ  objectHandle;

    // Allocate an endpoint table
    uint8_t __attribute__((aligned(512))) endpointTable[USB_HOST_ENDPOINT_TABLE_SIZE];

    usbHostInit.moduleInit = SYS_MODULE_POWER_RUN_FULL;

    // The usbID member of the USB_HOST_INIT data structure
    // should be USB_ID_x for PIC32MX devices and should be
    // USBHS_ID_x PIC32MZ devices. Typical values are USB_ID_1
    // for PIC32MX and USBHS_ID_0 for PIC32MZ devices.

    usbHostInit.usbID           = USB_ID_1; //for PIC32MX devices
    usbHostInit.stopInIdle      = false;
    usbHostInit.suspendInSleep  = false;
    usbHostInit.endpointTable   = endpointTable;
    usbHostInit.interruptSource = INT_SOURCE_USB_1;
    usbHostInit.nTPLEntries     = 2
    usbHostInit.usbSpeed        = USB_SPEED_FULL;
    usbHostInit.tplTable        = tplTable;

    objectHandle = USB_HOST_Initialize(USB_HOST_0, (SYS_MODULE_INIT*)usbHostInit);
    if (SYS_MODULE_OBJ_INVALID == objectHandle)
    {
        // Handle error
    }
    </code>
  Remarks:
    This routine must be called before any other USB Host routine is called.

    This routine should only be called once during system initialization
    unless USB_HOST_Deinitialize is called to de-initialize the Host Layer
    instance. This routine will NEVER block for hardware access.
*/

SYS_MODULE_OBJ USB_HOST_Initialize(const SYS_MODULE_INDEX index,
                                   const SYS_MODULE_INIT * const initData)
{
    USB_HOST_INIT           *HostInit;
    USB_HOST_BUS_INFO       *hc;
    HC_DEVICE_ID             rootHubId;
    DRV_USB_INIT             drvUsbInit;
    SYS_MODULE_OBJ           drvObj;

      /* Copy init data into local variable. */
    HostInit = (USB_HOST_INIT *)initData;

    SYS_ASSERT( ( ( index >= 0 ) && ( index < USB_HOST_INSTANCES_NUMBER ) ),
                      " USB HOST Layer: Invalid index or value assigned to\
                        USB_HOST_INSTANCES_NUMBER ");


    SYS_ASSERT(gUsbHostInfo.businfo[index].inuse == false, "Host controller\
               instance already in use");

  
    /* Address mapping */
    hc =  &(gUsbHostInfo.businfo[index]);
    gUsbHostInfo.hostDeviceDriverinfo = HostInit->tplList;
    drvUsbInit.interruptSource = HostInit->interruptSource ;
    drvUsbInit.moduleInit = HostInit->moduleInit ;
    drvUsbInit.operationMode = USB_OPMODE_HOST ;
    drvUsbInit.stopInIdle = HostInit->stopInIdle ;
    drvUsbInit.suspendInSleep = HostInit->suspendInSleep ;
    drvUsbInit.usbID = HostInit->usbID ;
    drvUsbInit.operationSpeed = HostInit->usbSpeed ;
    drvUsbInit.endpointTable = HostInit->endpointTable;
   
   
    drvObj = DRV_USB_Initialize (index , ( SYS_MODULE_INIT* ) &drvUsbInit);
    SYS_ASSERT((drvObj != SYS_MODULE_OBJ_INVALID ),
                                    "USB Host Layer: Driver obj is NULL ");

    /* Open the controller */
    hc->hostControllerHandle= (DRV_HANDLE ) DRV_USB_Open (
                                    index ,
    DRV_IO_INTENT_EXCLUSIVE|DRV_IO_INTENT_NONBLOCKING|DRV_IO_INTENT_READWRITE );
  
    /* Assigned the default list to NULL */
    hc->attachdevicesCount = 0x00;
  
    /* Based on the speed support we have to allocate band width
     * for periodic transfer in a frame */
    if( HostInit->usbSpeed ==  USB_SPEED_FULL ||
            HostInit->usbSpeed ==  USB_SPEED_LOW)
    {
        hc->totalbandwidth =  USB_FULL_SPEED_BANDWIDTH;
        hc->availableBandwidth = USB_FULL_SPEED_BANDWIDTH;
    }
    else
    {
        hc->totalbandwidth =  USB_HIGH_SPEED_BANDWIDTH;
        hc->availableBandwidth = USB_HIGH_SPEED_BANDWIDTH;
    }
    /* To support multiple controllers will maintain
     * index number is controller ID */
    hc->hostcontrollerid  = index ;

    /* Register a callback with the driver. */
    DRV_USB_ClientEventCallBackSet(hc->hostControllerHandle,
                                   hc->hostcontrollerid,
                                   _USB_HOST_EventHandler);

    /* Enable USB controller */
    //DRV_USB_HOST_OperationEnable(hc->hostControllerHandle, true);

    /* Initialization complete then application open */
    hc->usbHostInstanceState = SYS_STATUS_READY ;
    
    
    /* Root Hub has only one port So may not have separate root hub driver */
    /* Root hul also one device so will enumerate the root hub and assign
     * address for root hub */
    /* Root hub responsabilities : Port suspend
     *                             port resume
     *                             port reset
     *                             port enable
     *                             port power   */
    /* We are sure that one controller is having only one port */
    /* To identify root hub port will assign address to the root hub port */
    rootHubId.hostcontrollerID =  hc->hostcontrollerid ;
    rootHubId.deviceID = _USB_HOST_GetNewAddress(rootHubId);
    /* Return handle as object */
    return(index);
}

// *****************************************************************************
/* Function:
    void USB_HOST_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specified instance of the USB Host Layer.

  Description:
    Deinitializes the specified instance of the USB Host Layer. This function
    will aslo deinitialize the USB Module driver and hence stop all USB Host
    related operation on the bus. All internal data structures will be reset.

  Precondition:
    Function USB_HOST_Initialize should have been called before calling this
    function.

  Parameters:
    object          - USB Host layer object handle, returned from the
                      USB_HOST_Initialize routine

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     //  Returned from USB_HOST_Initialize
    SYS_STATUS          status;


    USB_HOST_Deinitialize(object);

    status = USB_HOST_Status(object);
    if (SYS_MODULE_DEINITIALIZED != status)
    {
        // Check again later if you need to know
        // when the driver is deinitialized.
    }
    </code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize operation
    must be called before the Initialize operation can be called again. This
    routine will NEVER block waiting for hardware.
*/

void USB_HOST_Deinitialize(SYS_MODULE_OBJ usbHostObject)
{
    uint8_t client;
    USB_HOST_BUS_INFO       *hc;
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX)usbHostObject;
       /* Address mapping */
    hc =  &(gUsbHostInfo.businfo[index]);
  /*invalidate the handle. */
      hc->usbHostInstanceState =  SYS_STATUS_UNINITIALIZED;
     // Invalidate all clients.
    for( client = 0; client <= USB_HOST_CLIENTS_NUMBER ; client++ )
    {
        usbHostClients[index][client].clientState = DRV_CLIENT_STATUS_CLOSED ;
    }
}

// *****************************************************************************
/* Function:
    USB_HOST_HANDLE USB_HOST_Open( const SYS_MODULE_INDEX index,
                               const DRV_IO_INTENT    ioIntent )

  Summary:
    Opens the specified Host Layer instance and returns a handle to it

  Description:
    This routine opens the specified Host Layer instance and provides a handle
    that must be provided to all other client-level operations to identify the
    caller and the instance of the host layer. The host layer can be opened
    exclusively by a client by specifying the ioIntent as
    DRV_IO_INTENT_EXCLUSIVE. Any other flag settings will not have an effect on
    clients interaction with the host layer.

  Precondition:
    Function USB_HOST_Initialize must have been called before calling this
    function.

  Parameters:
    index       - Identifier for the object instance to be opened

    intent      - can be DRV_IO_INTENT_EXCLUSIVE which allows a client to open the
                  host layer exclusively. Any other flags are ignored.

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance).

    If an error occurs, the return value is USB_HOST_HANDLE_INVALID. Error can occur
    - if the number of client ojects allocated via USB_HOST_CLIENTS_NUMBER is
    insufficient.
    - if the client is trying to open the host layer but host layer has been opened
    exclusively by another client.
    - if the host layer instance being opened is not initialized or is
    invalid.

  Example:
    <code>
    USB_HOST_HANDLE handle;

    handle = USB_HOST_Open(USB_HOST_0, DRV_IO_INTENT_EXCLUSIVE);
    if (USB_HOST_HANDLE_INVALID == handle)
    {
        // Unable to open the driver
        // May be the driver is not initialized or the initialization
        // is not complete.
    }
    </code>

  Remarks:
    The handle returned is valid until the USB_HOST_Close routine is called.
    This routine will NEVER block waiting for hardware. This function is thread
    safe in a RTOS application. It should not be called in an ISR.
*/
USB_HOST_HANDLE USB_HOST_Open( const SYS_MODULE_INDEX index,
                               const DRV_IO_INTENT    intent )
{
    uint8_t i;
    USB_HOST_HANDLE retValue = USB_HOST_HANDLE_INVALID;
    USB_HOST_CLIENT_STRUCT* usbHostThisClient;
    USB_HOST_BUS_INFO       *hc;

         /* Address mapping */
    hc =  &(gUsbHostInfo.businfo[index]);

     /* Make sure the index is with in range. */
    SYS_ASSERT( ( ( index >= 0 ) && ( index <= USB_HOST_INSTANCES_NUMBER ) ),
                   " USB HOST Layer: Invalid index or value assigned to\
                     USB_HOST_INSTANCES_NUMBER ");

    if( intent & ( DRV_IO_INTENT_NONBLOCKING | DRV_IO_INTENT_SHARED ) )
    {
        /* The driver only supports this mode */
        SYS_ASSERT(false, "Host layer supports non blocking and\
                           shared access only");
        return USB_HOST_HANDLE_INVALID;
    }
    
    for(i = 0; i < USB_HOST_CLIENTS_NUMBER + 1; i++)
    {
        // Copy this local client.
        usbHostThisClient = (USB_HOST_CLIENT_STRUCT *)&usbHostClients[index][i];

        // Check for a free handle.
        if( usbHostThisClient->clientState == DRV_CLIENT_STATUS_CLOSED )
        {
            // Ready the client.
            usbHostThisClient->clientState = DRV_CLIENT_STATUS_READY;
            // Link the instance index.
            usbHostThisClient->usbHostInstance = hc;
            retValue = (DRV_HANDLE)usbHostThisClient;
            break;
        }    
    }

    // you may have to increase the value of USB_HOST_MAX_MAX_CLIENTS,
    // or close unused handles.
    SYS_ASSERT( ( DRV_HANDLE_INVALID != retValue ),
                "USB Host layer: No free client handles");
    return ( retValue ) ;
  
}

// *****************************************************************************
/* Function:
    SYS_STATUS USB_HOST_Status( SYS_MODULE_OBJ object )

  Summary:
    Gets the current status of the USB Host Layer.

  Description:
    This routine provides the current status of the USB Host Layer.

  Precondition:
    Function USB_HOST_Initialize should have been called before calling this
    function.

  Parameters:
    object          - USB Host Layer object handle, returned from the
                      USB_HOST_Initialize routine

  Returns:
    SYS_STATUS_READY          - Indicates that the USB Host layer is ready for
                                operations.

    SYS_STATUS_DEINITIALIZED  - Indicates that the driver has been
                                de-initialized

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from USB_HOST_Initialize
    SYS_STATUS          status;

    status = USB_HOST_Status(object);
    if (SYS_STATUS_READY == status)
    {
        // This means the driver can be opened using the
        // USB_HOST_Open() function.
    }
    </code>

  Remarks:
    None.
*/
SYS_STATUS USB_HOST_Status (SYS_MODULE_OBJ usbHostObject)
{
    USB_HOST_BUS_INFO       *hc;
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX)usbHostObject;
         /* Address mapping */
    hc =  &(gUsbHostInfo.businfo[index]);
    /*Return host instance state */
    return ( hc->usbHostInstanceState );
}

// *****************************************************************************
/* Function:
    void USB_HOST_Close( USB_HOST_HANDLE handle )

  Summary:
    Closes an opened-instance of the USB Host Layer.

  Description:
    This routine closes an opened-instance of the USB Host Layer, invalidating
    the handle.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

  Returns:
    None

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open

    USB_HOST_Close(handle);
    </code>

  Remarks:
    After calling this routine, the handle passed in "handle" must not be used
    with any of the remaining driver routines.  A new handle must be obtained by
    calling USB_HOST_Open before the caller may use the driver again.  This
    function is thread safe in a RTOS application.

    Note:
    Usually there is no need for the driver client to verify that the Close
    operation has completed.
*/

void USB_HOST_Close(USB_HOST_HANDLE hClient )
{
    USB_HOST_CLIENT_HANDLE usbHostClientHandle;
    /* Check the valid handle. */
    SYS_ASSERT( ( USB_HOST_HANDLE_INVALID != hClient ),"Invalid client handle");
    /* Close the handle. */
    usbHostClientHandle = (USB_HOST_CLIENT_HANDLE)hClient;
    /* close the handle. */
    usbHostClientHandle->clientState = DRV_CLIENT_STATUS_CLOSED;
}

// *****************************************************************************
/* Function:
    void USB_HOST_Tasks (SYS_MODULE_OBJ object );

  Summary:
    Maintains the USB Host's state machine. It manages the USB Module driver and
    responds to USB Module driver events.

  Description:
    This routine maintains the USB Host layer's state machine. It manages and
    the USB Module driver and responds to USB module driver events.  This
    function should be called from the SYS_Tasks() function.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  USB_HOST_Initialize)

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from USB_HOST_Initialize

    while (true)
    {
        USB_HOST_Tasks (object);

        // Do other tasks
    }
    </code>

  Remarks:
    This routine is normally not called directly by an application.
*/
void USB_HOST_Tasks   (SYS_MODULE_OBJ usbHostObject)

{
    uint8_t i;
    USB_HOST_BUS_INFO *hc;
    SYS_MODULE_INDEX index = (SYS_MODULE_INDEX) usbHostObject;
    uint8_t attachedDeviceCount;
    /* Address mapping */
    hc = &(gUsbHostInfo.businfo[index]);

    USB_HOST_EnumerateDevice( );

    attachedDeviceCount = hc->attachdevicesCount;
    if (attachedDeviceCount > 0) {
        /* call attached devices Tasks */
        for (i = 0; i < USB_HOST_MAX_DEVICE_SUPPORTED; i++) {
            if ((hc->attachedDevicesList[i].assigned)
                    && (hc->attachedDevicesList[i].
                    driver->task != NULL))
                hc->attachedDevicesList[i].driver->task();

        }
    }
}

// *****************************************************************************
/* Function:
    USB_ERROR USB_HOST_EventCallBackSet ( USB_HOST_HANDLE hostHandle,
        USB_HOST_EVENT_CALLBACK callback, uintptr_t context);

  Summary:
    Allows a client to identify an event handling function for the host layer
    to call back when host layer events are generated.

  Description:
    This function allows a client to identify an event handling function for the
    host layer to call back when host layer events are generated.

    The event handler should be set before the client the host layer operation
    is enabled. The event handler once set, persists until the client closes the
    driver or sets another event handler.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    Host Layer instance.

    USB_HOST_Open must have been called to obtain a valid opened Host Layer
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the host layer's
                   open routine

    callback     - Pointer to the event handler function.

    context      - The value of parameter will be passed back to the client
                   unchanged, when the eventHandler function is called.  It can
                   be used to identify any client specific data object that
                   identifies the instance of the client module (for example,
                   it may be a pointer to the client module's state structure).

  Returns:
    USB_ERROR_NONE - Callback function was registered successfully.
    USB_ERROR_PARAMETER_INVALID - Callback function was NULL or hostHandle
    is invalid.

  Example:
    <code>
    // myAppObj is an application specific state data object.
    MY_APP_OBJ myAppObj;

    USB_HOST_HANDLE usbHostHandle;

    // usbHostHandle is the handle returned
    // by the USB_HOST_Open function.

    // Client registers an event handler with host layer.

    USB_HOST_EventCallBackSet( usbHostHandle, APP_USBHostEventHandler,
                                     (uintptr_t)&myAppObj );

    USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler(uintptr_t context,
                USB_HOST_EVENTS event, void * eventData)
    {
        switch(event)
        {
            case USB_HOST_EVENT_UNSUPPORTED_DEVICE:
                break;
            ...
        }
        return(USB_HOST_EVENT_RESPONSE_NONE);
    }
    </code>

  Remarks:
    None.

*/

USB_ERROR USB_HOST_EventCallBackSet ( USB_HOST_HANDLE hostHandle,
    USB_HOST_EVENT_CALLBACK callback, uintptr_t context)
{
       USB_HOST_CLIENT_STRUCT* hostClientHandle;

    SYS_ASSERT( ( USB_HOST_HANDLE_INVALID != hostHandle ),
            "USB Device Layer: Handle passed is invalid" );

    hostClientHandle = (USB_HOST_CLIENT_STRUCT*)hostHandle;

    // Check if this handle is in a ready state.
    if(hostClientHandle->clientState == DRV_CLIENT_STATUS_READY)
    {
        // Register the callback function.
        hostClientHandle->callBackFunc = callback;

        // Return OK
         return (USB_ERROR_NONE);
    }
    else
    {
        // Return failed
        return (USB_ERROR_CLIENT_NOT_READY);
    }
}
// *****************************************************************************
/* Function:
    void USB_HOST_OperationEnable( USB_HOST_HANDLE handle )

  Summary:
    Enables host operation.

  Description:
    The function enables host operation. When enabled, the host layer can detect
    and enumerate attached devices. The application must call the
    USB_HOST_OperationIsEnabled() function to check if the operation has
    completed.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

  Returns:
    None

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open

    // Enabled host operation
    USB_HOST_OperationEnable(handle);

    // Wait till host operation is enabled.
    while(!USB_HOST_OperationIsEnabled(handle));

    </code>

  Remarks:
    It is recommended that only on host layer client call this function.
    Multiple host layer clients calling this may cause indeterministic behavior.

*/
void  USB_HOST_OperationEnable(USB_HOST_HANDLE hostHandle)
{
    USB_HOST_CLIENT_STRUCT* usbHostThisClient;
    USB_HOST_BUS_INFO       *hc;

    usbHostThisClient = ( USB_HOST_CLIENT_STRUCT* )hostHandle;
    hc = usbHostThisClient->usbHostInstance;
     /* Enable USB controller */
    DRV_USB_HOST_OperationEnable(hc->hostControllerHandle, true);
}

// *****************************************************************************
/* Function:
    void USB_HOST_OperationDisable( USB_HOST_HANDLE handle )

  Summary:
    Disabled host operation.

  Description:
    The function disables host operation. Disabling the host operation will cause
    the host to ignore attached device. All bus communication will be halted and
    USB bus will be suspended.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

  Returns:
    None

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open

    // Enabled host operation
    USB_HOST_OperationDisable(handle);

    </code>

  Remarks:
    This function may not be used in a typical USB Host application. One
    possible use could be in a case where a fatal system error has occurred.
    Once disabled, the Host operation must be enabled again using the
    USB_HOST_OperationEnable() function.

*/
void  USB_HOST_OperationDisable (USB_HOST_HANDLE hostHandle)
{
     USB_HOST_CLIENT_STRUCT* usbHostThisClient;
    USB_HOST_BUS_INFO       *hc;

    usbHostThisClient = ( USB_HOST_CLIENT_STRUCT* )hostHandle;
    hc = usbHostThisClient->usbHostInstance;
     /* Enable USB controller */
    DRV_USB_HOST_OperationEnable(hc->hostControllerHandle, false);

}

// *****************************************************************************
/* Function:
    bool USB_HOST_OperationIsEnabled( USB_HOST_HANDLE handle )

  Summary:
    Allows the application to check if the host operation is enabled.

  Description:
    The function allows the application to check if the host operation is
    enabled. This function should be called after the USB_HOST_OperationEnable()
    function is called to check if the operation has been enabled.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

  Returns:
    None.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open

    // Enabled host operation
    USB_HOST_OperationEnable(handle);

    // Wait till host operation is enabled.
    while(!USB_HOST_OperationIsEnabled(handle));
    </code>

  Remarks:
    None.
*/

bool  USB_HOST_OperationIsEnabled (USB_HOST_HANDLE hostHandle)
{
    USB_HOST_CLIENT_STRUCT* usbHostThisClient;
    USB_HOST_BUS_INFO       *hc;
    bool result;

    usbHostThisClient = ( USB_HOST_CLIENT_STRUCT* )hostHandle;
    hc = usbHostThisClient->usbHostInstance;
    result = DRV_USB_HOST_OperationIsEnabled(hc->hostControllerHandle);
    return ( result );
}

// *****************************************************************************
/* Function:
    void USB_HOST_DeviceSuspend ( USB_HOST_HANDLE handle, uint8_t address );

  Summary:
    Suspends the USB.

  Description:
    The function suspends the USB. If address is an address of a device that is
    connected directly to the USB module, this function will directly suspend
    the bus. If the address is an address of a device that is connected to the
    module via a hub, the USB Host layer will suspend the hub port to which this
    device is connected. The function only places a request to suspend the
    device. The application must use the USB_HOST_DeviceIsSuspended() function
    to check if the device suspend is complete.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

    address     - Address of the device.

  Returns:
    USB_ERROR_NONE  - The request was accepted successfully.
    USB_ERROR_PARAMETER_INVALID - The device address or handle is invalid.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open
    USB_ERROR result;

    // Suspend the device with address 2
    result = USB_HOST_Device(handle, 2);
    if(USB_ERROR_NONE == result)
    {
        // Wait till device is suspended.
        while(!USB_HOST_DeviceIsSuspended(handle, 2));
    }

    </code>

  Remarks:
    In cases where the device is connected directly to the USB Module, the bus
    suspend request will be serviced immediately. In cases where the device is
    connected to the USB module via a hub, the application must call the
    USB_HOST_DeviceIsSuspended() function to check if the device has been
    suspended.
*/

USB_ERROR   USB_HOST_DeviceSuspend (USB_HOST_HANDLE hostHandle,
                                    uint8_t deviceAddress)
{
    //To be implemented in next release
    return USB_ERROR_NONE;
}

// *****************************************************************************
/* Function:
    bool USB_HOST_DeviceIsSuspended ( USB_HOST_HANDLE handle, uint8_t address );

  Summary:
    Checks if the attached USB device has been suspended.

  Description:
    This function checks if the attached USB device has been suspended. This
    function can be called after calling the USB_HOST_DeviceSuspend() function
    to check if suspend request has been completed.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

    address     - Address of the device.

  Returns:
    true    - Device is suspended.
    false   - Device is not suspended or device address or handle is invalid.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open
    USB_ERROR result;

    // Suspend the device with address 2
    result = USB_HOST_Device(handle, 2);
    if(USB_ERROR_NONE == result)
    {
        // Wait till device is suspended.
        while(!USB_HOST_DeviceIsSuspended(handle, 2));
    }

    </code>

  Remarks:
    In cases where the device is connected directly to the USB Module, the bus
    suspend request will be serviced immediately. In cases where the device is
    connected to the USB module via a hub, the application must call the
    USB_HOST_DeviceIsSuspended() function to check if the device has been
    suspended.
*/
bool   USB_HOST_DeviceIsSuspended      (USB_HOST_HANDLE hostHandle, uint8_t deviceAddress)
{

    //To be implemented in next release
    return USB_ERROR_NONE;
}

// *****************************************************************************
/* Function:
    void USB_HOST_DeviceResume ( USB_HOST_HANDLE handle, uint8_t address );

  Summary:
    Resumes the USB.

  Description:
    The function resumes the USB. If address is an address of a device that is
    connected directly to the USB module, this function will directly resume
    the bus. If the address is an address of a device that is connected to the
    module via a hub, the USB Host layer will resume the hub port to which this
    device is connected. The function only places a request to resume the
    device. The application must use the USB_HOST_DeviceIsResumeed() function
    to check if the device resume is complete.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

    address     - Address of the device.

  Returns:
    USB_ERROR_NONE  - The request was accepted successfully.
    USB_ERROR_PARAMETER_INVALID - The device address or handle is invalid.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open
    USB_ERROR result;

    // Resume the device with address 2
    result = USB_HOST_Device(handle, 2);
    if(USB_ERROR_NONE == result)
    {
        // Wait till device is resumed.
        while(!USB_HOST_DeviceIsResumed(handle, 2));
    }

    </code>

  Remarks:
    In cases where the device is connected directly to the USB Module, the bus
    resume request will be serviced immediately. In cases where the device is
    connected to the USB module via a hub, the application must call the
    USB_HOST_DeviceIsResumed() function to check if the device has been
    resumed.
*/

USB_ERROR USB_HOST_DeviceResume (USB_HOST_HANDLE hostHandle,
                                 uint8_t deviceAddress)
{

    //To be implemented in next release
    return USB_ERROR_NONE;
}


// *****************************************************************************
/* Function:
    bool USB_HOST_DeviceIsResumed ( USB_HOST_HANDLE handle, uint8_t address );

  Summary:
    Checks if the attached USB device has been resumed.

  Description:
    This function checks if the attached USB device has been resumed. This
    function can be called after calling the USB_HOST_DeviceResume() function
    to check if resume request has been completed.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

    address     - Address of the device.

  Returns:
    true    - Device is resumed.
    false   - Device is not resumed or device address or handle is invalid.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open
    USB_ERROR result;

    // Resume the device with address 2
    result = USB_HOST_DeviceResume(handle, 2);
    if(USB_ERROR_NONE == result)
    {
        // Wait till device is resumed.
        while(!USB_HOST_DeviceIsResumed(handle, 2));
    }

    </code>

  Remarks:
    In cases where the device is connected directly to the USB Module, the bus
    resume request will be serviced immediately. In cases where the device is
    connected to the USB module via a hub, the application must call the
    USB_HOST_DeviceIsResumed() function to check if the device has been
    resumed.
*/

bool USB_HOST_DeviceIsResumed(USB_HOST_HANDLE hostHandle, uint8_t deviceAddress)
{

    //To be implemented in next release
    return USB_ERROR_NONE;
}


// *****************************************************************************
/* Function:
    USB_ERROR USB_HOST_DeviceInformationGet ( USB_HOST_HANDLE handle,
            uint8_t address, USB_DEVICE_INFORMATION * deviceInformation );

  Summary:
    Returns select information about the attached device.

  Description:
    This function returns select information about the attached device. The
    application may use this information to update it display or for other
    application purposes. The device information is returned in the
    deviceInformation data structure.

  Precondition:
    The USB_HOST_Initialize routine must have been called for the specified
    USB Host Layer instance.

  Parameters:
    handle       - A valid open-instance handle, returned from the Host Layers's
                   open routine

    address     - Address of the device.

    deviceInformation - pointer to a data structure where the device
                        information will be stored

  Returns:
    USB_ERROR_NONE - Function was successful.
    USB_ERROR_PARAMETER_INVALID - Device address or host handle is invalid or
    deviceInformation pointer is NULL.

  Example:
    <code>
    USB_HOST_HANDLE handle;  // Returned from USB_HOST_Open
    USB_ERROR result;
    USB_DEVICE_INFORMATION deviceInfo;

    // Get informationa about attached device with address 2
    result = USB_HOST_DeviceInformationGet(handle, 2, &deviceInfo);
    if(USB_ERROR_NONE == result)
    {
        // Display the string descriptor of the attached device.
        APP_PrintToDisplay(deviceInformation.stringDesciptor);
    }

    </code>

  Remarks:
    None.
*/

USB_ERROR USB_HOST_DeviceInformationGet(USB_HOST_HANDLE hostHandle,
                                        uint8_t deviceAddress,
                                        USB_DEVICE_INFORMATION * deviceInfo)
{
    HC_DEVICE_ID Id ;
    uint8_t   count;
    USB_DEVICE_INFO *device;
    Id.deviceID = deviceAddress;
    Id.hostcontrollerID = hostHandle;
    device = _USB_HOST_GetDeviceInfo( Id );
    if( device == NULL )
    {
        return USB_ERROR_DEVICE_FUNCTION_NOT_CONFIGURED;
    }
    deviceInfo->vid =  device->vendorid;
    deviceInfo->pid =  device->productid;
    for( count = 0 ; count < USB_HOST_DEVICE_INFORMATION_STRING_LENGTH; count++ )
    {
    deviceInfo->stringDescriptor[count] = device->ManufacturerName[count];
    }

    return USB_ERROR_NONE;
}




/*****************************************************************************/
/* Function:
    USB_ERROR USB_HOST_IRPSubmit (USB_HOST_PIPE_HANDLE PipeHandle ,
                                     USB_HOST_IRP *irp )
  Summary:
    It configure the hardware and transfer the data

  Description:
      Send request to the Host controller driver

  Parameters:
    USB_HOST_IRP      - i/o request packet from class drivers

  Returns:
    USB_HOST_STATUS
*/

USB_ERROR USB_HOST_IRPSubmit (USB_HOST_PIPE_HANDLE PipeHandle ,
                                     USB_HOST_IRP *irp)
{
    USB_ERROR status;
    DRV_USB_HOST_PIPE_HANDLE hPipe;
    /*default status*/
    status = USB_ERROR_NONE;

    hPipe = (DRV_USB_HOST_PIPE_HANDLE) PipeHandle;

    /* Valied endpoint or not */
    if (PipeHandle != (DRV_USB_HOST_PIPE_HANDLE) NULL && irp != NULL)
    {
        /* pass the info to HCD */
        status = DRV_USB_HOST_IRPSubmit(hPipe, irp);
    }
    else
    {
        /* pipe handle is not valid*/
        return USB_ERROR_ENDPOINT_NOT_CONFIGURED;
    }
    return status;
}
// *****************************************************************************

/* Function:
    USB_ERROR USB_HOST_IRPCancel ( USB_HOST_PIPE_HANDLE PipeHandle ,
                               USB_HOST_IRP *irp )

  Summary:
      cancel irps

  Description:
      API provides cancel the irp related to this pipe

  Parameters:
    USB_HOST_PIPE_HANDLE      - pipe information
    USB_HOST_IRP              *irp

  Returns:
    USB_ERROR
 */
USB_ERROR USB_HOST_IRPCancel(USB_HOST_PIPE_HANDLE PipeHandle,
                             USB_HOST_IRP *irp)
{
    USB_ERROR status;
    DRV_USB_HOST_PIPE_HANDLE hPipe;
    /* default state */
    status = USB_ERROR_NONE;

    hPipe = (DRV_USB_HOST_PIPE_HANDLE) PipeHandle;

    /*validate the pipe handle and irp*/
    if(PipeHandle != (USB_HOST_PIPE_HANDLE) NULL && irp != (USB_HOST_IRP *)NULL)
    {
         /* pass the info to HCD */
        DRV_USB_HOST_IRPCancel(irp);
    }
    return status;
}

// *****************************************************************************
/* Function:
    USB_HOST_PIPE_HANDLE  USB_HOST_PipeSetup( HC_DEVICE_ID id ,
                                          USB_ENDPOINT_DESCRIPTOR *endPointDesc,
                                          uint8_t speed )

  Summary:
         Create pipe for transfer the data 

  Description:
        Function controller can setup the pipe for transfer data

  Parameters:
    HC_DEVICE_ID                id              //Hc id + Device id
    USB_ENDPOINT_DESCRIPTOR     *endPointDesc // Endpoint desc information
     uint8_t                    speed        // Speed of the device

  Returns:
    USB_HOST_PIPE_HANDLE
*/

USB_HOST_PIPE_HANDLE  USB_HOST_PipeSetup( HC_DEVICE_ID id ,
                                          USB_ENDPOINT_DESCRIPTOR *endPointDesc,
                                          uint8_t speed )
 {
    USB_HOST_PIPE_HANDLE pipeHandle;
    USB_ENDPOINT endpointAndDirection;
    USB_DEVICE_INFO *deviceInfo;
    USB_HOST_BUS_INFO *busInfo;
    USB_HOST_HANDLE hostControllerHandle;
    uint8_t deviceAddress;
    uint8_t transferType;
    uint8_t interval;
    uint16_t maxPacketSize;

     /* bus information */
    busInfo = _USB_HOST_GetBusInfo(id);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(id);
    /* hcHandle is required to talk HCD */
    hostControllerHandle = deviceInfo->hostControllerHandle;
    /* Device Address */
    deviceAddress = id.deviceID;
    /* Transfer type */
    transferType = (endPointDesc->bmAttributes)& 0x03;
    /* Interval for periodic transfers */
    if ( transferType ==  USB_TRANSFER_TYPE_BULK )
    {
        /* Bulk endpoints we ignore binterval value reported by endpoint descriptor*/
        interval = 0x00;
    }
    else
    {
        interval = endPointDesc->bInterval;
    }
    /* Endpoint maxpacket size */
    maxPacketSize = endPointDesc->wMaxPacketSize;
    /* Endpoint address and direction */
    endpointAndDirection = USB_ENDPOINT_AND_DIRECTION(endPointDesc->dirn,
                                            endPointDesc->bEndpointAddress);
    /* Control transfers pipe is created */
    if (transferType == USB_TRANSFER_TYPE_CONTROL)
    {
        pipeHandle = deviceInfo->controlPipeHandle;
    }
    else
   {
        /* Bandwidth available condition */
        #if 0
        if ( busInfo->availableBandwidth < maxPacketSize )
            return -1;
        else 
            busInfo->availableBandwidth -= maxPacketSize;
        #endif
        /* New pipe created */
        pipeHandle = DRV_USB_HOST_PipeSetup(hostControllerHandle, deviceAddress,
            endpointAndDirection,0,0, transferType, interval, maxPacketSize, speed);
    }
    /* Return pipe handle to the host function driver */
    return (USB_HOST_PIPE_HANDLE) pipeHandle;
}

// *****************************************************************************
/* Function:
    USB_HOST_PipeClose(USB_HOST_PIPE_HANDLE PipeHandle)

  Summary:
     Close the pipe

  Description:
     After detach the device we have close all the pipes related to the device.

  Parameters:
    USB_HOST_PIPE_HANDLE          PipeHandle          //Pipe handle

  Returns:
    USB_HOST_STATUS
*/

 USB_ERROR USB_HOST_PipeClose(USB_HOST_PIPE_HANDLE PipeHandle)
 {
     USB_ERROR status;
     DRV_USB_HOST_PIPE_HANDLE hpipe;
     status = USB_ERROR_NONE;
     hpipe = (DRV_USB_HOST_PIPE_HANDLE ) PipeHandle;
     /* validate pipe handle */
      if(hpipe != (DRV_USB_HOST_PIPE_HANDLE ) NULL)
     {
        /* close the pipe */
        DRV_USB_HOST_PipeClose ( hpipe);
        return status;
      }
      else
      {
          status = USB_ERROR_HOST_PIPE_INVALID;
      }
      return status;
}

 // *****************************************************************************
/* Function:
    USB_HOST_STATUS USB_HOST_SetInterface( HC_DEVICE_ID deviceId,
                   uint8_t interfaceNumber, uint8_t alrernateSettingNumber)

  Summary:
    Set Interface 

  Description:
    Function driver can set the interface based on alternatesetting

  Parameters:
    HC_DEVICE_ID                deviceId // HC id + Device id
    uint8_t                     interfaceNumber
    uint8_t                     alrernateSettingNumber

  Returns:
    USB_HOST_STATUS
*/
USB_ERROR USB_HOST_SetInterface( HC_DEVICE_ID deviceId,
                   uint8_t interfaceNumber, uint8_t alrernateSettingNumber)
{
    USB_HOST_STATUS status;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *deviceInfo;
    USB_CONFIGURATION_INFO *configurationInfo;
    USB_ALTERNATE_SETTING_INFO *altSettingInfo;
   
    status = USB_HOST_SUCCESS;
    /* bus information */
    busInfo = _USB_HOST_GetBusInfo(deviceId);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(deviceId);

    if(busInfo == NULL || deviceInfo == NULL )
        return USB_HOST_ERROR;
    /* get configuration information */
    configurationInfo = &(deviceInfo->configDescriptorInfo
                                    [deviceInfo->activeConfigurationNumber]);
    /* get alternate setting information */
    altSettingInfo = &(configurationInfo->interfaceInfo[interfaceNumber].
                            alternateSettingInfo[alrernateSettingNumber]);

    /* set feature */
    /* Fill setup packet for set interface */
    deviceInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
                                 USB_SETUP_TYPE_STANDARD |
                                 USB_SETUP_RECIPIENT_INTERFACE;
    deviceInfo->setupPacket[1] = USB_REQUEST_SET_INTERFACE;
    deviceInfo->setupPacket[2] = alrernateSettingNumber; // Index
    deviceInfo->setupPacket[3] = 0; // Type
    deviceInfo->setupPacket[4] = interfaceNumber;
    deviceInfo->setupPacket[5] = 0;
    deviceInfo->setupPacket[6] = 0; //length
    deviceInfo->setupPacket[7] = 0;

    /* Fill irp */
    deviceInfo->controlIrp.data = NULL;
    deviceInfo->controlIrp.setup = deviceInfo->setupPacket;
    deviceInfo->controlIrp.size = 0;
    deviceInfo->controlIrp.callback=(USB_HOST_IRP_CALLBACK)_setupPacketCallback;
    deviceInfo->deviceState = STATE_CONFIGURING;
    deviceInfo->deviceSubState = SUBSTATE_SET_INTERFACE;
    deviceInfo->deviceSubSubState = SUBSUBSTATE_SEND_SET_INTERFACE;
    // Move to state machine
    /* DRV_USB_HOST_IRPSubmit(deviceInfo->controlPipeHandle,
                                &deviceInfo->controlIrp); */
    return status;
}
 // *****************************************************************************
/* Function:
   USB_HOST_STATUS USB_HOST_FindEndpoint ( USB_HOST_DRIVER_QUERY *query,
                                        USB_ENDPOINT_DESCRIPTOR **endPointDesc)

  Summary:
    Find endpoint desc

  Description:
    Function driver can get the Endpoint information

  Parameters:
    USB_HOST_DRIVER_QUERY *query,
     USB_ENDPOINT_DESCRIPTOR **endPointDesc


  Returns:
    USB_HOST_STATUS
*/
USB_ERROR USB_HOST_FindEndpoint ( USB_HOST_DRIVER_QUERY *query,
                                        USB_ENDPOINT_DESCRIPTOR **endPointDesc)
{
    USB_HOST_STATUS status;
    USB_CONFIGURATION_INFO *cfgInfo;
    uint8_t interfaceNumber;
    USB_ENDPOINT endpointAndDirection;
    USB_ALTERNATE_SETTING_INFO *alternateSettingInfo;
    uint8_t endpointAddress, endpointType, endpointDirection;
    //uint8_t direction;
    uint8_t addressMatch = 0;

    status = USB_ERROR_NONE;
    if (query == NULL || endPointDesc == NULL)
        return USB_HOST_INVALID_ARG;
    /* Get active configuration information */
    cfgInfo = _USB_HOST_GetConfigurationInfo(query->id,
                                            query->configurationNumber);
    /* Interface Number */
    interfaceNumber = query->interfaceNumber;
    /* Check the interface number is valid */
    if (interfaceNumber >= cfgInfo->configurationDescriptor->bNumInterfaces)
        return USB_HOST_MAX_INTERFACES_INVALID;
    /* Get alternate setting information */
    alternateSettingInfo = &(cfgInfo->interfaceInfo[query->interfaceNumber].
                        alternateSettingInfo[query->alternateSettingNumber]);
    /* Endpoint information */
    endpointAddress = query->endpointAddress;
    endpointType = query->endpointType;
    endpointDirection = query->endpointDirection;
      /* Endpoint address and direction */
    endpointAndDirection = USB_ENDPOINT_AND_DIRECTION(endpointDirection,
                                            endpointAddress);

    for (addressMatch = 0; addressMatch < alternateSettingInfo->
                        interfaceDescriptor->bNumEndPoints; addressMatch++)
    {
        if (query->flags & USB_MATCH_ENDPOINT_TYPE)
        {
            if (endpointType != (alternateSettingInfo->endpointInfo
                    [addressMatch].endpointDescriptor->bmAttributes & 0x0F))
                continue;
        }
        if (query->flags & USB_MATCH_ENDPOINT_DIRECTION)
        {
            if (endpointDirection != (alternateSettingInfo->endpointInfo
                    [addressMatch].endpointDescriptor->dirn))
                continue;
        }
        if(addressMatch >= alternateSettingInfo->interfaceDescriptor->
                           bNumEndPoints  )
        {
            return  USB_HOST_MAX_ENDPOINT_INVALID;
        }
        /* Endpoint found!  */
         *endPointDesc = alternateSettingInfo->endpointInfo[addressMatch].
                                               endpointDescriptor;
    }
    return status;
}
 // *****************************************************************************
/* Function:
    USB_HOST_STATUS USB_HOST_FindInterface ( USB_HOST_DRIVER_QUERY *query,
                                      USB_INTERFACE_DESCRIPTOR **interfaceDesc)

  Summary:
    Find interface descriptor

  Description:
    Function driver can get the interface descriptor based on query.

  Parameters:
    USB_HOST_DRIVER_QUERY               *query,
     USB_INTERFACE_DESCRIPTOR           **interfaceDesc


  Returns:
    USB_HOST_STATUS
*/
 USB_ERROR USB_HOST_FindInterface ( USB_HOST_DRIVER_QUERY *query,
                                      USB_INTERFACE_DESCRIPTOR **interfaceDesc)
 {
    USB_CONFIGURATION_INFO *cfgInfo;
    uint8_t totalInterfaces;
    uint8_t altSettingNumber;
    //USB_ALTERNATE_SETTING_INFO *alternateSettingInfo;
    USB_INTERFACE_DESCRIPTOR *interface;
    uint8_t i;
     USB_HOST_STATUS status;

    /* Get Active configuration information*/
    cfgInfo = _USB_HOST_GetConfigurationInfo(query->id, query->configurationNumber);
    /* Find No of interfaces in alternate setting */
    totalInterfaces = cfgInfo->configurationDescriptor->bNumInterfaces;
    /* Alternate setting number */
    altSettingNumber = query->alternateSettingNumber;
    status = USB_HOST_MAX_INTERFACES_INVALID;
    for (i = query->interfaceNumber; i < totalInterfaces; i++)
    {
        for (;altSettingNumber < USB_HOST_MAX_ALTERNATE_SETTINGS; altSettingNumber++)
        {
            interface = cfgInfo->interfaceInfo[i].
                    alternateSettingInfo[altSettingNumber].interfaceDescriptor;

            if (query->interfaceClass != interface->bInterfaceClass)
                continue;
            if (query->interfaceSubClass != interface->bInterfaceSubClass)
                continue;
            if (query->interfaceProtocol != interface->bInterfaceProtocol)
                continue;
            *interfaceDesc = interface;
            status = USB_ERROR_NONE;
            break;
        }
    }
    return status;
 }
// *****************************************************************************
/*
 *  Function:
    void  USB_HOST_displayAttachedDevicesList( uint8_t *USB_HOST_deviceList)

  Summary:
    This function Display Attached Device Driver names

  Description:
    Use for Demos

  Precondition:
    None.

  Parameters:
         uint8_t *USB_HOST_deviceList   // pointer to display..
   Returns:
        None

  Remarks:

 */
#if 0
void  USB_HOST_displayAttachedDevicesList( uint8_t *USB_HOST_deviceList)
{
    uint8_t count , attachedDeviceCount;
    uint8_t i;
     /* multiple controllers  */
     attachedDeviceCount = gUsbHostInfo.businfo[0].attachdevicesCount;
     for( count= 0 ; count < attachedDeviceCount ; count++ )
     {
         if(gUsbHostInfo.businfo[0].
                 attachedDevicesList[count].driver != NULL)
         {
         /* Display the Names */
         for( i = 0 ; i < 4 ; i ++ )
         USB_HOST_deviceList[ (count * 4) +i] = gUsbHostInfo.businfo[0].
                 attachedDevicesList[count].driver->driverName[i] ;
         }
     }
}
#endif 
// *****************************************************************************
/*
 *  Function:
    USB_HOST_STATUS   USB_HOST_EndpointHalt (USB_HOST_PIPE pipeHandle )

  Summary:
        setup packet with set feature of halt endpoint

  Description:
    Use for prevent the device from deenumerated 

  Precondition:
    None.

  Parameters:
         USB_HOST_PIPE         pipeHandle  //pipe info
   Returns:
        USB_HOST_STATUS

  Remarks:

 */
USB_HOST_STATUS   USB_HOST_EndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )
{
    USB_HOST_STATUS status;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *deviceInfo;

    /* prevent the device from deenumerated */
    status = USB_HOST_SUCCESS;
    /* bus information */
    busInfo = _USB_HOST_GetBusInfo(deviceId);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(deviceId);

    if(busInfo == NULL || deviceInfo == NULL )
        return USB_HOST_ERROR;

    /* set feature */
    /* Fill setup packet for set interface */
    deviceInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
                                 USB_SETUP_TYPE_STANDARD |
                                 USB_SETUP_RECIPIENT_ENDPOINT;
    deviceInfo->setupPacket[1] = USB_REQUEST_SET_FEATURE;
    deviceInfo->setupPacket[2] = USB_FEATURE_SELECTOR_ENDPOINT_HALT; // Index
    deviceInfo->setupPacket[3] = 0; // Type
    deviceInfo->setupPacket[4] = endpointNumber;
    deviceInfo->setupPacket[5] = 0;
    deviceInfo->setupPacket[6] = 0; //length
    deviceInfo->setupPacket[7] = 0;

    /* Fill irp */
    deviceInfo->controlIrp.data = NULL;
    deviceInfo->controlIrp.setup = deviceInfo->setupPacket;
    deviceInfo->controlIrp.size = 0;
    deviceInfo->controlIrp.callback=(USB_HOST_IRP_CALLBACK)_setupPacketCallback;
    //deviceInfo->deviceState = STATE_CONFIGURING;
    //deviceInfo->deviceSubState = SUBSTATE_SET_INTERFACE;
    //deviceInfo->deviceSubSubState = SUBSUBSTATE_SEND_SET_INTERFACE;
  
     DRV_USB_HOST_IRPSubmit(deviceInfo->controlPipeHandle,
                                &deviceInfo->controlIrp);
     // Give some time delay to settle down for set feature
    return status;
 }
// *****************************************************************************
/*
 *  Function:
    USB_HOST_STATUS   USB_HOST_ClearEndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )

  Summary:
        setup packet with set feature of clear halt endpoint

  Description:
    Use for prevent the device from deenumerated and clear the halt

  Precondition:
    None.

  Parameters:
         HC_DEVICE_ID                   deviceId
         uint8_t                        endpointNumber
   Returns:
        USB_HOST_STATUS

  Remarks:

 */
USB_HOST_STATUS   USB_HOST_ClearEndpointHalt ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )
{
    USB_HOST_STATUS status;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *deviceInfo;

    /* prevent the device from deenumerated */
    /* clear the halt */
    status = USB_HOST_SUCCESS;
    /* bus information */
    busInfo = _USB_HOST_GetBusInfo(deviceId);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(deviceId);

    if(busInfo == NULL || deviceInfo == NULL )
        return USB_HOST_ERROR;

    /* set feature */
    /* Fill setup packet for set interface */
    deviceInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
                                 USB_SETUP_TYPE_STANDARD |
                                 USB_SETUP_RECIPIENT_ENDPOINT;
    deviceInfo->setupPacket[1] = USB_REQUEST_CLEAR_FEATURE;
    deviceInfo->setupPacket[2] = USB_FEATURE_SELECTOR_ENDPOINT_HALT; // Index
    deviceInfo->setupPacket[3] = 0; // Type
    deviceInfo->setupPacket[4] = endpointNumber;
    deviceInfo->setupPacket[5] = 0;
    deviceInfo->setupPacket[6] = 0; //length
    deviceInfo->setupPacket[7] = 0;

    /* Fill irp */
    deviceInfo->controlIrp.data = NULL;
    deviceInfo->controlIrp.setup = deviceInfo->setupPacket;
    deviceInfo->controlIrp.size = 0;
    deviceInfo->controlIrp.callback=(USB_HOST_IRP_CALLBACK)_setupPacketCallback;
    //deviceInfo->deviceState = STATE_CONFIGURING;
    //deviceInfo->deviceSubState = SUBSTATE_SET_INTERFACE;
    //deviceInfo->deviceSubSubState = SUBSUBSTATE_SEND_SET_INTERFACE;

     DRV_USB_HOST_IRPSubmit(deviceInfo->controlPipeHandle,
                                &deviceInfo->controlIrp);
     // Give some time delay to settle down for set feature
    return status;
 }


// ***************************************************************************
/*
 *  Function:
    USB_HOST_STATUS   USB_HOST_IsEndpointHalted ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )

  Summary:
        setup packet with find status of endpoint

  Description:
    Use for find the status of endpoint.

  Precondition:
    None.

  Parameters:
         HC_DEVICE_ID                   deviceId
         uint8_t                        endpointNumber
   Returns:
        USB_HOST_STATUS

  Remarks:

 */
bool   USB_HOST_IsEndpointIsHalted ( HC_DEVICE_ID deviceId ,
                                          uint8_t endpointNumber )
{
    USB_ERROR status;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *deviceInfo;

    /* prevent the device from deenumerated */
    /* clear the halt */
    status = USB_HOST_SUCCESS;
    /* bus information */
    busInfo = _USB_HOST_GetBusInfo(deviceId);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(deviceId);

    if(busInfo == NULL || deviceInfo == NULL )
        return USB_HOST_ERROR;

    /* set feature */
    /* Fill setup packet for set interface */
    deviceInfo->setupPacket[0] = USB_SETUP_DIRN_DEVICE_TO_HOST |
                                 USB_SETUP_TYPE_STANDARD |
                                 USB_SETUP_RECIPIENT_ENDPOINT;
    deviceInfo->setupPacket[1] = USB_REQUEST_GET_STATUS;
    deviceInfo->setupPacket[2] = 0x00; // Index
    deviceInfo->setupPacket[3] = 0; // Type
    deviceInfo->setupPacket[4] = endpointNumber;
    deviceInfo->setupPacket[5] = 0;
    deviceInfo->setupPacket[6] = 2; //length
    deviceInfo->setupPacket[7] = 0;

    /* Fill irp */
    deviceInfo->controlIrp.data = &( deviceInfo->devicestatus );
    deviceInfo->controlIrp.setup = deviceInfo->setupPacket;
    deviceInfo->controlIrp.size = 2;
    deviceInfo->controlIrp.callback=(USB_HOST_IRP_CALLBACK)_setupPacketCallback;
    //deviceInfo->deviceState = STATE_CONFIGURING;
    //deviceInfo->deviceSubState = SUBSTATE_SET_INTERFACE;
    //deviceInfo->deviceSubSubState = SUBSUBSTATE_SEND_SET_INTERFACE;

     DRV_USB_HOST_IRPSubmit(deviceInfo->controlPipeHandle,
                                &deviceInfo->controlIrp);
     /* last bit shows the state of endpoint*/
     while( 1 )
     {
        if( deviceInfo->controlIrp.status == USB_HOST_IRP_STATUS_COMPLETED )
            break;

     }
     if( deviceInfo->devicestatus & 0x1)
         return true;
     else
         return false;
  
 }
// ***************************************************************************
/*
 *  Function:
    USB_HOST_STATUS   USB_HOST_getDeviveStatus ( HC_DEVICE_ID deviceId ,
                                          uint16_t *status )

  Summary:
        setup packet with find status of device

  Description:
    Use for find the status of device

  Precondition:
    None.

  Parameters:
         HC_DEVICE_ID                   deviceId
         uint16_t*                      device status
   Returns:
        USB_HOST_STATUS

  Remarks:

 */
USB_HOST_STATUS   USB_HOST_getDeviveStatus ( HC_DEVICE_ID deviceId ,
                                          uint16_t *devicestatus )
{
    USB_HOST_STATUS status;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *deviceInfo;

    /* prevent the device from deenumerated */
    /* clear the halt */
    status = USB_HOST_SUCCESS;
    /* bus information */
    busInfo = _USB_HOST_GetBusInfo(deviceId);
    /* device information */
    deviceInfo = _USB_HOST_GetDeviceInfo(deviceId);

    if(busInfo == NULL || deviceInfo == NULL )
        return USB_HOST_ERROR;

    /* set feature */
    /* Fill setup packet for set interface */
    deviceInfo->setupPacket[0] = USB_SETUP_DIRN_DEVICE_TO_HOST |
                                 USB_SETUP_TYPE_STANDARD |
                                 USB_SETUP_RECIPIENT_DEVICE  ;
    deviceInfo->setupPacket[1] = USB_REQUEST_GET_STATUS;
    deviceInfo->setupPacket[2] = 0x00; // Index
    deviceInfo->setupPacket[3] = 0; // Type
    deviceInfo->setupPacket[4] = 0x00;
    deviceInfo->setupPacket[5] = 0;
    deviceInfo->setupPacket[6] = 2; //length
    deviceInfo->setupPacket[7] = 0;

    /* Fill irp */
    deviceInfo->controlIrp.data = & (deviceInfo->devicestatus);
    deviceInfo->controlIrp.setup = deviceInfo->setupPacket;
    deviceInfo->controlIrp.size = 2;
    deviceInfo->controlIrp.callback=(USB_HOST_IRP_CALLBACK)_setupPacketCallback;
    //deviceInfo->deviceState = STATE_CONFIGURING;
    //deviceInfo->deviceSubState = SUBSTATE_SET_INTERFACE;
    //deviceInfo->deviceSubSubState = SUBSUBSTATE_SEND_SET_INTERFACE;
   
     DRV_USB_HOST_IRPSubmit(deviceInfo->controlPipeHandle,
                                &deviceInfo->controlIrp);
    
      *devicestatus = deviceInfo->devicestatus;
      return status;
 }
/*************************************************************************/

/* Function:
    USB_HOST_STATUS USB_HOST_DeEnumerate_Device ( HC_DEVICE_ID  deviceid )

  Summary:
      DeEnumerates newly disconnected device

  Description:
      This function deenumerate newly disconnected device ,All the resourcess
 allocated for the device has to be removed

  Parameters:
   HC_DEVICE_ID             -  device id

  Returns:
    None
*/
USB_HOST_STATUS USB_HOST_DeEnumerate_Device( HC_DEVICE_ID  deviceID )
{
     USB_HOST_STATUS  status;
     USB_HOST_BUS_INFO *busInfo;
     USB_DEVICE_INFO *deviceInfo;
     USB_HOST_DRIVER *interfaceDriver;
     uint8_t  interfaceNumber;
     status =  USB_HOST_SUCCESS;
     /* Get  bus information*/
     busInfo = _USB_HOST_GetBusInfo(deviceID);
     /* Get parent device information */
     deviceInfo = _USB_HOST_GetDeviceInfo(deviceID );

     if(deviceInfo == NULL)
         return  -1;
     if( deviceInfo->driver == NULL )
     {
          /* Release address */
     _USB_HOST_FreeAddress (busInfo , deviceID.deviceID);
     deviceInfo->deviceId.deviceID = 0x00;
     deviceInfo->assigned = 0x00;
     gUsbHostInfo.businfo[0].attachdevicesCount --;
     return status;
     }
     /* Disconnect the driver */
     if(deviceInfo->driver)
     {
        /* if the driver is class or vendor driver */
        deviceInfo->driver->deInitializeDriver(deviceID);
     }
     else
     {
         /* disconnect the interface driver */
         for(interfaceNumber = 0 ; interfaceNumber <= USB_HOST_MAX_INTERFACES ;
                 interfaceNumber++ )
         {
             interfaceDriver = deviceInfo->configDescriptorInfo
                     [deviceInfo->activeConfigurationNumber].
                     interfaceInfo[interfaceNumber].interfaceDriver;
             /* De initialize the interface driver */
             interfaceDriver->deInitializeDriver(deviceID);
         }
     }
     // pipes are availabele we have to close all the pipes
     USB_HOST_PipeClose( deviceInfo->controlPipeHandle );
     USB_HOST_PipeClose( deviceInfo->defaultPipeHandle );
     /* Release address */
     _USB_HOST_FreeAddress (busInfo , deviceID.deviceID);
     deviceInfo->deviceId.deviceID = 0x00;
     deviceInfo->assigned = 0x00;
     gUsbHostInfo.businfo[0].attachdevicesCount --;
     /* Free allocated buffer */
     return status;
}

/* Function:
    void USB_HOST_EnumerateDevice()

  Summary:
      Enumerates newly connected device and state machine

  Description:
      This function enumerate newly disconnected device ,All the resourcess
 allocated for the device.

  Parameters:
   None

  Returns:
    None
*/
void USB_HOST_EnumerateDevice()
{
    //uint8_t count;
    uint8_t dataLength;
    //uint16_t totalLoad;
    static uint8_t interfaceIndex = 0;
    USB_ENDPOINT endpointAndDirection;
    uint8_t configdescLength;
    uint8_t deviceCount;
    //static uint32_t failureCount = 0;
    USB_DEVICE_INFO *enumerateDeviceinfo;



    for (deviceCount = 0; deviceCount < USB_HOST_MAX_DEVICE_SUPPORTED; deviceCount++)
    {
        /*Get device information */
        enumerateDeviceinfo = &(gUsbHostInfo.businfo[0].attachedDevicesList
                                                                [deviceCount]);
        /* validate the device in use or not */
        if (enumerateDeviceinfo->assigned == 0x00)
            continue;
        /* jump to the device state */
        if (enumerateDeviceinfo->deviceState == STATE_ATTACHED)
        {
            if (enumerateDeviceinfo->deviceSubState == SUBSTATE_SETTLE)
            {
                if (enumerateDeviceinfo->deviceSubSubState ==
                                        SUBSUBSTATE_START_SETTLING_DELAY)
                {
                    enumerateDeviceinfo->deviceSubSubState =
                                                      SUBSUBSTATE_SETTLING_DONE;
                    /* Wait 100ms for the insertion process to
                     complete and power at the device to be stable.*/
                    DRV_USB_HOST_TimerStart(enumerateDeviceinfo->
                                                    hostControllerHandle, 100);
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                                    SUBSUBSTATE_SETTLING_DONE)
                {
                    if (DRV_USB_HOST_TimerIsComplete(enumerateDeviceinfo->
                                                        hostControllerHandle))
                    {
                        enumerateDeviceinfo->deviceSubState =
                                                          SUBSTATE_RESET_DEVICE;
                        enumerateDeviceinfo->deviceSubSubState =
                                                          SUBSUBSTATE_SET_RESET;
                    }

                }
            } 
            else if (enumerateDeviceinfo->deviceSubState ==
                                                        SUBSTATE_RESET_DEVICE)
            {

                if (enumerateDeviceinfo->deviceSubSubState ==
                                                        SUBSUBSTATE_SET_RESET)
                {
                    enumerateDeviceinfo->deviceSubSubState =
                                                        SUBSUBSTATE_RESET_WAIT;
                    if (enumerateDeviceinfo->parentId.deviceID == USB_ROOT_HUB)
                    {
                        DRV_USB_HOST_BusResetControl(enumerateDeviceinfo->
                                                    hostControllerHandle, true);
                    }
                    else
                    {
                        /* Hub related port reset */
                    }
                    DRV_USB_HOST_TimerStart(enumerateDeviceinfo->
                                                    hostControllerHandle, 100);
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                                        SUBSUBSTATE_RESET_WAIT)
                {
                    if (DRV_USB_HOST_TimerIsComplete(enumerateDeviceinfo->
                                                        hostControllerHandle))
                    {
                        enumerateDeviceinfo->deviceSubSubState =
                                                    SUBSUBSTATE_RESET_COMPLETE;
                        if (enumerateDeviceinfo->parentId.deviceID ==
                                                                  USB_ROOT_HUB)
                        {
                            DRV_USB_HOST_BusResetControl(enumerateDeviceinfo->
                                                   hostControllerHandle, false);

                        }
                        /* Enable SOF generation */
                        DRV_USB_HOST_StartOfFrameControl(enumerateDeviceinfo->
                                                    hostControllerHandle, true);
                        DRV_USB_HOST_TimerStart(enumerateDeviceinfo->
                                                    hostControllerHandle, 50);
                    }
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                                    SUBSUBSTATE_RESET_COMPLETE)
                {
                    if (DRV_USB_HOST_TimerIsComplete(enumerateDeviceinfo->
                                                        hostControllerHandle))
                    {
                        enumerateDeviceinfo->deviceSubState =
                                            SUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE;
                        enumerateDeviceinfo->deviceSubSubState =
                                    SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR_SIZE;

                    }

                }
            }
            else if (enumerateDeviceinfo->deviceSubState ==
                                            SUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE)
            {
                if (enumerateDeviceinfo->deviceSubSubState ==
                                    SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR_SIZE)
                {
                    enumerateDeviceinfo->speed = 
                        DRV_USB_HOST_DeviceCurrentSpeedGet(
                            enumerateDeviceinfo->hostControllerHandle);
                    if (enumerateDeviceinfo->speed < USB_SPEED_FULL )
                        enumerateDeviceinfo->speed = USB_SPEED_FULL;

                    /* opent the default pipe */
                    /* Create the first control transfer pipe */
                    endpointAndDirection = USB_ENDPOINT_AND_DIRECTION(
                                       USB_DATA_DIRECTION_DEVICE_TO_HOST, 0x00);
                    enumerateDeviceinfo->defaultPipeHandle =
                    DRV_USB_HOST_PipeSetup(
                                    enumerateDeviceinfo->hostControllerHandle,
                                    /*TEMP_DEVICE_ID*/ 0 ,endpointAndDirection ,0, 0,
                                    USB_TRANSFER_TYPE_CONTROL, 0,
                                    8, enumerateDeviceinfo->speed);
                    /*Fill setup packet */
                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] = 0;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_DEVICE;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 8; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;
                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data = (int8_t *)
                                       &(enumerateDeviceinfo->deviceDescriptor);
                    enumerateDeviceinfo->controlIrp.setup =
                                               enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 8;

                    enumerateDeviceinfo->controlIrp.callback = (void *)
                                                        _setupPacketCallback;
                    enumerateDeviceinfo->deviceSubSubState =
                                SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                         enumerateDeviceinfo->defaultPipeHandle,
                                         &(enumerateDeviceinfo->controlIrp));
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                        SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE_COMPLETE)
                {

                    if (enumerateDeviceinfo->controlIrp.status ==
                                                USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        enumerateDeviceinfo->deviceState = STATE_ADDRESSING;
                        enumerateDeviceinfo->deviceSubState =
                                                    SUBSTATE_SET_DEVICE_ADDRESS;
                        enumerateDeviceinfo->deviceSubSubState =
                                            SUBSUBSTATE_SEND_SET_DEVICE_ADDRESS;
                    }
                    else
                    {
                        if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                                DRV_USB_HOST_PipeClose(enumerateDeviceinfo->defaultPipeHandle);
                            }
                            else
                            {
                                //De enumerate the device 
                            }
                        }


                    }
                }

            }
        }
        else if (enumerateDeviceinfo->deviceState == STATE_ADDRESSING)
        {
            if (enumerateDeviceinfo->deviceSubState ==
                                                SUBSTATE_SET_DEVICE_ADDRESS)
            {
                if (enumerateDeviceinfo->deviceSubSubState ==
                                        SUBSUBSTATE_SEND_SET_DEVICE_ADDRESS)
                {
                    /* allocate new address for the device */
                    enumerateDeviceinfo->deviceId.deviceID =
                            _USB_HOST_GetNewAddress(enumerateDeviceinfo->deviceId);

                    /* Fill the setup packet for set address */
                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_HOST_TO_DEVICE |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;

                    enumerateDeviceinfo->setupPacket[1] =
                                                        USB_REQUEST_SET_ADDRESS;
                    enumerateDeviceinfo->setupPacket[2] =
                                         enumerateDeviceinfo->deviceId.deviceID;
                    enumerateDeviceinfo->setupPacket[3] = 0;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 0;
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data = NULL;
                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 0;
                              
                    enumerateDeviceinfo->controlIrp.callback = (void *)
                                                        _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_SET_DEVICE_ADDRESS_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                        enumerateDeviceinfo->defaultPipeHandle,
                                        &enumerateDeviceinfo->controlIrp);
                }
                else if (enumerateDeviceinfo->deviceSubSubState == 
                                        SUBSUBSTATE_SET_DEVICE_ADDRESS_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        /* open control pipe with new address */
                         endpointAndDirection = USB_ENDPOINT_AND_DIRECTION(
                                USB_DATA_DIRECTION_DEVICE_TO_HOST, 0x00);


                        enumerateDeviceinfo->controlPipeHandle = 
                                DRV_USB_HOST_PipeSetup(
                                enumerateDeviceinfo->hostControllerHandle,
                                enumerateDeviceinfo->deviceId.deviceID ,
                                endpointAndDirection /* Endpoint */, 0, 0,
                                USB_TRANSFER_TYPE_CONTROL/* Pipe type */,
                                0, /* bInterval */
                         enumerateDeviceinfo->deviceDescriptor.bMaxPacketSize0,
                         enumerateDeviceinfo->speed);
                        enumerateDeviceinfo->deviceState = STATE_CONFIGURING;
                        enumerateDeviceinfo->deviceSubState =
                                                SUBSTATE_GET_DEVICE_DESCRIPTOR;
                        enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR;
                    }
                    else
                    {
                         if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                            }
                            else
                            {
                                //De enumerate the device
                            }
                        }
                    }
                }
            }
        }
        if (enumerateDeviceinfo->deviceState == STATE_CONFIGURING)
        {
            if (enumerateDeviceinfo->deviceSubState == 
                                            SUBSTATE_GET_DEVICE_DESCRIPTOR)
            {
                if (enumerateDeviceinfo->deviceSubSubState == 
                                    SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR)
                {
                   /*Fill setup packet */
                    enumerateDeviceinfo->setupPacket[0] =
                                                USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                USB_SETUP_TYPE_STANDARD |
                                                USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] = 0;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_DEVICE;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] =
                            enumerateDeviceinfo->deviceDescriptor.bLength;
                    enumerateDeviceinfo->setupPacket[7] = 0;
                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data = (int8_t *)
                                       &(enumerateDeviceinfo->deviceDescriptor);

                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size =
                                  enumerateDeviceinfo->deviceDescriptor.bLength;
                   
                    enumerateDeviceinfo->controlIrp.callback =
                                (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                        enumerateDeviceinfo->controlPipeHandle,
                                        &(enumerateDeviceinfo->controlIrp));
                } 
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                SUBSUBSTATE_GET_DEVICE_DESCRIPTOR_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                                USB_HOST_IRP_STATUS_COMPLETED)
                    {

                        enumerateDeviceinfo->deviceSubState =
                                                SUBSTATE_GET_CONFIG_DESCRIPTOR;
                        enumerateDeviceinfo->deviceSubSubState =
                                    SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR_SIZE;
                    }
                    else
                    {
                         if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                            }
                            else
                            {
                                //De enumerate the device
                            }
                        }
                    }
                }

            }
            else if (enumerateDeviceinfo->deviceSubState == 
                                                SUBSTATE_GET_CONFIG_DESCRIPTOR)
            {

                if (enumerateDeviceinfo->deviceSubSubState == 
                                    SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR_SIZE)
                {

                    /*Fill setup packet */
                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] = 0;
                    enumerateDeviceinfo->setupPacket[3] =
                                                USB_DESCRIPTOR_CONFIGURATION;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 9; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */

                    enumerateDeviceinfo->controlIrp.data =
                                                    enumerateDeviceinfo->buffer;

                    enumerateDeviceinfo->controlIrp.setup =
                                               enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 9;
                    enumerateDeviceinfo->controlIrp.callback =
                                (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_SIZE_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                    enumerateDeviceinfo->controlPipeHandle,
                                    &(enumerateDeviceinfo->controlIrp));
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                        SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_SIZE_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {

                        configdescLength = enumerateDeviceinfo->buffer[2];
                        enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR;
                    }
                    else
                    {
                         if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                            }
                            else
                            {
                                //De enumerate the device
                            }
                        }
                    }

                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                        SUBSUBSTATE_SEND_GET_CONFIG_DESCRIPTOR)
                {
                    /*Fill setup packet */
                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] = 0;
                    enumerateDeviceinfo->setupPacket[3] =
                                                  USB_DESCRIPTOR_CONFIGURATION;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] =
                                                enumerateDeviceinfo->buffer[2];
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */

                    enumerateDeviceinfo->controlIrp.data =
                                                enumerateDeviceinfo->buffer;

                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size =
                                                enumerateDeviceinfo->buffer[2];
                    enumerateDeviceinfo->controlIrp.callback =
                                  (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                    SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                enumerateDeviceinfo->controlPipeHandle,
                                &(enumerateDeviceinfo->controlIrp));
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                SUBSUBSTATE_GET_CONFIG_DESCRIPTOR_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                    USB_HOST_IRP_STATUS_COMPLETED)
                    {

                        dataLength = enumerateDeviceinfo->controlIrp.size;
                      
                        _USB_HOST_ParseConfigDescriptor(
                                                enumerateDeviceinfo->buffer,
                                &(enumerateDeviceinfo->configDescriptorInfo[0]),
                                            dataLength);
                        
                        enumerateDeviceinfo->deviceSubState =
                                                    SUBSTATE_SET_CONFIGURATION;
                        enumerateDeviceinfo->deviceSubSubState =
                                            SUBSUBSTATE_SEND_SET_CONFIGURATION;
                    }
                    else
                    {
                         if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                            }
                            else
                            {
                                //De enumerate the device
                            }
                        }
                    }
                }
            }
            else if (enumerateDeviceinfo->deviceSubState ==
                                                SUBSTATE_SET_CONFIGURATION)
            {
                if (enumerateDeviceinfo->deviceSubSubState == 
                                        SUBSUBSTATE_SEND_SET_CONFIGURATION)
                {

                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_HOST_TO_DEVICE |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                USB_REQUEST_SET_CONFIGURATION;
                    enumerateDeviceinfo->setupPacket[2] = 
                            enumerateDeviceinfo->configDescriptorInfo[0].
                            configurationDescriptor->bConfigurationValue;
                    enumerateDeviceinfo->setupPacket[3] = 0; // Type
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 0; //length
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data = NULL;
                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 0;
                    enumerateDeviceinfo->controlIrp.callback =
                                (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_WAIT_FOR_SET_CONFIGURATION;
                    DRV_USB_HOST_IRPSubmit(
                                        enumerateDeviceinfo->controlPipeHandle,
                                            &enumerateDeviceinfo->controlIrp);
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                    SUBSUBSTATE_WAIT_FOR_SET_CONFIGURATION)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                                USB_HOST_IRP_STATUS_COMPLETED)
                    {
                    //   enumerateDeviceinfo->configDescriptorInfo[0].load =
                      //                                          totalLoad;
                        DRV_USB_HOST_TimerStart(
                                enumerateDeviceinfo->hostControllerHandle, 50);
                        enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_SET_CONFIGURATION_COMPLETE;
                    }
                    else
                    {
                         if (enumerateDeviceinfo->controlIrp.status < 0)
                        {
                            enumerateDeviceinfo->enumerationFailCount++;
                            // Reset the device states

                            if (enumerateDeviceinfo->enumerationFailCount < 3)
                            {
                                enumerateDeviceinfo->deviceState =
                                                            STATE_ATTACHED;
                                enumerateDeviceinfo->deviceSubState =
                                                            SUBSTATE_SETTLE;
                                enumerateDeviceinfo->deviceSubSubState =
                                        SUBSUBSTATE_START_SETTLING_DELAY;
                            }
                            else
                            {
                                //De enumerate the device
                            }
                        }
                    }
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                     SUBSUBSTATE_SET_CONFIGURATION_COMPLETE)
                {
                    if (DRV_USB_HOST_TimerIsComplete(
                                    enumerateDeviceinfo->hostControllerHandle))
                    {
                        _USB_HOST_FindDriver(enumerateDeviceinfo);
                        gUsbHostInfo.businfo[0].attachdevicesCount++;
                        enumerateDeviceinfo->deviceState = HOST_STATE_RUNNING;
                        enumerateDeviceinfo->deviceSubState =
                                                        SUBSTATE_SET_INTERFACE;
                        enumerateDeviceinfo->deviceSubSubState =
                                                SUBSUBSTATE_SEND_SET_INTERFACE;
                    }
                }
            }
            else if (enumerateDeviceinfo->deviceSubState ==
                                                    SUBSTATE_SET_INTERFACE)
            {
                if (enumerateDeviceinfo->deviceSubSubState == 
                                                SUBSUBSTATE_SEND_SET_INTERFACE)
                {
                    /* Fill setup packet for set interface */
                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_HOST_TO_DEVICE |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_SET_INTERFACE;
                    enumerateDeviceinfo->setupPacket[2] = 0; // Index
                    enumerateDeviceinfo->setupPacket[3] = 0; // Type
                    enumerateDeviceinfo->setupPacket[4] = interfaceIndex;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 0; //length
                    enumerateDeviceinfo->setupPacket[7] = 0;
                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data = NULL;
                    enumerateDeviceinfo->controlIrp.setup =
                                               enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 0;
                    enumerateDeviceinfo->controlIrp.callback =
                                   (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                            SUBSUBSTATE_SET_INTERFACE_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                    enumerateDeviceinfo->controlPipeHandle,
                                    &enumerateDeviceinfo->controlIrp);
                }
                else if (enumerateDeviceinfo->deviceSubSubState == 
                                            SUBSUBSTATE_SET_INTERFACE_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status ==
                                                USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        interfaceIndex++;
                        if (interfaceIndex == enumerateDeviceinfo->
                              configDescriptorInfo[0].configurationDescriptor->
                                bNumInterfaces)
                        {
                            enumerateDeviceinfo->deviceState =
                                                            HOST_STATE_RUNNING;
                            enumerateDeviceinfo->deviceSubState =
                                                SUBSTATE_GET_STRING_DESCRIPTOR;
                            enumerateDeviceinfo->deviceSubSubState =
                                                    SUBSTATE_SEND_LANGUAGE_ID;
                        } 
                        else
                        {

                            enumerateDeviceinfo->deviceSubSubState =
                                                SUBSUBSTATE_SEND_SET_INTERFACE;
                        }
                    }
                }
            }
            else if (enumerateDeviceinfo->deviceSubState ==
                                                SUBSTATE_GET_STRING_DESCRIPTOR)
                {

                /* This may be optional */
                /* Get all string descriptors from the device */
                if (enumerateDeviceinfo->deviceSubSubState == 
                                                    SUBSTATE_SEND_LANGUAGE_ID)
                {

                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] = 0;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_STRING; 
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] = 0;
                    enumerateDeviceinfo->setupPacket[6] = 4; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data =
                                                enumerateDeviceinfo->languageId;
                    enumerateDeviceinfo->controlIrp.setup =
                                               enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 4;
                    enumerateDeviceinfo->controlIrp.callback =
                                   (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                            SUBSTATE_SEND_LANGUAGE_ID_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                    enumerateDeviceinfo->controlPipeHandle,
                                    &enumerateDeviceinfo->controlIrp);

                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                                    SUBSTATE_SEND_LANGUAGE_ID)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        /* Language id contains the length and descriptor type*/
                        enumerateDeviceinfo->deviceSubSubState =
                                            SUBSTATE_SEND_MANUFACTURE_NAME;
                    }
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                            SUBSTATE_SEND_MANUFACTURE_NAME)
                {

                    enumerateDeviceinfo->setupPacket[0] =
                                                USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                USB_SETUP_TYPE_STANDARD |
                                                USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] =
                            enumerateDeviceinfo->deviceDescriptor.iManufacturer;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_STRING; 
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] =
                            enumerateDeviceinfo->deviceDescriptor.iManufacturer;
                    enumerateDeviceinfo->setupPacket[6] = 20; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data =
                                        enumerateDeviceinfo->ManufacturerName;
                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 20;
                    enumerateDeviceinfo->controlIrp.callback =
                                (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                        SUBSTATE_SEND_MANUFACTURENAME_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                    enumerateDeviceinfo->controlPipeHandle,
                                    &enumerateDeviceinfo->controlIrp);

                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                        SUBSTATE_SEND_MANUFACTURENAME_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        /* Language id contains the length and descriptor type */
                        enumerateDeviceinfo->deviceSubSubState =
                                                    SUBSTATE_SEND_PRODUCT_NAME;
                    }
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                                    SUBSTATE_SEND_PRODUCT_NAME)
                {
                    enumerateDeviceinfo->setupPacket[0] =
                                                     USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                     USB_SETUP_TYPE_STANDARD |
                                                     USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] =
                                enumerateDeviceinfo->deviceDescriptor.iProduct;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_STRING;
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] =
                                enumerateDeviceinfo->deviceDescriptor.iProduct;
                    enumerateDeviceinfo->setupPacket[6] = 20; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data =
                                    enumerateDeviceinfo->ManufacturerName;
                    enumerateDeviceinfo->controlIrp.setup =
                                        enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 20;
                    enumerateDeviceinfo->controlIrp.callback =
                                (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                            SUBSTATE_SEND_PRODUCT_NAME_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                        enumerateDeviceinfo->controlPipeHandle,
                                        &enumerateDeviceinfo->controlIrp);
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                        SUBSTATE_SEND_PRODUCT_NAME_COMPLETE)
                {

                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        /* Language id contains the length and descriptor type */
                        enumerateDeviceinfo->deviceSubSubState =
                                                    SUBSTATE_SEND_SERIAL_NUMBER;
                    }
                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                            SUBSTATE_SEND_SERIAL_NUMBER)
                {

                    enumerateDeviceinfo->setupPacket[0] =
                                                    USB_SETUP_DIRN_DEVICE_TO_HOST |
                                                    USB_SETUP_TYPE_STANDARD |
                                                    USB_SETUP_RECIPIENT_DEVICE;
                    enumerateDeviceinfo->setupPacket[1] =
                                                    USB_REQUEST_GET_DESCRIPTOR;
                    enumerateDeviceinfo->setupPacket[2] =
                           enumerateDeviceinfo->deviceDescriptor.iSerialNumber;
                    enumerateDeviceinfo->setupPacket[3] = USB_DESCRIPTOR_STRING; 
                    enumerateDeviceinfo->setupPacket[4] = 0;
                    enumerateDeviceinfo->setupPacket[5] =
                            enumerateDeviceinfo->deviceDescriptor.iSerialNumber;
                    enumerateDeviceinfo->setupPacket[6] = 20; /* length */
                    enumerateDeviceinfo->setupPacket[7] = 0;

                    /* Fill irp */
                    enumerateDeviceinfo->controlIrp.data =
                                            enumerateDeviceinfo->serialNumber;
                    enumerateDeviceinfo->controlIrp.setup =
                                            enumerateDeviceinfo->setupPacket;
                    enumerateDeviceinfo->controlIrp.size = 20;
                    enumerateDeviceinfo->controlIrp.callback =
                                   (USB_HOST_IRP_CALLBACK) _setupPacketCallback;

                    enumerateDeviceinfo->deviceSubSubState =
                                          SUBSTATE_SEND_SERIAL_NUMBER_COMPLETE;
                    DRV_USB_HOST_IRPSubmit(
                                        enumerateDeviceinfo->controlPipeHandle,
                                        &enumerateDeviceinfo->controlIrp);

                }
                else if (enumerateDeviceinfo->deviceSubSubState ==
                                        SUBSTATE_SEND_SERIAL_NUMBER_COMPLETE)
                {
                    if (enumerateDeviceinfo->controlIrp.status == 
                                            USB_HOST_IRP_STATUS_COMPLETED)
                    {
                        /* Language id contains the length and descriptor type*/
                        enumerateDeviceinfo->deviceState = DEVICE_READY;
                    }
                }
            }
        }
        else if (enumerateDeviceinfo->deviceState == HOST_STATE_RUNNING)
        {
            // driver function required...
        }
        else if (enumerateDeviceinfo->deviceState == STATE_HOLDING)
        {
            
        }
    }
}
/******************************************************************************
  Function:
    void _USB_HOST_EventHandler(void* referenceHandle,
        DRV_USB_EVENT eventType, DRV_USB_EVENT_DATA *eventData )

  Summary:
    Handles the events originating from USB Host Controller Driver

  Description:
    This routine is registered into the USB Host controller driver as a callback
    function. The USB Host controller driver calls this function in case of events
    from the USB controller driver.

  Parameters:
    referenceHandle           - USB Host Instance
    eventType                 - Event type
    eventData                 - Data associated with the event

  Returns:
    none.
*/

void _USB_HOST_EventHandler( uintptr_t referenceHandle,
            DRV_USB_EVENT eventType, void * eventData )
{
      HC_DEVICE_ID  removeID;
  
    USB_DEVICE_INFO *deviceInfo;

    switch (eventType)
    {
        case DRV_USB_EVENT_SOF_DETECT:
            break;
        case DRV_USB_EVENT_IDLE_DETECT:
            break;
        case DRV_USB_EVENT_RESUME_DETECT:
            break;
        case DRV_USB_EVENT_ERROR:
            break;
        case DRV_USB_EVENT_HOST_DETACH:
            /* Disable the SOF */
            DRV_USB_HOST_StartOfFrameControl(gUsbHostInfo.
                                businfo[referenceHandle].attachedDevicesList[0].
                                hostControllerHandle, false);
            deviceInfo = &(gUsbHostInfo.businfo[referenceHandle].
                                                        attachedDevicesList[0]);
            removeID = deviceInfo->deviceId;
            deviceInfo->assigned =  0x00;
            USB_HOST_DeEnumerate_Device(removeID );
            break;
        case DRV_USB_EVENT_HOST_ATTACH:
            //parent id is root hub , speed is full sped..
             deviceInfo = &(gUsbHostInfo.businfo[referenceHandle].
                                                        attachedDevicesList[0]);

             deviceInfo->deviceState =  STATE_ATTACHED;
             deviceInfo->deviceSubState = SUBSTATE_SETTLE;
             deviceInfo->deviceSubSubState = SUBSUBSTATE_START_SETTLING_DELAY;
             deviceInfo->parentId.deviceID = USB_ROOT_HUB;
             deviceInfo->parentId.hostcontrollerID = 0;
             deviceInfo->assigned = 1 ;
             deviceInfo->hostControllerHandle = gUsbHostInfo.
                                businfo[referenceHandle].hostControllerHandle;
             break;
        default:
            break;
    }
}





/******************************************************************************
  Function:
    USB_HOST_BUS_INFO * _USB_HOST_GetBusInfo( HC_DEVICE_ID Id)

  Summary:
    Get the  controller/ bus information based on deviceID

  Description:
    Bus information is global.collect the information based on attached devices.

  Parameters:
    HC_DEVICE_ID                 - Host controller Id + device id.

  Returns:
    USB_HOST_BUS_INFO *          - return to the pointer to the bus information
*/

USB_HOST_BUS_INFO* _USB_HOST_GetBusInfo(HC_DEVICE_ID Id)
{
    uint8_t count;
    USB_HOST_BUS_INFO *bus;
    for (count = 0; count < USB_HOST_INSTANCES_NUMBER; count++)
    {
        if (gUsbHostInfo.businfo[count].hostcontrollerid == Id.hostcontrollerID)
        {
            bus = (USB_HOST_BUS_INFO *)&(gUsbHostInfo.businfo[count]);
            return bus;
        }
    }
    return NULL;
}

 /******************************************************************************
  Function:
    _USB_HOST_GetDeviceInfo(HC_DEVICE_ID Id )

  Summary:
 Get device information based on host controller id and device id

  Description:
 Collect all the device related information

  Parameters:
    HC_DEVICE_ID                - Host controllerId + device ID

  Returns:
    USB_DEVICE_INFO *           - pointer to the device information
*/
USB_DEVICE_INFO * _USB_HOST_GetDeviceInfo(HC_DEVICE_ID Id)
{
    uint8_t count;
    USB_HOST_BUS_INFO *busInfo;
    USB_DEVICE_INFO *parentInfo;

    /* Address 1 is reserved for root hub */
    if (Id.deviceID < 0x01)
        return NULL;
    busInfo = _USB_HOST_GetBusInfo(Id);
    if(busInfo == NULL)
        return NULL;
    for (count = 0; count < USB_HOST_MAX_DEVICE_SUPPORTED; count++)
    {
        if(busInfo->attachedDevicesList[count].deviceId.deviceID == Id.deviceID)
        {
            parentInfo = &(busInfo->attachedDevicesList[count]);
            return parentInfo;
        }
    }
    return NULL;
}


  /******************************************************************************
  Function:
  uint8_t _USB_HOST_GetNewAddress(HC_DEVICE_ID id )

  Summary:
    Allocate a unique 8 bit device address

  Description:
 Assign address for Host controller and device address

  Parameters:
   USB_HOST_BUS_INFO *                - bus information pointer

  Returns:
  uint8_t
*/
uint8_t _USB_HOST_GetNewAddress(HC_DEVICE_ID id)
{
    USB_HOST_BUS_INFO *busInfo;
    uint8_t tempAddress;
    busInfo = _USB_HOST_GetBusInfo(id);
    for (tempAddress = 1; tempAddress <= USB_MAX_USB_ADDRESS; tempAddress++)
    {
        if ((busInfo->addressBits[tempAddress / 8] & 
                (1 << (tempAddress % 8))) == 0)
        {
            break;
        }
    }
    busInfo->addressBits[tempAddress / 8] |= (1 << (tempAddress % 8));
    return tempAddress;
}


/******************************************************************************
  Function:
    int8_t _USB_HOST_ParseConfigDescriptor(uint8_t *buffer,
                              USB_CONFIGURATION_INFO *config_desc_info,
                              uint8_t length)
  Summary:
 Parse descriptors

  Description:
    This routine is parse the configuration descriptor that holds the
 configuration descriptor, interface descriptor and endpoint descriptors

  Parameters:
    uint8_t*                             - raw configuration descriptor
    USB_CONFIGURATION_INFO *             - configuration information
    uint8_t                              - Length of the configuration descriptor

  Returns:
    int8_t                              - Status
*/

int8_t _USB_HOST_ParseConfigDescriptor(uint8_t *buffer,
                              USB_CONFIGURATION_INFO *configDescriptorInfo,
                              uint8_t length)
{
    USB_CONFIGURATION_DESCRIPTOR *tempcfg;
    USB_INTERFACE_DESCRIPTOR *interfaceDescriptor;
    USB_ENDPOINT_DESCRIPTOR *endpointDescriptor;
    USB_DESCRIPTOR_HEADER *header;
    USB_ALTERNATE_SETTING_INFO *altSetting = NULL;
    uint8_t totalInterfaces= 0;
    uint8_t context = 0;
    uint8_t totalEndpoints = 0;

    /* Typecast to raw configuration info to configuration descriptor */
    tempcfg = (USB_CONFIGURATION_DESCRIPTOR *) buffer;
    /* validate the length of configuration descriptor*/
    if (tempcfg->bLength != USB_CONFIG_DESCRPTR_SIZE)
        return USB_HOST_CONFIG_DESCRPTR_SIZE_INVALID;
    /* Validate the number of interfaces */
    if (tempcfg->bNumInterfaces > USB_HOST_MAX_INTERFACES)
        return USB_HOST_MAX_INTERFACES_INVALID;
    configDescriptorInfo->configurationDescriptor = tempcfg;
    buffer = buffer + USB_CONFIG_DESCRPTR_SIZE;
    length = length - USB_CONFIG_DESCRPTR_SIZE;
    /* parse the configuration descriptor */
    while (length > 2)
    {
        /* parse header information */
        header = (USB_DESCRIPTOR_HEADER *) buffer;
        if (header->size > length)
            return USB_HOST_HEADER_INVALID;
        /* Every alt setting starts with an exactly one interface descriptor
           followed by zero or more class specific interace descriptors
           followed by zero or more endpoint descriptors .
           Each endpoint descriptor is immediateley followed by zero or
           more class specific endpoint descriptor */
        switch (header->descType)
        {
            case USB_DESCRIPTOR_INTERFACE:
                interfaceDescriptor = (USB_INTERFACE_DESCRIPTOR *) buffer;
                /* valid interface place into configuration desc */
                altSetting = &(configDescriptorInfo->interfaceInfo
                        [interfaceDescriptor->bInterfaceNumber].
                  alternateSettingInfo[interfaceDescriptor->bAlternateSetting]);
                altSetting->interfaceDescriptor = interfaceDescriptor;
                length -= header->size;
                buffer += header->size;
                if (interfaceDescriptor->bAlternateSetting == 0)
                    totalInterfaces++;
                if (totalInterfaces > tempcfg->bNumInterfaces)
                    return USB_HOST_INTERFACE_DESC_SIZE_INVALID; // invalid desc
                /* standard interface desc */
                context = 1;
                totalEndpoints = 0;
                break;
            case USB_DESCRIPTOR_ENDPOINT:
                context = 3;
                endpointDescriptor = (USB_ENDPOINT_DESCRIPTOR *) buffer;
                /* End point zero never have descriptor */
                if ((endpointDescriptor->bEndpointAddress & 0xf) == 0)
                    return USB_HOST_ENDPOINT_DESC_SIZE_INVALID; // invalid descriptor
                if (totalEndpoints >= DRV_USB_HOST_PIPES_NUMBER )
                    return USB_HOST_MAX_ENDPOINT_INVALID; // Invalid descriptor
                /* valid endpoint place into cfg desc */
                altSetting->endpointInfo[totalEndpoints].
                        endpointDescriptor = endpointDescriptor;
                length -= header->size;
                buffer += header->size;
                totalEndpoints++;
                break;
            case USB_DESCRIPTOR_DEVICE:
            case USB_DESCRIPTOR_CONFIGURATION:
            case USB_DESCRIPTOR_STRING:
                return USB_HOST_DESC_INVALID; // invalid descriptor
                break;

            default:
                if (altSetting == NULL)
                    return USB_HOST_ALT_SETTING_INVALID; // invalid descriptor
                /* class specific interface descriptor */
                if ((context == 1) || (context == 2)) {
                    context = 2;
                    if (!altSetting->classSpecific)
                        altSetting->classSpecific = buffer;
                    length -= header->size;
                    buffer += header->size;
                    altSetting->classEndPtr = buffer;
                    break;
                }

                /* Class specific End Point Deccriptors */
                if ((context == 3) || (context == 4)) {
                    context = 4;
                    if (!(altSetting->endpointInfo[totalEndpoints - 1].
                                                            classSpecific))
                        altSetting->endpointInfo[totalEndpoints - 1].
                                                    classSpecific = buffer;
                    length -= header->size;
                    buffer += header->size;
                    altSetting->endpointInfo[totalEndpoints - 1].
                                                    classEndPtr = buffer;
                    return 1;
                    break;
                }
                break;
        }
    }
    return 1;
}

/******************************************************************************
  Function:
    int8_t  _USB_HOST_FindDriver( USB_DEVICE_INFO *newdevice)

  Summary:
    Find a maching a driver from the target peripheral list

  Description:
 Driver has to find based on Vendorid , productid, version number in
 device descritor
 or class - subclass - protocol values in device descriptor
 or class - subclass - protocol values in interface descriptor

  Parameters:
    USB_DEVICE_INFO *                   - newdevice information
  Returns:
    int8_t                                 - return status
*/
int8_t  _USB_HOST_FindDriver( USB_DEVICE_INFO *newdevice)
{
    uint8_t count = 0;
    uint8_t driverFound = 0;
    uint8_t countAltSettingNumber;
    USB_HOST_TARGET_PERIPHERAL_LIST *driverInfo;
    uint8_t configNumber;
    uint8_t interfaceNumber ;
    uint8_t instanceNumber = 0;
    //void   *instanceNumber;
    USB_CONFIGURATION_INFO *configuatationInfo;
    USB_ALTERNATE_SETTING_INFO *alternateSettingInfo;
    
    /* First we have to check it match any vendor specific drivre */
    for( count = 0 ; count < USB_HOST_MAX_DRIVER_SUPPORTED ; count++)
    {
      //  driverInfo=  &(USBTPList[count]);
        driverInfo = &(gUsbHostInfo.hostDeviceDriverinfo[count]);
        
        /* first validate vendor specific driver is available */
        if(( driverInfo->device.idVendor == newdevice->vendorid) &&
           ( driverInfo->device.idProduct == newdevice->productid))
          
        {
          newdevice->driverType = USB_VENDOR_DEVICE_DRIVER ;
          driverFound = 1 ;
          return driverFound ;
        }
     }
     /* Second we have to check any device specific class driver */
     for( count = 0 ; count < USB_HOST_MAX_DRIVER_SUPPORTED ; count++)
     {
      //   driverInfo=  &(USBTPList[count]);
        driverInfo = &(gUsbHostInfo.hostDeviceDriverinfo[count]);

        /* first validate class specific driver is available */
        if(( driverInfo->device.class == newdevice->classid) &&
           ( driverInfo->device.subClass == newdevice->subclass) &&
           ( driverInfo->device.protocol == newdevice->protocol))
        {
            newdevice->driverType = USB_STANDARD_DEVICE_DRIVER ;
            newdevice->driver = driverInfo->classDriver ;
            driverFound = 1 ;
            return driverFound;
        }
     }

      for( count = 0 ; count < USB_HOST_MAX_DRIVER_SUPPORTED ; count++)
     {
        // driverInfo=  &(USBTPList[count]);
         driverInfo = &(gUsbHostInfo.hostDeviceDriverinfo[count]);
     /* Based on interface descriptor values we have to find driver */
     for(configNumber = 0  ; configNumber < newdevice->deviceDescriptor.
                                            bNumConfigurations; configNumber++ )
     {
         configuatationInfo = &(newdevice->configDescriptorInfo[configNumber]);
         for(interfaceNumber =0 ; interfaceNumber < configuatationInfo->
                 configurationDescriptor->bNumInterfaces ; interfaceNumber++ )
         {
             for ( countAltSettingNumber = 0 ; countAltSettingNumber <=
                     USB_HOST_MAX_ALTERNATE_SETTINGS ;countAltSettingNumber++)
             {
                alternateSettingInfo = &(configuatationInfo->
                        interfaceInfo[interfaceNumber].
                        alternateSettingInfo[countAltSettingNumber]);
                if(alternateSettingInfo->interfaceDescriptor)
                {
                    if((alternateSettingInfo->interfaceDescriptor->
                            bInterfaceClass == driverInfo->device.class ) &&
                       (alternateSettingInfo->interfaceDescriptor->
                            bInterfaceSubClass == driverInfo->device.subClass)&&
                       (alternateSettingInfo->interfaceDescriptor->
                            bInterfaceProtocol == driverInfo->device.protocol )  )
                    {
                         newdevice->driverType = USB_STANDARD_INTERFACE_DRIVER ;
                         newdevice->driver = driverInfo->classDriver ;
                         driverFound = 1 ;
                         /* intstance Number */
                          newdevice->driver->initializeInterfaceDriver(
                          newdevice->deviceId ,interfaceNumber,&instanceNumber ,
                                  newdevice->speed);
                         return driverFound;
                    }
                }
             }
         }
     }
      }
  
    return 0;
 }

/******************************************************************************
  Function:
    int8_t  _USB_HOST_AttachDriver( USB_DEVICE_INFO *newdevice ,
                                    USB_HOST_BUS_INFO *bus_info )

  Summary:
   Initialize a device or interface

  Description:

  Parameters:
    USB_DEVICE_INFO *                   - newdevice information
    USB_HOST_BUS_INFO *                 - bus information

  Returns:
   none
 */
void _USB_HOST_AttachDriver(USB_DEVICE_INFO *newdevice)
{
    switch (newdevice->driverType)
    {
        case USB_VENDOR_DEVICE_DRIVER:
            newdevice->driver->initializeDeviceDriver(newdevice->deviceId, 0);
            break;
        case USB_STANDARD_DEVICE_DRIVER:
           
            newdevice->driver->initializeDeviceDriver(newdevice->deviceId, 0);
            break;
        case USB_STANDARD_INTERFACE_DRIVER:

            //  newdevice->driver->initializeInterfaceDriver(
            //newdevice->deviceId ,interfaceNumber ,instanceNumber );
            break;
        default:
            break;
    }
}



/******************************************************************************
  Function:
    _USB_HOST_FreeAddress (USB_HOST_BUS_INFO *bus , uint8_t deviceAddress)

  Summary:
    Free address

  Description:
    It is used for free the adress to the Host controller


  Parameters:
   USB_HOST_BUS_INFO *                 - bus information
   uint8_t                             - deviceAddress to be free

  Returns:
    uint8_t
*/
 uint8_t _USB_HOST_FreeAddress (USB_HOST_BUS_INFO *busInfo ,
                                uint8_t deviceAddress)
 {
     /* The address is no longer being used. */
     busInfo->addressBits[deviceAddress/ 8] &= ~(1 << (deviceAddress % 8));

     return 0;
 }


 /******************************************************************************
  Function:
    USB_CONFIGURATION_INFO* _USB_HOST_GetConfigurationInfo (
                                                        HC_DEVICE_ID id,
                                                uint8_t configurationNumber)

  Summary:
     Get device configuration information

  Description:
    Based  on device Identifier  and bConfiguration value get the
    configuration information

  Parameters:
    HC_DEVICE_ID                - Host controllerId + device ID
    uint8_t                     - configurationNumbe

  Returns:
    USB_CONFIGURATION_INFO*    - pointer to the device configuration information
*/
USB_CONFIGURATION_INFO* _USB_HOST_GetConfigurationInfo
                                                ( HC_DEVICE_ID id,
                                                  uint8_t configurationNumber)
  {
     //  USB_CONFIGURATION_INFO *cfgInfo;
       USB_DEVICE_INFO *deviceInfo;
       uint8_t count;
       deviceInfo = _USB_HOST_GetDeviceInfo(id);
       if(configurationNumber == 0)
           return &(deviceInfo->
                configDescriptorInfo[deviceInfo->activeConfigurationNumber ]);
       else
       {
           /* bConfigurationValue in the device's descriptor */


        for (count = 0; count < USB_HOST_MAX_CONFIGURATION ; count++)
        {
            if (&(deviceInfo->configDescriptorInfo[count]) &&
                (deviceInfo->configDescriptorInfo[count].
                    configurationDescriptor->bConfigurationValue
                    == configurationNumber ))

                return &(deviceInfo->configDescriptorInfo[count]);
        }

       }
       return NULL;
  }
  /**************************************************************/

uint8_t  USB_HOST_deviceState( HC_DEVICE_ID deviceId )
{
     USB_DEVICE_INFO    *deviceInfo;
     /* device information */
     deviceInfo = _USB_HOST_GetDeviceInfo(deviceId );
     return deviceInfo->deviceState;
}

/*************************************************************************/

USB_HOST_STATUS USB_HOST_getActiveConfigDesc (HC_DEVICE_ID id ,
                        USB_CONFIGURATION_DESCRIPTOR **configurationDescriptor)
{
    USB_CONFIGURATION_INFO *cfgInfo;
    cfgInfo = _USB_HOST_GetConfigurationInfo(id, 0);
    if (cfgInfo == NULL)
        return USB_HOST_ERROR;
    *configurationDescriptor = cfgInfo->configurationDescriptor;
    return USB_HOST_SUCCESS;
}

 uint8_t USB_HOST_DeviceDetect()
 {
     uint8_t count;
     count = gUsbHostInfo.businfo[0].attachdevicesCount;
     return count;
 }



void USB_HOST_HUB_enumerateDevice(HC_DEVICE_ID id ,uint8_t portNumber ,
                                                                uint8_t speed )

{
    static uint8_t deviceCount = 1;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].deviceState =
                                                            STATE_ATTACHED;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].deviceSubState =
                                            SUBSTATE_GET_DEVICE_DESCRIPTOR_SIZE;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].deviceSubSubState =
                                    SUBSUBSTATE_SEND_GET_DEVICE_DESCRIPTOR_SIZE;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].parentId.deviceID =
                                                            id.deviceID;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].parentId.
                                                        hostcontrollerID = 0;
    gUsbHostInfo.businfo[0].attachedDevicesList[deviceCount].assigned = 0x01;
    deviceCount++;
  }


void _setupPacketCallback (USB_HOST_IRP * irp)
{
    

    if(irp->status != USB_HOST_IRP_STATUS_COMPLETED )
   {
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT)
        {
            // Timing problem will resend the same packet
        }
         if( irp->status == USB_HOST_IRP_STATUS_ERROR_BUS)
        {
            // Re enumerate the device
        }
         if( irp->status == USB_HOST_IRP_STATUS_ERROR_DATA ||
                 irp->status == USB_HOST_IRP_STATUS_ERROR_BUS )
        {
            // Resend the request
        }
          if( irp->status == USB_HOST_IRP_STATUS_ERROR_STALL)
        {
            //clear the stall
        }


    }

}


/************************************************************************/
 /* calculation from 5.11.3 specification usb2.0 */
#if 0
 /* The time required for the host or transaction
translator to prepare for or recover from the
transmission; Host Controller implementation-specific */
#define Host_Delay  100 // Specific to the Host controller nano seconds..

 /* The time provided by the Host Controller for hubs to
enable low-speed ports; measured as the delay from the
end of the PRE PID to the start of the low-speed SYNC;
minimum of four full-speed bit times */

#define  Hub_LS_Setup  30 // TO DO

 /* The byte count of data payload */

#define Data_bc  64 // TO DO

 /* BitStuffTime Function that calculates theoretical additional time
required due to bit stuffing in signaling; worst case
is (1.1667*8*Data_bc) */

uint32_t _USB_HOST_CheckBandwidth ( uint8_t direction_n_type,
                                    uint8_t speed,
                                    uint32_t max_pkt_size)
{
    uint32_t bandwidth;
    switch ( speed )
    {
        case USB_SPEED_LOW :
             if( direction_n_type == CONTROL_TRANSFER_PIPE  ||
                direction_n_type ==  BULK_IN_TRANSFER_PIPE  ||
                direction_n_type  ==  INTERRUPT_IN_TRANSFER_PIPE ||
                direction_n_type  ==  ISOCHRONOUS_IN_TRANSFER_PIPE )
             {
                 bandwidth = 64060 + (2 * Hub_LS_Setup) + (676.67 *
                         Floor(3.167 + BitStuffTime(Data_bc))) + Host_Delay;
             }

             else if (direction_n_type  ==  BULK_OUT_TRANSFER_PIPE ||
                      direction_n_type  ==  INTERRUPT_OUT_TRANSFER_PIPE ||
                      direction_n_type ==  ISOCHRONOUS_OUT_TRANSFER_PIPE )
             {
                 bandwidth = 64107 + (2 * Hub_LS_Setup) + (667.0 *
                         Floor(3.167 + BitStuffTime(Data_bc))) + Host_Delay ;
             }


                break;
        case   USB_SPEED_FULL:

            if( direction_n_type == CONTROL_TRANSFER_PIPE  ||
                direction_n_type ==  BULK_IN_TRANSFER_PIPE  ||
                direction_n_type  ==  BULK_OUT_TRANSFER_PIPE ||
                direction_n_type  ==  INTERRUPT_IN_TRANSFER_PIPE ||
                direction_n_type  ==  INTERRUPT_OUT_TRANSFER_PIPE )
            {
                bandwidth = 9107 + (83.54 * Floor(3.167 +
                        BitStuffTime(Data_bc))) + Host_Delay ;
            }

            else if ( direction_n_type == ISOCHRONOUS_IN_TRANSFER_PIPE )
            {
                bandwidth = 7268 + (83.54 * Floor(3.167 +
                        BitStuffTime(Data_bc))) + Host_Delay;
            }
            else if (direction_n_type ==  ISOCHRONOUS_OUT_TRANSFER_PIPE )
            {
                bandwidth = 6265 + (83.54 * Floor(3.167 +
                        BitStuffTime(Data_bc))) + Host_Delay;
            }

            break;
        case   USB_SPEED_HIGH  :
            if( direction_n_type == CONTROL_TRANSFER_PIPE  ||
                direction_n_type ==  BULK_IN_TRANSFER_PIPE  ||
                direction_n_type  ==  BULK_OUT_TRANSFER_PIPE ||
                direction_n_type  ==  INTERRUPT_IN_TRANSFER_PIPE ||
                direction_n_type  ==  INTERRUPT_OUT_TRANSFER_PIPE )
            {

               bandwidth = (55 * 8 * 2.083) + (2.083 * Floor(3.167 +
                       BitStuffTime(Data_bc))) + Host_Delay;
            }

            else if ( direction_n_type == ISOCHRONOUS_IN_TRANSFER_PIPE  ||
                direction_n_type ==  ISOCHRONOUS_OUT_TRANSFER_PIPE  )
            {
                bandwidth = (38 * 8 * 2.083) + (2.083 * Floor(3.167 +
                        BitStuffTime(Data_bc))) + Host_Delay;
            }
            break;
        case USB_SPEED_SUPER :
            /* TO DO */
            break;

    }
}

#endif 
