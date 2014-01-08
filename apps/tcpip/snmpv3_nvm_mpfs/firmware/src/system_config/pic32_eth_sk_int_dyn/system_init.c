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
#if defined (SYS_FS_FILESYSTEM_MPFS)
#include "driver/nvm/drv_nvm.h"
#include "driver/nvm/drv_nvm_media.h"
#endif
#include "tcpip/src/system/pic32mz_ports.h"
#include "tcpip/tcpip.h"

#include "tcpip_stack_init.h"

#include "tcpip/src/system/system_userio_private.h"
#include "system/clk/sys_clk.h"
#include "tcpip/src/system/system_services_private.h"

// Device Configuration
// PIC32 ESK configuration fuses
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration

extern unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);
// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************
#if defined (SYS_FS_FILESYSTEM_MPFS)
const DRV_NVM_INIT drvNVMInit =
{
    .nvmID = NVM_ID_0,
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .interruptSource = INT_SOURCE_FLASH_CONTROL,
};

const DRV_NVM_MEDIA_INIT drvNVMMediaInit =
{
    .mediaStartAddress = (uintptr_t)MPFS_IMAGE_DATA,
    .nSectors = 16,
    .sectorSizeInBytes = 512,
    .drvNVMIndex = DRV_NVM_INDEX_0,
};

const SYS_FS_REGISTRATION_TABLE sysMPFSInit [ SYS_FS_MAX_FILE_SYSTEM_TYPE ] =
{
    {
        .nativeFileSystemType = MPFS2,
        .nativeFileSystemFunctions = &MPFSFunctions
    }
};
#endif //defined (SYS_FS_FILESYSTEM_MPFS)

const SYS_CLK_INIT sysCLKInit =
{
    .systemClockSource = SYS_CLK_SOURCE_PRIMARY,
    .systemClockFrequency = 80000000,
    .peripheralClockEnable = true,
    .peripheralClockSource = SYS_CLK_SOURCE_SYSCLK_OUT,
    .peripheralClockFrequency = 40000000
};

static void SetPic32MXIoPins(void)
{
        PORTSetPinsDigitalOut(_ETH_ALT_MDC_PORT, _ETH_ALT_MDC_BIT);
        PORTSetPinsDigitalIn(_ETH_ALT_MDIO_PORT, _ETH_ALT_MDIO_BIT);

        PORTSetPinsDigitalOut(_ETH_ALT_TXEN_PORT, _ETH_ALT_TXEN_BIT);
        PORTSetPinsDigitalOut(_ETH_ALT_TXD0_PORT, _ETH_ALT_TXD0_BIT);
        PORTSetPinsDigitalOut(_ETH_ALT_TXD1_PORT, _ETH_ALT_TXD1_BIT);


        PORTSetPinsDigitalIn(_ETH_ALT_RXCLK_PORT, _ETH_ALT_RXCLK_BIT);
        PORTSetPinsDigitalIn(_ETH_ALT_RXDV_PORT, _ETH_ALT_RXDV_BIT);
        PORTSetPinsDigitalIn(_ETH_ALT_RXD0_PORT, _ETH_ALT_RXD0_BIT);
        PORTSetPinsDigitalIn(_ETH_ALT_RXD1_PORT, _ETH_ALT_RXD1_BIT);
        PORTSetPinsDigitalIn(_ETH_ALT_RXERR_PORT, _ETH_ALT_RXERR_BIT);
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
    /* Set up cache and wait states for
     * maximum performance. */
    SYSTEMConfigPerformance(80000000);

    BSP_Initialize();
    
    SetPic32MXIoPins();

    /* Initializethe interrupt system  */
    SYS_INT_Initialize();

    /* Initialize the clock system service. This is used
     * by the SPI Driver. */
    SYS_CLK_Initialize(&sysCLKInit);

    clkObject.systemClock = 80000000L;

    //Turn ON the system clock
    if(!SYS_TICK_Initialize(clkObject.systemClock, SYS_TICKS_PER_SECOND))
    {
        return;
    }

    SYS_INT_Enable();

#if defined (SYS_FS_ENABLE)
#if defined (SYS_FS_FILESYSTEM_MPFS)
    /* Initialize the NVM driver */
    appDrvObjects.drvNVMObject = DRV_NVM_Initialize(DRV_NVM_INDEX_0,
            (SYS_MODULE_INIT *)&drvNVMInit);

    appDrvObjects.drvNVMMediaObject = DRV_NVM_MEDIA_Initialize(DRV_NVM_MEDIA_INDEX_0,
            (SYS_MODULE_INIT *)&drvNVMMediaInit);
    /* Initialize the SYS_FS Layer */
    SYS_FS_Initialize( (const void *) sysMPFSInit );
#endif //defined (SYS_FS_FILESYSTEM_MPFS)
#endif
#if defined(SYS_DEBUG_ENABLE)
    if(!_SYS_DEBUG_INIT(SYS_DEBUG_PORT))
    {
        return;
    }
#endif

#if defined(SYS_CONSOLE_ENABLE)
    if(!_SYS_CONSOLE_INIT(SYS_CONSOLE_PORT))
    {
        return;
    }
#endif

#if defined (SYS_RANDOM_ENABLE)
    if(!_SYS_RANDOM_INIT())
    {
        return;
    }
#endif

#if defined(SYS_COMMAND_ENABLE)
    if (!_SYS_COMMAND_INIT())
    {
        return;
    }
#endif

#if defined(SYS_USERIO_ENABLE)
    if (!SYS_USERIO_Initialize(0))
    {
        return;
    }
#endif

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

