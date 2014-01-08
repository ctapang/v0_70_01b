/* Created by plibgen $Revision: 1.29 $ */

#ifndef _SPI_P32MX340F256H_H
#define _SPI_P32MX340F256H_H

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

    SPI_ID_1 = 0,
    SPI_ID_2,
    SPI_NUMBER_OF_MODULES

} SPI_MODULE_ID;

typedef enum {

    SPI_PRESCALE_PRIMARY_NOT_SUPPORTED = 0

} SPI_PRESCALE_PRIMARY;

typedef enum {

    SPI_PRESCALE_SECONDARY_NOT_SUPPORTED = 0

} SPI_PRESCALE_SECONDARY;

typedef enum {

    SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE = 0,
    SPI_INPUT_SAMPLING_PHASE_AT_END = 1

} SPI_INPUT_SAMPLING_PHASE;

typedef enum {

    SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK = 0,
    SPI_OUTPUT_DATA_PHASE_ON_ACTIVE_TO_IDLE_CLOCK = 1

} SPI_OUTPUT_DATA_PHASE;

typedef enum {

    SPI_COMMUNICATION_WIDTH_8BITS = 0,
    SPI_COMMUNICATION_WIDTH_16BITS = 1,
    SPI_COMMUNICATION_WIDTH_32BITS = 2

} SPI_COMMUNICATION_WIDTH;

typedef enum {

    SPI_CLOCK_POLARITY_IDLE_LOW = 0,
    SPI_CLOCK_POLARITY_IDLE_HIGH = 1

} SPI_CLOCK_POLARITY;

typedef enum {

    SPI_FIFO_INTERRUPT_NOT_SUPPORTED = 0

} SPI_FIFO_INTERRUPT;

typedef enum {

    SPI_ERROR_INTERRUPT_NOT_SUPPORTED = 0

} SPI_ERROR_INTERRUPT;

typedef enum {

    SPI_PIN_SLAVE_SELECT = 0,
    SPI_PIN_DATA_OUT = 1

} SPI_PIN;

typedef enum {

    SPI_FIFO_TYPE_NOT_SUPPORTED = 0

} SPI_FIFO_TYPE;

typedef enum {

    SPI_BAUD_RATE_CLOCK_NOT_SUPPORTED = 0

} SPI_BAUD_RATE_CLOCK;

typedef enum {

    SPI_FRAME_SYNC_PULSE_NOT_SUPPORTED = 0

} SPI_FRAME_SYNC_PULSE;

typedef enum {

    SPI_FRAME_PULSE_POLARITY_ACTIVE_LOW = 0,
    SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH = 1

} SPI_FRAME_PULSE_POLARITY;

typedef enum {

    SPI_FRAME_PULSE_DIRECTION_OUTPUT = 0,
    SPI_FRAME_PULSE_DIRECTION_INPUT = 1

} SPI_FRAME_PULSE_DIRECTION;

typedef enum {

    SPI_FRAME_PULSE_EDGE_PRECEDES_FIRST_BIT_CLOCK = 0,
    SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK = 1

} SPI_FRAME_PULSE_EDGE;

typedef enum {

    SPI_FRAME_PULSE_WIDTH_NOT_SUPPORTED = 0

} SPI_FRAME_PULSE_WIDTH;

typedef enum {

    SPI_AUDIO_PROTOCOL_NOT_SUPPORTED = 0

} SPI_AUDIO_PROTOCOL;

typedef enum {

    SPI_AUDIO_TRANSMIT_MODE_NOT_SUPPORTED = 0

} SPI_AUDIO_TRANSMIT_MODE;

typedef enum {

    SPI_AUDIO_ERROR_NOT_SUPPORTED = 0

} SPI_AUDIO_ERROR;

typedef enum {

    SPI_AUDIO_COMMUNICATION_WIDTH_NOT_SUPPORTED = 0

} SPI_AUDIO_COMMUNICATION_WIDTH;

INLINE SFR_TYPE* _SPI_FRAMED_COMMUNICATION_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_FRAME_SYNC_PULSE_DIRECTION_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_FRAME_SYNC_PULSE_POLARITY_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_FRAME_SYNC_PULSE_EDGE_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_ENABLE_CONTROL_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_STOP_IN_IDLE_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_PIN_CONTROL_SDO_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_MODE32_COMMUNICATION_WIDTH_PIC32_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_MODE16_COMMUNICATION_WIDTH_PIC32_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_INPUT_SAMPLE_PHASE_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_OUTPUT_DATA_PHASE_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_PIN_CONTROL_SS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_CLOCK_POLARITY_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_MASTER_CONTROL_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1CON;
        case SPI_ID_2 :
            return &SPI2CON;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_BUS_STATUS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1STAT;
        case SPI_ID_2 :
            return &SPI2STAT;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_RECEIVER_OVERFLOW_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1STAT;
        case SPI_ID_2 :
            return &SPI2STAT;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_TRANSMIT_BUFFER_EMPTY_STATUS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1STAT;
        case SPI_ID_2 :
            return &SPI2STAT;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_RECEIVE_BUFFER_STATUS_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1STAT;
        case SPI_ID_2 :
            return &SPI2STAT;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_BUFFER_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1BUF;
        case SPI_ID_2 :
            return &SPI2BUF;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SPI_BAUD_RATE_VREG(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return &SPI1BRG;
        case SPI_ID_2 :
            return &SPI2BRG;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _SPI_FRAMED_COMMUNICATION_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMEN_MASK;
        case SPI_ID_2 :
            return _SPI2CON_FRMEN_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_DIRECTION_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMSYNC_MASK;
        case SPI_ID_2 :
            return _SPI2CON_FRMSYNC_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_POLARITY_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMPOL_MASK;
        case SPI_ID_2 :
            return _SPI2CON_FRMPOL_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_EDGE_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SPIFE_MASK;
        case SPI_ID_2 :
            return _SPI2CON_SPIFE_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_ENABLE_CONTROL_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_ON_MASK;
        case SPI_ID_2 :
            return _SPI2CON_ON_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_STOP_IN_IDLE_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SIDL_MASK;
        case SPI_ID_2 :
            return _SPI2CON_SIDL_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SDO_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_DISSDO_MASK;
        case SPI_ID_2 :
            return _SPI2CON_DISSDO_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE32_COMMUNICATION_WIDTH_PIC32_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE32_MASK;
        case SPI_ID_2 :
            return _SPI2CON_MODE32_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE16_COMMUNICATION_WIDTH_PIC32_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE16_MASK;
        case SPI_ID_2 :
            return _SPI2CON_MODE16_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_INPUT_SAMPLE_PHASE_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SMP_MASK;
        case SPI_ID_2 :
            return _SPI2CON_SMP_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_OUTPUT_DATA_PHASE_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKE_MASK;
        case SPI_ID_2 :
            return _SPI2CON_CKE_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SS_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SSEN_MASK;
        case SPI_ID_2 :
            return _SPI2CON_SSEN_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_CLOCK_POLARITY_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKP_MASK;
        case SPI_ID_2 :
            return _SPI2CON_CKP_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MASTER_CONTROL_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MSTEN_MASK;
        case SPI_ID_2 :
            return _SPI2CON_MSTEN_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUS_STATUS_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIBUSY_MASK;
        case SPI_ID_2 :
            return _SPI2STAT_SPIBUSY_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVER_OVERFLOW_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIROV_MASK;
        case SPI_ID_2 :
            return _SPI2STAT_SPIROV_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_TRANSMIT_BUFFER_EMPTY_STATUS_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPITBE_MASK;
        case SPI_ID_2 :
            return _SPI2STAT_SPITBE_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVE_BUFFER_STATUS_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIRBF_MASK;
        case SPI_ID_2 :
            return _SPI2STAT_SPIRBF_MASK;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUFFER_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)-1;
        case SPI_ID_2 :
            return (SFR_DATA)-1;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BAUD_RATE_MASK(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)-1;
        case SPI_ID_2 :
            return (SFR_DATA)-1;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAMED_COMMUNICATION_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMEN_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_FRMEN_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_DIRECTION_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMSYNC_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_FRMSYNC_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_POLARITY_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMPOL_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_FRMPOL_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_EDGE_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SPIFE_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_SPIFE_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_ENABLE_CONTROL_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_ON_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_ON_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_STOP_IN_IDLE_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SIDL_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_SIDL_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SDO_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_DISSDO_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_DISSDO_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE32_COMMUNICATION_WIDTH_PIC32_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE32_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_MODE32_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE16_COMMUNICATION_WIDTH_PIC32_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE16_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_MODE16_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_INPUT_SAMPLE_PHASE_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SMP_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_SMP_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_OUTPUT_DATA_PHASE_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKE_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_CKE_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SSEN_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_SSEN_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_CLOCK_POLARITY_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKP_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_CKP_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MASTER_CONTROL_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MSTEN_POSITION;
        case SPI_ID_2 :
            return _SPI2CON_MSTEN_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUS_STATUS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIBUSY_POSITION;
        case SPI_ID_2 :
            return _SPI2STAT_SPIBUSY_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVER_OVERFLOW_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIROV_POSITION;
        case SPI_ID_2 :
            return _SPI2STAT_SPIROV_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_TRANSMIT_BUFFER_EMPTY_STATUS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPITBE_POSITION;
        case SPI_ID_2 :
            return _SPI2STAT_SPITBE_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVE_BUFFER_STATUS_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIRBF_POSITION;
        case SPI_ID_2 :
            return _SPI2STAT_SPIRBF_POSITION;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUFFER_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)0;
        case SPI_ID_2 :
            return (SFR_DATA)0;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BAUD_RATE_POS(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)0;
        case SPI_ID_2 :
            return (SFR_DATA)0;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAMED_COMMUNICATION_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMEN_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_FRMEN_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_DIRECTION_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMSYNC_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_FRMSYNC_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_POLARITY_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_FRMPOL_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_FRMPOL_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_FRAME_SYNC_PULSE_EDGE_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SPIFE_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_SPIFE_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_ENABLE_CONTROL_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_ON_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_ON_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_STOP_IN_IDLE_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SIDL_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_SIDL_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SDO_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_DISSDO_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_DISSDO_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE32_COMMUNICATION_WIDTH_PIC32_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE32_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_MODE32_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MODE16_COMMUNICATION_WIDTH_PIC32_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MODE16_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_MODE16_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_INPUT_SAMPLE_PHASE_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SMP_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_SMP_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_OUTPUT_DATA_PHASE_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKE_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_CKE_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_PIN_CONTROL_SS_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_SSEN_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_SSEN_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_CLOCK_POLARITY_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_CKP_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_CKP_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_MASTER_CONTROL_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1CON_MSTEN_LENGTH;
        case SPI_ID_2 :
            return _SPI2CON_MSTEN_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUS_STATUS_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIBUSY_LENGTH;
        case SPI_ID_2 :
            return _SPI2STAT_SPIBUSY_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVER_OVERFLOW_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIROV_LENGTH;
        case SPI_ID_2 :
            return _SPI2STAT_SPIROV_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_TRANSMIT_BUFFER_EMPTY_STATUS_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPITBE_LENGTH;
        case SPI_ID_2 :
            return _SPI2STAT_SPITBE_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_RECEIVE_BUFFER_STATUS_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return _SPI1STAT_SPIRBF_LENGTH;
        case SPI_ID_2 :
            return _SPI2STAT_SPIRBF_LENGTH;
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BUFFER_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SPI_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SPI_BAUD_RATE_LEN(SPI_MODULE_ID i)
{
    switch (i) {
        case SPI_ID_1 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SPI_ID_2 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/spi_EnableControl_Default.h"
#include "../templates/spi_StopInIdle_Default.h"
#include "../templates/spi_ReceiverOverflow_Default.h"
#include "../templates/spi_TransmitBufferFullStatus_Unsupported.h"
#include "../templates/spi_TransmitBufferEmptyStatus_Default.h"
#include "../templates/spi_ReceiveBufferStatus_Default.h"
#include "../templates/spi_PinControl_PIC32_1.h"
#include "../templates/spi_CommunicationWidth_PIC32.h"
#include "../templates/spi_AudioCommunicationWidth_Unsupported.h"
#include "../templates/spi_InputSamplePhase_Default.h"
#include "../templates/spi_OutputDataPhase_Default.h"
#include "../templates/spi_ClockPolarity_Default.h"
#include "../templates/spi_MasterControl_Default.h"
#include "../templates/spi_SecondaryPrescale_Unsupported.h"
#include "../templates/spi_PrimaryPrescale_Unsupported.h"
#include "../templates/spi_BaudRate_Default.h"
#include "../templates/spi_BusStatus_Default.h"
#include "../templates/spi_ReadDataSignStatus_Unsupported.h"
#include "../templates/spi_SlaveSelectControl_Unsupported.h"
#include "../templates/spi_TransmitUnderRunStatus_Unsupported.h"
#include "../templates/spi_FIFOControl_Unsupported.h"
#include "../templates/spi_FIFOCount_Unsupported.h"
#include "../templates/spi_ReceiveFIFOStatus_Unsupported.h"
#include "../templates/spi_FIFOShiftRegisterEmptyStatus_Unsupported.h"
#include "../templates/spi_FIFOInterruptMode_Unsupported.h"
#include "../templates/spi_FramedCommunication_Default.h"
#include "../templates/spi_FrameSyncPulseDirection_Default.h"
#include "../templates/spi_FrameSyncPulsePolarity_Default.h"
#include "../templates/spi_FrameSyncPulseEdge_Default.h"
#include "../templates/spi_FrameSyncPulseWidth_Unsupported.h"
#include "../templates/spi_FrameSyncPulseCounter_Unsupported.h"
#include "../templates/spi_FrameErrorStatus_Unsupported.h"
#include "../templates/spi_Buffer_Default.h"
#include "../templates/spi_BaudRateClock_Unsupported.h"
#include "../templates/spi_ErrorInterruptControl_Unsupported.h"
#include "../templates/spi_AudioErrorControl_Unsupported.h"
#include "../templates/spi_AudioProtocolControl_Unsupported.h"
#include "../templates/spi_AudioTransmitMode_Unsupported.h"
#include "../templates/spi_AudioProtocolMode_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_SPI_Enable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_Enable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_Enable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SPI_Disable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_Disable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_Disable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsEnableControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsEnableControl_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsEnableControl_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_StopInIdleEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_StopInIdleEnable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_StopInIdleEnable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SPI_StopInIdleDisable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_StopInIdleDisable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_StopInIdleDisable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsStopInIdleControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsStopInIdleControl_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsStopInIdleControl_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_ReceiverHasOverflowed(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ReceiverHasOverflowed_Default(index);
        case SPI_ID_2 :
            return SPI_ReceiverHasOverflowed_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_ReceiverOverflowClear(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_ReceiverOverflowClear_Default(index);
            break;
        case SPI_ID_2 :
            SPI_ReceiverOverflowClear_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsReceiverOverflow(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsReceiverOverflow_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsReceiverOverflow_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_TransmitBufferIsFull(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_TransmitBufferIsFull_Unsupported(index);
        case SPI_ID_2 :
            return SPI_TransmitBufferIsFull_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsTransmitBufferFullStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsTransmitBufferFullStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsTransmitBufferFullStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_TransmitBufferIsEmpty(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_TransmitBufferIsEmpty_Default(index);
        case SPI_ID_2 :
            return SPI_TransmitBufferIsEmpty_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_ExistsTransmitBufferEmptyStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsTransmitBufferEmptyStatus_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsTransmitBufferEmptyStatus_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_ReceiverBufferIsFull(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ReceiverBufferIsFull_Default(index);
        case SPI_ID_2 :
            return SPI_ReceiverBufferIsFull_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_ExistsReceiveBufferStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsReceiveBufferStatus_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsReceiveBufferStatus_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_PinEnable(SPI_MODULE_ID index, SPI_PIN pin)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_PinEnable_PIC32_1(index, pin);
            break;
        case SPI_ID_2 :
            SPI_PinEnable_PIC32_1(index, pin);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SPI_PinDisable(SPI_MODULE_ID index, SPI_PIN pin)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_PinDisable_PIC32_1(index, pin);
            break;
        case SPI_ID_2 :
            SPI_PinDisable_PIC32_1(index, pin);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsPinControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsPinControl_PIC32_1(index);
        case SPI_ID_2 :
            return SPI_ExistsPinControl_PIC32_1(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_CommunicationWidthSelect(SPI_MODULE_ID index, SPI_COMMUNICATION_WIDTH width)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_CommunicationWidthSelect_PIC32(index, width);
            break;
        case SPI_ID_2 :
            SPI_CommunicationWidthSelect_PIC32(index, width);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsCommunicationWidth(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsCommunicationWidth_PIC32(index);
        case SPI_ID_2 :
            return SPI_ExistsCommunicationWidth_PIC32(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioCommunicationWidthSelect(SPI_MODULE_ID index, SPI_AUDIO_COMMUNICATION_WIDTH mode)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioCommunicationWidthSelect_Unsupported(index, mode);
            break;
        case SPI_ID_2 :
            SPI_AudioCommunicationWidthSelect_Unsupported(index, mode);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsAudioCommunicationWidth(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsAudioCommunicationWidth_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsAudioCommunicationWidth_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_InputSamplePhaseSelect(SPI_MODULE_ID index, SPI_INPUT_SAMPLING_PHASE phase)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_InputSamplePhaseSelect_Default(index, phase);
            break;
        case SPI_ID_2 :
            SPI_InputSamplePhaseSelect_Default(index, phase);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsInputSamplePhase(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsInputSamplePhase_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsInputSamplePhase_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_OutputDataPhaseSelect(SPI_MODULE_ID index, SPI_OUTPUT_DATA_PHASE phase)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_OutputDataPhaseSelect_Default(index, phase);
            break;
        case SPI_ID_2 :
            SPI_OutputDataPhaseSelect_Default(index, phase);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsOutputDataPhase(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsOutputDataPhase_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsOutputDataPhase_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_ClockPolaritySelect(SPI_MODULE_ID index, SPI_CLOCK_POLARITY polarity)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_ClockPolaritySelect_Default(index, polarity);
            break;
        case SPI_ID_2 :
            SPI_ClockPolaritySelect_Default(index, polarity);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsClockPolarity(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsClockPolarity_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsClockPolarity_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_MasterEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_MasterEnable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_MasterEnable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SPI_SlaveEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_SlaveEnable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_SlaveEnable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsMasterControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsMasterControl_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsMasterControl_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_PrescaleSecondarySelect(SPI_MODULE_ID index, SPI_PRESCALE_SECONDARY prescale)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_PrescaleSecondarySelect_Unsupported(index, prescale);
            break;
        case SPI_ID_2 :
            SPI_PrescaleSecondarySelect_Unsupported(index, prescale);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsSecondaryPrescale(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsSecondaryPrescale_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsSecondaryPrescale_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_PrescalePrimarySelect(SPI_MODULE_ID index, SPI_PRESCALE_PRIMARY prescale)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_PrescalePrimarySelect_Unsupported(index, prescale);
            break;
        case SPI_ID_2 :
            SPI_PrescalePrimarySelect_Unsupported(index, prescale);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsPrimaryPrescale(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsPrimaryPrescale_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsPrimaryPrescale_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_BaudRateSet(SPI_MODULE_ID index, uint32_t clockFrequency, uint32_t baudRate)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_BaudRateSet_Default(index, clockFrequency, baudRate);
            break;
        case SPI_ID_2 :
            SPI_BaudRateSet_Default(index, clockFrequency, baudRate);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsBaudRate(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsBaudRate_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsBaudRate_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_IsBusy(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_IsBusy_Default(index);
        case SPI_ID_2 :
            return SPI_IsBusy_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SPI_ExistsBusStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsBusStatus_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsBusStatus_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ReadDataIsSignExtended(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ReadDataIsSignExtended_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ReadDataIsSignExtended_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsReadDataSignStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsReadDataSignStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsReadDataSignStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_SlaveSelectEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_SlaveSelectEnable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_SlaveSelectEnable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_SlaveSelectDisable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_SlaveSelectDisable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_SlaveSelectDisable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsSlaveSelectControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsSlaveSelectControl_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsSlaveSelectControl_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_TransmitUnderRunStatusGet(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_TransmitUnderRunStatusGet_Unsupported(index);
        case SPI_ID_2 :
            return SPI_TransmitUnderRunStatusGet_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsTransmitUnderRunStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsTransmitUnderRunStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsTransmitUnderRunStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_FIFOEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FIFOEnable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_FIFOEnable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_FIFODisable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FIFODisable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_FIFODisable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFIFOControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFIFOControl_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFIFOControl_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t _PLIB_UNSUPPORTED PLIB_SPI_FIFOCountGet(SPI_MODULE_ID index, SPI_FIFO_TYPE type)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_FIFOCountGet_Unsupported(index, type);
        case SPI_ID_2 :
            return SPI_FIFOCountGet_Unsupported(index, type);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFIFOCount(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFIFOCount_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFIFOCount_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ReceiverFIFOIsEmpty(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ReceiverFIFOIsEmpty_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ReceiverFIFOIsEmpty_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsReceiveFIFOStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsReceiveFIFOStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsReceiveFIFOStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_FIFOShiftRegisterIsEmpty(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_FIFOShiftRegisterIsEmpty_Unsupported(index);
        case SPI_ID_2 :
            return SPI_FIFOShiftRegisterIsEmpty_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFIFOShiftRegisterEmptyStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFIFOShiftRegisterEmptyStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFIFOShiftRegisterEmptyStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_FIFOInterruptModeSelect(SPI_MODULE_ID index, SPI_FIFO_INTERRUPT mode)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FIFOInterruptModeSelect_Unsupported(index, mode);
            break;
        case SPI_ID_2 :
            SPI_FIFOInterruptModeSelect_Unsupported(index, mode);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFIFOInterruptMode(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFIFOInterruptMode_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFIFOInterruptMode_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_FramedCommunicationEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FramedCommunicationEnable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_FramedCommunicationEnable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SPI_FramedCommunicationDisable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FramedCommunicationDisable_Default(index);
            break;
        case SPI_ID_2 :
            SPI_FramedCommunicationDisable_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsFramedCommunication(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFramedCommunication_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsFramedCommunication_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_FrameSyncPulseDirectionSelect(SPI_MODULE_ID index, SPI_FRAME_PULSE_DIRECTION direction)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FrameSyncPulseDirectionSelect_Default(index, direction);
            break;
        case SPI_ID_2 :
            SPI_FrameSyncPulseDirectionSelect_Default(index, direction);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsFrameSyncPulseDirection(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameSyncPulseDirection_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameSyncPulseDirection_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_FrameSyncPulsePolaritySelect(SPI_MODULE_ID index, SPI_FRAME_PULSE_POLARITY polarity)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FrameSyncPulsePolaritySelect_Default(index, polarity);
            break;
        case SPI_ID_2 :
            SPI_FrameSyncPulsePolaritySelect_Default(index, polarity);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsFrameSyncPulsePolarity(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameSyncPulsePolarity_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameSyncPulsePolarity_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_FrameSyncPulseEdgeSelect(SPI_MODULE_ID index, SPI_FRAME_PULSE_EDGE edge)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FrameSyncPulseEdgeSelect_Default(index, edge);
            break;
        case SPI_ID_2 :
            SPI_FrameSyncPulseEdgeSelect_Default(index, edge);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsFrameSyncPulseEdge(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameSyncPulseEdge_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameSyncPulseEdge_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_FrameSyncPulseWidthSelect(SPI_MODULE_ID index, SPI_FRAME_PULSE_WIDTH width)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FrameSyncPulseWidthSelect_Unsupported(index, width);
            break;
        case SPI_ID_2 :
            SPI_FrameSyncPulseWidthSelect_Unsupported(index, width);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFrameSyncPulseWidth(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameSyncPulseWidth_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameSyncPulseWidth_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_FrameSyncPulseCounterSelect(SPI_MODULE_ID index, SPI_FRAME_SYNC_PULSE pulse)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_FrameSyncPulseCounterSelect_Unsupported(index, pulse);
            break;
        case SPI_ID_2 :
            SPI_FrameSyncPulseCounterSelect_Unsupported(index, pulse);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFrameSyncPulseCounter(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameSyncPulseCounter_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameSyncPulseCounter_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_FrameErrorStatusGet(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_FrameErrorStatusGet_Unsupported(index);
        case SPI_ID_2 :
            return SPI_FrameErrorStatusGet_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsFrameErrorStatus(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsFrameErrorStatus_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsFrameErrorStatus_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SPI_BufferClear(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_BufferClear_Default(index);
            break;
        case SPI_ID_2 :
            SPI_BufferClear_Default(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SPI_DATA_TYPE PLIB_SPI_BufferRead(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_BufferRead_Default(index);
        case SPI_ID_2 :
            return SPI_BufferRead_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (SPI_DATA_TYPE)0;
    }
}

INLINE_API void PLIB_SPI_BufferWrite(SPI_MODULE_ID index, SPI_DATA_TYPE data)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_BufferWrite_Default(index, data);
            break;
        case SPI_ID_2 :
            SPI_BufferWrite_Default(index, data);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SPI_ExistsBuffer(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsBuffer_Default(index);
        case SPI_ID_2 :
            return SPI_ExistsBuffer_Default(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_BaudRateClockSelect(SPI_MODULE_ID index, SPI_BAUD_RATE_CLOCK type)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_BaudRateClockSelect_Unsupported(index, type);
            break;
        case SPI_ID_2 :
            SPI_BaudRateClockSelect_Unsupported(index, type);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsBaudRateClock(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsBaudRateClock_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsBaudRateClock_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_ErrorInterruptEnable(SPI_MODULE_ID index, SPI_ERROR_INTERRUPT error)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_ErrorInterruptEnable_Unsupported(index, error);
            break;
        case SPI_ID_2 :
            SPI_ErrorInterruptEnable_Unsupported(index, error);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_ErrorInterruptDisable(SPI_MODULE_ID index, SPI_ERROR_INTERRUPT error)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_ErrorInterruptDisable_Unsupported(index, error);
            break;
        case SPI_ID_2 :
            SPI_ErrorInterruptDisable_Unsupported(index, error);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsErrorInterruptControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsErrorInterruptControl_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsErrorInterruptControl_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioErrorEnable(SPI_MODULE_ID index, SPI_AUDIO_ERROR error)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioErrorEnable_Unsupported(index, error);
            break;
        case SPI_ID_2 :
            SPI_AudioErrorEnable_Unsupported(index, error);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioErrorDisable(SPI_MODULE_ID index, SPI_AUDIO_ERROR error)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioErrorDisable_Unsupported(index, error);
            break;
        case SPI_ID_2 :
            SPI_AudioErrorDisable_Unsupported(index, error);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsAudioErrorControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsAudioErrorControl_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsAudioErrorControl_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioProtocolEnable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioProtocolEnable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_AudioProtocolEnable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioProtocolDisable(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioProtocolDisable_Unsupported(index);
            break;
        case SPI_ID_2 :
            SPI_AudioProtocolDisable_Unsupported(index);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsAudioProtocolControl(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsAudioProtocolControl_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsAudioProtocolControl_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioTransmitModeSelect(SPI_MODULE_ID index, SPI_AUDIO_TRANSMIT_MODE mode)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioTransmitModeSelect_Unsupported(index, mode);
            break;
        case SPI_ID_2 :
            SPI_AudioTransmitModeSelect_Unsupported(index, mode);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsAudioTransmitMode(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsAudioTransmitMode_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsAudioTransmitMode_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_SPI_AudioProtocolModeSelect(SPI_MODULE_ID index, SPI_AUDIO_PROTOCOL mode)
{
    switch (index) {
        case SPI_ID_1 :
            SPI_AudioProtocolModeSelect_Unsupported(index, mode);
            break;
        case SPI_ID_2 :
            SPI_AudioProtocolModeSelect_Unsupported(index, mode);
            break;
        case SPI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_SPI_ExistsAudioProtocolMode(SPI_MODULE_ID index)
{
    switch (index) {
        case SPI_ID_1 :
            return SPI_ExistsAudioProtocolMode_Unsupported(index);
        case SPI_ID_2 :
            return SPI_ExistsAudioProtocolMode_Unsupported(index);
        case SPI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
