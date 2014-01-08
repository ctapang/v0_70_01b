/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_AlternateIOEnableControl_Default.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : AlternateIOEnableControl
    and its Variant : Default
    For following APIs :
        PLIB_USART_ExistsAlternateIO
        PLIB_USART_AlternateIOEnable
        PLIB_USART_AlternateIODisable

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

#ifndef _USART_ALTERNATEIOENABLECONTROL_DEFAULT_H
#define _USART_ALTERNATEIOENABLECONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USART_ALT_IO_ENABLE_VREG(index)

  MASKs: 
    _USART_ALT_IO_ENABLE_MASK(index)

  POSs: 
    _USART_ALT_IO_ENABLE_POS(index)

  LENs: 
    _USART_ALT_IO_ENABLE_LEN(index)

*/


//******************************************************************************
/* Function :  USART_ExistsAlternateIO_Default

  Summary:
    Implements Default variant of PLIB_USART_ExistsAlternateIO

  Description:
    This template implements the Default variant of the PLIB_USART_ExistsAlternateIO function.
*/

PLIB_TEMPLATE bool USART_ExistsAlternateIO_Default( USART_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  USART_AlternateIOEnable_Default

  Summary:
    Implements Default variant of PLIB_USART_AlternateIOEnable 

  Description:
    This template implements the Default variant of the PLIB_USART_AlternateIOEnable function.
*/

PLIB_TEMPLATE void USART_AlternateIOEnable_Default( USART_MODULE_ID index )
{
   _SFR_BIT_SET(
	    _USART_ALT_IO_ENABLE_VREG(index),
		_USART_ALT_IO_ENABLE_POS(index)
		);
}


//******************************************************************************
/* Function :  USART_AlternateIODisable_Default

  Summary:
    Implements Default variant of PLIB_USART_AlternateIODisable 

  Description:
    This template implements the Default variant of the PLIB_USART_AlternateIODisable function.
*/

PLIB_TEMPLATE void USART_AlternateIODisable_Default( USART_MODULE_ID index )
{
   _SFR_BIT_CLEAR(
	    _USART_ALT_IO_ENABLE_VREG(index),
		_USART_ALT_IO_ENABLE_POS(index)
		);
}


#endif /*_USART_ALTERNATEIOENABLECONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

