/*******************************************************************************
  SPI Device Driver Definition

  Company:
    Microchip Technology Inc.

  File Name:
    drv_spi_static.c

  Summary:
    SPI Driver static single client implementation.

  Description:
    The SPI device driver provides a simple interface to manage the SPI
    modules on Microchip microcontrollers.  This file implements the core
    interface routines for the SPI driver.
    
    While building the driver from source, ALWAYS use this file in the build.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
    Defines the hardware instances objects that are available on the device.

  Description:
    This data type defines the hardware instance objects that are available on
    the device, so as to capture the hardware state of the instance.

  Remarks:
    Not all modes are available on all devices.
*/

DRV_SPI_OBJ                         _DRV_SPI_OBJ_MAKE_NAME( gDrvSPIObj ) ;


// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects that are available on the device.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the Client state of the instance.

  Remarks:
    None.
*/

DRV_SPI_CLIENT_OBJ                  _DRV_SPI_OBJ_MAKE_NAME( gDrvSPIClientObj ) ;


// *****************************************************************************
/* Driver buffer objects.

  Summary:
    Defines the buffer objects.

  Description:
    This data type defines the buffer objects.

  Remarks:
    None.
*/

SPI_DATA_TYPE                       gDrvSPIBufferObj[DRV_SPI_BUFFER_SIZE];


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Macros
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_SPI_OBJ(obj,mem)

  Summary:
    Returns the appropriate driver object member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.

*/

#define _DRV_SPI_OBJ(obj,mem)       _DRV_SPI_OBJ_MAKE_NAME(gDrvSPIObj).mem


// *****************************************************************************
/* Macro: _DRV_SPI_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_SPI_CLIENT_OBJ(obj,mem)    _DRV_SPI_OBJ_MAKE_NAME(gDrvSPIClientObj).mem

/* Below commented for PIC32, as it is not required.
void lockIO(){
asm volatile ("mov #OSCCON,w1 \n"
				"mov #0x46, w2 \n"
				"mov #0x57, w3 \n"
				"mov.b w2,[w1] \n"
				"mov.b w3,[w1] \n"
				"bset OSCCON, #6");
}

void unlockIO(){
asm volatile ("mov #OSCCON,w1 \n"
				"mov #0x46, w2 \n"
				"mov #0x57, w3 \n"
				"mov.b w2,[w1] \n"
				"mov.b w3,[w1] \n"
				"bclr OSCCON, #6");
}
*/


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************


//******************************************************************************
/* Function:
    static void _DRV_SPI_PortSetup( const SPI_MODULE_ID    plibId,
                                    DRV_SPI_PORTS_CONFIG   * portsConfig )

  Summary:
    Sets up the ports from the initialization structure.

  Description:
    This function sets up the ports from the initialization structure.

  Remarks:
    Called.
*/

static void _DRV_SPI_PortSetup( DRV_SPI_PORT_PINS * pinConfig )
{
    // Ram: ToDo

// Below commented for PIC32 testing. Enable for PIC24.
//    AD1PCFGL = 0xFFFF;
//
//    unlockIO();
//
//    /* Master */
//    _RP18R = 8;	 // sck1 output - RP18 - RB5
//    _SDI1R = 0;  // sdi1 input  - RP0  - RB0
//    _RP20R = 7;  // sdo1 output - RP20 - RD5
//    _RP13R = 9;  // ss1  output - RP13 - RB2
//
//    _SCK2R = 28; // sck2 input  - RP28 - RB4
//    _SDI2R = 1;  // sdi2 input  - RP1  - RB1
//    _RP27R = 10; // sdo2 output - RP27 - RG9
//    _SS2R  = 12; // ss2  input  - RP19 - RG8
//
//    Nop();
//
//    lockIO();
//
//    /* Pin activation */
//    PLIB_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET(plibId), SPI_PIN_SERIAL_CLOCK );
    PLIB_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET(plibId), SPI_PIN_DATA_OUT );

    /* Check if the PORTS configuration is through remapping ? */
    if( true == DRV_SPI_PORTS_REMAP_USAGE )
    {
//        /* MISO - Input Mapping */
//        SYS_PORTS_InputRemapping( portsConfig->inputFunc, portsConfig->inputPin );
//
//        /* MOSI - Output Mapping */
//        SYS_PORTS_OutputRemapping( portsConfig->outputPin, portsConfig->outputFunc );
//
//        /* SCK - Mapping */
//        if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
//        {
//            /* SCK - Output Mapping */
//            SYS_PORTS_OutputRemapping( portsConfig->clockOutputPin, portsConfig->clockOutputFunc );
//        }
//        else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
//        {
//            /* SCK - Input Mapping */
//            SYS_PORTS_InputRemapping( portsConfig->clockInputFunc, portsConfig->clockInputPin );
//        }
//
//        /* /SS - Mapping */
//        if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
//        {
//            /* /SS - Output Mapping */
//            SYS_PORTS_OutputRemapping( portsConfig->ssOutputPin, portsConfig->ssOutputFunc );
//        }
//        else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
//        {
//            /* /SS - Input Mapping */
//            SYS_PORTS_InputRemapping( portsConfig->ssInputFunc, portsConfig->ssInputPin );
//        }
    }
    else /* ( false == DRV_SPI_PORTS_REMAP_USAGE ) */
    {
//        /* MISO - Input Enabling */
//        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_DATA_IN );
//
//        /* MOSI - Output Enabling */
//        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_DATA_OUT );
//
//        /* SCK - Enabling */
//        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_SERIAL_CLOCK );
//
//        if ( false == DRV_SPI_SLAVE_SELECT_MANUAL )
//        {
//            /* Slave Select - Input Enabling */
//            _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_SLAVE_SELECT );
//        }
//        else
//        {
//            /* /SS - Configuration for Manual mode */
//            if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
//            {
//                /* /SS - Output */
//                _DRV_SPI_PinDirectionWriteSet( portsConfig->portId, portsConfig->pinNumber );
//            }
//            else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
//            {
//                /* /SS - Input */
//                _DRV_SPI_PinDirectionReadSet( portsConfig->portId, portsConfig->pinNumber );
//            }
//        }
    }

} /* _DRV_SPI_PortSetup */


//******************************************************************************
/* Function:
    static void _DRV_SPI_SetupHardware( const SPI_MODULE_ID    plibId,
                                        DRV_SPI_OBJ_HANDLE     dObj,
                                        DRV_SPI_INIT           *spiInit )

  Summary:
    Sets up the hardware from the initialization structure.

  Description:
    This function sets up the hardware from the initialization structure.
 
  Remarks:
    Called.
*/

static void _DRV_SPI_SetupHardware( DRV_SPI_INIT * spiInit )
{
    /* Initialize the Interrupt Sources */
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ( DRV_SPI_INDEX, txInterruptSource ) = _DRV_SPI_INT_SRC_GET( spiInit->txInterruptSource ) );
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ( DRV_SPI_INDEX, rxInterruptSource ) = _DRV_SPI_GET_INT_SRC_RX( spiInit->rxInterruptSource ) );
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ( DRV_SPI_INDEX, errInterruptSource ) = _DRV_SPI_GET_INT_SRC_ERROR( spiInit->errInterruptSource ) );

    /* Power state initialization */
    if( PLIB_SPI_ExistsStopInIdleControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
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
    }

    /* Clock Mode Intialization */
    if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 0 - Idle State Low & Sampling on Rising Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                          SPI_CLOCK_POLARITY_IDLE_LOW );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
        }
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 1 - Idle State Low & Sampling on Falling Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                          SPI_CLOCK_POLARITY_IDLE_LOW );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                            SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
        }
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 2 - Idle State High & Sampling on Falling Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                          SPI_CLOCK_POLARITY_IDLE_HIGH );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
        }
    }
    else // ( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE == _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode ) )
    {
        /* Mode 3 - Idle State High & Sampling on Rising Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                          SPI_CLOCK_POLARITY_IDLE_HIGH );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                            SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
        }
    }
    /* Update the clock mode */
    _DRV_SPI_OBJ( DRV_SPI_INDEX, clockMode ) = _DRV_SPI_CLOCK_OPERATION_MODE_GET( spiInit->clockMode );

    /* Input Sample Phase */
    if( PLIB_SPI_ExistsInputSamplePhase( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_SPI_InputSamplePhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                         _DRV_SPI_INPUT_SAMPLE_PHASE_GET( spiInit->inputSamplePhase ) );
        _DRV_SPI_OBJ( DRV_SPI_INDEX, inputSamplePhase ) = _DRV_SPI_INPUT_SAMPLE_PHASE_GET( spiInit->inputSamplePhase );
    }

    /* Usage Mode Master/Slave */
    if( PLIB_SPI_ExistsMasterControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( _DRV_SPI_USAGE_MODE_GET( spiInit->spiMode ) == DRV_SPI_MODE_MASTER )
        {
            /* Master Enable */
            PLIB_SPI_MasterEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }
        else
        {
            /* Slave Enable */
            PLIB_SPI_SlaveEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }

        _DRV_SPI_OBJ( DRV_SPI_INDEX, spiMode ) = _DRV_SPI_USAGE_MODE_GET( spiInit->spiMode );
    }

    /* Slave Select Handling */
    if( _DRV_SPI_USAGE_MODE_GET( spiInit->spiMode ) == DRV_SPI_MODE_SLAVE )
    {
        if( PLIB_SPI_ExistsSlaveSelectControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_SlaveSelectEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }
    }
    else
    {
        if( PLIB_SPI_ExistsSlaveSelectControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_SlaveSelectDisable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) );
        }
    }

    /* Communication Width Selection */
    if( PLIB_SPI_ExistsCommunicationWidth( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_SPI_CommunicationWidthSelect( _DRV_SPI_PERIPHERAL_ID_GET( plibId ),
                                           _DRV_SPI_COMMUNICATION_WIDTH_GET( spiInit->commWidth ) );
        _DRV_SPI_OBJ( DRV_SPI_INDEX, commWidth) = _DRV_SPI_COMMUNICATION_WIDTH_GET( spiInit->commWidth );
    }

    /* Baudrate selection */
    if( PLIB_SPI_ExistsBaudRate( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
    {
        // For PIC32
        PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL ),
                              _DRV_SPI_BAUD_RATE_VALUE_GET( spiInit->baudRate ) );
        // For PIC24
        //PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), 4000000,
        //                      _DRV_SPI_BAUD_RATE_VALUE_GET( spiInit->baudRate ) );
    }

    /* Protocol Selection */
    if( _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType ) == DRV_SPI_PROTOCOL_TYPE_FRAMED )
    {
        /* Frame Sync Pulse Direction */
        if( PLIB_SPI_ExistsFrameSyncPulseDirection( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_FrameSyncPulseDirectionSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ),
                                                    DRV_SPI_FRAME_SYNC_PULSE_DIRECTION );
        }

        /* Frame Sync Pulse Polarity */
        if( PLIB_SPI_ExistsFrameSyncPulsePolarity( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_FrameSyncPulsePolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ),
                                                   DRV_SPI_FRAME_SYNC_PULSE_POLARITY );
        }

        /* Frame Sync Pulse Edge */
        if( PLIB_SPI_ExistsFrameSyncPulseEdge( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_FrameSyncPulseEdgeSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ),
                                               DRV_SPI_FRAME_SYNC_PULSE_EDGE );
        }

        /* Check if the framed communication is supported by the device */
        if( PLIB_SPI_ExistsFramedCommunication( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_FramedCommunicationEnable( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) );
        }

        /* ToDo: Other Frame based parameters update, if any */
    }
    else if( _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType ) == DRV_SPI_PROTOCOL_TYPE_AUDIO )
    {
        /* Check if the audio protocol is supported by the device */
        if( PLIB_SPI_ExistsAudioProtocolControl( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_SPI_AudioProtocolEnable( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) );
        }

        /* ToDo: Other Audio based parameters update */
    }

    _DRV_SPI_OBJ( DRV_SPI_INDEX, spiProtocolType ) = _DRV_SPI_PROTOCOL_USAGE_TYPE_GET( spiInit->spiProtocolType );

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

        _DRV_SPI_OBJ( DRV_SPI_INDEX, bufferType ) = _DRV_SPI_BUFFER_USAGE_TYPE_GET( spiInit->bufferType );
    }

    /* Buffer interrupt mode selection */
    if( _DRV_SPI_BUFFER_USAGE_TYPE_GET( spiInit->bufferType ) == DRV_SPI_BUFFER_TYPE_ENHANCED )
    {
        if( PLIB_SPI_ExistsFIFOInterruptMode( _DRV_SPI_PERIPHERAL_ID_GET( plibId ) ) )
        {
            /* Update the transmit buffer interrupt mode */
            _DRV_SPI_TxFIFOInterruptModeSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ),
                                                _DRV_SPI_TX_FIFO_INTERRUPT_MODE_GET( spiInit->txInterruptMode ) );
            /* Update the receive buffer interrupt mode */
            _DRV_SPI_RxFIFOInterruptModeSelect( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ),
                                                _DRV_SPI_RX_FIFO_INTERRUPT_MODE_GET( spiInit->rxInterruptMode ) );
        }
    }

    /* SPI Port Setup */
    _DRV_SPI_PortSetup( &spiInit->pinConfig );
    //_DRV_SPI_OBJ(DRV_SPI_INDEX, portsConfig) = spiInit->pinConfig;

} /* _DRV_SPI_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_SPI_Initialize( const SYS_MODULE_INDEX  index,
                                       const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the given instance of the SPI module.

  Description:
    This function initializes hardware for the instance of the SPI module,
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

void _DRV_SPI_MAKE_NAME(Initialize)( const SYS_MODULE_INIT * const init )
{
    DRV_SPI_INIT * spiInit = NULL;

    /* Assign to the local pointer the init data passed */
    spiInit = ( DRV_SPI_INIT * ) init;

    /* Object is valid, set it in use */
    _DRV_SPI_OBJ( DRV_SPI_INDEX, inUse ) = true;

    /* Update the SPI Module Index */
    _DRV_SPI_OBJ( DRV_SPI_INDEX, spiId ) = _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId );

    /* Setup the Hardware */
    _DRV_SPI_SetupHardware( spiInit );

    /* Update the object index */
    _DRV_SPI_OBJ( DRV_SPI_INDEX, objIndex ) = DRV_SPI_INDEX;

    /* Clear the SPI Overflow Flag */
    if( PLIB_SPI_ExistsReceiverOverflow( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) )
    {
        PLIB_SPI_ReceiverOverflowClear ( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) );
    }

    /* Interrupt flag cleared on the safer side */
// For PIC24
//    IFS0bits.SPI1IF = false; // _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, txInterruptSource ) ) );
//    IFS0bits.SPI1IF = false; // _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, rxInterruptSource ) ) );
//    IFS0bits.SPF1IF = false; // _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, errInterruptSource ) ) );
// For PIC32
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, txInterruptSource ) ) );
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, rxInterruptSource ) ) );
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, errInterruptSource ) ) );
    
    /* Enable the interrupt source in case of interrupt mode */
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, txInterruptSource ) ) );
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, rxInterruptSource ) ) );
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, errInterruptSource ) ) );

    /* Set the current driver state */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , status ) = SYS_STATUS_READY;

    /* Enable the SPI module */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) )
    {
        PLIB_SPI_Enable( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) ;
    }

} /* DRV_SPI_Initialize */


//******************************************************************************
/* Function:
    void DRV_SPI_Reinitialize( SYS_MODULE_OBJ          object,
                               const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes and refreshes the hardware for the instance of the SPI
    module.

  Description:
    This function reinitializes and refreshes the hardware for the instance
    of the SPI module using the specified hardware initialization data.
    It does not clear or reinitialize internal data structures.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware.

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Reinitialize )( const SYS_MODULE_INIT * const init )
{
    DRV_SPI_INIT * spiInit = NULL;

    /* Valid init structure is present */
    spiInit = ( DRV_SPI_INIT * ) init;

    /* Stop/Disable the device if needed */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) )
    {
        PLIB_SPI_Disable ( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) ;
    }

    /* Setup the Hardware */
    _DRV_SPI_SetupHardware( spiInit );

    /* Start/Enable the device if it was stop/disabled */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) )
    {
        PLIB_SPI_Enable ( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) ;
    }

    /* Set the curent driver state */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , status ) = SYS_STATUS_READY;

} /* DRV_SPI_Reinitialize */


//******************************************************************************
/* Function:
    void DRV_SPI_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the SPI module.

  Description:
    Deinitializes the specific module instancedisabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Deinitialize )( void )
{
    /* Interrupt De-Registration */
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, txInterruptSource ) ) );
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, rxInterruptSource ) ) );
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, errInterruptSource ) ) );

    /* Stop/Disable the device if needed */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) )
    {
        PLIB_SPI_Enable ( _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ) ) ;
    }

    /* SPI Port Deselect */
    if( false == DRV_SPI_PORTS_REMAP_USAGE )
    {
//        /* MISO - Input Enabling */
//        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), SPI_PIN_DATA_IN );
//
//        /* MOSI - Output Enabling */
//        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), SPI_PIN_DATA_OUT );
//
//        /* SCK - Enabling */
//        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), SPI_PIN_SERIAL_CLOCK );
//
//        if ( false == DRV_SPI_SLAVE_SELECT_MANUAL )
//        {
//            /* Slave Select - Input Enabling */
//            _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), SPI_PIN_SLAVE_SELECT );
//        }
    }
    else
    {

    }

    /* Set the Device Status */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , status ) = SYS_STATUS_UNINITIALIZED;

    /* Remove the driver usage */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , inUse ) = false;

} /* DRV_SPI_Deinitialize */


//******************************************************************************
/* Function:
    SYS_STATUS DRV_SPI_Status( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the SPI module.

  Description:
    This function Provides the current status of the hardware instance of the
    SPI module.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    SYS_STATUS_READY  -  Indicates that any previous module operation for the
                         specified module has completed
                        
    SYS_STATUS_BUSY   -  Indicates that a previous module operation for the
                         specified module has not yet completed
                        
    SYS_STATUS_ERROR  -  Indicates that the specified module is in an error state
*/

SYS_STATUS _DRV_SPI_MAKE_NAME( Status )( void )
{
    /* Return the status associated with the driver handle */
    return ( _DRV_SPI_OBJ( DRV_SPI_INDEX , status ) );

} /* DRV_SPI_Status */


//******************************************************************************
/* Function:
    void DRV_SPI_Tasks( SYS_MODULE_OBJ object )

  Summary:
    Used to maintain the driver's state machine and implement its ISR.

  Description:
    This function is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Tasks )( void )
{
    unsigned int bytesRead = 0 ;
// For PIC24
//    if( true == IFS0bits.SPI1IF) // _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , rxInterruptSource ) ) )
// For PIC32
    if( true == _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , rxInterruptSource ) ) ) )
    {
        if( PLIB_SPI_ReceiverBufferIsFull( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) ||
            !PLIB_SPI_ReceiverFIFOIsEmpty( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            while( bytesRead < _DRV_SPI_OBJ( DRV_SPI_INDEX , bufLength ) )
            {
                /* Receive a byte in the buffer */
                gDrvSPIBufferObj[bytesRead++] = PLIB_SPI_BufferRead( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
            }

            /* Give an indication to the higher layer upon successful transmission */
            _DRV_SPI_OBJ( DRV_SPI_INDEX , callback( ) );

            /* Update the transfer status */
            _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) |= DRV_SPI_TRANSFER_STATUS_SUCCESS;

            /* Clear Interrupt/Status Flag */
// For PIC24
//            IFS0bits.SPI1IF = false; // _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_RX( _DRV_SPI_OBJ( DRV_SPI_INDEX , rxInterruptSource ) ) ) ;
// For PIC32
            _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_RX( _DRV_SPI_OBJ( DRV_SPI_INDEX , rxInterruptSource ) ) ) ;
        }
    }

    /* This state is encountered when an error interrupt has occurred.
       or an error has occurred during read */
// For PIC24
//    if( true == IFS0bits.SPF1IF) // _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_GET_INT_SRC_ERROR( _DRV_SPI_OBJ( DRV_SPI_INDEX , errInterruptSource ) ) )
// For PIC32
      if( true == _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_GET_INT_SRC_ERROR( _DRV_SPI_OBJ( DRV_SPI_INDEX , errInterruptSource ) ) ) )
    {
        /* Check for the overflow error */
        if( PLIB_SPI_ReceiverHasOverflowed ( _DRV_SPI_PERIPHERAL_ID_GET(  _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            if( PLIB_SPI_ExistsReceiverOverflow( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
            {
                PLIB_SPI_ReceiverOverflowClear ( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
            }

            /* Update the transfer status */
            _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) |= DRV_SPI_TRANSFER_STATUS_OVERFLOW;
        }

        /* Clear Interrupt/Status Flag */
// For PIC24
//        IFS0bits.SPF1IF = false; // _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_ERROR( _DRV_SPI_OBJ( DRV_SPI_INDEX , errInterruptSource ) );
// For PIC32
          _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_ERROR( _DRV_SPI_OBJ( DRV_SPI_INDEX , errInterruptSource ) ) );
    }
    
} /* DRV_SPI_Tasks */


//******************************************************************************
/* Function:
    DRV_HANDLE DRV_SPI_Open( const SYS_MODULE_INDEX    index,
                             const DRV_IO_INTENT       intent )

  Summary:
    Opens the specific module instance and returns a handle.

  Description:
    This function opens a driver for use by any client module and provides a
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

void _DRV_SPI_MAKE_NAME( Open )( const DRV_IO_INTENT ioIntent )
{
    /* Setup client operations */

    /* To Do: OSAL - Lock Mutex */

    _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , inUse ) = true;
    _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , driverObject ) = DRV_SPI_INDEX;

    /* Update that, the client is opened in exclusive access mode */
    if( DRV_IO_ISEXCLUSIVE( ioIntent ) )
    {
        _DRV_SPI_OBJ( DRV_SPI_INDEX , IsExclusive ) = true;
    }

    /* To Do: OSAL - Unlock Mutex */

    /* Update the Client Status */
    _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , status ) = DRV_SPI_CLIENT_STATUS_READY;

} /* DRV_SPI_Open */


//******************************************************************************
/* Function:
    void DRV_SPI_Close( DRV_HANDLE handle )

  Summary:
    Closes an opened-instance of a driver.

  Description:
    This function closes an opened instance of a driver, invalidating the specified
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Close )( void )
{
    /* To Do: OSAL - lock Mutex */

    /* Free the Client Instance */
    _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , inUse ) = false ;

    /* To Do: OSAL - unlock Mutex */

    /* Update the Client Status */
    _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , status ) = DRV_SPI_CLIENT_STATUS_INVALID;

} /* DRV_SPI_Close */


//******************************************************************************
/* Function:
    DRV_SPI_CLIENT_STATUS DRV_SPI_ClientStatus(DRV_HANDLE handle)

  Summary:
    Gets the status of the module instance associated with the handle.

  Description:
    This function gets the status of the module instance associated with the
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    DRV_SPI_CLIENT_STATUS value describing the current status of the driver.
*/

DRV_SPI_CLIENT_STATUS _DRV_SPI_MAKE_NAME( ClientStatus )( void )
{
    /* Return the client status associated with the handle passed */
    return( _DRV_SPI_CLIENT_OBJ( DRV_SPI_INDEX , status ) );

} /* DRV_SPI_ClientStatus */


// *****************************************************************************
/* Function:
    void DRV_SPI_CommunicationSetup( DRV_HANDLE                        handle,
                                     const DRV_SPI_COMM_CONFIG * const config )

  Summary:
    Sets up the device communication parameters.

  Description:
    This function sets up the device communication parameters.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    config       - Communication parameters indetified by DRV_SPI_COMM_CONFIG

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( CommunicationSetup )( const DRV_SPI_COMM_CONFIG * const config )
{
     /* Stop/Disable the device */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
    {
        PLIB_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
    }

    /* Input Sample Phase */
    if( PLIB_SPI_ExistsInputSamplePhase( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
    {
        PLIB_SPI_InputSamplePhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                         config->inputSamplePhase );
        _DRV_SPI_OBJ( DRV_SPI_INDEX , inputSamplePhase ) = config->inputSamplePhase;
    }

    /* Clock Mode Intialization */
    if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE == config->clockMode )
    {
        /* Mode 0 - Idle State Low & Sampling on Rising Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                          SPI_CLOCK_POLARITY_IDLE_LOW );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
        }
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL == config->clockMode )
    {
        /* Mode 1 - Idle State Low & Sampling on Falling Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                          SPI_CLOCK_POLARITY_IDLE_LOW );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                            SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
        }
    }
    else if( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL == config->clockMode )
    {
        /* Mode 2 - Idle State High & Sampling on Falling Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                          SPI_CLOCK_POLARITY_IDLE_HIGH );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                            SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK );
        }
    }
    else // ( DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE == config->clockMode )
    {
        /* Mode 3 - Idle State High & Sampling on Rising Edge */

        /* Clock Polarity */
        if( PLIB_SPI_ExistsClockPolarity( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_ClockPolaritySelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                          SPI_CLOCK_POLARITY_IDLE_HIGH );
        }

        /* Output Data Phase */
        if( PLIB_SPI_ExistsOutputDataPhase( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
        {
            PLIB_SPI_OutputDataPhaseSelect( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ),
                                            SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK );
        }
    }
    /* Update the clock mode */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , clockMode ) = config->clockMode;

    /* Usage Mode Master/Slave */
    if( PLIB_SPI_ExistsMasterControl( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
    {
        if( config->spiMode == DRV_SPI_MODE_MASTER )
        {
            /* Master Enable */
            PLIB_SPI_MasterEnable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
        }
        else
        {
            /* Slave Enable */
            PLIB_SPI_SlaveEnable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
        }

        _DRV_SPI_OBJ( DRV_SPI_INDEX , spiMode ) = config->spiMode;
    }

    /* Baudrate selection */
    if( PLIB_SPI_ExistsBaudRate( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
    {
        // For PIC32
        PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL ),
                              config->baudRate );
        // For PIC24
        //PLIB_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), 4000000,
        //                      config->baudRate );
    }

    /* Register the callback */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , callback ) = config->callback;

     /* Restart the device */
    if( PLIB_SPI_ExistsEnableControl( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) ) )
    {
        PLIB_SPI_Enable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ) );
    }

} /* DRV_SPI_CommunicationSetup */


// *****************************************************************************
/* Function:
    SPI_DATA_TYPE DRV_SPI_Get( DRV_HANDLE handle )

  Summary:
    Gets/Reads a byte or word data from the SPI.

  Description:
    This function gets/reads a byte or word data from the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A byte or word Data received by the SPI driver.
*/

SPI_DATA_TYPE _DRV_SPI_MAKE_NAME( Get )( void )
{
    SPI_DATA_TYPE buffer;

    /* Update the data read from the buffer */
    buffer = gDrvSPIBufferObj[0];

    /* Update the transfer status */
    _DRV_SPI_OBJ( DRV_SPI_INDEX, transferStatus ) = 0;

    return( ( SPI_DATA_TYPE ) buffer );

} /* DRV_SPI_Get */


// *****************************************************************************
/* Function:
    void DRV_SPI_Put( DRV_HANDLE handle, const SPI_DATA_TYPE buffer )

  Summary:
    Writes a byte or word data to the SPI.

  Description:
    This function writes a byte or word data to the SPI.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

    buffer       - A byte or word data to be written to the SPI

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Put )( const SPI_DATA_TYPE buffer )
{
    /* Update the buffer length */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , bufLength ) = 1;

    /* Write the Data onto the SPI SDO/MOSI */
    PLIB_SPI_BufferWrite( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, spiId ) ), ( SPI_DATA_TYPE ) buffer ) ;

    if( DRV_SPI_BUFFER_TYPE_STANDARD == _DRV_SPI_OBJ( DRV_SPI_INDEX , bufferType ) )
    {
        /* Wait for Data Transmission */
        while( !PLIB_SPI_ReceiverBufferIsFull( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX, spiId ) ) ) );
    }

    /* Update the transfer status */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) |= DRV_SPI_TRANSFER_STATUS_IN_PROGRESS;

} /* DRV_SPI_Put */


// *****************************************************************************
/* Function:
    unsigned int DRV_SPI_GetBuffer ( DRV_HANDLE handle, SPI_DATA_TYPE *buffer,
                                     const unsigned int numbytes )

  Summary:
    Reads buffered data from the SPI.

  Description:
    This function reads buffered data from the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    buffer       - Buffer into which the data read from the SPI instance
                   will be placed.

    numbytes     - Total number of bytes that need to be read from the module
                   instance (must be equal to or less than the size of the
                   buffer)

  Returns:
    Number of bytes actually copied into the caller's buffer or -1 if there
    is an error (call DRV_SPI_ClientStatus to identify the error).
*/

unsigned int _DRV_SPI_MAKE_NAME( GetBuffer ) ( SPI_DATA_TYPE *buffer, const unsigned int numbytes )
{
    unsigned int bytesRead = 0 ;

    /* Block till the requested bytes are read */
    while ( bytesRead < numbytes )
    {
        /* Update the data read from the buffer */
        buffer[bytesRead++] = gDrvSPIBufferObj[bytesRead];
    }

    /* Update the transfer status */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) = 0;

    /* Return the number of bytes read */
    return bytesRead ;

} /* DRV_SPI_GetBuffer */


// *****************************************************************************
/* Function:
    unsigned int DRV_SPI_PutBuffer ( DRV_HANDLE handle, const SPI_DATA_TYPE *buffer,
                                     const unsigned int numbytes )

  Summary:
    Writes a buffered data to the SPI.

  Description:
    This function writes a buffered data to the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    buffer       - Buffer containing the data write to the SPI instance

    numbytes     - Total number of bytes that to write to the SPI instance
                   (must be equal to or less than the size of the buffer)

  Returns:
    Number of bytes actually written to the SPI or -1 if there is an error
    (call DRV_SPI_ClientStatus to identify the error).
*/

unsigned int _DRV_SPI_MAKE_NAME( PutBuffer ) ( const SPI_DATA_TYPE *buffer, const unsigned int numbytes )
{
    unsigned int bytesWritten = 0;

    /* Update the buffer length */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , bufLength ) = numbytes;

    /* Block till the requested bytes are written */
    while( bytesWritten < numbytes )
    {
        /* Write the Data onto the SPI SDO/MOSI */
        PLIB_SPI_BufferWrite( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( DRV_SPI_INDEX , spiId ) ), (SPI_DATA_TYPE)buffer[bytesWritten++] ) ;
    }

    /* Update the transfer status */
    _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) |= DRV_SPI_TRANSFER_STATUS_IN_PROGRESS;

} /* DRV_SPI_PutBuffer */


// *****************************************************************************
/* Function:
    DRV_SPI_TRANSFER_STATUS DRV_SPI_TransferStatus( DRV_HANDLE handle )

  Summary:
    Returns the transmitter and receiver transfer status.

  Description:
    This function returns the transmitter and receiver transfer status.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_SPI_TRANSFER_STATUS value describing the current status of the
    transfer.
*/

DRV_SPI_TRANSFER_STATUS _DRV_SPI_MAKE_NAME( TransferStatus )( void )
{
    DRV_SPI_TRANSFER_STATUS status = 0;

    /* Check for the transfer status */
    if( _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) & DRV_SPI_TRANSFER_STATUS_SUCCESS )
    {
        /* Update status saying the transfer was successful */
        status |= DRV_SPI_TRANSFER_STATUS_SUCCESS;
    }
    else if( _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) & DRV_SPI_TRANSFER_STATUS_OVERFLOW )
    {
        /* Update status saying the transfer resulted in an overflow */
        status |= DRV_SPI_TRANSFER_STATUS_OVERFLOW;
    }
    else if( _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) & DRV_SPI_TRANSFER_STATUS_IN_PROGRESS )
    {
        /* Indicate that the data transfer has been initiated */
        status |= DRV_SPI_TRANSFER_STATUS_IN_PROGRESS;
    }
    else //  if( _DRV_SPI_OBJ( DRV_SPI_INDEX , transferStatus ) & DRV_SPI_TRANSFER_STATUS_EMPTY )
    {
        /* Indicate that the data transfer is not initiated */
        status |= DRV_SPI_TRANSFER_STATUS_EMPTY;
    }

    /* return the status information */
    return status;

} /* DRV_SPI_TransferStatus */


//******************************************************************************
/* Function:
    unsigned int DRV_SPI_VersionGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets the SPI driver version in numerical format.

  Description:
    This function gets the SPI driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringed version can be obtained
    using DRV_SPI_VersionStrGet.

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/

unsigned int _DRV_SPI_MAKE_NAME( VersionGet )( void )
{
    return( ( _DRV_SPI_VERSION_MAJOR * 10000 ) +
            ( _DRV_SPI_VERSION_MINOR * 100 ) +
            ( _DRV_SPI_VERSION_PATCH ) );

} /* DRV_SPI_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_SPI_VersionStrGet ( void )

  Summary:
    Gets the SPI driver version in string format.

  Description:
    This function gets the SPI driver version. The version is returned as
    major.minor.path[type], where type is optional. The numerical version can
    be obtained using DRV_SPI_VersionGet.

  Parameters:
    None.

  Returns:
    Current SPI driver version in the string format.

  Remarks:
    None.
*/

char * _DRV_SPI_MAKE_NAME( VersionStrGet )( void )
{
    return _DRV_SPI_VERSION_STR;

} /* DRV_SPI_VersionStrGet */


/*******************************************************************************
End of File
*/



