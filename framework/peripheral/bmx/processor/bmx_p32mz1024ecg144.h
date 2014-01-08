/* Created by plibgen $Revision: 1.29 $ */

#ifndef _BMX_P32MZ1024ECG144_H
#define _BMX_P32MZ1024ECG144_H

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

    BMX_NUMBER_OF_MODULES

} BMX_MODULE_ID;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsArbitrationMode(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_ArbitrationModeSet(BMX_MODULE_ID index, PLIB_BMX_ARB_MODE mode)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PLIB_BMX_ARB_MODE _PLIB_UNSUPPORTED PLIB_BMX_ArbitrationModeGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (PLIB_BMX_ARB_MODE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsDataRamWaitState(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_DataRamWaitStateSet(BMX_MODULE_ID index, PLIB_BMX_DATA_RAM_WAIT_STATES wait)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PLIB_BMX_DATA_RAM_WAIT_STATES _PLIB_UNSUPPORTED PLIB_BMX_DataRamWaitStateGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (PLIB_BMX_DATA_RAM_WAIT_STATES)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsProgramFlashMemoryCacheDma(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashMemoryCacheDmaEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashMemoryCacheDmaDisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsBusExceptionIXI(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionIXIEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionIXIDisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsBusExceptionICD(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionICDEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionICDDisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsBusExceptionDMA(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionDMAEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionDMADisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsBusExceptionData(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionDataEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionDataDisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsBusExceptionInstruction(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionInstructionEnable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_BusExceptionInstructionDisable(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsProgramFlashPartition(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashPartitionGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashPartitionSet(BMX_MODULE_ID index, size_t user_size)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsDataRAMPartition(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_BMX_DataRAMPartitionSet(BMX_MODULE_ID index, size_t kernProgOffset, size_t userDataOffset, size_t userProgOffset)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_DataRAMKernelProgramOffsetGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_DataRAMUserDataOffsetGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_DataRAMUserProgramOffsetGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsProgramFlashMemorySize(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashMemorySizeGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsDataRAMSize(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_DataRAMSizeGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_BMX_ExistsProgramFlashBootSize(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API size_t _PLIB_UNSUPPORTED PLIB_BMX_ProgramFlashBootSizeGet(BMX_MODULE_ID index)
{
    switch (index) {
        case BMX_NUMBER_OF_MODULES :
        default :
            return (size_t)0;
    }
}

#endif
