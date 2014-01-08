/*******************************************************************************
  Peripheral Library specific for 16 bit parts

  Company:
    Microchip Technology Inc.

  File Name:
    plib_common_16bit.h

  Summary:
    This file defines the 16 bit specific macros and definitions used by the peripheral
    library implementation headers.

  Description:
    This file defines the 16 bit specific macros and definitions used by the peripheral
    library implementation headers.  All the definitions in this file are
    private to the peripheral library implementation.

  Remarks:
    None
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _PLIB_COMMON_16BIT_H
#define _PLIB_COMMON_16BIT_H

#include <assert.h>
#include <stdint.h>

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* These macros are used to access bits in registers in the peripheral libraries
*/

// *****************************************************************************
/* SFR_TYPE datatype

  Summary:
    Defines the type for SFR on the 16 bit parts

  Description:
    This type is specific to the SFR type in the 16 bit parts.

*/

typedef volatile uint16_t SFR_TYPE;


// *****************************************************************************
/* SFR_DATA datatype

  Summary:
    Defines the type for SFR data on the 16 bit parts

  Description:
    This type is specific to the SFR data in the 16 bit parts.

*/

typedef uint16_t SFR_DATA;


#if 0 /* TODO:  Test and enable these functions. */
// *****************************************************************************
/* Function:
    unsigned uintptr_t _PLIB_VirtToPhys(const void* p)

  Summary:
    Translates a virtual pointer to a phyiscal address

  Description:
    This function translates a virtual pointer to a physical address suitable 
    for use with DMA and other hardware operations that require a physical 
    address.

  Precondition:
    None.

  Parameters:
    p       - Pointer to be converted
  
  Returns:
    The physical address corresponding to the virtual input pointer.

  Example:
    <code>
    int         myData;
    uintptr_t   physAddr;
    physAddr = _PLIB_VirtToPhys(&myData);  // Safe to write to DMA register
    </code>

  Remarks:
    On parts that do not require this translation, this function returns
    the given address unchanged (other than by the data type to which
    it is cast).
*/

extern __inline__ uintptr_t __attribute__((always_inline)) _PLIB_VirtToPhys(const void* p)
{
	return (uintptr_t)p;
}


// *****************************************************************************
/* Function:
   void* _PLIB_PhysToVirtK0( uintptr_t a )

  Summary:
    Translates a PIC32 K0 segment physical address to a virtual pointer

  Description:
    This function translates a PIC32 K0 segmente physical address to a virtual 
    pointer.

  Precondition:
    None.

  Parameters:
    a       - Pnysical address to be converted
  
  Returns:
    A virtual pointer corresponding to the given physical address.

  Example:
    <code>
    char *      pMyData;    // Virtual pointer to DMA data
    pMyData = _PLIB_PhysToVirtK0(PHY_ADDR_MY_DMA_BUFFER);
    </code>

  Remarks:
    On parts that do not require this translation, this function returns
    the given address unchanged (other than by the data type to which
    it is cast).
*/

extern __inline__ void* __attribute__((always_inline)) _PLIB_PhysToVirtK0( uintptr_t a )
{
	return a;
}


// *****************************************************************************
/* Function:
   void* _PLIB_PhysToVirtK1( uintptr_t a )

  Summary:
    Translates a K1 segment physical address to a virtual pointer

  Description:
    This function translates a K1 segmente physical address to a virtual 
    pointer.

  Precondition:
    None.

  Parameters:
    a       - Pnysical address to be converted
  
  Returns:
    A virtual pointer corresponding to the given physical address.

  Example:
    <code>
    char *      pMyData;    // Virtual pointer to DMA data
    pMyData = _PLIB_PhysToVirtK1(PHY_ADDR_MY_DMA_BUFFER);
    </code>

  Remarks:
    On parts that do not require this translation, this function returns
    the given address unchanged (other than by the data type to which
    it is cast).
*/

extern __inline__ void* __attribute__((always_inline)) _PLIB_PhysToVirtK1( uintptr_t a )
{
	return a);
}
#endif


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
*/

#include "peripheral/plib_common.h"

#endif /* End of File _PLIB_COMMON_16BIT_H */

