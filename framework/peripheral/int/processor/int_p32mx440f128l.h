/* Created by plibgen $Revision: 1.29 $ */

#ifndef _INT_P32MX440F128L_H
#define _INT_P32MX440F128L_H

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

    INT_NUMBER_OF_MODULES

} INT_MODULE_ID;

typedef enum {

    INT_VECTOR_SPACING_NONE

} INT_VECTOR_SPACING;

typedef enum {

    INT_SHADOW_REGISTER_NONE

} INT_SHADOW_REGISTER;

typedef enum {

    INT_OFFSET_VECTOR_NONE

} INT_OFFSET_VECTOR;

typedef enum {

    INT_EXTERNAL_SOURCES_NONE

} INT_EXTERNAL_SOURCES;

typedef enum {

    INT_PRIORITY_LEVEL_NONE

} INT_PRIORITY_LEVEL;

typedef enum {

    INT_SUBPRIORITY_LEVEL_NONE

} INT_SUBPRIORITY_LEVEL;

typedef enum {

    INT_SOURCE_NONE

} INT_SOURCE;

typedef enum {

    INT_VECTOR_NONE

} INT_VECTOR;

typedef enum {

    INT_TRAP_SOURCE_NONE

} INT_TRAP_SOURCE;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSingleVectorShadowSet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorShadowSetDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorShadowSetEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_MultiVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsProximityTimerEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerEnable(INT_MODULE_ID index, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsProximityTimerControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerSet(INT_MODULE_ID index, uint32_t timerreloadvalue)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsExternalINTEdgeSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ExternalRisingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ExternalFallingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTCPUPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_PriorityGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTCPUVector(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_VECTOR _PLIB_UNSUPPORTED PLIB_INT_VectorGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_VECTOR)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourceFlag(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_SourceFlagGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SourceFlagSet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SourceFlagClear(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourceControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SourceEnable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_SourceDisable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_SourceIsEnabled(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsVectorPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_VectorPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_VectorPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_VectorSubPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_SUBPRIORITY_LEVEL subPriority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_SUBPRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_VectorSubPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_SUBPRIORITY_LEVEL)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsCPUCurrentPriorityLevel(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_CPUCurrentPriorityLevelGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsEnableControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_Enable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_Disable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_IsEnabled(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTNesting(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsTrapSource(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagGet(INT_MODULE_ID index, INT_TRAP_SOURCE trapSource)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagClear(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsAlternateVectorTable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_AlternateVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_StandardVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPeripheralControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsHighPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsLowPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
