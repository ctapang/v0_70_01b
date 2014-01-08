/*******************************************************************************
  Ports Peripheral Library Interface Header

  Company:
    Microchip Technology Inc.

  File Name:
    plib_ports.h

  Summary:
    Ports Peripheral Library Interface header for Ports function definitions.

  Description:
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the Ports
    Peripheral Library for all families of Microchip microcontrollers. The
    definitions in this file are common to the Ports peripheral.
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

#ifndef _PLIB_PORTS_H
#define _PLIB_PORTS_H

#include <stdint.h>
#include <stddef.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/*  PORTS data mask definition

  Summary:
    Data type defining the PORTS data mask

  Description:
    This data type defines the PORTS data mask

  Remarks:
    This data type changes sizes, depending on if it is being used on an 8- 16-
    or 32-bit part.
*/

typedef uint16_t        PORTS_DATA_MASK;


// *****************************************************************************
/*  PORTS data type definition

  Summary:
    Data type defining the PORTS data type.

  Description:
    This data type defines the PORTS data type.

  Remarks:
    This data type changes sizes, depending on if it is being used on an 8-, 16-,
    or 32-bit device.
*/

typedef uint32_t        PORTS_DATA_TYPE;


// *****************************************************************************
// *****************************************************************************
// Section: Included Files (continued at end of file)
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.  However,
    please see the bottom of the file for additional implementation header files
    that are also included.
*/

#include "peripheral/ports/processor/ports_processor.h"


// *****************************************************************************
// *****************************************************************************
// Section: PORTS Peripheral Library Interface Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    void PLIB_PORTS_RemapInput( PORTS_MODULE_ID      index,
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
    PLIB_PORTS_RemapInput(MY_PORTS_INSTANCE, INPUT_FUNC_IC1, INPUT_PIN_RPD2 );

    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsRemapInputOutput in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_RemapInput( PORTS_MODULE_ID      index,
							  PORTS_REMAP_INPUT_FUNCTION function,
							  PORTS_REMAP_INPUT_PIN      remapPin );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_RemapOutput( PORTS_MODULE_ID      index,
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
    PLIB_PORTS_RemapInputOutput(MY_PORTS_INSTANCE, OTPUT_FUNC_U3TX, OUTPUT_PIN_RPA14);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsRemapInputOutput in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_RemapOutput( PORTS_MODULE_ID      index,
                                  PORTS_REMAP_OUTPUT_FUNCTION function,
                                  PORTS_REMAP_OUTPUT_PIN      remapPin );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinModeSelect( PORTS_MODULE_ID  index,
                                   PORTS_ANALOG_PIN pin,
                                   PORTS_PIN_MODE   mode )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pin             - Possible values of PORTS_ANALOG_PIN
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinModeSelect( PORTS_MODULE_ID  index,
                               PORTS_ANALOG_PIN pin,
                               PORTS_PIN_MODE   mode );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinModePerPortSelect( PORTS_MODULE_ID  index,
	                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos,
                               PORTS_PIN_MODE   mode );

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinModePerPortSelect( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos,
                               PORTS_PIN_MODE   mode );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullDownPerPortEnable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullDownPerPortEnable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullDownPerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullDownPerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullUpPerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullUpPerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullUpPerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinChangeNoticePerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinChangeNoticePerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
	void PLIB_PORTS_PinChangeNoticePerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinChangeNoticePerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePerPortTurnOn ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePerPortTurnOn ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel );


// *****************************************************************************
/* Function:
void PLIB_PORTS_ChangeNoticePerPortTurnOff( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePerPortTurnOff( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel );


// *****************************************************************************
/* Function:
	void PLIB_PORTS_ChangeNoticeInIdlePerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeInIdlePerPortEnable ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel );


// *****************************************************************************
/* Function:
    bool PLIB_PORTS_ChangeNoticePerPortHasOccured ( PORTS_MODULE_ID  index,
	                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos )

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeInIdlePerPortDisable( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel );

// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinModePerPortSelect( PORTS_MODULE_ID  index,
	                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos,
                               PORTS_PIN_MODE   mode );

  Summary:
    Enables the selected pin as analog or digital.

  Description:
    This function enables the selected pin as analog or digital.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Port pin channel
    bitPos          - Position in the PORT pins
    mode            - Possible values of PORTS_PIN_MODE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PIN       - PORTS_ANALOG_PIN_0
    // MY_PIN_MODE  - PORTS_PIN_MODE_ANALOG
    PLIB_PORTS_PinModeSelect(MY_PORTS_INSTANCE, MY_PIN, MY_PIN_MODE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinMode in your application to determine whether
	this feature is available.
*/

bool PLIB_PORTS_ChangeNoticePerPortHasOccured ( PORTS_MODULE_ID  index,
                               PORTS_CHANNEL channel, PORTS_BIT_POS  bitPos );



// *****************************************************************************
/* Function:
    bool PLIB_PORTS_PinGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                            PORTS_BIT_POS       bitPos )

  Summary:
    Reads/Gets data from the selected digital pin.

  Description:
    This function reads/gets data from the selected digital pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    Port pin read data.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    bool bitStatus = PLIB_PORTS_PinGet(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsRead in your application to determine whether
	this feature is available.
*/

bool PLIB_PORTS_PinGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                        PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinWrite( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                              PORTS_BIT_POS       bitPos,
                              bool            value )

  Summary:
    Writes the selected digital pin/latch.

  Description:
    This function writes to the selected digital pin/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS
    value           - Value to be written to the specific pin/latch
                      true - sets the bit, false - clears the bit

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinWrite(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinWrite( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                          PORTS_BIT_POS       bitPos,
                          bool            value );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                            PORTS_BIT_POS       bitPos )

  Summary:
    Sets the selected digital pin/latch.

  Description:
    This function sets the selected digital pin/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinSet(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                        PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinClear( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                              PORTS_BIT_POS       bitPos )

  Summary:
    Clears the selected digital pin/latch.

  Description:
    This function clears the selected digital pin/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinClear(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinClear( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                          PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinToggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                               PORTS_BIT_POS       bitPos )

  Summary:
    Toggles the selected digital pin/latch.

  Description:
    This function toggles the selected digital pin/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinToggle(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinToggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinDirectionInputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                          PORTS_BIT_POS       bitPos )

  Summary:
    Enables the read (input) direction for the selected pin.

  Description:
    This function enables the read (input) direction for the selected pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinDirectionInputSet(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsDirection in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinDirectionInputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                      PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinDirectionOutputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                           PORTS_BIT_POS       bitPos )

  Summary:
    Enables the write (output) direction for the selected pin.

  Description:
    This function enables the write (output) direction for the selected pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinDirectionOutputSet(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsDirection in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinDirectionOutputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                       PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinOpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                        PORTS_BIT_POS       bitPos )

  Summary:
    Enables the open drain functionality for the selected pin.

  Description:
    This function enables the open drain functionality for the selected pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinOpenDrainEnable(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsOpenDrain in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinOpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                    PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinOpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                         PORTS_BIT_POS       bitPos )

  Summary:
    Disables the open drain functionality for the selected pin.

  Description:
    This function disables the open drain functionality for the selected pin.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    bitPos          - Possible values of PORTS_BIT_POS

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_PIN_10
    PLIB_PORTS_PinOpenDrainDisable(MY_PORTS_INSTANCE, MY_CHANNEL, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsOpenDrain in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinOpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                     PORTS_BIT_POS       bitPos );


// *****************************************************************************
/* Function:
    PORTS_DATA_TYPE PLIB_PORTS_Read( PORTS_MODULE_ID index, PORTS_CHANNEL channel )

  Summary:
    Reads the selected digital port.

  Description:
    This function reads from the selected digital port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.

  Returns:
    data on a port with width PORTS_DATA_TYPE

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_TYPE readData = PLIB_PORTS_Read(MY_PORTS_INSTANCE, MY_CHANNEL);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsRead in your application to determine whether
	this feature is available.
*/

PORTS_DATA_TYPE PLIB_PORTS_Read( PORTS_MODULE_ID index, PORTS_CHANNEL channel );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_Write( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_DATA_TYPE value )

  Summary:
    Writes the selected digital port/latch.

  Description:
    This function writes to the selected digital port/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    value           - Value to be written into a port of width PORTS_DATA_TYPE

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_VALUE - 0x1234
    PLID_PORTS_Write(MY_PORTS_INSTANCE, MY_CHANNEL, MY_VALUE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_Write( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                       PORTS_DATA_TYPE value );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_Set( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                         PORTS_DATA_TYPE value,
                         PORTS_DATA_MASK mask )

  Summary:
    Writes the selected digital port/latch based on the mask.

  Description:
    This function writes to the selected digital port/latch relative to the mask.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    value           - Value to be written into a port of width PORTS_DATA_TYPE
    mask            - Identifies the bits to be written to

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_VALUE - 0x1234
    PORTS_DATA_MASK myMask = (PORTS_DATA_MASK)0x00FF;
    PLIB_PORTS_Set(MY_PORTS_INSTANCE, MY_CHANNEL, MY_VALUE, myMask);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_Set( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                     PORTS_DATA_TYPE value,
                     PORTS_DATA_MASK mask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_Toggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                            PORTS_DATA_MASK toggleMask )

  Summary:
    Toggles the selected digital port/latch.

  Description:
    This function toggles the selected digital port/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    toggleMask      - Identifies the bits to be toggled

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK toggleMask = (PORTS_DATA_MASK)0x00FF;
    PLIB_PORTS_Toggle(MY_PORTS_INSTANCE, MY_CHANNEL, toggleMask);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_Toggle( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                        PORTS_DATA_MASK toggleMask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_Clear( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                           PORTS_DATA_MASK clearMask )

  Summary:
    Clears the selected digital port/latch.

  Description:
    This function clears the selected digital port/latch.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    clearMask       - Identifies the bits to be cleared

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK clearMask = (PORTS_DATA_MASK)0x00FF;
    PLIB_PORTS_Clear(MY_PORTS_INSTANCE, MY_CHANNEL, clearMask);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsWrite in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_Clear( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                       PORTS_DATA_MASK clearMask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_DirectionInputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                       PORTS_DATA_MASK mask )

  Summary:
    Enables the read (input) direction for the selected port.

  Description:
    This function enables the read (input) direction for the selected port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    mask            - mask for the direction of width PORTS_DATA_MASK

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_DirectionInputSet(MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsDirection in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_DirectionInputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                   PORTS_DATA_MASK mask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_DirectionOutputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                        PORTS_DATA_MASK mask )

  Summary:
    Enables the write (output) direction for the selected port.

  Description:
    This function enables the write (output) direction for the selected port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    mask            - mask for the direction of width PORTS_DATA_MASK

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_DirectionOutputSet(MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsDirection in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_DirectionOutputSet( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                    PORTS_DATA_MASK mask );


// *****************************************************************************
/* Function:
    PORTS_DATA_MASK PLIB_PORTS_DirectionGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel )

  Summary:
    Reads the direction of the selected digital port.

  Description:
    This function reads the direction of the selected digital port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.

  Returns:
    Direction of the selected port of type PORTS_DATA_MASK

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PORTS_DATA_MASK readDir = PLIB_PORTS_DirectionGet(MY_PORTS_INSTANCE, MY_CHANNEL);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsDirection in your application to determine whether
	this feature is available.
*/

PORTS_DATA_MASK PLIB_PORTS_DirectionGet( PORTS_MODULE_ID index, PORTS_CHANNEL channel );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_OpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                     PORTS_DATA_MASK mask )

  Summary:
    Enables the open drain functionality for the selected port.

  Description:
    This function enables the open drain functionality for the selected port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    mask            - mask of type PORTS_DATA_MASK

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_OpenDrainEnable(MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsOpenDrain in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_OpenDrainEnable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                 PORTS_DATA_MASK mask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_OpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                      PORTS_DATA_MASK mask )

  Summary:
    Disables the open drain functionality for the selected port.

  Description:
    This function disables the open drain functionality for the selected port.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    channel         - Identifier for the PORTS channel A, B, C, etc.
    mask            - mask of type PORTS_DATA_MASK

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_OpenDrainDisable(MY_PORTS_INSTANCE, MY_CHANNEL, (PORTS_DATA_MASK)0x00FF);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPortsOpenDrain in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_OpenDrainDisable( PORTS_MODULE_ID index, PORTS_CHANNEL channel,
                                  PORTS_DATA_MASK mask );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticeEnable( PORTS_MODULE_ID index )

  Summary:
    Global Change Notice enable.

  Description:
    This function enables the global Change Notice feature.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_ChangeNoticeEnable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNotice in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeEnable( PORTS_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticeDisable( PORTS_MODULE_ID index )

  Summary:
    Global Change Notice disable.

  Description:
    This function disables the global Change Notice feature.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_ChangeNoticeDisable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNotice in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeDisable( PORTS_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinChangeNoticeEnable( PORTS_MODULE_ID         index,
                                           PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Port pin Change Notice enable.

  Description:
    This function enables the port pin Change Notice feature.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    PLIB_PORTS_PinChangeNoticeEnable(MY_PORTS_INSTANCE, MY_PINNUM);
    </code>

  Remarks:
 	This feature may not be available on all devices. Please refer to the
 	specific device data sheet to determine availability or use
 	PLIB_PORTS_ExistsPinChangeNotice in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinChangeNoticeEnable( PORTS_MODULE_ID         index,
                                       PORTS_CHANGE_NOTICE_PIN pinNum );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_PinChangeNoticeDisable( PORTS_MODULE_ID         index,
                                            PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Port pin Change Notice disable.

  Description:
    This function disables the port pin Change Notice feature.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    PLIB_PORTS_PinChangeNoticeDisable(MY_PORTS_INSTANCE, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsPinChangeNotice in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_PinChangeNoticeDisable( PORTS_MODULE_ID         index,
                                        PORTS_CHANGE_NOTICE_PIN pinNum );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticeInIdleEnable( PORTS_MODULE_ID index )

  Summary:
    CPU Idle mode halts Change Notice operation.

  Description:
    This function halts Change Notice operation on CPU Idle mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_ChangeNoticeInIdleEnable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNoticeInIdle in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeInIdleEnable( PORTS_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticeInIdleDisable( PORTS_MODULE_ID index )

  Summary:
    CPU Idle does not affect Change Notice operation.

  Description:
    This function allows change notice operation to continue upon CPU Idle mode.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    PLIB_PORTS_ChangeNoticeInIdleDisable(MY_PORTS_INSTANCE);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNoticeInIdle in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticeInIdleDisable( PORTS_MODULE_ID index );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullUpEnable( PORTS_MODULE_ID         index,
                                              PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Enable pull-up on input change.

  Description:
    This function enables pull-up on input change.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    PLIB_PORTS_ChangeNoticePullUpEnable(MY_PORTS_INSTANCE, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNoticePullUp in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullUpEnable( PORTS_MODULE_ID         index,
                                          PORTS_CHANGE_NOTICE_PIN pinNum );


// *****************************************************************************
/* Function:
    void PLIB_PORTS_ChangeNoticePullUpDisable( PORTS_MODULE_ID         index,
                                               PORTS_CHANGE_NOTICE_PIN pinNum )

  Summary:
    Disable pull-up on input change.

  Description:
    This function disables pull-up on input change.

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured
    pinNum          - Possible values of PORTS_CHANGE_NOTICE_PIN

  Returns:
    None.

  Example:
    <code>
    // Where MY_PORTS_INSTANCE, is the ports instance selected for use by the
    // application developer.
    // MY_PINNUM - PORTS_CHANGE_NOTICE_PIN_10
    PLIB_PORTS_ChangeNoticePullUpDisable(MY_PORTS_INSTANCE, MY_PINNUM);
    </code>

  Remarks:
	This feature may not be available on all devices. Please refer to the
	specific device data sheet to determine availability or use
	PLIB_PORTS_ExistsChangeNoticePullUp in your application to determine whether
	this feature is available.
*/

void PLIB_PORTS_ChangeNoticePullUpDisable( PORTS_MODULE_ID         index,
                                           PORTS_CHANGE_NOTICE_PIN pinNum );


// *****************************************************************************
// *****************************************************************************
// Section: PORTS Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_PORTS_ExistsRemapInput( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the RemapInput feature exists on the PORTS module 

  Description:
    This function identifies whether the RemapInput feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_RemapInput

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RemapInput feature is supported on the device
    - false  - The RemapInput feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsRemapInput( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsRemapOutput( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the RemapOutput feature exists on the PORTS module 

  Description:
    This function identifies whether the RemapOutput feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_RemapOutput

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The RemapOutput feature is supported on the device
    - false  - The RemapOutput feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsRemapOutput( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPinMode( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PinMode feature exists on the PORTS module 

  Description:
    This function identifies whether the PinMode feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinModeSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PinMode feature is supported on the device
    - false  - The PinMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPinMode( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPortsRead( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PortsRead feature exists on the PORTS module 

  Description:
    This function identifies whether the PortsRead feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinGet
    - PLIB_PORTS_Read

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PortsRead feature is supported on the device
    - false  - The PortsRead feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPortsRead( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPortsWrite( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PortsWrite feature exists on the PORTS module 

  Description:
    This function identifies whether the PortsWrite feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinWrite
    - PLIB_PORTS_PinSet
    - PLIB_PORTS_PinClear
    - PLIB_PORTS_PinToggle
    - PLIB_PORTS_Write
    - PLIB_PORTS_Set
    - PLIB_PORTS_Toggle
    - PLIB_PORTS_Clear

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PortsWrite feature is supported on the device
    - false  - The PortsWrite feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPortsWrite( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPortsDirection( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PortsDirection feature exists on the PORTS module 

  Description:
    This function identifies whether the PortsDirection feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinDirectionInputSet
    - PLIB_PORTS_PinDirectionOutputSet
    - PLIB_PORTS_DirectionInputSet
    - PLIB_PORTS_DirectionOutputSet
    - PLIB_PORTS_DirectionGet

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PortsDirection feature is supported on the device
    - false  - The PortsDirection feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPortsDirection( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPortsOpenDrain( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PortsOpenDrain feature exists on the PORTS module 

  Description:
    This function identifies whether the PortsOpenDrain feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinOpenDrainEnable
    - PLIB_PORTS_PinOpenDrainDisable
    - PLIB_PORTS_OpenDrainEnable
    - PLIB_PORTS_OpenDrainDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PortsOpenDrain feature is supported on the device
    - false  - The PortsOpenDrain feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPortsOpenDrain( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNotice( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNotice feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNotice feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticeEnable
    - PLIB_PORTS_ChangeNoticeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNotice feature is supported on the device
    - false  - The ChangeNotice feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNotice( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPinChangeNotice( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PinChangeNotice feature exists on the PORTS module 

  Description:
    This function identifies whether the PinChangeNotice feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinChangeNoticeEnable
    - PLIB_PORTS_PinChangeNoticeDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PinChangeNotice feature is supported on the device
    - false  - The PinChangeNotice feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPinChangeNotice( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticeInIdle( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticeInIdle feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticeInIdle feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticeInIdleEnable
    - PLIB_PORTS_ChangeNoticeInIdleDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticeInIdle feature is supported on the device
    - false  - The ChangeNoticeInIdle feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticeInIdle( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePullUp( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticePullup feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticePullup feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticePullUpEnable
    - PLIB_PORTS_ChangeNoticePullUpDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticePullup feature is supported on the device
    - false  - The ChangeNoticePullup feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePullUp( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPinModePerPort( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PinModePerPort feature exists on the PORTS module 

  Description:
    This function identifies whether the PinModePerPort feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinModePerPortSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PinModePerPort feature is supported on the device
    - false  - The PinModePerPort feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPinModePerPort( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePullDownPerPort( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticePullDownPerPort feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticePullDownPerPort feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticePullDownPerPortEnable
    - PLIB_PORTS_ChangeNoticePullDownPerPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticePullDownPerPort feature is supported on the device
    - false  - The ChangeNoticePullDownPerPort feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePullDownPerPort( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePullUpPerPort( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticePullUpPerPort feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticePullUpPerPort feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticePullUpPerPortEnable
    - PLIB_PORTS_ChangeNoticePullUpPerPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticePullUpPerPort feature is supported on the device
    - false  - The ChangeNoticePullUpPerPort feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePullUpPerPort( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsPinChangeNoticePerPort( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the PinChangeNoticePerPort feature exists on the PORTS module 

  Description:
    This function identifies whether the PinChangeNoticePerPort feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_PinChangeNoticePerPortEnable
    - PLIB_PORTS_PinChangeNoticePerPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The PinChangeNoticePerPort feature is supported on the device
    - false  - The PinChangeNoticePerPort feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsPinChangeNoticePerPort( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePerPortTurnOn( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticePerPortTurnOn feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticePerPortTurnOn feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticePerPortTurnOn
    - PLIB_PORTS_ChangeNoticePerPortTurnOff

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticePerPortTurnOn feature is supported on the device
    - false  - The ChangeNoticePerPortTurnOn feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePerPortTurnOn( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePerPortInIdle( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticeInIdlePerPort feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticeInIdlePerPort feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticeInIdlePerPortEnable
    - PLIB_PORTS_ChangeNoticeInIdlePerPortDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticeInIdlePerPort feature is supported on the device
    - false  - The ChangeNoticeInIdlePerPort feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePerPortInIdle( PORTS_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_PORTS_ExistsChangeNoticePerPortStatus( PORTS_MODULE_ID index )

  Summary:
    Identifies whether the ChangeNoticePerPortStatus feature exists on the PORTS module 

  Description:
    This function identifies whether the ChangeNoticePerPortStatus feature is available on the PORTS module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_PORTS_ChangeNoticePerPortHasOccured

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ChangeNoticePerPortStatus feature is supported on the device
    - false  - The ChangeNoticePerPortStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_PORTS_ExistsChangeNoticePerPortStatus( PORTS_MODULE_ID index );



#endif // #ifndef _PLIB_PORTS_H
/*******************************************************************************
 End of File
*/