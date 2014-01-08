/*******************************************************************************
  MPLAB Harmony RTCC Alarm Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony rtcc_alarm main function

  Description:
    This example sets up the RTCC module to function as an alarm,
    which goes off at 6:00am every morning. The time is set to
    5:59:55, so the alarm will trigger 5 seconds after running
    the code.

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
#include "peripheral/rtcc/plib_rtcc.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/int/plib_int.h"


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
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

bool alarmTriggered;

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

    SYSKEY = 0xaa996655; /* Write first unlock key to SYSKEY */
    SYSKEY = 0x556699aa; /* Write second unlock key to SYSKEY */

    /* Enable writes to RTCC module */
    PLIB_RTCC_WriteEnable(RTCC_ID_0);

    /* Disable the clock, wait for the operation to complete */
    PLIB_RTCC_Disable(RTCC_ID_0);
    while (PLIB_RTCC_ClockRunningStatus(RTCC_ID_0));

    /* Set time and date */
    PLIB_RTCC_RTCTimeSet(RTCC_ID_0, 0x05595500); /* Time = 5 hrs 59 mins 55 sec */
    PLIB_RTCC_RTCDateSet(RTCC_ID_0, 0x13031505); /* Date = 2013 March 15 Friday */

    /* Disable the alarm, wait for the operation to complete */
    PLIB_RTCC_AlarmDisable(RTCC_ID_0);
    while (RTCALRMbits.ALRMSYNC == 1);

    /* Set alarm time and date */
    PLIB_RTCC_AlarmTimeSet(RTCC_ID_0, 0x06000000); /* Time = 6 hrs 0 mins 0 sec */
    PLIB_RTCC_AlarmDateSet(RTCC_ID_0, 0x13031505); /* Date = 2013 March 15 Friday */

    /* Configure alarm mode - alarm is set to ignore the date and instead trigger
       once a day (when the time is 6:00am) */
    PLIB_RTCC_AlarmMaskModeSelect(RTCC_ID_0, RTCC_ALARM_ONCE_A_DAY);

    /* Enable the RTCC interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_RTCC);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_RTCC, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_RTCC, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Enable RTCC module */
    PLIB_RTCC_AlarmEnable(RTCC_ID_0);
    PLIB_RTCC_Enable(RTCC_ID_0);

    /* Disable writes to RTCC and lock */
    PLIB_RTCC_WriteDisable(RTCC_ID_0);
    SYSKEY = 0;

    /* Stuck in this loop, waiting for alarm to be triggered */
    while (1)
    {
        /* Toggles the LEDs a few times when the alarm is triggered */
        if (alarmTriggered)
        {
            int i;
            int delay;
            for (i = 0; i < 20; i++)
            {
                /* Toggle the LEDs on the Explorer-16 */
                PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK) 0x00FF);

                /* Some delay */
                delay = 1000 * 200;
                while (delay--);
            }

            alarmTriggered = 0;
        }
    }

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_RTCC_VECTOR)))
RTCCHandler(void)
{
    alarmTriggered = 1;

    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_RTCC);
}


/*******************************************************************************
 End of File
*/
