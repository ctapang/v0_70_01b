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

// *****************************************************************************

/***************************************************
 * Application Data Initialization
 **************************************************/
APP_DATA appData =
{
    .deviceHandle  = USB_DEVICE_HANDLE_INVALID,
    .isConfigured = false,
    .emulateMouse = true,
    .hidInstance = 0,
    .isMouseReportSendBusy = false,
    .isSwitchPressed = false,
    .ignoreSwitchPress = false

};

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

/******************************************************
 * Application Tasks routine. This function is called
 * from SYS_Tasks() routine.
 ******************************************************/

void APP_Tasks (void )
{
    static int8_t   vector = 0;
    static uint8_t  movement_length = 0;
    static bool     sent_dont_move = false;

    int8_t dir_table[] ={-4,-4,-4, 0, 4, 4, 4, 0};

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
                appData.state = APP_STATE_MOUSE_EMULATE;
            }
            break;

        case APP_STATE_MOUSE_EMULATE:

            APP_ProcessSwitchPress(&appData);

            /* The following logic rotates the mouse icon when
             * a switch is pressed */

            if(appData.isSwitchPressed)
            {
                /* Toggle the mouse emulation with each switch press */
                appData.emulateMouse ^= 1;
                appData.isSwitchPressed = false;
            }

            if(appData.emulateMouse)
            {
                sent_dont_move = false;

                if(movement_length > 14) 
                {
                    appData.mouseButton[0] = MOUSE_BUTTON_STATE_RELEASED;
                    appData.mouseButton[1] = MOUSE_BUTTON_STATE_RELEASED;
                    appData.xCoordinate =(int8_t)dir_table[vector & 0x07] ;
                    appData.yCoordinate =(int8_t)dir_table[(vector+2) & 0x07];
                    vector ++;
                    movement_length = 0;
                }
            }
            else
            { 
                appData.mouseButton[0] = MOUSE_BUTTON_STATE_RELEASED;
                appData.mouseButton[1] = MOUSE_BUTTON_STATE_RELEASED;
                appData.xCoordinate = 0;
                appData.yCoordinate = 0;

            }

            if(!appData.isMouseReportSendBusy)
            {
                if(((sent_dont_move == false) && (!appData.emulateMouse)) || (appData.emulateMouse))
                {
                    /* This means we can send the mouse report. The
                       isMouseReportBusy flag is updated in the HID Event Handler. */

                    appData.isMouseReportSendBusy = true;

                    /* Create the mouse report */

                    MOUSE_ReportCreate(appData.xCoordinate, appData.yCoordinate,
                            appData.mouseButton, &appData.mouseReport);

                    /* Send the mouse report. */
                    USB_DEVICE_HID_ReportSend(appData.hidInstance,
                            &appData.reportTransferHandle, (uint8_t*)&appData.mouseReport,
                            sizeof(MOUSE_REPORT));

                    movement_length ++;		
                    sent_dont_move = true;
                }
            }

            break;

        case APP_STATE_ERROR:

            break;

        default:
            break;
    }
}
/***************************************************
 * Application Initialization Routine. This function
 * is called from the SYS_Initialize() routine
 **************************************************/

void APP_Initialize ( void )
{
    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);
   
}

void APP_USBDeviceHIDEventHandler(USB_DEVICE_HID_INDEX hidInstance,
        USB_DEVICE_HID_EVENT event,
        USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
        void * eventData, uintptr_t userData)

{
    APP_DATA * appData = (APP_DATA *)userData;

    switch(event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:

            /* This means the mouse report was sent.
             We are free to send another report */

            appData->isMouseReportSendBusy = false;
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:

            /* Dont care for other event in this demo */
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:

            /* For now just accept this as is */
            USB_DEVICE_HID_ControlStatus(hidInstance, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

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
            appData.isMouseReportSendBusy = false;
            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            appData.emulateMouse = true;
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
