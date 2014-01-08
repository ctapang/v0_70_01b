/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_Postscale_Default.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Postscale
    and its Variant : Default
    For following APIs :
        PLIB_TMR_PostscaleSelect
        PLIB_TMR_PostscaleGet
        PLIB_TMR_PostscaleDivisorGet
        PLIB_TMR_ExistsPostscale

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

#ifndef _TMR_POSTSCALE_DEFAULT_H
#define _TMR_POSTSCALE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_POSTSCALE_VREG(index)

  MASKs: 
    _TMR_POSTSCALE_MASK(index)

  POSs: 
    _TMR_POSTSCALE_POS(index)

  LENs: 
    _TMR_POSTSCALE_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_PostscaleSelect_Default

  Summary:
    Implements Default variant of PLIB_TMR_PostscaleSelect 

  Description:
    This template implements the Default variant of the PLIB_TMR_PostscaleSelect function.
*/

PLIB_TEMPLATE void TMR_PostscaleSelect_Default( TMR_MODULE_ID index , TMR_POSTSCALE postscale )
{
    _SFR_FIELD_WRITE( _TMR_POSTSCALE_VREG(index),
                      _TMR_POSTSCALE_MASK(index),
                      _TMR_POSTSCALE_POS(index),
                      postscale )
}


//******************************************************************************
/* Function :  TMR_PostscaleGet_Default

  Summary:
    Implements Default variant of PLIB_TMR_PostscaleGet 

  Description:
    This template implements the Default variant of the PLIB_TMR_PostscaleGet function.
*/

PLIB_TEMPLATE TMR_POSTSCALE TMR_PostscaleGet_Default( TMR_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_PostscaleDivisorGet_Default

  Summary:
    Implements Default variant of PLIB_TMR_PostscaleDivisorGet 

  Description:
    This template implements the Default variant of the PLIB_TMR_PostscaleDivisorGet function.
*/

PLIB_TEMPLATE uint16_t TMR_PostscaleDivisorGet_Default( TMR_MODULE_ID index , TMR_POSTSCALE postscale )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_ExistsPostscale_Default

  Summary:
    Implements Default variant of PLIB_TMR_ExistsPostscale

  Description:
    This template implements the Default variant of the PLIB_TMR_ExistsPostscale function.
*/

PLIB_TEMPLATE bool TMR_ExistsPostscale_Default( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_POSTSCALE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

