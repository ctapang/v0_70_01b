/*******************************************************************************
  MPLAB Harmony BMX Memory Partition Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony mem_partition main function

  Description:
    This example partitions flash memory and ram. Explorer-16 LEDs
    are turned on if the ram partition sizes are correct and the
    partitioning completed successfully.

  Notes:
    - Ram partitions must be sized to exactly fill the entire ram segment.
      If the partition sizes are too large, too small or undeclared, ram is
      automatically allocated entirely as kernel data.
    - A custom linker script is included in this example (procdefs.ld).
      This is needed in order to resize "kseg1_data_mem" to the intended
      kernel data ram partition size. If this is not done, partitioning the
      ram will cause the data stored on the stack to be inaccessible
      after partitioning and the program will crash.

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
#include "peripheral/bmx/plib_bmx.h"

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
    /* Flash sizes */
    size_t totalFlashSize;
    size_t userPartitionSize = 20 * 1024; // User Mode = 20kb

    /* Ram sizes */
    size_t totalRamSize;
    size_t kernDataRamSize = 64 * 1024; // Kernel Data = 64KB
    size_t kernProgRamSize = 32 * 1024; // Kernel Program = 32KB
    size_t userDataRamSize = 16 * 1024; // User Data = 16KB
    size_t userProgRamSize = 16 * 1024; // User Program = 16KB

    /* Flash offsets */
    size_t userPartitionOffset;

    /* Ram offsets */
    size_t userProgOffset;
    size_t userDataOffset;
    size_t kernProgOffset;

    /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Set the lower 8 bits of PORTA as output (for Explorer-16 LEDs),
       clear the bits to ensure there is no mismatch when they are toggled */
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Get size of program flash and data ram */
    totalFlashSize = PLIB_BMX_ProgramFlashMemorySizeGet(BMX_ID_0);
    totalRamSize = PLIB_BMX_DataRAMSizeGet(BMX_ID_0);

    /* Setup flash offsets */
    userPartitionOffset = totalFlashSize - userPartitionSize;

    /* Setup ram offsets */
    kernProgOffset = kernDataRamSize;
    userDataOffset = kernProgOffset + kernProgRamSize;
    userProgOffset = userDataOffset + userDataRamSize;

    /* Set a user mode partition in flash memory of 20kb, the rest will be kernel mode */
    PLIB_BMX_ProgramFlashPartitionSet(BMX_ID_0, userPartitionOffset);

    /* Set RAM partitions */
    PLIB_BMX_DataRAMPartitionSet(BMX_ID_0, kernProgOffset, userDataOffset, userProgOffset);

    /* Get the offsets */
    kernProgOffset = PLIB_BMX_DataRAMKernelProgramOffsetGet(BMX_ID_0);
    userDataOffset = PLIB_BMX_DataRAMUserDataOffsetGet(BMX_ID_0);
    userProgOffset = PLIB_BMX_DataRAMUserProgramOffsetGet(BMX_ID_0);

    /* Check the sizes of each partition, to ensure everything was successful */
    kernDataRamSize = kernProgOffset;
    kernProgRamSize = userDataOffset - kernProgOffset;
    userDataRamSize = userProgOffset - userDataOffset;
    userProgRamSize = totalRamSize - userProgOffset;

    /* Verify partition sizes fit RAM */
    if ((kernDataRamSize + kernProgRamSize + userDataRamSize + userProgRamSize) == totalRamSize)
    {
        /* Turn on LEDs */
        PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, 0xFF);
    }

    /* Stuck in this loop */
    while (1);

    /* Program should not go here during normal operation */
    return EXIT_FAILURE;
}


/*******************************************************************************
 End of File
*/