/*******************************************************************************
 System Initialization File

  File Name:
    system_init.c

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

#include "app.h"
/*TODO For Graphics stack
       #include "TouchScreen.h"
*/



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


// Enable the below section if you are using PIC32MX devices and disable the configuration bit settings for PIC32MZ 

/*
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF
#pragma config ICESEL = ICS_PGx2
*/



// Enable the below section if you are using PIC32MZ devices

#pragma config FMIIEN   = OFF              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO   = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY  = OFF             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = OFF           // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY  = OFF             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         //3 System PLL Input Divider (1x Divider)
#pragma config FPLLRNG  = RANGE_8_16_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_POSC      // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_33       //50 System PLL Multiplier (PLL Multiply by 50)
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

// DEVCFG0 
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER   = PG_ALL
#pragma config FSLEEP   = OFF
#pragma config FECCCON  = OFF_UNLOCKED
#pragma config BOOTISA  = MIPS32
#pragma config TRCEN    = OFF
#pragma config ICESEL   = ICS_PGx2
//#pragma config JTAGEN   = OFF
#pragma config DEBUG    = ON

// DEVCP0
#pragma config CP = OFF  
//End of configuration bits settings

/*TODO Configuration Tool would add below For Graphics stack
          void CheKseg0CacheOn(void);

		  #define GFX_DEFAULT_FOREGROUND_PAGE	GFX_PAGE9
          #define GFX_DEFAULT_BACKGROUND_PAGE 	GFX_PAGE10
          #define GFX_DEFAULT_DESTINATION_PAGE 	GFX_PAGE4

		  // TouchScreen Init Values
		  #ifdef USE_TOUCHSCREEN_RESISTIVE
		  #define TOUCH_INIT_VALUES   (NULL)
		  #endif
*/




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

<#if usb_dev_obj_sys_init?has_content>
<#list usb_dev_obj_sys_init as func>
${func}
</#list>
</#if>

<#if fs_drv_init_sys_init?has_content>
<#list fs_drv_init_sys_init as func>
${func}
</#list>
</#if>

// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************

<#if fs_sys_init_sys_init?has_content>
<#list fs_sys_init_sys_init as func>
${func}
</#list>
</#if>
  
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

<#if harmony_gfx_SYS_Initialize_var?has_content>
<#list harmony_gfx_SYS_Initialize_var as func>
${func}
</#list>
</#if>

void SYS_Initialize ( void* data )
{

    /* Initialize the BSP */
   // BSP_Initialize ( );

<#if fs_init_seq_sys_init?has_content>
    <#list fs_init_seq_sys_init as func>
    ${func}
     </#list>
  </#if>
  
    // TODO perform inialization of the system

	/*TODO For Graphics Stack. In the future releases, the tool would add required initialization API's appropriately.

		// initialize the Flash Memory driver
		SST25Init();

		// initialize the timer that manages the tick counter
		TickInit();

		GFX_OBJ_Initialize();

		// initialize the components for Resistive Touch Screen
		TouchInit();

		GFX_PRIM_Initialize(0);

		DisplayBacklightOn();

		ImageDecoderInit();

		JPEGInit();

		GFX_SchemeInit();
	*/

	/* TODO For USB Stack. In the future releases, the tool would add required initialization API's appropriately.

		//Initialize the USB Host controller driver
		DRV_USB_Initialize ( );

		//Initialize the USB device layer
		USB_DEVICE_Initialize( );

		//Initialize the USB host layer
		USB_HOST_Initialize ( );

	*/

	/* TODO For TCPIP Stack. In the future releases, the tool would add required initialization API'sappropriately.

		// Initialize the TCPIP stack
		TCPIP_STACK_Initialize( );


	*/
<#if harmony_sys_init?has_content>
	<#list harmony_sys_init as func>
    ${func}
	</#list>
</#if>
	
	<#if harmony_gfx_SYS_Initialize_1?has_content>
		<#list harmony_gfx_SYS_Initialize_1 as func>
    ${func}
		</#list>
	</#if>

    /* Initialize the Application */
    APP_Initialize ( );
	
	<#if harmony_gfx_SYS_Initialize_2?has_content>
		<#list harmony_gfx_SYS_Initialize_2 as func>
    ${func}
		</#list>
	</#if>
	
<#if harmony_usb_system_int_service?has_content>
<#list harmony_usb_system_int_service as func>
	${func}
</#list>
</#if>
	

    
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
