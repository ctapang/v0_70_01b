/*******************************************************************************
  Power Peripheral Library Interface Header

  Company:
    Microchip Technology Inc.

  File Name:
    plib_power.h

  Summary:
    Defines the Power Peripheral Library interface.

  Description:
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the Power
    Peripheral Library for Microchip microcontrollers.  The definitions in 
    this file are for the Power Controller module.
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

#ifndef _PLIB_POWER_H
#define _PLIB_POWER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files (continued at end of file)
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.  However,
    please see the bottom of the file for additional implementation header files
    that are also included
*/

#include "peripheral/power/processor/power_processor.h"


// *****************************************************************************
// *****************************************************************************
// Section: Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_POWER_PeripheralModuleDisable ( POWER_MODULE_ID index, POWER_MODULE source )

  Summary:
    Disable the power supply for the module selected in the source.

  Description:
    This function completely shuts down the selected peripheral, effectively 
    powering down all circuits and removing all clock sources. This has the 
    additional effect of making any of the module’s control and buffer registers, 
    which are mapped in the SFR space, unavailable for operations.
	
  Precondition:
    None.

  Parameters:
    index   - Identifier for the device instance to be configured
    source  - Select the module to be disabled from POWER_MODULE enum

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_PeripheralModuleDisable (POWER_ID_0, POWER_MODULE_ADC);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsPeripheralModuleControl in your application to determine whether
	this feature is available.
   
 */

void PLIB_POWER_PeripheralModuleDisable (POWER_MODULE_ID index, POWER_MODULE source);


//******************************************************************************
/* Function:
    void PLIB_POWER_PeripheralModuleEnable ( POWER_MODULE_ID index, POWER_MODULE source )

  Summary:
    Enable the power supply for the module selected in the source.

  Description:
    This function enables the power supply back to the selected module.
	
  Precondition:
    None.

  Parameters:
    index   - Identifier for the device instance to be configured
    source  - Select the module to be enabled from POWER_MODULE enum

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_PeripheralModuleEnable (POWER_ID_0, POWER_MODULE_ADC);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsPeripheralModuleControl in your application to determine whether
	this feature is available.
   
 */

void PLIB_POWER_PeripheralModuleEnable (POWER_MODULE_ID index, POWER_MODULE source);

//******************************************************************************
/* Function:
    bool PLIB_POWER_PeripheralModuleIsEnabled ( POWER_MODULE_ID index, POWER_MODULE source )

  Summary:
    Check if selected peripheral is enabled or not

  Description:
    This function checks if selected peripheral is enabled or not.
	
  Precondition:
    None.

  Parameters:
    index   - Identifier for the device instance to be configured
    source  - Select the module to be enabled from POWER_MODULE enum

  Returns:
    - true    - Power of the selected peripheral is enabled
    - false   - Power of the selected peripheral is disabled

  Example:
    <code>
    if (PLIB_POWER_PeripheralModuleIsEnabled ( POWER_MODULE_0, POWER_MODULE_ADC ))
	{
	
	}
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsPeripheralModuleControl in your application to determine whether
	this feature is available.
   
 */

bool PLIB_POWER_PeripheralModuleIsEnabled (POWER_MODULE_ID index, POWER_MODULE source);

//*******************************************************************************
/*  Function:
    void PLIB_POWER_VoltageRegulatorEnable (POWER_MODULE_ID index)

  Summary:
    Enable the voltage regulator during Sleep mode.

  Description:
    This function enables the voltage regulator during Sleep mode for the selected
    device.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_VoltageRegulatorEnable(POWER_ID_0);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsVoltageRegulatorControl in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_VoltageRegulatorEnable (POWER_MODULE_ID index);


//*******************************************************************************
/*  Function:
    bool PLIB_POWER_VoltageRegulatorIsEnabled (POWER_MODULE_ID index)

  Summary:
    Provides the status of the voltage regulator during Sleep mode.

  Description:
    This function provides the status of the voltage regulator during Sleep mode 
    for the selected device.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    - true    - The voltage regulator will be enabled in Sleep mode
    - false   - The voltage regulator will be disabled in Sleep mode

  Example:
    <code>
    if (PLIB_POWER_VoltageRegulatorIsEnabled(POWER_ID_0))
	{
	
	}
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsVoltageRegulatorControl in your application to determine whether
	this feature is available.
*/
bool PLIB_POWER_VoltageRegulatorIsEnabled (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_VoltageRegulatorDisable (POWER_MODULE_ID index)

  Summary:
    Disables the voltage regulator during Sleep mode.

  Description:
    This function disables the voltage regulator into during Sleep mode for
    the selected device.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_VoltageRegulatorDisable(POWER_ID_0); 
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsVoltageRegulatorControl in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_VoltageRegulatorDisable (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeviceWasInSleepMode (POWER_MODULE_ID index)

  Summary:
    Returns the Sleep mode status of the device.

  Description:
    This function returns the Sleep mode status of the device. It tells whether 
    or not the device was in Sleep mode before waking up.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
	
  Returns:
    - true    - The device was in Sleep mode before waking up
    - false   - The device was not in Sleep mode

  Example:
    <code>
    if(PLIB_POWER_DeviceWasInSleepMode(POWER_ID_0))
    {
	
    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsSleepStatus in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeviceWasInSleepMode (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_ClearSleepStatus (POWER_MODULE_ID index)

  Summary:
    Clear the Sleep mode status bit of the device.

  Description:
    This function clears the Sleep status bit of the device if it was previously 
    in Sleep mode. However, it does not mean that it wakes up the device from sleep.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
	
  Returns:
    None

  Example:
    <code>
    if(PLIB_POWER_DeviceWasInSleepMode(POWER_ID_0))
    {
	    PLIB_POWER_ClearSleepStatus (POWER_ID_0);
    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsSleepStatus in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_ClearSleepStatus (POWER_MODULE_ID index);

//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeviceWasInIdleMode (POWER_MODULE_ID index)

  Summary:
    Returns the Idle mode status of the device.

  Description:
    This function returns the Idle mode status of the device. It tells whether 
    or not the device was in Idle mode before waking up.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
	
  Returns:
    - true    - The device was in Idle mode before waking up
    - false   - The device was not in Idle mode


  Example:
    <code>
    if(PLIB_POWER_DeviceWasInIdleMode(POWER_ID_0))
    {
	
    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsIdleStatus in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeviceWasInIdleMode (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_ClearIdleStatus (POWER_MODULE_ID index)

  Summary:
    Clears the Idle mode status of the device.

  Description:
    This function clears the Idle status bit of the device if it was previously
    in Idle mode. However, it does not mean that it wakes up the device from Idle.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
	
  Returns:
    None

  Example:
    <code>
    if(PLIB_POWER_DeviceWasInIdleMode(POWER_ID_0))
    {
	    PLIB_POWER_ClearIdleStatus (POWER_ID_0);
    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsIdleStatus in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_ClearIdleStatus (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_DeepSleepModeEnable (POWER_MODULE_ID index)

  Summary:
    Enables the Deep Sleep mode.

  Description:
    This function enables the Deep Sleep mode. Deep Sleep mode is intended to provide 
    the lowest levels of power consumption available without requiring the use of 
    external switches to completely remove all power from the device.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_DeepSleepModeEnable(POWER_ID_0);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepMode in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_DeepSleepModeEnable (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_DeepSleepModeDisable (POWER_MODULE_ID index)

  Summary:
    Disables the Deep Sleep mode.

  Description:
    This function disables the Deep Sleep mode. Deep Sleep mode is intended to 
    provide the lowest levels of power consumption available without requiring 
    the use of external switches to completely remove all power from the device.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_DeepSleepModeDisable(POWER_ID_0);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepMode in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_DeepSleepModeDisable (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_DeepSleepBOREnable (POWER_MODULE_ID index)

  Summary:
    Enables the Deep Sleep BOR mode.

  Description:
    This function enables the Deep Sleep BOR mode. The Deep Sleep BOR is 
    ndependent of the standard BOR and a Deep Sleep BOR event will not cause a
    wake-up from Deep Sleep.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_DeepSleepBOREnable(POWER_ID_0);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepBOR in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_DeepSleepBOREnable (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    void PLIB_POWER_DeepSleepBORDisable (POWER_MODULE_ID index)

  Summary:
    Disables the Deep Sleep BOR.

  Description:
    This function disables the Deep Sleep BOR. The Deep Sleep BOR is independent 
    of the standard BOR and a Deep Sleep BOR event will not cause a wake-up 
    from Deep Sleep.

	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_POWER_DeepSleepBORDisable(POWER_ID_0);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepBOR in your application to determine whether
	this feature is available.
*/

void PLIB_POWER_DeepSleepBORDisable (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeepSleepInterruptOnChangeStatus (POWER_MODULE_ID index)

  Summary:
    Returns the status of the Deep Sleep Interrupt-on-Change bit.
	
  Description:
    This function returns the status of the Deep Sleep Interrupt-on-Change bit.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    - true    - Interrupt-on-Change was asserted during Deep Sleep
    - false   - Interrupt-on-Change was not asserted during Deep Sleep

  Example:
    <code>
    if(PLIB_POWER_DeepSleepInterruptOnChangeStatus(POWER_ID_0))
    {

    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepInterruptOnChange in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeepSleepInterruptOnChangeStatus (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeepSleepFaultDetectStatus (POWER_MODULE_ID index)

  Summary:
    Returns the status of Deep Sleep Fault Detect bit.  
	
  Description:
    This function returns the status of the Deep Sleep Fault Detect bit.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    true    - A Fault occurred during Deep Sleep, and some Deep Sleep 
              configuration  settings may have been corrupted
    false   - No Fault was detected during Deep Sleep

  Example:
    <code>
    if(PLIB_POWER_DeepSleepFaultDetectStatus(POWER_ID_0))
    {

    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepFaultDetect in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeepSleepFaultDetectStatus (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeepSleepMCLREventStatus (POWER_MODULE_ID index)

  Summary:
    Returns the status of the Deep Sleep MCLR Event bit.
	
  Description:
    This function returns the status of the Deep Sleep MCLR Event bit.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    - true    - The MCLR pin was active and was asserted during Deep Sleep
    - false   - The MCLR pin was not active, or was active, but not asserted
	        during Deep Sleep

  Example:
    <code>
    if(PLIB_POWER_DeepSleepMCLREventStatus(POWER_ID_0))
    {

    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepMCLREvent in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeepSleepMCLREventStatus (POWER_MODULE_ID index);


//******************************************************************************
/*  Function:
    bool PLIB_POWER_DeepSleepPowerOnResetStatus (POWER_MODULE_ID index)

  Summary:
    Returns the status of Deep Sleep Power-on Reset bit.  
	
  Description:
    This function returns the status of the Deep Sleep Power-on Reset bit.
	
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    - true    - The VDD supply POR circuit was active and a POR event was detected
    - false   - The VDD supply POR circuit was not active, or was active but did
                not detect a POR event

  Example:
    <code>
    if(PLIB_POWER_DeepSleepPowerOnResetStatus(POWER_ID_0))
    {

    }
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the 
	specific device data sheet to determine availability or use 
	PLIB_POWER_ExistsDeepSleepPowerOnReset in your application to determine whether
	this feature is available.
*/

bool PLIB_POWER_DeepSleepPowerOnResetStatus (POWER_MODULE_ID index);

// *****************************************************************************
// *****************************************************************************
// Section: POWER Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_POWER_ExistsPeripheralModuleControl( POWER_MODULE_ID index )

  Summary:
    Identifies whether the PeripheralModuleControl feature exists on the POWER module 

  Description:
    This function identifies whether the PeripheralModuleControl feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_PeripheralModuleDisable
    - PLIB_POWER_PeripheralModuleEnable
    - PLIB_POWER_PeripheralModuleIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PeripheralModuleControl feature is supported on the device
    - false  - The PeripheralModuleControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsPeripheralModuleControl( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsVoltageRegulatorControl( POWER_MODULE_ID index )

  Summary:
    Identifies whether the VoltageRegulatorControl feature exists on the POWER module 

  Description:
    This function identifies whether the VoltageRegulatorControl feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_VoltageRegulatorEnable
    - PLIB_POWER_VoltageRegulatorDisable
    - PLIB_POWER_VoltageRegulatorIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The VoltageRegulatorControl feature is supported on the device
    - false  - The VoltageRegulatorControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsVoltageRegulatorControl( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsSleepStatus( POWER_MODULE_ID index )

  Summary:
    Identifies whether the SleepStatus feature exists on the POWER module 

  Description:
    This function identifies whether the SleepStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeviceWasInSleepMode
    - PLIB_POWER_ClearSleepStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SleepStatus feature is supported on the device
    - false  - The SleepStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsSleepStatus( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsIdleStatus( POWER_MODULE_ID index )

  Summary:
    Identifies whether the IdleStatus feature exists on the POWER module 

  Description:
    This function identifies whether the IdleStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeviceWasInIdleMode
    - PLIB_POWER_ClearIdleStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The IdleStatus feature is supported on the device
    - false  - The IdleStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsIdleStatus( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepMode( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepModeControl feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepModeControl feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepModeEnable
    - PLIB_POWER_DeepSleepModeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepModeControl feature is supported on the device
    - false  - The DeepSleepModeControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepMode( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepBOR( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepBORControl feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepBORControl feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepBOREnable
    - PLIB_POWER_DeepSleepBORDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepBORControl feature is supported on the device
    - false  - The DeepSleepBORControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepBOR( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepInterruptOnChange( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepIOCStatus feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepIOCStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepInterruptOnChangeStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepIOCStatus feature is supported on the device
    - false  - The DeepSleepIOCStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepInterruptOnChange( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepFaultDetect( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepFaultDetectStatus feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepFaultDetectStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepFaultDetectStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepFaultDetectStatus feature is supported on the device
    - false  - The DeepSleepFaultDetectStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepFaultDetect( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepMCLREvent( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepMCLRStatus feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepMCLRStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepMCLREventStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepMCLRStatus feature is supported on the device
    - false  - The DeepSleepMCLRStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepMCLREvent( POWER_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_POWER_ExistsDeepSleepPowerOnReset( POWER_MODULE_ID index )

  Summary:
    Identifies whether the DeepSleepPORStatus feature exists on the POWER module 

  Description:
    This function identifies whether the DeepSleepPORStatus feature is available on the POWER module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_POWER_DeepSleepPowerOnResetStatus

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The DeepSleepPORStatus feature is supported on the device
    - false  - The DeepSleepPORStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_POWER_ExistsDeepSleepPowerOnReset( POWER_MODULE_ID index );


#endif //#ifndef _PLIB_POWER_H
/*******************************************************************************
 End of File
*/

