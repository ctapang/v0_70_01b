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

APP_DRV_OBJECTS USBHostdemoappDrvObject;




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
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1

/*
 CLKO Output Signal Active on the OSCO Pin(OSCIOFNC)    = Enable
 Primary Oscillator Configuration(POSCMOD)              = External
 Secondary Oscillator Enable(FSOSCEN)                   = Enable
 Oscillator Selection Bits(FNOSC)                       = Primary osc with PLL
 */
#pragma config OSCIOFNC = ON, POSCMOD = HS, FSOSCEN = ON, FNOSC = PRIPLL

/* Enable USB PLL */
#pragma config UPLLEN   = ON

/* USB PLL input devider */
#pragma config UPLLIDIV = DIV_2

#pragma config ICESEL = ICS_PGx2


 // Allocate an endpoint table
    uint8_t __attribute__((aligned(512))) endpointTable[USB_HOST_ENDPOINT_TABLE_SIZE];

extern const USB_HOST_TARGET_PERIPHERAL_LIST USBTPList[1];
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
SYS_MODULE_OBJ usbHostObject=SYS_MODULE_OBJ_INVALID;
// *****************************************************************************
// *****************************************************************************
/* USB Host layer Initialization Data

  Summary:
    Defines the Host layer initialization data

  Description
    This structure defines the Host layer's initialization data.

  Remarks:
    None.
*/



 USB_HOST_INIT    usbHostInitData =
{
   /* System module initialization */
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},

     /* Identifies peripheral (PLIB-level) ID */
    .usbID = USB_ID_1,

    /* Identifies the Idle mode behavior. If true the USB module will stop when
       the microcontroller enter IDLE mode */
    .stopInIdle = false ,

    /* If true, the USB module will automatically suspend when the the
       microcontroller enter sleep mode */
    .suspendInSleep = false ,

    .endpointTable = endpointTable,
     /* Interrupt Source for USB module */
    .interruptSource = INT_SOURCE_USB_1,

    /* Number of entries in the TPL table */
    .nTPLEntries     = 2,

     /* USB Device Speed */
    .usbSpeed = USB_SPEED_FULL,

    .tplList = (USB_HOST_TARGET_PERIPHERAL_LIST * )USBTPList

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
    
    /* Set up cache and wait states for
     * maximum performance. */
    SYSTEMConfigPerformance(80000000);

    /* Initialize the BSP */
    BSP_Initialize( );

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

   // handle = USB_HOST_Open(USB_HOST_0, DRV_IO_INTENT_EXCLUSIVE);

   // USB_HOST_OperationEnable(handle);

    // Wait till host operation is enabled.
    //while(!USB_HOST_OperationIsEnabled(handle));
     
    USB_HOST_MSD_EventHandlerSet(USB_HOST_MSD_INDEX_0,
                                 &USB_HOST_MSD_ApplicationEventHandler);

    /* set priority for USB interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_USB, INT_PRIORITY_LEVEL3);

    /* set sub-priority for USB interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_USB, INT_SUBPRIORITY_LEVEL3);

    /* Initialize the global interrupts */
    SYS_INT_Enable();

       /* Initialize the SYS_FS Layer */
    SYS_FS_Initialize( (const void *) sysFSInit );

}



/******************* End of file ******************************* */
