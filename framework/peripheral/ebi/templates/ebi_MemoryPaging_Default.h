/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_MemoryPaging_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemoryPaging
    and its Variant : Default
    For following APIs :
        PLIB_EBI_MemoryPagingSet
        PLIB_EBI_ExistsMemoryPaging

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

#ifndef _EBI_MEMORYPAGING_DEFAULT_H
#define _EBI_MEMORYPAGING_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_PAGEMODE0_VREG(index)
    _EBI_PAGESIZE0_VREG(index)
    _EBI_PAGEMODE1_VREG(index)
    _EBI_PAGESIZE1_VREG(index)
    _EBI_PAGEMODE2_VREG(index)
    _EBI_PAGESIZE2_VREG(index)

  MASKs: 
    _EBI_PAGEMODE0_MASK(index)
    _EBI_PAGESIZE0_MASK(index)
    _EBI_PAGEMODE1_MASK(index)
    _EBI_PAGESIZE1_MASK(index)
    _EBI_PAGEMODE2_MASK(index)
    _EBI_PAGESIZE2_MASK(index)

  POSs: 
    _EBI_PAGEMODE0_POS(index)
    _EBI_PAGESIZE0_POS(index)
    _EBI_PAGEMODE1_POS(index)
    _EBI_PAGESIZE1_POS(index)
    _EBI_PAGEMODE2_POS(index)
    _EBI_PAGESIZE2_POS(index)

  LENs: 
    _EBI_PAGEMODE0_LEN(index)
    _EBI_PAGESIZE0_LEN(index)
    _EBI_PAGEMODE1_LEN(index)
    _EBI_PAGESIZE1_LEN(index)
    _EBI_PAGEMODE2_LEN(index)
    _EBI_PAGESIZE2_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_MemoryPagingSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_MemoryPagingSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_MemoryPagingSet function.
*/

PLIB_TEMPLATE void EBI_MemoryPagingSet_Default( EBI_MODULE_ID index , int ChipSelectNumber , bool PageMode , EBI_PAGE_SIZE MemoryPageSize )
{
    switch (ChipSelectNumber)
	{
	case 0:
	_SFR_BIT_WRITE(_EBI_PAGEMODE0_VREG(index), _EBI_PAGEMODE0_POS(index), PageMode );
	_SFR_FIELD_WRITE(_EBI_PAGESIZE0_VREG(index), _EBI_PAGESIZE0_MASK(index), _EBI_PAGESIZE0_POS(index), MemoryPageSize );
	break;

	case 1:
	_SFR_BIT_WRITE(_EBI_PAGEMODE1_VREG(index), _EBI_PAGEMODE1_POS(index), PageMode );
	_SFR_FIELD_WRITE(_EBI_PAGESIZE1_VREG(index), _EBI_PAGESIZE1_MASK(index), _EBI_PAGESIZE1_POS(index), MemoryPageSize );
	break;
	
	case 2:
	_SFR_BIT_WRITE(_EBI_PAGEMODE2_VREG(index), _EBI_PAGEMODE2_POS(index), PageMode );
	_SFR_FIELD_WRITE(_EBI_PAGESIZE2_VREG(index), _EBI_PAGESIZE2_MASK(index), _EBI_PAGESIZE2_POS(index), MemoryPageSize );
	break;



	default:
        PLIB_ASSERT(false,"Chip Select Number is Invalid, Check input arguments");
	break;
	}
}


//******************************************************************************
/* Function :  EBI_ExistsMemoryPaging_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsMemoryPaging

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsMemoryPaging function.
*/

PLIB_TEMPLATE bool EBI_ExistsMemoryPaging_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_MEMORYPAGING_DEFAULT_H*/

/******************************************************************************
 End of File
*/

