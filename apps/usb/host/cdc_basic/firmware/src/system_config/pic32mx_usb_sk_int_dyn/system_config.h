/*******************************************************************************
  CDC Basic Demo Configuration Header

  Company:
    Microchip Technology Inc.

  File Name:
    sys_config.h

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
// Section: USB Host Layer Configuration
// *****************************************************************************
// *****************************************************************************

#define USB_HOST_INDEX_0                0
#define USB_HOST_CLIENTS_NUMBER         1
#define USB_HOST_MAX_INTERFACES         2   /* Max interfaces per device */
#define USB_HOST_INSTANCES_NUMBER       1   /* Maximum Host layer instances */
#define USB_HOST_MAX_CONFIGURATION      1   /* Host support configurations per device */
#define USB_HOST_MAX_DRIVER_SUPPORTED   1   /* Based on TPL list.  */
#define USB_HOST_MAX_DEVICE_SUPPORTED   1   /* This is max per bus including root hub */
#define USB_HOST_MAX_ALTERNATE_SETTINGS 1   /* Max alternate setting per device */

#define USB_HOST_DEVICE_INFORMATION_STRING_LENGTH 31

// *****************************************************************************
// *****************************************************************************
// Section: USB Host Contoller Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_INSTANCES_NUMBER            1
#define DRV_USB_CLIENTS_NUMBER              1
#define DRV_USB_INTERRUPT_MODE              true
#define DRV_USB_HOST_SUPPORT                true
#define DRV_USB_DEVICE_SUPPORT              false
#define DRV_USB_HOST_PIPES_NUMBER           5
#define DRV_USB_HOST_IRP_PER_FRAME_NUMBER   5
#define DRV_USB_HOST_IRP_NUMBER             5
#define DRV_USB_ENDPOINTS_NUMBER            5
#define DRV_USB_HOST_NAK_LIMIT              200


// *****************************************************************************
// *****************************************************************************
// Section: CDC Class Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define  USB_HOST_CDC_INSTANCES_NUMBER   1

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/



#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

