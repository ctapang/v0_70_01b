/* Created by plibgen $Revision: 1.29 $ */

#ifndef _PORTS_P32MX230F064B_H
#define _PORTS_P32MX230F064B_H

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

    PORTS_ID_0 = 0,
    PORTS_NUMBER_OF_MODULES

} PORTS_MODULE_ID;

typedef enum {

    PORTS_PIN_MODE_ANALOG = 0,
    PORTS_PIN_MODE_DIGITAL = 1

} PORTS_PIN_MODE;

typedef enum {

    PORTS_CHANGE_NOTICE_PIN_NONE

} PORTS_CHANGE_NOTICE_PIN;

typedef enum {

    PORTS_ANALOG_PIN_NONE

} PORTS_ANALOG_PIN;

typedef enum {

    PORTS_BIT_POS_0 = 0,
    PORTS_BIT_POS_1 = 1,
    PORTS_BIT_POS_2 = 2,
    PORTS_BIT_POS_3 = 3,
    PORTS_BIT_POS_4 = 4,
    PORTS_BIT_POS_5 = 5,
    PORTS_BIT_POS_6 = 6,
    PORTS_BIT_POS_7 = 7,
    PORTS_BIT_POS_8 = 8,
    PORTS_BIT_POS_9 = 9,
    PORTS_BIT_POS_10 = 10,
    PORTS_BIT_POS_11 = 11,
    PORTS_BIT_POS_12 = 12,
    PORTS_BIT_POS_13 = 13,
    PORTS_BIT_POS_14 = 14,
    PORTS_BIT_POS_15 = 15

} PORTS_BIT_POS;

typedef enum {

    INPUT_FUNC_INT1 = 0,
    INPUT_FUNC_INT2 = 1,
    INPUT_FUNC_INT3 = 2,
    INPUT_FUNC_INT4 = 3,
    INPUT_FUNC_T2CK = 5,
    INPUT_FUNC_T3CK = 6,
    INPUT_FUNC_T4CK = 7,
    INPUT_FUNC_T5CK = 8,
    INPUT_FUNC_IC1 = 9,
    INPUT_FUNC_IC2 = 10,
    INPUT_FUNC_IC3 = 11,
    INPUT_FUNC_IC4 = 12,
    INPUT_FUNC_IC5 = 13,
    INPUT_FUNC_OCFA = 17,
    INPUT_FUNC_OCFB = 18,
    INPUT_FUNC_U1RX = 19,
    INPUT_FUNC_U1CTS = 20,
    INPUT_FUNC_U2RX = 21,
    INPUT_FUNC_U2CTS = 22,
    INPUT_FUNC_SDI1 = 32,
    INPUT_FUNC_SS1 = 33,
    INPUT_FUNC_SDI2 = 35,
    INPUT_FUNC_SS2 = 36,
    INPUT_FUNC_REFCLKI1 = 45

} PORTS_REMAP_INPUT_FUNCTION;

typedef enum {

    INPUT_PIN_RPB9 = 0x04,
    INPUT_PIN_RPB10 = 0x03,
    INPUT_PIN_RPB5 = 0x01,
    INPUT_PIN_RPC1 = 0x06,
    INPUT_PIN_RPB1 = 0x02,
    INPUT_PIN_RPB3 = 0x01,
    INPUT_PIN_RPC4 = 0x07,
    INPUT_PIN_RPB8 = 0x04,
    INPUT_PIN_RPB15 = 0x03,
    INPUT_PIN_RPB0 = 0x02,
    INPUT_PIN_RPB7 = 0x04,
    INPUT_PIN_RPC3 = 0x07,
    INPUT_PIN_RPB14 = 0x01,
    INPUT_PIN_RPB6 = 0x01,
    INPUT_PIN_RPB2 = 0x04,
    INPUT_PIN_RPC2 = 0x06,
    INPUT_PIN_RPA0 = 0x00,
    INPUT_PIN_RPB4 = 0x02,
    INPUT_PIN_RPC7 = 0x05,
    INPUT_PIN_RPC0 = 0x06,
    INPUT_PIN_RPC5 = 0x07,
    INPUT_PIN_RPA1 = 0x00,
    INPUT_PIN_RPB11 = 0x03,
    INPUT_PIN_RPA8 = 0x05,
    INPUT_PIN_RPC8 = 0x06,
    INPUT_PIN_RPA9 = 0x07,
    INPUT_PIN_RPA2 = 0x00,
    INPUT_PIN_RPA4 = 0x02,
    INPUT_PIN_RPB13 = 0x03,
    INPUT_PIN_RPC6 = 0x05,
    INPUT_PIN_RPA3 = 0x00,
    INPUT_PIN_RPC9 = 0x05

} PORTS_REMAP_INPUT_PIN;

typedef enum {

    OTPUT_FUNC_SDO1 = 0x03,
    OTPUT_FUNC_SDO2 = 0x04,
    OTPUT_FUNC_OC3 = 0x05,
    OTPUT_FUNC_C2OUT = 0x07,
    OTPUT_FUNC_U1TX = 0x01,
    OTPUT_FUNC_U2RTS = 0x02,
    OTPUT_FUNC_OC4 = 0x05,
    OTPUT_FUNC_SS1 = 0x03,
    OTPUT_FUNC_OC5 = 0x06,
    OTPUT_FUNC_C1OUT = 0x07,
    OTPUT_FUNC_U1RTS = 0x01,
    OTPUT_FUNC_U2TX = 0x02,
    OTPUT_FUNC_SS2 = 0x04,
    OTPUT_FUNC_OC2 = 0x05,
    OTPUT_FUNC_OC1 = 0x05,
    OTPUT_FUNC_C3OUT = 0x07,
    OTPUT_FUNC_REFCLKO = 0x07,
    OTPUT_FUNC_NO_CONNECT = 0x00

} PORTS_REMAP_OUTPUT_FUNCTION;

typedef enum {

    OUTPUT_PIN_RPA0 = 0,
    OUTPUT_PIN_RPA1 = 1,
    OUTPUT_PIN_RPA2 = 2,
    OUTPUT_PIN_RPA3 = 3,
    OUTPUT_PIN_RPA4 = 4,
    OUTPUT_PIN_RPB0 = 11,
    OUTPUT_PIN_RPB1 = 12,
    OUTPUT_PIN_RPB2 = 13,
    OUTPUT_PIN_RPB3 = 14,
    OUTPUT_PIN_RPB4 = 15,
    OUTPUT_PIN_RPB5 = 16,
    OUTPUT_PIN_RPB7 = 18,
    OUTPUT_PIN_RPB8 = 19,
    OUTPUT_PIN_RPB9 = 20,
    OUTPUT_PIN_RPB10 = 21,
    OUTPUT_PIN_RPB11 = 22,
    OUTPUT_PIN_RPB13 = 24,
    OUTPUT_PIN_RPB14 = 25,
    OUTPUT_PIN_RPB15 = 26

} PORTS_REMAP_OUTPUT_PIN;

typedef enum {

    PORT_CHANNEL_A = 0x00,
    PORT_CHANNEL_B = 0x01

} PORTS_CHANNEL;

INLINE SFR_TYPE* _PORTS_READ_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &PORTA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_WRITE_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &LATA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_DIRECTION_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &TRISA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_OPEN_DRAIN_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &ODCA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_MODE_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &ANSELA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_PULL_UP_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNPUA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNENA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_PULL_DOWN_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNPDA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_STATUS_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNSTATA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_TURN_ON_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNCONA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_A_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNCONA;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_READ_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &PORTB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_WRITE_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &LATB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_DIRECTION_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &TRISB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_OPEN_DRAIN_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &ODCB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_MODE_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &ANSELB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_PULL_UP_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNPUB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNENB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_PULL_DOWN_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNPDB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_CHANGE_NOTICE_STATUS_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNSTATB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_TURN_ON_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNCONB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_B_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &CNCONB;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_INT1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &INT1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_INT2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &INT2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_INT3_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &INT3R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_INT4_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &INT4R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_T2CK_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &T2CKR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_T3CK_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &T3CKR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_T4CK_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &T4CKR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_T5CK_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &T5CKR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_IC1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &IC1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_IC2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &IC2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_IC3_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &IC3R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_IC4_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &IC4R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_IC5_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &IC5R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_OCFA_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &OCFAR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_OCFB_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &OCFBR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_U1RX_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &U1RXR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_U1CTS_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &U1CTSR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_U2RX_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &U2RXR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_U2CTS_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &U2CTSR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_SDI1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &SDI1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_SS1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &SS1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_SDI2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &SDI2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_SS2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &SS2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_FUNC_REFCLKI1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &REFCLKIR;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPA0_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPA0R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPA1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPA1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPA2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPA2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPA3_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPA3R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPA4_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPA4R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB0_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB0R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB1_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB1R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB2_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB2R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB3_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB3R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB4_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB4R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB5_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB5R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB7_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB7R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB8_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB8R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB9_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB9R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB10_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB10R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB11_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB11R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB13_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB13R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB14_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB14R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _PORTS_REMAP_PIN_RPB15_VREG(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return &RPB15R;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_ON_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_A_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_SIDL_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)-1;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_ON_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_B_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_SIDL_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT1R_INT1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT2R_INT2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT3_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT3R_INT3R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT4_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT4R_INT4R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T2CK_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T2CKR_T2CKR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T3CK_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T3CKR_T3CKR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T4CK_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T4CKR_T4CKR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T5CK_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T5CKR_T5CKR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC1R_IC1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC2R_IC2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC3_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC3R_IC3R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC4_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC4R_IC4R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC5_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC5R_IC5R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFA_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFAR_OCFAR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFB_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFBR_OCFBR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1RX_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1RXR_U1RXR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1CTS_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1CTSR_U1CTSR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2RX_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2RXR_U2RXR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2CTS_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2CTSR_U2CTSR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI1R_SDI1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS1R_SS1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI2R_SDI2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS2R_SS2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_REFCLKI1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _REFCLKIR_REFCLKIR_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA0_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA0R_RPA0R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA1R_RPA1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA2R_RPA2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA3_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA3R_RPA3R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA4_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA4R_RPA4R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB0_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB0R_RPB0R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB1_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB1R_RPB1R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB2_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB2R_RPB2R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB3_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB3R_RPB3R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB4_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB4R_RPB4R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB5_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB5R_RPB5R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB7_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB7R_RPB7R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB8_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB8R_RPB8R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB9_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB9R_RPB9R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB10_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB10R_RPB10R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB11_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB11R_RPB11R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB13_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB13R_RPB13R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB14_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB14R_RPB14R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB15_MASK(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB15R_RPB15R_MASK;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_ON_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_A_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_SIDL_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)0;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_ON_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_B_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_SIDL_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT1R_INT1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT2R_INT2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT3_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT3R_INT3R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT4_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT4R_INT4R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T2CK_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T2CKR_T2CKR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T3CK_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T3CKR_T3CKR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T4CK_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T4CKR_T4CKR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T5CK_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T5CKR_T5CKR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC1R_IC1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC2R_IC2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC3_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC3R_IC3R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC4_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC4R_IC4R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC5_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC5R_IC5R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFA_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFAR_OCFAR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFB_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFBR_OCFBR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1RX_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1RXR_U1RXR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1CTS_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1CTSR_U1CTSR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2RX_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2RXR_U2RXR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2CTS_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2CTSR_U2CTSR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI1R_SDI1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS1R_SS1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI2R_SDI2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS2R_SS2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_REFCLKI1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _REFCLKIR_REFCLKIR_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA0_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA0R_RPA0R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA1R_RPA1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA2R_RPA2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA3_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA3R_RPA3R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA4_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA4R_RPA4R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB0_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB0R_RPB0R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB1_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB1R_RPB1R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB2_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB2R_RPB2R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB3_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB3R_RPB3R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB4_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB4R_RPB4R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB5_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB5R_RPB5R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB7_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB7R_RPB7R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB8_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB8R_RPB8R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB9_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB9R_RPB9R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB10_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB10R_RPB10R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB11_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB11R_RPB11R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB13_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB13R_RPB13R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB14_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB14R_RPB14R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB15_POS(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB15R_RPB15R_POSITION;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_ON_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_A_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONA_SIDL_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_READ_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_WRITE_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_DIRECTION_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_OPEN_DRAIN_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_MODE_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_UP_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_PULL_DOWN_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_CHANGE_NOTICE_STATUS_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return (SFR_DATA)sizeof(SFR_DATA);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_TURN_ON_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_ON_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_PIN_CHANGE_NOTICE_IN_IDLE_B_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _CNCONB_SIDL_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT1R_INT1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT2R_INT2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT3_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT3R_INT3R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_INT4_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _INT4R_INT4R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T2CK_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T2CKR_T2CKR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T3CK_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T3CKR_T3CKR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T4CK_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T4CKR_T4CKR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_T5CK_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _T5CKR_T5CKR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC1R_IC1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC2R_IC2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC3_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC3R_IC3R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC4_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC4R_IC4R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_IC5_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _IC5R_IC5R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFA_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFAR_OCFAR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_OCFB_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _OCFBR_OCFBR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1RX_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1RXR_U1RXR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U1CTS_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U1CTSR_U1CTSR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2RX_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2RXR_U2RXR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_U2CTS_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _U2CTSR_U2CTSR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI1R_SDI1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS1R_SS1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SDI2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SDI2R_SDI2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_SS2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _SS2R_SS2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_FUNC_REFCLKI1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _REFCLKIR_REFCLKIR_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA0_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA0R_RPA0R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA1R_RPA1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA2R_RPA2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA3_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA3R_RPA3R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPA4_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPA4R_RPA4R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB0_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB0R_RPB0R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB1_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB1R_RPB1R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB2_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB2R_RPB2R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB3_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB3R_RPB3R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB4_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB4R_RPB4R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB5_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB5R_RPB5R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB7_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB7R_RPB7R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB8_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB8R_RPB8R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB9_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB9R_RPB9R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB10_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB10R_RPB10R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB11_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB11R_RPB11R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB13_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB13R_RPB13R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB14_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB14R_RPB14R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _PORTS_REMAP_PIN_RPB15_LEN(PORTS_MODULE_ID i)
{
    switch (i) {
        case PORTS_ID_0 :
            return _RPB15R_RPB15R_LENGTH;
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/ports_RemapInput_default.h"
#include "../templates/ports_RemapOutput_PIC32_2.h"
#include "../templates/ports_PinMode_Unsupported.h"
#include "../templates/ports_PortsRead_MCU32_PPS.h"
#include "../templates/ports_PortsWrite_MCU32_PPS.h"
#include "../templates/ports_PortsDirection_MCU32_PPS.h"
#include "../templates/ports_PortsOpenDrain_MCU32_PPS.h"
#include "../templates/ports_ChangeNotice_Unsupported.h"
#include "../templates/ports_PinChangeNotice_Unsupported.h"
#include "../templates/ports_ChangeNoticeInIdle_Unsupported.h"
#include "../templates/ports_ChangeNoticePullup_Unsupported.h"
#include "../templates/ports_PinModePerPort_Default.h"
#include "../templates/ports_ChangeNoticePullDownPerPort_Default.h"
#include "../templates/ports_ChangeNoticePullUpPerPort_Default.h"
#include "../templates/ports_PinChangeNoticePerPort_Default.h"
#include "../templates/ports_ChangeNoticePerPortTurnOn_Default.h"
#include "../templates/ports_ChangeNoticeInIdlePerPort_Default.h"
#include "../templates/ports_ChangeNoticePerPortStatus_Default.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API void PLIB_PORTS_RemapInput(PORTS_MODULE_ID index, PORTS_REMAP_INPUT_FUNCTION function, PORTS_REMAP_INPUT_PIN remapPin)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_RemapInput_default(index, function, remapPin);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsRemapInput(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsRemapInput_default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_RemapOutput(PORTS_MODULE_ID index, PORTS_REMAP_OUTPUT_FUNCTION function, PORTS_REMAP_OUTPUT_PIN remapPin)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_RemapOutput_PIC32_2(index, function, remapPin);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsRemapOutput(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsRemapOutput_PIC32_2(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_PinModeSelect(PORTS_MODULE_ID index, PORTS_ANALOG_PIN pin, PORTS_PIN_MODE mode)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinModeSelect_Unsupported(index, pin, mode);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PORTS_ExistsPinMode(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPinMode_Unsupported(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PORTS_PinGet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_PinGet_MCU32_PPS(index, channel, bitPos);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API PORTS_DATA_TYPE PLIB_PORTS_Read(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_Read_MCU32_PPS(index, channel);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (PORTS_DATA_TYPE)0;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPortsRead(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPortsRead_MCU32_PPS(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_PinWrite(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos, bool value)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinWrite_MCU32_PPS(index, channel, bitPos, value);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinSet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinSet_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinClear(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinClear_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinToggle(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinToggle_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_Write(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_TYPE value)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_Write_MCU32_PPS(index, channel, value);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_Set(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_TYPE value, PORTS_DATA_MASK mask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_Set_MCU32_PPS(index, channel, value, mask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_Toggle(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK toggleMask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_Toggle_MCU32_PPS(index, channel, toggleMask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_Clear(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK clearMask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_Clear_MCU32_PPS(index, channel, clearMask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPortsWrite(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPortsWrite_MCU32_PPS(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_PinDirectionInputSet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinDirectionInputSet_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinDirectionOutputSet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinDirectionOutputSet_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_DirectionInputSet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK mask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_DirectionInputSet_MCU32_PPS(index, channel, mask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_DirectionOutputSet(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK mask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_DirectionOutputSet_MCU32_PPS(index, channel, mask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API PORTS_DATA_MASK PLIB_PORTS_DirectionGet(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_DirectionGet_MCU32_PPS(index, channel);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (PORTS_DATA_MASK)0;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPortsDirection(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPortsDirection_MCU32_PPS(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_PinOpenDrainEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinOpenDrainEnable_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinOpenDrainDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinOpenDrainDisable_MCU32_PPS(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_OpenDrainEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK mask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_OpenDrainEnable_MCU32_PPS(index, channel, mask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_OpenDrainDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_DATA_MASK mask)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_OpenDrainDisable_MCU32_PPS(index, channel, mask);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPortsOpenDrain(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPortsOpenDrain_MCU32_PPS(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticeEnable(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeEnable_Unsupported(index);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticeDisable(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeDisable_Unsupported(index);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PORTS_ExistsChangeNotice(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNotice_Unsupported(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_PinChangeNoticeEnable(PORTS_MODULE_ID index, PORTS_CHANGE_NOTICE_PIN pinNum)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinChangeNoticeEnable_Unsupported(index, pinNum);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_PinChangeNoticeDisable(PORTS_MODULE_ID index, PORTS_CHANGE_NOTICE_PIN pinNum)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinChangeNoticeDisable_Unsupported(index, pinNum);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PORTS_ExistsPinChangeNotice(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPinChangeNotice_Unsupported(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticeInIdleEnable(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeInIdleEnable_Unsupported(index);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticeInIdleDisable(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeInIdleDisable_Unsupported(index);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PORTS_ExistsChangeNoticeInIdle(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticeInIdle_Unsupported(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_MODULE_ID index, PORTS_CHANGE_NOTICE_PIN pinNum)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullUpEnable_Unsupported(index, pinNum);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_PORTS_ChangeNoticePullUpDisable(PORTS_MODULE_ID index, PORTS_CHANGE_NOTICE_PIN pinNum)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullUpDisable_Unsupported(index, pinNum);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_PORTS_ExistsChangeNoticePullUp(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePullUp_Unsupported(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_PinModePerPortSelect(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos, PORTS_PIN_MODE mode)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinModePerPortSelect_Default(index, channel, bitPos, mode);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPinModePerPort(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPinModePerPort_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePullDownPerPortEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullDownPerPortEnable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePullDownPerPortDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullDownPerPortDisable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsChangeNoticePullDownPerPort(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePullDownPerPort_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullUpPerPortEnable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePullUpPerPortDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePullUpPerPortDisable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsChangeNoticePullUpPerPort(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePullUpPerPort_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_PinChangeNoticePerPortEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinChangeNoticePerPortEnable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_PinChangeNoticePerPortDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_PinChangeNoticePerPortDisable_Default(index, channel, bitPos);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsPinChangeNoticePerPort(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsPinChangeNoticePerPort_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePerPortTurnOn(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePerPortTurnOn_Default(index, channel);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticePerPortTurnOff(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticePerPortTurnOff_Default(index, channel);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsChangeNoticePerPortTurnOn(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePerPortTurnOn_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticeInIdlePerPortEnable(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeInIdlePerPortEnable_Default(index, channel);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_PORTS_ChangeNoticeInIdlePerPortDisable(PORTS_MODULE_ID index, PORTS_CHANNEL channel)
{
    switch (index) {
        case PORTS_ID_0 :
            PORTS_ChangeNoticeInIdlePerPortDisable_Default(index, channel);
            break;
        case PORTS_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_PORTS_ExistsChangeNoticePerPortInIdle(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePerPortInIdle_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PORTS_ChangeNoticePerPortHasOccured(PORTS_MODULE_ID index, PORTS_CHANNEL channel, PORTS_BIT_POS bitPos)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ChangeNoticePerPortHasOccured_Default(index, channel, bitPos);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_PORTS_ExistsChangeNoticePerPortStatus(PORTS_MODULE_ID index)
{
    switch (index) {
        case PORTS_ID_0 :
            return PORTS_ExistsChangeNoticePerPortStatus_Default(index);
        case PORTS_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

#endif
