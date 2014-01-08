/*******************************************************************************
  MPLAB Harmony WDT Timeout Example

  Company:
    Microchip Technology Inc.

  File Name:
    system_init.c

  Summary:
    MPLAB Harmony wdt_timeout initialization

  Description:
    This file contains the MPLAB Harmony wdt_timeout initialization routine.
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

#if defined(cfg_ex16_pic32mx795f512l)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"


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

#pragma config WDTPS = PS1 /* WDT timeout period = 1ms */

// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void SYS_Initialize ( void )

  Remarks:
    See prototype in system_config.h.
*/

void SYS_Initialize ( void )
{
    SYSTEMConfigPerformance(SYS_FREQUENCY);

    BSP_Initialize();

    PLIB_PORTS_PinChangeNoticeEnable(PORTS_ID_0, CN15);
    PLIB_PORTS_PinChangeNoticeEnable(PORTS_ID_0, CN16);
    PLIB_PORTS_PinChangeNoticeEnable(PORTS_ID_0, CN19);
    CNCONbits.ON = 1;

    /* Enable the change notice interrupt source, set its priority level to 2,
       set its subpriority level to 0 */
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_PRIORITY_LEVEL2);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CN, INT_SUBPRIORITY_LEVEL0);

    /* Enable multi-vectored interrupts, enable the generation of interrupts to the CPU */
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    APP_Initialize();

    PLIB_WDT_Enable(WDT_ID_0);
}


#endif //__32MX795F512L__


/*******************************************************************************
 End of File
*/
