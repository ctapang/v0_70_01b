/* Created by plibgen $Revision: 1.29 $ */

#ifndef _TMR_P32MX450F128H_H
#define _TMR_P32MX450F128H_H

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

    TMR_ID_1 = 0,
    TMR_ID_2,
    TMR_ID_3,
    TMR_ID_4,
    TMR_ID_5,
    TMR_NUMBER_OF_MODULES

} TMR_MODULE_ID;

typedef enum {

    TMR_PRESCALE_VALUE_1 = 0x00,
    TMR_PRESCALE_VALUE_2 = 0x01,
    TMR_PRESCALE_VALUE_4 = 0x02,
    TMR_PRESCALE_VALUE_8 = 0x03,
    TMR_PRESCALE_VALUE_16 = 0x04,
    TMR_PRESCALE_VALUE_32 = 0x05,
    TMR_PRESCALE_VALUE_64 = 0x06,
    TMR_PRESCALE_VALUE_256 = 0x07

} TMR_PRESCALE;

typedef enum {

    TMR_POSTSCALE_NOT_SUPPORTED = 0x00

} TMR_POSTSCALE;

typedef enum {

    TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK = 0,
    TMR_CLOCK_SOURCE_EXTERNAL_INPUT_PIN = 1

} TMR_CLOCK_SOURCE;

typedef enum {

    TMR_GATE_SOURCE_NOT_SUPPORTED = 0x00

} TMR_GATE_SOURCE;

typedef enum {

    TMR_ASSIGNMENT_NOT_SUPPORTED = 0x00

} TMR_ASSIGNMENT;

typedef enum {

    TMR_CLOCK_SOURCE_EDGE_NONE

} TMR_CLOCK_SOURCE_EDGE;

typedef enum {

    TMR_GATE_POLARITY_NOT_SUPPORTED = 0x00

} TMR_GATE_POLARITY;

INLINE SFR_TYPE* _TMR_ENABLE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_STOP_IN_IDLE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_ASYNC_TIMER_WRITE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return (SFR_TYPE*)-1;
        case TMR_ID_3 :
            return (SFR_TYPE*)-1;
        case TMR_ID_4 :
            return (SFR_TYPE*)-1;
        case TMR_ID_5 :
            return (SFR_TYPE*)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_COUNTER_ASYNC_WRITE_IN_PROGRESS_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return (SFR_TYPE*)-1;
        case TMR_ID_3 :
            return (SFR_TYPE*)-1;
        case TMR_ID_4 :
            return (SFR_TYPE*)-1;
        case TMR_ID_5 :
            return (SFR_TYPE*)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_GATED_TIME_ACCUMULATION_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_PRESCALE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_CLOCK_SOURCE_SYNC_INVERTED_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return (SFR_TYPE*)-1;
        case TMR_ID_3 :
            return (SFR_TYPE*)-1;
        case TMR_ID_4 :
            return (SFR_TYPE*)-1;
        case TMR_ID_5 :
            return (SFR_TYPE*)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_CLOCK_SOURCE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &T1CON;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_PERIOD_REGISTER_16BIT_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &PR1;
        case TMR_ID_2 :
            return &PR2;
        case TMR_ID_3 :
            return &PR3;
        case TMR_ID_4 :
            return &PR4;
        case TMR_ID_5 :
            return &PR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_PERIOD_MATCH_MODE_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &PR1;
        case TMR_ID_2 :
            return &TMR2;
        case TMR_ID_3 :
            return &TMR3;
        case TMR_ID_4 :
            return &TMR4;
        case TMR_ID_5 :
            return &TMR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_VALUE_REGISTER_16BIT_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return &TMR1;
        case TMR_ID_2 :
            return &TMR2;
        case TMR_ID_3 :
            return &TMR3;
        case TMR_ID_4 :
            return &TMR4;
        case TMR_ID_5 :
            return &TMR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_MODE_16BIT_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_TYPE*)-1;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_MODE_32BIT_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_TYPE*)-1;
        case TMR_ID_2 :
            return &T2CON;
        case TMR_ID_3 :
            return &T3CON;
        case TMR_ID_4 :
            return &T4CON;
        case TMR_ID_5 :
            return &T5CON;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_PERIOD_REGISTER_16BIT_LOW_32_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_TYPE*)-1;
        case TMR_ID_2 :
            return &PR2;
        case TMR_ID_3 :
            return &PR3;
        case TMR_ID_4 :
            return &PR4;
        case TMR_ID_5 :
            return &PR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}


INLINE SFR_TYPE* _TMR_PERIOD_REGISTER_16BIT_HIGH_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_TYPE*)-1;
        case TMR_ID_2 :
            return (SFR_TYPE*)-1;
        case TMR_ID_4 :
            return (SFR_TYPE*)-1;
        case TMR_ID_3 :
            return &PR3;
        case TMR_ID_5 :
            return &PR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _TMR_VALUE_REGISTER_16BIT_LOW_VREG(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_TYPE*)-1;
        case TMR_ID_2 :
            return &TMR2;
        case TMR_ID_3 :
            return &TMR3;
        case TMR_ID_4 :
            return &TMR4;
        case TMR_ID_5 :
            return &TMR5;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _TMR_ENABLE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_ON_MASK;
        case TMR_ID_2 :
            return _T2CON_ON_MASK;
        case TMR_ID_3 :
            return _T3CON_ON_MASK;
        case TMR_ID_4 :
            return _T4CON_ON_MASK;
        case TMR_ID_5 :
            return _T5CON_ON_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_STOP_IN_IDLE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_SIDL_MASK;
        case TMR_ID_2 :
            return _T2CON_SIDL_MASK;
        case TMR_ID_3 :
            return _T3CON_SIDL_MASK;
        case TMR_ID_4 :
            return _T4CON_SIDL_MASK;
        case TMR_ID_5 :
            return _T5CON_SIDL_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_ASYNC_TIMER_WRITE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWDIS_MASK;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_COUNTER_ASYNC_WRITE_IN_PROGRESS_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWIP_MASK;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_GATED_TIME_ACCUMULATION_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TGATE_MASK;
        case TMR_ID_2 :
            return _T2CON_TGATE_MASK;
        case TMR_ID_3 :
            return _T3CON_TGATE_MASK;
        case TMR_ID_4 :
            return _T4CON_TGATE_MASK;
        case TMR_ID_5 :
            return _T5CON_TGATE_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PRESCALE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCKPS_MASK;
        case TMR_ID_2 :
            return _T2CON_TCKPS_MASK;
        case TMR_ID_3 :
            return _T3CON_TCKPS_MASK;
        case TMR_ID_4 :
            return _T4CON_TCKPS_MASK;
        case TMR_ID_5 :
            return _T5CON_TCKPS_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_SYNC_INVERTED_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TSYNC_MASK;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCS_MASK;
        case TMR_ID_2 :
            return _T2CON_TCS_MASK;
        case TMR_ID_3 :
            return _T3CON_TCS_MASK;
        case TMR_ID_4 :
            return _T4CON_TCS_MASK;
        case TMR_ID_5 :
            return _T5CON_TCS_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_MATCH_MODE_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_16BIT_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_MASK;
        case TMR_ID_3 :
            return _T3CON_T32_MASK;
        case TMR_ID_4 :
            return _T4CON_T32_MASK;
        case TMR_ID_5 :
            return _T5CON_T32_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_32BIT_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_MASK;
        case TMR_ID_3 :
            return _T3CON_T32_MASK;
        case TMR_ID_4 :
            return _T4CON_T32_MASK;
        case TMR_ID_5 :
            return _T5CON_T32_MASK;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_LOW_32_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_LOW_MASK(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_ENABLE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_ON_POSITION;
        case TMR_ID_2 :
            return _T2CON_ON_POSITION;
        case TMR_ID_3 :
            return _T3CON_ON_POSITION;
        case TMR_ID_4 :
            return _T4CON_ON_POSITION;
        case TMR_ID_5 :
            return _T5CON_ON_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_STOP_IN_IDLE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_SIDL_POSITION;
        case TMR_ID_2 :
            return _T2CON_SIDL_POSITION;
        case TMR_ID_3 :
            return _T3CON_SIDL_POSITION;
        case TMR_ID_4 :
            return _T4CON_SIDL_POSITION;
        case TMR_ID_5 :
            return _T5CON_SIDL_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_ASYNC_TIMER_WRITE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWDIS_POSITION;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_COUNTER_ASYNC_WRITE_IN_PROGRESS_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWIP_POSITION;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_GATED_TIME_ACCUMULATION_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TGATE_POSITION;
        case TMR_ID_2 :
            return _T2CON_TGATE_POSITION;
        case TMR_ID_3 :
            return _T3CON_TGATE_POSITION;
        case TMR_ID_4 :
            return _T4CON_TGATE_POSITION;
        case TMR_ID_5 :
            return _T5CON_TGATE_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PRESCALE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCKPS_POSITION;
        case TMR_ID_2 :
            return _T2CON_TCKPS_POSITION;
        case TMR_ID_3 :
            return _T3CON_TCKPS_POSITION;
        case TMR_ID_4 :
            return _T4CON_TCKPS_POSITION;
        case TMR_ID_5 :
            return _T5CON_TCKPS_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_SYNC_INVERTED_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TSYNC_POSITION;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCS_POSITION;
        case TMR_ID_2 :
            return _T2CON_TCS_POSITION;
        case TMR_ID_3 :
            return _T3CON_TCS_POSITION;
        case TMR_ID_4 :
            return _T4CON_TCS_POSITION;
        case TMR_ID_5 :
            return _T5CON_TCS_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)0;
        case TMR_ID_2 :
            return (SFR_DATA)0;
        case TMR_ID_3 :
            return (SFR_DATA)0;
        case TMR_ID_4 :
            return (SFR_DATA)0;
        case TMR_ID_5 :
            return (SFR_DATA)0;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_MATCH_MODE_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)0;
        case TMR_ID_2 :
            return (SFR_DATA)0;
        case TMR_ID_3 :
            return (SFR_DATA)0;
        case TMR_ID_4 :
            return (SFR_DATA)0;
        case TMR_ID_5 :
            return (SFR_DATA)0;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)0;
        case TMR_ID_2 :
            return (SFR_DATA)0;
        case TMR_ID_3 :
            return (SFR_DATA)0;
        case TMR_ID_4 :
            return (SFR_DATA)0;
        case TMR_ID_5 :
            return (SFR_DATA)0;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_16BIT_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_POSITION;
        case TMR_ID_3 :
            return _T3CON_T32_POSITION;
        case TMR_ID_4 :
            return _T4CON_T32_POSITION;
        case TMR_ID_5 :
            return _T5CON_T32_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_32BIT_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_POSITION;
        case TMR_ID_3 :
            return _T3CON_T32_POSITION;
        case TMR_ID_4 :
            return _T4CON_T32_POSITION;
        case TMR_ID_5 :
            return _T5CON_T32_POSITION;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_LOW_32_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)0;
        case TMR_ID_3 :
            return (SFR_DATA)0;
        case TMR_ID_4 :
            return (SFR_DATA)0;
        case TMR_ID_5 :
            return (SFR_DATA)0;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_LOW_POS(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)0;
        case TMR_ID_3 :
            return (SFR_DATA)0;
        case TMR_ID_4 :
            return (SFR_DATA)0;
        case TMR_ID_5 :
            return (SFR_DATA)0;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_ENABLE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_ON_LENGTH;
        case TMR_ID_2 :
            return _T2CON_ON_LENGTH;
        case TMR_ID_3 :
            return _T3CON_ON_LENGTH;
        case TMR_ID_4 :
            return _T4CON_ON_LENGTH;
        case TMR_ID_5 :
            return _T5CON_ON_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_STOP_IN_IDLE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_SIDL_LENGTH;
        case TMR_ID_2 :
            return _T2CON_SIDL_LENGTH;
        case TMR_ID_3 :
            return _T3CON_SIDL_LENGTH;
        case TMR_ID_4 :
            return _T4CON_SIDL_LENGTH;
        case TMR_ID_5 :
            return _T5CON_SIDL_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_ASYNC_TIMER_WRITE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWDIS_LENGTH;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_COUNTER_ASYNC_WRITE_IN_PROGRESS_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TWIP_LENGTH;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_GATED_TIME_ACCUMULATION_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TGATE_LENGTH;
        case TMR_ID_2 :
            return _T2CON_TGATE_LENGTH;
        case TMR_ID_3 :
            return _T3CON_TGATE_LENGTH;
        case TMR_ID_4 :
            return _T4CON_TGATE_LENGTH;
        case TMR_ID_5 :
            return _T5CON_TGATE_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PRESCALE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCKPS_LENGTH;
        case TMR_ID_2 :
            return _T2CON_TCKPS_LENGTH;
        case TMR_ID_3 :
            return _T3CON_TCKPS_LENGTH;
        case TMR_ID_4 :
            return _T4CON_TCKPS_LENGTH;
        case TMR_ID_5 :
            return _T5CON_TCKPS_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_SYNC_INVERTED_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TSYNC_LENGTH;
        case TMR_ID_2 :
            return (SFR_DATA)-1;
        case TMR_ID_3 :
            return (SFR_DATA)-1;
        case TMR_ID_4 :
            return (SFR_DATA)-1;
        case TMR_ID_5 :
            return (SFR_DATA)-1;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_CLOCK_SOURCE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return _T1CON_TCS_LENGTH;
        case TMR_ID_2 :
            return _T2CON_TCS_LENGTH;
        case TMR_ID_3 :
            return _T3CON_TCS_LENGTH;
        case TMR_ID_4 :
            return _T4CON_TCS_LENGTH;
        case TMR_ID_5 :
            return _T5CON_TCS_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_MATCH_MODE_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_16BIT_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_LENGTH;
        case TMR_ID_3 :
            return _T3CON_T32_LENGTH;
        case TMR_ID_4 :
            return _T4CON_T32_LENGTH;
        case TMR_ID_5 :
            return _T5CON_T32_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_MODE_32BIT_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return _T2CON_T32_LENGTH;
        case TMR_ID_3 :
            return _T3CON_T32_LENGTH;
        case TMR_ID_4 :
            return _T4CON_T32_LENGTH;
        case TMR_ID_5 :
            return _T5CON_T32_LENGTH;
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_PERIOD_REGISTER_16BIT_LOW_32_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _TMR_VALUE_REGISTER_16BIT_LOW_LEN(TMR_MODULE_ID i)
{
    switch (i) {
        case TMR_ID_1 :
            return (SFR_DATA)-1;
        case TMR_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/tmr_GatedTimeAccumulation_Default.h"
#include "../templates/tmr_GatePolarity_Unsupported.h"
#include "../templates/tmr_GateToggleMode_Unsupported.h"
#include "../templates/tmr_GateSinglePulseMode_Unsupported.h"
#include "../templates/tmr_GateSinglePulseAcquisition_Unsupported.h"
#include "../templates/tmr_GateCurrentState_Unsupported.h"
#include "../templates/tmr_GateSource_Unsupported.h"
#include "../templates/tmr_ClockSource_Default.h"
#include "../templates/tmr_TimerOscillator_Unsupported.h"
#include "../templates/tmr_Prescale_Default.h"
#include "../templates/tmr_ClockSourceSync_Inverted.h"
#include "../templates/tmr_ClockSourceSync_Unsupported.h"
#include "../templates/tmr_Mode8Bit_Unsupported.h"
#include "../templates/tmr_Mode16Bit_Unsupported.h"
#include "../templates/tmr_Mode16Bit_Default.h"
#include "../templates/tmr_Mode32Bit_Unsupported.h"
#include "../templates/tmr_Mode32Bit_Default.h"
#include "../templates/tmr_EnableControl_Default.h"
#include "../templates/tmr_Postscale_Unsupported.h"
#include "../templates/tmr_ClockSourceEdge_Unsupported.h"
#include "../templates/tmr_PrescalerControl_Unsupported.h"
#include "../templates/tmr_StopInIdle_Default.h"
#include "../templates/tmr_TimerAssignment_Unsupported.h"
#include "../templates/tmr_OperationInSleep_Unsupported.h"
#include "../templates/tmr_TriggerEventReset_Unsupported.h"
#include "../templates/tmr_CountMode_Unsupported.h"
#include "../templates/tmr_Counter8bit_Unsupported.h"
#include "../templates/tmr_Counter16Bit_In16BitRegister.h"
#include "../templates/tmr_Counter32Bit_Unsupported.h"
#include "../templates/tmr_Counter32Bit_In16BitRegister.h"
#include "../templates/tmr_Period8Bit_Unsupported.h"
#include "../templates/tmr_Period16Bit_In16BitRegister.h"
#include "../templates/tmr_Period32Bit_Unsupported.h"
#include "../templates/tmr_Period32Bit_In16BitRegister_pic32.h"
#include "../templates/tmr_CounterAsyncWriteControl_Default.h"
#include "../templates/tmr_CounterAsyncWriteControl_Unsupported.h"
#include "../templates/tmr_CounterAsyncWriteInProgress_Default.h"
#include "../templates/tmr_CounterAsyncWriteInProgress_Unsupported.h"
#include "../templates/tmr_SystemClockStatus_Unsupported.h"
#include "../templates/tmr_TimerOperationMode_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_TMR_GateEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateEnable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_GateEnable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_GateEnable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_GateEnable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_GateEnable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_TMR_GateDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateDisable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_GateDisable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_GateDisable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_GateDisable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_GateDisable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsGatedTimeAccumulation(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGatedTimeAccumulation_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsGatedTimeAccumulation_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsGatedTimeAccumulation_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsGatedTimeAccumulation_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsGatedTimeAccumulation_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GatePolaritySelect(TMR_MODULE_ID index, TMR_GATE_POLARITY polarity)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GatePolaritySelect_Unsupported(index, polarity);
            break;
        case TMR_ID_2 :
            TMR_GatePolaritySelect_Unsupported(index, polarity);
            break;
        case TMR_ID_3 :
            TMR_GatePolaritySelect_Unsupported(index, polarity);
            break;
        case TMR_ID_4 :
            TMR_GatePolaritySelect_Unsupported(index, polarity);
            break;
        case TMR_ID_5 :
            TMR_GatePolaritySelect_Unsupported(index, polarity);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGatePolarity(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGatePolarity_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGatePolarity_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGatePolarity_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGatePolarity_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGatePolarity_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateToggleModeEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateToggleModeEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_GateToggleModeEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_GateToggleModeEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_GateToggleModeEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_GateToggleModeEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateToggleModeDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateToggleModeDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_GateToggleModeDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_GateToggleModeDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_GateToggleModeDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_GateToggleModeDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGateToggleMode(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGateToggleMode_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGateToggleMode_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGateToggleMode_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGateToggleMode_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGateToggleMode_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateSinglePulseModeEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateSinglePulseModeEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_GateSinglePulseModeEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_GateSinglePulseModeEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_GateSinglePulseModeEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_GateSinglePulseModeEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateSinglePulseModeDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateSinglePulseModeDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_GateSinglePulseModeDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_GateSinglePulseModeDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_GateSinglePulseModeDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_GateSinglePulseModeDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGateSinglePulseMode(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGateSinglePulseMode_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGateSinglePulseMode_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGateSinglePulseMode_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGateSinglePulseMode_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGateSinglePulseMode_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateSinglePulseAcquisitionStart(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateSinglePulseAcquisitionStart_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_GateSinglePulseAcquisitionStart_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_GateSinglePulseAcquisitionStart_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_GateSinglePulseAcquisitionStart_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_GateSinglePulseAcquisitionStart_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_GateSinglePulseAcquisitionHasCompleted(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_GateSinglePulseAcquisitionHasCompleted_Unsupported(index);
        case TMR_ID_2 :
            return TMR_GateSinglePulseAcquisitionHasCompleted_Unsupported(index);
        case TMR_ID_3 :
            return TMR_GateSinglePulseAcquisitionHasCompleted_Unsupported(index);
        case TMR_ID_4 :
            return TMR_GateSinglePulseAcquisitionHasCompleted_Unsupported(index);
        case TMR_ID_5 :
            return TMR_GateSinglePulseAcquisitionHasCompleted_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGateSinglePulseAcqusition(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGateSinglePulseAcqusition_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGateSinglePulseAcqusition_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGateSinglePulseAcqusition_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGateSinglePulseAcqusition_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGateSinglePulseAcqusition_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_GateCurrentStateGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_GateCurrentStateGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_GateCurrentStateGet_Unsupported(index);
        case TMR_ID_3 :
            return TMR_GateCurrentStateGet_Unsupported(index);
        case TMR_ID_4 :
            return TMR_GateCurrentStateGet_Unsupported(index);
        case TMR_ID_5 :
            return TMR_GateCurrentStateGet_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGateCurrentState(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGateCurrentState_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGateCurrentState_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGateCurrentState_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGateCurrentState_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGateCurrentState_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_GateSourceSelect(TMR_MODULE_ID index, TMR_GATE_SOURCE source)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_GateSourceSelect_Unsupported(index, source);
            break;
        case TMR_ID_2 :
            TMR_GateSourceSelect_Unsupported(index, source);
            break;
        case TMR_ID_3 :
            TMR_GateSourceSelect_Unsupported(index, source);
            break;
        case TMR_ID_4 :
            TMR_GateSourceSelect_Unsupported(index, source);
            break;
        case TMR_ID_5 :
            TMR_GateSourceSelect_Unsupported(index, source);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsGateSource(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsGateSource_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsGateSource_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsGateSource_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsGateSource_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsGateSource_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_ClockSourceSelect(TMR_MODULE_ID index, TMR_CLOCK_SOURCE source)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_ClockSourceSelect_Default(index, source);
            break;
        case TMR_ID_2 :
            TMR_ClockSourceSelect_Default(index, source);
            break;
        case TMR_ID_3 :
            TMR_ClockSourceSelect_Default(index, source);
            break;
        case TMR_ID_4 :
            TMR_ClockSourceSelect_Default(index, source);
            break;
        case TMR_ID_5 :
            TMR_ClockSourceSelect_Default(index, source);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsClockSource(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsClockSource_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsClockSource_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsClockSource_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsClockSource_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsClockSource_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_TimerOscillatorEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_TimerOscillatorEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_TimerOscillatorEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_TimerOscillatorEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_TimerOscillatorEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_TimerOscillatorEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_TimerOscillatorDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_TimerOscillatorDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_TimerOscillatorDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_TimerOscillatorDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_TimerOscillatorDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_TimerOscillatorDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsTimerOscillator(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsTimerOscillator_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsTimerOscillator_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsTimerOscillator_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsTimerOscillator_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsTimerOscillator_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_PrescaleSelect(TMR_MODULE_ID index, TMR_PRESCALE prescale)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_PrescaleSelect_Default(index, prescale);
            break;
        case TMR_ID_2 :
            TMR_PrescaleSelect_Default(index, prescale);
            break;
        case TMR_ID_3 :
            TMR_PrescaleSelect_Default(index, prescale);
            break;
        case TMR_ID_4 :
            TMR_PrescaleSelect_Default(index, prescale);
            break;
        case TMR_ID_5 :
            TMR_PrescaleSelect_Default(index, prescale);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API TMR_PRESCALE PLIB_TMR_PrescaleGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_PrescaleGet_Default(index);
        case TMR_ID_2 :
            return TMR_PrescaleGet_Default(index);
        case TMR_ID_3 :
            return TMR_PrescaleGet_Default(index);
        case TMR_ID_4 :
            return TMR_PrescaleGet_Default(index);
        case TMR_ID_5 :
            return TMR_PrescaleGet_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (TMR_PRESCALE)0;
    }
}

INLINE_API bool PLIB_TMR_ExistsPrescale(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPrescale_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsPrescale_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsPrescale_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsPrescale_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsPrescale_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_ClockSourceExternalSyncEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_ClockSourceExternalSyncEnable_Inverted(index);
            break;
        case TMR_ID_2 :
            TMR_ClockSourceExternalSyncEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_ClockSourceExternalSyncEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_ClockSourceExternalSyncEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_ClockSourceExternalSyncEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_TMR_ClockSourceExternalSyncDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_ClockSourceExternalSyncDisable_Inverted(index);
            break;
        case TMR_ID_2 :
            TMR_ClockSourceExternalSyncDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_ClockSourceExternalSyncDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_ClockSourceExternalSyncDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_ClockSourceExternalSyncDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsClockSourceSync(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsClockSourceSync_Inverted(index);
        case TMR_ID_2 :
            return TMR_ExistsClockSourceSync_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsClockSourceSync_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsClockSourceSync_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsClockSourceSync_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_Mode8BitEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Mode8BitEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_Mode8BitEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_Mode8BitEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_Mode8BitEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_Mode8BitEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsMode8Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsMode8Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsMode8Bit_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsMode8Bit_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsMode8Bit_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsMode8Bit_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Mode16BitEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Mode16BitEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_Mode16BitEnable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_Mode16BitEnable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_Mode16BitEnable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_Mode16BitEnable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsMode16Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsMode16Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsMode16Bit_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsMode16Bit_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsMode16Bit_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsMode16Bit_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Mode32BitEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Mode32BitEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_Mode32BitEnable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_Mode32BitEnable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_Mode32BitEnable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_Mode32BitEnable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsMode32Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsMode32Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsMode32Bit_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsMode32Bit_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsMode32Bit_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsMode32Bit_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Start(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Start_Default(index);
            break;
        case TMR_ID_2 :
            TMR_Start_Default(index);
            break;
        case TMR_ID_3 :
            TMR_Start_Default(index);
            break;
        case TMR_ID_4 :
            TMR_Start_Default(index);
            break;
        case TMR_ID_5 :
            TMR_Start_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_TMR_Stop(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Stop_Default(index);
            break;
        case TMR_ID_2 :
            TMR_Stop_Default(index);
            break;
        case TMR_ID_3 :
            TMR_Stop_Default(index);
            break;
        case TMR_ID_4 :
            TMR_Stop_Default(index);
            break;
        case TMR_ID_5 :
            TMR_Stop_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsEnableControl(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsEnableControl_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsEnableControl_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsEnableControl_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsEnableControl_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsEnableControl_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_PostscaleSelect(TMR_MODULE_ID index, TMR_POSTSCALE postscale)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_PostscaleSelect_Unsupported(index, postscale);
            break;
        case TMR_ID_2 :
            TMR_PostscaleSelect_Unsupported(index, postscale);
            break;
        case TMR_ID_3 :
            TMR_PostscaleSelect_Unsupported(index, postscale);
            break;
        case TMR_ID_4 :
            TMR_PostscaleSelect_Unsupported(index, postscale);
            break;
        case TMR_ID_5 :
            TMR_PostscaleSelect_Unsupported(index, postscale);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API TMR_POSTSCALE _PLIB_UNSUPPORTED PLIB_TMR_PostscaleGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_PostscaleGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_PostscaleGet_Unsupported(index);
        case TMR_ID_3 :
            return TMR_PostscaleGet_Unsupported(index);
        case TMR_ID_4 :
            return TMR_PostscaleGet_Unsupported(index);
        case TMR_ID_5 :
            return TMR_PostscaleGet_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (TMR_POSTSCALE)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_TMR_PostscaleDivisorGet(TMR_MODULE_ID index, TMR_POSTSCALE postscale)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_PostscaleDivisorGet_Unsupported(index, postscale);
        case TMR_ID_2 :
            return TMR_PostscaleDivisorGet_Unsupported(index, postscale);
        case TMR_ID_3 :
            return TMR_PostscaleDivisorGet_Unsupported(index, postscale);
        case TMR_ID_4 :
            return TMR_PostscaleDivisorGet_Unsupported(index, postscale);
        case TMR_ID_5 :
            return TMR_PostscaleDivisorGet_Unsupported(index, postscale);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsPostscale(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPostscale_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsPostscale_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsPostscale_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsPostscale_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsPostscale_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_ClockSourceEdgeSelect(TMR_MODULE_ID index, TMR_CLOCK_SOURCE_EDGE source)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_ClockSourceEdgeSelect_Unsupported(index, source);
            break;
        case TMR_ID_2 :
            TMR_ClockSourceEdgeSelect_Unsupported(index, source);
            break;
        case TMR_ID_3 :
            TMR_ClockSourceEdgeSelect_Unsupported(index, source);
            break;
        case TMR_ID_4 :
            TMR_ClockSourceEdgeSelect_Unsupported(index, source);
            break;
        case TMR_ID_5 :
            TMR_ClockSourceEdgeSelect_Unsupported(index, source);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API TMR_CLOCK_SOURCE_EDGE _PLIB_UNSUPPORTED PLIB_TMR_ClockSourceEdgeGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ClockSourceEdgeGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ClockSourceEdgeGet_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ClockSourceEdgeGet_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ClockSourceEdgeGet_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ClockSourceEdgeGet_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (TMR_CLOCK_SOURCE_EDGE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsClockSourceEdge(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsClockSourceEdge_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsClockSourceEdge_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsClockSourceEdge_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsClockSourceEdge_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsClockSourceEdge_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_PrescalerEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_PrescalerEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_PrescalerEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_PrescalerEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_PrescalerEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_PrescalerEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_PrescalerDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_PrescalerDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_PrescalerDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_PrescalerDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_PrescalerDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_PrescalerDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsPrescalerAssignment(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPrescalerAssignment_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsPrescalerAssignment_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsPrescalerAssignment_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsPrescalerAssignment_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsPrescalerAssignment_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_StopInIdleEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_StopInIdleEnable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_StopInIdleEnable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_StopInIdleEnable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_StopInIdleEnable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_StopInIdleEnable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_TMR_StopInIdleDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_StopInIdleDisable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_StopInIdleDisable_Default(index);
            break;
        case TMR_ID_3 :
            TMR_StopInIdleDisable_Default(index);
            break;
        case TMR_ID_4 :
            TMR_StopInIdleDisable_Default(index);
            break;
        case TMR_ID_5 :
            TMR_StopInIdleDisable_Default(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsStopInIdleControl(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsStopInIdleControl_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsStopInIdleControl_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsStopInIdleControl_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsStopInIdleControl_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsStopInIdleControl_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_AssignmentSelect(TMR_MODULE_ID index, TMR_ASSIGNMENT tmrNums)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_AssignmentSelect_Unsupported(index, tmrNums);
            break;
        case TMR_ID_2 :
            TMR_AssignmentSelect_Unsupported(index, tmrNums);
            break;
        case TMR_ID_3 :
            TMR_AssignmentSelect_Unsupported(index, tmrNums);
            break;
        case TMR_ID_4 :
            TMR_AssignmentSelect_Unsupported(index, tmrNums);
            break;
        case TMR_ID_5 :
            TMR_AssignmentSelect_Unsupported(index, tmrNums);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsTimerAssignment(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsTimerAssignment_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsTimerAssignment_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsTimerAssignment_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsTimerAssignment_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsTimerAssignment_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_OperateInSleepEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_OperateInSleepEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_OperateInSleepEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_OperateInSleepEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_OperateInSleepEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_OperateInSleepEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_OperateInSleepDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_OperateInSleepDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_OperateInSleepDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_OperateInSleepDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_OperateInSleepDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_OperateInSleepDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsOperationInSleep(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsOperationInSleep_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsOperationInSleep_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsOperationInSleep_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsOperationInSleep_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsOperationInSleep_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_TriggerEventResetEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_TriggerEventResetEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_TriggerEventResetEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_TriggerEventResetEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_TriggerEventResetEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_TriggerEventResetEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_TriggerEventResetDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_TriggerEventResetDisable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_TriggerEventResetDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_TriggerEventResetDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_TriggerEventResetDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_TriggerEventResetDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsTriggerEventReset(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsTriggerEventReset_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsTriggerEventReset_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsTriggerEventReset_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsTriggerEventReset_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsTriggerEventReset_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_ContinousCountModeEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_ContinousCountModeEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_ContinousCountModeEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_ContinousCountModeEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_ContinousCountModeEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_ContinousCountModeEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_SingleShotModeEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_SingleShotModeEnable_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_SingleShotModeEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_SingleShotModeEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_SingleShotModeEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_SingleShotModeEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsCountMode(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCountMode_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsCountMode_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsCountMode_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsCountMode_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsCountMode_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_Counter8BitSet(TMR_MODULE_ID index, uint8_t value)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter8BitSet_Unsupported(index, value);
            break;
        case TMR_ID_2 :
            TMR_Counter8BitSet_Unsupported(index, value);
            break;
        case TMR_ID_3 :
            TMR_Counter8BitSet_Unsupported(index, value);
            break;
        case TMR_ID_4 :
            TMR_Counter8BitSet_Unsupported(index, value);
            break;
        case TMR_ID_5 :
            TMR_Counter8BitSet_Unsupported(index, value);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_TMR_Counter8BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Counter8BitGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_Counter8BitGet_Unsupported(index);
        case TMR_ID_3 :
            return TMR_Counter8BitGet_Unsupported(index);
        case TMR_ID_4 :
            return TMR_Counter8BitGet_Unsupported(index);
        case TMR_ID_5 :
            return TMR_Counter8BitGet_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_Counter8BitClear(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter8BitClear_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_Counter8BitClear_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_Counter8BitClear_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_Counter8BitClear_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_Counter8BitClear_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsCounter8Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCounter8Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsCounter8Bit_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsCounter8Bit_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsCounter8Bit_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsCounter8Bit_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Counter16BitSet(TMR_MODULE_ID index, uint16_t value)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter16BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_2 :
            TMR_Counter16BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_3 :
            TMR_Counter16BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_4 :
            TMR_Counter16BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_5 :
            TMR_Counter16BitSet_In16BitRegister(index, value);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint16_t PLIB_TMR_Counter16BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Counter16BitGet_In16BitRegister(index);
        case TMR_ID_2 :
            return TMR_Counter16BitGet_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_Counter16BitGet_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_Counter16BitGet_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_Counter16BitGet_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API void PLIB_TMR_Counter16BitClear(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter16BitClear_In16BitRegister(index);
            break;
        case TMR_ID_2 :
            TMR_Counter16BitClear_In16BitRegister(index);
            break;
        case TMR_ID_3 :
            TMR_Counter16BitClear_In16BitRegister(index);
            break;
        case TMR_ID_4 :
            TMR_Counter16BitClear_In16BitRegister(index);
            break;
        case TMR_ID_5 :
            TMR_Counter16BitClear_In16BitRegister(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsCounter16Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCounter16Bit_In16BitRegister(index);
        case TMR_ID_2 :
            return TMR_ExistsCounter16Bit_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_ExistsCounter16Bit_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_ExistsCounter16Bit_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_ExistsCounter16Bit_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Counter32BitSet(TMR_MODULE_ID index, uint32_t value)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter32BitSet_Unsupported(index, value);
            break;
        case TMR_ID_2 :
            TMR_Counter32BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_3 :
            TMR_Counter32BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_4 :
            TMR_Counter32BitSet_In16BitRegister(index, value);
            break;
        case TMR_ID_5 :
            TMR_Counter32BitSet_In16BitRegister(index, value);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_TMR_Counter32BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Counter32BitGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_Counter32BitGet_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_Counter32BitGet_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_Counter32BitGet_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_Counter32BitGet_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void PLIB_TMR_Counter32BitClear(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Counter32BitClear_Unsupported(index);
            break;
        case TMR_ID_2 :
            TMR_Counter32BitClear_In16BitRegister(index);
            break;
        case TMR_ID_3 :
            TMR_Counter32BitClear_In16BitRegister(index);
            break;
        case TMR_ID_4 :
            TMR_Counter32BitClear_In16BitRegister(index);
            break;
        case TMR_ID_5 :
            TMR_Counter32BitClear_In16BitRegister(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsCounter32Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCounter32Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsCounter32Bit_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_ExistsCounter32Bit_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_ExistsCounter32Bit_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_ExistsCounter32Bit_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_TMR_Period8BitSet(TMR_MODULE_ID index, uint8_t period)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Period8BitSet_Unsupported(index, period);
            break;
        case TMR_ID_2 :
            TMR_Period8BitSet_Unsupported(index, period);
            break;
        case TMR_ID_3 :
            TMR_Period8BitSet_Unsupported(index, period);
            break;
        case TMR_ID_4 :
            TMR_Period8BitSet_Unsupported(index, period);
            break;
        case TMR_ID_5 :
            TMR_Period8BitSet_Unsupported(index, period);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_TMR_Period8BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Period8BitGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_Period8BitGet_Unsupported(index);
        case TMR_ID_3 :
            return TMR_Period8BitGet_Unsupported(index);
        case TMR_ID_4 :
            return TMR_Period8BitGet_Unsupported(index);
        case TMR_ID_5 :
            return TMR_Period8BitGet_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsPeriod8Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPeriod8Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsPeriod8Bit_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsPeriod8Bit_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsPeriod8Bit_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsPeriod8Bit_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Period16BitSet(TMR_MODULE_ID index, uint16_t period)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Period16BitSet_In16BitRegister(index, period);
            break;
        case TMR_ID_2 :
            TMR_Period16BitSet_In16BitRegister(index, period);
            break;
        case TMR_ID_3 :
            TMR_Period16BitSet_In16BitRegister(index, period);
            break;
        case TMR_ID_4 :
            TMR_Period16BitSet_In16BitRegister(index, period);
            break;
        case TMR_ID_5 :
            TMR_Period16BitSet_In16BitRegister(index, period);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint16_t PLIB_TMR_Period16BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Period16BitGet_In16BitRegister(index);
        case TMR_ID_2 :
            return TMR_Period16BitGet_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_Period16BitGet_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_Period16BitGet_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_Period16BitGet_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_TMR_ExistsPeriod16Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPeriod16Bit_In16BitRegister(index);
        case TMR_ID_2 :
            return TMR_ExistsPeriod16Bit_In16BitRegister(index);
        case TMR_ID_3 :
            return TMR_ExistsPeriod16Bit_In16BitRegister(index);
        case TMR_ID_4 :
            return TMR_ExistsPeriod16Bit_In16BitRegister(index);
        case TMR_ID_5 :
            return TMR_ExistsPeriod16Bit_In16BitRegister(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_Period32BitSet(TMR_MODULE_ID index, uint32_t period)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_Period32BitSet_Unsupported(index, period);
            break;
        case TMR_ID_2 :
            TMR_Period32BitSet_In16BitRegister_pic32(index, period);
            break;
        case TMR_ID_3 :
            TMR_Period32BitSet_In16BitRegister_pic32(index, period);
            break;
        case TMR_ID_4 :
            TMR_Period32BitSet_In16BitRegister_pic32(index, period);
            break;
        case TMR_ID_5 :
            TMR_Period32BitSet_In16BitRegister_pic32(index, period);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_TMR_Period32BitGet(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_Period32BitGet_Unsupported(index);
        case TMR_ID_2 :
            return TMR_Period32BitGet_In16BitRegister_pic32(index);
        case TMR_ID_3 :
            return TMR_Period32BitGet_In16BitRegister_pic32(index);
        case TMR_ID_4 :
            return TMR_Period32BitGet_In16BitRegister_pic32(index);
        case TMR_ID_5 :
            return TMR_Period32BitGet_In16BitRegister_pic32(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_TMR_ExistsPeriod32Bit(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsPeriod32Bit_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsPeriod32Bit_In16BitRegister_pic32(index);
        case TMR_ID_3 :
            return TMR_ExistsPeriod32Bit_In16BitRegister_pic32(index);
        case TMR_ID_4 :
            return TMR_ExistsPeriod32Bit_In16BitRegister_pic32(index);
        case TMR_ID_5 :
            return TMR_ExistsPeriod32Bit_In16BitRegister_pic32(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_TMR_CounterAsyncWriteEnable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_CounterAsyncWriteEnable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_CounterAsyncWriteEnable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_CounterAsyncWriteEnable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_CounterAsyncWriteEnable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_CounterAsyncWriteEnable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_TMR_CounterAsyncWriteDisable(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            TMR_CounterAsyncWriteDisable_Default(index);
            break;
        case TMR_ID_2 :
            TMR_CounterAsyncWriteDisable_Unsupported(index);
            break;
        case TMR_ID_3 :
            TMR_CounterAsyncWriteDisable_Unsupported(index);
            break;
        case TMR_ID_4 :
            TMR_CounterAsyncWriteDisable_Unsupported(index);
            break;
        case TMR_ID_5 :
            TMR_CounterAsyncWriteDisable_Unsupported(index);
            break;
        case TMR_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_TMR_ExistsCounterAsyncWriteControl(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCounterAsyncWriteControl_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsCounterAsyncWriteControl_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsCounterAsyncWriteControl_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsCounterAsyncWriteControl_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsCounterAsyncWriteControl_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_TMR_CounterAsyncWriteInProgress(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_CounterAsyncWriteInProgress_Default(index);
        case TMR_ID_2 :
            return TMR_CounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_3 :
            return TMR_CounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_4 :
            return TMR_CounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_5 :
            return TMR_CounterAsyncWriteInProgress_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_TMR_ExistsCounterAsyncWriteInProgress(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsCounterAsyncWriteInProgress_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsCounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsCounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsCounterAsyncWriteInProgress_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsCounterAsyncWriteInProgress_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_SystemClockFromTimerIsActive(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_SystemClockFromTimerIsActive_Unsupported(index);
        case TMR_ID_2 :
            return TMR_SystemClockFromTimerIsActive_Unsupported(index);
        case TMR_ID_3 :
            return TMR_SystemClockFromTimerIsActive_Unsupported(index);
        case TMR_ID_4 :
            return TMR_SystemClockFromTimerIsActive_Unsupported(index);
        case TMR_ID_5 :
            return TMR_SystemClockFromTimerIsActive_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_TMR_ExistsSystemClockStatus(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsSystemClockStatus_Unsupported(index);
        case TMR_ID_2 :
            return TMR_ExistsSystemClockStatus_Unsupported(index);
        case TMR_ID_3 :
            return TMR_ExistsSystemClockStatus_Unsupported(index);
        case TMR_ID_4 :
            return TMR_ExistsSystemClockStatus_Unsupported(index);
        case TMR_ID_5 :
            return TMR_ExistsSystemClockStatus_Unsupported(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_TMR_IsPeriodMatchBased(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_IsPeriodMatchBased_Default(index);
        case TMR_ID_2 :
            return TMR_IsPeriodMatchBased_Default(index);
        case TMR_ID_3 :
            return TMR_IsPeriodMatchBased_Default(index);
        case TMR_ID_4 :
            return TMR_IsPeriodMatchBased_Default(index);
        case TMR_ID_5 :
            return TMR_IsPeriodMatchBased_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_TMR_ExistsTimerOperationMode(TMR_MODULE_ID index)
{
    switch (index) {
        case TMR_ID_1 :
            return TMR_ExistsTimerOperationMode_Default(index);
        case TMR_ID_2 :
            return TMR_ExistsTimerOperationMode_Default(index);
        case TMR_ID_3 :
            return TMR_ExistsTimerOperationMode_Default(index);
        case TMR_ID_4 :
            return TMR_ExistsTimerOperationMode_Default(index);
        case TMR_ID_5 :
            return TMR_ExistsTimerOperationMode_Default(index);
        case TMR_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
