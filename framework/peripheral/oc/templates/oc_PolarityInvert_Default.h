/*******************************************************************************
  OC Peripheral Library Template Implementation

  File Name:
    oc_PolarityInvert_Default.h

  Summary:
    OC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PolarityInvert
    and its Variant : Default
    For following APIs :
        PLIB_OC_PolarityInvertedEnable
        PLIB_OC_PolarityInvertedDisable
        PLIB_OC_ExistsPolarityInvert

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

#ifndef _OC_POLARITYINVERT_DEFAULT_H
#define _OC_POLARITYINVERT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OC_POLARITY_INVERT_VREG(index)

  MASKs: 
    _OC_POLARITY_INVERT_MASK(index)

  POSs: 
    _OC_POLARITY_INVERT_POS(index)

  LENs: 
    _OC_POLARITY_INVERT_LEN(index)

*/


//******************************************************************************
/* Function :  OC_PolarityInvertedEnable_Default

  Summary:
    Implements Default variant of PLIB_OC_PolarityInvertedEnable 

  Description:
    This template implements the Default variant of the PLIB_OC_PolarityInvertedEnable function.
*/

PLIB_TEMPLATE void OC_PolarityInvertedEnable_Default( OC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  OC_PolarityInvertedDisable_Default

  Summary:
    Implements Default variant of PLIB_OC_PolarityInvertedDisable 

  Description:
    This template implements the Default variant of the PLIB_OC_PolarityInvertedDisable function.
*/

PLIB_TEMPLATE void OC_PolarityInvertedDisable_Default( OC_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  OC_ExistsPolarityInvert_Default

  Summary:
    Implements Default variant of PLIB_OC_ExistsPolarityInvert

  Description:
    This template implements the Default variant of the PLIB_OC_ExistsPolarityInvert function.
*/

PLIB_TEMPLATE bool OC_ExistsPolarityInvert_Default( OC_MODULE_ID index )
{
    return true;
}


#endif /*_OC_POLARITYINVERT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

