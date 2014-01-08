/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    Application Header file

  Description:
    Application Header file.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "system_config.h"
#include "bsp_config.h"
#include "system/common/sys_module.h"
#include "system/common/sys_common.h"
#include "system/int/sys_int.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_common.h"
#include "usb/usb_device.h"
#include "usb/usb_device_cdc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

#define COM1 0
#define COM2 1

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum
{
    /* Application opens and attaches the device here */
    APP_STATE_INIT = 0,

    /* Application waits for device configuration*/
    APP_STATE_WAIT_FOR_CONFIGURATION,

    /* Application checks if the device is still configured*/
    APP_STATE_CHECK_IF_CONFIGURED,

   /* A character is received from host */
    APP_STATE_CHECK_FOR_READ_COMPLETE,

    /* Wait for the transmit to get completed */
    APP_STATE_CHECK_FOR_WRITE_COMPLETE,

    /* Wait for the write to complete */
    APP_STATE_WAIT_FOR_WRITE_COMPLETE,

    /* Application Error state*/
    APP_STATE_ERROR

} APP_STATES;

/******************************************************
 * Application COM Port Object
 ******************************************************/

typedef struct
{
    USB_DEVICE_CDC_INDEX cdcInstance;

    /* Read Data Buffer */
    uint8_t readBuffer[64];

    /* Write Data Buffer */
    uint8_t writeBuffer[64];

    /* Set Line Coding Data */
    USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING setLineCodingData;

    /* Get Line Coding Data */
    USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING getLineCodingData;

    /* Contorl Line State */
    USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE controlLineStateData;

    /* Break data */
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK breakData;

    /* Read transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE readTransferHandle;

    /* Write transfer handle */
    USB_DEVICE_CDC_TRANSFER_HANDLE writeTransferHandle;

    /* True if a character was read */
    bool isReadComplete;

    /* True if a character was written*/
    bool isWriteComplete;
    
}APP_COM_PORT_OBJECT;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/

typedef struct
{
    /* Device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE deviceHandle;

    /* Application's current state*/
    APP_STATES state;

    /* Device configured state */
    bool isConfigured;

    APP_COM_PORT_OBJECT appCOMPortObjects[2];
   
} APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

/*******************************************************************************
  Function:
    void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event,
                                    USB_DEVICE_EVENT_DATA * eventData);

  Summary:
    Device layer event notification callback.

  Description:
    This routine defines the device layer event notification callback.

  Precondition:
    The device layer should be opened by the application and the callback should
    be registered with the device layer.

  Parameters:
    events  - specific device event

  Returns:
    None.

  Remarks:
    None.
*/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event,
                                    USB_DEVICE_EVENT_DATA * eventData);

/*******************************************************************************
  Function:
    void APP_USBDeviceCDCEventHandler
    (
        USB_DEVICE_CDC_INDEX index ,
        USB_DEVICE_CDC_EVENT event ,
        USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void* pData,
        uintptr_t userData 
    )

  Summary:
    CDC function driver event notification callback.

  Description:
    This routine defines the CDC function driver event notification callback.

  Precondition:
    The callback should be registered with the CDC function driver.

  Parameters:
    iCDC        - cdc function driver handle
    callback    - callabck type (USB_DEVICE_CDC_CALLBACK_TYPE)
    event       - specific event occured

  Returns:
    None.

  Remarks:
    None.
*/
void APP_USBDeviceCDCEventHandler
(
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void* pData,
    uintptr_t userData
);

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
 * Application Intitialization routine. This is called from SYS_Initialize()
 ******************************************************************************/

void APP_Initialize ( void );


/*********************************************************************
 * Application Tasks routine. This is called from SYS_Tasks().
 *********************************************************************/

void APP_Tasks ( void );

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

/****************************
 * Application Data Object
 *****************************/
extern APP_DATA appData;

/*****************************************
 * USB Device Function Driver Registration
 * Table
 ******************************************/
extern const USB_DEVICE_FUNC_REGISTRATION_TABLE 
            funcRegistrationTable[USB_DEVICE_CDC_INSTANCES_NUMBER];

/*****************************************
 * USB Device Master Descriptor
 ******************************************/
extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

/*****************************************
 * CDC Function Driver function pointers.
 ******************************************/
extern USB_DEVICE_FUNCTION_DRIVER cdcFuncDriver;

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

