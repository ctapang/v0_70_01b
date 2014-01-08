/*******************************************************************************
  MPLAB Harmony SPI Loopback Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony spi_loopback main function

  Description:
    This example assumes that the SPI SDO (output) is connected
    to the SDI (input). Data is then transferred directly from the
    output to the input and the Explorer-16 LEDs are turned on if
    the data transfer is successful.

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
#include "peripheral/ports/plib_ports.h"
#include "peripheral/spi/plib_spi.h"


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
#define SYS_FREQUENCY (80000000)
#define PB_FREQUENCY  (10000000)


// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

char txData[] = "Testing 8-bit SPI!";
char rxData[sizeof(txData)];


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

    /* Setup SPI module - 8 bit transfers, master mode, 10MHz SPI clock speed */
    PLIB_SPI_CommunicationWidthSelect(SPI_ID_1, SPI_COMMUNICATION_WIDTH_8BITS);
    PLIB_SPI_BaudRateSet(SPI_ID_1, PB_FREQUENCY , PB_FREQUENCY);
    PLIB_SPI_PinEnable(SPI_ID_1, SPI_PIN_DATA_OUT);
    PLIB_SPI_InputSamplePhaseSelect(SPI_ID_1, SPI_INPUT_SAMPLING_PHASE_AT_END);
    PLIB_SPI_MasterEnable(SPI_ID_1);
    PLIB_SPI_Enable(SPI_ID_1);

    unsigned int txDataSize = sizeof(txData);
    unsigned int index = 0;

    /* Keep going until there is no data left to transfer */
    while(txDataSize--) 
    {
        /* Write data to buffer */
        PLIB_SPI_BufferWrite(SPI_ID_1, txData[index]);

        /* Wait for receive buffer to fill */
        while(!PLIB_SPI_ReceiverBufferIsFull(SPI_ID_1));

        /* Read the data */
        rxData[index] = PLIB_SPI_BufferRead(SPI_ID_1);

        /* If received data != sent data, there was an error */
        if(rxData[index] != txData[index])
	{
            return EXIT_FAILURE;
	}

        index++; /* increment index */
    }

    /* Turn on LEDs to verify data transfer was successful */
    PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/

