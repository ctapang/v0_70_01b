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

void TouchMessageCallback(SYS_MSG_OBJECT *pMsg);

// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = OFF, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF

#pragma config ICESEL = ICS_PGx2

void CheKseg0CacheOn(void);

/////////////////////////////////////////////////////////////////////////////
// TouchScreen Init Values
/////////////////////////////////////////////////////////////////////////////
#ifdef USE_TOUCHSCREEN_RESISTIVE
#define TOUCH_INIT_VALUES   (NULL)
#endif

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

SYS_MODULE_OBJ   object, oSpiObject;
DRV_SPI_INIT     SPI_Init_Data;
SYS_MSG_INSTANCE iSysMsg = SYS_MSG_0;
SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;
DRV_SPI_CLIENT_SETUP cSpiCommConfig;
DRV_HANDLE hSpiHandle;

void SYS_Initialize ( void* data )
{

    #if defined(__PIC32MX__)
    SYSTEMConfigPerformance(80000000);
    #endif

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

    /////////////////////////////////////////////////////////////////////////////
    //                  DRIVER SPECIFIC INITIALIZATION DATA
    /////////////////////////////////////////////////////////////////////////////
    #if !defined(GUI_DEV_BOARD)
    SPI_Init_Data.moduleInit.value   = SYS_MODULE_POWER_RUN_FULL;
    SPI_Init_Data.spiId              = SST25_SPI_CHANNEL;
    SPI_Init_Data.spiMode            = DRV_SPI_MODE_MASTER;
    SPI_Init_Data.spiProtocolType    = DRV_SPI_PROTOCOL_TYPE_STANDARD;
    SPI_Init_Data.commWidth          = SPI_COMMUNICATION_WIDTH_8BITS;
    SPI_Init_Data.baudRate           = 1;
    SPI_Init_Data.bufferType         = DRV_SPI_BUFFER_TYPE_STANDARD;
    SPI_Init_Data.clockMode          = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL;
    SPI_Init_Data.inputSamplePhase   = SPI_INPUT_SAMPLING_PHASE_AT_END;
    SPI_Init_Data.txInterruptSource  = INT_SOURCE_SPI_2_TRANSMIT; // INT_SOURCE_SPI_1_EVENT
    SPI_Init_Data.rxInterruptSource  = INT_SOURCE_SPI_2_RECEIVE;  // INT_SOURCE_SPI_1_EVENT
    SPI_Init_Data.errInterruptSource = INT_SOURCE_SPI_2_ERROR;

    hSpiHandle = DRV_SPI_Open( DRV_SPI_INDEX_0,
                         DRV_IO_INTENT_READ|DRV_IO_INTENT_WRITE|DRV_IO_INTENT_BLOCKING);

    cSpiCommConfig.baudRate         = 1;
    cSpiCommConfig.inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END;
    cSpiCommConfig.clockMode        = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL;

    DRV_SPI_ClientSetup( hSpiHandle, &cSpiCommConfig );

    oSpiObject = DRV_SPI_Initialize( DRV_SPI_INDEX_0, (SYS_MODULE_INIT*)&SPI_Init_Data );

    if( SYS_MODULE_OBJ_INVALID == oSpiObject )
    {
        // Handle error
    }

    // initialize the Flash Memory driver
    SST25Init(&SPI_Init_Data);
    #endif

    // initialize the timer that manages the tick counter
    TickInit();

    /////////////////////////////////////////////////////////////////////////////
    //                  DRIVER SPECIFIC INITIALIZATION DATA
    /////////////////////////////////////////////////////////////////////////////

    GFX_DRV_lcc_Initialize(0); //Initialize the Graphics Driver

    while (handle != 0)
    {
        handle = GFX_DRV_lcc_Open(0);
    }

    GFX_Initialize();

    // initialize the components for Resistive Touch Screen
    TouchInit(&SST25WriteWord, &SST25ReadWord, &SST25SectorErase, NULL);

    ImageDecoderInit();

    JPEGInit();                  // Initialize JPEG

    /* Initialize the Application */
    APP_Initialize ( );
    
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
