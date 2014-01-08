/* Created by plibgen $Revision: 1.29 $ */

#ifndef _EBI_P32MZ2048ECG144_H
#define _EBI_P32MZ2048ECG144_H

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

    EBI_ID_0 = 0,
    EBI_NUMBER_OF_MODULES

} EBI_MODULE_ID;

typedef enum {

    CS_TIMING_0 = 0x00,
    CS_TIMING_1 = 0x01,
    CS_TIMING_2 = 0x02

} EBI_CS_TIMING;

typedef enum {

    SRAM = 0x01,
    NORFLASH = 0x02

} EBI_MEMORY_TYPE;

typedef enum {

    CSNOTUSED = 0x00,
    MEMORY_SIZE_64KB = 0x01,
    MEMORY_SIZE_128KB = 0x02,
    MEMORY_SIZE_256KB = 0x03,
    MEMORY_SIZE_512KB = 0x04,
    MEMORY_SIZE_1MB = 0x05,
    MEMORY_SIZE_2MB = 0x06,
    MEMORY_SIZE_4MB = 0x07,
    MEMORY_SIZE_8MB = 0x08,
    MEMORY_SIZE_16MB = 0x09

} EBI_MEMORY_SIZE;

typedef enum {

    PAGE_WORD4 = 0x00,
    PAGE_WORD8 = 0x01,
    PAGE_WORD16 = 0x02,
    PAGE_WORD32 = 0x03

} EBI_PAGE_SIZE;

typedef enum {

    MEMORY_WIDTH_8BIT = 0x04,
    MEMORY_WIDTH_16BIT = 0x00

} EBI_STATIC_MEMORY_WIDTH;

typedef enum {

    EBI_EBIADDR_PIN0 = 0x01,
    EBI_EBIADDR_PIN1 = 0x03,
    EBI_EBIADDR_PIN2 = 0x07,
    EBI_EBIADDR_PIN3 = 0x0F,
    EBI_EBIADDR_PIN4 = 0x1F,
    EBI_EBIADDR_PIN5 = 0x3F,
    EBI_EBIADDR_PIN6 = 0x7F,
    EBI_EBIADDR_PIN7 = 0xFF,
    EBI_EBIADDR_PIN8 = 0x1FF,
    EBI_EBIADDR_PIN9 = 0x3FF,
    EBI_EBIADDR_PIN10 = 0x7FF,
    EBI_EBIADDR_PIN11 = 0xFFF,
    EBI_EBIADDR_PIN12 = 0x1FFF,
    EBI_EBIADDR_PIN13 = 0x3FFF,
    EBI_EBIADDR_PIN14 = 0x7FFF,
    EBI_EBIADDR_PIN15 = 0xFFFF,
    EBI_EBIADDR_PIN16 = 0x1FFFF,
    EBI_EBIADDR_PIN17 = 0x3FFFF,
    EBI_EBIADDR_PIN18 = 0x7FFFF,
    EBI_EBIADDR_PIN19 = 0xFFFFF,
    EBI_EBIADDR_PIN20 = 0x1FFFF,
    EBI_EBIADDR_PIN21 = 0x3FFFFF,
    EBI_EBIADDR_PIN22 = 0x7FFFFF,
    EBI_EBIADDR_PIN23 = 0xFFFFFF,
    EBI_ADDR_PRESET8 = 0xFF,
    EBI_ADDR_PRESET12 = 0xFFF,
    EBI_ADDR_PRESET16 = 0xFFFF,
    EBI_ADDR_PRESET_ALL = 0xFFFFFF

} EBI_ADDRESS_PORT;

INLINE SFR_TYPE* _EBI_CSADDR0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBICS0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_CSADDR1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBICS1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_CSADDR2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBICS2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_CSADDR3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBICS3;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_REGSEL0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMTYPE0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMSIZE0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_REGSEL1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMTYPE1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMSIZE1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_REGSEL2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMTYPE2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMSIZE2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_REGSEL3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK3;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMTYPE3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK3;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_MEMSIZE3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIMSK3;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_RDYMODE0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGESIZE0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TPRC0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TBTA0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWP0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWR0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TAS0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TRC0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGEMODE0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT0;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_RDYMODE1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGESIZE1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TPRC1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TBTA1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWP1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWR1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TAS1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TRC1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGEMODE1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT1;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_RDYMODE2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGESIZE2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TPRC2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TBTA2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWP2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TWR2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TAS2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TRC2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_PAGEMODE2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMT2;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_TRPD_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBIFTRPD;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_SMDWIDTH0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMCON;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_SMDWIDTH1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMCON;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_SMDWIDTH2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMCON;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_SMRP_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &EBISMCON;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIPINEN_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIA;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIA0EN_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIA;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYINV3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYINV2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYINV1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYEN3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYEN2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYEN1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRDYLVL_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIRPEN_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIWEEN_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIOEEN_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIBSEN1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIBSEN0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBICSEN3_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBICSEN2_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBICSEN1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBICSEN0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIDEN1_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _EBI_EBIDEN0_VREG(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return &CFGEBIC;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS0_CSADDR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS1_CSADDR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS2_CSADDR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS3_CSADDR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_REGSEL_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMTYPE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMSIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_REGSEL_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMTYPE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMSIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_REGSEL_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMTYPE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMSIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_REGSEL_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMTYPE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMSIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_RDYMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGESIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TPRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TBTA_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWP_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TAS_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGEMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_RDYMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGESIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TPRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TBTA_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWP_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TAS_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGEMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_RDYMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGESIZE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TPRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TBTA_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWP_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWR_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TAS_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TRC_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGEMODE_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRPD_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIFTRPD_TRPD_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH0_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH2_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMRP_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMRP_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIPINEN_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIPINEN_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIA0EN_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIA0EN_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV3_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV2_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN3_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN2_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYLVL_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYLVL_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRPEN_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRPEN_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIWEEN_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIWEEN_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIOEEN_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIOEEN_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN0_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN3_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN3_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN2_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN2_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN0_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN1_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN1_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN0_MASK(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN0_MASK;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS0_CSADDR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS1_CSADDR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS2_CSADDR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS3_CSADDR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_REGSEL_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMTYPE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMSIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_REGSEL_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMTYPE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMSIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_REGSEL_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMTYPE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMSIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_REGSEL_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMTYPE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMSIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_RDYMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGESIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TPRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TBTA_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWP_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TAS_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGEMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_RDYMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGESIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TPRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TBTA_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWP_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TAS_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGEMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_RDYMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGESIZE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TPRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TBTA_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWP_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWR_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TAS_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TRC_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGEMODE_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRPD_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIFTRPD_TRPD_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH0_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH2_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMRP_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMRP_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIPINEN_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIPINEN_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIA0EN_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIA0EN_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV3_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV2_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN3_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN2_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYLVL_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYLVL_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRPEN_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRPEN_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIWEEN_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIWEEN_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIOEEN_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIOEEN_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN0_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN3_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN3_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN2_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN2_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN0_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN1_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN1_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN0_POS(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN0_POSITION;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS0_CSADDR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS1_CSADDR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS2_CSADDR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_CSADDR3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBICS3_CSADDR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_REGSEL_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMTYPE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK0_MEMSIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_REGSEL_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMTYPE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK1_MEMSIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_REGSEL_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMTYPE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK2_MEMSIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_REGSEL3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_REGSEL_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMTYPE3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMTYPE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_MEMSIZE3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIMSK3_MEMSIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_RDYMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGESIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TPRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TBTA_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWP_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TWR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TAS_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_TRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT0_PAGEMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_RDYMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGESIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TPRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TBTA_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWP_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TWR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TAS_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_TRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT1_PAGEMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_RDYMODE2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_RDYMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGESIZE2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGESIZE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TPRC2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TPRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TBTA2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TBTA_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWP2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWP_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TWR2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TWR_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TAS2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TAS_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRC2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_TRC_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_PAGEMODE2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMT2_PAGEMODE_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_TRPD_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBIFTRPD_TRPD_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH0_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMDWIDTH2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMDWIDTH2_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_SMRP_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _EBISMCON_SMRP_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIPINEN_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIPINEN_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIA0EN_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIA_EBIA0EN_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV3_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV2_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYINV1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYINV1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN3_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN2_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYEN1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYEN1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRDYLVL_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRDYLVL_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIRPEN_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIRPEN_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIWEEN_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIWEEN_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIOEEN_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIOEEN_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIBSEN0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIBSEN0_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN3_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN3_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN2_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN2_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBICSEN0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBICSEN0_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN1_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN1_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _EBI_EBIDEN0_LEN(EBI_MODULE_ID i)
{
    switch (i) {
        case EBI_ID_0 :
            return _CFGEBIC_EBIDEN0_LENGTH;
        case EBI_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/ebi_Base_Address_EBIP32_144pin.h"
#include "../templates/ebi_MemoryCharacteristics_EBIP32_144pin.h"
#include "../templates/ebi_MemoryTimingConfig_Default.h"
#include "../templates/ebi_ReadyMode_Default.h"
#include "../templates/ebi_MemoryPaging_Default.h"
#include "../templates/ebi_PageMode_Default.h"
#include "../templates/ebi_PageReadTime_Default.h"
#include "../templates/ebi_DataTurnAroundTime_Default.h"
#include "../templates/ebi_WritePulseWidth_Default.h"
#include "../templates/ebi_AddressHoldTime_Default.h"
#include "../templates/ebi_AddressSetupTime_Default.h"
#include "../templates/ebi_ReadCycleTime_Default.h"
#include "../templates/ebi_FlashTiming_Default.h"
#include "../templates/ebi_StaticMemoryWidthRegister_Default.h"
#include "../templates/ebi_FlashPowerDownMode_Default.h"
#include "../templates/ebi_ControlEnable_Default.h"
#include "../templates/ebi_AddressPinEnableBits_Default.h"
#include "../templates/ebi_ReadyPin3Config_Default.h"
#include "../templates/ebi_ReadyPin2Config_Default.h"
#include "../templates/ebi_ReadyPin1Config_Default.h"
#include "../templates/ebi_ReadyPinSens_Default.h"
#include "../templates/ebi_FlashResetPin_Default.h"
#include "../templates/ebi_WriteOutputControl_Default.h"
#include "../templates/ebi_ByteSelectPin_Default.h"
#include "../templates/ebi_ChipSelectEnable_EBIP32_144pin.h"
#include "../templates/ebi_DataEnable_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_EBI_BaseAddressSet(EBI_MODULE_ID index, int ChipSelectNumber, uint32_t BaseAddress)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_BaseAddressSet_EBIP32_144pin(index, ChipSelectNumber, BaseAddress);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t PLIB_EBI_BaseAddressGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_BaseAddressGet_EBIP32_144pin(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsBaseAddress(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsBaseAddress_EBIP32_144pin(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_MemoryCharacteristicsSet(EBI_MODULE_ID index, int ChipSelectNumber, EBI_MEMORY_TYPE MemoryType, EBI_MEMORY_SIZE MemorySize, EBI_CS_TIMING TimingReg)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_MemoryCharacteristicsSet_EBIP32_144pin(index, ChipSelectNumber, MemoryType, MemorySize, TimingReg);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsMemoryCharacteristics(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsMemoryCharacteristics_EBIP32_144pin(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_MemoryTimingConfigSet(EBI_MODULE_ID index, int CS_Timing_Reg, int PageReadTime, int DataTurnAroundTime, int WritePulseWidth, int AddressHoldTime, int AddressSetupTime, int ReadCycleTime)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_MemoryTimingConfigSet_Default(index, CS_Timing_Reg, PageReadTime, DataTurnAroundTime, WritePulseWidth, AddressHoldTime, AddressSetupTime, ReadCycleTime);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsMemoryTimingConfig(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsMemoryTimingConfig_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ReadyModeSet(EBI_MODULE_ID index, bool ReadyPin0, bool ReadyPin1, bool ReadyPin2)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ReadyModeSet_Default(index, ReadyPin0, ReadyPin1, ReadyPin2);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ReadyModeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ReadyModeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadyMode(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadyMode_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_MemoryPagingSet(EBI_MODULE_ID index, int ChipSelectNumber, bool PageMode, EBI_PAGE_SIZE MemoryPageSize)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_MemoryPagingSet_Default(index, ChipSelectNumber, PageMode, MemoryPageSize);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsMemoryPaging(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsMemoryPaging_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_PageModeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_PageModeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsPageMode(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsPageMode_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_PageReadCycleTimeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_PageReadCycleTimeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsPageReadTime(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsPageReadTime_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_DataTurnAroundTimeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_DataTurnAroundTimeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsDataTurnAroundTime(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsDataTurnAroundTime_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_WritePulseWidthGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_WritePulseWidthGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsWritePulseWidth(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsWritePulseWidth_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_AddressHoldTimeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_AddressHoldTimeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsAddressHoldTime(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsAddressHoldTime_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_AddressSetupTimeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_AddressSetupTimeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsAddressSetupTime(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsAddressSetupTime_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API int PLIB_EBI_ReadCycleTimeGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ReadCycleTimeGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadCycleTime(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadCycleTime_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_FlashTimingSet(EBI_MODULE_ID index, int FlashTiming)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_FlashTimingSet_Default(index, FlashTiming);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API int PLIB_EBI_FlashTimingGet(EBI_MODULE_ID index, int ChipSelectNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_FlashTimingGet_Default(index, ChipSelectNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (int)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsFlashTiming(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsFlashTiming_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_StaticMemoryWidthRegisterSet(EBI_MODULE_ID index, int RegstierNumber, EBI_STATIC_MEMORY_WIDTH StaticMemoryWidthRegister)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_StaticMemoryWidthRegisterSet_Default(index, RegstierNumber, StaticMemoryWidthRegister);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API EBI_STATIC_MEMORY_WIDTH PLIB_EBI_StaticMemoryWidthRegisterGet(EBI_MODULE_ID index, int RegstierNumber)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_StaticMemoryWidthRegisterGet_Default(index, RegstierNumber);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (EBI_STATIC_MEMORY_WIDTH)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsStaticMemoryWidthRegister(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsStaticMemoryWidthRegister_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_FlashPowerDownModeSet(EBI_MODULE_ID index, bool FlashPowerDownMode)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_FlashPowerDownModeSet_Default(index, FlashPowerDownMode);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_FlashPowerDownModeGet(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_FlashPowerDownModeGet_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsFlashPowerDownMode(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsFlashPowerDownMode_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ControlEnableSet(EBI_MODULE_ID index, bool EnableBit)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ControlEnableSet_Default(index, EnableBit);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ControlEnableGet(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ControlEnableGet_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsControlEnable(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsControlEnable_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_AddressPinEnableBitsSet(EBI_MODULE_ID index, EBI_ADDRESS_PORT AddressPort)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_AddressPinEnableBitsSet_Default(index, AddressPort);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsAddressPinEnableBits(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsAddressPinEnableBits_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ReadyPin3ConfigSet(EBI_MODULE_ID index, bool ReadyPin3Enable, bool ReadyPin3Invert)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ReadyPin3ConfigSet_Default(index, ReadyPin3Enable, ReadyPin3Invert);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadyPin3Config(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadyPin3Config_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ReadyPin2ConfigSet(EBI_MODULE_ID index, bool ReadyPin2Enable, bool ReadyPin2Invert)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ReadyPin2ConfigSet_Default(index, ReadyPin2Enable, ReadyPin2Invert);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadyPin2Config(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadyPin2Config_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ReadyPin1ConfigSet(EBI_MODULE_ID index, bool ReadyPin1Enable, bool ReadyPin1Invert)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ReadyPin1ConfigSet_Default(index, ReadyPin1Enable, ReadyPin1Invert);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadyPin1Config(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadyPin1Config_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ReadyPinSensSet(EBI_MODULE_ID index, bool SensitivityControl)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ReadyPinSensSet_Default(index, SensitivityControl);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsReadyPinSens(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsReadyPinSens_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_FlashResetPinSet(EBI_MODULE_ID index, bool FlashResetPin)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_FlashResetPinSet_Default(index, FlashResetPin);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_FlashResetPinGet(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_FlashResetPinGet_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_EBI_ExistsFlashResetPin(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsFlashResetPin_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_WriteOutputControlSet(EBI_MODULE_ID index, bool WriteEnable, bool OutputEnable)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_WriteOutputControlSet_Default(index, WriteEnable, OutputEnable);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsWriteOutputControl(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsWriteOutputControl_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ByteSelectPinSet(EBI_MODULE_ID index, bool ByteSelect0, bool ByteSelect1)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ByteSelectPinSet_Default(index, ByteSelect0, ByteSelect1);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsByteSelectPin(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsByteSelectPin_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_ChipSelectEnableSet(EBI_MODULE_ID index, bool ChipSelect0, bool ChipSelect1, bool ChipSelect2, bool ChipSelect3)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_ChipSelectEnableSet_EBIP32_144pin(index, ChipSelect0, ChipSelect1, ChipSelect2, ChipSelect3);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsChipSelectEnable(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsChipSelectEnable_EBIP32_144pin(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_EBI_DataEnableSet(EBI_MODULE_ID index, bool DataUpperByte, bool DataLowerByte)
{
    switch (index) {
        case EBI_ID_0 :
            EBI_DataEnableSet_Default(index, DataUpperByte, DataLowerByte);
            break;
        case EBI_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_EBI_ExistsDataEnable(EBI_MODULE_ID index)
{
    switch (index) {
        case EBI_ID_0 :
            return EBI_ExistsDataEnable_Default(index);
        case EBI_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
