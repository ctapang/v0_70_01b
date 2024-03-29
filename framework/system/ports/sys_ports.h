/*******************************************************************************
  Ports System Service Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    sys_ports.h

  Summary:
    Ports System Service interface definitions

  Description:
    This file contains the interface definition for the Ports system
    service.  It provides a way to interact with the Ports subsystem to
    manage the timing requests supported by the system
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

#ifndef _SYS_PORTS_H
#define _SYS_PORTS_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "peripheral/ports/plib_ports.h"

// *****************************************************************************
// *****************************************************************************
// Section: SYS PORTS Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* SYS PORTS PULLUP status

  Summary:
    Provides the pull-up and pull-down status.

  Description:
    These constants provide the pull-up or pull-down status definitions.

  Remarks:
    None.

*/

typedef enum
{
    /* PULLUP Disable */
    SYS_PORTS_PULLUP_DISABLE
        /*DOM-IGNORE-BEGIN*/  = 0 /*DOM-IGNORE-END*/,
    /* PULLUP Enable */
    SYS_PORTS_PULLUP_ENABLE
        /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/,

} SYS_PORTS_PULLUP_PULLDOWN_STATUS;

// *****************************************************************************
/* SYS PORTS PIN DIRECTION

  Summary:
    Defines the direction of the port pins.

  Description:
    These constants provide the port pin direction definitions.

  Remarks:
    None.

*/

typedef enum
{
    /* Direction as output */
    SYS_PORTS_DIRECTION_OUTPUT
        /*DOM-IGNORE-BEGIN*/  = 0 /*DOM-IGNORE-END*/,
    /* Direction as input */
    SYS_PORTS_DIRECTION_INPUT
        /*DOM-IGNORE-BEGIN*/  = 1 /*DOM-IGNORE-END*/,

} SYS_PORTS_PIN_DIRECTION;

// *****************************************************************************
// *****************************************************************************
// Section: SYS PORTS CONTROL Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    PORTS_DATA_TYPE SYS_PORTS_Read( PORTS_MODULE_ID index, PORTS_CHANNEL channel )

  Summary:
    Reads the data from the I/O port.

  Description:
    This function reads the data from the I/O port.

  Preconditions:
    The direction of the port to be set as input.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.

  Returns:
    Return the data read from the port.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_TYPE readData;
    readData = SYS_PORTS_Read( MY_PORTS_INSTANCE, MY_CHANNEL );

  Remarks:
    None.
*/

PORTS_DATA_TYPE SYS_PORTS_Read( PORTS_MODULE_ID index, PORTS_CHANNEL channel );

// *****************************************************************************
/* Function:
    void SYS_PORTS_Write( PORTS_MODULE_ID index, 
                          PORTS_CHANNEL channel,
                          PORTS_DATA_TYPE value )

  Summary:
    Writes the data to the I/O port.

  Description:
    This function writes the data to the I/O port.

  Preconditions:
    The direction of the port to be set as output.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    value           - Value to be written into a port of width PORTS_DATA_TYPE

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
	PORTS_DATA_TYPE writeData;
	SYS_PORTS_Write( MY_PORTS_INSTANCE, MY_CHANNEL, MY_VALUE );

  Remarks:
    None.
*/

void SYS_PORTS_Write( PORTS_MODULE_ID index,
                      PORTS_CHANNEL channel,
                      PORTS_DATA_TYPE value );
                      
// *****************************************************************************
/* Function:
    void SYS_PORTS_Set( PORTS_MODULE_ID index, PORTS_CHANNEL channel, 
                         PORTS_DATA_TYPE value,
                         PORTS_DATA_MASK mask )

  Summary:
    Writes the selected digital port/latch based on the mask.

  Description:
    This function writes to the selected digital port/latch relative to the mask.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    value           - Value to be written into a port of width PORTS_DATA_TYPE
    mask            - Identifies the bits to be written

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_VALUE - 0x1234
    PORTS_DATA_MASK myMask = (PORTS_DATA_MASK)0x00FF;
    SYS_PORTS_Set(MY_PORTS_INSTANCE, MY_CHANNEL, MY_VALUE, myMask);
    </code>

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_Set( PORTS_MODULE_ID index, PORTS_CHANNEL channel, 
                    PORTS_DATA_TYPE value,
                    PORTS_DATA_MASK mask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_Clear ( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_DATA_MASK clearMask )

  Summary:
    Clears the selected digital port.

  Description:
    This function clears the selected digital port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    clearMask       - Identifies the bits to be cleared

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK clearMask = (PORTS_DATA_MASK)0x00FF;
    SYS_PORTS_Clear( MY_PORTS_INSTANCE, MY_CHANNEL, clearMask );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_Clear ( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_DATA_MASK clearMask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_DirectionSelect( PORTS_MODULE_ID index, 
                                 SYS_PORTS_PIN_DIRECTION pinDir,
                                 PORTS_CHANNEL channel, 
                                 PORTS_DATA_MASK mask )

  Summary:
    Enables the direction for the selected port.

  Description:
    This function enables the direction for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinDir          - Pin direction
    channel         - Identifier for the PORT channel: A, B, C, etc.
    mask            - Mask for the direction of width PORTS_DATA_MASK

  Returns:
    None

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_PIN_DIRECTION pinDir;
    pinDir = SYS_PORTS_DIRECTION_INPUT;
    PORTS_DATA_MASK myMask = (PORTS_DATA_MASK)0x00FF;
    SYS_PORTS_DirectionSelect(MY_PORTS_INSTANCE, pinDir, MY_CHANNEL, myMask );

  Remarks:
    None.
*/

void SYS_PORTS_DirectionSelect( PORTS_MODULE_ID index, 
                             SYS_PORTS_PIN_DIRECTION pinDir, 
                             PORTS_CHANNEL channel, 
                             PORTS_DATA_MASK mask );

// *****************************************************************************
/* Function:
    PORTS_DATA_MASK SYS_PORTS_DirectionGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel ) 

  Summary:
    Reads the direction for the selected port.

  Description:
    This function reads the direction for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.

  Returns:
    Direction of the port.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK value;
    value = SYS_PORTS_DirectionGet( MY_PORTS_INSTANCE, MY_CHANNEL );

  Remarks:
    None.
*/

PORTS_DATA_MASK SYS_PORTS_DirectionGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel );

// *****************************************************************************
/* Function:
    void SYS_PORTS_Toggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_DATA_MASK toggleMask )

  Summary:
    Toggles the selected digital port pins.

  Description:
    This function toggles the selected digital port pins.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    toggleMask      - Identifies the bits to be toggled

  Returns:
    None

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK toggleMask = (PORTS_DATA_MASK)0x00FF;	
    SYS_PORTS_Toggle( MY_PORTS_INSTANCE, MY_CHANNEL, toggleMask );

  Remarks:
    None.
*/

void SYS_PORTS_Toggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                       PORTS_DATA_MASK toggleMask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PullUpEnable( PORTS_MODULE_ID index, 
                                 PORTS_CHANNEL channel,
                                 PORTS_DATA_MASK mask )

  Summary:
    Enables the pull-up for the selected port.

  Description:
    This function enables the pull-up for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    mask            - Mask of type PORTS_DATA_MASK

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_PullUpEnable( MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PullUpEnable( PORTS_MODULE_ID index, 
                             PORTS_CHANNEL channel,
                             PORTS_DATA_MASK mask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PullUpDisable( PORTS_MODULE_ID index, 
                                 PORTS_CHANNEL channel,
                                 PORTS_DATA_MASK mask )

  Summary:
    Disables the pull-up for the selected port.

  Description:
    This function disables the pull-up for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    mask            - Mask of type PORTS_DATA_MASK

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_PullUpDisable( MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
    On some devices, pull-up disable leads to pull-down enable.
*/

void SYS_PORTS_PullUpDisable( PORTS_MODULE_ID index, 
                             PORTS_CHANNEL channel,
                             PORTS_DATA_MASK mask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_OpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                     PORTS_DATA_MASK mask )

  Summary:
    Enables the open-drain functionality for the selected port.

  Description:
    This function enables the open-drain functionality for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    mask            - Mask of type PORTS_DATA_MASK

  Returns:
    None

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_OpenDrainEnable( MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_OpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                PORTS_DATA_MASK mask );

// *****************************************************************************
/* Function:
    void SYS_PORTS_OpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                     PORTS_DATA_MASK mask )

  Summary:
    Disables the open-drain functionality for the selected port.

  Description:
    This function disables the open-drain functionality for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    mask            - Mask of type PORTS_DATA_MASK

  Returns:
    None

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_PeripheralOpenDrainDisable( MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_OpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                 PORTS_DATA_MASK mask );

// *****************************************************************************
// *****************************************************************************
// Section: SYS PORT PINS REMAPING Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SYS_PORTS_RemapInput( PORTS_MODULE_ID      index,
							  PORTS_REMAP_INPUT_FUNCTION function,
							  PORTS_REMAP_INPUT_PIN      remapPin )

  Summary:
    Input/Output (I/O) function remapping.

  Description:
    This function controls the I/O function remapping.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    function        - One of the possible values of PORTS_REMAP_INPUT_FUNCTION
    remapPin        - One of the possible values of PORTS_REMAP_INPUT_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // Remapping input function 'Input Capture 1' to the Remappable pin 'RPD2'
    SYS_PORTS_RemapInput(MY_PORTS_INSTANCE, INPUT_FUNC_IC1, INPUT_PIN_RPD2 );

    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	SYS_PORTS_ExistsRemapInputOutput in your application to determine whether
	this feature is available.
*/

void SYS_PORTS_RemapInput( PORTS_MODULE_ID      index,
							  PORTS_REMAP_INPUT_FUNCTION function,
							  PORTS_REMAP_INPUT_PIN      remapPin );


// *****************************************************************************
/* Function:
    void SYS_PORTS_RemapOutput( PORTS_MODULE_ID      index,
                                      PORTS_REMAP_OUTPUT_FUNCTION function,
                                      PORTS_REMAP_OUTPUT_PIN      remapPin )

  Summary:
    Input/Output (I/O) function remapping.

  Description:
    This function controls the I/O function remapping.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    function        - One of the possible values of PORTS_REMAP_OUTPUT_FUNCTION
    remapPin        - One of the possible values of PORTS_REMAP_OUTPUT_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // Remapping output function 'UART3 Transmit' to the Remappable pin 'RPA14'
    SYS_PORTS_RemapInputOutput(MY_PORTS_INSTANCE, OTPUT_FUNC_U3TX, OUTPUT_PIN_RPA14);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	SYS_PORTS_ExistsRemapInputOutput in your application to determine whether
	this feature is available.
*/

void SYS_PORTS_RemapOutput( PORTS_MODULE_ID      index,
                                  PORTS_REMAP_OUTPUT_FUNCTION function,
                                  PORTS_REMAP_OUTPUT_PIN      remapPin );


// *****************************************************************************
// *****************************************************************************
// Section: SYS Change Notification Pins Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationGlobalEnable( PORTS_MODULE_ID index )

  Summary:
    Globally enables the change notification for the selected port.

  Description:
    This function globally enables the change notification for the selected port.

  Preconditions:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_ChangeNotificationGlobalEnable( MY_PORTS_INSTANCE );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationGlobalEnable( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationGlobalDisable( PORTS_MODULE_ID index );

  Summary:
    Globally disables the change notification for the selected port.

  Description:
    This function globally disables the change notification for the selected port.

  Preconditions:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_ChangeNotificationGlobalDisable( MY_PORTS_INSTANCE);

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationGlobalDisable( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationEnable( PORTS_MODULE_ID index, 
                                             PORTS_CHANGE_NOTICE_PIN pinNum, 
                                             SYS_PORTS_PULLUP_PULLDOWN_STATUS value )

  Summary:
    Enables the change notification for the selected port.

  Description:
    This function enables the change notification for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured  
    value           - Pull-up enable or disable value
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_PULLUP_PULLDOWN_STATUS value;
    PORTS_CHANGE_NOTICE_PIN pinNum;
    SYS_PORTS_ChangeNotificationEnable( index, pinNum, value );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationEnable( PORTS_MODULE_ID index, 
                                         PORTS_CHANGE_NOTICE_PIN pinNum, 
                                         SYS_PORTS_PULLUP_PULLDOWN_STATUS value );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationDisable( PORTS_MODULE_ID index, 
                                              PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Disables the change notification for the selected port.

  Description:
    This function disables the change notification for the selected port.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured  
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_CHANGE_NOTICE_PIN pinNum;
    SYS_PORTS_ChangeNotificationDisable( index, pinNum );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationDisable( PORTS_MODULE_ID index, 
                                          PORTS_CHANGE_NOTICE_PIN pinNum );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationInIdleModeEnable( PORTS_MODULE_ID index );

  Summary:
    Enables the change notification for the selected port in Sleep or Idle mode.

  Description:
    This function enables the change notification for the selected port in Sleep
    or Idle mode.

  Preconditions:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_ChangeNotificationInIdleModeEnable( MY_PORTS_INSTANCE );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationInIdleModeEnable( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationInIdleModeDisable( PORTS_MODULE_ID index);

  Summary:
    Disables the change notification for the selected port in Sleep or Idle mode.

  Description:
    This function disables the change notification for the selected port in Sleep
    or Idle mode.

  Preconditions:
    None.

  Parameters:
    None.

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_ChangeNotificationInIdleModeDisable( MY_PORTS_INSTANCE );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationInIdleModeDisable( PORTS_MODULE_ID index );
                                        
// *****************************************************************************
/* Function:
    bool SYS_PORTS_ChangeNotificationStatus( PORTS_MODULE_ID         index,
                                             PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Gets the status of the corresponding notification pin.

  Description:
    This function gets the status of the corresponding notification pin..

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    - true  - Change notice has occurred
    - false - Change notice has not occurred

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    //pinNUM is the change notification pin
    bool status;
    status = SYS_PORTS_ChangeNotificationStatus( MY_PORTS_INSTANCE, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

bool SYS_PORTS_ChangeNotificationStatus( PORTS_MODULE_ID         index,
                                         PORTS_CHANGE_NOTICE_PIN pinNum ); 

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationPullUpEnable ( PORTS_MODULE_ID         index,
                                                    PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Enables a weak pull-up on the change notification pin.

  Description:
    This function enables a weak pull-up on the change notification pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    SYS_PORTS_ChangeNotificationPullUpEnable( MY_PORTS_INSTANCE, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationPullUpEnable ( PORTS_MODULE_ID         index,
                                                PORTS_CHANGE_NOTICE_PIN pinNum );


// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationPullUpDisable ( PORTS_MODULE_ID         index,
                                                    PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Disables pull-up on input change.

  Description:
    This function disables pull-up on input change.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    SYS_PORTS_ChangeNotificationPullUpDisable( MY_PORTS_INSTANCE, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationPullUpDisable ( PORTS_MODULE_ID         index,
                                                PORTS_CHANGE_NOTICE_PIN pinNum );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationPullDownEnable ( PORTS_MODULE_ID         index,
                                                      PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Enables pull-down on input change.

  Description:
    This function enables pull-down on input change.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    SYS_PORTS_ChangeNotificationPullDownEnable( MY_PORTS_INSTANCE, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationPullDownEnable ( PORTS_MODULE_ID         index,
                                                  PORTS_CHANGE_NOTICE_PIN pinNum );

// *****************************************************************************
/* Function:
    void SYS_PORTS_ChangeNotificationPullDownDisable ( PORTS_MODULE_ID         index,
                                                       PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Disables pull-down on input change.

  Description:
    This function disables pull-down on input change.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    SYS_PORTS_ChangeNotificationPullDownDisable( MY_PORTS_INSTANCE, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_ChangeNotificationPullDownDisable ( PORTS_MODULE_ID         index,
                                                   PORTS_CHANGE_NOTICE_PIN pinNum );

// *****************************************************************************
// *****************************************************************************
// Section: SYS PORT PINS Control Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinModeSelect ( PORTS_MODULE_ID index, PORTS_ANALOG_PIN pin, PORTS_PIN_MODE mode)

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pin             - Possible values of PORTS_ANALOG_PIN
    mode            - Possible values of PORTS_PIN_MODE	

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_AN0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    SYS_PORTS_PinModSYS_PORTS_PinModeSelecteSelect( MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinModeSelect ( PORTS_MODULE_ID index, PORTS_ANALOG_PIN pin, PORTS_PIN_MODE mode);

// *****************************************************************************
/* Function:
    void SYS_PORTS_IOLockEnable( PORTS_MODULE_ID index )

  Summary:
    Enables the I/O lock.

  Description:
    This function enables the I/O lock.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_IOLockEnable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
    This feature is available for devices with Peripheral Pin Select (PPS) 
    functionality. If the associated Configuration bit is set, this function can 
    only be set once.

    This function is not available on all devices. Please refer to the specific
    device data sheet for availability.
*/

void SYS_PORTS_IOLockEnable( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    void SYS_PORTS_IOLockDisable( PORTS_MODULE_ID index )

  Summary:
    Disables the I/O lock.

  Description:
    This function disables the I/O lock.

  Preconditions:
    index           - Identifier for the device instance to be configured

  Parameters:
    The associated Configuration bit should be �0�.

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    SYS_PORTS_IOLockDisable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
    This feature is available for devices with PPS functionality. If the
    associated Configuration bit is set and if the I/O lock is enabled, this
    feature can never be used to disable the I/O lock. The only way to
    clear the bit and re-enable peripheral remapping is to perform a device
    Reset.

    This function is not available on all devices. Please refer to the specific
    device data sheet for availability.
*/

void SYS_PORTS_IOLockDisable( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    bool SYS_PORTS_IOLockIsActive( PORTS_MODULE_ID index )

  Summary:
    Returns the status of I/O lock.

  Description:
    This function returns the status of I/O lock.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    - true  - I/O lock is active
    - false - I/O lock is not active

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    bool lockStatus;
    lockStatus = SYS_PORTS_IOLockIsActive(MY_PORTS_INSTANCE);
    </code>

  Remarks:
    This feature is available for devices with PPS functionality.

    This function is not available on all devices. Please refer to the specific
    device data sheet for availability.
*/

bool SYS_PORTS_IOLockIsActive( PORTS_MODULE_ID index );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinWrite ( PORTS_MODULE_ID index, 
                              PORTS_CHANNEL channel,
                              PORTS_BIT_POS bitPos
                              bool value )

  Summary:
    Writes the selected digital pin.

  Description:
    This function writes the selected digital pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS
    value           - Value to be written to the specific pin/latch:
                      - true  - Sets the bit
                      - false - Clears the bit

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinWrite(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM, value);

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinWrite ( PORTS_MODULE_ID index, 
                          PORTS_CHANNEL channel,
                          PORTS_BIT_POS bitPos,
                          bool value );

// *****************************************************************************
/* Function:
    bool SYS_PORTS_PinRead ( PORTS_MODULE_ID index, 
                             PORTS_CHANNEL channel,
                             PORTS_BIT_POS bitPos )

  Summary:
    Reads the selected digital pin.

  Description:
    This function reads the selected digital pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    The status of the port pin.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    bool bitStatus = SYS_PORTS_PinRead(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

bool SYS_PORTS_PinRead ( PORTS_MODULE_ID index, 
                         PORTS_CHANNEL channel,
                         PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinToggle ( PORTS_MODULE_ID index, 
                               PORTS_CHANNEL channel,
                               PORTS_BIT_POS bitPos )

  Summary:
    Toggles the selected digital pin.

  Description:
    This function toggles the selected digital pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinToggle( MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinToggle ( PORTS_MODULE_ID index, 
                           PORTS_CHANNEL channel,
                           PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinSet( PORTS_MODULE_ID index, 
                           PORTS_CHANNEL channel, 
                           PORTS_BIT_POS bitPos )

  Summary:
    Sets the selected digital pin/latch.

  Description:
    This function sets the selected digital pin/latch.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinSet(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinSet( PORTS_MODULE_ID index, 
                       PORTS_CHANNEL channel, 
                       PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinClear ( PORTS_MODULE_ID index, 
                              PORTS_CHANNEL channel,
                              PORTS_BIT_POS bitPos )

  Summary:
    Clears the selected digital pin.

  Description:
    This function clears the selected digital pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_IO_PIN_10
    SYS_PORTS_PinClear( MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinClear ( PORTS_MODULE_ID index, 
                          PORTS_CHANNEL channel,
                          PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinDirectionSelect ( PORTS_MODULE_ID index,
                                     SYS_PORTS_PIN_DIRECTION pinDir,
                                     PORTS_CHANNEL channel,
                                     PORTS_BIT_POS bitPos )
  Summary:
    Enables the direction for the selected pin.

  Description:
    This functino enables the direction for the selected pin.

  Preconditions:
    None

  Parameters:
    index           - Identifier for the device instance to be configured
    pinDir          - Pin direction
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PIN_DIRECTION pinDir;
    pinDir = SYS_PORTS_DIRECTION_INPUT;
    SYS_PORTS_PinDirectionSelect(MY_PORTS_INSTANCE, pinDir, MY_CHANNEL, MY_PINNUM);

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinDirectionSelect ( PORTS_MODULE_ID index,
                                 SYS_PORTS_PIN_DIRECTION pinDir,
                                 PORTS_CHANNEL channel,
                                 PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinPullUpEnable ( PORTS_MODULE_ID index, 
                                     PORTS_CHANNEL channel,
                                     PORTS_BIT_POS bitPos );

  Summary:
    Enables the pull-up functionality for the selected pin.

  Description:
    This functin enables the pull-up functionality for the selected pin.

  Preconditions:
    None

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinPullUpEnable( MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinPullUpEnable ( PORTS_MODULE_ID index, 
                                 PORTS_CHANNEL channel,
                                 PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinPullUpDisable ( PORTS_MODULE_ID index, 
                                      PORTS_CHANNEL channel,
                                      PORTS_BIT_POS bitPos );

  Summary:
    Disables the pull-up functionality for the selected pin

  Description:
    This function disables the pull-up functionality for the selected pin.

  Preconditions:
    None

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinPullUpDisable( MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
    On some devices, pull-up disable leads to pull-down enable.
*/

void SYS_PORTS_PinPullUpDisable ( PORTS_MODULE_ID index, 
                                  PORTS_CHANNEL channel,
                                  PORTS_BIT_POS bitPos );

// *****************************************************************************
/* Function:
    void SYS_PORTS_PinOpenDrainEnable ( PORTS_MODULE_ID index, 
                                        PORTS_CHANNEL channel,
                                        PORTS_BIT_POS bitPos )

  Summary:
    Enables the open-drain functionality for the selected pin.

  Description:
    This function enables the open-drain functionality for the selected pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS


  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinOpenDrainEnable( MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM );

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinOpenDrainEnable ( PORTS_MODULE_ID index, 
                                    PORTS_CHANNEL channel,
                                    PORTS_BIT_POS bitPos );


// *****************************************************************************
/* Function:
    void SYS_PORTS_PinOpenDrainDisable ( PORTS_MODULE_ID index, 
                                         PORTS_CHANNEL channel,
                                         PORTS_BIT_POS bitPos )

  Summary:
    Disables the open-drain functionality for the selected pin.

  Description:
    This function disables the open-drain functionality for the selected pin.

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORT channel: A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS


  Returns:
    None.

  Example:
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    SYS_PORTS_PinOpenDrainDisable(MY_PORTS_INSTANCE, MY_PINNUM);

  Remarks:
    Not all features are available on all devices. Refer to the specific device
    data sheet for availability.
*/

void SYS_PORTS_PinOpenDrainDisable ( PORTS_MODULE_ID index, 
                                     PORTS_CHANNEL channel,
                                     PORTS_BIT_POS bitPos );
                                     

#endif //SYS_PORTS_H

/*******************************************************************************
 End of File
*/
