/*******************************************************************************
  WDT Peripheral Library Template Implementation

  File Name:
    wdt_PostscalarValue_Default.h

  Summary:
    WDT PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PostscalarValue
    and its Variant : Default
    For following APIs :
        PLIB_WDT_ExistsPostscalarValue
        PLIB_WDT_PostscalarValueGet

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

#ifndef _WDT_POSTSCALARVALUE_DEFAULT_H
#define _WDT_POSTSCALARVALUE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _WDT_POSTSCALAR_VALUE_VREG(index)

  MASKs: 
    _WDT_POSTSCALAR_VALUE_MASK(index)

  POSs: 
    _WDT_POSTSCALAR_VALUE_POS(index)

  LENs: 
    _WDT_POSTSCALAR_VALUE_LEN(index)

*/


//******************************************************************************
/* Function :  WDT_ExistsPostscalarValue_Default

  Summary:
    Implements Default variant of PLIB_WDT_ExistsPostscalarValue

  Description:
    This template implements the Default variant of the PLIB_WDT_ExistsPostscalarValue function.
*/

PLIB_TEMPLATE bool WDT_ExistsPostscalarValue_Default( WDT_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  WDT_PostscalarValueGet_Default

  Summary:
    Implements Default variant of PLIB_WDT_PostscalarValueGet 

  Description:
    This template implements the Default variant of the PLIB_WDT_PostscalarValueGet function.
*/

PLIB_TEMPLATE char WDT_PostscalarValueGet_Default( WDT_MODULE_ID index )
{
    return _SFR_FIELD_READ(_WDT_POSTSCALAR_VALUE_VREG(index),
                                _WDT_POSTSCALAR_VALUE_MASK(index),
                                _WDT_POSTSCALAR_VALUE_POS(index));
}


#endif /*_WDT_POSTSCALARVALUE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

