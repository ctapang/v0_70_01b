/*******************************************************************************
  MPLAB Harmony PMP LCD Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony pmp_lcd main function

  Description:
    Writes two lines of text to the LCD screen on the Explorer-16.

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
#include "peripheral/pmp/plib_pmp.h"
#include "peripheral/tmr/plib_tmr.h"


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
// Section: Function Prototypes
// *****************************************************************************
// *****************************************************************************

void Delay_ms(unsigned int x);
void initializeLCD(void);
void writeToLCD(int reg, char c);
void writeString(unsigned char *string);
void newLine(void);


// *****************************************************************************
// *****************************************************************************
// Section: Constant Data
// *****************************************************************************
// *****************************************************************************

/* Define aliases for the LCD data and command registers */
#define DATAREG 1 /* Data register */
#define CMDREG 0  /* Command register */

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main(void)
{
    /* Setup Timer 1 to use for the Delay_ms function - 39,062KHz Timer 1 clock */
    PLIB_TMR_ClockSourceSelect(TMR_ID_1, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_1, TMR_PRESCALE_VALUE_256);
    PLIB_TMR_Counter16BitClear(TMR_ID_1);
    PLIB_TMR_Period16BitSet(TMR_ID_1, 0xFFFF);
    PLIB_TMR_Start(TMR_ID_1);
    
    /* Execute LCD initialization sequence */
    initializeLCD();

    writeToLCD(CMDREG, 0x0F); /* Turn on blinking cursor */
    writeString("Hello!"); /* Write string to the LCD */
    newLine(); /* Set cursor to line two */
    writeString("Testing..."); /* Print another string */

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
/*
  Function:
    void Delay_ms (unsigned int x)

  Summary:
    Delay needed for the LCD to process data (in ms)
*/
void Delay_ms(unsigned int x)
{
    PLIB_TMR_Counter16BitClear(TMR_ID_1); /* Clear the timer */
    while (PLIB_TMR_Counter16BitGet(TMR_ID_1) < (40 * x)); /* 40 Timer 1 ticks = ~1ms */
}


/*******************************************************************************
/*
  Function:
    void initializeLCD (void)

  Summary:
    LCD initialization sequence
*/
void initializeLCD(void)
{
    /* Configure general PMP options - enable read/write strobes, long waits, etc */
    PLIB_PMP_OperationModeSelect(PMP_ID_0, PMP_MASTER_READ_WRITE_STROBES_MULTIPLEXED);
    PLIB_PMP_AddressSet(PMP_ID_0, PMP_PMA0_PORT);
    PLIB_PMP_ReadWriteStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH);
    PLIB_PMP_WriteEnableStrobePolaritySelect(PMP_ID_0, PMP_POLARITY_ACTIVE_HIGH);
    PLIB_PMP_AddressPortEnable(PMP_ID_0, PMP_PMA0_PORT);
    PLIB_PMP_ReadWriteStrobePortEnable(PMP_ID_0);
    PLIB_PMP_WriteEnableStrobePortEnable(PMP_ID_0);
    PLIB_PMP_WaitStatesDataSetUpSelect(PMP_ID_0, PMP_DATA_WAIT_FOUR);
    PLIB_PMP_WaitStatesStrobeSelect(PMP_ID_0, PMP_STROBE_WAIT_16);
    PLIB_PMP_WaitStatesDataHoldSelect(PMP_ID_0, PMP_DATA_HOLD_4);
    PLIB_PMP_Enable(PMP_ID_0);
    
    Delay_ms(30); /* LCD needs 30ms to power on and perform startup functions */

    PLIB_PMP_AddressSet(PMP_ID_0, CMDREG); /* Access the LCD command register */

    PLIB_PMP_MasterSend(PMP_ID_0, 0x38); /* LCD Function Set - 8-bit interface, 2 lines, 5*7 Pixels */
    Delay_ms(1); /* Needs a 40us delay to complete */

    PLIB_PMP_MasterSend(PMP_ID_0, 0x0C); /* Turn on display (with cursor hidden) */
    Delay_ms(1); /* Needs a 40us delay to complete */

    PLIB_PMP_MasterSend(PMP_ID_0, 0x01); /* Clear the display */
    Delay_ms(2); /* Needs a 1.64ms delay to complete */

    PLIB_PMP_MasterSend(PMP_ID_0, 0x06); /* Set text entry mode - auto increment, no shift */
    Delay_ms(1); /* Needs a 40us delay to complete */
}


/*******************************************************************************
/*
  Function:
    void writeToLCD(int reg, char c)

  Summary:
    Writes a byte of data to either of the two LCD registers (DATAREG, CMDREG)
*/
void writeToLCD(int reg, char c)
{
    PLIB_PMP_AddressSet(PMP_ID_0, reg); /* Either 'DATAREG' or 'CMDREG' */

    while (PLIB_PMP_PortIsBusy(PMP_ID_0));

    PLIB_PMP_MasterSend(PMP_ID_0, c); /* Write the byte to selected register */
    
    Delay_ms(1); /* 40us needed in between each write */
}


/*******************************************************************************
/*
  Function:
    void writeString (unsigned char *string)

  Summary:
    Used to write text strings to the LCD
*/
void writeString(unsigned char *string)
{
    while (*string) 
    {
        writeToLCD(DATAREG, *string++); /* Send characters one by one */
    }
}


/*******************************************************************************
/*
  Function:
    void newLine(void)

  Summary:
    Sets the LCD cursor position to line two
*/
void newLine(void)
{
    writeToLCD(CMDREG, 0xC0); /* Cursor address 0x80 + 0x40 = 0xC0 */
}


/*******************************************************************************
 End of File
*/