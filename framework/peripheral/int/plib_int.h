/***********************************************************************
  Company:
    Microchip Technology Inc.
  File Name:
    plib_int.h
  Summary:
    Defines the Interrupt Peripheral Library interface
  Description:
    Interrupt Peripheral Library Interface Header
    
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the
    Interrupt Peripheral Library for Microchip microcontrollers. The
    definitions in this file are for the Interrupt Controller module.   
  ***********************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc. All rights reserved.

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

#ifndef _PLIB_INT_H
#define _PLIB_INT_H

// *****************************************************************************
// *****************************************************************************
// Section: Includes
// *****************************************************************************
// *****************************************************************************

#include "peripheral/int/processor/int_processor.h"


// *****************************************************************************
// *****************************************************************************
// Section: Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************

//*******************************************************************************
/*
  Function:
    void PLIB_INT_SingleVectorShadowSetEnable ( INT_MODULE_ID index )

  Summary:
    Enables the Shadow Register Set in Single Vector mode.

  Description:
    This function enables usage of the "shadow" set of processor registers
    when operating in Single Vector mode.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 
	
  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SingleVectorShadowSetEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the SingleVectorShadowSet feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSingleVectorShadowSet API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SingleVectorShadowSetEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*  Function:
    void PLIB_INT_SingleVectorShadowSetDisable(INT_MODULE_ID index);

  Summary:
    Disables the Shadow Register Set in Single Vector mode.

  Description:
    This function disables usage of the "shadow" set of processor registers
    when operating in Single Vector mode.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SingleVectorShadowSetEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the SingleVectorShadowSet feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSingleVectorShadowSet API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SingleVectorShadowSetDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_MultiVectorSelect(INT_MODULE_ID index);

  Summary:
    Configures the Interrupt Controller for Multiple Vector mode.

  Description:
    This function configures the Interrupt Controller for Multiple Vector mode.
    Interrupt requests will serviced at the calculated vector addresses.  The CPU 
    vectors to the unique address for each vector number.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_MultiVectorSelect( INT_ID_0 );
    </code>

  Remarks:
    While the user can, during run-time, reconfigure the interrupt controller
    from Single Vector mode to Multiple Vector mode, such action is strongly
    discouraged, as it may result in undefined behavior.

    This function implements an operation of the VectorSelect feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorSelect API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_MultiVectorSelect ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_SingleVectorSelect(INT_MODULE_ID index);

  Summary:
    Configures the Interrupt Controller for Single Vector mode.

  Description:
    The function configures the Interrupt Controller for Single Vector mode.
    All interrupt requests will serviced at one vector address. The CPU vectors 
    to the same address for all interrupt sources.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SingleVectorSelect( INT_ID_0 );
    </code>

  Remarks:
    While the user can, during run-time, reconfigure the Interrupt Controller
    from Single Vector mode to Multiple Vector mode, such action is strongly
    discouraged, as it may result in undefined behavior.

    This function implements an operation of the VectorSelect feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorSelect API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SingleVectorSelect ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_ProximityTimerEnable ( 	INT_MODULE_ID index, 
                                            INT_PRIORITY_LEVEL priority )

  Summary:
    Enables the interrupt temporal-proximity timer and selects the priority
    levels that start the timer.

  Description:
    This function enables the interrupt temporal-proximity timer and selects the 
    priority levels that start the timer. One of the possible values from
    PLIB_INT_PRIORITY_LEVEL can be selected. Interrupts of that priority and
    lower start the temporal proximity timer. 
    
  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 
			
	priority - One of possible values from INT_PRIORITY_LEVEL.

  Returns:
    None.

  Example:
    <code>
    //Interrupts of group priority 3 or lower start the temporal proximity timer
    PLIB_INT_ProximityTimerEnable( INT_ID_0, INT_PRIORITY_LEVEL3 );
    </code>

  Remarks:
    This function implements an operation of the ProximityTimerEnable feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsProximityTimerEnable API to write flexible code 
    to automatically determine if this feature is available.

    Choosing INT_PRIORITY_0 disables the proximity timer (exactly the
    same as if PLIB_INT_ProximityTimerDisable had been called.
*/

void PLIB_INT_ProximityTimerEnable ( INT_MODULE_ID index, 
                                     INT_PRIORITY_LEVEL priority );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_ProximityTimerDisable( INT_MODULE_ID index )

  Summary:
    Disables the interrupt temporal-proximity timer.

  Description:
    This function disables the interrupt temporal-proximity timer.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_ProximityTimerDisable(INT_PRIORITY_LEVEL3);
    </code>

  Remarks:
    This function implements an operation of the ProximityTimerEnable feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsProximityTimerEnable API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_ProximityTimerDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_ExternalRisingEdgeSelect ( INT_MODULE_ID index, 
												INT_EXTERNAL_SOURCES source )

  Summary:
    Selects the rising edge as the edge polarity of the external interrupt.

  Description:
    This function selects the rising edge as the edge polarity of the external
    interrupt.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 
			
    source - One or more of the values from INT_EXTERNAL_SOURCES.  Values can be
				combined using a bitwise "OR" operation.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_ExternalRisingEdgeSelect( INT_ID_0,
                                        ( INT_EXTERNAL_INT_SOURCE0 |
                                            INT_EXTERNAL_INT_SOURCE1 ) );
    </code>

  Remarks:
    This function implements an operation of the ExternalINTEdgeSelect feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsExternalINTEdgeSelect API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_ExternalRisingEdgeSelect ( INT_MODULE_ID index, 
											INT_EXTERNAL_SOURCES source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_ExternalFallingEdgeSelect ( INT_MODULE_ID index, INT_EXTERNAL_SOURCES source )

  Summary:
    Selects the falling edge as the edge polarity of the external interrupt.

  Description:
    This function selects the falling edge as the edge polarity of the external
    interrupt.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 

	source - One or more of the values from INT_EXTERNAL_SOURCES.  Values can be
			combined using a bitwise "OR" operation.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_ExternalFallingEdgeSelect( INT_ID_0,
                                        (INT_EXTERNAL_INT_SOURCE0 |
                                        INT_EXTERNAL_INT_SOURCE1) );
    </code>

  Remarks:
    This function implements an operation of the ExternalINTEdgeSelect feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsExternalINTEdgeSelect API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_ExternalFallingEdgeSelect ( INT_MODULE_ID index, INT_EXTERNAL_SOURCES source );


//*******************************************************************************
/*
  Function:
    INT_PRIORITY_LEVEL PLIB_INT_PriorityGet ( INT_MODULE_ID index )

  Summary:
    Returns the priority level of the latest interrupt presented to the CPU.

  Description:
    This function returns the priority level of the latest interrupt presented to
    the CPU.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    One of the possible values from INT_PRIORITY_LEVEL.

  Example:
    <code>
    INT_PRIORITY_LEVEL level = PLIB_INT_RequestedPriorityLevelGet( INT_ID_0 );
    </code>

  Remarks:
    This value should only be used when the interrupt controller is configured
    for single vector mode using the function PLIB_INT_SingleVectorSelect.

    This function implements an operation of the INTCPUPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsINTCPUPriority API to write flexible code 
    to automatically determine if this feature is available.
*/

INT_PRIORITY_LEVEL PLIB_INT_PriorityGet ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    INT_VECTOR PLIB_INT_VectorGet ( INT_MODULE_ID index )

  Summary:
    Returns the interrupt vector that is presented to the CPU.

  Description:
    This function returns the interrupt vector that is presented to the CPU.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    One of the possible values from INT_VECTOR.

  Example:
    <code>
    INT_VECTOR level = PLIB_INT_VectorGet( INT_ID_0 );
    </code>

  Remarks:
    This value should only be used when the interrupt controller is configured
    for single vector mode using the function PLIB_INT_MultiVectorDisable.

    This function implements an operation of the INTCPUVector feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsINTCPUVector API to write flexible code 
    to automatically determine if this feature is available.
*/

INT_VECTOR PLIB_INT_VectorGet ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_ProximityTimerSet ( INT_MODULE_ID index, uint32_t timerReloadValue )

  Summary:
    Sets the temporal proximity timer reload value.  This value is used to
    reload the proximity timer after it has been triggered by an interrupt
    event.

  Description:
    This function sets the temporal proximity timer reload value.  This value 
    is used to reload the proximity timer after it has been triggered by an 
    interrupt event.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 

	timerReloadValue - Timer reload value.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_ProximityTimerSet(INT_ID_0, 0x12345678);
    </code>

  Remarks:
    This function implements an operation of the ProximityTimerControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsProximityTimerControl API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_ProximityTimerSet ( INT_MODULE_ID index, uint32_t timerreloadvalue );


//*******************************************************************************
/*
  Function:
    uint32_t PLIB_INT_ProximityTimerGet(INT_MODULE_ID index);

  Summary:
    Returns the value used by the temporal proximity timer as a reload value
    when the temporal proximity timer is triggered by an interrupt event.

  Description:
    This function returns the value used by the temporal proximity timer as a
    reload value when the temporal proximity timer is triggered by an interrupt
    event.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 

  Returns:
    Timer reload value.

  Example:
    <code>
    uint32_t timer;

    timer = PLIB_INT_ProximityTimerGet( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the ProximityTimerControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsProximityTimerControl API to write flexible code 
    to automatically determine if this feature is available.
*/

uint32_t PLIB_INT_ProximityTimerGet ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    bool PLIB_INT_SourceFlagGet ( INT_MODULE_ID index, INT_SOURCE source )

  Summary:
    Returns the status of the interrupt flag for the selected source.

  Description:
    This function returns the status of the interrupt flag for the selected
    source. The flag is set when the interrupt request is recognized. The pending
    interrupt request will not cause further processing if the interrupt is not
    enabled using the function PLIB_INT_InterruptSourceEnable or if interrupts
    are not enabled (on processors that support the PLIB_INT_Enable feature).

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ).   
    
	source - One of the possible values from INT_SOURCE.

  Returns:
    true    - If the interrupt request is recognized for the source
    false   - If the interrupt request is not recognized for the source

  Example:
    <code>
    if(PLIB_INT_SourceFlagGet(INT_ID_0, INT_SOURCE_TIMER_1))
    {
        PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_1);
    }
    </code>

  Remarks:
    This function implements an operation of the SourceFlag feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceFlag API to write flexible code 
    to automatically determine if this feature is available.
*/

bool PLIB_INT_SourceFlagGet ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_SourceFlagSet ( INT_MODULE_ID index, INT_SOURCE source )

  Summary:
    Sets the status of the interrupt flag for the selected source.

  Description:
    This function sets the status of the interrupt flag for the selected source.
    This function will not be used during normal operation of the system. It is
    used to generate test interrupts for debug and testing purposes.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
		INT_ID_0 for all the devices which has only interrupt module ). 

	source - One of the possible values from INT_SOURCE.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SourceFlagSet(INT_ID_0,INT_SOURCE_TIMER_1);
    </code>

  Remarks:
    This function implements an operation of the SourceFlag feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceFlag API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SourceFlagSet ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_SourceFlagClear ( INT_MODULE_ID index, INT_SOURCE source );

  Summary:
    Clears the status of the interrupt flag for the selected source.

  Description:
    This function clears the status of the interrupt flag for the selected source.
    The flag is set when the interrupt request is identified. The pending
    interrupt request will not cause further processing if the interrupt is not
    enabled using the function PLIB_INT_InterruptSourceEnable or if interrupts
    are not enabled (on processors that support the PLIB_INT_Enable feature).


  Precondition:
    None.

  Parameters:
   index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 
  
    source - One of the possible values from INT_SOURCE.

  Returns:
    None.

  Example:
    <code>
    if(PLIB_INT_SourceFlagGet(INT_ID_0,INT_SOURCE_TIMER_1))
    {
        PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_TIMER_1);
    }
    </code>

  Remarks:
    This function implements an operation of the SourceFlag feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceFlag API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SourceFlagClear ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_SourceEnable ( INT_MODULE_ID index, INT_SOURCE source )

  Summary:
    Enables the interrupt source.

  Description:
    This function enables the interrupt source. The interrupt flag is set when
    the interrupt request is sampled. The pending interrupt request will not
    cause further processing if the interrupt is not enabled using this function
    or if interrupts are not enabled (on processors that support the
    PLIB_INT_Enable feature).


  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 

	source - One of the possible values from INT_SOURCE.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_TIMER_1);
    </code>

  Remarks:
    This function implements an operation of the SourceControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceControl API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SourceEnable ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_SourceDisable ( INT_MODULE_ID index, INT_SOURCE source )

  Summary:
    Disables the interrupt source

  Description:
    This function disables the given interrupt source.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only interrupt module ). 
			
    source - One of the possible values from INT_SOURCE.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_SourceDisable(INT_ID_0,INT_SOURCE_TIMER_1);
    </code>

  Remarks:
    This function implements an operation of the SourceControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceControl API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_SourceDisable ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    bool PLIB_INT_SourceIsEnabled ( INT_MODULE_ID index, INT_SOURCE source )

  Summary:
    Gets the enable state of the interrupt source.

  Description:
    This function gets the enable state of the interrupt source.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	

    source - One of the possible values from INT_SOURCE.

  Returns:
    - true    - If the interrupt source is enabled
    - false   - If the interrupt source is disabled

  Example:
    <code>
    if(PLIB_INT_SourceIsEnabled(INT_ID_0,INT_SOURCE_TIMER_1) != true)
    {
        PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_TIMER_1);
    }
     </code>

  Remarks:
    This function implements an operation of the SourceControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsSourceControl API to write flexible code 
    to automatically determine if this feature is available.
*/

bool PLIB_INT_SourceIsEnabled ( INT_MODULE_ID index, INT_SOURCE source );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_VectorPrioritySet( 	INT_MODULE_ID index,
                                        INT_VECTOR vector, 
                                        INT_PRIORITY_LEVEL priority )

  Summary:
    Sets the priority of the interrupt vector.

  Description:
    Sets the priority of the interrupt vector. The priority is one of the
    possible values from INT_PRIORITY_LEVEL.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	
				
    vector      - One of the possible values from INT_VECTOR

    priority    - One of the possible values from INT_PRIORITY_LEVEL

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_PRIORITY_LEVEL_4);
    </code>

  Remarks:
    This function implements an operation of the VectorPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorPriority API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_VectorPrioritySet( 	INT_MODULE_ID index, 
                                    INT_VECTOR vector, 
                                    INT_PRIORITY_LEVEL priority );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_VectorSubPrioritySet ( 	INT_MODULE_ID index,
                                            INT_VECTOR vector, 
                                            INT_SUBPRIORITY_LEVEL subPriority )

  Summary:
    Sets the sub-priority of the interrupt vector.

  Description:
    This function sets the sub priority of the interrupt vector.  The sub-priority
    is one of the possible values from INT_SUBPRIORITY_LEVEL.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	
    vector      - One of the possible values from INT_VECTOR
    subPriority - One of the possible values from INT_SUBPRIORITY_LEVEL

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_SUBPRIORITY_LEVEL_1);
    </code>

  Remarks:
    This function implements an operation of the VectorPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorPriority API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_VectorSubPrioritySet ( 	INT_MODULE_ID index, 
                                        INT_VECTOR vector, 
                                        INT_SUBPRIORITY_LEVEL subPriority );


//*******************************************************************************
/*
  Function:
    PLIB_INT_PRIORITY_LEVEL INT_VectorPriorityGet ( INT_MODULE_ID index, INT_VECTOR vector )

  Summary:
    Gets the priority of the interrupt vector.

  Description:
    Gets the priority of the interrupt vector. The priority is one of the
    possible values from INT_PRIORITY_LEVEL

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	  
					
    vector      - One of the possible values from INT_VECTOR

  Returns:
    priority    - One of the possible values from INT_PRIORITY_LEVEL

  Example:
    <code>
    INT_PRIORITY_LEVEL level;
    level = PLIB_INT_VectorPriorityGet(INT_ID_0, INT_VECTOR_T1);
    </code>

  Remarks:
    This function implements an operation of the VectorPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorPriority API to write flexible code 
    to automatically determine if this feature is available.
*/

INT_PRIORITY_LEVEL PLIB_INT_VectorPriorityGet ( INT_MODULE_ID index, INT_VECTOR vector );


//*******************************************************************************
/*
  Function:
    INT_SUBPRIORITY_LEVEL PLIB_INT_VectorSubPriorityGet (INT_MODULE_ID index, INT_VECTOR vector )

  Summary:
    Gets the sub-priority of the interrupt vector.

  Description:
    This function gets the sub-priority of the interrupt vector.  The priority is
    one of the possible values from INT_SUBPRIORITY_LEVEL.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	  
    vector      - One of the possible values from INT_VECTOR

  Returns:
    priority    - One of the possible values from INT_SUBPRIORITY_LEVEL

  Example:
    <code>
    INT_SUBPRIORITY_LEVEL level;
    level = PLIB_INT_VectorSubPriorityGet(INT_ID_0, INT_VECTOR_T1);
    </code>

  Remarks:
    This function implements an operation of the VectorPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsVectorPriority API to write flexible code 
    to automatically determine if this feature is available.
*/

INT_SUBPRIORITY_LEVEL PLIB_INT_VectorSubPriorityGet ( INT_MODULE_ID index, INT_VECTOR vector );


//*******************************************************************************
/*
  Function:
    INT_PRIORITY_LEVEL PLIB_INT_CPUCurrentPriorityLevelGet ( INT_MODULE_ID index )

  Summary:
    Gets the interrupt priority level at which the CPU is currently operating.

  Description:
    This function gets the interrupt priority level at which the CPU is
    currently operating.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	

  Returns:
    priority    - The current interrupt priority of the CPU. Range (0 - 15)

  Example:
    <code>
    INT_PRIORITY_LEVEL currentCPUPriority;
    currentCPUPriority = PLIB_INT_CPUCurrentPriorityLevelGet( INT_ID_0 );
    </code>

  Remarks:
    User interrupts are disabled when the CPU priority is more than 7.

    This function implements an operation of the CPUCurrentPriorityLevel feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsCPUCurrentPriorityLevel API to write flexible code 
    to automatically determine if this feature is available.
*/

INT_PRIORITY_LEVEL PLIB_INT_CPUCurrentPriorityLevelGet ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_NestingEnable ( INT_MODULE_ID index )

  Summary:
    Enables interrupt nesting.

  Description:
    This function enables interrupt nesting on processors that support it.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_NestingEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the INTNesting feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsINTNesting API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_NestingEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_NestingDisable ( INT_MODULE_ID index )

  Summary:
    Disables interrupt nesting.

  Description:
    This function disables interrupt nesting on processors that support it.

  Precondition:
    None.

  Parameters:
	index   - Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_NestingDisable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the INTNesting feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsINTNesting API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_NestingDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    bool PLIB_INT_TrapSourceFlagGet ( INT_MODULE_ID index, INT_TRAP_SOURCE trapSource )

  Summary:
    Returns the status of the flag for the selected trap.

  Description:
    This function returns the status of the flag for the selected trap. The flag
    is set when the trap request is recognized.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	
				
    trapSource 	- One of the possible values from INT_TRAP_SOURCE

  Returns:
    - true    - If the request has been recognized for the trap
    - false   - If the request is not recognized for the trap

  Example:
    <code>
    if(PLIB_INT_TrapSourceFlagGet(INT_ID_0,INT_ADDRESS_OVERFLOW_TRAP))
    {
        PLIB_INT_TrapSourceFlagClear(INT_ID_0,INT_ADDRESS_OVERFLOW_TRAP);
    }
    </code>

  Remarks:
    Some processor documentation uses the term "Exception" instead of the term
    "Trap".  For purposes of the Interrupt Peripheral Library, these two terms
    are synonyms.  The difference between a trap (or exception) and an
    interrupt is that a trap cannot be enabled or disabled, whereas an
    interrupt can be.

    This function implements an operation of the TrapSource feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsTrapSource API to write flexible code 
    to automatically determine if this feature is available.
*/

bool PLIB_INT_TrapSourceFlagGet ( INT_MODULE_ID index, INT_TRAP_SOURCE trapSource );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_TrapSourceFlagClear ( INT_MODULE_ID index, INT_TRAP_SOURCE trapSource )

  Summary:
    Clears the flag for the selected trap.

  Description:
    This function clears the flag for the selected trap.  The flag is set when
    the request is recognized.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only interrupt module ). 	 
					
    trapSource 	- One of the possible values from INT_TRAP_SOURCE

  Returns:
    None.

  Example:
    <code>
    if(PLIB_INT_TrapSourceFlagGet(INT_ID_0,INT_ADDRESS_OVERFLOW_TRAP))
    {
        PLIB_INT_TrapSourceFlagClear(INT_ID_0,INT_ADDRESS_OVERFLOW_TRAP);
    }
    </code>

  Remarks:
    Some processor documentation uses the term "Exception" instead of the term
    "Trap".  For purposes of the Interrupt Peripheral Library, these two terms
    are synonyms.  The difference between a trap (or exception) and an
    interrupt is that a trap cannot be enabled or disabled, whereas an
    interrupt can be.

    This function implements an operation of the TrapSource feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsTrapSource API to write flexible code 
    to automatically determine if this feature is available.
*/

void PLIB_INT_TrapSourceFlagClear ( INT_MODULE_ID index, INT_TRAP_SOURCE trapsource );


/*************************************************************************
  Function:
      void PLIB_INT_AlternateVectorTableSelect ( INT_MODULE_ID index )
    
  Summary:
    Enables the use of the alternate vector table.

  Description:
    This function enables the processor to use the alternate vector table
    instead of the default vector table. If the alternate vector table is
    enabled using this function, all interrupt and exception processing
    uses the alternate vectors instead of the default vectors. The
    alternate vectors are organized in the same manner as the default
    vectors.
    
    Alternate vectors support emulation and debugging by providing a means
    to switch between an application and support environment, without
    requiring the interrupt vectors to be reprogrammed. This feature can
    also be used to enable switching between different software algorithms
    during run time for evaluation.
  
  PreCondition:
    None.
  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	 
				
  Return:
    None.
  
  Example:
    <code>
    PLIB_INT_AlternateVectorTableSelect( INT_ID_0 );
    </code>
  Remarks:
    This function implements an operation of the AlternateVectorTable feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsAlternateVectorTable API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_AlternateVectorTableSelect ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_StandardVectorTableSelect ( INT_MODULE_ID index );

  Summary:
    Enables the use of the standard vector table.

  Description:
    This function enables use of the standard vector table. This is the default.
    It is only necessary to use this function if the alternate vector table was
    enabled using the PLIB_INT_AlternateVectorTableSelect function.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_StandardVectorTableSelect( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the AlternateVectorTable feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsAlternateVectorTable API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_StandardVectorTableSelect ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_Enable ( INT_MODULE_ID index )

  Summary:
    Enables the generation of interrupts to the CPU.

  Description:
    This function enables the generation of interrupts to the CPU.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
				INT_ID_0 for all the devices which has only interrupt module ). 	 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_Enable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the EnableControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsEnableControl API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_Enable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_Disable ( INT_MODULE_ID index )

  Summary:
    Disables the generation of interrupts to the CPU.

  Description:
    This function disables the generation of interrupts to the CPU.

  Precondition:
    None.

  Parameters:
	index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only one interrupt module ). 	 

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_Disable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the EnableControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsEnableControl API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_Disable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    bool PLIB_INT_IsEnabled ( INT_MODULE_ID index )

  Summary:
    Identifies if interrupts are currently enabled or disabled at the top level.

  Description:
    This function identifies if interrupts are enabled or disabled at the top 
    level.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    - true        - If the interrupts are currently enabled
    - false       - If the interrupts are currently disabled

  Example:
    <code>
    status = PLIB_INT_IsEnabled( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the EnableControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsEnableControl API to write flexible code 
    to automatically determine if this feature is available. 
*/

bool PLIB_INT_IsEnabled ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PeripheralsEnable ( INT_MODULE_ID index )

  Summary:
    Enables the generation of interrupts to the CPU by the peripherals.

  Description:
    This function enables the generation of interrupts to the CPU by the
    peripherals on devices with the ability to disable them.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PeripheralsEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the PeripheralControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsPeripheralControl API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PeripheralsEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PeripheralsDisable ( INT_MODULE_ID index )

  Summary:
    Disables the generation of interrupts to the CPU by the peripherals.

  Description:
    This function disables the generation of interrupts to the CPU by the
    peripherals on devices that support this feature.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PeripheralsDisable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the PeripheralControl feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsPeripheralControl API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PeripheralsDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityHighEnable ( INT_MODULE_ID index )

  Summary:
    Enables the generation of high-priority interrupts to the CPU.

  Description:
    This function enables the generation of high-priority interrupts to the CPU
    on devices that support this feature.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityHighEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the HighPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsHighPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityHighEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityHighDisable ( INT_MODULE_ID index )

  Summary:
    Disables the generation of high-priority interrupts to the CPU.

  Description:
    This function disables the generation of high-priority interrupts to the
    CPU on devices that support high-priority interrupts.

  Precondition:
    None.

  Parameters:
    index   	- Identifier for the module instance to be configured (it should be 
					INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityHighDisable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the HighPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsHighPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityHighDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityLowEnable ( INT_MODULE_ID index )

  Summary:
    Enables generation of low-priority interrupts to the CPU.

  Description:
    This function enables generation of low-priority interrupts to the CPU on
    devices that support this feature.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityLowEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the LowPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsLowPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityLowEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityLowDisable ( INT_MODULE_ID index )

  Summary:
    Disables the generation of low-priority interrupts to the CPU.

  Description:
    This function disables the generation of low-priority interrupts to the CPU
    on devices that support this feature.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityLowDisable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the LowPriority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsLowPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityLowDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityEnable ( INT_MODULE_ID index )

  Summary:
    Enables interrupt priority levels.

  Description:
    This function enables interrupt priority levels on devices that support
    programmable interrupt priorities.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityEnable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the Priority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityEnable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    void PLIB_INT_PriorityDisable ( INT_MODULE_ID index )

  Summary:
    Disables interrupt priority levels.

  Description:
    This function disables interrupt priority levels on devices that support
    programmable interrupt priorities.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    None.

  Example:
    <code>
    PLIB_INT_PriorityDisable( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the Priority feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsPriority API to write flexible code 
    to automatically determine if this feature is available. 
*/

void PLIB_INT_PriorityDisable ( INT_MODULE_ID index );


//*******************************************************************************
/*
  Function:
    bool PLIB_INT_DISIStatusGet ( INT_MODULE_ID index )

  Summary:
    Returns the status of the DISI instruction status.

  Description:
    This function returns the status of the DISI instruction status.

  Precondition:
    None.

  Parameters:
    index   - Identifier for the module instance to be configured (it should be 
			INT_ID_0 for all the devices which has only one interrupt module ).

  Returns:
    - true        - If DISI is active
    - false       - If DISI is not active

  Example:
    <code>
    PLIB_INT_DISIStatusGet( INT_ID_0 );
    </code>

  Remarks:
    This function implements an operation of the DISI feature.  
    This feature may not be available on all parts.  
    Please refer to the data sheet to determine if this feature is available 
    or call the PLIB_INT_ExistsDISI API to write flexible code 
    to automatically determine if this feature is available. 
*/

bool PLIB_INT_DISIStatusGet ( INT_MODULE_ID index );


// *****************************************************************************
// *****************************************************************************
// Section: INT Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_INT_ExistsSingleVectorShadowSet( INT_MODULE_ID index )

  Summary:
    Identifies whether the SingleVectorShadowSet feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the SingleVectorShadowSet feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_SingleVectorShadowSetDisable
    - PLIB_INT_SingleVectorShadowSetEnable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SingleVectorShadowSet feature is supported on the device
    - false  - The SingleVectorShadowSet feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsSingleVectorShadowSet( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsVectorSelect( INT_MODULE_ID index )

  Summary:
    Identifies whether the VectorSelect feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the VectorSelect feature is available on 
    the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_MultiVectorSelect
    - PLIB_INT_SingleVectorSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The VectorSelect feature is supported on the device
    - false  - The VectorSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsVectorSelect( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsProximityTimerEnable( INT_MODULE_ID index )

  Summary:
    Identifies whether the ProximityTimerEnable feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the ProximityTimerEnable feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_ProximityTimerEnable
    - PLIB_INT_ProximityTimerDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ProximityTimerEnable feature is supported on the device
    - false  - The ProximityTimerEnable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsProximityTimerEnable( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsProximityTimerControl( INT_MODULE_ID index )

  Summary:
    Identifies whether the ProximityTimerControl feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the ProximityTimerControl feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_ProximityTimerSet
    - PLIB_INT_ProximityTimerGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ProximityTimerControl feature is supported on the device
    - false  - The ProximityTimerControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsProximityTimerControl( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsExternalINTEdgeSelect( INT_MODULE_ID index )

  Summary:
    Identifies whether the ExternalINTEdgeSelect feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the ExternalINTEdgeSelect feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_ExternalRisingEdgeSelect
    - PLIB_INT_ExternalFallingEdgeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    Existence of the ExternalINTEdgeSelect feature: 
    - true   - The ExternalINTEdgeSelect feature is supported on the device
    - false  - The ExternalINTEdgeSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsExternalINTEdgeSelect( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsINTCPUPriority( INT_MODULE_ID index )

  Summary:
    Identifies whether the INTCPUPriority feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the INTCPUPriority feature is available on 
    the Interrupt Controller module. When this function returns true, this 
    function is supported on the device:
    - PLIB_INT_PriorityGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The INTCPUPriority feature is supported on the device
    - false  - The INTCPUPriority feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsINTCPUPriority( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsINTCPUVector( INT_MODULE_ID index )

  Summary:
    Identifies whether the INTCPUVector feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the INTCPUVector feature is available on the 
    Interrupt Controller module. When this function returns true, this function 
    is supported on the device:
    - PLIB_INT_VectorGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The INTCPUVector feature is supported on the device
    - false  - The INTCPUVector feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsINTCPUVector( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsSourceFlag( INT_MODULE_ID index )

  Summary:
    Identifies whether the SourceFlag feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the SourceFlag feature is available on the 
    Interrupt Controller module. When this function returns true, these functions 
    are supported on the device:
    - PLIB_INT_SourceFlagGet
    - PLIB_INT_SourceFlagSet
    - PLIB_INT_SourceFlagClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SourceFlag feature is supported on the device
    - false  - The SourceFlag feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsSourceFlag( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsSourceControl( INT_MODULE_ID index )

  Summary:
    Identifies whether the SourceControl feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the SourceControl feature is available on 
    the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_SourceEnable
    - PLIB_INT_SourceDisable
    - PLIB_INT_SourceIsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SourceControl feature is supported on the device
    - false  - The SourceControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsSourceControl( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsVectorPriority( INT_MODULE_ID index )

  Summary:
    Identifies whether the VectorPriority feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the VectorPriority feature is available on 
    the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_VectorPrioritySet
    - PLIB_INT_VectorPriorityGet
    - PLIB_INT_VectorSubPrioritySet
    - PLIB_INT_VectorSubPriorityGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The VectorPriority feature is supported on the device
    - false  - The VectorPriority feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsVectorPriority( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsCPUCurrentPriorityLevel( INT_MODULE_ID index )

  Summary:
    Identifies whether the CPUCurrentPriorityLevel feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the CPUCurrentPriorityLevel feature is 
    available on the Interrupt Controller module. When this function returns true, 
    this function is supported on the device:
    - PLIB_INT_CPUCurrentPriorityLevelGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The CPUCurrentPriorityLevel feature is supported on the device
    - false  - The CPUCurrentPriorityLevel feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsCPUCurrentPriorityLevel( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsINTNesting( INT_MODULE_ID index )

  Summary:
    Identifies whether the INTNesting feature exists on the Interrupt Controller 
    module.

  Description:
    This function identifies whether the INTNesting feature is available on the 
    Interrupt Controller module. When this function returns true, these functions 
    are supported on the device:
    - PLIB_INT_NestingEnable
    - PLIB_INT_NestingDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The INTNesting feature is supported on the device
    - false  - The INTNesting feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsINTNesting( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsTrapSource( INT_MODULE_ID index )

  Summary:
    Identifies whether the TrapSource feature exists on the Interrupt Controller 
    module.

  Description:
    This function identifies whether the TrapSource feature is available on the 
    Interrupt Controller module. When this function returns true, these functions 
    are supported on the device:
    - PLIB_INT_TrapSourceFlagGet
    - PLIB_INT_TrapSourceFlagClear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The TrapSource feature is supported on the device
    - false  - The TrapSource feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsTrapSource( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsAlternateVectorTable( INT_MODULE_ID index )

  Summary:
    Identifies whether the AlternateVectorTable feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the AlternateVectorTable feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_AlternateVectorTableSelect
    - PLIB_INT_StandardVectorTableSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AlternateVectorTable feature is supported on the device
    - false  - The AlternateVectorTable feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsAlternateVectorTable( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsEnableControl( INT_MODULE_ID index )

  Summary:
    Identifies whether the EnableControl feature exists on the Interrupt Controller 
    module.

  Description:
    This function identifies whether the EnableControl feature is available on 
    the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_Enable
    - PLIB_INT_Disable
    - PLIB_INT_IsEnabled

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The EnableControl feature is supported on the device
    - false  - The EnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsEnableControl( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsPeripheralControl( INT_MODULE_ID index )

  Summary:
    Identifies whether the PeripheralControl feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the PeripheralControl feature is available 
    on the Interrupt Controller module. When this function returns true, these 
    functions are supported on the device:
    - PLIB_INT_PeripheralsEnable
    - PLIB_INT_PeripheralsDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    Existence of the PeripheralControl feature: 
    - true   - The PeripheralControl feature is supported on the device
    - false  - The PeripheralControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsPeripheralControl( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsHighPriority( INT_MODULE_ID index )

  Summary:
    Identifies whether the HighPriority feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the HighPriority feature is available on the 
    Interrupt Controller module. When this function returns true, these functions 
    are supported on the device:
    - PLIB_INT_PriorityHighEnable
    - PLIB_INT_PriorityHighDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The HighPriority feature is supported on the device
    - false  - The HighPriority feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsHighPriority( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsLowPriority( INT_MODULE_ID index )

  Summary:
    Identifies whether the LowPriority feature exists on the Interrupt 
    Controller module.

  Description:
    This function identifies whether the LowPriority feature is available on the 
    Interrupt Controller module. When this function returns true, these functions
    are supported on the device:
    - PLIB_INT_PriorityLowEnable
    - PLIB_INT_PriorityLowDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LowPriority feature is supported on the device
    - false  - The LowPriority feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsLowPriority( INT_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_INT_ExistsPriority( INT_MODULE_ID index )

  Summary:
    Identifies whether the Priority feature exists on the Interrupt Controller 
    module.

  Description:
    This function identifies whether the Priority feature is available on the Interrupt 
    Controller module. When this function returns true, these functions are supported 
    on the device:
    - PLIB_INT_PriorityEnable
    - PLIB_INT_PriorityDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The Priority feature is supported on the device
    - false  - The Priority feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_INT_ExistsPriority( INT_MODULE_ID index );

 
#endif //#ifndef _PLIB_INT_H
/*******************************************************************************
 End of File
*/

