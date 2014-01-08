/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    USB Host CDC Basic application definitions

  Description:
    This file contains the USB Host CDC Basic application definitions.
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
#include "bsp_config.h"
#include "system/system.h"
#include "system/int/sys_int.h"
#include "usb/usb_chapter_9.h"
#include "usb/usb_host.h"
#include "usb/usb_host_cdc.h"
#include "usb/src/usb_host_cdc_local.h"

extern USB_HOST_DRIVER cdcDriver;

#define USB_HOST_CDC_INDEX_0 0

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

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
   
    /* Controller driver object returned by controller driver init function */
    SYS_MODULE_OBJ              usbHostObject;

    SYS_MODULE_OBJ              usbHostScsiObject;

} APP_DRV_OBJECTS;

/*******************************************************
 * Application definitions.
 *******************************************************/
#define APP_HOST_CDC_BAUDRATE_SUPPORTED 9600UL
#define APP_HOST_CDC_PARITY_TYPE        0
#define APP_HOST_CDC_STOP_BITS          0      
#define APP_HOST_CDC_NO_OF_DATA_BITS    8  

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum 
{
    APP_STATE_OPEN_HOST_LAYER,
    APP_STATE_WAIT_FOR_HOST_ENABLE,
    APP_STATE_WAIT_FOR_DEVICE_ATTACH,
    APP_STATE_DEVICE_CONNECTED,
    APP_STATE_WAIT_FOR_GET_LINE_CODING,
    APP_STATE_SEND_SET_LINE_CODING,
    APP_STATE_WAIT_FOR_SET_LINE_CODING,
    APP_STATE_SEND_SET_CONTROL_LINE_STATE,
    APP_STATE_WAIT_FOR_SET_CONTROL_LINE_STATE,
    APP_STATE_SEND_PROMPT_TO_DEVICE,
    APP_STATE_WAIT_FOR_PROMPT_SEND_COMPLETE,
    APP_STATE_GET_DATA_FROM_DEVICE,
    APP_STATE_WAIT_FOR_DATA_FROM_DEVICE,
    APP_STATE_DATA_RECEIVED_FROM_DEVICE,
    APP_STATE_ERROR

} APP_STATE;

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
   APP_STATE  state;
   USB_HOST_HANDLE hostHandle;

}APP_DATA;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/**********************************************************
 * Application Initialize. This function is called from
 * the SYS_Initialize routine.
 ***********************************************************/

void APP_Initialize (APP_DATA * appData);

/**********************************************************
 * Application Tasks. This function is called from
 * the SYS_Tasks routine.
 ***********************************************************/
void APP_Tasks ( APP_DATA * appData );

/**********************************************************
 * CDC Class Driver Application Event Handler.
 ***********************************************************/

USB_HOST_CDC_EVENT_RESPONSE APP_USBHostCDCEventHandler
(
    USB_HOST_CDC_INDEX index,
    USB_HOST_CDC_EVENT event,
    void * eventData,
    uintptr_t context
);

/**********************************************************
 * USB Host Layer System Module Object.
 ***********************************************************/

extern SYS_MODULE_OBJ usbHostObject;
extern APP_DATA appData;
extern const USB_HOST_TARGET_PERIPHERAL_LIST USBTPList[];
#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

