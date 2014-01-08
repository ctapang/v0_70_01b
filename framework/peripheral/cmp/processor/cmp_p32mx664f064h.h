/* Created by plibgen $Revision: 1.29 $ */

#ifndef _CMP_P32MX664F064H_H
#define _CMP_P32MX664F064H_H

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

    CMP_ID_1 = 0,
    CMP_NUMBER_OF_MODULES

} CMP_MODULE_ID;

typedef enum {

    CMP_CVREF_VOLTAGE_SOURCE_NEG_REFERENCE_NONE

} CMP_CVREF_VOLTAGE_SOURCE_NEG_REFERENCE;

typedef enum {

    CMP_MASK_C_NONE

} CMP_MASK_C;

typedef enum {

    CMP_MASK_B_NONE

} CMP_MASK_B;

typedef enum {

    CMP_MASK_A_NONE

} CMP_MASK_A;

typedef enum {

    CMP_SPEED_POWER_NONE

} CMP_SPEED_POWER;

typedef enum {

    CMP_FILTER_CLOCK_NONE

} CMP_FILTER_CLOCK;

typedef enum {

    CMP_CLOCK_DIVIDE_NONE

} CMP_CLOCK_DIVIDE;

typedef enum {

    CMP_CVREF_VALUE_NONE

} CMP_CVREF_VALUE;

typedef enum {

    CMP_CVREF_VOLTAGE_SOURCE_NONE

} CMP_CVREF_VOLTAGE_SOURCE;

typedef enum {

    CMP_INTERRUPT_EVENT_NONE

} CMP_INTERRUPT_EVENT;

typedef enum {

    CMP_INVERTING_INPUT_NONE

} CMP_INVERTING_INPUT;

typedef enum {

    CMP_NON_INVERTING_INPUT_NONE

} CMP_NON_INVERTING_INPUT;

typedef enum {

    CMP_CVREF_REFERENCE_SELECT_NONE

} CMP_CVREF_REFERENCE_SELECT;

typedef enum {

    CMP_CVREF_BANDGAP_SELECT_NONE

} CMP_CVREF_BANDGAP_SELECT;

INLINE SFR_TYPE* _CMP_CMP_ENABLE_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_OUTPUT_ENABLE_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_INVERT_OUTPUT_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_OUTPUT_LEVEL_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_INTERRUPT_EVENT_SELECT_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_NON_INVERTING_INPUT_SELECTION_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_INVERTING_INPUT_SELECTION_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CM1CON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_STOP_IN_IDLE_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CMSTAT;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_CVREF_ENABLE_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CVRCON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_CVREF_OUTPUT_ENABLE_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CVRCON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_CVREF_WIDE_RANGE_CONTROL_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CVRCON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_CVREF_VOLTAGE_RANGE_SELECT_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CVRCON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _CMP_CMP_CVREF_VALUE_SELECT_VREG(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return &CVRCON;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_ENABLE_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_ON_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_ENABLE_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COE_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INVERT_OUTPUT_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CPOL_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_LEVEL_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COUT_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INTERRUPT_EVENT_SELECT_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_EVPOL_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_NON_INVERTING_INPUT_SELECTION_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CREF_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_INVERTING_INPUT_SELECTION_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CCH_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_STOP_IN_IDLE_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CMSTAT_SIDL_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_ENABLE_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_ON_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_OUTPUT_ENABLE_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVROE_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_WIDE_RANGE_CONTROL_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_BGSEL_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VOLTAGE_RANGE_SELECT_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVRSS_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VALUE_SELECT_MASK(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVR_MASK;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_ENABLE_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_ON_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_ENABLE_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COE_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INVERT_OUTPUT_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CPOL_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_LEVEL_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COUT_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INTERRUPT_EVENT_SELECT_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_EVPOL_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_NON_INVERTING_INPUT_SELECTION_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CREF_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_INVERTING_INPUT_SELECTION_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CCH_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_STOP_IN_IDLE_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CMSTAT_SIDL_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_ENABLE_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_ON_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_OUTPUT_ENABLE_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVROE_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_WIDE_RANGE_CONTROL_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_BGSEL_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VOLTAGE_RANGE_SELECT_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVRSS_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VALUE_SELECT_POS(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVR_POSITION;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_ENABLE_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_ON_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_ENABLE_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COE_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INVERT_OUTPUT_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CPOL_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_OUTPUT_LEVEL_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_COUT_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_INTERRUPT_EVENT_SELECT_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_EVPOL_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_NON_INVERTING_INPUT_SELECTION_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CREF_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_INVERTING_INPUT_SELECTION_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CM1CON_CCH_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_STOP_IN_IDLE_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CMSTAT_SIDL_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_ENABLE_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_ON_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_OUTPUT_ENABLE_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVROE_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_WIDE_RANGE_CONTROL_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_BGSEL_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VOLTAGE_RANGE_SELECT_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVRSS_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _CMP_CMP_CVREF_VALUE_SELECT_LEN(CMP_MODULE_ID i)
{
    switch (i) {
        case CMP_ID_1 :
            return _CVRCON_CVR_LENGTH;
        case CMP_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/cmp_ComparatorEnableControl_Default.h"
#include "../templates/cmp_ComparatorOutputEnableControl_Default.h"
#include "../templates/cmp_InvertOutputSelectControl_Default.h"
#include "../templates/cmp_OutputLevelSelectControl_Default.h"
#include "../templates/cmp_InterruptEventSelect_Default.h"
#include "../templates/cmp_NonInvertingInputSelect_Default.h"
#include "../templates/cmp_InvertingInputSelect_Default.h"
#include "../templates/cmp_StopInIdle_Default.h"
#include "../templates/cmp_CVREFEnableControl_Default.h"
#include "../templates/cmp_CVREFOutputEnableControl_Default.h"
#include "../templates/cmp_CVREFWideRangeControl_Default.h"
#include "../templates/cmp_CVREFVoltageRangeSelect_Default.h"
#include "../templates/cmp_CVREFRefVoltageRangeSelect_Unsupported.h"
#include "../templates/cmp_CVREFBGRefVoltageRangeSelect_Unsupported.h"
#include "../templates/cmp_CVREFValueSelect_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_CMP_ExistsEnableControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsEnableControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_Enable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Enable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_Disable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Disable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsOutputEnableControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsOutputEnableControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_OutputEnable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_OutputEnable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_OutputDisable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_OutputDisable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsInvertOutputControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsInvertOutputControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_InvertedOutputSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_InvertedOutputSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_NonInvertedOutputSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_NonInvertedOutputSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsOutputLevelControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsOutputLevelControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_OutputHighSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_OutputHighSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_OutputLowSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_OutputLowSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_Cmp1OutputHighSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Cmp1OutputHighSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_Cmp1OutputLowSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Cmp1OutputLowSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_Cmp2OutputHighSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Cmp2OutputHighSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_Cmp2OutputLowSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_Cmp2OutputLowSelect_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsInterruptEventSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsInterruptEventSelect_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_InterruptEventSelect(CMP_MODULE_ID index, CMP_INTERRUPT_EVENT event)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_InterruptEventSelect_Default(index, event);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsNonInvertingInputSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsNonInvertingInputSelect_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_NonInvertingInputChannelSelect(CMP_MODULE_ID index, CMP_NON_INVERTING_INPUT input)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_NonInvertingInputChannelSelect_Default(index, input);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsInvertingInputSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsInvertingInputSelect_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_InvertingInputChannelSelect(CMP_MODULE_ID index, CMP_INVERTING_INPUT channel)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_InvertingInputChannelSelect_Default(index, channel);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsStopInIdle(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsStopInIdle_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_StopInIdleModeEnable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_StopInIdleModeEnable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_StopInIdleModeDisable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_StopInIdleModeDisable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsCVREFEnableControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFEnableControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_CVREF_Enable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_Enable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_CVREF_Disable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_Disable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsCVREFOutputEnableControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFOutputEnableControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_CVREF_OutputEnable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_OutputEnable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_CVREF_OutputDisable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_OutputDisable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsCVREFWideRangeControl(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFWideRangeControl_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_CVREF_WideRangeEnable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_WideRangeEnable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_CMP_CVREF_WideRangeDisable(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_WideRangeDisable_Default(index);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_CVREF_WideRangeIsEnabled(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_CVREF_WideRangeIsEnabled_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_CMP_ExistsCVREFVoltageRangeSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFVoltageRangeSelect_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_CVREF_SourceVoltageSelect(CMP_MODULE_ID index, CMP_CVREF_VOLTAGE_SOURCE source)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_SourceVoltageSelect_Default(index, source);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_CMP_ExistsCVREFRefVoltageRangeSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFRefVoltageRangeSelect_Unsupported(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_CMP_CVREF_ReferenceVoltageSelect(CMP_MODULE_ID index, CMP_CVREF_REFERENCE_SELECT reference)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_ReferenceVoltageSelect_Unsupported(index, reference);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_CMP_ExistsCVREFBGRefVoltageRangeSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFBGRefVoltageRangeSelect_Unsupported(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_CMP_CVREF_BandGapReferenceSourceSelect(CMP_MODULE_ID index, CMP_CVREF_BANDGAP_SELECT select)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_BandGapReferenceSourceSelect_Unsupported(index, select);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_CMP_ExistsCVREFValueSelect(CMP_MODULE_ID index)
{
    switch (index) {
        case CMP_ID_1 :
            return CMP_ExistsCVREFValueSelect_Default(index);
        case CMP_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_CMP_CVREF_ValueSelect(CMP_MODULE_ID index, CMP_CVREF_VALUE value)
{
    switch (index) {
        case CMP_ID_1 :
            CMP_CVREF_ValueSelect_Default(index, value);
            break;
        case CMP_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
