/* Created by plibgen $Revision: 1.29 $ */

#ifndef _DMT_P32MZ1024ECH064_H
#define _DMT_P32MZ1024ECH064_H

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

    DMT_ID_0 = 0,
    DMT_NUMBER_OF_MODULES

} DMT_MODULE_ID;

INLINE SFR_TYPE* _DMT_ON_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTCON;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_STEP1_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTPRECLR;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_STEP2_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTCLR;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_WINOPN_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTSTAT;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_DMTEVENT_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTSTAT;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_BAD_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTSTAT;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_COUNTER_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTCNT;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_PSCNT_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTPSCNT;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _DMT_PSINTV_VREG(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return &DMTPSINTV;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _DMT_ON_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCON_ON_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP1_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPRECLR_STEP1_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP2_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCLR_STEP2_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_WINOPN_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_WINOPN_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_DMTEVENT_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_DMTEVENT_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_BAD_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_BAD_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_COUNTER_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCNT_COUNTER_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSCNT_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSCNT_PSCNT_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSINTV_MASK(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSINTV_PSINTV_MASK;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_ON_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCON_ON_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP1_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPRECLR_STEP1_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP2_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCLR_STEP2_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_WINOPN_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_WINOPN_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_DMTEVENT_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_DMTEVENT_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_BAD_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_BAD_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_COUNTER_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCNT_COUNTER_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSCNT_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSCNT_PSCNT_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSINTV_POS(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSINTV_PSINTV_POSITION;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_ON_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCON_ON_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP1_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPRECLR_STEP1_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_STEP2_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCLR_STEP2_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_WINOPN_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_WINOPN_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_DMTEVENT_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_DMTEVENT_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_BAD_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTSTAT_BAD_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_COUNTER_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTCNT_COUNTER_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSCNT_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSCNT_PSCNT_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _DMT_PSINTV_LEN(DMT_MODULE_ID i)
{
    switch (i) {
        case DMT_ID_0 :
            return _DMTPSINTV_PSINTV_LENGTH;
        case DMT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/dmt_Enable_Default.h"
#include "../templates/dmt_DeadManTimerStatus_Default.h"
#include "../templates/dmt_Step1_Default.h"
#include "../templates/dmt_Step2_Default.h"
#include "../templates/dmt_Counter_Default.h"
#include "../templates/dmt_PostscalerValue_Default.h"
#include "../templates/dmt_PostscalerInterval_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_DMT_Enable(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            DMT_Enable_Default(index);
            break;
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_DMT_Disable(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            DMT_Disable_Default(index);
            break;
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DMT_IsEnabled(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_IsEnabled_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_ExistsEnableControl(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsEnableControl_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_WindowIsOpen(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_WindowIsOpen_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_EventOccured(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_EventOccured_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_BAD2Get(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_BAD2Get_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_BAD1Get(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_BAD1Get_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_DMT_ExistsStatus(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsStatus_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DMT_ClearStep1(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            DMT_ClearStep1_Default(index);
            break;
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DMT_ExistsStep1(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsStep1_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_DMT_ClearStep2(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            DMT_ClearStep2_Default(index);
            break;
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_DMT_ExistsStep2(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsStep2_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_DMT_CounterGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_CounterGet_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_DMT_ExistsCounter(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsCounter_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_DMT_PostscalerValueGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_PostscalerValueGet_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_DMT_ExistsPostscalerValue(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsPostscalerValue_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_DMT_PostscalerIntervalGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_PostscalerIntervalGet_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_DMT_ExistsPostscalerInterval(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_ID_0 :
            return DMT_ExistsPostscalerInterval_Default(index);
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
