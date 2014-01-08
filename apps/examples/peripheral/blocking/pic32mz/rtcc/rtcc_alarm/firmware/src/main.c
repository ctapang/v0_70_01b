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
#include "peripheral/osc/plib_osc.h"
#include "peripheral/rtcc/plib_rtcc.h"
#include "peripheral/int/plib_int.h"
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
    // Set PORTH pins to digital output (for the three starter-kit LEDs),
    // clear the pins to ensure LEDs are off
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_0,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_1,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_2,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    //ANSELH = 0;
    //TRISH = 0;
    //LATH = 0;

    SYSKEY = 0xaa996655; // Write first unlock key to SYSKEY
    SYSKEY = 0x556699aa; // Write second unlock key to SYSKEY
    //PLIB_CORE_SysUnlock();
    // Enable writes to RTCC module
    PLIB_RTCC_WriteEnable(RTCC_ID_0);

    // Disable the clock, wait for the operation to complete
    PLIB_RTCC_Disable(RTCC_ID_0);
    while (PLIB_RTCC_ClockRunningStatus(RTCC_ID_0));

     // Set time and date
    PLIB_RTCC_RTCTimeSet(RTCC_ID_0, 0x05595500); // Time = 5 hrs 59 mins 55 sec
    PLIB_RTCC_RTCDateSet(RTCC_ID_0, 0x13031505); // Date = 2013 March 15 Friday

    // Disable the alarm, wait for the operation to complete
    PLIB_RTCC_AlarmDisable(RTCC_ID_0);
    while (RTCALRMbits.ALRMSYNC);

    // Set alarm time and date
    PLIB_RTCC_AlarmTimeSet(RTCC_ID_0, 0x06000000); // Time = 6 hrs 0 mins 0 sec
    PLIB_RTCC_AlarmDateSet(RTCC_ID_0, 0x13031505); // Date = 2013 March 15 Friday

    // Configure alarm mode - alarm is set to ignore the date and instead trigger
    // once a day (when the time is 6:00am)
    PLIB_RTCC_AlarmMaskModeSelect(RTCC_ID_0, RTCC_ALARM_ONCE_A_DAY);

    // Enable the RTCC interrupt source, set its priority level to 2,
    // set its subpriority level to 0
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_RTCC);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_RTCC, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_RTCC, INT_SUBPRIORITY_LEVEL0);
    //IEC5bits.RTCCIE = 1;
    //IPC41bits.RTCCIP = 2;

    // Enable multi-vectored interrupts, enable the generation of interrupts to the CPU
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    // Enable RTCC module
    PLIB_RTCC_AlarmEnable(RTCC_ID_0);
    PLIB_RTCC_Enable(RTCC_ID_0);

     // Disable writes to RTCC and lock
    PLIB_RTCC_WriteDisable(RTCC_ID_0);
    SYSKEY = 0;

    alarmTriggered = 0;

    while (1)
    {
        // Simple loop that toggles the LEDs a few times, when the alarm is triggered
        if (alarmTriggered)
        {
            int i;
            int delay;
            for (i = 0; i < 20; i++)
            {
                // Toggle the LEDs
                PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
                //LATHINV = 0x7;

                // Some delay
                delay = 1000 * 1000 * 10;
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
    // Clear the interrupt flag
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_RTCC);
    //IFS5bits.RTCCIF = 0;

    alarmTriggered = 1;
}


/*******************************************************************************
 End of File
*/
