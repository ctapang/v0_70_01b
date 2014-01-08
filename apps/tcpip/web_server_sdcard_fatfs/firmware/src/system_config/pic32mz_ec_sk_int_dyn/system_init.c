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
#include "hardware_config.h"
#include "system_config.h"
#include "driver/sdcard/drv_sdcard.h"
#include "driver/spi/drv_spi.h"
#include "tcpip/src/system/pic32mz_ports.h"
#include "tcpip/tcpip.h"


#include "tcpip/src/system/system_userio_private.h"
#include "system/clk/src/sys_clk_local.h"

// Device Configuration
// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN = OFF             // Ethernet RMII/MII Enable (RMII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_3         // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_8_16_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN   = OFF           // USB PLL Enable (USB PLL is disabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (SPLL)
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal enabled, otherwise HS mode doesn't work.
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
// DMTCNT = No Setting
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

// DEVCFG0
#pragma config DEBUG = ON              // Background Debugger Enable (Debugger is disabled)
//#pragma config DEBUG = OFF
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select
#pragma config TRCEN = ON               // Trace Enable (Trace features in the CPU are enabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
//#pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config DBGPER = PG_ALL
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)
//#pragma config JTAGEN = OFF

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
#pragma config_alt FWDTEN=OFF
#pragma config_alt USERID = 0x1234u

#if defined (HARMONY_TMR_PORTING)
SYS_MODULE_OBJ TimerObjectHandle;
SYS_MODULE_OBJ TimerDriverHandle;
SYS_TMR_INIT TimerInitConfig;

DRV_TMR_INIT   timerInit =
{
    .tmrId = TMR_ID,
    .timerPeriod = TIMER_PERIOD,
    .clockSource = TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK,
    .interruptSource = TMR_INT_SOURCE,
    .prescale = TMR_PRESCALE_VALUE_4,
    .postscale = TMR_POSTSCALE_NOT_SUPPORTED,
    .sourceEdge = TMR_CLOCK_SOURCE_EDGE_NONE,
    .moduleInit.value = SYS_MODULE_POWER_RUN_FULL,
};
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
DRV_SPI_INIT drvSPIInit =
{
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .spiId = SPI_ID_2,
    .spiMode = DRV_SPI_MODE_MASTER,
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,
    .baudRate = 100000,
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,
    .rxInterruptMode = 0,
    .txInterruptMode = 0,
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL,
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,
    .txInterruptSource = INT_SOURCE_SPI_2_TRANSMIT,
    .rxInterruptSource = INT_SOURCE_SPI_2_RECEIVE,
    .errInterruptSource = INT_SOURCE_SPI_2_ERROR,
};

DRV_SDCARD_INIT drvSDCARDInit =
{
    .writeProtectPort = PORT_CHANNEL_F,
    .writeProtectBitPosition = PORTS_BIT_POS_1,
    .cardDetectPort = PORT_CHANNEL_J,
    .cardDetectBitPosition = PORTS_BIT_POS_5,
    .chipSelectPort = PORT_CHANNEL_B,
    .chipSelectBitPosition = PORTS_BIT_POS_14,
    //.sdcardSpeedHz = 25000000,    // for very fast cards
    .sdcardSpeedHz = 20000000,    // for faster cards
    //.sdcardSpeedHz = 2000000,    // for not so fast cards
    .spiId = SPI_ID_2,
    //.devName = "mmcblka1"
};

const SYS_FS_REGISTRATION_TABLE sysFATFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = FAT,
        .nativeFileSystemFunctions = &FatFsFunctions
    }
};

extern void icache_init(void);
extern void dcache_init(void);
extern void cache_enable(unsigned int mode);

static void SetPic32MZIoPins(void)
{
    PORTSetPinsDigitalOut(_ETH_MDC_PORT, _ETH_MDC_BIT);
    PORTSetPinsDigitalIn(_ETH_MDIO_PORT, _ETH_MDIO_BIT);

    PORTSetPinsDigitalOut(_ETH_TXEN_PORT, _ETH_TXEN_BIT);
    PORTSetPinsDigitalOut(_ETH_TXD0_PORT, _ETH_TXD0_BIT);
    PORTSetPinsDigitalOut(_ETH_TXD1_PORT, _ETH_TXD1_BIT);


    PORTSetPinsDigitalIn(_ETH_RXCLK_PORT, _ETH_RXCLK_BIT);
    PORTSetPinsDigitalIn(_ETH_RXDV_PORT, _ETH_RXDV_BIT);
    PORTSetPinsDigitalIn(_ETH_RXD0_PORT, _ETH_RXD0_BIT);
    PORTSetPinsDigitalIn(_ETH_RXD1_PORT, _ETH_RXD1_BIT);
    PORTSetPinsDigitalIn(_ETH_RXERR_PORT, _ETH_RXERR_BIT);
}

// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************
/*******************************************************************************
  Function:
    void SYS_Initialize ( void *data )

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
void SYS_Initialize(void* data)
{
    BSP_Initialize();

    // cache configuration
    cache_enable(0);
    SetPic32MZIoPins();

    /* Initializethe interrupt system  */
    SYS_INT_Initialize();

    /* Remap the SPI pins */
    PLIB_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SDO2, OUTPUT_PIN_RPG8);
    PLIB_PORTS_RemapInput(PORTS_ID_0, INPUT_FUNC_SDI2, INPUT_PIN_RPD7);

     /* set priority for SPI interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2_TX, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2_RX, INT_PRIORITY_LEVEL3);

    /* set sub-priority for SPI interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2_TX, INT_SUBPRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2_RX, INT_SUBPRIORITY_LEVEL1);

    clkObject.systemClock = 200000000L;

    //Turn ON the system clock
    if(!SYS_TICK_Initialize(clkObject.systemClock, SYS_TICKS_PER_SECOND))
    {
        return;
    }

    SYS_INT_Enable();

    /* Initialize the clock system service. This is used
     * by the SPI Driver. */
    clkObject.MZperipheralClock[2] = 100000000L;
    clkObject.peripheralClock = 100000000L;
    
    /* Initialize the SPI driver */
    appDrvObjects.drvSPIObject = DRV_SPI_Initialize(DRV_SPI_INDEX_0,
            (SYS_MODULE_INIT *)&drvSPIInit);

    /* Initialize the SDCARD driver*/
    appDrvObjects.drvSDCARDObject = DRV_SDCARD_Initialize(DRV_SDCARD_INDEX_0,
            (SYS_MODULE_INIT *)&drvSDCARDInit);

    /* Initialize the SYS_FS Layer */
    SYS_FS_Initialize( (const void *) sysFATFSInit );
    
    if(!_SYS_DEBUG_INIT(SYS_DEBUG_PORT))
    {
        return;
    }

    if(!_SYS_CONSOLE_INIT(SYS_CONSOLE_PORT))
    {
        return;
    }

    if(!_SYS_RANDOM_INIT())
    {
        return;
    }

    if (!_SYS_COMMAND_INIT())
    {
        return;
    }

    if (!SYS_USERIO_Initialize(0))
    {
        return;
    }

    // TCP/IP stack initialization
    SYS_OUT_MESSAGE("TCPStack " TCPIP_STACK_VERSION "  ""                ");

    // Initialize the TCPIP stack
    if (!TCPIP_STACK_Init())
    {
       return;
    }

    APP_Initialize();

    return;

} //SYS_Initialize

/*******************************************************************************/
/*******************************************************************************
 End of File
*/

