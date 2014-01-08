/*******************************************************************************
  Comparator Peripheral Library Interface Header

  Company:      
    Microchip Technology Inc.

  File Name:   
    plib_cmp.h

  Summary:
    Comparator Peripheral Library Interface Header for Comparator module definitions.

  Description:
    This header file contains the function prototypes and definitions of the 
    data types and constants that make up the interface to the Comparator 
    Peripheral Library for all families of Microchip microcontrollers. The 
    definitions in this file are common to the Comparator peripheral.
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

#ifndef _PLIB_CMP_H
#define _PLIB_CMP_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files (continued at end of file)
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are inlcuded in this file.  However,
    please see the bottom of the file for additional implementation header files
    that are also included
*/

#include "processor/cmp_processor.h"


// *****************************************************************************
// *****************************************************************************
// Section: Comparator Peripheral Library Interface Routines
// *****************************************************************************

// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - General Configuration
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_Enable ( CMP_CVREF_MOD index )

 Summary:
   Enables the voltage reference of the Comparator module.

 Description:
   This function enables the voltage reference of the Comparator module.

 Precondition:
   The Comparator module should be appropriately configured before being enabled.

 Parameters:
   index    - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
    PLIB_CMP_CVREF_Enable(CMP_CVREF_ID_1);
   </code>

 Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFEnableControl 
	in your application to determine whether this feature is available.
 */

void PLIB_CMP_CVREF_Enable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_Disable ( CMP_MODULE_ID index )

  Summary:
    Disables the voltage reference of the Comparator module.

  Description:
    This function disables the voltage reference of the Comparator module.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_Disable (CMP_CVREF_ID_1);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFEnableControl 
	in your application to determine whether this feature is available.
 */

void PLIB_CMP_CVREF_Disable(CMP_MODULE_ID index);

//******************************************************************************
/*  Function:
    void PLIB_CMP_CVREF_OutputEnable ( CMP_MODULE_ID index )

  Summary:
    Enables the voltage output.

  Description:
    This function enables the voltage output

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_OutputEnable(CMP_CVREF_ID_1);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFOutputEnableControl 
	in your application to determine whether this feature is available.

 */

void PLIB_CMP_CVREF_OutputEnable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_OutputDisable ( CMP_MODULE_ID index )

  Summary:
    Disables the output voltage.

  Description:
    This function disables the reference voltage output.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_VoltageOutputDisable(CMP_CVREF_ID_1);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFOutputEnableControl 
	in your application to determine whether this feature is available.
 */

void PLIB_CMP_CVREF_OutputDisable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
   void PLIB_CMP_CVREF_Output2Enable ( CMP_MODULE_ID index )

 Summary:
   Enables the Vsource/2 voltage output.

 Description:
   This function enables the Vsource/2 voltage output. This is independent of
   voltage output 1.

 Precondition:
   None.

 Parameters:
   index    - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   PLIB_CMP_CVREF_Output2Enable(CMP_CVREF_ID_1);
   </code>

 Remarks:
   Note: This feature is not available on all devices.  Please refer to the
   specific device data sheet to determine availability.

*/

void PLIB_CMP_CVREF_Output2Enable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
   void PLIB_CMP_CVREF_Output2Disable ( CMP_MODULE_ID index )

 Summary:
   Disables the Vsource/2 voltage output.

 Description:
   This function disables the Vsource/2 voltage output.

 Precondition:
   None.

 Parameters:
   index    - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   PLIB_CMP_CVREF_Output2Disable(CMP_CVREF_ID_1);
   </code>

 Remarks:
   Note: This feature is not available on all devices.  Please refer to the
	    specific device data sheet to determine availability.

*/

void PLIB_CMP_CVREF_Output2Disable(CMP_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - External Voltage Reference
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_ReferenceVoltageSelect ( CMP_MODULE_ID index,
        CMP_CVREF_VALUE value );

  Summary:
    Selects the voltage reference value.

  Description:
    This function selects the voltage reference value. This value decides how
    many resistance units will be added and thus decides the output voltage.

  Precondition:
    Determine the correct value that should be passed.

  Parameters:
    index    - Identifier for the device instance to be configured
    value    - Select value from CMP_CVREF_VALUE

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_ReferenceVoltageSelect ( CMP_CVREF_ID_1,  CMP_CVREF_VALUE_13 );
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFRefVoltageRangeSelect 
    in your application to determine whether this feature is available.
*/

void PLIB_CMP_CVREF_ReferenceVoltageSelect(CMP_MODULE_ID index, CMP_CVREF_REFERENCE_SELECT reference);

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_SourceVoltageSelect ( CMP_MODULE_ID index, CMP_CVREF_VOLTAGE_SOURCE source )

  Summary:
    Connects the Comparator module to the selected voltage source.

  Description:
    This function connects the Comparator module to the selected voltage source.
  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
    source   - Select the voltage source from CMP_CVREF_VOLTAGE_SOURCE

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_SourceVoltageSelect (CMP_CVREF_ID_1, CMP_CVREF_VOLTAGE_SOURCE_INTERNAL);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFVoltageRangeSelect in your application 
	to determine whether this feature is available.	
 */

void PLIB_CMP_CVREF_SourceVoltageSelect (CMP_MODULE_ID index, CMP_CVREF_VOLTAGE_SOURCE source);

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_SourceNegativeInputSelect ( CMP_MODULE_ID index, CMP_CVREF_VOLTAGE_SOURCE_NEG_REFERENCE negInput )

  Summary:
    Configures the Comparator module to use the selected input as a negative reference.

  Description:
    This function configures the Comparator module to use the selected input as a negative
    reference for the voltage source.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured.
    negInput - Select the voltage source negative reference from
			   CMP_CVREF_VOLTAGE_SOURCE_NEG_REFERENCE
  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_SourceNegativeInputSelect (CMP_CVREF_ID_1, CMP_CVREF_VOLTAGE_SOURCE_NEG_REF_GROUND);
    </code>

  Remarks:
    Note:  This feature is not available on all devices.  Please refer to the
    specific device data sheet for availability. For such devices, selecting
    the positive source will automatically select the negative input.
 */

void PLIB_CMP_CVREF_SourceNegativeInputSelect (CMP_MODULE_ID index, CMP_CVREF_VOLTAGE_SOURCE_NEG_REFERENCE negInput );

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_WideRangeEnable ( CMP_MODULE_ID index )

  Summary:
    Enables the wide range.

  Description:
    This function enables the wide range for reference voltage. The voltage range starts
    from zero if the wide range is selected.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_WideRangeEnable(CMP_CVREF_ID_1);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFWideRangeControl
	in your application to determine whether this feature is available.
 */

void PLIB_CMP_CVREF_WideRangeEnable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_WideRangeDisable ( CMP_MODULE_ID index )

  Summary:
    Disables the wide range.

  Description:
    This function disables the wide range for reference voltage. The range of possible
    voltages will become narrower, and finer voltage options can be achieved
    in this case.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_WideRangeDisable(CMP_CVREF_ID_1);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFWideRangeControl
	in your application to determine whether this feature is available.
 */

void PLIB_CMP_CVREF_WideRangeDisable(CMP_MODULE_ID index);

//******************************************************************************
/* Function:
    bool PLIB_CMP_CVREF_WideRangeIsEnabled ( CMP_MODULE_ID index );

  Summary:
    Returns whether the wide range is selected for the reference voltage.

  Description:
    This function returns whether the wide range is enabled.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
             - true  = The wide range is enabled
             - false = The wide range is not enabled

  Example:
    <code>
    bool range;

    range = PLIB_CMP_CVREF_WideRangeIsEnabled(MY_CMP_CVREF_ID);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFWideRangeControl
	in your application to determine whether this feature is available.
 */

bool PLIB_CMP_CVREF_WideRangeIsEnabled(CMP_MODULE_ID index);


//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_ValueSelect ( CMP_MODULE_ID index,
        CMP_CVREF_VALUE value );

  Summary:
    Selects the voltage reference value.

  Description:
    This function selects the voltage reference value. This value decides how
    many resistance units will be added and therefore, decides the output voltage.

  Precondition:
    Determine the correct value that should be passed.

  Parameters:
    index    - Identifier for the device instance to be configured
    value    - Select value from CMP_CVREF_VALUE

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_ValueSelect ( CMP_CVREF_ID_1,  CMP_CVREF_VALUE_13 );
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFValueSelect
	in your application to determine whether this feature is available.	
 */

void PLIB_CMP_CVREF_ValueSelect(CMP_MODULE_ID index, CMP_CVREF_VALUE value);


//******************************************************************************
/* Function:
    CMP_CVREF_VALUE PLIB_CMP_CVREF_ValueGet( CMP_MODULE_ID index );

  Summary:
    Returns the voltage setting value.

  Description:
    This function returns the configured reference voltage value.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured

  Returns:
    CMP_CVREF_VALUE - Reference voltage value

  Example:
    <code>
    CMP_CVREF_VALUE value;

    value = PLIB_CMP_CVREF_ValueGet ( CMP_CVREF_ID_1 );
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFValueSelect
	in your application to determine whether this feature is available.	
 */

CMP_CVREF_VALUE PLIB_CMP_CVREF_ValueGet(CMP_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - Internal Voltage Reference
// *****************************************************************************
// *****************************************************************************


//******************************************************************************
/* Function:
    void PLIB_CMP_CVREF_BandGapReferenceSourceSelect ( CMP_MODULE_ID index,
        CMP_CVREF_BANDGAP_SELECT bandGap );

  Summary:
    Selects the band gap reference voltage source.

  Description:
    This function selects the band gap reference voltage source from the
    available options from CMP_CVREF_BANDGAP_SELECT.

  Precondition:
    None.

  Parameters:
    index    - Identifier for the device instance to be configured
    select   - Select a band gap reference source from CMP_CVREF_BANDGAP_SELECT

  Returns:
    None.

  Example:
    <code>
    PLIB_CMP_CVREF_BandGapReferenceSourceSelect ( CMP_CVREF_ID_1,  PLIB_CMP_CVREF_BANDGAP_0_6V );
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_CVREF_ExistsCVREFBGRefVoltageRangeSelect
	in your application to determine whether this feature is available.
*/
void PLIB_CMP_CVREF_BandGapReferenceSourceSelect(CMP_MODULE_ID index, CMP_CVREF_BANDGAP_SELECT select);

// *****************************************************************************
/* Function:
    void PLIB_CMP_Enable (CMP_MODULE_ID index)

  Summary:
    Enables the Comparator module.

  Description:
    This function enables (i.e., turns ON) the selected Comparator module.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_Enable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsEnableControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_Enable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_Disable (CMP_MODULE_ID index)

  Summary:
    Disables the Comparator module.

  Description:
    This function disables (i.e., turns OFF) the selected Comparator module.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_Disable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsEnableControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_Disable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_OutputEnable (CMP_MODULE_ID index)

  Summary:
    Enables the Comparator output.

  Description:
    This function enables (i.e., turns ON) the Comparator output.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_OutputEnable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputEnableControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_OutputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_OutputDisable (CMP_MODULE_ID index)

  Summary:
    Disables the Comparator output.

  Description:
    This function disables (i.e., turns OFF) the Comparator output.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_OutputDisable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputEnableControl
	in your application to determine whether this feature is 
    available.
*/

void PLIB_CMP_OutputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_InvertedOutputSelect (CMP_MODULE_ID index)

  Summary:
    Comparator output is inverted.

  Description:
    This function will select the inverted comparator output.  

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_InvertedOutputSelect(MY_CMP_INSTANCE,);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputEnableControlExistsInvertOutputControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_InvertedOutputSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_NonInvertedOutputSelect (CMP_MODULE_ID index)

  Summary:
    Comparator output is non-inverted.

  Description:
    This function will select the non-inverted comparator output.  

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_NonInvertedOutputSelect(MY_CMP_INSTANCE,);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputEnableControlExistsInvertOutputControl
	in your application to determine whether this feature is 
    available.
*/

void PLIB_CMP_NonInvertedOutputSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_OutputHighSelect (CMP_MODULE_ID index)

  Summary:
    Comparator output bit is set to '1'.

  Description:
    This function will set the Comparator output bit to '1'.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_OutputHighSelect(MY_CMP_INSTANCE,);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputLevelControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_OutputHighSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_OutputLowSelect (CMP_MODULE_ID index)

  Summary:
    Comparator output bit is set to '0'.

  Description:
    This function will set the Comparator output bit to '0'.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    PLIB_CMP_OutputLowSelect(MY_CMP_INSTANCE,);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsOutputLevelControl
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_OutputLowSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_InterruptEventSelect (CMP_MODULE_ID index,CMP_INTERRUPT_EVENT event)

  Summary:
    Comparator interrupt event select.

  Description:
    This function will select when the Comparator interrupt should occur.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    event           - One of the possible values from CMP_INTERRUPT_EVENT
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // CMP_INTERRUPT_EVENT - CMP_LOW_TO_HIGH
    PLIB_CMP_InterruptEventSelect(MY_CMP_INSTANCE, CMP_LOW_TO_HIGH);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsInterruptEventSelect
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_InterruptEventSelect (CMP_MODULE_ID index,CMP_INTERRUPT_EVENT event);

// *****************************************************************************
/* Function:
    void PLIB_CMP_InvertingInputChannelSelect(CMP_MODULE_ID index,CMP_INVERTING_INPUT channel)

  Summary:
    Comparator inverting input channel select.

  Description:
    This function will select the inverting input channels for the Comparator.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - One of the possible values from CMP_INVERTING_INPUT
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_InvertingInputChannelSelect(MY_CMP_INSTANCE,CMP_INVERTING_INPUT_CHANNEL_B);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsInvertingInputSelect
	in your application to determine whether this feature is 
    available.	
*/

void PLIB_CMP_InvertingInputChannelSelect (CMP_MODULE_ID index,CMP_INVERTING_INPUT channel);

// *****************************************************************************
/* Function:
    void PLIB_CMP_NonInvertingInputChannelSelect(CMP_MODULE_ID index, CMP_NON_INVERTING_INPUT input)

  Summary:
    Comparator input channel select.

  Description:
    This function will select the non-inverting input channels for the Comparator.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - One of the possible values from CMP_NON_INVERTING_INPUT
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_NonInvertingInputChannelSelect(MY_CMP_INSTANCE,CMP_NON_INVERTING_INPUT_A);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsNonInvertingInputSelect
	in your application to determine whether this feature is 
    available.s	
*/

void PLIB_CMP_NonInvertingInputChannelSelect(CMP_MODULE_ID index, CMP_NON_INVERTING_INPUT input);

// *****************************************************************************
/* Function:
    void PLIB_CMP_StopInIdleModeEnable (CMP_MODULE_ID index)

  Summary:
    Enables Stop in Idle mode.

  Description:
    This function will discontinue operation of all comparators when the device enters Idle mode.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_StopInIdleModeEnable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsStopInIdle
	in your application to determine whether this feature is 
    available.
*/

void PLIB_CMP_StopInIdleModeEnable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_StopInIdleModeDisable (CMP_MODULE_ID index)

  Summary:
    Disables Stop in Idle mode.

  Description:
    This function will continue operation of all enabled comparators when the device enters Idle mode.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_StopInIdleModeDisable(MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. 
	Please refer to the specific device data sheet to determine
	availability or use PLIB_CMP_ExistsStopInIdle
	in your application to determine whether this feature is 
    available.
*/

void PLIB_CMP_StopInIdleModeDisable(CMP_MODULE_ID index);
// *****************************************************************************
/* Function:
   void PLIB_CMP_Cmp1OutputHighSelect (CMP_MODULE_ID index)

 Summary:
   Comparator output bit is set to '1'.

 Description:
   This function will set the Comparator output bit to '1'.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   PLIB_CMP_Cmp1OutputHighSelect(MY_CMP_INSTANCE,);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_Cmp1OutputHighSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_Cmp1OutputLowSelect (CMP_MODULE_ID index)

 Summary:
   Comparator output bit is set to '0'.

 Description:
   This function will set the Comparator output bit to '0'.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   PLIB_CMP_Cmp1OutputLowSelect(MY_CMP_INSTANCE,);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_Cmp1OutputLowSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_Cmp2OutputHighSelect (CMP_MODULE_ID index)

 Summary:
   Comparator output bit is set to '1'.

 Description:
   This function will set the Comparator output bit to '1'.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   PLIB_CMP_Cmp2OutputHighSelect(MY_CMP_INSTANCE,);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_Cmp2OutputHighSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_Cmp2OutputLowSelect (CMP_MODULE_ID index)

 Summary:
   Comparator output bit is set to '0'.

 Description:
   This function will set the Comparator output bit to '0'.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   PLIB_CMP_Cmp2OutputLowSelect(MY_CMP_INSTANCE,);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_Cmp2OutputLowSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_SpeedPowerSelect (CMP_MODULE_ID index,CMP_SPEED_POWER normal)

 Summary:
   Comparator speed/power select.

 Description:
   This function will select the speed/power of the Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured
   normal          - One of the possible values from CMP_SPEED_POWER
 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_SpeedPowerSelect(MY_CMP_INSTANCE,CMP_SPEED_POWER_HIGHER);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

//void PLIB_CMP_SpeedPowerSelect(CMP_MODULE_ID index,CMP_SPEED_POWER normal);

// *****************************************************************************
/* Function:
   void PLIB_CMP_HysteresisEnable (CMP_MODULE_ID index)

 Summary:
   Comparator hysteresis enable.

 Description:
   This function will enable the hysteresis of the Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_HysteresisEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_HysteresisEnable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_HysteresisDisable (CMP_MODULE_ID index)

 Summary:
   Comparator hysteresis disable.

 Description:
   This function will disable the hysteresis of the Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_HysteresisDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_HysteresisDisable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_HysteresisDisable (CMP_MODULE_ID index)

 Summary:
   Comparator hysteresis disable.

 Description:
   This function will disable the hysteresis of the Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_HysteresisDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_HysteresisDisable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OutputSynchronousWithTimer1Enable (CMP_MODULE_ID index)

 Summary:
   Comparator Output Synchronous mode select.

 Description:
   This function will synchronize comparator output to the rising edge of the Timer1 clock.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OutputSynchronousWithTimer1Enable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OutputSynchronousWithTimer1Enable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OutputSynchronousWithTimer1Disable (CMP_MODULE_ID index)

 Summary:
   Comparator output is asynchronous.

 Description:
   This function will disable the synchronized comparator output with the Timer1 clock.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OutputSynchronousWithTimer1Disable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OutputSynchronousWithTimer1Disable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   bool PLIB_CMP_OutputStatusGet (CMP_MODULE_ID index)

 Summary:
   Comparator output status.

 Description:
   This function will return the current status of the Comparator output.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
                   - true  = The status flag is set
                   - false = The status flag is clear

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // bool cmp_status=PLIB_CMP_OutputStatusGet(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

bool PLIB_CMP_OutputStatusGet(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   bool PLIB_CMP_EventHasOccurred (CMP_MODULE_ID index)

 Summary:
   Comparator event status.

 Description:
   This function will return the current event status of the Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
                   - true  = The event flag is set
                   - false = The event flag is clear


 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // bool cmp_event_status = PLIB_CMP_EventHasOccurred(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

bool PLIB_CMP_EventHasOccurred(CMP_MODULE_ID index);


// *****************************************************************************
/* Function:
   void PLIB_CMP_EventStatusClear (CMP_MODULE_ID index)

 Summary:
   Comparator event clear.

 Description:
   This function will clear event status bit of the Comparator. Subsequent triggers
   and interrupts are disabled until the bit is cleared.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_EventStatusClear(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_EventStatusClear(CMP_MODULE_ID index);


// *****************************************************************************
/* Function:
   void PLIB_CMP_OpAmpModeDisable (CMP_MODULE_ID index)

 Summary:
   Op amp operation mode disable.

 Description:
   This function will cause the circuit to operate as a Comparator.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OpAmpModeDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OpAmpModeDisable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OpAmpModeEnable (CMP_MODULE_ID index)

 Summary:
   Op amp operation mode enable.

 Description:
   This function will cause the circuit to operate as an Op amp.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OpAmpModeEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OpAmpModeEnable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OpAmpOutputEnable (CMP_MODULE_ID index)

 Summary:
   Op amp output enable.

 Description:
   This function will enable the Op amp output pin.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OpAmpOutputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OpAmpOutputEnable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OpAmpOutputDisable (CMP_MODULE_ID index)

 Summary:
   Op amp output disable.

 Description:
   This function will disable the Op amp output pin.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OpAmpOutputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

void PLIB_CMP_OpAmpOutputDisable(CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_MaskAInputSelect (CMP_MODULE_ID index,CMP_MASK_A select)

 Summary:
   Comparator Mask A input select.

 Description:
   This function will select the Comparator MASK A input source.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured
   select          - One of the possible values from CMP_MASK_A

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_MaskAInputSelect(MY_CMP_INSTANCE,CMP_MASK_A_PWM1L);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

//void PLIB_CMP_MaskAInputSelect(CMP_MODULE_ID index,CMP_MASK_A select);

// *****************************************************************************
/* Function:
   void PLIB_CMP_MaskBInputSelect (CMP_MODULE_ID index,CMP_MASK_B select)

 Summary:
   Comparator Mask B input select.

 Description:
   This function will select the Comparator MASK B input source.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured
   select          - One of the possible values from CMP_MASK_B

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_MaskBInputSelect(MY_CMP_INSTANCE,CMP_MASK_B_PWM1L);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

//void PLIB_CMP_MaskBInputSelect(CMP_MODULE_ID index,CMP_MASK_B select);

// *****************************************************************************
/* Function:
   void PLIB_CMP_MaskCInputSelect (CMP_MODULE_ID index,CMP_MASK_C select)

 Summary:
   Comparator Mask C input select.

 Description:
   This function will select the Comparator MASK C input source.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured
   select          - One of the possible values from CMP_MASK_C

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_MaskBInputSelect(MY_CMP_INSTANCE,CMP_MASK_C_PWM1L);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/

//void PLIB_CMP_MaskCInputSelect(CMP_MODULE_ID index,CMP_MASK_C select);

// *****************************************************************************
/* Function:
   void PLIB_CMP_HighLevelMaskSelect (CMP_MODULE_ID index)

 Summary:
   High-level masking select.

 Description:
   This function will select the high-level masking.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_HighLevelMaskSelect(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_HighLevelMaskSelect (CMP_MODULE_ID index);


// *****************************************************************************
/* Function:
   void PLIB_CMP_LowLevelMaskSelect (CMP_MODULE_ID index)

 Summary:
   Low-level masking select.

 Description:
   This function will select the low -evel masking

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_LowLevelMaskSelect(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_LowLevelMaskSelect (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateCInputEnable (CMP_MODULE_ID index)

 Summary:
   C input connected to OR gate.

 Description:
   This function will select the C input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateCInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateCInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateCInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate C input disable.

 Description:
   This function will disable the C input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateCInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateCInputDisable (CMP_MODULE_ID index);


// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedCInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate inverted C input disable.

 Description:
   This function will disable the inverted C input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedCInputDisable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedCInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedCInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted C input connected to OR gate

 Description:
   This function will select the inverted C input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedCInputEnable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedCInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateBInputEnable (CMP_MODULE_ID index)

 Summary:
   B input connected to OR gate.

 Description:
   This function will select the B input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateBInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateBInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateBInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate B input disable.

 Description:
   This function will disable the B input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateBInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateBInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedBInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate inverted B input disable.

 Description:
   This function will disable the inverted B input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedBInputDisable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedBInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedBInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted B input connected to OR gate

 Description:
   This function will select the inverted B input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedBInputEnable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedBInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateAInputEnable (CMP_MODULE_ID index)

 Summary:
   A input connected to OR gate.

 Description:
   This function will select the A input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateAInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateAInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateAInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate A input disable.

 Description:
   This function will disable the A input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateAInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateAInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedAInputDisable (CMP_MODULE_ID index)

 Summary:
  OR gate inverted A input disable.

 Description:
   This function will disable the inverted A input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedAInputDisable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedAInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_OrGateInvertedAInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted A input connected to OR gate.

 Description:
   This function will select the inverted A input as the input to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_OrGateInvertedAInputEnable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_OrGateInvertedAInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_NegativeAndGateOutputEnable (CMP_MODULE_ID index)

 Summary:
   Negative AND gate output enable.

 Description:
   This function will enable the negative AND gate output to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_NegativeAndGateOutputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_NegativeAndGateOutputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_NegativeAndGateOutputDisable (CMP_MODULE_ID index)

 Summary:
   Negative AND gate output disable.

 Description:
   This function will disable the negative AND gate output to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_NegativeAndGateOutputDisable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_NegativeAndGateOutputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_PositiveAndGateOutputEnable (CMP_MODULE_ID index)

 Summary:
   Positive AND gate output enable.

 Description:
   This function will enable the positive AND gate output to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_PositiveAndGateOutputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_PositiveAndGateOutputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_PositiveAndGateOutputDisable (CMP_MODULE_ID index)

 Summary:
   Positive AND gate output disable.

 Description:
   This function will disable the positive AND gate output to the OR gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_PositiveAndGateOutputDisable (MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_PositiveAndGateOutputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateCInputEnable (CMP_MODULE_ID index)

 Summary:
   C input enabled as input to the AND gate.

 Description:
   This function will select the C input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateCInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateCInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateCInputDisable (CMP_MODULE_ID index)

 Summary:
   C input disabled as input to the AND gate.

 Description:
   This function will disable the C input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateCInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateCInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedCInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted C input enabled as input to the AND gate.

 Description:
   This function will enable the inverted C input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedCInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedCInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedCInputDisable (CMP_MODULE_ID index)

 Summary:
   Inverted C input disabled as input to the AND gate.

 Description:
   This function will disable the inverted C input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedCInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedCInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateBInputEnable (CMP_MODULE_ID index)

 Summary:
   B input enabled as input to the AND gate.

 Description:
   This function will select the B input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateBInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateBInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateBInputDisable (CMP_MODULE_ID index)

 Summary:
   B input disabled as input to the AND gate.

 Description:
   This function will disable the B input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateBInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateBInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedBInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted B input enabled as input to the AND gate.

 Description:
   This function will enable the inverted B input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedBInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedBInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedBInputDisable (CMP_MODULE_ID index)

 Summary:
   Inverted B input disabled as input to the AND gate.

 Description:
   This function will disable the inverted B input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedBInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedBInputDisable (CMP_MODULE_ID index);


// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateAInputEnable (CMP_MODULE_ID index)

 Summary:
   A input enabled as input to the AND gate.

 Description:
   This function will select the A input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateAInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateAInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateAInputDisable (CMP_MODULE_ID index)

 Summary:
   A input disabled as input to the AND gate

 Description:
   This function will disable the A input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateAInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateAInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedAInputEnable (CMP_MODULE_ID index)

 Summary:
   Inverted A input enabled as input to the AND gate.

 Description:
   This function will enable the inverted A input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedAInputEnable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedAInputEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
   void PLIB_CMP_AndGateInvertedAInputDisable (CMP_MODULE_ID index)

 Summary:
   Inverted A input disabled as input to the AND gate.

 Description:
   This function will disable the inverted A input as the input to the AND gate.

 Precondition:
   None.

 Parameters:
   index           - Identifier for the device instance to be configured

 Returns:
   None.

 Example:
   <code>
   // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
   // application developer.
   // PLIB_CMP_AndGateInvertedAInputDisable(MY_CMP_INSTANCE);
   </code>

 Remarks:
   Note: This feature is not available on all devices. Please refer to the
   specific device data sheet for availability.
*/
void PLIB_CMP_AndGateInvertedAInputDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_FilterInputClockSelect (CMP_MODULE_ID index,CMP_FILTER_CLOCK inputclock)

  Summary:
    Comparator filter input clock select.

  Description:
    This function will select the Comparator filter input clock.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    inputclock      - One of the possible values from CMP_FILTER_CLOCK

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_FilterInputClockSelect (MY_CMP_INSTANCE,CMP_FILTER_CLOCK_FP);
    </code>

  Remarks:
    Note: This feature is not available on all devices. Please refer to the
    specific device data sheet for availability.
*/

void PLIB_CMP_FilterInputClockSelect (CMP_MODULE_ID index, CMP_FILTER_CLOCK inputclock);

// *****************************************************************************
/* Function:
    void PLIB_CMP_FilterEnable (CMP_MODULE_ID index)

  Summary:
    Comparator filter enable.

  Description:
    This function will enable the Comparator digital filter.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_FilterEnable (MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature is not available on all devices. Please refer to the
    specific device data sheet for availability.
*/

void PLIB_CMP_FilterEnable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_FilterDisable (CMP_MODULE_ID index)

  Summary:
    Comparator filter disable.

  Description:
    This function will disable the Comparator digital filter.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    
  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_FilterDisable (MY_CMP_INSTANCE);
    </code>

  Remarks:
    Note: This feature is not available on all devices. Please refer to the
    specific device data sheet for availability.
*/

void PLIB_CMP_FilterDisable (CMP_MODULE_ID index);

// *****************************************************************************
/* Function:
    void PLIB_CMP_FilterClockDivideSelect (CMP_MODULE_ID index,CMP_CLOCK_DIVIDE scale)

  Summary:
    Comparator filter clock divide select.

  Description:
    This function will select the Comparator filter clock divide.

  Precondition: 
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    scale          - One of the possible values from CMP_CLOCK_DIVIDE

  Returns:
    None.

  Example:
    <code>
    // Where MY_CMP_INSTANCE, is the Comparator instance selected for use by the
    // application developer.
    // PLIB_CMP_FilterClockDivideSelect (MY_CMP_INSTANCE,CMP_FILTER_CLOCK_DIVIDE_1_2);
    </code>

  Remarks:
    Note: This feature is not available on all devices. Please refer to the
    specific device data sheet for availability.
*/

void PLIB_CMP_FilterClockDivideSelect (CMP_MODULE_ID index,CMP_CLOCK_DIVIDE scale);

// *****************************************************************************
// *****************************************************************************
// Section: Comparator Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_CMP_ExistsEnableControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the ComparatorEnableControl feature exists on the Comparator module.

  Description:
    This function identifies whether the ComparatorEnableControl feature is available on the
    Comparator module. When this function returns true, these functions are supported on 
    the device:
    - PLIB_CMP_Enable
    - PLIB_CMP_Disable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The ComparatorEnableControl feature is supported on the device
                    - false = The ComparatorEnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsEnableControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsOutputEnableControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the ComparatorOutputEnableControl feature exists on the Comparator module.

  Description:
    This function identifies whether the ComparatorOutputEnableControl feature is available 
    on the Comparator module. When this function returns true, these functions are supported 
    on the device:
    - PLIB_CMP_OutputEnable
    - PLIB_CMP_OutputDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                 - true  = The ComparatorOutputEnableControl feature is supported on the device
                 - false = The ComparatorOutputEnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsOutputEnableControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsInvertOutputControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the InvertOutputSelectControl feature exists on the Comparator module.

  Description:
    This function identifies whether the InvertOutputSelectControl feature is available 
    on the Comparator module. When this function returns true, these functions are 
    supported on the device:
    - PLIB_CMP_InvertedOutputSelect
    - PLIB_CMP_NonInvertedOutputSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                 - true  = The InvertOutputSelectControl feature is supported on the device
                 - false = The InvertOutputSelectControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsInvertOutputControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsOutputLevelControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the OutputLevelSelectControl feature exists on the Comparator module.

  Description:
    This function identifies whether the OutputLevelSelectControl feature is available 
    on the Comparator module. When this function returns true, these functions are 
    supported on the device:
    - PLIB_CMP_OutputHighSelect
    - PLIB_CMP_OutputLowSelect
    - PLIB_CMP_Cmp1OutputHighSelect
    - PLIB_CMP_Cmp1OutputLowSelect
    - PLIB_CMP_Cmp2OutputHighSelect
    - PLIB_CMP_Cmp2OutputLowSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The OutputLevelSelectControl feature is supported on the device
                    - false = The OutputLevelSelectControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsOutputLevelControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsInterruptEventSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the InterruptEventSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the InterruptEventSelect feature is available on 
    the Comparator module. When this function returns true, this function is
    supported on the device:
    - PLIB_CMP_InterruptEventSelect 

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The InterruptEventSelect feature is supported on the device
                    - false = The InterruptEventSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsInterruptEventSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsNonInvertingInputSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the NonInvertingInputSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the NonInvertingInputSelect feature is available
    on the Comparator module. When this function returns true, this function is
    supported on the device:
    - PLIB_CMP_adc 

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The NonInvertingInputSelect feature is supported on the device
                    - false = The NonInvertingInputSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsNonInvertingInputSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsInvertingInputSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the InvertingInputSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the InvertingInputSelect feature is available
    on the Comparator module. When this function returns true, this function is
    supported on the device:
    - PLIB_CMP_InvertingInputChannelSelect 

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The InvertingInputSelect feature is supported on the device
                    - false = The InvertingInputSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsInvertingInputSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsStopInIdle( CMP_MODULE_ID index )

  Summary:
    Identifies whether the StopInIdle feature exists on the Comparator module.

  Description:
    This function identifies whether the StopInIdle feature is available
    on the Comparator module. When this function returns true, these functions are
    supported on the device:
    - PLIB_CMP_StopInIdleModeEnable
    - PLIB_CMP_StopInIdleModeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The StopInIdle feature is supported on the device
                    - false = The StopInIdle feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsStopInIdle( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFEnableControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFEnableControl feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFEnableControl feature is available
    on the Comparator module. When this function returns true, these functions are
    supported on the device:
    - PLIB_CMP_CVREF_Enable
    - PLIB_CMP_CVREF_Disable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFEnableControl feature is supported on the device
                    - false = The CVREFEnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFEnableControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFOutputEnableControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFOutputEnableControl feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFOutputEnableControl feature is available
    on the Comparator module. When this function returns true, these functions are
    supported on the device:
    - PLIB_CMP_CVREF_OutputEnable
    - PLIB_CMP_CVREF_OutputDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFOutputEnableControl feature is supported on the device
                    - false = The CVREFOutputEnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFOutputEnableControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFWideRangeControl( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFWideRangeControl feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFWideRangeControl feature is available
    on the Comparator module. When this function returns true, these functions are
    supported on the device:
    - PLIB_CMP_CVREF_WideRangeEnable
    - PLIB_CMP_CVREF_WideRangeDisable
    - PLIB_CMP_CVREF_WideRangeIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFWideRangeControl feature is supported on the device
                    - false = The CVREFWideRangeControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFWideRangeControl( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFVoltageRangeSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFVoltageRangeSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFVoltageRangeSelect feature is available
    on the Comparator module. When this function returns true, the following function is 
    supported on the device:
    - PLIB_CMP_CVREF_SourceVoltageSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFVoltageRangeSelect feature is supported on the device
                    - false = The CVREFVoltageRangeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFVoltageRangeSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFRefVoltageRangeSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFRefVoltageRangeSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFRefVoltageRangeSelect feature is available 
    on the Comparator module. When this function returns true, the following function is 
    supported on the device:
    - PLIB_CMP_CVREF_ReferenceVoltageSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFRefVoltageRangeSelect feature is supported on the device
                    - false = The CVREFRefVoltageRangeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFRefVoltageRangeSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFBGRefVoltageRangeSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFBGRefVoltageRangeSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFBGRefVoltageRangeSelect feature is 
    available on the Comparator module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_CMP_CVREF_BandGapReferenceSourceSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFBGRefVoltageRangeSelect feature is supported on the device
                    - false = The CVREFBGRefVoltageRangeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFBGRefVoltageRangeSelect( CMP_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_CMP_ExistsCVREFValueSelect( CMP_MODULE_ID index )

  Summary:
    Identifies whether the CVREFValueSelect feature exists on the Comparator module.

  Description:
    This function identifies whether the CVREFValueSelect feature is available on 
    the Comparator module. When this function returns true, the following function is
    supported on the device:
    - PLIB_CMP_CVREF_ValueSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
                    - true  = The CVREFValueSelect feature is supported on the device
                    - false = The CVREFValueSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_CMP_ExistsCVREFValueSelect( CMP_MODULE_ID index );

#endif // #ifndef _PLIB_CMP_H
/*******************************************************************************
 End of File
*/

