/*******************************************************************************
  PCACHE Peripheral Library Template Implementation

  File Name:
    pcache_CacheLineLock_Default.h

  Summary:
    PCACHE PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : CacheLineLock
    and its Variant : Default
    For following APIs :
        PLIB_PCACHE_CacheLineLock
        PLIB_PCACHE_CacheLineUnlock
        PLIB_PCACHE_CacheLineIsLocked
        PLIB_PCACHE_ExistsCacheLineLock

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

#ifndef _PCACHE_CACHELINELOCK_DEFAULT_H
#define _PCACHE_CACHELINELOCK_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PCACHE_CACHE_LINE_LOCK_VREG(index)

  MASKs: 
    _PCACHE_CACHE_LINE_LOCK_MASK(index)

  POSs: 
    _PCACHE_CACHE_LINE_LOCK_POS(index)

  LENs: 
    _PCACHE_CACHE_LINE_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  PCACHE_CacheLineLock_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheLineLock 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheLineLock function.
*/

PLIB_TEMPLATE void PCACHE_CacheLineLock_Default( PCACHE_MODULE_ID index )
{
    _SFR_BIT_SET(_PCACHE_CACHE_LINE_LOCK_VREG(index), _PCACHE_CACHE_LINE_LOCK_POS(index));
}


//******************************************************************************
/* Function :  PCACHE_CacheLineUnlock_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheLineUnlock 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheLineUnlock function.
*/

PLIB_TEMPLATE void PCACHE_CacheLineUnlock_Default( PCACHE_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_PCACHE_CACHE_LINE_LOCK_VREG(index), _PCACHE_CACHE_LINE_LOCK_POS(index));
}


//******************************************************************************
/* Function :  PCACHE_CacheLineIsLocked_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheLineIsLocked 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheLineIsLocked function.
*/

PLIB_TEMPLATE bool PCACHE_CacheLineIsLocked_Default( PCACHE_MODULE_ID index )
{
    return _SFR_BIT_READ(_PCACHE_CACHE_LINE_LOCK_VREG(index), _PCACHE_CACHE_LINE_LOCK_POS(index));
}


//******************************************************************************
/* Function :  PCACHE_ExistsCacheLineLock_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_ExistsCacheLineLock

  Description:
    This template implements the Default variant of the PLIB_PCACHE_ExistsCacheLineLock function.
*/

PLIB_TEMPLATE bool PCACHE_ExistsCacheLineLock_Default( PCACHE_MODULE_ID index )
{
    return true;
}


#endif /*_PCACHE_CACHELINELOCK_DEFAULT_H*/

/******************************************************************************
 End of File
*/

