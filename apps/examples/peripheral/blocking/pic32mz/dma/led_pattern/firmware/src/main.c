/*******************************************************************************
  MPLAB Harmony DMA LED Pattern Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony led_pattern main function

  Description:
    This example blinks LEDs on the starter-kit using a pattern stored
    in flash memory. It uses the DMA controller to transfer data from flash
    to the I/O port controlling the LEDs. The DMA transfer is initiated by
    timer 2 interrupts. Once the pattern is completely transferred, the
    process is repeated.

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
#include <stdlib.h>
#include "peripheral/dma/plib_dma.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/osc/plib_osc.h"
#include "peripheral/tmr/plib_tmr.h"
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
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

/* Bytes that define the pattern that will be output to the LED's */
static const unsigned char	LED_pattern[]=
{
	0x01,	0x02,	0x04,	0x04,	0x02,	0x01
};


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Set PORTH pins to output (for the three starter-kit LEDs),
       clear the pins to ensure LEDs are off */

    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_0,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_1,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_H,PORTS_BIT_POS_2,PORTS_PIN_MODE_DIGITAL);
    //ANSELH = 0;
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_0);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_1);
    PLIB_PORTS_PinDirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, PORTS_BIT_POS_2);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    //TRISH = 0;
    //LATH = 0;

    /* Enable the DMA module */
    PLIB_DMA_Enable(DMA_ID_0);

    /* Channel is continuously enabled */
    PLIB_DMA_ChannelXAutoEnable(DMA_ID_0, DMA_CHANNEL_0);

    /* Set the source and destinaton addresses (addresses are converted from virtual to physical) */
    PLIB_DMA_ChannelXSourceStartAddressSet(DMA_ID_0, DMA_CHANNEL_0, (uint32_t)LED_pattern);
    PLIB_DMA_ChannelXDestinationStartAddressSet(DMA_ID_0, DMA_CHANNEL_0, (uint32_t)&LATH);

    /* Set the source and destination sizes */
    PLIB_DMA_ChannelXSourceSizeSet(DMA_ID_0, DMA_CHANNEL_0, sizeof(LED_pattern));
    PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DMA_CHANNEL_0, 1);

    /* Set the number of bytes per transfer */
    PLIB_DMA_ChannelXCellSizeSet(DMA_ID_0, DMA_CHANNEL_0, 1);

    /* DMA transfer to start on Timer 2 interrupt */
    PLIB_DMA_ChannelXTriggerEnable(DMA_ID_0, DMA_CHANNEL_0, DMA_CHANNEL_TRIGGER_TRANSFER_START);
    PLIB_DMA_ChannelXStartIRQSet(DMA_ID_0, DMA_CHANNEL_0, DMA_TRIGGER_TIMER_2);

    /* Set the PBCLK3 divisor to 128 and enable PBCLK3 (for timer 2) */
     PLIB_OSC_PBClockDivisorSet(OSC_ID_0, OSC_PERIPHERAL_BUS_3, 0x7F);
     PLIB_OSC_PBOutputClockEnable(OSC_ID_0, OSC_PERIPHERAL_BUS_3);
    //SYSKEY = 0xaa996655;
    //SYSKEY = 0x556699aa;
    //PB3DIV = 0x0000807F;
    //SYSKEY = 0;

    /* Setup Timer 2 - period is set to 610 to trigger an interrupt 10 times
       a second */
    PLIB_TMR_ClockSourceSelect(TMR_ID_2, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_2, TMR_PRESCALE_VALUE_256);
    PLIB_TMR_Mode16BitEnable(TMR_ID_2);
    PLIB_TMR_Counter16BitClear(TMR_ID_2);
    PLIB_TMR_Period16BitSet(TMR_ID_2, 610);

    /* Enable the Timer 2 interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T2, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T2, INT_SUBPRIORITY_LEVEL0);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_2);
    //IEC0bits.T2IE = 1;
    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Enable DMA channel 0 */
    PLIB_DMA_ChannelXEnable(DMA_ID_0, DMA_CHANNEL_0);

    /* Start Timer 2 */
    PLIB_TMR_Start(TMR_ID_2);

    /* Stuck in this loop, waiting for interrupts to occur */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_TIMER_2_VECTOR)))
TimerHandler(void)
{
    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_2);
    //IFS0bits.T2IF = 0;
}


/*******************************************************************************
 End of File
*/
