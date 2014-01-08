/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_ISRJumpTableBaseAddress_Default.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ISRJumpTableBaseAddress
    and its Variant : Default
    For following APIs :
        PLIB_ADC_IsrJumpTableBaseAddressSet
        PLIB_ADC_IsrJumpTableBaseAddressGet
        PLIB_ADC_ExistsISRJumpTableBaseAddress

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

#ifndef _ADC_ISRJUMPTABLEBASEADDRESS_DEFAULT_H
#define _ADC_ISRJUMPTABLEBASEADDRESS_DEFAULT_H

// ****************************************************************************
/*  ADC Sample size

  Summary:
    Data type defining the size of the adc sample register.

  Description:
    This data type defines  the size of the adc sample register.

  Remarks:
    None
*/

#define ADC_SAMPLE      uint32_t


//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_ISR_JUMP_TABLE_BASE_ADDRESS_VREG(index)

  MASKs: 
    _ADC_ISR_JUMP_TABLE_BASE_ADDRESS_MASK(index)

  POSs: 
    _ADC_ISR_JUMP_TABLE_BASE_ADDRESS_POS(index)

  LENs: 
    _ADC_ISR_JUMP_TABLE_BASE_ADDRESS_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_IsrJumpTableBaseAddressSet_Default

  Summary:
    Implements Default variant of PLIB_ADC_IsrJumpTableBaseAddressSet 

  Description:
    This template implements the Default variant of the PLIB_ADC_IsrJumpTableBaseAddressSet function.
*/

PLIB_TEMPLATE void ADC_IsrJumpTableBaseAddressSet_Default( ADC_MODULE_ID index , int baseAddr )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_IsrJumpTableBaseAddressGet_Default

  Summary:
    Implements Default variant of PLIB_ADC_IsrJumpTableBaseAddressGet 

  Description:
    This template implements the Default variant of the PLIB_ADC_IsrJumpTableBaseAddressGet function.
*/

PLIB_TEMPLATE int ADC_IsrJumpTableBaseAddressGet_Default( ADC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsISRJumpTableBaseAddress_Default

  Summary:
    Implements Default variant of PLIB_ADC_ExistsISRJumpTableBaseAddress

  Description:
    This template implements the Default variant of the PLIB_ADC_ExistsISRJumpTableBaseAddress function.
*/

PLIB_TEMPLATE bool ADC_ExistsISRJumpTableBaseAddress_Default( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_ISRJUMPTABLEBASEADDRESS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

