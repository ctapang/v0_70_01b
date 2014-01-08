/*******************************************************************************
  MPLAB Harmony NVM Flash Modify Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony flash_modify main function

  Description:
    Reads, writes and erases data in the program flash memory.
    The simple_nvm_functions source file contains example functions
    that demonstrate how word write, row write, and page erase
    operations work. If all operations complete successfully,
    the first two LEDs on the Explorer-16 will light up.

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
#include "peripheral/nvm/plib_nvm.h"
#include "peripheral/ports/plib_ports.h"
#include "simple_nvm_functions.h"


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

uint32_t PROGRAM_FLASH_BASE_ADDRESS = 0xBD008000;
uint32_t databuff[128]; /* 512 bytes = 1 row */
uint32_t randomWord = 0x12345678;

#define buffSize  (sizeof(databuff) / sizeof(uint32_t))

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

    /* Fill databuff with some data */
    unsigned int x;
    for (x = 0; x < buffSize; x++){
        databuff[x] = x;
    }

    /* Erase page (4096 bytes), starting at PROGRAM_FLASH_BASE_ADDRESS */
    NVMpageErase(PROGRAM_FLASH_BASE_ADDRESS);

    /* Write a word of data */
    NVMwriteWord(PROGRAM_FLASH_BASE_ADDRESS, randomWord);

    /* Verify that data written to flash memory is valid */
    if (PLIB_NVM_FlashRead(NVM_ID_0, PROGRAM_FLASH_BASE_ADDRESS) == 0x12345678)
    {
        /* If the data matches, turn on first LED */
       PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_0);
    }

    /* Erase page once again... */
    NVMpageErase(PROGRAM_FLASH_BASE_ADDRESS);

    /* Write a row of data to PROGRAM_FLASH_BASE_ADDRESS, using databuff array as the source */
    NVMwriteRow(PROGRAM_FLASH_BASE_ADDRESS, (uint32_t)databuff);

    /* Verify that data written to flash memory is valid */
    if (!memcmp(databuff, (void *)PROGRAM_FLASH_BASE_ADDRESS, sizeof(databuff)))
    {
        /* If the data matches, turn on second LED */
        PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_A, PORTS_BIT_POS_1);
    }
   
   /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/


