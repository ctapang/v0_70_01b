/*******************************************************************************
  MPLAB Harmony Comparator Voltage Reference Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony triangle_wave main function

  Description:
    This example will generate a triangular wave on the CVref output
    pin.

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
#include "peripheral/cmp/plib_cmp.h"


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
    unsigned char step = 0;; /* Used to hold the value of the desired CVref step */
    unsigned char ramp = 0; /* Used to track the direction of the waveform (rising or falling) */

    PLIB_CMP_CVREF_SourceVoltageSelect(CMP_ID_1, CMP_CVREF_VOLTAGE_SOURCE_INTERNAL);
    PLIB_CMP_CVREF_ReferenceVoltageSelect(CMP_ID_1, CMP_CVREF_RESISTOR_LADDER_VOLTAGE);
    PLIB_CMP_CVREF_WideRangeEnable(CMP_ID_1);
    PLIB_CMP_CVREF_ValueSelect(CMP_ID_1, step);
    PLIB_CMP_CVREF_OutputEnable(CMP_ID_1);
    PLIB_CMP_CVREF_Enable(CMP_ID_1);

    /* Stuck in this loop */
    while (1)
    {
        for (ramp = 0; ramp <= 31; ramp++)
        {
            if (ramp <= 15)
            {
                /* Ramp up */
                step = ramp;
            }

            else
            {
                /* Ramp down */
                step = 31 - ramp;
            }

            PLIB_CMP_CVREF_ValueSelect(CMP_ID_1, step);
        }
    }

    /* Disable CVREF (not executed) */
    PLIB_CMP_CVREF_Disable(CMP_ID_1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/

