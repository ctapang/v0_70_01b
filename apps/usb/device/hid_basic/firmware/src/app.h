/*******************************************************************************
 USB HID DEMO

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
#include "usb/usb_device_hid.h"


#define HID_RPT01_SIZE          28

// *****************************************************************************
/* Application Data

  Summary:
    Holds switch data

  Description:
    This structure holds the switch data

  Remarks:
    This structure is used by the appplication to process a switch press.
*/

typedef struct
{
    bool    wasSwitchPressed;
    unsigned int pressedCount;
}
SWITCH_STATE;


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
    DRV_HANDLE              usbDevHandle;

    /* LED blink status*/
    bool blinkStatusValid;
    
    /* Recieve data buffer */
    uint8_t receiveDataBuffer[64];

    /* Transmit data buffer */
    uint8_t  transmitDataBuffer[64];

   
    /* Device configured */
    bool deviceConfigured;

    /*Switch state*/
    SWITCH_STATE switch1;

    /* Switch was pressed */
    bool switchPressed;

    /* Send report transfer handle*/
    USB_DEVICE_HID_TRANSFER_HANDLE txTransferHandle;

    /* Receive report transfer handle */
    USB_DEVICE_HID_TRANSFER_HANDLE rxTransferHandle;

    /* Configuration value selected by the host*/
    uint8_t configurationValue;

    /* USB speed*/
    USB_SPEED usbSpeed;

    /* HID data received flag*/
    bool hidDataReceived;

    /* HID data transmitted flag */
    bool hidDataTransmitted;

    /* HID data transmitted flag*/
    bool flagDataTransmitted;
    
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

/* Application USB Device Layer event handler function */

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT events,
        USB_DEVICE_EVENT_DATA * eventData);

 
extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1];
extern SYS_MODULE_OBJ driverObjectHandle, usbDeviceObj;

extern APP_DATA appData;

extern APP_DRV_OBJECTS appDrvObject;
/* Device Descriptor */
extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

void APP_Initialize ( void );
void APP_Tasks (void );

/* Application USB Device HID Event Handler Function */
USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler (
                            USB_DEVICE_HID_INDEX iHID,
                            USB_DEVICE_HID_EVENT event,
                            USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                            void * eventData,
                            uintptr_t userData );

#endif
