/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_GlobalSoftwareTrigger_Default.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : GlobalSoftwareTrigger
    and its Variant : Default
    For following APIs :
        PLIB_ADC_GlobalSoftwareTriggerSet
        PLIB_ADC_ExistsGlobalSoftwareTrigger

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

#ifndef _ADC_GLOBALSOFTWARETRIGGER_DEFAULT_H
#define _ADC_GLOBALSOFTWARETRIGGER_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_GLOBAL_SOFTWARE_TRIGGER_VREG(index)

  MASKs: 
    _ADC_GLOBAL_SOFTWARE_TRIGGER_MASK(index)

  POSs: 
    _ADC_GLOBAL_SOFTWARE_TRIGGER_POS(index)

  LENs: 
    _ADC_GLOBAL_SOFTWARE_TRIGGER_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_GlobalSoftwareTriggerSet_Default

  Summary:
    Implements Default variant of PLIB_ADC_GlobalSoftwareTriggerSet 

  Description:
    This template implements the Default variant of the PLIB_ADC_GlobalSoftwareTriggerSet function.
*/

PLIB_TEMPLATE void ADC_GlobalSoftwareTriggerSet_Default( ADC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsGlobalSoftwareTrigger_Default

  Summary:
    Implements Default variant of PLIB_ADC_ExistsGlobalSoftwareTrigger

  Description:
    This template implements the Default variant of the PLIB_ADC_ExistsGlobalSoftwareTrigger function.
*/

PLIB_TEMPLATE bool ADC_ExistsGlobalSoftwareTrigger_Default( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_GLOBALSOFTWARETRIGGER_DEFAULT_H*/

/******************************************************************************
 End of File
*/

