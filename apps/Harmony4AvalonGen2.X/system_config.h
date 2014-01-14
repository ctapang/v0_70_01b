/*******************************************************************************
  MPLAB Harmony Demo Configuration Header

  Company:
    Microchip Technology Incorporated

  File Name:
    system_config.h

  Summary:
    Top-level configuration header file.

  Description:
    This file is the top-level configuration header for the Harmony Demo
    application for the Explorer-16 board with PIC32MX795F512L.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _SYS_CONFIG_H
#define _SYS_CONFIG_H

// processor type
#define __PIC32MX__   1
#define __32MX250F128B__  1

// given all of the #pragma config statements in system_init.c, we get 40MHz for our clock
#define SYS_FREQUENCY 40000000L

#define hwGLOBAL_INTERRUPT_BIT			( 0x01UL )

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_DEVICE_SUPPORT      true

#define DRV_USB_HOST_SUPPORT        false

#define DRV_USB_ENDPOINTS_NUMBER    3

#define DRV_USB_INSTANCES_NUMBER    1

#define DRV_USB_INTERRUPT_MODE    true

#define USB_DEVICE_MAX_INSTANCES    1

#define USB_DEVICE_MAX_CLIENTS      1

#define USB_DEVICE_MAX_FUNCTION_DRIVER  1

#define USB_DEVICE_EP0_BUFFER_SIZE  64

#define USB_DEVICE_CDC_INSTANCES_NUMBER  1

#define DRV_USB_CLIENTS_NUMBER  1

#define USB_DEVICE_HID_INSTANCES_NUMBER  1

#define USB_DEVICE_HID_FUNC_INDEX  0

#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED  6

#define DRV_USB_INDEX               0
#define DRV_USB_PERIPHERAL_ID       USB_ID_1
#define DRV_USB_INTERRUPT_SOURCE    INT_SOURCE_USB_1


// WatchDog timer

#define WDT_PLIB_ID    			WDT_ID_1

// Analog to Digital converter (voltage telemetry)

#define DRV_ADC_INTERRUPT_MODE true

// *****************************************************************************
// *****************************************************************************
// Section: ADC Core Funtionality Configuration Macros
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* ADC hardware instance configuration

  Summary:
    Sets up the maximum number of hardware instances that can be supported.

  Description:
    This macro sets up the maximum number of hardware instances that can be
    supported.

  Remarks:
    Commented out because otherwise drv_adc_client_multi.h gets included.
*/

//#define DRV_ADC_INSTANCES_NUMBER            1


// *****************************************************************************
/* ADC Maximum Number of Clients

  Summary:
    Selects the miximum number of clients.

  Description:
    This definition selectd the maximum number of clients that the ADC driver can
    support at run time.

  Remarks:
    Commented out because otherwise drv_adc_client_multi.h gets included.

*/

//#define DRV_ADC_CLIENTS_NUMBER            1


// *****************************************************************************
/* ADC Static Index Selection

  Summary:
    ADC static index selection.

  Description:
    ADC static index selection for the driver object reference.

  Remarks:
    This index is required to make a reference to the driver object.
*/

#define DRV_ADC_INDEX                            DRV_ADC_INDEX_0


// *****************************************************************************
/* ADC Interrupt And Polled Mode Operation Control

  Summary:
    Controls operation of the driver in the interrupt or polled mode.

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro are:
    - true - Select if interrupt mode of adc operation is desired
    - false - Select if polling mode of adc operation is desired
    Not defining this option to true or false will result in a build error.

  Remarks:
    None.
*/

#define DRV_ADC_INTERRUPT_MODE      true


// *****************************************************************************
/* ADC Internal buffer size

  Summary:
    Define the internal buffer size.

  Description:
    This macro defines the internal buffer size.

  Remarks:
    None.
*/

#define DRV_ADC_INTERNAL_BUFFER_SIZE             2

#define _ADC_EXISTS_CONVERSION_RESULT_IN_BUFFER_ARRAY 1


// *****************************************************************************
/* ADC Auto Sampling Enable

  Summary:
    Rnable the suto-sampling feature of the ADC.

  Description:
    This macro enables the auto-sampling feature of the ADC.  This macro can take
    the following values:
    - true - Enables the auto-sampling feature of the ADC
    - false - Disables the auto-sampling feature of the ADC
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the instance
  Remarks:
    None.
*/

#define DRV_ADC_AUTO_SAMPLING_ENABLE             true


// *****************************************************************************
/* ADC Alternate Input Sampling Enable

  Summary:
    Enable the alternate input sampling feature of the ADC.

  Description:
    This macro enables the alternate input sampling feature of the ADC. This macro can
    take the following values:
    - true - Enables the alternate Input sampling feature of the ADC
    - false - Disables the alternate Input sampling feature of the ADC
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the instance

  Remarks:
    None.
*/

#define DRV_ADC_ALTERNATE_INPUT_SAMPLING_ENABLE        false


// *****************************************************************************
/* ADC Stop on conversion Enable

  Summary:
    Enable the stop on conversion feature of the ADC.

  Description:
    This macro enables the stop on conversion feature of the ADC.  This macro can
    take the following values:
    - true - Enables the ADC to stop on conversion
    - false - Disables the ADC to stop on conversion
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the instance

  Remarks:
    None.
*/

#define DRV_ADC_STOP_ON_CONVERSION_ENABLE        false


// *****************************************************************************
// *****************************************************************************
// Section: Initialization Overrides
// *****************************************************************************
// *****************************************************************************
/* This section defines the initialization overrides */

// *****************************************************************************
/* ADC PLIB ID Selection

  Summary:
    ADC PLIB ID Selection

  Description:
    This macro selects the ADC PLIB ID Selection. This is an intialization
    override of the adcID member of the intialization configuration.

  Remarks:
    None.

*/

#define DRV_ADC_PERIPHERAL_ID                     ADC_ID_1


// *****************************************************************************
/* ADC Interrupt Source

  Summary:
    Defines the interrupt source of the static driver.

  Description:
    Macro to define the interrupt source of the static driver.

  Remarks:
    Refer to the Interrupt Peripheral Library document for more information on
    the PLIB_INT_SOURCE enumeration.
*/

#define DRV_ADC_INTERRUPT_SOURCE            INT_SOURCE_ADC_1


// *****************************************************************************
/* Samples per Interrupt

  Summary:
    Define the sample per interrupt.

  Description:
    This macro defines the samples per interrupt of the ADC driver. This
    provides static override of the dynamic selection of the sample per
    interrupt. If this macro is defined, this will be used for setting up the
    samples per interrupt and not the samples per interrupt value provided by
    DRV_ADC_INIT.

  Remarks:
    Select this size based on the device available and the number of samples
    that are required to form a set.

*/

#define DRV_ADC_SAMPLES_PER_INTERRUPT       2


// *****************************************************************************
/* ADC Acquisition Time

  Summary:
    Defines the acquisition time.

  Description:
    This macro defines the acquistition time of the ADC driver. This provides
    static override of the dynamic selection of the acquisition time. If this
    macro is defined, this will be used for setting up the acquisition time
    and not the acquisition time value provided by DRV_ADC_INIT.

  Remarks:
    None.

*/

#define DRV_ADC_ACQUISITION_TIME            ADC_ACQUISITION_TIME_4_TAD


// *****************************************************************************
/* ADC Voltage Reference

  Summary:
    Defines the voltage reference.

  Description:
    This macro defines the voltage reference of the ADC driver. This provides
    static override of the dynamic selection of the voltage reference. If this
    macro is defined, this will be used for setting up the voltage reference
    and not the voltage reference value provided by DRV_ADC_INIT.

  Remarks:
    None.

*/

#define DRV_ADC_VOLTAGE_REFERENCE           ADC_VREF_POS_TO_VDD_VREF_NEG_TO_VSS


// *****************************************************************************
/* ADC Data Output Format

  Summary:
    Defines the data output format.

  Description:
    This macro defines the data output format for the ADC driver. This
    provides static override of the dynamic selection of the data output format.
    If this macro is defined, this will be used for setting up the data output
    format and not the data output format value provided by DRV_ADC_INIT.

  Remarks:
    None.

*/

#define DRV_ADC_RESULT_FORMAT          ADC_RESULT_FORMAT_INTEGER_16BIT


// *****************************************************************************
/* Conversion Trigger Source

  Summary:
    Defines the conversion trigger source.

  Description:
    This macro defines the conversion trigger source for the ADC driver. This
    provides static override of the dynamic selection of the conversion trigger
    source. If this macro is defined, this will be used for setting up the
    conversion trigger source and not the conversion trigger source value
    provided by DRV_ADC_INIT.

  Remarks:
    None.

*/

#define DRV_ADC_CONVERSION_TRIGGER_SOURCE   ADC_CONVERSION_TRIGGER_INTERNAL_COUNT


// *****************************************************************************
/* ADC Conversion Clock Source

  Summary:
    Defines the conversion clock source.

  Description:
    This macro defines the conversion clock source for the ADC driver. This
    provides static override of the dynamic selection of the conversion clock
    source. If this macro is defined, this will be used for setting up the
    conversion clock source and not the conversion clock source value provided
    by DRV_ADC_INIT.

  Remarks:
    None.

*/

#define DRV_ADC_CONVERSION_CLOCK_SOURCE     ADC_CLOCK_SRC_SYSTEM_CLOCK


// *****************************************************************************
/* ADC Conversion Clock

  Summary:
    Defines the conversion clock.

  Description:
    This macro defines the conversion clock for the ADC driver. This provides
    static override of the dynamic selection of the conversion clock. If this
    macro is defined, this will be used for setting up the conversion clock
    and not the conversion clock value provided by DRV_ADC_INIT.

  Remarks:
    None.
*/

#define DRV_ADC_CONVERSION_CLOCK_PRESCALER  ADC_CONV_CLOCK_4_TCY


// *****************************************************************************
/* ADC Analog input channel

  Summary:
    Defines the analog input channel.

  Description:
    This macro defines the analog input channel for the ADC driver. This
    provides static override of the dynamic selection of the analog input. If
    this macro is defined, this will be used for setting up the analog input
    and not the analog input value provided by DRV_ADC_INIT.

  Remarks:
    None.
*/

#define DRV_ADC_ANALOG_INPUT                ADC_INPUT_POSITIVE_AN2


// *****************************************************************************
/* ADC power state configuration

  Summary:
    Controls the power state of the ADC.

  Description:
    This macro controls the power state of the ADC.

  Remarks:
    Note: This feature may not be available in the device or the ADC module
    selected.
*/

#define DRV_ADC_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// Timer
#define DRV_TMR_COUNT_WIDTH 32
#define SYS_TMR_MAX_PERIODIC_EVENTS 4
#define DRV_TMR_INDEX 0
#define DRV_TMR_INTERRUPT_MODE 1
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4
#define DRV_TMR_ALARM_ENABLE 1
#define DRV_TMR_ALARM_PERIODIC 1


// *****************************************************************************
// Section: SPI Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_SPI_INSTANCES_NUMBER                    2

#define DRV_SPI_CLIENTS_NUMBER                      1

#define DRV_SPI_INTERRUPT_MODE                      true

#define DRV_SPI_PORTS_REMAP_USAGE                   true

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK

#define DRV_SPI_CLIENT_SPECIFIC_CONTROL             1


// *****************************************************************************
// *****************************************************************************
// Section: System Clock Service Configuration
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_CONFIG_USBPLL_ENABLE              true

#define SYS_CLK_PRIMARY_CLOCK                     80000000L

#define SYS_CLK_SECONDARY_CLOCK                   80000000

#define SYS_CLK_CLOCK_CONFIG_ERROR                10

#define SYS_CLK_CONFIG_USBPLL_DIVISOR             2

#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR         2

#define SYS_CLK_CONFIG_SYSCLK_OP_DIVISOR          1

#define SYS_CLK_ON_WAIT_IDLE                      1

#define SYS_CLK_ON_WAIT_SLEEP                     0

#define SYS_CLK_EXTERNAL_CLOCK                    4000000


// *****************************************************************************
// *****************************************************************************
// Section: System Timer Service Configuration
// *****************************************************************************
// *****************************************************************************




#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/


