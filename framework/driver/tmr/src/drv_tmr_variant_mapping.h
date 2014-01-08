/*******************************************************************************
  Timer Driver Feature Variant Implementations

  Company:
    Microchip Technology Inc.

  File Name:
    drv_tmr_variant_mapping.h

  Summary:
    Timer driver feature variant implementations.

  Description:
    This file implements the functions which differ based on different devices
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


#ifndef _DRV_TMR_VARIANT_MAPPING_H
#define _DRV_TMR_VARIANT_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#if (true == DRV_TMR_UNIFIED)
    #if !defined(DRV_TMR_INSTANCES_NUMBER)

        /* Map internal macros and functions to the static single open variant */
        #include "driver/tmr/src/static/drv_tmr_hw_static.h"
        #include "driver/tmr/src/client_single/drv_tmr_client_single.h"

    #else // (DRV_TMR_INSTANCES_NUMBER > 1)

        /* Map internal macros and functions to the dynamic variant */
        #include "driver/tmr/src/dynamic/drv_tmr_hw_dynamic.h"
        #include "driver/tmr/src/client_multi/drv_tmr_client_multi.h"

    #endif

#endif


// *****************************************************************************
// *****************************************************************************
// Section: Timer Driver Static Object Generation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_TMR_OBJ_MAKE_NAME(name)

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

#define _DRV_TMR_OBJ_MAKE_NAME(name)        _DRV_STATIC_OBJ_NAME_A(name, DRV_TMR_INDEX)


// *****************************************************************************
// *****************************************************************************
// Section: Symbolic Constants
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Feature Variant Mapping
// *****************************************************************************
// *****************************************************************************
/* Some variants are determined by hardware feature existence, some features
   are determined user configuration of the driver, and some variants are
   combination of the two.
*/


// *****************************************************************************
/* Peripheral Library ID Static Configuration Override

  Summary:
    Allows static override of the peripehral library ID.

  Description:
    These macros allow the peripheral library ID to be statically overriden by 
    the DRV_TMR_PERIPHERAL_ID configuration macro, if it is defined.
    
    _DRV_TMR_PERIPHERAL_ID_GET replaces the value passed in with the value defined by
    the DRV_TMR_PERIPHERAL_ID configuration option.
    
    _DRV_TMR_STATIC_PLIB_ID removes any statement passed into it from the build
    if the DRV_TMR_PERIPHERAL_ID configuration option is defined.
*/

#if defined(DRV_TMR_PERIPHERAL_ID)

    #define _DRV_TMR_PERIPHERAL_ID_GET(plibId)      DRV_TMR_PERIPHERAL_ID
    #define _DRV_TMR_STATIC_PLIB_ID(any)

#else

    #define _DRV_TMR_PERIPHERAL_ID_GET(plibId)      plibId
    #define _DRV_TMR_STATIC_PLIB_ID(any)            any

#endif


// *****************************************************************************
/* Interrupt Source Static Configuration Override

  Summary:
    Allows static override of the interrupt source.

  Description:
    These macros allow the interrupt source to be statically overriden by the 
    DRV_TMR_INTERRUPT_SOURCE configuration macro, if it is defined.
    
    _DRV_TMR_GET_INT_SRC replaces the value passed in with the value defined by
    the DRV_TMR_INTERRUPT_SOURCE configuration option.
    
    _DRV_TMR_STATIC_INT_SRC removes any statement passed into it from the build
    if the DRV_TMR_INTERRUPT_SOURCE configuration option is defined.
*/

#if defined(DRV_TMR_INTERRUPT_SOURCE)

    #define _DRV_TMR_INT_SRC_GET(source)    DRV_TMR_INTERRUPT_SOURCE
    #define _DRV_TMR_STATIC_INT_SRC(any)

#else

    #define _DRV_TMR_INT_SRC_GET(source)    source
    #define _DRV_TMR_STATIC_INT_SRC(any)    any

#endif


// *****************************************************************************
/* Interrupt Source Control

  Summary:
    Macros to enable, disable or clear the interrupt source.

  Description:
    These macros enable, disable, or clear the interrupt source

    These macros get mapped to the respective SYS module APIs if the configuration
    option DRV_TMR_INTERRUPT_MODE is set to true.
 
  Remarks:
    These macros are mandatory
*/

#if defined (DRV_TMR_INTERRUPT_MODE)

    #if(DRV_TMR_INTERRUPT_MODE == true)

        #define _DRV_TMR_InterruptSourceEnable(source)          SYS_INT_SourceEnable( source )
        #define _DRV_TMR_InterruptSourceDisable(source)         SYS_INT_SourceDisable( source )
        #define _DRV_TMR_InterruptSourceClear(source)           SYS_INT_SourceStatusClear( source )

        #define _DRV_TMR_InterruptSourceStatusGet(source)       SYS_INT_SourceStatusGet( source )

    #elif (DRV_TMR_INTERRUPT_MODE == false)

        #define _DRV_TMR_InterruptSourceEnable(source)
        #define _DRV_TMR_InterruptSourceDisable(source)
        #define _DRV_TMR_InterruptSourceClear(source)           SYS_INT_SourceStatusClear( source )

        #define _DRV_TMR_InterruptSourceStatusGet(source)       SYS_INT_SourceStatusGet( source )

    #else

        #error "No Task mode chosen at build, interrupt or polling needs to be selected. "

    #endif

#else

    #error "No Task mode chosen at build, interrupt or polling needs to be selected. "

#endif



// *****************************************************************************
/* Macro:
    _DRV_TMR_PeriodSet

  Summary:
    Sets the period value using the configured Timer bit-width mode.

  Description:
    This macro sets the period value using the Timer bit-width mode
    configured at build time.
  
     - Option DRV_TMR_COUNT_WIDTH = 8 selects 8-bit Timer mode

     - Option DRV_TMR_COUNT_WIDTH = 16 selects 16-bit Timer mode

     - Option DRV_TMR_COUNT_WIDTH = 32 selects 32-bit Timer mode

  Remarks:
    One of the above must be defined at build time.
*/

#if defined (DRV_TMR_COUNT_WIDTH)

    #if( DRV_TMR_COUNT_WIDTH == 8 )

        #define _DRV_TMR_PeriodSet(index, value)    \
                (                                   \
                    PLIB_TMR_Period8BitSet( _DRV_TMR_PERIPHERAL_ID_GET(index), (uint8_t)value ) \
                )

    #elif( DRV_TMR_COUNT_WIDTH == 16 )

        #define _DRV_TMR_PeriodSet(index, value)    \
                (                                   \
                    PLIB_TMR_Period16BitSet( _DRV_TMR_PERIPHERAL_ID_GET(index), (uint16_t)value ) \
                )

    #elif( DRV_TMR_COUNT_WIDTH == 32 )

        #define _DRV_TMR_PeriodSet(index, value)    \
                (                                   \
                    PLIB_TMR_Period32BitSet( _DRV_TMR_PERIPHERAL_ID_GET(index), (uint32_t)value ) \
                )

    #else

        #error "No timer bit-width selected. "

    #endif

#else

    #error "No timer bit-width selected. "

#endif


// *****************************************************************************
/* Macro:
    _DRV_TMR_SyncModeAsyncExtWithoutClockSync

  Summary:
    Disables synchronization with an external clock when the appropriate Timer
    bit-width mode has been configured.

  Description:
    This macro disables synchronization with an external clock when an
    appropriate timer bit-width mode has been configured.

    Note:  External clock synchronization is only appropriate when configured
           in 16-bit mode.

  Remarks:
    None.
*/

#if defined (DRV_TMR_COUNT_WIDTH)

    #if( DRV_TMR_COUNT_WIDTH == 8 )

        #define _DRV_TMR_SyncModeAsyncExtWithoutClockSync(index)

    #elif( DRV_TMR_COUNT_WIDTH == 16 )

        #define _DRV_TMR_SyncModeAsyncExtWithoutClockSync(index)  _DRV_TMR_ExternalClockSyncDisable(_DRV_TMR_PERIPHERAL_ID_GET(index))

    #elif( DRV_TMR_COUNT_WIDTH == 32 )

        #define _DRV_TMR_SyncModeAsyncExtWithoutClockSync(index)

    #else

        #error "No timer bit-width selected. "

    #endif

#else

    #error "No timer bit-width selected. "

#endif

// *****************************************************************************
/* Macro:
    _DRV_TMR_SyncModeAsyncExtWithClockSync

  Summary:
    Enables synchronization with an external clock when the appropriate Timer
    bit-width mode has been configured.

  Description:
    This macro enables synchronization with an external clock when an
    appropriate timer bit-width mode has been configured.
    
    Note:  External clock synchronization is only appropriate when configured
           in 16-bit mode.

  Remarks:
    None.
*/

#if defined (DRV_TMR_COUNT_WIDTH)

    #if( DRV_TMR_COUNT_WIDTH == 8 )

        #define _DRV_TMR_SyncModeAsyncExtWithClockSync(index)

    #elif( DRV_TMR_COUNT_WIDTH == 16 )

        #define _DRV_TMR_SyncModeAsyncExtWithClockSync(index)     _DRV_TMR_ExternalClockSyncEnable(_DRV_TMR_PERIPHERAL_ID_GET(index))

    #elif( DRV_TMR_COUNT_WIDTH == 32 )

        #define _DRV_TMR_SyncModeAsyncExtWithClockSync(index)

    #else

        #error "No timer bit-width mode selected. "

    #endif

#else

    #error "No timer bit-width selected. "

#endif

// *****************************************************************************
/* Alarm feature variable declaration macros

  Summary:
    Macros to declare the alarm members of the driver

  Description:
    These macros enable the alarm members presence in the driver objects.

    The configuration option DRV_TMR_ALARM_ENABLE enables them to do so.

  Remarks:
    None
*/

#if defined (DRV_TMR_ALARM_ENABLE)

    #define _DRV_TMR_DECLARE_ALARM_COUNTER(countDeclare)    countDeclare
    #define _DRV_TMR_DECLARE_ALARM_CALLBACK(cbDeclare)      cbDeclare
    #define _DRV_TMR_DECLARE_ALARM_FLAG(declare)            declare

#else // (!DRV_TMR_ALARM_ENABLE)

    #define _DRV_TMR_DECLARE_ALARM_COUNTER(countDeclare)
    #define _DRV_TMR_DECLARE_ALARM_CALLBACK(cbDeclare)
    #define _DRV_TMR_DECLARE_ALARM_FLAG(declare)

#endif


// *****************************************************************************
// *****************************************************************************
// Initializtion Parameter Static Overrides
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Sync mode Static Configuration Override

  Summary:
    Allows static override of the sync mode.

  Description:
    These macros allow the sync mode to be statically overriden by
    the DRV_TMR_SYNCHRONIZATION_MODE configuration macro, if it is defined.

    _DRV_TMR_SYNC_MODE_GET replaces the value passed in with the value defined by
    the DRV_TMR_SYNCHRONIZATION_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_SYNCHRONIZATION_MODE)

    #define _DRV_TMR_SYNC_MODE_GET(arg)                     DRV_TMR_SYNCHRONIZATION_MODE

#else

    #define _DRV_TMR_SYNC_MODE_GET(mode)                    (mode)

#endif


// *****************************************************************************
/* TMR period Static Configuration Override

  Summary:
    Allows static override of the Timer period.

  Description:
    These macros allow the Timer period to be statically overriden by
    the DRV_TMR_TIMER_PERIOD configuration macro, if it is defined.

    _DRV_TMR_VALUE_GET replaces the value passed in with the value defined by
    the DRV_TMR_TIMER_PERIOD configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_TIMER_PERIOD)

    #define _DRV_TMR_VALUE_GET(arg)                             DRV_TMR_TIMER_PERIOD

#else

    #define _DRV_TMR_VALUE_GET(arg)                             (arg)

#endif


// *****************************************************************************
/* Clock source Static Configuration Override

  Summary:
    Allows static override of the clock source.

  Description:
    These macros allow the clock source to be statically overriden by
    the DRV_TMR_CLOCK_SOURCE configuration macro, if it is defined.

    _DRV_TMR_CLOCK_SOURCE_GET replaces the value passed in with the value defined by
    the DRV_TMR_CLOCK_SOURCE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_CLOCK_SOURCE)

    #define _DRV_TMR_CLOCK_SOURCE_GET(arg)                      DRV_TMR_CLOCK_SOURCE

#else

    #define _DRV_TMR_CLOCK_SOURCE_GET(arg)                      (arg)

#endif


// *****************************************************************************
/* Prescale Static Configuration Override

  Summary:
    Allows static override of the prescale.

  Description:
    These macros allow the prescale to be statically overriden by
    the DRV_TMR_PRESCALE configuration macro, if it is defined.

    _DRV_TMR_PRESCALE_GET replaces the value passed in with the value defined by
    the DRV_TMR_PRESCALE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_PRESCALE)

    #define _DRV_TMR_PRESCALE_GET(arg)                          DRV_TMR_PRESCALE

#else

    #define _DRV_TMR_PRESCALE_GET(arg)                          (arg)

#endif


// *****************************************************************************
/* Source edge Static Configuration Override

  Summary:
    Allows static override of the source edge.

  Description:
    These macros allow the prescale to be statically overriden by
    the DRV_TMR_PRESCALE configuration macro, if it is defined.

    _DRV_TMR_PRESCALE_GET replaces the value passed in with the value defined by
    the DRV_TMR_PRESCALE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_SOURCE_EDGE)

    #define _DRV_TMR_SOURCE_EDGE_GET(arg)                       DRV_TMR_SOURCE_EDGE

#else

    #define _DRV_TMR_SOURCE_EDGE_GET(arg)                       (arg)

#endif


// *****************************************************************************
/* Postscale Static Configuration Override

  Summary:
    Allows static override of the postscale.

  Description:
    These macros allow the postscale to be statically overriden by
    the DRV_TMR_POSTSCALE configuration macro, if it is defined.

    _DRV_TMR_POSTSCALE_GET replaces the value passed in with the value defined by
    the DRV_TMR_POSTSCALE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_POSTSCALE)

    #define _DRV_TMR_POSTSCALE_GET(arg)                         DRV_TMR_POSTSCALE

#else

    #define _DRV_TMR_POSTSCALE_GET(arg)                         (arg)

#endif


// *****************************************************************************
/* Power mode Configuration Override

  Summary:
    Allows static override of the Power mode.

  Description:
    These macros allow the Power mode to be statically overriden by
    the DRV_TMR_CONFIG_INIT_POWER_MODE configuration macro, if it is defined.

    _DRV_TMR_POWER_STATE_GET replaces the value passed in with the value defined by
    the DRV_TMR_CONFIG_INIT_POWER_MODE configuration option.

   Remarks:
    None.
*/

#if defined(DRV_TMR_POWER_STATE)

    #define _DRV_TMR_POWER_STATE_GET(arg)                         DRV_TMR_POWER_STATE

#else

    #define _DRV_TMR_POWER_STATE_GET(arg)                         (arg)

#endif


#endif //_DRV_TMR_VARIANT_MAPPING_H

/*******************************************************************************
 End of File
*/

