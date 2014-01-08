/*******************************************************************************
  NVM Peripheral Library Template Implementation

  File Name:
    nvm_ProgramEraseOperation_Default.h

  Summary:
    NVM PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ProgramEraseOperation
    and its Variant : Default
    For following APIs :
        PLIB_NVM_ExistsProgramEraseOperation
        PLIB_NVM_FlashEraseOperationSelect
        PLIB_NVM_FlashWriteOperationSelect

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

//DOM-IGNORE-END

#ifndef _NVM_PROGRAMERASEOPERATION_DEFAULT_H
#define _NVM_PROGRAMERASEOPERATION_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _NVM_PROGRAM_ERASE_OPERATION_SELECT_VREG(index)

  MASKs: 
    _NVM_PROGRAM_ERASE_OPERATION_SELECT_MASK(index)

  POSs: 
    _NVM_PROGRAM_ERASE_OPERATION_SELECT_POS(index)

  LENs: 
    _NVM_PROGRAM_ERASE_OPERATION_SELECT_LEN(index)

*/


//******************************************************************************
/* Function :  NVM_ExistsProgramEraseOperation_Default

  Summary:
    Implements Default variant of PLIB_NVM_ExistsProgramEraseOperation

  Description:
    This template implements the Default variant of the PLIB_NVM_ExistsProgramEraseOperation function.
*/

PLIB_TEMPLATE bool NVM_ExistsProgramEraseOperation_Default( NVM_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  NVM_FlashEraseOperationSelect_Default

  Summary:
    Implements Default variant of PLIB_NVM_FlashEraseOperationSelect 

  Description:
    This template implements the Default variant of the PLIB_NVM_FlashEraseOperationSelect function.
*/

PLIB_TEMPLATE void NVM_FlashEraseOperationSelect_Default( NVM_MODULE_ID index )
{
    _SFR_BIT_SET(_NVM_PROGRAM_ERASE_OPERATION_SELECT_VREG(index), _NVM_PROGRAM_ERASE_OPERATION_SELECT_POS(index));
}


//******************************************************************************
/* Function :  NVM_FlashWriteOperationSelect_Default

  Summary:
    Implements Default variant of PLIB_NVM_FlashWriteOperationSelect 

  Description:
    This template implements the Default variant of the PLIB_NVM_FlashWriteOperationSelect function.
*/

PLIB_TEMPLATE void NVM_FlashWriteOperationSelect_Default( NVM_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_NVM_PROGRAM_ERASE_OPERATION_SELECT_VREG(index), _NVM_PROGRAM_ERASE_OPERATION_SELECT_POS(index));

}


#endif /*_NVM_PROGRAMERASEOPERATION_DEFAULT_H*/

/******************************************************************************
 End of File
*/

