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
    each one to an Explorer 16 LED. If the flag is set, the LED
    is turned on and the reset flag is cleared.

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
#include "peripheral/reset/plib_reset.h"
#include "peripheral/ports/plib_ports.h"


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

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Set the lower 8 bits of PORTA as output (for Explorer-16 LEDs),
       clear the bits to ensure there is no mismatch when they are toggled */
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_POWERON)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_POWERON);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0);
        /* execute power on reset handler */
    }

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_BROWNOUT)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_BROWNOUT);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1);
        /* execute brown out reset handler */
    }

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_MCLR)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_MCLR);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_2);
        /* execute master clear reset handler */
    }

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_SOFTWARE)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_SOFTWARE);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_3);
        /* execute software reset handler */
    }

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_CONFIG_MISMATCH)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_CONFIG_MISMATCH);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_4);
        /* execute configuration mismatch reset handler */
    }

    if (PLIB_RESET_ReasonGet(RESET_ID_0) == RESET_REASON_WDT_TIMEOUT)
    {
        PLIB_RESET_ReasonClear(RESET_ID_0, RESET_REASON_WDT_TIMEOUT);
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_5);
        /* execute watchdog timeout reset handler */
    }

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}