/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    ADC data logger demo application definitions (advanced driver-based version)

  Description:
    This file contains the ADC data logger demo application definitions for the 
    driver-based version that uses some advanced driver features.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>
#include "system_config.h"
#include "bsp_config.h"
#include "usb/usb_device_audio.h"
#include "usb/usb_audio.h"
#include "system/int/sys_int.h"


typedef struct
{
    int16_t right;
    int16_t left;
}
AUDIO_PLAY_SAMPLE;

/* shoule be atlease 1 to support master channel */
#define APP_AUDIO_NUM_MAX_CHANNELS  1

typedef struct
{
    uint16_t curVolume;
    uint16_t minVolume;
    uint16_t maxVolume;
    uint16_t resVolume;

}APP_AUDIO_FEATURE_VOLUME_ATTRIBUTE;

typedef struct
{
    uint8_t curBass;
    uint8_t minBass;
    uint8_t maxBass;
    uint8_t resBass;

}APP_AUDIO_FEATURE_BASS_ATTRIBUTE;

typedef struct
{
    uint8_t curMid;
    uint8_t minMid;
    uint8_t maxMid;
    uint8_t resMid;

}APP_AUDIO_FEATURE_MID_ATTRIBUTE;

typedef struct
{
    uint8_t curTreble;
    uint8_t minTreble;
    uint8_t maxTreble;
    uint8_t resTreble;

}APP_AUDIO_FEATURE_TREBLE_ATTRIBUTE;


typedef struct
{
    uint16_t curDelay;
    uint16_t minDelay;
    uint16_t maxDelay;
    uint16_t resDelay;

}APP_AUDIO_FEATURE_DELAY_ATTRIBUTE;

typedef struct
{
    uint8_t curMute[APP_AUDIO_NUM_MAX_CHANNELS];

    APP_AUDIO_FEATURE_VOLUME_ATTRIBUTE volume[APP_AUDIO_NUM_MAX_CHANNELS];

    APP_AUDIO_FEATURE_BASS_ATTRIBUTE bass[APP_AUDIO_NUM_MAX_CHANNELS];

    APP_AUDIO_FEATURE_MID_ATTRIBUTE mid[APP_AUDIO_NUM_MAX_CHANNELS];

    APP_AUDIO_FEATURE_TREBLE_ATTRIBUTE treble[APP_AUDIO_NUM_MAX_CHANNELS];

    uint8_t curAutoGainControl[APP_AUDIO_NUM_MAX_CHANNELS];

    APP_AUDIO_FEATURE_DELAY_ATTRIBUTE delay[APP_AUDIO_NUM_MAX_CHANNELS];

    uint8_t curBassBoost[APP_AUDIO_NUM_MAX_CHANNELS];

    uint8_t curLoudness[APP_AUDIO_NUM_MAX_CHANNELS];

}APP_AUDIO_FEATURE_UNIT_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum
{
    APP_NOT_INITIALIZED  = 0,
            
    APP_INITIALIZED = 1,

    APP_SUBMIT_RX_REQUEST = 2,

    APP_SUBMIT_TX_REQUEST = 3,
            
    APP_PROCESS_DATA = 4,

    APP_IDLE = 5,

    APP_SEND_DATA_TO_CODEC = 6,

    APP_MUTE_AUDIO_PLAYBACK = 7,

    APP_USB_INTERFACE_ALTERNATE_SETTING_RCVD = 8,

    /* Application Error state*/
    APP_STATE_ERROR = -1

} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/

typedef struct
{
    /* device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE              usbDevHandle;

    USB_DEVICE_AUDIO_INDEX audioInstance;

//    DRV_AK4953A_OBJ_HANDLE audioCodecHandle;

    /* Application's current state*/
    APP_STATES              state;

    /* device configured state */
    bool isConfigured;

    USB_DEVICE_AUDIO_TRANSFER_HANDLE readTransferHandle;

    USB_DEVICE_AUDIO_TRANSFER_HANDLE writeTransferHandle;

     /* volume potentiometer */
    uint16_t volumeAnalog;

     /* last saved potentiometer reading */
    int16_t prevVolumeAnalog;

    uint8_t currentInterfaceAlternateSetting;

    bool dacMute;

} APP_DATA;


// *****************************************************************************
/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/


/*******************************************************************************
  Function:
    void APP_UsbDeviceEventCallBack(USB_DEVICE_EVENTS events)

  Summary:
    Device layer event notification callback.

  Description:
    This routine defines the device layer event notification callback.

  Precondition:
    The device layer should be opened by the application and the callback should
    be registered with the device layer.

  Parameters:
    events  - specific device event

  Returns:
    None.

  Remarks:
    None.
*/

void APP_UsbDeviceEventCallBack(USB_DEVICE_EVENT events, USB_DEVICE_EVENT_DATA * eventData);



// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     ADC data logger application initialization routine

  Description:
    This routine initializes ADC data logger application.  This function opens
    the necessary drivers, initializes the timer and registers the application
    callback with the USART driver.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    USB Device Audio application tasks function

  Description:
    This routine is the USB Device Audio Speaker application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
*/

void APP_Tasks ( void );

//void SYS_Initialize ( void* data );

//void SYS_Tasks ( void );

void APP_USBDeviceAudioEventHandler
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    USB_DEVICE_AUDIO_EVENT event ,
    USB_DEVICE_CONTROL_TRANSFER_HANDLE controlTransferHandle,
    void * pData,
    uintptr_t context
);

int APP_AudioEntitySettingsCallback
(
    USB_DEVICE_AUDIO_INDEX iAudio ,
    uintptr_t controlHandle,
    USB_AUDIO_CONTROL_INTERFACE_REQUEST *setupPkt
);

 


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************
//extern APP_DRV_OBJECTS appDrvObject;

extern SYS_MODULE_OBJ usbDevObject;

extern APP_DATA appData;

extern volatile uint8_t pushButton;

extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[USB_DEVICE_AUDIO_MAX_INSTANCES];

extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

USB_DEVICE_FUNCTION_DRIVER audioFuncDriver;


//extern AUDIO_PLAY_SAMPLE *rxBuffer;//[APP_NO_OF_SAMPLES_IN_A_USB_FRAME];// Holds the Even Audio Data received from Host
//extern AUDIO_PLAY_SAMPLE rxBuffer_1[APP_NO_OF_SAMPLES_IN_A_USB_FRAME];
#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

