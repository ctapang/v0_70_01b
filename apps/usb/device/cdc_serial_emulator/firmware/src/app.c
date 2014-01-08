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

};

/****************************************************
 * Application UART2 Write Routine
 ***************************************************/
void APP_UART2Write(void * data, size_t length)
{
    appData.uartTransmitData = data;
    appData.uartTransmitDataLength = length;
    appData.isUARTTransmitBusy = true;
    appData.uartTxCount = 0;
    U2TXREG = *((uint8_t *)(data));
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_TRANSMIT);

}

/*******************************************************
 * UART2 Initialize routine. Baud rate is set 9600
 *******************************************************/
void APP_UART2Initialize(void)
{
    /* Initialize the UART2 on Explorer 16 board */
    U2MODE = 0x8000;
    U2STA = 0x1400;
    U2BRG = 520;
    appData.isUARTTransmitBusy = false;
    SYS_INT_SourceDisable(INT_SOURCE_USART_2_TRANSMIT);
    SYS_INT_SourceEnable(INT_SOURCE_USART_2_RECEIVE);
}


/*******************************************************
 * UART2 Transmit busy routine. Returns true is UART2
 * is busy transmitting data.
 *******************************************************/
bool APP_UART2TransmitIsBusy(void)
{
    return(appData.isUARTTransmitBusy);
}

/*******************************************************
 * UART2 Received Ready routine. Returns true if UART2
 * has received data.
 *******************************************************/
bool APP_UART2ReceiveReady(void)
{
    if(appData.isUARTReceivedData)
    {
        appData.isUARTReceivedData = false;
        return(true);
    }
    else
    {
        return(false);
    }
}

/*******************************************************
 * UART2 Received Data Read routine.  Returns the
 * character that was last received.
 *******************************************************/
uint8_t APP_UART2Read(void)
{
    return(appData.uartReceivedData);
}

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
        APP_UART2Initialize();

        retVal = true;
    }
    else
    {
        retVal = false;
    }
    
    return(retVal);
}

/*******************************************************
 * Application initialize routine. 
 *******************************************************/

void APP_Initialize(APP_DATA * appData)
{
    APP_UART2Initialize();
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
        case USB_DEVICE_EVENT_DECONFIGURED:

            // USB device is reset or device is deconfigured.
            // This means that USB device layer is about to deininitialize
            // all function drivers. 

            // Also turn ON LEDs to indicate reset/deconfigured state.
            /* Switch on red and orange, switch off green */

            BSP_SwitchONLED ( LED_9 );
            BSP_SwitchONLED ( LED_6 );
            BSP_SwitchOFFLED ( LED_5 );

            appData.isConfigured = false;

            
            break;

        case USB_DEVICE_EVENT_CONFIGURED:

            /* check the configuration */
            if ( eventData->eventConfigured.configurationValue == 1)
            {
                /* the device is in configured state */
                /* Switch on green and switch off red and orange */
                BSP_SwitchOFFLED ( LED_9 );
                BSP_SwitchOFFLED ( LED_6 );
                BSP_SwitchONLED ( LED_5 );

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
            BSP_SwitchOFFLED ( LED_9 );
            BSP_SwitchONLED ( LED_6 );
            BSP_SwitchONLED ( LED_5 );
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
            appDataObject->readLength =
                    ((USB_DEVICE_CDC_EVENT_DATA_READ_COMPLETE*)pData)->length;
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

            break;
   
        default:
            break;
    }

    return USB_DEVICE_CDC_EVENT_RESPONSE_NONE;
}


/**********************************************************
 * Application tasks routine. This function implements the
 * application state machine.
 ***********************************************************/
void APP_Tasks ( APP_DATA * appData )
{

    /* Update the application state machine based
     * on the current state */

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
                /* Schedule the first read from CDC function driver */
                
                appData->state = APP_STATE_CHECK_CDC_READ;
                appData->isReadComplete = false;
                USB_DEVICE_CDC_Read (appData->cdcInstance, &appData->readTransferHandle,
                        appData->readBuffer, 64);
            }
            break;
            
        case APP_STATE_CHECK_CDC_READ:

            if(APP_StateReset())
            {
                break;
            }

            /* If a read is complete, then schedule a read
             * else check if UART has received data */
           
            if(appData->isReadComplete == true)
            {
                appData->isReadComplete = false;
                APP_UART2Write(appData->readBuffer, appData->readLength);
                appData->state = APP_STATE_CHECK_UART_TRANSMIT_COMPLETE;
            }
            else
            {
                appData->state = APP_STATE_CHECK_UART_RECEIVE;
            }
           
            break;

        case APP_STATE_CHECK_UART_TRANSMIT_COMPLETE:

            /* Check if the UART transmission is complete */
            if(!APP_UART2TransmitIsBusy())
            {
                /* This means UART transmit is done. Schedule the next
                 * read  and go to the next state */

                appData->isReadComplete = false;
                USB_DEVICE_CDC_Read (appData->cdcInstance, &appData->readTransferHandle,
                        appData->readBuffer, 64);
                appData->state = APP_STATE_CHECK_UART_RECEIVE;
            }
   
        case APP_STATE_CHECK_UART_RECEIVE:
               
            if(APP_StateReset())
            {
                break;
            }

            /* Check if a character was received on the UART */

            if(APP_UART2ReceiveReady())
            {
                /* Send the character to the CDC function driver */

                USB_DEVICE_CDC_Write(0, &appData->writeTransferHandle,
                        &appData->uartReceivedData, 1,
                        USB_DEVICE_CDC_TRANSFER_FLAGS_DATA_COMPLETE);

            }

            appData->state = APP_STATE_CHECK_CDC_READ;
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

