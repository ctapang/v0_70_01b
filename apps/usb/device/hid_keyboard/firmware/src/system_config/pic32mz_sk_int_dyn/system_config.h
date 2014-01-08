/*******************************************************************************
  HID Mouse Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    system_config.h

  Summary:
    Top-level configuration header for the PIC32MX USB Starter kit.

  Description:
    This file is the top-level configuration header for the HID Basic demo
    application for the PIC32MX USB starter kit.
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

#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H


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
// Section: HID Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* MAX HID Instances */
#define USB_DEVICE_HID_INSTANCES_NUMBER   1

/* HID Instance ID */
#define USB_DEVICE_HID_FUNC_INDEX 0

/* Queue size to be used for each endpoint */
#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED 2

// *****************************************************************************
// *****************************************************************************
// Section: Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            1

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              1

/* Defines endpoint 0 size */
#define USB_DEVICE_EP0_BUFFER_SIZE 64

// *****************************************************************************
// *****************************************************************************
// Section: USB driver configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum USB driver instances */
#define DRV_USB_INSTANCES_NUMBER            USB_DEVICE_MAX_INSTANCES

/* Maximum clients per instance of the driver */
#define DRV_USB_CLIENTS_NUMBER              1

/* Interrupt mode enabled */
#define DRV_USB_INTERRUPT_MODE              true

/* Maximum endpoints used */
#define DRV_USB_ENDPOINTS_NUMBER            2

/* Device mode is enabled */
#define DRV_USB_DEVICE_SUPPORT              true

/* Host mode is enabled */
#define DRV_USB_HOST_SUPPORT                false

// *****************************************************************************
// *****************************************************************************
// Section: Configuration specific application definitions
// *****************************************************************************
// *****************************************************************************

/* Application Switch Debounce period */
#define APP_SWITCH_DEBOUNCE_PERIOD 0x989680


#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

