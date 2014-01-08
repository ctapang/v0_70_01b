/*******************************************************************************
  USB Device layer interface names mapping

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_mapping.h

  Summary:
    USB Device Layer Interface names mapping

  Description:
    This header file maps the interface prototypes in "usb_device.h" to
    static variants of these routines appropriate for the selcted configuration.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _USB_DEVICE_MAPPING_H
#define _USB_DEVICE_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  See the bottom of file for implementation header include files.
*/

#include <stdint.h>
#include <stdbool.h>

#include "usb_device_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: USB Driver API Mapping to USB device layer API
// *****************************************************************************
// *****************************************************************************
#define USB_CD_HANDLE_mac (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)

#define USB_DEVICE_EndpointEnable( handle, epAddrs, epType, epSize )   \
        DRV_USB_DEVICE_EndpointEnable( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAddrs, epType, epSize )
#define USB_DEVICE_EndpointDisable( handle, epAdrs )     \
        DRV_USB_DEVICE_EndpointDisable( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointStall( handle, epAdrs )      \
        DRV_USB_DEVICE_EndpointStall((((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointStallClear( handle, epAdrs )  \
        DRV_USB_DEVICE_EndpointStallClear( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointIsEnabled( handle, epAdrs )   \
        DRV_USB_DEVICE_EndpointIsEnabled( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointIsStalled( handle, epAdrs )   \
        DRV_USB_DEVICE_EndpointIsStalled( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_IRPSubmit( handle, epAdrs, irp )       \
        DRV_USB_DEVICE_IRPSubmit( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs, irp )
#define USB_DEVICE_IRPCancelAll( handle, epAdrs )        \
        DRV_USB_DEVICE_IRPCancelAll( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_Attach( handle )     DRV_USB_DEVICE_Attach( ((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)
#define USB_DEVICE_Detach( handle )     DRV_USB_DEVICE_Detach( ((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)




#endif // #ifndef _USB_DEVICE_MAPPING_H

/*******************************************************************************
 End of File
*/

