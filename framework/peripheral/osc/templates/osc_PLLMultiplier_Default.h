/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_PLLMultiplier_Default.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PLLMultiplier
    and its Variant : Default
    For following APIs :
        PLIB_OSC_ExistsSysPLLMultiplier
        PLIB_OSC_SysPLLMultiplierSelect
        PLIB_OSC_SysPLLMultiplierGet

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

#ifndef _OSC_PLLMULTIPLIER_DEFAULT_H
#define _OSC_PLLMULTIPLIER_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_OSC_SYSPLL_MULTIPLIER_VREG(index)
    _OSC_OSC_REGISTER_LOCK_VREG(index)

  MASKs: 
    _OSC_OSC_SYSPLL_MULTIPLIER_MASK(index)
    _OSC_OSC_REGISTER_LOCK_MASK(index)

  POSs: 
    _OSC_OSC_SYSPLL_MULTIPLIER_POS(index)
    _OSC_OSC_REGISTER_LOCK_POS(index)

  LENs: 
    _OSC_OSC_SYSPLL_MULTIPLIER_LEN(index)
    _OSC_OSC_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsSysPLLMultiplier_Default

  Summary:
    Implements Default variant of PLIB_OSC_ExistsSysPLLMultiplier

  Description:
    This template implements the Default variant of the PLIB_OSC_ExistsSysPLLMultiplier function.
*/

PLIB_TEMPLATE bool OSC_ExistsSysPLLMultiplier_Default( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_SysPLLMultiplierSelect_Default

  Summary:
    Implements Default variant of PLIB_OSC_SysPLLMultiplierSelect 

  Description:
    This template implements the Default variant of the PLIB_OSC_SysPLLMultiplierSelect function.
*/

PLIB_TEMPLATE void OSC_SysPLLMultiplierSelect_Default( OSC_MODULE_ID index , OSC_SYSPLL_MULTIPLIER pll_multiplier )
{
    _SFR_FIELD_WRITE(_OSC_OSC_SYSPLL_MULTIPLIER_VREG(index),
                         _OSC_OSC_SYSPLL_MULTIPLIER_MASK(index),
                         _OSC_OSC_SYSPLL_MULTIPLIER_POS(index) ,
                         pll_multiplier );
}


//******************************************************************************
/* Function :  OSC_SysPLLMultiplierGet_Default

  Summary:
    Implements Default variant of PLIB_OSC_SysPLLMultiplierGet 

  Description:
    This template implements the Default variant of the PLIB_OSC_SysPLLMultiplierGet function.
*/

PLIB_TEMPLATE OSC_SYSPLL_MULTIPLIER OSC_SysPLLMultiplierGet_Default( OSC_MODULE_ID index )
{
    return _SFR_FIELD_READ(_OSC_OSC_SYSPLL_MULTIPLIER_VREG(index),
                               _OSC_OSC_SYSPLL_MULTIPLIER_MASK(index),
                               _OSC_OSC_SYSPLL_MULTIPLIER_POS(index) );
}


#endif /*_OSC_PLLMULTIPLIER_DEFAULT_H*/

/******************************************************************************
 End of File
*/

