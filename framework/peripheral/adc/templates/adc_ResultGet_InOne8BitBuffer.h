/*******************************************************************************
  ADC Peripheral Library Template Implementation

  File Name:
    adc_ResultGet_InOne8BitBuffer.h

  Summary:
    ADC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ResultGet
    and its Variant : InOne8BitBuffer
    For following APIs :
        PLIB_ADC_ResultGet
        PLIB_ADC_ExistsResultGet

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

#ifndef _ADC_RESULTGET_INONE8BITBUFFER_H
#define _ADC_RESULTGET_INONE8BITBUFFER_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _ADC_RESULT_GET_IN_ONE_8BIT_BUFFER_VREG(index)

  MASKs: 
    _ADC_RESULT_GET_IN_ONE_8BIT_BUFFER_MASK(index)

  POSs: 
    _ADC_RESULT_GET_IN_ONE_8BIT_BUFFER_POS(index)

  LENs: 
    _ADC_RESULT_GET_IN_ONE_8BIT_BUFFER_LEN(index)

*/


//******************************************************************************
/* Function :  ADC_ResultGet_InOne8BitBuffer

  Summary:
    Implements InOne8BitBuffer variant of PLIB_ADC_ResultGet 

  Description:
    This template implements the InOne8BitBuffer variant of the PLIB_ADC_ResultGet function.
*/

PLIB_TEMPLATE ADC_SAMPLE ADC_ResultGet_InOne8BitBuffer( ADC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  ADC_ExistsResultGet_InOne8BitBuffer

  Summary:
    Implements InOne8BitBuffer variant of PLIB_ADC_ExistsResultGet

  Description:
    This template implements the InOne8BitBuffer variant of the PLIB_ADC_ExistsResultGet function.
*/

PLIB_TEMPLATE bool ADC_ExistsResultGet_InOne8BitBuffer( ADC_MODULE_ID index )
{
    return true;
}


#endif /*_ADC_RESULTGET_INONE8BITBUFFER_H*/

/******************************************************************************
 End of File
*/

