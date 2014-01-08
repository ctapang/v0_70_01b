/*******************************************************************************
  Generic USB Device Definitions for the Template Version

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_generic_config_template.h

  Summary:
    Generic USB device configuration definitions template.

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

#ifndef _USB_DEVICE_GENERIC_CONFIG_TEMPLATE_H_
#define _USB_DEVICE_GENERIC_CONFIG_TEMPLATE_H_


#error "This is configuration template file. Do not include it directly."


// *****************************************************************************
// *****************************************************************************
// Section: Generic USB device Configuration
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Generic USB device Maximum Number of instances

  Summary:
    Selects the maximum number of Generic USB device instances.

  Description:
    This definition select the maximum number of Generic USB device instances.

  Remarks:
    None.

*/

#define USB_DEVICE_GEN_DRIVER_MAX_INSTANCES  /*DOM-IGNORE-BEGIN*/ 1 /*DOM-IGNORE-END*/


// *****************************************************************************
/* Maximum no.of endpoints except control endpoint.

  Summary:
    Sets the maximum number of endpoints, with the exception of the control 
    endpoint.

  Description:
    This constant sets the maximum number of endpoints, with the exception of the
    control endpoint.
	
  Remarks:
    This definition is required to inform the maximum number of of endpoints (except 
    for the control endpoints) used in the application to the Generic USB device 
    function driver.
*/

#define USB_DEVICE_GEN_DRIVER_MAX_PIPES /*DOM-IGNORE-BEGIN*/ 2 /*DOM-IGNORE-END*/


#endif // #ifndef _USB_DEVICE_GENERIC_CONFIG_TEMPLATE_H_

/*******************************************************************************
 End of File
*/

