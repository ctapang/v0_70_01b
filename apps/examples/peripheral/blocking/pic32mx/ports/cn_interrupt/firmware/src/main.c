/*******************************************************************************
  MPLAB Harmony Change Notice Interrupt Example

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    MPLAB Harmony cn_interrupt main function

  Description:
    When SW4 (the right most button on Explorer-16) is pressed,
    it triggers a change notice interrupt, which then toggles the
    Explorer-16 LEDs.

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
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"


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
    /* Disable JTAG to free up PORTA pins */
    DDPCONbits.JTAGEN = 0;

    /* Set the lower 8 bits of PORTA as output (for Explorer-16 LEDs),
       clear the bits to ensure there is no mismatch when they are toggled */
    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Set pin 13 as input (connected to switch 4 on the Explorer) */
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13);
  
    /* Enable CN19 (CN19 corresponds to pin 13), enable weak pullups on CN19,
       enable the global change notice module */
    PLIB_PORTS_PinChangeNoticeEnable(PORTS_ID_0, CN19);
    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, CN19);
    PLIB_PORTS_ChangeNoticeEnable(PORTS_ID_0);
    //CNCONbits.ON = 1;

    /* Enable the change notice interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

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

void __attribute__((interrupt(ipl2), vector(_CHANGE_NOTICE_VECTOR)))
ChangeNoticeHandler(void)
{
    unsigned int temp;

    /* Read port to clear mismatch on change notice pins */
    temp = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_D);

    /* Toggle the LEDs on the Explorer-16 */
    PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
}


/*******************************************************************************
 End of File
*/