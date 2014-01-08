/*******************************************************************************
 System Initialization File

  File Name:
    sys_init.c

  Summary:
    System Initialization.

  Description:
    This file contains source code necessary to initialize the system.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

/*
*********************************************************************************************************
*                                                INCLUDES
*********************************************************************************************************
*/
#include <xc.h>
#include <sys/attribs.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <lib_cfg.h>
#include <GenericTypeDefs.h>
#include "os.h"
#include "app_cfg.h"

/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

OS_TCB       SystemDisplayDriverTaskTCB;
CPU_STK      SystemDisplayDriverTaskStk[SYSTEM_DISPLAYDRIVERTASK_STKSIZE];


/*
*********************************************************************************************************
*                                                CONFIGURATION WORDS
*********************************************************************************************************
*/
// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC       // System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_4
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = ON              // USB PLL Enable (USB PLL is enabled)


// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

#pragma config DMTCNT = 0

/* DEVCFG0 */
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER = PG_ALL
#pragma config FSLEEP = OFF
#pragma config FECCCON = OFF_UNLOCKED
#pragma config BOOTISA = MIPS32
#pragma config TRCEN = ON
#pragma config ICESEL = ICS_PGx2
#pragma config DEBUG = ON

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
#pragma config_alt FWDTEN=OFF
#pragma config_alt USERID = 0x1234u

/*******************************************************************************
  Function:
    void SYS_Initialize ( SYS_INIT_DATA *data )

  Summary:
    Initializes the board, services, drivers, application and other modules

  Description:
    This routine initializes the board, services, drivers, application and other
    modules as configured at build time.  In a bare-metal environment (where no
    OS is supported), this routine should be called almost immediately after
    entering the "main" routine.

  Precondition:
    The C-language run-time environment and stack must have been initialized.

  Parameters:
    data        - Pointer to the system initialzation data structure containing
                  pointers to the board, system service, and driver
                  initialization routines
  Returns:
    None.

  Example:
    <code>
    SYS_INT_Initialize(NULL);
    </code>

  Remarks:
    Basic System Initialization Sequence:

    1.  Initilize minimal board services and processor-specific items
        (enough to use the board to initialize drivers and services)
    2.  Initialize all supported system services
    3.  Initialize all supported modules
        (libraries, drivers, middleware, and application-level modules)
    4.  Initialize the main (static) application, if present.

    The order in which services and modules are initialized and started may be
    important.

    For a static system (a system not using the ISP's dynamic implementation
    of the initialization and "Tasks" services) this routine is implemented
    for the specific configuration of an application.
 */

void SYS_Initialize ( void* data )
{
   OS_ERR os_err;
   
   /* Initialize the USB device layer */

   /* Initialize the uC/CPU services                     */
   CPU_Init();
   
   /* Init uC/OS-III.                                    */
   OSInit(&os_err);
   
   /* Initialize the Application */
   APP_Initialize();    
   
   /* Create the system driver task */
   OSTaskCreate((OS_TCB      *)&SystemDisplayDriverTaskTCB,                    
                (CPU_CHAR    *)"Display Driver Task",
                (OS_TASK_PTR  )SystemDisplayDriverTask,
                (void        *)0,
                (OS_PRIO      )SYSTEM_DISPLAYDRIVERTASK_PRIO,
                (CPU_STK     *)&SystemDisplayDriverTaskStk[0],
                (CPU_STK_SIZE )SYSTEM_DISPLAYDRIVERTASK_STKSIZE_LIMIT,
                (CPU_STK_SIZE )SYSTEM_DISPLAYDRIVERTASK_STKSIZE,
                (OS_MSG_QTY   )0u,
                (OS_TICK      )0u,
                (void        *)0,
                (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                (OS_ERR      *)&os_err);
   
   BSP_InitIO();
    
   
   GFX_Initialize();
   GFX_DRV_lcc_Initialize(0);
   GFX_DRV_lcc_Open(0);
}

/*******************************************************************************/
/*******************************************************************************
 End of File
*/
