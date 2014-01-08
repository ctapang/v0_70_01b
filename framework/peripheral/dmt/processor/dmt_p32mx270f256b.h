/* Created by plibgen $Revision: 1.23 $ */

#ifndef _DMT_P32MX270F256B_H
#define _DMT_P32MX270F256B_H

/* Section 1 - Enumerate instances, define constants, VREGs */

#include <xc.h>
#include <stdbool.h>

#include "peripheral/plib_common_32bit.h"

#define INLINE static inline

typedef enum {

    DMT_NUMBER_OF_MODULES

} DMT_MODULE_ID;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE void _PLIB_UNSUPPORTED PLIB_DMT_Enable(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_DMT_Disable(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_IsEnabled(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsEnableControl(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_WindowIsOpen(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_EventOccured(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_BAD2Get(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_BAD1Get(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsStatus(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_DMT_ClearStep1(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsStep1(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE void _PLIB_UNSUPPORTED PLIB_DMT_ClearStep2(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsStep2(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE uint32_t _PLIB_UNSUPPORTED PLIB_DMT_CounterGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsCounter(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE uint32_t _PLIB_UNSUPPORTED PLIB_DMT_PostscalerValueGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsPostscalerValue(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE uint32_t _PLIB_UNSUPPORTED PLIB_DMT_PostscalerIntervalGet(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE bool _PLIB_UNSUPPORTED PLIB_DMT_ExistsPostscalerInterval(DMT_MODULE_ID index)
{
    switch (index) {
        case DMT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
