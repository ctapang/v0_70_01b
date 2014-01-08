/*******************************************************************************
  MPLAB Harmony Simple Watch Dog Timer Example

  Company:
    Microchip Technology Inc.

  File Name:
    button.c

  Summary:
    MPLAB Harmony simple_wdt button setup

  Description:
    Sets up switch 1 (SW1) to be used for the Watch Dog Timer example.

  Tested with:
    -PIC32MZ2048ECH144 (PIC32MZ Starter Kit)
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
#include "button.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/wdt/plib_wdt.h"

/*******************************************************************************
/*
  Function:
    void ChangeNoticeHandler (void)

  Summary:
    This is the change notice interrupt handler for the push button. It
    has a built in delay routine to cause the WDT to timeout.
*/
void __attribute__((interrupt(ipl2), vector(_CHANGE_NOTICE_B_VECTOR)))
ChangeNoticeHandler(void)
{
    unsigned int temp;
    unsigned int i;

    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    //LATH = 0;

    // Read port to clear mismatch on change notice pin
    temp = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_B);

    // Clear the interrupt flag
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE_B);
    //IFS3bits.CNBIF = 0;

    // Short delay causing the WDT to fail to be serviced in time
    i = 1024 * 1000 * 10;
    while (i--);
}


/*******************************************************************************
/*
  Function:
    void setupPushButton (void)

  Summary:
    Configures the change notice module and enables interrupts for
    the push button.
*/
void setupPushButton(void)
{
    // Set RB12 as input (switch 1 on the starter kit)
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0,PORT_CHANNEL_B,PORTS_BIT_POS_12,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12);
    //ANSELBbits.ANSB12 = 0;

    // Enable weak pullups on RB12, enable change notice interrupts on RB12,
    // enable the global change notice module
    PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0,PORT_CHANNEL_B,PORTS_BIT_POS_12);
    PLIB_PORTS_PinChangeNoticePerPortEnable(PORTS_ID_0,PORT_CHANNEL_B,PORTS_BIT_POS_12);
    PLIB_PORTS_ChangeNoticePerPortTurnOn(PORTS_ID_0,PORT_CHANNEL_B);
    //CNPUBbits.CNPUB12 = 1;
    //CNENBbits.CNIEB12 = 1;
    //CNCONBbits.ON = 1;

    // Enable the change notice interrupt source, set its priority level to 2,
    // set its subpriority level to 0
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE_B);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CHANGE_NOTICE_B, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CHANGE_NOTICE_B, INT_SUBPRIORITY_LEVEL0);
    //IEC3bits.CNBIE = 1;
    //IPC29bits.CNBIP = 2;

    // Enable multi-vectored interrupts, enable the generation of interrupts to the CPU
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);
}


/*******************************************************************************
 End of File
*/

