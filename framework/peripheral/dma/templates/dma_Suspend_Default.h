/*******************************************************************************
  DMA Peripheral Library Template Implementation

  File Name:
    dma_Suspend_Default.h

  Summary:
    DMA PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Suspend
    and its Variant : Default
    For following APIs :
        PLIB_DMA_ExistsSuspend
        PLIB_DMA_SuspendEnable
        PLIB_DMA_SuspendDisable
        PLIB_DMA_SuspendIsEnabled

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

#ifndef _DMA_SUSPEND_DEFAULT_H
#define _DMA_SUSPEND_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DMA_SUSPEND_VREG(index)

  MASKs:
    _DMA_SUSPEND_MASK(index)

  POSs:
    _DMA_SUSPEND_POS(index)

  LENs:
    _DMA_SUSPEND_LEN(index)

*/


//******************************************************************************
/* Function :  DMA_ExistsSuspend_Default

  Summary:
    Implements Default variant of PLIB_DMA_ExistsSuspend

  Description:
    This template implements the Default variant of the PLIB_DMA_ExistsSuspend function.
*/

PLIB_TEMPLATE bool DMA_ExistsSuspend_Default( DMA_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  DMA_SuspendEnable_Default

  Summary:
    Implements Default variant of PLIB_DMA_SuspendEnable

  Description:
    This template implements the Default variant of the PLIB_DMA_SuspendEnable function.
*/

PLIB_TEMPLATE void DMA_SuspendEnable_Default( DMA_MODULE_ID index )
{
	_SFR_BIT_SET( _DMA_SUSPEND_VREG( index ), _DMA_SUSPEND_POS( index ) );
}


//******************************************************************************
/* Function :  DMA_SuspendDisable_Default

  Summary:
    Implements Default variant of PLIB_DMA_SuspendDisable

  Description:
    This template implements the Default variant of the PLIB_DMA_SuspendDisable function.
*/

PLIB_TEMPLATE void DMA_SuspendDisable_Default( DMA_MODULE_ID index )
{
	_SFR_BIT_CLEAR( _DMA_SUSPEND_VREG( index ), _DMA_SUSPEND_POS( index ) );
}


//******************************************************************************
/* Function :  DMA_SuspendIsEnabled_Default

  Summary:
    Implements Default variant of PLIB_DMA_SuspendIsEnabled

  Description:
    This template implements the Default variant of the PLIB_DMA_SuspendIsEnabled function.
*/

PLIB_TEMPLATE bool DMA_SuspendIsEnabled_Default( DMA_MODULE_ID index )
{
    return _SFR_BIT_READ( _DMA_SUSPEND_VREG( index ), _DMA_SUSPEND_POS( index ) );
}


#endif /*_DMA_SUSPEND_DEFAULT_H*/

/******************************************************************************
 End of File
*/

