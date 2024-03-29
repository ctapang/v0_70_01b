/* Created by plibgen $Revision: 1.29 $ */

#ifndef _DEVCON_P32MZ1024ECM064_H
#define _DEVCON_P32MZ1024ECM064_H

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

    DEVCON_ID_0 = 0,
    DEVCON_NUMBER_OF_MODULES

} DEVCON_MODULE_ID;

INLINE SFR_TYPE* _DEVCON_IC_ALT_CLOCK_SELECT_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_OC_ALT_CLOCK_SELECT_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_PPS_LOCK_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_PMD_LOCK_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_PERMISSION_GROUP_LOCK_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_USB_SUSPEND_SLEEP_ENABLE_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_ECC_CONFIGURATION_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_JTAG_ENABLE_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_TRACE_OUTPUT_ENABLE_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_JTAG_TDO_USE_ENABLE_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &CFGCON;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_DEVICE_REVISION_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &DEVID;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DEVCON_DEVICE_ID_VREG(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return &DEVID;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _DEVCON_IC_ALT_CLOCK_SELECT_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ICACLK_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_OC_ALT_CLOCK_SELECT_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_OCACLK_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PPS_LOCK_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_IOLOCK_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PMD_LOCK_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PMDLOCK_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PERMISSION_GROUP_LOCK_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PGLOCK_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_USB_SUSPEND_SLEEP_ENABLE_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_USBSSEN_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_ECC_CONFIGURATION_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ECCCON_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_ENABLE_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_JTAGEN_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_TRACE_OUTPUT_ENABLE_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TROEN_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_TDO_USE_ENABLE_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TDOEN_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_REVISION_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_VER_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_ID_MASK(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_DEVID_MASK;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_IC_ALT_CLOCK_SELECT_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ICACLK_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_OC_ALT_CLOCK_SELECT_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_OCACLK_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PPS_LOCK_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_IOLOCK_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PMD_LOCK_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PMDLOCK_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PERMISSION_GROUP_LOCK_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PGLOCK_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_USB_SUSPEND_SLEEP_ENABLE_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_USBSSEN_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_ECC_CONFIGURATION_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ECCCON_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_ENABLE_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_JTAGEN_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_TRACE_OUTPUT_ENABLE_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TROEN_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_TDO_USE_ENABLE_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TDOEN_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_REVISION_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_VER_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_ID_POS(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_DEVID_POSITION;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_IC_ALT_CLOCK_SELECT_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ICACLK_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_OC_ALT_CLOCK_SELECT_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_OCACLK_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PPS_LOCK_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_IOLOCK_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PMD_LOCK_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PMDLOCK_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_PERMISSION_GROUP_LOCK_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_PGLOCK_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_USB_SUSPEND_SLEEP_ENABLE_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_USBSSEN_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_ECC_CONFIGURATION_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_ECCCON_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_ENABLE_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_JTAGEN_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_TRACE_OUTPUT_ENABLE_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TROEN_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_JTAG_TDO_USE_ENABLE_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _CFGCON_TDOEN_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_REVISION_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_VER_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DEVCON_DEVICE_ID_LEN(DEVCON_MODULE_ID i)
{
    switch (i) {
        case DEVCON_ID_0 :
            return _DEVID_DEVID_LENGTH;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/devcon_AlternateClock_Default.h"
#include "../templates/devcon_DeviceRegsLockUnlock_PIC32MZ.h"
#include "../templates/devcon_USB_PHY_SleepModeSet_Default.h"
#include "../templates/devcon_ECCModes_Default.h"
#include "../templates/devcon_JTAGEnable_Default.h"
#include "../templates/devcon_TraceOutput_Default.h"
#include "../templates/devcon_JTAGUsesTDO_Default.h"
#include "../templates/devcon_IgnoreDebugFreeze_Unsupported.h"
#include "../templates/devcon_DeviceVerAndId_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_DEVCON_AlternateClockEnable(DEVCON_MODULE_ID index, DEVCON_ALT_CLOCK_TARGET targetAltClock)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_AlternateClockEnable_Default(index, targetAltClock);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DEVCON_AlternateClockDisable(DEVCON_MODULE_ID index, DEVCON_ALT_CLOCK_TARGET targetAltClock)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_AlternateClockDisable_Default(index, targetAltClock);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsAlternateClock(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsAlternateClock_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_DeviceRegistersLock(DEVCON_MODULE_ID index, DEVCON_REGISTER_SET registersToLock)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_DeviceRegistersLock_PIC32MZ(index, registersToLock);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DEVCON_DeviceRegistersUnlock(DEVCON_MODULE_ID index, DEVCON_REGISTER_SET registersToLock)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_DeviceRegistersUnlock_PIC32MZ(index, registersToLock);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsDeviceRegsLockUnlock(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsDeviceRegsLockUnlock_PIC32MZ(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_USBPHYSleepModeSet(DEVCON_MODULE_ID index, DEVCON_USB_SLEEP_MODE sleepOrRun)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_USBPHYSleepModeSet_Default(index, sleepOrRun);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsUSB_PHY_SleepModeSet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsUSB_PHY_SleepModeSet_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_FlashErrCorrectionModeSet(DEVCON_MODULE_ID index, DEVCON_ECC_CONFIG flashECC)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_FlashErrCorrectionModeSet_Default(index, flashECC);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsECCModes(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsECCModes_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_JTAGPortEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_JTAGPortEnable_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DEVCON_JTAGPortDisable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_JTAGPortDisable_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsJTAGEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsJTAGEnable_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_TraceOutputEnable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_TraceOutputEnable_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DEVCON_TraceOutputDisable(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_TraceOutputDisable_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsTraceOutput(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsTraceOutput_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DEVCON_2WireJTAGEnableTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_2WireJTAGEnableTDO_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DEVCON_2WireJTAGDisableTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_2WireJTAGDisableTDO_Default(index);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsJTAGUsesTDO(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsJTAGUsesTDO_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_IgnoreDebugFreezeEnable(DEVCON_MODULE_ID index, DEVCON_DEBUG_PERIPHERAL myPeripheral)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_IgnoreDebugFreezeEnable_Unsupported(index, myPeripheral);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DEVCON_IgnoreDebugFreezeDisable(DEVCON_MODULE_ID index, DEVCON_DEBUG_PERIPHERAL myPeripheral)
{
    switch (index) {
        case DEVCON_ID_0 :
            DEVCON_IgnoreDebugFreezeDisable_Unsupported(index, myPeripheral);
            break;
        case DEVCON_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DEVCON_ExistsIgnoreDebugFreeze(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsIgnoreDebugFreeze_Unsupported(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_DEVCON_DeviceVersionGet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_DeviceVersionGet_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API uint32_t PLIB_DEVCON_DeviceIdGet(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_DeviceIdGet_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_DEVCON_ExistsDeviceVerAndId(DEVCON_MODULE_ID index)
{
    switch (index) {
        case DEVCON_ID_0 :
            return DEVCON_ExistsDeviceVerAndId_Default(index);
        case DEVCON_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
