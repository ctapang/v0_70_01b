/*******************************************************************************
 USB HID DEMO

 Company:
 Microchip Technology Inc.

 File Name:
 app.c

 Summary:
 This file contains all application specific initialization and functionality.

 Description:
 
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"

/*****************************************
 * Create an application data object
 *****************************************/

APP_DATA appData;

/********************************************************
 * Application switch press routine
 ********************************************************/

void APP_ProcessSwitchPress(APP_DATA * appData)
{
    /* This function checks if the switch is pressed and then
     * debounces the switch press*/

    if(!appData->ignoreSwitchPress)
    {
        /* Check if the switch was pressed */
        if(BSP_ReadSwitch(SWITCH_1) == BSP_SWITCH_STATE_PRESSED)
        {
            /* The switch was pressed. Ignore any more switch presses
             * and then start the debounce timer. The debounce timer
             * is implemented using the core timer */

            appData->ignoreSwitchPress = true;
            BSP_StartTimer(APP_SWITCH_DEBOUNCE_PERIOD);
            SYS_INT_SourceEnable(INT_SOURCE_TIMER_CORE);

        }
    }
}

/********************************************************
 * Application Keyboard LED update routine.
 ********************************************************/

void APP_KeyboardLEDStatus(void)
{
    /* This measn we have a valid output report from the host*/

    if(appData.keyboardOutputReport.ledState.numLock
            == KEYBOARD_LED_STATE_ON)
    {
        BSP_SwitchONLED(LED_2);
    }
    else
    {
        BSP_SwitchOFFLED(LED_2);
    }

    if(appData.keyboardOutputReport.ledState.capsLock
            == KEYBOARD_LED_STATE_ON)
    {
        BSP_SwitchONLED(LED_1);
    }
    else
    {
        BSP_SwitchOFFLED(LED_1);
    }
}

/********************************************************
 * Application Keyboard Emulation Routine
 ********************************************************/

void APP_EmulateKeyboard(void)
{

    if(appData.isSwitchPressed)
    {
        /* Clear the switch pressed flag */
        appData.isSwitchPressed = false;

        /* If the switch was pressed, update the key counter and then
         * add the key to the keycode array. */
        appData.key ++;

        if(appData.key == USB_HID_KEYBOARD_KEYPAD_KEYBOARD_RETURN_ENTER)
        {
            appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
        }

        appData.keyCodeArray.keyCode[0] = appData.key;

        /* Start a switch press ignore counter */
    }
    else
    {
        /* Indicate no event */

         appData.keyCodeArray.keyCode[0] =
                 USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    }

    KEYBOARD_InputReportCreate(&appData.keyCodeArray,
            &appData.keyboardModifierKeys, &appData.keyboardInputReport);

}


/*******************************************************************************
  Function:
    void APP_Tasks(void)

  Summary:
    Application routines. 

  Description:
    This routine reads the HID report from PC and depending on the PC command
    takes action to toggle LED. Reads switch status and reports to PC.
    

  Parameters:
    None.

  Returns:
    None.*/

void APP_Tasks (void )
{
    switch(appData.state)
    {
        case APP_STATE_INIT:

            /* Open an instance of the device layer */
            appData.deviceHandle = USB_DEVICE_Open( 0, DRV_IO_INTENT_READWRITE );

            /* Register a callback with device layer to get
             * event notification (for end point 0) */
            USB_DEVICE_EventCallBackSet(appData.deviceHandle,
                    APP_USBDeviceEventHandler);

            /* Attach the device */

            USB_DEVICE_Attach(appData.deviceHandle);

            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;

            break;
        
        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device is configured. The
             * isConfigured flag is updated in the
             * Device Event Handler */

            if(appData.isConfigured)
            {
                /* Initialize the flag and place a request for a
                 * output report */

                appData.isReportReceived = false;

                USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                        &appData.receiveTransferHandle,
                        (uint8_t *)&appData.keyboardOutputReport,1);

                appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            }

            break;

        case APP_STATE_CHECK_IF_CONFIGURED:

            /* This state is needed because the device can get
             * unconfigured asynchronously. Any application state
             * machine reset should happen within the state machine
             * context only. */

            if(appData.isConfigured)
            {
                appData.state = APP_STATE_SWITCH_PROCESS;
            }
            else
            {
                /* This means the device got de-configured.
                 * We reset the state and the wait for configuration */

                APP_StateReset();
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_SWITCH_PROCESS:

            /* Process the switch state and go to the
             * next state. */
            
            APP_ProcessSwitchPress(&appData);
            appData.state = APP_STATE_CHECK_FOR_OUTPUT_REPORT;
            break;

        case APP_STATE_CHECK_FOR_OUTPUT_REPORT:

            if(appData.isReportReceived == true)
            {
                /* Update the LED and schedule and
                 * request */

                APP_KeyboardLEDStatus();

                appData.isReportReceived = false;
                USB_DEVICE_HID_ReportReceive(appData.hidInstance,
                        &appData.receiveTransferHandle,
                        (uint8_t *)&appData.keyboardOutputReport,1);
            }

            appData.state = APP_STATE_EMULATE_KEYBOARD;
            break;

        case APP_STATE_EMULATE_KEYBOARD:

            if(appData.isReportSentComplete)
            {
                /* This means report can be sent*/
                
                APP_EmulateKeyboard();
                
                appData.isReportSentComplete = false;
                USB_DEVICE_HID_ReportSend(appData.hidInstance,
                    &appData.sendTransferHandle,
                    (uint8_t *)&appData.keyboardInputReport,
                    sizeof(KEYBOARD_INPUT_REPORT));
             }

            appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            break;

        case APP_STATE_ERROR:
            break;

        default:
            break;
    }
  
}

/**********************************************
 * This function is called by when the device
 * is de-configured. It resets the application
 * state in anticipation for the next device
 * configured event
 **********************************************/

void APP_StateReset(void)
{
    appData.isReportReceived = false;
    appData.isReportSentComplete = true;
    appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
    appData.keyboardModifierKeys.modifierkeys = 0;
    appData.keyboardOutputReport.data = 0;
    appData.isSwitchPressed = false;
    appData.ignoreSwitchPress = false;
}

/**********************************************
 * This function is called by SYS_Initialize()
 * function and run after power up.
 **********************************************/

void APP_Initialize ( void )
{
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
    appData.isConfigured = false;

    /* Initialize the keycode array */
    appData.key = USB_HID_KEYBOARD_KEYPAD_KEYBOARD_A;
    appData.keyCodeArray.keyCode[0] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[1] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[2] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[3] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[4] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    appData.keyCodeArray.keyCode[5] = USB_HID_KEYBOARD_KEYPAD_RESERVED_NO_EVENT_INDICATED;
    
    /* Initialize the modifier keys */
    appData.keyboardModifierKeys.modifierkeys = 0;

    /* Initialise the led state */
    appData.keyboardOutputReport.data = 0;

    /* Intialize the switch state */
    appData.isSwitchPressed = false;
    appData.ignoreSwitchPress = false;

    /* Initialize the HID instance index.  */
    appData.hidInstance = 0;

    /* Initialize tracking variables */
    appData.isReportReceived = false;
    appData.isReportSentComplete = true;

    /* Initialize the application state*/
    appData.state = APP_STATE_INIT;

    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

}

USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler
(
    USB_DEVICE_HID_INDEX hidInstance,
    USB_DEVICE_HID_EVENT event,
    USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * eventData, uintptr_t userData
)
{
    APP_DATA * appData = (APP_DATA *)userData;

    switch(event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:

            /* This means the mouse report was sent.
             We are free to send another report */

            appData->isReportSentComplete = true;
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:

            /* This means we have received a report */
            appData->isReportReceived = true;
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:

            /* For now just accept this as is */
            USB_DEVICE_HID_ControlStatus(hidInstance, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

        default:
            break;
    }

    return USB_DEVICE_HID_EVENT_RESPONSE_NONE;
}

/*******************************************************************************
  Function:
    void APP_USBDeviceEventHandler (USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * eventData)

  Summary:
    Event callback generated by USB device layer.

  Description:
    This event handler will handle all device layer events.

  Parameters:
    None.

  Returns:
    None.*/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * eventData)
{
    switch(event)
    {
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            /* Device got deconfigured */

            appData.isConfigured = false;
            BSP_SwitchONLED ( LED_1);
            BSP_SwitchONLED ( LED_2);
            BSP_SwitchOFFLED ( LED_3);

            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* Device is configured */

            if(eventData->eventConfigured.configurationValue == 1)
            {
                appData.isConfigured = true;

                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );

                /* Register the Application HID Event Handler. */

                USB_DEVICE_HID_EventHandlerSet(appData.hidInstance,
                        APP_USBDeviceHIDEventHandler, (uintptr_t)&appData);
            }
            break;

        case USB_DEVICE_EVENT_SUSPENDED:
            BSP_SwitchOFFLED ( LED_1 );
            BSP_SwitchONLED ( LED_2 );
            BSP_SwitchONLED ( LED_3 );
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ATTACHED:
        case USB_DEVICE_EVENT_DETACHED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;

    }
}

/*****************************End Of File**************************************/
