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
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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
 Peripheral Clock Divisor (FPBDIV)              = Divide by 2
 */
/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
// DEVCFG3
// USERID = No Setting
#pragma config PMDL1WAY = OFF            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_5         // PLL Input Divider (2x Divider)
#pragma config FPLLMUL = MUL_16         // PLL Multiplier (20x Multiplier, with an overall result of 10x)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
// NOTE: It seems that for the simulator, no matter what FNOSC is set to, the simulator
// DEVCFG1 register always shows FNOSC = 0.
#pragma config FNOSC = PRIPLL           // Oscillator Selection Bits (Fast RC Osc w/ multipliers and dividers)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (External Clock)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_1           // Peripheral Clock Divisor (Pb_Clk == Sys_Clk / 2)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WISZ_25      // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config JTAGEN = OFF             // JTAG Enable (JTAG Port Disabled)
#pragma config ICESEL = ICS_PGx3        // ICE/ICD Comm Channel Select (Communicate on PGEC3/PGED3)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


/* Enable USB PLL */
#pragma config UPLLEN   = ON

/* USB PLL input devider */
#pragma config UPLLIDIV = DIV_6

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

uint8_t __attribute__((aligned(512))) endpointTable[USB_DEVICE_ENDPOINT_TABLE_SIZE];


// *****************************************************************************
/* USB Device layer Initialization Data

  Summary:
    Defines the device layer initialization data

  Description
    This structure defines the device layer's initialization data.

  Remarks:
    None.
*/

USB_DEVICE_INIT usbDevInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* USB device driver client index*/
    USB_ID_1, //DRV_USB_INDEX_0,

    false, // never stop USB

    false, // never suspend USB

    INT_SOURCE_USB_1,  // interrupt source (specific to PIC32MX250F128B)

    endpointTable,   // end point table

    1,    // registered func count

    /* Function driver table registered to this instance of the USB device layer*/
    (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,

    /* Pointer to USB Descriptor structure */
    (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor,

    USB_SPEED_FULL
};


// *****************************************************************************
/* USB controller driver Initialization Data

  Summary:
    Defines the USB controller driver Initialization Data

  Description
    This structure defines the USB controller driver Initialization Data.

  Remarks:
    None.
*/


SYS_MODULE_OBJ TimerObjectHandle;
SYS_MODULE_OBJ TimerDriverHandle;
SYS_TMR_INIT TimerInitConfig;

/*Timer load values. Values differ for each processor based on the clock settings*/
/*The given count values are valid only if the device config registers are
 programmed as shown below (see above for the system clock settings)*/
// Internal highspeed RC osc = 8MHz
// PLLIDIV = 2, Freq = 4MHz
// PLLMUL = 20, Freq = 80MHz
// PLLODIV = 2, Freq = 40MHz
// PBDIV = 1,   Freq = 40MHz
// TMR Module I/P = 40MHz
// TMR Prescaler = 1:8 = 5MHz
// TMR Prescaler = 1:256 = 156,250Hz
// TMR Step = 6.4uS/Count
#define APP_TMR_1S      0x0002625A

#define APP_TMR_500mS   0x0001312D


#define ONE_SECOND  5000000 // 156250
#define ONE_MILLISEC (ONE_SECOND/1000)

DRV_TMR_INIT   timerInit =
{
    .moduleInit.value = SYS_MODULE_POWER_RUN_FULL,
    .tmrId = TMR_ID_2,
    .clockSource = TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK,
    .timerPeriod = (ONE_SECOND >> 3), // changing this has NO effect
    .prescale = TMR_PRESCALE_VALUE_8,
    //.prescale = TMR_PRESCALE_VALUE_256,
    .sourceEdge = TMR_CLOCK_SOURCE_EDGE_NONE,
    .postscale = TMR_POSTSCALE_NOT_SUPPORTED,
    .syncMode = DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL,
    .interruptSource = INT_SOURCE_TIMER_3, // timer 2 and timer 3 are joined together
};

// "PRIVATE" methods

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

    For a static system (a system not using the Harmony's dynamic implementation
    of the initialization and "Tasks" services) this routine is implemented
    for the specific configuration of an application.
 */

bool TickInit();
void TimerHandler();

extern APP_DATA appObject;

void USB_Init()
{
    SYS_INT_VectorPrioritySet(INT_VECTOR_USB, INT_PRIORITY_LEVEL2);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_USB, INT_SUBPRIORITY_LEVEL2);

    //Initialize the USB device layer (this also calls DRV_USB_Initialize)
    appDrvObject.usbDevObject = USB_DEVICE_Initialize(  0, (SYS_MODULE_INIT *)&usbDevInitData  );

    /* check if the object returned by the device layer is valid */
    SYS_ASSERT((SYS_MODULE_OBJ_INVALID != appDrvObject.usbDevObject), "Invalid USB DEVICE object");

    /* open an instance of the device layer */
    appObject.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );

    /* Register a callback with device layer to get event notification (for end point 0) */
    USB_DEVICE_EventCallBackSet(appObject.usbDevHandle, &APP_USBDeviceEventHandler);

    USB_DEVICE_GENERIC_EventHandlerSet(USB_DEVICE_GENERIC_INDEX_0,
            &APP_USBDeviceGenericEventHandler, (uintptr_t) NULL);

    USB_DEVICE_Attach(appObject.usbDevHandle);
}

void SYS_Initialize ( void* data )
{
    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.

    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:*/

    SYSTEMConfigPerformance(SYS_FREQUENCY);

    /* Initialize the BSP (Power Supply Voltage and SPI pins and interrupts) */
    BSP_Initialize ( );

    // initialize the timer that manages the tick counter
    TickInit();

    //Interrupt initialize for multi-vectored ints
    SYS_INT_Initialize();

    /* Enable all defined interrupts */
    SYS_INT_Enable();

    USB_Init();

    // Disable interrrupts for now
    //SYS_INT_Disable();

    /* Initialize the Application */
    APP_Initialize ( );
}

bool TickInit()
{
    TimerInitConfig.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
    TimerInitConfig.drvIndex = DRV_TMR_INDEX_0;
    TimerInitConfig.alarmPeriod = 1; // this is fixed to 1 millisec (can't use any other value)

    clkObject.peripheralClock = SYS_FREQUENCY;

    TimerDriverHandle = DRV_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&timerInit);

    if (TimerDriverHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    TimerObjectHandle = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&TimerInitConfig);

    if (TimerObjectHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    // The first param must be a multiple of TimerInitConfig.alarmPeriod (see above).
    // Call the handler once every 1 second.
    TimerObjectHandle = SYS_TMR_CallbackPeriodic (1000, &TimerHandler);


     /* set priority for Timer 3 interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_T3, INT_PRIORITY_LEVEL5);

    /* set sub-priority for Timer 3 interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T3, INT_SUBPRIORITY_LEVEL3);

    //SYS_INT_SourceEnable(INT_SOURCE_TIMER_3);

    return true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

extern void BSP_SetVoltage(BSP_VOLTAGE delta);
extern void BSP_Toggle_Red_LED();

//int j = 0;

void TimerHandler(void)
{
    BSP_Toggle_Red_LED();
    //j++;
    //if (j > 32)
    //    j = 0;
    //BSP_SetVoltage((BSP_VOLTAGE)j);
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
