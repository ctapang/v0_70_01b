/*******************************************************************************
  PIC32 ESK BSP initialization file

  Summary:
    BSP Module for PIC32 ESK
    
  Description:
    Performs the BSP initialization of the PIC32 ESK board
 *******************************************************************************/

/*******************************************************************************
File Name: bsp.c 
Copyright 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
#include <xc.h>

#if defined(__PIC32MX__)
#include <p32xxxx.h>
#include <plib.h>
#endif


#include "hardware_config.h"


#if defined(__PIC32MX__)
// Talladega configuration
// PIC32 ESK configuration fuses
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FPBDIV = DIV_1, POSCMOD = XT, FNOSC = PRIPLL, CP = OFF
#pragma config FMIIEN = OFF, FETHIO = OFF	// external PHY in RMII/alternate configuration
#endif


#if defined(__PIC32MZ__)
// Michigan configuration

#define __PIC32MZ__CONFIG_2

#if defined(__PIC32MZ__CONFIG_1)
//
/* Set up the Device Configuration */
// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN = OFF              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON              // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = OFF           // USB USBID Selection (Controlled by Port Function)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC       // System PLL Input Clock Selection (POSC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_12MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = OFF             // USB PLL Enable (USB PLL is enabled)

// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF             // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Enabled)
//#pragma config FCKSM = CSECME           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disabled, FSCM Disabled)
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
#pragma config JTAGEN = OFF
#pragma config DEBUG = OFF

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)


#elif defined(__PIC32MZ__CONFIG_2)

// DEVCFG3
// USERID = No Setting
#pragma config FMIIEN = OFF              // Ethernet RMII/MII Enable (MII Enabled)
#pragma config FETHIO = ON             // Ethernet I/O Pin Select (Default Ethernet I/O)
#pragma config PGL1WAY = ON             // Permission Group Lock One Way Configuration (Allow only one reconfiguration)
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USBID Selection (Controlled by the USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (8x Divider)
#pragma config FPLLRNG = RANGE_BYPASS
#pragma config FPLLICLK = PLL_FRC       // System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_50       // System PLL Multiplier (PLL Multiply by 128)
#pragma config FPLLODIV = DIV_2
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 24 MHz)
#pragma config UPLLEN = ON              // USB PLL Enable (USB PLL is enabled)

// DEVCFG1
#pragma config FNOSC = SPLL           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = ON             // Secondary Oscillator Enable (Enable SOSC)
#pragma config IESO = ON                // Internal/External Switch Over (Enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF              // Watchdog Timer Enable (WDT Enabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
// DMTCNT = No Setting
#pragma config FDMTEN = OFF              // Deadman Timer Enable (Deadman Timer is enabled)

// DEVCFG0
#pragma config DEBUG = ON              // Background Debugger Enable (Debugger is disabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select
#pragma config TRCEN = ON               // Trace Enable (Trace features in the CPU are enabled)
#pragma config BOOTISA = MIPS32         // Boot ISA Selection (Boot code and Exception code is MIPS32)
#pragma config FECCCON = OFF_UNLOCKED   // Dynamic Flash ECC Configuration (ECC and Dynamic ECC are disabled (ECCCON bits are writable))
#pragma config FSLEEP = OFF             // Flash Sleep Mode (Flash is powered down when the device is in Sleep mode)
#pragma config DBGPER = ALLOW_PG2       // Debug Mode CPU Access Permission (Allow CPU access to Permission Group 2 permission regions)
#pragma config EJTAGBEN = NORMAL        // EJTAG Boot (Normal EJTAG functionality)

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
#pragma config_alt FWDTEN=OFF
#pragma config_alt USERID = 0x1234u

#endif // defined(__PIC32MZ__CONFIG_1/__PIC32MZ__CONFIG_1)

#endif  // defined(__PIC32MZ__)


/****************************************************************************
  Function:
    void BSP_Initialize(void)

  Description:
    This routine initializes the hardware. 

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
 ***************************************************************************/
void BSP_Initialize(void)
{
//#if defined(__PIC32MZ__)
    // LEDs
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
    LED6_TRIS = 0;
    LED7_TRIS = 0;
    LED_PUT(0x00);

#if defined(__PIC32MX__)

    CNPUESET = 0x00098000; // Turn on weak pull ups on CN15, CN16, CN19 (RD5, RD7, RD13), which is connected to buttons on PIC32 Starter Kit boards

    // ADC
    AD1CON1 = 0x84E4; // Turn on, auto sample start, auto-convert, 12 bit mode (on parts with a 12bit A/D)
    AD1CON2 = 0x0404; // AVdd, AVss, int every 2 conversions, MUXA only, scan
    AD1CON3 = 0x1003; // 16 Tad auto-sample, Tad = 3*Tcy
    AD1CSSL = 1 << 2; // Scan pot

#endif

}


