/* Created by plibgen $Revision: 1.29 $ */

#ifndef _WDT_P32MX220F032D_H
#define _WDT_P32MX220F032D_H

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

    WDT_ID_0 = 0,
    WDT_NUMBER_OF_MODULES

} WDT_MODULE_ID;

INLINE SFR_TYPE* _WDT_TIMER_CLEAR_VREG(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return &WDTCON;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _WDT_WINDOW_ENABLE_VREG(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return &WDTCON;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _WDT_POSTSCALAR_VALUE_VREG(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return &WDTCON;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _WDT_ENABLE_CONTROL_VREG(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return &WDTCON;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _WDT_TIMER_CLEAR_MASK(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTCLR_MASK;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_WINDOW_ENABLE_MASK(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTWINEN_MASK;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_POSTSCALAR_VALUE_MASK(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_SWDTPS_MASK;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_ENABLE_CONTROL_MASK(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_ON_MASK;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_TIMER_CLEAR_POS(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTCLR_POSITION;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_WINDOW_ENABLE_POS(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTWINEN_POSITION;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_POSTSCALAR_VALUE_POS(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_SWDTPS_POSITION;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_ENABLE_CONTROL_POS(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_ON_POSITION;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_TIMER_CLEAR_LEN(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTCLR_LENGTH;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_WINDOW_ENABLE_LEN(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_WDTWINEN_LENGTH;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_POSTSCALAR_VALUE_LEN(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_SWDTPS_LENGTH;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _WDT_ENABLE_CONTROL_LEN(WDT_MODULE_ID i)
{
    switch (i) {
        case WDT_ID_0 :
            return _WDTCON_ON_LENGTH;
        case WDT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/wdt_EnableControl_Default.h"
#include "../templates/wdt_WindowEnable_Default.h"
#include "../templates/wdt_TimerClear_Default.h"
#include "../templates/wdt_PostscalarValue_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_WDT_ExistsEnableControl(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_ExistsEnableControl_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_WDT_Enable(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            WDT_Enable_Default(index);
            break;
        case WDT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_WDT_Disable(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            WDT_Disable_Default(index);
            break;
        case WDT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_WDT_IsEnabled(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_IsEnabled_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_WDT_ExistsWindowEnable(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_ExistsWindowEnable_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_WDT_WindowEnable(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            WDT_WindowEnable_Default(index);
            break;
        case WDT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_WDT_WindowDisable(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            WDT_WindowDisable_Default(index);
            break;
        case WDT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_WDT_ExistsTimerClear(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_ExistsTimerClear_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_WDT_TimerClear(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            WDT_TimerClear_Default(index);
            break;
        case WDT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_WDT_ExistsPostscalarValue(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_ExistsPostscalarValue_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API char PLIB_WDT_PostscalarValueGet(WDT_MODULE_ID index)
{
    switch (index) {
        case WDT_ID_0 :
            return WDT_PostscalarValueGet_Default(index);
        case WDT_NUMBER_OF_MODULES :
        default :
            return (char)0;
    }
}

#endif
