/*******************************************************************************
  Clock System Service Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk.h

  Summary:
    API for the Clock System Service.

  Description:
    This file contains the interface definition for the Clock System
    Service.  It provides a way to interact with the Clock subsystem to
    manage the timing requests supported by the system.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _SYS_CLK_H
#define _SYS_CLK_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "src/sys_clk_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: SYS Clock Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/*  Peripherals Clocks enumeration (PIC32MZ only)

  Summary:
	Lists the available peripheral clocks.

  Description:
	This enumeration lists all of the available peripheral clocks. This is used 
        by the SYS_CLK_ClockFrequencyGet function to return the peripheral 
        clock frequency to the caller.

  Remarks:
    None.
*/
typedef enum
{
    CLK_PERIPH_BUS_1 /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/,
    CLK_PERIPH_BUS_2,
    CLK_PERIPH_BUS_3,
    CLK_PERIPH_BUS_4,
    CLK_PERIPH_BUS_5,
    CLK_PERIPH_BUS_6, /* not used */
    CLK_PERIPH_BUS_7,
    CLK_PERIPH_BUS_8,
}CLK_PERIPH_BUS_MZ;


// *****************************************************************************
/*  Clocks enumeration

  Summary:
	Lists the available clock outputs.

  Description:
	This enumeration lists all of the available clock outputs. This is used 
        by the SYS_CLK_ClockFrequencyGet and SYS_CLK_ClockIsReady functions.

  Remarks:
    'Clock output' means output from the clock source.
*/

typedef enum
{
    /* Selects System clock output. This is used by the
    CPU and some of the peripherals */
    CLK_SYSTEM /*DOM-IGNORE-BEGIN*/  = 0 /*DOM-IGNORE-END*/,

    /* Selects peripheral clock output. This is used by most
    of the peripherals */
    CLK_PERIPHERAL /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/,

    /* Selects USB clock output. This is used by the
    USB module */
    CLK_USB /*DOM-IGNORE-BEGIN*/  = 2 /*DOM-IGNORE-END*/,

    /* Selects referece clock output. This to check any of the
    clock or it could be used as a clock source for other devices */
    CLK_REFERENCE /*DOM-IGNORE-BEGIN*/  = 3 /*DOM-IGNORE-END*/,

    /* Selects Graphics clock output. This is used by the display
    module */
    CLK_GRAPHIX /*DOM-IGNORE-BEGIN*/  = 4 /*DOM-IGNORE-END*/,

    /* Selects ADC/PWM clock */
    CLK_ADCPWM /*DOM-IGNORE-BEGIN*/  = 5 /*DOM-IGNORE-END*/,

}SYS_CLK_OUTPUT;


// *****************************************************************************
/*  Clock clocks enumeration

  Summary:
    Lists the available clock outputs.

  Description:
    This enumeration lists all the available clock outputs. This is used by the 
    SYS_CLK_ClockFrequencyGet and SYS_CLK_ClockIsReady functions.

  Remarks:
    'Clock output' means output from the clock source.
    Not all clock sources are available for all devices. Refer to the
    specific device data sheet to determine the available clock sources.
*/

typedef enum
{
    /* This gives the total number of sources present */
    SYS_CLK_TOTAL_SOURCES /*DOM-IGNORE-BEGIN*/  = 15 /*DOM-IGNORE-END*/,

    /* Source of clock is external(from the pin)
    This is used only for the Reference clock. */
    SYS_CLK_SOURCE_EXTERNAL /*DOM-IGNORE-BEGIN*/  = 14 /*DOM-IGNORE-END*/,

    /* Source of clock is output of USB PLL
    This is used only for the Reference clock. */
    SYS_CLK_SOURCE_USBPLL_OUT /*DOM-IGNORE-BEGIN*/  = 13 /*DOM-IGNORE-END*/,

    /* Source of clock is the output of System PLL.
    This is used only for the Reference clock. */
    SYS_CLK_SOURCE_SYSPLL_OUT /*DOM-IGNORE-BEGIN*/  = 12 /*DOM-IGNORE-END*/,

    /* Source of clock is peripheral clock.
    This is used only for the Reference clock. */
    SYS_CLK_SOURCE_PBCLK_OUT /*DOM-IGNORE-BEGIN*/  = 11 /*DOM-IGNORE-END*/,

    /* Source of clock is System clock.
    This is used for Peripheral clock and the Reference clock. */
    SYS_CLK_SOURCE_SYSCLK_OUT /*DOM-IGNORE-BEGIN*/  = 10 /*DOM-IGNORE-END*/,

    /* Source of clock is Auxiliary clock. */
    SYS_CLK_SOURCE_AUXILIARY /*DOM-IGNORE-BEGIN*/  = 9 /*DOM-IGNORE-END*/,

    /* Source of clock is internal fast RC divided by the divisor
    configured in software. This is used only for the System clock. */
    SYS_CLK_SOURCE_FRC_BY_DIV /*DOM-IGNORE-BEGIN*/  = 8 /*DOM-IGNORE-END*/,

    /* Source of clock is internal fast RC divided by 16.
    This is used only for the System clock. */
    SYS_CLK_SOURCE_FRC_BY_16  /*DOM-IGNORE-BEGIN*/  = 7 /*DOM-IGNORE-END*/,

    /* Source of clock is internal low power RC.
    This is used for System clock and the Reference clock. */
    SYS_CLK_SOURCE_LPRC /*DOM-IGNORE-BEGIN*/  = 6 /*DOM-IGNORE-END*/,

    /* Source of clock is secondary oscillator.
    This is used for System clock and the Reference clock. */
    SYS_CLK_SOURCE_SECONDARY /*DOM-IGNORE-BEGIN*/  = 5 /*DOM-IGNORE-END*/,

    /* Source of clock is primary oscillator multiplied by
    the USB PLL value and divided by the divisor configured by software.
    This is used only for the USB clock */
    SYS_CLK_SOURCE_PRIMARY_USBPLL /*DOM-IGNORE-BEGIN*/  = 4 /*DOM-IGNORE-END*/,

    /* Source of clock is primary oscillator multiplied by
    the System PLL value and divided by the divisor configured by software.
    This is used for System clock and the Reference clock. */
    SYS_CLK_SOURCE_PRIMARY_SYSPLL /*DOM-IGNORE-BEGIN*/  = 3 /*DOM-IGNORE-END*/,

    /* Source of clock is primary oscillator.
    This is used for System clock, Reference clock and the USB clock */
    SYS_CLK_SOURCE_PRIMARY /*DOM-IGNORE-BEGIN*/  = 2 /*DOM-IGNORE-END*/,

    /* Source of clock is internal fast RC multiplied by system PLL.
    This is used for System clock and the Reference clock.  */
    SYS_CLK_SOURCE_FRC_SYSPLL /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/,

    /* Source of clock is internal fast RC
    This is used for System clock, Reference clock and the USB clock */
    SYS_CLK_SOURCE_FRC /*DOM-IGNORE-BEGIN*/  = 0 /*DOM-IGNORE-END*/,

}SYS_CLK_SOURCE;


// *****************************************************************************
/*  Peripheral clock sources enumeration

  Summary:
    Lists the available clock sources for the peripheral clock.

  Description:
    This enumeration lists all the available peripheral clock sources. This is
    used by the SYS_CLK_ClockFrequencySet function.

  Remarks:
   	None.
*/

typedef enum
{
    /* Source of clock is system clock */
    SYS_CLK_SOURCE_SYSTEMCLK /*DOM-IGNORE-BEGIN*/  = 0 /*DOM-IGNORE-END*/
}CLK_SOURCE_PERIPHERAL;


// *****************************************************************************
/* Clock System Service Reference Oscillator initialization data

  Summary:
    Defines the data required to initialize the Oscillator for the Clock System 
    Service.

  Description:
    This structure defines the data required to initialize the Oscillator
    for the Clock System Service.

  Remarks:
   Calling this API may not be essential in some cases. Some of the elements in
   this structure are part of the library configuration file. Setting them here
   will override the configuration file setting.
*/

typedef	struct
{
    /* Initializations for System clock  */
    SYS_CLK_SOURCE systemClockSource;
    /* Set the System clock frequency */
    unsigned long systemClockFrequency;

    /* Initializations for USB clock  */
    /* Enable the USB clock. If the device doesn't need USB clock, set this
    variable to 'false'. In that case, user need not set next two variables. */
    bool usbClockEnable;
    /* Select the USB clock source */
    SYS_CLK_SOURCE usbClockSource;
    /* Set the USB clock frequency */
    unsigned long usbClockFrequency;

    /* Initializations for Peripheral clock  */
    /* Enable the Peripheral clock. If the device doesn't need Peripheral clock,
    set this variable to 'false'. In that case, user need not set next two
    variables. */
    bool peripheralClockEnable;
    /* Select the Peripheral clock source */
    SYS_CLK_SOURCE peripheralClockSource;
    /* Set the Peripheral clock frequency */
    unsigned long peripheralClockFrequency;

    /* Initializations for Reference clock out  */
    /* Set this variable to 'true' to enable the reference clock out.
    The system service will discard this either if this variable is set to
    'false' or if the device doesn't has 'reference clock out' feature. */
    bool referenceClockEnable;
    /* Base clock for the reference clock out. This will be divided and
    tuned to get the actual Reference clock output */
    SYS_CLK_SOURCE referenceClockSource;
    /* Use this to fine tune the divided reference oscillator clock out. */
    unsigned long referenceClockFrequency;

    /* Even though the secondary oscillator is not used, keeping the
    oscillator running, allows a fast switch to the lower system
    clock for low-power operation */
    bool secondaryOscKeepEnabled;

    /* System action on a 'Wait' instruction */
    OSC_OPERATION_ON_WAIT onWaitInstruction;

    /* Stop reference clock out in Idle mode */
    bool referenceStopInIdle;
    /* Stop reference clock out in sleep mode */
    bool referenceSuspendInSleep;
}SYS_CLK_INIT;


// *****************************************************************************
/* Clock module FRC tuning modes

  Summary:
    Defines the data required for tuning the FRC Oscillator.

  Description:
    This structure defines the necessary data required to tune the FRC
    Oscillator.

  Remarks:
   None.
*/

typedef	struct
{
    /* Oscillator tuning mode */
    OSC_TUNING_MODE tuningMode;

    /* The data required may vary depending on the mode. This could
    be pointed to a variable or an array of data */
    uint8_t *tuningData;

}SYS_CLK_FRCTUNING_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: SYS CLK Module Initialization Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SYS_CLK_Initialize ( const SYS_CLK_INIT * const clkInit )

  Summary:
    Initializes hardware and internal data structure of the System Clock.

  Description:
    This function initializes the hardware and internal data structure of the System
    Clock.

  Precondition:
    None.

  Parameters:
    clkInit      - Pointer to a data structure containing any data necessary
                   to initialize the System Clock. This pointer can be
                   NULL if no data is required as static overrides have
                   been provided.

  Returns:
    None.

  Example:
    <code>
    SYS_CLK_INIT generalInit;

    // Populate the oscillator initialization structure
    generalInit.systemClockSource = SYS_CLK_SOURCE_FRC_SYSPLL;
    generalInit.systemClockFrequency = 30000000;
    generalInit.usbClockEnable = true;
    generalInit.usbClockSource = SYS_CLK_SOURCE_PRIMARY_USBPLL;
    generalInit.usbClockFrequency = 48000000;
    generalInit.peripheralClockEnable = true;
    generalInit.peripheralClockSource = SYS_CLK_SOURCE_SYSCLK_OUT;
    generalInit.peripheralClockFrequency = 15000000;

    generalInit.referenceClockEnable = true;
    generalInit.referenceClockSource = SYS_CLK_SOURCE_FRC;
    generalInit.referenceClockFrequency = 8000000;

    SYS_CLK_Initialize (&generalInit);

    <code>

  Remarks:
    This could be called at the time of system initialization to initialize the
    oscillator or after initialization to change any of the initialization
    settings.
*/

void SYS_CLK_Initialize ( const SYS_CLK_INIT const * clkInit );


// *****************************************************************************
/* Function:
	unsigned long SYS_CLK_ClockFrequencySet( SYS_ CLK_OUTPUT outputClock,
                                                 SYS_CLK_SOURCE clockSource,
                                                 unsigned long clockFrequency);

  Summary:
    Configures the clock multiplier and divisor values.

  Description:
    This function configures the clock multiplier and divisor values. This
    function covers all of the configuration for an oscillator clock output.
    All of the arguments in the API may not be applicable in all cases.
    The API discards the arguments that are not relevant.

  Precondition:
    The SYS_CLK_Initialize function should be called before calling this API.

  Parameters:
    outputClock 	- Clock for which the source is to be selected
    clockSource 	- Select the clock source
    clockFrequency 	- Select the clock clock frequecncy

  Returns:
    None.

  Example:
    <code>
	SYS_CLK_ClockFrequencySet(CLK_SYSTEM, SYS_CLK_SOURCE_FRC, 8000000);
    <code>

  Remarks:
    This API returns a zero if it cannot achieve the value requested. The user 
    must recheck the hardware and enter the possible value.


*/

unsigned long SYS_CLK_ClockFrequencySet( SYS_CLK_OUTPUT outputClock,
                                         SYS_CLK_SOURCE clockSource,
                                         unsigned long clockFrequency );


/*******************************************************************************
  Function:
    void SYS_CLK_ClockFailureCallbackRegister ( void *callback )

  Summary:
    Allows registration of a call back function that will be triggered on a clock
    failure.

  Description:
    This function allows registration of a callback function that will be
    triggered on a clock failure. In addition, this function monitors the Fail-Safe
    Clock Monitor (FSCM).

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired System Clock

  Returns:
    None.

  Example:
    <code>
    SYS_CLK_ClockFailureCallbackRegister(&ErrorHandle);

    void ErrorHandle (void)
    {
		//Handle the error.
	}
    </code>

  Remarks:
    This function is not available on all devices. Please refer to the specific
    device data sheet for availability.
*/

void SYS_CLK_ClockFailureCallbackRegister ( void *callback );


// *****************************************************************************
// *****************************************************************************
// Section: SYS Clock Status Routines
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    unsigned long SYS_CLK_ClockFrequencyGet ( SYS_ CLK_OUTPUT clockOutput )

  Summary:
    Gets the selected clock frequency in Hz.

  Description:
    This function gets the selected clock frequency in Hz.

  Precondition:
    The selected clock output must be configured and enabled.

  Parameters:
    Selected clock frequency in Hz.

  Returns:
    Clock frequency in Hz.

  Example:
    <code>
    unsigned long sysClockOutputHz;

    sysClockOutputHz = SYS_CLK_ClockFrequencyGet(CLK_SYSTEM);
    </code>

  Remarks:
 */

unsigned long SYS_CLK_ClockFrequencyGet ( SYS_CLK_OUTPUT clockOutput );


//******************************************************************************
/* Function:
    unsigned long SYS_CLK_MZPeriphBusFreqGet ( CLK_PERIPH_BUS_MZ periphBus )

  Summary:
    Gets the selected peripheral clock frequency in Hz (PIC32MZ only).

  Description:
    This function gets the selected clock frequency in Hz (PIC32MZ only).

  Precondition:
    The selected clock output must be configured and enabled.

  Parameters:
    Selected clock frequency in Hz.

  Returns:
    Clock frequency in Hz.

  Example:
    <code>
    unsigned long sysClockOutputHz;

    sysClockOutputHz = SYS_CLK_ClockFrequencyGet(CLK_PERIPH_BUS_2);
    </code>

  Remarks:
*/
unsigned long SYS_CLK_MZPeriphBusFreqGet ( CLK_PERIPH_BUS_MZ periphBus );

//******************************************************************************
/* Function:
    bool SYS_CLK_ClockIsReady ( SYS_ CLK_OUTPUT clockOutput )

  Summary:
    Checks whether the selected clock output is stable and ready to use.

  Description:
    This function checks whether the selected clock output is stable. This
    should be checked at system start-up, after the initialization is complete
    and also each time when there is a change in the clock setup configuration.
    This function checks the PLL lock status to determine whether the PLL is 
    enabled.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    - true 	- The selected clock output is stable
    - false 	- The selected clock output is not stable

  Example:
    <code>
    //Wait until the selected clock output is getting stabilized.
    while(!SYS_CLK_ClockIsReady(CLK_SYSTEM));

    </code>

  Remarks:
	This function should be called at system start-up.

	This API is non-blocking in nature, so the application must call this API 
        in a loop to wait until the initial settling time of the oscillator expires 
        and the oscillator becomes ready.

 */

bool SYS_CLK_ClockIsReady ( SYS_CLK_OUTPUT clockOutput );


// *****************************************************************************
// *****************************************************************************
// Section: SYS Clock Optional features
// *****************************************************************************
// *****************************************************************************
/* These APIs may not be applicable for all the devices */

//******************************************************************************
/* Function:
    void SYS_CLK_FRCTune ( OSC_FRC_TUNE tuningData )

  Summary:
    This function is used for direct value based FRC oscillator tuning.

  Description:
    This function triggers the FRC tuning based on the selected mode. FRC
    tuning functionality has been provided to help customers compensate for
    temperature effects on the FRC frequency over a wide range of temperatures.

  Precondition:
    The device selected must support the oscillator tuning feature.

  Parameters:
    tuningData - One of the possible value of OSC_FRC_TUNE enum

  Returns:
    None.

  Example:
    <code>
    SYS_CLK_FRCTune( OSC_FRC_TUNE_MINUS_1_875_PERCENT);
    </code>

  Remarks:
 	The tuning step size is an approximation, and is neither characterized, nor
 	tested.

 	This API may can be only used with devices that support direct value
 	based FRC tuning. Refer to the specific device data sheet to determine
 	whether this feature exists for your device.
 */

void SYS_CLK_FRCTune ( OSC_FRC_DIV tuningData );


//******************************************************************************
/* Function:
    void SYS_CLK_FRCTuneAdvanced ( SYS_CLK_FRCTUNING_DATA *tuningData )

  Summary:
    Starts the FRC tuning.

  Description:
    This function triggers the FRC tuning based on the selected mode.

  Precondition:
    The device selected must support the oscillator tuning feature.

  Parameters:
    tuningData - An instance of the structure SYS_CLK_FRCTUNING_DATA
    tuningMode - FRC oscillator tuning mode
    tuningData - Data used for tuning

  Returns:
    None.

  Example:
    <code>
    SYS_CLK_FRCTUNING_DATA tuningInput;
	CLK_FRC_TUNING_VALUE tuningValue;

	tuningData.tuningMode = CLK_TUNING_USING_NUMBER;
	tuningInput.tuningData = &tuningValue;

    SYS_CLK_FRCTuningSet(&tuningInput);
    </code>

  Remarks:
 	This function is not applicable for devices that do not have
 	an FRC oscillator and devices that do have an FRC oscillator, but not
 	FRC tuning. Refer to the specific device data sheet to determine
 	whether this feature exists for your device.
 */

void SYS_CLK_FRCTuningSet ( SYS_CLK_FRCTUNING_DATA *tuningData );


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "src/sys_clk_internal.h"

#include "sys_clk_mapping.h"

#endif //SYS_CLK_H

/*******************************************************************************
 End of File
*/

