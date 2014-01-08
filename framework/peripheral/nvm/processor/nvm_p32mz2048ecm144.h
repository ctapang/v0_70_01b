/* Created by plibgen $Revision: 1.29 $ */

#ifndef _NVM_P32MZ2048ECM144_H
#define _NVM_P32MZ2048ECM144_H

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

    NVM_ID_0 = 0,
    NVM_NUMBER_OF_MODULES

} NVM_MODULE_ID;

typedef enum {

    WORD_PROGRAM_OPERATION = 0x4001,
    ROW_PROGRAM_OPERATION = 0x4003,
    PAGE_ERASE_OPERATION = 0x4004,
    FLASH_ERASE_OPERATION = 0x4007,
    UPPER_FLASH_REGION_ERASE_OPERATION = 0x4006,
    LOWER_FLASH_REGION_ERASE_OPERATION = 0x4005,
    QUAD_WORD_PROGRAM_OPERATION = 0x4002

} NVM_OPERATION_MODE;

typedef enum {

    LOWER_BOOT_ALIAS_AREA = 0x8000,
    UPPER_BOOT_ALIAS_AREA = 0x0080

} NVM_BOOT_MEMORY_AREA;

typedef enum {

    LOWER_BOOT_ALIAS_PAGE4 = 0x1000,
    LOWER_BOOT_ALIAS_PAGE3 = 0x0800,
    LOWER_BOOT_ALIAS_PAGE2 = 0x0400,
    LOWER_BOOT_ALIAS_PAGE1 = 0x0200,
    LOWER_BOOT_ALIAS_PAGE0 = 0x0100,
    UPPER_BOOT_ALIAS_PAGE4 = 0x0010,
    UPPER_BOOT_ALIAS_PAGE3 = 0x0008,
    UPPER_BOOT_ALIAS_PAGE2 = 0x0004,
    UPPER_BOOT_ALIAS_PAGE1 = 0x0002,
    UPPER_BOOT_ALIAS_PAGE0 = 0x0001

} NVM_BOOT_MEMORY_PAGE;

INLINE SFR_TYPE* _NVM_OPERATION_MODE_WAAA_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_FLASH_BANK_REGION_SELECT_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_LOW_VOLTAGE_ERROR_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_WRITE_ERROR_STATUS_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_MEMORY_MODIFY_CONTROL_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_WRITE_OPERATION_CONTROL_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMCON;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_KEY_SEQUENCE_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMKEY;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_ADDRESS_MODIFY_CONTROL_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMADDR;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_PROVIDE_QUAD_DATA_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMDATA0;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_FLASH_WP_MEMORY_RANGE_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMPWP;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_LOCK_PFM_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMPWP;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_LOCK_BOOT_MEM_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMBWP;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_BOOT_PWP_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMBWP;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _NVM_SOURCE_ADDRESS_SELECT_VREG(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return &NVMSRCADDR;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _NVM_OPERATION_MODE_WAAA_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_NVMOP_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_BANK_REGION_SELECT_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_SWAP_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOW_VOLTAGE_ERROR_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_LVDERR_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_ERROR_STATUS_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WRERR_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_MEMORY_MODIFY_CONTROL_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WREN_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_OPERATION_CONTROL_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WR_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_KEY_SEQUENCE_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)-1;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_ADDRESS_MODIFY_CONTROL_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)-1;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_PROVIDE_QUAD_DATA_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)-1;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_WP_MEMORY_RANGE_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWP_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_PFM_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWPULOCK_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_BOOT_MEM_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWPULOCK_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_BOOT_PWP_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWP4_MASK;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_SOURCE_ADDRESS_SELECT_MASK(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)-1;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_OPERATION_MODE_WAAA_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_NVMOP_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_BANK_REGION_SELECT_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_SWAP_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOW_VOLTAGE_ERROR_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_LVDERR_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_ERROR_STATUS_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WRERR_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_MEMORY_MODIFY_CONTROL_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WREN_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_OPERATION_CONTROL_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WR_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_KEY_SEQUENCE_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)0;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_ADDRESS_MODIFY_CONTROL_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)0;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_PROVIDE_QUAD_DATA_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)0;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_WP_MEMORY_RANGE_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWP_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_PFM_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWPULOCK_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_BOOT_MEM_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWPULOCK_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_BOOT_PWP_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWP4_POSITION;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_SOURCE_ADDRESS_SELECT_POS(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)0;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_OPERATION_MODE_WAAA_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_NVMOP_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_BANK_REGION_SELECT_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_SWAP_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOW_VOLTAGE_ERROR_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_LVDERR_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_ERROR_STATUS_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WRERR_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_MEMORY_MODIFY_CONTROL_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WREN_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_WRITE_OPERATION_CONTROL_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMCON_WR_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_KEY_SEQUENCE_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_ADDRESS_MODIFY_CONTROL_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_PROVIDE_QUAD_DATA_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_FLASH_WP_MEMORY_RANGE_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWP_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_PFM_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMPWP_PWPULOCK_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_LOCK_BOOT_MEM_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWPULOCK_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_BOOT_PWP_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return _NVMBWP_LBWP4_LENGTH;
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _NVM_SOURCE_ADDRESS_SELECT_LEN(NVM_MODULE_ID i)
{
    switch (i) {
        case NVM_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/nvm_AccessEnableControl_Unsupported.h"
#include "../templates/nvm_ProgramEraseOperation_Unsupported.h"
#include "../templates/nvm_EEPROMReadInitiate_Unsupported.h"
#include "../templates/nvm_StopInIdle_Unsupported.h"
#include "../templates/nvm_WriteErrorStatus_Default.h"
#include "../templates/nvm_MemoryModificationControl_Default.h"
#include "../templates/nvm_OperationMode_PIC32WAAA_Support.h"
#include "../templates/nvm_AddressModifyControl_Default.h"
#include "../templates/nvm_ProvideData_Unsupported.h"
#include "../templates/nvm_WriteOperation_Default.h"
#include "../templates/nvm_KeySequence_Default.h"
#include "../templates/nvm_SourceAddress_Default.h"
#include "../templates/nvm_LowVoltageStatus_Unsupported.h"
#include "../templates/nvm_LowVoltageError_Default.h"
#include "../templates/nvm_FlashBankRegionSelect_Default.h"
#include "../templates/nvm_ProvideQuadData_Default.h"
#include "../templates/nvm_LockPFMSelect_Default.h"
#include "../templates/nvm_FlashWPMemoryRangeProvide_Default.h"
#include "../templates/nvm_LockBootSelect_Default.h"
#include "../templates/nvm_BootPageWriteProtect_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsAccessEnable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsAccessEnable_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_FlashAccessEnable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashAccessEnable_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_EEPROMAccessEnable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMAccessEnable_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsProgramEraseOperation(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsProgramEraseOperation_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_FlashEraseOperationSelect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashEraseOperationSelect_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_FlashWriteOperationSelect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashWriteOperationSelect_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsEEPROMReadInitiate(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsEEPROMReadInitiate_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_EEPROMReadStart(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMReadStart_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsStopInIdle(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsStopInIdle_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_StopInIdleEnable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_StopInIdleEnable_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_StopInIdleDisable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_StopInIdleDisable_Unsupported(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsWriteErrorStatus(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsWriteErrorStatus_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_WriteOperationHasTerminated(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_WriteOperationHasTerminated_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsMemoryModificationControl(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsMemoryModificationControl_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_MemoryModifyEnable(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_MemoryModifyEnable_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_MemoryModifyInhibit(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_MemoryModifyInhibit_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsOperationMode(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsOperationMode_PIC32WAAA_Support(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_MemoryOperationSelect(NVM_MODULE_ID index, NVM_OPERATION_MODE operationmode)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_MemoryOperationSelect_PIC32WAAA_Support(index, operationmode);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsAddressModifyControl(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsAddressModifyControl_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_FlashAddressToModify(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashAddressToModify_Default(index, address);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_EEPROMAddressToModify(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMAddressToModify_Default(index, address);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsProvideData(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsProvideData_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_FlashProvideData(NVM_MODULE_ID index, uint32_t data)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashProvideData_Unsupported(index, data);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_NVM_EEPROMProvideData(NVM_MODULE_ID index, uint32_t data)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMProvideData_Unsupported(index, data);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsWriteOperation(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsWriteOperation_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_NVM_FlashRead(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_FlashRead_Default(index, address);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API uint32_t PLIB_NVM_EEPROMRead(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_EEPROMRead_Default(index, address);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void PLIB_NVM_FlashWriteStart(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashWriteStart_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_FlashEraseStart(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashEraseStart_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_EEPROMWriteStart(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMWriteStart_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_EEPROMEraseStart(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMEraseStart_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_FlashWriteCycleHasCompleted(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_FlashWriteCycleHasCompleted_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsKeySequence(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsKeySequence_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_FlashWriteKeySequence(NVM_MODULE_ID index, uint32_t keysequence)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashWriteKeySequence_Default(index, keysequence);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_EEPROMWriteKeySequence(NVM_MODULE_ID index, uint32_t keysequence)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_EEPROMWriteKeySequence_Default(index, keysequence);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsSourceAddress(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsSourceAddress_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_DataBlockSourceAddress(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_DataBlockSourceAddress_Default(index, address);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_ExistsLowVoltageStatus(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsLowVoltageStatus_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_NVM_LowVoltageEventIsActive(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_LowVoltageEventIsActive_Unsupported(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsLowVoltageError(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsLowVoltageError_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_LowVoltageIsDetected(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_LowVoltageIsDetected_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsFlashBankRegionSelect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsFlashBankRegionSelect_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_ProgramFlashBank1LowerRegion(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_ProgramFlashBank1LowerRegion_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_ProgramFlashBank2LowerRegion(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_ProgramFlashBank2LowerRegion_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsProvideQuadData(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsProvideQuadData_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_FlashProvideQuadData(NVM_MODULE_ID index, uint32_t* data)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashProvideQuadData_Default(index, data);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsLockPFMSelect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsLockPFMSelect_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_LockProgramFlashMemory(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_LockProgramFlashMemory_Default(index);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_IsProgramFlashMemoryLocked(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_IsProgramFlashMemoryLocked_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsFlashWPMemoryRangeProvide(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsFlashWPMemoryRangeProvide_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_FlashWriteProtectMemoryAreaRange(NVM_MODULE_ID index, uint32_t address)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_FlashWriteProtectMemoryAreaRange_Default(index, address);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_ExistsLockBootSelect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsLockBootSelect_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_LockBootMemory(NVM_MODULE_ID index, NVM_BOOT_MEMORY_AREA memoryArea)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_LockBootMemory_Default(index, memoryArea);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_IsBootMemoryLocked(NVM_MODULE_ID index, NVM_BOOT_MEMORY_AREA memoryArea)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_IsBootMemoryLocked_Default(index, memoryArea);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_NVM_ExistsBootPageWriteProtect(NVM_MODULE_ID index)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_ExistsBootPageWriteProtect_Default(index);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_NVM_BootPageWriteProtectionEnable(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_BootPageWriteProtectionEnable_Default(index, bootPage);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_NVM_BootPageWriteProtectionDisable(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage)
{
    switch (index) {
        case NVM_ID_0 :
            NVM_BootPageWriteProtectionDisable_Default(index, bootPage);
            break;
        case NVM_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_NVM_IsBootPageWriteProtected(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage)
{
    switch (index) {
        case NVM_ID_0 :
            return NVM_IsBootPageWriteProtected_Default(index, bootPage);
        case NVM_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
