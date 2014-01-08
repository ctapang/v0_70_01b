/*******************************************************************************
  SD CARD Device Driver Definition

  Company:
    Microchip Technology Inc.

  FileName:
    drv_sdcard.c

  Summary:
    SD CARD Device Driver Implementation

  Description:
    The SD CARD device driver provides a simple interface to manage the SD CARD
    modules on Microchip microcontrollers.  This file Implements the core
    interface routines for the SD CARD driver.

    While building the driver from source, ALWAYS use this file in the build.
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


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "sdcard/src/drv_sdcard_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Driver Hardware instance objects.

  Summary:
    Defines the hardware instances objects that are available on the part

  Description:
    This data type defines the hardware instance objects that are available on
    the part, so as to capture the hardware state of the instance.

  Remarks:
    Not all modes are available on all micro-controllers.
*/

DRV_SDCARD_OBJ              _DRV_SDCARD_OBJ_MAKE_NAME ( gDrvSDCARDObj );


// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the Client instances objects that are available on the part

  Description:
    This data type defines the Client instance objects that are available on
    the part, so as to capture the Client state of the instance.

  Remarks:
    None
*/

DRV_SDCARD_CLIENT_OBJ       gDrvSDCARDClientObj[DRV_SDCARD_CLIENTS_NUMBER];


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

DRV_SDCARD_CLIENT_OBJ _DRV_SDCARD_ClientObjectAllocate( SYS_MODULE_INDEX drvIndex )
{
    /* Local Variables */
    DRV_SDCARD_CLIENT_OBJ_HANDLE hClientObj = ( DRV_SDCARD_CLIENT_OBJ_HANDLE )0;
    uint8_t i = 0;

    for (i = 0; i < DRV_SDCARD_CLIENTS_NUMBER ; i++)
    {
        hClientObj = ( i * drvIndex );
        // Return the matching index associated the hardware instance.
        if ( !( ( _DRV_SDCARD_CLIENT_OBJ( hClientObj, inUse ) == true ) ) )
        {
            _DRV_SDCARD_CLIENT_OBJ( hClientObj, driverObject ) = drvIndex;
            return hClientObj;
        }
    }

    /* Returns the available client object */
    return -1;

} /* _DRV_SDCARD_ClientObjectAllocate */


//******************************************************************************
/* Function:
    static void _DRV_SDCARD_SetupHardware( DRV_SDCARD_INIT  * sdcardInit )

  Summary:
    Sets up the hardware from the initialization structure

  Description:
    This routine sets up the hardware from the initialization structure.

  Remarks:
    Called
*/

static void _DRV_SDCARD_SetupHardware( DRV_SDCARD_INIT * sdcardInit )
{
    /* Initialize the Interrupt Source */
    _DRV_SDCARD_STATIC_INT_SRC( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) = _DRV_SDCARD_INT_SRC_GET( sdcardInit->interruptSource ) );

    /* Power state initialization */
    _DRV_SDCARD_PowerState( _DRV_SDCARD_PERIPHERAL_ID_GET(plibId) , sdcardInit);

    /* TODO: Call to other Module specific Initialization APIs */

} /* _DRV_SDCARD_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_SDCARD_Initialize( const SYS_MODULE_INDEX    index,
                                          const SYS_MODULE_INIT     * const init )

  Summary:
    Initializes hardware and data for the given instance of the SD CARD module

  Description:
    This routine initializes hardware for the instance of the SD CARD module,
    using the hardware initialization given data.  It also initializes all
    necessary internal data.

  Parameters:
    index           - Identifies the driver instance to be initialized
    init            - Pointer to the data structure containing all data
                      necessary to initialize the hardware. This pointer may
                      be null if no data is required and static initialization
                      values are to be used.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.
*/

void _DRV_SDCARD_MAKE_NAME( Initialize )( const SYS_MODULE_INIT * const init )
{
    DRV_SDCARD_INIT * sdcardInit = NULL;

    /* Assign to the local pointer the init data passed */
    sdcardInit = ( DRV_SDCARD_INIT * ) init;

    /* TODO : Initialize any other SD CARD specific members */

    /* Object is valid, set it in use */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, inUse ) = true;

    /* Setup the Hardware */
    _DRV_SDCARD_SetupHardware( sdcardInit );

    /* Reset the number of clients */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, numClients ) = 0;

    /* Interrupt flag cleared on the safer side */
    _DRV_SDCARD_InterruptSourceClear( _DRV_SDCARD_INT_SRC_GET( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) ) );

    /* Enable the interrupt source in case of interrupt mode */
    _DRV_SDCARD_InterruptSourceEnable( _DRV_SDCARD_INT_SRC_GET( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) ) );

    /* Set the current driver state */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, status ) = SYS_STATUS_READY;

} /* DRV_SDCARD_Initialize */


//******************************************************************************
/* Function:
    void DRV_SDCARD_Reinitialize( SYS_MODULE_OBJ        object,
                                  const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes and refreshes the hardware for the instance of the SD CARD
    module

  Description:
    This routine reinitializes and refreshes the hardware for the instance of
    the SD CARD module using the hardware initialization given data. It does not
    clear or reinitialize internal data structures

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware.

  Returns:
    None
*/

void _DRV_SDCARD_MAKE_NAME( Reinitialize )( const SYS_MODULE_INIT * const init )
{
    DRV_SDCARD_INIT * sdcardInit = NULL;

    /* Valid init structure is present */
    sdcardInit = ( DRV_SDCARD_INIT * ) init;

    /* TODO: Stop/Disable the device if needed */

    /* Set the current driver state */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, status ) = SYS_STATUS_UNINITIALIZED ;

    /* Setup the Hardware */
    _DRV_SDCARD_SetupHardware( sdcardInit );

    /* TODO: Start/Enable the device if it was stop/disabled */

    /* Set the curent driver state */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, status ) = SYS_STATUS_READY;

} /* DRV_SDCARD_Reinitialize */


//******************************************************************************
/* Function:
    void DRV_SDCARD_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the SD CARD module

  Description:
    Deinitializes the specific module instancedisabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None
*/

void _DRV_SDCARD_MAKE_NAME( Deinitialize )( void )
{
    /* Interrupt De-Registration */
    _DRV_SDCARD_InterruptSourceDisable( _DRV_SDCARD_INT_SRC_GET( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) ) );

    /* Set the Device Status */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, status ) = SYS_MODULE_DEINITIALIZED;

    /* Remove the driver usage */
    _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, inUse ) = false;

} /* DRV_SDCARD_Deinitialize */


//******************************************************************************
/* Function:
    SYS_STATUS DRV_SDCARD_Status( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the SD CARD module

  Description:
    This routine Provides the current status of the hardware instance of the
    SD CARD module.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    SYS_STATUS_READY    Indicates that any previous module operation for the
                        specified module has completed

    SYS_STATUS_BUSY     Indicates that a previous module operation for the
                        specified module has not yet completed

    SYS_STATUS_ERROR    Indicates that the specified module is in an error state
*/

SYS_STATUS _DRV_SDCARD_MAKE_NAME( Status )( void )
{
    /* Return the status associated with the driver handle */
    return( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, status ) );

} /* DRV_SDCARD_Status */


//******************************************************************************
/* Function:
    void DRV_SDCARD_Tasks( SYS_MODULE_OBJ object)

  Summary:
    Used to maintain the driver's state machine and implement its ISR

  Description:
    This routine is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None
*/

void _DRV_SDCARD_MAKE_NAME( Tasks )( void )
{
    /* Check if the Interrupt/Status is set */
    if (  true == _DRV_SDCARD_InterruptSourceStatusGet( _DRV_SDCARD_INT_SRC_GET( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) ) )  )
    {

        // TODO : Perform driver specific tasks

        /* Clear Interrupt/Status Flag */
        _DRV_SDCARD_InterruptSourceClear( _DRV_SDCARD_INT_SRC_GET( _DRV_SDCARD_OBJ( DRV_SDCARD_INDEX, interruptSource ) ) );
    }

} /* DRV_SDCARD_Tasks */


//******************************************************************************
/* Function:
    DRV_HANDLE DRV_SDCARD_Open( const SYS_MODULE_INDEX  drvIndex,
                                const DRV_IO_INTENT     ioIntent )

  Summary:
    Opens the specific module instance and returns a handle

  Description:
    This routine opens a driver for use by any client module and provides a
    handle that must be provided to any of the other driver operations to
    identify the caller and the instance of the driver/hardware module.

  Parameters:
    drvIndex        - Identifier for the instance to be initialized
    ioIntent        - Possible values from the enumeration DRV_IO_INTENT

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance)
    If an error occurs, the return value is DRV_HANDLE_INVALID
*/

 DRV_HANDLE DRV_SDCARD_Open( const DRV_IO_INTENT ioIntent )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SDCARD_CLIENT_OBJ_HANDLE hClientObj = (DRV_SDCARD_CLIENT_OBJ_HANDLE) 0;
    DRV_SDCARD_OBJ_HANDLE hObj = 0;

    /* Setup client operations */

    /* To Do: OSAL - Lock Mutex */

    /* Allocate the client object and set the flag as in use */
    hClientObj = _DRV_SDCARD_ClientObjectAllocate( _DRV_SDCARD_INDEX_GET( DRV_SDCARD_INDEX ) );
    
    gDrvSDCARDClientObj[hClientObj].inUse = true;
    gDrvSDCARDClientObj[hClientObj].driverObject = _DRV_SDCARD_INDEX_GET( DRV_SDCARD_INDEX );

    /* Increment the client in case of Multi client support, otherwise remove
       the below statement */
    hObj = gDrvSDCARDClientObj[hClientObj].driverObject;

    /* Check for exclusive access */
    if( ( gDrvSDCARDObj[dObj].IsExclusive == true ) ||
        ( gDrvSDCARDObj[dObj].numClients > 0) && DRV_IO_ISEXCLUSIVE( ioIntent ) )
    {
        /* Set that the hardware instance is opened in exclusive mode */
        return DRV_HANDLE_INVALID;
    }

    /* Check if max number of clients open */
    if( gDrvSDCARDObj[dObj].numClients > DRV_SDCARD_CLIENTS_NUMBER )
    {
        /* Set that the hardware instance is opened with max clients */
        return DRV_HANDLE_INVALID;
    }

    gDrvSDCARDObj[hObj].numClients++  ;

    /* Check for the client object */
    SYS_ASSERT( hClientObj < DRV_SDCARD_CLIENTS_NUMBER , "Invalid Client Object" );

    /* To Do: OSAL - Unlock Mutex */

    /* Update the Client Status */
    gDrvSDCARDClientObj[hClientObj].status = DRV_SDCARD_CLIENT_STATUS_READY;

    /* Return the client object */
    return( ( DRV_HANDLE ) hClientObj );

} /* DRV_SDCARD_Open */


//******************************************************************************
/* Function:
    void DRV_SDCARD_Close( DRV_HANDLE handle )

  Summary:
    Closes an opened-instance of a driver

  Description:
    This routine closes an opened-instance of a driver, invalidating the given
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None
*/

void DRV_SDCARD_Close( DRV_HANDLE handle )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SDCARD_CLIENT_OBJ_HANDLE hClientObj = ( DRV_SDCARD_CLIENT_OBJ_HANDLE ) 0;

    /* Get the Client object from the handle passed */
    hClientObj = handle;

    /* Check for the Client validity */
    SYS_ASSERT(  hClientObj < DRV_SDCARD_CLIENTS_NUMBER, "Invalid Client Object" );

    /* To Do: OSAL - lock Mutex */

    /* Free the Client Instance */
    gDrvSDCARDClientObj[hClientObj].inUse = false ;

    /* To Do: OSAL - unlock Mutex */

    /* Update the Client Status */
    gDrvSDCARDClientObj[hClientObj].status = DRV_SDCARD_CLIENT_STATUS_INVALID;

} /* DRV_SDCARD_Close */


//******************************************************************************
/* Function:
    DRV_SDCARD_CLIENT_STATUS DRV_SDCARD_ClientStatus( DRV_HANDLE handle )

  Summary:
    Gets the status of the module instance associated with the handle

  Description:
    This routine gets the status of the module instance associated with the
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    DRV_SDCARD_CLIENT_STATUS value describing the current status of the driver
*/

DRV_SDCARD_CLIENT_STATUS DRV_SDCARD_ClientStatus( DRV_HANDLE handle )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SDCARD_CLIENT_OBJ_HANDLE hClientObj = (DRV_SDCARD_CLIENT_OBJ_HANDLE) 0;

    /* Get the Client object from the handle passed */
    hClientObj = handle;

    /* Check for the Client validity */
    SYS_ASSERT( hClientObj < DRV_SDCARD_CLIENTS_NUMBER, "Invalid Client Object" );

    /* Return the client status associated with the handle passed */
    return( gDrvSDCARDClientObj[hClientObj].status );

} /* DRV_SDCARD_ClientStatus */


//******************************************************************************
/* Function:
    unsigned int DRV_SDCARD_VersionGet( void )

  Summary:
    Gets SD card driver version in numerical format.

  Description:
    This routine gets the SD card driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringized version can be obtained
    using DRV_SDCARD_VersionStrGet()

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/

unsigned int _DRV_SDCARD_MAKE_NAME( VersionGet )( void )
{
    return( ( _DRV_SDCARD_VERSION_MAJOR * 10000 ) +
            ( _DRV_SDCARD_VERSION_MINOR * 100 ) +
            ( _DRV_SDCARD_VERSION_PATCH ) );

} /* DRV_SDCARD_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_SDCARD_VersionStrGet( void )

  Summary:
    Gets SD card driver version in string format.

  Description:
    This routine gets the SD card driver version. The version is returned as
    major.minor.path[type], where type is optional. The numertical version can
    be obtained using DRV_SDCARD_VersionGet()

  Parameters:
    None.

  Returns:
    Current SD card driver version in the string format.

  Remarks:
    None.
*/

char * _DRV_SDCARD_MAKE_NAME( VersionStrGet )( void )
{
    return _DRV_SDCARD_VERSION_STR;

} /* DRV_SDCARD_VersionStrGet */


/*******************************************************************************
End of File
*/



