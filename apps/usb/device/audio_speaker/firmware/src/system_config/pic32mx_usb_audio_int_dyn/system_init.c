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
//#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
//#pragma config OSCIOFNC = ON, POSCMOD = HS, FSOSCEN = ON, FNOSC = PRIPLL
///* Enable USB PLL */
//#pragma config UPLLEN   = ON
///* USB PLL input devider */
//#pragma config UPLLIDIV = DIV_2
//#pragma config ICESEL = ICS_PGx2

 /** CONFIGURATION **************************************************/
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_3, FPLLODIV = DIV_2
#pragma config POSCMOD = EC, FNOSC = PRIPLL, FPBDIV = DIV_1, FSOSCEN = OFF
#pragma config UPLLEN = ON, UPLLIDIV = DIV_3, FVBUSONIO = OFF, FUSBIDIO = OFF
#pragma config FWDTEN = OFF, JTAGEN = OFF
#pragma config IESO = OFF, IOL1WAY = ON, PMDL1WAY = ON, OSCIOFNC = OFF
#pragma config ICESEL = ICS_PGx1


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

SYS_MODULE_OBJ usbDevObject=SYS_MODULE_OBJ_INVALID;

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
    .moduleInit = {SYS_MODULE_POWER_RUN_FULL},

    /* Identifies peripheral (PLIB-level) ID */
    .usbID = USB_ID_1,

    /* Stop in idle */
    .stopInIdle = false,

     /* Stop in sleep */
    .suspendInSleep = false,

    /* Interrupt source */
    .interruptSource =INT_SOURCE_USB_1,
    
    .endpointTable = endpointTable,
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
	/* Setup cache and flash wait states
     * for operation at 80MHz. */

    SYSTEMConfigPerformance(80000000);

    //CheKseg0CacheOn();
    
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
