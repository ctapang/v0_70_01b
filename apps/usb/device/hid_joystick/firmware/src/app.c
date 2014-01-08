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

void APP_EmulateJoystick(void)
{
    if(BSP_ReadSwitch(SWITCH_1) == BSP_SWITCH_STATE_PRESSED)
    {
        /* Clear the switch pressed flag */
        
        appData.joystickReport.members.buttons.x = 1;
        appData.joystickReport.members.buttons.square = 0;
        appData.joystickReport.members.buttons.o = 0;
        appData.joystickReport.members.buttons.triangle = 0;
        appData.joystickReport.members.buttons.L1 = 0;
        appData.joystickReport.members.buttons.R1 = 0;
        appData.joystickReport.members.buttons.L2 = 0;
        appData.joystickReport.members.buttons.R2 = 0;
        appData.joystickReport.members.buttons.select = 0;
        appData.joystickReport.members.buttons.start = 0;
        appData.joystickReport.members.buttons.left_stick = 0;
        appData.joystickReport.members.buttons.right_stick = 0;
        appData.joystickReport.members.buttons.home = 0;

        /* Move the hat switch to the east position */
        appData.joystickReport.members.hat_switch.hat_switch = HAT_SWITCH_EAST;

        /* Move the X and Y coordinates to their extreme values */
        appData.joystickReport.members.analog_stick.X = 0;
        appData.joystickReport.members.analog_stick.Y = 0;
      
    }
    else
    {
        /* Indicate no event */

        appData.joystickReport.val[0] = 0x00;
        appData.joystickReport.val[1] = 0x00;
        appData.joystickReport.val[2] = 0x08;
        appData.joystickReport.val[3] = 0x80;
        appData.joystickReport.val[4] = 0x80;
        appData.joystickReport.val[5] = 0x80;
        appData.joystickReport.val[6] = 0x80;
    }
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
            appData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

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
                appData.state = APP_STATE_EMULATE_JOYSTICK;
            }
            else
            {
                /* This means the device got de-configured.
                 * We reset the state and the wait for configuration */

                APP_StateReset();
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_EMULATE_JOYSTICK:

            if(appData.isReportSentComplete)
            {
                /* This means report can be sent*/
                
                APP_EmulateJoystick();
                
                appData.isReportSentComplete = false;
                USB_DEVICE_HID_ReportSend(appData.hidInstance,
                    &appData.sendTransferHandle,
                    (uint8_t *)&appData.joystickReport,
                    sizeof(USB_HID_JOYSTICK_REPORT));
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
    appData.isReportSentComplete = true;
    appData.switch1IsPressed = false;
}

/**********************************************
 * This function is called by SYS_Initialize()
 * function and run after power up.
 **********************************************/

void APP_Initialize ( void )
{
    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
    appData.isConfigured = false;

    /* Initialize joysitck Buttons */
    appData.joystickReport.val[0] = 0x00;
    appData.joystickReport.val[1] = 0x00;

    /* Hat switch */
    appData.joystickReport.val[2] = 0x08;

    /* Analog sticks */
    appData.joystickReport.val[3] = 0x80;
    appData.joystickReport.val[4] = 0x80;
    appData.joystickReport.val[5] = 0x80;
    appData.joystickReport.val[6] = 0x80;
 
    /* Intialize the switch state */
    appData.switch1IsPressed = false;

    /* Initialize the HID instance index.  */
    appData.hidInstance = 0;

    /* Initialize tracking variables */
    appData.isReportSentComplete = true;

    /* Initialize the application state*/
    appData.state = APP_STATE_INIT;

}

void APP_USBDeviceHIDEventHandler
(
    USB_DEVICE_HID_INDEX instanceIndex,
    USB_DEVICE_HID_EVENT event,
    USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * pData,
    uintptr_t context
)

{
    APP_DATA * appData = (APP_DATA *)context;

    switch(event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:

            /* This means the mouse report was sent.
             We are free to send another report */

            appData->isReportSentComplete = true;
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:

            /* This event is not used in this demo */
            
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:

            /* For now just accept this as is */
            USB_DEVICE_HID_ControlStatus(instanceIndex, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

//        case USB_DEVICE_HID_EVENT_CONTROL_TRANSFER_DATA_SENT:
//
//             /* For now just accept this as is */
//            USB_DEVICE_HID_ControlStatus(instanceIndex, controlTransferHandle,
//                    USB_DEVICE_CONTROL_STATUS_OK);



        default:
            break;
    }
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
