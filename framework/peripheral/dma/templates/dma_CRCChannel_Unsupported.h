/*******************************************************************************
  DMA Peripheral Library Template Implementation

  File Name:
    dma_CRCChannel_Unsupported.h

  Summary:
    DMA PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : CRCChannel
    and its Variant : Unsupported
    For following APIs :
        PLIB_DMA_ExistsCRCChannel
        PLIB_DMA_CRCChannelSelect
        PLIB_DMA_CRCChannelGet

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

#ifndef _DMA_CRCCHANNEL_UNSUPPORTED_H
#define _DMA_CRCCHANNEL_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  DMA_ExistsCRCChannel_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_DMA_ExistsCRCChannel

  Description:
    This template implements the Unsupported variant of the PLIB_DMA_ExistsCRCChannel function.
*/

PLIB_TEMPLATE bool DMA_ExistsCRCChannel_Unsupported( DMA_MODULE_ID index )
{
    return false;
}


//******************************************************************************
/* Function :  DMA_CRCChannelSelect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_DMA_CRCChannelSelect 

  Description:
    This template implements the Unsupported variant of the PLIB_DMA_CRCChannelSelect function.
*/

PLIB_TEMPLATE void DMA_CRCChannelSelect_Unsupported( DMA_MODULE_ID index , DMA_CHANNEL channel )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_DMA_CRCChannelSelect");
}


//******************************************************************************
/* Function :  DMA_CRCChannelGet_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_DMA_CRCChannelGet 

  Description:
    This template implements the Unsupported variant of the PLIB_DMA_CRCChannelGet function.
*/

PLIB_TEMPLATE DMA_CHANNEL DMA_CRCChannelGet_Unsupported( DMA_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_DMA_CRCChannelGet");
}


#endif /*_DMA_CRCCHANNEL_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

