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
#include "mouse.h"


// *****************************************************************************
/* Application States

  Summary:
    Enumeration of possible application states.

  Description:
    Enumeration of possible application states.

  Remarks:
    None.
*/

typedef enum
{
    /* Application opens the device layer in this state */
    APP_STATE_INIT,

    /* Application waits for configuration in this state */
    APP_STATE_WAIT_FOR_CONFIGURATION,

    /* Application runs mouse emulation in this state */
    APP_STATE_MOUSE_EMULATE,

    /* Application error state */
    APP_STATE_ERROR

}APP_STATES;

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
    /* Application state */
    APP_STATES state; 

    /* device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE  deviceHandle;

    /* Is device configured */
    bool isConfigured;

    /* Mouse Report */
    MOUSE_REPORT mouseReport;

    /* If true, then mouse is emulated */
    bool emulateMouse;

    /* Switch state variables*/
    bool ignoreSwitchPress;

    bool isSwitchPressed;

    /* Mouse x coordinate*/
    MOUSE_COORDINATE xCoordinate;

    /* Mouse y coordinate*/
    MOUSE_COORDINATE yCoordinate;

    /* Mouse buttons*/
    MOUSE_BUTTON_STATE mouseButton[MOUSE_BUTTON_NUMBERS];

    /* HID instance associated with this app object*/
    SYS_MODULE_INDEX hidInstance;

    /* Transfer handle */
    USB_DEVICE_HID_TRANSFER_HANDLE reportTransferHandle;

    /* Tracks the progress of the report send */
    bool isMouseReportSendBusy;

    /* Device Layer System Module Object */
    SYS_MODULE_OBJ deviceLayerObject;

} APP_DATA;

/********************************************************
 * Application Event Handler for USB Device Layer events
 ********************************************************/
void APP_USBDeviceEventHandler(USB_DEVICE_EVENT events,
        USB_DEVICE_EVENT_DATA * pData);

/********************************************************
 * Application Initialize Function. Called from
 * SYS_Initialize() function.
 ********************************************************/
void APP_Initialize(void);

/********************************************************
 * Application Tasks Function. Called from
 * SYS_Tasks() function.
 ********************************************************/
void APP_Tasks(void);

/********************************************************
 * Function Driver Registration Table
 ********************************************************/
extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1];

/********************************************************
 * Application Data Object
 ********************************************************/
extern APP_DATA appData;

/********************************************************
 * USB Device Layer Master Descriptor
 ********************************************************/
extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;


#endif
