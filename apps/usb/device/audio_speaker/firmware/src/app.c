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

#include "app.h"
#include "pps.h"
#include "ak4645a.h"
// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

/* entity data */
USB_AUDIO_COPY_PROTECT_CONTROL inCopyProtect;
USB_AUDIO_COPY_PROTECT_CONTROL outCopyProtect;

AUDIO_PLAY_SAMPLE rxBuffer[APP_NO_OF_SAMPLES_IN_A_USB_FRAME];
AK4645AState* pCodecHandle=NULL;
uint8_t DACMute = 1; // Holds the status of Mute Control




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
    UINT audioCodecWrite =0;
    if ( iAudio == 0 )
    {
        switch (event)
        {
            case USB_DEVICE_AUDIO_EVENT_READ_COMPLETE:
                audioCodecWrite = AK4645AWrite ( pCodecHandle ,( AudioStereo* ) rxBuffer , pCodecHandle->frameSize );
                AK4645AAdjustSampleRateTx ( pCodecHandle );
                appData.state = APP_SUBMIT_RX_REQUEST;
            break;
            case USB_DEVICE_AUDIO_EVENT_WRITE_COMPLETE:
            break;

            case USB_DEVICE_AUDIO_EVENT_INTERAFCE_ALTERNATE_SETTING:
                interfaceInfo = (USB_DEVICE_AUDIO_INTERFACE_INFO *)pData;
                if (interfaceInfo->interfaceAlternateSettting == 0)
                {
                    AK4645ADACMute(pCodecHandle, TRUE);
                    AK4645ABufferClear(pCodecHandle);
                    appData.state = APP_IDLE;
                    appData.currentInterfaceAlternateSetting = 0;
                }
                else if(interfaceInfo->interfaceAlternateSettting == 1)
                {
                    AK4645ADACMute(pCodecHandle, FALSE);
                    appData.state =  APP_SUBMIT_RX_REQUEST;
                    appData.currentInterfaceAlternateSetting = 1;
                }
            break;
            case USB_DEVICE_AUDIO_EVENT_ENTITY_SETTINGS_RECEIVED:
                APP_AudioEntitySettingsCallback(iAudio, controlTransferHandle, pData );
                break;
            case USB_DEVICE_AUDIO_EVENT_CONTROL_TRANSFER_RECEIVED:
                USB_DEVICE_ControlStatus(appData.usbDevHandle,controlTransferHandle, USB_DEVICE_CONTROL_STATUS_OK );
                if (appData.currentInterfaceAlternateSetting == 1)
                AK4645ADACMute(pCodecHandle, DACMute);
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
                USB_DEVICE_ControlReceive(appData.usbDevHandle, controlHandle,(uint8_t *) &DACMute, 1 );
            }
            else if(featureRequest->bRequest ==  USB_AUDIO_CSRC_GET_CUR)
            {
                /*Handle Get request*/
                USB_DEVICE_ControlSend(appData.usbDevHandle, controlHandle, (uint8_t *)&DACMute, 1 );
            }
            else
            {
                 USB_DEVICE_ControlStatus( appData.usbDevHandle, controlHandle, USB_DEVICE_CONTROL_STATUS_ERROR);

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
            USB_DEVICE_ControlStatus (appData.usbDevHandle,controlHandle, USB_DEVICE_CONTROL_STATUS_ERROR);
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
            USB_DEVICE_ControlStatus(appData.usbDevHandle, controlHandle,USB_DEVICE_CONTROL_STATUS_ERROR);
        break;
    }//end of switch(controlRequest->entityID)
    return err;
}//end of function APP_AudioEntitySettingsCallback


// *****************************************************************************
// *****************************************************************************
// Section: Application Local Routines
// *****************************************************************************
// *****************************************************************************

/*** VOLUME INIT AND CONTROL ***/

void VolumeControlInit()
{
	TRISAbits.TRISA0=1;
	ANSELA = 1;
	AD1CHS = 0;
	AD1CON1 = 0x080E0;
        AD1CON2 = 0;
        AD1CON3 = 0x1FFF;
        AD1CSSL = 0;
}

void VolumeControlTask ( )
{
    AD1CON1bits.SAMP = 1;
    while ( ! AD1CON1bits.DONE );
    appData.volumeAnalog = ADC1BUF0;
    if ( pCodecHandle != NULL )
    {
        if ( ( appData.volumeAnalog > ( appData.prevVolumeAnalog + 15 ) ) ||
             ( appData.volumeAnalog < ( appData.prevVolumeAnalog - 15 ) ) )
        {
            AK4645ASetDACVolume ( pCodecHandle , ( ( ( UINT32 ) ( appData.volumeAnalog * 100 ) ) >> 10 ) );
        }

        appData.prevVolumeAnalog = appData.volumeAnalog;
    }
}


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


void APP_InitCodec(void)
{
    
    ANSELA = ANSELB = 0;
    TRISAbits.TRISA3 = 0;
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA1 = 1;
    TRISBbits.TRISB5 = 0;
    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    LATAbits.LATA3 = 0;

    PPSOutput(3, RPA4, REFCLKO);	//REFCLK0: RPA4 - Out
    PPSInput(2, SDI1, RPA1);		//SDI: RPA1 - In
    PPSOutput(2, RPB5, SDO1);		//SDO: RPB5 - Out
    PPSInput(1, SS1, RPB4);			//SS: RPB4 - In

    // Initialize reference clock out module
    REFOCONbits.ROSEL = 6;
    REFOCONbits.RODIV = 4;
    REFOCONbits.OE = 1;
    REFOCONbits.ON = 1;

    LATAbits.LATA3 = 1;

    pCodecHandle=AK4645AOpen(O_WR);

    if(pCodecHandle==NULL)
    {
        SYS_ASSERT ( false , "Unable to open the codec" );
    }

    if(AK4645ASetSampleRate(pCodecHandle, SAMPLERATE_48000HZ)!=1)
    {
        SYS_ASSERT ( false , "Unable to set sampling rate to 48kHz" );
    }

    if(AK4645ASetADCDACOptions(pCodecHandle, TRUE)!=1)
    {
       SYS_ASSERT ( false , "Unable to setup ADC and DAC" );
    }

    AK4645AStartAudio(pCodecHandle, TRUE);

    if(AK4645ASetDACVolume(pCodecHandle, 90)!=1)
    {
        SYS_ASSERT ( false , "Unable to set DAC volume" );
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
    APP_InitCodec ( );

    VolumeControlInit ( );

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
        case APP_SUBMIT_RX_REQUEST:
            {
                audioErr = USB_DEVICE_AUDIO_Read ( USB_DEVICE_INDEX_0 , &appData.readTransferHandle, 1 , rxBuffer, 192 );
                appData.state = APP_IDLE;
            }
            break;
            case APP_PROCESS_DATA:
            {
                VolumeControlTask ();
                
                appData.state = APP_IDLE;

                
            }
            break;
            case APP_IDLE:
            break;

            default:
                break;
        }// end of switch(appData.state)
} //End of APP_Tasks

/*******************************************************************************
 End of File
 */

