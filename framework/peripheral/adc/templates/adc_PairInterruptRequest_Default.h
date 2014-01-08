/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_PairInterruptRequest_Default.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PairInterruptRequest
    and its Variant : Default
    For following APIs :
        PLIB_ADC_PairInterruptRequestEnable
        PLIB_ADC_PairInterruptRequestDisable
        PLIB_ADC_ExistsPairInterruptRequest

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

#ifndef _ADC_PAIRINTERRUPTREQUEST_DEFAULT_H
#define _ADC_PAIRINTERRUPTREQUEST_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_PAIR_INTERRUPT_REQUEST_VREG(index)

  MASKs: 
    _ADC_PAIR_INTERRUPT_REQUEST_MASK(index)

  POSs: 
    _ADC_PAIR_INTERRUPT_REQUEST_POS(index)

  LENs: 
    _ADC_PAIR_INTERRUPT_REQUEST_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_PairInterruptRequestEnable_Default

  Summary:
    Implements Default variant of PLIB_ADC_PairInterruptRequestEnable 

  Description:
    This template implements the Default variant of the PLIB_ADC_PairInterruptRequestEnable function.
*/

PLIB_TEMPLATE void ADC_PairInterruptRequestEnable_Default( ADC_MODULE_ID index , ADC_PAIR pairNum )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_PairInterruptRequestDisable_Default

  Summary:
    Implements Default variant of PLIB_ADC_PairInterruptRequestDisable 

  Description:
    This template implements the Default variant of the PLIB_ADC_PairInterruptRequestDisable function.
*/

PLIB_TEMPLATE void ADC_PairInterruptRequestDisable_Default( ADC_MODULE_ID index , ADC_PAIR pairNum )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsPairInterruptRequest_Default

  Summary:
    Implements Default variant of PLIB_ADC_ExistsPairInterruptRequest

  Description:
    This template implements the Default variant of the PLIB_ADC_ExistsPairInterruptRequest function.
*/

PLIB_TEMPLATE bool ADC_ExistsPairInterruptRequest_Default( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_PAIRINTERRUPTREQUEST_DEFAULT_H*/

/******************************************************************************
 End of File
*/

