/*******************************************************************************
  MPLAB Harmony Simple NVM Functions Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    simple_nvm_functions source file

  Description:
    This file contains functions that read and write to flash memory.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include "peripheral/nvm/plib_nvm.h"
#include "simple_nvm_functions.h"


/*******************************************************************************
/*
  Function:
    uint32_t virtualToPhysical (uint32_t address)

  Summary:
    Converts a virtual memory address to a physical one
*/
uint32_t virtualToPhysical(uint32_t address)
{
    return (address & 0x1FFFFFFF);
}


/*******************************************************************************
/*
  Function:
    void NVMpageErase (uint32_t address)

  Summary:
    Erases a page in flash memory (4096 bytes)
*/
void NVMpageErase(uint32_t address)
{
    // Base address of page to be erased
   PLIB_NVM_FlashAddressToModify(NVM_ID_0, virtualToPhysical(address));

   // Select page erase function & enable flash write/erase operations
   PLIB_NVM_MemoryOperationSelect(NVM_ID_0, PAGE_ERASE_OPERATION);

   // Write the unlock key sequence
   PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0xAA996655);
   PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0x556699AA);

   // Start the operation
   PLIB_NVM_FlashWriteStart(NVM_ID_0);

   // Wait until the operation has completed
   while (PLIB_NVM_FlashWriteCycleHasCompleted(NVM_ID_0));

   // Disable flash write/erase operations
   PLIB_NVM_MemoryModifyInhibit(NVM_ID_0);
}


/*******************************************************************************
/*
  Function:
    void NVMwriteWord (uint32_t address, uint32_t data)

  Summary:
    Writes a word in flash memory (4 bytes)
*/
void NVMwriteWord(uint32_t address, uint32_t data)
{
    // Base address of where word is to be written
   PLIB_NVM_FlashAddressToModify(NVM_ID_0, virtualToPhysical(address));
   // Word of data to be written
   PLIB_NVM_FlashProvideData(NVM_ID_0 , data);

   // Select word write function & enable flash write/erase operations
   PLIB_NVM_MemoryOperationSelect(NVM_ID_0, WORD_PROGRAM_OPERATION);

   // Write the unlock key sequence
   PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0xAA996655);
   PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0x556699AA);

   // Start the operation
   PLIB_NVM_FlashWriteStart(NVM_ID_0);

   // Wait until the operation has completed
   while (PLIB_NVM_FlashWriteCycleHasCompleted(NVM_ID_0));

   // Disable flash write/erase operations
   PLIB_NVM_MemoryModifyInhibit(NVM_ID_0);
}


/*******************************************************************************
/*
  Function:
    void NVMwriteRow (uint32_t destAddr, uint32_t srcAddr)

  Summary:
    Writes a row in flash memory (512 bytes)
*/
void NVMwriteRow(uint32_t destAddr, uint32_t srcAddr)
{
    // Base address of row to be written to (destination)
    PLIB_NVM_FlashAddressToModify(NVM_ID_0, virtualToPhysical(destAddr));
    // Data buffer address (source)
    PLIB_NVM_DataBlockSourceAddress(NVM_ID_0, virtualToPhysical(srcAddr));

    // Select row write function & enable flash write/erase operations
    PLIB_NVM_MemoryOperationSelect(NVM_ID_0, ROW_PROGRAM_OPERATION);

    // Write the unlock key sequence
    PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0xAA996655);
    PLIB_NVM_FlashWriteKeySequence(NVM_ID_0, 0x556699AA);

    // Start the operation
    PLIB_NVM_FlashWriteStart(NVM_ID_0);

    // Wait until the operation has completed
    while (PLIB_NVM_FlashWriteCycleHasCompleted(NVM_ID_0));

    // Disable flash write/erase operations
    PLIB_NVM_MemoryModifyInhibit(NVM_ID_0);
}


/*******************************************************************************
 End of File
*/

