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

// *****************************************************************************
/* Application Data

  Summary:
    Contains application data

  Description:
    This structure contains application data.
*/

APP_DATA appData =
{
    .usbDevHandle = USB_DEVICE_HANDLE_INVALID,
    .blinkStatusValid = true,
    .deviceConfigured = false,
    .txTransferHandle = ( USB_DEVICE_CONTROL_TRANSFER_HANDLE )NULL,
    .rxTransferHandle = ( USB_DEVICE_CONTROL_TRANSFER_HANDLE )NULL
};

APP_DRV_OBJECTS appDrvObject = 
{
	.usbDevObject = SYS_MODULE_OBJ_INVALID,
};	

/*******************************************************************************
  Function:
    void APP_usbHID_CallBack ( SYS_MODULE_INDEX funcDriverIndex,
                        USB_DEVICE_HID_CALLBACK_TYPE callback,
                         USB_DEVICE_HID_CALLBACK_EVENT event)

  Summary:
    Application Callback.
    

  Description:
    This function gets called by the HID function driver if any event of type
    USB_DEVICE_HID_CALLBACK_EVENT occurs.

  Parameters:
    callback        - Callback type that indicates the why this callback was
                      called.
    event           - Indicates what event triggered this callback.
 
  Returns:
    None.*/

USB_DEVICE_HID_EVENT_RESPONSE APP_USBDeviceHIDEventHandler (  USB_DEVICE_HID_INDEX iHID,
                            USB_DEVICE_HID_EVENT event,
                            USB_DEVICE_HID_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                            void * eventData,
                            uintptr_t userData )
{
    USB_DEVICE_HID_EVENT_DATA_REPORT_SENT * reportSent;
    USB_DEVICE_HID_EVENT_DATA_REPORT_RECEIVED * reportReceived;

    /* Check type of event */
	switch (event)
    {
        case USB_DEVICE_HID_EVENT_REPORT_SENT:

            /* The eventData parameter will be USB_DEVICE_HID_EVENT_REPORT_SENT
             * pointer type containing details about the report that was
             * sent. */
            reportSent = (USB_DEVICE_HID_EVENT_DATA_REPORT_SENT *) eventData;
            if(reportSent->handle == appData.txTransferHandle )
            {
                // Transfer progressed.
                appData.hidDataTransmitted = true;
            }
            else
            {
                // This should never happen
                while(1);
            }
            break;

        case USB_DEVICE_HID_EVENT_REPORT_RECEIVED:

            /* The eventData parameter will be USB_DEVICE_HID_EVENT_REPORT_RECEIVED
             * pointer type containing details about the report that was
             * received. */

            reportReceived = (USB_DEVICE_HID_EVENT_DATA_REPORT_RECEIVED *) eventData;
            if(reportReceived->handle == appData.rxTransferHandle )
            {
                // Transfer progressed.
                appData.hidDataReceived = true;
            }
            else
            {
                // This should never happen
                while(1);
            }
            break;

        case USB_DEVICE_HID_EVENT_SET_IDLE:

            /* For now we just accept this request as is. We acknowledge
             * this request using the USB_DEVICE_HID_ControlStatus()
             * function with a USB_DEVICE_CONTROL_STATUS_OK flag */

            USB_DEVICE_HID_ControlStatus(iHID, controlTransferHandle,
                        USB_DEVICE_CONTROL_STATUS_OK);
                break;

        default:
            // Nothing to do.
            break;
    }
    return USB_DEVICE_HID_EVENT_RESPONSE_NONE;
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

     /* Check if device is configured.
     See if it is configured with correct
     configuration value and correct speed.
     */
   if( (appData.deviceConfigured == true)
           &&(appData.configurationValue == 1))
   {
       if( appData.hidDataReceived )
       {
           /* Look at the data the host sent, to see what
            * kind of application specific command it sent. */

            switch(appData.receiveDataBuffer[0])
            {
                case 0x80:

                    // Toggle on board LED1 to LED2.
                    BSP_ToggleLED( LED_1 );
                    BSP_ToggleLED( LED_2 );

                    appData.hidDataReceived = false;

                    // Place a new read request.
                    USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_FUNC_INDEX,
                            &appData.rxTransferHandle,
                            appData.receiveDataBuffer,
                            sizeof(appData.receiveDataBuffer) );

                    break;

                case 0x81:

                    if(appData.hidDataTransmitted)
                    {
                        /* Echo back to the host PC the command we are fulfilling in
                         * the first byte.  In this case, the Get Pushbutton State
                         * command. */

                        appData.transmitDataBuffer[0] = 0x81;

                        if( BSP_ReadSwitch(SWITCH_1) == BSP_SWITCH_STATE_PRESSED )
                        {
                            appData.transmitDataBuffer[1] = 0x00;
                        }
                        else
                        {
                            appData.transmitDataBuffer[1] = 0x01;
                        }

                        appData.hidDataTransmitted = false;

                        //Prepare the USB module to send the data packet to the host
                        USB_DEVICE_HID_ReportSend (USB_DEVICE_HID_FUNC_INDEX,
                                &appData.txTransferHandle,
                                appData.transmitDataBuffer,
                                sizeof( appData.transmitDataBuffer ) );

                        appData.hidDataReceived = false;

                        // Place a new read request.
                        USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_FUNC_INDEX,
                                &appData.rxTransferHandle,
                                appData.receiveDataBuffer,
                                sizeof(appData.receiveDataBuffer) );
                    }
                    break;

                default:
                    appData.hidDataReceived = false;

                        // Place a new read request.
                    USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_FUNC_INDEX,
                            &appData.rxTransferHandle,
                            appData.receiveDataBuffer,
                            sizeof(appData.receiveDataBuffer) );
                    break;
            }
        }
   }
}

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
    Application sepcific initialization.

  Description:
    Initialize LEDs on starter kit and initialize
    switches.


  Parameters:
    None.

  Returns:
    None.*/

void APP_Initialize ( void )
{

    
}

/*******************************************************************************
  Function:
    void APP_UsbDeviceEventCallBack ( void )

  Summary:
    Event callback generated by USB device layer.

  Description:
   It is very important that when device is configured, application initializes
   handles to correct function driver. If device is deconfigured, application
   has to close peviously opened handles to function drivers.

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
            // Host has deconfigured the device or a bus reset has happened.
            // Device layer is going to de-initialize all function drivers.
            // Hence close handles to all function drivers (Only if they are
            // opened previously.

            BSP_SwitchONLED(LED_1);
            BSP_SwitchONLED(LED_2);
            BSP_SwitchOFFLED(LED_3);
            appData.deviceConfigured = false;
            break;

        case USB_DEVICE_EVENT_CONFIGURED:
            // Set the flag indicating device is configured.
            appData.deviceConfigured = true;

            // Save the other details for later use.
            appData.configurationValue =
                    eventData->eventConfigured.configurationValue;
            appData.usbSpeed = eventData->eventConfigured.speed ;

            appData.hidDataTransmitted = true;
            appData.hidDataReceived = false;

            // Place a new read request.
            USB_DEVICE_HID_ReportReceive (USB_DEVICE_HID_FUNC_INDEX,
                    &appData.rxTransferHandle,
                    appData.receiveDataBuffer,
                    sizeof(appData.receiveDataBuffer) );

            BSP_SwitchOFFLED(LED_1);
            BSP_SwitchOFFLED(LED_2);
            BSP_SwitchONLED(LED_3);

            break;

        case USB_DEVICE_EVENT_SUSPENDED:

            /* Switch on green and orange, switch off red */
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
