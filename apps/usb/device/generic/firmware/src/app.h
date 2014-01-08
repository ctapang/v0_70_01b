/*******************************************************************************
 Generic USB driver DEMO

 Company:
 Microchip Technology Inc.

 File Name:
 app.h

 Summary:
 Application specific header file.

 Description:
 Application specific header file.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
 Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _APP_H_
#define _APP_H_

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "system_config.h"
#include "system/system.h"
#include "bsp_config.h"
#include "usb/usb_common.h"
#include "driver/usb/drv_usb.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_device.h"
#include "usb/usb_device_generic.h"

// *****************************************************************************
/* Application State

  Summary:
    Defines the various application states

  Description:
    Defines the various application states

  Remarks:
    This enumeration is used by the application to track various
    application states.
*/

typedef enum
{
    /* Wait for the device to get configured */
    APP_WAIT_FOR_DEVICE_CONFIGURE,

    /* Get the pipe handle */
    APP_GET_PIPE_HANDLE,

    /* Check if a command is available */
    APP_CHECK_COMMAND,

    /* Process LED Command */
    APP_PROCESS_LED_COMMAND,

    /* Wait for TX to get ready */
    APP_WAIT_FOR_TX_READY,

    /* An error occurred */
    APP_ERROR

}
APP_STATE;


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
    /* device layer handle returned by device layer open function */
    DRV_HANDLE usbDevHandle;

    /* Recieve data buffer */
    uint8_t receivedDataBuffer[64];

    /* Transmit data buffer */
    uint8_t  transmitDataBuffer[2];

        /* Track device configuration */
    bool deviceIsConfigured;

    /* Configuration value */
    uint8_t configValue;

    /* speed */
    USB_SPEED speed;

    /* ep data sent */
    bool epDataWritePending;

    /* ep data received */
    bool epDataReadPending;

    /* Transfer handle */
    USB_DEVICE_GENERIC_TRANSFER_HANDLE writeTranferHandle;

    /* Transfer handle */
    USB_DEVICE_GENERIC_TRANSFER_HANDLE readTranferHandle;

    USB_ENDPOINT endpointTx;

    USB_ENDPOINT endpointRx;

} APP_DATA;



// *****************************************************************************
/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

typedef struct
{
    /* device layer object returned by device layer init function */
    SYS_MODULE_OBJ              usbDevObject;

} APP_DRV_OBJECTS;

/*********************************************************
 * Application USB Device Layer Event Handler.
 *********************************************************/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT events,
        USB_DEVICE_EVENT_DATA * eventData);

/*********************************************************
 * Application USB Device Generic Function Driver
 * Event Handler.
 *********************************************************/
void APP_USBDeviceGenericEventHandler ( USB_DEVICE_GENERIC_INDEX iGEN,
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    USB_DEVICE_GENERIC_EVENT event, USB_DEVICE_GENERIC_EVENT_DATA * eventData,
    uintptr_t userData );

/************************************************************
 * Application Initialize routine called from SYS_Initialize
 * routine.
 ************************************************************/
void APP_Initialize (void);

/************************************************************
 * Application Initialize routine called from SYS_Initialize
 * routine.
 ************************************************************/
void APP_Tasks(void);

/************************************************************
 * USB Devic Layer Function Driver Registration Table.
 ************************************************************/
extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1];

/************************************************************
 * Application Data.
 ************************************************************/
extern APP_DRV_OBJECTS appDrvObject;
extern APP_DATA appData;

/************************************************************
 * USB Device Layer Master Descriptor Table.
 ************************************************************/
extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

#endif
