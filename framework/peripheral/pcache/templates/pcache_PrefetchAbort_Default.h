/*******************************************************************************
  PCACHE Peripheral Library Template Implementation

  File Name:
    pcache_PrefetchAbort_Default.h

  Summary:
    PCACHE PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PrefetchAbort
    and its Variant : Default
    For following APIs :
        PLIB_PCACHE_PrefetchAbortRead
        PLIB_PCACHE_PrefetchAbortWrite
        PLIB_PCACHE_ExistsPrefetchAbort

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

#ifndef _PCACHE_PREFETCHABORT_DEFAULT_H
#define _PCACHE_PREFETCHABORT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PCACHE_PREFETCH_ABORT_VREG(index)

  MASKs: 
    _PCACHE_PREFETCH_ABORT_MASK(index)

  POSs: 
    _PCACHE_PREFETCH_ABORT_POS(index)

  LENs: 
    _PCACHE_PREFETCH_ABORT_LEN(index)

*/


//******************************************************************************
/* Function :  PCACHE_PrefetchAbortRead_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_PrefetchAbortRead 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_PrefetchAbortRead function.
*/

PLIB_TEMPLATE uint32_t PCACHE_PrefetchAbortRead_Default( PCACHE_MODULE_ID index )
{
    return _SFR_READ(_PCACHE_PREFETCH_ABORT_VREG(index));
}


//******************************************************************************
/* Function :  PCACHE_PrefetchAbortWrite_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_PrefetchAbortWrite 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_PrefetchAbortWrite function.
*/

PLIB_TEMPLATE void PCACHE_PrefetchAbortWrite_Default( PCACHE_MODULE_ID index , uint32_t data )
{
    _SFR_WRITE(_PCACHE_PREFETCH_ABORT_VREG(index), data);
}


//******************************************************************************
/* Function :  PCACHE_ExistsPrefetchAbort_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_ExistsPrefetchAbort

  Description:
    This template implements the Default variant of the PLIB_PCACHE_ExistsPrefetchAbort function.
*/

PLIB_TEMPLATE bool PCACHE_ExistsPrefetchAbort_Default( PCACHE_MODULE_ID index )
{
    return true;
}


#endif /*_PCACHE_PREFETCHABORT_DEFAULT_H*/

/******************************************************************************
 End of File
*/
