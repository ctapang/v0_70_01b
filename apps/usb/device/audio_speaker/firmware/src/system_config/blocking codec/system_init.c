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

#include "app_MEB2.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
/* Set up the Device Configuration */
// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN   = OFF              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO   = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY  = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON           // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY  = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3         //3 System PLL Input Divider (1x Divider)
#pragma config FPLLRNG  = RANGE_8_16_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_50       //50 System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN   = ON              // USB PLL Enable (USB PLL is enabled)

// DEVCFG1
#pragma config FNOSC    = SPLL             // Oscillator Selection Bits (SPLL)
#pragma config DMTINTV  = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN  = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO     = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD  = EC             // Primary Oscillator Configuration (Primary osc enabled)
#pragma config OSCIOFNC = ON           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM    = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS    = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM  = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS   = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN   = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
// DMTCNT = No Setting
#pragma config FDMTEN   = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

/* DEVCFG0 */
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER   = PG_ALL
#pragma config FSLEEP   = OFF
#pragma config FECCCON  = OFF_UNLOCKED
#pragma config BOOTISA  = MIPS32
#pragma config TRCEN    = OFF
#pragma config ICESEL   = ICS_PGx2
#pragma config JTAGEN   = OFF
#pragma config DEBUG    = ON

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)



// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

SYS_MODULE_OBJ usbDevObject = SYS_MODULE_OBJ_INVALID;
SYS_MODULE_OBJ drvAudioCodecObject =  SYS_MODULE_OBJ_INVALID; 


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
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_ID_0,

    /* Stop in idle */
    .stopInIdle = false,

     /* Stop in sleep */
    .suspendInSleep = false,

    /* Interrupt source */
    .interruptSource =INT_SOURCE_USB_1,

    /* Number of function drivers registered to this instance of the
    USB device layer */
    .registeredFuncCount =  1,

    /* Function driver table registered to this instance of the USB device layer*/
    .registeredFunctions = (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,

    /* Pointer to USB Descriptor structure */
    .usbMasterDescriptor = (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor,

    .deviceSpeed = USB_SPEED_FULL
};



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

void SYS_Initialize ( void* data )
{
    
    /* Initialize the BSP */
    BSP_Initialize( );

     /* Initialize the USB device layer */
    usbDevObject = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 ,
                                                    ( SYS_MODULE_INIT* ) & usbDevInitData);

     /* check if the object returned by the device layer is valid */
    SYS_ASSERT((SYS_MODULE_OBJ_INVALID != usbDevObject), "Invalid USB DEVICE object");

   

	/* Initializethe interrupt system  */
    SYS_INT_Initialize();
	
    
     /* set priority for USB interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_USB, INT_PRIORITY_LEVEL3);

    /* set sub-priority for USB interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_USB, INT_SUBPRIORITY_LEVEL3);

    /* Initialize the global interrupts */
    SYS_INT_Enable();
   
    /* open an instance of the device layer */
    appData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );

    if(appData.usbDevHandle == USB_DEVICE_HANDLE_INVALID)
    {
        SYS_ASSERT(false, "Could not open device layer");
        appData.state = APP_STATE_ERROR;    
    }
    
    /* Register a callback with device layer to get event notification (for end point 0) */
    USB_DEVICE_EventCallBackSet(appData.usbDevHandle, APP_UsbDeviceEventCallBack);

    USB_DEVICE_Attach(appData.usbDevHandle);

}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
