/*******************************************************************************
  USB DEVICE Audio Speaker Demo Application

  File Name:
    app.c

  Summary:
    USB DEVICE Audio Speaker Demo application

  Description:
    This file contains the USB DEVICE Audio Speaker Demo application logic.
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

#include "app_MEB2.h"
#include "ak4953a.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

/* entity data */
USB_AUDIO_COPY_PROTECT_CONTROL inCopyProtect;
USB_AUDIO_COPY_PROTECT_CONTROL outCopyProtect;

AUDIO_PLAY_SAMPLE rxBuffer[APP_NO_OF_SAMPLES_IN_A_USB_FRAME];
//uint8_t DACMute = 1; // Holds the status of Mute Control
AK4953AState* pCodecHandle=NULL;
uint8_t appMuteControlHandle;

// *****************************************************************************
/* Application Data

  Summary:
    Contains application data

  Description:
    This structure contains application data.
*/

APP_DATA appData =
{
    /* Device Layer Handle  */
    .usbDevHandle = -1,

    /* USB Audio Instance index for this app object00*/
    .audioInstance = 0,

     /* app state */
    .state = APP_NOT_INITIALIZED, //APP_SUBMIT_RX_REQUEST,

    /* device configured status */
    .isConfigured = false,

    .readTransferHandle = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID,

    .writeTransferHandle = USB_DEVICE_AUDIO_TRANSFER_HANDLE_INVALID,

    .currentInterfaceAlternateSetting = 0,

    .dacMute = FALSE

};

void APP_USBDeviceAudioEventHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * pData,
    uintptr_t context
)
{
    USB_DEVICE_AUDIO_INTERFACE_INFO * interfaceInfo;
    
    if ( iAudio == 0 )
    {
        switch (event)
        {
            case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE:
                //We have received an audio frame from the Host.
                //Now send this audio frame to Audio Codec for Playback.
                //In this event handler we are only setting the application state.
                //The App_Tasks() function will take responsibility of
                //sending the data to the audio codec.
                if (appData.state == APP_IDLE)
                appData.state = APP_SEND_DATA_TO_CODEC;
            break;
            
            case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE:
                //Indicates that we have successfully sent an audio frame to the
                //USB Host.
            break;

            case USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING:
                //We have received a request from USB host to change the Interface-
                //Alternate setting.
                interfaceInfo = (USB_DEVICE_AUDIO_INTERFACE_INFO *)pData;
                appData.currentInterfaceAlternateSetting = interfaceInfo->interfaceAlternateSettting;
                appData.state = APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD;
                break;
            
            case USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED:
                //An audio control setup packet arrived from USB Host. 
                APP_AudioEntitySettingsCallback(iAudio, controlTransferHandle, pData );
                break;
                
            case USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVED:
                //This event indicates that a Control transfer data is received from Host.
                // Now send an ACK to let the Host know that the control transfer
                //data is received successfully.
                USB_DEVICE_AUDIO_ControlStatus(iAudio,controlTransferHandle, USB_DEVICE_AUDIO_CONTROL_STATUS_OK );

                //Check if it is a Mute control request. 
                if (appMuteControlHandle == controlTransferHandle)
                {
                    appData.state = APP_MUTE_AUDIO_PLAYBACK;
                }
            break;

            case  USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_SENT:
            break;
            
            default:
                SYS_ASSERT ( false , "Invalid callback" );
            break;
        } //end of switch ( callback )
    }//end of if  if ( iAudio == 0 )
}//end of function APP_AudioEventCallback


int APP_TerminalRequestHandler (USB_AUDIO_CONTROL_INTERFACE_REQUEST* controlRequest )
{
    int8_t err = 0;

    /* check if input or output terminal */
    if(controlRequest->entityID == APP_ID_INPUT_TERMINAL)
    {
        /* we need to support get CUR request */
        //pData[0] = inCopyProtect;
    }
    else if(controlRequest->entityID == APP_ID_OUTPUT_TERMINAL)
    {
        /*we need to support set CUR request */
        //outCopyProtect = pData[0];
    }
    return err;
}


int APP_FeatureUnitRequestHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    uintptr_t controlHandle,
    USB_AUDIO_CONTROL_INTERFACE_REQUEST* controlRequest
)
{
    USB_AUDIO_FEATURE_CONTROL_REQUEST* featureRequest;
    featureRequest = (USB_AUDIO_FEATURE_CONTROL_REQUEST*) controlRequest;

    int8_t err = 0;

    switch(featureRequest->controlSelector)
    {
        case USB_AUDIO_FCS_MUTE_CONTROL:
        {
            if (featureRequest->bRequest == USB_AUDIO_CSRC_SET_CUR )
            {
                //A control write transfer recived from Host. Now recieve data from Host.
                appMuteControlHandle = controlHandle;
                USB_DEVICE_AUDIO_ControlReceive(iAudio, controlHandle,(uint8_t *) &(appData.dacMute), 1 );

            }
            else if(featureRequest->bRequest ==  USB_AUDIO_CSRC_GET_CUR)
            {
                /*Handle Get request*/
                USB_DEVICE_AUDIO_ControlSend(iAudio, controlHandle, (uint8_t *)&(appData.dacMute), 1 );
            }
            else
            {
                 USB_DEVICE_AUDIO_ControlStatus( iAudio, controlHandle, USB_DEVICE_AUDIO_CONTROL_STATUS_ERROR);

            }
        }
        break;

        case USB_AUDIO_FCS_VOLUME_CONTROL:
        case USB_AUDIO_FCS_BASS_CONTROL:
        case USB_AUDIO_FCS_MID_CONTROL:
        case USB_AUDIO_FCS_TREBLE_CONTROL:
        case USB_AUDIO_FCS_GRAPHIC_EQUALIZER_CONTROL:
        case USB_AUDIO_FCS_AUTOMATIC_GAIN_CONTROL:
        case USB_AUDIO_FCS_DELAY_CONTROL:
        case USB_AUDIO_FCS_BASS_BOOST_CONTROL:
        case USB_AUDIO_FCS_LOUDNESS_CONTROL :
        case USB_AUDIO_FCS_FU_CONTROL_UNDEFINED:
        default:
            //This USB Audio Speaker application does not support any other feature unit request
            // from Host. So Stall if any other feature unit request recieved from Host.
            USB_DEVICE_AUDIO_ControlStatus (iAudio,controlHandle, USB_DEVICE_AUDIO_CONTROL_STATUS_ERROR);
        break;

    } // end of switch(featureRequest->controlSelector)
    return err;
} //end of function APP_FeatureUnitRequestHandler

int APP_AudioEntitySettingsCallback
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    uintptr_t controlHandle,
    USB_AUDIO_CONTROL_INTERFACE_REQUEST *setupPkt
)
{
    int8_t err=-1;
    USB_AUDIO_CONTROL_INTERFACE_REQUEST* controlRequest;
    controlRequest = (USB_AUDIO_CONTROL_INTERFACE_REQUEST*) setupPkt;
    switch(controlRequest->entityID)
    {
        case APP_ID_INPUT_TERMINAL:
        case APP_ID_OUTPUT_TERMINAL:
            err = APP_TerminalRequestHandler (controlRequest);
        break;

        case APP_ID_FEATURE_UNIT:
            err = APP_FeatureUnitRequestHandler (iAudio, controlHandle, controlRequest);
        break;
        case APP_ID_MIXER_UNIT:
        case APP_ID_SELECTOR_UNIT:
        case APP_ID_PROCESSING_UNIT:
        case APP_ID_EXTENSION_UNIT:
        default:
            //This USB Audio Speaker application does not support any other control request
            // received for other unit from Host. So Stall if any other request recieved from Host.
            USB_DEVICE_AUDIO_ControlStatus(iAudio, controlHandle, USB_DEVICE_AUDIO_CONTROL_STATUS_ERROR );
        break;
    }//end of switch(controlRequest->entityID)
    return err;
}//end of function APP_AudioEntitySettingsCallback


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
/* These routines are called by drivers when certain events occur.
*/

/******************************************************************************
  Function:
    void APP_usbDeviceEventCallBack(USB_DEVICE_EVENTS events)

  Remarks:
    See prototype in app.h.
*/

void APP_UsbDeviceEventCallBack( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * pEventData )
{
    switch( event )
    {
        case USB_DEVICE_EVENT_RESET:
            break;
        case USB_DEVICE_EVENT_DECONFIGURED:
            // USB device is reset or device is deconfigured.
            // This means that USB device layer is about to deininitialize
            // all function drivers. So close handles to previously opened
            // function drivers.


            // Also turn ON LEDs to indicate reset/deconfigured state.
            /* Switch on red and orange, switch off green */
            BSP_SwitchONLED ( LED_1);
            BSP_SwitchONLED ( LED_2);
            BSP_SwitchOFFLED ( LED_3);
            break;

        case USB_DEVICE_EVENT_CONFIGURED:
            /* check the configuration */
             /* Initialize the Application */

            if(pEventData->eventConfigured.configurationValue == 1)
            {
                /* the device is in configured state */
                /* Switch on green and switch off red and orange */
                BSP_SwitchOFFLED ( LED_1 );
                BSP_SwitchOFFLED ( LED_2 );
                BSP_SwitchONLED ( LED_3 );

                /* mark that set configuration is complete */
                appData.isConfigured = true;

                /* as the device is configured we can open handles to
                 function drivers appropriate to this configuration value */
                USB_DEVICE_AUDIO_EventHandlerSet
                (
                    0,
                    APP_USBDeviceAudioEventHandler ,
                    (uintptr_t)NULL
                );
                APP_Initialize ();
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


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************
/******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize ( void )
{
    AK4953AInit();
    pCodecHandle=AK4953AOpen(O_WR);
    if(pCodecHandle==NULL)
    {
        SYS_ASSERT ( false , "Unable to open the codec" );
    }

    if(AK4953ASetSampleRate(pCodecHandle, SAMPLERATE_48000HZ)!=1)
    {
        SYS_ASSERT ( false , "Unable to set sampling rate to 48kHz" );
    }

    if(AK4953ASetADCDACOptions(pCodecHandle, TRUE)!=1)
    {
       SYS_ASSERT ( false , "Unable to setup ADC and DAC" );
    }

    AK4953AStartAudio(pCodecHandle, TRUE);
    if(AK4953ASetDACVolume(pCodecHandle, 90)!=1)
    {
        SYS_ASSERT ( false , "Unable to set DAC volume" );
    }
    appData.state = APP_INITIALIZED;
}

/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 */

USB_DEVICE_AUDIO_RESULT audioErr =0;

void APP_Tasks ( void )
{
    switch(appData.state)
    {
        case APP_NOT_INITIALIZED:
            break;

        case APP_INITIALIZED:
            appData.state = APP_SUBMIT_RX_REQUEST;
            break;

        case APP_SUBMIT_RX_REQUEST:
            audioErr = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle, 1 , (void*)rxBuffer, 192);
            appData.state = APP_IDLE;
            break;

        case APP_PROCESS_DATA:
            appData.state = APP_IDLE;
            break;

        case APP_SEND_DATA_TO_CODEC:
            AK4953AWrite ( pCodecHandle ,( AudioStereo* ) rxBuffer , pCodecHandle->frameSize );
            AK4953AAdjustSampleRateTx ( pCodecHandle );
            appData.state = APP_SUBMIT_RX_REQUEST;
            break;

        case APP_MUTE_AUDIO_PLAYBACK:
            
            if (appData.currentInterfaceAlternateSetting == 0)
            {
               AK4953ADACMute(pCodecHandle, TRUE);
               appData.state = APP_IDLE;
            }
            else if (appData.currentInterfaceAlternateSetting == 1)
            {
                AK4953ADACMute(pCodecHandle, appData.dacMute);
                appData.state = APP_SUBMIT_RX_REQUEST;
            }
            break;
        case APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD:
            if (appData.currentInterfaceAlternateSetting == 0)
                {
                    AK4953ADACMute(pCodecHandle, TRUE);
                    AK4953ABufferClear(pCodecHandle);
                    appData.state = APP_IDLE;
                }
                else if(appData.currentInterfaceAlternateSetting == 1)
                {
                    AK4953ADACMute(pCodecHandle, appData.dacMute );
                    appData.state =  APP_SUBMIT_RX_REQUEST;
                }
            break; 
        case APP_IDLE:
            if (appData.currentInterfaceAlternateSetting == 0)
                {
                    AK4953ADACMute(pCodecHandle, TRUE);
                    AK4953ABufferClear(pCodecHandle);
                }
            break;
            
        default:
            break;
        }// end of switch(appData.state)
} //End of APP_Tasks

/*******************************************************************************
 End of File
 */


