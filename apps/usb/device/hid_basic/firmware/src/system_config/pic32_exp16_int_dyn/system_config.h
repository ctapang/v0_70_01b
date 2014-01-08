/*******************************************************************************
  ADC Data Logger Demo Configuration Header
  
  Company:      
    Microchip Technology Inc.
  
  File Name:   
    system_config.h

  Summary:
    Top-level configuration header for the ADC data logger demo application for
    the explorer-16, PIC32MX, interrupt-driven, dynamic configuration

  Description:
    This file is the top-level configuration header for the ADC data logger demo 
    application for the explorer-16, PIC32MX, interrupt-driven, dynamic 
    configuration.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/

#include "bsp_config.h"

// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration options for the application
*/

// *****************************************************************************
/* OSC Clock

  Summary:
    Defines the OSC clock

  Description:
    This constant defines the OSC clock.

  Remarks:
    This is a placeholder implementation of the system services.
*/

#define SYS_CLK_CONFIG_OSC_CLOCK_FREQUENCY                       8000000


// *****************************************************************************
/* Peripheral Clock

  Summary:
    Defines the peripheral clock

  Description:
    This constant defines the peripheral clock.

  Remarks:
    This is a placeholder implementation of the system services.
*/

#define SYS_CLK_CONFIG_PERIPHERAL_CLOCK_FREQUENCY                       80000000


// ****************************************************************************
/* Timer Period Values

  Summary:
    Timer period values necessary to achieve desired event timing

  Description:
    These constants define the timer period values necessary to achive the
    desired timer events.

  Remarks:
    Timer values differ for each processor based on the clock settings.  The
    given count values are valid only if the device config registers are
    programmed as shown below:

    Explorer 16 Board, XTAL = 8MHz
    PLLIDIV = 2, Freq = 4MHz
    PLLMUL = 20, Freq = 80MHz
    PLLODIV = 1, Freq = 80MHz
    PBDIV = 1,   Freq = 80MHz
    TMR Module I/P = 80MHz
    TMR Prescaler = 1:256 = 312500Hz
    TMR Step = 3.2uS/Count
*/

#define APP_TMR_1S      0x0004C4B4

#define APP_TMR_500mS   0x0002625A

#define APP_TMR_200mS   0x0000F424

#define APP_TMR_100mS   0x00007A12

#define APP_TMR_50mS    0x00003D09

#define APP_TMR_10mS    0x00000C35

#define APP_TMR_1mS     0x00000138


// ****************************************************************************
/* APP_FULL_SCALE_VOLTS

  Summary:
    The maximum voltage the ADC is capable of reading.

  Description:
    This constatnt defines the maximum voltage multiplied by 100,
    the ADC is caplble of reading. 500 suggests that the onboard ADC can convert
    maximum of 5V into a digital value.
*/

#define APP_FULL_SCALE_VOLTS            (BSP_POTENTIOMETER_MAX_VOLTS - BSP_POTENTIOMETER_MIN_VOLTS) * 100


// ****************************************************************************
/* APP_FULL_SCALE_ADC

  Summary:
    Full scale ADC value (10 bit)

  Description:
    This constatnt defines the maximum digital representation of the analog
    voltage.
*/

#define APP_FULL_SCALE_ADC              (DRV_ADC_SampleMaxGet(appData.adcHandle) - DRV_ADC_SampleMinGet(appData.adcHandle))


// ****************************************************************************
/* APP_ADC_CONFIG_SAMPLES_NUMBER

  Summary:
    The number of samples App accumulates before avaraging the voltage

  Description:
    This constatnt defines the number of potentiometer voltage samples
    accumulated by the application before avaraging them.
*/

#define APP_ADC_CONFIG_SAMPLES_NUMBER      10


// ****************************************************************************
/* APP_UART_INIT_MSG_SIZE

  Summary:
    The init message size

  Description:
    This constatnt defines the size of the initial message displayed by the
    application.
*/

#define APP_UART_INIT_MSG_SIZE      95


// ****************************************************************************
/* APP_UART_VOLT_DISPLAY_SIZE

  Summary:
    Periodic voltage message size

  Description:
    This constatnt defines the size of the periodic voltage message displayed
    by the application.
*/

#define APP_UART_VOLT_DISPLAY_SIZE  12


// ****************************************************************************
/* APP_ADC_CONFIG_INPUTS

  Summary:
    The inputs to scan for the ADC

  Description:
    This constatnt defines the inputs to scan for ADC.
*/

#define APP_ADC_CONFIG_INPUTS              BSP_POTENTIOMETER_INPUT


// ****************************************************************************
/* APP_TMR_ID

  Summary:
    The timer ID to be used for the application

  Description:
    This constatnt defines the the PLIB ID for the Timer used.
*/

#define APP_TMR_ID      TMR_ID_1


// ****************************************************************************
/* APP_ADC_ID

  Summary:
    The ADC module ID to be used for the application

  Description:
    This constatnt defines the the PLIB ID for the ADC used.
*/

#define APP_ADC_ID      ADC_ID_1


// ****************************************************************************
/* APP_USART_ID

  Summary:
    The USART Module ID to be used for the application

  Description:
    This constatnt defines the the PLIB ID for the USART used.
*/

#define APP_USART_ID    BSP_RS232_PORT


// ****************************************************************************
/* APP_USART_INDEX

  Summary:
    USART driver instance index used for the application

  Description:
    This constatnt defines the the module index for the Timer used.
*/

#define APP_USART_INDEX DRV_USART_INDEX_0


// ****************************************************************************
/* APP_ADC_INDEX

  Summary:
    ADC driver instance index used for the application

  Description:
    This constatnt defines the the module index for the ADC used.
*/

#define APP_ADC_INDEX   DRV_ADC_INDEX_0


// ****************************************************************************
/* APP_TMR_INDEX

  Summary:
    ADC driver instance index used for the application

  Description:
    This constatnt defines the the module index for the USART used.
*/

#define APP_TMR_INDEX   DRV_TMR_INDEX_0


// ****************************************************************************
/* APP_TMR_INT_SOURCE

  Summary:
    Interrupt source ID for Timer.

  Description:
    This constant defines the interrupt source ID for timer.
*/

#define APP_TMR_INT_SOURCE      PLIB_INT_SOURCE_TIMER_1


// ****************************************************************************
/* APP_ADC_INT_SOURCE

  Summary:
    Interrupt source ID for ADC.

  Description:
    This constant defines the interrupt source ID for ADC.
*/

#define APP_ADC_INT_SOURCE      PLIB_INT_SOURCE_ADC_1


// ****************************************************************************
/* APP_USART_INT_SOURCE_TX

  Summary:
    Transmit Interrupt source ID for USART.

  Description:
    This constant defines the TX interrupt source ID for USART.
*/

#define APP_USART_INT_SOURCE_TX    PLIB_INT_SOURCE_USART_2_TRANSMIT


// ****************************************************************************
/* APP_USART_INT_SOURCE_RX

  Summary:
    Receive Interrupt source ID for USART.

  Description:
    This constant defines the RX interrupt source ID for USART.
*/

#define APP_USART_INT_SOURCE_RX    PLIB_INT_SOURCE_USART_2_RECEIVE


// ****************************************************************************
/* APP_USART_INT_SOURCE_ERROR

  Summary:
    Error Interrupt source ID for USART.

  Description:
    This constant defines the error interrupt source ID for USART.
*/

#define APP_USART_INT_SOURCE_ERROR    PLIB_INT_SOURCE_USART_2_ERROR


// ****************************************************************************
/* APP_CURRENT_CONFIG_MSG

  Summary:
    Initial message displayed via the USART

  Description:
    This constant defines the initial message displayed by the application.

  Remarks:
    The size of this constant is defined by the constant APP_UART_INIT_MSG_SIZE.
*/

#define APP_CURRENT_CONFIG_MSG  "\r\nOnboard Potentiometer Voltage (Volts)\r\n" \
                                "Using Advanced Dynamic Drivers in Interrupt Mode\r\n"


// ****************************************************************************
/* APP_VOLT_MSG

  Summary:
    Periodic voltage message via the USART

  Description:
    This constant defines the periodic voltage message displayed by the
    application.

 Remarks:
    The size of this constant is defined by the constant APP_UART_VOLT_DISPLAY_SIZE.
*/

#define APP_VOLT_MSG    "\r\nVol= .  V"


// ****************************************************************************
/* APP_VOLT_INSERT_POS_0

  Summary:
    Position of the voltage one's digit in the APP_VOLT_MSG

  Description:
    This constant defines the Position of the voltage one's digit in the
    APP_VOLT_MSG. In this position the first voltage digit gets appended for
    display. If the current volatge is 3.67Volts, 3 gets appended in the
    APP_VOLT_MSG at the position defined by this constant.
*/

#define APP_VOLT_INSERT_POS_0   6


// ****************************************************************************
/* APP_VOLT_INSERT_POS_1

  Summary:
    Position of tenths digit in the APP_VOLT_MSG

  Description:
    This constant defines the Position of the voltage's tenths digit in the
    APP_VOLT_MSG. In this position the tenths voltage digit gets appended for
    display. If the current volatge is 3.67Volts, 6 gets appended in the
    APP_VOLT_MSG at the position defined by this constant.
*/

#define APP_VOLT_INSERT_POS_1   8


// ****************************************************************************
/* APP_VOLT_INSERT_POS_2

  Summary:
    Position of hundredths digit in the APP_VOLT_MSG

  Description:
    This constant defines the Position of the voltage's hundredths digit in the
    APP_VOLT_MSG. In this position the hundredths voltage digit gets appended for
    display. If the current volatge is 3.67Volts, 7 gets appended in the
    APP_VOLT_MSG at the position defined by this constant.
*/

#define APP_VOLT_INSERT_POS_2   9


// *****************************************************************************
// *****************************************************************************
// Section: ADC Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* ADC interrupt and polled/operation control

   Summary:
    Configures the ADC driver for polled/interrupt modes.

   Description:
    This constant controls the operation of the driver in the interrupt or polled
    modes of operation.
    - DRV_ADC_CONFIG_TASKS_MODE_INTERRUPT_ENABLE    true
        ADC module is configured for polled mode
    - DRV_ADC_CONFIG_TASKS_MODE_INTERRUPT_ENABLE    false
        ADC module is configured for interrupt mode

   Remarks:
    Only one of the above mentioned configuration should be defined.
*/

#define DRV_ADC_CONFIG_TASKS_MODE_INTERRUPT_ENABLE    true


// *****************************************************************************
/* ADC driver objects configuration

  Summary
    Sets up the maximum number of hardware instances that can be supported

  Description
    Sets up the maximum number of hardware instances that can be supported

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_DRIVER_OBJECTS_NUMBER 1


// *****************************************************************************
/* ADC Client Count Configuration

  Summary
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Description
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_CLIENT_OBJECTS_NUMBER 1


// *****************************************************************************
/* ADC Instances

   Summary
    Configures the number of ADC Instances

   Description
    Configures the number of ADC Instances
	
   Remarks:
    None.
*/

#define DRV_ADC_CONFIG_NUMBER_OF_INSTANCES                              1


// *****************************************************************************
/* ADC Static PLIB ID Selection

   Summary
    ADC Static PLIB ID Selection

   Description
    ADC Static PLIB ID Selection

   Remarks:
    None.
*/

#define DRV_ADC_CONFIG_INIT_PLIB_ID                              APP_ADC_ID


// *****************************************************************************
/* ADC Interrupt Source

  Summary:
    Macro to define the interrupt source in case of static driver

  Description:
    Macro to define the interrupt source in case of static driver

  Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
*/

#define DRV_ADC_CONFIG_INIT_INTERRUPT_SOURCE            APP_ADC_INT_SOURCE


// ****************************************************************************
/* DRV_ADC_CONFIG_INIT_ANALOG_INPUT

  Summary:
    The inputs to scan for the ADC

  Description:
    This constatnt defines the inputs to scan for ADC.
*/

#define DRV_ADC_CONFIG_INIT_ANALOG_INPUT              APP_ADC_CONFIG_INPUTS


// *****************************************************************************
/* ADC Auto Sampling Enable

  Summary:
    Macro to enable the Auto sampling feature of the ADC

  Description:
    This macro enables the Auto sampling feature of the ADC.  This macro can take
    following values:
    - true - Enables the auto sampling feature of adc
    - false - Disables the auto sampling feature of adc
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the
             instance.
  Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_AUTO_SAMPLING_ENABLE             false


// *****************************************************************************
/* ADC Alternate Input Sampling Enable

  Summary:
    Macro to enable the alternate Input sampling feature of the ADC

  Description:
    This macro enables the alternate Input sampling feature of the ADC. This macro can
    take following values:
    - true - Enables the alternate Input sampling feature of adc
    - false - Disables the alternate Input sampling feature of adc
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the
             instance.

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_ALTERNATE_INPUT_SAMPLING_ENABLE        false


// *****************************************************************************
/* ADC Stop on conversion Enable

  Summary:
    Macro to enable the stop on conversion feature of the ADC

  Description:
    This macro enables the stop on conversion feature of the ADC.  This macro can
    take following values:
    - true - Enables the adc to stop on conversion
    - false - Disables the adc to stop on conversion
    - DRV_CONFIG_NOT_SUPPORTED - When the feature is not supported on the
             instance.

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_STOP_ON_CONVERSION_ENABLE        false


// *****************************************************************************
/* Samples per Interrupt

  Summary:
    Macro to define the sample per interrupt

  Description:
    This macro defines the samples per interrupt of the ADC driver. This
    provides static override of the dynamic selection of the sample per
    interrupt. If this macro is defined, this will be used for setting up the
    samples per interrupt and not the samples per interrupt value provided by
    DRV_ADC_INIT.

  Remarks:
    Select this size based on the part available and the number of samples
    that are required to from a set.

*/

#define DRV_ADC_CONFIG_INIT_SAMPLES_PER_INTERRUPT                  1


// *****************************************************************************
/* ADC Internal buffer size

  Summary:
    Macro to define the internal buffer size.

  Description:
    This macro defines the internal buffer size.

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_INTERNAL_BUFFER_SIZE                   1


// *****************************************************************************
/* ADC Acquisition Time

   Summary:
    Macro to define the acquisition time

   Description:
    This macro defines the acquistition time of the ADC driver. This provides
    static override of the dynamic selection of the acquisition time. If this
    macro is defined, this will be used for setting up the acquisition time
    and not the acquisition time value provided by DRV_ADC_INIT.

   Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_ACQUISITION_TIME PLIB_ADC_ACQUISITION_TIME_20_TAD


// *****************************************************************************
/* ADC Voltage Reference

   Summary:
    Macro to define the voltage reference

   Description:
    This macro defines the voltage reference of the ADC driver. This provides
    static override of the dynamic selection of the voltage reference. If this
    macro is defined, this will be used for setting up the voltage reference
    and not the voltage reference value provided by DRV_ADC_INIT.

   Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_VOLTAGE_REF  PLIB_ADC_VREF_POS_TO_VDD_VREF_NEG_TO_VSS


// *****************************************************************************
/* ADC Data Output Format

   Summary:
    Macro to define the data output format

   Description:
    This macro defines the data output format for the ADC driver. This
    provides static override of the dynamic selection of the data output format.
    If this macro is defined, this will be used for setting up the data output
    format and not the data output format value provided by DRV_ADC_INIT.

   Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_DATA_OUTPUT_FORMAT   PLIB_ADC_OUTPUT_FORMAT_INTEGER_16BIT


// *****************************************************************************
/* Conversion Trigger Source

   Summary:
    Macro to define the conversion trigger source

   Description:
    This macro defines the conversion trigger source for the ADC driver. This
    provides static override of the dynamic selection of the conversion trigger
    source. If this macro is defined, this will be used for setting up the
    conversion trigger source and not the conversion trigger source value
    provided by DRV_ADC_INIT.

   Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_CONVERSION_TRIGGER_SOURCE    PLIB_ADC_CONVERSION_TRIGGER_INTERNAL_COUNT


// *****************************************************************************
/* ADC Conversion Clock Source

   Summary:
    Macro to define the conversion clock source

   Description:
    This macro defines the conversion clock source for the ADC driver. This
    provides static override of the dynamic selection of the conversion clock
    source. If this macro is defined, this will be used for setting up the
    conversion clock source and not the conversion clock source value provided
    by DRV_ADC_INIT.

   Remarks:
    None

 */

#define DRV_ADC_CONFIG_INIT_CONVERSION_CLOCK_SOURCE  PLIB_ADC_CLOCK_SRC_SYSTEM_CLOCK


// *****************************************************************************
/* ADC Conversion Clock

  Summary:
    Macro to define the conversion clock

  Description:
    This macro defines the conversion clock for the ADC driver. This provides
    static override of the dynamic selection of the conversion clock. If this
    macro is defined, this will be used for setting up the conversion clock
    and not the conversion clock value provided by DRV_ADC_INIT.

  Remarks:
    None
*/

#define DRV_ADC_CONFIG_INIT_CONVERSION_CLOCK_PRESCALER  PLIB_ADC_CONV_CLOCK_20_TCY


// *****************************************************************************
/* ADC power state configuration

  Summary:
    Macro controls power state of the ADC

  Description:
    This macro controls the power state of the ADC

  Remarks:
    Note: This feature may not be available in the device or the ADC module
    selected
*/

#define DRV_ADC_CONFIG_INIT_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP


// *****************************************************************************
// *****************************************************************************
// Section: TMR Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* TMR Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is
    - true - Select if interrupt mode of timer operation is desired
    - false - Select if polling mode of timer operation is desired.
    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_TMR_CONFIG_TASKS_MODE_INTERRUPT_ENABLE          true


// *****************************************************************************
/* TMR driver objects configuration

  Summary
    Sets up the maximum number of hardware instances that can be supported

  Description
    Sets up the maximum number of hardware instances that can be supported

  Remarks:
    None
*/

#define DRV_TMR_CONFIG_DRIVER_OBJECTS_NUMBER 1


// *****************************************************************************
/* TMR Client Count Configuration

  Summary
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Description
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Remarks:
    None
*/

#define DRV_TMR_CONFIG_CLIENT_OBJECTS_NUMBER 1


// *****************************************************************************
/* TMR Static PLIB ID Selection

   Summary
    TMR Static PLIB ID Selection

   Description
    TMR Static PLIB ID Selection

   Remarks:
    Note: Some devices also support TMR_ID_0
*/

#define DRV_TMR_CONFIG_INIT_PLIB_ID                              APP_TMR_ID


// *****************************************************************************
/* TMR Interrupt Source

   Summary:
    Macro to define the interrupt source in case of static driver

   Description:
    Macro to define the interrupt source in case of static driver

   Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
 */

#define DRV_TMR_CONFIG_INIT_INTERRUPT_SOURCE                     APP_TMR_INT_SOURCE


// *****************************************************************************
/* TMR mode configuration

  Summary:
    Macro controls mode of the TMR

  Description:
    This macro controls the mode of the TMR, it selects that the timer needs
    to support 8 bit, 16 bit or 32 bit mode. The acceptable values of this
    configuration is
         - 8, (Use this for 8 bit timers)
         - 16 (Use this for 16 bit timers)
         - 32 (Use this for 32 bit timers)

  Remarks:
    This is a Mandatory config option, which enables the TMR count width.
*/

#define DRV_TMR_CONFIG_TIMER_MODE_SELECT        16


// *****************************************************************************
/* TMR Operating mode configuration

   Summary:
    Macro controls Operating mode of the TMR

   Description:
    This macro controls the Operating mode of the TMR
    It takes in one of the possible values of the enumeration
    DRV_TMR_SYNC_MODE

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
*/

#define DRV_TMR_CONFIG_INIT_SYNC_MODE    DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL


// *****************************************************************************
/* TMR Value Initial Value

   Summary:
    TMR value for an overflow or a period match based timer

   Description:
    TMR value for an overflow or a period match based timer

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Note: User is required to give the count value. Driver will internally
    adjust the value as required for the TMR hardware based on the overflow or
    period match functionality
*/

#define DRV_TMR_CONFIG_INIT_INITIAL_COUNT    APP_TMR_10mS


// *****************************************************************************
/* TMR Clock Source

   Summary:
    TMR module clock source selection

   Description:
    TMR module clock source selection, based on the enumeration


   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Refer to the processor peripheral header for more information
*/

#define DRV_TMR_CONFIG_INIT_CLOCK_SOURCE     PLIB_TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK


// *****************************************************************************
/* TMR Prescale

   Summary:
    TMR module prescale value

   Description:
    TMR module prescale value

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Refer to the processor peripheral header for more information
*/

#define DRV_TMR_CONFIG_INIT_PRESCALE     PLIB_TMR_PRESCALE_TX_VALUE_256


// *****************************************************************************
/* Selecting the alarm functionality

  Summary:
    Alarm Functionality

  Description:
    This feature enables the alarm functionality inside the TMR driver.

   Remarks:
    This is an additional feature
*/

#define DRV_TMR_CONFIG_OPT_ALARM


// *****************************************************************************
/* Alarm type configuration option for periodic alarm

  Summary:
    Alarm type configuration

  Description:
    This value, if used enables Alarm type
    - DRV_TMR_CONFIG_OPT_ALARM_PERIODIC    false - Periodic Alarm

   Remarks:
    Continuous or a periodic alarm
*/

#define DRV_TMR_CONFIG_OPT_ALARM_PERIODIC    true


// *****************************************************************************
/* TMR alarm Callback notification Configuration

   Summary
    Sets up notification mechanism in the TMR driver through alarms

   Description
    Sets up the notification mechanism in the TMR driver alarms
    When this is defined the driver will call the callback functions if
    registered when the transactions are complete.

   Remarks:
    None
*/

#define DRV_TMR_CONFIG_OPT_ALARM_CALLBACKS


// *****************************************************************************
/* TMR post scale configuration

   Summary:
    Macro controls post scale of the TMR

   Description:
    This macro controls the post scale of the TMR

   Remarks:
    Note: This feature may not be available in the device or the TMR module
    selected
*/

#define DRV_TMR_CONFIG_INIT_POSTSCALE_SELECT 0


// *****************************************************************************
/* TMR power state configuration

  Summary:
    Macro controls power state of the TMR

  Description:
    This macro controls the power state of the TMR

  Remarks:
    Note: This feature may not be available in the device or the TMR module
    selected
*/

#define DRV_TMR_CONFIG_INIT_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP


// *****************************************************************************
// *****************************************************************************
// Section: USART Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* USART interrupt/polled Mode operation control

   Summary:
    Configures the USART driver for polled/interrupt modes.

   Description:
    This constant controls the operation of the driver in the interrupt or polled
    modes of operation.
    - DRV_USART_CONFIG_TASKS_MODE_POLLING
        USART module is configured for polled mode
    - DRV_USART_CONFIG_TASKS_MODE_INTERRUPT
        USART module is configured for interrupt mode

   Remarks:
    Only one of the above mentioned configuration should be defined.
*/

#define DRV_USART_CONFIG_TASKS_MODE_INTERRUPT_ENABLE        true


// *****************************************************************************
/* USART driver objects configuration

  Summary
    Sets up the maximum number of hardware instances that can be supported

  Description
    Sets up the maximum number of hardware instances that can be supported

  Remarks:
    None
*/

#define DRV_USART_CONFIG_DRIVER_OBJECTS_NUMBER 1


// *****************************************************************************
/* USART Client Count Configuration

  Summary
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Description
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Remarks:
    None
*/

#define DRV_USART_CONFIG_CLIENT_OBJECTS_NUMBER 1


// *****************************************************************************
/* USART Instances

   Summary
    Configures the number of USART Instances

   Description
    Configures the number of USART Instances
	
   Remarks:
    None.
*/

#define DRV_USART_CONFIG_NUMBER_OF_INSTANCES                              1


// *****************************************************************************
/* USART Static PLIB ID Selection

   Summary
    USART  Static PLIB ID Selection

   Description
    USART  Static PLIB ID Selection
*/

#define DRV_USART_CONFIG_INIT_PLIB_ID                       APP_USART_ID


// *****************************************************************************
/* USART transmit interrupt Source

   Summary:
    Macro to define the USART transmit interrupt source in case of static driver

   Description:
    This constant defines the USART transmit interrupt source in case of static
    driver

   Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
 */

#define DRV_USART_CONFIG_INIT_INTERRUPT_SOURCE_TX           APP_USART_INT_SOURCE_TX


// *****************************************************************************
/* USART receive interrupt Source

   Summary:
    Macro to define the USART receive interrupt source in case of static driver

   Description:
    This constant defines the USART receive interrupt source in case of static
    driver

   Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
 */

#define DRV_USART_CONFIG_INIT_INTERRUPT_SOURCE_RX           APP_USART_INT_SOURCE_RX


// *****************************************************************************
/* USART error interrupt Source

   Summary:
    Macro to define the USART error interrupt source in case of static driver

   Description:
    This constant defines the USART error interrupt source in case of static
    driver

   Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
 */

#define DRV_USART_CONFIG_INIT_INTERRUPT_SOURCE_ERROR        APP_USART_INT_SOURCE_ERROR


// *****************************************************************************
/* Hand Shake Mode

  Summary:
    The handshake mode used in the communication.

  Description:
    This constant defines the handshake mode used.
*/

#define DRV_USART_CONFIG_INIT_HANDSHAKE_MODE                DRV_USART_CONFIG_INIT_HANDSHAKE_MODE_NONE


// *****************************************************************************
/* Line Control Mode - 8N1

  Summary:
    Macro defines the line control mode as 8 data bits, no parity and 1 stop bit

  Description:
    This macro defines the line control mode as 8 data bits, no parity and 1
    stop bit. It provides a static override of the initialization configuration
    of the line control mode.
*/

#define DRV_USART_CONFIG_INIT_LINE_CONTROL                  DRV_USART_CONFIG_INIT_LINE_CONTROL_8N1


// *****************************************************************************
/* USART Baud Rate configuration

   Summary:
    Macro controls operation of the driver for Baud rate configuration

   Description:
    This macro controls the operation of the driver for Baud rate configuration
*/

#define DRV_USART_CONFIG_INIT_BAUD_RATE                     9600


// *****************************************************************************
/* USART RS232 Suppport

   Summary
    Enables the support of the RS 232 mode in all instances of the peripheral.

   Description
    This macro controls support of the RS 232 mode in all instances of the
    peripheral. If the macro is defined, the RS 232 mode is
    supported on all peripherals. If the macro is not defined, the
    RS 232 mode is not supported by the driver.

   Remarks:
    None
*/

#define DRV_USART_CONFIG_INIT_OPERATION_MODE                DRV_USART_CONFIG_INIT_OPERATION_MODE_RS232


// *****************************************************************************
/* USART Byte mode internal buffer Tx size configuration

  Summary:
    Macro controls operation of the driver for defining the size of the Tx buffer

  Description:
    This macro controls the operation of the driver for defining the size of the Tx buffer
*/

#define DRV_USART_CONFIG_BYTE_Q_SIZE_TX                 30


// *****************************************************************************
/* USART Byte mode internal buffer Rx size configuration

  Summary:
    Macro controls operation of the driver for defining the size of the Rx buffer

  Description:
    This macro controls the operation of the driver for defining the size of the Rx buffer


*/

#define DRV_USART_CONFIG_BYTE_Q_SIZE_RX                 1


// *****************************************************************************
/* Stop In Idle disable

  Summary:
    stop in idle is disabld.

  Description:
    stop in idle is disabld.


*/

#define DRV_USART_CONFIG_INIT_POWER_STATE                   SYS_MODULE_POWER_IDLE_STOP

// *****************************************************************************
/* Wake on start disable

  Summary:
    Macro configures that the peripheral should not wake up on start

  Description:
    This macro configures that the peripheral should not wake up on start.
*/

#define DRV_USART_CONFIG_INIT_WAKE_ON_START_ENABLE          false

// *****************************************************************************
/* Auto Baud disable

  Summary:
    Macro configures disables the auto baud.

  Description:
    This macro configures disables the auto baud. This is a static override of
    initialization parameter.
*/

#define DRV_USART_CONFIG_INIT_AUTO_BAUD_ENABLE              false


#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

