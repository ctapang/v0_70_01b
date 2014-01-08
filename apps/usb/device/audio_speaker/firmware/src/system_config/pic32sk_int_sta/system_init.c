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


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


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
    DRV_USB_INDEX_0,

    /* Number of function drivers registered to this instance of the
    USB device layer */
    1,

    /* Function driver table registered to this instance of the USB device layer*/
    (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,

    /* Pointer to USB Descriptor structure */
    (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor
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

DRV_USB_INIT usbCDInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* Identifies peripheral (PLIB-level) ID */
    USB_ID_1,

    /* USB module setup */
    {
        /* USB module operating mode */
        USB_OPMODE_DEVICE,

        /* Buffer Ping Pong Mode */
        USB_PING_PONG_NO_PING_PONG,

        /* stop in idle */
        false,

        /* suspend in sleep */
        false,
        
        /* OTG interrupts to be enabled */
        ~USB_OTG_INT_ALL,
        
        /* General USB Interrupts to be enabled */
        USB_INT_ALL & ~USB_INT_SOF,
        
        /* USB Error Interrupts to be enabled */
        USB_ERR_INT_ALL

    },

    /* Interrupt Source for USB module */
    INT_SOURCE_USB_1
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
	unsigned int cache_status;
    
   /* enable cache */
    cache_status = CHECON;
    cache_status |= (3 << _CHECON_PREFEN_POSITION);
    CHECON = cache_status;
    CheKseg0CacheOn();
    
    /* Initialize the BSP */
    BSP_Initialize( );

    /* Initialize the USB Controller driver */
    appDrvObject.usbCDObject = DRV_USB_Initialize (DRV_USB_INDEX_0 ,
                                                   ( SYS_MODULE_INIT* ) & usbCDInitData);

    /* check if the object returned by the controller driver is valid */
    SYS_ASSERT((SYS_MODULE_OBJ_INVALID != appDrvObject.usbCDObject), "Invalid USB CD object");
	
     /* Initialize the USB device layer */
	appDrvObject.usbDevObject = USB_DEVICE_Initialize (USB_DEVICE_INDEX_0 ,
                                                    ( SYS_MODULE_INIT* ) & usbDevInitData);
    
    /* check if the object returned by the device layer is valid */
    SYS_ASSERT((SYS_MODULE_OBJ_INVALID != appDrvObject.usbDevObject), "Invalid USB DEVICE object");
    
    /* open an instance of the device layer */
    appData.usbDevHandle = USB_DEVICE_Open( USB_DEVICE_INDEX_0, DRV_IO_INTENT_READWRITE );
    
    /* Register a callback with device layer to get event notification (for end point 0) */
    USB_DEVICE_EventCallBackSet(appData.usbDevHandle, APP_UsbDeviceEventCallBack);

    /* Initialize the Application */
    APP_Initialize ( );

    /* Initializethe interrupt system  */
    SYS_INT_Initialize();
    
     /* set priority for USB interrupt source */
    SYS_INT_PrioritySet(INT_SOURCE_USB_1, INT_PRIORITY_LEVEL3);
    
    /* set sub-priority for USB interrupt source */
    SYS_INT_SubprioritySet(INT_SOURCE_USB_1, INT_SUBPRIORITY_LEVEL3);

    /* Initialize the global interrupts */
    SYS_INT_Enable();
    
   
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
