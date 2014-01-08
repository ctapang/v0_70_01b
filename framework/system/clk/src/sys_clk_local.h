/*******************************************************************************
  Clock System Service Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk_local.h

  Summary:
    Clock System Service local declarations and definitions.

  Description:
    This file contains the Clock System Service local declarations and
    definitions.
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

#ifndef _SYS_CLK_LOCAL_H
#define _SYS_CLK_LOCAL_H

// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "peripheral/osc/plib_osc.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Oscillator module ID used by the PLIB

  Summary:
    Configures the modules ID used by the peripheral library.

  Description:
    This macro configures the modules Id used by the peripheral library.

  Remarks:
    None.
*/

#define OSC_PLIB_ID                                                 OSC_ID_0


// *****************************************************************************
/* Oscillator System Service Hardware Instance Object

  Summary:
    Defines the object required for the maintainence of the hardware.

  Description:
    This defines the object required for the maintainence of the hardware.

  Remarks:
    None.
*/

typedef struct _SYS_OSC_OBJ_STRUCT
{
    /* This variable holds the system clock value. It is also
    used to calculate the other clocks which are derived from the system clock */
    unsigned long systemClock;

    /* This variable holds the peripheral clock value.  */
    unsigned long peripheralClock;

    unsigned long MZperipheralClock[9];
    /* This variable holds the Reference clock value. */
    unsigned long referenceClock;

    /* This variable holds the USB clock value.  */
    unsigned long usbClock;

} SYS_CLK_OBJECT;

extern SYS_CLK_OBJECT clkObject;


#endif //#ifndef _SYS_OSC_LOCAL_H

/*******************************************************************************
 End of File
*/

