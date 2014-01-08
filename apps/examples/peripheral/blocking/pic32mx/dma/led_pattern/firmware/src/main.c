/*******************************************************************************
  MPLAB Harmony DMA LED Pattern Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony led_pattern main function

  Description:
    This example blinks LEDs on the Explorer-16 using a pattern stored
    in flash memory. It uses the DMA controller to transfer data from flash
    to the I/O port controlling the LEDs. The DMA transfer is initiated by
    timer 1 interrupts. Once the pattern is completely transferred, the
    process is repeated.

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
#include "peripheral/dma/plib_dma.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"

// *****************************************************************************
// *****************************************************************************
// Section: Device Configuration
// *****************************************************************************
// *****************************************************************************

/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 10 MHz (SYSCLK / FPBDIV) */
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8, FSOSCEN = ON
#pragma config ICESEL = ICS_PGx2, FCKSM = CSECME, OSCIOFNC = ON
#define SYS_FREQUENCY (80000000L)


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

/* Bytes that define the pattern that will be output to the LED's */
static const unsigned char	LED_pattern[]=
{
	0x1,	0x2,	0x4,	0x8,	0x10,	0x20,	0x40,	0x80,
	0xff,	0x0,	0x55,	0xaa,	0xe7,	0x18,	0xff,	0xaa,
	0x0f,	0x00,	0x0f,	0x00,	0xf0,	0x00,	0xf0,	0x00
};


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

    /* Enable the DMA module */
    PLIB_DMA_Enable(DMA_ID_0);

    /* Channel is continuously enabled */
    PLIB_DMA_ChannelXAutoEnable(DMA_ID_0, DMA_CHANNEL_0);

    /* Set the source and destinaton addresses (addresses are converted from virtual to physical) */
    PLIB_DMA_ChannelXSourceStartAddressSet(DMA_ID_0, DMA_CHANNEL_0, (uint32_t)LED_pattern);
    PLIB_DMA_ChannelXDestinationStartAddressSet(DMA_ID_0, DMA_CHANNEL_0, (uint32_t)&LATA);

    /* Set the source and destination sizes */
    PLIB_DMA_ChannelXSourceSizeSet(DMA_ID_0, DMA_CHANNEL_0, sizeof(LED_pattern));
    PLIB_DMA_ChannelXDestinationSizeSet(DMA_ID_0, DMA_CHANNEL_0, 1);

    /* Set the number of bytes per transfer */
    PLIB_DMA_ChannelXCellSizeSet(DMA_ID_0, DMA_CHANNEL_0, 1);

    /* DMA transfer to start on Timer 1 interrupt */
    PLIB_DMA_ChannelXTriggerEnable(DMA_ID_0, DMA_CHANNEL_0, DMA_CHANNEL_TRIGGER_TRANSFER_START);
    PLIB_DMA_ChannelXStartIRQSet(DMA_ID_0, DMA_CHANNEL_0, DMA_TRIGGER_TIMER_1);

    /* Setup Timer 1 to trigger an interrupt 10 times a second */
    PLIB_TMR_ClockSourceSelect(TMR_ID_1, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_1, TMR_PRESCALE_VALUE_256);
    PLIB_TMR_Counter16BitClear(TMR_ID_1);
    PLIB_TMR_Period16BitSet(TMR_ID_1, 3906);

    /* Enable the Timer 1 interrupt source, set its priority level to 2, set
       its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_TIMER_1);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_T1, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Enable DMA channel 0 */
    PLIB_DMA_ChannelXEnable(DMA_ID_0, DMA_CHANNEL_0);

    /* Start Timer 1 */
    PLIB_TMR_Start(TMR_ID_1);

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

void __attribute__((interrupt(ipl2), vector(_TIMER_1_VECTOR)))
TimerHandler(void)
{
    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_TIMER_1);
}


/*******************************************************************************
 End of File
*/
