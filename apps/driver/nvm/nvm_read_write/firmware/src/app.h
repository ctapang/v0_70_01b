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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/attribs.h>
#include "system_config.h"
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"
#include "driver/nvm/drv_nvm.h"
#include "bsp_config.h"

#define     NO_OF_BYTES_TO_WRITE            DRV_NVM_PAGE_SIZE
#define     NO_OF_BYTES_TO_READ             DRV_NVM_PAGE_SIZE

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
    APP_STATE_INIT,

    APP_STATE_WAIT_FOR_READY,

    APP_STATE_WRITE_NVM_DRV,

    APP_STATE_INIT_READ_NVM_DRV,

    APP_STATE_NVM_ERASE,

    APP_STATE_BUFF_STATUS_CHK,

    APP_STATE_READ_NVM_DRV,

    APP_STATE_VERIFY,

    APP_STATE_NVM_WRITE_STATUS,

    APP_STATE_NVM_READ_STATUS,
	
    /* The app closes the file and idles */
    APP_STATE_IDLE,

    /* An app error has occurred */
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
    /* SYS_FS File handle */
    DRV_HANDLE              nvmHandle;

    DRV_NVM_BUFFER_HANDLE nvmbufferHandle;
       
    /* Application's current state */
    APP_STATES              state;

    /* Application data buffer */
    uint8_t                 data[64];

    uint32_t            nBytesWritten;

    uint32_t            nBytesRead;

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
    NVM FAT Single Disk Demo application tasks function

  Description:
    NVM FAT Single Disk Demo application tasks function. This routine implements
    the application in a non blocking manner.

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

/* The demo app writes this string to the file */
extern const uint8_t writeData[];

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

