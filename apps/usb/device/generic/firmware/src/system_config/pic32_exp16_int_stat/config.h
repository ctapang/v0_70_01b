/*******************************************************************************
  ADC Data Logger Configuration Header
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    config.h

  Summary:
    ADC data logger demo application configuration header for the explorer-16, 
    PIC32MX, interrupt-driven, static configuration

  Description:
    This file is the ADC data logger demo application configuration header for
    the explorer-16, PIC32MX, interrupt-driven, static configuration.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright © 2011-2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _CONFIG_H    // Guards against multiple inclusion
#define _CONFIG_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/

// Driver configurations

// #include "tmr/config/drv_tmr_config_static.h"
// #include "adc/config/drv_adc_config_static.h"
// #include "usart/config/drv_usart_config_static.h"

/*BSP Configuration header*/

#include "bsp_config.h"

// *****************************************************************************
// *****************************************************************************
// Section: Board Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration for the board.
*/

// TODO


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

/*ADC Driver Configuration*/

#define DRV_ADC_CONFIG_INTERRUPT_MODE

#define DRV_ADC_USE_INTERRUPT_SOURCE_ID         PLIB_INT_SOURCE_ADC_1

#define DRV_ADC_CONFIG_BUILD_TYPE DRV_BUILD_TYPE_STATIC

#define DRV_ADC_CONFIG_OPEN_TYPE DRV_OPEN_TYPE_SINGLE

#define DRV_ADC_STATIC_ID 		1

#define DRV_ADC_CONFIG_MODE	DRV_CONFIG_MODE_ADVANCED

#define DRV_ADC_CONFIG_SUPPORT_CALLBACKS

#define DRV_ADC_CONFIG_CLIENT_MAX_NUMBER                        1

#define DRV_ADC_CONFIG_BUFFER_QUEUE_SLOTS_MAX                   20

#define DRV_ADC_CONFIG_MAX_BUFFER_QUEUE_SLOTS                   1

#define DRV_ADC_CONVERSION_MODE_10BIT

#define DRV_ADC_CONFIG_MAX_NUMBER_OF_CHANNELS                   1

#define DRV_ADC_CONFIG_MAX_NUMBER_OF_SAMPLES_PER_INTERRUPT      1

#define DRV_ADC_CONFIG_MAX_NUMBER_OF_INPUTS                     1

#define DRV_ADC_CONFIG_CONVERSION_TRIGGER_SRC   PLIB_ADC_CONVERSION_TRIGGER_SAMP_CLEAR


/*TMR Driver Configuration*/

#define DRV_TMR_CONFIG_INTERRUPT_MODE

#define DRV_TMR_CONFIG_BUILD_TYPE DRV_BUILD_TYPE_STATIC

#define DRV_TMR_STATIC_ID      1

#define DRV_TMR_CONFIG_MODE	DRV_CONFIG_MODE_ADVANCED

#define DRV_TMR_CONFIG_SUPPORT_CALLBACKS

#define DRV_TMR_CONFIG_MAX_ALARM_OBJECTS                    1

#define DRV_TMR_CONFIG_ALARM_AT_RESOLUTION_OF_BASE

#define DRV_TMR_CONFIG_SINGLE_ALARM_PER_MODULE

#define DRV_TMR_CONFIG_ALARM_TYPE_PERIODIC

#define DRV_TMR_CONFIG_NUMBER_OF_INSTANCES      1

#define DRV_TMR_CONFIG_COUNT_MODE_16BIT

#define DRV_TMR_CONFIG_OPERATION_MODE_SYNC_INTERNAL

#define DRV_TMR_CONFIG_INTERRUPT_SOURCE_ID         PLIB_INT_SOURCE_TIMER_1

#define DRV_TMR_CONFIG_PRESCALE         PLIB_TMR_PRESCALE_TX_VALUE_256

#define DRV_TMR_CONFIG_CLOCK_SOURCE     PLIB_TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK


/*UART Driver Configuration*/

#define DRV_USART_CONFIG_INTERRUPT_MODE

#define DRV_USART_CONFIG_NUMBER_OF_INSTANCES            1

#define DRV_USART_CONFIG_BUILD_TYPE DRV_BUILD_TYPE_STATIC

#define DRV_USART_CONFIG_OPEN_TYPE DRV_OPEN_TYPE_SINGLE

#define DRV_USART_USE_USART_ID      2

#define DRV_USART_STATIC_ID 2

#define DRV_USART_CONFIG_MODE	DRV_CONFIG_MODE_ADVANCED

#define DRV_USART_CONFIG_SUPPORT_CALLBACKS

#define DRV_USART_CONFIG_SUPPORT_OPERATION_MODE_RS232

#define DRV_USART_CONFIG_CLIENT_MAX_NUMBER              1

#define DRV_USART_CONFIG_BUFFER_QUEUE_SLOTS_MAX         2

#define DRV_USART_TX_INTERRUPT_SOURCE_ID                PLIB_INT_SOURCE_USART_2_TRANSMIT

#define DRV_USART_RX_INTERRUPT_SOURCE_ID                PLIB_INT_SOURCE_USART_2_RECEIVE

#define DRV_USART_ERROR_INTERRUPT_SOURCE_ID             PLIB_INT_SOURCE_USART_2_ERROR

#define DRV_USART_CONFIG_BAUD_RATE_CLOCK                (80000000ul/(1 << OSCCONbits.PBDIV))// - PIC32

#define DRV_USART_CONFIG_BAUD_RATE                      9600

#define DRV_USART_CONFIG_SUPPORT_SINGLEBUFFER


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration options for the application
*/

/*Full scale ADC value (10 bit)*/
#define FULL_SCALE_VOLT             1024UL

/*The number of samples App accumulates before avaraging the voltage*/
#define APP_ADC_CONFIG_SAMPLES      10

/*The init message size(displayed on HyperTerminal)*/
#define APP_UART_INIT_MSG_SIZE      90

/*Periodic voltage message size(displayed on HyperTerminal)*/
#define APP_UART_VOLT_DISPLAY_SIZE  12

/*Sampling frequency for ADC*/
#define APP_ADC_SAMPLING_FREQUENCY  10000

/*ADC Error Tolarence*/
#define APP_ADC_ERROR_TOLARENCE     10

/*Timer load values. Values differ for each processor based on the clock settings*/
/*The given count values are valid only if the device config registers are
 programmed as shown below*/
// Explorer 16 Board, XTAL = 8MHz
// PLLIDIV = 2, Freq = 4MHz
// PLLMUL = 20, Freq = 80MHz
// PLLODIV = 1, Freq = 80MHz
// PBDIV = 1,   Freq = 80MHz
// TMR Module I/P = 80MHz
// TMR Prescaler = 1:256 = 312500Hz
// TMR Step = 3.2uS/Count
#define APP_TMR_1S      0x0004C4B4

#define APP_TMR_500mS   0x0002625A

#define APP_TMR_200mS   0x0000F424

#define APP_TMR_100mS   0x00007A12

#define APP_TMR_50mS	0x00003D09

#define APP_TMR_10mS    0x00000C35

#define APP_TMR_1mS     0x00000138

/* The timer id to be used for the application */
#define APP_TMR_ID      TMR_ID_1

/* The ADC module id to be used for the applicaiton */
#define APP_ADC_ID      ADC_ID_1

/* The USART Module id to be used for the application */
#define APP_USART_ID    USART_ID_2

/*UART instance index*/
#define APP_USART_INDEX 0

/*ADC instance index*/
#define APP_ADC_INDEX 0

/*TMR instance index*/
#define APP_TMR_INDEX 0

/*Initial Message displayed on the HyperTerminal*/
#define CURRENT_CONFIG_MSG  "\r\nOnboard Potentiometer Voltage (Volts)\r\nUsing Advanced Static Drivers in Interrupt Mode\r\n"

#define APP_InitInt() APP_InitIntPeripherals()

#endif // _CONFIG_H

/*******************************************************************************
 End of File
*/

