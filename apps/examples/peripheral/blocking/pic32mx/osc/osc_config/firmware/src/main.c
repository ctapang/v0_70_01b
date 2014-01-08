/*******************************************************************************
  MPLAB Harmony Oscillator Configuration Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony osc_config main function

  Description:
    This example demonstrates how to change the system clock
    source and PLL values during run-time.

  Tested with:
    -PIC32MX795F512L on the Explorer-16 Demo Board
    -XC32 compiler, MPLAB X IDE
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <xc.h>
#include <stdlib.h>
#include "peripheral/osc/plib_osc.h"


// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx2, OSCIOFNC = ON
#define SYS_FREQUENCY (80000000L)

/* This must be enabled to allow for clock switching! */
#pragma config FCKSM = CSECME


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Switch clock source from the primary oscillator to the FRC
       -PLL values should not be modified in run-time until the current clock
        source is switched to a non-PLL source */
    PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_FRC);
    while (!PLIB_OSC_ClockSwitchingIsComplete(OSC_ID_0));
    
    /* Change PLL values */
    PLIB_OSC_SysPLLMultiplierSelect(OSC_ID_0, 24);
    PLIB_OSC_SysPLLOutputDivisorSet(OSC_ID_0, OSC_SYSPLL_OUT_DIV_256);

    /* Switch clock source back to the primary oscillator, now using new PLL values
       -SYSCLK was orignally 80MHz, now it is 375KHz */
    PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_PRIMARY_WITH_PLL);
    while (!PLIB_OSC_ClockSwitchingIsComplete(OSC_ID_0));

    /* Switch clock source to the Internal Low-Power RC Oscillator (LPRC)
       Now SYSCLK is running at ~31.25KHz */
    PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_LPRC);
    while (!PLIB_OSC_ClockSwitchingIsComplete(OSC_ID_0));

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/