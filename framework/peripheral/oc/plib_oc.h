/*******************************************************************************
  Output Compare Module Peripheral Library Interface Header

  Company:
    Microchip Technology Inc.

  File Name:
    plib_oc.h

  Summary:
    This file contains the interface definition for the Output Compare (OC)
    peripheral library.

  Description:
    This library provides a low-level abstraction of the Output Compare module
    on Microchip microcontrollers with a convenient C language interface.
    It can be used to simplify low-level access to the module without the necessity
    of interacting directly with the module's registers, thus hiding differences
    between one microcontroller variant and another.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright © 2013 released Microchip Technology Inc. All rights reserved.

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

#ifndef _PLIB_OC_H_    // Guards against multiple inclusion
#define _PLIB_OC_H_

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/
#include "processor/oc_processor.h"

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

//*******************************************************************************
/*  Function:
   void PLIB_OC_Enable( OC_MODULE_ID index )

  Summary:
   Enables the OC module.

  Description:
    This function enables the OC module.

  Precondition:
    The module should be appropriately configured before being enabled.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    //Do all the other configurations before enabling.

    PLIB_OC_Enable(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsEnableControl in your application to determine
    whether this feature is available.
*******************************************************************************/

void PLIB_OC_Enable( OC_MODULE_ID index );


//*******************************************************************************
/*  Function:
   void PLIB_OC_Disable( OC_MODULE_ID index )

  Summary:
   Disable the OC module

  Description:
    This function disables the OC module.

  Precondition:
    None.

  Parameters:
    index       - Identifies the OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_Disable(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsEnableControl in your application to determine
    whether this feature is available.
*******************************************************************************/

void PLIB_OC_Disable( OC_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_OC_AlternateClockEnable(OC_MODULE_ID index

  Summary:
    Selects the alternate clock source.

  Description:
    Selects the alternate clock source instead of Timer 2/3.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
  <code>
    // Call system service to unlock oscillator
    #define MY_OC_ID OC_ID_1
    PLIB_OC_AlternateClockEnable( MY_OC_ID );
  </code>

  Remarks:
    The feature is not supported on all devices.  Check your device's data sheet.
    A system unlock must be performed before this function can be executed.
    This function applies to all input capture modules, regardless of the
    OC_MODULE_ID passed in the call.
*/

void PLIB_OC_AlternateClockEnable(OC_MODULE_ID index);


// *****************************************************************************
/* Function:
    void PLIB_OC_AlternateClockDisable(OC_MODULE_ID index

  Summary:
    Selects Timer 2/3.instead of the alternate clock source.

  Description:
    Selects Timer 2/3.instead of the alternate clock source.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
  <code>
    // Call system service to unlock oscillator
    #define MY_OC_ID OC_ID_1
    PLIB_OC_AlternateClockDisable( MY_OC_ID );
  </code>

  Remarks:
    The feature is not supported on all devices.  Check your device's data sheet.
    A system unlock must be performed before this function can be executed.
    This function applies to all input capture modules, regardless of the
    OC_MODULE_ID passed in the call.
*/

void PLIB_OC_AlternateClockDisable(OC_MODULE_ID index);


// *****************************************************************************
/* Function:
    void PLIB_OC_StopInIdleEnable( OC_MODULE_ID index )

  Summary:
    Discontinues OC module operation when the device enters Idle mode

  Description:
    This function discontinues OC module operation when the device enters
    Idle mode.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_StopInIdleEnable(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsStopInIdle in your application to determine
    whether this feature is available.
*/

void PLIB_OC_StopInIdleEnable( OC_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_OC_StopInIdleDisable( OC_MODULE_ID index )

  Summary:
    OC module continues operating when the device enters Idle mode

  Description:
    The function continues OC module operation when the device enters Idle mode.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_StopInIdleDisable(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsStopInIdle in your application to determine
    whether this feature is available.
*/

void PLIB_OC_StopInIdleDisable( OC_MODULE_ID index);


// *****************************************************************************
/* Function:
    void PLIB_OC_Buffer32BitSet( OC_MODULE_ID index, uint32_t val32Bit)

  Summary:
    Sets a 32-bit primary compare value for compare operations.

  Description:
    This function sets a 32-bit primary compare value for compare operations in
    all modes except PWM modes.

  Precondition:
    The PWM mode of operation should not be selected. The buffer size should be set to
    32-bits by the PLIB_OC_BufferSizeSelect() function.

  Parameters:
    index           - Identifies the desired OC module
    val32Bit        - Sets a 32-bit primary compare value

  Returns:
    None

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_Buffer32BitSet(MY_OC_ID, 0x000000FF);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsBufferValue in your application to determine
    whether this feature is available.
*/

void PLIB_OC_Buffer32BitSet( OC_MODULE_ID index, uint32_t val32Bit);


   // *****************************************************************************
/* Function:
    void PLIB_OC_Buffer16BitSet( OC_MODULE_ID index, uint16_t val16Bit)

  Summary:
    Sets a 16-bit primary compare value for compare operations.

  Description:
    This function sets a 16-bit primary compare value for compare operations in all
    modes except PWM modes.

  Precondition:
    The PWM mode of operation should not be selected. The buffer size should be set
    to 16-bits by the PLIB_OC_BufferSizeSelect() function.

  Parameters:
    index           - Identifies the desired OC module
    val16Bit        - Sets a 16-bit primary compare value
  Returns:
    None

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_Buffer16BitSet(MY_OC_ID, 0x00FF);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsBufferValue in your application to determine
    whether this feature is available.
*/

void PLIB_OC_Buffer16BitSet( OC_MODULE_ID index, uint16_t val16Bit);


//*****************************************************************************
/* Function:
    void PLIB_OC_PulseWidth32BitSet( OC_MODULE_ID index,uint32_t pulseWidth)

  Summary:
    Sets a 32-bit pulse width for OC module output.

  Description:
    This function sets a 32-bit pulse width for OC module in dual compare modes.
    A dual compare mode can be selected using PLIB_OC_ModeSelect() routine. Secondary
    compare match event (pulse width) decides the trailing(falling) edge of OC
    module output.

  Precondition:
    Dual compare operation should be selected. The buffer size should be set to
    32-bits by the PLIB_OC_BufferSizeSelect() function.

  Parameters:
    index           - Identifies the desired OC module
    pulseWidth      - Pulse width value

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_PulseWidth32BitSet(MY_OC_ID, 0x00000FFF);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsPulseWidth in your application to determine
    whether this feature is available.
*/

void PLIB_OC_PulseWidth32BitSet( OC_MODULE_ID index, uint32_t pulseWidth);


//*****************************************************************************
/* Function:
    void PLIB_OC_PulseWidth16BitSet( OC_MODULE_ID index,uint16_t pulseWidth)

  Summary:
    Sets a 16-bit pulse width for OC module output.

  Description:
    This function sets a 16-bit pulse width for the OC module in dual compare
    modes. A dual compare mode can be selected using the PLIB_OC_ModeSelect()
    function. Secondary compare match event (pulse width) decides the
    trailing (falling) edge of the OC module output.

  Precondition:
    Dual compare operation should be selected. The buffer size should be set to
    16-bits by the PLIB_OC_BufferSizeSelect() function.

  Parameters:
    index           - Identifies the desired OC module
    pulseWidth      - Pulse width value

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_PulseWidth16BitSet(MY_OC_ID, 0x0FFF);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsPulseWidth in your application to determine
    whether this feature is available.
*/

void PLIB_OC_PulseWidth16BitSet( OC_MODULE_ID index, uint16_t pulseWidth);


//*****************************************************************************
/* Function:
     void PLIB_OC_TriggerSet(OC_MODULE_ID index)

  Summary:
    Sets the trigger status for the OC module.

  Description:
    This function sets the trigger status for the OC module.

  Precondition:
    Dual compare mode must be selected for this function.

  Parameters:
    index           - Identifies the desired OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_TriggerSet(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsTriggerControl in your application to determine
    whether this feature is available.
*/

void PLIB_OC_TriggerSet(OC_MODULE_ID index);


//*****************************************************************************
/* Function:
     void PLIB_OC_TriggerClear(OC_MODULE_ID index)

  Summary:
    Clears the trigger status for the OC module.

  Description:
    This function clears the trigger status for the OC module.

  Precondition:
    Dual compare mode must be selected for this function.

  Parameters:
    index           - Identifies the desired OC module

  Returns:
    None

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_TriggerClear(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsTriggerControl in your application to determine
    whether this feature is available.
*/

void PLIB_OC_TriggerClear(OC_MODULE_ID index);


//*****************************************************************************
/* Function:
     void PLIB_OC_PWMDutyCycleResolutionSet(OC_MODULE_ID index, OC_CLOCK_RESOLUTION clkResolution)

  Summary:
    Sets the PWM duty cycle resolution and delays the falling edge of OC output
    in compare modes.

  Description:
    This function sets the PWM duty cycle resolution in PWM mode and delays the
    falling edge of OC output in compare modes.

  Precondition:
    Dual compare mode must be selected for this function.

  Parameters:
    index           - Identifies the desired OC module
    clkResolution   - Select clock resolution

  Returns:
    None

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    PLIB_OC_PWMDutyCycleResolutionSet(MY_OC_ID,OC_CLOCK_P1);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsPWMDutyCycleResolutionControl in your application to determine
    whether this feature is available.
*/

void PLIB_OC_PWMDutyCycleResolutionSet(OC_MODULE_ID index, OC_CLOCK_RESOLUTION clkResolution);


// *****************************************************************************
/* Function:
    void PLIB_OC_TimerSelect( OC_MODULE_ID index, OC_16BIT_TIMERS tmr )

  Summary:
    Selects a clock source for the OC module.

  Description:
    This function selects a clock source for the OC module if the 16-bit
    time base is set.

  Precondition:
    The 16-bit time base needs to be set.

  Parameters:
    index      - Identifies the desired OC module
    tmr        - Identifies the timer

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // 16-bit Timer2 is selected
    PLIB_OC_TimerSelect(MY_OC_ID, OC_TIMER_16BIT_TMR2);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsTimerSelect in your application to determine
    whether this feature is available.
*/
void PLIB_OC_TimerSelect( OC_MODULE_ID index, OC_16BIT_TIMERS tmr );


//*****************************************************************************
/* Function:
    void PLIB_OC_FaultInputSelect(OC_MODULE_ID index, OC_FAULTS flt)

  Summary:
    Selects a Fault input for the OC module.

  Description:
    This function selects a Fault input for the OC module.

  Precondition:
    Set the operation mode using PLIB_OC_ModeSelect() before selecting the Fault input.

  Parameters:
    index      - Identifies the desired OC module
    flt        - Identifies the OC fault input

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Fault B is enabled for Output Compare Module
    PLIB_OC_FaultInputSelect(MY_OC_ID, OC_FAULT_B);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsFaultInput in your application to determine
    whether this feature is available.
*/

void PLIB_OC_FaultInputSelect(OC_MODULE_ID index, OC_FAULTS flt);


//*****************************************************************************
/* Function:
    void PLIB_OC_FaultModeSelect(OC_MODULE_ID index, OC_FAULT_MODES modes)

  Summary:
    Selects an automatic or software-based mode to clear the Fault.

  Description:
    This function selects a mode to clear the Fault mode. The Fault mode can be
    reset automatically or by software once the Fault source ceases to exist.

  Precondition:
    Set the operation mode using PLIB_OC_ModeSelect() routine before selecting
    the fault input.

  Parameters:
    index      - Identifies the desired OC module
    modes      - Identifies the mode to reset Fault status

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Fault mode is maintained even after fault ceases. Fault mode is reset in software.
    PLIB_OC_FaultModeSelect(MY_OC_ID, OC_SOFTWARE_CLEAR);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsFaultModeSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_FaultModeSelect(OC_MODULE_ID index, OC_FAULT_MODES modes);

//*****************************************************************************
/* Function:
    void PLIB_OC_PolarityInvertedEnable(OC_MODULE_ID index)

  Summary:
    Output compare polarity is inverted.

  Description:
    This function inverts the polarity of the OC module output.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Invert polarity of OC module output
    PLIB_OC_PolarityInvertedEnable(MY_OC_ID);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsPolarityInvert in your application to determine
    whether this feature is available.
*/

void PLIB_OC_PolarityInvertedEnable(OC_MODULE_ID index);


//*****************************************************************************
/* Function:
    void PLIB_OC_PolarityInvertedDisable(OC_MODULE_ID index)

  Summary:
    Disables OC module output inversion polarity.

  Description:
    This function disables polarity inversion of OC module output.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Polarity of OC module output is Non-inverted
    PLIB_OC_PolarityInvertedDisable(OC_MODULE_ID index);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsPolarityInvert in your application to determine
    whether this feature is available.
*/

void PLIB_OC_PolarityInvertedDisable(OC_MODULE_ID index);


//*******************************************************************************
/*  Function:
   void PLIB_OC_FaultTristateSelect(OC_MODULE_ID index, OC_FAULT_TRISTATE tristateSel)

  Summary:
   The OC module output can be tristated or driven to a known state when a Fault occurs.

  Description:
   This function is used to enable or disable tristating of OC module outputs when a
   Fault occurs.

  Precondition:
   None.

  Parameters:
    index       - Identifies the desired OC module
    tristateSel - Enable/Disable Tristate

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    //Tristate OC module output

    PLIB_OC_FaultTristateSelect(MY_OC_ID,OC_ENABLE_TRISTATE);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsFaultTristateSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_FaultTristateSelect(OC_MODULE_ID index, OC_FAULT_TRISTATE tristateSel);


//*******************************************************************************
/*  Function:
   void PLIB_OC_FaultOutSelect( OC_MODULE_ID index, OC_FAULT_OUT fltState )

  Summary:
   OC output pin is driven to a known state on a Fault.

  Description:
   This function sets OC output to a known state on occurrence of a Fault in Edge
   or Center-Aligned PWM modes.

  Precondition:
   Edge or Center-Aligned PWM mode with Faults enabled should be selected. OC module
   output tristate should be disabled on occurrence of a Fault via
   PLIB_OC_TriStateDisable().

  Parameters:
    index      - Identifies the desired OC module
    fltState   - Identifies the high or low state to which the output is driven
                 on a fault

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1

    //PWM output is set to High on occurrence of fault

    PLIB_OC_FaultOutSelect(MY_OC_ID,OC_HIGH);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsFaultOutSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_FaultOutSelect( OC_MODULE_ID index, OC_FAULT_OUT fltState );


//*****************************************************************************
/* Function:
    void PLIB_OC_TriggerStatusModeSelect(OC_MODULE_ID index, OC_TRIGGER_STATUS_MODES modes)

  Summary:
    Selects the trigger status reset mode.

  Description:
    This function lets the user to reset the trigger status via software or a
    compare match.

  Precondition:
   None.

  Parameters:
    index      - Identifies the desired OC module
    modes      - Identifies the trigger status reset mode

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    //Trigger status is reset by compare match
    PLIB_OC_TriggerStatusModeSelect(MY_OC_ID, OC_TRIGGER_STATUS_MATCH);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsTriggerStatusModeSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_TriggerStatusModeSelect(OC_MODULE_ID index, OC_TRIGGER_STATUS_MODES modes);


//*****************************************************************************
/* Function:
    void PLIB_OC_SyncModeSelect(OC_MODULE_ID index, OC_SYNC_MODES mode)

  Summary:
    Selects the synchronization mode for the OC module.

  Description:
    This function selects the synchronization mode for Othe OC module. The
    Synchronous or Asynchronous mode of operation can be selected.

  Precondition:
    If Asynchronous mode is selected and an OC trigger is selected, that OC
    module must be disabled first before enabling the trigger functionality.

  Parameters:
    index      - Identifies the desired OC module
    mode       - Identifies the mode (Synchronous or Asynchronous)

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Synchronous mode of operation is selected.
    PLIB_OC_SyncModeSelect(MY_OC_ID, OC_MODE_SYNC);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsSyncModeSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_SyncModeSelect(OC_MODULE_ID index, OC_SYNC_MODES mode);


 //*****************************************************************************
/* Function:
    void PLIB_OC_SyncSourceSelect(OC_MODULE_ID index, OC_SYNC_SOURCES src)

  Summary:
    Selects the input source for synchronous or asynchronous (triggered) operation
    of the OC module.

  Description:
    This function selects the input source for synchronous or asynchronous
    (triggered) operation of the OC module.

  Precondition:
    If an OC trigger is selected, that OC module must be disabled before it is
    configured to be used as a trigger to the next OC module.

  Parameters:
    index      - Identifies the desired OC module
    src        - Identifies the input source

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    //Input Capture is selected as the input source
    PLIB_OC_SyncSourceSelect(MY_OC_ID, OC_SYNC_SOURCE_IC6);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsSyncSourceSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_SyncSourceSelect(OC_MODULE_ID index, OC_SYNC_SOURCES src);


// *****************************************************************************
/* Function:
    void PLIB_OC_BufferSizeSelect( OC_MODULE_ID index, OC_BUFFER_SIZE size )

  Summary:
    Sets the buffer size and pulse width to 16-bits or 32-bits.

  Description:
    This function sets the size of the buffer and pulse width to 16-bits or 32-bits.
    The choice is made based on whether a 16-bit timer or a 32-bit timer is selected.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module
    size       - Identifies the size of compare value

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Buffer size and pulse width size are set to 32-bits
    PLIB_OC_BufferSizeSelect(MY_OC_ID, OC_BUFFER_SIZE_32BIT);
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsBufferSize in your application to determine
    whether this feature is available.
*/

void PLIB_OC_BufferSizeSelect( OC_MODULE_ID index, OC_BUFFER_SIZE size );


// *****************************************************************************
/* Function:
    void PLIB_OC_ModeSelect( OC_MODULE_ID index, OC_COMPARE_MODES cmpMode )

  Summary:
    Selects the compare mode for the OC module.

  Description:
    This function selects the compare mode for the OC module.

  Precondition:
    The OC module must be turned off before a new mode is selected. The OC module
    is turned off via PLIB_OC_ModeSelect(MY_OC_ID,OC_COMPARE_TURN_OFF_MODE)

  Parameters:
    index      - Identifies the desired OC module
    cmpMode    - Identifies the compare mode for OC module

  Returns:
    None.

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    // Dual compare continuous pulse mode is selected
    PLIB_OC_ModeSelect(MY_OC_ID, OC_DUAL_COMPARE_CONTINUOUS_PULSE_MODE );
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsCompareModeSelect in your application to determine
    whether this feature is available.
*/

void PLIB_OC_ModeSelect( OC_MODULE_ID index, OC_COMPARE_MODES cmpMode );


// *****************************************************************************
/* Function:
   bool PLIB_OC_FaultHasOccurred(OC_MODULE_ID index)

  Summary:
   Checks if a PWM fault has occurred.

  Description:
   This function returns 'true' if a PWM Fault has occurred and 'false' if no
   Fault condition exists.

  Precondition:
   This function should be used only in Edge or Center-Aligned PWM mode
   set by the PLIB_OC_ModeSelect() function.

  Parameters:
   index        - Identifies the desired OC module

  Returns:
   bool         - true  - PWM Fault has occurred
                - false - No PWM fault

  Example:
  <code>
    #define MY_OC_ID OC_ID_1
    if(!PLIB_OC_FaultHasOccurred(MY_OC_ID))
    {
        // Do some operation
    };
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsFaultStatus in your application to determine
    whether this feature is available.

*/

bool PLIB_OC_FaultHasOccurred(OC_MODULE_ID index);


//*****************************************************************************
/* Function:
    bool PLIB_OC_IsTriggered(OC_MODULE_ID index)

  Summary:
    Checks whether or not a timer source has been triggered.

  Description:
    This function checks whether Output Compare timer has been triggered or not.
    This function returns 'true' if OC timer is triggered and running and 'false'
    if the OC timer is cleared and stopped.

  Precondition:
    None.

  Parameters:
    index      - Identifies the desired OC module

  Returns:
    bool       - true  - OC timer is triggered and running
               - false - OC timer is stopped and held in clear

  Example:
    <code>
    #define MY_OC_ID OC_ID_1
    if(!PLIB_OC_IsTriggered(MY_OC_ID))
    {
        // Do some operation
    };
    </code>

  Remarks:
    This feature may not be available on all devices. Please refer to the
    specific device data sheet to determine availability or use
    PLIB_OC_ExistsTimerTriggered in your application to determine
    whether this feature is available.
*/

bool PLIB_OC_IsTriggered(OC_MODULE_ID index);


// *****************************************************************************
// *****************************************************************************
// Section: OC Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device.
*/

//******************************************************************************
//******************************************************************************
/* Function :  bool PLIB_OC_ExistsEnableControl( OC_MODULE_ID index )

  Summary:
    Identifies whether the EnableControl feature exists on the OC module.

  Description:
    This function identifies whether the EnableControl feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_Enable
    - PLIB_OC_Disable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the EnableControl feature is supported on the device
    - false  - If the EnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsEnableControl( OC_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_OC_ExistsAlternateClock( OC_MODULE_ID index )

  Summary:
    Identifies whether the AlternateClock feature exists on the OC module

  Description:
    This function identifies whether the AlternateClock feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_AlternateClockEnable
    - PLIB_OC_AlternateClockDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AlternateClock feature is supported on the device
    - false  - The AlternateClock feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsAlternateClock( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsStopInIdle( OC_MODULE_ID index )

  Summary:
    Identifies whether the StopInIdle feature exists on the OC module.

  Description:
    This function identifies whether the StopInIdle feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_StopInIdleEnable
    - PLIB_OC_StopInIdleDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the StopInIdle feature is supported on the device
    - false  - If the StopInIdle feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsStopInIdle( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsFaultInput( OC_MODULE_ID index )

  Summary:
    Identifies whether the FaultInput feature exists on the OC module.

  Description:
    This function identifies whether the FaultInput feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_FaultInputSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the FaultInput feature is supported on the device
    - false  - If the FaultInput feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsFaultInput( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsFaultStatus( OC_MODULE_ID index )

  Summary:
    Identifies whether the FaultStatus feature exists on the OC module.

  Description:
    This function identifies whether the FaultStatus feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_FaultHasOccurred

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the FaultStatus feature is supported on the device
    - false  - If the FaultStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsFaultStatus( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsTimerSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the TimerSelect feature exists on the OC module.

  Description:
    This function identifies whether the TimerSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_TimerSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the TimerSelect feature is supported on the device
    - false  - If the TimerSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsTimerSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsBufferValue( OC_MODULE_ID index )

  Summary:
    Identifies whether the BufferValue feature exists on the OC module.

  Description:
    This function identifies whether the BufferValue feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_Buffer32BitSet
    - PLIB_OC_Buffer16BitSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the BufferValue feature is supported on the device
    - false  - If the BufferValue feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsBufferValue( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsPulseWidth( OC_MODULE_ID index )

  Summary:
    Identifies whether the PulseWidth feature exists on the OC module.

  Description:
    This function identifies whether the PulseWidth feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_PulseWidth32BitSet
    - PLIB_OC_PulseWidth16BitSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the PulseWidth feature is supported on the device
    - false  - If the PulseWidth feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsPulseWidth( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsBufferSize( OC_MODULE_ID index )

  Summary:
    Identifies whether the BufferSize feature exists on the OC module.

  Description:
    This function identifies whether the BufferSize feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_BufferSizeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the BufferSize feature is supported on the device
    - false  - If the BufferSize feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsBufferSize( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsCompareModeSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the CompareModeSelect feature exists on the OC module.

  Description:
    This function identifies whether the CompareModeSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_ModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the CompareModeSelect feature is supported on the device
    - false  - If the CompareModeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsCompareModeSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsTriggerControl( OC_MODULE_ID index )

  Summary:
    Identifies whether the TriggerControl feature exists on the OC module.

  Description:
    This function identifies whether the TriggerControl feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_TriggerSet
    - PLIB_OC_TriggerClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the TriggerControl feature is supported on the device
    - false  - If the TriggerControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsTriggerControl( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsPWMDutyCycleResolutionControl( OC_MODULE_ID index )

  Summary:
    Identifies whether the PWMDutyCycleResolution feature exists on the OC module.

  Description:
    This function identifies whether the PWMDutyCycleResolution feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_PWMDutyCycleResolutionSet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the PWMDutyCycleResolution feature is supported on the device
    - false  - If the PWMDutyCycleResolution feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsPWMDutyCycleResolutionControl( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsPolarityInvert( OC_MODULE_ID index )

  Summary:
    Identifies whether the PolarityInvert feature exists on the OC module.

  Description:
    This function identifies whether the PolarityInvert feature is available on the OC module.
    When this function returns true, these functions are supported on the device:
    - PLIB_OC_PolarityInvertedEnable
    - PLIB_OC_PolarityInvertedDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the PolarityInvert feature is supported on the device
    - false  - If the PolarityInvert feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsPolarityInvert( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsFaultModeSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the FaultModeSelect feature exists on the OC module.

  Description:
    This function identifies whether the FaultModeSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_FaultModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the FaultModeSelect feature is supported on the device
    - false  - If the FaultModeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsFaultModeSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsFaultTristateSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the FaultTristateSelect feature exists on the OC module.

  Description:
    This function identifies whether the FaultTristateSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_FaultTristateSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the FaultTristateSelect feature is supported on the device
    - false  - If the FaultTristateSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsFaultTristateSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsSyncModeSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the SyncModeSelect feature exists on the OC module.

  Description:
    This function identifies whether the SyncModeSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_SyncModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the SyncModeSelect feature is supported on the device
    - false  - If the SyncModeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsSyncModeSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsSyncSourceSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the SyncSourceSelect feature exists on the OC module.

  Description:
    This function identifies whether the SyncSourceSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_SyncSourceSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the SyncSourceSelect feature is supported on the device
    - false  - If the SyncSourceSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsSyncSourceSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsTriggerStatusModeSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the TriggerStatusModeSelect feature exists on the OC module.

  Description:
    This function identifies whether the TriggerStatusModeSelect feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_TriggerStatusModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the TriggerStatusModeSelect feature is supported on the device
    - false  - If the TriggerStatusModeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsTriggerStatusModeSelect( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsTimerTriggered( OC_MODULE_ID index )

  Summary:
    Identifies whether the TimerTriggered feature exists on the OC module.

  Description:
    This function identifies whether the TimerTriggered feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_IsTriggered

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the TimerTriggered feature is supported on the device
    - false  - If the TimerTriggered feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsTimerTriggered( OC_MODULE_ID index );


//******************************************************************************
/* Function :  bool PLIB_OC_ExistsFaultOutSelect( OC_MODULE_ID index )

  Summary:
    Identifies whether the FaultOut feature exists on the OC module.

  Description:
    This function identifies whether the FaultOut feature is available on the OC module.
    When this function returns true, this function is supported on the device:
    - PLIB_OC_FaultOutSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - If the FaultOut feature is supported on the device
    - false  - If the FaultOut feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_OC_ExistsFaultOutSelect( OC_MODULE_ID index );


#endif
/*******************************************************************************
 End of File
*/
