/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    MSD DEvice application definitions (advanced driver-based version)

  Description:
    This file contains the MSD Device demo application definitions for the
    driver-based version that uses some advanced driver features.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "system_config.h"
#include "system/system.h"
#include "bsp_config.h"
#include "system/int/sys_int.h"
#include "mdd_internal_flash.h"
#include "usb/usb_device_msd.h"

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/

typedef struct
{
    /* device layer handle returned by device layer open function */
    USB_DEVICE_HANDLE              usbDevHandle;

} APP_DATA;


// *****************************************************************************
/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

typedef struct
{
    /* device layer object returned by device layer init function */
    SYS_MODULE_OBJ              usbDevObject;
  
} APP_DRV_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/


/*******************************************************************************
  Function:
    void APP_USBDeviceEventHandler(USB_DEVICE_EVENTS events)

  Summary:
    Device layer event notification callback.

  Description:
    This routine defines the device layer event notification callback.

  Precondition:
    The device layer should be opened by the application and the callback should
    be registered with the device layer.

  Parameters:
    events  - specific device event

  Returns:
    None.

  Remarks:
    None.
*/

void APP_USBDeviceEventHandler(USB_DEVICE_EVENT events,
        USB_DEVICE_EVENT_DATA * eventData);


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/**************************************************************
 * Application Intialization routine. This is called from
 * SYS_Initialize() function 
 *************************************************************/
void APP_Initialize ( void );


/**************************************************************
 * Application Tasks routine. This is called from
 * SYS_Tasks() function 
 *************************************************************/

void APP_Tasks ( void );


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************
extern APP_DRV_OBJECTS appDrvObject;

extern APP_DATA appData;

extern const USB_DEVICE_FUNC_REGISTRATION_TABLE funcRegistrationTable[1];

extern const USB_MASTER_DESCRIPTOR usbMasterDescriptor;

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

