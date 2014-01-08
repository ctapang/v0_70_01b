/*******************************************************************************
  MPLAB Harmony Simple Watch Dog Timer Example

  Company:
    Microchip Technology Inc.

  File Name:
    button.c

  Summary:
    MPLAB Harmony simple_wdt button setup

  Description:
    Sets up the right-most button on the Explorer - 16 to be used for the
    Watch Dog Timer example.

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
#include "button.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/int/plib_int.h"

/*******************************************************************************
/*
  Function:
    void ChangeNoticeHandler (void)

  Summary:
    This is the change notice interrupt handler for the push button. It
    has a built in delay routine to cause the WDT to timeout.
*/
void __attribute__((interrupt(ipl2), vector(_CHANGE_NOTICE_VECTOR)))
ChangeNoticeHandler(void)
{
    unsigned int temp;
    unsigned int i;

    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_A, (PORTS_DATA_MASK)0x00FF);

    /* Read port to clear mismatch on change notice pins */
    temp = PLIB_PORTS_Read(PORTS_ID_0, PORT_CHANNEL_D);

    /* Clear the interrupt flag */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);

    /* Short delay causing the WDT to fail to be serviced in time */
    i = 1024 * 100;
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
    /* Set pin 13 as input (connected to switch 4 on the Explorer) */
    PLIB_PORTS_PinDirectionInputSet(PORTS_ID_0, PORT_CHANNEL_D, PORTS_BIT_POS_13);

    /* Enable the global change notice module, enable weak pullups on CN19,
       enable CN19 (CN19 is pin 13) */
    PLIB_PORTS_ChangeNoticeEnable(PORTS_ID_0);
    //CNCONbits.ON = 1;
    PLIB_PORTS_ChangeNoticePullUpEnable(PORTS_ID_0, CN19);
    PLIB_PORTS_PinChangeNoticeEnable(PORTS_ID_0, CN19);

    /* Enable the change notice interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);
}


/*******************************************************************************
 End of File
*/

