/* Created by plibgen $Revision: 1.29 $ */

#ifndef _POWER_P32MZ1024ECG064_H
#define _POWER_P32MZ1024ECG064_H

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

    POWER_ID_0 = 0,
    POWER_NUMBER_OF_MODULES

} POWER_MODULE_ID;

typedef enum {

    POWER_MODULE_ADC1 = 0x00,
    POWER_MODULE_CVR = 0x0C,
    POWER_MODULE_CMP1 = 0x20,
    POWER_MODULE_CMP2 = 0x21,
    POWER_MODULE_IC1 = 0x40,
    POWER_MODULE_IC2 = 0x41,
    POWER_MODULE_IC3 = 0x42,
    POWER_MODULE_IC4 = 0x43,
    POWER_MODULE_IC5 = 0x44,
    POWER_MODULE_IC6 = 0x45,
    POWER_MODULE_IC7 = 0x46,
    POWER_MODULE_IC8 = 0x47,
    POWER_MODULE_IC9 = 0x48,
    POWER_MODULE_OC1 = 0x50,
    POWER_MODULE_OC2 = 0x51,
    POWER_MODULE_OC3 = 0x52,
    POWER_MODULE_OC4 = 0x53,
    POWER_MODULE_OC5 = 0x54,
    POWER_MODULE_OC6 = 0x55,
    POWER_MODULE_OC7 = 0x56,
    POWER_MODULE_OC8 = 0x57,
    POWER_MODULE_OC9 = 0x58,
    POWER_MODULE_TMR1 = 0x60,
    POWER_MODULE_TMR2 = 0x61,
    POWER_MODULE_TMR3 = 0x62,
    POWER_MODULE_TMR4 = 0x63,
    POWER_MODULE_TMR5 = 0x64,
    POWER_MODULE_TMR6 = 0x65,
    POWER_MODULE_TMR7 = 0x66,
    POWER_MODULE_TMR8 = 0x67,
    POWER_MODULE_TMR9 = 0x68,
    POWER_MODULE_UART1 = 0x80,
    POWER_MODULE_UART2 = 0x81,
    POWER_MODULE_UART3 = 0x82,
    POWER_MODULE_UART4 = 0x83,
    POWER_MODULE_UART5 = 0x84,
    POWER_MODULE_UART6 = 0x85,
    POWER_MODULE_SPI1 = 0x88,
    POWER_MODULE_SPI2 = 0x89,
    POWER_MODULE_SPI3 = 0x8A,
    POWER_MODULE_SPI4 = 0x8B,
    POWER_MODULE_I2C1 = 0x90,
    POWER_MODULE_I2C3 = 0x92,
    POWER_MODULE_I2C4 = 0x93,
    POWER_MODULE_I2C5 = 0x94,
    POWER_MODULE_USB = 0x98,
    POWER_MODULE_RTCC = 0xA0,
    POWER_MODULE_REF_CLK_OUTPUT1 = 0xA8,
    POWER_MODULE_REF_CLK_OUTPUT2 = 0xA9,
    POWER_MODULE_REF_CLK_OUTPUT3 = 0xAA,
    POWER_MODULE_REF_CLK_OUTPUT4 = 0xAB,
    POWER_MODULE_PMP = 0xB0,
    POWER_MODULE_SQI1 = 0xB6,
    POWER_MODULE_ETHERNET = 0xBB,
    POWER_MODULE_DMA = 0xC4,
    POWER_MODULE_RANDOM_NUM_GENERATOR = 0xD4

} POWER_MODULE;

INLINE SFR_TYPE* _POWER_SLEEP_STATUS_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IDLE_STATUS_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ENABLE_BCFGERR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ENABLE_BCFGFAIL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ENABLE_CMR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_POSTSCALAR_EXTR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ENABLE_SWR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER_DMTO_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER_WDTO_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER_BOR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_POSTSCALAR_POR_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &RCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_VOLTAGE_REGULATOR_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PWRCON;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ADC1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD1;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_CVR_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD1;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_CMP1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD2;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_CMP2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD2;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC5_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC6_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC7_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC8_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_IC9_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC5_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC6_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC7_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC8_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_OC9_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD3;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER5_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER6_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER7_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER8_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_TIMER9_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD4;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART5_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_UART6_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_SPI1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_SPI2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_SPI3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_SPI4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_I2C1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_I2C3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_I2C4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_I2C5_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_USB_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD5;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_RTCC_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_REF_CLK_OUTPUT1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_REF_CLK_OUTPUT2_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_REF_CLK_OUTPUT3_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_REF_CLK_OUTPUT4_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_PMP_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_SQI1_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_ETHERNET_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD6;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_DMA_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD7;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _POWER_RANDOM_NUM_GENERATOR_CONTROL_VREG(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return &PMD7;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _POWER_SLEEP_STATUS_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SLEEP_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IDLE_STATUS_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_IDLE_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGERR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGERR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGFAIL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGFAIL_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_CMR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_CMR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_EXTR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_EXTR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_SWR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SWR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_DMTO_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_DMTO_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_WDTO_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_WDTO_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_BOR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BOR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_POR_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_POR_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_VOLTAGE_REGULATOR_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PWRCON_VREGS_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ADC1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_AD1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CVR_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_CVRMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC5_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC5MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC6_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC6MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC7_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC7MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC8_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC8MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC9_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC9MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC5_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC5MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC6_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC6MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC7_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC7MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC8_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC8MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC9_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC9MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER5_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T5MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER6_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T6MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER7_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T7MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER8_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T8MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER9_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T9MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART5_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U5MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART6_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U6MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C5_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C5MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_USB_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_USBMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RTCC_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_RTCCMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT2_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO2MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT3_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO3MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT4_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO4MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_PMP_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_PMPMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SQI1_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_SQI1MD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ETHERNET_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_ETHMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_DMA_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_DMAMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RANDOM_NUM_GENERATOR_CONTROL_MASK(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_RNGMD_MASK;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SLEEP_STATUS_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SLEEP_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IDLE_STATUS_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_IDLE_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGERR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGERR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGFAIL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGFAIL_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_CMR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_CMR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_EXTR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_EXTR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_SWR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SWR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_DMTO_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_DMTO_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_WDTO_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_WDTO_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_BOR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BOR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_POR_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_POR_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_VOLTAGE_REGULATOR_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PWRCON_VREGS_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ADC1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_AD1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CVR_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_CVRMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC5_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC5MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC6_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC6MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC7_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC7MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC8_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC8MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC9_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC9MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC5_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC5MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC6_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC6MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC7_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC7MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC8_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC8MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC9_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC9MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER5_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T5MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER6_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T6MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER7_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T7MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER8_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T8MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER9_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T9MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART5_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U5MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART6_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U6MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C5_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C5MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_USB_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_USBMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RTCC_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_RTCCMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT2_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO2MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT3_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO3MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT4_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO4MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_PMP_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_PMPMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SQI1_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_SQI1MD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ETHERNET_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_ETHMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_DMA_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_DMAMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RANDOM_NUM_GENERATOR_CONTROL_POS(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_RNGMD_POSITION;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SLEEP_STATUS_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SLEEP_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IDLE_STATUS_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_IDLE_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGERR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGERR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_BCFGFAIL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BCFGFAIL_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_CMR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_CMR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_EXTR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_EXTR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ENABLE_SWR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_SWR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_DMTO_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_DMTO_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_WDTO_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_WDTO_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER_BOR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_BOR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_POSTSCALAR_POR_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _RCON_POR_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_VOLTAGE_REGULATOR_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PWRCON_VREGS_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ADC1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_AD1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CVR_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD1_CVRMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_CMP2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD2_CMP2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC5_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC5MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC6_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC6MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC7_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC7MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC8_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC8MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_IC9_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_IC9MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC5_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC5MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC6_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC6MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC7_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC7MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC8_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC8MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_OC9_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD3_OC9MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER5_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T5MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER6_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T6MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER7_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T7MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER8_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T8MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_TIMER9_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD4_T9MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART5_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U5MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_UART6_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_U6MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SPI4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_SPI4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_I2C5_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_I2C5MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_USB_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD5_USBMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RTCC_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_RTCCMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT2_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO2MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT3_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO3MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_REF_CLK_OUTPUT4_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_REFO4MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_PMP_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_PMPMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_SQI1_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_SQI1MD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_ETHERNET_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD6_ETHMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_DMA_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_DMAMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _POWER_RANDOM_NUM_GENERATOR_CONTROL_LEN(POWER_MODULE_ID i)
{
    switch (i) {
        case POWER_ID_0 :
            return _PMD7_RNGMD_LENGTH;
        case POWER_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/power_PeripheralModuleControl_PIC32_2.h"
#include "../templates/power_VoltageRegulatorControl_Default.h"
#include "../templates/power_SleepStatus_Default.h"
#include "../templates/power_IdleStatus_Default.h"
#include "../templates/power_DeepSleepModeControl_Unsupported.h"
#include "../templates/power_DeepSleepBORControl_Unsupported.h"
#include "../templates/power_DeepSleepIOCStatus_Unsupported.h"
#include "../templates/power_DeepSleepFaultDetectStatus_Unsupported.h"
#include "../templates/power_DeepSleepMCLRStatus_Unsupported.h"
#include "../templates/power_DeepSleepPORStatus_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_POWER_ExistsPeripheralModuleControl(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsPeripheralModuleControl_PIC32_2(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_POWER_PeripheralModuleDisable(POWER_MODULE_ID index, POWER_MODULE source)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_PeripheralModuleDisable_PIC32_2(index, source);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_POWER_PeripheralModuleEnable(POWER_MODULE_ID index, POWER_MODULE source)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_PeripheralModuleEnable_PIC32_2(index, source);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_POWER_PeripheralModuleIsEnabled(POWER_MODULE_ID index, POWER_MODULE source)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_PeripheralModuleIsEnabled_PIC32_2(index, source);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_POWER_ExistsVoltageRegulatorControl(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsVoltageRegulatorControl_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_POWER_VoltageRegulatorEnable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_VoltageRegulatorEnable_Default(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_POWER_VoltageRegulatorDisable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_VoltageRegulatorDisable_Default(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_POWER_VoltageRegulatorIsEnabled(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_VoltageRegulatorIsEnabled_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_POWER_ExistsSleepStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsSleepStatus_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_POWER_DeviceWasInSleepMode(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeviceWasInSleepMode_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_POWER_ClearSleepStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_ClearSleepStatus_Default(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_POWER_ExistsIdleStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsIdleStatus_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_POWER_DeviceWasInIdleMode(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeviceWasInIdleMode_Default(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_POWER_ClearIdleStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_ClearIdleStatus_Default(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepMode(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepMode_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeEnable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_DeepSleepModeEnable_Unsupported(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepModeDisable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_DeepSleepModeDisable_Unsupported(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepBOR(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepBOR_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepBOREnable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_DeepSleepBOREnable_Unsupported(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepBORDisable(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            POWER_DeepSleepBORDisable_Unsupported(index);
            break;
        case POWER_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepInterruptOnChange(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepInterruptOnChange_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepInterruptOnChangeStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeepSleepInterruptOnChangeStatus_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepFaultDetect(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepFaultDetect_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepFaultDetectStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeepSleepFaultDetectStatus_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepMCLREvent(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepMCLREvent_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepMCLREventStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeepSleepMCLREventStatus_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_ExistsDeepSleepPowerOnReset(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_ExistsDeepSleepPowerOnReset_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_POWER_DeepSleepPowerOnResetStatus(POWER_MODULE_ID index)
{
    switch (index) {
        case POWER_ID_0 :
            return POWER_DeepSleepPowerOnResetStatus_Unsupported(index);
        case POWER_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
