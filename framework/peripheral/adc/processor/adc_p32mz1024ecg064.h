/* Created by plibgen $Revision: 1.29 $ */

#ifndef _ADC_P32MZ1024ECG064_H
#define _ADC_P32MZ1024ECG064_H

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

    ADC_NUMBER_OF_MODULES

} ADC_MODULE_ID;

typedef enum {

    ADC_MUX_NONE

} ADC_MUX;

typedef enum {

    ADC_RESULT_BUF_STATUS_NONE

} ADC_RESULT_BUF_STATUS;

typedef enum {

    ADC_VOLTAGE_REFERENCE_NONE

} ADC_VOLTAGE_REFERENCE;

typedef enum {

    ADC_SAMPLING_MODE_NONE

} ADC_SAMPLING_MODE;

typedef enum {

    ADC_SAMPLES_PER_INTERRUPT_NONE

} ADC_SAMPLES_PER_INTERRUPT;

typedef enum {

    ADC_INPUTS_POSITIVE_NONE

} ADC_INPUTS_POSITIVE;

typedef enum {

    ADC_INPUTS_SCAN_NONE

} ADC_INPUTS_SCAN;

typedef enum {

    ADC_INPUTS_NEGATIVE_NONE

} ADC_INPUTS_NEGATIVE;

typedef enum {

    ADC_REFERENCE_INPUT_NONE

} ADC_REFERENCE_INPUT;

typedef enum {

    ADC_CHANNEL_GROUP_NONE

} ADC_CHANNEL_GROUP;

typedef enum {

    ADC_CHANNEL123_INPUTS_NEG_NONE

} ADC_CHANNEL123_INPUTS_NEG;

typedef enum {

    ADC_CHANNEL123_INPUTS_POS_NONE

} ADC_CHANNEL123_INPUTS_POS;

typedef enum {

    ADC_CLOCK_SOURCE_NONE

} ADC_CLOCK_SOURCE;

typedef enum {

    ADC_CONVERSION_TRIGGER_SOURCE_NONE

} ADC_CONVERSION_TRIGGER_SOURCE;

typedef enum {

    ADC_CONVERSION_ORDER_NONE

} ADC_CONVERSION_ORDER;

typedef enum {

    ADC_RESULT_SIZE_NONE

} ADC_RESULT_SIZE;

typedef enum {

    ADC_RESULT_FORMAT_NONE

} ADC_RESULT_FORMAT;

typedef enum {

    ADC_BUFFER_MODE_NONE

} ADC_BUFFER_MODE;

typedef enum {

    ADC_DMA_ADDRESS_INCREMENT_NONE

} ADC_DMA_ADDRESS_INCREMENT;

typedef enum {

    ADC_DMA_BUFFER_MODE_NONE

} ADC_DMA_BUFFER_MODE;

typedef enum {

    ADC_DMA_INPUT_BUFFER_NONE

} ADC_DMA_INPUT_BUFFER;

typedef enum {

    ADC_PAIR_NONE

} ADC_PAIR;

typedef enum {

    ADC_CONVERSION_TRIGGER_GROUP_NONE

} ADC_CONVERSION_TRIGGER_GROUP;

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_Enable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_Disable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsEnableControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_StopInIdleEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_StopInIdleDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsStopInIdleControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_CalibrationEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_CalibrationDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsCalibrationControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InputSelectPositive(ADC_MODULE_ID index, ADC_INPUTS_POSITIVE inputs)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InputSelectNegative(ADC_MODULE_ID index, ADC_INPUTS_NEGATIVE negInput)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsInputSelect(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InputScanMaskAdd(ADC_MODULE_ID index, ADC_INPUTS_SCAN scanInputs)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InputScanMaskRemove(ADC_MODULE_ID index, ADC_INPUTS_SCAN scanInputs)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxInputScanSelect(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_VoltageReferenceSelect(ADC_MODULE_ID index, ADC_VOLTAGE_REFERENCE configValue)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsVoltageReference(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ChannelGroupSelect(ADC_MODULE_ID index, ADC_CHANNEL_GROUP chlGroup)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsChannelGroup(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_DMAEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_DMADisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsDMAControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_DMAAddressIncrementSelect(ADC_MODULE_ID index, ADC_DMA_ADDRESS_INCREMENT incRate)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsDMAAddressIncrement(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_DMABufferModeSelect(ADC_MODULE_ID index, ADC_DMA_BUFFER_MODE bufferMode)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsDMABufferMode(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_DMAInputBufferSelect(ADC_MODULE_ID index, ADC_DMA_INPUT_BUFFER buffer)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsDMABuffersPerAnalogInput(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxChannel0InputPositiveSelect(ADC_MODULE_ID index, ADC_MUX muxType, ADC_INPUTS_POSITIVE input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxChannel0PositiveInput(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxChannel0InputNegativeSelect(ADC_MODULE_ID index, ADC_MUX muxType, ADC_INPUTS_NEGATIVE input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxChannel0NegativeInput(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxChannel123InputPositiveSelect(ADC_MODULE_ID index, ADC_MUX muxType, ADC_CHANNEL123_INPUTS_POS input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxChannel123PositiveInput(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxChannel123InputNegativeSelect(ADC_MODULE_ID index, ADC_MUX muxType, ADC_CHANNEL123_INPUTS_NEG input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxChannel123NegativeInput(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxAInputScanEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_MuxAInputScanDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsMuxInputScanControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InternalReferenceChannelEnable(ADC_MODULE_ID index, ADC_REFERENCE_INPUT input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_InternalReferenceChannelDisable(ADC_MODULE_ID index, ADC_REFERENCE_INPUT input)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsInternalReferenceChannelControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SamplingModeSelect(ADC_MODULE_ID index, ADC_SAMPLING_MODE mode)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplingModeControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SamplesPerInterruptSelect(ADC_MODULE_ID index, ADC_SAMPLES_PER_INTERRUPT value)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplesPerInterruptSelect(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SampleAutoStartEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SampleAutoStartDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplingAutoStart(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SamplingStart(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SamplingStop(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplingControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API ADC_SAMPLE _PLIB_UNSUPPORTED PLIB_ADC_SampleMaxGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_SAMPLE)0;
    }
}

INLINE_API ADC_SAMPLE _PLIB_UNSUPPORTED PLIB_ADC_SampleMinGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_SAMPLE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSampleResolution(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_SampleAcqusitionTimeSet(ADC_MODULE_ID index, ADC_ACQUISITION_TIME acqTime)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplingAcquisitionTime(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_SamplingIsActive(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsSamplingStatus(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionStart(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionClockSet(ADC_MODULE_ID index, uint32_t baseFrequency, ADC_CONVERSION_CLOCK value)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API ADC_CONVERSION_CLOCK _PLIB_UNSUPPORTED PLIB_ADC_ConversionClockGet(ADC_MODULE_ID index, uint32_t baseFrequency)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_CONVERSION_CLOCK)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionClock(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionClockSourceSelect(ADC_MODULE_ID index, ADC_CLOCK_SOURCE source)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionClockSource(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionTriggerGroupSelect(ADC_MODULE_ID index, ADC_CONVERSION_TRIGGER_GROUP group)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionTriggerGroup(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionTriggerSourceSelect(ADC_MODULE_ID index, ADC_CONVERSION_TRIGGER_SOURCE source)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionTriggerSource(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionStopSequenceEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionStopSequenceDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionStopSequenceControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ConversionHasCompleted(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionStatus(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ResultSizeSelect(ADC_MODULE_ID index, ADC_RESULT_SIZE resSize)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultSize(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ResultFormatSelect(ADC_MODULE_ID index, ADC_RESULT_FORMAT resultFormat)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultFormat(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ResultBufferModeSelect(ADC_MODULE_ID index, ADC_BUFFER_MODE mode)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultBufferMode(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API ADC_RESULT_BUF_STATUS _PLIB_UNSUPPORTED PLIB_ADC_ResultBufferStatusGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_RESULT_BUF_STATUS)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultBufferFillStatus(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ResultSignGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultSign(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API ADC_SAMPLE _PLIB_UNSUPPORTED PLIB_ADC_ResultGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_SAMPLE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API ADC_SAMPLE _PLIB_UNSUPPORTED PLIB_ADC_ResultGetByIndex(ADC_MODULE_ID index, uint8_t bufferIndex)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (ADC_SAMPLE)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsResultGetByIndex(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_IsrJumpTableBaseAddressSet(ADC_MODULE_ID index, int baseAddr)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API int _PLIB_UNSUPPORTED PLIB_ADC_IsrJumpTableBaseAddressGet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsISRJumpTableBaseAddress(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_GlobalSoftwareTriggerSet(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsGlobalSoftwareTrigger(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_ConversionOrderSelect(ADC_MODULE_ID index, ADC_CONVERSION_ORDER order)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsConversionOrder(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_AsynchronousDedicatedSamplingEnable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_AsynchronousDedicatedSamplingDisable(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsAsynchronousDedicatedSampling(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairInterruptAfterFirstConversion(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairInterruptAfterSecondConversion(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsPairInterruptOnConversion(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairSampleStatusClear(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_PairSampleIsAvailable(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsPairSampleStatus(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairInterruptRequestEnable(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairInterruptRequestDisable(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsPairInterruptRequest(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairConversionStart(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_PairConversionIsPending(ADC_MODULE_ID index, ADC_PAIR pairNum)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsPairConversionControl(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_ADC_PairTriggerSourceSelect(ADC_MODULE_ID index, ADC_PAIR pairNum, ADC_CONVERSION_TRIGGER_SOURCE trigSrc)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_ADC_ExistsPairTriggerSource(ADC_MODULE_ID index)
{
    switch (index) {
        case ADC_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
