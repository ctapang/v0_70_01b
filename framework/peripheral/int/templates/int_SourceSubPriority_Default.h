/*******************************************************************************
  INT Peripheral Library Template Implementation

  File Name:
    int_SourceSubPriority_Default.h

  Summary:
    INT PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SourceSubPriority
    and its Variant : Default
    For following APIs :
        PLIB_INT_ExistsSourceSubPriority
        PLIB_INT_SourceSubPrioritySet
        PLIB_INT_SourceSubPriorityGet

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

#ifndef _INT_SOURCESUBPRIORITY_DEFAULT_H
#define _INT_SOURCESUBPRIORITY_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _INT_INT_SRC_SUB_PRIORITY_VREG(index)

  MASKs: 
    _INT_INT_SRC_SUB_PRIORITY_MASK(index)

  POSs: 
    _INT_INT_SRC_SUB_PRIORITY_POS(index)

  LENs: 
    _INT_INT_SRC_SUB_PRIORITY_LEN(index)

*/


//******************************************************************************
/* Function :  INT_ExistsSourceSubPriority_Default

  Summary:
    Implements Default variant of PLIB_INT_ExistsSourceSubPriority

  Description:
    This template implements the Default variant of the PLIB_INT_ExistsSourceSubPriority function.
*/

PLIB_TEMPLATE bool INT_ExistsSourceSubPriority_Default( INT_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  INT_SourceSubPrioritySet_Default

  Summary:
    Implements Default variant of PLIB_INT_SourceSubPrioritySet 

  Description:
    This template implements the Default variant of the PLIB_INT_SourceSubPrioritySet function.
*/

PLIB_TEMPLATE void INT_SourceSubPrioritySet_Default( INT_MODULE_ID index , INT_SOURCE source , INT_SUBPRIORITY_LEVEL subpriority )
{
    _SFR_FIELD_WRITE(_INT_SUB_PRIO_VREG(source, index),_INT_SUB_PRIO_MASK(source, index),_INT_SUB_PRIO_POS(source, index),subpriority);
}


//******************************************************************************
/* Function :  INT_SourceSubPriorityGet_Default

  Summary:
    Implements Default variant of PLIB_INT_SourceSubPriorityGet 

  Description:
    This template implements the Default variant of the PLIB_INT_SourceSubPriorityGet function.
*/

PLIB_TEMPLATE INT_SUBPRIORITY_LEVEL INT_SourceSubPriorityGet_Default( INT_MODULE_ID index , INT_SOURCE source )
{
    return ( _SFR_FIELD_READ(_INT_SUB_PRIO_VREG(source, index),_INT_SUB_PRIO_MASK(source, index),_INT_SUB_PRIO_POS(source, index)));
}


#endif /*_INT_SOURCESUBPRIORITY_DEFAULT_H*/

/******************************************************************************
 End of File
*/

