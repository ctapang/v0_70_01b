/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_InputSelect_Default.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : InputSelect
    and its Variant : Default
    For following APIs :
        PLIB_ADC_InputSelectPositive
        PLIB_ADC_InputSelectNegative
        PLIB_ADC_ExistsInputSelect

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

#ifndef _ADC_INPUTSELECT_DEFAULT_H
#define _ADC_INPUTSELECT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_INPUT_SELECT_VREG(index)

  MASKs: 
    _ADC_INPUT_SELECT_MASK(index)

  POSs: 
    _ADC_INPUT_SELECT_POS(index)

  LENs: 
    _ADC_INPUT_SELECT_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_InputSelectPositive_Default

  Summary:
    Implements Default variant of PLIB_ADC_InputSelectPositive 

  Description:
    This template implements the Default variant of the PLIB_ADC_InputSelectPositive function.
*/

PLIB_TEMPLATE void ADC_InputSelectPositive_Default( ADC_MODULE_ID index , ADC_INPUTS_POSITIVE inputs )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_InputSelectNegative_Default

  Summary:
    Implements Default variant of PLIB_ADC_InputSelectNegative 

  Description:
    This template implements the Default variant of the PLIB_ADC_InputSelectNegative function.
*/

PLIB_TEMPLATE void ADC_InputSelectNegative_Default( ADC_MODULE_ID index , ADC_INPUTS_NEGATIVE negInput )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsInputSelect_Default

  Summary:
    Implements Default variant of PLIB_ADC_ExistsInputSelect

  Description:
    This template implements the Default variant of the PLIB_ADC_ExistsInputSelect function.
*/

PLIB_TEMPLATE bool ADC_ExistsInputSelect_Default( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_INPUTSELECT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

