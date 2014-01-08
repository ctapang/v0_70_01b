/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_ClockSourceEdge_Default.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ClockSourceEdge
    and its Variant : Default
    For following APIs :
        PLIB_TMR_ClockSourceEdgeSelect
        PLIB_TMR_ClockSourceEdgeGet
        PLIB_TMR_ExistsClockSourceEdge

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

#ifndef _TMR_CLOCKSOURCEEDGE_DEFAULT_H
#define _TMR_CLOCKSOURCEEDGE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_CLOCK_SOURCE_EDGE_VREG(index)

  MASKs: 
    _TMR_CLOCK_SOURCE_EDGE_MASK(index)

  POSs: 
    _TMR_CLOCK_SOURCE_EDGE_POS(index)

  LENs: 
    _TMR_CLOCK_SOURCE_EDGE_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_ClockSourceEdgeSelect_Default

  Summary:
    Implements Default variant of PLIB_TMR_ClockSourceEdgeSelect 

  Description:
    This template implements the Default variant of the PLIB_TMR_ClockSourceEdgeSelect function.
*/

PLIB_TEMPLATE void TMR_ClockSourceEdgeSelect_Default( TMR_MODULE_ID index , TMR_CLOCK_SOURCE_EDGE source )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_ClockSourceEdgeGet_Default

  Summary:
    Implements Default variant of PLIB_TMR_ClockSourceEdgeGet 

  Description:
    This template implements the Default variant of the PLIB_TMR_ClockSourceEdgeGet function.
*/

PLIB_TEMPLATE TMR_CLOCK_SOURCE_EDGE TMR_ClockSourceEdgeGet_Default( TMR_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  TMR_ExistsClockSourceEdge_Default

  Summary:
    Implements Default variant of PLIB_TMR_ExistsClockSourceEdge

  Description:
    This template implements the Default variant of the PLIB_TMR_ExistsClockSourceEdge function.
*/

PLIB_TEMPLATE bool TMR_ExistsClockSourceEdge_Default( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_CLOCKSOURCEEDGE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

