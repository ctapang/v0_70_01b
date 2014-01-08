/*******************************************************************************
  INT Peripheral Library Template Implementation

  File Name:
    int_INTNesting_Default.h

  Summary:
    INT PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : INTNesting
    and its Variant : Default
    For following APIs :
        PLIB_INT_ExistsINTNesting
        PLIB_INT_NestingEnable
        PLIB_INT_NestingDisable

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

#ifndef _INT_INTNESTING_DEFAULT_H
#define _INT_INTNESTING_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _INT_INT_NESTING_VREG(index)

  MASKs: 
    _INT_INT_NESTING_MASK(index)

  POSs: 
    _INT_INT_NESTING_POS(index)

  LENs: 
    _INT_INT_NESTING_LEN(index)

*/


//******************************************************************************
/* Function :  INT_ExistsINTNesting_Default

  Summary:
    Implements Default variant of PLIB_INT_ExistsINTNesting

  Description:
    This template implements the Default variant of the PLIB_INT_ExistsINTNesting function.
*/

PLIB_TEMPLATE bool INT_ExistsINTNesting_Default( INT_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  INT_NestingEnable_Default

  Summary:
    Implements Default variant of PLIB_INT_NestingEnable 

  Description:
    This template implements the Default variant of the PLIB_INT_NestingEnable function.
*/

PLIB_TEMPLATE void INT_NestingEnable_Default( INT_MODULE_ID index )
{
	_SFR_BIT_SET(_INT_INT_NESTING_VREG(index), _INT_INT_NESTING_POS(index));
}


//******************************************************************************
/* Function :  INT_NestingDisable_Default

  Summary:
    Implements Default variant of PLIB_INT_NestingDisable 

  Description:
    This template implements the Default variant of the PLIB_INT_NestingDisable function.
*/

PLIB_TEMPLATE void INT_NestingDisable_Default( INT_MODULE_ID index )
{
	_SFR_BIT_CLEAR(_INT_INT_NESTING_VREG(index), _INT_INT_NESTING_POS(index));
}


#endif /*_INT_INTNESTING_DEFAULT_H*/

/******************************************************************************
 End of File
*/

