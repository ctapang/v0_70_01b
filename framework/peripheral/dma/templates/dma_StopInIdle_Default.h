/*******************************************************************************
  DMA Peripheral Library Template Implementation

  File Name:
    dma_StopInIdle_Default.h

  Summary:
    DMA PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : StopInIdle
    and its Variant : Default
    For following APIs :
        PLIB_DMA_ExistsStopInIdle
        PLIB_DMA_StopInIdleEnable
        PLIB_DMA_StopInIdleDisable

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

#ifndef _DMA_STOPINIDLE_DEFAULT_H
#define _DMA_STOPINIDLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DMA_STOPINIDLE_VREG(index)

  MASKs:
    _DMA_STOPINIDLE_MASK(index)

  POSs:
    _DMA_STOPINIDLE_POS(index)

  LENs:
    _DMA_STOPINIDLE_LEN(index)

*/


//******************************************************************************
/* Function :  DMA_ExistsStopInIdle_Default

  Summary:
    Implements Default variant of PLIB_DMA_ExistsStopInIdle

  Description:
    This template implements the Default variant of the PLIB_DMA_ExistsStopInIdle function.
*/

PLIB_TEMPLATE bool DMA_ExistsStopInIdle_Default( DMA_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  DMA_StopInIdleEnable_Default

  Summary:
    Implements Default variant of PLIB_DMA_StopInIdleEnable

  Description:
    This template implements the Default variant of the PLIB_DMA_StopInIdleEnable function.
*/

PLIB_TEMPLATE void DMA_StopInIdleEnable_Default( DMA_MODULE_ID index )
{
	_SFR_BIT_SET( _DMA_STOPINIDLE_VREG( index ), _DMA_STOPINIDLE_POS( index ) );
}


//******************************************************************************
/* Function :  DMA_StopInIdleDisable_Default

  Summary:
    Implements Default variant of PLIB_DMA_StopInIdleDisable

  Description:
    This template implements the Default variant of the PLIB_DMA_StopInIdleDisable function.
*/

PLIB_TEMPLATE void DMA_StopInIdleDisable_Default( DMA_MODULE_ID index )
{
	_SFR_BIT_CLEAR( _DMA_STOPINIDLE_VREG( index ), _DMA_STOPINIDLE_POS( index ) );
}


#endif /*_DMA_STOPINIDLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

