/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_DataEnable_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DataEnable
    and its Variant : Default
    For following APIs :
        PLIB_EBI_DataEnableSet
        PLIB_EBI_ExistsDataEnable

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

#ifndef _EBI_DATAENABLE_DEFAULT_H
#define _EBI_DATAENABLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_EBIDEN1_VREG(index)
    _EBI_EBIDEN0_VREG(index)

  MASKs: 
    _EBI_EBIDEN1_MASK(index)
    _EBI_EBIDEN0_MASK(index)

  POSs: 
    _EBI_EBIDEN1_POS(index)
    _EBI_EBIDEN0_POS(index)

  LENs: 
    _EBI_EBIDEN1_LEN(index)
    _EBI_EBIDEN0_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_DataEnableSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_DataEnableSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_DataEnableSet function.
*/

PLIB_TEMPLATE void EBI_DataEnableSet_Default( EBI_MODULE_ID index , bool DataUpperByte , bool DataLowerByte )
{
    _SFR_BIT_WRITE(_EBI_EBIDEN1_VREG(index), _EBI_EBIDEN1_POS(index), DataUpperByte );
    _SFR_BIT_WRITE(_EBI_EBIDEN0_VREG(index), _EBI_EBIDEN0_POS(index), DataLowerByte );
    
}


//******************************************************************************
/* Function :  EBI_ExistsDataEnable_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsDataEnable

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsDataEnable function.
*/

PLIB_TEMPLATE bool EBI_ExistsDataEnable_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_DATAENABLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

