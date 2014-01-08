/* Created by plibgen $Revision: 1.29 $ */

#ifndef _SQI_P32MZ1024ECM100_H
#define _SQI_P32MZ1024ECM100_H

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

    SQI_ID_0 = 0,
    SQI_NUMBER_OF_MODULES

} SQI_MODULE_ID;

typedef enum {

    SQI_XFER_MODE_XIP = 3,
    SQI_XFER_MODE_DMA = 2,
    SQI_XFER_MODE_PIO = 1

} SQI_XFER_MODE;

typedef enum {

    SQI_DATA_MODE_SF = 1,
    SQI_DATA_MODE_3 = 3,
    SQI_DATA_MODE_0 = 0

} SQI_DATA_MODE;

typedef enum {

    SQI_DATA_FORMAT_LSBF = 1,
    SQI_DATA_FORMAT_MSBF = 3

} SQI_DATA_FORMAT;

typedef enum {

    SQI_DATA_OEN_QUAD = 2,
    SQI_DATA_OEN_DUAL = 1,
    SQI_DATA_OEN_SINGLE = 0

} SQI_DATA_OEN;

typedef enum {

    SQI_CS_OEN_BOTH = 3,
    SQI_CS_OEN_1 = 2,
    SQI_CS_OEN_0 = 1,
    SQI_CS_OEN_NONE = 0

} SQI_CS_OEN;

typedef enum {

    SQI_CMD_RECEIVE = 2,
    SQI_CMD_TRANSMIT = 1,
    SQI_CMD_IDLE = 0

} SQI_XFER_CMD;

typedef enum {

    SQI_LANE_QUAD = 2,
    SQI_LANE_DUAL = 1,
    SQI_LANE_SINGLE = 0

} SQI_LANE_MODE;

typedef enum {

    SQI_CS_1 = 1,
    SQI_CS_0 = 0

} SQI_CS_NUM;

typedef enum {

    CLK_DIV_256 = 80,
    CLK_DIV_128 = 40,
    CLK_DIV_64 = 20,
    CLK_DIV_32 = 10,
    CLK_DIV_16 = 8,
    CLK_DIV_8 = 4,
    CLK_DIV_4 = 2,
    CLK_DIV_2 = 1,
    CLK_DIV_1 = 0

} SQI_CLK_DIV;

typedef enum {

    ADDR_BYTES_4 = 4,
    ADDR_BYTES_3 = 3,
    ADDR_BYTES_2 = 2,
    ADDR_BYTES_1 = 1,
    ADDR_BYTES_0 = 0

} SQI_ADDR_BYTES;

typedef enum {

    DUMMY_BYTES_7 = 7,
    DUMMY_BYTES_6 = 6,
    DUMMY_BYTES_5 = 5,
    DUMMY_BYTES_4 = 4,
    DUMMY_BYTES_3 = 3,
    DUMMY_BYTES_2 = 2,
    DUMMY_BYTES_1 = 1,
    DUMMY_BYTES_0 = 0

} SQI_DUMMY_BYTES;

typedef enum {

    MODE_BYTES_3 = 3,
    MODE_BYTES_2 = 2,
    MODE_BYTES_1 = 1,
    MODE_BYTES_0 = 0

} SQI_MODE_BYTES;

typedef enum {

    SQI_PKTCOMP = 10,
    SQI_BDDONE = 9,
    SQI_CONTHR = 8,
    SQI_CONEMPTY = 7,
    SQI_CONFULL = 6,
    SQI_RXTHR = 5,
    SQI_RXEMPTY = 4,
    SQI_RXFULL = 3,
    SQI_TXTHR = 2,
    SQI_TXEMPTY = 1,
    SQI_TXFULL = 0,
    SQI_ALL_INT = 0xFF

} SQI_INTERRUPTS;

typedef enum {

    BD_STATE_DISABLED = 5,
    BD_STATE_DONE = 4,
    BD_STATE_PROCESSING_DATA = 3,
    BD_STATE_BEING_FETCHED = 2,
    BD_STATE_FETCH_REQ_PENDING = 1,
    BD_STATE_IDLE = 0

} SQI_BD_STATE;

INLINE SFR_TYPE* _SQI_NUMBER_OF_DUMMY_BYTES_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_NUMBER_OF_ADDRESS_BYTES_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_FLASH_READ_OPCODE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DATA_LANE_MODE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DUMMY_LANE_MODE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_MODE_LANES_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_ADDRESS_LANE_MODE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CMD_LANE_MODE_OR_XCON1_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_XIP_CHIP_SELECT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_XIP_MODE_CODE_OR_XCON2_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1XCON2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_ENABLE_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CHIP_SELECT_PIN_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DATA_OUTPUT_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_SOFT_RESET_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_BURST_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_SQID2_AS_HOLD_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_SQID3_AS_WRITE_PROTECT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_SF_MODE_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIVE_DATA_LATCH_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DATA_FORMAT_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CPOL_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CPHA_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSFER_MODE_CONTROL_OR_CFG_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CFG;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DEASSERT_CS_AFTER_TRANSFER_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CHIP_SELECT_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_LANE_MODE_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSFER_COMMAND_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSFER_COUNT_IN_BYTES_OR_CON_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CLOCK_DIVIDER_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CLKCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CLOCK_IS_STABLE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CLKCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CLOCK_CONTROL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CLKCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIVE_BUFFER_THRESHOLD_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CMDTHR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_BUFFER_THRESHOLD_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1CMDTHR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIEVE_BUFFER_THRESHOLD_FOR_INT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1INTTHR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_BUFFER_THRESHOLD_FOR_INT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1INTTHR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_INTERRUPT_ENABLE_VAL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1INTEN;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_INTERRUPT_FLAG_VAL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1INTSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_DATA_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1TXBUF;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIVE_DATA_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1RXBUF;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_BUF_FREE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIEVE_BUF_COUNT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT1;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_D3_PIN_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_D2_PIN_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_D1_PIN_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_D0_PIN_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIEVER_UNDER_RUN_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMITTER_OVER_FLOW_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1STAT2;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DMA_ENABLE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_BD_POLL_ENABLE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DMA_START_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CURRENT_BD_ADDRESS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDCURADD;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_BD_BASE_ADDR_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDBASEADDR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_BD_PROCESS_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DMA_IN_PROGRESS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_DMA_IS_ACTIVE_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_BD_CONTROL_WORD_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_POLL_COUNTER_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDPOLLCON;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDTXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_TRANSMIT_BUF_COUNT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDTXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CURRENT_TRANSMIT_LENGTH_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDTXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIVE_STATUS_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDRXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_RECEIVE_BUF_COUNT_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDRXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CURRENT_RECEIVE_LENGTH_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1BDRXDSTAT;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_CONTROL_BUF_THRESHOLD_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1THR;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _SQI_INTERRUPT_SIGNAL_ENABLE_VAL_VREG(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return &SQI1INTSEN;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_DUMMY_BYTES_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_DUMMYBYTES_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_ADDRESS_BYTES_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_ADDRBYTES_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_FLASH_READ_OPCODE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_READOPCODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_LANE_MODE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDATA_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DUMMY_LANE_MODE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDUMMY_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_MODE_LANES_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEMODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ADDRESS_LANE_MODE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEADDR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CMD_LANE_MODE_OR_XCON1_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPECMD_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_CHIP_SELECT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_DEVSEL_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODEBYTES_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_MODE_CODE_OR_XCON2_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODECODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ENABLE_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SQIEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_PIN_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CSEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_OUTPUT_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_DATAEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SOFT_RESET_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RESET_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BURST_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_BURSTEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID2_AS_HOLD_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_HOLD_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID3_AS_WRITE_PROTECT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_WP_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SF_MODE_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SERMODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_LATCH_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RXLATCH_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_FORMAT_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_LSBF_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPOL_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPOL_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPHA_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPHA_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_MODE_CONTROL_OR_CFG_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_MODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DEASSERT_CS_AFTER_TRANSFER_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DASSERT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DEVSEL_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_LANE_MODE_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_LANEMODE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COMMAND_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_CMDINIT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COUNT_IN_BYTES_OR_CON_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_TXRXCOUNT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_DIVIDER_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_CLKDIV_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_IS_STABLE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_STABLE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_CONTROL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_EN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUFFER_THRESHOLD_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_RXCMDTHR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_TXCMDTHR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUFFER_THRESHOLD_FOR_INT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_RXINTTHR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_FOR_INT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_TXINTTHR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_ENABLE_VAL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTEN_PKTCOMPIE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_FLAG_VAL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSTAT_PKTCOMPIF_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_DATA_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1TXBUF_TXDATA_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1RXBUF_RXDATA_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_FREE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_TXBUFFREE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUF_COUNT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_RXBUFCNT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D3_PIN_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID3_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D2_PIN_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID2_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D1_PIN_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID1_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D0_PIN_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID0_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVER_UNDER_RUN_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_RXUN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMITTER_OVER_FLOW_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_TXOV_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_ENABLE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_DMAEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_POLL_ENABLE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_POLLEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_START_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_START_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_BD_ADDRESS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCURADD_BDCURRADDR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_BASE_ADDR_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDBASEADDR_BDADDR_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_PROCESS_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDSTATE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IN_PROGRESS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMASTART_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IS_ACTIVE_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMAACTV_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_CONTROL_WORD_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDCON_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_POLL_COUNTER_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDPOLLCON_POLLCON_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXSTATE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_COUNT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXBUFCNT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_TRANSMIT_LENGTH_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXCURBUFLEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_STATUS_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXSTATE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUF_COUNT_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXBUFCNT_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_RECEIVE_LENGTH_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXCURBUFLEN_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CONTROL_BUF_THRESHOLD_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1THR_THRES_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_SIGNAL_ENABLE_VAL_MASK(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSEN_PKTCOMPISE_MASK;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_DUMMY_BYTES_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_DUMMYBYTES_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_ADDRESS_BYTES_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_ADDRBYTES_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_FLASH_READ_OPCODE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_READOPCODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_LANE_MODE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDATA_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DUMMY_LANE_MODE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDUMMY_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_MODE_LANES_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEMODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ADDRESS_LANE_MODE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEADDR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CMD_LANE_MODE_OR_XCON1_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPECMD_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_CHIP_SELECT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_DEVSEL_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODEBYTES_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_MODE_CODE_OR_XCON2_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODECODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ENABLE_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SQIEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_PIN_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CSEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_OUTPUT_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_DATAEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SOFT_RESET_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RESET_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BURST_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_BURSTEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID2_AS_HOLD_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_HOLD_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID3_AS_WRITE_PROTECT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_WP_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SF_MODE_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SERMODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_LATCH_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RXLATCH_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_FORMAT_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_LSBF_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPOL_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPOL_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPHA_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPHA_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_MODE_CONTROL_OR_CFG_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_MODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DEASSERT_CS_AFTER_TRANSFER_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DASSERT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DEVSEL_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_LANE_MODE_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_LANEMODE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COMMAND_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_CMDINIT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COUNT_IN_BYTES_OR_CON_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_TXRXCOUNT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_DIVIDER_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_CLKDIV_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_IS_STABLE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_STABLE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_CONTROL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_EN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUFFER_THRESHOLD_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_RXCMDTHR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_TXCMDTHR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUFFER_THRESHOLD_FOR_INT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_RXINTTHR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_FOR_INT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_TXINTTHR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_ENABLE_VAL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTEN_PKTCOMPIE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_FLAG_VAL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSTAT_PKTCOMPIF_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_DATA_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1TXBUF_TXDATA_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1RXBUF_RXDATA_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_FREE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_TXBUFFREE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUF_COUNT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_RXBUFCNT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D3_PIN_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID3_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D2_PIN_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID2_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D1_PIN_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID1_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D0_PIN_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID0_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVER_UNDER_RUN_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_RXUN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMITTER_OVER_FLOW_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_TXOV_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_ENABLE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_DMAEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_POLL_ENABLE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_POLLEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_START_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_START_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_BD_ADDRESS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCURADD_BDCURRADDR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_BASE_ADDR_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDBASEADDR_BDADDR_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_PROCESS_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDSTATE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IN_PROGRESS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMASTART_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IS_ACTIVE_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMAACTV_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_CONTROL_WORD_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDCON_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_POLL_COUNTER_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDPOLLCON_POLLCON_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXSTATE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_COUNT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXBUFCNT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_TRANSMIT_LENGTH_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXCURBUFLEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_STATUS_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXSTATE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUF_COUNT_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXBUFCNT_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_RECEIVE_LENGTH_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXCURBUFLEN_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CONTROL_BUF_THRESHOLD_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1THR_THRES_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_SIGNAL_ENABLE_VAL_POS(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSEN_PKTCOMPISE_POSITION;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_DUMMY_BYTES_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_DUMMYBYTES_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_NUMBER_OF_ADDRESS_BYTES_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_ADDRBYTES_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_FLASH_READ_OPCODE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_READOPCODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_LANE_MODE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDATA_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DUMMY_LANE_MODE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEDUMMY_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_MODE_LANES_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEMODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ADDRESS_LANE_MODE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPEADDR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CMD_LANE_MODE_OR_XCON1_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON1_TYPECMD_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_CHIP_SELECT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_DEVSEL_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_NUMBER_OF_MODE_BYTES_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODEBYTES_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_XIP_MODE_CODE_OR_XCON2_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1XCON2_MODECODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_ENABLE_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SQIEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_PIN_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CSEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_OUTPUT_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_DATAEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SOFT_RESET_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RESET_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BURST_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_BURSTEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID2_AS_HOLD_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_HOLD_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SQID3_AS_WRITE_PROTECT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_WP_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_SF_MODE_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_SERMODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_LATCH_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_RXLATCH_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DATA_FORMAT_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_LSBF_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPOL_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPOL_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CPHA_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_CPHA_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_MODE_CONTROL_OR_CFG_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CFG_MODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DEASSERT_CS_AFTER_TRANSFER_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DASSERT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CHIP_SELECT_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_DEVSEL_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_LANE_MODE_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_LANEMODE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COMMAND_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_CMDINIT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSFER_COUNT_IN_BYTES_OR_CON_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CON_TXRXCOUNT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_DIVIDER_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_CLKDIV_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_IS_STABLE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_STABLE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CLOCK_CONTROL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CLKCON_EN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUFFER_THRESHOLD_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_RXCMDTHR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1CMDTHR_TXCMDTHR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUFFER_THRESHOLD_FOR_INT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_RXINTTHR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUFFER_THRESHOLD_FOR_INT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTTHR_TXINTTHR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_ENABLE_VAL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTEN_PKTCOMPIE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_FLAG_VAL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSTAT_PKTCOMPIF_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_DATA_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1TXBUF_TXDATA_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_DATA_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1RXBUF_RXDATA_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_FREE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_TXBUFFREE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVE_BUF_COUNT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT1_RXBUFCNT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D3_PIN_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID3_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D2_PIN_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID2_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D1_PIN_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID1_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_D0_PIN_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_SQID0_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIEVER_UNDER_RUN_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_RXUN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMITTER_OVER_FLOW_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1STAT2_TXOV_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_ENABLE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_DMAEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_POLL_ENABLE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_POLLEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_START_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCON_START_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_BD_ADDRESS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDCURADD_BDCURRADDR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_BASE_ADDR_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDBASEADDR_BDADDR_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_PROCESS_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDSTATE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IN_PROGRESS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMASTART_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_DMA_IS_ACTIVE_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_DMAACTV_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_BD_CONTROL_WORD_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDSTAT_BDCON_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_POLL_COUNTER_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDPOLLCON_POLLCON_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXSTATE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_TRANSMIT_BUF_COUNT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXBUFCNT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_TRANSMIT_LENGTH_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDTXDSTAT_TXCURBUFLEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_STATUS_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXSTATE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_RECEIVE_BUF_COUNT_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXBUFCNT_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CURRENT_RECEIVE_LENGTH_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1BDRXDSTAT_RXCURBUFLEN_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_CONTROL_BUF_THRESHOLD_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1THR_THRES_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _SQI_INTERRUPT_SIGNAL_ENABLE_VAL_LEN(SQI_MODULE_ID i)
{
    switch (i) {
        case SQI_ID_0 :
            return _SQI1INTSEN_PKTCOMPISE_LENGTH;
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/sqi_XIPNumberOfDummyBytes_Default.h"
#include "../templates/sqi_XIPNumberOfAddressBytes_Default.h"
#include "../templates/sqi_XIPReadOpCode_Default.h"
#include "../templates/sqi_XIPLaneMode_Default.h"
#include "../templates/sqi_XIPControlWord1_Default.h"
#include "../templates/sqi_XIPChipSelect_Default.h"
#include "../templates/sqi_XIPModeBytes_Default.h"
#include "../templates/sqi_XIPModeCode_Default.h"
#include "../templates/sqi_XIPControlWord2_Default.h"
#include "../templates/sqi_EnableControl_Default.h"
#include "../templates/sqi_CSOutputEnable_Default.h"
#include "../templates/sqi_DataOutputEnable_Default.h"
#include "../templates/sqi_SoftReset_Default.h"
#include "../templates/sqi_BurstControl_Default.h"
#include "../templates/sqi_HoldPinControl_Default.h"
#include "../templates/sqi_WPPinControl_Default.h"
#include "../templates/sqi_ReceiveLatch_Default.h"
#include "../templates/sqi_DataFormat_Default.h"
#include "../templates/sqi_DataModeControl_Default.h"
#include "../templates/sqi_TransferModeControl_Default.h"
#include "../templates/sqi_ConfigWord_Default.h"
#include "../templates/sqi_CSDeassert_Default.h"
#include "../templates/sqi_ChipSelect_Default.h"
#include "../templates/sqi_LaneMode_Default.h"
#include "../templates/sqi_TransferCommand_Default.h"
#include "../templates/sqi_TransferCount_Default.h"
#include "../templates/sqi_ControlWord_Default.h"
#include "../templates/sqi_ClockDivider_Default.h"
#include "../templates/sqi_ClockReady_Default.h"
#include "../templates/sqi_ClockControl_Default.h"
#include "../templates/sqi_RxBufThreshold_Default.h"
#include "../templates/sqi_TxBufThreshold_Default.h"
#include "../templates/sqi_RxBufIntThreshold_Default.h"
#include "../templates/sqi_TxBufIntThreshold_Default.h"
#include "../templates/sqi_InterruptControl_Default.h"
#include "../templates/sqi_InterruptStatus_Default.h"
#include "../templates/sqi_TxData_Default.h"
#include "../templates/sqi_RxData_Default.h"
#include "../templates/sqi_TxBufferFree_Default.h"
#include "../templates/sqi_RxBufferCount_Default.h"
#include "../templates/sqi_DataPinStatus_Default.h"
#include "../templates/sqi_RxUnderRun_Default.h"
#include "../templates/sqi_TxOverFlow_Default.h"
#include "../templates/sqi_DMAEnable_Default.h"
#include "../templates/sqi_BDPollingEnable_Default.h"
#include "../templates/sqi_StartDMA_Default.h"
#include "../templates/sqi_BDCurrentAddress_Default.h"
#include "../templates/sqi_BDBaseAddress_Default.h"
#include "../templates/sqi_BDProcessState_Default.h"
#include "../templates/sqi_DMAProcessInProgress_Default.h"
#include "../templates/sqi_DMAEngineBusy_Default.h"
#include "../templates/sqi_BDControlWord_Default.h"
#include "../templates/sqi_BDPollCount_Default.h"
#include "../templates/sqi_BDTxState_Default.h"
#include "../templates/sqi_BDTxBufCount_Default.h"
#include "../templates/sqi_BDTxLength_Default.h"
#include "../templates/sqi_BDRxState_Default.h"
#include "../templates/sqi_BDRxBufCount_Default.h"
#include "../templates/sqi_BDRxLength_Default.h"
#include "../templates/sqi_ConBufThreshold_Default.h"
#include "../templates/sqi_InterruptSignalControl_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_SQI_XIPDummyBytesSet(SQI_MODULE_ID index, SQI_DUMMY_BYTES bytes)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPDummyBytesSet_Default(index, bytes);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_DUMMY_BYTES PLIB_SQI_XIPDummyBytesGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPDummyBytesGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_DUMMY_BYTES)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPNumberOfDummyBytes(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPNumberOfDummyBytes_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPAddressBytesSet(SQI_MODULE_ID index, SQI_ADDR_BYTES bytes)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPAddressBytesSet_Default(index, bytes);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_ADDR_BYTES PLIB_SQI_XIPAddressBytesGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPAddressBytesGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_ADDR_BYTES)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPNumberOfAddressBytes(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPNumberOfAddressBytes_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPReadOpcodeSet(SQI_MODULE_ID index, uint8_t opCode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPReadOpcodeSet_Default(index, opCode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_XIPReadOpcodeGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPReadOpcodeGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPReadOpCode(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPReadOpCode_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPLaneModeSet(SQI_MODULE_ID index, SQI_LANE_MODE dataLanes, SQI_LANE_MODE dummyLanes, SQI_LANE_MODE modeLanes, SQI_LANE_MODE addrLanes, SQI_LANE_MODE cmdLanes)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPLaneModeSet_Default(index, dataLanes, dummyLanes, modeLanes, addrLanes, cmdLanes);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPLaneMode(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPLaneMode_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPControlWord1Set(SQI_MODULE_ID index, SQI_DUMMY_BYTES dummyBytes, SQI_ADDR_BYTES addressBytes, uint8_t readOpcode, SQI_LANE_MODE dataLaneMode, SQI_LANE_MODE dummyLaneMode, SQI_LANE_MODE modeCodeLaneMode, SQI_LANE_MODE addressLaneMode, SQI_LANE_MODE cmdLaneMode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPControlWord1Set_Default(index, dummyBytes, addressBytes, readOpcode, dataLaneMode, dummyLaneMode, modeCodeLaneMode, addressLaneMode, cmdLaneMode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SQI_XIPControlWord1Get(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPControlWord1Get_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPControlWord1(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPControlWord1_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPChipSelectSet(SQI_MODULE_ID index, SQI_CS_NUM csNum)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPChipSelectSet_Default(index, csNum);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_CS_NUM PLIB_SQI_XIPChipSelectGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPChipSelectGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_CS_NUM)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPChipSelect(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPChipSelect_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPModeBytesSet(SQI_MODULE_ID index, SQI_MODE_BYTES bytes)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPModeBytesSet_Default(index, bytes);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_MODE_BYTES PLIB_SQI_XIPModeBytesGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPModeBytesGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_MODE_BYTES)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPModeBytes(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPModeBytes_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPModeCodeSet(SQI_MODULE_ID index, uint8_t code)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPModeCodeSet_Default(index, code);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_XIPModeCodeGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPModeCodeGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPModeCode(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPModeCode_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_XIPControlWord2Set(SQI_MODULE_ID index, SQI_CS_NUM devSelect, SQI_MODE_BYTES modeBytes, uint8_t modeCode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_XIPControlWord2Set_Default(index, devSelect, modeBytes, modeCode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SQI_XIPControlWord2Get(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_XIPControlWord2Get_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsXIPControlWord2(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsXIPControlWord2_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_Enable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_Enable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_Disable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_Disable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsEnableControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsEnableControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_CSOutputEnableSelect(SQI_MODULE_ID index, SQI_CS_OEN csPins)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_CSOutputEnableSelect_Default(index, csPins);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsCSOutputEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsCSOutputEnable_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DataOutputEnableSelect(SQI_MODULE_ID index, SQI_DATA_OEN dataPins)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DataOutputEnableSelect_Default(index, dataPins);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsDataOutputEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDataOutputEnable_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_SoftReset(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_SoftReset_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsSoftReset(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsSoftReset_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_BurstEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_BurstEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsBurstControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBurstControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_HoldSet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_HoldSet_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_HoldClear(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_HoldClear_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_HoldGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_HoldGet_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsHoldPinControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsHoldPinControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_WriteProtectSet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_WriteProtectSet_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_WriteProtectClear(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_WriteProtectClear_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_WriteProtectGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_WriteProtectGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsWPPinControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsWPPinControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ReceiveLatchEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ReceiveLatchEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_ReceiveLatchDisable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ReceiveLatchDisable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ReceiveLatchGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ReceiveLatchGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsReceiveLatch(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsReceiveLatch_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DataFormatSet(SQI_MODULE_ID index, SQI_DATA_FORMAT dataformat)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DataFormatSet_Default(index, dataformat);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_DATA_FORMAT PLIB_SQI_DataFormatGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DataFormatGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_DATA_FORMAT)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsDataFormat(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDataFormat_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DataModeSet(SQI_MODULE_ID index, SQI_DATA_MODE mode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DataModeSet_Default(index, mode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsDataModeControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDataModeControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_TransferModeSet(SQI_MODULE_ID index, SQI_XFER_MODE mode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_TransferModeSet_Default(index, mode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_XFER_MODE PLIB_SQI_TransferModeGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TransferModeGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_XFER_MODE)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTransferModeControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTransferModeControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ConfigWordSet(SQI_MODULE_ID index, bool sqiEnable, SQI_CS_OEN csPins, SQI_DATA_OEN dataPins, bool reset, bool burstEn, bool hold, bool writeProtect, bool rxLatch, SQI_DATA_FORMAT lsbf, SQI_DATA_MODE dataMode, SQI_XFER_MODE xferMode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ConfigWordSet_Default(index, sqiEnable, csPins, dataPins, reset, burstEn, hold, writeProtect, rxLatch, lsbf, dataMode, xferMode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SQI_ConfigWordGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ConfigWordGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsConfigWord(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsConfigWord_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ChipSelectDeassertEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ChipSelectDeassertEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_ChipSelectDeassertDisable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ChipSelectDeassertDisable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsCSDeassert(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsCSDeassert_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ChipSelectSet(SQI_MODULE_ID index, SQI_CS_NUM csNum)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ChipSelectSet_Default(index, csNum);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_CS_NUM PLIB_SQI_ChipSelectGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ChipSelectGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_CS_NUM)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsChipSelect(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsChipSelect_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_LaneModeSet(SQI_MODULE_ID index, SQI_LANE_MODE mode)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_LaneModeSet_Default(index, mode);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_LANE_MODE PLIB_SQI_LaneModeGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_LaneModeGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_LANE_MODE)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsLaneMode(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsLaneMode_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_TransferDirectionSet(SQI_MODULE_ID index, SQI_XFER_CMD command)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_TransferDirectionSet_Default(index, command);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API SQI_XFER_CMD PLIB_SQI_TransferDirectionGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TransferDirectionGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_XFER_CMD)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTransferCommand(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTransferCommand_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ByteCountSet(SQI_MODULE_ID index, uint16_t xferCount)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ByteCountSet_Default(index, xferCount);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint16_t PLIB_SQI_ByteCountGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ByteCountGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTransferCount(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTransferCount_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ControlWordSet(SQI_MODULE_ID index, bool csDeassert, SQI_CS_NUM csNum, SQI_LANE_MODE laneMode, SQI_XFER_CMD command, uint16_t xferCount)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ControlWordSet_Default(index, csDeassert, csNum, laneMode, command, xferCount);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_SQI_ControlWordGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ControlWordGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsControlWord(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsControlWord_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ClockDividerSet(SQI_MODULE_ID index, SQI_CLK_DIV clkDivider)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ClockDividerSet_Default(index, clkDivider);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsClockDivider(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsClockDivider_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ClockIsStable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ClockIsStable_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsClockReady(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsClockReady_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ClockEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ClockEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_ClockDisable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ClockDisable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsClockControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsClockControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_RxBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_RxBufferThresholdSet_Default(index, threshold);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_RxBufferThresholdGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_RxBufferThresholdGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsRxBufThreshold(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsRxBufThreshold_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_TxBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_TxBufferThresholdSet_Default(index, threshold);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_TxBufferThresholdGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TxBufferThresholdGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTxBufThreshold(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTxBufThreshold_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_RxBufferThresholdIntSet(SQI_MODULE_ID index, uint8_t threshold)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_RxBufferThresholdIntSet_Default(index, threshold);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_RxBufferThresholdIntGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_RxBufferThresholdIntGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsRxBufIntThreshold(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsRxBufIntThreshold_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_TxBufferThresholdIntSet(SQI_MODULE_ID index, uint8_t threshold)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_TxBufferThresholdIntSet_Default(index, threshold);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_TxBufferThresholdIntGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TxBufferThresholdIntGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTxBufIntThreshold(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTxBufIntThreshold_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_InterruptEnable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_InterruptEnable_Default(index, interruptFlag);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_InterruptDisable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_InterruptDisable_Default(index, interruptFlag);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_InterruptIsEnabled(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_InterruptIsEnabled_Default(index, interruptFlag);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsInterruptControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsInterruptControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_InterruptFlagGet(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_InterruptFlagGet_Default(index, interruptFlag);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsInterruptStatus(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsInterruptStatus_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_TransmitData(SQI_MODULE_ID index, uint32_t data)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_TransmitData_Default(index, data);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsTxData(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTxData_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint32_t PLIB_SQI_ReceiveData(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ReceiveData_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsRxData(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsRxData_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_TransmitBufferFreeSpaceGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TransmitBufferFreeSpaceGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTxBufferFree(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTxBufferFree_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_NumberOfReceiveBufferReads(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_NumberOfReceiveBufferReads_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsRxBufferCount(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsRxBufferCount_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_DataLineStatus(SQI_MODULE_ID index, bool dataPin)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DataLineStatus_Default(index, dataPin);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsDataPinStatus(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDataPinStatus_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ReceiveBufferIsUnderrun(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ReceiveBufferIsUnderrun_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsRxUnderRun(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsRxUnderRun_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_TransmitBufferHasOverflowed(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_TransmitBufferHasOverflowed_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsTxOverFlow(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsTxOverFlow_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DMAEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMAEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_DMADisable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMADisable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_DMAIsEnabled(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMAIsEnabled_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsDmaEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDmaEnable_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DMABDPollEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMABDPollEnable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_DMABDPollDisable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMABDPollDisable_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_DMABDPollIsEnabled(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDPollIsEnabled_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDPollingEnable(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDPollingEnable_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DMABDFetchStart(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMABDFetchStart_Default(index);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsStartDMA(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsStartDMA_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void* PLIB_SQI_DMABDCurrentAddressGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDCurrentAddressGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (void*)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDCurrentAddress(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDCurrentAddress_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DMABDBaseAddressSet(SQI_MODULE_ID index, void* baseBDAddress)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMABDBaseAddressSet_Default(index, baseBDAddress);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void* PLIB_SQI_DMABDBaseAddressGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDBaseAddressGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (void*)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDBaseAddress(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDBaseAddress_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API SQI_BD_STATE PLIB_SQI_DMABDStateGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDStateGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_BD_STATE)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDProcessState(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDProcessState_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_DMAHasStarted(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMAHasStarted_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsDMAProcessInProgress(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDMAProcessInProgress_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_DMABDIsBusy(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDIsBusy_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsDMAEngineBusy(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsDMAEngineBusy_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint16_t PLIB_SQI_DMABDControlWordGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDControlWordGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint16_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDControlWord(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDControlWord_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_DMABDPollCounterSet(SQI_MODULE_ID index, uint16_t pollCount)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_DMABDPollCounterSet_Default(index, pollCount);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDPollCount(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDPollCount_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API SQI_BD_STATE PLIB_SQI_DMABDTransmitStateGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDTransmitStateGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_BD_STATE)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDTxState(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDTxState_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_DMABDTransmitBufferCountGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDTransmitBufferCountGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDTxBufCount(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDTxBufCount_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_DMABDTransmitBufferLengthGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDTransmitBufferLengthGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDTxLength(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDTxLength_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API SQI_BD_STATE PLIB_SQI_DMABDReceiveStateGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDReceiveStateGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (SQI_BD_STATE)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDRxState(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDRxState_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_DMABDReceiveBufferCountGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDReceiveBufferCountGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDRxBufCount(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDRxBufCount_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API uint8_t PLIB_SQI_DMABDReceiveBufferLengthGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_DMABDReceiveBufferLengthGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsBDRxLength(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsBDRxLength_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_ControlBufferThresholdSet(SQI_MODULE_ID index, uint8_t threshold)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_ControlBufferThresholdSet_Default(index, threshold);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint8_t PLIB_SQI_ControlBufferThresholdGet(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ControlBufferThresholdGet_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (uint8_t)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsConBufThreshold(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsConBufThreshold_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_SQI_InterruptSignalEnable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_InterruptSignalEnable_Default(index, interruptFlag);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_SQI_InterruptSignalDisable(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            SQI_InterruptSignalDisable_Default(index, interruptFlag);
            break;
        case SQI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_SQI_InterruptSignalIsEnabled(SQI_MODULE_ID index, SQI_INTERRUPTS interruptFlag)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_InterruptSignalIsEnabled_Default(index, interruptFlag);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_SQI_ExistsInterruptSignalControl(SQI_MODULE_ID index)
{
    switch (index) {
        case SQI_ID_0 :
            return SQI_ExistsInterruptSignalControl_Default(index);
        case SQI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
