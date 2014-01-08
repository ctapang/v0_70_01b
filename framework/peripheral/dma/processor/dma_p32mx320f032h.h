/* Created by plibgen $Revision: 1.29 $ */

#ifndef _DMA_P32MX320F032H_H
#define _DMA_P32MX320F032H_H

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

    DMA_NUMBER_OF_MODULES

} DMA_MODULE_ID;

typedef enum {

    DMA_CHANNEL_NONE

} DMA_CHANNEL;

typedef enum {

    DMA_CHANNEL_PRIORITY_NONE

} DMA_CHANNEL_PRIORITY;

typedef enum {

    DMA_CHANNEL_TRIGGER_TYPE_NONE

} DMA_CHANNEL_TRIGGER_TYPE;

typedef enum {

    DMA_TRIGGER_SOURCE_NONE

} DMA_TRIGGER_SOURCE;

typedef enum {

    DMA_CRC_TYPE_NONE

} DMA_CRC_TYPE;

typedef enum {

    DMA_CRC_BYTE_ORDER_NONE

} DMA_CRC_BYTE_ORDER;

typedef enum {

    DMA_INT_TYPE_NONE

} DMA_INT_TYPE;

typedef enum {

    DMA_CRC_BIT_ORDER_NONE

} DMA_CRC_BIT_ORDER;

typedef enum {

    DMA_PATTERN_LENGTH_NONE

} DMA_PATTERN_LENGTH;

typedef enum {

    DMA_CHANNEL_COLLISION_NONE

} DMA_CHANNEL_COLLISION;

typedef enum {

    DMA_PING_PONG_MODE_NONE

} DMA_PING_PONG_MODE;

typedef enum {

    DMA_CHANNEL_TRANSFER_DIRECTION_NONE

} DMA_CHANNEL_TRANSFER_DIRECTION;

typedef enum {

    DMA_ADDRESS_OFFSET_TYPE_NONE

} DMA_ADDRESS_OFFSET_TYPE;

typedef enum {

    DMA_SOURCE_ADDRESSING_MODE_NONE

} DMA_SOURCE_ADDRESSING_MODE;

typedef enum {

    DMA_DESTINATION_ADDRESSING_MODE_NONE

} DMA_DESTINATION_ADDRESSING_MODE;

typedef enum {

    DMA_CHANNEL_ADDRESSING_MODE_NONE

} DMA_CHANNEL_ADDRESSING_MODE;

typedef enum {

    DMA_CHANNEL_DATA_SIZE_NONE

} DMA_CHANNEL_DATA_SIZE;

typedef enum {

    DMA_TRANSFER_MODE_NONE

} DMA_TRANSFER_MODE;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsBusy(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_BusyActiveSet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_BusyActiveReset(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_IsBusy(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsSuspend(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_SuspendEnable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_SuspendDisable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_SuspendIsEnabled(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsStopInIdle(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_StopInIdleEnable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_StopInIdleDisable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsEnableControl(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_Enable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_Disable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_IsEnabled(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelBits(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelBitsGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsLastBusAccess(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_LastBusAccessIsRead(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_LastBusAccessIsWrite(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsRecentAddress(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DMA_RecentAddressAccessed(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCChannel(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCChannelSelect(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API DMA_CHANNEL _PLIB_UNSUPPORTED PLIB_DMA_CRCChannelGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (DMA_CHANNEL)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCType(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API DMA_CRC_TYPE _PLIB_UNSUPPORTED PLIB_DMA_CRCTypeGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (DMA_CRC_TYPE)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCTypeSet(DMA_MODULE_ID index, DMA_CRC_TYPE CRCType)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCAppendMode(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCAppendModeEnable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCAppendModeDisable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_CRCAppendModeIsEnabled(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRC(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCEnable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCDisable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_CRCIsEnabled(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCPolynomialLength(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCPolynomialLengthSet(DMA_MODULE_ID index, uint8_t polyLength)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_DMA_CRCPolynomialLengthGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCBitOrder(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCBitOrderSelect(DMA_MODULE_ID index, DMA_CRC_BIT_ORDER bitOrder)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCWriteByteOrder(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCWriteByteOrderAlter(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCWriteByteOrderMaintain(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCByteOrder(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCByteOrderSelect(DMA_MODULE_ID index, DMA_CRC_BYTE_ORDER byteOrder)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API DMA_CRC_BYTE_ORDER _PLIB_UNSUPPORTED PLIB_DMA_CRCByteOrderGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (DMA_CRC_BYTE_ORDER)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCData(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DMA_CRCDataRead(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCDataWrite(DMA_MODULE_ID index, uint32_t DMACRCdata)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsCRCXOREnable(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_CRCXOREnableSet(DMA_MODULE_ID index, uint32_t DMACRCXOREnableMask)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DMA_CRCXOREnableGet(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXPriority(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPrioritySelect(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_CHANNEL_PRIORITY channelPriority)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API DMA_CHANNEL_PRIORITY _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPriorityGet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (DMA_CHANNEL_PRIORITY)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXEvent(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXEventIsDetected(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXAuto(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXAutoEnable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXAutoDisable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXAutoIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXChainEnbl(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXChainEnable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXChainDisable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXChainIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXDisabled(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDisabledEnablesEvents(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDisabledDisablesEvents(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelX(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXEnable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDisable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXChain(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXChainToLower(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXChainToHigher(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXPatternLength(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternLengthSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_PATTERN_LENGTH patternLen)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API DMA_PATTERN_LENGTH _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternLengthGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (DMA_PATTERN_LENGTH)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXPatternIgnoreByte(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternIgnoreByteEnable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternIgnoreByteIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternIgnoreByteDisable(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXBusy(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXBusyActiveSet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXBusyInActiveSet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXBusyIsBusy(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXPatternIgnore(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternIgnoreSet(DMA_MODULE_ID index, DMA_CHANNEL channel, uint8_t pattern)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternIgnoreGet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXTrigger(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXTriggerEnable(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_CHANNEL_TRIGGER_TYPE trigger)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXTriggerIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_CHANNEL_TRIGGER_TYPE trigger)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXTriggerDisable(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_CHANNEL_TRIGGER_TYPE trigger)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsAbortTransfer(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_AbortTransferSet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsStartTransfer(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_StartTransferSet(DMA_MODULE_ID index, DMA_CHANNEL channel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXStartIRQ(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXStartIRQSet(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_TRIGGER_SOURCE IRQnum)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXAbortIRQ(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXAbortIRQSet(DMA_MODULE_ID index, DMA_CHANNEL channel, DMA_TRIGGER_SOURCE IRQ)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXINTSourceFlag(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceFlagGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceFlagSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceFlagClear(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXINTSource(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceEnable(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceDisable(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ChannelXINTSourceIsEnabled(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, DMA_INT_TYPE dmaINTSource)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXSourceStartAddress(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXSourceStartAddressGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXSourceStartAddressSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint32_t sourceStartAddress)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXDestinationStartAddress(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDestinationStartAddressGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDestinationStartAddressSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint32_t destinationStartAddress)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXSourceSize(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXSourceSizeGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXSourceSizeSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint16_t sourceSize)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXDestinationSize(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDestinationSizeGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDestinationSizeSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint16_t destinationSize)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXSourcePointer(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXSourcePointerGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXDestinationPointer(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXDestinationPointerGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXCellSize(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXCellSizeGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXCellSizeSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint16_t CellSize)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXCellProgressPointer(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXCellProgressPointerGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_DMA_ExistsChannelXPatternData(DMA_MODULE_ID index)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternDataGet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_DMA_ChannelXPatternDataSet(DMA_MODULE_ID index, DMA_CHANNEL dmaChannel, uint16_t patternData)
{
    switch (index) {
        case DMA_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
