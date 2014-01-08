/*******************************************************************************
  MPLAB Harmony UART Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony simple_uart main function

  Description:
    When the Explorer-16 is connected to a PC with an RS-232 cable,
    the device will echo what characters the user types into a terminal
    program (e.g. Putty) and write the corresponding 8-bit character
    pattern to the Explorer LEDs.

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
#include "peripheral/usart/plib_usart.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"
#include "uart_functions.h"


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
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

uint32_t baudRate = 9600;
uint32_t clockFreq = 80000000;


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
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_UART2, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_UART2, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    /* Enable the UART module*/
    PLIB_USART_Enable(USART_ID_2);

    /* Write text to the console */
    WriteString("*** UART Interrupt-driven Application Example ***\r\n");
    WriteString("*** Type some characters and observe the Explorer-16 LEDs toggle ***\r\n");

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

void __attribute__((interrupt(ipl2), vector(_UART2_VECTOR)))
UartHandler(void)
{
    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_USART_2_RECEIVE);

    /* Make sure receive buffer has data availible */
    if (PLIB_USART_ReceiverDataIsAvailable(USART_ID_2))
    {
        char data;

        /* Get the data from the buffer */
        data = PLIB_USART_ReceiverByteReceive(USART_ID_2);

        /* Echo what we just received */
        PutCharacter(data);

        /* Write the character mask to the LEDs */
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, data);
    }  
}


/*******************************************************************************
 End of File
*/

