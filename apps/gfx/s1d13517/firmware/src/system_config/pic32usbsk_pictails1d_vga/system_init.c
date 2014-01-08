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

/*
 System PLL Output Clock Divider (FPLLODIV)     = Divide by 1
 PLL Multiplier (FPLLMUL)                       = Multiply by 20
 PLL Input Divider (FPLLIDIV)                   = Divide by 2
 Watchdog Timer Enable (FWDTEN)                 = Disabled
 Clock Switching and Monitor Selection (FCKSM)  = Clock Switch Enable,
                                                  Fail Safe Clock Monitoring Enable
 Peripheral Clock Divisor (FPBDIV)              = Divide by 1
 */
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_2

/*
 CLKO Output Signal Active on the OSCO Pin(OSCIOFNC)    = Enable
 Primary Oscillator Configuration(POSCMOD)              = External
 Secondary Oscillator Enable(FSOSCEN)                   = Enable
 Oscillator Selection Bits(FNOSC)                       = Primary osc with PLL
 */
#pragma config OSCIOFNC = ON, POSCMOD = HS, FSOSCEN = ON, FNOSC = PRIPLL

#pragma config ICESEL = ICS_PGx2

void CheKseg0CacheOn(void);

#define GFX_DEFAULT_FOREGROUND_PAGE	GFX_PAGE9
#define GFX_DEFAULT_BACKGROUND_PAGE 	GFX_PAGE10
#define GFX_DEFAULT_DESTINATION_PAGE 	GFX_PAGE4

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

SYS_MODULE_OBJ   object;
DRV_PMP_INIT     init;
DRV_SPI_INIT     SPI_Init_Data;
SYS_MSG_INSTANCE iSysMsg = SYS_MSG_0;
SYS_OBJ_HANDLE hSysMsg, hMsgType, hMailbox;

void TouchMessageCallback(SYS_MSG_OBJECT *pMsg);

void SYS_Initialize ( void* data )
{
   unsigned int cache_status;

   /////////////////////////////////////////////////////////////////////////////
   // ADC Explorer 16 Development Board Errata (work around 2)
   // RB15 should be output
   /////////////////////////////////////////////////////////////////////////////
    LATBbits.LATB15 = 0;
    TRISBbits.TRISB15 = 0;

/* enable cache */
    SYSTEMConfigPerformance(80000000);

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

    // populate the PMP init configuration structure
    init.polarity.addressLatchPolarity = PMP_POLARITY_ACTIVE_HIGH;
    init.polarity.rwStrobePolarity = PMP_POLARITY_ACTIVE_LOW;
    init.polarity.writeEnableStrobePolarity = PMP_POLARITY_ACTIVE_LOW;
    init.polarity.chipselect1Polarity = PMP_POLARITY_ACTIVE_HIGH;
    init.polarity.chipselect2Polarity = PMP_POLARITY_ACTIVE_LOW;
    init.ports.readWriteStrobe = PORT_ENABLE;
    init.ports.writeEnableStrobe = PORT_ENABLE;
    init.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
    init.pmpID            = PMP_ID_0;
    init.stopInIdle       = false;
    init.muxMode          = PMP_MUX_NONE;

    object = DRV_PMP_Initialize (DRV_PMP_INDEX_0, (SYS_MODULE_INIT *)&init);

    /* Initialize the Application */
    APP_Initialize ( );

    /////////////////////////////////////////////////////////////////////////////
    //                  DRIVER SPECIFIC INITIALIZATION DATA
    /////////////////////////////////////////////////////////////////////////////

    GFX_DRV_S1D13517_Initialize(0); //Initialize the Graphics Driver

    SPI_Init_Data.spiId = SST25_SPI_CHANNEL;
    SPI_Init_Data.spiMode = DRV_SPI_MODE_MASTER;
    SPI_Init_Data.spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD;
    SPI_Init_Data.commWidth = SPI_COMMUNICATION_WIDTH_8BITS;
    SPI_Init_Data.baudRate = 1;
    SPI_Init_Data.bufferType = DRV_SPI_BUFFER_TYPE_STANDARD;
    SPI_Init_Data.clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE;
    SPI_Init_Data.inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END;

    DRV_SPI_Init(SST25_SPI_CHANNEL, &SPI_Init_Data);

    // initialize the Flash Memory driver
    SST25Init(&SPI_Init_Data);

    // initialize the timer that manages the tick counter
    TickInit();

    while (GFX_DRV_S1D13517_Open(0) != 0);

    GFX_Initialize();

    // initialize the components for Resistive Touch Screen
    TouchInit(&SST25WriteWord, &SST25ReadWord, &SST25SectorErase, NULL);

    ImageDecoderInit();

    JPEGInit();                  // Initialize JPEG

    while(GFX_PageSet(BACKGROUND_PAGE, GFX_DEFAULT_BACKGROUND_PAGE) == GFX_STATUS_FAILURE);
    while(GFX_PageSet(TRANSITION_PAGE, GFX_PAGE5) == GFX_STATUS_FAILURE);

    GFX_SchemeInit();

    GFX_ColorSet(WHITE);
    while(GFX_ScreenClear() == GFX_STATUS_FAILURE);
    while(GFX_DoubleBufferEnable() == GFX_STATUS_FAILURE);
    
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
