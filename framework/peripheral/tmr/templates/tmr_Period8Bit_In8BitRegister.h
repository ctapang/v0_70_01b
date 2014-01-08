/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_Period8Bit_In8BitRegister.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Period8Bit
    and its Variant : In8BitRegister
    For following APIs :
        PLIB_TMR_Period8BitSet
        PLIB_TMR_Period8BitGet
        PLIB_TMR_ExistsPeriod8Bit

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

#ifndef _TMR_PERIOD8BIT_IN8BITREGISTER_H
#define _TMR_PERIOD8BIT_IN8BITREGISTER_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_PERIOD_REGISTER_8BIT_VREG(index)

  MASKs: 
    _TMR_PERIOD_REGISTER_8BIT_MASK(index)

  POSs: 
    _TMR_PERIOD_REGISTER_8BIT_POS(index)

  LENs: 
    _TMR_PERIOD_REGISTER_8BIT_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_Period8BitSet_In8BitRegister

  Summary:
    Implements In8BitRegister variant of PLIB_TMR_Period8BitSet 

  Description:
    This template implements the In8BitRegister variant of the PLIB_TMR_Period8BitSet function.
*/

PLIB_TEMPLATE void TMR_Period8BitSet_In8BitRegister( TMR_MODULE_ID index , uint8_t period )
{
    if( _TMR_PERIOD_MATCH_MODE_VREG( index ) == (SFR_TYPE *)-1 )
    {
        /* Overflow TMR */
        _SFR_WRITE( _TMR_VALUE_REGISTER_8BIT_VREG( index ), ((UINT8_MAX + 1) - (uint8_t)period) );
    }
    else
    {
        /* Period Match TMR */
        _SFR_WRITE( _TMR_PERIOD_REGISTER_8BIT_VREG( index ), period );
    }
}


//******************************************************************************
/* Function :  TMR_Period8BitGet_In8BitRegister

  Summary:
    Implements In8BitRegister variant of PLIB_TMR_Period8BitGet 

  Description:
    This template implements the In8BitRegister variant of the PLIB_TMR_Period8BitGet function.
*/

PLIB_TEMPLATE uint8_t TMR_Period8BitGet_In8BitRegister( TMR_MODULE_ID index )
{
    return( _SFR_GET( _TMR_PERIOD_REGISTER_8BIT_VREG( index ) ) );
}


//******************************************************************************
/* Function :  TMR_ExistsPeriod8Bit_In8BitRegister

  Summary:
    Implements In8BitRegister variant of PLIB_TMR_ExistsPeriod8Bit

  Description:
    This template implements the In8BitRegister variant of the PLIB_TMR_ExistsPeriod8Bit function.
*/

PLIB_TEMPLATE bool TMR_ExistsPeriod8Bit_In8BitRegister( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_PERIOD8BIT_IN8BITREGISTER_H*/

/******************************************************************************
 End of File
*/

