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
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

/****************************************************
 * This is the text that is sent to the host
 * when a switch is pressed
 ****************************************************/

uint8_t switchPrompt[] = "\r\nPUSH BUTTON PRESSED";

/*****************************************************
 * Initialize the application data structure. All
 * application related variables are stored in this
 * data structure.
 *****************************************************/

APP_DATA appData = 
{
    /* Device Layer Handle  */
    .deviceHandle = -1 ,

    /* CDC Instance index for this app object00*/
    .cdcInstance = 0,

    /* app state */
    .state = APP_STATE_INIT ,

    /* device configured status */
    .isConfigured = false,

    /* Initial get line coding state */
    .getLineCodingData = {9600, 0, 0, 8},

    /* Read Transfer Handle */
    .readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID,

    /* Write Transfer Handle */
    .writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID,

    /* Intialize the read complete flag */
    .isReadComplete = true,

    /*Initialize the write complete flag*/
    .isWriteComplete = true,

    /* Initialize Ignore switch flag */
    .ignoreSwitchPress = false

};

/*****************************************************
 * This function is called in every step of the
 * application state machine.
 *****************************************************/

bool APP_StateReset(void)
{
    /* This function returns true if the device
     * was reset  */
    
    bool retVal;
    
    if(appData.isConfigured == false)
    {
        appData.state = APP_STATE_WAIT_FOR_CONFIGURATION;
        appData.readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
        appData.isReadComplete = true;
        appData.isWriteComplete = true;
        retVal = true;
    }
    else
    {
        retVal = false;
    }
    
    return(retVal);
}

/*******************************************************
 * USB Device Layer Events - Application Event Handler
 *******************************************************/

void APP_USBDeviceEventHandler ( USB_DEVICE_EVENT event,
        USB_DEVICE_EVENT_DATA * eventData )
{

    switch ( event )
    {
        case USB_DEVICE_EVENT_RESET:
       
            // USB device is reset or device is deconfigured.
            // This means that USB device layer is about to deininitialize
            // all function drivers. 

            // Also turn ON LEDs to indicate reset/deconfigured state.
            /* Switch on red and orange, switch off green */

            BSP_SwitchONLED ( LED_1 );
            BSP_SwitchONLED ( LED_2 );
            BSP_SwitchOFFLED ( LED_3 );

            appData.isConfigured = false;
            
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* check the configuration */

            if ( eventData->eventConfigured.configurationValue == 1)
            {
                /* the device is in configured state */
                /* Switch on green and switch off red and orange */
                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );

                /* Register the CDC Device application event handler here.
                 * Note how the appData object pointer is passed as the 
                 * user data */

                USB_DEVICE_CDC_EventHandlerSet(USB_DEVICE_CDC_INDEX_0,
                        APP_USBDeviceCDCEventHandler, (uintptr_t)&appData);
                
                /* mark that set configuration is complete */
                appData.isConfigured = true;

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
        case USB_DEVICE_EVENT_DETACHED:
        case USB_DEVICE_EVENT_ERROR:
        default:
            break;

    }

}

/*******************************************************
 * USB CDC Device Events - Application Event Handler
 *******************************************************/

USB_DEVICE_CDC_EVENT_RESPONSE APP_USBDeviceCDCEventHandler
( 
    USB_DEVICE_CDC_INDEX index ,
    USB_DEVICE_CDC_EVENT event ,
    USB_DEVICE_CDC_CONTROL_TRANSFER_HANDLE controlTransferHandle,
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

             USB_DEVICE_CDC_ControlSend(index, controlTransferHandle,
                    &appDataObject->getLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_GET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_LINE_CODING:

            /* This means the host wants to set the line coding.
             * This is a control transfer request. Use the
             * USB_DEVICE_ControlReceive() function to receive the 
             * data from the host */

            USB_DEVICE_CDC_ControlReceive(index, controlTransferHandle,
                    &appDataObject->setLineCodingData,
                    sizeof(USB_DEVICE_CDC_EVENT_DATA_SET_LINE_CODING));

            break;

        case USB_DEVICE_CDC_EVENT_SET_CONTROL_LINE_STATE:

            /* This means the host is setting the control line state.
             * Read the control line state. We will accept this request
             * for now. */

            controlLineStateData =
                    (USB_DEVICE_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE *)pData;
            appDataObject->controlLineStateData.dtr = controlLineStateData->dtr;
            appDataObject->controlLineStateData.carrier =
                    controlLineStateData->carrier;

            USB_DEVICE_CDC_ControlStatus(index, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);

            break;

        case USB_DEVICE_CDC_EVENT_SEND_BREAK:

            /* This means that the host is requesting that a break of the
             * specified duration be sent. Read the break duration */

            breakData = (USB_DEVICE_CDC_EVENT_DATA_SEND_BREAK *)pData;
            appDataObject->breakData.duration = breakData->duration;
            break; 

        case USB_DEVICE_CDC_EVENT_READ_COMPLETE:

            /* This means that the host has sent some data*/
            appDataObject->isReadComplete = true;
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_RECEIVED:

            /* The data stage of the last control transfer is
             * complete. For now we accept all the data */

            USB_DEVICE_CDC_ControlStatus(index, controlTransferHandle,
                    USB_DEVICE_CONTROL_STATUS_OK);
            break;

        case USB_DEVICE_CDC_EVENT_CONTROL_TRANSFER_DATA_SENT:

            /* This means the GET LINE CODING function data is valid. We dont
             * do much with this data in this demo. */
            break;

        case USB_DEVICE_CDC_EVENT_WRITE_COMPLETE:

            /* This means that the data write got completed. We can schedule
             * the next read. */

            appDataObject->isWriteComplete = true;
            break;
   
        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}

/******************************************************
 * Application Initialize is currently not used. It is
 * called from the SYS_Initialized() function.
 ******************************************************/

void APP_Initialize ( APP_DATA * appData )
{
    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);
}

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

/**********************************************************
 * Application tasks routine. This function implements the
 * application state machine.
 ***********************************************************/
void APP_Tasks ( APP_DATA * appData )
{

    /* Update the application state machine based
     * on the current state */

    USB_DEVICE_CDC_RESULT result;

    APP_ProcessSwitchPress(appData);

    switch(appData->state)
    {
        case APP_STATE_INIT:

            /* Open the device layer */
            appData->deviceHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0,
                    DRV_IO_INTENT_READWRITE );

            if(appData->deviceHandle == USB_DEVICE_HANDLE_INVALID)
            {
                SYS_ASSERT(false, "Could not open device layer");
                appData->state = APP_STATE_ERROR;
                break;
            }

            /* Register a callback with device layer to get event notification (for end point 0) */
            USB_DEVICE_EventCallBackSet(appData->deviceHandle, APP_USBDeviceEventHandler);

            /* Attach the device */
            USB_DEVICE_Attach (appData->deviceHandle);

            appData->state = APP_STATE_WAIT_FOR_CONFIGURATION;

            break;

        case APP_STATE_WAIT_FOR_CONFIGURATION:

            /* Check if the device was configured */
            if(appData->isConfigured)
            {
                /* If the device is configured then lets start reading */
                appData->state = APP_STATE_SCHEDULE_READ;
            }
            break;
            
        case APP_STATE_SCHEDULE_READ:

            if(APP_StateReset())
            {
                break;
            }

            /* If a read is complete, then schedule a read
             * else wait for the current read to complete */

            appData->state = APP_STATE_WAIT_FOR_READ_COMPLETE;
            if(appData->isReadComplete == true)
            {
                appData->isReadComplete = false;
                appData->readTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
                USB_DEVICE_CDC_Read (appData->cdcInstance, &appData->readTransferHandle,
                        appData->readBuffer, 64);
                if(appData->readTransferHandle == USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID)
                {
                    appData->state = APP_STATE_ERROR;
                    break;
                }
            }
           
            break;

        case APP_STATE_WAIT_FOR_READ_COMPLETE:
        case APP_STATE_CHECK_SWITCH_PRESSED:
        
            if(APP_StateReset())
            {
                break;
            }

            /* Check if a character was received or a switch was pressed.
             * The isReadComplete flag gets updated in the CDC event handler. */

            if(appData->isReadComplete || appData->isSwitchPressed)
            {
                 appData->state = APP_STATE_SCHEDULE_WRITE;
            }

            break;
          
            
        case APP_STATE_SCHEDULE_WRITE:

            if(APP_StateReset())
            {
                break;
            }

            /* Setup the write */

            appData->writeTransferHandle = USB_DEVICE_CDC_TRANSFER_HANDLE_INVALID;
            appData->isWriteComplete = false;
            appData->state = APP_STATE_WAIT_FOR_WRITE_COMPLETE;

            if(appData->isSwitchPressed)
            {
                /* If the switch was pressed, then send the switch prompt*/
                appData->isSwitchPressed = false;
                result = USB_DEVICE_CDC_Write(appData->cdcInstance, &appData->writeTransferHandle,
                     switchPrompt, 23, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }
            else
            {
                /* Else echo the received character + 1*/
                appData->readBuffer[0] = appData->readBuffer[0] + 1;
                USB_DEVICE_CDC_Write(appData->cdcInstance, &appData->writeTransferHandle,
                    appData->readBuffer, 1, USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);
            }
                   
            break;

        case APP_STATE_WAIT_FOR_WRITE_COMPLETE:

            if(APP_StateReset())
            {
                break;
            }

            /* Check if a character was sent. The isWriteComplete
             * flag gets updated in the CDC event handler */

            if(appData->isWriteComplete == true)
            {
                appData->state = APP_STATE_SCHEDULE_READ;

            }

            break;

        case APP_STATE_ERROR:
            break;
        default:
            break;
    }
} 


/*******************************************************************************
 End of File
 */

