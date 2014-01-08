/* Created by plibgen $Revision: 1.29 $ */

#ifndef _ADCP_P32MX250F128C_H
#define _ADCP_P32MX250F128C_H

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

    ADCP_NUMBER_OF_MODULES

} ADCP_MODULE_ID;

typedef enum {

    ADCP_VREF_SOURCE_NONE

} ADCP_VREF_SOURCE;

typedef enum {

    ADCP_CLOCK_SOURCE_NONE

} ADCP_CLOCK_SOURCE;

typedef enum {

    ADCP_CLASS12_INPUT_ID_NONE

} ADCP_CLASS12_INPUT_ID;

typedef enum {

    ADCP_SH_ID_NONE

} ADCP_SH_ID;

typedef enum {

    ADCP_DSH_ID_NONE

} ADCP_DSH_ID;

typedef enum {

    ADCP_SH_MODE_NONE

} ADCP_SH_MODE;

typedef enum {

    ADCP_SCAN_TRG_SRC_NONE

} ADCP_SCAN_TRG_SRC;

typedef enum {

    ADCP_TRG_SRC_NONE

} ADCP_TRG_SRC;

typedef enum {

    ADCP_INPUT_ID_NONE

} ADCP_INPUT_ID;

typedef enum {

    ADCP_DCMP_ID_NONE

} ADCP_DCMP_ID;

typedef enum {

    ADCP_ODFLTR_ID_NONE

} ADCP_ODFLTR_ID;

typedef enum {

    ADCP_ODFLTR_SAMPLE_RATIO_NONE

} ADCP_ODFLTR_SAMPLE_RATIO;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_Enable(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_Disable(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsEnableControl(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_CalibrationStart(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsCalibration(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_Configure(ADCP_MODULE_ID index, ADCP_VREF_SOURCE voltageRefSelect, bool boostVref, bool fractionalOutputOn, bool stopInIdle, ADCP_CLOCK_SOURCE adcClockSource, int8_t adcClockDivider, int8_t oversampleDigFilterSamTime, int8_t earlyIntEnable, int8_t class2and3SampleTime)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsConfiguration(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_LowPowerStateEnter(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_LowPowerStateExit(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_LowPowerStateGet(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsLowPowerControl(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ModuleIsReady(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsReadyStatus(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_AlternateInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_DefaultInputSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsInputSelect(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_SHModeSelect(ADCP_MODULE_ID index, ADCP_DSH_ID id, ADCP_SH_MODE mode)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsModeSelect(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_ChannelScanConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable, ADCP_SCAN_TRG_SRC triggerSource)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsChannelScan(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_Class12TriggerConfigure(ADCP_MODULE_ID index, ADCP_CLASS12_INPUT_ID inputId, ADCP_TRG_SRC triggerSource)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_GlobalSoftwareTrigger(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_IndividualTrigger(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsTriggering(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API AN_READY _PLIB_UNSUPPORTED PLIB_ADCP_ResultReady(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (AN_READY)0;
    }
}

INLINE_API int32_t _PLIB_UNSUPPORTED PLIB_ADCP_ResultGet(ADCP_MODULE_ID index, ADCP_INPUT_ID inputId)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int32_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_ResultReadyGrpIntConfigure(ADCP_MODULE_ID index, uint32_t lowEnable, uint32_t highEnable)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsConversionResults(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_DigCmpConfig(ADCP_MODULE_ID index, ADCP_DCMP_ID id, bool globalIntEnable, bool inBetweenOrEqual, bool greaterEqualHi, bool lessThanHi, bool greaterEqualLo, bool lessThanLo, uint32_t inputEnable, int32_t hiLimit, int32_t loLimit)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_DigCmpEnable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_DigCmpDisable(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API int16_t _PLIB_UNSUPPORTED PLIB_ADCP_DigCmpAIdGet(ADCP_MODULE_ID index, ADCP_DCMP_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsDigCmp(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_OsampDigFilterConfig(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id, ADCP_INPUT_ID inputId, ADCP_ODFLTR_SAMPLE_RATIO oversampleRatio, bool globalIntEnable)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_OsampDigFilterEnable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADCP_OsampDigFilterDisable(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_OsampDigFilterDataRdy(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int16_t _PLIB_UNSUPPORTED PLIB_ADCP_OsampDigFilterDataGet(ADCP_MODULE_ID index, ADCP_ODFLTR_ID id)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (int16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADCP_ExistsOsampDigFilter(ADCP_MODULE_ID index)
{
    switch (index) {
        case ADCP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
