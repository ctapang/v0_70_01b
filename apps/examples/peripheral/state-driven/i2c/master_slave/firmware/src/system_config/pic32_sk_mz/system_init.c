/*******************************************************************************
  MPLAB Harmony I2C Master Slave Example

  Company:
    Microchip Technology Inc.

  File Name:
    system_init.c

  Summary:
    MPLAB Harmony master_slave initialization

  Description:
    This file contains the MPLAB Harmony master_slave initialization routine.
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

#if defined(cfg_pic32_sk_mz)

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

/* SYSCLK = 200 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV) */
#pragma config FPLLIDIV = DIV_1, FPLLMULT = MUL_50, FPLLODIV = DIV_2
#pragma config FPLLRNG = RANGE_5_10_MHZ, FPLLICLK = PLL_FRC, FNOSC = SPLL
#pragma config FSOSCEN = OFF, IESO = ON, POSCMOD = OFF, FCKSM = CSECMD
#pragma config FDMTEN = OFF, DMTCNT = DMT31, FWDTEN = OFF, ICESEL = ICS_PGx2

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

    CNENBbits.CNIEB12 = 1;
    CNENBbits.CNIEB13 = 1;
    CNENBbits.CNIEB14 = 1;
    CNCONBbits.ON = 1;

    // Enable the change notice interrupt source, set its priority level to 2,
    // set its subpriority level to 0
    // PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_CHANGE_NOTICE_B);
    // PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_CHANGE_NOTICE_B, INT_PRIORITY_LEVEL2);
    // PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_CHANGE_NOTICE_B, INT_SUBPRIORITY_LEVEL0);
    IEC3bits.CNBIE = 1;
    IPC29bits.CNBIP = 2;

    // Enable multi-vectored interrupts, enable the generation of interrupts to the CPU
    PLIB_INT_MultiVectorSelect(INT_ID_0);
    PLIB_INT_Enable(INT_ID_0);

    APP_Initialize();

    PLIB_WDT_Enable(WDT_ID_0);
}


#endif //__32MZ2048ECH144__

/*******************************************************************************
 End of File
*/
