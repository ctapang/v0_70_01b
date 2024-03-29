/*******************************************************************************
  ETH Peripheral Library Template Implementation

  File Name:
    eth_Enable_Default.h

  Summary:
    ETH PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Enable
    and its Variant : Default
    For following APIs :
        PLIB_ETH_Enable
        PLIB_ETH_Disable
        PLIB_ETH_IsEnabled
        PLIB_ETH_ExistsEnable

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

#ifndef _ETH_ENABLE_DEFAULT_H
#define _ETH_ENABLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _ETH_ETHERNET_ON_VREG(index)

  MASKs:
    _ETH_ETHERNET_ON_MASK(index)

  POSs:
    _ETH_ETHERNET_ON_POS(index)

  LENs:
    _ETH_ETHERNET_ON_LEN(index)

*/


//******************************************************************************
/* Function :  ETH_Enable_Default

  Summary:
    Implements Default variant of PLIB_ETH_Enable

  Description:
    This template implements the Default variant of the PLIB_ETH_Enable function.
*/

PLIB_TEMPLATE void ETH_Enable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_SET(_ETH_ETHERNET_ON_VREG(index),_ETH_ETHERNET_ON_POS(index));
}


//******************************************************************************
/* Function :  ETH_Disable_Default

  Summary:
    Implements Default variant of PLIB_ETH_Disable

  Description:
    This template implements the Default variant of the PLIB_ETH_Disable function.
*/

PLIB_TEMPLATE void ETH_Disable_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_ETH_ETHERNET_ON_VREG(index),_ETH_ETHERNET_ON_POS(index));
}


//******************************************************************************
/* Function :  ETH_IsEnabled_Default

  Summary:
    Implements Default variant of PLIB_ETH_IsEnabled

  Description:
    This template implements the Default variant of the PLIB_ETH_IsEnabled function.
*/

PLIB_TEMPLATE bool ETH_IsEnabled_Default( ETH_MODULE_ID index )
{
    return (bool)_SFR_BIT_READ(_ETH_ETHERNET_ON_VREG(index),_ETH_ETHERNET_ON_POS(index));
}


//******************************************************************************
/* Function :  ETH_ExistsEnable_Default

  Summary:
    Implements Default variant of PLIB_ETH_ExistsEnable

  Description:
    This template implements the Default variant of the PLIB_ETH_ExistsEnable function.
*/

PLIB_TEMPLATE bool ETH_ExistsEnable_Default( ETH_MODULE_ID index )
{
    return true;
}


#endif /*_ETH_ENABLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

