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

#include "app.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************
/* Set up the Device Configuration */
// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN   = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO   = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY  = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON           // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY  = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3         //3 System PLL Input Divider (1x Divider)
#pragma config FPLLRNG  = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
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
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM    = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS    = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM  = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS   = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN   = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
// DMTCNT = No Setting
#pragma config FDMTEN   = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

/* DEVCFG0 */
#pragma config DEBUG = ON               // Background Debugger Enable (Debugger is enabled)
#pragma config JTAGEN = ON              // JTAG Enable (JTAG Disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config TRCEN = OFF              // Trace Enable (Trace features in the CPU are disabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)


// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************

/******************************************************************************
 * USB Embedded Host Targeted Peripheral List (TPL)
 * and USB Host Layer System Module Object.
 *****************************************************************************/

extern const USB_HOST_TARGET_PERIPHERAL_LIST USBTPList[];
SYS_MODULE_OBJ usbHostObject=SYS_MODULE_OBJ_INVALID;
// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
extern APP_DATA appData;
void BSP_VBUSSwitchEnable(void);
// *****************************************************************************
/******************************************************************************
 * USB Embedded Host Layer Initialization data.
 *****************************************************************************/

 USB_HOST_INIT    usbHostInitData =
{
   /* System module initialization */
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},

     /* Identifies peripheral (PLIB-level) ID */
    .usbID = USBHS_ID_0,

    /* Identifies the Idle mode behavior. If true the USB module will stop when
       the microcontroller enter IDLE mode */
    .stopInIdle = false ,

    /* If true, the USB module will automatically suspend when the the
       microcontroller enter sleep mode */
    .suspendInSleep = false ,

    .endpointTable = NULL,
    
     /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB_1,

    /* Number of entries in the TPL table */
    .nTPLEntries     = 1,

     /* USB Device Speed */
    .usbSpeed = USB_SPEED_HIGH,

    .tplList = (USB_HOST_TARGET_PERIPHERAL_LIST *)(USBTPList)

};

/* Initialization structure for sys_fs layer */
const SYS_FS_REGISTRATION_TABLE sysFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = FAT,
        .nativeFileSystemFunctions = &FatFsFunctions
    }

};

// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************
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

void SYS_Initialize ( void* data )
{
 
     /* Initialize the BSP */
    BSP_Initialize( );

 /* Enable the VBUS switch */
    BSP_VBUSSwitchEnable();     /* Enable the VBUS switch */


    /* Initialize the USB host layer */
    usbHostObject = USB_HOST_Initialize (USB_HOST_0 ,
                                        ( SYS_MODULE_INIT *)& usbHostInitData );

     /* check if the object returned by the device layer is valid */
    SYS_ASSERT((SYS_MODULE_OBJ_INVALID != usbHostObject),
                                          "Invalid USB HOST object");

    /* Initialize the Application */
    APP_Initialize (&appData );

    /* Initializethe interrupt system  */
    SYS_INT_Initialize();

   /* Register the application event handler with CDC Class driver */
    USB_HOST_MSD_EventHandlerSet(USB_HOST_MSD_INDEX_0,
                                 &USB_HOST_MSD_ApplicationEventHandler);

     /* Set the interrupt vector priority for USB and Timer 2 interrupt */
     SYS_INT_VectorPrioritySet(INT_VECTOR_USB, INT_PRIORITY_LEVEL4);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_USB, INT_SUBPRIORITY_LEVEL0);
    SYS_INT_VectorPrioritySet(INT_VECTOR_T2, INT_PRIORITY_LEVEL4 );
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T2, INT_SUBPRIORITY_LEVEL0);

    /* Initialize the global interrupts */
    SYS_INT_Enable();

       /* Initialize the SYS_FS Layer */
    SYS_FS_Initialize( (const void *) sysFSInit );

}



/************************  End of File ***************************/
