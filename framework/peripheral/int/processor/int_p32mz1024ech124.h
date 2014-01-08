/* Created by plibgen $Revision: 1.28 $ */

#ifndef _INT_P32MZ1024ECH124_H
#define _INT_P32MZ1024ECH124_H

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

    INT_ID_0 = 0,
    INT_NUMBER_OF_MODULES

} INT_MODULE_ID;

typedef enum {

    INT_VECTOR_SPACING_0 = 0x00,
    INT_VECTOR_SPACING_8 = 0x01,
    INT_VECTOR_SPACING_16 = 0x10,
    INT_VECTOR_SPACING_32 = 0x20,
    INT_VECTOR_SPACING_64 = 0x40,
    INT_VECTOR_SPACING_128 = 0x80,
    INT_VECTOR_SPACING_256 = 0x100,
    INT_VECTOR_SPACING_512 = 0x200

} INT_VECTOR_SPACING;

typedef enum {

    INT_SHADOW_REGISTER_0 = 0x00,
    INT_SHADOW_REGISTER_1 = 0x01,
    INT_SHADOW_REGISTER_2 = 0x02,
    INT_SHADOW_REGISTER_3 = 0x03,
    INT_SHADOW_REGISTER_4 = 0x04,
    INT_SHADOW_REGISTER_5 = 0x05,
    INT_SHADOW_REGISTER_6 = 0x06,
    INT_SHADOW_REGISTER_7 = 0x07,
    INT_SHADOW_REGISTER_8 = 0x08,
    INT_SHADOW_REGISTER_9 = 0x09,
    INT_SHADOW_REGISTER_10 = 0x0A,
    INT_SHADOW_REGISTER_11 = 0x0B,
    INT_SHADOW_REGISTER_12 = 0x0C,
    INT_SHADOW_REGISTER_13 = 0x0D,
    INT_SHADOW_REGISTER_14 = 0x0E,
    INT_SHADOW_REGISTER_15 = 0x0F

} INT_SHADOW_REGISTER;

typedef enum {

    INT_VECTOR_0 = 0x00,
    INT_VECTOR_1 = 0x01,
    INT_VECTOR_2 = 0x02,
    INT_VECTOR_3 = 0x03,
    INT_VECTOR_4 = 0x04,
    INT_VECTOR_5 = 0x05,
    INT_VECTOR_6 = 0x06,
    INT_VECTOR_7 = 0x07,
    INT_VECTOR_8 = 0x08,
    INT_VECTOR_9 = 0x09,
    INT_VECTOR_10 = 0x0A,
    INT_VECTOR_11 = 0x0B,
    INT_VECTOR_12 = 0x0C,
    INT_VECTOR_13 = 0x0D,
    INT_VECTOR_14 = 0x0E,
    INT_VECTOR_15 = 0x0F,
    INT_VECTOR_16 = 0x10,
    INT_VECTOR_17 = 0x11,
    INT_VECTOR_18 = 0x12,
    INT_VECTOR_19 = 0x13,
    INT_VECTOR_20 = 0x14,
    INT_VECTOR_21 = 0x15,
    INT_VECTOR_22 = 0x16,
    INT_VECTOR_23 = 0x17,
    INT_VECTOR_24 = 0x18,
    INT_VECTOR_25 = 0x19,
    INT_VECTOR_26 = 0x1A,
    INT_VECTOR_27 = 0x1B,
    INT_VECTOR_28 = 0x1C,
    INT_VECTOR_29 = 0x1D,
    INT_VECTOR_30 = 0x1E,
    INT_VECTOR_31 = 0x1F,
    INT_VECTOR_32 = 0x20,
    INT_VECTOR_33 = 0x21,
    INT_VECTOR_34 = 0x22,
    INT_VECTOR_35 = 0x23,
    INT_VECTOR_36 = 0x24,
    INT_VECTOR_37 = 0x25,
    INT_VECTOR_38 = 0x26,
    INT_VECTOR_39 = 0x27,
    INT_VECTOR_40 = 0x28,
    INT_VECTOR_41 = 0x29,
    INT_VECTOR_42 = 0x2A,
    INT_VECTOR_43 = 0x2B,
    INT_VECTOR_44 = 0x2C,
    INT_VECTOR_45 = 0x2E,
    INT_VECTOR_46 = 0x2F,
    INT_VECTOR_47 = 0x30,
    INT_VECTOR_48 = 0x31,
    INT_VECTOR_49 = 0x32,
    INT_VECTOR_50 = 0x33,
    INT_VECTOR_51 = 0x34,
    INT_VECTOR_52 = 0x35,
    INT_VECTOR_53 = 0x36,
    INT_VECTOR_54 = 0x37,
    INT_VECTOR_55 = 0x38,
    INT_VECTOR_56 = 0x39,
    INT_VECTOR_57 = 0x3B,
    INT_VECTOR_58 = 0x3C,
    INT_VECTOR_59 = 0x3D,
    INT_VECTOR_60 = 0x3E,
    INT_VECTOR_61 = 0x3F,
    INT_VECTOR_62 = 0x40,
    INT_VECTOR_63 = 0x41,
    INT_VECTOR_64 = 0x42,
    INT_VECTOR_65 = 0x43,
    INT_VECTOR_66 = 0x44,
    INT_VECTOR_67 = 0x45,
    INT_VECTOR_68 = 0x46,
    INT_VECTOR_69 = 0x47,
    INT_VECTOR_70 = 0x48,
    INT_VECTOR_71 = 0x49,
    INT_VECTOR_72 = 0x4A,
    INT_VECTOR_73 = 0x4B,
    INT_VECTOR_74 = 0x4C,
    INT_VECTOR_75 = 0x4D,
    INT_VECTOR_76 = 0x4E,
    INT_VECTOR_77 = 0x4F,
    INT_VECTOR_78 = 0x50,
    INT_VECTOR_79 = 0x51,
    INT_VECTOR_80 = 0x52,
    INT_VECTOR_81 = 0x53,
    INT_VECTOR_82 = 0x54,
    INT_VECTOR_83 = 0x55,
    INT_VECTOR_84 = 0x56,
    INT_VECTOR_85 = 0x57,
    INT_VECTOR_86 = 0x58,
    INT_VECTOR_87 = 0x59,
    INT_VECTOR_88 = 0x5A,
    INT_VECTOR_89 = 0x5B,
    INT_VECTOR_90 = 0x5C,
    INT_VECTOR_91 = 0x5D,
    INT_VECTOR_92 = 0x5E,
    INT_VECTOR_93 = 0x5F,
    INT_VECTOR_94 = 0x60,
    INT_VECTOR_95 = 0x61,
    INT_VECTOR_96 = 0x62,
    INT_VECTOR_97 = 0x63,
    INT_VECTOR_98 = 0x64,
    INT_VECTOR_99 = 0x65,
    INT_VECTOR_100 = 0x66,
    INT_VECTOR_101 = 0x67,
    INT_VECTOR_102 = 0x68,
    INT_VECTOR_103 = 0x69,
    INT_VECTOR_104 = 0x6A,
    INT_VECTOR_105 = 0x6B,
    INT_VECTOR_106 = 0x6D,
    INT_VECTOR_107 = 0x6E,
    INT_VECTOR_108 = 0x6F,
    INT_VECTOR_109 = 0x70,
    INT_VECTOR_110 = 0x71,
    INT_VECTOR_111 = 0x72,
    INT_VECTOR_112 = 0x73,
    INT_VECTOR_113 = 0x74,
    INT_VECTOR_114 = 0x75,
    INT_VECTOR_115 = 0x76,
    INT_VECTOR_116 = 0x77,
    INT_VECTOR_117 = 0x78,
    INT_VECTOR_118 = 0x79,
    INT_VECTOR_119 = 0x7A,
    INT_VECTOR_120 = 0x7B,
    INT_VECTOR_121 = 0x7C,
    INT_VECTOR_122 = 0x7D,
    INT_VECTOR_123 = 0x7E,
    INT_VECTOR_124 = 0x7F,
    INT_VECTOR_125 = 0x80,
    INT_VECTOR_126 = 0x81,
    INT_VECTOR_127 = 0x82,
    INT_VECTOR_128 = 0x83,
    INT_VECTOR_129 = 0x84,
    INT_VECTOR_130 = 0x85,
    INT_VECTOR_131 = 0x86,
    INT_VECTOR_132 = 0x87,
    INT_VECTOR_133 = 0x88,
    INT_VECTOR_134 = 0x89,
    INT_VECTOR_135 = 0x8A,
    INT_VECTOR_136 = 0x8B,
    INT_VECTOR_137 = 0x8C,
    INT_VECTOR_138 = 0x8D,
    INT_VECTOR_139 = 0x8E,
    INT_VECTOR_140 = 0x8F,
    INT_VECTOR_141 = 0x90,
    INT_VECTOR_142 = 0x91,
    INT_VECTOR_143 = 0x92,
    INT_VECTOR_144 = 0x93,
    INT_VECTOR_145 = 0x94,
    INT_VECTOR_146 = 0x95,
    INT_VECTOR_147 = 0x96,
    INT_VECTOR_148 = 0x97,
    INT_VECTOR_149 = 0x98,
    INT_VECTOR_150 = 0x99,
    INT_VECTOR_151 = 0x9A,
    INT_VECTOR_152 = 0x9B,
    INT_VECTOR_153 = 0x9C,
    INT_VECTOR_154 = 0x9D,
    INT_VECTOR_155 = 0x9E,
    INT_VECTOR_156 = 0x9F,
    INT_VECTOR_157 = 0xA0,
    INT_VECTOR_158 = 0xA1,
    INT_VECTOR_159 = 0xA2,
    INT_VECTOR_160 = 0xA3,
    INT_VECTOR_161 = 0xA4,
    INT_VECTOR_162 = 0xA5,
    INT_VECTOR_163 = 0xA6,
    INT_VECTOR_164 = 0xA7,
    INT_VECTOR_165 = 0xA8,
    INT_VECTOR_166 = 0xA9,
    INT_VECTOR_167 = 0xAA,
    INT_VECTOR_168 = 0xAB,
    INT_VECTOR_169 = 0xAC,
    INT_VECTOR_170 = 0xAD,
    INT_VECTOR_171 = 0xAE,
    INT_VECTOR_172 = 0xAF,
    INT_VECTOR_173 = 0xB0,
    INT_VECTOR_174 = 0xB1,
    INT_VECTOR_175 = 0xB2,
    INT_VECTOR_176 = 0xB3,
    INT_VECTOR_177 = 0xB4,
    INT_VECTOR_178 = 0xB5,
    INT_VECTOR_179 = 0xB6,
    INT_VECTOR_180 = 0xB7,
    INT_VECTOR_181 = 0xB8,
    INT_VECTOR_182 = 0xB9,
    INT_VECTOR_183 = 0xBA,
    INT_VECTOR_184 = 0xBB,
    INT_VECTOR_185 = 0xBC,
    INT_VECTOR_186 = 0xBD,
    INT_VECTOR_187 = 0xBE,
    INT_VECTOR_188 = 0x10,
    INT_VECTOR_189 = 0x20,
    INT_VECTOR_190 = 0x40

} INT_OFFSET_VECTOR;

typedef enum {

    INT_EXTERNAL_INT_SOURCE0 = 0x01,
    INT_EXTERNAL_INT_SOURCE1 = 0x02,
    INT_EXTERNAL_INT_SOURCE2 = 0x04,
    INT_EXTERNAL_INT_SOURCE3 = 0x08,
    INT_EXTERNAL_INT_SOURCE4 = 0x10

} INT_EXTERNAL_SOURCES;

typedef enum {

    INT_PRIORITY_LEVEL0 = 0x0,
    INT_PRIORITY_LEVEL1 = 0x01,
    INT_PRIORITY_LEVEL2 = 0x02,
    INT_PRIORITY_LEVEL3 = 0x03,
    INT_PRIORITY_LEVEL4 = 0x04,
    INT_PRIORITY_LEVEL5 = 0x05,
    INT_PRIORITY_LEVEL6 = 0x06,
    INT_PRIORITY_LEVEL7 = 0x07

} INT_PRIORITY_LEVEL;

typedef enum {

    INT_SUBPRIORITY_LEVEL0 = 0x0,
    INT_SUBPRIORITY_LEVEL1 = 0x01,
    INT_SUBPRIORITY_LEVEL2 = 0x02,
    INT_SUBPRIORITY_LEVEL3 = 0x03

} INT_SUBPRIORITY_LEVEL;

typedef enum {

    INT_SOURCE_TIMER_CORE = 0x00,
    INT_SOURCE_SOFTWARE_0 = 0x01,
    INT_SOURCE_SOFTWARE_1 = 0x02,
    INT_SOURCE_EXTERNAL_0 = 0x03,
    INT_SOURCE_TIMER_1 = 0x04,
    INT_SOURCE_INPUT_CAPTURE_1_ERROR = 0x05,
    INT_SOURCE_INPUT_CAPTURE_1 = 0x06,
    INT_SOURCE_OUTPUT_COMPARE_1 = 0x07,
    INT_SOURCE_EXTERNAL_1 = 0x08,
    INT_SOURCE_TIMER_2 = 0x09,
    INT_SOURCE_INPUT_CAPTURE_2_ERROR = 0x0A,
    INT_SOURCE_INPUT_CAPTURE_2 = 0x0B,
    INT_SOURCE_OUTPUT_COMPARE_2 = 0x0C,
    INT_SOURCE_EXTERNAL_2 = 0x0D,
    INT_SOURCE_TIMER_3 = 0x0E,
    INT_SOURCE_INPUT_CAPTURE_3_ERROR = 0x0F,
    INT_SOURCE_INPUT_CAPTURE_3 = 0x10,
    INT_SOURCE_OUTPUT_COMPARE_3 = 0x11,
    INT_SOURCE_EXTERNAL_3 = 0x12,
    INT_SOURCE_TIMER_4 = 0x13,
    INT_SOURCE_INPUT_CAPTURE_4_ERROR = 0x14,
    INT_SOURCE_INPUT_CAPTURE_4 = 0x15,
    INT_SOURCE_OUTPUT_COMPARE_4 = 0x16,
    INT_SOURCE_EXTERNAL_4 = 0x17,
    INT_SOURCE_TIMER_5 = 0x18,
    INT_SOURCE_INPUT_CAPTURE_5_ERROR = 0x19,
    INT_SOURCE_INPUT_CAPTURE_5 = 0x1A,
    INT_SOURCE_OUTPUT_COMPARE_5 = 0x1B,
    INT_SOURCE_TIMER_6 = 0x1C,
    INT_SOURCE_INPUT_CAPTURE_6_ERROR = 0x1D,
    INT_SOURCE_INPUT_CAPTURE_6 = 0x1E,
    INT_SOURCE_OUTPUT_COMPARE_6 = 0x1F,
    INT_SOURCE_TIMER_7 = 0x20,
    INT_SOURCE_INPUT_CAPTURE_7_ERROR = 0x21,
    INT_SOURCE_INPUT_CAPTURE_7 = 0x22,
    INT_SOURCE_OUTPUT_COMPARE_7 = 0x23,
    INT_SOURCE_TIMER_8 = 0x24,
    INT_SOURCE_INPUT_CAPTURE_8_ERROR = 0x25,
    INT_SOURCE_INPUT_CAPTURE_8 = 0x26,
    INT_SOURCE_OUTPUT_COMPARE_8 = 0x27,
    INT_SOURCE_TIMER_9 = 0x28,
    INT_SOURCE_INPUT_CAPTURE_9_ERROR = 0x29,
    INT_SOURCE_INPUT_CAPTURE_9 = 0x2A,
    INT_SOURCE_OUTPUT_COMPARE_9 = 0x2B,
    INT_SOURCE_ADC_1 = 0x2C,
    INT_SOURCE_ADC_1_DC1 = 0x2E,
    INT_SOURCE_ADC_1_DC2 = 0x2F,
    INT_SOURCE_ADC_1_DC3 = 0x30,
    INT_SOURCE_ADC_1_DC4 = 0x31,
    INT_SOURCE_ADC_1_DC5 = 0x32,
    INT_SOURCE_ADC_1_DC6 = 0x33,
    INT_SOURCE_ADC_1_DF1 = 0x34,
    INT_SOURCE_ADC_1_DF2 = 0x35,
    INT_SOURCE_ADC_1_DF3 = 0x36,
    INT_SOURCE_ADC_1_DF4 = 0x37,
    INT_SOURCE_ADC_1_DF5 = 0x38,
    INT_SOURCE_ADC_1_DF6 = 0x39,
    INT_SOURCE_ADC_1_DATA0 = 0x3B,
    INT_SOURCE_ADC_1_DATA1 = 0x3C,
    INT_SOURCE_ADC_1_DATA2 = 0x3D,
    INT_SOURCE_ADC_1_DATA3 = 0x3E,
    INT_SOURCE_ADC_1_DATA4 = 0x3F,
    INT_SOURCE_ADC_1_DATA5 = 0x40,
    INT_SOURCE_ADC_1_DATA6 = 0x41,
    INT_SOURCE_ADC_1_DATA7 = 0x42,
    INT_SOURCE_ADC_1_DATA8 = 0x43,
    INT_SOURCE_ADC_1_DATA9 = 0x44,
    INT_SOURCE_ADC_1_DATA10 = 0x45,
    INT_SOURCE_ADC_1_DATA11 = 0x46,
    INT_SOURCE_ADC_1_DATA12 = 0x47,
    INT_SOURCE_ADC_1_DATA13 = 0x48,
    INT_SOURCE_ADC_1_DATA14 = 0x49,
    INT_SOURCE_ADC_1_DATA15 = 0x4A,
    INT_SOURCE_ADC_1_DATA16 = 0x4B,
    INT_SOURCE_ADC_1_DATA17 = 0x4C,
    INT_SOURCE_ADC_1_DATA18 = 0x4D,
    INT_SOURCE_ADC_1_DATA19 = 0x4E,
    INT_SOURCE_ADC_1_DATA20 = 0x4F,
    INT_SOURCE_ADC_1_DATA21 = 0x50,
    INT_SOURCE_ADC_1_DATA22 = 0x51,
    INT_SOURCE_ADC_1_DATA23 = 0x52,
    INT_SOURCE_ADC_1_DATA24 = 0x53,
    INT_SOURCE_ADC_1_DATA25 = 0x54,
    INT_SOURCE_ADC_1_DATA26 = 0x55,
    INT_SOURCE_ADC_1_DATA27 = 0x56,
    INT_SOURCE_ADC_1_DATA28 = 0x57,
    INT_SOURCE_ADC_1_DATA29 = 0x58,
    INT_SOURCE_ADC_1_DATA30 = 0x59,
    INT_SOURCE_ADC_1_DATA31 = 0x5A,
    INT_SOURCE_ADC_1_DATA32 = 0x5B,
    INT_SOURCE_ADC_1_DATA33 = 0x5C,
    INT_SOURCE_ADC_1_DATA34 = 0x5D,
    INT_SOURCE_ADC_1_DATA35 = 0x5E,
    INT_SOURCE_ADC_1_DATA36 = 0x5F,
    INT_SOURCE_ADC_1_DATA37 = 0x60,
    INT_SOURCE_ADC_1_DATA38 = 0x61,
    INT_SOURCE_ADC_1_DATA39 = 0x62,
    INT_SOURCE_ADC_1_DATA40 = 0x63,
    INT_SOURCE_ADC_1_DATA41 = 0x64,
    INT_SOURCE_ADC_1_DATA42 = 0x65,
    INT_SOURCE_ADC_1_DATA43 = 0x66,
    INT_SOURCE_ADC_1_DATA44 = 0x67,
    INT_SOURCE_CORE_PERF_COUNT = 0x68,
    INT_SOURCE_FAST_DEBUG = 0x69,
    INT_SOURCE_SYSTEM_BUS_PROTECTION = 0x6A,
    INT_SOURCE_CRYPTO = 0x6B,
    INT_SOURCE_SPI_1_ERROR = 0x6D,
    INT_SOURCE_SPI_1_RECEIVE = 0x6E,
    INT_SOURCE_SPI_1_TRANSMIT = 0x6F,
    INT_SOURCE_USART_1_ERROR = 0x70,
    INT_SOURCE_USART_1_RECEIVE = 0x71,
    INT_SOURCE_USART_1_TRANSMIT = 0x72,
    INT_SOURCE_I2C_1_BUS = 0x73,
    INT_SOURCE_I2C_1_SLAVE = 0x74,
    INT_SOURCE_I2C_1_MASTER = 0x75,
    INT_SOURCE_CHANGE_NOTICE_A = 0x76,
    INT_SOURCE_CHANGE_NOTICE_B = 0x77,
    INT_SOURCE_CHANGE_NOTICE_C = 0x78,
    INT_SOURCE_CHANGE_NOTICE_D = 0x79,
    INT_SOURCE_CHANGE_NOTICE_E = 0x7A,
    INT_SOURCE_CHANGE_NOTICE_F = 0x7B,
    INT_SOURCE_CHANGE_NOTICE_G = 0x7C,
    INT_SOURCE_CHANGE_NOTICE_H = 0x7D,
    INT_SOURCE_CHANGE_NOTICE_J = 0x7E,
    INT_SOURCE_CHANGE_NOTICE_K = 0x7F,
    INT_SOURCE_PARALLEL_PORT = 0x80,
    INT_SOURCE_PARALLEL_PORT_ERROR = 0x81,
    INT_SOURCE_COMPARATOR_1 = 0x82,
    INT_SOURCE_COMPARATOR_2 = 0x83,
    INT_SOURCE_USB_1 = 0x84,
    INT_SOURCE_USB_1_DMA = 0x85,
    INT_SOURCE_DMA_0 = 0x86,
    INT_SOURCE_DMA_1 = 0x87,
    INT_SOURCE_DMA_2 = 0x88,
    INT_SOURCE_DMA_3 = 0x89,
    INT_SOURCE_DMA_4 = 0x8A,
    INT_SOURCE_DMA_5 = 0x8B,
    INT_SOURCE_DMA_6 = 0x8C,
    INT_SOURCE_DMA_7 = 0x8D,
    INT_SOURCE_SPI_2_ERROR = 0x8E,
    INT_SOURCE_SPI_2_RECEIVE = 0x8F,
    INT_SOURCE_SPI_2_TRANSMIT = 0x90,
    INT_SOURCE_USART_2_ERROR = 0x91,
    INT_SOURCE_USART_2_RECEIVE = 0x92,
    INT_SOURCE_USART_2_TRANSMIT = 0x93,
    INT_SOURCE_I2C_2_BUS = 0x94,
    INT_SOURCE_I2C_2_SLAVE = 0x95,
    INT_SOURCE_I2C_2_MASTER = 0x96,
    INT_SOURCE_CAN_1 = 0x97,
    INT_SOURCE_CAN_2 = 0x98,
    INT_SOURCE_ETH_1 = 0x99,
    INT_SOURCE_SPI_3_ERROR = 0x9A,
    INT_SOURCE_SPI_3_RECEIVE = 0x9B,
    INT_SOURCE_SPI_3_TRANSMIT = 0x9C,
    INT_SOURCE_USART_3_ERROR = 0x9D,
    INT_SOURCE_USART_3_RECEIVE = 0x9E,
    INT_SOURCE_USART_3_TRANSMIT = 0x9F,
    INT_SOURCE_I2C_3_BUS = 0xA0,
    INT_SOURCE_I2C_3_SLAVE = 0xA1,
    INT_SOURCE_I2C_3_MASTER = 0xA2,
    INT_SOURCE_SPI_4_ERROR = 0xA3,
    INT_SOURCE_SPI_4_RECEIVE = 0xA4,
    INT_SOURCE_SPI_4_TRANSMIT = 0xA5,
    INT_SOURCE_USART_4_ERROR = 0xAA,
    INT_SOURCE_USART_4_RECEIVE = 0xAB,
    INT_SOURCE_USART_4_TRANSMIT = 0xAC,
    INT_SOURCE_I2C_4_BUS = 0xAD,
    INT_SOURCE_I2C_4_SLAVE = 0xAE,
    INT_SOURCE_I2C_5_MASTER = 0xB8,
    INT_SOURCE_SPI_5_ERROR = 0xB0,
    INT_SOURCE_SPI_5_RECEIVE = 0xB1,
    INT_SOURCE_SPI_5_TRANSMIT = 0xB2,
    INT_SOURCE_USART_5_ERROR = 0xB3,
    INT_SOURCE_USART_5_RECEIVE = 0xB4,
    INT_SOURCE_USART_5_TRANSMIT = 0xB5,
    INT_SOURCE_I2C_5_BUS = 0xB6,
    INT_SOURCE_I2C_5_SLAVE = 0xB7,
    INT_SOURCE_SPI_6_ERROR = 0xB9,
    INT_SOURCE_SPI_6_RECEIVE = 0xBA,
    INT_SOURCE_SPI_6_TRANSMIT = 0xBB,
    INT_SOURCE_USART_6_ERROR = 0xBC,
    INT_SOURCE_USART_6_RECEIVE = 0xBD,
    INT_SOURCE_USART_6_TRANSMIT = 0xBE,
    INT_SOURCE_RTCC = 0xA6,
    INT_SOURCE_FLASH_CONTROL = 0xA7,
    INT_SOURCE_PREFETCH = 0xA8,
    INT_SOURCE_SQI1 = 0xA9,
    INT_SOURCE_I2C_4_MASTER = 0xAF

} INT_SOURCE;

typedef enum {

    INT_VECTOR_CT = 0x00,
    INT_VECTOR_CS0 = 0x08,
    INT_VECTOR_CS1 = 0x10,
    INT_VECTOR_INT0 = 0x18,
    INT_VECTOR_T1 = 0x20,
    INT_VECTOR_IC1 = 0x30,
    INT_VECTOR_IC1_ERROR = 0x28,
    INT_VECTOR_OC1 = 0x38,
    INT_VECTOR_INT1 = 0x40,
    INT_VECTOR_T2 = 0x48,
    INT_VECTOR_IC2 = 0x58,
    INT_VECTOR_IC2_ERROR = 0x50,
    INT_VECTOR_OC2 = 0x60,
    INT_VECTOR_INT2 = 0x68,
    INT_VECTOR_T3 = 0x70,
    INT_VECTOR_IC3 = 0x80,
    INT_VECTOR_IC3_ERROR = 0x78,
    INT_VECTOR_OC3 = 0x88,
    INT_VECTOR_INT3 = 0x90,
    INT_VECTOR_T4 = 0x98,
    INT_VECTOR_IC4 = 0xA8,
    INT_VECTOR_IC4_ERROR = 0xA0,
    INT_VECTOR_OC4 = 0xB0,
    INT_VECTOR_INT4 = 0xB8,
    INT_VECTOR_T5 = 0xC0,
    INT_VECTOR_IC5 = 0xD0,
    INT_VECTOR_IC5_ERROR = 0xC8,
    INT_VECTOR_OC5 = 0xD8,
    INT_VECTOR_T6 = 0xE0,
    INT_VECTOR_IC6_ERROR = 0xE8,
    INT_VECTOR_IC6 = 0xF0,
    INT_VECTOR_OC6 = 0xF8,
    INT_VECTOR_T7 = 0x100,
    INT_VECTOR_IC7_ERROR = 0x108,
    INT_VECTOR_IC7 = 0x110,
    INT_VECTOR_OC7 = 0x118,
    INT_VECTOR_T8 = 0x120,
    INT_VECTOR_IC8_ERROR = 0x128,
    INT_VECTOR_IC8 = 0x130,
    INT_VECTOR_OC8 = 0X138,
    INT_VECTOR_T9 = 0x140,
    INT_VECTOR_IC9_ERROR = 0x148,
    INT_VECTOR_IC9 = 0x150,
    INT_VECTOR_OC9 = 0x158,
    INT_VECTOR_ADC1 = 0x160,
    INT_VECTOR_ADC1_DC1 = 0x170,
    INT_VECTOR_ADC1_DC2 = 0x178,
    INT_VECTOR_ADC1_DC3 = 0x180,
    INT_VECTOR_ADC1_DC4 = 0x188,
    INT_VECTOR_ADC1_DC5 = 0x190,
    INT_VECTOR_ADC1_DC6 = 0x198,
    INT_VECTOR_ADC1_DF1 = 0x1A0,
    INT_VECTOR_ADC1_DF2 = 0x1A8,
    INT_VECTOR_ADC1_DF3 = 0x1B0,
    INT_VECTOR_ADC1_DF4 = 0x1B8,
    INT_VECTOR_ADC1_DF5 = 0x1C0,
    INT_VECTOR_ADC1_DF6 = 0x1C8,
    INT_VECTOR_ADC1_DATA0 = 0x1D8,
    INT_VECTOR_ADC1_DATA1 = 0x1E0,
    INT_VECTOR_ADC1_DATA2 = 0x1E8,
    INT_VECTOR_ADC1_DATA3 = 0x1F0,
    INT_VECTOR_ADC1_DATA4 = 0x1F8,
    INT_VECTOR_ADC1_DATA5 = 0x200,
    INT_VECTOR_ADC1_DATA6 = 0x208,
    INT_VECTOR_ADC1_DATA7 = 0x210,
    INT_VECTOR_ADC1_DATA8 = 0x218,
    INT_VECTOR_ADC1_DATA9 = 0x220,
    INT_VECTOR_ADC1_DATA10 = 0x228,
    INT_VECTOR_ADC1_DATA11 = 0x230,
    INT_VECTOR_ADC1_DATA12 = 0x238,
    INT_VECTOR_ADC1_DATA13 = 0x240,
    INT_VECTOR_ADC1_DATA14 = 0x248,
    INT_VECTOR_ADC1_DATA15 = 0x250,
    INT_VECTOR_ADC1_DATA16 = 0x258,
    INT_VECTOR_ADC1_DATA17 = 0x260,
    INT_VECTOR_ADC1_DATA18 = 0x268,
    INT_VECTOR_ADC1_DATA19 = 0x270,
    INT_VECTOR_ADC1_DATA20 = 0x278,
    INT_VECTOR_ADC1_DATA21 = 0x280,
    INT_VECTOR_ADC1_DATA22 = 0X288,
    INT_VECTOR_ADC1_DATA23 = 0x290,
    INT_VECTOR_ADC1_DATA24 = 0x298,
    INT_VECTOR_ADC1_DATA25 = 0x2A0,
    INT_VECTOR_ADC1_DATA26 = 0x2A8,
    INT_VECTOR_ADC1_DATA27 = 0x2B0,
    INT_VECTOR_ADC1_DATA28 = 0x2B8,
    INT_VECTOR_ADC1_DATA29 = 0x2C0,
    INT_VECTOR_ADC1_DATA30 = 0x2C8,
    INT_VECTOR_ADC1_DATA31 = 0x2D0,
    INT_VECTOR_ADC1_DATA32 = 0x2D8,
    INT_VECTOR_ADC1_DATA33 = 0x2E0,
    INT_VECTOR_ADC1_DATA34 = 0x2E8,
    INT_VECTOR_ADC1_DATA35 = 0x2F0,
    INT_VECTOR_ADC1_DATA36 = 0x2F8,
    INT_VECTOR_ADC1_DATA37 = 0x300,
    INT_VECTOR_ADC1_DATA38 = 0x308,
    INT_VECTOR_ADC1_DATA39 = 0x310,
    INT_VECTOR_ADC1_DATA40 = 0x318,
    INT_VECTOR_ADC1_DATA41 = 0x320,
    INT_VECTOR_ADC1_DATA42 = 0x328,
    INT_VECTOR_ADC1_DATA43 = 0x330,
    INT_VECTOR_ADC1_DATA44 = 0x338,
    INT_VECTOR_CORE_PERF_COUNT = 0x340,
    INT_VECTOR_CORE_FAST_DEBUG_CHANNEL = 0x348,
    INT_VECTOR_CORE_SYSTEM_BUS_PROTECTION = 0x350,
    INT_VECTOR_CRYPTO = 0x358,
    INT_VECTOR_SPI1_FAULT = 0x368,
    INT_VECTOR_SPI1_RX = 0x370,
    INT_VECTOR_SPI1_TX = 0x378,
    INT_VECTOR_UART1_FAULT = 0x380,
    INT_VECTOR_UART1_RX = 0x388,
    INT_VECTOR_UART1_TX = 0x390,
    INT_VECTOR_I2C1_BUS = 0x398,
    INT_VECTOR_I2C1_SLAVE = 0x3A0,
    INT_VECTOR_I2C1_MASTER = 0x3A8,
    INT_VECTOR_SPI2_FAULT = 0x470,
    INT_VECTOR_SPI2_RX = 0x478,
    INT_VECTOR_SPI2_TX = 0x480,
    INT_VECTOR_UART2_FAULT = 0x488,
    INT_VECTOR_UART2_RX = 0x490,
    INT_VECTOR_UART2_TX = 0x498,
    INT_VECTOR_I2C2_BUS = 0x4A0,
    INT_VECTOR_I2C2_SLAVE = 0x4A8,
    INT_VECTOR_I2C2_MASTER = 0x4B0,
    INT_VECTOR_SPI3_FAULT = 0x4D0,
    INT_VECTOR_SPI3_RX = 0x4D8,
    INT_VECTOR_SPI3_TX = 0x4E0,
    INT_VECTOR_UART3_FAULT = 0x4E8,
    INT_VECTOR_UART3_RX = 0x4F0,
    INT_VECTOR_UART3_TX = 0x4F8,
    INT_VECTOR_I2C3_BUS = 0x500,
    INT_VECTOR_I2C3_SLAVE = 0x508,
    INT_VECTOR_I2C3_MASTER = 0x510,
    INT_VECTOR_SPI4_FAULT = 0x518,
    INT_VECTOR_SPI4_RX = 0x520,
    INT_VECTOR_SPI4_TX = 0x528,
    INT_VECTOR_UART4_FAULT = 0x550,
    INT_VECTOR_UART4_RX = 0x558,
    INT_VECTOR_I2C4_BUS = 0x568,
    INT_VECTOR_I2C4_SLAVE = 0x570,
    INT_VECTOR_I2C4_MASTER = 0x578,
    INT_VECTOR_SPI5_FAULT = 0x580,
    INT_VECTOR_SPI5_RX = 0x588,
    INT_VECTOR_SPI5_TX = 0x590,
    INT_VECTOR_UART5_FAULT = 0x598,
    INT_VECTOR_UART5_RX = 0x5A0,
    INT_VECTOR_UART5_TX = 0x5A8,
    INT_VECTOR_I2C5_BUS = 0x5B0,
    INT_VECTOR_I2C5_SLAVE = 0x5B8,
    INT_VECTOR_I2C5_MASTER = 0x5C0,
    INT_VECTOR_SPI6_FAULT = 0x5C8,
    INT_VECTOR_SPI6_RX = 0x5D0,
    INT_VECTOR_SPI6_TX = 0x5D8,
    INT_VECTOR_UART6_FAULT = 0x5E0,
    INT_VECTOR_UART6_RX = 0x5E8,
    INT_VECTOR_UART6_TX = 0x5F0,
    INT_VECTOR_CHANGE_NOTICE_A = 0x3B0,
    INT_VECTOR_CHANGE_NOTICE_B = 0x3B8,
    INT_VECTOR_CHANGE_NOTICE_C = 0x3C0,
    INT_VECTOR_CHANGE_NOTICE_D = 0X3C8,
    INT_VECTOR_CHANGE_NOTICE_E = 0x3D0,
    INT_VECTOR_CHANGE_NOTICE_F = 0x3D8,
    INT_VECTOR_CHANGE_NOTICE_G = 0x3E0,
    INT_VECTOR_CHANGE_NOTICE_H = 0x3E8,
    INT_VECTOR_CHANGE_NOTICE_J = 0x3F0,
    INT_VECTOR_CHANGE_NOTICE_K = 0x3F8,
    INT_VECTOR_PMP = 0x400,
    INT_VECTOR_PMP_ERROR = 0x408,
    INT_VECTOR_USB = 0x420,
    INT_VECTOR_USB_DMA = 0x428,
    INT_VECTOR_RTCC = 0x530,
    INT_VECTOR_FLASH = 0x538,
    INT_VECTOR_SQI1 = 0x548,
    INT_VECTOR_CMP1 = 0x410,
    INT_VECTOR_CMP2 = 0x418,
    INT_VECTOR_DMA0 = 0x430,
    INT_VECTOR_DMA1 = 0x438,
    INT_VECTOR_DMA2 = 0x440,
    INT_VECTOR_DMA3 = 0x448,
    INT_VECTOR_DMA4 = 0x450,
    INT_VECTOR_DMA5 = 0x458,
    INT_VECTOR_DMA6 = 0x460,
    INT_VECTOR_DMA7 = 0x468,
    INT_VECTOR_CAN1 = 0x4B8,
    INT_VECTOR_CAN2 = 0x4C0,
    INT_VECTOR_ETH = 0x4C8

} INT_VECTOR;

typedef enum {

    INT_TRAP_SOURCE_NONE

} INT_TRAP_SOURCE;

INLINE SFR_TYPE* _INT_INT_EXT_INT0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_PROXIMITY_TIMER_ENABLE_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_SINGLE_MULTI_VECTOR_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTCON;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_SHADOW_SET_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &PRISS;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_PRIORITY_SHADOW_REGISTER_SELECT_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &PRISS;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_LATEST_INT_VECTOR_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTSTAT;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_LATEST_INT_PRIORITY_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &INTSTAT;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_FLAG_STATUS_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IFS0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_FLAG_STATUS_2_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IFS0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_FLAG_STATUS_1_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IFS1;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_ENABLE_CONTROL_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IEC0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_ENABLE_CONTROL_1_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IEC1;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_ENABLE_CONTROL_2_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IEC2;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_INT_PRIORITY_CONTROL_0_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &IPC0;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_TYPE* _INT_VECTOR_ADDRESS_OFFSET_SET_VREG(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return &OFF000;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_TYPE*)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_SS0_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIORITY_SHADOW_REGISTER_SELECT_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_PRI1SS_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SIRQ_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_2_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_IC4EIF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_T7IF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_T7IE_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_2_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC2_AD1D5IE_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_VECTOR_ADDRESS_OFFSET_SET_MASK(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _OFF000_VOFF_MASK;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_SS0_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIORITY_SHADOW_REGISTER_SELECT_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_PRI1SS_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SIRQ_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_2_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_IC4EIF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_T7IF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_T7IE_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_2_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC2_AD1D5IE_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_VECTOR_ADDRESS_OFFSET_SET_POS(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _OFF000_VOFF_POSITION;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_EXT_INT0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_INT0EP_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PROXIMITY_TIMER_ENABLE_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_TPC_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SINGLE_MULTI_VECTOR_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTCON_MVEC_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_SHADOW_SET_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_SS0_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_PRIORITY_SHADOW_REGISTER_SELECT_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _PRISS_PRI1SS_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_VECTOR_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SIRQ_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_LATEST_INT_PRIORITY_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _INTSTAT_SRIPL_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_CTIF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_2_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS0_IC4EIF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_FLAG_STATUS_1_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IFS1_T7IF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC0_CTIE_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_1_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC1_T7IE_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_ENABLE_CONTROL_2_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IEC2_AD1D5IE_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_INT_PRIORITY_CONTROL_0_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _IPC0_CTIS_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

INLINE SFR_DATA _INT_VECTOR_ADDRESS_OFFSET_SET_LEN(INT_MODULE_ID i)
{
    switch (i) {
        case INT_ID_0 :
            return _OFF000_VOFF_LENGTH;
        case INT_NUMBER_OF_MODULES :
        default :
            return (SFR_DATA)-1;
    }
}

/* Section 2 - Feature variant inclusion */

#define PLIB_TEMPLATE INLINE
#include "../templates/int_SingleVectorShadowSet_Default.h"
#include "../templates/int_VectorSelect_Default.h"
#include "../templates/int_ProximityTimerEnable_Default.h"
#include "../templates/int_ProximityTimerControl_Unsupported.h"
#include "../templates/int_ExternalINTEdgeSelect_Default.h"
#include "../templates/int_INTCPUPriority_Default.h"
#include "../templates/int_INTCPUVector_Default.h"
#include "../templates/int_SourceFlag_Default.h"
#include "../templates/int_SourceControl_Default.h"
#include "../templates/int_VectorPriority_Default.h"
#include "../templates/int_CPUCurrentPriorityLevel_Default.h"
#include "../templates/int_EnableControl_PIC32.h"
#include "../templates/int_INTNesting_Unsupported.h"
#include "../templates/int_TrapSource_Unsupported.h"
#include "../templates/int_AlternateVectorTable_Unsupported.h"
#include "../templates/int_PeripheralControl_Unsupported.h"
#include "../templates/int_HighPriority_Unsupported.h"
#include "../templates/int_LowPriority_Unsupported.h"
#include "../templates/int_Priority_Unsupported.h"

/* Section 3 - PLIB dispatch function definitions */

INLINE_API bool PLIB_INT_ExistsSingleVectorShadowSet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSingleVectorShadowSet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SingleVectorShadowSetDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorShadowSetDisable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SingleVectorShadowSetEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorShadowSetEnable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsVectorSelect_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_MultiVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_MultiVectorSelect_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SingleVectorSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_SingleVectorSelect_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsProximityTimerEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsProximityTimerEnable_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_ProximityTimerEnable(INT_MODULE_ID index, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerEnable_Default(index, priority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_ProximityTimerDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerDisable_Default(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsProximityTimerControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsProximityTimerControl_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerSet(INT_MODULE_ID index, uint32_t timerreloadvalue)
{
    switch (index) {
        case INT_ID_0 :
            INT_ProximityTimerSet_Unsupported(index, timerreloadvalue);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API uint32_t _PLIB_UNSUPPORTED PLIB_INT_ProximityTimerGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ProximityTimerGet_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (uint32_t)0;
    }
}

INLINE_API bool PLIB_INT_ExistsExternalINTEdgeSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsExternalINTEdgeSelect_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_ExternalRisingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_ID_0 :
            INT_ExternalRisingEdgeSelect_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_ExternalFallingEdgeSelect(INT_MODULE_ID index, INT_EXTERNAL_SOURCES source)
{
    switch (index) {
        case INT_ID_0 :
            INT_ExternalFallingEdgeSelect_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsINTCPUPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTCPUPriority_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_PriorityGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_PriorityGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsINTCPUVector(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTCPUVector_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_VECTOR PLIB_INT_VectorGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_VECTOR)0;
    }
}

INLINE_API bool PLIB_INT_ExistsSourceFlag(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSourceFlag_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_INT_SourceFlagGet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            return INT_SourceFlagGet_Default(index, source);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SourceFlagSet(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceFlagSet_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SourceFlagClear(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceFlagClear_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_ExistsSourceControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsSourceControl_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_SourceEnable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceEnable_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_SourceDisable(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            INT_SourceDisable_Default(index, source);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_SourceIsEnabled(INT_MODULE_ID index, INT_SOURCE source)
{
    switch (index) {
        case INT_ID_0 :
            return INT_SourceIsEnabled_Default(index, source);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool PLIB_INT_ExistsVectorPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsVectorPriority_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_VectorPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_PRIORITY_LEVEL priority)
{
    switch (index) {
        case INT_ID_0 :
            INT_VectorPrioritySet_Default(index, vector, priority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_VectorPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorPriorityGet_Default(index, vector);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API void PLIB_INT_VectorSubPrioritySet(INT_MODULE_ID index, INT_VECTOR vector, INT_SUBPRIORITY_LEVEL subpriority)
{
    switch (index) {
        case INT_ID_0 :
            INT_VectorSubPrioritySet_Default(index, vector, subpriority);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API INT_SUBPRIORITY_LEVEL PLIB_INT_VectorSubPriorityGet(INT_MODULE_ID index, INT_VECTOR vector)
{
    switch (index) {
        case INT_ID_0 :
            return INT_VectorSubPriorityGet_Default(index, vector);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_SUBPRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsCPUCurrentPriorityLevel(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsCPUCurrentPriorityLevel_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API INT_PRIORITY_LEVEL PLIB_INT_CPUCurrentPriorityLevelGet(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_CPUCurrentPriorityLevelGet_Default(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (INT_PRIORITY_LEVEL)0;
    }
}

INLINE_API bool PLIB_INT_ExistsEnableControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsEnableControl_PIC32(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void PLIB_INT_Enable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_Enable_PIC32(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void PLIB_INT_Disable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_Disable_PIC32(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool PLIB_INT_IsEnabled(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_IsEnabled_PIC32(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsINTNesting(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsINTNesting_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_NestingEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_NestingDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_NestingDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsTrapSource(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsTrapSource_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagGet(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_ID_0 :
            return INT_TrapSourceFlagGet_Unsupported(index, trapsource);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_TrapSourceFlagClear(INT_MODULE_ID index, INT_TRAP_SOURCE trapsource)
{
    switch (index) {
        case INT_ID_0 :
            INT_TrapSourceFlagClear_Unsupported(index, trapsource);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsAlternateVectorTable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsAlternateVectorTable_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_AlternateVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_AlternateVectorTableSelect_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_StandardVectorTableSelect(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_StandardVectorTableSelect_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPeripheralControl(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsPeripheralControl_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PeripheralsEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PeripheralsDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PeripheralsDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsHighPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsHighPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityHighEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityHighDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityHighDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsLowPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsLowPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityLowEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityLowDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityLowDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API bool _PLIB_UNSUPPORTED PLIB_INT_ExistsPriority(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            return INT_ExistsPriority_Unsupported(index);
        case INT_NUMBER_OF_MODULES :
        default :
            return (bool)0;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityEnable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityEnable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

INLINE_API void _PLIB_UNSUPPORTED PLIB_INT_PriorityDisable(INT_MODULE_ID index)
{
    switch (index) {
        case INT_ID_0 :
            INT_PriorityDisable_Unsupported(index);
            break;
        case INT_NUMBER_OF_MODULES :
        default :
            break;
    }
}

#endif
