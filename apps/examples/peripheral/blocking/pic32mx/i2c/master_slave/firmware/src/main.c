/*******************************************************************************
  MPLAB Harmony I2C Master-Slave Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony master_slave main function

  Description:
    This example assumes that the clock and data lines of I2C1 and I2C2
    are connected (SDA1<->SDA2 & SCL1<->SCL2). The I2C1 module operates as
    the master and the I2C2 module operates as the slave. The slave
    accepts data from the master using the interrupt service routine,
    which saves the character string received from the master into the
    dataBuff[] array.

  Notes:
    The slave code in this example (in the ISR) is only setup to accept writes
    from the master, so that it can save a string of text received from the
    master. Additional states in the ISR must be added in order for the slave
    to properly handle a read command, where the slave sends back data to the
    master. Check App Note AN734 for more info on a I2C slave state machine.

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

#include "i2c_functions.h"
#include "peripheral/i2c/plib_i2c.h"
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

/* 100KHz I2C baud rate, slave address is set to 0x1A (arbitrary) */
#define clkFreq 80000000
#define baudRate_100KHz 100000
#define slaveAddress 0x1A

// *****************************************************************************
// *****************************************************************************
// Section: Global Variables
// *****************************************************************************
// *****************************************************************************

char *someString = "Microchip I2C";
char dataBuff[32];
unsigned int buffIndex = 0;


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Initialize the master and slave, set the baud rate, set the slave address */
    initMaster(baudRate_100KHz, clkFreq);
    initSlave(baudRate_100KHz, clkFreq, slaveAddress);

    /* Instruct the master to trigger a start condition */
    PLIB_I2C_MasterStart(I2C_ID_1);
    waitForIdleMaster();

    /* Send address byte and wait for slave to acknowledge */
    sendAddressByteToSlave(0x1A);

    /* Send a string of text to the slave */
    sendStringToSlave(someString);

    /* Instruct the master to trigger a stop condition */
    PLIB_I2C_MasterStop(I2C_ID_1);
    waitForIdleMaster();

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

void __attribute__((interrupt(ipl2), vector(_I2C_2_VECTOR)))
i2cSlaveHandler(void)
{
    char temp;

    /* Last byte received was address with write indication */
    if ((!PLIB_I2C_SlaveReadIsRequested(I2C_ID_2)) && (PLIB_I2C_SlaveAddressIsDetected(I2C_ID_2)))
    {
        /* Dummy read to clear receive buffer */
        temp = SlaveRead();

        /* Instruct slave to release the clock */
        PLIB_I2C_SlaveClockRelease(I2C_ID_2);
    }

    /* Last byte received was data with write indication */
    else if ((!PLIB_I2C_SlaveReadIsRequested(I2C_ID_2)) && (PLIB_I2C_SlaveDataIsDetected(I2C_ID_2)))
    {
        /* Store the received data into dataBuff[] array */
        dataBuff[buffIndex] = SlaveRead();

        /* Increment the index */
        buffIndex++;

        /* Instruct slave to release the clock */
        PLIB_I2C_SlaveClockRelease(I2C_ID_2);
    }

    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0,INT_SOURCE_I2C_2_SLAVE);
    //IFS1 = (0 << 12);
}


/*******************************************************************************
 End of File
*/
