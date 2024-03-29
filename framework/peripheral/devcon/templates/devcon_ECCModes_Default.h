/*******************************************************************************
  DEVCON Peripheral Library Template Implementation

  File Name:
    devcon_ECCModes_Default.h

  Summary:
    DEVCON PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ECCModes
    and its Variant : Default
    For following APIs :
        PLIB_DEVCON_FlashErrCorrectionModeSet
        PLIB_DEVCON_ExistsECCModes

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

#ifndef _DEVCON_ECCMODES_DEFAULT_H
#define _DEVCON_ECCMODES_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DEVCON_ECC_CONFIGURATION_VREG(index)

  MASKs:
    _DEVCON_ECC_CONFIGURATION_MASK(index)

  POSs:
    _DEVCON_ECC_CONFIGURATION_POS(index)

  LENs:
    _DEVCON_ECC_CONFIGURATION_LEN(index)

*/


//******************************************************************************
/* Function :  DEVCON_FlashErrCorrectionModeSet_Default

  Summary:
    Implements Default variant of PLIB_DEVCON_FlashErrCorrectionModeSet

  Description:
    This template implements the Default variant of the PLIB_DEVCON_FlashErrCorrectionModeSet function.
*/

PLIB_TEMPLATE void DEVCON_FlashErrCorrectionModeSet_Default( DEVCON_MODULE_ID index , DEVCON_ECC_CONFIG flashECC )
{
    _SFR_FIELD_WRITE(_DEVCON_ECC_CONFIGURATION_VREG(index),
                     _DEVCON_ECC_CONFIGURATION_MASK(index),
                     _DEVCON_ECC_CONFIGURATION_POS(index) ,
                     flashECC                             );
}


//******************************************************************************
/* Function :  DEVCON_ExistsECCModes_Default

  Summary:
    Implements Default variant of PLIB_DEVCON_ExistsECCModes

  Description:
    This template implements the Default variant of the PLIB_DEVCON_ExistsECCModes function.
*/

PLIB_TEMPLATE bool DEVCON_ExistsECCModes_Default( DEVCON_MODULE_ID index )
{
    return true;
}


#endif /*_DEVCON_ECCMODES_DEFAULT_H*/

/******************************************************************************
 End of File
*/

