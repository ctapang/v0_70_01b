/*******************************************************************************
  USB Host CDC Basic Demo
  
  File Name:
    app.c

  Summary:
    This application demonstrate CDC Host Class Driver functionality.

  Description:
    This application demonstrate CDC Host Class Driver functionality.
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

/* Application data object */
APP_DATA appData;

/* This is the string that will written to the file */
uint8_t prompt[8] = "\r\nLED : ";

/* Array to hold read data */
uint8_t inDataArray[64];
uint8_t USB_CDC_OUT_Data_Array[64];

/* Transfer Handles */
USB_HOST_CDC_TRANSFER_HANDLE getLinecodeTransferHandle;
USB_HOST_CDC_TRANSFER_HANDLE setLinecodeTransferHandle;
USB_HOST_CDC_TRANSFER_HANDLE transferHandle;

/* Line coding and other CDC related data */
USB_CDC_LINE_CODING cdcHostLineCoding;
USB_CDC_LINE_CODING cdcDeviceLineCoding;
USB_CDC_CONTROL_LINE_STATE controlLineState;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/**********************************************************
 * Application Initialize. This function is called from
 * the SYS_Initialize routine.
 ***********************************************************/

void APP_Initialize ( APP_DATA *appData )
{
    /* Initialize the application state machine */
    appData->state =  APP_STATE_OPEN_HOST_LAYER;
    cdcHostLineCoding.dwDTERate     = APP_HOST_CDC_BAUDRATE_SUPPORTED;
    cdcHostLineCoding.bDataBits     = (uint8_t)APP_HOST_CDC_NO_OF_DATA_BITS;
    cdcHostLineCoding.bParityType   = (uint8_t)APP_HOST_CDC_PARITY_TYPE;
    cdcHostLineCoding.bCharFormat   = (uint8_t)APP_HOST_CDC_STOP_BITS;
    controlLineState.dtr = 0;
    controlLineState.carrier = 0;

}

/**********************************************************
 * Application Tasks. This function is called from
 * the SYS_Tasks routine.
 ***********************************************************/

void APP_Tasks( APP_DATA * appData)
{
    USB_HOST_CDC_RESULT result;
    uint8_t  temp;

    switch (appData->state)
    {
        case APP_STATE_OPEN_HOST_LAYER:

            /* Open the host layer and then enable Host layer operation */
            appData->hostHandle = USB_HOST_Open(USB_HOST_0, DRV_IO_INTENT_EXCLUSIVE);

            if (appData->hostHandle != USB_HOST_HANDLE_INVALID)
            {
                /* Host layer was opened successfully. Enable operation
                 * and then wait for operation to be enabled  */

                USB_HOST_OperationEnable(appData->hostHandle );
                appData->state = APP_STATE_WAIT_FOR_HOST_ENABLE;

            }
            else
            {
                /* Could not open host. Goto error state */
                appData->state = APP_STATE_ERROR;
            }
            break;

        case APP_STATE_WAIT_FOR_HOST_ENABLE:

            /* Check if the host operation has been enabled */
            if(USB_HOST_OperationIsEnabled(appData->hostHandle))
            {
                /* This means host operation is enabled. We can 
                 * move on to the next state */

                appData->state = APP_STATE_WAIT_FOR_DEVICE_ATTACH;
            }

            break;
            
        case APP_STATE_WAIT_FOR_DEVICE_ATTACH:

            /* Wait for device attach. The state machine will move
             * to the next state when the USB_HOST_CDC_EVENT_ATTACH
             * is received. The application state is update in the 
             * CDC Host event handler */

            break;

        case APP_STATE_DEVICE_CONNECTED:

            /* CDC Device was attached. Send a Get Line Coding 
             * command to the attached device and then wait
             * for the command to complete */

            result = USB_HOST_CDC_LineCodingGet(USB_HOST_CDC_INDEX_0,
                    &getLinecodeTransferHandle, &cdcDeviceLineCoding);

            if(USB_HOST_CDC_RESULT_OK == result)
            {
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_WAIT_FOR_GET_LINE_CODING;
            }
            else
            {
                /* There was an error in the command request.
                 * Goto error state */

                appData->state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_WAIT_FOR_GET_LINE_CODING:

            /* The application waits here for the Get Line
             * coding request to be complete. This state
             * is updated in the 
             * USB_HOST_CDC_EVENT_GET_LINE_CODING_COMPLETE event */

            break;

        case APP_STATE_SEND_SET_LINE_CODING:

            /* In this state, the application sends the 
             * Set Line Coding request to the device. */

            result = USB_HOST_CDC_LineCodingSet(USB_HOST_CDC_INDEX_0,
                    &setLinecodeTransferHandle, &cdcHostLineCoding);

            if(USB_HOST_CDC_RESULT_OK == result)
            {
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_WAIT_FOR_SET_LINE_CODING;
            }
            else
            {
                /* There was an error in the command request.
                 * Goto error state */

                appData->state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_WAIT_FOR_SET_LINE_CODING:
            
            /* The application waits here for the Set Line
             * coding request to be complete. This state
             * is updated in the 
             * USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE event */

            break;

        case APP_STATE_SEND_SET_CONTROL_LINE_STATE :

            result = USB_HOST_CDC_ControlLineStateSet(USB_HOST_CDC_INDEX_0,
                    &transferHandle, &controlLineState);

            if(USB_HOST_CDC_RESULT_OK == result)
            {
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_WAIT_FOR_SET_CONTROL_LINE_STATE;
            }
            else
            {
                /* There was an error in the command request.
                 * Goto error state */

                appData->state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_WAIT_FOR_SET_CONTROL_LINE_STATE:

            /* The application waits here for the Set Control
             * Line State request to be complete. This state
             * is updated in the 
             * USB_HOST_CDC_EVENT_SET_CONTROL_LINE_STATE_COMPLETE
             * event */
            break;
        case APP_STATE_SEND_PROMPT_TO_DEVICE:

            /* In this state, the application sends a prompt
             * message to the attached CDC device. */

            result = USB_HOST_CDC_Write(USB_HOST_CDC_INDEX_0, &transferHandle, prompt, 8);

            if(USB_HOST_CDC_RESULT_OK == result)
            {
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_WAIT_FOR_PROMPT_SEND_COMPLETE;
            }
            else
            {
                /* There was an error in the command request.
                 * Goto error state */

                appData->state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_WAIT_FOR_PROMPT_SEND_COMPLETE:

            /* The application waits here for the prompt
             * to be send to the device. The state gets
             * updated in the 
             * USB_HOST_CDC_EVENT_WRITE_COMPLETE event */

            break;

        case APP_STATE_GET_DATA_FROM_DEVICE:

            /* Now the application waits for some data from
             * the device. This data will indicate which
             * LED on the PIC32 starter kit should be 
             * switched ON */

            result = USB_HOST_CDC_Read(USB_HOST_CDC_INDEX_0, 
                                &transferHandle, inDataArray, 1);

            if(USB_HOST_CDC_RESULT_OK == result)
            {
                /* Command request was successful. Wait for the
                 * command request to complete */

                appData->state = APP_STATE_WAIT_FOR_DATA_FROM_DEVICE;
            }
            else
            {
                /* There was an error in the command request.
                 * Goto error state */

                appData->state = APP_STATE_ERROR;
            }

            break;

        case APP_STATE_WAIT_FOR_DATA_FROM_DEVICE:

            /* Here the application waits for data to 
             * arrive from the attached device. This
             * state get updated in the 
             * USB_HOST_CDC_EVENT_READ_COMPLETE event */

            break;

        case APP_STATE_DATA_RECEIVED_FROM_DEVICE:
            
            /* We got data from the attached device.
             * This should be a number; 1, 2 or 3 which
             * which decides which LED on the PIC32 starter
             * kit should be switched on */

            temp = inDataArray[0];

            if ( temp == '1')
            {
                /* Switch on LED 1 */

                BSP_SwitchONLED(LED_1);
                BSP_SwitchOFFLED(LED_2);
                BSP_SwitchOFFLED(LED_3);
            }
            else if ( temp == '2')
            {
                /* Switch on LED 2 */
                BSP_SwitchONLED(LED_2);
                BSP_SwitchOFFLED(LED_1);
                BSP_SwitchOFFLED(LED_3);
            }
            else if (temp == '3')
            {
                /* Switch on LED 3 */
                BSP_SwitchONLED(LED_3);
                BSP_SwitchOFFLED(LED_1);
                BSP_SwitchOFFLED(LED_2);
            }

            /* Send the prompt to the device and wait
             * for data again */
            appData->state = APP_STATE_SEND_PROMPT_TO_DEVICE;

            break;

        case APP_STATE_ERROR:

            /* Some error has occurred */
            
            break;
        default:
            break;
    }
} 

/*************************************************************
 * CDC Host Application Event Handler function.
 ************************************************************/

USB_HOST_CDC_EVENT_RESPONSE APP_USBHostCDCEventHandler
(
    USB_HOST_CDC_INDEX index,
    USB_HOST_CDC_EVENT event,
    void * eventData,
    uintptr_t context
)
{   
    /* Get the application context */
    APP_DATA * appData = (APP_DATA*)context;
    uint8_t deviceAddress;

    USB_HOST_CDC_EVENT_DATA_SET_LINE_CODING_COMPLETE * setLineCodingEventData;
    USB_HOST_CDC_EVENT_DATA_GET_LINE_CODING_COMPLETE * getLineCodingEventData;
    USB_HOST_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE_COMPLETE * setControlLineStateEventData;
    USB_HOST_CDC_EVENT_DATA_READ_COMPLETE * readCompleteEventData;
    USB_HOST_CDC_EVENT_DATA_WRITE_COMPLETE * writeCompleteEventData;
   

    switch(event)
    {
        case USB_HOST_CDC_EVENT_ATTACH:

            /* The event data in this case is the address of the
             * attached device. */

            appData->state = APP_STATE_DEVICE_CONNECTED;
            deviceAddress = *((uint8_t *)eventData);
            break;

        case USB_HOST_CDC_EVENT_DETACH:

            /* This means the device was detached. There is no event data
             * associated with this event.*/

            appData->state = APP_STATE_WAIT_FOR_DEVICE_ATTACH;
            break;

        case USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE:

            /* This means the Set Line Coding request completed. We can
             * find out if the request was successful. */

            setLineCodingEventData =
                (USB_HOST_CDC_EVENT_DATA_SET_LINE_CODING_COMPLETE *)eventData;

            if(setLineCodingEventData->transferStatus
                    == USB_HOST_CDC_TRANSFER_STATUS_ERROR)
            {
                /* This means the transfer terminated because of an
                 * error. */
                appData->state = APP_STATE_ERROR;
            }
            else
            {

                /* The application should next send the Set Control Line
                 * state request to the attached device */

                appData->state = APP_STATE_SEND_SET_CONTROL_LINE_STATE;
            }
            break;

        case USB_HOST_CDC_EVENT_GET_LINE_CODING_COMPLETE:

            /* This means the Get Line Coding request completed. We can
             * find out if the request was successful. */

            getLineCodingEventData =
                (USB_HOST_CDC_EVENT_DATA_GET_LINE_CODING_COMPLETE *)eventData;

            if(getLineCodingEventData->transferStatus
                    == USB_HOST_CDC_TRANSFER_STATUS_ERROR)
            {
                /* This means the transfer terminated because of an
                 * error. */
                appData->state = APP_STATE_ERROR;
            }
            else
            {
                /* The application should next send the Set Line Coding
                 * request to the device */

                appData->state = APP_STATE_SEND_SET_LINE_CODING;
            }
            break;

        case USB_HOST_CDC_EVENT_SET_CONTROL_LINE_STATE_COMPLETE:

            /* This means the Set Control Line State request completed. We can
             * find out if the request was successful. */

            setControlLineStateEventData =
                (USB_HOST_CDC_EVENT_DATA_SET_CONTROL_LINE_STATE_COMPLETE *)eventData;

            if(setControlLineStateEventData->transferStatus
                    == USB_HOST_CDC_TRANSFER_STATUS_ERROR)
            {
                /* This means the transfer terminated because of an
                 * error. */
                appData->state = APP_STATE_ERROR;
            }
            else
            {
                /* The application must now send the prompt message
                 * to the attached device */

                appData->state =  APP_STATE_SEND_PROMPT_TO_DEVICE;
            }
            break;

        case USB_HOST_CDC_EVENT_SEND_BREAK_COMPLETE:
            
            /* This event is not used in this application */
            
            break;

        case USB_HOST_CDC_EVENT_WRITE_COMPLETE:

            /* This means the Write request completed. We can
             * find out if the request was successful. */

            writeCompleteEventData =
                (USB_HOST_CDC_EVENT_DATA_WRITE_COMPLETE *)eventData;

            if(writeCompleteEventData->transferStatus
                    == USB_HOST_CDC_TRANSFER_STATUS_ERROR)
            {
                /* This means there transfer terminated because of an
                   error.*/

                appData->state = APP_STATE_ERROR;
            }
            else
            {

                /* The application now waits for data from the attache device */

                appData->state = APP_STATE_GET_DATA_FROM_DEVICE;
            }

            break;

        case USB_HOST_CDC_EVENT_READ_COMPLETE:

            /* This means the Read request completed. We can
             * find out if the request was successful. */

            readCompleteEventData =
                (USB_HOST_CDC_EVENT_DATA_READ_COMPLETE *)eventData;

            if(readCompleteEventData->transferStatus
                    == USB_HOST_CDC_TRANSFER_STATUS_ERROR)
            {
                /* This means there transfer terminated because of an
                 * error. */
                appData->state = APP_STATE_ERROR;
               // appData->state = APP_STATE_SEND_PROMPT_TO_DEVICE;
            }
            else
            {
                /* The application can now process the received data */
                appData->state = APP_STATE_DATA_RECEIVED_FROM_DEVICE;
            }
            break;

        case USB_HOST_CDC_EVENT_SERIAL_STATE_NOTIFICATION_RECEIVED:

            /* This event is not used in the application */
           
            break;

         default:
            break;
    }

    return USB_HOST_CDC_EVENT_RESPONSE_NONE;

}

/*************************************************************
 * USB Host Layer Application Event Handler function.
 ************************************************************/

USB_HOST_EVENT_RESPONSE APP_USBHostEventHandler
            (USB_HOST_EVENTS event, void * eventData, uintptr_t context)
{

     switch(event)
    {
        case USB_HOST_EVENT_VBUS_REQUEST_POWER:
            break;
        case USB_HOST_EVENT_UNSUPPORTED_DEVICE:
            break;

        case USB_HOST_EVENT_CANNOT_ENUMERATE:
            break;
    }
        return USB_HOST_EVENT_RESPONSE_NONE;

}

/*****************************  End of File ***********/

