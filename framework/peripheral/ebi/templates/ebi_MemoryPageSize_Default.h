/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_MemoryPageSize_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemoryPageSize
    and its Variant : Default
    For following APIs :
        PLIB_EBI_MemoryPageSizeSet
        PLIB_EBI_MemoryPageSizeGet
        PLIB_EBI_ExistsMemoryPageSize

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

#ifndef _EBI_MEMORYPAGESIZE_DEFAULT_H
#define _EBI_MEMORYPAGESIZE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_PAGESIZE_VREG(index)

  MASKs: 
    _EBI_PAGESIZE_MASK(index)

  POSs: 
    _EBI_PAGESIZE_POS(index)

  LENs: 
    _EBI_PAGESIZE_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_MemoryPageSizeSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemoryPageSizeSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemoryPageSizeSet function.
*/

PLIB_TEMPLATE void EBI_MemoryPageSizeSet_Default( EBI_MODULE_ID index , EBI_PAGE_SIZE MemoryPageSize )
{
    _SRF_FIELD_WRITE( _EBI_PAGESIZE_VREG(index), _EBI_PAGESIZE_MASK(index),  _EBI_PAGESIZE_POS(index), MemoryPageSize);
}


//******************************************************************************
/* Function :  EBI_MemoryPageSizeGet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemoryPageSizeGet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemoryPageSizeGet function.
*/

PLIB_TEMPLATE EBI_PAGE_SIZE EBI_MemoryPageSizeGet_Default( EBI_MODULE_ID index )
{
    return (_SRF_FIELD_READ( _EBI_PAGESIZE_VREG(index), _EBI_PAGESIZE_MASK(index),  _EBI_PAGESIZE_POS(index)));
}


//******************************************************************************
/* Function :  EBI_ExistsMemoryPageSize_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsMemoryPageSize

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsMemoryPageSize function.
*/

PLIB_TEMPLATE bool EBI_ExistsMemoryPageSize_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_MEMORYPAGESIZE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

