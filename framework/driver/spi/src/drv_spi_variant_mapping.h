/*******************************************************************************
  SPI Driver Feature Variant Implementations

  Company:
    Microchip Technology Inc.

  File Name:
    drv_spi_variant_mapping.h

  Summary:
    SPI Driver feature variant implementations.

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature.
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


#ifndef _DRV_SPI_VARIANT_MAPPING_H
#define _DRV_SPI_VARIANT_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#if (true == DRV_SPI_UNIFIED)

    #if !defined(DRV_SPI_INSTANCES_NUMBER)
    
        #if defined(DRV_SPI_CLIENTS_NUMBER)
        
            /* Map internal macros and functions to the static multi open variant */
            #include "driver/spi/src/static/drv_spi_hw_static.h"
            #include "driver/spi/src/client_single/drv_spi_client_multi.h"
        
        #else
        
            /* Map internal macros and functions to the static single open variant */
            #include "driver/spi/src/static/drv_spi_hw_static.h"
            #include "driver/spi/src/client_single/drv_spi_client_single.h"
    
        #endif
        
    #else // (DRV_SPI_INSTANCES_NUMBER > 1)
    
        /* Map internal macros and functions to the dynamic variant */
        #include "driver/spi/src/dynamic/drv_spi_hw_dynamic.h"
        #include "driver/spi/src/client_multi/drv_spi_client_multi.h"
    
    #endif

#endif

// *****************************************************************************
// *****************************************************************************
// Section: SPI Driver Static Object Generation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_SPI_OBJ_MAKE_NAME(name)

  Summary:
    Creates an instance-specific static object name.

  Description:
     This macro creates the instance-specific name of the specified static object
     by inserting the index number into the name.

  Remarks:
    This macro does not affect the dynamic objects.
*/

#define _DRV_STATIC_OBJ_NAME_B(name,id)     name ## id

#define _DRV_STATIC_OBJ_NAME_A(name,id)     _DRV_STATIC_OBJ_NAME_B(name,id)

#define _DRV_SPI_OBJ_MAKE_NAME(name)        _DRV_STATIC_OBJ_NAME_A(name, DRV_SPI_INDEX)


// *****************************************************************************
// *****************************************************************************
// Section: Feature Variant Mapping
// *****************************************************************************
// *****************************************************************************
/* Some variants are determined by hardware feature existence, some features
   are determined user configuration of the driver, and some variants are
   a combination of the two.
*/

// *****************************************************************************
/* PLIB ID Static Configuration Override

  Summary:
    Allows static override of the peripehral library ID.

  Description:
    These macros allow the peripheral library ID to be statically overriden by 
    the DRV_SPI_PERIPHERAL_ID configuration macro, if it is defined.
    
    _DRV_SPI_PERIPHERAL_ID_GET replaces the value passed in with the value
    defined by the DRV_SPI_PERIPHERAL_ID configuration option.
    
    _DRV_SPI_STATIC_PLIB_ID removes any statement passed into it from the
    build if the DRV_SPI_PERIPHERAL_ID configuration option is defined.
*/

#if defined(DRV_SPI_PERIPHERAL_ID)

    #define _DRV_SPI_PERIPHERAL_ID_GET(plibId)          DRV_SPI_PERIPHERAL_ID
    #define _DRV_SPI_STATIC_PLIB_ID(any)

#else

    #define _DRV_SPI_PERIPHERAL_ID_GET(plibId)          plibId
    #define _DRV_SPI_STATIC_PLIB_ID(any)                any

#endif


// *****************************************************************************
/* Interrupt Source Static Configuration Override

  Summary:
    Allows static override of the interrupt source.

  Description:
    These macros allow the interrupt source to be statically overriden by the 
    DRV_SPI_INTERRUPT_SOURCE configuration macro, if it is defined.
    
    _DRV_SPI_INT_SRC_GET replaces the value passed in with the value defined
    by the DRV_SPI_INTERRUPT_SOURCE configuration option.
    
    _DRV_SPI_STATIC_INT_SRC removes any statement passed into it from the
    build if the DRV_SPI_INTERRUPT_SOURCE configuration option is defined.
*/

#if defined(DRV_SPI_INTERRUPT_SOURCE)

    /* Static access macros */
    #define _DRV_SPI_INT_SRC_GET(source)                DRV_SPI_INTERRUPT_SOURCE
    #define _DRV_SPI_STATIC_INT_SRC(any)

#else

    /* Dynamic access macros */
    #define _DRV_SPI_INT_SRC_GET(source)                source
    #define _DRV_SPI_STATIC_INT_SRC(any)                any

#endif

#if defined(DRV_SPI_INTERRUPT_SOURCE_RX)

    /* Static access macros */
    #define _DRV_SPI_GET_INT_SRC_RX(source)             DRV_SPI_INTERRUPT_SOURCE_RX
    #define _DRV_SPI_STATIC_INT_SRC_RX(any)

#else

    /* Dynamic access macros */
    #define _DRV_SPI_GET_INT_SRC_RX(source)             source
    #define _DRV_SPI_STATIC_INT_SRC_RX(any)             any

#endif

#if defined(DRV_SPI_INTERRUPT_SOURCE_ERROR)

    /* Static access macros */
    #define _DRV_SPI_GET_INT_SRC_ERROR(source)          DRV_SPI_INTERRUPT_SOURCE_ERROR
    #define _DRV_SPI_STATIC_INT_SRC_ERROR(any)

#else

    /* Dynamic access macros */
    #define _DRV_SPI_GET_INT_SRC_ERROR(source)          source
    #define _DRV_SPI_STATIC_INT_SRC_ERROR(any)          any

#endif

#if defined(DRV_SPI_CLIENT_SPECIFIC_CONTROL)
	#define _DRV_SPI_CLIENT_SWITCH_CLIENT()\
		if(dObj->lastClientHandle != lObj->clientHandle) \
		{ \
			_DRV_SPI_ClientHardwareSetup(lObj->clientHandle);\
			dObj->lastClientHandle = lObj->clientHandle; \
		}
        #define _DRV_SPI_SAVE_LAST_CLIENT()\
            {\
                dObj = clientObj->driverObject;\
                gDrvSPIObj[dObj].lastClientHandle = DRV_SPI_CLIENTS_NUMBER + 1 ;\
            }
#else
	#define _DRV_SPI_CLIENT_SWITCH_CLIENT()
        #define _DRV_SPI_SAVE_LAST_CLIENT()
#endif	

// *****************************************************************************
/* Interrupt Source Control

  Summary:
    Macros to enable, disable or clear the interrupt source.

  Description:
    These macros enable, disable, or clear the interrupt source.

    The macros get mapped to the respective SYS module APIs if the configuration
    option DRV_SPI_INTERRUPT_MODE is set to true.
 
  Remarks:
    These macros are mandatory.
*/

#if defined (DRV_SPI_INTERRUPT_MODE) && (DRV_SPI_INTERRUPT_MODE == true)

    #define _DRV_SPI_InterruptSourceEnable(source)      SYS_INT_SourceEnable( source )
    #define _DRV_SPI_InterruptSourceDisable(source)     SYS_INT_SourceDisable( source )
    #define _DRV_SPI_InterruptSourceClear(source)       SYS_INT_SourceStatusClear( source )

    #define _DRV_SPI_InterruptSourceStatusGet(source)   SYS_INT_SourceStatusGet( source )
    #define _DRV_SPI_InterruptSourceStatusSet(source)   SYS_INT_SourceStatusSet( source )

#elif defined (DRV_SPI_INTERRUPT_MODE) && (DRV_SPI_INTERRUPT_MODE == false)

    #define _DRV_SPI_InterruptSourceEnable(source)
    #define _DRV_SPI_InterruptSourceDisable(source)
    #define _DRV_SPI_InterruptSourceClear(source)       SYS_INT_SourceStatusClear( source )

    #define _DRV_SPI_InterruptSourceStatusGet(source)   SYS_INT_SourceStatusGet( source )

#else

    #error "No Task mode chosen at build, interrupt or polling needs to be selected. "

#endif


// *****************************************************************************
/* TX FIFO Interrupt Mode Control

  Summary:
    Selects the FIFO interrupt mode.

  Description:
    This macro selects the FIFO interrupt mode.

  Remarks:
    Mandatory for the enhanced mode.
*/

#if defined ( __PIC24F__ )
    #define _DRV_SPI_TxFIFOInterruptModeSelect( index, mode )     \
            PLIB_SPI_FIFOInterruptModeSelect( index, mode )
#elif defined ( __PIC32MX__ )
    #define _DRV_SPI_TxFIFOInterruptModeSelect( index, mode )   PLIB_SPI_FIFOInterruptModeSelect( index, mode )
#else
    #define _DRV_SPI_TxFIFOInterruptModeSelect( index, mode )
#endif


// *****************************************************************************
/* RX FIFO Interrupt Mode Control

  Summary:
    Select the FIFO interrupt mode.

  Description:
    This macro selects the FIFO interrupt mode.

  Remarks:
    Mandatory for the enhanced mode.
*/

#if defined ( __PIC24F__ )
    #define _DRV_SPI_RxFIFOInterruptModeSelect( index, mode )
#elif defined ( __PIC32MX__ )
    #define _DRV_SPI_RxFIFOInterruptModeSelect( index, mode )   PLIB_SPI_FIFOInterruptModeSelect(index, mode )
#else
    #define _DRV_SPI_RxFIFOInterruptModeSelect( index, mode )
#endif


// *****************************************************************************
// *****************************************************************************
// Initialization Parameter Static Overrides
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Power mode Configuration Override

  Summary:
    Allows static override of the power mode.

  Description:
    These macros allow the power mode to be statically overriden by
    the DRV_SPI_POWER_STATE configuration macro, if it is defined.

    _DRV_SPI_POWER_STATE_GET replaces the value passed in with the value defined by
    the DRV_SPI_POWER_STATE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_POWER_STATE)

    #define _DRV_SPI_POWER_STATE_GET(arg)               DRV_SPI_POWER_STATE

#else

    #define _DRV_SPI_POWER_STATE_GET(arg)               (arg)

#endif


// *****************************************************************************
/* Communication width Configuration Override

  Summary:
    Allows static override of the communication width.

  Description:
    These macros allow the communication width to be statically overriden by
    the DRV_SPI_COMMUNICATION_WIDTH configuration macro, if it is defined.

    _DRV_SPI_COMMUNICATION_WIDTH_GET replaces the value passed in with the value
    defined by the DRV_SPI_COMMUNICATION_WIDTH configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_COMMUNICATION_WIDTH)

    #define _DRV_SPI_COMMUNICATION_WIDTH_GET(arg)       DRV_SPI_COMMUNICATION_WIDTH

#else

    #define _DRV_SPI_COMMUNICATION_WIDTH_GET(arg)       (arg)

#endif


// *****************************************************************************
/* Protocol type Configuration Override

  Summary:
    Allows static override of the protocol type.

  Description:
    These macros allow the protocol type to be statically overriden by
    the DRV_SPI_PROTOCOL_USAGE_TYPE configuration macro, if it is defined.

    _DRV_SPI_PROTOCOL_TYPE_GET replaces the value passed in with the value
    defined by the DRV_SPI_PROTOCOL_USAGE_TYPE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_PROTOCOL_USAGE_TYPE)

    #define _DRV_SPI_PROTOCOL_USAGE_TYPE_GET(arg)       DRV_SPI_PROTOCOL_USAGE_TYPE

#else

    #define _DRV_SPI_PROTOCOL_USAGE_TYPE_GET(arg)       (arg)

#endif


// *****************************************************************************
/* Buffer type Configuration Override

  Summary:
    Allows static override of the buffer type.

  Description:
    These macros allow the buffer type to be statically overriden by
    the DRV_SPI_BUFFER_USAGE_TYPE configuration macro, if it is defined.

    _DRV_SPI_BUFFER_TYPE_GET replaces the value passed in with the value
    defined by the DRV_SPI_BUFFER_USAGE_TYPE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_BUFFER_USAGE_TYPE)

    #define _DRV_SPI_BUFFER_USAGE_TYPE_GET(arg)         DRV_SPI_BUFFER_USAGE_TYPE

#else

    #define _DRV_SPI_BUFFER_USAGE_TYPE_GET(arg)         (arg)

#endif


// *****************************************************************************
/* TX FIFO Interrupt Mode Configuration Override

  Summary:
    Allows static override of the TX FIFO interrupt mode.

  Description:
    These macros allow the TX FIFO interrupt mode to be statically overriden by
    the DRV_SPI_TX_FIFO_INTERRUPT_MODE configuration macro, if it is defined.

    _DRV_SPI_TX_FIFO_INTERRUPT_MODE_GET replaces the value passed in with the value
    defined by the DRV_SPI_TX_FIFO_INTERRUPT_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_TX_FIFO_INTERRUPT_MODE)

    #define _DRV_SPI_TX_FIFO_INTERRUPT_MODE_GET(arg)         DRV_SPI_TX_FIFO_INTERRUPT_MODE

#else

    #define _DRV_SPI_TX_FIFO_INTERRUPT_MODE_GET(arg)         (arg)

#endif


// *****************************************************************************
/* RX FIFO Interrupt Mode Configuration Override

  Summary:
    Allows static override of the RX FIFO interrupt mode.

  Description:
    These macros allow the RX FIFO interrupt mode to be statically overriden by
    the DRV_SPI_RX_FIFO_INTERRUPT_MODE configuration macro, if it is defined.

    _DRV_SPI_RX_FIFO_INTERRUPT_MODE_GET replaces the value passed in with the value
    defined by the DRV_SPI_RX_FIFO_INTERRUPT_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_RX_FIFO_INTERRUPT_MODE)

    #define _DRV_SPI_RX_FIFO_INTERRUPT_MODE_GET(arg)         DRV_SPI_RX_FIFO_INTERRUPT_MODE

#else

    #define _DRV_SPI_RX_FIFO_INTERRUPT_MODE_GET(arg)         (arg)

#endif


// *****************************************************************************
/* Input Sample Phase Configuration Override

  Summary:
    Allows static override of the input sample phase.

  Description:
    These macros allow the input sample phase to be statically overriden by
    the DRV_SPI_INPUT_SAMPLE_PHASE configuration macro, if it is defined.

    _DRV_SPI_INPUT_SAMPLE_PHASE_GET replaces the value passed in with the value
    defined by the DRV_SPI_INPUT_SAMPLE_PHASE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_INPUT_SAMPLE_PHASE)

    #define _DRV_SPI_INPUT_SAMPLE_PHASE_GET(arg)        DRV_SPI_INPUT_SAMPLE_PHASE

#else

    #define _DRV_SPI_INPUT_SAMPLE_PHASE_GET(arg)        (arg)

#endif


// *****************************************************************************
/* SPI mode Configuration Override

  Summary:
    Allows static override of the SPI mode.

  Description:
    These macros allow the SPI mode to be statically overriden by
    the DRV_SPI_USAGE_MODE configuration macro, if it is defined.

    _DRV_SPI_USAGE_MODE_GET replaces the value passed in with the value
    defined by the DRV_SPI_USAGE_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_USAGE_MODE)

    #define _DRV_SPI_USAGE_MODE_GET(arg)                DRV_SPI_USAGE_MODE

#else

    #define _DRV_SPI_USAGE_MODE_GET(arg)                (arg)

#endif

#if defined(DRV_SPI_DUPLEX_MODE)

    #define _DRV_SPI_DUPLEX_MODE_GET(arg)                DRV_SPI_DUPLEX_MODE

#else

    #define _DRV_SPI_DUPLEX_MODE_GET(arg)                (arg)

#endif


// *****************************************************************************
/* Baud rate value Configuration Override

  Summary:
    Allows static override of the baud rate value.

  Description:
    These macros allow the baud rate value to be statically overriden by
    the DRV_SPI_BAUD_RATE_VALUE configuration macro, if it is defined.

    _DRV_SPI_BAUD_RATE_VALUE_GET replaces the value passed in with the value
    defined by the DRV_SPI_BAUD_RATE_VALUE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_BAUD_RATE_VALUE)

    #define _DRV_SPI_BAUD_RATE_VALUE_GET(arg)           DRV_SPI_BAUD_RATE_VALUE

#else

    #define _DRV_SPI_BAUD_RATE_VALUE_GET(arg)           (arg)

#endif


// *****************************************************************************
/* SPI clock operation mode Configuration Override

  Summary:
    Allows static override of the SPI clock operation mode.

  Description:
    These macros allow the SPI clock operation mode to be statically overriden by
    the DRV_SPI_CLOCK_OPERATION_MODE configuration macro, if it is defined.

    _DRV_SPI_CLOCK_OPERATION_MODE_GET replaces the value passed in with the value
    defined by the DRV_SPI_CLOCK_OPERATION_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_SPI_CLOCK_OPERATION_MODE)

    #define _DRV_SPI_CLOCK_OPERATION_MODE_GET(arg)      DRV_SPI_CLOCK_OPERATION_MODE

#else

    #define _DRV_SPI_CLOCK_OPERATION_MODE_GET(arg)      (arg)

#endif



#endif //_DRV_SPI_VARIANT_MAPPING_H

/*******************************************************************************
 End of File
*/

