/*******************************************************************************
  DMA Peripheral Library Template Implementation

  File Name:
    dma_ChannelXSourceStartAddress_Default.h

  Summary:
    DMA PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChannelXSourceStartAddress
    and its Variant : Default
    For following APIs :
        PLIB_DMA_ExistsChannelXSourceStartAddress
        PLIB_DMA_ChannelXSourceStartAddressGet
        PLIB_DMA_ChannelXSourceStartAddressSet

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

#ifndef _DMA_CHANNELXSOURCESTARTADDRESS_DEFAULT_H
#define _DMA_CHANNELXSOURCESTARTADDRESS_DEFAULT_H

#include <sys/kmem.h>
#define ConvertToPhysicalAddress(a) ((uint32_t)KVA_TO_PA(a))
#define ConvertToVirtualAddress(a)  PA_TO_KVA1(a)

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DMA_CHANNEL_X_SOURCESTARTADDRESS_VREG(index)

  MASKs:
    _DMA_CHANNEL_X_SOURCESTARTADDRESS_MASK(index)

  POSs:
    _DMA_CHANNEL_X_SOURCESTARTADDRESS_POS(index)

  LENs:
    _DMA_CHANNEL_X_SOURCESTARTADDRESS_LEN(index)

*/


//******************************************************************************
/* Function :  DMA_ExistsChannelXSourceStartAddress_Default

  Summary:
    Implements Default variant of PLIB_DMA_ExistsChannelXSourceStartAddress

  Description:
    This template implements the Default variant of the PLIB_DMA_ExistsChannelXSourceStartAddress function.
*/

PLIB_TEMPLATE bool DMA_ExistsChannelXSourceStartAddress_Default( DMA_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  DMA_ChannelXSourceStartAddressGet_Default

  Summary:
    Implements Default variant of PLIB_DMA_ChannelXSourceStartAddressGet

  Description:
    This template implements the Default variant of the PLIB_DMA_ChannelXSourceStartAddressGet function.
*/

PLIB_TEMPLATE uint32_t DMA_ChannelXSourceStartAddressGet_Default( DMA_MODULE_ID index , DMA_CHANNEL dmaChannel )
{
    SFR_TYPE *pDmaChanXControlReg;

    // The Channel 0 control register is at the base of the Channel control register
    // array.  We can index to the others from it, once we have its address.
    pDmaChanXControlReg = (SFR_TYPE *)_DMA_CHANNEL_X_SOURCESTARTADDRESS_VREG(index);

	return (uint32_t) ConvertToVirtualAddress(_SFR_READ(&pDmaChanXControlReg[48*dmaChannel]));
}


//******************************************************************************
/* Function :  DMA_ChannelXSourceStartAddressSet_Default

  Summary:
    Implements Default variant of PLIB_DMA_ChannelXSourceStartAddressSet

  Description:
    This template implements the Default variant of the PLIB_DMA_ChannelXSourceStartAddressSet function.
*/

PLIB_TEMPLATE void DMA_ChannelXSourceStartAddressSet_Default( DMA_MODULE_ID index , DMA_CHANNEL dmaChannel , uint32_t sourceStartAddress )
{
    SFR_TYPE *pDmaChanXControlReg;

    // The Channel 0 control register is at the base of the Channel control register
    // array.  We can index to the others from it, once we have its address.
    pDmaChanXControlReg = (SFR_TYPE *)_DMA_CHANNEL_X_SOURCESTARTADDRESS_VREG(index);

    _SFR_WRITE(&pDmaChanXControlReg[48*dmaChannel],ConvertToPhysicalAddress(sourceStartAddress));
}


#endif /*_DMA_CHANNELXSOURCESTARTADDRESS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

