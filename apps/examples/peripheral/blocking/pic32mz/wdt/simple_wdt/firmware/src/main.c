/*******************************************************************************
  MPLAB Harmony Simple Watch Dog Timer Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony simple_wdt main function

  Description:
    The green LED on the starter-kit will repeatedly blink as
    long as the WDT is being serviced on time. When SW1 is pressed,
    it executes a simple delay routine. This delay causes the WDT
    to fail to be serviced in time, setting the WDT event flag and
    resetting the system. The red LED will then blink forever to
    indicate a timeout reset has occured.

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
#include "button.h"
#include "peripheral/ports/plib_ports.h"
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

#pragma config WDTPS = PS1 /* WDT timeout period = 1ms */


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
     unsigned int i, j;

    // Set the lower 8 bits of PORTA as output (for Explorer-16 LEDs),
    // clear the bits to ensure there is no mismatch when they are toggled
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_0,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_1,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_2,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x00FF);
    //ANSELH = 0;
    //TRISH = 0;
    //LATH = 0;

    // Enable interrupts for the push button, so the delay routine will be triggered
    // when SW1 is pressed.
    setupPushButton();

    /* Check for a previous WDT Event.
       The program won't enter this loop until the button has been pressed,
       causing a delay interrupt to occur. This is the WDT handling routine,
       and it needs to be placed at the start of user code. */
    //if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_WDT_TIMEOUT)
    if (RCONbits.WDTO)
    {
        // Disable the WDT to keep it from resetting the system again
        PLIB_WDT_Disable(WDT_ID_0);

        // Clear the WDT event flag so a subsequent event can set the event bit
        PLIB_WDT_TimerClear(WDT_ID_0);
	     //WDTCONbits.WDTCLRKEY = 0x5743;

        // User code to handle a WDT timeout event would be here

        // Blink red +LED ON/OFF forever to indicate that we have seen WDT timeout reset.
        while (1)
        {
            // Toggle the red LED
            PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0);
            //LATHINV = 0x1;

            // Some delay
            j = 1000 * 1000 * 10;
            while (j--);
        }
    }

    // WDT timeout period is set in the Device Configuration (WDTPS)
    PLIB_WDT_Enable(WDT_ID_0); // Enable the WDT

    // If a WDT event has not occured, blink the green LED to indicate that the
    // device is running smoothly and the WDT is being serviced on time.
    while (1)
    {
        // Blink green LED to indicate device is functioning normally
        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2);
        //LATHINV = 0x4;

        // Some delay
        i = 1000 * 1000 * 10;
        while (i--)
        {
            PLIB_WDT_TimerClear(WDT_ID_0); // Service the WDT
            //WDTCONbits.WDTCLRKEY = 0x5743;
        }
    }


    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/


