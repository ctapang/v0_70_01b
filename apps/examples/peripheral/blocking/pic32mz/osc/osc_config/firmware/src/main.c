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
    -PIC32MZ2048ECH144 (Starter Kit)
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

/* SYSCLK = 200 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV) */
#pragma config FPLLIDIV = DIV_1, FPLLMULT = MUL_50, FPLLODIV = DIV_2
#pragma config FPLLRNG = RANGE_5_10_MHZ, FPLLICLK = PLL_FRC, FNOSC = SPLL
#pragma config FSOSCEN = OFF, IESO = ON, POSCMOD = OFF
#pragma config FDMTEN = OFF, DMTCNT = DMT31, FWDTEN = OFF, ICESEL = ICS_PGx2

/* This must be enabled to allow for clock switching! */
#pragma config FCKSM = CSECME


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Switch clock source from the FRC with PLL to the FRC without PLL
       - PLL values should not be modified in run-time until the current clock
         source is switched to a non-PLL source */
    PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_FRC_BY_FRCDIV);
    while (!PLIB_OSC_ClockSwitchingIsComplete(OSC_ID_0));

    /* Change PLL values (output divisor changed from 2 to 32) */
    PLIB_OSC_SysPLLOutputDivisorSet(OSC_ID_0, OSC_SYSPLL_OUT_DIV_32);

    /* Switch clock source back to FRC with PLL, now using new PLL values
       - SYSCLK was orignally 200MHz, now it is 12.5MHz */
    PLIB_OSC_SysClockSelect(OSC_ID_0, OSC_SYSTEM_PLL );
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