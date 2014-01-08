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
#include "nvm_disk_images.h"


/* Set up the Device Configuration */
// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN = ON              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = OFF            // Permission Group Lock One Way Configuration (Allow multiple reconfigurations)
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow multiple reconfigurations)
#pragma config IOL1WAY = OFF            // Peripheral Pin Select Configuration (Allow multiple reconfigurations)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3
#pragma config FPLLRNG = RANGE_8_16_MHZ
#pragma config FPLLICLK = PLL_POSC
#pragma config FPLLMULT = MUL_50
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ
#pragma config UPLLEN = ON

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (System PLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = EC            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
// DMTCNT = No Setting
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

/* DEVCFG0 */
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER = PG_ALL
#pragma config FSLEEP = OFF
#pragma config FECCCON = OFF_UNLOCKED
#pragma config BOOTISA = MIPS32
#pragma config TRCEN = OFF
#pragma config ICESEL = ICS_PGx2
//#pragma config JTAGEN = OFF
#pragma config DEBUG = OFF

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

const DRV_SPI_INIT drvSPIInit =
{
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .spiId = SPI_ID_2,
    .spiMode = DRV_SPI_MODE_MASTER,
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,
    .baudRate = 10000,
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,
    .rxInterruptMode = 0,
    .txInterruptMode = 0,
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL,
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,
    .txInterruptSource = INT_SOURCE_SPI_2_TRANSMIT,
    .rxInterruptSource = INT_SOURCE_SPI_2_RECEIVE,
    .errInterruptSource = INT_SOURCE_SPI_2_ERROR,
};

const DRV_SDCARD_INIT drvSDCARDInit =
{
    .writeProtectPort = PORT_CHANNEL_F,
    .writeProtectBitPosition = PORTS_BIT_POS_1,
    .cardDetectPort = PORT_CHANNEL_J,
    .cardDetectBitPosition = PORTS_BIT_POS_5,
    .chipSelectPort = PORT_CHANNEL_B,
    .chipSelectBitPosition = PORTS_BIT_POS_14,
    .sdcardSpeedHz = 20000000,
    .spiId = SPI_ID_2,
};

const DRV_NVM_INIT drvNVMInit =
{
    .nvmID = NVM_ID_0,
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .interruptSource = INT_SOURCE_FLASH_CONTROL,
};

const DRV_NVM_MEDIA_INIT drvNVMMediaInit =
{
    .mediaStartAddress = (uintptr_t)masterBootRecord,
    .nSectors = 16,
    .sectorSizeInBytes = 512,
    .drvNVMIndex = DRV_NVM_INDEX_0,
};

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

     /* Initializethe interrupt system  */
    SYS_INT_Initialize();
	
    /* Remap the SPI pins */
    SYS_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SDO2, OUTPUT_PIN_RPG8);
    SYS_PORTS_RemapInput(PORTS_ID_0, INPUT_FUNC_SDI2, INPUT_PIN_RPD7);

    /* set priority for SPI interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2_TX, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2_RX, INT_PRIORITY_LEVEL3);

    /* set sub-priority for SPI interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2_TX, INT_SUBPRIORITY_LEVEL3);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2_RX, INT_SUBPRIORITY_LEVEL3);

    /* set priority for NVM interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_FLASH, INT_PRIORITY_LEVEL3);
    /* set sub priority priority for NVM interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_FLASH, INT_SUBPRIORITY_LEVEL3);

    /* Initialize the global interrupts */
    SYS_INT_Enable();

    /* Initialize the SPI driver */
    appDrvObjects.drvSPIObject = DRV_SPI_Initialize(DRV_SPI_INDEX_0,
            (SYS_MODULE_INIT *)&drvSPIInit);

    /* Initialize the SDCARD driver*/
    appDrvObjects.drvSDCARDObject = DRV_SDCARD_Initialize(DRV_SDCARD_INDEX_0,
            (SYS_MODULE_INIT *)&drvSDCARDInit);

     /* Initialize the NVM driver */
    appDrvObjects.drvNVMObject = DRV_NVM_Initialize(DRV_NVM_INDEX_0,
            (SYS_MODULE_INIT *)&drvNVMInit);

    appDrvObjects.drvNVMMediaObject = DRV_NVM_MEDIA_Initialize(DRV_NVM_MEDIA_INDEX_0,
            (SYS_MODULE_INIT *)&drvNVMMediaInit);

    /* Initialize the SYS_FS Layer */
    SYS_FS_Initialize( (const void *) sysFSInit );
    
    /* Initialize the Application */
    APP_Initialize ( );
   
   
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
