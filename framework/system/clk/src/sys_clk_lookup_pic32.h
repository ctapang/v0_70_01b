/*******************************************************************************
  Clock System Service Look-up Tables

  Company:
    Microchip Technology Inc.

  File Name:
    sys_clk_lookup_pic32.h

  Summary:
    Clock System service look-up tables.

  Description:
    This file contains the Clock System Service look-up tables.
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

#ifndef _SYS_CLK_LOOKUP_PIC32_H
#define _SYS_CLK_LOOKUP_PIC32_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


#include "system/clk/sys_clk.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Type Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* System PLL multiplier look-up table

  Summary:
    Look-up table for the system PLL multiplier.

  Description:
    This array holds the value of the actual multiplication factor corresponding
    to each possible value in the register.

  Remarks:
    None.
*/

unsigned char sysPllMultiplierLookup[8] = {15, 16, 17, 18, 19, 20, 21, 24};


// *****************************************************************************
/* System PLL output divisor look-up table

  Summary:
    Look-up table for system PLL output divisor.

  Description:
    This array holds the value of the actual division factor corresponding
    to each possible value in the register.

  Remarks:
    None.
*/

unsigned char sysPllDivisorLookup[8] = {1, 2, 4, 8, 16, 32, 64, 255 };


// *****************************************************************************
/* Reference clock source look-up table

  Summary:
    Look-up table to convert the value of a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the reference clock output.

  Description:
    This array holds the value corresponding to a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the reference clock output.

  Remarks:
    None.
*/

char referenceClockSource[SYS_CLK_TOTAL_SOURCES] =
			{3, -1, 2, -1, -1, 5, 4, -1, -1, -1, 0, 1, 6, 7, 8};


// *****************************************************************************
/* System clock source look-up table

  Summary:
    Look-up table to convert the value of a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the System clock.

  Description:
    This array holds the value corresponding to a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the system clock output.

  Remarks:
    None.
*/

char systemClockSource[SYS_CLK_TOTAL_SOURCES] =
			{0, 1, 2, 3, -1, 4, 5, 6, 7, -1, -1, -1, -1, -1, -1};


// *****************************************************************************
/* USB clock source look-up table

  Summary:
    Look-up table to convert the value of a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the USB clock.

  Description:
    This array holds the value corresponding to a clock source in the SYS_CLK_SOURCE
    enumeration to the actual value of the source (which could be written to the
    hardware register) for the USB clock output.

  Remarks:
    None.
*/

char usbClockSource[SYS_CLK_TOTAL_SOURCES] =
	{1, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};


// *****************************************************************************
/* Peripheral clock divisor look-up table

  Summary:
    Look-up table for peripheral clock divisor.

  Description:
    This array holds the value of the actual division factor corresponding to
    each possible value in the PBDIV register.

  Remarks:
    None.
*/

unsigned char peripheralDivisorLookup[4] = {1, 2, 4, 8};

// *****************************************************************************
/* FRC clock divisor look-up table

  Summary:
    Look-up table for FRC clock divisor.

  Description:
    This array holds the value of the actual division factor corresponding to
    each possible value in the FRCDIV register.

  Remarks:
    None.
*/

unsigned char FRCDivisorLookup[8] = {1, 2, 4, 8, 16, 32, 64, 255 };


// *****************************************************************************
/* Macro:
    SYS_CLK_SysSourceToRegValue( factor )

  Summary:
    Converts the value of the system clock source in the SYS_CLK_SOURCE 
    enumeration to the actual value to be written to the register.

  Description:
    This macro converts the value of the system clock source in the SYS_CLK_SOURCE 
    enumeration to the actual value to be written to the register.

  Remarks:
    None.

*/

#define SYS_CLK_SysSourceToRegValue( factor ) 		systemClockSource[factor]


// *****************************************************************************
/* Macro:
    SYS_CLK_UsbSourceToRegValue( factor )

  Summary:
    Converts the value of the USB clock source in the SYS_CLK_SOURCE
    enumeration to the actual value to be written to the register.

  Description:
    This macro converts the value of the USB clock source in the SYS_CLK_SOURCE
    enumeration to the actual value to be written to the register.

  Remarks:
    None.

*/

#define SYS_CLK_UsbSourceToRegValue( factor ) 		usbClockSource[factor]


// *****************************************************************************
/* Macro:
    SYS_CLK_ReferenceSourceToRegValue( factor )

  Summary:
    Converts the value of the reference clock source in the SYS_CLK_SOURCE
    enumeration to the actual value to be written to the register.

  Description:
    This macro converts the value of the reference clock source in the
    SYS_CLK_SOURCE enumeration to the actual value to be written to the register.

  Remarks:
    None.

*/

#define SYS_CLK_ReferenceSourceToRegValue( factor ) referenceClockSource[factor]


#endif //#ifndef _SYS_CLK_LOOKUP_PIC32_H

/*******************************************************************************
 End of File
*/

