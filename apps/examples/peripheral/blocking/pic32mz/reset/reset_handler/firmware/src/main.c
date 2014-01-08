/*******************************************************************************
  MPLAB Harmony Reset Handler Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony reset_handler main function

  Description:
    This example does checks on various reset flags, assigning
    each one to an PIC32MZ Starter Kit LED. If the flag is set, the LED
    is turned on and the reset flag is cleared.

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
#include "peripheral/reset/plib_reset.h"


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


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
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

    //if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_POWERON)
    if (RCONbits.POR)
    {
        // Turn on green LED
        //PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_POWERON);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2);
        RCONbits.POR = 0;
        //LATHSET = 0x4;
        // execute power on reset handler
        // ...
    }

    //if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_BROWNOUT)
    if (RCONbits.BOR)
    {
        // Turn on orange LED
        //PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_BROWNOUT);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1);
        RCONbits.BOR = 0;
        //LATHSET = 0x2;
        // execute brown out reset handler
        // ...
    }

    //if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_MCLR,)
    if (RCONbits.EXTR)
    {
        // Turn on red LED
        //PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_MCLR);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0);
        RCONbits.EXTR = 0;
        //LATHSET = 0x1;
        // execute master clear reset handler
        // ...
    }

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/