/*******************************************************************************
  USB DEVICE Audio Speaker Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB AUDIO accessory board.

  Description:
    This file is the top-level configuration header for the USB DEVICE Audio Speaker demo
    application for the PIC32 USB AUDIO accessory board.
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

#ifndef __SYS_CONFIG_H
#define __SYS_CONFIG_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************



#define APP_ID_INPUT_TERMINAL  0x01
#define APP_ID_OUTPUT_TERMINAL 0x02
#define APP_ID_MIXER_UNIT      0x03
#define APP_ID_SELECTOR_UNIT   0x04
#define APP_ID_FEATURE_UNIT    0x05
#define APP_ID_PROCESSING_UNIT 0x06
#define APP_ID_EXTENSION_UNIT  0x07

#define APP_AUDIO_SAMPLING_FREQUENCY_48000
#define APP_AUDIO_MAX_FREQ              48000
#define APP_AUDIO_MAX_SAMPLES           ( APP_AUDIO_MAX_FREQ / 1000 )
#define APP_NO_OF_SAMPLES_IN_A_USB_FRAME 48



#define USB_DEVICE_AUDIO_MAX_INTERFACE_COLLECTIONS      1
#define USB_DEVICE_AUDIO_MAX_STREAMING_INTERFACES       1
#define USB_DEVICE_AUDIO_MAX_INTERFACES                 2
#define USB_DEVICE_AUDIO_MAX_ALTERNATE_SETTING          2
#define USB_DEVICE_AUDIO_NUM_FEATURE_UNITS              1
#define USB_DEVICE_AUDIO_FEATURE_UNIT_ID                APP_ID_FEATURE_UNIT
#define USB_DEVICE_AUDIO_CONTROL_INTERFACE_ID           0x00
#define USB_DEVICE_AUDIO_STREAMING_INTERFACE_ID         0x01

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************
#define DRV_USB_DEVICE_SUPPORT true

#define DRV_USB_HOST_SUPPORT false

#define DRV_USB_ENDPOINTS_NUMBER 2
#define DRV_SPI_INTERRUPT_MODE                      false

/* Number of driver instances */
#define DRV_SPI_INSTANCES_NUMBER                    		1

/* Number of client to be supported */
#define DRV_SPI_CLIENTS_NUMBER                      		1

#define DRV_SPI_PORTS_REMAP_USAGE                   false

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

#define DRV_SPI_PERIPHERAL_ID                       SPI_ID_1

// *****************************************************************************
/* USB hardware instance configuration

  Summary:
    Selects the maximum number of hardware instances that can be supported by
    the dynamic driver

  Description:
    This definition selects the maximum number of hardware instances that can be
    supported by the dynamic driver. Comment this line for a static build of the
    driver.

  Remarks:
    None
*/

#define DRV_USB_INSTANCES_NUMBER  /*DOM-IGNORE-BEGIN*/ 1 /*DOM-IGNORE-END*/

// *****************************************************************************
/* USB Maximum Number of Clients

  Summary:
    Selects the maximum number of clients

  Description:
    This definition select the maximum number of clients that the USB driver can
    support at run time. In almost all realistic USB device applications, the driver
    will atleast have 2 or more clients.

  Remarks:
    None.

*/

#define DRV_USB_CLIENTS_NUMBER  /*DOM-IGNORE-BEGIN*/ 1/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Maximum Number of Pipes

  Summary:
    Selects the maximum number of Pipes

  Description:
    Selects the maximum number of Pipes. Endpoint 0 will require one pipe that
    supports both directions. All other endpoints will require one pipe for each
    direction.

  Remarks:
    None.

*/

#define DRV_USB_PIPES_NUMBER   /*DOM-IGNORE-BEGIN*/4 /*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Maximum Number of Transfer Requests

  Summary:
    Selects the maximum number of Transfer Requests

  Description:
    Selects the maximum number of Transfer Requests. These transfers form the 
    transfer queues for each pipe.

  Remarks:
    None.

*/

#define DRV_USB_XFERS_NUMBER  /*DOM-IGNORE-BEGIN*/13/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Static Index Selection

  Summary:
    USB Static Index selection

  Description:
    USB Static Index selection for the driver object reference. This is a static
    override.

  Remarks:
    This index is required to make a reference to the driver object
*/

//#define DRV_USB_INDEX  /*DOM-IGNORE-BEGIN*/DRV_USB_INDEX_0/*DOM-IGNORE-END*/


// *****************************************************************************
/* USB Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is

    - true  - Select if interrupt mode of timer operation is desired

    - false - Select if polling mode of timer operation is desired

    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_USB_INTERRUPT_MODE  /*DOM-IGNORE-BEGIN*/true/*DOM-IGNORE-END*/


// *****************************************************************************
// *****************************************************************************
// Section: USB Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            1

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              2

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE                   64

/* Maximum function drivers allowed per instance of the USB device layer */
#define USB_DEVICE_MAX_FUNCTION_DRIVER      1


// *****************************************************************************
// *****************************************************************************
// Section: AUDIO Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* Audio function driver index */
#define APP_USBAUDIO_FUNC_INDEX                         0

/* Maximum instances of Audio function driver */
#define USB_DEVICE_AUDIO_MAX_INSTANCES			1

/* Max Q size for controller driver */
#define USB_DEVICE_AUDIO_QUEUE_SIZE                     2

// *****************************************************************************
// *****************************************************************************
// Section: AK4953A Audio Codec Driver Configuration
// *****************************************************************************
// *****************************************************************************
#define DRV_AK4953A_INSTANCES_NUMBER 1
#define DRV_AK4953A_CLIENTS_NUMBER 2
#define DRV_AK4953A_INDEX_MAX 1
#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

