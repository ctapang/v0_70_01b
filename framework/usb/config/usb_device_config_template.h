/*******************************************************************************
  USB Device Layer Compile Time Options

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_config_template.h

  Summary:
    USB device configuration template header file.

  Description:
    This file contains USB device layer compile time options (macros) that are to
    be configured by the user. This file is a template file and must be used as
    an example only. This file must not be directly included in the project.

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

#ifndef _USB_DEVICE_CONFIG_TEMPLATE_H_
#define _USB_DEVICE_CONFIG_TEMPLATE_H_

#error (" This is a template file and must not be included directly in the project" );

// *****************************************************************************
// *****************************************************************************
// Section: USB Device configuration Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* 
  Summary:
    Sets the maximum possible number of instances of the USB device that
    can be instantiated by using USB_DEVICE_Initialize() routine. 

  Description:
    In case of microcontrollers with more than one USB peripheral, the value
    of this constant can be increased to support more than one instances of USB 
    device layer.
    
  Remarks:
    The static implementation supports only one instance. Setting the value of
    this constant to > 1 has no effect on static implementations. Only in dynamic
    implementations of the USB device layer this value can be set > 1.
    
    The USB device layer has to support at least one instance. Therefore, ensure
    that the value of this constant is set to > 0.
    
    Increasing the instance count consumes RAM and can lead to performance
    degradation.
*/

#define USB_DEVICE_MAX_INSTANCES 1


// *****************************************************************************
/*
  Summary:
    Sets the maximum possible number of  clients an instance of the USB
    device can open using USB_DEVICE_Open.

  Description:
    If multiple clients need USB device layer services, user can set the value
    of this constant to > 1.
    
  Remarks:
    The value of this macro must not be set to zero. Each instance of the USB device
    layer must support at least one client. Therefore, set the value to at least 1.
    
    The static single client implementaion of the USB device layer supports only one
    client. Therefore, increasing the value of this constant > 1 has no effect in
    static single client implementation.
    
    Increase the client count consumes RAM and can lead to performance
    degradation.
*/

#define USB_DEVICE_MAX_CLIENTS 1


// *****************************************************************************
/* 
  Summary:
   Sets the maximum number of function drivers at a time that are supported by 
   an instance of the USB device layer.

  Description:
   This constant sets the maximum number of function drivers that are loaded
   by a USB device instance for a configuration set by the USB host.
    
  Remarks:
   None.
*/
#define USB_DEVICE_MAX_FUNCTION_DRIVER 3


#endif



