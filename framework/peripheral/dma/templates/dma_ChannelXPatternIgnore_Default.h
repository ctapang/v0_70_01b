/*******************************************************************************
  DMA Peripheral Library Template Implementation

  File Name:
    dma_ChannelXPatternIgnore_Default.h

  Summary:
    DMA PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChannelXPatternIgnore
    and its Variant : Default
    For following APIs :
        PLIB_DMA_ExistsChannelXPatternIgnore
        PLIB_DMA_ChannelXPatternIgnoreSet
        PLIB_DMA_ChannelXPatternIgnoreGet

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

#ifndef _DMA_CHANNELXPATTERNIGNORE_DEFAULT_H
#define _DMA_CHANNELXPATTERNIGNORE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DMA_CHANNEL_X_PATTERN_IGNORE_VREG(index)

  MASKs:
    _DMA_CHANNEL_X_PATTERN_IGNORE_MASK(index)

  POSs:
    _DMA_CHANNEL_X_PATTERN_IGNORE_POS(index)

  LENs:
    _DMA_CHANNEL_X_PATTERN_IGNORE_LEN(index)

*/


//******************************************************************************
/* Function :  DMA_ExistsChannelXPatternIgnore_Default

  Summary:
    Implements Default variant of PLIB_DMA_ExistsChannelXPatternIgnore

  Description:
    This template implements the Default variant of the PLIB_DMA_ExistsChannelXPatternIgnore function.
*/

PLIB_TEMPLATE bool DMA_ExistsChannelXPatternIgnore_Default( DMA_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  DMA_ChannelXPatternIgnoreSet_Default

  Summary:
    Implements Default variant of PLIB_DMA_ChannelXPatternIgnoreSet

  Description:
    This template implements the Default variant of the PLIB_DMA_ChannelXPatternIgnoreSet function.
*/

PLIB_TEMPLATE void DMA_ChannelXPatternIgnoreSet_Default( DMA_MODULE_ID index , DMA_CHANNEL channel , uint8_t pattern )
{
    SFR_TYPE *pDmaChanXControlReg;

    // The Channel 0 control register is at the base of the Channel control register
    // array.  We can index to the others from it, once we have its address.
    pDmaChanXControlReg = (SFR_TYPE *)_DMA_CHANNEL_X_PATTERN_IGNORE_VREG(index);

	_SFR_FIELD_WRITE(&pDmaChanXControlReg[48*channel],
					_DMA_CHANNEL_X_PATTERN_IGNORE_MASK(index),
					_DMA_CHANNEL_X_PATTERN_IGNORE_POS(index) ,
					pattern                      );
}


//******************************************************************************
/* Function :  DMA_ChannelXPatternIgnoreGet_Default

  Summary:
    Implements Default variant of PLIB_DMA_ChannelXPatternIgnoreGet

  Description:
    This template implements the Default variant of the PLIB_DMA_ChannelXPatternIgnoreGet function.
*/

PLIB_TEMPLATE uint8_t DMA_ChannelXPatternIgnoreGet_Default( DMA_MODULE_ID index , DMA_CHANNEL channel )
{
    SFR_TYPE *pDmaChanXControlReg;

    // The Channel 0 control register is at the base of the Channel control register
    // array.  We can index to the others from it, once we have its address.
    pDmaChanXControlReg = (SFR_TYPE *)_DMA_CHANNEL_X_PATTERN_IGNORE_VREG(index);

	return _SFR_FIELD_READ(&pDmaChanXControlReg[48*channel],
					_DMA_CHANNEL_X_PATTERN_IGNORE_MASK(index),
					_DMA_CHANNEL_X_PATTERN_IGNORE_POS(index));
}


#endif /*_DMA_CHANNELXPATTERNIGNORE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

