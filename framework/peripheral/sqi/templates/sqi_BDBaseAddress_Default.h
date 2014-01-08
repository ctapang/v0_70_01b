/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_BDBaseAddress_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : BDBaseAddress
    and its Variant : Default
    For following APIs :
        PLIB_SQI_DMABDBaseAddressSet
        PLIB_SQI_DMABDBaseAddressGet
        PLIB_SQI_ExistsBDBaseAddress

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

#ifndef _SQI_BDBASEADDRESS_DEFAULT_H
#define _SQI_BDBASEADDRESS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_BD_BASE_ADDR_VREG(index)

  MASKs:
    _SQI_BD_BASE_ADDR_MASK(index)

  POSs:
    _SQI_BD_BASE_ADDR_POS(index)

  LENs:
    _SQI_BD_BASE_ADDR_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_DMABDBaseAddressSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_DMABDBaseAddressSet

  Description:
    This template implements the Default variant of the PLIB_SQI_DMABDBaseAddressSet function.
*/

PLIB_TEMPLATE void SQI_DMABDBaseAddressSet_Default( SQI_MODULE_ID index , void *baseBDAddress )
{
	_SFR_WRITE (_SQI_BD_BASE_ADDR_VREG(index), (uint32_t) baseBDAddress);
}


//******************************************************************************
/* Function :  SQI_DMABDBaseAddressGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_DMABDBaseAddressGet

  Description:
    This template implements the Default variant of the PLIB_SQI_DMABDBaseAddressGet function.
*/

PLIB_TEMPLATE void* SQI_DMABDBaseAddressGet_Default( SQI_MODULE_ID index )
{
	return (void*) _SFR_READ(_SQI_CURRENT_BD_ADDRESS_VREG(index));
}


//******************************************************************************
/* Function :  SQI_ExistsBDBaseAddress_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsBDBaseAddress

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsBDBaseAddress function.
*/

PLIB_TEMPLATE bool SQI_ExistsBDBaseAddress_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_BDBASEADDRESS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

