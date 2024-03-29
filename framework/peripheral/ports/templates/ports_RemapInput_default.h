/*******************************************************************************
  PORTS Peripheral Library Template Implementation

  File Name:
    ports_RemapInput_default.h

  Summary:
    PORTS PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : RemapInput
    and its Variant : default
    For following APIs :
        PLIB_PORTS_RemapInput
        PLIB_PORTS_ExistsRemapInput

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _PORTS_REMAPINPUT_DEFAULT_H
#define _PORTS_REMAPINPUT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PORTS_REMAP_FUNC_INT1_VREG(index)

  MASKs: 
    _PORTS_REMAP_FUNC_INT1_MASK(index)

  POSs: 
    _PORTS_REMAP_FUNC_INT1_POS(index)

  LENs: 
    _PORTS_REMAP_FUNC_INT1_LEN(index)

*/


//******************************************************************************
/* Function :  PORTS_RemapInput_default

  Summary:
    Implements default variant of PLIB_PORTS_RemapInput 

  Description:
    This template implements the default variant of the PLIB_PORTS_RemapInput function.
*/

PLIB_TEMPLATE void PORTS_RemapInput_default( PORTS_MODULE_ID      index , PORTS_REMAP_INPUT_FUNCTION function , PORTS_REMAP_INPUT_PIN      remapPin )
{
    _SFR_FIELD_WRITE( _PORTS_REMAP_FUNC_INT1_VREG(index) + function,
                          _PORTS_REMAP_FUNC_INT1_MASK(index),
                          _PORTS_REMAP_FUNC_INT1_POS(index),
                            remapPin );
}


//******************************************************************************
/* Function :  PORTS_ExistsRemapInput_default

  Summary:
    Implements default variant of PLIB_PORTS_ExistsRemapInput

  Description:
    This template implements the default variant of the PLIB_PORTS_ExistsRemapInput function.
*/

PLIB_TEMPLATE bool PORTS_ExistsRemapInput_default( PORTS_MODULE_ID index )
{
    return true;
}


#endif /*_PORTS_REMAPINPUT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

