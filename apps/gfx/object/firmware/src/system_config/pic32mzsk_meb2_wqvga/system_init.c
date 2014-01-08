/*******************************************************************************
 System Initialization File

  File Name:
    system_init.c

  Summary:
    System Initialization.

  Description:
    This file contains source code necessary to initialize the system.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2013 released Microchip Technology Inc.  All rights reserved.

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
#include "app.h"

// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
// DEVCFG2
#pragma config FPLLIDIV = DIV_1,FPLLRNG = RANGE_5_10_MHZ,FPLLICLK = PLL_FRC,FPLLMULT = MUL_50,FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ,UPLLEN = OFF

// DEVCFG1
#pragma config FNOSC = SPLL,DMTINTV = WIN_127_128,FSOSCEN = OFF,IESO = OFF,POSCMOD = OFF,OSCIOFNC = ON
#pragma config FCKSM = CSECMD,WDTPS = PS1048576,WDTSPGM = STOP,WINDIS = NORMAL,FWDTEN = OFF,FWDTWINSZ = WINSZ_25
// DMTCNT = No Setting
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config EJTAGBEN = NORMAL,DBGPER = ALLOW_PG2,FSLEEP = OFF,FECCCON = OFF_UNLOCKED,BOOTISA = MIPS32,TRCEN = ON,DEBUG = ON
// DEVCP0
#pragma config CP = OFF

#pragma config ICESEL = ICS_PGx2

/////////////////////////////////////////////////////////////////////////////
// TouchScreen Init Values
/////////////////////////////////////////////////////////////////////////////

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************

//SYS_MODULE_OBJ   object, oSpiObject;
//DRV_PMP_INIT     init;
SYS_MSG_INSTANCE iSysMsg = SYS_MSG_0;
SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;
//DRV_HANDLE hSpiHandle;

void TouchMessageCallback(SYS_MSG_OBJECT *pMsg);

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
    /* Initializethe interrupt system  */
    SYS_INT_Initialize();

    /* Initialize the global interrupts */
    SYS_INT_Enable();

    SYS_MSG_MESSAGING_OBJECT oSysMsg;
    SYS_MSG_INIT sSysMsgInit;
    uint16_t nQSizes[] = SYS_MSG_BUFFER_SIZES;

    sSysMsgInit.nMaxMsgsDelivered  = SYS_MSG_MAX_MSGS_DELIVERED;
    sSysMsgInit.nMessagePriorities = SYS_MSG_MAX_PRIORITY+1;
    sSysMsgInit.nQSizes = nQSizes;

    hSysMsg = SYS_MSG_Initialize(iSysMsg,(SYS_OBJ_HANDLE)&sSysMsgInit);
    oSysMsg = *(SYS_MSG_MESSAGING_OBJECT *)hSysMsg;

    hMsgType = SYS_MSG_TypeCreate(iSysMsg, TYPE_TOUCHSCREEN , 0);
    hMailbox = SYS_MSB_MailboxOpen( iSysMsg, (SYS_MSG_RECEIVE_CALLBACK)&TouchMessageCallback );

    SYS_MSG_MailboxMsgAdd(hMailbox,hMsgType);

    /* Initialize the Application */
    APP_Initialize ( );

    // initialize the timer that manages the tick counter
    TickInit();

    /* Initialize the display driver */
    GFX_DRV_lcc_Initialize(0);   //Initialize the Graphics Driver

    while( handle != 0)
    {
        handle = GFX_DRV_lcc_Open(0);
    }

    /* Initialize the grahpics library */
    GFX_Initialize();
    
    // initialize the components for Touch Screen
    TouchInit(((void *)0), ((void *)0), ((void *)0), NULL);
    
    InitializeSchemes();

    StartScreen();
}

void TouchMessageCallback(SYS_MSG_OBJECT *pMsg)
{
    static GFX_GOL_MESSAGE gMsg;

    gMsg.type = pMsg->nMessageTypeID;
    gMsg.uiEvent = pMsg->param0;
    gMsg.param1 = pMsg->param1;
    gMsg.param2 = pMsg->param2;

    GFX_GOL_ObjectMessage(&gMsg);
}
/*******************************************************************************/
/*******************************************************************************
 End of File
*/
