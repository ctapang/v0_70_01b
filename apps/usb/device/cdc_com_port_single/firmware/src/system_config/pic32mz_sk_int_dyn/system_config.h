/*******************************************************************************
  CDC Basic Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the CDC Basic demo
    application for the PIC32 USB starter kit.
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
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* Enables Device Support */
#define DRV_USB_DEVICE_SUPPORT      true

/* Disables host support */
#define DRV_USB_HOST_SUPPORT        false

/* Provides 3 endpoints*/
#define DRV_USB_ENDPOINTS_NUMBER    3

/* Only one instance of the USB Peripheral*/
#define DRV_USB_INSTANCES_NUMBER    1

/* Enables Interrupt mode */
#define DRV_USB_INTERRUPT_MODE      true

/* Driver clients number */
#define DRV_USB_CLIENTS_NUMBER      1

// *****************************************************************************
// *****************************************************************************
// Section: USB Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES         1

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS             1

/* Maximum function drivers allowed per instance of the USB device layer */
#define USB_DEVICE_FUNCTION_DRIVERS_NUMBER      1

/* EP0 size in bytes */
#define USB_DEVICE_EP0_BUFFER_SIZE          64


// *****************************************************************************
// *****************************************************************************
// Section: CDC Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_INSTANCES_NUMBER   1

/* CDC Transfer Queue Size for both read and
 * write. Applicable to all instances of the
 * function driver */
#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED      3

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

