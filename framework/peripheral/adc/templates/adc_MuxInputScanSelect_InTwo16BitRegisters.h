/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_MuxInputScanSelect_InTwo16BitRegisters.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MuxInputScanSelect
    and its Variant : InTwo16BitRegisters
    For following APIs :
        PLIB_ADC_InputScanMaskAdd
        PLIB_ADC_InputScanMaskRemove
        PLIB_ADC_ExistsMuxInputScanSelect

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

#ifndef _ADC_MUXINPUTSCANSELECT_INTWO16BITREGISTERS_H
#define _ADC_MUXINPUTSCANSELECT_INTWO16BITREGISTERS_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_MUX_INPUT_SCAN_SELECT_TWO_16BITS_VREG(index)

  MASKs: 
    _ADC_MUX_INPUT_SCAN_SELECT_TWO_16BITS_MASK(index)

  POSs: 
    _ADC_MUX_INPUT_SCAN_SELECT_TWO_16BITS_POS(index)

  LENs: 
    _ADC_MUX_INPUT_SCAN_SELECT_TWO_16BITS_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_InputScanMaskAdd_InTwo16BitRegisters

  Summary:
    Implements InTwo16BitRegisters variant of PLIB_ADC_InputScanMaskAdd 

  Description:
    This template implements the InTwo16BitRegisters variant of the PLIB_ADC_InputScanMaskAdd function.
*/

PLIB_TEMPLATE void ADC_InputScanMaskAdd_InTwo16BitRegisters( ADC_MODULE_ID index , ADC_INPUTS_SCAN scanInputs )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_InputScanMaskRemove_InTwo16BitRegisters

  Summary:
    Implements InTwo16BitRegisters variant of PLIB_ADC_InputScanMaskRemove 

  Description:
    This template implements the InTwo16BitRegisters variant of the PLIB_ADC_InputScanMaskRemove function.
*/

PLIB_TEMPLATE void ADC_InputScanMaskRemove_InTwo16BitRegisters( ADC_MODULE_ID index , ADC_INPUTS_SCAN scanInputs )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsMuxInputScanSelect_InTwo16BitRegisters

  Summary:
    Implements InTwo16BitRegisters variant of PLIB_ADC_ExistsMuxInputScanSelect

  Description:
    This template implements the InTwo16BitRegisters variant of the PLIB_ADC_ExistsMuxInputScanSelect function.
*/

PLIB_TEMPLATE bool ADC_ExistsMuxInputScanSelect_InTwo16BitRegisters( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_MUXINPUTSCANSELECT_INTWO16BITREGISTERS_H*/

/******************************************************************************
 End of File
*/

