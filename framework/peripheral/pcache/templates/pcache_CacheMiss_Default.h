/*******************************************************************************
  PCACHE Peripheral Library Template Implementation

  File Name:
    pcache_CacheMiss_Default.h

  Summary:
    PCACHE PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : CacheMiss
    and its Variant : Default
    For following APIs :
        PLIB_PCACHE_CacheMissRead
        PLIB_PCACHE_CacheMissWrite
        PLIB_PCACHE_ExistsCacheMiss

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

#ifndef _PCACHE_CACHEMISS_DEFAULT_H
#define _PCACHE_CACHEMISS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PCACHE_CACHE_MISS_VREG(index)

  MASKs: 
    _PCACHE_CACHE_MISS_MASK(index)

  POSs: 
    _PCACHE_CACHE_MISS_POS(index)

  LENs: 
    _PCACHE_CACHE_MISS_LEN(index)

*/


//******************************************************************************
/* Function :  PCACHE_CacheMissRead_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheMissRead 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheMissRead function.
*/

PLIB_TEMPLATE uint32_t PCACHE_CacheMissRead_Default( PCACHE_MODULE_ID index )
{
    return _SFR_READ(_PCACHE_CACHE_MISS_VREG(index));
}


//******************************************************************************
/* Function :  PCACHE_CacheMissWrite_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheMissWrite 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheMissWrite function.
*/

PLIB_TEMPLATE void PCACHE_CacheMissWrite_Default( PCACHE_MODULE_ID index , uint32_t data )
{
    _SFR_WRITE(_PCACHE_CACHE_MISS_VREG(index), data);
}


//******************************************************************************
/* Function :  PCACHE_ExistsCacheMiss_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_ExistsCacheMiss

  Description:
    This template implements the Default variant of the PLIB_PCACHE_ExistsCacheMiss function.
*/

PLIB_TEMPLATE bool PCACHE_ExistsCacheMiss_Default( PCACHE_MODULE_ID index )
{
    return true;
}


#endif /*_PCACHE_CACHEMISS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

