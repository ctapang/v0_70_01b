/*******************************************************************************
  Timer System Service Feature Variant Implementations

  Company:
    Microchip Technology Inc.

  File Name:
    sys_tmr_variant_mapping.h

  Summary:
    Timer System Service feature variant implementations.

  Description:
    This file implements the functions which differ based on different parts
    and various implementations of the same feature.
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


#ifndef _SYS_TMR_VARIANT_MAPPING_H
#define _SYS_TMR_VARIANT_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Symbolic Constants
// *****************************************************************************
// *****************************************************************************



// *****************************************************************************
// *****************************************************************************
// Section: Feature Variant Mapping
// *****************************************************************************
// *****************************************************************************
/* Some variants are determined by hardware feature existence, some features
   are determined user configuration of the driver, and some variants are
   combination of the two.
*/


#if defined (DRV_TMR_COUNT_WIDTH)

    #if( DRV_TMR_COUNT_WIDTH == 8 )

        #define _SYS_TMR_PeriodSet(handle, value)                       \
                (                                                       \
                    DRV_TMR_Period8BitSet( handle, (uint8_t)value )     \
                )

    #elif( DRV_TMR_COUNT_WIDTH == 16 )

        #define _SYS_TMR_PeriodSet(handle, value)                        \
                (                                                       \
                    DRV_TMR_Period16BitSet( handle, (uint16_t)value )   \
                )

    #elif( DRV_TMR_COUNT_WIDTH == 32 )

        #define _SYS_TMR_PeriodSet(handle, value)                       \
                (                                                       \
                    DRV_TMR_Period32BitSet( handle, (uint32_t)value )   \
                )

    #else

        #error "No timer bit-width selected. "

    #endif

#else

    #error "No timer bit-width selected. "

#endif


#if defined (DRV_TMR_COUNT_WIDTH)

    #if( DRV_TMR_COUNT_WIDTH == 8 )

        #define _SYS_TMR_CounterGet(handle)      DRV_TMR_Counter8BitGet( handle )

    #elif( DRV_TMR_COUNT_WIDTH == 16 )

        #define _SYS_TMR_CounterGet(handle)      DRV_TMR_Counter16BitGet( handle )

    #elif( DRV_TMR_COUNT_WIDTH == 32 )

        #define _SYS_TMR_CounterGet(handle)      DRV_TMR_Counter32BitGet( handle )
        
    #else

        #error "No timer bit-width selected. "

    #endif

#else

    #error "No timer bit-width selected. "

#endif


#endif //_SYS_TMR_VARIANT_MAPPING_H

/*******************************************************************************
 End of File
*/

