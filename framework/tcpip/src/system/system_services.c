/*******************************************************************************

  Summary:

  Description:

*******************************************************************************/

/*******************************************************************************
FileName:     system_services.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#if   defined (__C32__)
  #include <stdlib.h> //malloc, free
  #if defined (__PIC32MX__)
    #include <peripheral/timer.h>
    #include <peripheral/int.h>
    #include <peripheral/system.h>
    #include <peripheral/reset.h>
  #elif defined (__PIC32MZ__)
    #include "pic32mz_ports.h"
  #else
    #error "Neither __PIC32MX__ nor __PIC32MZ__ is defined!"
  #endif
#elif defined (__C30__)
    #include <spi.h>
    #include <stdlib.h>
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif

#include "hardware_config.h"
#include "system_config.h"
#include "tcpip/src/system/system_services.h"
#include "tcpip/src/system/system_services_private.h"

// driver configuration
#define SYSTEM_DRIVER_MODULE_CONFIGURATION

#include "tcpip/src/system/drivers/drv_media.h"
#include "media_storage_config.h"
#include "tcpip/src/system/system_userio_private.h"
#include "tcpip/src/system/fs/sys_fs.h"
#include "tcpip/src/system/fs/system_fs_private.h"

#include "tcpip/tcpip.h"

#define TCPIP_STACK_MODULE_CONFIGURATION

#include "tcpip_modules_config.h"

#include "system/init/sys_init.h"


// definitions
//

#if   defined (__C32__)

    #define FRC_FREQ       8000000     // standard Fast Internal RC Oscillator value, 8 MHz
    #define LPRC_FREQ       31000      // standard low power Internal RC Oscillator value, 31 KHz

    /********************************
     *   Macros to convert the interrupt priorities from numbers to priority levels and ipl
     **********************************/

    #define    _PRI_LEVEL(lvl)        INT_PRIORITY_LEVEL_ ## lvl
    #define    PRI_LEVEL(lvl)        _PRI_LEVEL(lvl)

    #define    _SUBPRI_LEVEL(slvl)    INT_SUB_PRIORITY_LEVEL_ ## slvl
    #define    SUBPRI_LEVEL(slvl)    _SUBPRI_LEVEL(slvl)

    #define    _IPL(lvl)        ipl ## lvl
    #define    IPL(lvl)        _IPL(lvl)

  #if defined (__PIC32MX__) // Not for PIC32MZ
    #define FRC_FREQ       8000000     // standard Fast Internal RC Oscillator value, 8 MHz
    #define LPRC_FREQ       31000      // standard low power Internal RC Oscillator value, 31 KHz
  #endif//defined (__PIC32MX__)

#elif defined (__C30__)

  #define FRC_FREQ       8000000     // standard Fast Internal RC Oscillator value, 8 MHz
  #define LPRC_FREQ       32000      // standard low power Internal RC Oscillator value, 31 KHz

#else
  #error "Neither __C32__ nor __C30__ is defined!"

#endif//defined (__C32__)

#if   defined(__PIC32MX__)
/*********************************************************************
 * Function:        void INTEnableSystemMultiVectoredInt(void)
 *
 * PreCondition:    EBASE and IntCtl.VS set up
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    System interrupts are turned on
 *
 * Overview:        Enables system wide multi-vectored interrupts
 ********************************************************************/
void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void)
{
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    // set the CP0 status IE bit high to turn on interrupts
    INTEnableInterrupts();

}

#elif defined (__PIC32MZ__)

void INTClearFlag(INT_SOURCE source)
{
    switch(source)
    {
        case INT_CT:
            IFS0bits.CTIF = 0;
            break;

        case INT_ETHERNET:
            IFS4bits.ETHIF = 0;
            break;

        case INT_INT1:
            IFS0bits.INT1IF = 0;
            break;
        default:

            SYS_ASSERT(false, "PIC32MZ implementation needed!");
            break;
    }
}

void INTEnable(INT_SOURCE source, INT_EN_DIS enable)
{
    switch(source)
    {
        case INT_CT:
            if(enable)
            {
                IEC0bits.CTIE = 1;
            }
            else
            {
                IEC0bits.CTIE = 0;
            }
            break;

        case INT_ETHERNET:
            if(enable)
            {
                IEC4bits.ETHIE = 1;
            }
            else
            {
                IEC4bits.ETHIE = 0;
            }
            break;

        case INT_INT1:
            if(enable)
            {
                IEC0bits.INT1IE = 1;
            }
            else
            {
                IEC0bits.INT1IE = 0;
            }
            break;

        default:

            SYS_ASSERT(false, "PIC32MZ implementation needed!");
            break;
    }
}


void INTSetVectorPriority(INT_VECTOR source, INT_PRIORITY priority)
{
    switch(source)
    {
        case INT_CORE_TIMER_VECTOR:
            IPC0CLR = _IPC0_CTIP_MASK;
            priority <<= _IPC0_CTIP_POSITION;
            IPC0SET = priority;
            break;

        case INT_ETH_VECTOR:
            IPC38CLR = _IPC38_ETHIP_MASK;
            priority <<= _IPC38_ETHIP_POSITION;
            IPC38SET = priority;
            break;

        case INT_EXTERNAL_1_VECTOR:
            IPC2CLR = _IPC2_INT1IP_MASK;
            priority <<= _IPC2_INT1IP_POSITION;
            IPC2SET = priority;
            break;

        default:

            SYS_ASSERT(false, "PIC32MZ implementation needed!");
            break;
    }
}

void INTSetVectorSubPriority(INT_VECTOR source, INT_SUB_PRIORITY_LEVEL subPri)
{
    switch(source)
    {
        case INT_CORE_TIMER_VECTOR:
            IPC0CLR = _IPC0_CTIS_MASK;
            subPri <<= _IPC0_CTIS_POSITION;
            IPC0SET = subPri;
            break;

        case INT_ETH_VECTOR:
            IPC38CLR = _IPC38_ETHIS_MASK;
            subPri <<= _IPC38_ETHIS_POSITION;
            IPC38SET = subPri;
            break;

        case INT_EXTERNAL_1_VECTOR:
            IPC2CLR = _IPC2_INT1IS_MASK;
            subPri <<= _IPC2_INT1IS_POSITION;
            IPC2SET = subPri;
            break;

        default:

            SYS_ASSERT(false, "PIC32MZ implementation needed!");
            break;
    }
}


unsigned int __attribute__((nomicromips))  INTEnableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("ei    %0" : "=r"(status));

    return status;
}

unsigned int __attribute__((nomicromips)) INTDisableInterrupts(void)
{
    unsigned int status = 0;

    asm volatile("di    %0" : "=r"(status));

    return status;
}


void __attribute__ ((nomicromips)) INTEnableSystemMultiVectoredInt(void)
{
    // set the CP0 cause IV bit high
    _CP0_BIS_CAUSE(0x00800000u);

    INTCONSET = _INTCON_MVEC_MASK;


    // set the CP0 status IE bit high to turn on interrupts
    // INTEnableInterrupts();
    __builtin_enable_interrupts();

}


// set up the PB divider: divide by 6 and obtain 33 MHz for UART PBClock
void SetPic32MZPB2(void)
{
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;

    PB2DIV = 0x8000 | (6 - 1);  // 200/6 MHz PB2 clock

    SYSKEY = 0x33333333;
}

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
#else
  #error "Neither __PIC32MX__ nor __PIC32MZ is defined!"

#endif  // defined (__PIC32MZ__)


typedef struct _tag_TickNode
{
        struct _tag_TickNode*   next;
        void (*tFunc)(SYS_TICK currTick);       // function to be called
        unsigned int            rate;           // rate of call
        unsigned int            currCnt;        // current count value
}sTickNode;     // system tick registration node


// global data
//
volatile SYS_TICK               _SystemTickCount = 0;
volatile unsigned int           _SystemTickResolution = 0;

// local data
//
static unsigned long             _SystemTickUpdateRate;
static int32_t                   _SystemClockFreq = -1;

static sTickNode*               _tickHead = 0;
static sTickNode*               _tickTail = 0;

/********************************** System Interface functions *****************************/
static SYS_INIT_DATA * initData = NULL;


void SYS_Initialize(void* data)
{
    if (data != NULL)
    {
        initData = (SYS_INIT_DATA*)data;
    }


    if (initData == NULL || initData->callout_BoardInitialize == NULL)
    {
        BSP_Initialize();
    }
    else
    {
        (*initData->callout_BoardInitialize)();
    }
#if  defined (__PIC32MX__)
    // Enable optimal performance
    SYSTEMConfigPerformance(SYS_CLK_ClockGet());

#elif defined(__PIC32MZ__)
    // Set PFM wait states
    PRECON = 0x32;
    // cache configuration
    SetPic32MZPB2();
    SetPic32MZIoPins();
#else
  #error "Neither __PIC32MX__ nor __PIC32MZ__ defined!"

#endif  //  defined (__PIC32MX__/__PIC32MZ__)

    // Enable multi-vectored interrupts (works for both PIC32MX and PIC32MZ
    INTEnableSystemMultiVectoredInt();

    //Turn ON the system clock
    if(!SYS_TICK_Initialize(SYS_CLK_ClockGet(), SYS_TICKS_PER_SECOND))
    {
        return;
    }

    if(!SYS_DRIVERS_Initialize())
    {
        return;
    }


#if defined (SYS_FS_ENABLE)
    const int ReplaceMe=0; // Replace with some meaningfull init variable
    SYS_FS_initialize(&ReplaceMe);
#endif//defined (SYS_FS_ENABLE)

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

#if defined(SYS_OUT_ENABLE)
    if(!_SYS_OUT_INIT( SYS_OUT_PORT))
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

#if defined (SYS_FS_ENABLE)
    {
        char path[SYS_FS_MAX_PATH+1]="";
        path[0]=SYS_FS_CHAR;
        strcpy(path+1,SYS_FS_MOUNT_POINT);
        if(SYS_FS_mount(SYS_FS_DEFAULT_MEDIA, path, SYS_FS_DEFAULT_FS, DRV_MEDIA_IO_INTENT_READ, "") == 0)
        {
            SYS_FS_chdir(path); //cd to the new mount point
            SYS_CONSOLE_PRINT("SYS_Initialize: The %s File System is mounted.\r\n", SYS_FS_DEFAULT_FS);
        }
        else
        {
            SYS_CONSOLE_PRINT("SYS_Initialize: Failed to mount the %s File System! \r\n", SYS_FS_DEFAULT_FS);
        }
    }
#endif//defined (SYS_FS_ENABLE)

    // TCP/IP stack initialization
    SYS_OUT_MESSAGE("TCPStack " TCPIP_STACK_VERSION "  ""                ");

    // Initialize the TCPIP stack
    if (!TCPIP_STACK_Initialize(TCPIP_HOSTS_CONFIGURATION, sizeof (TCPIP_HOSTS_CONFIGURATION) / sizeof (*TCPIP_HOSTS_CONFIGURATION),
            TCPIP_STACK_MODULE_CONFIG_TBL, sizeof (TCPIP_STACK_MODULE_CONFIG_TBL) / sizeof (*TCPIP_STACK_MODULE_CONFIG_TBL)))
    {
        return ;
    }

    if (initData != NULL && initData->callout_AppInitialize != NULL)
    {
        (*initData->callout_AppInitialize)();
    }


   return;

} //SYS_Initialize

/*********************************************************************
 * Function:        void SYS_Tasks(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Runs the system tasks
 *
 * Side Effects:    None
 *
 * Overview:        This function runs the system tasks.
 *
 * Note:            None
 ********************************************************************/
void SYS_Tasks(void)
{
#if defined(SYS_COMMAND_ENABLE)
    _SYS_COMMAND_TASK();
#endif

#if defined(SYS_USERIO_ENABLE)
    SYS_USERIO_Tasks();
#endif

    TCPIP_STACK_Task();

    if (initData != NULL && initData->pTasksApp != NULL)
    {
        (*initData->pTasksApp)();
    }
}


/*********************************************************************
 * Function:        uint32_t SYS_CLK_ClockGet(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current system running frequency
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the system running clock frequency.
 *
 * Note:            The function returns a value cached in _SystemClockFreq.
 *                  Any function that changes the system oscillator clock settings
 *                  has to update the _SystemClockFreq variable accordingly.
 ********************************************************************/
uint32_t SYS_CLK_ClockGet(void)
{

    if(_SystemClockFreq < 0)
    {
        _SystemClockFreq = SYS_CLK_OscClockGet();
    }

    return _SystemClockFreq;
}


/*********************************************************************
 * Function:        uint32_t SYS_CLK_OscClockGet(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current system running frequency
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the system running clock frequency
 *                  based on the current oscillator settings
 *
 * Note:            None
 ********************************************************************/
uint32_t SYS_CLK_OscClockGet(void)
{
#if defined(__PIC32MZ__)
    return 200000000;

#else
    uint32_t sysClock;

  #if defined (__C32__)
    __OSCCONbits_t    osccon;
  #elif defined (__C30__)
    OSCCONBITS osccon;
  #endif

    osccon = OSCCONbits;    // read current configuration
    if(osccon.COSC == 3 || osccon.COSC == 1)
    {    // running with PLL

        if(osccon.COSC == 3)
        {    // running on Primary PLL
            sysClock = (unsigned long)BSP_BOARD_XTAL_FREQ;
        }
        else
        {
            sysClock = (unsigned long)FRC_FREQ; // fixed Fast RC
        }

  #if defined (__PIC32MX__)
        unsigned int pllInDiv, pllMult, oDiv;
        // calculate input divider
        pllInDiv = 1 + DEVCFG2bits.FPLLIDIV;
        if(pllInDiv == 7)
        {
            pllInDiv = 10;
        }
        else if(pllInDiv == 8)
        {
            pllInDiv = 12;
        }
        sysClock /= pllInDiv;

        // pll multiplier
        pllMult = 15 + osccon.PLLMULT;
        if(pllMult == 22)
        {
            pllMult = 24;
        }
        sysClock *= pllMult;
        // finally the output divider
        oDiv = osccon.PLLODIV;
        sysClock >>= oDiv;

  #elif defined (__dsPIC33F__) || defined (__PIC24H__) ||defined (__dsPIC33E__) || defined (__PIC24E__)

        uint16_t pllDiv, pllPre, pllPost;
        pllDiv = PLLFBDbits.PLLDIV + 2;
        pllPre = CLKDIVbits.PLLPRE + 2;
        switch (CLKDIVbits.PLLPOST)
        {
            case 0:
                pllPost = 2;
                break;
            case 1:
                pllPost = 4;
                break;
            case 3:
                pllPost = 8;
                break;
            default:
                // Not a valid case
                pllPost = 1;
                break;
        }

        sysClock = sysClock * (pllDiv/(pllPre * pllPost));
        sysClock = sysClock >> 1;                               // Divide by 2 to find Fcy

  #elif defined (__PIC24F__)
    sysClock <<= 2;     // Mulby 4 for 4x PLL
    #if defined (_CPDIV)
    uint8_t cpdiv;
    cpdiv = CLKDIVbits.CPDIV;
    sysClock >>= cpdiv;
    #endif
    // Divide by 2 to get Fcy
    sysClock >>= 1;
  #endif
    }

    else switch (osccon.COSC)
    {
        case 7: // FRC/FRCDIV
            #if defined (__PIC32MX__)
            sysClock = FRC_FREQ >> osccon.FRCDIV;
            if(osccon.FRCDIV == 7)
            {
                sysClock >>= 1; // divide by 8 actually
            }
            #elif defined (__dsPIC33F__) || defined (__PIC24H__) || defined (__dsPIC33E__) || defined (__PIC24E__)
            sysClock = FRC_FREQ >> CLKDIVbits.FRCDIV;
            if(CLKDIVbits.FRCDIV == 7)
            {
                sysClock >>= 1; // divide by 8 actually
            }
            #else
            sysClock = FRC_FREQ >> CLKDIVbits.RCDIV;
            if(CLKDIVbits.RCDIV == 7)
            {
                sysClock >>= 1; // divide by 8 actually
            }
            #endif
            break;

        case 6: // FRC/16
            sysClock = (unsigned int)FRC_FREQ/16;
            break;

        case 5: // LPRC
            sysClock = LPRC_FREQ;
            break;

        case 4: // SOSC
            sysClock = BSP_SOSC_XTAL_FREQ;
            break;

        case 2: // Primary Osc
            sysClock = (unsigned int)BSP_BOARD_XTAL_FREQ;
            break;

        default: // FRC
            sysClock = (unsigned int)FRC_FREQ;
            break;
    }

    return sysClock;

#endif//defined(__PIC32MZ__)
}//SYS_CLK_OscClockGet


/*********************************************************************
 * Function:        uint32_t SYS_CLK_PeripheralClockGet(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Current peripheral bus frequency
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the peripheral bus clock frequency.
 *
 * Note:            None
 ********************************************************************/
uint32_t SYS_CLK_PeripheralClockGet(void)
{
#if   defined (__C32__)
  #if defined (__PIC32MZ__)
    return SYS_CLK_ClockGet()/6;
  #elif defined (__PIC32MX__)
    return SYS_CLK_ClockGet()>>mOSCGetPBDIV();
  #else
    #error "Neither __PIC32MX__ nor __PIC32MZ__ is defined!"
  #endif
#elif defined (__C30__)
    #if defined (__PIC24F__)
        return (SYS_CLK_ClockGet());  // Peripheral clk and instruction clock is in the ratio 1:1
    #else
        return (SYS_CLK_ClockGet()/2);  // Periperal clk is div/2
    #endif
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
}

/*********************************************************************
 * Function:        void SYS_Reboot(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function reboots the system.
 *
 * Note:            None
 ********************************************************************/
void SYS_Reboot(void)
{
#if   defined (__C32__)
#if defined (__PIC32MZ__)
    SYS_ASSERT(false, "PIC32MZ implementation needed!");
#elif defined (__PIC32MX__)
    SoftReset();
  #else
    #error "Neither __PIC32MX__ nor __PIC32MZ__ is defined!"
  #endif
#elif defined (__C30__)
    RCONbits.POR = 0;
    asm("reset");
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif

}

/*********************************************************************
 * Function:        void SYS_WDT_Clear(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function clears the system WatchDog Timer.
 *
 * Note:            None
 ********************************************************************/
void SYS_WDT_Clear(void)
{
#if   defined(__C30__)
    __asm__ volatile ("clrwdt");
#elif defined(__C32__)
  #if defined(__PIC32MX__)
    WDTCONSET = _WDTCON_WDTCLR_MASK;
  #elif defined(__PIC32MZ__)
    SYS_ASSERT(false, "PIC32MZ implementation needed!");
  #else
    #error "Neither __PIC32MX__ nor __PIC32MZ__ is defined!" 
  #endif

#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
}


/*********************************************************************
 * Function:        bool SYS_TICK_Initialize(uint32_t sysClock, uint32_t ticksPerSec)
 *
 * PreCondition:    None
 *
 * Input:           sysClock    - system clock frequency, Hz
 *                  ticksPerSec - number of ticks to generate per second
 *
 * Output:          true if initialization succeeded,
 *                  false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        Initializes the system tick counter.
 *
 * Note:            Normal value for ticksPerSec should be 100 (i.e. interrupt every 10 ms).
 ********************************************************************/
bool SYS_TICK_Initialize(uint32_t sysClock, uint32_t ticksPerSec)
{
#if   defined (__C32__)
    INTEnable(INT_CT, INT_DISABLED);

    _SystemTickResolution=ticksPerSec;
    _SystemTickUpdateRate=sysClock/(2*ticksPerSec);
    _tickHead = 0;
    _tickTail = 0;

    INTClearFlag(INT_CT);

    // clear the count reg
    _CP0_SET_COUNT(0);
    // set up the period in the compare reg
    _CP0_SET_COMPARE(_SystemTickUpdateRate);
    // The Core timer should halt when we are halted at a debug breakpoint.
    _CP0_BIC_DEBUG(_CP0_DEBUG_COUNTDM_MASK);

    INTSetVectorPriority(INT_CORE_TIMER_VECTOR, PRI_LEVEL(SYS_TICK_IPL));
    INTSetVectorSubPriority(INT_CORE_TIMER_VECTOR, SUBPRI_LEVEL(SYS_TICK_SIPL));
    INTEnable(INT_CT, INT_ENABLED);

#elif defined (__C30__)

    DisableIntT3;       // Disable the Timer 3 interrupt

    _SystemTickResolution = ticksPerSec;
    _SystemTickUpdateRate = sysClock / ticksPerSec;
    _tickHead = 0;
    _tickTail = 0;

    _T3IF = 0;          // Clear the Timer 1 interrupt flag
    OpenTimer23( 0x8000,_SystemTickUpdateRate);
    ConfigIntTimer23(T3_INT_PRIOR_4);

#else
  #error "Neither __C32__ nor __C30__ is defined!"

#endif//defined (__C32__)

    return true;

}//SYS_TICK_Initialize

/*********************************************************************
 * Function:        SystemTickHandle SYS_TICK_TimerCreate(void (*tickTimerHandler)(SYS_TICK currSysTick))
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *                  tickTimerHandler - valid handler address
 *
 * Input:           tickTimerHandler - handler to be called from the tick ISR
 *
 * Output:          a valid handle if the registration succeeded,
 *                  NULL otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function creates a timer based on the System Tick.
 *                  It registrates a callback handler with the SystemTick ISR
 *                  The handler will be called from within this ISR at specified rate.
 *
 * Note:            - All the registered handlers expiring in a current tick
 *                    will be called in turn, sequentially.
 *                    Therefore they have to be as short as possible.
 *                  - The timer handler is called from within an ISR. All the
 *                    ISR code restrictions apply.
 *                  - The SYS_TICK_TimerCreate() should not be called from within an ISR.
 *                  - The rate of which the System Tick based timer expires is set by the
 *                    SYS_TICK_TimerSetRate();
 *
 ********************************************************************/
SystemTickHandle SYS_TICK_TimerCreate(void (*tickTimerHandler)(SYS_TICK currSysTick))
{
        sTickNode*  newNode=0;

        if(tickTimerHandler)
        {
            newNode=SystemMalloc(sizeof(*newNode));
            if(newNode)
            {
                newNode->tFunc=tickTimerHandler;
                newNode->rate=newNode->currCnt=0;
                newNode->next=0;
#if   defined (__C32__)
                INTEnable(INT_CT, INT_DISABLED);
#elif defined (__C30__)
                DisableIntT1;       // Disable the Timer 1 interrupt
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
                // add tail
                if(_tickTail==0)
                {
                    _tickHead=_tickTail=newNode;
                }
                else
                {
                    _tickTail->next=newNode;
                    _tickTail=newNode;
                }
#if   defined (__C32__)
                INTEnable(INT_CT, INT_ENABLED);
#elif defined (__C30__)
                EnableIntT1;       // Enable the Timer 1 interrupt
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
            }
        }

    return (SystemTickHandle)newNode;

}


/*********************************************************************
 * Function:        bool SYS_TICK_TimerDelete(SystemTickHandle tmrHandle)
 *
 * PreCondition:    SYS_TICK_Initialize, SYS_TICK_TimerCreate should have been called
 *
 * Input:           tmrHandle - handle to a Tick Timer to be unregistered from the tick ISR
 *                              The handle should have been obtained by SYS_TICK_TimerCreate()
 *
 * Output:          true if the deletion succeeded, false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function deletes a System Tick timer previously created by
 *                  SYS_TICK_TimerCreate() and registered with the System Tick ISR.
 *
 * Note:            The SYS_TICK_TimerDelete() should not be called from within an ISR.
 ********************************************************************/
bool SYS_TICK_TimerDelete(SystemTickHandle tmrHandle)
{
    sTickNode   *pTick, *prev;

    if(_tickHead==0)
    {
        return false;   // no registered handlers
    }
#if   defined (__C32__)
    INTEnable(INT_CT, INT_DISABLED);
#elif defined (__C30__)
    DisableIntT1;       // Disable the Timer 1 interrupt
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
    if((pTick=_tickHead) == (sTickNode*)tmrHandle)
    {   // remove head
        if(_tickHead==_tickTail)
        {
            _tickHead=_tickTail=0;
        }
        else
        {
            _tickHead=pTick->next;
        }
    }
    else for(prev=_tickHead, pTick=_tickHead->next; pTick!=0; prev=pTick, pTick=pTick->next)
    {   // search within the list
        if(pTick == (sTickNode*)tmrHandle)
        {   // found it
            prev->next=pTick->next;
            if(_tickTail==pTick)
            {   // adjust tail
                _tickTail=prev;
            }
            break;
        }
    }
#if   defined (__C32__)
    INTEnable(INT_CT, INT_ENABLED);
#elif defined (__C30__)
    EnableIntT1;       // Enable the Timer 1 interrupt
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
    if(pTick)
    {
        free(pTick);
    }

    return pTick != 0;

}//SYS_TICK_TimerDelete


/*********************************************************************
 * Function:        bool SYS_TICK_TimerSetRate(SystemTickHandle tmrHandle, unsigned int rate)
 *
 * PreCondition:    SYS_TICK_Initialize, SYS_TICK_TimerCreate should have been called
 *
 * Input:           tmrHandle - handle to a Tick Timer to update the rate for.
 *                              The handle should have been obtained by SYS_TICK_TimerCreate()
 *                  rate      - current timer rate, in System Tick counts
 *
 * Output:          true if the update succeeded, false otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the rate of a System Tick timer previously created by
 *                  SYS_TICK_TimerCreate() and registered with the System Tick ISR.
 *
 *
 * Note:            A timer with rate == 0 is disabled
 ********************************************************************/
bool SYS_TICK_TimerSetRate(SystemTickHandle tmrHandle, unsigned int rate)
{
    sTickNode*  tNode;

    tNode = (sTickNode*)tmrHandle;
#if   defined (__C32__)
    INTEnable(INT_CT, INT_DISABLED);  // core timer interrupt disabled
#elif defined (__C30__)
    DisableIntT1;       // Disable the Timer 1 interrupt
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
    tNode->rate = tNode->currCnt = rate;
#if   defined (__C32__)
    INTEnable(INT_CT, INT_ENABLED);
#elif defined (__C30__)
    EnableIntT1;       // Enable the Timer 1 interrupt
#endif
    return true;


}

/*********************************************************************
 * Function:        void _ISR _SystemTickIntHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          _SystemTickCount variable is updated
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/

#if   defined (__C32__)
  #if defined (__PIC32MZ__)
//void __ISR_AT_VECTOR(INT_CORE_TIMER_VECTOR, IPL(SYS_TICK_IPL))
//void __ISR_AT_VECTOR(0) _SystemTickIntHandler(void)
//void __ISR_AT_VECTOR(_CORE_TIMER_VECTOR, IPL7SRS)
// void __attribute__((at_vector(_CORE_TIMER_VECTOR), interrupt(3), nomicromips))
void __attribute__((at_vector(INT_CORE_TIMER_VECTOR), interrupt, nomicromips))
  #elif defined (__PIC32MX__)
void __ISR(_CORE_TIMER_VECTOR, IPL(SYS_TICK_IPL))
  #else
    #error "Neither __PIC32MX__ nor __PIC32MZ__ is defined!"
  #endif
_SystemTickIntHandler(void)
{
    sTickNode   *pTick;

    _SystemTickCount ++;

    for(pTick=_tickHead; pTick!=0; pTick=pTick->next)
    {
        if(pTick->rate != 0)
        {
            if(--pTick->currCnt==0)
            {
                pTick->currCnt=pTick->rate;
                (*pTick->tFunc)(_SystemTickCount);
            }
        }
    }

  #if defined(__DEBUG)
    _CP0_SET_COMPARE(_CP0_GET_COUNT() + _SystemTickUpdateRate);
  #else
    _CP0_SET_COMPARE(_CP0_GET_COMPARE() + _SystemTickUpdateRate);
  #endif
    __asm__ __volatile__("ehb");
    INTClearFlag(INT_CT);

}//_SystemTickIntHandler

#elif defined (__C30__)

void __attribute__((interrupt, no_auto_psv)) _ISR _T3Interrupt(void)
{
    sTickNode   *pTick;

    _T3IF = 0;                         /* Clear the 32 bit timer23 interrupt */
    _SystemTickCount++;
    for(pTick=_tickHead; pTick!=0; pTick=pTick->next)
    {
        if(pTick->rate != 0)
        {
            if(--pTick->currCnt==0)
            {
                pTick->currCnt=pTick->rate;
                (*pTick->tFunc)(_SystemTickCount);
            }
        }
    }
}

#else
  #error "Neither __C32__ nor __C30__ is defined!"

#endif//#if defined (__C32__)

/*********************************************************************
 * Function:        void  SYS_TICK_MsDelay(uint32_t mSec)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           mSec - delay to achieve
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function delays execution for the specified number of milli seconds
 *
 * Note:            A timer with rate == 0 is disabled
 ********************************************************************/
void SYS_TICK_MsDelay(uint32_t mSec)
{
    if(mSec)
    {
        uint32_t sysClk = SYS_CLK_ClockGet();
        uint32_t t0;
#if   defined (__C32__)
        t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < (sysClk/2000)*mSec);
#elif defined (__C30__)
        t0 = ReadTimer23();
        while (ReadTimer23() -  t0 < (sysClk/2000)*mSec);
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
    }
}

/*********************************************************************
 * Function:        void  SYS_TICK_UsDelay(uint32_t uSec)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           uSec - delay to achieve, micro seconds
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function delays execution for the specified number of micro seconds
 *
 * Note:            A timer with rate == 0 is disabled
 ********************************************************************/
void SYS_TICK_UsDelay(uint32_t uSec)
{
    if(uSec)
    {
        uint32_t sysClk = SYS_CLK_ClockGet();
        uint32_t t0;
#if   defined (__C32__)
        t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < (sysClk/2000000l)*uSec);
#elif defined (__C30__)
        t0 = ReadTimer23();
        while (ReadTimer23() -  t0 < (sysClk/2000000l)*uSec);
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif
    }
}

/*********************************************************************
 * Function:        void  SYS_TICK_NsDelay(uint32_t nSec)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           nSec - delay to achieve, nano seconds
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function delays execution for the specified number of nano seconds
 *
 * Note:            Depending on the system running frequency there is a minimum
 *                  delay that can be achieved.
 *                  See SYS_TICK_HwResolutionGet().
 *                  For example, running at 80MHz, the smallest delay
 *                  that can be achieved is 25 ns.
 *                  These minimum delays are not very accurate.
 ********************************************************************/
void SYS_TICK_NsDelay(uint32_t nSec)
{
        uint32_t sysClk = SYS_CLK_ClockGet();
        uint32_t t0;
        uint32_t wClks = (sysClk * nSec)/2000000000ull;
        if(wClks == 0)
        {
            wClks++;
        }

#if   defined (__C32__)
        t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < wClks);
#elif defined (__C30__)
        t0 = ReadTimer23();
        while (ReadTimer23() -  t0 < wClks);
#else
  #error "Neither __C32__ nor __C30__ is defined!"
#endif


}


// *****************************************************************************
// *****************************************************************************
// Section: System Interrupts Interface
// *****************************************************************************
// *****************************************************************************
// conversion table, new style to old plib style
static const INT_SOURCE _sys_isrc_tbl[PLIB_INT_SOURCES] =
{
#if   defined (__C32__)
    INT_INT1,       // PLIB_INT_SOURCE_EXTERNAL_1,

    INT_INT3,       // PLIB_INT_SOURCE_EXTERNAL_3,

    INT_CN,         // PLIB_INT_SOURCE_CHANGE_NOTICE,

  #if defined (_ETH) && defined(TCPIP_IF_PIC32INT)
   #if defined(__PIC32MZ__) || defined(__PIC32MX__)
    INT_ETHERNET,   // PLIB_INT_SOURCE_ETH_1,
   #endif
  #endif

#elif defined (__C30__)
   INT_CN,         // PLIB_INT_SOURCE_CHANGE_NOTICE,

   INT_INT3,       // PLIB_INT_SOURCE_EXTERNAL_3,

   INT_INT1,       // PLIB_INT_SOURCE_EXTERNAL_1,

#endif

};


static const INT_VECTOR _sys_ivec_tbl[PLIB_INT_SOURCES] =
{
#if   defined (__C32__)

    INT_EXTERNAL_1_VECTOR,       // PLIB_INT_SOURCE_EXTERNAL_1,

    INT_EXTERNAL_3_VECTOR,       // PLIB_INT_SOURCE_EXTERNAL_3,

    INT_CHANGE_NOTICE_VECTOR,         // PLIB_INT_SOURCE_CHANGE_NOTICE,

// Compile only for PIC32MX with Ethernet MAC interface
#if defined (_ETH) && defined(TCPIP_IF_PIC32INT)
  #if defined(__PIC32MZ__) || defined(__PIC32MX__)
    INT_ETH_VECTOR,   // PLIB_INT_SOURCE_ETH_1,
  #endif
#endif

#elif defined (__C30__)

    INT_CHANGE_NOTICE_VECTOR,         // PLIB_INT_SOURCE_CHANGE_NOTICE,

    INT_EXTERNAL_1_VECTOR,       // PLIB_INT_SOURCE_EXTERNAL_1,

    INT_EXTERNAL_3_VECTOR,       // PLIB_INT_SOURCE_EXTERNAL_3,
#endif

};


typedef void(*iHandler)(void* param);

typedef struct
{
    iHandler    h;  // handler
    void*       p;  // handler param
}isrDcpt;       // ISR descriptor


// registered handlers
//
static isrDcpt _sys_isrDcpt_tbl[PLIB_INT_SOURCES] =
{
    {0, 0 },
};

#if defined (__C30__)

void INTClearFlag(INT_SOURCE source)
{
    switch(source)
    {
        case INT_CN:
            _CNIF = 0;
        break;
        case INT_INT1:
            _INT1IF = 0;
        break;
        case INT_INT3:
            _INT3IF = 0;
        break;
        default :
        break;
    }
}

void INTEnable(INT_SOURCE source, INT_EN_DIS enable)
{
    switch(source)
    {
        case INT_CN:
            _CNIE = enable;
        break;
        case INT_INT1:
            _INT1IE = enable;
        break;
        case INT_INT3:
            _INT3IE = enable;
        break;
        default :
        break;
    }
}


void INTSetVectorPriority(INT_VECTOR source, INT_PRIORITY priority)
{
    switch(source)
    {
        case INT_CHANGE_NOTICE_VECTOR:
            _CNIP = priority;
        break;
        case INT_EXTERNAL_1_VECTOR:
            _INT1IP = priority;
        break;
        case INT_EXTERNAL_3_VECTOR:
            _INT3IP = priority;
        break;
        default :
        break;
    }
}

#endif//defined(__C30__)


bool SYS_INT_SourceDisable(SYS_INT_SOURCE src)
{
    INT_SOURCE  iSrc = _sys_isrc_tbl[src];   // translation to the old plib

    INTEnable(iSrc, INT_DISABLED);

    return true;
}


void SYS_INT_SourceEnable(SYS_INT_SOURCE src)
{
    INT_SOURCE  iSrc = _sys_isrc_tbl[src];   // translation to the old plib

    INTEnable(iSrc, INT_ENABLED);
}


bool SYS_INT_SourceRestore(SYS_INT_SOURCE src, bool enabled)
{
    if(enabled)
    {
        INT_SOURCE  iSrc = _sys_isrc_tbl[src];   // translation to the old plib
        INTEnable(iSrc, INT_ENABLED);
    }

    return enabled;
}


void SYS_INT_SourceStatusClear(SYS_INT_SOURCE src)
{
    INT_SOURCE  iSrc = _sys_isrc_tbl[src];   // translation to the old plib
    INTClearFlag(iSrc);
}


void SYS_INT_PrioritySet(SYS_INT_SOURCE src, SYS_INT_PRIORITY intPri)
{
    INT_VECTOR  iVec = _sys_ivec_tbl[src];   // translation to the old plib
    INTSetVectorPriority(iVec, intPri);
}


void SYS_INT_SubprioritySet(SYS_INT_SOURCE src, SYS_INT_SUBPRIORITY intSubPri)
{
    INT_VECTOR  iVec = _sys_ivec_tbl[src];   // translation to the old plib
    INTSetVectorSubPriority(iVec, intSubPri);
}


// an usual implementation will dynamically adjust the required handler for a specified vector.
// this is just a static approach
void SYS_INT_DynamicRegister(SYS_INT_SOURCE src, void(*handler)(void* param), void* param )
{
    // minimal check for this one
    if(src <0 || src >= sizeof(_sys_isrDcpt_tbl)/sizeof(*_sys_isrDcpt_tbl) )
    {
        SYS_ASSERT(false, "");
        return;
    }

    bool iLev = SYS_INT_SourceDisable(src);

    _sys_isrDcpt_tbl[src].h = handler;
    _sys_isrDcpt_tbl[src].p = param;

    SYS_INT_SourceRestore(src, iLev);

}


// here are the ISR we hooked!
//
#if defined (__PIC32MZ__)
 void __attribute__((vector(INT_EXTERNAL_1_VECTOR), interrupt, nomicromips, weak)) _Sys_Ext1_Isr(void)
#elif defined (__PIC32MX__)
 void __attribute__((vector(_EXTERNAL_1_VECTOR), interrupt, nomips16, weak)) _Sys_Ext1_Isr(void)
#elif defined (__C30__)
 void __attribute__((interrupt, no_auto_psv)) _ISR _INT1Interrupt(void)
#endif
{
    iHandler ih = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_EXTERNAL_1].h;

    if(ih)
    {
        void* p = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_EXTERNAL_1].p;
        (*ih)(p);
    }
    else
    {
        SYS_ASSERT(false, "");  // just to make sure, at this time that no interrupt is enabled before
                        // registering a handler or after de-registering it!
    }
}

#if defined (__PIC32MZ__)
 void __attribute__((vector(INT_EXTERNAL_3_VECTOR), interrupt, nomicromips, weak)) _Sys_Ext3_Isr(void)
#elif defined (__PIC32MX__)
 void __attribute__((vector(_EXTERNAL_3_VECTOR), interrupt, nomips16, weak)) _Sys_Ext3_Isr(void)
#elif defined (__C30__)
 void __attribute__((interrupt, no_auto_psv)) _ISR _INT3Interrupt(void)
#endif
{
    iHandler ih = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_EXTERNAL_3].h;

    if(ih)
    {
        void* p = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_EXTERNAL_3].p;
        (*ih)(p);
    }
    else
    {
        SYS_ASSERT(false, "");
    }
}

#if defined (__PIC32MZ__)
 void __attribute__((vector(INT_CHANGE_NOTICE_VECTOR), interrupt, nomicromips, weak)) _Sys_CN_Isr(void)
#elif defined (__PIC32MX__)
 void __attribute__((vector(_CHANGE_NOTICE_VECTOR), interrupt, nomips16, weak)) _Sys_CN_Isr(void)
#elif defined (__C30__)
 void __attribute__((interrupt, no_auto_psv)) _ISR _CNInterrupt(void)
#endif
{
    iHandler ih = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_CHANGE_NOTICE].h;

    if(ih)
    {
        void* p = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_CHANGE_NOTICE].p;
        (*ih)(p);
    }
    else
    {
        SYS_ASSERT(false, "");
    }
}


#if defined (__C32__) && defined(_ETH) && defined(TCPIP_IF_PIC32INT)

  #if   defined (__PIC32MZ__)
void __attribute__((vector(INT_ETH_VECTOR), interrupt, nomicromips, weak)) _Sys_Eth_Isr(void)
  #elif defined (__PIC32MX__)
void __attribute__((vector(_ETH_VECTOR), interrupt, nomips16, weak)) _Sys_Eth_Isr(void)
  #endif
{
    iHandler ih = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_ETH_1].h;

    if(ih)
    {
        void* p = _sys_isrDcpt_tbl[PLIB_INT_SOURCE_ETH_1].p;
        (*ih)(p);
    }
    else
    {
        SYS_ASSERT(false, "");
    }
}

#endif//defined (__C32__) && defined(_ETH) && defined(TCPIP_IF_PIC32INT)


// initializatiopn of the system drivers
// add other drivers as they become available
bool SYS_DRIVERS_Initialize(void)
{

    // drv_media
    // if any type of supported storages
#if defined(MEDIA_STORAGE_EEPROM) || defined(MEDIA_STORAGE_SPIFLASH) || defined(MEDIA_STORAGE_INTERNAL_FLASH)
    DRV_MEDIA_MODULE_OBJ mediaObj;

    mediaObj = DRV_MEDIA_Initialize(0, &MEDIA_STORAGE_CONFIGURATION);
    if(mediaObj ==  DRV_MEDIA_MODULE_OBJ_INVALID)
    {
        return false;
    }

#endif// defined(MEDIA_STORAGE_EEPROM) || defined(MEDIA_STORAGE_SPIFLASH) || defined(MEDIA_STORAGE_INTERNAL_FLASH)
    // other drivers

    return true;

}

