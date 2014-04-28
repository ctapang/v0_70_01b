/*******************************************************************************
  USB Device Layer Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device.h

  Summary:
    USB Device Layer Interface Header

  Description:
    This header file contains the function prototypes and definitions of the
    data types and constants that make up the interface to the USB device
    layer.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  A file that maps the interface definitions above to appropriate static
          implementations (depending on build mode) is included at the bottom of
          this file.
*/

#include <stdint.h>
#include <stdbool.h>

#include "../system/common/sys_module.h"
#include "../system/common/sys_common.h"
#include "driver/usb/usbfs/src/drv_usb_local.h"
#include "../driver/driver_common.h"
#include "../usb/usb_common.h"
#include "../usb/usb_chapter_9.h"
#include "../../apps/Harmony4AvalonGen2.X/system_config.h"


// *****************************************************************************
// *****************************************************************************
// Section: USB Device Layer Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* USB Device Layer Index Numbers

  Summary:
    USB device layer index definitions.

  Description:
    These constants provide USB device layer index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

    These values should be passed into the USB_DEVICE_Initialize and
    USB_DEVICE_Open routines to identify the device layer instance in use.
*/

#define USB_DEVICE_INDEX_0         0
#define USB_DEVICE_INDEX_1         1
#define USB_DEVICE_INDEX_2         2
#define USB_DEVICE_INDEX_3         3
#define USB_DEVICE_INDEX_4         4
#define USB_DEVICE_INDEX_5         5

// *****************************************************************************
/* USB Device Layer Module Index Count

  Summary:
    Number of valid USB Device Layer indices

  Description:
    This constant identifies number of valid USB device layer indices.

  Remarks:
    This constant should be used in place of hard-coded numeric literals.

    This value is derived from part-specific header files defined as part of the
    peripheral libraries.
*/

#define USB_DEVICE_INDEX_COUNT     _USB_DEVICE_EXISTS

//*******************************************************************************
/*  Data type for USB device handle.

  Summary:
    Data type for USB device handle.

  Description:
    The data type of the handle that is returned from USB_DEVICE_Open
    function.

  Remarks:
    None.

*/

typedef uintptr_t USB_DEVICE_HANDLE;


// *****************************************************************************
/* USB Device Layer invalid handle

  Summary:
    Macro that defines the value of invalid device handle.

  Description:
    
  Remarks:
    
*/

#define USB_DEVICE_HANDLE_INVALID ((USB_DEVICE_HANDLE)(-1))

//*******************************************************************************
/* Configuration descriptors pointer

  Summary:
    Pointer to an array that contains pointer to configuration descriptors.

  Description:
    

  Remarks:
    

*/

typedef uint8_t** USB_DEVICE_CONFIG_DESCS_PTR;

//*******************************************************************************
/* String descriptors pointer

  Summary:
    Pointer to an array that contains pointer to string descriptors.

  Description:
    

  Remarks:
    

*/

typedef uint8_t** USB_DEVICE_STRING_DESCS_PTR;

//*******************************************************************************
/*  Data type of control transfer handle.

  Summary:
    Data type of USB device control transfer handle.

  Description:
    This is the data type of the handle that must be used by the
    application client for all control transfers.

  Remarks:
    Also see,
        USB_DEVICE_ControlSend
        USB_DEVICE_ControlReceive
        USB_DEVICE_ControlStatus

*/

typedef uintptr_t USB_DEVICE_CONTROL_TRANSFER_HANDLE;


//*******************************************************************************
/* 

  Summary:
    Enumerated data type identifying results of a control transfer.

  Description:
    These enumerated values are the possible return values for
    control transfer operation.

  Remarks:
      Also see,
        USB_DEVICE_ControlSend
        USB_DEVICE_ControlReceive
        USB_DEVICE_ControlStatus

*/

typedef enum
{

    /* Control transfer failed. This could be because the 
       control transfer handle is no more valid since the control transfer
      was aborted by host by sending a new setup packet */
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED
            /*DOM-IGNORE-BEGIN*/ = USB_ERROR_DEVICE_CONTROL_TRANSFER_FAILED /*DOM-IGNORE-END*/,

    /* Control transfer was successful*/
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS
            /*DOM-IGNORE-BEGIN*/ = USB_ERROR_NONE /*DOM-IGNORE-END*/
    
}USB_DEVICE_CONTROL_TRANSFER_RESULT;


//*******************************************************************************
/* USB Device control transfer events

  Summary:
    This datatype defines the different control transfer events.

  Description:
    

  Remarks:
    None.

*/

typedef enum
{
    /* Previous control transfer was aborted. */
    USB_DEVICE_CONTROL_TRANSFER_ABORTED
            /*DOM-IGNORE-BEGIN*/ = -1 /*DOM-IGNORE-END*/,
 
    /*DOM-IGNORE-BEGIN*/
    USB_DEVICE_CONTROL_TRANSFER_NO_EVENT = 0,
    /*DOM-IGNORE-END*/

   /* Control transfer data stage was completed */
    USB_DEVICE_CONTROL_DATA_RECEIVED
            /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /* A setup packet was received and control transfer is in
     setup stage */
    USB_DEVICE_CONTROL_SETUP_REQUEST
            /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/,

    /* Control transfer data stage transmit is complete */
    USB_DEVICE_CONTROL_DATA_SENT = 3

}USB_DEVICE_CONTROL_TRANSFER_EVENT;


#define USB_DEVICE_ENDPOINT_TABLE_SIZE (DRV_USB_ENDPOINTS_NUMBER * DRV_USB_ENDPOINT_TABLE_ENTRY_SIZE)

//*******************************************************************************
/* USB Device control transfer event data.

  Summary:
    USB device control transfer event data.

  Description:


  Remarks:
    None.

*/
typedef union 
{
    /* Data associated with USB_DEVICE_CONTROL_SETUP_REQUEST */
    USB_SETUP_PACKET * setupRequest;


}USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA;


//*******************************************************************************
/* Power state

  Summary:
    Enumerated data type that identifies if the device is self powered or
    bus powered .

  Description:


  Remarks:
    Also see,
        USB_DEVICE_PowerStateSet

*/

typedef enum{

    /* Device is bus powered */
    USB_DEVICE_POWER_STATE_BUS_POWERED 
            /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /* Device is self powered */
    USB_DEVICE_POWER_STATE_SELF_POWERED 
            /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/,

}USB_DEVICE_POWER_STATE;

//*******************************************************************************
/* Remote wakeup status

  Summary:
    Enumerated data type that identifies if the remote wakeup status of the
    device.

  Description:


  Remarks:
    Also see,
    USB_DEVICE_RemoteWakeupIsEnabled
*/

typedef enum{

     /* Remote wakeup is disabled */
    USB_DEVICE_REMOTE_WAKEUP_DISABLED
            /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,
    /* Remote wakeup is enabled */
    USB_DEVICE_REMOTE_WAKEUP_ENABLED
            /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/   

}USB_DEVICE_REMOTE_WAKEUP_STATUS;


// *****************************************************************************
/* USB device states as described in chapter-9 of USB 2.0 specification

  Summary:
    Standard USB device states as described in Chapter-9 of USB 2.0 Specification.

  Description:
    This data type identifies the USB Device States.

  Remarks:
    The USB specification doesn't define the state of a device when it 
    is detached from the USB. The USB_DEVICE_STATE_DETACHED is not the standard
    state, but is required to indicate the user, that the device is not in 
    any of the known states.
*/

typedef enum 
{
    /* Device is not in any of the known USB states*/
    USB_DEVICE_STATE_DETACHED
            /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,
            
    /* Device is in attached state*/
    USB_DEVICE_STATE_ATTACHED
            /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,
            
    /*Device is in powered state*/
    USB_DEVICE_STATE_POWERED            
            /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/,
            
    /*Device is in default state*/    
    USB_DEVICE_STATE_DEFAULT           
            /*DOM-IGNORE-BEGIN*/ = 3 /*DOM-IGNORE-END*/,
    
    /*Device is in addressed state*/ 
    USB_DEVICE_STATE_ADDRESSED            
            /*DOM-IGNORE-BEGIN*/ = 4 /*DOM-IGNORE-END*/,
    
    /*Device is in configured state*/ 
    USB_DEVICE_STATE_CONFIGURED         
            /*DOM-IGNORE-BEGIN*/ = 5 /*DOM-IGNORE-END*/,
    
    /*Device is in suspended state*/ 
    USB_DEVICE_STATE_SUSPENDED          
            /*DOM-IGNORE-BEGIN*/ = 6 /*DOM-IGNORE-END*/  
    
    
}USB_DEVICE_STATE;


// *****************************************************************************
/*
  Summary:
    Enumerated data-type identifying the bus events that has occurred in
    the USB device layer.

  Description:
    Datatype that identifies the event that is active in the USB device layer.

  Remarks:
    None.
*/

typedef enum 
{
    /* USB bus reset occurred. This event is an indication to the application
     client that device layer is about to de-initialize the function drivers.
     For application client, this event means that it has to close any open
     handles to function drivers */
    USB_DEVICE_EVENT_RESET 
             /*DOM-IGNORE-BEGIN*/ = DRV_USB_EVENT_RESET_DETECT /*DOM-IGNORE-END*/,
   

    /* This event is an indication to the application client that device is
     suspended and it can put the device to power-down mode if required. */
    USB_DEVICE_EVENT_SUSPENDED
             /*DOM-IGNORE-BEGIN*/ = DRV_USB_EVENT_IDLE_DETECT /*DOM-IGNORE-END*/,

    /* This event indicates that device has resumed from suspended state. */
    USB_DEVICE_EVENT_RESUMED
             /*DOM-IGNORE-BEGIN*/ = DRV_USB_EVENT_RESUME_DETECT /*DOM-IGNORE-END*/,    

    /* This event is an indication to the application client that an error 
     occurred on the USB bus */
    USB_DEVICE_EVENT_ERROR
             /*DOM-IGNORE-BEGIN*/ = DRV_USB_EVENT_ERROR /*DOM-IGNORE-END*/,

    /* This event is generated for every start of frame.
     * Application client can use this SOF event for general time based house keeping activities.*/
    USB_DEVICE_EVENT_SOF
           /*DOM-IGNORE-BEGIN*/ = DRV_USB_EVENT_SOF_DETECT /*DOM-IGNORE-END*/,

     /* This event is an indication to the application client that the device is
     detached from the host and device layer is about to de-initialize the
     function drivers. For application client, this event means that it has to
     close any open handles to function drivers */
    USB_DEVICE_EVENT_DETACHED,

     /* This event is an indication to the application client that device layer
     is about to de-initialize the function drivers. For application client,
     this event means that it has to close any open handles to function drivers */
    USB_DEVICE_EVENT_DECONFIGURED,

    /* This event is an indication to the application client that device layer
     has initialized all function drivers and applicaton can open handles to
     function drivers. */
    USB_DEVICE_EVENT_CONFIGURED,

    /* This event indicates that device is attached to the host */
    USB_DEVICE_EVENT_ATTACHED

}USB_DEVICE_EVENT;


// *****************************************************************************
/*
  Summary:
   Data-type that holds the data related to USB device configured event.

  Description:
    

  Remarks:
    Also see
        USB_DEVICE_EVENT_DATA
        USB_DEVICE_CALLBACK
        
*/

typedef struct 
{
    /* Configuration value selected by the host*/
    uint8_t configurationValue;

    /* USB speed at which the device is connected to host */
    USB_SPEED speed;
}USB_DEVICE_EVENT_DATA_CONFIGURED;


// *****************************************************************************
/*
  Summary:
   Data assosciated with USB bus events.

  Description:
    

  Remarks:
     Also see
        USB_DEVICE_CALLBACK
*/

typedef union 
{
    /* Data related to configured event */
   USB_DEVICE_EVENT_DATA_CONFIGURED eventConfigured;
}USB_DEVICE_EVENT_DATA;


// *****************************************************************************
/* USB Device Layer Callback Function Pointer

  Summary:
    Pointer to a USB Device Layer callback function data type for bus events.

  Description:
    This is the data type of the callback function that will be called by the USB 
    device layer when there is a bus event from USB device layer.

  Remarks:
    A USB Device Layer callback function must have the following function signature:

        void MyCallBack ( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData );
        
   Where, "event" indicates an event on the USB device layer, and "MyCallBack" can be 
   any name desired as the function is called through the pointer.
    
*/

typedef void (*USB_DEVICE_CALLBACK) (USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData);


// *****************************************************************************
/* USB Device Layer control transfer callback Function Pointer

  Summary:
    

  Description:
    This is the data type of the callback function that will be called by the USB
    device layer when there is a control transfer event from USB device layer.

  Remarks:
    A USB Device Layer callback function must have the following function signature:

        void MyCallBack ( USB_DEVICE_EVENT event, USB_DEVICE );

   Where, "event" indicates an event on the USB device layer, and "MyCallBack" can be
   any name desired as the function is called through the pointer.

*/

typedef void (*USB_DEVICE_CONTROL_TRANSFER_CALLBACK)
                                (   USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                    USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA *  eventData);
                                                
                                                
// *****************************************************************************
/* Global USB Descriptor Structure.

  Summary:
    Global USB descriptor structure containing pointers to standard USB 
    descriptor structures. 

  Description:
    

  Remarks:
    
*/

typedef struct 
{
   
    /* Pointer to standard device descriptor (for low/full speed) */
    uint8_t*          ptrDeviceDescriptor;
    
    /* Total number configurations available (for low/full speed)*/
    uint8_t         configDescriptorCount;
    
    /* Pointer to array of configurations descriptor pointers
    (for low/full speed)*/
    USB_DEVICE_CONFIG_DESCS_PTR        ptrConfigDescriptor;
    
     /* Pointer to array of high speed standard Device descriptor.
     Assign this to NULL if not supported.*/
    uint8_t*          ptrHighSpeedDeviceDescriptor;
    
    /* Total number of high speed configurations available.
    Set this to zero if not supported*/
    uint8_t         highSpeedConfigDescriptorCount;
    
    /* Pointer to array of high speed configurations descriptor pointers.
    Set this to NULL if not supported*/
    USB_DEVICE_CONFIG_DESCS_PTR        ptrHighSpeedConfigDescriptor;
    
    /* Total number of string descriptors available (common to all speeds)*/
    uint8_t         stringDescCount;
       
    /* Pointer to array of string Descriptor pointers (common to all speeds)*/
    USB_DEVICE_STRING_DESCS_PTR        ptrStringDesc;
    
    /* Pointer to full speed device_qualifier descriptor. 
    Device responds with this descriptor when it is operating at high speed */
    uint8_t*  ptrFullSpeedDeviceQualifier;
    
    /* Pointer to high speed device_qualifier descriptor. 
    Device responds with this descriptor when it is operating at full speed */ 
    uint8_t*  ptrHighSpeedDeviceQualifier;
    
}USB_MASTER_DESCRIPTOR;


// *****************************************************************************
/* USB function driver structure

  Summary:
    A function driver has to expose standard APIs to device layer using 
    following structure.

  Description:
    All function drivers (including vendor specific ones) must provide callback
    functions to USB device layer in the format specified by this structure.
    The USB device layer calls these callback functions at the time of 
    appropriate event.

  Remarks:
    Even the vendor specific function drivers must provide callback functions
    in this format.
    
*/

typedef struct  
{
    /* Initialize gets called by the Device layer when it recieves set configuration event.
      The device layer will initialize a function driver for every descriptor.
      Based on the descriptor type the function driver has to initialize itself. */
    void (*initializeByDescriptor)
            (SYS_MODULE_INDEX funcDriverIndex, USB_DEVICE_HANDLE usbDeviceHandle,
               void* funcDriverInit, uint8_t interfaceNumber, uint8_t alternateSetting,
               uint8_t descriptorType, uint8_t * pDescriptor );
            
    /* deInit gets called when the device layer detects a device dettach,
    change in configuration or ob USB bus reset.*/
    void (*deInitialize)(SYS_MODULE_INDEX funcDriverIndex);
 
                                    
    /* This function will be called by the device layer when there is a interface specific
     setup packet request */
    void (*controlTransferNotification) (
                                        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlHandle,
                                        SYS_MODULE_INDEX index,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent,
                                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * controlEventData);
                               
                                    
   /* Function driver Tasks */
   void (*tasks)(SYS_MODULE_INDEX funcDriverIndex);
                     
} USB_DEVICE_FUNCTION_DRIVER;


// *****************************************************************************
/* Global USB Device function registration structure

  Summary:
    A function driver has to be registered with the USB device layer
    using this structure.

  Description:
    

  Remarks:
    
*/

typedef struct   
{
    
    /* Type of speed (high, full or low speed) */
    USB_SPEED            speed;
    
    /* Configuration Value to which the function driver
    has to be tied */
    uint8_t                     configurationValue;

    /* Interface number to which this function driver
     has to be tied */
    uint8_t                     interfaceNumber;

    /* Number of interfaces used by the function */
    uint8_t                     numberOfInterfaces;
    
    /* Function driver instance index */
    SYS_MODULE_INDEX            funcDriverIndex;
    
    /* Pointer to a structure that contains function driver initialization data */
    void*                       funcDriverInit;
    
    /* Pinter to a standard structure that exposes function driver APIs to 
    USB device layer*/
    USB_DEVICE_FUNCTION_DRIVER*  driver;
    
} USB_DEVICE_FUNC_REGISTRATION_TABLE;


// *****************************************************************************
/*  Control transfer status stage

  Summary:
   This enumerated data-type identifies the status stage of control transfer.

  Description:


  Remarks:
    Also see,
        USB_DEVICE_ControlStatus
*/

typedef enum 
{
    /* Control transfer is supported.
       Send ZLP in the status stage. */
    USB_DEVICE_CONTROL_STATUS_OK,

     /* Control transfer is not supported.
        Stall control endpoint. */
    USB_DEVICE_CONTROL_STATUS_ERROR

}USB_DEVICE_CONTROL_STATUS;


// *****************************************************************************
/* USB Device Initialization Structure

  Summary:
    This structure has to be initialized by the system/application and must
    be passed as parameter to USB_DEVICE_Initialize(). 

  Description:
    

  Remarks:
    Also see,
        USB_DEVICE_Initialization
*/

typedef struct 
{
    /* System module initialization */
    SYS_MODULE_INIT     moduleInit;    

    /* Identifies peripheral (PLIB-level) ID */
    unsigned int        usbID;

    /* Boolean flag: true -> Stop USB module in Idle Mode */
    bool                stopInIdle;     

    /* Boolean flag: true -> Suspend USB in Sleep Mode */
    bool                suspendInSleep; 

    /* Interrupt Source for USB module */
    INT_SOURCE          interruptSource;
      
    /* Endpoint Table Buffer */
    void                *endpointTable;

    /* Number of function drivers registered to this instance of the 
    USB device layer */
    uint16_t        registeredFuncCount;
    
    /* Function driver table registered to this instance of the USB device layer*/
    USB_DEVICE_FUNC_REGISTRATION_TABLE      *registeredFunctions;
    
    /* Pointer to USB Descriptor structure */
    USB_MASTER_DESCRIPTOR             *usbMasterDescriptor;

    /* Speed at which this device speed should operate*/
    USB_SPEED   deviceSpeed;

} USB_DEVICE_INIT;


// *****************************************************************************
// *****************************************************************************
// Section: USB Device Layer Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ USB_DEVICE_Initialize(const SYS_MODULE_INDEX instanceIndex, 
                                            const SYS_MODULE_INIT * const init)

  Summary:
    Creates and initializes an instance of the USB device layer.

  Description:
    This function initializes an instance of USB device layer, making it ready
    for clients to open and use it. The number of instances is limited by the 
    value of macro USB_DEVICE_MAX_INSTANCES.

  Precondition:
    None.

  Parameters:
    instanceIndex     - In case of microcontrollers with multiple USB peripherals,
                        user can create multiple instances of USB device layer.
                        Parameter instanceIndex identifies this instance.
    
    init              - Pointer to a data structure containing any data necessary
                        to initialize the USB device layer

  Returns:
    If successful, returns a valid handle to a device layer object. 
    Otherwise, it returns SYS_MODULE_OBJ_INVALID. 

  Example:
    <code>
    
    USB_DEVICE_INIT deviceLayerInit;
    SYS_MODULE_OBJ usbDeviceObj;

     // System module initialization
    deviceLayerInit.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
     // Identifies peripheral (PLIB-level) ID
    deviceLayerInit.usbID = USB_ID_1;
    // Boolean flag: true -> Stop USB module in Idle Mode
    deviceLayerInit.stopInIdle = false;
    // Boolean flag: true -> Suspend USB in Sleep Mode
    deviceLayerInit.suspendInSleep = false;
     // Interrupt Source for USB module
    deviceLayerInit.interruptSource = INT_SOURCE_USB_1;
    // Number of function drivers registered to this instance of the
    USB device layer 
    deviceLayerInit.registeredFuncCount = 1;
    // Function driver table registered to this instance of the USB device layer
    deviceLayerInit.registeredFunctions = funcRegistrationTable;
    // Pointer to USB Descriptor structure 
    deviceLayerInit.usbMasterDescriptor   = &usbMasterDescriptor;

    // USB device initialization
    usbDeviceObj = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, &deviceLayerInit);
      
    if (SYS_MODULE_OBJ_INVALID == usbDeviceObj)
    {
        // Handle error
    }
    </code>

  Remarks:
    This routine must be called before any other USB Device Layer routine is called
    and after the initialization of USB Device Driver.
    This routine should only be called once during system initialization.
*/

SYS_MODULE_OBJ USB_DEVICE_Initialize(const SYS_MODULE_INDEX instanceIndex, 
                                              const SYS_MODULE_INIT * const init);
                                                        
                                                   
// *****************************************************************************
/* Function:
    void USB_DEVICE_Reinitialize( SYS_MODULE_OBJ usbDeviceObj,
                                  const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes the USB device layer

  Description:
    This function reinitializes the USB device layer.

  Precondition:
    USB device driver and USB device layer must have been initialized.
    

  Parameters:
    usbDeviceObj    - Driver object handle, returned by USB_DEVICE_Initialize

    init            - Pointer to a data structure containing any data necessary
                      to reinitialize the USB device layer.

  Returns:
    None

  Example:
    <code>
        USB_DEVICE_INIT deviceLayerInit;
            
       // System module initialization
        deviceLayerInit.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
         // Identifies peripheral (PLIB-level) ID
        deviceLayerInit.usbID = USB_ID_1;
        // Boolean flag: true -> Stop USB module in Idle Mode
        deviceLayerInit.stopInIdle = false;
        // Boolean flag: true -> Suspend USB in Sleep Mode
        deviceLayerInit.suspendInSleep = false;
         // Interrupt Source for USB module
        deviceLayerInit.interruptSource = INT_SOURCE_USB_1;
        // Number of function drivers registered to this instance of the
        USB device layer
        deviceLayerInit.registeredFuncCount = 1;
        // Function driver table registered to this instance of the USB device layer
        deviceLayerInit.registeredFunctions = funcRegistrationTable;
        // Pointer to USB Descriptor structure
        deviceLayerInit.usbMasterDescriptor   = &usbMasterDescriptor;

        // USB device initialization
        usbDeviceObj = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, &deviceLayerInit);

        if (SYS_MODULE_OBJ_INVALID == usbDeviceObj)
        {

        } 
        
        // Do something here.
         
        // Re-initialize if required.
        // System module initialization
        deviceLayerInit.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
         // Identifies peripheral (PLIB-level) ID
        deviceLayerInit.usbID = USB_ID_1;
        // Boolean flag: true -> Stop USB module in Idle Mode
        deviceLayerInit.stopInIdle = false;
        // Boolean flag: true -> Suspend USB in Sleep Mode
        deviceLayerInit.suspendInSleep = false;
         // Interrupt Source for USB module
        deviceLayerInit.interruptSource = INT_SOURCE_USB_1;
        // Number of function drivers registered to this instance of the
        USB device layer
        deviceLayerInit.registeredFuncCount = 1;
        // Function driver table registered to this instance of the USB device layer
        deviceLayerInit.registeredFunctions = funcRegistrationTable;
        // Pointer to USB Descriptor structure
        deviceLayerInit.usbMasterDescriptor   = &usbMasterDescriptor;
      
        USB_DEVICE_ReInitialize(USB_DEVICE_INDEX_0, &deviceLayerInit);
   
    </code>

  Remarks:
    This function can be called multiple times to reinitialize the USB device layer.

    This operation reinitializes all the module variables of the USB device layer 
    associated with the instance specified by the parameter "usbDeviceObj".
*/

void USB_DEVICE_Reinitialize ( SYS_MODULE_OBJ usbDeviceObj,
                                        const SYS_MODULE_INIT * const init );
                                                                 
                                                                 
// *****************************************************************************
/* Function:
    void USB_DEVICE_Deinitialize ( SYS_MODULE_OBJ usbDeviceobj )

  Summary:
    Deinitializes the specified instance of the USB device layer.

  Description:
    This function deinitializes the specified instance of the USB device layer,
    disabling its operation (and any hardware) and invalidates all of the internal data.

  Precondition:
    Function USB_DEVICE_Initialize must have been called before calling this
    routine and a valid SYS_MODULE_OBJ must have been returned.

  Parameters:
    object          - USB device layer object handle, returned by USB_DEVICE_Initialize

  Returns:
    None.

  Example:
    <code>
    
    </code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize operation
    must be called before the Initialize operation can be called again.
    
*/

void USB_DEVICE_Deinitialize ( SYS_MODULE_OBJ usbDeviceObj );


// *****************************************************************************
/* Function:
    SYS_STATUS USB_DEVICE_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the USB device layer

  Description:
    This function provides the current status of the USB device layer.

  Precondition:
    The USB_DEVICE_Initialize function must have been called before calling this
    function.

  Parameters:
    object  - Driver object handle, returned from USB_DEVICE_Initialize

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
  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from DRV_USB_Initialize
    SYS_STATUS          status;

    status = USB_DEVICE_Status(object);

    if (SYS_STATUS_ERROR >= status)
    {
        // Handle error
    }
    </code>

  Remarks:
    None.
*/

SYS_STATUS USB_DEVICE_Status( SYS_MODULE_OBJ object );

                                                                                    
// *****************************************************************************
/* Function:
    USB_DEVICE_HANDLE USB_DEVICE_Open( const SYS_MODULE_INDEX instanceIndex,
                                const DRV_IO_INTENT    intent )

  Summary:
    Opens the specified USB device layer instance and returns a handle to it.

  Description:
    This function opens the USB device layer instance specified by instance index
    and provides a handle that must be provided to all other client-level operations 
    to identify the caller and the instance of the USB device layer.
    The number of handles a client can open is limited by the value set to 
    USB_DEVICE_MAX_CLIENTS.

  Precondition:
    This function must be called after USB device driver initialization
    and after the initialization of USB Device Layer.

  Parameters:
    instanceIndex   - USB device layer instance index
    intent      - Zero or more of the values from the enumeration
                  DRV_IO_INTENT ORed together to indicate the intended use
                  of the driver

  Returns:
    If successful, returns a valid handle to a device layer object. Otherwise, it 
    returns SYS_MODULE_OBJ_INVALID. 

  Example:
    <code>
    USB_DEVICE_HANDLE usbDeviceHandle;
    
    // Before opening a handle, USB device must have been initialized 
    // by calling USB_DEVICE_Initialize().
    usbDeviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_BLOCKING );
    
    if(USB_DEVICE_HANDLE_INVALID == usbDeviceHandle)
    {
        //Failed to open handle.
    }
    
    </code>

  Remarks:
    This routine must be called after USB device driver initialization
    and after the initialization of USB Device Layer.
    This routine should be called only once during system initialization.
*/

USB_DEVICE_HANDLE USB_DEVICE_Open( const SYS_MODULE_INDEX instanceIndex,
                                        const DRV_IO_INTENT    intent );


// *****************************************************************************
/* Function:
    void USB_DEVICE_Close( USB_DEVICE_HANDLE usbDevHandle )

  Summary:
    Closes an opened handle to an instance of the USB device layer.

  Description:
    This function closes an opened handle to an instance of the USB device layer,
    invalidating the handle.

  Precondition:
    The USB_DEVICE_Initialize function must have been called for the specified
    device layer instance. USB_DEVICE_Open must have been called to obtain a 
    valid opened device handle.

  Parameters:
    handle       - A valid open-instance handle, returned from USB_DEVICE_Open

  Returns:
    None

  Example:
    <code>
    USB_DEVICE_HANDLE usbDeviceHandle;
    
    // Before opening a handle, USB device must have been initialized 
    // by calling USB_DEVICE_Initialize().
    usbDeviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0 );
    
    if(USB_DEVICE_HANDLE_INVALID == usbDeviceHandle)
    {
        //Failed to open handle.
    }
    
    .................
    .................
    // User's code
    .................
    .................
    // Close handle
    USB_DEVICE_Close( usbDevHandle );
    </code>

  Remarks:
    After calling this routine, the handle passed in "usbDevHandle" must not be used
    with any of the remaining driver routines.  A new handle must be obtained by
    calling USB_DEVICE_Open() before the client may use the device layer again.

*/

void USB_DEVICE_Close( USB_DEVICE_HANDLE usbDeviceHandle );


// *****************************************************************************
/* Function:
    DRV_CLIENT_STATUS USB_DEVICE_ClientStatus
                                             ( USB_DEVICE_HANDLE usbDeviceHandle )

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

  Example:
    <code>
    
    </code>

  Remarks:
    None.
*/

DRV_CLIENT_STATUS USB_DEVICE_ClientStatus( USB_DEVICE_HANDLE usbDevHandle );


// *****************************************************************************
/* Function:
    USB_ERROR_STATUS USB_DEVICE_EventCallBackSet
         ( USB_DEVICE_HANDLE usbDeviceHandle, USB_DEVICE_CALLBACK *callBackFunc )

  Summary:
    Client can register its call-back function into the device layer.

  Description:
    The USB Device Layer notifies the event to the client by calling callBackFunc.

  Precondition:
    The device layer must have been initialized by calling USB_DEVICE_Initialize
    and a valid handle to the instance must have been obtained by calling 
    USB_DEVICE_Open.

  Parameters:
    usbDeviceHandle    - Pointer to the device layer handle that is returned from
                        USB_DEVICE_Open
                        
    callBackFunc      - Pointer to the call back function. The device layer calls
                        notifies the client about bus event by calling this function.
    
  Returns:
    Returns USB_ERROR_NONE if successful.

  Example:
    <code>
    
    </code>

  Remarks:
    None.
    
*/

USB_ERROR USB_DEVICE_EventCallBackSet( USB_DEVICE_HANDLE usbDeviceHandle,
                                       const USB_DEVICE_CALLBACK callBackFunc );


// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_ControlEventCallBackSet
         ( USB_DEVICE_HANDLE usbDeviceHandle,
                            const USB_DEVICE_CONTROL_EVENT_CALLBACK *callBackFunc )

  Summary:
    Client can register its call-back function into the device layer to get
    control transfer events.

  Description:
    The USB Device Layer notifies the control transfer events to the client
    by calling callBackFunc.

  Precondition:
    The device layer must have been initialized by calling USB_DEVICE_Initialize
    and a valid handle to the instance must have been obtained by calling
    USB_DEVICE_Open.

  Parameters:
    usbDeviceHandle    - Pointer to the device layer handle that is returned from
                        USB_DEVICE_Open

    callBackFunc      - Pointer to the control transfer event handler. The device layer
                        notifies the client about control transfer event by
                        calling this function.

  Returns:
    Returns USB_ERROR_NONE if successful.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

USB_ERROR USB_DEVICE_ControlEventCallBackSet( USB_DEVICE_HANDLE usbDeviceHandle,
                     const USB_DEVICE_CONTROL_TRANSFER_CALLBACK callBackFunc );


// *****************************************************************************
/* Function:
    USB_DEVICE_STATE USB_DEVICE_GetDeviceState( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    Returns the current state of the USB device.

  Description:
    This function returns the current state of the USB device, as described in Chapter 9 of
    USB 2.0 Specification.

  Precondition:
    The USB device layer must have been initialized and opened before calling this
    function.

  Parameters:
    usbDeviceHandle    - Pointer to the device layer handle that is returned from
                        USB_DEVICE_Open
    
  Returns:
    USB_DEVICE_STATE_DETACHED        - Device is not in any of the known states
  
    USB_DEVICE_STATE_ATTACHED        - Device is attached to the USB, 
                                       but is not powered
    
    USB_DEVICE_STATE_POWERED         - Device is attached to the USB and powered, 
                                       but has not been reset
    
    USB_DEVICE_STATE_DEFAULT         - Device is attached to the USB and powered 
                                       and has been reset, but has not been assigned 
                                       a unique address
    
    USB_DEVICE_STATE_ADDRESS         - Device is attached to the USB, powered, 
                                       has been reset, and a unique device address 
                                       has been assigned
    
    USB_DEVICE_STATE_CONFIGURED      - Device is attached to the USB, powered, 
                                       has been reset, has a unique address, 
                                       is configured, and is not suspended
    
    USB_DEVICE_STATE_SUSPENDED       - Device is, at minimum, attached to the 
                                       USB and is powered and has not seen bus 
                                       activity for 3 ms. The device is still in 
                                       addresed state.

  Example:
    <code>
    USB_DEVICE_STATE usbDevState;
    
    // Get USB Device State.
    usbDevState = USB_DEVICE_GetDeviceState( usbDeviceHandle );
    
    switch(usbDevState)
    {
        case USB_DEVICE_STATE_ATTACHED:
            // Add code here            
            break;
            
        case USB_DEVICE_STATE_POWERED:
           // Add code here
           break;     
                  
        default:
            break;
     }     
    </code>

  Remarks:
    This function must be called only after the device layer is initialized and opened
    by calling USB_DEVICE_Initialize and USB_DEVICE_Open.
    
*/

USB_DEVICE_STATE USB_DEVICE_GetDeviceState(USB_DEVICE_HANDLE usbDeviceHandle);


// *****************************************************************************
/* Function:
    void USB_DEVICE_Tasks( SYS_MODULE_OBJ devLayerObj )

  Summary:
    USB Device layer calls all other function driver tasks in this function.
    It also generates and forwards events to its clients.

  Description:
    This function must be periodically called by the user application. The USB Device
    layer calls all other function driver tasks in this function. It also generates 
    and forwards events to its clients.
    

  Precondition:
    Device layer must have been initialized by calling USB_DEVICE_Initialize.

  Parameters:
    devLayerObj    - Pointer to the Device Layer Object that is returned from
                     USB_DEVICE_Initialize

  Returns:
    none.

  Example:
    <code>
    
    </code>

  Remarks:
    This function must be called only after the device layer is initialized by calling 
    function USB_DEVICE_Initialize.
    
*/

void USB_DEVICE_Tasks( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    uint8_t USB_DEVICE_GetConfigurationValue( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    Informs the client of the current USB device configuration set by the USB host.

  Description:
    This function returns the current active USB device configuration.

  Precondition:
    The USB Device Layer must have been initialized and opened before calling this
    function.

  Parameters:
    usbDeviceHandle    - Pointer to the Device Layer Handle that is returned from
                        USB_DEVICE_Open
    
  Returns:
    Present active configuration.

  Example:
    <code>
    </code>

  Remarks:
    This function must be called only after the device layer is initialized and opened
    by calling USB_DEVICE_Initialize and USB_DEVICE_Open.
    
*/

uint8_t USB_DEVICE_GetConfigurationValue( USB_DEVICE_HANDLE usbDeviceHandle );


// *****************************************************************************
/* Function:
    DRV_USB_SPEED USB_DEVICE_GetDeviceSpeed(USB_DEVICE_HANDLE usbDeviceHandle)

  Summary:
    Informs the client of the current operation speed of the USB bus.

  Description:
    The USB device stack supports both high speed and full speed operations.
    This function returns the current operation speed of the USB bus.

  Precondition:
    The USB device layer must have been initialized and a valid handle
    to USB device layer must have been opened.

  Parameters:
    usbDeviceHandle    - Pointer to device layer handle that is returned from
                        USB_DEVICE_Open
    
  Returns:
     
    USB_SPEED_LOW           -  USB module is at low speed
    
    USB_SPEED_FULL          -  USB module is at full speed
    
    USB_SPEED_HIGH          -  USB module is at high speed

  Example:
    <code>     
    </code>

  Remarks:
    This function must be called only after the device layer is initialized and opened
    by calling USB_DEVICE_Initialize and USB_DEVICE_Open.
    
*/

USB_SPEED USB_DEVICE_GetDeviceSpeed( USB_DEVICE_HANDLE usbDeviceHandle );


// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_EndpointEnable(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection,
                                        USB_TRANSFER_TYPE transferType,
                                        uint16_t endpointSize);

  Summary:
    This function enables a endpoint for the specified direction and endpoint
    size.

  Description:
    This function enables a endpoint for the specified  direction  and  endpoint
    size.  The function will  enable  the  endpoint  for  communication  in  one
    direction at a time.  It must be called twice if the  endpoint  is  required
    to communicate in both the directions, except for control endpoints.  If the
    endpoint  type   is   a   control   endpoint,   the   endpoint   is   always
    bi-directional  and  the  function   needs   to   be   called   only   once.
    The size of the endpoint must  match  the  wMaxPacketSize  reported  in  the
    endpoint  descriptor for this endpoint.  The function does not check if the
    endpoint  is  already in use.  It is the client's responsibility to make sure
    that a  endpoint  is  not accidently re-used.

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().

    endpointAndDirection    - Specifies the endpoint and direction.
    transferType            - Should be USB_TRANSFER_TYPE_CONTROL for control
                              endpoint, USB_TRANSFER_TYPE_BULK for bulk endpoint,
                              USB_TRANSFER_TYPE_INTERRUPT for interrupt endpoint
                              and USB_TRANSFER_TYPE_ISOCHRONOUS for isochronous
                              endpoint.
    endpointSize            - Maximum size (in bytes) of the endpoint as
                              reported in the endpoint descriptor.

  Returns:
    USB_ERROR_NONE - The endpoint was successfully enabled.
    USB_ERROR_DEVICE_ENDPOINT_INVALID - If the endpoint that is being accessed is
                                        is out of the valid endpoint defined for
                                        this driver instance.

  Example:
    <code>
    // This code snippet shows an example of how to enable endpoint
    // 0 for control transfers. Note that for a control endpoint, the
    // direction parameter is ignored. A control endpoint is always
    // bi-directional. Endpoint sizeis 64 bytes.

    USB_ENDPOINT ep;

    handle = USB_DEVICE_Open(USB_DEVICE_INDEX_0);
    ep.endpoint = 0;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointEnable(handle, ep, USB_TRANSFER_TYPE_CONTROL, 64);

    // This code snippet shows an example of how to set up a endpoint
    // for BULK IN transfer. For an IN transfer, data moves from device
    // to host. In this example, endpoint 1 is enabled. The maximum
    // packet size is 64.

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointEnable(handle, ep, USB_TRANSFER_TYPE_BULK, 64);

    // If endpoint 1 must also be set up for BULK OUT, then the enable
    // function must be called again, as shown here.

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_HOST_TO_DEVICE;

    USB_DEVICE_EndpointEnable(handle, ep, USB_TRANSFER_TYPE_BULK, 64);
    </code>

  Remarks:
    None.
*/
USB_ERROR USB_DEVICE_EndpointEnable(USB_DEVICE_HANDLE usbDeviceHandle,
                                    USB_ENDPOINT endpointAndDirection,
                                    USB_TRANSFER_TYPE transferType,
                                    uint16_t endpointSize);

// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_EndpointDisable(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection)

  Summary:
    This function disables an endpoint.

  Description:
    This function disables an endpoint. If the endpoint type is control type
    then both directions are disabled. For non-control endpoints, the function
    disables one direction at a time.

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    USB_ERROR_NONE - The endpoint was successfully enabled.
    USB_ERROR_DEVICE_ENDPOINT_INVALID - If the endpoint that is being accessed is
                                        is out of the valid endpoint defined for
                                        this driver instance.

  Example:
    <code>
    // This code snippet shows an example of how to disable
    // a control endpoint. Note that the direction parameter is ignored.
    // For a control endpoinnt, both the directions are disabled.

    handle = USB_DEVICE_Open(USB_DEVICE_INDEX_0);
    USB_ENDPOINT ep;

    ep.endpoint = 0;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointDisable(handle, ep );

    // This code snippet shows an example of how to disable a BULK IN
    // endpoint

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointDisable(handle, ep );

    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access to modify the endpoint features.
*/

USB_ERROR USB_DEVICE_EndpointDisable(USB_DEVICE_HANDLE usbDeviceHandle,
                                    USB_ENDPOINT endpointAndDirection);

// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_EndpointStall(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection)

  Summary:
    This function stalls an endpoint in the specified direction.

  Description:
    This function stalls an endpoint in the specified direction.

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    USB_ERROR_NONE - The endpoint was successfully enabled.
    USB_ERROR_DEVICE_ENDPOINT_INVALID - If the endpoint that is being accessed is
                                        is out of the valid endpoint defined for
                                        this driver instance.

  Example:
    <code>
    // This code snippet shows an example of how to stall an endpoint. In
    // this case , endpoint 1 IN direction is stalled.

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointStall(handle, ep);

    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access to modify the endpoint features.
*/

USB_ERROR USB_DEVICE_EndpointStall(USB_DEVICE_HANDLE usbDeviceHandle,
                                  USB_ENDPOINT endpointAndDirection);

// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_EndpointStallClear(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection)

  Summary:
    This function clears the stall on an endpoint in the specified direction.

  Description:
    This function clears the stall on an endpoint in the specified direction.

  Precondition:
    Client handle should be valid.

  Parameters:
     usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    USB_ERROR_NONE - The endpoint was successfully enabled.
    USB_ERROR_DEVICE_ENDPOINT_INVALID - If the endpoint that is being accessed is
                                        is out of the valid endpoint defined for
                                        this driver instance.

  Example:
    <code>
    // This code snippet shows an example of how to clear a stall. In this
    // example. the stall on endpoint 1 IN direction is cleared.

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    USB_DEVICE_EndpointStallClear(handle, ep);

    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access to modify the endpoint features.
*/
USB_ERROR USB_DEVICE_EndpointStallClear(USB_DEVICE_HANDLE usbDeviceHandle,
                                       USB_ENDPOINT endpointAndDirection);

// *****************************************************************************
/* Function:
   bool USB_DEVICE_EndpointIsEnabled(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection)

  Summary:
    This function returns the enable/ disable status of the specified endpoint
    and direction.

  Description:
    This function returns the enable/ disable status of the specified endpoint
    and direction.

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    Returns true if the endpoint is enabled, false otherwise.

  Example:
    <code>
    // This code snippet shows an example of how the
    // USB_DEVICE_EndpointIsEnabled() function can be used to obtain the
    // status of the endpoint 1 and IN direction.

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    if(DRV_USB_ENDPOINT_STATE_DISABLED ==
                USB_DEVICE_EndpointIsEnabled(handle, ep))
    {
        // Endpoint is disabled. Enaable endpoint.

        USB_DEVICE_EndpointEnable(handle, ep, USB_ENDPOINT_TYPE_BULK, 64);

    }

    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access to read the endpoint features.
*/

bool USB_DEVICE_EndpointIsEnabled(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection);

// *****************************************************************************
/* Function:
    bool USB_DEVICE_EndpointIsStalled(USB_DEVICE_HANDLE usbDeviceHandle,
                                        USB_ENDPOINT endpointAndDirection)

  Summary:
    This function returns the stall status of the specified endpoint
    and direction.

  Description:
    This function returns the stall status of the specified endpoint
    and direction.

  Precondition:
    Client handle should be valid.

  Parameters:
     usbDeviceHandle        - USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    Returns true if endpoint is stalled, false otherwise.

  Example:
    <code>
    // This code snippet shows an example of how the
    // USB_DEVICE_EndpointIsStalled() function can be used to obtain the
    // stall status of the endpoint 1 and IN direction.

    USB_ENDPOINT ep;

    ep.endpoint = 1;
    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;

    if(true == USB_DEVICE_EndpointIsStalled (handle, ep))
    {
        // Endpoint stall is enabled. Clear the stall.

        USB_DEVICE_EndpointStallClear(handle, ep);

    }

    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access to read the endpoint features.
*/

bool USB_DEVICE_EndpointIsStalled(USB_DEVICE_HANDLE usbDeviceHandle,
                                                         USB_ENDPOINT endpoint);

// *****************************************************************************
/* Function:
    USB_ERROR USB_DEVICE_IRPSubmit(USB_DEVICE_HANDLE usbDeviceHandle,
                                   USB_ENDPOINT endpointAndDirection,
                                   USB_DEVICE_IRP * irp);

  Summary:
    This function submits a I/O Request Packet (IRP) for  processing to the
    USB Driver.

  Description:
    This function submits a I/O Request  Packet  (IRP)  for  processing  to  the
    USB Driver.  The IRP allows a client to send and receive data from  the  USB
    Host.  The data will sent or received through the specified  endpoint.   The
    direction of the data transfer is indicated by the  direction  flag  in  the
    endpointAndDirection structure.  Submitting an  IRP  arms  the  endpoint  to
    either send data to or receive data from the  host.   If  an  IRP  is  under
    progress on the endpoint, then the  subsequent  IRP  submit  operation  will
    result in the IRPs getting queued.  The contents of the IRP  should  not  be
    changed till the IRP has been processed.

    Particular attention should be paid to  the  size  parameter  of  IRP.   The
    following should be noted:

    * The size parameter while sending data  to  the  host  can  be  less  than,
      greater than, equal to or be an exact multiple of maximum packet size  for
      the endpoint.  The maximum packet size for  the  endpoint  determines  the
      number of transactions required to process the IRP.
    * If the size parameter while sending data to the host is less than  maximum
      packet  size,   the   transfer   will   complete   in   one   transaction.
    * If the size parameter while sending data  to  the  host  is  greater  than
      maximum packet size, the IRP will be processed in  mulitple  transactions.
    * If the size parameter while sending data to the host is  equal  to  or  an
      exact multiple of the maximum  packet  size,  the  client  can  optionally
      ask  the  driver  to  send  a  Zero  Length  packet  by   specifying   the
      USB_DEVICE_IRP_FLAG_SEND_ZLP flag as the flag parameter.
    * The size parameter while receiving data from the host  must  be  an  exact
      multiple of the maximum packet size of the endpoint.  If this is  not  the
      case, the driver will return  a  USB_DEVICE_IRP_SUBMIT_RESULT_INVALID_SIZE
      result. If while processing the IRP, the driver receives less than maximum
      packet size or a ZLP from the  host,  the  driver  considers  the  IRP  as
      processed. The size paramter at this point contains the actual amount of
      data received from the host.

  Precondition:
    Client handle should be valid.

  Parameters:
     usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
 
    endpointAndDirection    - Specifies the endpoint and direction.
    irp                     - Pointer to the USB_DEVICE_IRP structure.

  Returns:
    USB_ERROR_NONE - if the IRP was submitted successful.
    USB_ERROR_IRP_SIZE_INVALID - if the size parameter of the IRP is not correct.
    USB_ERROR_IRP_QUEUE_FULL - if the driver IRP queue is full.

  Example:
    <code>
    // The following code snippet shows an example of how to schedule a
    // IRP to send data from device to host. Assume that max packet size
    // is 64 and endpoint is 1.

    USB_ENDPOINT ep;
    USB_DEVICE_IRP irp;

    ep.direction = USB_DATA_DIRECTION_DEVICE_TO_HOST;
    ep.endpoint = 1;

    irp.data = myDataBufferToSend;
    irp.size = 130;
    irp.flags = USB_DEVICE_IRP_FLAG_NONE;
    irp.callback = MyIRPCompletionCallback;
    irp.referenceData = (uintptr_t)&myDeviceLayerObj;

    if (USB_DEVICE_IRPSubmit(handle, ep, irp)
            != USB_ERROR_NONE)
    {
        // This means there was an error.
    }
    else
    {
        // The status of the IRP can be checked.
        while(irp.status != USB_DEVICE_IRP_STATUS_COMPLETED)
        {
            // Wait or run a task routine.
        }
    }

    // The following code snippet shows how the client can request
    // the driver to send a ZLP when the size is an exact multiple of
    // end point size.

    irp.data = myDataBufferToSend;
    irp.size = 128;
    irp.flags = USB_DEVICE_IRP_FLAG_SEND_ZLP;
    irp.callback = MyIRPCompletionCallback;
    irp.referenceData = (uintptr_t)&myDeviceLayerObj;

    // Note that while  receiving data from the host, the size should
    // be an exact multiple maximum packet size of the endpoint. In the
    // example below, the USB_DEVICE_IRPSubmit() function will
    // return a USB_DEVICE_IRP_SUBMIT_RESULT_INVALID_SIZE value.

    ep.direction = USB_DATA_DIRECTION_HOST_TO_DEVICE;
    ep.endpoint = 1;

    irp.data = myDataBufferToSend;
    irp.size = 60; // THIS SIZE IS NOT CORRECT
    irp.flags = USB_DEVICE_IRP_FLAG_NONE;
    irp.callback = MyIRPCompletionCallback;
    irp.referenceData = (uintptr_t)&myDeviceLayerObj;

    </code>

  Remarks:
    This function must not be called by the application clients. Application 
    must not submit IRP directly.
*/
USB_ERROR USB_DEVICE_IRPSubmit(USB_DEVICE_HANDLE usbDeviceHandle,
                                         USB_ENDPOINT endpointAndDirection,
                                         USB_DEVICE_IRP * irp);

// *****************************************************************************
/* Function:
    void USB_DEVICE_IRPCancelAll (USB_DEVICE_HANDLE usbDeviceHandle,
                                    USB_ENDPOINT endpointAndDirection);

  Summary:
    This function cancels all IRPs that are queued and in progress at the
    specified endpoint.

  Description:
    This function cancels all IRPs that  are  queued  and  in  progress  at  the
    specified endpoint.  The driver checks if IRPs are to be  cancelled  at  two
    instances; when it has called the IRP callback and is ready to proccess  the
    next IRP in the queue and when it is ready to process the  next  transaction
    in the the current IRP.  It is recommended that this function be  called  in
    the IRP callback of the IRP that just completed as this ensures that an  IRP
    in progress is not cancelled.  Cancelling an IRP that is progress may  cause
    disturbance to the USB host firmware.  Cancelling the  IRP  from  any  other
    location, other  than  a  IRP  callback  could  cause  an  IRP  that  is  in
    progress  to  get   cancelled.


  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle  -        USB device handle returned by USB_DEVICE_Open().
    endpointAndDirection    - Specifies the endpoint and direction.

  Returns:
    USB_ERROR_NONE - The endpoint was successfully enabled.
    USB_ERROR_DEVICE_ENDPOINT_INVALID - If the endpoint that is being accessed is
                                        is out of the valid endpoint defined for
                                        this driver instance.


  Example:
    <code>
    // This code snippet shows an exampl of how to cancel all IRPs.

    void MyIRPCallback(USB_DEVICE_IRP * irp)
    {
        // Check if this is setup command

        if(irp->status == USB_DEVICE_IRP_STATUS_SETUP)
        {
            if(IsSetupCommandSupported(irp->data) == false)
            {
                // This means that this setup command is not
                // supported. Stall the endpoint.

                USB_DEVICE_IRPCancelAll(handle, ep);
                USB_DEVICE_EndpointStall(handle, ep);
            }
         }
     }


    </code>

  Remarks:
    This function must not be called by the application clients. Application has
    no access modify the IRPs.
*/

USB_ERROR USB_DEVICE_IRPCancelAll (USB_DEVICE_HANDLE usbDeviceHandle,
                                    USB_ENDPOINT endpointAndDirection);


// *****************************************************************************
/* Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT
                    USB_DEVICE_ControlSend( USB_DEVICE_HANDLE usbDeviceHandle,
                           USB_DEVICE_CONTROL_TRANSFER_HANDLE controlXferHandle,
                            void *  data, size_t length)

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

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlSend
                          ( USB_DEVICE_HANDLE usbDeviceHandle,
                            void *  data, size_t length );


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
    data             -   Pointer to buffer that holds data.
    length           -   Size in bytes.

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

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlReceive
                              ( USB_DEVICE_HANDLE usbDeviceHandle,
                                USB_DEVICE_CONTROL_TRANSFER_HANDLE controlXferHandle,
                                void *  data, size_t length);


// *****************************************************************************
/* Function:
    USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlStatus
                        ( USB_DEVICE_HANDLE usbDeviceHandle,
                          USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                          USB_DEVICE_CONTROL_STATUS status)

  Summary:
    Initiates status stage of the control transfer.

  Description:

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle        -   USB device handle returned by USB_DEVICE_Open().
    controlTransferHandle  -   Control transfer handle that is returned by
                           bus event callback function.
    status                 -   USB_DEVICE_CONTROL_STATUS_SEND_ZLP/
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

USB_DEVICE_CONTROL_TRANSFER_RESULT USB_DEVICE_ControlStatus( 
                               USB_DEVICE_HANDLE usbDeviceHandle,
                               USB_DEVICE_CONTROL_STATUS status);


// *****************************************************************************
/* Function:
    USB_DEVICE_REMOTE_WAKEUP_STATUS USB_DEVICE_RemoteWakeupIsEnabled
                                          ( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    Gets the "Remote wakeup" status of the device.

  Description:

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    -   USB device handle returned by USB_DEVICE_Open().
    
  Returns:
    USB_DEVICE_REMOTE_WAKEUP_ENABLED -  Remote wakeup is enabled.
    USB_DEVICE_REMOTE_WAKEUP_DISABLED - Remote wakeup is disabled.

  Example:
    <code>

    </code>

  Remarks:

*/
USB_DEVICE_REMOTE_WAKEUP_STATUS USB_DEVICE_RemoteWakeupIsEnabled
                                        ( USB_DEVICE_HANDLE usbDeviceHandle );


// *****************************************************************************
/* Function:
    void USB_DEVICE_PowerStateSet( USB_DEVICE_HANDLE usbDeviceHandle,
                               USB_DEVICE_POWER_STATE powerState )

  Summary:
    Sets power state of the device.

  Description:
   Application clients can use this function to set the power state of the
   device. A USB device can be bus powered ot self powered.

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle     -   USB device handle returned by USB_DEVICE_Open().
    powerState          -   USB_DEVICE_POWER_STATE_BUS_POWERED/
                            USB_DEVICE_POWER_STATE_SELF_POWERED

  Returns:
    None.
 
  Example:
    <code>

    </code>

  Remarks:

*/
void USB_DEVICE_PowerStateSet( USB_DEVICE_HANDLE usbDeviceHandle,
                               USB_DEVICE_POWER_STATE powerState );


// *****************************************************************************
/* Function:
    void USB_DEVICE_Attach( USB_DEVICE_HANDLE usbDeviceHandle )

  Summary:
    This function will attach the device to the USB.

  Description:
    This function will attach the device to the USB.  It does this  by  enabling
    the pull up resistors on the D+ or D- lines. This function should be called
    when the USB device layer is ready  to  receive  communication  from  the  host
    (typically after all initialization is complete).

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle   - Client's USB device layer handle (returned from
                        USB_DEVICE_Open)

  Returns:
    None.

  Example:
    <code>

    USB_DEVICE_INIT deviceLayerInit;
    SYS_MODULE_OBJ usbDeviceObj;
    USB_DEVICE_HANDLE usbDeviceHandle;

     // System module initialization
    deviceLayerInit.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
     // Identifies peripheral (PLIB-level) ID
    deviceLayerInit.usbID = USB_ID_1;
    // Boolean flag: true -> Stop USB module in Idle Mode
    deviceLayerInit.stopInIdle = false;
    // Boolean flag: true -> Suspend USB in Sleep Mode
    deviceLayerInit.suspendInSleep = false;
     // Interrupt Source for USB module
    deviceLayerInit.interruptSource = INT_SOURCE_USB_1;
    // Number of function drivers registered to this instance of the
    USB device layer
    deviceLayerInit.registeredFuncCount = 1;
    // Function driver table registered to this instance of the USB device layer
    deviceLayerInit.registeredFunctions = funcRegistrationTable;
    // Pointer to USB Descriptor structure
    deviceLayerInit.usbMasterDescriptor   = &usbMasterDescriptor;

    // USB device initialization
    usbDeviceObj = USB_DEVICE_Initialize(USB_DEVICE_INDEX_0, &deviceLayerInit);

    if (SYS_MODULE_OBJ_INVALID == usbDeviceObj)
    {
        // Handle error
    }

    // Get an handle to the USB device layer.
    usbDeviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                                                      DRV_IO_INTENT_BLOCKING );

    if(USB_DEVICE_HANDLE_INVALID == usbDeviceHandle)
    {
        // Failed to open handle.
        // Handle error.
    }

    // Now, connect device to USB
    USB_DEVICE_Attach(usbDeviceHandle);

    </code>

  Remarks:
    None.
*/

void USB_DEVICE_Attach( USB_DEVICE_HANDLE usbDeviceHandle );


// *****************************************************************************
/* Function:
    void USB_DEVICE_Detach( USB_DEVICE_HANDLE usbDeviceHandle );

  Summary:
    This function will detach the device from the USB. 

  Description:
    This function will detach  the  device  from  the  USB.   It  does  this  by
    disabling the pull up resistors on the D+ or D- lines. This function should
    be called when the application wants to disconnect the device  from  the  bus
    (typically to implement a soft detach or switch  to  host  mode  operation).

  Precondition:
    Client handle should be valid.

  Parameters:
    usbDeviceHandle    - Client's driver handle (returned from USB_DEVICE_Open)

  Returns:
    None.

  Example:
    <code>
    USB_DEVICE_HANDLE usbDeviceHandle;

    // Detach the device from the USB
    USB_DEVICE_Detach( usbDeviceHandle );

    </code>

  Remarks:
    None.
*/

void USB_DEVICE_Detach( USB_DEVICE_HANDLE usbDeviceHandle );


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

void USB_DEVICE_ResumeStart( USB_DEVICE_HANDLE usbDeviceHandle );


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

void USB_DEVICE_ResumeStop ( USB_DEVICE_HANDLE usbDeviceHandle );

// *****************************************************************************
// *****************************************************************************
// Section: Included Files (continued)
// *****************************************************************************
// *****************************************************************************
/*  The file included below maps the interface definitions above to appropriate
    static implementations, depending on build mode.
*/

#include "src/usb_device_mapping.h"

#endif
