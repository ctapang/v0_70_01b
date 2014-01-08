/*******************************************************************************
  USB DEVICE CDC Basic Demo Application
  
  File Name:
    app.c

  Summary:
    USB DEVICE CDC Basic Demo application

  Description:
    This file contains the USB DEVICE CDC Basic Demo application logic.
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
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

APP_DATA appData;

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************

/*************************************************
 * Application Device Layer Event Handler
 *************************************************/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * pData)
{
    switch( event )
    {
        case USB_DEVICE_EVENT_DETACHED:
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:

            // USB bus reset is detected or device is deconfigured.
            // This means that USB device layer is about to deinitialize
            // all function drivers. Application has to close handles to all
            // function drivers.
           
            appData.isConfigured = false;

            /* Switch on red and orange, switch off green
             * just as an indication */

            BSP_SwitchONLED ( LED_1);
            BSP_SwitchONLED ( LED_2);
            BSP_SwitchOFFLED ( LED_3);
            break;


        case USB_DEVICE_EVENT_CONFIGURED:
            
            /* Check the configuration */
            if(pData->eventConfigured.configurationValue == 1)
            {
                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the 
                 * user data */

                USB_DEVICE_CDC_EventHandlerSet(COM1,
                        APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

                USB_DEVICE_CDC_EventHandlerSet(COM2,
                        APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);

                /* Mark that app is configured complete */
                appData.isConfigured = true;
               
                /* Switch on green and switch off red and orange LEDs as
                 * an indication that we are configured*/

                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );
            }
            break;   
            
        case USB_DEVICE_EVENT_SUSPENDED:
            /* Switch on green and orange, switch off red */
            BSP_SwitchOFFLED ( LED_1 );
            BSP_SwitchONLED ( LED_2 );
            BSP_SwitchONLED ( LED_3 );
            break;

        case USB_DEVICE_EVENT_RESUMED:
        case USB_DEVICE_EVENT_ATTACHED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;
    }
	
}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/************************************************
 * Application State Reset Function
 ************************************************/

void APP_StateReset(void)
{
    appData.appCOMPortObjects[COM1].isReadComplete = false;
    appData.appCOMPortObjects[COM1].isWriteComplete = false;
    appData.appCOMPortObjects[COM2].isReadComplete = false;
    appData.appCOMPortObjects[COM2].isWriteComplete = false;
}

/************************************************
 * Application Initialize function
 ************************************************/

void APP_Initialize ( void )
{
    /* Initialize the application object */

    appData.deviceHandle = USB_DEVICE_HANDLE_INVALID;
    appData.isConfigured = false;
    appData.state = APP_STATE_INIT;

    appData.appCOMPortObjects[COM1].getLineCodingData.dwDTERate = 9600;
    appData.appCOMPortObjects[COM1].getLineCodingData.bDataBits = 8;
    appData.appCOMPortObjects[COM1].getLineCodingData.bParityType = 0;
    appData.appCOMPortObjects[COM1].getLineCodingData.bCharFormat = 0;

    appData.appCOMPortObjects[COM2].getLineCodingData.dwDTERate = 9600;
    appData.appCOMPortObjects[COM2].getLineCodingData.bDataBits = 8;
    appData.appCOMPortObjects[COM2].getLineCodingData.bParityType = 0;
    appData.appCOMPortObjects[COM2].getLineCodingData.bCharFormat = 0;

    appData.appCOMPortObjects[COM1].readTransferHandle
                    = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    appData.appCOMPortObjects[COM1].writeTransferHandle
            = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    appData.appCOMPortObjects[COM1].isReadComplete = true;
    appData.appCOMPortObjects[COM1].isWriteComplete = false;

    appData.appCOMPortObjects[COM2].readTransferHandle
            = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    appData.appCOMPortObjects[COM2].writeTransferHandle
            = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
    appData.appCOMPortObjects[COM2].isReadComplete = true;
    appData.appCOMPortObjects[COM2].isWriteComplete = false;
}

/************************************************
 * Application Tasks Routine
 ************************************************/

void APP_Tasks ( void )
{
    /* Update the application state machine based
     * on the current state */

    switch(appData.state)
    {
        case APP_STATE_INIT:

            /* Open the device layer */
            appData.deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData.deviceHandle == USB_DEVICE_HANDLE_INVALID)
            {
                SYS_ASSERT(false, "Could not open device layer");
                appData.state = APP_STATE_ERROR;
                break;
            }

            /* Register a callback with device layer to get event 
             * notification */
            USB_DEVICE_EventCallBackSet(appData.deviceHandle,
                    APP_USBDeviceEventHandler);

            /* Attach the device */
            USB_DEVICE_Attach (appData.deviceHandle);

            appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;

            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device was configured */

            if(appData.isConfigured)
            {
                /* If the device is configured then lets start
                 * the application */

                appData.state = APP_STATE_CHECK_IF_CONFIGURED;

                /* Schedule a read on COM1 and COM2 */

                USB_DEVICE_CDC_Read(COM1,
                        &appData.appCOMPortObjects[COM1].readTransferHandle,
                        &appData.appCOMPortObjects[COM1].readBuffer, 64);

                USB_DEVICE_CDC_Read(COM2,
                        &appData.appCOMPortObjects[COM2].readTransferHandle,
                        appData.appCOMPortObjects[COM2].readBuffer, 64);

                appData.appCOMPortObjects[COM1].isReadComplete = false;
                appData.appCOMPortObjects[COM2].isReadComplete = false;
            }
            break;

        case APP_STATE_CHECK_IF_CONFIGURED:

            if(appData.isConfigured)
            {
                /* This means this device is still configured */

                appData.state = APP_STATE_CHECK_FOR_READ_COMPLETE;
            }
            else
            {
                APP_StateReset();
                appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
            }
            break;

        case APP_STATE_CHECK_FOR_READ_COMPLETE:

            if(appData.appCOMPortObjects[COM1].isReadComplete == true)
            {
                /* This means we got data on COM1. This means we can write the data.*/

                appData.appCOMPortObjects[COM1].isReadComplete = false;
                appData.appCOMPortObjects[COM2].isWriteComplete = false;

                USB_DEVICE_CDC_Write(COM2,
                        &appData.appCOMPortObjects[COM2].writeTransferHandle,
                        appData.appCOMPortObjects[COM1].readBuffer, 1,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
              
            }

            if(appData.appCOMPortObjects[COM2].isReadComplete == true)
            {
                /* This means we got data on COM1. Check if we can write the
                 * data to COM2*/

                appData.appCOMPortObjects[COM2].isReadComplete = false;
                appData.appCOMPortObjects[COM1].isWriteComplete = false;

                USB_DEVICE_CDC_Write(COM1,
                        &appData.appCOMPortObjects[COM1].writeTransferHandle,
                        appData.appCOMPortObjects[COM2].readBuffer, 1,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

            }
            appData.state = APP_STATE_CHECK_FOR_WRITE_COMPLETE;
            break;

        case APP_STATE_CHECK_FOR_WRITE_COMPLETE:

            /* Check if the write is complete */
            
            if(appData.appCOMPortObjects[COM2].isWriteComplete)
            {
                USB_DEVICE_CDC_Read(COM1,
                        &appData.appCOMPortObjects[COM1].readTransferHandle,
                        &appData.appCOMPortObjects[COM1].readBuffer, 64);
                
                appData.appCOMPortObjects[COM1].isReadComplete = false;
                appData.appCOMPortObjects[COM2].isWriteComplete = false;
              
            }
            
            if(appData.appCOMPortObjects[COM1].isWriteComplete)
            {
                USB_DEVICE_CDC_Read(COM2,
                        &appData.appCOMPortObjects[COM2].readTransferHandle,
                        &appData.appCOMPortObjects[COM2].readBuffer, 64);
                
                appData.appCOMPortObjects[COM2].isReadComplete = false;
                appData.appCOMPortObjects[COM1].isWriteComplete = false;
              
            }

            appData.state = APP_STATE_CHECK_IF_CONFIGURED;
            break;

        case APP_STATE_ERROR:
            break;

        default:
            break;
    }
}


/************************************************
 * CDC COM1 Application Event Handler
 ************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler
(
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void* pData,
    uintptr_t userData
)
{

    APP_DATA * appDataObject;
    appDataObject = (APP_DATA *)userData;
    USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE * controlLineStateData;
    USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK * breakData;

    switch ( event )
    {
        case USB_DEVICE_CDC_EVENT_GET_LINE_CODING:

            /* This means the host wants to know the current line
             * coding. This is a control transfer request. Use the
             * USB_DEVICE_ControlSend() function to send the data to
             * host.  */

            USB_DEVICE_ControlSend(appDataObject->deviceHandle,
                    controlTransferHandle, 
                    (uint8_t *)&appDataObject->appCOMPortObjects[index].getLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the
             * data from the host */

            USB_DEVICE_ControlReceive(appDataObject->deviceHandle,
                    controlTransferHandle, 
                    (uint8_t *) &appDataObject->appCOMPortObjects[index].setLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData = (USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE *)pData;
            appDataObject->appCOMPortObjects[index].controlLineStateData.dtr
                    = controlLineStateData->dtr;
            appDataObject->appCOMPortObjects[index].controlLineStateData.carrier
                    = controlLineStateData->carrier;

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent. Read the break duration */

            breakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData;
            appDataObject->appCOMPortObjects[index].breakData.duration
                    = breakData->duration;
            break;

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            /* This means that the host has sent some data*/
            appDataObject->appCOMPortObjects[index].isReadComplete = true;

            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. For now we accept all the data */

            USB_DEVICE_ControlStatus(appDataObject->deviceHandle,
                    controlTransferHandle, USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We dont
             * do much with this data in this demo. */

            break;

        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the data write got completed. We can schedule
             * the next read. */

            appDataObject->appCOMPortObjects[index].isWriteComplete = true;

            break;

        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}




/*******************************************************************************
 End of File
 */

