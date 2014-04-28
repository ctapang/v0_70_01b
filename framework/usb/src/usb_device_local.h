/*******************************************************************************
  USB Device Layer local Header File

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_local.h

  Summary:
    USB device layer local header file.

  Description:
    This header file contains private data types required for usb_device_layer.c.
    This header file must not be included in the application.
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

#ifndef _USB_DEVICE_LOCAL_H
#define _USB_DEVICE_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// ***************************************************************************** /

#include "../usb_device.h"





// *****************************************************************************
/* USB device layer function driver data

  Summary:
    This structure has members that has information about the function drivers.

  Description:
    This structure has members that has information about the function drivers.

  Remarks:
    None.

*/

typedef struct _USB_DEVICE_FUNC_DRIVER_DATA_
{

    /* First Interface number used by this instance of function driver*/
    uint8_t                     interfaceNumber;

    uint8_t                     numberOfInterfaces;

    /* Function driver instance index */
    SYS_MODULE_INDEX            funcDriverIndex;

    /* Pointer to a structure which contains function driver initialization data */
    void*                       funcDriverInit;

    /* Pinter to a standard structure that exposes function driver APIs to USB device layer*/
    USB_DEVICE_FUNCTION_DRIVER*  driver;



}USB_DEVICE_FUNC_DRIVER_DATA;


typedef union
{
    struct{
       
        /* Self powered */
        unsigned selfPowered:1;
        /* Remote wake up */
        unsigned remoteWakeup:1;
         /* Reserved bits */
        unsigned :6;
        unsigned :8 ;
    };

    struct{
        
        /* Endpoint halt */
        unsigned endPointHalt:1;
        /*Reserved bits */
        unsigned :7;
        /* Reserved bits */
        unsigned :8;
    };
    uint16_t status;
}USB_DEVICE_STATUS_RESPONSE;


typedef struct _USB_DEVICE_CONTROL_TRANSFER_STRUCT
{
    /* Control transfer state */
    bool  inProgress;

    uint8_t rxDataCount;

    uint8_t expectedRxDataCount;

    SYS_MODULE_INDEX handlerIndex;

    uint8_t * rxBuffer;

    /* Temporary pointer to function driver provided control transfer function.
     The setup packet will be forwarded to this function driver provided control transfer function */
    void (* handler)(   USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                        SYS_MODULE_INDEX handlerIndex,
                        USB_DEVICE_CONTROL_TRANSFER_EVENT controlTransferState,
                        USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * eventData );

     /* Setup packet buffer */
    //SETUP_PKT setupPacket;

      USB_DEVICE_CONTROL_TRANSFER_HANDLE handle;


}USB_DEVICE_CONTROL_TRANSFER_STRUCT;


// *****************************************************************************
/* USB Device Handle

  Summary:


  Description:


  Remarks:
    None.

*/

typedef struct _USB_DEVICE_INSTANCE_STRUCT_
{
    /* State of this instance */
    SYS_STATUS usbDeviceInstanceState;

    /* USB Device Ch-9 State */
    USB_DEVICE_STATE    usbDeviceState;

     /* USB Device state before entering suspend state */
    USB_DEVICE_STATE usbDevStatePriorSuspend;

    /* Pointer to master descriptor table */
    USB_MASTER_DESCRIPTOR *ptrMasterDescTable;

    /* Number of function driver instances registered */
    uint16_t    registeredFuncDriverCount;

     /* Function table registered to this instance of the USB device layer */
    USB_DEVICE_FUNC_REGISTRATION_TABLE  *registeredFuncDrivers;

     /* This instance index */
    SYS_MODULE_INDEX usbDevLayerIndex;
    
    /* USB Controller driver handle */
    DRV_HANDLE usbCDHandle;

   
    /* EP0 rx buffer*/
    uint8_t ep0RxBuffer[USB_DEVICE_EP0_BUFFER_SIZE];

    /* Tx IRP */
    USB_DEVICE_IRP  irpEp0Tx[2 * DRV_USB_MAX_QUEUE_LENGTH]; // only for endpoint 0

    /* Rx IRP */
    USB_DEVICE_IRP  irpEp0Rx[2 * DRV_USB_MAX_QUEUE_LENGTH]; // only for endpoint 0

    /* USB Speed - high speed or full speed */
    USB_SPEED    usbSpeed;

    /* Set address is pending */
    bool setAddressPending;

    /* Device address */
    uint8_t deviceAddress;   

    /* Current active configuration */
    uint8_t activeConfiguration;

    /* Maximum configurations available for the selected speed*/
    uint8_t maxConfigs;

    /* Pointer to configuration descriptor group for the selected speed*/
    USB_DEVICE_CONFIG_DESCS_PTR configDescriptorsPtr;

    /* Pointer to active host selected descriptor */
    uint8_t * pActiveConfigDesc;

    /* Currently active events */
    USB_DEVICE_EVENT event;

      

    /* The two bytes that we are going to reply with for
     standard GET_STATUS request */
    USB_DEVICE_STATUS_RESPONSE getStatusResponse;

    /* Self powered state*/
    USB_DEVICE_POWER_STATE selfPowered;

    bool remoteWakeupStatus;

    /* Control transfer related structure */
    USB_DEVICE_CONTROL_TRANSFER_STRUCT controlTransfer;

    USB_DEVICE_HANDLE hClientInternalOperation;



}USB_DEVICE_INSTANCE_STRUCT;


// *****************************************************************************
/*  USB device layer client object structure

  Summary:
    USB device layer client object structure.

  Description:
    USB device layer client object structure.

  Remarks:
   None.

*/

typedef struct _USB_DEVICE_CLIENT_STRUCT_
{
    

    /* Client status */
    DRV_CLIENT_STATUS clientState;

    /* Pointer to the bus event callback function */
    USB_DEVICE_CALLBACK callBackFunc;

    /* Pointer to control transfer event callback
     function */
    USB_DEVICE_CONTROL_TRANSFER_CALLBACK controlTransferEventCallback;
      
    /* This instance of the USB device layer */
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance;


}*USB_DEVICE_CLIENT_HANDLE, USB_DEVICE_CLIENT_STRUCT;



#endif