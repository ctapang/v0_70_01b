/*******************************************************************************
  USART Device Driver Definition

  Company:
    Microchip Technology Inc.

  FileName:
    drv_usart.c

  Summary:
    USART Device Driver Definition

  Description:
    The USART device driver provides a simple interface to manage the USART modules
    on Microchip microcontrollers.  This file defines the interface definition
    for the USART driver.
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
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "drv_usart_local.h"

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

void _DRV_USART_LineControlModeSetDyn ( const USART_MODULE_ID plibId,
                                        const DRV_USART_LINE_CONTROL_MODES lineControlMode,
                                        const DRV_USART_HANDSHAKE_MODES flowControl )
{
    if( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8NONE1 )
    {
        if(USART_ExistsLineControlMode_RXandTXCombined(_DRV_USART_PERIPHERAL_ID_GET( plibId )))
        {
            PLIB_USART_LineControlModeSelect(_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8N1 | _DRV_USART_FLOW_CONTROL(flowControl));
        }
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

static void _DRV_USART_SetupHardware
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG_COMMA( const USART_MODULE_ID plibId )
    _DRV_USART_DYN_ARG_COMMA( DRV_USART_OBJ dObj )
    DRV_USART_INIT * usartInit
)
{
    /* Get the USART Interrupt Sources */
    _DRV_USART_STATIC_INT_SRC_TX( _DRV_USART_OBJ(dObj, txInterruptSource) = _DRV_USART_GET_INT_SRC_TX(usartInit->txInterruptSource) );
    _DRV_USART_STATIC_INT_SRC_RX( _DRV_USART_OBJ(dObj, rxInterruptSource) = _DRV_USART_GET_INT_SRC_RX(usartInit->rxInterruptSource) );
    _DRV_USART_STATIC_INT_SRC_ERROR( _DRV_USART_OBJ(dObj, errorInterruptSource) = _DRV_USART_GET_INT_SRC_ERROR(usartInit->errorInterruptSource) );

    /* setup rx and tx polarity */
    _DRV_USART_RXPolarityInverted ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    _DRV_USART_TXPolarityInverted ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;

    /* Setup the stop in idle mode */
    _DRV_USART_PowerState ( _DRV_USART_PERIPHERAL_ID_GET( plibId ) , usartInit ) ;

    /* setup the wake on start mode */
    _DRV_USART_WakeOnStartSetup ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;
    /* Wake on start disable doesnt exist in PLIBs */

    /* Setup line control & handshaking */
    _DRV_USART_LineControlModeSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                    _DRV_USART_LINE_CONTROL_GET(usartInit->lineControlMode) ,
                                    _DRV_USART_HANDSHAKE_MODE_GET(usartInit->handShakeMode ) );

    /* setup operation modes */
    _DRV_USART_OperationModeSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                  _DRV_USART_HANDSHAKE_MODE_GET(usartInit->handShakeMode )) ;

    /* setup Auto address detection */
    _DRV_USART_RXAutoAddressEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;

    /* setup IrDA */
    _DRV_USART_IrDAEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;

    /* setup as sync master or slave */
    _DRV_USART_SyncMasterEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ));
    _DRV_USART_SyncSlaveEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ));

    /* setup Rx FIFO */
    if(USART_ExistsReceiverFIFOLevel_Default(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_ReceiverFIFOLevelSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId )  ,
                                       USART_RECEIVE_FIFO_LEVEL_RECEIVE_BUFFER_ONE_CHAR ) ;
    }

    /* setup Tx FIFO */
    if(USART_ExistsTransmitterFIFO_Default(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_TransmitterFIFOLevelSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                          USART_TRANSMITFIFO_LEVEL_TRANSMIT_ALL_CHAR_TRANSMITTED ) ;
    }
    /* setup high baud rate */
    if(USART_ExistsBaudRateHigh_In16BitRegister(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }

    /* Setup AutoBaud */
    _DRV_USART_AutoBaudSetup ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;

    /* Setup 16 bit mode for BRG */
    _DRV_USART_BaudRate16BitModeSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;

    /* Set high baud rate*/
    if(USART_ExistsBaudRateHigh_In16BitRegister(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }

    if(USART_ExistsBaudRateHigh_In16BitRegister(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , SYS_CLK_PeripheralClockGet(),
                                                                 _DRV_USART_BAUD_RATE_GET ( usartInit->brgValue ) ) ;
    }

    /* Receiver Enable control */
    if(USART_ExistsReceiverEnable_Default(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
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

_DRV_USART_DYN_RETURN_TYPE (SYS_MODULE_OBJ) _DRV_USART_MAKE_NAME ( Initialize )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG_COMMA( const SYS_MODULE_INDEX drvIndex )
    const SYS_MODULE_INIT * const init
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );
    DRV_USART_INIT           *usartInit     = NULL ;

    /* Validate the driver index */
    if ( _DRV_USART_INDEX_GET(drvIndex) >= DRV_USART_INDEX_COUNT )
    {
        _DRV_USART_DYN_RETURN( SYS_MODULE_OBJ_INVALID );
    }

    /* Assign to the local pointer the init data passed */
    usartInit = ( DRV_USART_INIT * ) init ;

    /* Allocate the driver object and set the operation flag to be in use */
    _DRV_USART_OBJ_ALLOCATE ( drvIndex , dObj ) ;
    _DRV_USART_OBJ ( dObj , operationalFlags ) = DRV_USART_OPERATIONAL_FLAG_IN_USE;

    /* Check that the object is valid */
    SYS_ASSERT ( _DRV_USART_ObjectIsValid ( dObj ) , "Hardware Object is invalid" ) ;

    /* Update the USART PLIB Id */
    _DRV_USART_DYN(_DRV_USART_OBJ( dObj , moduleId ) = _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) );
    _DRV_USART_DYN(_DRV_USART_OBJ( dObj, objIndex ) = drvIndex);
    /* Setup the Hardware */
    _DRV_USART_SetupHardware( _DRV_USART_DYN_PARAM_COMMA( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) )
                              _DRV_USART_DYN_PARAM_COMMA( dObj )
                              usartInit ) ;

    /* Enable the USART module */
    if(USART_ExistsEnable_Default(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
    {
        PLIB_USART_Enable ( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) ) ;
    }
    /* For internal Buffer operations */
    _DRV_USART_OBJ ( dObj , txHead)  = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , txTail)  = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxHead)  = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxTail)  = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxStatus.s.empty) = true;
    _DRV_USART_OBJ ( dObj , txStatus.s.empty) = true;
    _DRV_USART_OBJ ( dObj , txStatus.s.full) = false;
    _DRV_USART_OBJ ( dObj , rxStatus.s.full) = false;

    /* Initialize buffer indices and the state machine.*/
    //_DRV_USART_SetupLoopbackOperation ( usartInit , dObj ) ;

    _DRV_USART_MC( _DRV_USART_OBJ(dObj, numClients) = 0 ) ;

    /* Clear the interrupts */
    _DRV_USART_InterruptSourceStatusClear( _DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)) ) ;
    _DRV_USART_InterruptSourceStatusClear( _DRV_USART_GET_INT_SRC_RX(_DRV_USART_OBJ(dObj, rxInterruptSource)) ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceStatusClear( _DRV_USART_GET_INT_SRC_ERROR(_DRV_USART_OBJ(dObj, errorInterruptSource)) ));

    /* Enable the interrupt source in case of interrupt mode */
    _DRV_USART_InterruptSourceEnable( _DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)) ) ;
    _DRV_USART_InterruptSourceEnable( _DRV_USART_GET_INT_SRC_RX(_DRV_USART_OBJ(dObj, rxInterruptSource)) ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceEnable( _DRV_USART_GET_INT_SRC_ERROR(_DRV_USART_OBJ(dObj, errorInterruptSource)) ));

    /* Update the status */
    _DRV_USART_OBJ(dObj, status) = SYS_STATUS_READY;

    /* Return the object structure */
    _DRV_USART_DYN_RETURN( (SYS_MODULE_OBJ)dObj );

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

void _DRV_USART_MAKE_NAME ( Reinitialize )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG_COMMA( SYS_MODULE_OBJ object )
    const SYS_MODULE_INIT * const init
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );
    DRV_USART_INIT * usartInit = NULL;

    /* Check that the object is valid */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver object is invalid" ) ;

    /* Disable the Usart */
    if(USART_ExistsEnable_Default(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
    {
        PLIB_USART_Disable ( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) ) ;
    }
    /* Setup the Hardware */
    _DRV_USART_SetupHardware( _DRV_USART_DYN_PARAM_COMMA( usartInit->usartID )
                              _DRV_USART_DYN_PARAM_COMMA( dObj )
                              usartInit ) ;

    /* Enable the USART module */
    if(USART_ExistsEnable_Default(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
    {
        PLIB_USART_Enable ( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) ) ;
    }

    /* Initialize buffer indices and the state machine.*/
    _DRV_USART_SetupLoopbackOperation ( usartInit , dObj ) ;

    //For internal Buffer operations
    _DRV_USART_OBJ ( dObj , txHead)  = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , txTail)  = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxHead)  = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxTail)  = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
    _DRV_USART_OBJ ( dObj , rxStatus.s.empty) = true;
    _DRV_USART_OBJ ( dObj , txStatus.s.empty) = true;
    _DRV_USART_OBJ ( dObj , txStatus.s.full) = false;
    _DRV_USART_OBJ ( dObj , rxStatus.s.full) = false;

    /* Update the status */
    _DRV_USART_OBJ( dObj ,status) =  SYS_STATUS_READY ;

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

void _DRV_USART_MAKE_NAME ( Deinitialize )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );

    /* Check that the object is valid */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver object is invalid" ) ;

    /* Disable the interrupt */
    _DRV_USART_InterruptSourceDisable( _DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)) ) ;
    _DRV_USART_InterruptSourceDisable( _DRV_USART_GET_INT_SRC_RX(_DRV_USART_OBJ(dObj, rxInterruptSource)) ) ;
    _DRV_USART_ERROR_INT(_DRV_USART_InterruptSourceDisable( _DRV_USART_GET_INT_SRC_ERROR(_DRV_USART_OBJ(dObj, errorInterruptSource)) ));

    /* Disable USART module */
    if(USART_ExistsEnable_Default(_DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) )))
    {
        PLIB_USART_Disable ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) ));
    }

    /* Deinitialize the USART status */
    _DRV_USART_OBJ( dObj ,status) =  SYS_STATUS_UNINITIALIZED ;

} /* DRV_USART_Deinitialize */


/*******************************************************************************
  Function:
    SYS_STATUS DRV_USART_Status ( SYS_MODULE_OBJ object )

  Summary:
    Gets the status of the USART instance

  Description:
    Returns the current status of the USART module.

  Remarks:
    SYS_STATUS_READY	Indicates that any previous module operation for the
                        specified module has completed
    SYS_STATUS_BUSY	Indicates that a previous module operation for the
                        specified module has not yet completed
    SYS_STATUS_ERROR	Indicates that the specified module is in an error state
*/

SYS_STATUS  _DRV_USART_MAKE_NAME ( Status )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver object is invalid" ) ;

    return ( _DRV_USART_OBJ ( dObj ,status) );

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

_DRV_USART_MC_RETURN_TYPE( DRV_HANDLE ) _DRV_USART_MAKE_NAME ( Open )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG_COMMA( const SYS_MODULE_INDEX drvIndex )
    const DRV_IO_INTENT ioIntent
)
{
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) drvIndex );

    /* Validate the driver index */
    if ( _DRV_USART_INDEX_GET(drvIndex) >= DRV_USART_INDEX_COUNT )
    {
        _DRV_USART_MC_RETURN( DRV_HANDLE_INVALID );
    }

    /* Check for exclusive access */
    if ( ( _DRV_USART_MC_Test( _DRV_USART_OBJ ( dObj , operationalFlags ) & DRV_USART_OPERATIONAL_FLAG_EXCLUSIVE_ACCESS )) ||
         ( _DRV_USART_MC_Test(_DRV_USART_OBJ( dObj , numClients ) > 0) && DRV_IO_ISEXCLUSIVE(ioIntent)) )
    {
        /* Set that the hardware instance is opened in exclusive mode */
        _DRV_USART_MC_RETURN( DRV_HANDLE_INVALID ) ;
    }

    /* Check if max number of clients open */
    if ( _DRV_USART_MC_Test(_DRV_USART_OBJ( dObj , numClients ) > DRV_USART_CLIENTS_NUMBER ))
    {
        /* Set that the hardware instance is opened with max clients */
        _DRV_USART_MC_RETURN( DRV_HANDLE_INVALID ) ;
    }

    /* Allocate the client object and set the flag as in use */
    _DRV_USART_MC(clientObj = _DRV_USART_ClientObjectAllocate(_DRV_USART_INDEX_GET(drvIndex))) ;
    _DRV_USART_CLIENT_OBJ ( clientObj , operationalFlags ) |= DRV_USART_OPERATIONAL_FLAG_IN_USE ;

    /* Increment the number of clients connected to the hardware instance */
    _DRV_USART_MC( _DRV_USART_OBJ(dObj, numClients)++ ) ;

    if(DRV_IO_ISEXCLUSIVE(ioIntent))
    {
        _DRV_USART_OBJ ( dObj , operationalFlags ) |= DRV_USART_OPERATIONAL_FLAG_EXCLUSIVE_ACCESS ;
    }

    // OSAL -> Unlock Module Mutex : TODO

    if(USART_ExistsTransmitterEnable_Default(_DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ ( drvIndex ,moduleId) )))
    {
        PLIB_USART_TransmitterEnable ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ ( drvIndex ,moduleId) ) ) ;
    }
    _DRV_USART_LoopbackEnable ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ ( drvIndex ,moduleId) ) , dObj ) ;

    /* Return the client object */
    _DRV_USART_MC_RETURN( ( DRV_HANDLE ) clientObj );

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

void  _DRV_USART_MAKE_NAME ( Close )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_USART_MC_ARG( DRV_HANDLE handle )
)
{
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER)  , "Invalid Client Object" ) ;

    /* To Do: OSAL - lock Mutex */

    /* Delete the Client Instance */
    _DRV_USART_CLIENT_OBJ ( clientObj , operationalFlags ) &= ( ~DRV_USART_OPERATIONAL_FLAG_IN_USE ) ;

    /* To Do: OSAL - unlock Mutex */

    /* Update the Client Status */
    _DRV_USART_CLIENT_OBJ ( clientObj , status ) = DRV_USART_STATUS_INVALID ;

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

DRV_USART_CLIENT_STATUS  _DRV_USART_MAKE_NAME ( ClientStatus )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_USART_MC_ARG( DRV_HANDLE handle )
)
{
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Return the client status associated with the handle passed */
    return (_DRV_USART_CLIENT_OBJ ( clientObj , status ) ) ;

} /* DRV_USART_ClientStatus */


/*******************************************************************************
  Function:
    uint8_t DRV_USART_ReadByte( DRV_HANDLE handle )

  Summary:
    Returns the byte read by the peripheral

  Description:
    This API returns the latest byte present in the internal buffer

  Remarks:
    None
*/

uint8_t _DRV_USART_MAKE_NAME ( ReadByte )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_USART_MC_ARG( DRV_HANDLE handle )
)
{
    uint8_t  c = 0;
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    if(_DRV_USART_OBJ(dObj , rxStatus.s.empty))
    {
        return c;
    }

    c = *_DRV_USART_OBJ(dObj , rxHead);
    _DRV_USART_OBJ(dObj , rxHead)++;

    if(_DRV_USART_OBJ(dObj , rxHead) == (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex)) + sizeof(_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex))))
    {
        _DRV_USART_OBJ(dObj , rxHead) = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
    }

    if(_DRV_USART_OBJ(dObj , rxHead) == _DRV_USART_OBJ(dObj , rxTail))
    {
               // Clears the RX full flag
                // Clears the flag reception complete
        _DRV_USART_OBJ(dObj , rxStatus.s.empty) = true;
    }
    _DRV_USART_OBJ(dObj , rxStatus.s.full) = false;

    return c;

} /* DRV_USART_ReadByte */


/*******************************************************************************
  Function:
    int DRV_USART_Read( DRV_HANDLE handle,  uint8_t *buffer,
                        const unsigned int numbytes )

  Summary:
    Returns the number of bytes read by the USART peripheral

  Description:
    This API returns the number of bytes read by the Peripheral and fills the bytes
    in the application read buffer

  Remarks:
    None
*/

int _DRV_USART_MAKE_NAME ( Read )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
    uint8_t *buffer ,
    const unsigned int numbytes
)
{
     unsigned int numBytesRead = 0 ;
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    while ( numBytesRead < ( numbytes - 1 ))
    {
        if( !_DRV_USART_OBJ(dObj , rxStatus.s.empty) )
        {
                buffer[numBytesRead++] = _DRV_USART_MAKE_NAME( ReadByte ) ( _DRV_USART_MC_PARAM( handle )) ;
        }
        else
        {
            return numBytesRead;
        }
    }

    return numBytesRead ;

} /* DRV_USART_Read */


/*******************************************************************************
  Function:
    void DRV_USART_WriteByte( DRV_HANDLE handle,  uint8_t byte )

  Summary:
    Adds the byte from application buffer to internal buffer

  Description:
    This API adds a data byte from application buffer to internal buffer provided
    there is space available

  Remarks:
    None
*/

void _DRV_USART_MAKE_NAME ( WriteByte )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
    const uint8_t byte
)
{
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    if(_DRV_USART_OBJ(dObj , txStatus.s.full))
    {
        return;
    }

    *_DRV_USART_OBJ(dObj , txTail) = byte;

    if(_DRV_USART_OBJ(dObj , txTail) == (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex)) + sizeof(_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex))))
    {
        _DRV_USART_OBJ(dObj , txTail) = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
    }

    _DRV_USART_OBJ(dObj , txTail)++;

    if(_DRV_USART_OBJ(dObj , txTail) == _DRV_USART_OBJ(dObj , txHead))
    {
        // Sets the flag TX full
        _DRV_USART_OBJ(dObj , txStatus.s.full) = true;
    }

    _DRV_USART_OBJ(dObj , txStatus.s.empty) = false;

    if( !_DRV_USART_InterruptSourceEnabled( _DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)) ) )
    {
        _DRV_USART_InterruptSourceEnable(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));
    }

} /* DRV_USART_Write */


/*******************************************************************************
  Function:
    unsigned int DRV_USART_Write( DRV_HANDLE handle,  uint8_t *buffer,
                                  const unsigned int numbytes )

  Summary:
    Returns the number of bytes written into the internal buffer

  Description:
    This API transfers the data from application buffer to internal buffer and returns
    the number of bytes added in that queue

  Remarks:
    None
*/

unsigned int _DRV_USART_MAKE_NAME ( Write )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
    const uint8_t *buffer ,
    const unsigned int numbytes
)
{
    unsigned int numBytesWritten = 0 ;
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    while ( numBytesWritten < ( numbytes - 1 ))
    {
        if(!_DRV_USART_OBJ(dObj , txStatus.s.full))
        {
            _DRV_USART_MAKE_NAME ( WriteByte ) ( _DRV_USART_MC_PARAM_COMMA( handle )
                                                buffer[numBytesWritten++] ) ;
        }
        else
        {
            return numBytesWritten;
        }
    }

    return numBytesWritten ;

} /* DRV_USART_Write */


/*******************************************************************************
  Function:
    DRV_USART_TRANSFER_STATUS DRV_USART_TransferStatusGet ( DRV_HANDLE handle )

  Summary:
    Returns the current status of the internal buffer

  Description:
    This API maintains and returns the current status of both the internal buffers

  Remarks:
    None
*/

DRV_USART_TRANSFER_STATUS _DRV_USART_MAKE_NAME ( TransferStatus )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_USART_MC_ARG( DRV_HANDLE handle )
)
{
    DRV_USART_TRANSFER_STATUS status = 0;
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Check for the Client validity */
    SYS_ASSERT( ( _DRV_USART_MC_Test( clientObj < DRV_USART_CLIENTS_NUMBER) ) , "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    if(_DRV_USART_OBJ(dObj , txStatus.s.full))
    {
        status |= DRV_USART_TRANSFER_STATUS_TX_FULL;
    }

    if(_DRV_USART_OBJ(dObj , txStatus.s.empty))
    {
        status |= DRV_USART_TRANSFER_STATUS_TX_EMPTY;
    }

    if(_DRV_USART_OBJ(dObj , rxStatus.s.full))
    {
        status |= DRV_USART_TRANSFER_STATUS_RX_FULL;
    }

    if(_DRV_USART_OBJ(dObj , rxStatus.s.empty))
    {
        status |= DRV_USART_TRANSFER_STATUS_RX_EMPTY;
    }
    else
    {
        status |= DRV_USART_TRANSFER_STATUS_RX_DATA_PRESENT;
    }

    return status;

} /* DRV_USART_TransferStatusGet */


/*******************************************************************************
  Function:
    void DRV_USART_TasksTX ( SYS_MODULE_OBJ object )

  Summary:
    Maintains the driver's tramsmitter state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal transmitter state
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.
*/

void  _DRV_USART_MAKE_NAME ( TasksTX )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );
    uint8_t byte ;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver Object is invalid" ) ;

    while (! PLIB_USART_ExistsTransmitterBufferFullStatus(_DRV_USART_OBJ(dObj , moduleId)))
    {
        byte = *_DRV_USART_OBJ(dObj , txHead);

        if(_DRV_USART_OBJ(dObj , txHead) == (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex)) + sizeof(_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex))))
        {
            _DRV_USART_OBJ(dObj , txHead) = (uint8_t *)_DRV_USART_BYTEQ_TX(_DRV_USART_OBJ(dObj, objIndex));
        }

        _DRV_USART_OBJ(dObj , txHead)++;

        _DRV_USART_OBJ(dObj , txStatus.s.full) = false;

        if(USART_ExistsTransmitter_Default(_DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) )))
        {
            PLIB_USART_TransmitterByteSend ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) ) , byte ) ;
        }
        if(_DRV_USART_OBJ(dObj , txHead) == _DRV_USART_OBJ(dObj , txTail))
        {
            _DRV_USART_OBJ(dObj , txStatus.s.empty) = true;
            break;
        }
    }

    _DRV_USART_InterruptSourceStatusClear(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));

    if(_DRV_USART_OBJ(dObj , txStatus.s.empty))
    {
        _DRV_USART_InterruptSourceDisable( _DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)) );
    }

} /* DRV_USART_TasksTX */


/*******************************************************************************
  Function:
    void DRV_USART_TasksRX ( SYS_MODULE_OBJ object )

  Summary:
    Maintains the driver's receiver state machine and implements its ISR

  Description:
    This routine is used to maintain the driver's internal receiver state
    machine and implement its ISR for interrupt-driven implementations.

  Precondition:
    The DRV_USART_Initialize routine must have been called for the specified
    USART driver instance.

  Parameters:
    object      - Object handle for the specified driver instance (returned from
                  DRV_USART_Initialize)

  Returns:
    None.
*/

void  _DRV_USART_MAKE_NAME ( TasksRX )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_USART_DYN( DRV_USART_OBJ    dObj     = (DRV_USART_OBJ) object );
    _DRV_USART_DYN( SYS_MODULE_INDEX objIndex = _DRV_USART_OBJ(dObj, objIndex));
    uint8_t                         byte ;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver Object is invalid" ) ;

    while (PLIB_USART_ExistsReceiverDataAvailableStatus (_DRV_USART_OBJ(dObj , moduleId) ))  // Do not loop in a tasks routine waiting for HW. -Bud
    {
        /* If a read request is recieved and data is available to read
           This state does all the work of reading the data from the RX
           buffer */

        // Receive a byte in the buffer
        if (USART_ExistsReceiver_Default(_DRV_USART_PERIPHERAL_ID_GET(_DRV_USART_OBJ(dObj , moduleId))))
        {
            byte =  PLIB_USART_ReceiverByteReceive( _DRV_USART_PERIPHERAL_ID_GET(_DRV_USART_OBJ(dObj , moduleId)) );
        }
        // Sets the flag data present

        *_DRV_USART_OBJ(dObj , rxTail) = byte;
        _DRV_USART_OBJ(dObj , rxTail)++;

        if(_DRV_USART_OBJ(dObj , rxTail) == ((uint8_t *)_DRV_USART_BYTEQ_RX(objIndex)) + sizeof(_DRV_USART_BYTEQ_RX(objIndex)))
        {
            _DRV_USART_OBJ(dObj , rxTail) = (uint8_t *)_DRV_USART_BYTEQ_RX(_DRV_USART_OBJ(dObj, objIndex));
        }

        if(_DRV_USART_OBJ(dObj , rxTail) == _DRV_USART_OBJ(dObj , rxHead))
        {
                        //Sets the flag RX full
            _DRV_USART_OBJ(dObj , rxStatus.s.full) = true;
        }
        _DRV_USART_OBJ(dObj , rxStatus.s.empty) = false;
    }

    _DRV_USART_InterruptSourceStatusClear( _DRV_USART_GET_INT_SRC_RX(_DRV_USART_OBJ(dObj, rxInterruptSource)) ) ;

} /* DRV_USART_TasksRX */


/*******************************************************************************
 End of File
*/

