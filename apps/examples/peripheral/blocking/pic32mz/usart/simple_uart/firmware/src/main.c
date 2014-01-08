/*******************************************************************************
  MPLAB Harmony UART Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony simple_uart main function

  Description:
    When the starter-kit is connected to a PC with an RS-232 cable,
    the device will echo what characters the user types into a terminal
    program (e.g. Putty).

  Tested with:
    -PIC32MZ2048ECH144 (PIC32MZ Starter Kit) with MEB II Board and
     ADM00393 UART to USB module (RX to pin 19, TX to Pin 11)
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
#include "peripheral/usart/plib_usart.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/osc/plib_osc.h"


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

#define baudRate 9600
#define clockFreq 200000000


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_B,PORTS_BIT_POS_14,PORTS_PIN_MODE_DIGITAL);
    //ANSELBCLR = 0x4000;
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_G,PORTS_BIT_POS_6,PORTS_PIN_MODE_DIGITAL);
    //ANSELGCLR = 0x0040;

    /* PPS setup */
    PLIB_PORTS_RemapOutput(PORTS_ID_0,OTPUT_FUNC_U2TX,OUTPUT_PIN_RPB14);
    //RPB14R = 0x02;
    PLIB_PORTS_RemapInput(PORTS_ID_0,INPUT_FUNC_U2RX,INPUT_PIN_RPG6);
    //U2RXR = 0x01;

    /* Set PBCLK2 to 200MHz (feeds into USART peripheral) */
    //SYSKEY = 0xAA996655;
    //SYSKEY = 0x556699AA;
    //PB2DIV = 0x00008000;
    //SYSKEY = 0x00000000;
    PLIB_OSC_PBClockDivisorSet(OSC_ID_0,OSC_PERIPHERAL_BUS_2,(OSC_PB_CLOCK_DIV_TYPE)0x01);

    /* Configure the baud rate, 8-N-1 data mode, enable TX/RX pins, generate interrupts when
       the receiver buffer has data */
    PLIB_USART_BaudRateSet(USART_ID_2, clockFreq, baudRate);
    PLIB_USART_LineControlModeSelect(USART_ID_2, USART_8N1);
    PLIB_USART_TransmitterEnable(USART_ID_2);
    PLIB_USART_ReceiverEnable(USART_ID_2);
    PLIB_USART_ReceiverInterruptModeSelect(USART_ID_2, USART_RECEIVE_FIFO_ONE_CHAR);
    
    /* Enable the UART2 receiver interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_UART2_RX, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_UART2_RX, INT_SUBPRIORITY_LEVEL0);
    //IEC4 = (1 << 18);
    //IPC36 = (2 << 18);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Enable the UART module*/
    PLIB_USART_Enable(USART_ID_2);

    /* Write text to the console */
    WriteString("*** UART Interrupt-driven Application Example ***\r\n");
    WriteString("*** Type some characters and observe the LEDs toggle ***\r\n");

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

void __attribute__((interrupt(ipl2), vector(_UART2_RX_VECTOR)))
UartHandler(void)
{
    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);
    //IFS4 = (0 << 18);

    /* Make sure receive buffer has data availible */
    if (PLIB_USART_ReceiverDataIsAvailable(USART_ID_2))
    {
        char data;

        /* Get the data from the buffer */
        data = PLIB_USART_ReceiverByteReceive(USART_ID_2);

        /* Echo what we just received */
        PutCharacter(data);
    }  
}


/*******************************************************************************
 End of File
*/

