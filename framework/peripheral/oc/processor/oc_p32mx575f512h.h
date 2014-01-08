/* Created by plibgen $Revision: 1.29 $ */

#ifndef _OC_P32MX575F512H_H
#define _OC_P32MX575F512H_H

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

    OC_ID_1 = 0,
    OC_ID_2,
    OC_ID_3,
    OC_ID_4,
    OC_ID_5,
    OC_NUMBER_OF_MODULES

} OC_MODULE_ID;

typedef enum {

    OC_COMPARE_TURN_OFF_MODE = 0,
    OC_SET_HIGH_SINGLE_PULSE_MODE = 1,
    OC_SET_LOW_SINGLE_PULSE_MODE = 2,
    OC_TOGGLE_CONTINUOUS_PULSE_MODE = 3,
    OC_DUAL_COMPARE_SINGLE_PULSE_MODE = 4,
    OC_DUAL_COMPARE_CONTINUOUS_PULSE_MODE = 5,
    OC_COMPARE_PWM_EDGE_ALIGNED_MODE = 6

} OC_COMPARE_MODES;

typedef enum {

    OC_BUFFER_SIZE_16BIT = 0,
    OC_BUFFER_SIZE_32BIT = 1

} OC_BUFFER_SIZE;

typedef enum {

    OC_TIMER_16BIT_TMR2 = 0,
    OC_TIMER_16BIT_TMR3 = 1

} OC_16BIT_TIMERS;

typedef enum {

    OC_FAULT_PRESET = 7,
    OC_FAULT_DISABLE = 6

} OC_FAULTS;

typedef enum {

    OC_FAULT_OUT_NOT_SUPPORTED = 0

} OC_FAULT_OUT;

typedef enum {

    OC_FAULT_MODES_NOT_SUPPORTED = 0

} OC_FAULT_MODES;

typedef enum {

    OC_FAULT_TRISTATE_NOT_SUPPORTED = 0

} OC_FAULT_TRISTATE;

typedef enum {

    OC_TRIGGER_STATUS_MODES_NOT_SUPPORTED = 0

} OC_TRIGGER_STATUS_MODES;

typedef enum {

    OC_CLOCK_RESOLUTION_NOT_SUPPORTED = 0

} OC_CLOCK_RESOLUTION;

typedef enum {

    OC_SYNC_MODES_NOT_SUPPORTED = 0

} OC_SYNC_MODES;

typedef enum {

    OC_SYNC_SOURCES_NOT_SUPPORTED = 0

} OC_SYNC_SOURCES;

INLINE SFR_TYPE* _OC_ENABLE_CONTROL_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_STOP_IN_IDLE_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_BUF_SIZE_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_FAULT_STATUS_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_TIMER_SELECT_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_CMP_MODE_SEL_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_FAULT_INPUT_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1CON;
        case OC_ID_2 :
            return &OC2CON;
        case OC_ID_3 :
            return &OC3CON;
        case OC_ID_4 :
            return &OC4CON;
        case OC_ID_5 :
            return &OC5CON;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_BUF_VAL_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1R;
        case OC_ID_2 :
            return &OC2R;
        case OC_ID_3 :
            return &OC3R;
        case OC_ID_4 :
            return &OC4R;
        case OC_ID_5 :
            return &OC5R;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _OC_SEC_CMP_VAL_VREG(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return &OC1RS;
        case OC_ID_2 :
            return &OC2RS;
        case OC_ID_3 :
            return &OC3RS;
        case OC_ID_4 :
            return &OC4RS;
        case OC_ID_5 :
            return &OC5RS;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _OC_ENABLE_CONTROL_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_ON_MASK;
        case OC_ID_2 :
            return _OC2CON_ON_MASK;
        case OC_ID_3 :
            return _OC3CON_ON_MASK;
        case OC_ID_4 :
            return _OC4CON_ON_MASK;
        case OC_ID_5 :
            return _OC5CON_ON_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_STOP_IN_IDLE_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_SIDL_MASK;
        case OC_ID_2 :
            return _OC2CON_SIDL_MASK;
        case OC_ID_3 :
            return _OC3CON_SIDL_MASK;
        case OC_ID_4 :
            return _OC4CON_SIDL_MASK;
        case OC_ID_5 :
            return _OC5CON_SIDL_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_SIZE_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OC32_MASK;
        case OC_ID_2 :
            return _OC2CON_OC32_MASK;
        case OC_ID_3 :
            return _OC3CON_OC32_MASK;
        case OC_ID_4 :
            return _OC4CON_OC32_MASK;
        case OC_ID_5 :
            return _OC5CON_OC32_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_STATUS_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCFLT_MASK;
        case OC_ID_2 :
            return _OC2CON_OCFLT_MASK;
        case OC_ID_3 :
            return _OC3CON_OCFLT_MASK;
        case OC_ID_4 :
            return _OC4CON_OCFLT_MASK;
        case OC_ID_5 :
            return _OC5CON_OCFLT_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_TIMER_SELECT_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCTSEL_MASK;
        case OC_ID_2 :
            return _OC2CON_OCTSEL_MASK;
        case OC_ID_3 :
            return _OC3CON_OCTSEL_MASK;
        case OC_ID_4 :
            return _OC4CON_OCTSEL_MASK;
        case OC_ID_5 :
            return _OC5CON_OCTSEL_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_CMP_MODE_SEL_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_MASK;
        case OC_ID_2 :
            return _OC2CON_OCM_MASK;
        case OC_ID_3 :
            return _OC3CON_OCM_MASK;
        case OC_ID_4 :
            return _OC4CON_OCM_MASK;
        case OC_ID_5 :
            return _OC5CON_OCM_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_INPUT_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_MASK;
        case OC_ID_2 :
            return _OC2CON_OCM_MASK;
        case OC_ID_3 :
            return _OC3CON_OCM_MASK;
        case OC_ID_4 :
            return _OC4CON_OCM_MASK;
        case OC_ID_5 :
            return _OC5CON_OCM_MASK;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_VAL_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)-1;
        case OC_ID_2 :
            return (SFR_DATA)-1;
        case OC_ID_3 :
            return (SFR_DATA)-1;
        case OC_ID_4 :
            return (SFR_DATA)-1;
        case OC_ID_5 :
            return (SFR_DATA)-1;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_SEC_CMP_VAL_MASK(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)-1;
        case OC_ID_2 :
            return (SFR_DATA)-1;
        case OC_ID_3 :
            return (SFR_DATA)-1;
        case OC_ID_4 :
            return (SFR_DATA)-1;
        case OC_ID_5 :
            return (SFR_DATA)-1;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_ENABLE_CONTROL_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_ON_POSITION;
        case OC_ID_2 :
            return _OC2CON_ON_POSITION;
        case OC_ID_3 :
            return _OC3CON_ON_POSITION;
        case OC_ID_4 :
            return _OC4CON_ON_POSITION;
        case OC_ID_5 :
            return _OC5CON_ON_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_STOP_IN_IDLE_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_SIDL_POSITION;
        case OC_ID_2 :
            return _OC2CON_SIDL_POSITION;
        case OC_ID_3 :
            return _OC3CON_SIDL_POSITION;
        case OC_ID_4 :
            return _OC4CON_SIDL_POSITION;
        case OC_ID_5 :
            return _OC5CON_SIDL_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_SIZE_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OC32_POSITION;
        case OC_ID_2 :
            return _OC2CON_OC32_POSITION;
        case OC_ID_3 :
            return _OC3CON_OC32_POSITION;
        case OC_ID_4 :
            return _OC4CON_OC32_POSITION;
        case OC_ID_5 :
            return _OC5CON_OC32_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_STATUS_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCFLT_POSITION;
        case OC_ID_2 :
            return _OC2CON_OCFLT_POSITION;
        case OC_ID_3 :
            return _OC3CON_OCFLT_POSITION;
        case OC_ID_4 :
            return _OC4CON_OCFLT_POSITION;
        case OC_ID_5 :
            return _OC5CON_OCFLT_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_TIMER_SELECT_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCTSEL_POSITION;
        case OC_ID_2 :
            return _OC2CON_OCTSEL_POSITION;
        case OC_ID_3 :
            return _OC3CON_OCTSEL_POSITION;
        case OC_ID_4 :
            return _OC4CON_OCTSEL_POSITION;
        case OC_ID_5 :
            return _OC5CON_OCTSEL_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_CMP_MODE_SEL_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_POSITION;
        case OC_ID_2 :
            return _OC2CON_OCM_POSITION;
        case OC_ID_3 :
            return _OC3CON_OCM_POSITION;
        case OC_ID_4 :
            return _OC4CON_OCM_POSITION;
        case OC_ID_5 :
            return _OC5CON_OCM_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_INPUT_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_POSITION;
        case OC_ID_2 :
            return _OC2CON_OCM_POSITION;
        case OC_ID_3 :
            return _OC3CON_OCM_POSITION;
        case OC_ID_4 :
            return _OC4CON_OCM_POSITION;
        case OC_ID_5 :
            return _OC5CON_OCM_POSITION;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_VAL_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)0;
        case OC_ID_2 :
            return (SFR_DATA)0;
        case OC_ID_3 :
            return (SFR_DATA)0;
        case OC_ID_4 :
            return (SFR_DATA)0;
        case OC_ID_5 :
            return (SFR_DATA)0;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_SEC_CMP_VAL_POS(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)0;
        case OC_ID_2 :
            return (SFR_DATA)0;
        case OC_ID_3 :
            return (SFR_DATA)0;
        case OC_ID_4 :
            return (SFR_DATA)0;
        case OC_ID_5 :
            return (SFR_DATA)0;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_ENABLE_CONTROL_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_ON_LENGTH;
        case OC_ID_2 :
            return _OC2CON_ON_LENGTH;
        case OC_ID_3 :
            return _OC3CON_ON_LENGTH;
        case OC_ID_4 :
            return _OC4CON_ON_LENGTH;
        case OC_ID_5 :
            return _OC5CON_ON_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_STOP_IN_IDLE_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_SIDL_LENGTH;
        case OC_ID_2 :
            return _OC2CON_SIDL_LENGTH;
        case OC_ID_3 :
            return _OC3CON_SIDL_LENGTH;
        case OC_ID_4 :
            return _OC4CON_SIDL_LENGTH;
        case OC_ID_5 :
            return _OC5CON_SIDL_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_SIZE_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OC32_LENGTH;
        case OC_ID_2 :
            return _OC2CON_OC32_LENGTH;
        case OC_ID_3 :
            return _OC3CON_OC32_LENGTH;
        case OC_ID_4 :
            return _OC4CON_OC32_LENGTH;
        case OC_ID_5 :
            return _OC5CON_OC32_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_STATUS_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCFLT_LENGTH;
        case OC_ID_2 :
            return _OC2CON_OCFLT_LENGTH;
        case OC_ID_3 :
            return _OC3CON_OCFLT_LENGTH;
        case OC_ID_4 :
            return _OC4CON_OCFLT_LENGTH;
        case OC_ID_5 :
            return _OC5CON_OCFLT_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_TIMER_SELECT_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCTSEL_LENGTH;
        case OC_ID_2 :
            return _OC2CON_OCTSEL_LENGTH;
        case OC_ID_3 :
            return _OC3CON_OCTSEL_LENGTH;
        case OC_ID_4 :
            return _OC4CON_OCTSEL_LENGTH;
        case OC_ID_5 :
            return _OC5CON_OCTSEL_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_CMP_MODE_SEL_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_LENGTH;
        case OC_ID_2 :
            return _OC2CON_OCM_LENGTH;
        case OC_ID_3 :
            return _OC3CON_OCM_LENGTH;
        case OC_ID_4 :
            return _OC4CON_OCM_LENGTH;
        case OC_ID_5 :
            return _OC5CON_OCM_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_FAULT_INPUT_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return _OC1CON_OCM_LENGTH;
        case OC_ID_2 :
            return _OC2CON_OCM_LENGTH;
        case OC_ID_3 :
            return _OC3CON_OCM_LENGTH;
        case OC_ID_4 :
            return _OC4CON_OCM_LENGTH;
        case OC_ID_5 :
            return _OC5CON_OCM_LENGTH;
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_BUF_VAL_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _OC_SEC_CMP_VAL_LEN(OC_MODULE_ID i)
{
    switch (i) {
        case OC_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case OC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/oc_EnableControl_Default.h"
#include "../templates/oc_AlternateClock_Default.h"
#include "../templates/oc_StopInIdle_Default.h"
#include "../templates/oc_FaultInput_Default.h"
#include "../templates/oc_FaultOut_Unsupported.h"
#include "../templates/oc_FaultStatus_Default.h"
#include "../templates/oc_TimerSelect_Default.h"
#include "../templates/oc_BufferValue_32Bit_Variant.h"
#include "../templates/oc_PulseWidth_32Bit_Variant.h"
#include "../templates/oc_BufferSize_Default.h"
#include "../templates/oc_CompareModeSelect_Default.h"
#include "../templates/oc_TriggerControl_Unsupported.h"
#include "../templates/oc_PWMDutyCycleResolution_Unsupported.h"
#include "../templates/oc_PolarityInvert_Unsupported.h"
#include "../templates/oc_FaultModeSelect_Unsupported.h"
#include "../templates/oc_FaultTristateSelect_Unsupported.h"
#include "../templates/oc_SyncModeSelect_Unsupported.h"
#include "../templates/oc_SyncSourceSelect_Unsupported.h"
#include "../templates/oc_TriggerStatusModeSelect_Unsupported.h"
#include "../templates/oc_TimerTriggered_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_OC_Enable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_Enable_Default(index);
            break;
        case OC_ID_2 :
            OC_Enable_Default(index);
            break;
        case OC_ID_3 :
            OC_Enable_Default(index);
            break;
        case OC_ID_4 :
            OC_Enable_Default(index);
            break;
        case OC_ID_5 :
            OC_Enable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_OC_Disable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_Disable_Default(index);
            break;
        case OC_ID_2 :
            OC_Disable_Default(index);
            break;
        case OC_ID_3 :
            OC_Disable_Default(index);
            break;
        case OC_ID_4 :
            OC_Disable_Default(index);
            break;
        case OC_ID_5 :
            OC_Disable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsEnableControl(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsEnableControl_Default(index);
        case OC_ID_2 :
            return OC_ExistsEnableControl_Default(index);
        case OC_ID_3 :
            return OC_ExistsEnableControl_Default(index);
        case OC_ID_4 :
            return OC_ExistsEnableControl_Default(index);
        case OC_ID_5 :
            return OC_ExistsEnableControl_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_AlternateClockEnable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_AlternateClockEnable_Default(index);
            break;
        case OC_ID_2 :
            OC_AlternateClockEnable_Default(index);
            break;
        case OC_ID_3 :
            OC_AlternateClockEnable_Default(index);
            break;
        case OC_ID_4 :
            OC_AlternateClockEnable_Default(index);
            break;
        case OC_ID_5 :
            OC_AlternateClockEnable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_OC_AlternateClockDisable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_AlternateClockDisable_Default(index);
            break;
        case OC_ID_2 :
            OC_AlternateClockDisable_Default(index);
            break;
        case OC_ID_3 :
            OC_AlternateClockDisable_Default(index);
            break;
        case OC_ID_4 :
            OC_AlternateClockDisable_Default(index);
            break;
        case OC_ID_5 :
            OC_AlternateClockDisable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsAlternateClock(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsAlternateClock_Default(index);
        case OC_ID_2 :
            return OC_ExistsAlternateClock_Default(index);
        case OC_ID_3 :
            return OC_ExistsAlternateClock_Default(index);
        case OC_ID_4 :
            return OC_ExistsAlternateClock_Default(index);
        case OC_ID_5 :
            return OC_ExistsAlternateClock_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_StopInIdleEnable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_StopInIdleEnable_Default(index);
            break;
        case OC_ID_2 :
            OC_StopInIdleEnable_Default(index);
            break;
        case OC_ID_3 :
            OC_StopInIdleEnable_Default(index);
            break;
        case OC_ID_4 :
            OC_StopInIdleEnable_Default(index);
            break;
        case OC_ID_5 :
            OC_StopInIdleEnable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_OC_StopInIdleDisable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_StopInIdleDisable_Default(index);
            break;
        case OC_ID_2 :
            OC_StopInIdleDisable_Default(index);
            break;
        case OC_ID_3 :
            OC_StopInIdleDisable_Default(index);
            break;
        case OC_ID_4 :
            OC_StopInIdleDisable_Default(index);
            break;
        case OC_ID_5 :
            OC_StopInIdleDisable_Default(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsStopInIdle(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsStopInIdle_Default(index);
        case OC_ID_2 :
            return OC_ExistsStopInIdle_Default(index);
        case OC_ID_3 :
            return OC_ExistsStopInIdle_Default(index);
        case OC_ID_4 :
            return OC_ExistsStopInIdle_Default(index);
        case OC_ID_5 :
            return OC_ExistsStopInIdle_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_FaultInputSelect(OC_MODULE_ID index, OC_FAULTS flt)
{
    switch (index) {
        case OC_ID_1 :
            OC_FaultInputSelect_Default(index, flt);
            break;
        case OC_ID_2 :
            OC_FaultInputSelect_Default(index, flt);
            break;
        case OC_ID_3 :
            OC_FaultInputSelect_Default(index, flt);
            break;
        case OC_ID_4 :
            OC_FaultInputSelect_Default(index, flt);
            break;
        case OC_ID_5 :
            OC_FaultInputSelect_Default(index, flt);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsFaultInput(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsFaultInput_Default(index);
        case OC_ID_2 :
            return OC_ExistsFaultInput_Default(index);
        case OC_ID_3 :
            return OC_ExistsFaultInput_Default(index);
        case OC_ID_4 :
            return OC_ExistsFaultInput_Default(index);
        case OC_ID_5 :
            return OC_ExistsFaultInput_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_FaultOutSelect(OC_MODULE_ID index, OC_FAULT_OUT fltState)
{
    switch (index) {
        case OC_ID_1 :
            OC_FaultOutSelect_Unsupported(index, fltState);
            break;
        case OC_ID_2 :
            OC_FaultOutSelect_Unsupported(index, fltState);
            break;
        case OC_ID_3 :
            OC_FaultOutSelect_Unsupported(index, fltState);
            break;
        case OC_ID_4 :
            OC_FaultOutSelect_Unsupported(index, fltState);
            break;
        case OC_ID_5 :
            OC_FaultOutSelect_Unsupported(index, fltState);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsFaultOutSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsFaultOutSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsFaultOutSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsFaultOutSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsFaultOutSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsFaultOutSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_OC_FaultHasOccurred(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_FaultHasOccurred_Default(index);
        case OC_ID_2 :
            return OC_FaultHasOccurred_Default(index);
        case OC_ID_3 :
            return OC_FaultHasOccurred_Default(index);
        case OC_ID_4 :
            return OC_FaultHasOccurred_Default(index);
        case OC_ID_5 :
            return OC_FaultHasOccurred_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_OC_ExistsFaultStatus(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsFaultStatus_Default(index);
        case OC_ID_2 :
            return OC_ExistsFaultStatus_Default(index);
        case OC_ID_3 :
            return OC_ExistsFaultStatus_Default(index);
        case OC_ID_4 :
            return OC_ExistsFaultStatus_Default(index);
        case OC_ID_5 :
            return OC_ExistsFaultStatus_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_TimerSelect(OC_MODULE_ID index, OC_16BIT_TIMERS tmr)
{
    switch (index) {
        case OC_ID_1 :
            OC_TimerSelect_Default(index, tmr);
            break;
        case OC_ID_2 :
            OC_TimerSelect_Default(index, tmr);
            break;
        case OC_ID_3 :
            OC_TimerSelect_Default(index, tmr);
            break;
        case OC_ID_4 :
            OC_TimerSelect_Default(index, tmr);
            break;
        case OC_ID_5 :
            OC_TimerSelect_Default(index, tmr);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsTimerSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsTimerSelect_Default(index);
        case OC_ID_2 :
            return OC_ExistsTimerSelect_Default(index);
        case OC_ID_3 :
            return OC_ExistsTimerSelect_Default(index);
        case OC_ID_4 :
            return OC_ExistsTimerSelect_Default(index);
        case OC_ID_5 :
            return OC_ExistsTimerSelect_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_Buffer32BitSet(OC_MODULE_ID index, uint32_t val32Bit)
{
    switch (index) {
        case OC_ID_1 :
            OC_Buffer32BitSet_32Bit_Variant(index, val32Bit);
            break;
        case OC_ID_2 :
            OC_Buffer32BitSet_32Bit_Variant(index, val32Bit);
            break;
        case OC_ID_3 :
            OC_Buffer32BitSet_32Bit_Variant(index, val32Bit);
            break;
        case OC_ID_4 :
            OC_Buffer32BitSet_32Bit_Variant(index, val32Bit);
            break;
        case OC_ID_5 :
            OC_Buffer32BitSet_32Bit_Variant(index, val32Bit);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_OC_Buffer16BitSet(OC_MODULE_ID index, uint16_t val16Bit)
{
    switch (index) {
        case OC_ID_1 :
            OC_Buffer16BitSet_32Bit_Variant(index, val16Bit);
            break;
        case OC_ID_2 :
            OC_Buffer16BitSet_32Bit_Variant(index, val16Bit);
            break;
        case OC_ID_3 :
            OC_Buffer16BitSet_32Bit_Variant(index, val16Bit);
            break;
        case OC_ID_4 :
            OC_Buffer16BitSet_32Bit_Variant(index, val16Bit);
            break;
        case OC_ID_5 :
            OC_Buffer16BitSet_32Bit_Variant(index, val16Bit);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsBufferValue(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsBufferValue_32Bit_Variant(index);
        case OC_ID_2 :
            return OC_ExistsBufferValue_32Bit_Variant(index);
        case OC_ID_3 :
            return OC_ExistsBufferValue_32Bit_Variant(index);
        case OC_ID_4 :
            return OC_ExistsBufferValue_32Bit_Variant(index);
        case OC_ID_5 :
            return OC_ExistsBufferValue_32Bit_Variant(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_PulseWidth32BitSet(OC_MODULE_ID index, uint32_t pulseWidth)
{
    switch (index) {
        case OC_ID_1 :
            OC_PulseWidth32BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_2 :
            OC_PulseWidth32BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_3 :
            OC_PulseWidth32BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_4 :
            OC_PulseWidth32BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_5 :
            OC_PulseWidth32BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_OC_PulseWidth16BitSet(OC_MODULE_ID index, uint16_t pulseWidth)
{
    switch (index) {
        case OC_ID_1 :
            OC_PulseWidth16BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_2 :
            OC_PulseWidth16BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_3 :
            OC_PulseWidth16BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_4 :
            OC_PulseWidth16BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_ID_5 :
            OC_PulseWidth16BitSet_32Bit_Variant(index, pulseWidth);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsPulseWidth(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsPulseWidth_32Bit_Variant(index);
        case OC_ID_2 :
            return OC_ExistsPulseWidth_32Bit_Variant(index);
        case OC_ID_3 :
            return OC_ExistsPulseWidth_32Bit_Variant(index);
        case OC_ID_4 :
            return OC_ExistsPulseWidth_32Bit_Variant(index);
        case OC_ID_5 :
            return OC_ExistsPulseWidth_32Bit_Variant(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_BufferSizeSelect(OC_MODULE_ID index, OC_BUFFER_SIZE size)
{
    switch (index) {
        case OC_ID_1 :
            OC_BufferSizeSelect_Default(index, size);
            break;
        case OC_ID_2 :
            OC_BufferSizeSelect_Default(index, size);
            break;
        case OC_ID_3 :
            OC_BufferSizeSelect_Default(index, size);
            break;
        case OC_ID_4 :
            OC_BufferSizeSelect_Default(index, size);
            break;
        case OC_ID_5 :
            OC_BufferSizeSelect_Default(index, size);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsBufferSize(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsBufferSize_Default(index);
        case OC_ID_2 :
            return OC_ExistsBufferSize_Default(index);
        case OC_ID_3 :
            return OC_ExistsBufferSize_Default(index);
        case OC_ID_4 :
            return OC_ExistsBufferSize_Default(index);
        case OC_ID_5 :
            return OC_ExistsBufferSize_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_OC_ModeSelect(OC_MODULE_ID index, OC_COMPARE_MODES cmpMode)
{
    switch (index) {
        case OC_ID_1 :
            OC_ModeSelect_Default(index, cmpMode);
            break;
        case OC_ID_2 :
            OC_ModeSelect_Default(index, cmpMode);
            break;
        case OC_ID_3 :
            OC_ModeSelect_Default(index, cmpMode);
            break;
        case OC_ID_4 :
            OC_ModeSelect_Default(index, cmpMode);
            break;
        case OC_ID_5 :
            OC_ModeSelect_Default(index, cmpMode);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_OC_ExistsCompareModeSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsCompareModeSelect_Default(index);
        case OC_ID_2 :
            return OC_ExistsCompareModeSelect_Default(index);
        case OC_ID_3 :
            return OC_ExistsCompareModeSelect_Default(index);
        case OC_ID_4 :
            return OC_ExistsCompareModeSelect_Default(index);
        case OC_ID_5 :
            return OC_ExistsCompareModeSelect_Default(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_TriggerSet(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_TriggerSet_Unsupported(index);
            break;
        case OC_ID_2 :
            OC_TriggerSet_Unsupported(index);
            break;
        case OC_ID_3 :
            OC_TriggerSet_Unsupported(index);
            break;
        case OC_ID_4 :
            OC_TriggerSet_Unsupported(index);
            break;
        case OC_ID_5 :
            OC_TriggerSet_Unsupported(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_TriggerClear(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_TriggerClear_Unsupported(index);
            break;
        case OC_ID_2 :
            OC_TriggerClear_Unsupported(index);
            break;
        case OC_ID_3 :
            OC_TriggerClear_Unsupported(index);
            break;
        case OC_ID_4 :
            OC_TriggerClear_Unsupported(index);
            break;
        case OC_ID_5 :
            OC_TriggerClear_Unsupported(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsTriggerControl(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsTriggerControl_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsTriggerControl_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsTriggerControl_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsTriggerControl_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsTriggerControl_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_PWMDutyCycleResolutionSet(OC_MODULE_ID index, OC_CLOCK_RESOLUTION clkResolution)
{
    switch (index) {
        case OC_ID_1 :
            OC_PWMDutyCycleResolutionSet_Unsupported(index, clkResolution);
            break;
        case OC_ID_2 :
            OC_PWMDutyCycleResolutionSet_Unsupported(index, clkResolution);
            break;
        case OC_ID_3 :
            OC_PWMDutyCycleResolutionSet_Unsupported(index, clkResolution);
            break;
        case OC_ID_4 :
            OC_PWMDutyCycleResolutionSet_Unsupported(index, clkResolution);
            break;
        case OC_ID_5 :
            OC_PWMDutyCycleResolutionSet_Unsupported(index, clkResolution);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsPWMDutyCycleResolutionControl(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsPWMDutyCycleResolutionControl_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsPWMDutyCycleResolutionControl_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsPWMDutyCycleResolutionControl_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsPWMDutyCycleResolutionControl_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsPWMDutyCycleResolutionControl_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_PolarityInvertedEnable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_PolarityInvertedEnable_Unsupported(index);
            break;
        case OC_ID_2 :
            OC_PolarityInvertedEnable_Unsupported(index);
            break;
        case OC_ID_3 :
            OC_PolarityInvertedEnable_Unsupported(index);
            break;
        case OC_ID_4 :
            OC_PolarityInvertedEnable_Unsupported(index);
            break;
        case OC_ID_5 :
            OC_PolarityInvertedEnable_Unsupported(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_PolarityInvertedDisable(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            OC_PolarityInvertedDisable_Unsupported(index);
            break;
        case OC_ID_2 :
            OC_PolarityInvertedDisable_Unsupported(index);
            break;
        case OC_ID_3 :
            OC_PolarityInvertedDisable_Unsupported(index);
            break;
        case OC_ID_4 :
            OC_PolarityInvertedDisable_Unsupported(index);
            break;
        case OC_ID_5 :
            OC_PolarityInvertedDisable_Unsupported(index);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsPolarityInvert(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsPolarityInvert_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsPolarityInvert_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsPolarityInvert_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsPolarityInvert_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsPolarityInvert_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_FaultModeSelect(OC_MODULE_ID index, OC_FAULT_MODES modes)
{
    switch (index) {
        case OC_ID_1 :
            OC_FaultModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_2 :
            OC_FaultModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_3 :
            OC_FaultModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_4 :
            OC_FaultModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_5 :
            OC_FaultModeSelect_Unsupported(index, modes);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsFaultModeSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsFaultModeSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsFaultModeSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsFaultModeSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsFaultModeSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsFaultModeSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_FaultTristateSelect(OC_MODULE_ID index, OC_FAULT_TRISTATE tristateSel)
{
    switch (index) {
        case OC_ID_1 :
            OC_FaultTristateSelect_Unsupported(index, tristateSel);
            break;
        case OC_ID_2 :
            OC_FaultTristateSelect_Unsupported(index, tristateSel);
            break;
        case OC_ID_3 :
            OC_FaultTristateSelect_Unsupported(index, tristateSel);
            break;
        case OC_ID_4 :
            OC_FaultTristateSelect_Unsupported(index, tristateSel);
            break;
        case OC_ID_5 :
            OC_FaultTristateSelect_Unsupported(index, tristateSel);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsFaultTristateSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsFaultTristateSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsFaultTristateSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsFaultTristateSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsFaultTristateSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsFaultTristateSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_SyncModeSelect(OC_MODULE_ID index, OC_SYNC_MODES mode)
{
    switch (index) {
        case OC_ID_1 :
            OC_SyncModeSelect_Unsupported(index, mode);
            break;
        case OC_ID_2 :
            OC_SyncModeSelect_Unsupported(index, mode);
            break;
        case OC_ID_3 :
            OC_SyncModeSelect_Unsupported(index, mode);
            break;
        case OC_ID_4 :
            OC_SyncModeSelect_Unsupported(index, mode);
            break;
        case OC_ID_5 :
            OC_SyncModeSelect_Unsupported(index, mode);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsSyncModeSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsSyncModeSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsSyncModeSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsSyncModeSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsSyncModeSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsSyncModeSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_SyncSourceSelect(OC_MODULE_ID index, OC_SYNC_SOURCES src)
{
    switch (index) {
        case OC_ID_1 :
            OC_SyncSourceSelect_Unsupported(index, src);
            break;
        case OC_ID_2 :
            OC_SyncSourceSelect_Unsupported(index, src);
            break;
        case OC_ID_3 :
            OC_SyncSourceSelect_Unsupported(index, src);
            break;
        case OC_ID_4 :
            OC_SyncSourceSelect_Unsupported(index, src);
            break;
        case OC_ID_5 :
            OC_SyncSourceSelect_Unsupported(index, src);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsSyncSourceSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsSyncSourceSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsSyncSourceSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsSyncSourceSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsSyncSourceSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsSyncSourceSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_OC_TriggerStatusModeSelect(OC_MODULE_ID index, OC_TRIGGER_STATUS_MODES modes)
{
    switch (index) {
        case OC_ID_1 :
            OC_TriggerStatusModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_2 :
            OC_TriggerStatusModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_3 :
            OC_TriggerStatusModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_4 :
            OC_TriggerStatusModeSelect_Unsupported(index, modes);
            break;
        case OC_ID_5 :
            OC_TriggerStatusModeSelect_Unsupported(index, modes);
            break;
        case OC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsTriggerStatusModeSelect(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsTriggerStatusModeSelect_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsTriggerStatusModeSelect_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsTriggerStatusModeSelect_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsTriggerStatusModeSelect_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsTriggerStatusModeSelect_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_IsTriggered(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_IsTriggered_Unsupported(index);
        case OC_ID_2 :
            return OC_IsTriggered_Unsupported(index);
        case OC_ID_3 :
            return OC_IsTriggered_Unsupported(index);
        case OC_ID_4 :
            return OC_IsTriggered_Unsupported(index);
        case OC_ID_5 :
            return OC_IsTriggered_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_OC_ExistsTimerTriggered(OC_MODULE_ID index)
{
    switch (index) {
        case OC_ID_1 :
            return OC_ExistsTimerTriggered_Unsupported(index);
        case OC_ID_2 :
            return OC_ExistsTimerTriggered_Unsupported(index);
        case OC_ID_3 :
            return OC_ExistsTimerTriggered_Unsupported(index);
        case OC_ID_4 :
            return OC_ExistsTimerTriggered_Unsupported(index);
        case OC_ID_5 :
            return OC_ExistsTimerTriggered_Unsupported(index);
        case OC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
