/*******************************************************************************
  ETH Peripheral Library Template Implementation

  File Name:
    eth_MIIMReadWrite_Default.h

  Summary:
    ETH PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : MIIMReadWrite
    and its Variant : Default
    For following APIs :
        PLIB_ETH_MIIMReadStart
        PLIB_ETH_MIIMWriteStart
        PLIB_ETH_ExistsMIIMReadWrite

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

#ifndef _ETH_MIIMREADWRITE_DEFAULT_H
#define _ETH_MIIMREADWRITE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _ETH_MIIM_READ_COMMAND_VREG(index)

  MASKs:
    _ETH_MIIM_READ_COMMAND_MASK(index)

  POSs:
    _ETH_MIIM_READ_COMMAND_POS(index)

  LENs:
    _ETH_MIIM_READ_COMMAND_LEN(index)

*/


//******************************************************************************
/* Function :  ETH_MIIMReadStart_Default

  Summary:
    Implements Default variant of PLIB_ETH_MIIMReadStart

  Description:
    This template implements the Default variant of the PLIB_ETH_MIIMReadStart function.
*/

PLIB_TEMPLATE void ETH_MIIMReadStart_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_SET(_ETH_MIIM_READ_COMMAND_VREG(index),_ETH_MIIM_READ_COMMAND_POS(index));
    __asm__ __volatile__ ("nop; nop; nop; nop;");   // there's 4 clock cycles till busy is set for a read op

}


//******************************************************************************
/* Function :  ETH_MIIMWriteStart_Default

  Summary:
    Implements Default variant of PLIB_ETH_MIIMWriteStart

  Description:
    This template implements the Default variant of the PLIB_ETH_MIIMWriteStart function.
*/

PLIB_TEMPLATE void ETH_MIIMWriteStart_Default( ETH_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_ETH_MIIM_READ_COMMAND_VREG(index),_ETH_MIIM_READ_COMMAND_POS(index));
}


//******************************************************************************
/* Function :  ETH_ExistsMIIMReadWrite_Default

  Summary:
    Implements Default variant of PLIB_ETH_ExistsMIIMReadWrite

  Description:
    This template implements the Default variant of the PLIB_ETH_ExistsMIIMReadWrite function.
*/

PLIB_TEMPLATE bool ETH_ExistsMIIMReadWrite_Default( ETH_MODULE_ID index )
{
    return true;
}


#endif /*_ETH_MIIMREADWRITE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

