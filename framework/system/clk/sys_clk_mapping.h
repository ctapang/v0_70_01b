/*******************************************************************************
  Clock System Service Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk_mapping.h

  Summary:
    Clock System Service mapping.

  Description:
    This file contains the interface definition for the Clock System Service. 
    It provides a way to interact with the System Clock to manage the timing 
    requests supported by the system.
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

#ifndef _SYS_CLK_MAPPING_H
#define _SYS_CLK_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"

// *****************************************************************************
// *****************************************************************************
// Section: SYS Clock Status Routines
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    unsigned long SYS_CLK_ClockFrequencyGet ( SYS_ CLK_OUTPUT clockOutput )

  Summary:
    Gets the selected clock frequency in Hz.

  Description:
    This function gets the selected clock frequency in Hz.

  Precondition:
    The selected clock output must be configured and enabled.

  Parameters:
    Selected clock frequency in Hz.

  Returns:
    Clock frequency in Hz.

  Example:
    <code>
    unsigned long sysClockOutputHz;

    sysClockOutputHz = SYS_CLK_ClockFrequencyGet(CLK_SYSTEM);
    </code>

  Remarks:
 */
#ifdef __XC16__

    #define SYS_CLK_ClockFrequencyGet(clockOutput ) SYS_CLK_PeripheralClockGet()

#endif

#endif //_SYS_CLK_MAPPING_H

/*******************************************************************************
 End of File
*/

