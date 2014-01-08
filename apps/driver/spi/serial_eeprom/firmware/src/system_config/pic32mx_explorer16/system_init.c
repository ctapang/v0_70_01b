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

#include "system_config.h"
#include "system_definitions.h"
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
// TODO configure the correct confiugraiton fuse settings for your part
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF
#pragma config ICESEL = ICS_PGx2


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* SPI Driver Initialization Data

  Summary:
    Defines the SPI driver's initialization data

  Description
    This structure defines the SPI driver's initialization data, passed into
    the driver's initialization routine ("DRV_SPI_Initialize") by the
    system's ("SYS_Initialize") routine.

  Remarks:
    None.
*/

DRV_SPI_INIT drvSPIInit =
{
    /* Requested power state */
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,

    /* Identifies USART hardware module (PLIB-level) ID */
    .spiId = SPI_ID_2,

    /* Operation Modes of the SPI driver */
    .spiMode = DRV_SPI_MODE_MASTER,

    /* SPI Protocol Type */
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,

    /* SPI Communication Width */
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,

    /* SPI Baud Rate Value */
    .baudRate = 10000000,

    /* SPI Buffer Type */
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,

    /* FIFO RX Interrupt Mode */
    .rxInterruptMode = SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY,

    /* FIFO TX Interrupt Mode */
    .txInterruptMode = SPI_FIFO_INTERRUPT_WHEN_TRANSMISSION_IS_COMPLETE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_FALL,

    /* SPI Input Sample Phase Selection */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,

    /* Transmit Interrupt Source for SPI module */
    .txInterruptSource = INT_SOURCE_SPI_2_TRANSMIT,

    /* Receive Interrupt Source for SPI module */
    .rxInterruptSource = INT_SOURCE_SPI_2_RECEIVE,

    /* Error Interrupt Source for SPI module */
    .errInterruptSource = INT_SOURCE_SPI_2_ERROR,
};

// *****************************************************************************
// *****************************************************************************
// Section: System Service Initialization Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************

SYS_CLK_INIT sysCLKInit =
{
    //.systemClockSource = SYS_CLK_SOURCE_PRIMARY,
    .systemClockSource = SYS_CLK_SOURCE_LPRC,
    .systemClockFrequency = 80000000,
    .peripheralClockEnable = true,
    .peripheralClockSource = SYS_CLK_SOURCE_SYSCLK_OUT,
    //.peripheralClockSource = SYS_CLK_SOURCE_FRC_BY_16,
    .peripheralClockFrequency = 80000000
};

// *****************************************************************************
// *****************************************************************************
// Section: System Data
// *****************************************************************************
// *****************************************************************************

/* Structure to hold the sample application's system data. */
/* Inialize the system */

SYS_STATUS drvSPI2Status;

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
    /* Set up cache and wait states for maximum performance. */
    SYSTEMConfigPerformance(80000000);

    /* Initializethe interrupt system  */
    SYS_INT_Initialize();

    /* set priority for SPI interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2, INT_PRIORITY_LEVEL3);

    /* set sub-priority for SPI interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2, INT_SUBPRIORITY_LEVEL3);

    /* Initialize the global interrupts */
    SYS_INT_Enable();

    /* Initialize the SPI Driver */
    appData.drvSPIObject = DRV_SPI_Initialize( DRV_SPI_INDEX_0,
                    (SYS_MODULE_INIT *)&drvSPIInit );

    /* Initialize the clock system service. This is used  by the SPI Driver. */
    SYS_CLK_Initialize(&sysCLKInit);

    /* Status of SPI2 driver*/
    drvSPI2Status = DRV_SPI_Status(appData.drvSPIObject);

    /* Halt the system if SPI driver is not initialized properly*/
    if(drvSPI2Status != SYS_STATUS_READY)
    {
        while(1);
    }

    /* Initialize the Application */
    APP_Initialize ( );
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
