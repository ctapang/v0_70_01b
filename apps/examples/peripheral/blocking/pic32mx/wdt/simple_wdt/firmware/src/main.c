/*******************************************************************************
  MPLAB Harmony Simple Watch Dog Timer Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony simple_wdt main function

  Description:
    The right-most LED on the Explorer-16 will repeatedly blink as
    long as the WDT is being serviced on time. When the right
    most button on the Explorer is pressed, it executes a simple
    delay routine. This delay causes the WDT to fail to be serviced
    in time, setting the WDT event flag and resetting the system.
    All eight LEDs will then blink forever to indicate a timeout
    reset has occurred.

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
#include "button.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/wdt/plib_wdt.h"


// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_1, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx2, FCKSM = CSECME, OSCIOFNC = ON
#define SYS_FREQUENCY (80000000L)

#pragma config WDTPS = PS1 /* WDT timeout period = 1ms */


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    unsigned int i;

    /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Set the lower 8 bits of PORTA as output (for Explorer-16 LEDs),
       clear the bits to ensure there is no mismatch when they are toggled */
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Enable interrupts for the push button, so the delay routine will be triggered
       on button press. */
    setupPushButton();

    /* Check for a previous WDT Event.
       The program won't enter this loop until the button has been pressed,
       causing a delay interrupt to occur. This is the WDT handling routine,
       and it needs to be placed at the start of user code. */
    // if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_WDT_TIMEOUT)
    if (RCONbits.WDTO)
    {
        /* Disable the WDT to keep it from resetting the system again */
        PLIB_WDT_Disable(WDT_ID_0);

        /* Clear the WDT event flag so a subsequent event can set the event bit */
        PLIB_WDT_TimerClear(WDT_ID_0);

        /* User code to handle a WDT timeout event would be here */

        /* Blink all LEDs ON/OFF forever to indicate that we have seen WDT timeout reset. */
        while (1)
        {
            /* Toggle the LEDs */
            PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

            /* Some delay */
            i = 1024 * 200;
            while (i--);
        }
    }

    /* WDT timeout period is set in the Device Configuration (WDTPS)
       Enable the WDT */
    PLIB_WDT_Enable(WDT_ID_0);

    /* Stuck in this loop servicing the WDT, until a timeout occurs
       and resets the system */
    while (1)
    {
        /* Toggle the LED */
        PLIB_PORTS_PinToggle(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0);

        /* Some delay */
        i = 1024 * 100;
        while (i--)
        {
            /* Service the WDT */
            PLIB_WDT_TimerClear(WDT_ID_0); 
        }
    }

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/


