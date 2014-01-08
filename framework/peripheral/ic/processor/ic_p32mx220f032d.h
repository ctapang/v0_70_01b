/* Created by plibgen $Revision: 1.29 $ */

#ifndef _IC_P32MX220F032D_H
#define _IC_P32MX220F032D_H

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

    IC_ID_1 = 0,
    IC_ID_2,
    IC_ID_3,
    IC_ID_4,
    IC_ID_5,
    IC_NUMBER_OF_MODULES

} IC_MODULE_ID;

typedef enum {

    IC_INPUT_CAPTURE_DISABLE_MODE = 0,
    IC_INPUT_CAPTURE_EDGE_DETECT_MODE = 1,
    IC_INPUT_CAPTURE_FALLING_EDGE_MODE = 2,
    IC_INPUT_CAPTURE_RISING_EDGE_MODE = 3,
    IC_INPUT_CAPTURE_EVERY_4TH_EDGE_MODE = 4,
    IC_INPUT_CAPTURE_EVERY_16TH_EDGE_MODE = 5,
    IC_INPUT_CAPTURE_EVERY_EDGE_MODE = 6,
    IC_INPUT_CAPTURE_INTERRUPT_MODE = 7

} IC_INPUT_CAPTURE_MODES;

typedef enum {

    IC_BUFFER_SIZE_16BIT = 0,
    IC_BUFFER_SIZE_32BIT = 1

} IC_BUFFER_SIZE;

typedef enum {

    IC_CLOCK_SOURCE_NOT_SUPPORTED = 0

} IC_CLOCK_SOURCES;

typedef enum {

    IC_SYNC_MODE_INPUT_NOT_SUPPORTED = 0

} IC_SYNC_MODE_INPUTS;

typedef enum {

    IC_SYNC_MODE_NOT_SUPPORTED = 0

} IC_SYNC_MODES;

typedef enum {

    IC_EDGE_FALLING = 0,
    IC_EDGE_RISING = 1

} IC_EDGE_TYPES;

typedef enum {

    IC_TIMER_TMR3 = 0,
    IC_TIMER_TMR2 = 1

} IC_TIMERS;

typedef enum {

    IC_INTERRUPT_ON_EVERY_CAPTURE_EVENT = 0,
    IC_INTERRUPT_ON_EVERY_2ND_CAPTURE_EVENT = 1,
    IC_INTERRUPT_ON_EVERY_3RD_CAPTURE_EVENT = 2,
    IC_INTERRUPT_ON_EVERY_4TH_CAPTURE_EVENT = 3

} IC_EVENTS_PER_INTERRUPT;

INLINE SFR_TYPE* _IC_ENABLE_CONTROL_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_STOP_IN_IDLE_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_EDGE_CAPTURE_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_BUFFER_SIZE_SET_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_TIMER_SELECT_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_EVENTS_PER_INTERRUPT_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_BUFFER_OVERFLOW_STATUS_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_BUFFER_IS_EMPTY_STATUS_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_CAPTURE_MODE_SELECT_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1CON;
        case IC_ID_2 :
            return &IC2CON;
        case IC_ID_3 :
            return &IC3CON;
        case IC_ID_4 :
            return &IC4CON;
        case IC_ID_5 :
            return &IC5CON;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _IC_BUFFER_32BIT_VALUE_VREG(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return &IC1BUF;
        case IC_ID_2 :
            return &IC2BUF;
        case IC_ID_3 :
            return &IC3BUF;
        case IC_ID_4 :
            return &IC4BUF;
        case IC_ID_5 :
            return &IC5BUF;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _IC_ENABLE_CONTROL_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ON_MASK;
        case IC_ID_2 :
            return _IC2CON_ON_MASK;
        case IC_ID_3 :
            return _IC3CON_ON_MASK;
        case IC_ID_4 :
            return _IC4CON_ON_MASK;
        case IC_ID_5 :
            return _IC5CON_ON_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_STOP_IN_IDLE_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_SIDL_MASK;
        case IC_ID_2 :
            return _IC2CON_SIDL_MASK;
        case IC_ID_3 :
            return _IC3CON_SIDL_MASK;
        case IC_ID_4 :
            return _IC4CON_SIDL_MASK;
        case IC_ID_5 :
            return _IC5CON_SIDL_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EDGE_CAPTURE_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_FEDGE_MASK;
        case IC_ID_2 :
            return _IC2CON_FEDGE_MASK;
        case IC_ID_3 :
            return _IC3CON_FEDGE_MASK;
        case IC_ID_4 :
            return _IC4CON_FEDGE_MASK;
        case IC_ID_5 :
            return _IC5CON_FEDGE_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_SIZE_SET_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_C32_MASK;
        case IC_ID_2 :
            return _IC2CON_C32_MASK;
        case IC_ID_3 :
            return _IC3CON_C32_MASK;
        case IC_ID_4 :
            return _IC4CON_C32_MASK;
        case IC_ID_5 :
            return _IC5CON_C32_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_TIMER_SELECT_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICTMR_MASK;
        case IC_ID_2 :
            return _IC2CON_ICTMR_MASK;
        case IC_ID_3 :
            return _IC3CON_ICTMR_MASK;
        case IC_ID_4 :
            return _IC4CON_ICTMR_MASK;
        case IC_ID_5 :
            return _IC5CON_ICTMR_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EVENTS_PER_INTERRUPT_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICI_MASK;
        case IC_ID_2 :
            return _IC2CON_ICI_MASK;
        case IC_ID_3 :
            return _IC3CON_ICI_MASK;
        case IC_ID_4 :
            return _IC4CON_ICI_MASK;
        case IC_ID_5 :
            return _IC5CON_ICI_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_OVERFLOW_STATUS_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICOV_MASK;
        case IC_ID_2 :
            return _IC2CON_ICOV_MASK;
        case IC_ID_3 :
            return _IC3CON_ICOV_MASK;
        case IC_ID_4 :
            return _IC4CON_ICOV_MASK;
        case IC_ID_5 :
            return _IC5CON_ICOV_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_IS_EMPTY_STATUS_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICBNE_MASK;
        case IC_ID_2 :
            return _IC2CON_ICBNE_MASK;
        case IC_ID_3 :
            return _IC3CON_ICBNE_MASK;
        case IC_ID_4 :
            return _IC4CON_ICBNE_MASK;
        case IC_ID_5 :
            return _IC5CON_ICBNE_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_CAPTURE_MODE_SELECT_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICM_MASK;
        case IC_ID_2 :
            return _IC2CON_ICM_MASK;
        case IC_ID_3 :
            return _IC3CON_ICM_MASK;
        case IC_ID_4 :
            return _IC4CON_ICM_MASK;
        case IC_ID_5 :
            return _IC5CON_ICM_MASK;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_32BIT_VALUE_MASK(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return (SFR_DATA)-1;
        case IC_ID_2 :
            return (SFR_DATA)-1;
        case IC_ID_3 :
            return (SFR_DATA)-1;
        case IC_ID_4 :
            return (SFR_DATA)-1;
        case IC_ID_5 :
            return (SFR_DATA)-1;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_ENABLE_CONTROL_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ON_POSITION;
        case IC_ID_2 :
            return _IC2CON_ON_POSITION;
        case IC_ID_3 :
            return _IC3CON_ON_POSITION;
        case IC_ID_4 :
            return _IC4CON_ON_POSITION;
        case IC_ID_5 :
            return _IC5CON_ON_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_STOP_IN_IDLE_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_SIDL_POSITION;
        case IC_ID_2 :
            return _IC2CON_SIDL_POSITION;
        case IC_ID_3 :
            return _IC3CON_SIDL_POSITION;
        case IC_ID_4 :
            return _IC4CON_SIDL_POSITION;
        case IC_ID_5 :
            return _IC5CON_SIDL_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EDGE_CAPTURE_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_FEDGE_POSITION;
        case IC_ID_2 :
            return _IC2CON_FEDGE_POSITION;
        case IC_ID_3 :
            return _IC3CON_FEDGE_POSITION;
        case IC_ID_4 :
            return _IC4CON_FEDGE_POSITION;
        case IC_ID_5 :
            return _IC5CON_FEDGE_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_SIZE_SET_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_C32_POSITION;
        case IC_ID_2 :
            return _IC2CON_C32_POSITION;
        case IC_ID_3 :
            return _IC3CON_C32_POSITION;
        case IC_ID_4 :
            return _IC4CON_C32_POSITION;
        case IC_ID_5 :
            return _IC5CON_C32_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_TIMER_SELECT_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICTMR_POSITION;
        case IC_ID_2 :
            return _IC2CON_ICTMR_POSITION;
        case IC_ID_3 :
            return _IC3CON_ICTMR_POSITION;
        case IC_ID_4 :
            return _IC4CON_ICTMR_POSITION;
        case IC_ID_5 :
            return _IC5CON_ICTMR_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EVENTS_PER_INTERRUPT_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICI_POSITION;
        case IC_ID_2 :
            return _IC2CON_ICI_POSITION;
        case IC_ID_3 :
            return _IC3CON_ICI_POSITION;
        case IC_ID_4 :
            return _IC4CON_ICI_POSITION;
        case IC_ID_5 :
            return _IC5CON_ICI_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_OVERFLOW_STATUS_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICOV_POSITION;
        case IC_ID_2 :
            return _IC2CON_ICOV_POSITION;
        case IC_ID_3 :
            return _IC3CON_ICOV_POSITION;
        case IC_ID_4 :
            return _IC4CON_ICOV_POSITION;
        case IC_ID_5 :
            return _IC5CON_ICOV_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_IS_EMPTY_STATUS_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICBNE_POSITION;
        case IC_ID_2 :
            return _IC2CON_ICBNE_POSITION;
        case IC_ID_3 :
            return _IC3CON_ICBNE_POSITION;
        case IC_ID_4 :
            return _IC4CON_ICBNE_POSITION;
        case IC_ID_5 :
            return _IC5CON_ICBNE_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_CAPTURE_MODE_SELECT_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICM_POSITION;
        case IC_ID_2 :
            return _IC2CON_ICM_POSITION;
        case IC_ID_3 :
            return _IC3CON_ICM_POSITION;
        case IC_ID_4 :
            return _IC4CON_ICM_POSITION;
        case IC_ID_5 :
            return _IC5CON_ICM_POSITION;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_32BIT_VALUE_POS(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return (SFR_DATA)0;
        case IC_ID_2 :
            return (SFR_DATA)0;
        case IC_ID_3 :
            return (SFR_DATA)0;
        case IC_ID_4 :
            return (SFR_DATA)0;
        case IC_ID_5 :
            return (SFR_DATA)0;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_ENABLE_CONTROL_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ON_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ON_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ON_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ON_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ON_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_STOP_IN_IDLE_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_SIDL_LENGTH;
        case IC_ID_2 :
            return _IC2CON_SIDL_LENGTH;
        case IC_ID_3 :
            return _IC3CON_SIDL_LENGTH;
        case IC_ID_4 :
            return _IC4CON_SIDL_LENGTH;
        case IC_ID_5 :
            return _IC5CON_SIDL_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EDGE_CAPTURE_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_FEDGE_LENGTH;
        case IC_ID_2 :
            return _IC2CON_FEDGE_LENGTH;
        case IC_ID_3 :
            return _IC3CON_FEDGE_LENGTH;
        case IC_ID_4 :
            return _IC4CON_FEDGE_LENGTH;
        case IC_ID_5 :
            return _IC5CON_FEDGE_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_SIZE_SET_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_C32_LENGTH;
        case IC_ID_2 :
            return _IC2CON_C32_LENGTH;
        case IC_ID_3 :
            return _IC3CON_C32_LENGTH;
        case IC_ID_4 :
            return _IC4CON_C32_LENGTH;
        case IC_ID_5 :
            return _IC5CON_C32_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_TIMER_SELECT_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICTMR_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ICTMR_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ICTMR_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ICTMR_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ICTMR_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_EVENTS_PER_INTERRUPT_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICI_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ICI_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ICI_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ICI_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ICI_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_OVERFLOW_STATUS_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICOV_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ICOV_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ICOV_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ICOV_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ICOV_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_IS_EMPTY_STATUS_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICBNE_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ICBNE_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ICBNE_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ICBNE_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ICBNE_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_CAPTURE_MODE_SELECT_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return _IC1CON_ICM_LENGTH;
        case IC_ID_2 :
            return _IC2CON_ICM_LENGTH;
        case IC_ID_3 :
            return _IC3CON_ICM_LENGTH;
        case IC_ID_4 :
            return _IC4CON_ICM_LENGTH;
        case IC_ID_5 :
            return _IC5CON_ICM_LENGTH;
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _IC_BUFFER_32BIT_VALUE_LEN(IC_MODULE_ID i)
{
    switch (i) {
        case IC_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case IC_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case IC_ID_3 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case IC_ID_4 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case IC_ID_5 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case IC_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/ic_EnableControl_Default.h"
#include "../templates/ic_AlternateClock_Default.h"
#include "../templates/ic_StopInIdle_Default.h"
#include "../templates/ic_EdgeCapture_Default.h"
#include "../templates/ic_EventsPerInterruptSelect_Default.h"
#include "../templates/ic_BufferValue_32Bit_Variant.h"
#include "../templates/ic_BufferIsEmptyStatus_Default.h"
#include "../templates/ic_BufferOverflowStatus_Default.h"
#include "../templates/ic_CaptureMode_Default.h"
#include "../templates/ic_BufferSize_Default.h"
#include "../templates/ic_TimerSelect_Default.h"
#include "../templates/ic_ClockSource_Unsupported.h"
#include "../templates/ic_SyncMode_Unsupported.h"
#include "../templates/ic_SyncModeInput_Unsupported.h"
#include "../templates/ic_TimerTriggered_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_IC_Enable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_Enable_Default(index);
            break;
        case IC_ID_2 :
            IC_Enable_Default(index);
            break;
        case IC_ID_3 :
            IC_Enable_Default(index);
            break;
        case IC_ID_4 :
            IC_Enable_Default(index);
            break;
        case IC_ID_5 :
            IC_Enable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_IC_Disable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_Disable_Default(index);
            break;
        case IC_ID_2 :
            IC_Disable_Default(index);
            break;
        case IC_ID_3 :
            IC_Disable_Default(index);
            break;
        case IC_ID_4 :
            IC_Disable_Default(index);
            break;
        case IC_ID_5 :
            IC_Disable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsEnable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsEnable_Default(index);
        case IC_ID_2 :
            return IC_ExistsEnable_Default(index);
        case IC_ID_3 :
            return IC_ExistsEnable_Default(index);
        case IC_ID_4 :
            return IC_ExistsEnable_Default(index);
        case IC_ID_5 :
            return IC_ExistsEnable_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_AlternateClockEnable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_AlternateClockEnable_Default(index);
            break;
        case IC_ID_2 :
            IC_AlternateClockEnable_Default(index);
            break;
        case IC_ID_3 :
            IC_AlternateClockEnable_Default(index);
            break;
        case IC_ID_4 :
            IC_AlternateClockEnable_Default(index);
            break;
        case IC_ID_5 :
            IC_AlternateClockEnable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_IC_AlternateClockDisable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_AlternateClockDisable_Default(index);
            break;
        case IC_ID_2 :
            IC_AlternateClockDisable_Default(index);
            break;
        case IC_ID_3 :
            IC_AlternateClockDisable_Default(index);
            break;
        case IC_ID_4 :
            IC_AlternateClockDisable_Default(index);
            break;
        case IC_ID_5 :
            IC_AlternateClockDisable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsAlternateClock(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsAlternateClock_Default(index);
        case IC_ID_2 :
            return IC_ExistsAlternateClock_Default(index);
        case IC_ID_3 :
            return IC_ExistsAlternateClock_Default(index);
        case IC_ID_4 :
            return IC_ExistsAlternateClock_Default(index);
        case IC_ID_5 :
            return IC_ExistsAlternateClock_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_StopInIdleEnable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_StopInIdleEnable_Default(index);
            break;
        case IC_ID_2 :
            IC_StopInIdleEnable_Default(index);
            break;
        case IC_ID_3 :
            IC_StopInIdleEnable_Default(index);
            break;
        case IC_ID_4 :
            IC_StopInIdleEnable_Default(index);
            break;
        case IC_ID_5 :
            IC_StopInIdleEnable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_IC_StopInIdleDisable(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            IC_StopInIdleDisable_Default(index);
            break;
        case IC_ID_2 :
            IC_StopInIdleDisable_Default(index);
            break;
        case IC_ID_3 :
            IC_StopInIdleDisable_Default(index);
            break;
        case IC_ID_4 :
            IC_StopInIdleDisable_Default(index);
            break;
        case IC_ID_5 :
            IC_StopInIdleDisable_Default(index);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsStopInIdle(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsStopInIdle_Default(index);
        case IC_ID_2 :
            return IC_ExistsStopInIdle_Default(index);
        case IC_ID_3 :
            return IC_ExistsStopInIdle_Default(index);
        case IC_ID_4 :
            return IC_ExistsStopInIdle_Default(index);
        case IC_ID_5 :
            return IC_ExistsStopInIdle_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_FirstCaptureEdgeSelect(IC_MODULE_ID index, IC_EDGE_TYPES edgeType)
{
    switch (index) {
        case IC_ID_1 :
            IC_FirstCaptureEdgeSelect_Default(index, edgeType);
            break;
        case IC_ID_2 :
            IC_FirstCaptureEdgeSelect_Default(index, edgeType);
            break;
        case IC_ID_3 :
            IC_FirstCaptureEdgeSelect_Default(index, edgeType);
            break;
        case IC_ID_4 :
            IC_FirstCaptureEdgeSelect_Default(index, edgeType);
            break;
        case IC_ID_5 :
            IC_FirstCaptureEdgeSelect_Default(index, edgeType);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsEdgeCapture(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsEdgeCapture_Default(index);
        case IC_ID_2 :
            return IC_ExistsEdgeCapture_Default(index);
        case IC_ID_3 :
            return IC_ExistsEdgeCapture_Default(index);
        case IC_ID_4 :
            return IC_ExistsEdgeCapture_Default(index);
        case IC_ID_5 :
            return IC_ExistsEdgeCapture_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_EventsPerInterruptSelect(IC_MODULE_ID index, IC_EVENTS_PER_INTERRUPT event)
{
    switch (index) {
        case IC_ID_1 :
            IC_EventsPerInterruptSelect_Default(index, event);
            break;
        case IC_ID_2 :
            IC_EventsPerInterruptSelect_Default(index, event);
            break;
        case IC_ID_3 :
            IC_EventsPerInterruptSelect_Default(index, event);
            break;
        case IC_ID_4 :
            IC_EventsPerInterruptSelect_Default(index, event);
            break;
        case IC_ID_5 :
            IC_EventsPerInterruptSelect_Default(index, event);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsEventsPerInterruptSelect(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsEventsPerInterruptSelect_Default(index);
        case IC_ID_2 :
            return IC_ExistsEventsPerInterruptSelect_Default(index);
        case IC_ID_3 :
            return IC_ExistsEventsPerInterruptSelect_Default(index);
        case IC_ID_4 :
            return IC_ExistsEventsPerInterruptSelect_Default(index);
        case IC_ID_5 :
            return IC_ExistsEventsPerInterruptSelect_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_IC_Buffer32BitGet(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_Buffer32BitGet_32Bit_Variant(index);
        case IC_ID_2 :
            return IC_Buffer32BitGet_32Bit_Variant(index);
        case IC_ID_3 :
            return IC_Buffer32BitGet_32Bit_Variant(index);
        case IC_ID_4 :
            return IC_Buffer32BitGet_32Bit_Variant(index);
        case IC_ID_5 :
            return IC_Buffer32BitGet_32Bit_Variant(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API uint16_t PLIB_IC_Buffer16BitGet(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_Buffer16BitGet_32Bit_Variant(index);
        case IC_ID_2 :
            return IC_Buffer16BitGet_32Bit_Variant(index);
        case IC_ID_3 :
            return IC_Buffer16BitGet_32Bit_Variant(index);
        case IC_ID_4 :
            return IC_Buffer16BitGet_32Bit_Variant(index);
        case IC_ID_5 :
            return IC_Buffer16BitGet_32Bit_Variant(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_IC_ExistsBufferValue(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsBufferValue_32Bit_Variant(index);
        case IC_ID_2 :
            return IC_ExistsBufferValue_32Bit_Variant(index);
        case IC_ID_3 :
            return IC_ExistsBufferValue_32Bit_Variant(index);
        case IC_ID_4 :
            return IC_ExistsBufferValue_32Bit_Variant(index);
        case IC_ID_5 :
            return IC_ExistsBufferValue_32Bit_Variant(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_IC_BufferIsEmpty(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_BufferIsEmpty_Default(index);
        case IC_ID_2 :
            return IC_BufferIsEmpty_Default(index);
        case IC_ID_3 :
            return IC_BufferIsEmpty_Default(index);
        case IC_ID_4 :
            return IC_BufferIsEmpty_Default(index);
        case IC_ID_5 :
            return IC_BufferIsEmpty_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_IC_ExistsBufferIsEmptyStatus(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsBufferIsEmptyStatus_Default(index);
        case IC_ID_2 :
            return IC_ExistsBufferIsEmptyStatus_Default(index);
        case IC_ID_3 :
            return IC_ExistsBufferIsEmptyStatus_Default(index);
        case IC_ID_4 :
            return IC_ExistsBufferIsEmptyStatus_Default(index);
        case IC_ID_5 :
            return IC_ExistsBufferIsEmptyStatus_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_IC_BufferOverflowHasOccurred(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_BufferOverflowHasOccurred_Default(index);
        case IC_ID_2 :
            return IC_BufferOverflowHasOccurred_Default(index);
        case IC_ID_3 :
            return IC_BufferOverflowHasOccurred_Default(index);
        case IC_ID_4 :
            return IC_BufferOverflowHasOccurred_Default(index);
        case IC_ID_5 :
            return IC_BufferOverflowHasOccurred_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_IC_ExistsBufferOverflowStatus(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsBufferOverflowStatus_Default(index);
        case IC_ID_2 :
            return IC_ExistsBufferOverflowStatus_Default(index);
        case IC_ID_3 :
            return IC_ExistsBufferOverflowStatus_Default(index);
        case IC_ID_4 :
            return IC_ExistsBufferOverflowStatus_Default(index);
        case IC_ID_5 :
            return IC_ExistsBufferOverflowStatus_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_ModeSelect(IC_MODULE_ID index, IC_INPUT_CAPTURE_MODES modeSel)
{
    switch (index) {
        case IC_ID_1 :
            IC_ModeSelect_Default(index, modeSel);
            break;
        case IC_ID_2 :
            IC_ModeSelect_Default(index, modeSel);
            break;
        case IC_ID_3 :
            IC_ModeSelect_Default(index, modeSel);
            break;
        case IC_ID_4 :
            IC_ModeSelect_Default(index, modeSel);
            break;
        case IC_ID_5 :
            IC_ModeSelect_Default(index, modeSel);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsCaptureMode(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsCaptureMode_Default(index);
        case IC_ID_2 :
            return IC_ExistsCaptureMode_Default(index);
        case IC_ID_3 :
            return IC_ExistsCaptureMode_Default(index);
        case IC_ID_4 :
            return IC_ExistsCaptureMode_Default(index);
        case IC_ID_5 :
            return IC_ExistsCaptureMode_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_BufferSizeSelect(IC_MODULE_ID index, IC_BUFFER_SIZE bufSize)
{
    switch (index) {
        case IC_ID_1 :
            IC_BufferSizeSelect_Default(index, bufSize);
            break;
        case IC_ID_2 :
            IC_BufferSizeSelect_Default(index, bufSize);
            break;
        case IC_ID_3 :
            IC_BufferSizeSelect_Default(index, bufSize);
            break;
        case IC_ID_4 :
            IC_BufferSizeSelect_Default(index, bufSize);
            break;
        case IC_ID_5 :
            IC_BufferSizeSelect_Default(index, bufSize);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsBufferSize(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsBufferSize_Default(index);
        case IC_ID_2 :
            return IC_ExistsBufferSize_Default(index);
        case IC_ID_3 :
            return IC_ExistsBufferSize_Default(index);
        case IC_ID_4 :
            return IC_ExistsBufferSize_Default(index);
        case IC_ID_5 :
            return IC_ExistsBufferSize_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_IC_TimerSelect(IC_MODULE_ID index, IC_TIMERS tmr)
{
    switch (index) {
        case IC_ID_1 :
            IC_TimerSelect_Default(index, tmr);
            break;
        case IC_ID_2 :
            IC_TimerSelect_Default(index, tmr);
            break;
        case IC_ID_3 :
            IC_TimerSelect_Default(index, tmr);
            break;
        case IC_ID_4 :
            IC_TimerSelect_Default(index, tmr);
            break;
        case IC_ID_5 :
            IC_TimerSelect_Default(index, tmr);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_IC_ExistsTimerSelect(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsTimerSelect_Default(index);
        case IC_ID_2 :
            return IC_ExistsTimerSelect_Default(index);
        case IC_ID_3 :
            return IC_ExistsTimerSelect_Default(index);
        case IC_ID_4 :
            return IC_ExistsTimerSelect_Default(index);
        case IC_ID_5 :
            return IC_ExistsTimerSelect_Default(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_IC_ClockSourceSelect(IC_MODULE_ID index, IC_CLOCK_SOURCES src)
{
    switch (index) {
        case IC_ID_1 :
            IC_ClockSourceSelect_Unsupported(index, src);
            break;
        case IC_ID_2 :
            IC_ClockSourceSelect_Unsupported(index, src);
            break;
        case IC_ID_3 :
            IC_ClockSourceSelect_Unsupported(index, src);
            break;
        case IC_ID_4 :
            IC_ClockSourceSelect_Unsupported(index, src);
            break;
        case IC_ID_5 :
            IC_ClockSourceSelect_Unsupported(index, src);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_IC_ExistsClockSource(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsClockSource_Unsupported(index);
        case IC_ID_2 :
            return IC_ExistsClockSource_Unsupported(index);
        case IC_ID_3 :
            return IC_ExistsClockSource_Unsupported(index);
        case IC_ID_4 :
            return IC_ExistsClockSource_Unsupported(index);
        case IC_ID_5 :
            return IC_ExistsClockSource_Unsupported(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_IC_SyncModeSelect(IC_MODULE_ID index, IC_SYNC_MODES syncMode)
{
    switch (index) {
        case IC_ID_1 :
            IC_SyncModeSelect_Unsupported(index, syncMode);
            break;
        case IC_ID_2 :
            IC_SyncModeSelect_Unsupported(index, syncMode);
            break;
        case IC_ID_3 :
            IC_SyncModeSelect_Unsupported(index, syncMode);
            break;
        case IC_ID_4 :
            IC_SyncModeSelect_Unsupported(index, syncMode);
            break;
        case IC_ID_5 :
            IC_SyncModeSelect_Unsupported(index, syncMode);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_IC_ExistsSyncMode(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsSyncMode_Unsupported(index);
        case IC_ID_2 :
            return IC_ExistsSyncMode_Unsupported(index);
        case IC_ID_3 :
            return IC_ExistsSyncMode_Unsupported(index);
        case IC_ID_4 :
            return IC_ExistsSyncMode_Unsupported(index);
        case IC_ID_5 :
            return IC_ExistsSyncMode_Unsupported(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_IC_SyncModeInputSelect(IC_MODULE_ID index, IC_SYNC_MODE_INPUTS input)
{
    switch (index) {
        case IC_ID_1 :
            IC_SyncModeInputSelect_Unsupported(index, input);
            break;
        case IC_ID_2 :
            IC_SyncModeInputSelect_Unsupported(index, input);
            break;
        case IC_ID_3 :
            IC_SyncModeInputSelect_Unsupported(index, input);
            break;
        case IC_ID_4 :
            IC_SyncModeInputSelect_Unsupported(index, input);
            break;
        case IC_ID_5 :
            IC_SyncModeInputSelect_Unsupported(index, input);
            break;
        case IC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_IC_ExistsSyncModeInput(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsSyncModeInput_Unsupported(index);
        case IC_ID_2 :
            return IC_ExistsSyncModeInput_Unsupported(index);
        case IC_ID_3 :
            return IC_ExistsSyncModeInput_Unsupported(index);
        case IC_ID_4 :
            return IC_ExistsSyncModeInput_Unsupported(index);
        case IC_ID_5 :
            return IC_ExistsSyncModeInput_Unsupported(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_IC_TimerIsTriggered(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_TimerIsTriggered_Unsupported(index);
        case IC_ID_2 :
            return IC_TimerIsTriggered_Unsupported(index);
        case IC_ID_3 :
            return IC_TimerIsTriggered_Unsupported(index);
        case IC_ID_4 :
            return IC_TimerIsTriggered_Unsupported(index);
        case IC_ID_5 :
            return IC_TimerIsTriggered_Unsupported(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_IC_ExistsTimerTriggered(IC_MODULE_ID index)
{
    switch (index) {
        case IC_ID_1 :
            return IC_ExistsTimerTriggered_Unsupported(index);
        case IC_ID_2 :
            return IC_ExistsTimerTriggered_Unsupported(index);
        case IC_ID_3 :
            return IC_ExistsTimerTriggered_Unsupported(index);
        case IC_ID_4 :
            return IC_ExistsTimerTriggered_Unsupported(index);
        case IC_ID_5 :
            return IC_ExistsTimerTriggered_Unsupported(index);
        case IC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
