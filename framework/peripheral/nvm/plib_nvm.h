/*******************************************************************************
  NVM Peripheral Library Interface Header

  Summary:
    NVM PLIB Interface Header for NVM common definitions

  Description:
    This header file contains the function prototypes and definitions of
    the data types and constants that make up the interface to the NVM
    PLIB for all families of Microchip microcontrollers..The definitions in
    this file are common to NVM peripheral.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
/******************************************************************************
File Name:  plib_nvm.h
Copyright © 2010,2011 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _PLIB_NVM_H
    #define _PLIB_NVM_H

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/*  A brief description of a section can be given directly below the section
    banner.
*/	

// ****************************************************************************
// ****************************************************************************
// Section: Included Files (continued at end of file)
// ****************************************************************************
// ****************************************************************************
/*  This section lists the other files that are inlcuded in this file.  However,
    please see the bottom of the file for additional implementation header files
    that are also included
 */

#include "processor/nvm_processor.h"


// ****************************************************************************
// ****************************************************************************
// Section: NVM Peripheral Library Interface Routines
// ****************************************************************************
// ****************************************************************************

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashAccessEnable( NVM_MODULE_ID index)

  Summary:
    Allows access to the Flash program memory		  

  Description:
    This routine allows access to the Flash program memory

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashAccessEnable(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsAccessEnable in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_FlashAccessEnable ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMAccessEnable ( NVM_MODULE_ID index)

  Summary:
    Allows access to the EEPROM program memory		  

  Description:
    This routine allows access to the EEPROM program memory

  Precondition:
    None.

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_EEPROMAccessEnable(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsAccessEnable in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_EEPROMAccessEnable ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashEraseOperationSelect( NVM_MODULE_ID index)

  Summary:
    Performs erase operation on the memory row selected		  

  Description:
    This routine Performs erase operation on the flash memory row selected

  Precondition:
    The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
	The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashEraseOperationSelect(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsProgramEraseOperation in your 
	application to determine whether this feature is available.

*/

void PLIB_NVM_FlashEraseOperationSelect ( NVM_MODULE_ID index); //For ERASE and FREE

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashWriteOperationSelect( NVM_MODULE_ID index)

  Summary:
    Performs erase operation on the memory row selected		  

  Description:
    This routine Performs erase operation on the flash memory row selected

  Precondition:
    The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
	The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashWriteOperationSelect(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsProgramEraseOperation in your 
	application to determine whether this feature is available.

*/

void PLIB_NVM_FlashWriteOperationSelect ( NVM_MODULE_ID index);

//******************************************************************************
/* Function:
		void PLIB_NVM_FlashEraseStart( NVM_MODULE_ID index)

	  Summary:
		Performs erase operation on the memory row selected		  

	  Description:
		This routine Performs erase operation on the flash memory row selected

	  Precondition:
		The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
			The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().

	  Parameters:
		index           - Identifier for the device instance to be configured

	  Returns:
		None.

	  Example:
		<code>
		PLIB_NVM_FlashEraseStart(MY_NVM_INSTANCE);
		</code>

	  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.
	 */

void PLIB_NVM_FlashEraseStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
		void PLIB_NVM_FlashWriteStart( NVM_MODULE_ID index)

	  Summary:
		Performs erase operation on the memory row selected		  

	  Description:
		This routine Performs erase operation on the flash memory row selected

	  Precondition:
		The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
			The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().

	  Parameters:
		index           - Identifier for the device instance to be configured

	  Returns:
		None.

	  Example:
		<code>
		PLIB_NVM_FlashWriteStart(MY_NVM_INSTANCE);
		</code>

	  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.
	 */

void PLIB_NVM_FlashWriteStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    bool PLIB_NVM_FlashWriteCycleHasCompleted( NVM_MODULE_ID index)

  Summary:
    This routine provides the status of the Flash/EEPROM write cycle.	  

  Description:
    This routine provides the status of the Flash/EEPROM write cycle which was initiated by a write/erase operation.

  Precondition:
    The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
        The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().
        A Write cycle must have been initiated via PLIB_NVM_EEPROMWriteInitiate().

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Write/Erase Cycle is incomplete.
    0 - Write cycle completed

  Example:
    <code>
        bool status;
    status = PLIB_NVM_FlashWriteCycleHasCompleted(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.

 */

bool PLIB_NVM_FlashWriteCycleHasCompleted ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    bool PLIB_NVM_WriteOperationHasTerminated( NVM_MODULE_ID index)

  Summary:
    This routine provides the status of the Flash/EEPROM write operation or sequence.	  

  Description:
    This routine provides the status of the Flash/EEPROM write operation or sequence which was initiated by a write/erase operation.

  Precondition:
    The Address row to be erased must be provided earlier using PLIB_NVM_FlashAddressToModify().
    The module should be configured to access Flash memory using PLIB_NVM_FlashMemoryAccessEnable().
    A Write cycle must have been initiated via PLIB_NVM_EEPROMWriteInitiate().

  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Write operation prematurely terminated.
    0 - Write operation completed.

  Example:
    <code>
        bool status;
    status = PLIB_NVM_WriteOperationHasTerminated(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteErrorStatus in your 
	application to determine whether this feature is available.

 */

bool PLIB_NVM_WriteOperationHasTerminated ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_MemoryModifyEnable( NVM_MODULE_ID index)

  Summary:
    Allows write cycles to Flash/EEPROM		  

  Description:
    This routine allows write cycles to Flash/EEPROM

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_MemoryModifyEnable(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsMemoryModificationControl in your 
	application to determine whether this feature is available.

 */

 void PLIB_NVM_MemoryModifyEnable ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_MemoryModifyInhibit( NVM_MODULE_ID index)

  Summary:
    Inhibits write cycles to Flash/EEPROM		  

  Description:
    This routine Inhibits write cycles to Flash/EEPROM

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_MemoryModifyInhibit(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsMemoryModificationControl in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_MemoryModifyInhibit ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMReadStart( NVM_MODULE_ID index)

  Summary:
    Initiates a EEPROM read cycle		  

  Description:
    This routine initiates the EERPOM read cycles

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_EEPROMReadStart(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_EEPROMReadStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    uint32_t PLIB_NVM_FlashRead( NVM_MODULE_ID index, uint32_t address)

  Summary:
    Takes the address parameter in the argument and loads the read address to 
        the appropriate register and returns the value read.

  Description:
    This routine takes the address parameter in the argument and loads the read address to 
        the appropriate register. The read operation provides data from the above address.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured
	
        address			- The address in the memory from which to read

  Returns:
    Data value read at the memory address.

  Example:
    <code>
        uint32_t	DataToBeRead;
    DataToBeRead = PLIB_NVM_FlashRead(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.

 */

uint32_t PLIB_NVM_FlashRead ( NVM_MODULE_ID index , uint32_t address ) ;

//******************************************************************************
/* Function:
    uint32_t PLIB_NVM_EEPROMRead( NVM_MODULE_ID index, uint32_t address)

  Summary:
    Takes the address parameter in the argument and loads the read address to 
        the appropriate register and returns the value read.

  Description:
    This routine takes the address parameter in the argument and loads the read address to 
        the appropriate register. The read operation provides data from the above address.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured
	
        address			- The address in the EEPROM memory from data is to be read

  Returns:
    Data value read at the EEPROM address.

  Example:
    <code>
        uint32_t	DataToBeRead;
    DataToBeRead = PLIB_NVM_EEPROMRead(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.

 */

uint32_t PLIB_NVM_EEPROMRead ( NVM_MODULE_ID index , uint32_t address ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashAddressToModify( NVM_MODULE_ID index, uint32_t address)

  Summary:
    Takes the address parameter in the argument and loads the address which will be 
        modified by the actual write operation to the appropriate pointer registers .

  Description:
    This routine takes the address parameter in the argument and loads the address 
        which will be modified by the actual write operation. The write operation following
        this will write the user data into the program memory.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured
	
        address			- The starting address in the memory from which data will be written

  Returns:
    None.

  Example:
    <code>
        uint32_t	address = MY_FLASH_BASE_ADDRESS;
    PLIB_NVM_FlashAddressToModify(MY_NVM_INSTANCE, address);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsAddressModifyControl in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashAddressToModify ( NVM_MODULE_ID index , uint32_t address ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMAddressToModify( NVM_MODULE_ID index, uint32_t address)

  Summary:
    Takes the address parameter in the argument and loads the EEPROM address which will be 
        modified by the actual write or erase operation to the appropriate pointer registers .

  Description:
    This routine takes the address parameter in the argument and loads the EEPROM address 
        which will be modified by the actual write or erase operation. The write or erase
        operation following this will write the user data into the program memory.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured
	
        address			- The starting address in the EEPROM memory from which data will be written

  Returns:
    None.

  Example:
    <code>
        uint32_t	address = MY_EEPROM_BASE_ADDRESS;
    PLIB_NVM_EEPROMAddressToModify(MY_NVM_INSTANCE, address);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsAddressModifyControl in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_EEPROMAddressToModify ( NVM_MODULE_ID index , uint32_t address ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashProvideData( NVM_MODULE_ID index, uint32_t data)

  Summary:
    Provides the user data to intermediate registers before written into flash

  Description:
    This routine provides the user data to intermediate registers before written into flash.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

        data			- Data to be written.
  Returns:
    None.

  Example:
    <code>
        uint32_t DataToWrite;
    PLIB_NVM_FlashProvideData(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsProvideData in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashProvideData ( NVM_MODULE_ID index , uint32_t data ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMProvideData( NVM_MODULE_ID index, uint32_t data)

  Summary:
    Provides the user data to intermediate registers before written into EEPROM

  Description:
    This routine provides the user data to intermediate registers before written into EEPROM.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

        data			- Data to be written.
  Returns:
    None.

  Example:
    <code>
        uint32_t DataToWrite;
    PLIB_NVM_EEPROMProvideData(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsProvideData in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_EEPROMProvideData ( NVM_MODULE_ID index , uint32_t data ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashWriteStart( NVM_MODULE_ID index)

  Summary:
    Initiates a Program memory erase/write cycle		  

  Description:
    This routine initiates the program memory erase or write cycles

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashWriteStart(MY_NVM_INSTANCE);
    </code>

  Remarks:
	Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.

 */

void PLIB_NVM_FlashWriteStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_FlashEraseStart( NVM_MODULE_ID index)

  Summary:
    Initiates a Program memory erase/write cycle		  

  Description:
    This routine initiates the program memory erase or write cycles

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashEraseStart(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
	Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashEraseStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMWriteStart( NVM_MODULE_ID index)

  Summary:
    Initiates a Program memory erase/write cycle		  

  Description:
    This routine initiates the program memory erase or write cycles

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
        PLIB_NVM_EEPROMWriteStart(MY_NVM_INSTANCE);
    </code>

  Remarks:
	Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_EEPROMWriteStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMEraseStart( NVM_MODULE_ID index)

  Summary:
    Initiates a Program memory erase/write cycle		  

  Description:
    This routine initiates the program memory erase or write cycles

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_EEPROMEraseStart(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
	Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsWriteOperation in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_EEPROMEraseStart ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_MemoryOperationSelect( NVM_MODULE_ID index, NVM_OPERATION_TYPE_SELECT	operationmode)

  Summary:
    Selects the operation to be performed on Flash/EEPROM memory.

  Description:
    This routine selects the operation to be performed on Flash/EEPROM memory.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_MemoryOperationSelect(MY_NVM_INSTANCE, NVM_MEMORY_ROW_PROGRAM_OPERATION);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsOperationMode in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_MemoryOperationSelect ( NVM_MODULE_ID index , NVM_OPERATION_MODE	operationmode ) ;


//******************************************************************************
/* Function:
    void PLIB_NVM_FlashWriteKeySequence( NVM_MODULE_ID index, uint32_t keysequence)

  Summary:
    Copies the mandatory KEY sequence into the respective registers.

  Description:
    This routine copies the mandatory KEY sequence into the respective registers.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

        keysequence		- Mandatory KEY sequence depending on the controller type
	
  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_FlashWriteKeySequence(MY_NVM_INSTANCE, keysequence);
    </code>

  Remarks:
    Without the KEY sequence write/erase operation will not be executed.

    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsKeySequence in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashWriteKeySequence ( NVM_MODULE_ID index , uint32_t keysequence ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_EEPROMWriteKeySequence( NVM_MODULE_ID index, uint32_t keysequence)

  Summary:
    Copies the mandatory KEY sequence into the respective registers.

  Description:
    This routine copies the mandatory KEY sequence into the respective registers.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

        keysequence		- Mandatory KEY sequence depending on the controller type
	
  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_EEPROMWriteKeySequence(MY_NVM_INSTANCE, keysequence);
    </code>

  Remarks:
    Without the KEY sequence write/erase operation will not be executed.

    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsKeySequence in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_EEPROMWriteKeySequence ( NVM_MODULE_ID index , uint32_t keysequence ) ;


//******************************************************************************
/* Function:
    void PLIB_NVM_DataBlockSourceAddress( NVM_MODULE_ID index, uint32_t address)

  Summary:
    Takes the address parameter in the argument and loads the base address from 
    which data has to be copied into flash.

  Description:
    This routine takes the address parameter in the argument and loads the base address from 
    which data has to be copied into flash. This is to copy a row of data directly into flash
    in one iteration without handling any intermediate holding registers.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured
    address	    - The starting address in the user date memory from which
                                                data will be written

  Returns:
    None.

  Example:
    <code>
    uint32_t	address = MY_RAM_BASE_ADDRESS;
    PLIB_NVM_DataBlockSourceAddress(MY_NVM_INSTANCE, address);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsSourceAddress in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_DataBlockSourceAddress ( NVM_MODULE_ID index , uint32_t address ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_StopInIdleEnable( NVM_MODULE_ID index)

  Summary:
    Discontinues Flash operation when device enters idle mode.

  Description:
    This routine discontinues Flash operation when device enters idle mode.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_StopInIdleEnable(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsStopInIdle in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_StopInIdleEnable ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    void PLIB_NVM_StopInIdleDisable( NVM_MODULE_ID index)

  Summary:
    Continues Flash operation when device enters idle mode.

  Description:
    This routine continues Flash operation when device enters idle mode.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    None.

  Example:
    <code>
    PLIB_NVM_StopInIdleDisable(MY_NVM_INSTANCE, DataToWrite);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsStopInIdle in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_StopInIdleDisable ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageIsDetected( NVM_MODULE_ID index)

  Summary:
    Provides low voltage error detection status

  Description:
    This routine provides detection of low voltage error status

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage detection and possible data corruption
        0 - Voltage Level Acceptable for programming.

  Example:
    <code>
        bool status;
    status = PLIB_NVM_LowVoltageIsDetected(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

bool PLIB_NVM_LowVoltageIsDetected ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

bool PLIB_NVM_LowVoltageEventIsActive ( NVM_MODULE_ID index ) ;

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_ProgramFlashBank1LowerRegion(NVM_MODULE_ID index);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_ProgramFlashBank2LowerRegion(NVM_MODULE_ID index);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashProvideQuadData(NVM_MODULE_ID index, uint32_t *data);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_LockProgramFlashMemory(NVM_MODULE_ID index);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

bool PLIB_NVM_IsProgramFlashMemoryLocked(NVM_MODULE_ID index);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_FlashWriteProtectMemoryAreaRange(NVM_MODULE_ID index, uint32_t address);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_LockBootMemory(NVM_MODULE_ID index, NVM_BOOT_MEMORY_AREA memoryArea);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

bool PLIB_NVM_IsBootMemoryLocked(NVM_MODULE_ID index, NVM_BOOT_MEMORY_AREA memoryArea);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_BootPageWriteProtectionEnable(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

void PLIB_NVM_BootPageWriteProtectionDisable(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage);

//******************************************************************************
/* Function:
    bool PLIB_NVM_LowVoltageEventIsActive( NVM_MODULE_ID index)

  Summary:
    Provides low voltage detection status

  Description:
    This routine provides detection of low voltage event if any.

  Precondition:
    None.
	
  Parameters:
    index           - Identifier for the device instance to be configured

  Returns:
    1 - Low Voltage Event active.
    0 - Low Voltage Event not Active

  Example:
    <code>
    bool status;
    status = PLIB_NVM_LowVoltageEventIsActive(MY_NVM_INSTANCE);
    </code>

  Remarks:
    Note: This feature may not be available on all devices. Please refer to the specific 
	device data sheet to determine availability or use PLIB_NVM_ExistsLowVoltageStatus in your 
	application to determine whether this feature is available.
 */

bool PLIB_NVM_IsBootPageWriteProtected(NVM_MODULE_ID index, NVM_BOOT_MEMORY_PAGE bootPage);


// *****************************************************************************
// *****************************************************************************
// Section: NVM Peripheral Library Exists API Routines
// *****************************************************************************
// *****************************************************************************
/* The functions below indicate the existence of the features on the device. 
*/

//******************************************************************************
/* Function :  PLIB_NVM_ExistsAccessEnable( NVM_MODULE_ID index )

  Summary:
    Identifies whether the AccessEnableControl feature exists on the NVM module 

  Description:
    This function identifies whether the AccessEnableControl feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashAccessEnable
    - PLIB_NVM_EEPROMAccessEnable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AccessEnableControl feature is supported on the device
    - false  - The AccessEnableControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsAccessEnable( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsProgramEraseOperation( NVM_MODULE_ID index )

  Summary:
    Identifies whether the ProgramEraseOperation feature exists on the NVM module 

  Description:
    This function identifies whether the ProgramEraseOperation feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashEraseOperationSelect
    - PLIB_NVM_FlashWriteOperationSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ProgramEraseOperation feature is supported on the device
    - false  - The ProgramEraseOperation feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsProgramEraseOperation( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsEEPROMReadInitiate( NVM_MODULE_ID index )

  Summary:
    Identifies whether the EEPROMReadInitiate feature exists on the NVM module 

  Description:
    This function identifies whether the EEPROMReadInitiate feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_EEPROMReadStart

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The EEPROMReadInitiate feature is supported on the device
    - false  - The EEPROMReadInitiate feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsEEPROMReadInitiate( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsStopInIdle( NVM_MODULE_ID index )

  Summary:
    Identifies whether the StopInIdle feature exists on the NVM module 

  Description:
    This function identifies whether the StopInIdle feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_StopInIdleEnable
    - PLIB_NVM_StopInIdleDisable

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The StopInIdle feature is supported on the device
    - false  - The StopInIdle feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsStopInIdle( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsWriteErrorStatus( NVM_MODULE_ID index )

  Summary:
    Identifies whether the WriteErrorStatus feature exists on the NVM module 

  Description:
    This function identifies whether the WriteErrorStatus feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_WriteOperationHasTerminated

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WriteErrorStatus feature is supported on the device
    - false  - The WriteErrorStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsWriteErrorStatus( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsMemoryModificationControl( NVM_MODULE_ID index )

  Summary:
    Identifies whether the MemoryModificationControl feature exists on the NVM module 

  Description:
    This function identifies whether the MemoryModificationControl feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_MemoryModifyEnable
    - PLIB_NVM_MemoryModifyInhibit

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The MemoryModificationControl feature is supported on the device
    - false  - The MemoryModificationControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsMemoryModificationControl( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsOperationMode( NVM_MODULE_ID index )

  Summary:
    Identifies whether the OperationMode feature exists on the NVM module 

  Description:
    This function identifies whether the OperationMode feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_MemoryOperationSelect

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The OperationMode feature is supported on the device
    - false  - The OperationMode feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsOperationMode( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsAddressModifyControl( NVM_MODULE_ID index )

  Summary:
    Identifies whether the AddressModifyControl feature exists on the NVM module 

  Description:
    This function identifies whether the AddressModifyControl feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashAddressToModify
    - PLIB_NVM_EEPROMAddressToModify

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The AddressModifyControl feature is supported on the device
    - false  - The AddressModifyControl feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsAddressModifyControl( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsProvideData( NVM_MODULE_ID index )

  Summary:
    Identifies whether the ProvideData feature exists on the NVM module 

  Description:
    This function identifies whether the ProvideData feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashProvideData
    - PLIB_NVM_EEPROMProvideData

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ProvideData feature is supported on the device
    - false  - The ProvideData feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsProvideData( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsWriteOperation( NVM_MODULE_ID index )

  Summary:
    Identifies whether the WriteOperation feature exists on the NVM module 

  Description:
    This function identifies whether the WriteOperation feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashRead
    - PLIB_NVM_EEPROMRead
    - PLIB_NVM_FlashWriteStart
    - PLIB_NVM_FlashEraseStart
    - PLIB_NVM_EEPROMWriteStart
    - PLIB_NVM_EEPROMEraseStart
    - PLIB_NVM_FlashWriteCycleHasCompleted

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The WriteOperation feature is supported on the device
    - false  - The WriteOperation feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsWriteOperation( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsKeySequence( NVM_MODULE_ID index )

  Summary:
    Identifies whether the KeySequence feature exists on the NVM module 

  Description:
    This function identifies whether the KeySequence feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashWriteKeySequence
    - PLIB_NVM_EEPROMWriteKeySequence

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The KeySequence feature is supported on the device
    - false  - The KeySequence feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsKeySequence( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsSourceAddress( NVM_MODULE_ID index )

  Summary:
    Identifies whether the SourceAddress feature exists on the NVM module 

  Description:
    This function identifies whether the SourceAddress feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_DataBlockSourceAddress

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The SourceAddress feature is supported on the device
    - false  - The SourceAddress feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsSourceAddress( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsLowVoltageStatus( NVM_MODULE_ID index )

  Summary:
    Identifies whether the LowVoltageStatus feature exists on the NVM module 

  Description:
    This function identifies whether the LowVoltageStatus feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_LowVoltageEventIsActive

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LowVoltageStatus feature is supported on the device
    - false  - The LowVoltageStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsLowVoltageStatus( NVM_MODULE_ID index );

//******************************************************************************
/* Function :  PLIB_NVM_ExistsLowVoltageError( NVM_MODULE_ID index )

  Summary:
    Identifies whether the LowVoltageError feature exists on the NVM module 

  Description:
    This function identifies whether the LowVoltageStatus feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_LowVoltageIsDetected 

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LowVoltageStatus feature is supported on the device
    - false  - The LowVoltageStatus feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsLowVoltageError( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsFlashBankRegionSelect( NVM_MODULE_ID index )

  Summary:
    Identifies whether the FlashBankRegionSelect feature exists on the NVM module 

  Description:
    This function identifies whether the FlashBankRegionSelect feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_ProgramFlashBank1LowerRegion
    - PLIB_NVM_ProgramFlashBank2LowerRegion

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The FlashBankRegionSelect feature is supported on the device
    - false  - The FlashBankRegionSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsFlashBankRegionSelect( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsProvideQuadData( NVM_MODULE_ID index )

  Summary:
    Identifies whether the ProvideQuadData feature exists on the NVM module 

  Description:
    This function identifies whether the ProvideQuadData feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashProvideQuadData

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The ProvideQuadData feature is supported on the device
    - false  - The ProvideQuadData feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsProvideQuadData( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsLockPFMSelect( NVM_MODULE_ID index )

  Summary:
    Identifies whether the LockPFMSelect feature exists on the NVM module 

  Description:
    This function identifies whether the LockPFMSelect feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_LockProgramFlashMemory
    - PLIB_NVM_IsProgramFlashMemoryLocked

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LockPFMSelect feature is supported on the device
    - false  - The LockPFMSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsLockPFMSelect( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsFlashWPMemoryRangeProvide( NVM_MODULE_ID index )

  Summary:
    Identifies whether the FlashWPMemoryRangeProvide feature exists on the NVM module 

  Description:
    This function identifies whether the FlashWPMemoryRangeProvide feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_FlashWriteProtectMemoryAreaRange

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The FlashWPMemoryRangeProvide feature is supported on the device
    - false  - The FlashWPMemoryRangeProvide feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsFlashWPMemoryRangeProvide( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsLockBootSelect( NVM_MODULE_ID index )

  Summary:
    Identifies whether the LockBootSelect feature exists on the NVM module 

  Description:
    This function identifies whether the LockBootSelect feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_LockBootMemory
    - PLIB_NVM_IsBootMemoryLocked

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The LockBootSelect feature is supported on the device
    - false  - The LockBootSelect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsLockBootSelect( NVM_MODULE_ID index );


//******************************************************************************
/* Function :  PLIB_NVM_ExistsBootPageWriteProtect( NVM_MODULE_ID index )

  Summary:
    Identifies whether the BootPageWriteProtect feature exists on the NVM module 

  Description:
    This function identifies whether the BootPageWriteProtect feature is available on the NVM module.
    When this function returns true, these functions are supported on the device: 
    - PLIB_NVM_BootPageWriteProtectionEnable
    - PLIB_NVM_BootPageWriteProtectionDisable
    - PLIB_NVM_IsBootPageWriteProtected

  Preconditions:
    None.

  Parameters:
    index           - Identifier for the device instance

  Returns:
    - true   - The BootPageWriteProtect feature is supported on the device
    - false  - The BootPageWriteProtect feature is not supported on the device

  Remarks:
    None.
*/

bool PLIB_NVM_ExistsBootPageWriteProtect( NVM_MODULE_ID index );


#endif  // #ifndef _PLIB_NVM_H
/******************************************************************************
 End of File
 */


