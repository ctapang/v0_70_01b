/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    ADC data logger demo application definitions (advanced driver-based version)

  Description:
    This file contains the ADC data logger demo application definitions for the 
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
#include "bsp_config.h"
#include "system/common/sys_module.h"
#include "system/int/sys_int.h"



//#include "peripheral/usb/plib_usb.h"

#include "usb/usb_chapter_9.h"

#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"

#include "usb/usb_host_msd.h"
#include "usb/usb_host_scsi.h"


//#include "GenericTypeDefs.h"
#include "system/fs/sys_fs_media_manager.h"
#include "system/fs/fat_fs/src/hardware_access/diskio.h"
#include "system/fs/fat_fs/src/file_system/ff.h"
#include "system/fs/sys_fs.h"

void SYS_Tasks ( void );
void SYS_Initialize ( void* data );

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


// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum {
    APP_STATE_OPEN_HOST_LAYER = 0,
    APP_STATE_WAIT_FOR_HOST_ENABLE,
    APP_STATE_WAIT_FOR_DEVICE_ATTACH,
    APP_STATE_DEVICE_CONNECTED,
    APP_STATE_MOUNT_DISK,
    APP_STATE_UNMOUNT_DISK,
    APP_STATE_OPEN_FILE,
    APP_STATE_WRITE_TO_FILE,
    APP_STATE_CLOSE_FILE,
    APP_STATE_IDLE,


    APP_STATE_ERROR

} APP_STATES;
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
    USB_HOST_HANDLE   hostHandle;
    /* SYS_FS File handle for 1st file */
    SYS_FS_HANDLE      fileHandle;

    /* SYS_FS File handle for 2nd file */
    SYS_FS_HANDLE      fileHandle1;

    /* Application's current state */
    APP_STATES              state;

    /* Application data buffer */
    uint8_t                 data[1024];

    uint32_t            nBytesWritten;

    uint32_t            nBytesRead;

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     ADC data logger application initialization routine

  Description:
    This routine initializes ADC data logger application.  This function opens
    the necessary drivers, initializes the timer and registers the application
    callback with the USART driver.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize (APP_DATA * appData);


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    ADC Data Logger application tasks function

  Description:
    This routine is the ADC Data Logger application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
*/

void APP_Tasks ( APP_DATA * appData );


bool USB_HOST_MSD_ApplicationEventHandler(USB_HOST_MSD_INDEX index,
        USB_HOST_MSD_EVENT event, void* pData);

extern SYS_MODULE_OBJ usbHostObject;
extern APP_DATA appData;
// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************


#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

