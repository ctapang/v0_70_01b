/*******************************************************************************
 System Interrupt Source File

  File Name:
    system_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the 
    interrupt sub-system.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2013 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#include <xc.h>
#include <sys/attribs.h>
#include "app.h"

/*********************************************************************
 * Function: Timer4 ISR
 *
 * PreCondition: none
 *
 * Input: none
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: increments tick counter. Tick is approx. 1 ms.
 *
 * Note: none
 *F
 ********************************************************************/
void __ISR( _TIMER_4_VECTOR ) _T4Interrupt(void)
{

    tick++;

    // Clear flag
    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_4);

}

void __ISR( _TIMER_3_VECTOR ) _T3Interrupt(void)
{

 //  if(GFX_GOL_RenderStatusGet() == NULL)
        SYS_MSG_Tasks( hSysMsg );

    // Clear flag
    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_3);
}

/*******************************************************************************
 End of File
 */

