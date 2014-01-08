/* Created by plibgen $Revision: 1.72 $ */

#ifndef _INT_P32MZ2048GP814_H
#define _INT_P32MZ2048GP814_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>


#include "peripheral/peripheral_common_32bit.h"

#define INLINE static inline

typedef enum {

    INT_NUMBER_OF_MODULES

} INT_MODULE_ID;

typedef enum {

    INT_PRIORITY_LEVEL_NONE

} INT_PRIORITY_LEVEL;

typedef enum {

    INT_EXTERNAL_SOURCES_NONE

} INT_EXTERNAL_SOURCES;

typedef enum {

    INT_SOURCE_NONE

} INT_SOURCE;

INLINE SFR_TYPE* _INT_FLAG_VREG(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_ENABLE_VREG(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_PRIO_VREG(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_SUB_PRIO_VREG(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _INT_FLAG_MASK(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_ENABLE_MASK(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIO_MASK(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SUB_PRIO_MASK(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_FLAG_POS(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_ENABLE_POS(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIO_POS(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SUB_PRIO_POS(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_FLAG_LEN(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_ENABLE_LEN(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIO_LEN(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SUB_PRIO_LEN(INT_SOURCE s, INT_MODULE_ID i)
{
    switch (s) {
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSingleVectorShadowSet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorShadowSetDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorShadowSetEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_MultiVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SingleVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsProximityTimerEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerEnable(INT_MODULE_ID index, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsProximityTimerControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerSet(INT_MODULE_ID index, uint32_t timerreloadvalue)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE uint32_t _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsExternalINTEdgeSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_ExternalRisingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_ExternalFallingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTCPUPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_PriorityGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTCPUVector(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE INT_SOURCE _PLIB_UNSUPPORTED PLIB_INT_VectorGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_SOURCE)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourceFlag(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_SourceFlagGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourceFlagSet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourceFlagClear(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourceControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourceEnable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourceDisable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_SourceIsEnabled(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourcePriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourcePrioritySet(INT_MODULE_ID index, INT_SOURCE source, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_SourcePriorityGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsSourceSubPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_SourceSubPrioritySet(INT_MODULE_ID index, INT_SOURCE source, INT_SUBPRIORITY_LEVEL subpriority)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE INT_SUBPRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_SourceSubPriorityGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_SUBPRIORITY_LEVEL)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsCPUCurrentPriorityLevel(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE INT_PRIORITY_LEVEL _PLIB_UNSUPPORTED PLIB_INT_CPUCurrentPriorityLevelGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTNesting(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_NestingEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_NestingDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsTrapSource(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagGet(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagClear(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsAlternateVectorTable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_AlternateVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_StandardVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsEnableControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_Enable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_Disable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_IsEnabled(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPeripheralControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsHighPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsLowPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_INT_PriorityDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
