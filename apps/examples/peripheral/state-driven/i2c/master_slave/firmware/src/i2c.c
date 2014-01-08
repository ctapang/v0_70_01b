/*******************************************************************************
  MPLAB Harmony I2C Functions

  Company:
    Microchip Technology Inc.

  File Name:
    i2c_functions.c

  Summary:
    MPLAB Harmony i2c_functions source file

  Description:
    Contains basic functions to write characters and strings to the UART module.

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

#include "i2c.h"
#include "app.h"

void LEDIndicateWorking(void)
{
    if (BSP_ReadCoreTimer() >= APP_LED_BLINK_DELAY_1s)
    {
        /* Toggle LED */
        BSP_ToggleLED(LED_1);

        /* Clear the core timer to restart count. */
        BSP_WriteCoreTimer(0);
    }
}

bool masterTransferIsComplete(void)
{
    return !PLIB_I2C_TransmitterIsBusy(I2C_ID_1);
}

/*******************************************************************************
/*
  Function:
    void initMaster (int baudRate, int clockFrequency)

  Summary:
    Initializes I2C1 module as the master.
*/
void initMaster(int baudRate, int clockFrequency)
{
    PLIB_I2C_TransmitterByteSend(I2C_ID_1, 0);
    PLIB_I2C_SlaveMask7BitSet(I2C_ID_1, 0);
    PLIB_I2C_SlaveAddress7BitSet(I2C_ID_1, 0);

    PLIB_I2C_BaudRateSet(I2C_ID_1, clockFrequency, baudRate);
    PLIB_I2C_Enable(I2C_ID_1);
}


/*******************************************************************************
/*
  Function:
    void initSlave (int baudRate, int clockFrequency, int address)

  Summary:
    Initializes I2C2 module as the slave.
*/
void initSlave(int baudRate, int clockFrequency, int address)
{
    PLIB_I2C_TransmitterByteSend(I2C_ID_2, 0);
    PLIB_I2C_SlaveMask7BitSet(I2C_ID_2, 0);

    PLIB_I2C_BaudRateSet(I2C_ID_2, clockFrequency, baudRate);
    PLIB_I2C_SlaveAddress7BitSet(I2C_ID_2, address);
    PLIB_I2C_SlaveClockStretchingEnable(I2C_ID_2);
    PLIB_I2C_SlaveClockRelease(I2C_ID_2);

    IEC1 = (1 << 12); // enable i2c2 slave interrupts
    IPC8 = (2 << 10); // priority level to 2

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    PLIB_I2C_Enable(I2C_ID_2);
}

/*******************************************************************************
/*
  Function:
    void waitForIdleMaster (void)

  Summary:
    Blocking loop that waits for the I2C master to become idle.
*/
bool masterIsIdle(void)
{
    return !(I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RSEN || I2C1CONbits.RCEN || I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
}


/*******************************************************************************
/*
  Function:
    char SlaveRead(void)

  Summary:
    Reads out a byte of data from the slave receive buffer.
*/
char SlaveRead(void)
{
     while(!PLIB_I2C_ReceivedByteIsAvailable(I2C_ID_2)); // wait for receive buffer to fill

     PLIB_I2C_ReceiverOverflowClear(I2C_ID_2); // clear overflow flag

     return (PLIB_I2C_ReceivedByteGet(I2C_ID_2));
}


/*******************************************************************************
 End of File
*/
