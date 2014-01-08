/*******************************************************************************
Generic USB function driver DEMO

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

#define GEN_USB_EP_IN_INDEX 1
#define GEN_USB_EP_OUT_INDEX 1

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
    .configValue = 0,
    .deviceIsConfigured = false
    
};

APP_DRV_OBJECTS appDrvObject =
{
    .usbDevObject = SYS_MODULE_OBJ_INVALID,
    
};


/*******************************************************************************
  Function:
    void APP_GenUSB_CallBack ( SYS_MODULE_INDEX funcDriverIndex,
		USB_DEVICE_GEN_DRIVER_CALLBACK_TYPE callback,
		USB_DEVICE_GEN_DRIVER_CALLBACK_EVENT event)


  Summary:
    Application Callback.


  Description:
    This function gets called by the Generic USB function driver if any event of type
    USB_DEVICE_GEN_DRIVER_CALLBACK_EVENT occurs.

  Parameters:
    callback        - Callback type that indicates the why this callback was
                      called.
    event           - Indicates what event triggered this callback.

  Returns:
    None.
 */

void APP_USBDeviceGenericEventHandler ( USB_DEVICE_GENERIC_INDEX iGEN,
                           USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
                           USB_DEVICE_GENERIC_EVENT event,
                           USB_DEVICE_GENERIC_EVENT_DATA * eventData,
                           uintptr_t userData )
{
    // Check type of callback
    switch (event)
    {
        case USB_DEVICE_GENERIC_EVENT_ENDPOINT_WRITE_COMPLETE:
            appData.epDataWritePending = false;
            break;

        case USB_DEVICE_GENERIC_EVENT_ENDPOINT_READ_COMPLETE:
            appData.epDataReadPending = false;
            break;

        default:
            break;
    }

}


/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
    Application specific initialization.

  Description:
    Initialize's transmit & receive data buffer object.

  Parameters:
    None.

  Returns:
    None.
 */

void APP_Initialize ( void )
{
   
   
    appData.endpointRx = 0x01;
    appData.endpointTx = 0x81;
    appData.epDataReadPending = true ;

    /* Place a new read request. */
    USB_DEVICE_GENERIC_EndpointRead ( USB_DEVICE_GENERIC_INDEX_0,
                                       &appData.readTranferHandle,
                                        appData.endpointRx,
                                        &appData.receivedDataBuffer[0],
                                        sizeof(appData.receivedDataBuffer) );
     appData.epDataWritePending = false;

}


/*******************************************************************************
  Function:
    void APP_Tasks(void)

  Summary:
    Application routines.

  Description:
    This routine reads the USB data from PC and depending on the PC command
    takes action to toggle LED. Reads switch status and reports to PC.


  Parameters:
    None.

  Returns:
    None.
 */

void APP_Tasks (void )
{
    
   if( appData.deviceIsConfigured
           && appData.configValue == 1 )
   {
   
       /* Check if Generic USB function driver has recieved
            data from host */

       if ( appData.epDataReadPending == false )
       {
           /* Look at the data the host sent,
            * to see what kind of application specific
            * command it sent. */

            switch(appData.receivedDataBuffer[0])
            {
                case 0x80:

                    /* This is the toggle LED command */
                    BSP_ToggleLED(LED_1);
                    BSP_ToggleLED(LED_2);
                    break;

                case 0x81:

                    /* This is a switch check command. Check if the TX is free
                     * for us to send a status. */

                    if(appData.epDataWritePending == false)
                    {
                        /* Echo back to the host PC the command we are fulfilling
                         * in the first byte.  In this case, the Get Pushbutton
                         * State command. */

                        appData.transmitDataBuffer[0] = 0x81;

                        if(BSP_ReadSwitch(SWITCH_1) == BSP_SWITCH_STATE_PRESSED)
                        {
                            appData.transmitDataBuffer[1] = 0x00;
                        }
                        else
                        {
                            appData.transmitDataBuffer[1] = 0x01;
                        }

                        /* Send the data to the host */

                        appData.epDataWritePending = true;

                        USB_DEVICE_GENERIC_EndpointWrite
                                ( USB_DEVICE_GENERIC_INDEX_0,
                                ( USB_DEVICE_GENERIC_TRANSFER_HANDLE *)&appData.writeTranferHandle,
                                appData.endpointTx, &appData.transmitDataBuffer[0],
                                sizeof(appData.transmitDataBuffer),
                                USB_DEVICE_GENERIC_TRANSFER_FLAG_NONE );
                    }
                    break;
                default:
                    break;
            }

            appData.epDataReadPending = true ;
            /* Place a new read request. */
            USB_DEVICE_GENERIC_EndpointRead ( USB_DEVICE_GENERIC_INDEX_0,
                &appData.readTranferHandle, appData.endpointRx,
                &appData.receivedDataBuffer[0],
                sizeof(appData.receivedDataBuffer) );
        }
   }
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
    None.
 */

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData)
{
 
   switch( event )
    {
        case USB_DEVICE_EVENT_RESET:
        case USB_DEVICE_EVENT_DECONFIGURED:
           

            // Also turn ON LEDs to indicate reset/deconfigured state.
            /* Switch on red and orange, switch off green */
            BSP_SwitchONLED ( LED_1);
            BSP_SwitchONLED ( LED_2);
            BSP_SwitchOFFLED ( LED_3);
            break;

        case USB_DEVICE_EVENT_CONFIGURED:
            /* check the configuration */
            if( eventData->eventConfigured.configurationValue == 1 )
            {
                /* The device is in configured state */
                /* Switch on green and switch off red and orange */
                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );

                /* Reset endpoint data send & receive flag  */
                appData.deviceIsConfigured = true;
                appData.configValue = 1;

                APP_Initialize();
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

/*****************************End Of File**************************************/
