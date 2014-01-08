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
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

#define _DEFAULT    (0x01<<7)       //Default Value (Bit 7 is set)
#define _SELF       (0x01<<6)       //Self-powered (Supports if set)

// *****************************************************************************
// *****************************************************************************
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_DEVICE_MODE_SUPPORT_ENABLE  true

#define DRV_USB_HOST_MODE_SUPPORT_ENABLE    false

#define DRV_USB_ENDPOINTS_NUMBER            3

#define DRV_USB_EP0_MAX_SIZE                64

//#define DRV_USB_INSTANCES_NUMBER            1     

#define DRV_USB_CLIENTS_NUMBER              2

#define DRV_USB_PIPES_NUMBER                4 

#define DRV_USB_XFERS_NUMBER                13

#define DRV_USB_INDEX                       DRV_USB_INDEX_0

#define DRV_USB_INTERRUPT_MODE              true

#define DRV_USB_PERIPHERAL_ID               USB_ID_1

#define DRV_USB_PING_PONG_MODE              0

#define DRV_USB_STOP_IN_IDLE                false

#define DRV_USB_SUSPEND_IN_SLEEP            false

#define DRV_USB_GEN_INT_ENABLES             (USB_INT_ALL & ~USB_INT_SOF)

#define DRV_USB_ERR_INT_ENABLES             USB_ERR_INT_ALL

#define DRV_USB_OTG_INT_ENABLES             ~USB_OTG_INT_ALL

#define DRV_USB_INTERRUPT_SOURCE            INT_SOURCE_USB_1

/* EP0 buffer size. Used by controller driver */
#define USB_EP0_BUFF_SIZE 64

// *****************************************************************************
// *****************************************************************************
// Section: Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            2

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              3

/* EP0 max size (in bytes) */
#define MAX_SIZE_EP0                        8

/* Maximum size of control transfer in bytes. */
#define MAX_SIZE_CONTROL_TX                 (MAX_SIZE_EP0 * 2)

/* Maximum function drivers allowed per instance of the USB device layer */
#define USB_DEVICE_MAX_FUNCTION_DRIVER      1


// *****************************************************************************
// *****************************************************************************
// Section: CDC Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* CDC function driver index */
#define APP_USBCDC_FUNC_INDEX                       0

/* data EP max size */
#define USB_DEVICE_CDC_DATA_EP_MAX_SIZE            		512

/* notiication EP max size **/
#define USB_DEVICE_CDC_NOTIFICATION_EP_MAX_SIZE    		1024

/* Maximum instances of CDC function driver */
#define USB_DEVICE_CDC_MAX_INSTANCES						1


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration options for the application
*/

/* IN buffer max size */
#define IN_BUFFER_MAX_SIZE      29

#define IN_ECHO_BUFFER_MAX_SIZE 27

#define TOTAL_EP                3

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

