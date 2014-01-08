/*******************************************************************************
  MPLAB Harmony Output Compare PWM Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony oc_pwm main function

  Description:
    Generates a 40KHz PWM with a 25% duty cycle on the OC1 output pin.

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
#include "peripheral/oc/plib_oc.h"


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
    /* Setup Timer 2 - PBclk as the source, prescaler is 1:1 (PBclk / 1),
       enable 16bit counter mode, clear the counter, set the period to 2,000
       - 80MHz PBclk / 1 = 80MHz Timer 2 clock
       - Period is set to 2,000 so that the timer rolls over every 25us
       - 1/25us = 40KHz signal */
    PLIB_TMR_ClockSourceSelect(TMR_ID_2, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_2, TMR_PRESCALE_VALUE_1);
    PLIB_TMR_Mode16BitEnable(TMR_ID_2);
    PLIB_TMR_Counter16BitClear(TMR_ID_2);
    PLIB_TMR_Period16BitSet(TMR_ID_2, 2000);

    /* Setup OCMP 1 module - Use timer 2, output is an edge aligned signal,
       disable PWM faults, duty cycle and compare values will have 16-bit values,
       buffer value is set to 0, pulse width (duty cycle) value is set to 500
       - The PWM remains high until the timer reaches 500. The PWM then goes
       - low until the timer hits its period of 2000, rolling over to repeat
       - the process again. 500/2,000 = 25% Duty Cycle */
    PLIB_OC_TimerSelect(OC_ID_1, OC_TIMER_16BIT_TMR2);
    PLIB_OC_ModeSelect(OC_ID_1, OC_COMPARE_PWM_EDGE_ALIGNED_MODE);
    PLIB_OC_FaultInputSelect(OC_ID_1, OC_FAULT_DISABLE);
    PLIB_OC_BufferSizeSelect(OC_ID_1, OC_BUFFER_SIZE_16BIT);
    PLIB_OC_Buffer16BitSet(OC_ID_1, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_1, 500);

    /* Enable the OCMP module and start the timer */
    PLIB_OC_Enable(OC_ID_1);
    PLIB_TMR_Start(TMR_ID_2);

    /* Stuck in this loop, PWM is being generated by Output Compare Module */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/