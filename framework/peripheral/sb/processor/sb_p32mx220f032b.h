/* Created by plibgen $Revision: 1.29 $ */

#ifndef _SB_P32MX220F032B_H
#define _SB_P32MX220F032B_H

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

    SB_NUMBER_OF_MODULES

} SB_MODULE_ID;

typedef enum {

    PLIB_SB_INIT_ID_NONE

} PLIB_SB_INIT_ID;

typedef enum {

    PLIB_SB_PG_INITIATOR_NONE

} PLIB_SB_PG_INITIATOR;

typedef enum {

    PLIB_SB_TGT_ID_NONE

} PLIB_SB_TGT_ID;

typedef enum {

    PLIB_SB_TGT_REGION_NONE

} PLIB_SB_TGT_REGION;

typedef enum {

    PLIB_SB_ERROR_NONE

} PLIB_SB_ERROR;

typedef enum {

    PLIB_SB_REGION_PG_NONE

} PLIB_SB_REGION_PG;

typedef enum {

    PLIB_SB_INIT_PG_NONE

} PLIB_SB_INIT_PG;

typedef enum {

    PLIB_SB_ARB_POLICY_NONE

} PLIB_SB_ARB_POLICY;

typedef enum {

    PLIB_SB_OCP_CMD_CODE_NONE

} PLIB_SB_OCP_CMD_CODE;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrStatus(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_PGVErrorStatus(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrClear(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_PGVErrorMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_ERROR _PLIB_UNSUPPORTED PLIB_SB_PGVErrorCode(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_ERROR)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGVErrorLogClearSingle(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGVErrorLogClearMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrInitID(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_INIT_ID _PLIB_UNSUPPORTED PLIB_SB_PGVErrorInitiatorID(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_INIT_ID)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrRegion(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int _PLIB_UNSUPPORTED PLIB_SB_PGVErrorRegion(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrCmdCode(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PLIB_SB_OCP_CMD_CODE _PLIB_UNSUPPORTED PLIB_SB_PGVErrorCommandCode(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (PLIB_SB_OCP_CMD_CODE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrPG(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int _PLIB_UNSUPPORTED PLIB_SB_PGVErrorPermissionGroup(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrRptPri(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGVErrorReportPrimaryEnable(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGVErrorReportPrimaryDisable(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrClrSingle(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_PGVErrorClearSingle(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGVErrClrMulti(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_PGVErrorClearMulti(SB_MODULE_ID index, PLIB_SB_TGT_ID target)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionAddrSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, uint32_t phys_addr)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_SB_PGRegionAddrGet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGRegAddr(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionSizeSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, uint32_t size)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_SB_PGRegionSizeGet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGRegSize(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionReadPermSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG readPerm)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionReadPermClear(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG readPerm)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGRegRdPerm(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionWritePermSet(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG writePerm)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_PGRegionWritePermClear(SB_MODULE_ID index, PLIB_SB_TGT_REGION region, PLIB_SB_REGION_PG writePerm)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsPGRegWrPerm(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsInitPermGrp(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_InitPermGrpSet(SB_MODULE_ID index, PLIB_SB_PG_INITIATOR initiator, PLIB_SB_INIT_PG pg)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsCPUPriority(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_CPUPrioritySet(SB_MODULE_ID index, PLIB_SB_ARB_POLICY priority)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SB_ExistsDMAPriority(SB_MODULE_ID index)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SB_DMAPrioritySet(SB_MODULE_ID index, PLIB_SB_ARB_POLICY priority)
{
    switch (index) {
        case SB_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
