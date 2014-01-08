/*******************************************************************************
  OC Peripheral Library Template Implementation

  File Name:
    oc_BufferValue_32Bit_Variant.h

  Summary:
    OC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : BufferValue
    and its Variant : 32Bit_Variant
    For following APIs :
        PLIB_OC_Buffer32BitSet
        PLIB_OC_Buffer16BitSet
        PLIB_OC_ExistsBufferValue

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

#ifndef _OC_BUFFERVALUE_32BIT_VARIANT_H
#define _OC_BUFFERVALUE_32BIT_VARIANT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OC_BUF_VAL_VREG(index)

  MASKs: 
    _OC_BUF_VAL_MASK(index)

  POSs: 
    _OC_BUF_VAL_POS(index)

  LENs: 
    _OC_BUF_VAL_LEN(index)

*/


//******************************************************************************
/* Function :  OC_Buffer32BitSet_32Bit_Variant

  Summary:
    Implements 32Bit_Variant variant of PLIB_OC_Buffer32BitSet 

  Description:
    This template implements the 32Bit_Variant variant of the PLIB_OC_Buffer32BitSet function.
*/

PLIB_TEMPLATE void OC_Buffer32BitSet_32Bit_Variant( OC_MODULE_ID index , uint32_t val32Bit )
{
    _SFR_WRITE( _OC_BUF_VAL_VREG(index), val32Bit);
}


//******************************************************************************
/* Function :  OC_Buffer16BitSet_32Bit_Variant

  Summary:
    Implements 32Bit_Variant variant of PLIB_OC_Buffer16BitSet 

  Description:
    This template implements the 32Bit_Variant variant of the PLIB_OC_Buffer16BitSet function.
*/

PLIB_TEMPLATE void OC_Buffer16BitSet_32Bit_Variant( OC_MODULE_ID index , uint16_t val16Bit )
{
    _SFR_WRITE( _OC_BUF_VAL_VREG(index), (val16Bit & 0X0000ffff));
}


//******************************************************************************
/* Function :  OC_ExistsBufferValue_32Bit_Variant

  Summary:
    Implements 32Bit_Variant variant of PLIB_OC_ExistsBufferValue

  Description:
    This template implements the 32Bit_Variant variant of the PLIB_OC_ExistsBufferValue function.
*/

PLIB_TEMPLATE bool OC_ExistsBufferValue_32Bit_Variant( OC_MODULE_ID index )
{
    return true;
}


#endif /*_OC_BUFFERVALUE_32BIT_VARIANT_H*/

/******************************************************************************
 End of File
*/

