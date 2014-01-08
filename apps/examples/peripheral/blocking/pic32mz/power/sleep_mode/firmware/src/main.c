/*******************************************************************************
  MPLAB Harmony Power-Saving Sleep Mode Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony sleep_mode main function

  Description:
    This example demonstrates how to put the device into sleep mode and
    then awake the device using the watchdog timer.

  Tested with:
    -PIC32MZ2048ECH144 (PIC32MZ Starter Kit)
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
#include "peripheral/ports/plib_ports.h"
#include "peripheral/power/plib_power.h"
#include "peripheral/wdt/plib_wdt.h"

// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 200 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV) */
#pragma config FPLLIDIV = DIV_1, FPLLMULT = MUL_50, FPLLODIV = DIV_2
#pragma config FPLLRNG = RANGE_5_10_MHZ, FPLLICLK = PLL_FRC, FNOSC = SPLL
#pragma config FSOSCEN = OFF, IESO = ON, POSCMOD = OFF, FCKSM = CSECMD
#pragma config FDMTEN = OFF, DMTCNT = DMT31, FWDTEN = OFF, ICESEL = ICS_PGx2

#pragma config WDTPS = PS8192 /* watchdog timer postscale value */


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    int i;

    // Set PORTH pins to output (for the three starter-kit LEDs),
    // clear the pins to ensure LEDs are off
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_0,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_1,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_2,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    //ANSELH = 0;
    //TRISH = 0;
    //LATH = 0;

    // Enable the watchdog timer, turn on the red LED to indicate the device is going into sleep
    // mode, then service the watchdog timer
    PLIB_WDT_Enable(WDT_ID_0);
    PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0);
    //LATHSET = 0x1;
    PLIB_WDT_TimerClear(WDT_ID_0);
    //WDTCONbits.WDTCLRKEY = 0x5743;

    // Put device into power saving sleep mode - the device will resume normal
    // operation when the WDT fails to be serviced and triggers a WDT timeout reset
    PLIB_POWER_DeepSleepModeEnable(POWER_ID_0);
    //OSCCONbits.SLPEN = 1;
    asm volatile("WAIT");

    // The device is now out of sleep mode, turn off the WDT so that it does
    // not reset the system after another timeout
    PLIB_WDT_Disable(WDT_ID_0);

    // Turn off the red LED
    PLIB_PORTS_PinClear(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0);
    //LATHCLR = 0x1;

    while (1)
    {
        // Blink green LED to indicate device is functioning normally
        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2);
        //LATHINV = 0x4;

        // Some delay
        i = 1000 * 1000 * 10;
        while (i--);
    }

     /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/