#include <xc.h>
/*
*********************************************************************************************************
*                                                CONFIGURATION WORDS
*********************************************************************************************************
*/
// DEVCFG2
#pragma config FPLLIDIV = DIV_1         // System PLL Input Divider (1x Divider)
#pragma config FPLLRNG = RANGE_5_10_MHZ // System PLL Input Range (5-10 MHz Input)
#pragma config FPLLICLK = PLL_FRC       // System PLL Input Clock Selection (FRC is input to the System PLL)
#pragma config FPLLMULT = MUL_50        // System PLL Multiplier (PLL Multiply by 50)
#pragma config FPLLODIV = DIV_4
#pragma config UPLLFSEL = FREQ_24MHZ    // USB PLL Input Frequency Selection (USB PLL input is 12 MHz)
#pragma config UPLLEN = ON              // USB PLL Enable (USB PLL is enabled)


// DEVCFG1
#pragma config FNOSC = SPLL             // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config DMTINTV = WIN_127_128    // DMT Count Window Interval (Window/Interval value is 127/128 counter value)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disable SOSC)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = EC             // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = ON            // CLKO Output Signal Active on the OSCO Pin (Enabled)
#pragma config FCKSM = CSECMD           // Clock Switching and Monitor Selection (Clock Switch Enabled, FSCM Enabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WDTSPGM = STOP           // Watchdog Timer Stop During Flash Programming (WDT stops during Flash programming)
#pragma config WINDIS = NORMAL          // Watchdog Timer Window Mode (Watchdog Timer is in non-Window mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled)
#pragma config FWDTWINSZ = WINSZ_25     // Watchdog Timer Window Size (Window size is 25%)
#pragma config FDMTEN = OFF             // Deadman Timer Enable (Deadman Timer is disabled)

#pragma config DMTCNT = 0

/* DEVCFG0 */
#pragma config EJTAGBEN = NORMAL
#pragma config DBGPER = PG_ALL
#pragma config FSLEEP = OFF
#pragma config FECCCON = OFF_UNLOCKED
#pragma config BOOTISA = MIPS32
#pragma config TRCEN = ON
#pragma config ICESEL = ICS_PGx2
#pragma config DEBUG = ON

// DEVCP0
#pragma config CP = OFF                 // Code Protect (Protection Disabled)
#pragma config_alt FWDTEN=OFF
#pragma config_alt USERID = 0x1234u

