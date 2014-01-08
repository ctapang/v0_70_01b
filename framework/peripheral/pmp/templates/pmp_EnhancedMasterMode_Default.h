/*******************************************************************************
  PMP Peripheral Library Template Implementation

  File Name:
    pmp_EnhancedMasterMode_Default.h

  Summary:
    PMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : EnhancedMasterMode
    and its Variant : Default
    For following APIs :
        PLIB_PMP_ExistsEnhancedMasterMode
        PLIB_PMP_EnhancedMasterModeSelect

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

#ifndef _PMP_ENHANCEDMASTERMODE_DEFAULT_H
#define _PMP_ENHANCEDMASTERMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PMP_ENHANCED_MASTER_VREG(index)

  MASKs: 
    _PMP_ENHANCED_MASTER_MASK(index)

  POSs: 
    _PMP_ENHANCED_MASTER_POS(index)

  LENs: 
    _PMP_ENHANCED_MASTER_LEN(index)

*/


//******************************************************************************
/* Function :  PMP_ExistsEnhancedMasterMode_Default

  Summary:
    Implements Default variant of PLIB_PMP_ExistsEnhancedMasterMode

  Description:
    This template implements the Default variant of the PLIB_PMP_ExistsEnhancedMasterMode function.
*/

PLIB_TEMPLATE bool PMP_ExistsEnhancedMasterMode_Default( PMP_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PMP_EnhancedMasterModeSelect_Default

  Summary:
    Implements Default variant of PLIB_PMP_EnhancedMasterModeSelect 

  Description:
    This template implements the Default variant of the PLIB_PMP_EnhancedMasterModeSelect function.
*/

PLIB_TEMPLATE void PMP_EnhancedMasterModeSelect_Default( PMP_MODULE_ID index , PMP_MASTER_MODE master )
{
   _SFR_FIELD_WRITE(	_PMP_ENHANCED_MASTER_VREG(index),
						_PMP_ENHANCED_MASTER_MASK(index),
						_PMP_ENHANCED_MASTER_POS(index),
						master);
}


#endif /*_PMP_ENHANCEDMASTERMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

