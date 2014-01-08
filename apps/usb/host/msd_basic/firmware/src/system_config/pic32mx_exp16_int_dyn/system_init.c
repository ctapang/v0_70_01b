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
/* Driver initialization data */
DRV_USB_INIT 	usbInitData;
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
// USB Embedded Host Targeted Peripheral List (TPL)
// *****************************************************************************


 USB_HOST_INIT    usbHostInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* USB host controller driver client index*/
    USB_HOST_INDEX_0,

    /* Number of host  drivers registered to this instance of the USB Host layer */
    3,

    USB_SPEED_FULL,
    /* Pointer to list of host available drivers information */
    //(USB_HOST_TARGET_PERIPHERAL_LIST *)USBTPList,
}; 



/* buffer used by the USB controller driver */
/* application needs to allocate space for this */
//uint8_t internalBuffer[DRV_USB_WORKING_BUFFER_SIZE(1,64)] __attribute__((aligned(512)));

//DRV_USB_HC_INIT  usbHCinitdata =
//{
//    /* System module initialization */
//    {SYS_MODULE_POWER_RUN_FULL},
//    /* Identifies peripheral (PLIB-level) ID */
//    USB_ID_1,
//    /* USB module setup */
//    {
//        /* USB module operating mode */
//        USB_OPMODE_HOST,
//        /* Buffer Ping Pong Mode */
//        USB_PING_PONG_FULL_PING_PONG,
//        /* stop in idle */
//        false,
//        /* suspend in sleep */
//        false,
//        /* OTG interrupts to be enabled */
//        USB_OTG_INT_BDEVICE_SESSION_END | USB_OTG_INT_SESSION_VALID | USB_OTG_INT_ID_STATE_CHANGE ,
//        /* General USB Interrupts to be enabled */
//        USB_INT_ALL & ~USB_INT_SOF,
//        /* USB Error Interrupts to be enabled */
//        USB_ERR_INT_ALL
//    },
//     /* Buffer needed by the driver for its operation */
//    HCinternalBuffer,
//
//    /* EP0 max size */
//    USB_EP0_BUFF_SIZE,
//
//    /* total number of end points */
//    1,
//
//    /* Interrupt Source for USB module */
//    INT_SOURCE_USB_1,
//};


// *****************************************************************************
/* USB Host layer Initialization Data

  Summary:
    Defines the host layer initialization data

  Description
    This structure defines the host layer's initialization data.

  Remarks:
    None.
*/






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
//    cache_status = CHECON;
//    cache_status |= (3 << _CHECON_PREFEN_POSITION);
//    CHECON = cache_status;
//    CheKseg0CacheOn();

    SYSTEMConfigPerformance(80000000);

    /* Initialize the BSP */
     BSP_Initialize( );

     //TODO
    /* Create the USB Driver Initialization
     * data structure */

    usbInitData.usbID = USB_ID_1;
    usbInitData.operationMode = USB_OPMODE_HOST;

    usbInitData.stopInIdle      = false;
    usbInitData.suspendInSleep   = false;

     usbInitData.interruptSource = INT_SOURCE_USB_1;
 

    SYS_INT_VectorPrioritySet( INT_VECTOR_USB, INT_PRIORITY_LEVEL4);
                           
   //  SYS_INT_PrioritySet( INT_VECTOR_T3, INT_PRIORITY_LEVEL5);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_USB, INT_SUBPRIORITY_LEVEL0);
     /* Initialize the USB Host controller driver */
     USBHostdemoappDrvObject.usbHCObject = DRV_USB_Initialize (DRV_USB_INDEX_0 ,
                                                    ( SYS_MODULE_INIT* ) &usbInitData);

    /* check if the object returned by the controller driver is valid */
     SYS_ASSERT((SYS_MODULE_OBJ_INVALID != USBHostdemoappDrvObject.usbHCObject), "Invalid USB HC object");
	
     /* Initialize the USB host layer */
     USBHostdemoappDrvObject.usbHostObject = USB_HOST_Initialize (USB_HOST_INDEX_0 ,
                                                     ( SYS_MODULE_INIT *)& usbHostInitData );
     /* check if the object returned by the device layer is valid */
    // SYS_ASSERT((SYS_MODULE_OBJ_INVALID != appDrvObject.usbHostObject), "Invalid USB HOST object");
    
    // /* open an instance of the device layer */
//     USBHostdemoappDrvObject.usbHostCDCHandle = USB_HOST_CDC_Open( USB_HOST_INDEX_0 );
    
    // /* Register a callback with device layer to get event notification (for end point 0) */
    // USB_DEVICE_EventCallBackSet(appData.usbDevHandle, APP_UsbDeviceEventCallBack);

    /* Initialize the Application */
    APP_Initialize ( );

    // /* /* Initializethe interrupt system  */
     SYS_INT_Initialize();
    
     // /* set priority for USB interrupt source */
     SYS_INT_VectorPrioritySet(INT_SOURCE_USB_1, INT_PRIORITY_LEVEL3);
    
    // /* set sub-priority for USB interrupt source */
     SYS_INT_VectorSubprioritySet(INT_SOURCE_USB_1, INT_SUBPRIORITY_LEVEL3);

    // /* Initialize the global interrupts */
     SYS_INT_Enable(); 
    
   
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
