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
File Name:  drv_usart_clientbuffer.c
Copyright Ã?Â© 2009-2010 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED Ã¢â?¬Å?AS ISÃ¯Â¿Â½? WITHOUT WARRANTY OF ANY KIND,
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

#include "usart/src/drv_usart_local.h"


extern char dirtyflag;
uint8_t *testbuffer;
// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t DRV_USART_Read( const DRV_HANDLE handle,  uint8_t *buffer,  const uint32_t numbytes);
 */
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

#include "usart/src/drv_usart_local.h"


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
    if      ( lineControlMode & DRV_USART_LINE_CONTROL_MODE_8NONE1 )
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
    //_DRV_USART_PowerState ( _DRV_USART_PERIPHERAL_ID_GET( plibId ) , usartInit ) ;

    /* setup the wake on start mode */
    _DRV_USART_WakeOnStartSetup ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;
    /* Wake on start disable doesnt exist in PLIBs */

    /* Setup line control & handshaking */
    //_DRV_USART_LineControlModeSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
    //                                _DRV_USART_LINE_CONTROL_GET(usartInit->lineControlMode) ,
    //                                _DRV_USART_HANDSHAKE_MODE_GET(usartInit->handShakeMode ) );

    _DRV_USART_LineControlModeSet8N1(_DRV_USART_PERIPHERAL_ID_GET ( plibId ),USART_8N1);
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
    if(PLIB_USART_ExistsReceiverFIFOLevel(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_ReceiverFIFOLevelSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId )  ,
                                       USART_RECEIVE_FIFO_LEVEL_RECEIVE_BUFFER_ONE_CHAR ) ;
    }

    /* setup Tx FIFO */
    if(PLIB_USART_ExistsTransmitterFIFO(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_TransmitterFIFOLevelSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ,
                                          USART_TRANSMITFIFO_LEVEL_TRANSMIT_ALL_CHAR_TRANSMITTED ) ;
    }
    /* setup high baud rate */
    if(PLIB_USART_ExistsBaudRateHigh(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }

    /* Setup AutoBaud */
    _DRV_USART_AutoBaudSetup ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , usartInit ) ;

    /* Setup 16 bit mode for BRG */
    _DRV_USART_BaudRate16BitModeSelect ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;

    /* Set high baud rate*/
    if(PLIB_USART_ExistsBaudRateHigh(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }

    if(PLIB_USART_ExistsBaudRateHigh(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_BaudRateHighSet ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) , SYS_CLK_PeripheralClockGet(),
                                                                 _DRV_USART_BAUD_RATE_GET ( usartInit->brgValue ) ) ;
    }

    /* Receiver Enable control */
    if(PLIB_USART_ExistsReceiverEnable(_DRV_USART_PERIPHERAL_ID_GET ( plibId )))
    {
        PLIB_USART_ReceiverEnable ( _DRV_USART_PERIPHERAL_ID_GET ( plibId ) ) ;
    }


    /*Initialize Buffers and Queues*/
    _DRV_USART_BufferInitialize( dObj );
    _DRV_USART_InitializeQueues(dObj);




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
    //SYS_ASSERT ( _DRV_USART_ObjectIsValid ( dObj ) , "Hardware Object is invalid" ) ;

    /* Update the USART PLIB Id */
    _DRV_USART_DYN(_DRV_USART_OBJ( dObj , moduleId ) = _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) );
    _DRV_USART_DYN(_DRV_USART_OBJ( dObj, objIndex ) = drvIndex);
    /* Setup the Hardware */
    _DRV_USART_SetupHardware( _DRV_USART_DYN_PARAM_COMMA( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) )
                              _DRV_USART_DYN_PARAM_COMMA( dObj )
                              usartInit ) ;

    /* Enable the USART module */
    if(PLIB_USART_ExistsEnable(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
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
    if(PLIB_USART_ExistsEnable(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
    {
        PLIB_USART_Disable ( _DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID ) ) ;
    }

    /* Setup the Hardware */
    _DRV_USART_SetupHardware( _DRV_USART_DYN_PARAM_COMMA( usartInit->usartID )
                              _DRV_USART_DYN_PARAM_COMMA( dObj )
                              usartInit ) ;

    /* Enable the USART module */
    if(PLIB_USART_ExistsEnable(_DRV_USART_PERIPHERAL_ID_GET( usartInit->usartID )))
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
    if(PLIB_USART_ExistsEnable(_DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) )))
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
    if(PLIB_USART_ExistsTransmitterEnable(_DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ ( dObj ,moduleId) )))
    {
        PLIB_USART_TransmitterEnable ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ ( dObj ,moduleId) ) ) ;
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

int32_t _DRV_USART_MAKE_NAME ( Read )
(
        _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
        uint8_t *buffer ,
        const uint32_t numbytes )
{
    DRV_USART_BUFFER_HANDLE          bufferHandle = -1 ;
    DRV_USART_IO_BUFFER              bufferObject ;
    int32_t                          numBytesRead = 0 ;

    bufferObject.buffer = buffer ;
    bufferObject.bufferSize = numbytes ;
    bufferObject.flags = DRV_USART_BUFFER_FLAG_READ ;

    bufferHandle = _DRV_USART_MAKE_NAME ( BufferAdd ) ( _DRV_USART_MC_ARG_COMMA( handle )
            & bufferObject ) ;

    SYS_ASSERT ( ( bufferHandle != (DRV_USART_BUFFER_HANDLE) NULL ) , "Unable to queue buffers for reading" ) ;

    while ( numBytesRead < ( numbytes - 1 ))
    {
        numBytesRead = _DRV_USART_MAKE_NAME ( BufferTransferStatus ) ( _DRV_USART_MC_ARG_COMMA( handle ) bufferHandle ) ;
        /* OSAL - Block for an event, else for the non-blocking call return */
    }

    return numBytesRead ;
}
#if 0
// *****************************************************************************
/******************************************************************************
o?  Function:
    uint8_t DRV_USART_Read( const DRV_HANDLE handle,  uint8_t *buffer,  const uint32_t numbytes);
 */

int32_t DRV_USART_FUNC_NAME ( ReadFromAddress )( DRV_USART_HANDLE_ARG_M ( handle )
uint8_t *buffer ,
        const uint32_t numbytes )
{
    DRV_USART_BUFFER_HANDLE          bufferHandle = -1 ;
    DRV_USART_IO_BUFFER              bufferObject ;
    int32_t                          numBytesRead = 0 ;

    bufferObject.buffer = buffer ;
    bufferObject.bufferSize = numbytes ;
    bufferObject.flags = DRV_USART_BUFFER_FLAG_READ_FROM_ADDRESS ;

    bufferHandle = DRV_USART_FUNC_NAME ( BufferAdd ) ( DRV_USART_HANDLE_PARAM_M ( handle )
            & bufferObject ) ;

    SYS_ASSERT ( ( bufferHandle != (DRV_USART_BUFFER_HANDLE) NULL ) , "Unable to queue buffers for reading" ) ;

    while ( numBytesRead < ( numbytes - 1 ))
    {
        numBytesRead = DRV_USART_FUNC_NAME ( BufferTransferStatus ) ( DRV_USART_HANDLE_PARAM_M ( handle ) bufferHandle ) ;
        /* OSAL - Block for an event, else for the non-blocking call return */
    }

    return numBytesRead ;
}
#endif
// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t DRV_USART_Write( const DRV_HANDLE handle,  uint8_t *buffer,  const uint32_t numbytes);
 */

unsigned int _DRV_USART_MAKE_NAME ( Write )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
        _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
        const uint8_t *buffer ,
        const uint32_t numbytes
)
{
    DRV_USART_BUFFER_HANDLE          bufferHandle = -1 ;
    DRV_USART_IO_BUFFER              bufferObject ;
    int32_t                          numBytesWritten = 0 ;

    bufferObject.buffer = (uint8_t *) buffer ;
    bufferObject.bufferSize = numbytes ;
    bufferObject.flags = DRV_USART_BUFFER_FLAG_WRITE ;

    bufferHandle = _DRV_USART_MAKE_NAME ( BufferAdd )(_DRV_USART_MC_ARG_COMMA( handle )&bufferObject) ;

    SYS_ASSERT ( ( bufferHandle != (DRV_USART_BUFFER_HANDLE) NULL ) , "Unable to queue buffers for writing" ) ;

    while ( numBytesWritten < ( numbytes - 1 ))
    {
        numBytesWritten = _DRV_USART_MAKE_NAME ( BufferTransferStatus )(_DRV_USART_MC_ARG_COMMA( handle ) bufferHandle ) ;
        /* OSAL - Block for an event, else for the non-blocking call return */
    }

    return numBytesWritten ;
}

#if 0
// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t DRV_USART_WriteToAddress( const DRV_HANDLE handle,  uint8_t *buffer,  const uint32_t numbytes);
 */

int32_t DRV_USART_FUNC_NAME ( WriteToAddress )(  DRV_USART_HANDLE_ARG_M ( handle )
        const uint8_t address ,
        const uint8_t *buffer ,
        const uint32_t numbytes )
{
    DRV_USART_BUFFER_HANDLE          bufferHandle = -1 ;
    DRV_USART_IO_BUFFER              bufferObject ;
    int32_t                          numBytesWritten = 0 ;

    bufferObject.buffer = (uint8_t *) buffer ;
    bufferObject.bufferSize = numbytes ;
    bufferObject.address = address ;
    bufferObject.flags = DRV_USART_BUFFER_FLAG_WRITE_TO_ADDRESS ;

    bufferHandle = DRV_USART_FUNC_NAME ( BufferAdd ) ( DRV_USART_HANDLE_PARAM_M ( handle )
            & bufferObject ) ;

    SYS_ASSERT ( ( bufferHandle != (DRV_USART_BUFFER_HANDLE) NULL ) , "Unable to queue buffers for writing" ) ;

    while ( numBytesWritten < ( numbytes - 1 ))
    {
        numBytesWritten = DRV_USART_FUNC_NAME ( BufferTransferStatus ) ( DRV_USART_HANDLE_PARAM_M ( handle ) bufferHandle ) ;
        /* OSAL - Block for an event, else for the non-blocking call return */
    }

    return numBytesWritten ;
}


// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t DRV_USART_Write( const DRV_HANDLE handle,  uint8_t *buffer,  const uint32_t numbytes);
 */

int32_t DRV_USART_FUNC_NAME ( WriteAfterBreak )( DRV_USART_HANDLE_ARG_M ( handle )
        const uint8_t *buffer ,
        const uint32_t numbytes )
{
    DRV_USART_BUFFER_HANDLE          bufferHandle = -1 ;
    DRV_USART_IO_BUFFER              bufferObject ;
    int32_t                          numBytesWritten = 0 ;

    bufferObject.buffer = (uint8_t *) buffer ;
    bufferObject.bufferSize = numbytes ;
    bufferObject.flags = DRV_USART_BUFFER_FLAG_WRITE_AFTER_BREAK ;

    bufferHandle = DRV_USART_FUNC_NAME ( BufferAdd ) ( DRV_USART_HANDLE_PARAM_M ( handle )
            & bufferObject ) ;

    SYS_ASSERT ( ( bufferHandle != (DRV_USART_BUFFER_HANDLE) NULL ) , "Unable to queue buffers for writing" ) ;

    while ( numBytesWritten < ( numbytes - 1 ))
    {
        numBytesWritten = DRV_USART_FUNC_NAME ( BufferTransferStatus ) ( DRV_USART_HANDLE_PARAM_M ( handle ) bufferHandle ) ;
        /* OSAL - Block for an event, else for the non-blocking call return */
    }

    return numBytesWritten ;
}

#endif
// *****************************************************************************
/******************************************************************************
  Function:
        DRV_USART_BUFFER_HANDLE* DRV_USART_BufferAdd( const DRV_HANDLE handle,
            DRV_USART_IO_BUFFER_OBJECT *bufferObject) ;
 */

DRV_HANDLE  _DRV_USART_MAKE_NAME ( BufferAdd )
(  
    _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
    DRV_USART_IO_BUFFER *bufferObject
)
{
    _DRV_USART_MC( DRV_USART_CLIENT_OBJ clientObj = (DRV_USART_CLIENT_OBJ) 0 );
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) 0 );
    _DRV_USART_MC(DRV_USART_BUFFER_OBJ bufferObj = (DRV_USART_BUFFER_OBJ)0);
    bool                                           readFromAddress    = false ;
    DRV_USART_BUFFER_FLAGS                         flags = 0;
    DRV_IO_BUFFER_TYPES              ioType ;
    DRV_USART_BUFFER_OBJECT         *usart_bufferObject = NULL ;
    
    /* Check if the handle is valid */
    uint8_t *buffer = bufferObject->buffer;
    uint32_t bufferSize = bufferObject->bufferSize;

    testbuffer = bufferObject->buffer;
    /* Get the Client object from the handle passed */
    _DRV_USART_MC( clientObj = handle ) ;

    /* Get the driver object from the client */
    _DRV_USART_DYN(dObj=_DRV_USART_CLIENT_OBJ(clientObj,driverObj));

    //moduleId = _DRV_USART_HW_INSTANCE(moduleIndex).moduleId;

    flags = bufferObject->flags;
    if (( flags & DRV_USART_BUFFER_FLAG_WRITE ))
    {
        ioType = DRV_IO_BUFFER_TYPE_WRITE ;
    }
    else
    {
        ioType = DRV_IO_BUFFER_TYPE_READ ;
    }

    bufferObj = _DRV_USART_CreateBufferObjectforQ(bufferObject->buffer ,
                                                  bufferObject->bufferSize ,
                                                  ioType ) ;

    usart_bufferObject = &gDrvUsartBufferQObj[bufferObj];
    /* Add the transaction buffer to the hardware read Q*/
    if (bufferObj != -1)
    {
#if 0
        if (_DRV_USART_IsWriteToAddressEnabled(flags))
        {
            _DRV_USART_WRITE_BUFFER(bufferObjectIndex).address = bufferObject->address ;
        }
#endif
         //_DRV_USART_AddWriteBufferObject(moduleIndex, bufferObjectIndex);

        _DRV_USART_SetBufferObjectHandle(bufferObj, handle);
        
        if(ioType == DRV_IO_BUFFER_TYPE_WRITE)
        {
            QUEUE_Push(&_DRV_USART_OBJ(dObj, writeQ), (void *)usart_bufferObject);
        }
        else
        {
            QUEUE_Push(&_DRV_USART_OBJ(dObj, readQ), (void *)usart_bufferObject);
        }

         _DRV_USART_InterruptSourceEnable(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));

        // OSAL --> Unlock the instance mutex

        _DRV_USART_BUFFER_OBJ(bufferObj, status) = DRV_USART_BUFFER_QUEUED ;

    /* Return the handle to the transaction buffer */
    return (DRV_USART_BUFFER_HANDLE)bufferObj ;
    }

}

// *****************************************************************************
/*
  Function:
    DRV_USART_BUFFER_STATUS DRV_USART_BufferStatus(  const DRV_HANDLE handle,
        const DRV_USART_BUFFER_HANDLE *bufferHandle);
 */

DRV_USART_BUFFER_STATUS  _DRV_USART_MAKE_NAME ( BufferStatus )(
                            _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
                            const DRV_USART_BUFFER_HANDLE bufferHandle)
{
    _DRV_USART_MC(DRV_USART_BUFFER_OBJ bufferObj = (DRV_USART_BUFFER_OBJ)0);

    bufferObj = (uint8_t) bufferHandle ;

    return _DRV_USART_BUFFER_OBJ(bufferObj, status) ;
}

// *****************************************************************************
/******************************************************************************
  Function:
    uint8_t
    DRV_USART_BufferTransferStatus ( const DRV_USART_BUFFER_HANDLE *bufferHandle, const DRV_IO_BUFFER_ID bufferId )
 */

int8_t  _DRV_USART_MAKE_NAME ( BufferTransferStatus )(
        _DRV_USART_MC_ARG_COMMA( DRV_HANDLE handle )
        const DRV_USART_BUFFER_HANDLE bufferHandle)
{
    _DRV_USART_MC(DRV_USART_BUFFER_OBJ bufferObj = (DRV_USART_BUFFER_OBJ)0);

    bufferObj = (uint8_t ) (bufferHandle) ;
#if 0
    if (!DRV_USART_CheckBufferObjectHandle ( bufferObjectIndex , handle ))
    {
        return -1 ;
    }
#endif
    if (_DRV_USART_BUFFER_OBJ(bufferObj, bufferFlags) & DRV_USART_BUFFER_FLAG_READ)
    {
        if (_DRV_USART_BUFFER_OBJ(bufferObj, bufferObject).buffer != (uint8_t *) NULL)
        {
            return (_DRV_USART_BUFFER_OBJ(bufferObj, bufferObject ).count ) ;
        }
    }
    else
    {
        if (_DRV_USART_BUFFER_OBJ(bufferObj, bufferObject).buffer != (uint8_t *) NULL)
        {
            return (_DRV_USART_BUFFER_OBJ(bufferObj, bufferObject).size -  _DRV_USART_BUFFER_OBJ(bufferObj, bufferObject).count) ;
        }
    }

    return -1 ;
}


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
    _DRV_USART_MC(DRV_USART_BUFFER_OBJ bufferObj = (DRV_USART_BUFFER_OBJ)0);
    BUFFER_OBJECT                   *bufferObject;
    uint8_t                          byte ;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver Object is invalid" ) ;

    //_DRV_USART_ClearStatusPreSend(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));

    //while (!PLIB_USART_TransmitterBufferIsFull(_DRV_USART_OBJ(dObj , moduleId)))
    while(!U2STAbits.UTXBF )
    {
        /* Check if there is a write buffer associated with the
           instance*/
        if(_DRV_USART_CheckCurrentBuffer(_DRV_USART_OBJ(dObj, currentWriteBuffer)))
        {
            _DRV_USART_OBJ(dObj, currentWriteBuffer) = _DRV_USART_GetNextBufferObject(&(_DRV_USART_OBJ(dObj, writeQ)));
        }

        /* Check if the valid buffer is available. */
        if (_DRV_USART_OBJ(dObj, currentWriteBuffer)!= NULL)
        {
#if 0
            /* If the write buffer needs to send the break first */
            if(_DRV_USART_IsWriteAfterBreakEnabled(_DRV_USART_WRITE_BUFFER(bufferObjectIndex).bufferFlags))
            {
                PLIB_USART_TransmitterBreakSend ( DRV_USART_MODULE_ID ( index ) ) ;
                _DRV_USART_CLEAR_FLAG ( _DRV_USART_WRITE_BUFFER(bufferObjectIndex).bufferFlags , DRV_USART_BUFFER_FLAG_WRITE_AFTER_BREAK ) ;
                while (!PLIB_USART_TransmitterBreakSendCompleted ( DRV_USART_MODULE_ID ( index ) )) ;
            }

            /* If the write buffer needs to send the address before teh
               data. */
            if(_DRV_USART_IsWriteToAddressEnabled(_DRV_USART_WRITE_BUFFER(bufferObjectIndex).bufferFlags))
            {
                PLIB_USART_TransmitterAddressSend ( DRV_USART_MODULE_ID ( index ) , _DRV_USART_WRITE_BUFFER(bufferObjectIndex).address ) ;
                _DRV_USART_CLEAR_FLAG (_DRV_USART_WRITE_BUFFER(bufferObjectIndex).bufferFlags , DRV_USART_BUFFER_FLAG_WRITE_TO_ADDRESS ) ;

                break ;
            }
#endif
            //bufferObject = (BUFFER_OBJECT*)_DRV_USART_OBJ(dObj, currentWriteBuffer)->bufferObject;

            bufferObject = (BUFFER_OBJECT *)&((gDrvUSARTObj[dObj].currentWriteBuffer)->bufferObject) ;
            byte = BUFFER_ReadByte ( bufferObject ) ;

            //byte = _DRV_USART_WRITE_BUFFER(bufferObjectIndex).buffer[_DRV_USART_WRITE_BUFFER(bufferObjectIndex).readIndex++];
            //_DRV_USART_WRITE_BUFFER(bufferObjectIndex).count--;

            PLIB_USART_TransmitterByteSend ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) ) , byte ) ;

            if (BUFFER_IsBufferEmpty ( bufferObject ))
            {
                /* Need to check that the callback is null or not,
                   the PIC 18 is having troubles with callbacks in the ISRs */
                //_DRV_USART_NotifyWriteComplete (_DRV_USART_OBJ(dObj, currentWriteBuffer)->handle ) ;
                // Pop the buffer.
                /* OSAL --> Lock the instance mutex */
                QUEUE_Pop(&(_DRV_USART_OBJ(dObj, writeQ)));
                /* OSAL --> Unlock the instance mutex */
                _DRV_USART_OBJ(dObj, currentWriteBuffer)->status =  DRV_USART_BUFFER_COMPLETED ;

                _DRV_USART_OBJ(dObj, currentWriteBuffer)->operationalFlags = 0;

                _DRV_USART_OBJ(dObj, currentWriteBuffer) = NULL;
            }
        }

        // Check if the transmission is complete
        if(QUEUE_IsEmpty(&(_DRV_USART_OBJ(dObj, writeQ))) && ((_DRV_USART_OBJ(dObj, currentWriteBuffer) == NULL )))
        {
            _DRV_USART_InterruptSourceDisable(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));
            break;
        }
    }

    _DRV_USART_ClearStatusPostSend(_DRV_USART_GET_INT_SRC_TX(_DRV_USART_OBJ(dObj, txInterruptSource)));
}


// *****************************************************************************
/******************************************************************************
  Function:
    void
    DRV_USART_Tasks_RX ( USART_MODULE_ID index)
 */

void  _DRV_USART_MAKE_NAME ( TasksRX )
( 
    _DRV_USART_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_USART_DYN( DRV_USART_OBJ dObj = (DRV_USART_OBJ) object );
    _DRV_USART_MC(DRV_USART_BUFFER_OBJ bufferObj = (DRV_USART_BUFFER_OBJ)0);
    BUFFER_OBJECT                   *bufferObject;
    uint8_t                          byte ;

    /* Check for the valid driver object passed */
    //SYS_ASSERT( _DRV_USART_ObjectIsValid( dObj ) , "Driver Object is invalid" ) ;

    //while (_DRV_USART_ReceiverDataAvailable (_DRV_USART_OBJ(dObj , moduleId) ))
    while(PLIB_USART_ReceiverDataIsAvailable (_DRV_USART_PERIPHERAL_ID_GET( _DRV_USART_OBJ(dObj , moduleId)  ) ))
    {
        // Receive a byte in the buffer
        byte = PLIB_USART_ReceiverByteReceive ( _DRV_USART_PERIPHERAL_ID_GET ( _DRV_USART_OBJ(dObj , moduleId) ) ) ;

        if(_DRV_USART_CheckCurrentBuffer(_DRV_USART_OBJ(dObj, currentReadBuffer)))
        {
            /* If a read buffer is available, get the read buffer
               from the read Q of the hardware instance. */
            _DRV_USART_OBJ(dObj, currentReadBuffer) = _DRV_USART_GetNextBufferObject(&(_DRV_USART_OBJ(dObj, readQ)));
        }

        /* Check if the read buffer is valid */
        if (_DRV_USART_OBJ(dObj, currentReadBuffer)!= NULL)
        {
#if 0
            if(_DRV_USART_IsReadFromAddressEnabled(_DRV_USART_READ_BUFFER(bufferObjectIndex).bufferFlags))
            {
                DRV_USART_485ReadComplete(hwInstance, byte, index);
                // Check that the address is what is required
                break ;
            }
#endif
            bufferObject = (BUFFER_OBJECT *)&((gDrvUSARTObj[dObj].currentReadBuffer)->bufferObject) ;

            BUFFER_WriteByte ( bufferObject , byte ) ;

            if (BUFFER_IsBufferFull ( bufferObject ))
            {
                // Notify - Read complete
                //DRV_USART_NotifyReadComplete (_DRV_USART_OBJ(dObj, currentWriteBuffer)->handle ) ;

                // Pop the buffer.
                /* Pop the buffer from the hardware instance Q. Perform
                   any clean up of the buffers that is required to be
                   done. */
                /* OSAL --> Lock the instance mutex */
                dirtyflag = 1;
                QUEUE_Pop(&(_DRV_USART_OBJ(dObj, readQ)));
                /* OSAL --> Unlock the instance mutex */

                _DRV_USART_OBJ(dObj, currentReadBuffer)->status =  DRV_USART_BUFFER_COMPLETED ;

                _DRV_USART_OBJ(dObj, currentReadBuffer)->operationalFlags = 0;

                _DRV_USART_OBJ(dObj, currentReadBuffer) = NULL;
//                //DRV_USART_485SetupToReadAddress(moduleIndex, index);

            }
        }
        if(QUEUE_IsEmpty(&(_DRV_USART_OBJ(dObj, readQ))) && ((_DRV_USART_OBJ(dObj, currentReadBuffer) == NULL )))
        {
            break;
        }
    }

    //SYS_INT_SourceStatusClear(_DRV_USART_RX_INT_SRC(moduleIndex));

}

/*******************************************************************************
 End of File
*/
