/*******************************************************************************
  USB Device HID Mouse Configuration Options

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_hid_mouse_config_template.h

  Summary:
    USB device HID mouse configuration template header file.

  Description:
    This file contains macros that should be configured by the user
    while using the USB Device HID Mouse Library. These macros should
    be defined in system_config.h

*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _USB_DEVICE_HID_MOUSE_CONFIG_TEMPLATE_H_
#define _USB_DEVICE_HID_MOUSE_CONFIG_TEMPLATE_H_

#error (" This is a template file and must not be included directly in the project" );

// *****************************************************************************
// *****************************************************************************
// Section: USB Device HID Mouse Library Configuration Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* 
  Summary:
    Sets the maximum number of mouse buttons.

  Description:
    This constant sets the maximum number of mouse buttons.
    
  Remarks:
    None.
*/

#define USB_HID_MOUSE_BUTTON_NUMBERS /*DOM-IGNORE-BEGIN*/ 2 /*DOM-IGNORE-END*/

// *****************************************************************************
/* 
  Summary:
    Sets the maximum number of mouse devices to be supported.

  Description:
    This constant sets the maximum number of mouse devices to be supported.
    
  Remarks:
    None.
*/
#define USB_HID_MOUSE_NUMBERS /*DOM-IGNORE-BEGIN*/ 1 /*DOM-IGNORE-END*/
#endif
