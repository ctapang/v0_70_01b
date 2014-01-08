/* Created by plibgen $Revision: 1.29 $ */

#ifndef _DEVCON_P32MX320F128H_H
#define _DEVCON_P32MX320F128H_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/peripheral_common_32bit.h"

/* Default definition used for all API dispatch functions */
#ifndef INLINE_API
    #define INLINE_API extern inline
#endif

/* Default definition used for all other functions */
#ifndef INLINE
    #define INLINE extern inline
#endif

typedef enum {

    DEVCON_NUMBER_OF_MODULES

} DEVCON_MODULE_ID;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_AlternateClockEnable(DEVCON_MODULE_ID index, DEVCON_ALT_CLOCK_TARGET targetAltClock)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_AlternateClockDisable(DEVCON_MODULE_ID index, DEVCON_ALT_CLOCK_TARGET targetAltClock)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsAlternateClock(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_DeviceRegistersLock(DEVCON_MODULE_ID index, DEVCON_REGISTER_SET registersToLock)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_DeviceRegistersUnlock(DEVCON_MODULE_ID index, DEVCON_REGISTER_SET registersToLock)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsDeviceRegsLockUnlock(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_USBPHYSleepModeSet(DEVCON_MODULE_ID index, DEVCON_USB_SLEEP_MODE sleepOrRun)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsUSB_PHY_SleepModeSet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_FlashErrCorrectionModeSet(DEVCON_MODULE_ID index, DEVCON_ECC_CONFIG flashECC)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsECCModes(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_JTAGPortEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_JTAGPortDisable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsJTAGEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_TraceOutputEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_TraceOutputDisable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsTraceOutput(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_2WireJTAGEnableTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_2WireJTAGDisableTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsJTAGUsesTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_IgnoreDebugFreezeEnable(DEVCON_MODULE_ID index, DEVCON_DEBUG_PERIPHERAL myPeripheral)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_IgnoreDebugFreezeDisable(DEVCON_MODULE_ID index, DEVCON_DEBUG_PERIPHERAL myPeripheral)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsIgnoreDebugFreeze(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_DEVCON_DeviceVersionGet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DEVCON_DeviceIdGet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsDeviceVerAndId(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
