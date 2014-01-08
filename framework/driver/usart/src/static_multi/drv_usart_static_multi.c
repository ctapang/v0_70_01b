/*******************************************************************************
  USART Driver Feature Variant for dual buffer support

  Summary:
    USART Driver Feature Variant for dual buffer support

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature. The functions are available
    because callback feature of the driver is selected.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
File Name:  drv_usart_static_multi.c
Copyright (c) 2009-2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "driver/usart/src/drv_usart_local.h"

#define driver __attribute__ ((section("DRIVER")))

//OSAL_MUTEX_DECLARE(mutexUSART_clientHandle);
//OSAL_MUTEX_DECLARE(mutexUSART_txBufferTransfer);
//OSAL_MUTEX_DECLARE(mutexUSART_rxBufferTransfer);
//OSAL_MUTEX_DECLARE(mutexUSART_txByteTransfer);
//OSAL_MUTEX_DECLARE(mutexUSART_rxByteTransfer);

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
DRV_USART_OBJECT  _DRV_USART_OBJ_MAKE_NAME ( gDrvUSARTObj ) ;

DRV_USART_OBJECT   *dObj = &(_DRV_USART_OBJ_MAKE_NAME ( gDrvUSARTObj ));

// *****************************************************************************
/* Macro: _DRV_USART_INDEX_GET(drvIndex)

  Summary:
    Returns the appropriate driver id for the configuration

  Description:
    Either return the statically declared driver id or returns the dynamic index
    passed into the macro. This macro has variations for dynamic or static
    driver

*/
#define _DRV_USART_INDEX_GET(drvIndex)  DRV_USART_INDEX


// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects

  Description:
    This data type defines the client instance objects that are available on
    the part, so as to capture the client state of the instance.
    It uses the configuration of maximum number of clients which can get
    registered per hardware instance.

  Remarks:
    Not all modes are available on all micro-controllers.
 */

DRV_USART_CLIENT_OBJECT gDrvUSARTClientObj[DRV_USART_CLIENTS_NUMBER];


// *****************************************************************************
/* Driver transfer instance objects.

  Summary:
    Defines the transfer instances objects

  Description:
    This data type defines the tranfser instance objects that are available on
    the part, so as to capture the client state of the instance.
    It uses the configuration of maximum number of transfer objects which can get
    registered per build.

  Remarks:
    Not all modes are available on all micro-controllers.
 */

DRV_USART_XFER_OBJECT   gDrvUSARTXferQObj[DRV_USART_XFER_BUFFER_NUMBER];


// *****************************************************************************
// *****************************************************************************
// Section: File scope functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void _DRV_USART_LineControlModeSetDyn ( const USART_MODULE_ID plibId,
                                            const DRV_USART_LINE_CONTROL_MODES lineControlMode,
                                            const DRV_USART_HANDSHAKE_MODES flowControl )

  Summary:
    Dynamically ets up the line control mode

  Description:
    This routine dynamically sets up the line control mode, as passed in.

  Remarks:
    This routine is the dynamic implementation of the _DRV_USART_LineControlModeSet
    routine. It may be overridden by the configuration parameter settings.
*/

void driver _DRV_USART_LineControlModeSetDyn
(
    const USART_MODULE_ID plibId,
    const DRV_USART_LINE_CONTROL_MODES lineControlMode,
    const DRV_USART_HANDSHAKE_MODES flowControl
)
{
    if( (lineControlMode & DRV_USART_LINE_CONTROL_MODE_8NONE1) == 0)
    {
        _DRV_USART_LineControlModeSet8N1(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else if ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_9NONE1 )
    {
        _DRV_USART_LineControlModeSet9N1(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else if ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8EVEN1 )
    {
        _DRV_USART_LineControlModeSet8E1(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else if ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8ODD1  )
    {
        _DRV_USART_LineControlModeSet8O1(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else if ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8EVEN2 )
    {
        _DRV_USART_LineControlModeSet8E2(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else if ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8ODD2  )
    {
        _DRV_USART_LineControlModeSet8O2(plibId, _DRV_USART_FLOW_CONTROL(flowControl));
    }
    else
    {
        SYS_ASSERT(false, "Invalid Line Control Mode");
    }

} /* _DRV_USART_LineControlModeSetDyn */


/*******************************************************************************
  Function:
    static void _DRV_USART_SetupHardware (  const USART_MODULE_ID plibId,
                                            DRV_USART_OBJ dObj, DRV_USART_INIT * usartInit )

  Summary:
    Initializes the hardware registers.

  Description:
    Take the initialization data from the application (through DRV_USART_Initialize
    function) and initialize the hardware registers.

  Remarks:
    None
*/
static void driver  _DRV_USART_SetupHardware
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    DRV_USART_INIT          *usartInit
)
{
    /* setup rx and tx polarity */
    _DRV_USART_RXPolarityInverted ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    _DRV_USART_TXPolarityInverted ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;

    /* Setup the stop in idle mode */
    _DRV_USART_PowerState ( _DRV_USART_PERIPHERAL_ID_GET( plibId ) , usartInit ) ;
    /* setup the wake on start mode */
    _DRV_USART_WakeOnStartSetup (_DRV_USART_PERIPHERAL_ID_GET  ( plibId ) , usartInit ) ;
    /* Wake on start disable doesnt exist in PLIBs */
    _DRV_USART_LineControlModeSet(_DRV_USART_PERIPHERAL_ID_GET ( plibId ),
                                     _DRV_USART_LINE_CONTROL_GET(usartInit->lineControlMode),
                                     _DRV_USART_HANDSHAKE_MODE_GET(usartInit->handShakeMode));
    /* setup operation modes */
    _DRV_USART_OperationModeSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                  _DRV_USART_HANDSHAKE_MODE_GET(usartInit->handShakeMode )) ;

    /* setup Auto address detection */
    _DRV_USART_RXAutoAddressEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;

    /* setup IrDA */
    _DRV_USART_IrDAEnable (  _DRV_USART_PERIPHERAL_ID_GET( plibId ) ) ;

    /* setup as sync master or slave */
    _DRV_USART_SyncMasterEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ));
    _DRV_USART_SyncSlaveEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ));

    /* setup Rx FIFO */
    /* setup Rx FIFO */
    if(PLIB_USART_ExistsReceiverInterruptMode( _DRV_USART_PERIPHERAL_ID_GET( plibId )))
    {
        PLIB_USART_ReceiverInterruptModeSelect  ( _DRV_USART_PERIPHERAL_ID_GET ( plibId )  ,
                                       USART_RECEIVE_FIFO_ONE_CHAR ) ;
    }
    /* setup Tx FIFO */
    if(PLIB_USART_ExistsTransmitterInterruptMode(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_TransmitterInterruptModeSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                          USART_TRANSMIT_FIFO_EMPTY ) ;
    }
    /* setup high baud rate */
    if(PLIB_USART_ExistsBaudRateHigh( _DRV_USART_PERIPHERAL_ID_GET( plibId )))
    {
        PLIB_USART_BaudRateHighEnable (  _DRV_USART_PERIPHERAL_ID_GET( plibId ) ) ;
    }

    /* Setup AutoBaud */
    _DRV_USART_AutoBaudSetup (  _DRV_USART_PERIPHERAL_ID_GET( plibId ) , usartInit ) ;

    /* Setup 16 bit mode for BRG */
    _DRV_USART_BaudRate16BitModeSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    /* Set high baud rate*/
    if(PLIB_USART_ExistsBaudRateHigh(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }
    if(PLIB_USART_ExistsBaudRateHigh(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , SYS_CLK_ClockFrequencyGet(CLK_PERIPHERAL),
                                                                  _DRV_USART_BAUD_RATE_GET( usartInit->brgValue ) ) ;
    }
    /* Receiver Enable control */
    if(PLIB_USART_ExistsReceiverEnable(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_ReceiverEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }

} /* _DRV_USART_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Interface Implementations
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    SYS_MODULE_OBJ DRV_USART_Initialize ( const SYS_MODULE_INDEX index,
                                          const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the instance of the USART module

  Description:
    This routine initializes hardware for the instance of the USART module,
    using the hardware initialization given data.  It also initializes any
    internal data structures.

  Parameters:
    drvId           - Identifier for the instance to be initialized
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware. This pointer may
                      be null if no data is required and default
                      initialization is to be used.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.
*/

void driver _DRV_USART_MAKE_NAME(Initialize)
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    const SYS_MODULE_INIT * const init
)
{
    DRV_USART_INIT                  *usartInit     = NULL ;
    bool                            status;
    
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_clientHandle)) == OSAL_RESULT_TRUE),
                 "Unable to create client handle mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_txBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create transmitter buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_rxBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create receiver buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_txByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create transmitter mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_rxByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create receiver mutex" );

    SYS_ASSERT(dObj->inUse == false, "Instance already in use");

    /* Assign to the local pointer the init data passed */
    usartInit = ( DRV_USART_INIT * ) init ;

    /* Disable the USART module */
    PLIB_USART_Disable ( ( usartInit->usartID ) ) ;
    
    dObj->inUse = true;

    /* Update the USART PLIB Id */
    dObj->moduleId      = ( usartInit->usartID );

    /* Setup the Hardware */
    _DRV_USART_SetupHardware(usartInit ) ;

    /* Enable the USART module */
    PLIB_USART_Enable ( ( usartInit->usartID ) ) ;

    dObj->byteTxStatus  =   DRV_USART_BYTE_IS_READY;

    dObj->byteRxStatus  =   DRV_USART_BYTE_IS_READY;
    
    dObj->numClients    = 0;

    if(usartInit->txQueueSize > 0)
    {
        status  =   _DRV_USART_QueueAllocate(&(dObj->writeQ) ,usartInit->txQueueSize);
        SYS_ASSERT(status == true, "Failed to allocate element in Queue");
    }
    else
    {
        dObj->writeQ.queueSize  =   0;
    }

    if(usartInit->rxQueueSize > 0)
    {
        status  =   _DRV_USART_QueueAllocate(&(dObj->readQ) ,usartInit->rxQueueSize);
        SYS_ASSERT(status == true, "Failed to allocate element in Queue");
    }
    else
    {
        dObj->readQ.queueSize  =   0;
    }

    /* Clear the interrupts */
    _DRV_USART_InterruptSourceStatusClear( DRV_USART_INTERRUPT_SOURCE_TX ) ;
    _DRV_USART_InterruptSourceStatusClear( DRV_USART_INTERRUPT_SOURCE_RX ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceStatusClear( DRV_USART_INTERRUPT_SOURCE_ERROR));

    /* Enable the interrupt source in case of interrupt mode */
    //_DRV_USART_InterruptSourceEnable( ((dObj->txInterruptSource)) ) ;
    _DRV_USART_InterruptSourceEnable( DRV_USART_INTERRUPT_SOURCE_RX ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceEnable(DRV_USART_INTERRUPT_SOURCE_ERROR));

    /* Update the status */
    (dObj->status) = SYS_STATUS_READY;
} /* DRV_USART_Initialize */


/*******************************************************************************
  Function:
    void DRV_USART_Reinitialize ( SYS_MODULE_OBJ object,
                                  const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes the hardware for the instance of the USART module.

  Description:
    This routine reinitializes the hardware for the instance of the USART module
    using the hardware initialization given data. It does not clear or re-
    initialize internal data structures. Application should call this function,
    if the module is already initilized and the it wants to change the Initiali-
    zation. An instance of SYS_MODULE_INIT structure should be filled in by the
    application and passed to the this function.


  Parameters:
    object      - Identifier for the instance to be re-initialized. This will
                  be returned by the Initialize function and will be used for
                  all the system level APIs as a module identifier.
    init        - Pointer to the data structure containing any data
                  necessary to initialize the hardware. This pointer may
                  be null if no data is required and default
                  initialization is to be used.

  Returns:
    None
*/

void driver _DRV_USART_MAKE_NAME(Reinitialize)
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    const SYS_MODULE_INIT   *const init
)
{
    DRV_USART_INIT              *usartInit = NULL;
    bool                        status;

    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_clientHandle)) == OSAL_RESULT_TRUE),
                 "Unable to create client handle mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_txBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create transmitter buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_rxBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create receiver buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_txByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create transmitter mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&(dObj->mutexUSART_rxByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to create receiver mutex" );

    /* Assign to the local pointer the init data passed */
    usartInit = ( DRV_USART_INIT * ) init ;

    /* Disable the Usart */
    PLIB_USART_Disable ( ( usartInit->usartID ) ) ;

    //OSAL_MUTEX_Delete(&mutexUSART);
    /* Setup the Hardware */
    _DRV_USART_SetupHardware(usartInit ) ;

    /* Enable the USART module */
    PLIB_USART_Enable ( ( usartInit->usartID ) ) ;
    //OSAL_MUTEX_Create(&mutexUSART);
    /* Initialize buffer indices and the state machine.*/
    _DRV_USART_SetupLoopbackOperation ( usartInit , dObj ) ;

    dObj->byteTxStatus  =   DRV_USART_BYTE_IS_READY;

    dObj->byteRxStatus  =   DRV_USART_BYTE_IS_READY;

    if(usartInit->txQueueSize > 0)
    {
        status  =   _DRV_USART_QueueAllocate(&(dObj->writeQ) ,usartInit->txQueueSize);
        SYS_ASSERT(status == true, "Failed to allocate element in Queue");
    }
    else
    {
        dObj->writeQ.queueSize  =   0;
    }

    if(usartInit->rxQueueSize > 0)
    {
        status  =   _DRV_USART_QueueAllocate(&(dObj->readQ) ,usartInit->rxQueueSize);
        SYS_ASSERT(status == true, "Failed to allocate element in Queue");
    }
    else
    {
        dObj->readQ.queueSize  =   0;
    }

    /* Update the status */
    (dObj->status) = SYS_STATUS_READY;
} /* DRV_USART_Reinitialize */


/*******************************************************************************
  Function:
    void DRV_USART_Deinitialize ( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the USART module

  Description:
    Deinitializes the specific module instance disabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object           - Identifier for the instance to be de-initialized

  Returns:
    None
*/

void driver _DRV_USART_MAKE_NAME(Deinitialize)
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
)
{
    /* Disable the interrupt */
    _DRV_USART_InterruptSourceDisable( DRV_USART_INTERRUPT_SOURCE_TX) ;
    _DRV_USART_InterruptSourceDisable( DRV_USART_INTERRUPT_SOURCE_RX ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceDisable(DRV_USART_INTERRUPT_SOURCE_ERROR));

     /* Disable USART module */
     PLIB_USART_Disable (  ( (dObj->moduleId) ));
     //OSAL_MUTEX_Delete(&mutexUSART);
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&(dObj->mutexUSART_clientHandle)) == OSAL_RESULT_TRUE),
                 "Unable to delete client handle mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&(dObj->mutexUSART_txBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to delete transmitter buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&(dObj->mutexUSART_rxBufferTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to delete receiver buffer mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&(dObj->mutexUSART_txByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to delete transmitter mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&(dObj->mutexUSART_rxByteTransfer)) == OSAL_RESULT_TRUE),
                 "Unable to delete receiver mutex" );

    /* Deinitialize the USART status */
    ( dObj->status) =  SYS_STATUS_UNINITIALIZED ;

} /* DRV_USART_Deinitialize */


/*******************************************************************************
  Function:
    SYS_STATUS DRV_USART_Status ( SYS_MODULE_OBJ object )

  Summary:
    Gets the status of the USART instance

  Description:
    Returns the current status of the USART module.

  Remarks:
    SYS_STATUS_READY    Indicates that any previous module operation for the
                        specified module has completed

    SYS_STATUS_BUSY     Indicates that a previous module operation for the
                        specified module has not yet completed

    SYS_STATUS_ERROR    Indicates that the specified module is in an error state
*/

SYS_STATUS driver _DRV_USART_MAKE_NAME(Status)
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
)
{
    return (  ( dObj->status) );

} /* DRV_USART_Status */


/*******************************************************************************
  Function:
    DRV_HANDLE DRV_USART_Open( const SYS_MODULE_INDEX index,
                               const DRV_IO_INTENT intent )

  Summary:
    Opens a new client for the device instance.

  Description:
    Returns a handle of the opened client instance. All client operation APIs
    will require this handle as an argument.

  Remarks:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance)
    If an error occurs, the return value is DRV_HANDLE_INVALID
*/

  DRV_HANDLE driver _DRV_USART_MAKE_NAME(Open)
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    const DRV_IO_INTENT ioIntent
)
{
     DRV_USART_CLIENT_OBJECT    *clientObj      = (DRV_USART_CLIENT_OBJECT*) gDrvUSARTClientObj;
     unsigned int iClient;
     bool foundIt;

    /* Validate the driver index */
    if ( _DRV_USART_INDEX_GET(drvIndex) >= DRV_USART_INDEX_COUNT )
    {
          return ( DRV_HANDLE_INVALID );
    }
   if(dObj->status != SYS_STATUS_READY)
    {
        /* The USART module should be ready */
        SYS_ASSERT(false, "Was the driver initialized?");
        return DRV_HANDLE_INVALID;
    }

    /* Check for exclusive access */
    if (((( dObj->numClients ) > 0) && DRV_IO_ISEXCLUSIVE(ioIntent)) )
    {
        /* Set that the hardware instance is opened in exclusive mode */
          return ( DRV_HANDLE_INVALID ) ;
    }

    if (OSAL_MUTEX_Lock(dObj->mutexUSART_clientHandle , 0) == OSAL_RESULT_TRUE)
    {
        /* Find available slot in array of client objects */
        foundIt = false;
        for (iClient = 0; iClient < DRV_USART_CLIENTS_NUMBER ; iClient++)
        {
            if ( !clientObj->inUse )
            {
                clientObj->inUse  = true;
                foundIt = true;
                break;
            }
            clientObj += 1;
        }
        OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_clientHandle) == OSAL_RESULT_TRUE),
                     "Unable to unlock client handle mutex" );
    }
    /* OSAL - Unlock Mutex */

    if ( !foundIt )
    {
        /* Couldn't find open slot in object array */
        SYS_ASSERT(false, "Insufficient Clients. Increase the number of clients via DRV_USB_CLIENTS_NUMBER");
        return  DRV_HANDLE_INVALID ;
    }

     /* Increment the number of clients connected to the hardware instance */
    //(dObj->numClients)++;

     clientObj->driverObj = (DRV_USART_OBJECT*)dObj;

     PLIB_USART_TransmitterEnable( dObj->moduleId) ;

    _DRV_USART_LoopbackEnable (dObj->moduleId , dObj) ;

    /* Update the Client Status */
      clientObj->status = DRV_USART_CLIENT_STATUS_READY;

    /* Return the client object */
      return ( ( DRV_HANDLE ) clientObj );

} /* DRV_USART_Open */


/*******************************************************************************
  Function:
    void DRV_USART_Close( DRV_HANDLE handle )

  Summary:
    Removes an opened client.

  Description:
    Closes an opened client of the USART. Clears the memory used by the client
    and removes the client from the driver.

   Remarks:
    None
*/

void driver  _DRV_USART_MAKE_NAME(Close)
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
      DRV_HANDLE handle
)
{
      DRV_USART_CLIENT_OBJECT   *clientObj = (DRV_USART_CLIENT_OBJECT*)handle;

    ( clientObj->inUse ) = 0;

    /* Update the Client Status */
    ( clientObj->status ) = DRV_USART_STATUS_INVALID ;

} /* DRV_USART_Close */


/*******************************************************************************
  Function:
    DRV_USART_CLIENT_STATUS DRV_USART_ClientStatus( DRV_HANDLE handle )

  Summary:
    Gets the status of the USART client.

  Description:
    Returns the present status of the client.

  Remarks:
    The status will be specific to USART and all possible status
    options are listed in DRV_USART_CLIENT_STATUS enum.
*/

DRV_USART_CLIENT_STATUS driver _DRV_USART_MAKE_NAME(ClientStatus)
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
      DRV_HANDLE handle
)
{
      DRV_USART_CLIENT_OBJECT       *clientObj = (DRV_USART_CLIENT_OBJECT*) handle;
      /* Return the client status associated with the handle passed */
      return ( ( clientObj->status ) ) ;

} /* DRV_USART_ClientStatus */

// *****************************************************************************
/*
  Function:
    DRV_USART_BUFFER_STATUS DRV_USART_BufferStatus(  const DRV_HANDLE handle,
        const DRV_USART_BUFFER_HANDLE *bufferHandle);
 */

//DRV_USART_BUFFER_STATUS driver  _DRV_USART_MAKE_NAME(BufferStatus)
uint8_t driver  _DRV_USART_MAKE_NAME(BufferStatus)
(
    DRV_HANDLE handle,
    const DRV_HANDLE bufferHandle
)
{
    DRV_USART_XFER_OBJECT *xFerObj = (DRV_USART_XFER_OBJECT*)bufferHandle;
    return xFerObj->status ;
}

// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t
    DRV_USART_BufferTransferStatus ( const DRV_USART_BUFFER_HANDLE *bufferHandle, const DRV_IO_BUFFER_ID bufferId )
 */

int8_t driver  DRV_USART_BufferTransferStatus(
        DRV_HANDLE handle,
        const DRV_HANDLE bufferHandle)
{
    DRV_USART_XFER_OBJECT       *xferObj        =       (DRV_USART_XFER_OBJECT*)NULL;

    xferObj = (DRV_USART_XFER_OBJECT* ) (bufferHandle) ;

    if(bufferHandle == NULL)
    {
        return -1;
    }
    else
    {
        return (xferObj->nbytes);
    }

}




// *****************************************************************************
/******************************************************************************
  Function:
        DRV_USART_BUFFER_HANDLE* DRV_USART_BufferAdd( const DRV_HANDLE handle,
            DRV_USART_IO_BUFFER_OBJECT *bufferObject) ;
 */

DRV_HANDLE driver  _DRV_USART_MAKE_NAME(BufferAdd)
(
    DRV_HANDLE handle,
    DRV_USART_IO_BUFFER *bufferObject
)
{
    DRV_USART_XFER_OBJECT       *xferObj        =       (DRV_USART_XFER_OBJECT*)NULL;
    DRV_USART_BUFFER_FLAGS      flags           =       0;
//    /* Get the driver object from the client */
//    dObj=clientObj->driverObj;

    flags = bufferObject->flags;
    if (( flags & DRV_USART_BUFFER_FLAG_WRITE ))
    {
        if (OSAL_MUTEX_Lock(dObj->mutexUSART_txBufferTransfer , 0) == OSAL_RESULT_TRUE)
        {
            xferObj  =   _DRV_USART_XferObjectAllocate(bufferObject, &dObj->writeQ);
            OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_txBufferTransfer ) == OSAL_RESULT_TRUE),
                         "Unable to unlock transmitter buffer mutex" );
        }

        if(xferObj == NULL)
        {
            return DRV_HANDLE_INVALID;
        }

        //_DRV_USART_InterruptSourceEnable(DRV_USART_INTERRUPT_SOURCE_TX);
        SYS_INT_SourceEnable(DRV_USART_INTERRUPT_SOURCE_TX);
    }
    else
    {
        if (OSAL_MUTEX_Lock(dObj->mutexUSART_rxBufferTransfer , 0) == OSAL_RESULT_TRUE)
        {
            xferObj  =   _DRV_USART_XferObjectAllocate(bufferObject, &dObj->readQ);
            OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_rxBufferTransfer ) == OSAL_RESULT_TRUE),
                         "Unable to unlock receiver buffer mutex" );
        }
        if(xferObj == NULL)
        {
            return DRV_HANDLE_INVALID;
        }
    }
    return (DRV_HANDLE)(xferObj) ;

}

void driver _DRV_USART_MAKE_NAME(TasksTX)
(
)
{
    DRV_USART_XFER_OBJECT           *xferObj;
    DRV_USART_QUEUE_OBJECT          *queue;
    char                            byte;

    if (SYS_INT_SourceStatusGet(DRV_USART_INTERRUPT_SOURCE_TX))
    {
        //Byte Mode Handling
        dObj->byteTxStatus = DRV_USART_BYTE_IS_READY;
        _DRV_USART_InterruptSourceDisable(DRV_USART_INTERRUPT_SOURCE_TX);
        //Queue Handling
        queue = &dObj->writeQ;
        xferObj = queue->queueStart + queue->currentPointer;

        if(xferObj->status != DRV_USART_BUFFER_COMPLETED)
        {
            if(xferObj->nbytes >= xferObj->size)
            {
                //Transfer complete
                xferObj->status = DRV_USART_BUFFER_COMPLETED;
                if(xferObj->eventCallback!= NULL)
                    xferObj->eventCallback();
                queue->currentPointer++;
                if(queue->currentPointer >= queue->queueSize)
                {
                    queue->currentPointer = 0;
                }
                xferObj = queue->queueStart + queue->currentPointer;

                if(xferObj->status == DRV_USART_BUFFER_COMPLETED)
                {
                    _DRV_USART_InterruptSourceStatusClear(DRV_USART_INTERRUPT_SOURCE_TX);
                    return;
                }
            }
            xferObj->status = DRV_USART_BUFFER_IN_PROGRESS;
            byte = xferObj->dataPointer[xferObj->nbytes++];
            //PLIB_USART_TransmitterByteSend(dObj->moduleId, byte);
            U2TXREG = byte;
            _DRV_USART_InterruptSourceEnable(DRV_USART_INTERRUPT_SOURCE_TX);
        }
    }
    //Send Data
    _DRV_USART_InterruptSourceStatusClear(DRV_USART_INTERRUPT_SOURCE_TX);
}

void driver _DRV_USART_MAKE_NAME(TasksRX)
(   
)
{
    DRV_USART_XFER_OBJECT           *xferObj;
    DRV_USART_QUEUE_OBJECT          *queue;
    char                            byte;

    if (SYS_INT_SourceStatusGet(DRV_USART_INTERRUPT_SOURCE_RX))
    {
        //Byte Mode Handling
        dObj->byteRxStatus = DRV_USART_BYTE_DATA_AVAILABLE;
        dObj->receivedByte = PLIB_USART_ReceiverByteReceive(dObj->moduleId);
        //Queue Handling
        queue = &dObj->readQ;
        xferObj = queue->queueStart + queue->currentPointer;

        if(xferObj->status != DRV_USART_BUFFER_COMPLETED)
        {
            xferObj->status = DRV_USART_BUFFER_IN_PROGRESS;

            byte = PLIB_USART_ReceiverByteReceive(dObj->moduleId);

            xferObj->dataPointer[xferObj->nbytes++] = dObj->receivedByte;

            if(xferObj->nbytes >= xferObj->size)
            {
                //Transfer complete
                xferObj->status = DRV_USART_BUFFER_COMPLETED;
                if(xferObj->eventCallback!= NULL)
                    xferObj->eventCallback();
                queue->currentPointer++;
                if(queue->currentPointer >= queue->queueSize)
                {
                    queue->currentPointer = 0;
                }
                xferObj = queue->queueStart + queue->currentPointer;
            }
        }
    }
    //Send Data
    _DRV_USART_InterruptSourceStatusClear(DRV_USART_INTERRUPT_SOURCE_RX);
}

bool driver _DRV_USART_MAKE_NAME(WriteByte)
(
    const DRV_HANDLE handle,
    const uint8_t byte
)
{
    if (OSAL_MUTEX_Lock(dObj->mutexUSART_txByteTransfer , 0) == OSAL_RESULT_TRUE)
    {
        if(dObj->byteTxStatus == DRV_USART_BYTE_IS_READY)
        {
            dObj->byteTxStatus = DRV_USART_BYTE_PENDING;
            //Send the Data
            OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_txByteTransfer) == OSAL_RESULT_TRUE),
                         "Unable to unlock transmitter mutex" );
            PLIB_USART_TransmitterByteSend (  ( (dObj->moduleId) ) , byte ) ;
            _DRV_USART_InterruptSourceStatusClear(DRV_USART_INTERRUPT_SOURCE_TX);
            _DRV_USART_InterruptSourceEnable(DRV_USART_INTERRUPT_SOURCE_TX);
        }
        else
        {
            //Release MUTEX
            OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_txByteTransfer) == OSAL_RESULT_TRUE),
                         "Unable to unlock transmitter mutex" );
            return false;
        }
        return true;
    }
}

bool driver _DRV_USART_MAKE_NAME(ReadByte)
(
    const DRV_HANDLE handle,
    char *byte
)
{
    //Get MUTEX
    if (OSAL_MUTEX_Lock(dObj->mutexUSART_rxByteTransfer , 0) == OSAL_RESULT_TRUE)
    {
        if(dObj->byteRxStatus == DRV_USART_BYTE_DATA_AVAILABLE)
        {
                //Read the Data
                _DRV_USART_InterruptSourceDisable(DRV_USART_INTERRUPT_SOURCE_RX);
                *byte = PLIB_USART_ReceiverByteReceive ( ( (dObj->moduleId) ) ) ;
                dObj->byteRxStatus = DRV_USART_BYTE_IS_READY;
                OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_rxByteTransfer ) == OSAL_RESULT_TRUE),
                             "Unable to unlock receiver mutex" );
                _DRV_USART_InterruptSourceEnable(DRV_USART_INTERRUPT_SOURCE_RX);
        }
        else
        {
                //Release MUTEX
                OSAL_ASSERT( (OSAL_MUTEX_Unlock(dObj->mutexUSART_rxByteTransfer ) == OSAL_RESULT_TRUE),
                             "Unable to unlock receiver mutex" );
                return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool driver _DRV_USART_QueueAllocate
(
    DRV_USART_QUEUE_OBJECT *queue,
    uint32_t size
)
{
    /* This function tries to allocate the required number
     * of transfer objects to the queue. Returns true if the
     * allocation was successful. Return false otherwise.*/
    unsigned int                    iEntry = 0, freeXferObj=0;
    DRV_USART_XFER_OBJECT           *xferObj;
    
    queue->queueStart     =     NULL;
    xferObj               =     (DRV_USART_XFER_OBJECT*)&gDrvUSARTXferQObj[0];
    //TO DO
    //Initialize RxQueue and TxQueue objects
    for (iEntry = 0; iEntry < DRV_USART_XFER_BUFFER_NUMBER; iEntry ++)
    {
        if(!xferObj->inUse)
        {
            /* We have found a object that is not is use. Increment
             * the free xfer object count and set the start of queue
             * to this object */
            freeXferObj ++;
            if(queue->queueStart == NULL)
            {
                queue->queueStart = (DRV_USART_XFER_OBJECT*)xferObj;
            }
        }
        else
        {
            /* This xfer object is not available */
            freeXferObj = 0;
            queue->queueStart = NULL;
        }

        if(freeXferObj == size)
        {
            /* If we have found the number of xfer objects
             * that we are looking for */
            break;
        }
        /* Check the next transfer object */
        xferObj += 1;
    }

    if((queue->queueStart == NULL) || freeXferObj< size)
    {
        queue->queueSize    =   0;
        queue->queueStart = NULL;
        return  false;
    }
    else
    {
        queue->queueSize    =   size;
        queue->currentPointer = 0;
        xferObj = queue->queueStart;
        for(iEntry = 0; iEntry < size; iEntry++ )
        {
            xferObj->inUse  = true;
            xferObj->status = DRV_USART_BUFFER_COMPLETED;
            xferObj++;
        }
        return true;
    }
}

DRV_USART_XFER_OBJECT * driver _DRV_USART_XferObjectAllocate
(
    DRV_USART_IO_BUFFER *bufferObject,
    DRV_USART_QUEUE_OBJECT *queue
)
{
    DRV_USART_XFER_OBJECT *xferObj = queue->queueStart;
    uint8_t count = queue->currentPointer, iEntry = 0;
    if((xferObj == NULL)||(bufferObject == NULL)||(queue == NULL))
    {
        return  NULL;
    }
    else
    {
        for(iEntry = 0; iEntry < queue->queueSize; iEntry++)
        {
            xferObj =  (DRV_USART_XFER_OBJECT*)(queue->queueStart + count);
            if(xferObj->status == DRV_USART_BUFFER_COMPLETED)
            {
                xferObj->dataPointer            =   bufferObject->buffer;
                xferObj->eventCallback          =   bufferObject->xferCallback;
                xferObj->size                   =   bufferObject->bufferSize;
                xferObj->nbytes                 =   0;
                xferObj->status                 =   DRV_USART_BUFFER_QUEUED;
                return  xferObj;
            }
            (count)++;

            if(count == queue->queueSize)
            {
                count = 0;
            }
        }
        return NULL;
    }
}
