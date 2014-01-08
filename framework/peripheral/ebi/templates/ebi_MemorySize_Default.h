/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_MemorySize_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemorySize
    and its Variant : Default
    For following APIs :
        PLIB_EBI_MemorySizeSet
        PLIB_EBI_MemorySizeGet
        PLIB_EBI_ExistsMemorySize

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

#ifndef _EBI_MEMORYSIZE_DEFAULT_H
#define _EBI_MEMORYSIZE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_MEMSIZE_VREG(index)

  MASKs: 
    _EBI_MEMSIZE_MASK(index)

  POSs: 
    _EBI_MEMSIZE_POS(index)

  LENs: 
    _EBI_MEMSIZE_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_MemorySizeSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemorySizeSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemorySizeSet function.
*/

PLIB_TEMPLATE void EBI_MemorySizeSet_Default( EBI_MODULE_ID index , EBI_MEMORY_SIZE MemorySize )
{
    _SFR_FIELD_WRITE( _EBI_MEMSIZE_VREG(index), _EBI_MEMSIZE_MASK(index),  _EBI_MEMSIZE_POS(index), MemorySize );
}


//******************************************************************************
/* Function :  EBI_MemorySizeGet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemorySizeGet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemorySizeGet function.
*/

PLIB_TEMPLATE EBI_MEMORY_SIZE EBI_MemorySizeGet_Default( EBI_MODULE_ID index )
{
    return ( _SFR_FIELD_READ(  _EBI_MEMSIZE_VREG(index), _EBI_MEMSIZE_MASK(index),  _EBI_MEMSIZE_POS(index)));
}


//******************************************************************************
/* Function :  EBI_ExistsMemorySize_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsMemorySize

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsMemorySize function.
*/

PLIB_TEMPLATE bool EBI_ExistsMemorySize_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_MEMORYSIZE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

