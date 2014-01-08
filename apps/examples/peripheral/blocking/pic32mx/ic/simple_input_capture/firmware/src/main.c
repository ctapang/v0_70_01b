/*******************************************************************************
  MPLAB Harmony Input Capture Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony simple_input_capture main function

  Description:
    When a rising edge is output to the input capture 1 pin (RD8),
    it triggers an interrupt, which then stores the captured timer
    value into the 'CaptureTime' variable.

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
#include "peripheral/tmr/plib_tmr.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/ic/plib_ic.h"


// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx2, FCKSM = CSECME, OSCIOFNC = ON
#define SYS_FREQUENCY (80000000L)


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

#define PERIOD  0xFFFFFFFF /* Timer period of ~4 billion (max period for 32 bit timer) */


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

unsigned int CaptureTime = 0; /* Used to store the captured timer value */


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* PBclk as the timer source, prescaler is 256 (PBclk / 256), enable timer 23
       (timer 2 + timer 3, 32 bit time), clear the counter, set timer period */
    PLIB_TMR_ClockSourceSelect(TMR_ID_2, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_2, TMR_PRESCALE_VALUE_256);
    PLIB_TMR_Mode32BitEnable(TMR_ID_2);
    PLIB_TMR_Counter32BitClear(TMR_ID_2);
    PLIB_TMR_Period32BitSet(TMR_ID_2, PERIOD);

    /* Setup input capture to capture only rising edges, captures start
       on first rising edge, use timer 2, use a 32 bit buffer for storing
       the captured timer value, enable the input capture 1 module */
    PLIB_IC_ModeSelect(IC_ID_1, IC_INPUT_CAPTURE_RISING_EDGE_MODE);
    PLIB_IC_FirstCaptureEdgeSelect(IC_ID_1, IC_EDGE_RISING);
    PLIB_IC_TimerSelect(IC_ID_1, IC_TIMER_TMR2);
    PLIB_IC_BufferSizeSelect(IC_ID_1, IC_BUFFER_SIZE_32BIT);
    PLIB_IC_Enable(IC_ID_1);

    /* Enable the input capture 1 interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_INPUT_CAPTURE_1);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_IC1, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_IC1, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Start the timer */
    PLIB_TMR_Start(TMR_ID_2);

    /* Waiting for input capture event (stuck in this loop) */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_INPUT_CAPTURE_1_VECTOR)))
InputCaptureHandler(void)
{
    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_INPUT_CAPTURE_1);

    /* Make sure input capture buffer is full before performing a read */
    if (!PLIB_IC_BufferIsEmpty(IC_ID_1))
    {
        /* Store the value of the capture event into CaptureTime variable */
        CaptureTime = PLIB_IC_Buffer32BitGet(IC_ID_1);
    }
}


/*******************************************************************************
 End of File
*/