/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_ChipSelectEnable_EBIP32_144pin.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChipSelectEnable
    and its Variant : EBIP32_144pin
    For following APIs :
        PLIB_EBI_ChipSelectEnableSet
        PLIB_EBI_ExistsChipSelectEnable

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

#ifndef _EBI_CHIPSELECTENABLE_EBIP32_144PIN_H
#define _EBI_CHIPSELECTENABLE_EBIP32_144PIN_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_EBICSEN0_VREG(index)
    _EBI_EBICSEN1_VREG(index)
    _EBI_EBICSEN2_VREG(index)
    _EBI_EBICSEN3_VREG(index)

  MASKs: 
    _EBI_EBICSEN0_MASK(index)
    _EBI_EBICSEN1_MASK(index)
    _EBI_EBICSEN2_MASK(index)
    _EBI_EBICSEN3_MASK(index)

  POSs: 
    _EBI_EBICSEN0_POS(index)
    _EBI_EBICSEN1_POS(index)
    _EBI_EBICSEN2_POS(index)
    _EBI_EBICSEN3_POS(index)

  LENs: 
    _EBI_EBICSEN0_LEN(index)
    _EBI_EBICSEN1_LEN(index)
    _EBI_EBICSEN2_LEN(index)
    _EBI_EBICSEN3_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_ChipSelectEnableSet_EBIP32_144pin

  Summary:
    Implements EBIP32_144pin variant of PLIB_EBI_ChipSelectEnableSet 

  Description:
    This template implements the EBIP32_144pin variant of the PLIB_EBI_ChipSelectEnableSet function.
*/

PLIB_TEMPLATE void EBI_ChipSelectEnableSet_EBIP32_144pin( EBI_MODULE_ID index , bool ChipSelect0 , bool ChipSelect1 , bool ChipSelect2 , bool ChipSelect3 )
{
    _SFR_BIT_WRITE (_EBI_EBICSEN0_VREG(index), _EBI_EBICSEN0_POS(index), ChipSelect0);
    _SFR_BIT_WRITE (_EBI_EBICSEN1_VREG(index), _EBI_EBICSEN1_POS(index), ChipSelect1);
    _SFR_BIT_WRITE (_EBI_EBICSEN2_VREG(index), _EBI_EBICSEN2_POS(index), ChipSelect2);
    _SFR_BIT_WRITE (_EBI_EBICSEN3_VREG(index), _EBI_EBICSEN3_POS(index), ChipSelect3);
}


//******************************************************************************
/* Function :  EBI_ExistsChipSelectEnable_EBIP32_144pin

  Summary:
    Implements EBIP32_144pin variant of PLIB_EBI_ExistsChipSelectEnable

  Description:
    This template implements the EBIP32_144pin variant of the PLIB_EBI_ExistsChipSelectEnable function.
*/

PLIB_TEMPLATE bool EBI_ExistsChipSelectEnable_EBIP32_144pin( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_CHIPSELECTENABLE_EBIP32_144PIN_H*/

/******************************************************************************
 End of File
*/

