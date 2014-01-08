/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_MemoryCharacteristics_EBIP32_100_124pin.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MemoryCharacteristics
    and its Variant : EBIP32_100_124pin
    For following APIs :
        PLIB_EBI_MemoryCharacteristicsSet
        PLIB_EBI_ExistsMemoryCharacteristics

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

#ifndef _EBI_MEMORYCHARACTERISTICS_EBIP32_100_124PIN_H
#define _EBI_MEMORYCHARACTERISTICS_EBIP32_100_124PIN_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_REGSEL0_100_VREG(index)
    _EBI_MEMTYPE0_100_VREG(index)
    _EBI_MEMSIZE0_100_VREG(index)

  MASKs: 
    _EBI_REGSEL0_100_MASK(index)
    _EBI_MEMTYPE0_100_MASK(index)
    _EBI_MEMSIZE0_100_MASK(index)

  POSs: 
    _EBI_REGSEL0_100_POS(index)
    _EBI_MEMTYPE0_100_POS(index)
    _EBI_MEMSIZE0_100_POS(index)

  LENs: 
    _EBI_REGSEL0_100_LEN(index)
    _EBI_MEMTYPE0_100_LEN(index)
    _EBI_MEMSIZE0_100_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_MemoryCharacteristicsSet_EBIP32_100_124pin

  Summary:
    Implements EBIP32_100_124pin variant of PLIB_EBI_MemoryCharacteristicsSet 

  Description:
    This template implements the EBIP32_100_124pin variant of the PLIB_EBI_MemoryCharacteristicsSet function.
*/

PLIB_TEMPLATE void EBI_MemoryCharacteristicsSet_EBIP32_100_124pin( EBI_MODULE_ID index , int ChipSelectNumber , EBI_MEMORY_TYPE MemoryType , EBI_MEMORY_SIZE MemorySize , EBI_CS_TIMING TimingReg )
{

switch (ChipSelectNumber)
	{
	case 0:
	_SFR_FIELD_WRITE(_EBI_MEMTYPE0_100_VREG(index), _EBI_MEMTYPE0_100_MASK(index), _EBI_MEMTYPE0_100_POS(index), MemoryType );
	_SFR_FIELD_WRITE(_EBI_MEMSIZE0_100_VREG(index), _EBI_MEMSIZE0_100_MASK(index), _EBI_MEMSIZE0_100_POS(index), MemorySize );
	_SFR_FIELD_WRITE(_EBI_REGSEL0_100_VREG(index), _EBI_REGSEL0_100_MASK(index), _EBI_REGSEL0_100_POS(index), TimingReg);
	break;

	default:
PLIB_ASSERT(false,"Chip Select Number is Invalid, Check input arguments");
	break;
	}
}


//******************************************************************************
/* Function :  EBI_ExistsMemoryCharacteristics_EBIP32_100_124pin

  Summary:
    Implements EBIP32_100_124pin variant of PLIB_EBI_ExistsMemoryCharacteristics

  Description:
    This template implements the EBIP32_100_124pin variant of the PLIB_EBI_ExistsMemoryCharacteristics function.
*/

PLIB_TEMPLATE bool EBI_ExistsMemoryCharacteristics_EBIP32_100_124pin( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_MEMORYCHARACTERISTICS_EBIP32_100_124PIN_H*/

/******************************************************************************
 End of File
*/

