/*******************************************************************************
  USART Driver Variant Mapping

  Company:
    Microchip Technology Inc.

  File Name:
    drv_usart_variant_mapping.h

  Summary:
    USART Driver Variant Mapping

  Description:
    This file provides feature and build variant mapping
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

#ifndef _DRV_USART_FEATURE_MAPPING_H
#define _DRV_USART_FEATURE_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#if (true == DRV_USART_UNIFIED)

    #if !defined(DRV_USART_INSTANCES_NUMBER)

        #if !defined(DRV_USART_CLIENTS_NUMBER)

            /* Map macros and functions to the static single-open variants */
            #include "driver/usart/src/unified/static/drv_usart_hw_static.h"
            #include "driver/usart/src/unified/client_single/drv_usart_client_single.h"

        #else

            /* Map macros and functions to the static multi-open variants */
            #include "driver/usart/src/unified/static/drv_usart_hw_static.h"
            #include "driver/usart/src/unified/client_multi/drv_usart_client_multi.h"

        #endif

    #else // (DRV_USART_CONFIG_BUILD_TYPE == DRV_BUILD_TYPE_DYNAMIC)

            #include "driver/usart/src/unified/dynamic/drv_usart_hw_dynamic.h"
            #include "driver/usart/src/unified/client_multi/drv_usart_client_multi.h"

    #endif
#endif
// *****************************************************************************
// *****************************************************************************
// Section: Configuration Constant Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Line Control mode configuration constants

  Summary:
    Line Control mode configuration constants

  Description:
    These macros define the line control mode configuration constants
    - DRV_USART_LINE_CONTROL_8E1
    - DRV_USART_LINE_CONTROL_8E2
    - DRV_USART_LINE_CONTROL_8O1
    - DRV_USART_LINE_CONTROL_8O2
    - DRV_USART_LINE_CONTROL_8N1
    - DRV_USART_LINE_CONTROL_8N2
    - DRV_USART_LINE_CONTROL_9N1
 */


#define DRV_USART_LINE_CONTROL_8N1                      0
#define DRV_USART_LINE_CONTROL_8E1                      1
#define DRV_USART_LINE_CONTROL_8O1                      2
#define DRV_USART_LINE_CONTROL_9N1                      3
#define DRV_USART_LINE_CONTROL_8N2                      4
#define DRV_USART_LINE_CONTROL_8E2                      5
#define DRV_USART_LINE_CONTROL_8O2                      6


// *****************************************************************************
// *****************************************************************************
// Section: Feature Variant Mapping
// *****************************************************************************
// *****************************************************************************
/* Some variants are determined by hardware feature existence and some features
   are determined user configuration of the driver, and some variants are
   combination of the two above.
*/


// *****************************************************************************
/* PLIB ID Static Configuration Override

  Summary:
    Allows static override of the peripehral library ID

  Description:
    These macros allow the peripheral library ID to be statically overriden by
    the DRV_USART_PERIPHERAL_ID configuration macro, if it is defined.

    _DRV_USART_PERIPHERAL_ID_GET replaces the value passed in with the value defined by
    the DRV_USART_PERIPHERAL_ID configuration option.
*/

#if defined(DRV_USART_PERIPHERAL_ID)

    #define _DRV_USART_PERIPHERAL_ID_GET(plibID)                DRV_USART_PERIPHERAL_ID

#else

    #define _DRV_USART_PERIPHERAL_ID_GET(plibId)                ( plibId )

#endif

// *****************************************************************************
/* Interrupt Source Static Configuration Override

  Summary:
    Allows static override of the interrupt source

  Description:
    These macros allow the interrupt source to be statically overriden by the
    DRV_USART_INTERRUPT_SOURCE_TX configuration macro, if it is defined.

    _DRV_USART_GET_INT_SRC replaces the value passed in with the value defined by
    the DRV_USART_INTERRUPT_SOURCE_TX configuration option.

    _DRV_USART_STATIC_INT_SRC removes any statement passed into it from the build
    if the DRV_USART_INTERRUPT_SOURCE configuration option is defined.
*/

#if defined(DRV_USART_INTERRUPT_SOURCE_TX)

    /* Static access macros */
    #define _DRV_USART_GET_INT_SRC_TX(source)                DRV_USART_INTERRUPT_SOURCE_TX
    #define _DRV_USART_STATIC_INT_SRC_TX(any)

#else

    /* Dynamic access macros */
    #define _DRV_USART_GET_INT_SRC_TX(source)                source
    #define _DRV_USART_STATIC_INT_SRC_TX(any)                any

#endif

#if defined(DRV_USART_INTERRUPT_SOURCE_RX)

    /* Static access macros */
    #define _DRV_USART_GET_INT_SRC_RX(source)                DRV_USART_INTERRUPT_SOURCE_RX
    #define _DRV_USART_STATIC_INT_SRC_RX(any)

#else

    /* Dynamic access macros */
    #define _DRV_USART_GET_INT_SRC_RX(source)                source
    #define _DRV_USART_STATIC_INT_SRC_RX(any)                any

#endif

#if defined(DRV_USART_INTERRUPT_SOURCE_ERROR)

    /* Static access macros */
    #define _DRV_USART_GET_INT_SRC_ERROR(source)             DRV_USART_INTERRUPT_SOURCE_ERROR
    #define _DRV_USART_STATIC_INT_SRC_ERROR(any)

#else

    /* Dynamic access macros */
    #define _DRV_USART_GET_INT_SRC_ERROR(source)           source
    #define _DRV_USART_STATIC_INT_SRC_ERROR(any)           any

#endif

// *****************************************************************************
/*  void
    _DRV_USART_HW_ERROR ( statement )

  Summary:
    Macro which controls the presence of the statment based on the optional
    hardware features

  Description:
    Macro which controls the presence of the statment based on the optional
    hardware features

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_ERROR_INTERRUPT)

    #define _DRV_USART_ERROR_INT(statement)                  statement

#else

    #define _DRV_USART_ERROR_INT(statement)                  Nop()

#endif

// *****************************************************************************
/*  void
    _DRV_USART_LineControlModeSet ( index , lineControlMode, flowControl)

  Summary:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

  Description:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

  Remarks:
    None
*/

#define _DRV_USART_LineControlModeSet8N1(plibId, flowControl)                       \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8N1 |flowControl )

#define _DRV_USART_LineControlModeSet9N1(plibId, flowControl)        \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_9N1 |flowControl )

#define _DRV_USART_LineControlModeSet8E1(plibId, flowControl)        \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8E1 |flowControl )

#define _DRV_USART_LineControlModeSet8O1(plibId, flowControl)        \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8O1 |flowControl )

#define _DRV_USART_LineControlModeSet8E2(plibId, flowControl)        \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8E2 |flowControl )

#define _DRV_USART_LineControlModeSet8O2(plibId, flowControl)        \
        PLIB_USART_LineControlModeSelect (_DRV_USART_PERIPHERAL_ID_GET( plibId ), USART_8O2 |flowControl )

#if defined(DRV_USART_CONFIG_RECEIVER_9BIT_MODE_ENABLE) && defined(DRV_USART_CONFIG_TRANSMITTER_9BIT_MODE_ENABLE)

    #define _DRV_USART_LineControlModeSet8N1(plibId, flowControl)                       \
            (                                                                           \
                PLIB_USART_Transmitter9BitModeDisable(_DRV_USART_PERIPHERAL_ID_GET( plibId )),     \
                PLIB_USART_Receiver9BitModeDisable(_DRV_USART_PERIPHERAL_ID_GET( plibId ))      \
            )

    #define _DRV_USART_LineControlModeSet9N1(plibId, flowControl)                       \
            (                                                                           \
                PLIB_USART_Transmitter9BitModeEnable(_DRV_USART_PERIPHERAL_ID_GET( plibId )),     \
                PLIB_USART_Receiver9BitModeEnable(_DRV_USART_PERIPHERAL_ID_GET( plibId ))      \
            )

    #define _DRV_USART_LineControlModeSet8E1(plibId, flowControl)

    #define _DRV_USART_LineControlModeSet8O1(plibId, flowControl)

    #define _DRV_USART_LineControlModeSet8E2(plibId, flowControl)

    #define _DRV_USART_LineControlModeSet8O2(plibId, flowControl)

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Driver feature variant mapping
// *****************************************************************************
// *****************************************************************************
/* Mapping of the driver feature variant mapping
*/

// *****************************************************************************
/*  void _DRV_USART_FLOW_CONTROL( flowControl )

  Summary:
    Statically overrides the flow control

  Description:
    This macro statically overrides the flow control method used for RTS if the
    flow control was selected in the configuration.

  Remarks:
    Defining the following configurations has the following effects:

    Handshaking Configuration:

      * DRV_USART_HANDSHAKE_MODE_SIMPLEX - The driver uses the simplex
        method of flow control (data only travels in one direction at a time).

      * DRV_USART_HANDSHAKE_MODE_FLOWCONTROL - The driver uses RTS to
        manage flow control handshaking.

      * DRV_USART_HANDSHAKE_MODE_NONE - The driver does not use
        handshaking to manage flow control.
*/

#if     defined(DRV_USART_HANDSHAKE_MODE) && \
               (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_SIMPLEX)

    #define _DRV_USART_FLOW_CONTROL(flowControl)    USART_HANDSHAKE_MODE_SIMPLEX

#elif   defined(DRV_USART_HANDSHAKE_MODE) && \
               (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_FLOWCONTROL)

    #if defined(DRV_USART_CONFIG_FLOW_CONTROL_MODE)

            #define _DRV_USART_FLOW_CONTROL(flowControl)    USART_HANDSHAKE_MODE_FLOW_CONTROL

    #else

            #define _DRV_USART_FLOW_CONTROL(flowControl)    0

    #endif

#elif   defined(DRV_USART_HANDSHAKE_MODE) && \
               (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_NONE)

    #define _DRV_USART_FLOW_CONTROL(flowControl)    0

#elif   defined(DRV_USART_CONFIG_FLOW_CONTROL_MODE)

    #define _DRV_USART_FLOW_CONTROL(flowControl)    ( (flowControl) & (USART_HANDSHAKE_MODE_SIMPLEX | USART_HANDSHAKE_MODE_FLOW_CONTROL) )

#else

    #define _DRV_USART_FLOW_CONTROL(flowControl)    0

#endif


// *****************************************************************************
/*  void
    _DRV_USART_LineControlModeSet ( plibId , lineControlMode, flowControl )

  Summary:
    Sets up the configured line control mode

  Description:
    This macro sets up the line control mode selected during configuration.

  Remarks:
    Defining the following configurations has the following effects:

      * DRV_USART_LINE_CONTROL_8N1 - The driver uses 8 data bits, no
        parity, and 1 stop bit.

      * DRV_USART_LINE_CONTROL_9N1 - The driver uses 9 data bits, no
        parity, and 1 stop bit.

      * DRV_USART_LINE_CONTROL_8E1 - The driver uses 8 data bits, even
        parity, and 1 stop bit.

      * DRV_USART_LINE_CONTROL_8O1 - The driver uses 8 data bits, odd
        parity, and 1 stop bit.

      * DRV_USART_LINE_CONTROL_8E2 - The driver uses 8 data bits, even
        parity, and 2 stop bits.

      * DRV_USART_LINE_CONTROL_8O2 - The driver uses 8 data bits, odd
        parity, and 2 stop bits.

      * If none of the above line-control definitions is defined, then the line
        control mode must be set dynamically.
*/

#if defined(DRV_USART_LINE_CONTROL) && \
           (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_8N1)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet8N1(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#elif defined(DRV_USART_LINE_CONTROL) && \
             (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_9N1)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet9N1(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#elif defined(DRV_USART_LINE_CONTROL) && \
             (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_8E1)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet8E1(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#elif defined(DRV_USART_LINE_CONTROL) && \
             (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_8O1)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet8O1(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#elif defined(DRV_USART_LINE_CONTROL) && \
             (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_8E2)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet8E2(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#elif defined(DRV_USART_LINE_CONTROL) && \
             (DRV_USART_LINE_CONTROL == DRV_USART_LINE_CONTROL_8O2)

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSet8O2(plibId, _DRV_USART_FLOW_CONTROL(flowControl))

#else

    #define _DRV_USART_LineControlModeSet(plibId, lineControlMode, flowControl)     _DRV_USART_LineControlModeSetDyn(plibId, lineControlMode, _DRV_USART_FLOW_CONTROL(flowControl))

#endif


// *****************************************************************************
/*  void
    _DRV_USART_OperationModeSet ( plibId , handshakeMode)

  Summary:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

  Description:
    Sets up the line control mode of the hardware instance according to the
    features present in the device.

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_OPERATION_MODE_CONTROL)

    /* If static override is defined use it else use the dynamic value */
    #if defined(DRV_USART_HANDSHAKE_MODE) && \
               (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_FLOWCONTROL)

        #define _DRV_USART_OperationModeSet( plibId , handshakeMode )     PLIB_USART_OperationModeSelect(_DRV_USART_PERIPHERAL_ID_GET( plibId ) ,USART_ENABLE_TX_RX_RTS_USED)

    #elif defined(DRV_USART_HANDSHAKE_MODE) && \
                 (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_SIMPLEX)

        #define _DRV_USART_OperationModeSet( plibId , handshakeMode )     PLIB_USART_OperationModeSelect(_DRV_USART_PERIPHERAL_ID_GET( plibId ) ,USART_ENABLE_TX_RX_CTS_RTS_USED)

    #elif defined(DRV_USART_HANDSHAKE_MODE) && \
                 (DRV_USART_HANDSHAKE_MODE == DRV_USART_HANDSHAKE_MODE_NONE)

        #define _DRV_USART_OperationModeSet( plibId , handshakeMode )     PLIB_USART_OperationModeSelect(_DRV_USART_PERIPHERAL_ID_GET( plibId ) ,USART_ENABLE_TX_RX_USED)

    #else

        #define _DRV_USART_OperationModeSet( plibId , handshakeMode )     \
               ((handshakeMode == DRV_USART_HANDSHAKE_MODE_NONE)?PLIB_USART_OperationModeSelect( _DRV_USART_PERIPHERAL_ID_GET( plibId ) ,USART_ENABLE_TX_RX_USED):0)

    #endif

#else

    #define _DRV_USART_OperationModeSet( plibId , handshakeMode)

#endif


// *****************************************************************************
/*  void
    _DRV_USART_SyncMasterEnableMode ( plibId )

  Summary:
    Sets up the synchronous master mode

  Description:
    Sets up the synchronous master mode

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_SYNC_MODE_SELECT)                    &&          \
    defined(DRV_USART_OPERATION_MODE)              &&          \
    (DRV_USART_OPERATION_MODE == DRV_USART_OPERATION_MODE_SYNCMASTER)

    #define _DRV_USART_SyncMasterEnable(plibId)                             \
        (                                                                   \
            PLIB_USART_SyncModeSelect(_DRV_USART_PERIPHERAL_ID_GET(plibId)),          \
            PLIB_USART_SyncClockSourceMasterSelect(_DRV_USART_PERIPHERAL_ID_GET(plibId))   \
        )
#else

    #define _DRV_USART_SyncMasterEnable(plibId)

#endif


// *****************************************************************************
/*  void
    _DRV_USART_SyncSlaveEnableMode ( plibId )

  Summary:
    Sets up the synchronous slave mode

  Description:
    Sets up the synchronous slave mode

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_SYNC_MODE_SELECT)                    &&          \
    defined(DRV_USART_OPERATION_MODE)              &&          \
    (DRV_USART_OPERATION_MODE == DRV_USART_OPERATION_MODE_SYNCSLAVE)

    #define _DRV_USART_SyncSlaveEnable(plibId)               \
        (                                                                   \
            PLIB_USART_SyncModeSelect(_DRV_USART_PERIPHERAL_ID_GET(plibId)),          \
            PLIB_USART_SyncClockSourceSlaveSelect(_DRV_USART_PERIPHERAL_ID_GET(plibId))   \
        )

#else

    #define _DRV_USART_SyncSlaveEnable(plibId)

#endif

// *****************************************************************************
/*  void DRV_USART_BRG16BitModeSelect ( plibId )

  Summary:
    Sets up the BRG in the 16 bit mode

  Description:
    Sets up the BRG in the 16 bit mode

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_BRG_BIT_MODE_SELECT)

    #define _DRV_USART_BaudRate16BitModeSelect(plibId)               \
            PLIB_USART_BaudRate16BitModeSelect ( ( plibId ) );

#else

    #define _DRV_USART_BaudRate16BitModeSelect(plibId)

#endif


// *****************************************************************************
/*  void _DRV_USART_RXPolarityInverted ( plibId )

  Summary:
    Sets up the inverted RX polarity

  Description:
    Sets up the inverted RX polarity

  Remarks:
    None
 */

#if defined( DRV_USART_CONFIG_RECEIVER_POLARITY)

    #if defined(DRV_USART_POLARITY_INVERTED_RX)          &&      \
               (DRV_USART_POLARITY_INVERTED_RX  == true)

        #define _DRV_USART_RXPolarityInverted(plibId)                   \
                PLIB_USART_ReceiverPolarityInvertEnable ( _DRV_USART_PERIPHERAL_ID_GET( plibId ) );

    #elif defined(DRV_USART_POLARITY_INVERTED_RX)          &&      \
               (DRV_USART_POLARITY_INVERTED_RX  == false)

        #define _DRV_USART_RXPolarityInverted(plibId)                   \
                PLIB_USART_ReceiverPolarityInvertDisable ( _DRV_USART_PERIPHERAL_ID_GET( plibId ) );

    #else

        #define _DRV_USART_RXPolarityInverted(plibId)

    #endif

#else

    #define _DRV_USART_RXPolarityInverted(plibId)

#endif


// *****************************************************************************
/*  void   _DRV_USART_TXPolarityInverted ( plibId )

  Summary:
    Sets up the inverted TX polarity

  Description:
    Sets up the inverted TX polarity

  Remarks:
    None
 */

#if defined( DRV_USART_CONFIG_TRANSMITTER_POLARITY)

    #if defined(DRV_USART_POLARITY_INVERTED_TX)          &&      \
               (DRV_USART_POLARITY_INVERTED_TX  == true)

        #define _DRV_USART_TXPolarityInverted(plibId)                   \
                PLIB_USART_TransmitterIdleIsLowEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) );

    #elif defined(DRV_USART_POLARITY_INVERTED_TX)          &&      \
               (DRV_USART_POLARITY_INVERTED_TX  == false)

        #define _DRV_USART_TXPolarityInverted(plibId)                   \
                PLIB_USART_TransmitterIdleIsLowDisable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) );

    #else

        #define _DRV_USART_TXPolarityInverted(plibId)

    #endif

#else

    #define _DRV_USART_TXPolarityInverted(plibId)

#endif

// *****************************************************************************
/*  void _DRV_USART_StopInIdleMode ( plibId , usartInit )

  Summary:
    Sets up the stop in idle enable

  Description:
    Sets up the stop in idle enable

  Remarks:
    None
 */

#if defined( DRV_USART_CONFIG_STOP_IN_IDLE_ENABLE)

    #if defined(DRV_USART_POWER_STATE) && \
               ( DRV_USART_POWER_STATE == SYS_MODULE_POWER_IDLE_STOP )

        #define _DRV_USART_PowerState(index , usartInit)   PLIB_USART_StopInIdleEnable( _DRV_USART_PERIPHERAL_ID_GET(index) )

    #elif  defined(DRV_USART_POWER_STATE) && \
                  ( (DRV_USART_POWER_STATE == SYS_MODULE_POWER_IDLE_RUN) || \
                    (DRV_USART_POWER_STATE == SYS_MODULE_POWER_RUN_FULL))

        #define _DRV_USART_PowerState(index , usartInit)   PLIB_USART_StopInIdleDisable( _DRV_USART_PERIPHERAL_ID_GET(index) )

    #else

        #define _DRV_USART_PowerState(index , usartInit )  \
                    ( ( _DRV_USART_POWER_STATE_GET(usartInit->moduleInit.sys.powerState) == SYS_MODULE_POWER_IDLE_STOP ) ? \
                        PLIB_USART_StopInIdleEnable( _DRV_USART_PERIPHERAL_ID_GET( index ) ) :        \
                        0 )
    #endif

#else

    #define _DRV_USART_PowerState(index , usartInit)

#endif


// *****************************************************************************
/*  void _DRV_USART_WakeOnStartSetup ( plibId )

  Summary:
    Sets up the stop in idle enable

  Description:
    Sets up the stop in idle enable

  Remarks:
    None
 */

#if defined( DRV_USART_CONFIG_WAKE_ON_START_ENABLE)

    #if defined(DRV_USART_WAKE_ON_START_ENABLE) && \
               (DRV_USART_WAKE_ON_START_ENABLE == true)

        #define _DRV_USART_WakeOnStartSetup( plibId , usartInit ) PLIB_USART_WakeOnStartEnable(_DRV_USART_PERIPHERAL_ID_GET( plibId ) )

    #elif defined(DRV_USART_WAKE_ON_START_ENABLE) && \
               (DRV_USART_WAKE_ON_START_ENABLE == false)

        #define _DRV_USART_WakeOnStartSetup( plibId , usartInit )

    #else

        #define _DRV_USART_WakeOnStartSetup( plibId , usartInit )                         \
        (                                                               \
            ((usartInit->initFlags & DRV_USART_INIT_FLAG_WAKE_ON_START_ENABLE)?PLIB_USART_WakeOnStartEnable(_DRV_USART_PERIPHERAL_ID_GET( plibId ) ):0)\
        )

    #endif

#else

    #define _DRV_USART_WakeOnStartSetup( plibId , usartInit )

#endif


// *****************************************************************************
/*  void _DRV_USART_RXAutoAddressEnable ( plibId )

  Summary:
    Sets up the auto address detect enable

  Description:
    Sets up the auto address detect enable

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_RECEIVER_AUTO_ADDRESS_DETECT_ENABLE) &&          \
    defined(DRV_USART_OPERATION_MODE)              &&          \
    (DRV_USART_OPERATION_MODE == DRV_USART_OPERATION_MODE_RS485)


    #define _DRV_USART_RXAutoAddressEnable( plibId , usartInit)     \
            PLIB_USART_ReceiverAutomaticAddressDetectEnable ( _DRV_USART_PERIPHERAL_ID_GET( plibId ),usartInit->operationModeInit.RS485Init.address )

#else

    #define _DRV_USART_RXAutoAddressEnable( plibId , usartInit )

#endif


// *****************************************************************************
/*  void _DRV_USART_IrDAEnable ( plibId )

  Summary:
    Sets up the auto address detect enable

  Description:
    Sets up the auto address detect enable

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_IRDA_ENABLE) &&                                  \
    defined(DRV_USART_OPERATION_MODE)              &&          \
    (DRV_USART_OPERATION_MODE == DRV_USART_OPERATION_MODE_IRDA)

    #define _DRV_USART_IrDAEnable( plibId )                               \
            (\
                PLIB_USART_IrDAEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) ),\
                PLIB_USART_OperationModeSelect ( _DRV_USART_PERIPHERAL_ID_GET( plibId ),USART_ENABLE_TX_RX_BCLK_USED ) \
            )

#else

    #define _DRV_USART_IrDAEnable( plibId )

#endif



// *****************************************************************************
/*  void _DRV_USART_AutoBaudSetup ( plibId , usartInit )

  Summary:
    Sets up the auto baud

  Description:
    Sets up the auto baud

  Remarks:
    None
 */

#if defined( DRV_USART_CONFIG_AUTO_BAUD)

    #if defined(DRV_USART_AUTO_BAUD_ENABLE) && \
               (DRV_USART_AUTO_BAUD_ENABLE == true)

        #define _DRV_USART_AutoBaudSetup(plibId , usartInit )     PLIB_USART_BaudRateAutoDetectEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) )

    #elif defined(DRV_USART_AUTO_BAUD_ENABLE) && \
               (DRV_USART_AUTO_BAUD_ENABLE == false)

        #define _DRV_USART_AutoBaudSetup(plibId , usartInit )

    #else

        #define _DRV_USART_AutoBaudSetup(plibId , usartInit )                \
               ((usartInit->initFlags & DRV_USART_INIT_FLAG_AUTO_BAUD_ENABLE)?PLIB_USART_BaudRateAutoDetectEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) ):0)

    #endif

#else

    #define _DRV_USART_AutoBaudSetup( plibId , usartInit )

#endif


// *****************************************************************************
/*  void  _DRV_USART_LoopbackEnable ( plibId , moduleIndex)

  Summary:
    Enables the loopback mode is enabled for hte hardware instance.

  Description:
    Enables the loopback mode is enabled for hte hardware instance.

  Remarks:
    None
 */

#if defined(DRV_USART_CONFIG_LOOPBACK_ENABLE)

    #if defined(DRV_USART_OPERATION_MODE)              &&          \
               (DRV_USART_OPERATION_MODE == DRV_USART_OPERATION_MODE_LOOPBACK)

        #define _DRV_USART_LoopbackEnable( plibId , moduleIndex)    PLIB_USART_LoopbackEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) )

        #define _DRV_USART_SetupLoopbackOperation(usartInit, dObj)  ( (dObj->operationalFlags)  |= DRV_USART_OPERATIONAL_FLAG_LOOPBACK )

    #else

        #define _DRV_USART_LoopbackEnable( plibId , dObj )                                              \
                (                                                                                       \
                    ((dObj->operationalFlags) & DRV_USART_OPERATIONAL_FLAG_LOOPBACK) ?    \
                        PLIB_USART_LoopbackEnable( _DRV_USART_PERIPHERAL_ID_GET( plibId ) ) :                     \
                        0                                                                               \
                )

        #define _DRV_USART_SetupLoopbackOperation(usartInit, dObj)                                              \
                (                                                                                               \
                    (usartInit->operationMode & DRV_USART_OPERATION_MODE_LOOPBACK) ?                            \
                        ( (dObj->operationalFlags)  |= DRV_USART_OPERATIONAL_FLAG_LOOPBACK ) :    \
                        0                                                                                       \
                )
    #endif

#else

    #define _DRV_USART_LoopbackEnable( plibId , moduleIndex)

    #define _DRV_USART_SetupLoopbackOperation(usartInit, dObj)

#endif

// *****************************************************************************
/*  void  _DRV_USART_ReadyToTransmit ( plibId , interruptSource)

  Summary:
    Provides the required mapping to the ready to transmit check status

  Description:
    Provides the required mapping to the ready to transmit check status

  Remarks:
    None
 */

#if defined(__XC16__)

#define _DRV_USART_ReadyToTransmit( plibId, interruptSource )  (PLIB_USART_TransmitterIsEmpty ( plibId ))

#else

#define _DRV_USART_ReadyToTransmit( plibId, interruptSource ) SYS_INT_SourceStatusGet( interruptSource )

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Interrrupt Variations
// *****************************************************************************
// *****************************************************************************
/* Mapping of the interrupt mode variations
*/


#if defined (DRV_USART_INTERRUPT_MODE) && \
            (DRV_USART_INTERRUPT_MODE == true)

    #define _DRV_USART_InterruptSourceEnabled(source)       SYS_INT_SourceIsEnabled( source )

    #define _DRV_USART_InterruptSourceEnable(source)        SYS_INT_SourceEnable( source )

    #define _DRV_USART_InterruptSourceDisable(source)       SYS_INT_SourceDisable( source )

    #define _DRV_USART_InterruptSourceStatusClear(source)   SYS_INT_SourceStatusClear( source )


#elif defined (DRV_USART_INTERRUPT_MODE) && \
              (DRV_USART_INTERRUPT_MODE == false)

    #define _DRV_USART_InterruptSourceEnabled(source)       false

    #define _DRV_USART_InterruptSourceEnable(source)

    #define _DRV_USART_InterruptSourceDisable(source)

    #define _DRV_USART_InterruptSourceStatusClear(source)       SYS_INT_SourceStatusClear( source )


#else

    #error "No Task mode chosen at build, interrupt or polling needs to be selected. "

#endif

// *****************************************************************************
// *****************************************************************************
// Initializtion Parameter Static Overrides
// *****************************************************************************
// *****************************************************************************


#if defined(DRV_USART_BAUD_RATE)

    #define     _DRV_USART_BAUD_RATE_GET(baudRate) DRV_USART_BAUD_RATE

#else

    #define     _DRV_USART_BAUD_RATE_GET(baudRate) baudRate

#endif


// *****************************************************************************
/* Static override for line control

  Summary:
 Enables a static override for Line Control

  Description:
    TODO

   Remarks:
    TODO
*/

#if defined(DRV_USART_LINE_CONTROL)

    #define _DRV_USART_LINE_CONTROL_GET(arg)                         DRV_USART_LINE_CONTROL

#else

    #define _DRV_USART_LINE_CONTROL_GET(arg)                         (arg)

#endif


// *****************************************************************************
/* TODO

  Summary:
    TODO

  Description:
    TODO

   Remarks:
    TODO
*/

#if defined(DRV_USART_HANDSHAKE_MODE)

    #define _DRV_USART_HANDSHAKE_MODE_GET(arg)                         DRV_USART_HANDSHAKE_MODE

#else

    #define _DRV_USART_HANDSHAKE_MODE_GET(arg)                         (arg)

#endif

#endif //_DRV_USART_FEATURE_MAPPING_H

/*******************************************************************************
 End of File
*/
