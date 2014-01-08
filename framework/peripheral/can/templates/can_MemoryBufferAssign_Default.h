/*******************************************************************************
  CAN Peripheral Library Template Implementation

  File Name:
    can_MemoryBufferAssign_Default.h

  Summary:
    CAN PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemoryBufferAssign
    and its Variant : Default
    For following APIs :
        PLIB_CAN_MemoryBufferAssign
        PLIB_CAN_ExistsMemoryBufferAssign

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

#ifndef _CAN_MEMORYBUFFERASSIGN_DEFAULT_H
#define _CAN_MEMORYBUFFERASSIGN_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _CAN_MEMORY_BUFFER_ASSIGN_VREG(index)

  MASKs: 
    _CAN_MEMORY_BUFFER_ASSIGN_MASK(index)

  POSs: 
    _CAN_MEMORY_BUFFER_ASSIGN_POS(index)

  LENs: 
    _CAN_MEMORY_BUFFER_ASSIGN_LEN(index)

*/


//******************************************************************************
/* Function :  CAN_MemoryBufferAssign_Default

  Summary:
    Implements Default variant of PLIB_CAN_MemoryBufferAssign 

  Description:
    This template implements the Default variant of the PLIB_CAN_MemoryBufferAssign function.
*/

PLIB_TEMPLATE void CAN_MemoryBufferAssign_Default( CAN_MODULE_ID index , void * buffer , int sizeInBytes )
{
    _SFR_WRITE(_CAN_MEMORY_BUFFER_ASSIGN_VREG(index), _PLIB_VirtToPhys(buffer));
    /* TODO Convert to physical address */
    /*TODO Add number of bytes*/
}


//******************************************************************************
/* Function :  CAN_ExistsMemoryBufferAssign_Default

  Summary:
    Implements Default variant of PLIB_CAN_ExistsMemoryBufferAssign

  Description:
    This template implements the Default variant of the PLIB_CAN_ExistsMemoryBufferAssign function.
*/

PLIB_TEMPLATE bool CAN_ExistsMemoryBufferAssign_Default( CAN_MODULE_ID index )
{
    return true;
}


#endif /*_CAN_MEMORYBUFFERASSIGN_DEFAULT_H*/

/******************************************************************************
 End of File
*/

