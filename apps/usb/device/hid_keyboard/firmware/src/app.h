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
#include "keyboard.h"


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

    /* Application checks if an output report is available */
    APP_STATE_CHECK_FOR_OUTPUT_REPORT,

    /* Application updates the switch states */
    APP_STATE_SWITCH_PROCESS,

    /* Application checks if it is still configured*/
    APP_STATE_CHECK_IF_CONFIGURED,

    /* Application emulates keyboard */
    APP_STATE_EMULATE_KEYBOARD,

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
    /* Handle to the device layer */
    USB_DEVICE_HANDLE deviceHandle;
 
    /* Application HID instance */
    USB_DEVICE_HID_INDEX hidInstance;

    /* Application state */
    APP_STATES state;

    /* Is device configured */
    bool isConfigured;

    /*Keyboard Report to be transmitted*/
    KEYBOARD_INPUT_REPORT keyboardInputReport;

    /* Keyboard modifier keys*/
    KEYBOARD_MODIFIER_KEYS keyboardModifierKeys;

    /* Keyboard output report */
    KEYBOARD_OUTPUT_REPORT keyboardOutputReport;

    /* Key code array*/
    KEYBOARD_KEYCODE_ARRAY keyCodeArray;

    /* Switch state*/
    bool ignoreSwitchPress;

    /* Tracks switch press*/
    bool isSwitchPressed;
    
    /* Track the send report status */
    bool isReportSentComplete;

    /* Track if a report was received */
    bool isReportReceived;

    /* Receive transfer handle */
    USB_DEVICE_HID_TRANSFER_HANDLE receiveTransferHandle;

    /* Send transfer handle */
    USB_DEVICE_HID_TRANSFER_HANDLE sendTransferHandle;

    /* Keycode to be sent */
    USB_HID_KEYBOARD_KEYPAD key;

    
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
 * System Tasks Function. Called from
 * main() function.
 ********************************************************/
void SYS_Tasks(void);

/********************************************************
 * System Initialize Function. Called from
 * main() function.
 ********************************************************/
void SYS_Initialize(void * data);

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

/********************************************************
 * Application State Reset function.
 ********************************************************/
void APP_StateReset(void);

/********************************************************
 * Switch Debounce period.
 ********************************************************/
#define SWITCH_DEBOUNCE ((uint32_t)0x1E8480 * 8)


#endif
