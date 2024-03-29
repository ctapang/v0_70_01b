/*******************************************************************************
  ETH Peripheral Library Template Implementation

  File Name:
    eth_MIIMScanMode_Default.h

  Summary:
    ETH PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MIIMScanMode
    and its Variant : Default
    For following APIs :
        PLIB_ETH_MIIMScanModeEnable
        PLIB_ETH_MIIMScanModeDisable
        PLIB_ETH_MIIMScanModeIsEnabled
        PLIB_ETH_ExistsMIIMScanMode

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

#ifndef _ETH_MIIMSCANMODE_DEFAULT_H
#define _ETH_MIIMSCANMODE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _ETH_MIIM_SCAN_MODE_VREG(index)

  MASKs:
    _ETH_MIIM_SCAN_MODE_MASK(index)

  POSs:
    _ETH_MIIM_SCAN_MODE_POS(index)

  LENs:
    _ETH_MIIM_SCAN_MODE_LEN(index)

*/


//******************************************************************************
/* Function :  ETH_MIIMScanModeEnable_Default

  Summary:
    Implements Default variant of PLIB_ETH_MIIMScanModeEnable

  Description:
    This template implements the Default variant of the PLIB_ETH_MIIMScanModeEnable function.
*/

PLIB_TEMPLATE void ETH_MIIMScanModeEnable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_SET(_ETH_MIIM_SCAN_MODE_VREG(index),_ETH_MIIM_SCAN_MODE_POS(index));
}


//******************************************************************************
/* Function :  ETH_MIIMScanModeDisable_Default

  Summary:
    Implements Default variant of PLIB_ETH_MIIMScanModeDisable

  Description:
    This template implements the Default variant of the PLIB_ETH_MIIMScanModeDisable function.
*/

PLIB_TEMPLATE void ETH_MIIMScanModeDisable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_ETH_MIIM_SCAN_MODE_VREG(index),_ETH_MIIM_SCAN_MODE_POS(index));
}


//******************************************************************************
/* Function :  ETH_MIIMScanModeIsEnabled_Default

  Summary:
    Implements Default variant of PLIB_ETH_MIIMScanModeIsEnabled

  Description:
    This template implements the Default variant of the PLIB_ETH_MIIMScanModeIsEnabled function.
*/

PLIB_TEMPLATE bool ETH_MIIMScanModeIsEnabled_Default( ETH_MODULE_ID index )
{
    return (bool)_SFR_BIT_READ(_ETH_MIIM_SCAN_MODE_VREG(index),_ETH_MIIM_SCAN_MODE_POS(index));
}


//******************************************************************************
/* Function :  ETH_ExistsMIIMScanMode_Default

  Summary:
    Implements Default variant of PLIB_ETH_ExistsMIIMScanMode

  Description:
    This template implements the Default variant of the PLIB_ETH_ExistsMIIMScanMode function.
*/

PLIB_TEMPLATE bool ETH_ExistsMIIMScanMode_Default( ETH_MODULE_ID index )
{
    return true;
}


#endif /*_ETH_MIIMSCANMODE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

