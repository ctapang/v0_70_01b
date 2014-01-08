/*******************************************************************************
  Generic USB function driver Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the Generic USB function driver demo
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
// Section: USB controller Driver Configuration
// *****************************************************************************
// *****************************************************************************

/* EP0 buffer size. Used by controller driver */
#define USB_DEVICE_EP0_BUFFER_SIZE 64



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
/* Number of endpoints suppported by the driver.

  Summary:
    

  Description:
   

  Remarks:
    None.
*/

#define DRV_USB_ENDPOINTS_NUMBER 2

// *****************************************************************************
/* Enable USB in device mode operation.

  Summary:
   Enables the USB to operate in device mode.

  Description:


  Remarks:
    None.
*/

#define DRV_USB_DEVICE_SUPPORT true


// *****************************************************************************
/* USB Host mode operation.

  Summary:
    Macro that enables host mode operation.

  Description:
   

  Remarks:
    None.
*/

#define DRV_USB_HOST_SUPPORT false


// *****************************************************************************
// *****************************************************************************
// Section: Device Layer Configuration
// *****************************************************************************
// *****************************************************************************

/* Maximum device layer instances */
#define USB_DEVICE_MAX_INSTANCES            1

/* Maximum clients for Device Layer */
#define USB_DEVICE_MAX_CLIENTS              1




// *****************************************************************************
// *****************************************************************************
// Section: Generic USB Function Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define USB_DEVICE_GENERIC_INDEX_0       0

/* Maximum endpoints used by generic driver.
 The value given here must match the information given in configuration
 descriptor */
#define USB_DEVICE_GENERIC_MAX_ENDPOINTS 1

/* Maximum IRPs reserved per endpoint. Increase this value
  if application encounters queue full for functions
  USB_DEVICE_GENERIC_EndpointRead and USB_DEVICE_GENERIC_EndpointWrite */
#define USB_DEVICE_GENERIC_MAX_QUEUE     1

/* Maximum instances */
#define USB_DEVICE_GENERIC_MAX_INSTANCES 1

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

