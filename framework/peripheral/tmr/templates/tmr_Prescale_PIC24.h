/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_Prescale_PIC24.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Prescale
    and its Variant : PIC24
    For following APIs :
        PLIB_TMR_PrescaleSelect
        PLIB_TMR_PrescaleGet
        PLIB_TMR_PrescaleDivisorGet
        PLIB_TMR_ExistsPrescale

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

#ifndef _TMR_PRESCALE_PIC24_H
#define _TMR_PRESCALE_PIC24_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_PRESCALE_PIC24_VREG(index)

  MASKs: 
    _TMR_PRESCALE_PIC24_MASK(index)

  POSs: 
    _TMR_PRESCALE_PIC24_POS(index)

  LENs: 
    _TMR_PRESCALE_PIC24_LEN(index)

*/

typedef struct
{
    TMR_PRESCALE    prescale;
    uint16_t        prescale_divisor;

} _TMR_DIVISOR_VALUE;


static const _TMR_DIVISOR_VALUE s_prescalerValues[] =
{
    {TMR_PRESCALE_1_TO_1,       1},
    {TMR_PRESCALE_1_TO_8,       8},
    {TMR_PRESCALE_1_TO_64,      64},
    {TMR_PRESCALE_1_TO_256,     256}
};


//******************************************************************************
/* Function :  TMR_PrescaleSelect_PIC24

  Summary:
    Implements PIC24 variant of PLIB_TMR_PrescaleSelect 

  Description:
    This template implements the PIC24 variant of the PLIB_TMR_PrescaleSelect function.
*/

PLIB_TEMPLATE void TMR_PrescaleSelect_PIC24( TMR_MODULE_ID index , TMR_PRESCALE prescale )
{
    _SFR_FIELD_WRITE( _TMR_PRESCALE_PIC24_VREG( index ),
                      _TMR_PRESCALE_PIC24_MASK( index ),
                      _TMR_PRESCALE_PIC24_POS( index ),
                      prescale );
}


//******************************************************************************
/* Function :  TMR_PrescaleGet_PIC24

  Summary:
    Implements PIC24 variant of PLIB_TMR_PrescaleGet 

  Description:
    This template implements the PIC24 variant of the PLIB_TMR_PrescaleGet function.
*/

PLIB_TEMPLATE TMR_PRESCALE TMR_PrescaleGet_PIC24( TMR_MODULE_ID index )
{
    return( _SFR_FIELD_READ( _TMR_PRESCALE_PIC24_VREG( index ),
                             _TMR_PRESCALE_PIC24_MASK( index ),
                             _TMR_PRESCALE_PIC24_POS( index ) ) );
}


//******************************************************************************
/* Function :  TMR_PrescaleDivisorGet_PIC24

  Summary:
    Implements PIC24 variant of PLIB_TMR_PrescaleDivisorGet 

  Description:
    This template implements the PIC24 variant of the PLIB_TMR_PrescaleDivisorGet function.
*/

PLIB_TEMPLATE uint16_t TMR_PrescaleDivisorGet_PIC24( TMR_MODULE_ID index , TMR_PRESCALE prescale )
{
    uint8_t i, arraySize = sizeof( s_prescalerValues )/sizeof( _TMR_DIVISOR_VALUE );

    for( i=0 ; i<arraySize; i++ )
    {
        if( ( prescale == s_prescalerValues[i].prescale ) )
        {
            return s_prescalerValues[i].prescale_divisor;
        }
    }

    PLIB_ASSERT(false, "Should never come here");

    return 0;
}


//******************************************************************************
/* Function :  TMR_ExistsPrescale_PIC24

  Summary:
    Implements PIC24 variant of PLIB_TMR_ExistsPrescale

  Description:
    This template implements the PIC24 variant of the PLIB_TMR_ExistsPrescale function.
*/

PLIB_TEMPLATE bool TMR_ExistsPrescale_PIC24( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_PRESCALE_PIC24_H*/

/******************************************************************************
 End of File
*/

