/*******************************************************************************
  Application Header

  File Name:
    app.h

  Summary:
    NVM FAT Single Disk application definitions (advanced driver-based version)

  Description:
    This file contains the NVM FAT Single Disk demo application definitions.
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
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"
#include "system/fs/sys_fs_media_manager.h"
#include "system/fs/fat_fs/src/hardware_access/diskio.h"
#include "system/fs/fat_fs/src/file_system/ff.h"
#include "system/fs/mpfs/mpfs.h"
#include "system/fs/sys_fs.h"
#include "tcpip/src/system/system_debug.h"
#include "tcpip/src/system/system_random.h"
#include "tcpip/src/system/system_command.h"
#include "tcpip/tcpip.h"

extern const uint8_t MPFS_IMAGE_DATA[];
// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

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
    /* In this state, the application waits for a IP Address */
    APP_TCPIP_WAIT_FOR_IP,

    APP_TCPIP_WAITING_FOR_COMMAND,

    APP_TCPIP_WAIT_ON_DNS,

    APP_TCPIP_WAIT_FOR_CONNECTION,

    APP_TCPIP_WAIT_FOR_RESPONSE,

    APP_TCPIP_CLOSING_CONNECTION,

    APP_TCPIP_ERROR,

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
    /* SYS_FS File handle */
    SYS_FS_HANDLE           fileHandle;

    /* Application's current state */
    APP_STATES              state;

    /* Application data buffer */

    UDP_SOCKET              socket;

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
    /* NVM Driver Object  */
    SYS_MODULE_OBJ              drvNVMObject;

    /* NVM Media Driver Object */
    SYS_MODULE_OBJ              drvNVMMediaObject;

    /* NVM Driver Object  */
    SYS_MODULE_OBJ              drvSPIObject;

    /* NVM Media Driver Object */
    SYS_MODULE_OBJ              drvSDCARDObject;


} APP_DRV_OBJECTS;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     This routine intializes the application object.

  Description:
    This routine initializes the application object. The application state is
    set to wait for media attach.

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

void APP_Initialize ( void );

/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
 UDP Client tasks

  Description:
  

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this function.

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

void APP_Tasks ( void );

/*******************************************************************************
  Function:
    void SYS_Initialize ( void * data )

  Summary:
    System Initialize function.

  Description:
    This is the SYSTEM Initialize function. All modules are initialized in this
    routine.

  Precondition:
    None.

  Parameters:
    data - This parameter is for reserved and should be set to NULL.

  Returns:
    None.

  Example:
    <code>
    SYS_Initialize(NULL);
    </code>

  Remarks:
    This routine must be called before SYS_Tasks() routine.
*/
void SYS_Initialize ( void* data );

/*******************************************************************************
  Function:
    void SYS_Tasks ( void )

  Summary:
    System Tasks function.

  Description:
    This is the SYSTEM Tasks function. The tasks routines of all modules is
    called in this routine. This routine implements the cooperative
    multi-tasking between different modules. The tasks routines of any module
    should not be blocking.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    while(1)
    {
        SYS_Tasks();
    }
    </code>

  Remarks:
    This routine must be called after SYS_Initialize() routine.
*/
void SYS_Tasks ( void );

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************
/* This is a container object for all application
 * related data. */
extern APP_DATA appData;

/* This is a container object for the SYS_MODULE_OBJ
 * returned by the driver initialization routines. */
extern APP_DRV_OBJECTS appDrvObjects;

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/