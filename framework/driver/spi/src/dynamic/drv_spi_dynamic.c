/*******************************************************************************
  SPI Device Driver Definition

  Company:
    Microchip Technology Inc.

  File Name:
    drv_spi_dynamic.c

  Summary:
    SPI Device Driver Dynamic Multiple Client Implementation

  Description:
    The SPI device driver provides a simple interface to manage the SPI
    modules on Microchip microcontrollers.  This file Implements the core
    interface routines for the SPI driver.

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

#include "driver/spi/src/drv_spi_local.h"

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

static DRV_SPI_OBJ             gDrvSPIObj[DRV_SPI_INSTANCES_NUMBER] ;


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

static DRV_SPI_CLIENT_OBJ      gDrvSPIClientObj [ DRV_SPI_CLIENTS_NUMBER ] ;


// *****************************************************************************
/* Driver data objects.

  Summary:
    Defines the data object.

  Description:
    This data type defines the data objects. This is used to queue the user
    requests for different operations.

  Remarks:
    None
*/

static DRV_SPI_BUFFER_OBJECT	gDrvSPIBufferObj [ DRV_SPI_INSTANCES_NUMBER ][ DRV_SPI_BUFFER_OBJ_SIZE ];


// *****************************************************************************
/* Macro: _DRV_SPI_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member

  Description:
    Either return the static object or returns the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_SPI_CLIENT_OBJ(obj,mem)    obj->mem


// *****************************************************************************
/* Macro: _DRV_SPI_CLIENT_OBJ_GET(obj)

  Summary:
    Returns the appropriate client instance

  Description:
    Either return the static object or returns the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_SPI_CLIENT_OBJ_GET(obj)    &gDrvSPIClientObj[obj]

// *****************************************************************************
/* Macro: _DRV_SPI_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member

  Description:
    Either return the static object or returns the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_SPI_DATA_OBJ(obj,mem)    ((DRV_SPI_BUFFER_OBJECT*)(obj))->mem


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    static void _DRV_SPI_SetupHardware ( const SPI_MODULE_ID    plibId,
                                        DRV_SPI_OBJ_HANDLE     dObj,
                                        DRV_SPI_INIT           * spiInit )

  Summary:
    Sets up the hardware from the initialization structure

  Description:
    This routine sets up the hardware from the initialization structure.

  Remarks:
    None.
*/

static void _DRV_SPI_SetupHardware ( const SPI_MODULE_ID plibId,
                                     DRV_SPI_OBJ *dObj,
                                     DRV_SPI_INIT * spiInit )
{
    /* Initialize the Interrupt Sources */
    _DRV_SPI_STATIC_INT_SRC( dObj->txInterruptSource =
    	_DRV_SPI_INT_SRC_GET( spiInit->txInterruptSource ) );
    _DRV_SPI_STATIC_INT_SRC( dObj->rxInterruptSource =
    	_DRV_SPI_GET_INT_SRC_RX( spiInit->rxInterruptSource ) );
    _DRV_SPI_STATIC_INT_SRC( dObj->errInterruptSource =
    	_DRV_SPI_GET_INT_SRC_ERROR( spiInit->errInterruptSource ) );

    // 1. disable all interrupts
    PLIB_SPI_ErrorInterruptDisable ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ,
                            _DRV_SPI_STATIC_INT_SRC( dObj->errInterruptSource ) );
    PLIB_INT_SourceDisable ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ,
                            _DRV_SPI_STATIC_INT_SRC( dObj->txInterruptSource ) );
    PLIB_INT_SourceDisable ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ,
                            _DRV_SPI_STATIC_INT_SRC( dObj->rxInterruptSource ) );

    // 2. turn it OFF
    PLIB_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );

    // 3. Clear rx buf
    PLIB_SPI_BufferClear( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );

    // 4. Clear outstanding interrupts
    PLIB_INT_SourceFlagClear( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        _DRV_SPI_STATIC_INT_SRC( dObj->errInterruptSource ) );
    PLIB_INT_SourceFlagClear( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        _DRV_SPI_STATIC_INT_SRC( dObj->txInterruptSource ) );
    PLIB_INT_SourceFlagClear( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        _DRV_SPI_STATIC_INT_SRC( dObj->rxInterruptSource ) );

    // 5. Clear receiver overlow
    PLIB_SPI_ReceiverOverflowClear( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );

    // 6. Select slave or master mode
    if( _DRV_SPI_USAGE_MODE_GET ( spiInit->spiMode ) == DRV_SPI_MODE_MASTER ) // DRV_SPI_MODE_SLAVE )
    {
        PLIB_SPI_SlaveSelectEnable ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
    }
    else
    {
	PLIB_SPI_SlaveSelectDisable ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ) );
    }


    /* Power state initialization */
    if( _DRV_SPI_POWER_STATE_GET( spiInit->moduleInit.value ) == SYS_MODULE_POWER_IDLE_STOP )
    {
        PLIB_SPI_StopInIdleEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
    }
    else if( ( _DRV_SPI_POWER_STATE_GET( spiInit->moduleInit.value ) == SYS_MODULE_POWER_IDLE_RUN ) ||
                ( _DRV_SPI_POWER_STATE_GET( spiInit->moduleInit.value ) == SYS_MODULE_POWER_RUN_FULL ) )
    {
        PLIB_SPI_StopInIdleDisable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
    }
    else
    {
        if( _DRV_SPI_POWER_STATE_GET( spiInit->moduleInit.sys.powerState ) == SYS_MODULE_POWER_IDLE_STOP )
        {
            PLIB_SPI_StopInIdleEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }
    }
    /* Clock Mode Initialization */
    if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 0 - Idle State Low & Sampling on Rising Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
            SPI_CLOCK_POLARITY_IDLE_LOW );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 1 - Idle State Low & Sampling on Falling Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
            SPI_CLOCK_POLARITY_IDLE_LOW );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
            SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 2 - Idle State High & Sampling on Falling Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ),
            SPI_CLOCK_POLARITY_IDLE_HIGH );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ),
            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
    }
    else // ( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 3 - Idle State High & Sampling on Rising Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ),
                        SPI_CLOCK_POLARITY_IDLE_HIGH );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
    }
    /* Update the clock mode */
    dObj->clockMode = _DRV_SPI_CLOCK_OPERATION_MODE_GET ( spiInit->clockMode );

    /* Input Sample Phase */
    if( PLIB_SPI_ExistsInputSamplePhase ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ) ) )
    {
        PLIB_SPI_InputSamplePhaseSelect ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ),
                _DRV_SPI_INPUT_SAMPLE_PHASE_GET( spiInit->inputSamplePhase ) );
        dObj->inputSamplePhase = _DRV_SPI_INPUT_SAMPLE_PHASE_GET ( spiInit->inputSamplePhase );
    }

    /* Usage Mode Master/Slave */
    if( _DRV_SPI_USAGE_MODE_GET( spiInit->spiMode ) == DRV_SPI_MODE_MASTER )
    {
        /* Master Enable */
        PLIB_SPI_MasterEnable ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ) );
        if (_DRV_SPI_DUPLEX_MODE_GET( spiInit->dataDirection) == HALF_DUPLEX)
            PLIB_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET(plibId), SPI_PIN_DATA_IN);
    }
    else
    {
        /* Slave Enable */
        PLIB_SPI_SlaveEnable ( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        if (_DRV_SPI_DUPLEX_MODE_GET( spiInit->dataDirection) == HALF_DUPLEX)
            PLIB_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET(plibId), SPI_PIN_DATA_OUT);
    }
    dObj->spiMode = _DRV_SPI_USAGE_MODE_GET ( spiInit->spiMode );

    /* Communication Width Selection */
    PLIB_SPI_CommunicationWidthSelect ( _DRV_SPI_PERIPHERAL_ID_GET ( plibId ),
                _DRV_SPI_COMMUNICATION_WIDTH_GET( spiInit->commWidth ) );
    dObj->commWidth = _DRV_SPI_COMMUNICATION_WIDTH_GET( spiInit->commWidth );

    /* Baudrate selection */
    // Below changed for PIC32 driver unit testing
    PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL ),
                _DRV_SPI_BAUD_RATE_VALUE_GET( spiInit->baudRate ) );

    /* Protocol Selection */
    if( _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType ) == DRV_SPI_PROTOCOL_TYPE_FRAMED )
    {
        /* Frame Sync Pulse Direction */
        PLIB_SPI_FrameSyncPulseDirectionSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
            DRV_SPI_FRAME_SYNC_PULSE_DIRECTION );

        /* Frame Sync Pulse Polarity */
        PLIB_SPI_FrameSyncPulsePolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                    DRV_SPI_FRAME_SYNC_PULSE_POLARITY );

        /* Frame Sync Pulse Edge */
        PLIB_SPI_FrameSyncPulseEdgeSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                    DRV_SPI_FRAME_SYNC_PULSE_EDGE );

        /* Check if the framed communication is supported by the device */
        PLIB_SPI_FramedCommunicationEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );

        /* ToDo: Other Frame based parameters update, if any */
    }
    else if( _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType ) == DRV_SPI_PROTOCOL_TYPE_AUDIO )
    {
        /* Check if the audio protocol is supported by the device */
        PLIB_SPI_AudioProtocolEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );

        /* ToDo: Other Audio based parameters update */
    }

    dObj->spiProtocolType = _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType );

    /* Buffer type selection */
    if( PLIB_SPI_ExistsFIFOControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( _DRV_SPI_BUFFER_USAGE_TYPE_GET( spiInit->bufferType ) == DRV_SPI_BUFFER_TYPE_ENHANCED )
        {
            /* Enhanced Buffer Mode Enable */
            PLIB_SPI_FIFOEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }
        else
        {
            /* Standard Buffer Mode Enable */
            PLIB_SPI_FIFODisable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }

        dObj->bufferType = _DRV_SPI_BUFFER_USAGE_TYPE_GET( spiInit->bufferType );
    }

    /* Buffer interrupt mode selection */
    if( _DRV_SPI_BUFFER_USAGE_TYPE_GET( spiInit->bufferType ) == DRV_SPI_BUFFER_TYPE_ENHANCED )
    {
        /* Update the transmit buffer interrupt mode */
        _DRV_SPI_TxFIFOInterruptModeSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        _DRV_SPI_TX_FIFO_INTERRUPT_MODE_GET( spiInit->txInterruptMode ) );
        /* Update the receive buffer interrupt mode */
        _DRV_SPI_RxFIFOInterruptModeSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                        _DRV_SPI_RX_FIFO_INTERRUPT_MODE_GET( spiInit->rxInterruptMode ) );
    }
} /* _DRV_SPI_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_SPI_Initialize ( const SYS_MODULE_INDEX  index,
                                       const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the given instance of the SPI module

  Description:
    This routine initializes hardware for the instance of the SPI module,
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
__attribute__((section("driver")))
SYS_MODULE_OBJ DRV_SPI_Initialize ( const SYS_MODULE_INDEX   drvIndex,
                                   const SYS_MODULE_INIT    * const init )
{
    DRV_SPI_INIT * spiInit;
    SPI_MODULE_ID spiId;

	  /* Validate the driver index */
    if ( drvIndex >= DRV_SPI_INDEX_COUNT )
    {
        return SYS_MODULE_OBJ_INVALID;
    }

    // client for this driver should not be in use
    DRV_SPI_CLIENT_OBJ  *clientObj      =
                        ( DRV_SPI_CLIENT_OBJ* ) _DRV_SPI_CLIENT_OBJ_GET(drvIndex);
    clientObj->inUse = false;

    DRV_SPI_OBJ *dObj = _DRV_SPI_INSTANCE_GET ( drvIndex );

    /* Assign to the local pointer the init data passed */
    spiInit = ( DRV_SPI_INIT * ) init;

    /* Object is valid, set it in use */
    dObj->inUse = true;

    /* Save the index of the driver. Important to know this
    as we are using reference based accessing */
    dObj->drvIndex = drvIndex;

    /* Update the SPI Module Index */
    dObj->spiId = _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId );

    /* Setup the Hardware */
    _DRV_SPI_SetupHardware ( _DRV_SPI_PERIPHERAL_ID_GET( dObj->spiId ),
                            dObj,
                            spiInit );

    /* Reset the number of clients */
    dObj->numClients = 0;

    /* Speed up accessing, take it to a local variable */
    spiId = dObj->spiId;

    /* Reset the locally used variables */
    dObj->lastClientHandle      = DRV_SPI_CLIENTS_NUMBER+1;

    /* Slave Select Handling */
    if( _DRV_SPI_USAGE_MODE_GET(spiInit->spiMode) == DRV_SPI_MODE_SLAVE )
    {
        PLIB_SPI_BufferClear( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) );
    }

    /* Clear the SPI Overflow Flag */

    PLIB_SPI_ReceiverOverflowClear ( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) );

    /* Interrupt flag cleared on the safer side */
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( dObj->txInterruptSource ) );
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( dObj->rxInterruptSource ) ) ;
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( dObj->errInterruptSource ) ) ;

    /* Set the current driver state */
    dObj->status = SYS_STATUS_READY;

    /* Enable the SPI module */
    PLIB_SPI_Enable( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) ;

    /* Return the driver handle */
    return( (SYS_MODULE_OBJ) dObj );
} /* DRV_SPI_Initialize */


//******************************************************************************
/* Function:
    void DRV_SPI_Deinitialize ( SYS_MODULE_OBJ object )

  Summary:
    De-initializes the specific module instance of the SPI module

  Description:
    De-initializes the specific module instance disabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None
*/
__attribute__((section("driver")))
void DRV_SPI_Deinitialize ( SYS_MODULE_OBJ object )
{
    DRV_SPI_OBJ *dObj = (DRV_SPI_OBJ*) object;
    SPI_MODULE_ID spiId = dObj->spiId;
	size_t iClient;
    /* Interrupt De-Registration */
    _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET( dObj->txInterruptSource ) );
    _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET( dObj->rxInterruptSource ) );
    _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET( dObj->errInterruptSource ) );

    /* Stop/Disable the device if needed */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
    {
        PLIB_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) );
    }

	for ( iClient = 0; iClient < DRV_SPI_CLIENTS_NUMBER ; iClient++ )
    {
		gDrvSPIClientObj[iClient].inUse = false;
	}

	dObj->numClients = 0;
	dObj->isExclusive = false;
	/* Clear all the pending requests */
	dObj->queueHead = NULL;
    /* Set the Device Status */
    dObj->status = SYS_STATUS_UNINITIALIZED;

    /* Remove the driver usage */
    dObj->inUse = false;
} /* DRV_SPI_Deinitialize */


//******************************************************************************
/* Function:
    SYS_STATUS DRV_SPI_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the SPI module

  Description:
    This routine Provides the current status of the hardware instance of the
    SPI module.

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
__attribute__((section("driver")))
SYS_STATUS DRV_SPI_Status ( SYS_MODULE_OBJ object )
{
    DRV_SPI_OBJ *dObj = (DRV_SPI_OBJ*) object;

    /* Return the status associated with the driver handle */
    return ( dObj->status );
} /* DRV_SPI_Status */


//******************************************************************************
/* Function:
    void DRV_SPI_Tasks ( SYS_MODULE_OBJ object )

  Summary:
    Used to maintain the driver's state machine and implement its ISR

  Description:
    This routine is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None.
*/


// debug
uint32_t buf[4];


__attribute__((section("driver")))
void DRV_SPI_Tasks ( SYS_MODULE_OBJ object )
{

    DRV_SPI_OBJ             *dObj           = (DRV_SPI_OBJ*)object;
    DRV_SPI_BUFFER_OBJECT   *lBufferObj     = dObj->currentBufObj;
    SPI_DATA_TYPE           dummy           = (SPI_DATA_TYPE)0xaaaaaaaa;
    SPI_MODULE_ID           spiId           = dObj->spiId;
    DRV_SPI_CLIENT_OBJ      *lClientObj;

    static int i = 0, j = 0, k = 0, m = 0, p = 0, r = 0, S = 0;

    int q;
    for(q = 0; q < 4; q++)
        buf[q] = 0x00000000L;

    switch ( dObj->task )
    {
        case DRV_SPI_TASK_PROCESS_QUEUE:
            i++;
            if (  dObj->queueHead != NULL ) //&& (( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) ) ||
                    //(PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ))))
            {
                /* Pop the first element from the queue */
                lBufferObj   = dObj->queueHead;
                dObj->currentBufObj = lBufferObj;

                /* Update the queue head */
                dObj->queueHead = lBufferObj->next;

                lClientObj = (DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle;

                /* We need not do this all the time but when the request from a
                 new client  */
                _DRV_SPI_CLIENT_SWITCH_CLIENT(dObj, lBufferObj);

                /* Update the task state as per the operation */
                if ( lBufferObj->operation == DRV_SPI_OP_READ )
                {
                    dObj->task = DRV_SPI_TASK_PROCESS_READ_ONLY;
                    SYS_ASSERT((lBufferObj->rxBuffer != NULL), "tx buf can't be null");
//                    j = 0;
//                    while ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
//                    {
//                        buf[j] = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
//                        if (++j >= 4)
//                            break;
//                    }
//                    i = 0;
                }
                else if ( lBufferObj->operation == DRV_SPI_OP_WRITE )
                {
                    dObj->task = DRV_SPI_TASK_PROCESS_WRITE_ONLY;
                    SYS_ASSERT((lBufferObj->txBuffer[0] != 0), "Buffer has zeroes in first word");
                }
            }
            else // spurious interrupt
            {
                while ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
                {
                    PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
                }
                while ( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
                {
                    PLIB_SPI_BufferWrite ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ), 0x00000000 );
                }
                _DRV_SPI_InterruptSourceClear ( _DRV_SPI_INT_SRC_GET ( dObj->rxInterruptSource ) ) ;
                _DRV_SPI_InterruptSourceClear ( _DRV_SPI_INT_SRC_GET ( dObj->txInterruptSource ) ) ;
            }
            break;
        case DRV_SPI_TASK_PROCESS_READ_ONLY:
            /* If RX buffer has some existing data to be read, read (receive them from FIFO) */
            if ( lBufferObj->transferSize )
            {
                if ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
                {
                    *lBufferObj->rxBuffer++ = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
                    lBufferObj->transferSize--;
                    S++;

                    /* Handle the overflow */
                    if ( lBufferObj->transferSize > 1 )
                    {
                            PLIB_SPI_BufferWrite( _DRV_SPI_PERIPHERAL_ID_GET( spiId ), dummy ) ;
                    }
                    else if ( lBufferObj->transferSize <= 0 ) /* If all transmission is complete */
                    {
                        /* Hold the buffer till the completion of the operation */
                        //lBufferObj->inUse = false;
                        dObj->task = DRV_SPI_TASK_PROCESS_QUEUE;

                        _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET ( dObj->rxInterruptSource ) ) ;

                        _DRV_SPI_CLIENT_OBJ(lBufferObj, status) |=
                                DRV_SPI_BUFFER_EVENT_COMPLETE;

                        /* Have a check here because DRV_SPI_ClientSetup function call is optional */
                        if ( _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle), callback) != NULL )
                        {
                            /* Give an indication to the higher layer upon successful transmission */
                            _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle),
                                callback)( DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)lBufferObj, 0x00 );
                        }
                    }
                }
                else
                {
                    /* Do not block in any case */
                    break;
                }
            }
            break;
        case DRV_SPI_TASK_PROCESS_WRITE_ONLY:
            k++;

            /* Loop till the transmit size, do not block though */
            if ( lBufferObj->transferSize )
            {
                m++;
                // pull the chip-select line low
                lClientObj = (DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle;
                if ( true != _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectLogicLevel) )
                {
                    _DRV_SPI_CHIP_SELECT_CLEAR(_DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectPort),
                        _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectBitPos));
                }
                else
                {
                    _DRV_SPI_CHIP_SELECT_SET(_DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectPort),
                        _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectBitPos));
                }

                while ( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
                {
                    PLIB_SPI_BufferWrite ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ), *lBufferObj->txBuffer++ );
                    lBufferObj->transferSize--;
                }
                if ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
                {
                    dummy = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
                }

                // when this buffer object is done, release it
                if ( lBufferObj->transferSize <= 0 )
                {
                    // is this the last buffer object in the queue? if so, stop transmission
                    if (dObj->queueHead == NULL)
                    {
                        // Release chip select signal
                        while (PLIB_SPI_IsBusy( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ))
                            r++;
                        if ( true != _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectLogicLevel) )
                        {
                            _DRV_SPI_CHIP_SELECT_SET(_DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectPort),
                                _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectBitPos));
                        }
                        else
                        {
                            _DRV_SPI_CHIP_SELECT_CLEAR(_DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectPort),
                                _DRV_SPI_CLIENT_OBJ(lClientObj, chipSelectBitPos));
                        }

                        _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET ( dObj->txInterruptSource ) ) ;
                    }

                    /* Hold the buffer till the completion of the operation */
                    lBufferObj->inUse = false;

                    dObj->task = DRV_SPI_TASK_PROCESS_QUEUE;

                    _DRV_SPI_CLIENT_OBJ(lBufferObj, status) |=
                        DRV_SPI_BUFFER_EVENT_COMPLETE;

                   /* Have a check here because DRV_SPI_ClientSetup function call is optional */
                    if ( _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle), callback) != NULL )
                    {
                        /* Give an indication to the higher layer upon successful transmission */
                        _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle), callback)
                                ( DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE)lBufferObj, 0x00 );
                    }
                }
             }
            break;
        case DRV_SPI_TASK_PROCESS_WRITE_READ:
            p++;
            if( lBufferObj->transferSize )
            {
                if ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
                {
                    *lBufferObj->rxBuffer++ = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
                    lBufferObj->transferSize--;

                    if ( lBufferObj->transferSize > 1 )
                    {
                        PLIB_SPI_BufferWrite ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ), *lBufferObj->txBuffer++ ) ;
                    }
                    else
                    {
                        dObj->task = DRV_SPI_TASK_PROCESS_QUEUE;
                        /* Hold the buffer till the completion of the operation */
                        lBufferObj->inUse = false;
                        _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET ( dObj->txInterruptSource ) ) ;

                        _DRV_SPI_CLIENT_OBJ(lBufferObj, status) |=
                            DRV_SPI_BUFFER_EVENT_COMPLETE;

                        /* Have a check because DRV_SPI_ClientSetup function call is optional */
                        if ( _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle), callback) != NULL )
                        {
                            /* Give an indication to the higher layer upon successful transmission */
                            _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ *)lBufferObj->clientHandle), callback)
                                    ( DRV_SPI_BUFFER_EVENT_COMPLETE, (DRV_SPI_BUFFER_HANDLE) lBufferObj, 0x00 );
                        }
                    }
                }
                else
                {
                    /* Do not block in any case */
                    break;
                }
            }
            break;
        default:
            break;

        }

    /* This state is encountered when an error interrupt has occurred.
       or an error has occurred during read */
    if ( true == _DRV_SPI_InterruptSourceStatusGet ( _DRV_SPI_GET_INT_SRC_ERROR ( dObj->errInterruptSource ) ) )
    {
        /* Check for the overflow error */
        if ( PLIB_SPI_ReceiverHasOverflowed ( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
        {
            if ( PLIB_SPI_ExistsReceiverOverflow ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
            {
                PLIB_SPI_ReceiverOverflowClear ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId) );
            }

            /* Update the transfer status */
            dObj->transferStatus |= DRV_SPI_BUFFER_EVENT_ERROR;
        }

        _DRV_SPI_InterruptSourceClear ( _DRV_SPI_GET_INT_SRC_ERROR( dObj->errInterruptSource ) );
    }
}


//******************************************************************************
/* Function:
    DRV_HANDLE DRV_SPI_Open ( const SYS_MODULE_INDEX    index,
                             const DRV_IO_INTENT       intent )

  Summary:
    Opens the specific module instance and returns a handle

  Description:
    This routine opens a driver for use by any client module and provides a
    handle that must be provided to any of the other driver operations to
    identify the caller and the instance of the driver/hardware module.

  Parameters:
    index           - Identifier for the instance to be initialized
    ioIntent        - Possible values from the enumeration DRV_IO_INTENT

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance)
    If an error occurs, the return value is DRV_HANDLE_INVALID
*/
__attribute__((section("driver")))
DRV_HANDLE DRV_SPI_Open ( const SYS_MODULE_INDEX   drvIndex,
                         const DRV_IO_INTENT      ioIntent )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SPI_CLIENT_OBJ  *clientObj      =
                        ( DRV_SPI_CLIENT_OBJ* ) _DRV_SPI_CLIENT_OBJ_GET(drvIndex);
    DRV_SPI_OBJ         *dObj;
    size_t              iClient;

    /* Validate the driver index */
    if( drvIndex >= DRV_SPI_INDEX_COUNT )
    {
        return DRV_HANDLE_INVALID;
    }
    /* Setup client operations */
    /* Find available slot in array of client objects */
    for ( iClient = 0; iClient < DRV_SPI_CLIENTS_NUMBER ; iClient++ )
    {
        if ( !clientObj->inUse )
        {
            /* Increment the client in case of Multi client support, otherwise remove
            the below statement */
            dObj = _DRV_SPI_INSTANCE_GET(drvIndex);

            clientObj->inUse  = true;
            clientObj->driverObject = dObj;
            /* Check for exclusive access */
            if ( ( dObj->isExclusive == true ) || ( dObj->inUse != true ) ||
                (( dObj->numClients > 0 ) && DRV_IO_ISEXCLUSIVE( ioIntent )) )
            {
                /* Set that the hardware instance is opened in exclusive mode */
                return DRV_HANDLE_INVALID;
            }

            /* Check if max number of clients open */
            if( dObj->numClients >= DRV_SPI_CLIENTS_NUMBER )
            {
                /* Set that the hardware instance is opened with max clients */
                return DRV_HANDLE_INVALID;
            }

            dObj->numClients++;

            /* Update that, the client is opened in exclusive access mode */
            if( DRV_IO_ISEXCLUSIVE( ioIntent ) )
            {
                dObj->isExclusive = true;
            }
            /* To Do: OSAL - Unlock Mutex */

            /* Return the client object ? */
            return ( DRV_HANDLE ) clientObj;
        }
        clientObj++;
    }
    /* TODO OSAL - Unlock Mutex */
    return  DRV_HANDLE_INVALID ;
} /* DRV_SPI_Open */


//******************************************************************************
/* Function:
    void DRV_SPI_Close ( DRV_HANDLE handle )

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
__attribute__((section("driver")))
void DRV_SPI_Close ( DRV_HANDLE handle )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SPI_CLIENT_OBJ *clientObj = (DRV_SPI_CLIENT_OBJ*)handle;

    /* To Do: OSAL - lock Mutex */

    /* Free the Client Instance */
    clientObj->inUse = false ;
    /* To Do: OSAL - unlock Mutex */
} /* DRV_SPI_Close */


// *****************************************************************************
/* Function:
    void DRV_SPI_ClientSetup ( DRV_HANDLE handle,
                                 const DRV_SPI_CLIENT_SETUP * const config )

  Summary:
    Sets up the device communication parameters

  Description:
    This function sets up the device communication parameters

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    config       - Communication parameters indetified by DRV_SPI_COMM_CONFIG

  Returns:
    None
*/
__attribute__((section("driver")))
void DRV_SPI_ClientSetup ( DRV_HANDLE handle,
                                 const DRV_SPI_CLIENT_SETUP * const config )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SPI_CLIENT_OBJ *clientObj = (DRV_SPI_CLIENT_OBJ*) handle;

    /* Get the Client object from the handle passed */
    /* Get the driver object from the client */
    int drv = clientObj->driverObject->drvIndex;
    //_DRV_SPI_SAVE_LAST_CLIENT(drv);
     gDrvSPIObj[drv].lastClientHandle = DRV_SPI_CLIENTS_NUMBER + 1 ;

    _DRV_SPI_CLIENT_OBJ(clientObj,baudRate)             = config->baudRate;
    _DRV_SPI_CLIENT_OBJ(clientObj,inputSamplePhase)     = config->inputSamplePhase;
    _DRV_SPI_CLIENT_OBJ(clientObj,clockMode)            = config->clockMode;
    _DRV_SPI_CLIENT_OBJ(clientObj,chipSelectLogicLevel) = config->chipSelectLogicLevel;
    _DRV_SPI_CLIENT_OBJ(clientObj,chipSelectPort)       = config->chipSelectPort;
    _DRV_SPI_CLIENT_OBJ(clientObj,chipSelectBitPos)     = config->chipSelectBitPos;
    _DRV_SPI_CLIENT_OBJ(clientObj,callback)             = NULL;

} /* DRV_SPI_ClientSetup */


// *****************************************************************************
/* Function:
    static void _DRV_SPI_ClientHardwareSetup ( DRV_HANDLE handle )

  Summary:
    Sets up the device communication parameters

  Description:
    This function sets up the device communication parameters

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    config       - Communication parameters identified by DRV_SPI_COMM_CONFIG

  Returns:
    None
*/
__attribute__((section("driver")))
void _DRV_SPI_ClientHardwareSetup ( DRV_HANDLE handle )
{
    /* Multi client variables are removed from single client builds. */
    DRV_SPI_CLIENT_OBJ  *clientObj  = (DRV_SPI_CLIENT_OBJ *) handle;
    /* Get the driver object from the client */
    DRV_SPI_OBJ         *dObj       = clientObj->driverObject;
    SPI_MODULE_ID       spiId       = dObj->spiId;

    /* Stop/Disable the device */
    PLIB_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) );

    /* Input Sample Phase */
    PLIB_SPI_InputSamplePhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
            _DRV_SPI_CLIENT_OBJ(clientObj, inputSamplePhase) );

    /* Clock Mode Intialization */
    if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE == _DRV_SPI_CLIENT_OBJ(clientObj, clockMode) )
    {
        /* Mode 0 - Idle State Low & Sampling on Rising Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                SPI_CLOCK_POLARITY_IDLE_LOW );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );

    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL == _DRV_SPI_CLIENT_OBJ(clientObj, clockMode) )
    {
        /* Mode 1 - Idle State Low & Sampling on Falling Edge */
        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                SPI_CLOCK_POLARITY_IDLE_LOW );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
        SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );

    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL == _DRV_SPI_CLIENT_OBJ(clientObj, clockMode) )
    {
        /* Mode 2 - Idle State High & Sampling on Falling Edge */
        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                    SPI_CLOCK_POLARITY_IDLE_HIGH );
        }

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
    }
    else // ( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE == config->clockMode )
    {
        /* Mode 3 - Idle State High & Sampling on Rising Edge */

        /* Clock Polarity */
        PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                SPI_CLOCK_POLARITY_IDLE_HIGH );

        /* Output Data Phase */
        PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiId ),
                SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
    }
    /* Baudrate selection */

    // Below for PIC32
    PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( spiId ), SYS_CLK_ClockFrequencyGet(CLK_PERIPHERAL),
                _DRV_SPI_CLIENT_OBJ(clientObj, baudRate) );

     gDrvSPIObj[_DRV_SPI_PERIPHERAL_ID_GET( spiId )].lastClientHandle = handle ;

    /* Restart the device */
    PLIB_SPI_Enable( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) );
} /* _DRV_SPI_ClientHardwareSetup */


//******************************************************************************
/* Function:
    DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddRead ( DRV_HANDLE handle, void *rxBuffer,
                                    size_t size )

  Summary:
    Adds a buffer to queue with a read request. Driver will process this
    request in the task routine.

  Description:
    This routine adds a buffer to queue with a read request. Driver will process
    this request in the task routine.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

	rxBuffer	 - Buffer to which the data to be filled.

	size		 - Number of bytes to be read.

  Returns:
    DRV_SPI_BUFFER_HANDLE using which application can track the current status of
    the buffer.
*/

__attribute__((section("driver")))
DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddRead ( DRV_HANDLE handle, void *rxBuffer,
                                    size_t size )
{
    DRV_SPI_BUFFER_OBJECT   *spiDataObj;
    DRV_SPI_OBJ             *dObj = ((DRV_SPI_CLIENT_OBJ *) handle)->driverObject;

    /* Get a slot in the queue */
    spiDataObj = _DRV_SPI_QueueSlotGet ( dObj );

    if ( spiDataObj != NULL )
    {
        /* Fill the data directly to the queue. Set the inUse flag only at the end */
        spiDataObj->clientHandle    = handle;
        spiDataObj->operation       = DRV_SPI_OP_READ;
        spiDataObj->txBuffer        = NULL;
        spiDataObj->rxBuffer        = rxBuffer;
        spiDataObj->transferSize    = size / sizeof(SPI_DATA_TYPE);
        spiDataObj->next            = NULL;

        if ( dObj->queueHead == NULL )
        {
            dObj->queueHead = spiDataObj;
        }
        else
        {
            dObj->taskLObj->next = spiDataObj;
        }
        dObj->taskLObj = spiDataObj;

        while ( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET( dObj->spiId ) ) )
        {
            SPI_DATA_TYPE dummy = (SPI_DATA_TYPE)0xaaaaaaaa; // should work whatever SPI_DATA_TYPE is
            PLIB_SPI_BufferWrite ( _DRV_SPI_PERIPHERAL_ID_GET ( dObj->spiId ), dummy );
        }

        while ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( dObj->spiId ) ) )
        {
            PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( dObj->spiId ) ); // discard
        }

        _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET ( dObj->rxInterruptSource ) ) ;

        _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( dObj->rxInterruptSource ) ) ;
        //_DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( dObj->txInterruptSource ) ) ;

        return (DRV_SPI_BUFFER_HANDLE)spiDataObj;
    }
    return (DRV_SPI_BUFFER_HANDLE)NULL;
}

__attribute__((section("driver")))
void DRV_SPI_FreeBuffer( DRV_HANDLE handle, DRV_SPI_BUFFER_HANDLE buf )
{
    ((DRV_SPI_BUFFER_OBJECT   *)buf)->inUse = false;
}


//******************************************************************************
/* Function:
    DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddWrite ( DRV_HANDLE handle, void *txBuffer,
                                    size_t size )

  Summary:
    Adds a buffer to queue with a write request. Driver will process this
    request in the task routine.

  Description:
    This routine adds a buffer to queue with a read request. Driver will process
    this request in the task routine.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

	rxBuffer	 - Buffer to which the data to be filled.

	size		 - Number of bytes to b read.

  Returns:
    DRV_SPI_BUFFER_HANDLE using which application can track the current status of
    the buffer.
*/
__attribute__((section("driver")))
DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddWrite ( DRV_HANDLE handle, void *txBuffer,
                                    size_t size )
{
    DRV_SPI_BUFFER_OBJECT *spiDataObj;
    DRV_SPI_OBJ *dObj = ((DRV_SPI_CLIENT_OBJ *) handle)->driverObject;

    /* Get a slot in the queue */
    spiDataObj = _DRV_SPI_QueueSlotGet (dObj);

    if ( spiDataObj != NULL )
    {
        /* Fill the data directly to the queue. Set the inUse flag only at the end */
        spiDataObj->clientHandle    = handle;
        spiDataObj->operation       = DRV_SPI_OP_WRITE;
        spiDataObj->txBuffer        = txBuffer;
        spiDataObj->rxBuffer        = NULL;
        spiDataObj->transferSize    = size / sizeof(SPI_DATA_TYPE);
        SYS_ASSERT((spiDataObj->transferSize == 16), "wrong byte count when transmitting spi"); // 64 / 4 = 16
        spiDataObj->next            = NULL;

        if ( dObj->queueHead == NULL )
        {
            dObj->queueHead = spiDataObj;
        }
        else
        {
            dObj->taskLObj->next = spiDataObj;
        }
        dObj->taskLObj = spiDataObj;

        _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( dObj->txInterruptSource ) ) ;

        return (DRV_SPI_BUFFER_HANDLE) spiDataObj;
    }
    return (DRV_SPI_BUFFER_HANDLE)NULL;
}


//******************************************************************************
/* Function:
    DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddWriteRead ( DRV_HANDLE handle, void *txBuffer,
                                            void *rxBuffer, uint32_t size )

  Summary:
    Adds a buffer to queue with a read request. Driver will process this
    request in the task routine.

  Description:
    This routine adds a buffer to queue with a read request. Driver will process
    this request in the task routine.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

	txBuffer 	 - Buffer which has the data.

	rxBuffer	 - Buffer to which the data to be filled.

	size		 - Number of bytes to b read.

  Returns:
    DRV_SPI_BUFFER_HANDLE using which application can track the current status of
    the buffer.
*/
__attribute__((section("driver")))
DRV_SPI_BUFFER_HANDLE DRV_SPI_BufferAddWriteRead ( DRV_HANDLE handle, void *txBuffer,
                                            void *rxBuffer, size_t size )
{
    DRV_SPI_BUFFER_OBJECT   *spiDataObj;
    DRV_SPI_OBJ             *dObj = ((DRV_SPI_CLIENT_OBJ *) handle)->driverObject;

    /* Get a slot in the queue */
    spiDataObj = _DRV_SPI_QueueSlotGet ( dObj );

    if ( spiDataObj != NULL )
    {
        /* Fill the data directly to the queue. Set the inUse flag only at the end */
        spiDataObj->clientHandle   	= handle;
        spiDataObj->operation           = DRV_SPI_OP_WRITE;
        spiDataObj->txBuffer            = txBuffer;
        spiDataObj->rxBuffer            = rxBuffer;
        spiDataObj->transferSize        = size / sizeof(SPI_DATA_TYPE);
        spiDataObj->next                = NULL;

        if ( dObj->queueHead == NULL )
        {
            dObj->queueHead = spiDataObj;
        }
        else
        {
            dObj->taskLObj->next = spiDataObj;
        }
        dObj->taskLObj = spiDataObj;

        _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( dObj->txInterruptSource ) ) ;
        _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( dObj->rxInterruptSource ) ) ;

        return (DRV_SPI_BUFFER_HANDLE) spiDataObj;
    }
    return (DRV_SPI_BUFFER_HANDLE)NULL;
}


// *****************************************************************************
/* Function:
    DRV_SPI_BUFFER_EVENT DRV_SPI_BufferStatus ( DRV_SPI_BUFFER_HANDLE bufferHandle )

  Summary:
    Returns the transmitter and receiver transfer status

  Description:
    This returns the transmitter and receiver transfer status.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_SPI_TRANSFER_STATUS value describing the current status of the
    transfer.
*/
__attribute__((section("driver")))
DRV_SPI_BUFFER_EVENT DRV_SPI_BufferStatus ( DRV_SPI_BUFFER_HANDLE bufferHandle )
{
    /* return the transfer status. This doesn't have any protection */
    return _DRV_SPI_DATA_OBJ(bufferHandle, status);

} /* DRV_SPI_TransferStatus */

__attribute__((section("driver")))
void DRV_SPI_BufferEventHandlerSet (const DRV_HANDLE handle,
                    const DRV_SPI_BUFFER_EVENT_HANDLER eventHandler,
                    const uintptr_t context )
{
    //DRV_SPI_CLIENT_OBJ *clientObj = (DRV_SPI_CLIENT_OBJ*)handle;
    _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ*)handle), callback) = eventHandler;
}

// When Asics timeout, we need to abort the current read buffer
__attribute__((section("driver")))
void DRV_SPI_AbortCurrentReadAndResetBuffers( const DRV_HANDLE handle)
{
    int index;
    DRV_SPI_OBJ* dObj = _DRV_SPI_CLIENT_OBJ(((DRV_SPI_CLIENT_OBJ*)handle), driverObject);
    DRV_SPI_BUFFER_OBJECT *lQueueObj;
    SYS_MODULE_INDEX drvIndex = dObj->drvIndex;

    _DRV_SPI_InterruptSourceDisable ( _DRV_SPI_INT_SRC_GET ( dObj->rxInterruptSource ) ) ;

    for ( index=0; index<DRV_SPI_BUFFER_OBJ_SIZE;index++ )
    {
        lQueueObj = &gDrvSPIBufferObj [ drvIndex ][ index ];

        lQueueObj->inUse = false;
        lQueueObj->next = NULL;
        lQueueObj->rxBuffer = NULL;
        lQueueObj->txBuffer = NULL;
        lQueueObj->transferSize = 0;
        lQueueObj->status = DRV_SPI_BUFFER_EVENT_PENDING;
    }

    dObj->queueHead = NULL;
    dObj->taskLObj = NULL;
}

// *****************************************************************************
/* Function:
    size_t DRV_SPI_Read ( DRV_HANDLE handle, void* buffer, size_t noOfBytes )

  Summary:
    Directly reads specified bytes from the SPI module, bypassing the queue.

  Description:
    This function reads specified bytes from the SPI module.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

	buffer		 - Buffer to which the read data should be written.

	noOfBytes	 - Number of bytes to be read.
  Returns:
    Number of bytes read.
*/
__attribute__((section("driver")))
size_t DRV_SPI_Read ( DRV_HANDLE handle, void* buffer, size_t noOfBytes )
{
    register char       *tempBuffer = buffer;
    DRV_SPI_OBJ         *dObj       = ((DRV_SPI_CLIENT_OBJ *) handle)->driverObject;
    SPI_MODULE_ID       spiId       = dObj->spiId;

    /* If there is something in the queue, return. Come back after some time. */
    if ( dObj->queueHead != NULL  )
    {
        return 0;
    }

    /* Block until the operation is complete */
    while ( noOfBytes )
    {
        /* Wait until the transmit buffer is free */
        //while ( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
        //{
        //    PLIB_SPI_BufferWrite( _DRV_SPI_PERIPHERAL_ID_GET( spiId ), 0xFF ) ;
        //}
        /* Wait until the data is received back */
        while ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
        {
            *tempBuffer++ = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
            noOfBytes--;
        }
    }
    /*TODO*/
    return 0;
}


// *****************************************************************************
/* Function:
    size_t DRV_SPI_Write ( DRV_HANDLE handle, void* buffer, size_t noOfBytes )

  Summary:
    Directly writes specified bytes from the SPI module, bypassing the queue.

  Description:
    This function writes specified bytes from the SPI module.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

	buffer		 - Buffer to which holds the data.

	noOfBytes	 - Number of bytes to be written.
  Returns:
    Number of bytes written.
*/
__attribute__((section("driver")))
size_t DRV_SPI_Write ( DRV_HANDLE handle, void* buffer, size_t noOfBytes )
{
    register uint32_t *tempBuffer       = buffer, dummy;
    DRV_SPI_OBJ *dObj               = ((DRV_SPI_CLIENT_OBJ *) handle)->driverObject;
    SPI_MODULE_ID spiId             = dObj->spiId;
    size_t count = noOfBytes / 4;

    /* If there is something in the queue, return. Come back after some time. */
    if ( dObj->queueHead != NULL  )
    {
        return 0;
    }
    SYS_ASSERT((tempBuffer[0] != 0), "First word to transmit cannot be zero");
    /* Block until the operation is complete */
    while ( count )
    {
        while ( PLIB_SPI_TransmitBufferIsEmpty ( _DRV_SPI_PERIPHERAL_ID_GET( spiId ) ) )
        {
            PLIB_SPI_BufferWrite ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ), *tempBuffer++ );
            count--;
        }
        if ( PLIB_SPI_ReceiverBufferIsFull ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) ) )
        {
            dummy = PLIB_SPI_BufferRead ( _DRV_SPI_PERIPHERAL_ID_GET ( spiId ) );
        }
    }
    return noOfBytes;
}


// *****************************************************************************
/* Function:
    DRV_SPI_BUFFER_OBJ* _DRV_SPI_QueueSlotGet ( DRV_SPI_OBJ *dObj )

  Summary:
    Adds an element to the queue.

  Description:
    This API adds an element to the queue.

  Parameters:
    spiDataObj   - Pointer to the structure which holds the data which is to be
    				added to the queue.

  Returns:
    DRV_SPI_BUFFER_HANDLE - Handle, a pointer to the allocated element in the
    						queue.
*/
__attribute__((section("driver")))
DRV_SPI_BUFFER_OBJECT* _DRV_SPI_QueueSlotGet ( DRV_SPI_OBJ *dObj )
{
    int index;
    DRV_SPI_BUFFER_OBJECT *lQueueObj;
    SYS_MODULE_INDEX drvIndex = dObj->drvIndex;

    for ( index=0; index<DRV_SPI_BUFFER_OBJ_SIZE;index++ )
    {
        lQueueObj = &gDrvSPIBufferObj [ drvIndex ][ index ];

        if ( lQueueObj->inUse == false )
        {
            /* This should be the first thing we do after getting a slot */
            lQueueObj->inUse    = true;
            lQueueObj->status   = DRV_SPI_BUFFER_EVENT_PENDING;

            /* Return the pointer reference */
            return lQueueObj;
        }
    }
    return NULL;
}


// *****************************************************************************
/* Function:
    void _DRV_SPI_QueueCleanup ( DRV_HANDLE *dObj )
 * Note: don't use this. It does not work because txBuffer is being incremented in
 * the Task method, and so txBuffer does not point to the heap memory anymore
 * when this method runs.

  Summary:
    Removes all inactive buffers in queue.

  Description:
    This API removes all inactive elements from the queue.

  Parameters:
    dObj   - Actually a client object.

  Returns:
    None.
*/
__attribute__((section("driver")))
void _DRV_SPI_QueueCleanup ( DRV_HANDLE *dObj )
{
    int index;
    DRV_SPI_BUFFER_OBJECT *lQueueObj;
    DRV_SPI_CLIENT_OBJ *clientObj = (DRV_SPI_CLIENT_OBJ*) dObj;
    SYS_MODULE_INDEX drvIndex = clientObj->driverObject->drvIndex;

    // clean up used buffers (free heap memory)
    for ( index=0; index<DRV_SPI_BUFFER_OBJ_SIZE;index++ )
    {
        lQueueObj = &gDrvSPIBufferObj [ drvIndex ][ index ];

        if ( lQueueObj->inUse == false
                && lQueueObj->status == DRV_SPI_BUFFER_EVENT_COMPLETE
                && lQueueObj->txBuffer != NULL)
        {
            free(lQueueObj->txBuffer);
            lQueueObj->txBuffer = NULL;
        }
    }
}

//******************************************************************************
/* Function:
    unsigned int DRV_SPI_VersionGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets SPI driver version in numerical format.

  Description:
    This routine gets the SPI driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringized version can be obtained
    using DRV_SPI_VersionStrGet()

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/
__attribute__((section("driver")))
unsigned int DRV_SPI_VersionGet( const SYS_MODULE_INDEX drvIndex )
{
    return( ( _DRV_SPI_VERSION_MAJOR * 10000 ) +
            ( _DRV_SPI_VERSION_MINOR * 100 ) +
            ( _DRV_SPI_VERSION_PATCH ) );

} /* DRV_SPI_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_SPI_VersionStrGet ( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets SPI driver version in string format.

  Description:
    This routine gets the SPI driver version. The version is returned as
    major.minor.path[type], where type is optional. The numertical version can
    be obtained using DRV_SPI_VersionGet()

  Parameters:
    None.

  Returns:
    Current SPI driver version in the string format.

  Remarks:
    None.
*/
__attribute__((section("driver")))
char * DRV_SPI_VersionStrGet( const SYS_MODULE_INDEX drvIndex )
{
    return _DRV_SPI_VERSION_STR;

} /* DRV_SPI_VersionStrGet */

/*******************************************************************************
End of File
*/



