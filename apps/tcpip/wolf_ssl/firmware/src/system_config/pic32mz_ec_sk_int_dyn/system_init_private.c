/*******************************************************************************

  Summary:

  Description:

*******************************************************************************/

/*******************************************************************************
File Name:    system_services_private.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS? WITHOUT WARRANTY OF ANY KIND,
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
#include <stdlib.h> //malloc, free
#include <xc.h>
#include <sys/attribs.h>

#include "system_config.h"
#include "app.h"
#if !defined (HARMONY_TMR_PORTING)
#define SYSTEM_DRIVER_MODULE_CONFIGURATION
#endif
#include "system/fs/sys_fs.h"
#include "system/clk/src/sys_clk_local.h"

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
        _SystemClockFreq = clkObject.systemClock;
    }

    return _SystemClockFreq;
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
    SYS_ASSERT(false, "PIC32MZ implementation needed!");
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
    SYS_ASSERT(false, "PIC32MZ implementation needed!");
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
    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

    _SystemTickResolution=ticksPerSec;
    _SystemTickUpdateRate=sysClock/(2*ticksPerSec);
    _tickHead = 0;
    _tickTail = 0;

    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_CORE);

    // clear the count reg
    _CP0_SET_COUNT(0);
    // set up the period in the compare reg
    _CP0_SET_COMPARE(_SystemTickUpdateRate);
    // The Core timer should halt when we are halted at a debug breakpoint.
    _CP0_BIC_DEBUG(_CP0_DEBUG_COUNTDM_MASK);

    SYS_INT_VectorPrioritySet(INT_VECTOR_CT, INT_PRIORITY_LEVEL5);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_CT, INT_SUBPRIORITY_LEVEL1);
    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_CORE);

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
            SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

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

            SYS_INT_SourceEnable(INT_SOURCE_TIMER_CORE);
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

    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

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
    SYS_INT_SourceEnable(INT_SOURCE_TIMER_CORE);

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
    SYS_INT_SourceDisable(INT_SOURCE_TIMER_CORE);

    tNode->rate = tNode->currCnt = rate;

    SYS_INT_SourceEnable(INT_SOURCE_TIMER_CORE);

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
void __ISR ( _CORE_TIMER_VECTOR,ipl5 ) _SystemTickIntHandler (void)
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
    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_CORE);

}//_SystemTickIntHandler
