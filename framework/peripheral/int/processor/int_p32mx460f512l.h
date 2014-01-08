/* Created by plibgen $Revision: 1.29 $ */

#ifndef _INT_P32MX460F512L_H
#define _INT_P32MX460F512L_H

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

    INT_ID_0 = 0,
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

INLINE SFR_TYPE* _INT_INT_EXT_INT0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_PROXIMITY_TIMER_ENABLE_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_SINGLE_MULTI_VECTOR_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_SHADOW_SET_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_LATEST_INT_VECTOR_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTSTAT;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_LATEST_INT_PRIORITY_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTSTAT;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_FLAG_STATUS_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IFS0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_FLAG_STATUS_1_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IFS1;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_ENABLE_CONTROL_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IEC0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_ENABLE_CONTROL_1_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IEC1;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_PRIORITY_CONTROL_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IPC0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_SS0_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_VEC_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_CNIF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_CNIE_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_SS0_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_VEC_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_CNIF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_CNIE_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_SS0_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_VEC_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_CNIF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_CNIE_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/int_SingleVectorShadowSet_Default.h"
#include "../templates/int_VectorSelect_Default.h"
#include "../templates/int_ProximityTimerEnable_Default.h"
#include "../templates/int_ProximityTimerControl_Default.h"
#include "../templates/int_ExternalINTEdgeSelect_Default.h"
#include "../templates/int_INTCPUPriority_Default.h"
#include "../templates/int_INTCPUVector_Default.h"
#include "../templates/int_SourceFlag_Default.h"
#include "../templates/int_SourceControl_Default.h"
#include "../templates/int_VectorPriority_Default.h"
#include "../templates/int_CPUCurrentPriorityLevel_Default.h"
#include "../templates/int_EnableControl_PIC32.h"
#include "../templates/int_INTNesting_Unsupported.h"
#include "../templates/int_TrapSource_Unsupported.h"
#include "../templates/int_AlternateVectorTable_Unsupported.h"
#include "../templates/int_PeripheralControl_Unsupported.h"
#include "../templates/int_HighPriority_Unsupported.h"
#include "../templates/int_LowPriority_Unsupported.h"
#include "../templates/int_Priority_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_INT_ExistsSingleVectorShadowSet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSingleVectorShadowSet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SingleVectorShadowSetDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorShadowSetDisable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SingleVectorShadowSetEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorShadowSetEnable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsVectorSelect_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_MultiVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_MultiVectorSelect_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SingleVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorSelect_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsProximityTimerEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsProximityTimerEnable_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_ProximityTimerEnable(INT_MODULE_ID index, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerEnable_Default(index, priority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_ProximityTimerDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerDisable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsProximityTimerControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsProximityTimerControl_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_ProximityTimerSet(INT_MODULE_ID index, uint32_t timerreloadvalue)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerSet_Default(index, timerreloadvalue);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_INT_ProximityTimerGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ProximityTimerGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_INT_ExistsExternalINTEdgeSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsExternalINTEdgeSelect_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_ExternalRisingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_ID_0 :
            INT_ExternalRisingEdgeSelect_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_ExternalFallingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_ID_0 :
            INT_ExternalFallingEdgeSelect_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsINTCPUPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTCPUPriority_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_PriorityGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_PriorityGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsINTCPUVector(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTCPUVector_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_VECTOR PLIB_INT_VectorGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_VECTOR)0;
    }
}

INLINE_API bool PLIB_INT_ExistsSourceFlag(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSourceFlag_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_INT_SourceFlagGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            return INT_SourceFlagGet_Default(index, source);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SourceFlagSet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceFlagSet_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SourceFlagClear(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceFlagClear_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsSourceControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSourceControl_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SourceEnable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceEnable_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SourceDisable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceDisable_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_SourceIsEnabled(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            return INT_SourceIsEnabled_Default(index, source);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_INT_ExistsVectorPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsVectorPriority_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_VectorPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_ID_0 :
            INT_VectorPrioritySet_Default(index, vector, priority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_VectorPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorPriorityGet_Default(index, vector);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API void PLIB_INT_VectorSubPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_SUBPRIORITY_LEVEL subPriority)
{
    switch (index) {
        case INT_ID_0 :
            INT_VectorSubPrioritySet_Default(index, vector, subPriority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_SUBPRIORITY_LEVEL PLIB_INT_VectorSubPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorSubPriorityGet_Default(index, vector);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_SUBPRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsCPUCurrentPriorityLevel(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsCPUCurrentPriorityLevel_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_CPUCurrentPriorityLevelGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_CPUCurrentPriorityLevelGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsEnableControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsEnableControl_PIC32(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_Enable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_Enable_PIC32(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_Disable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_Disable_PIC32(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_IsEnabled(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_IsEnabled_PIC32(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTNesting(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTNesting_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_NestingEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_NestingDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsTrapSource(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsTrapSource_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagGet(INT_MODULE_ID index, INT_TRAP_SOURCE trapSource)
{
    switch (index) {
        case INT_ID_0 :
            return INT_TrapSourceFlagGet_Unsupported(index, trapSource);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagClear(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_ID_0 :
            INT_TrapSourceFlagClear_Unsupported(index, trapsource);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsAlternateVectorTable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsAlternateVectorTable_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_AlternateVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_AlternateVectorTableSelect_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_StandardVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_StandardVectorTableSelect_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPeripheralControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsPeripheralControl_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PeripheralsEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PeripheralsDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsHighPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsHighPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityHighEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityHighDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsLowPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsLowPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityLowEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityLowDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
