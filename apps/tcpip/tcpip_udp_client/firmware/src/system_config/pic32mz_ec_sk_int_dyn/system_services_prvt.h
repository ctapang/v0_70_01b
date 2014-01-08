/*******************************************************************************

  Summary:

  Description:

*******************************************************************************/

/*******************************************************************************
File Name:  system_services_prvt.h
Copyright ?2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS?WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _SYSTEM_SERVICES_PRIVATE_H_
#define _SYSTEM_SERVICES_PRIVATE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <xc.h>
#include "system_config.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Tick Functions
// *****************************************************************************
// *****************************************************************************
typedef unsigned long SYS_TICK;

extern volatile SYS_TICK        _SystemTickCount;
extern volatile unsigned int    _SystemTickResolution;

#define SystemTickDiff(NewTick, StartTick)       (NewTick - StartTick)


typedef const void*    SystemTickHandle;                   // handle to access the System Tick functions


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
 * Note:            None
 ********************************************************************/
uint32_t    SYS_CLK_ClockGet(void);

// backward compatible definition for the system clock
#define SystemGetInstructionClock()   SYS_CLK_ClockGet()

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
void        SYS_WDT_Clear(void);

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
void        SYS_Reboot(void);

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
 * Note:            - Normal value for ticksPerSec should be 100 (i.e. interrupt every 10 ms).
 *                  - This implementation uses the core timer.
 *                    It takes exclusive control of the ISR for this resource.
 *                    This may eventually change as it will be integrated at the system level.
 ********************************************************************/
bool SYS_TICK_Initialize(uint32_t sysClock, uint32_t ticksPerSec);

/*********************************************************************
 * Function:        SYS_TICK SYS_TICK_Get(void)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the system tick is returned
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            None
 ********************************************************************/
SYS_TICK    SYS_TICK_Get(void);

extern __inline__ SYS_TICK __attribute__((always_inline)) SYS_TICK_Get(void)
{
    return _SystemTickCount;
}


/*********************************************************************
 * Function:        uint32_t SYS_TICK_ResolutionGet(void)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the system tick resolution
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the number of system ticks per second
 *
 * Note:            None
 ********************************************************************/
uint32_t        SYS_TICK_ResolutionGet(void);

extern __inline__ uint32_t __attribute__((always_inline)) SYS_TICK_ResolutionGet(void)
{
    return _SystemTickResolution;
}

/*********************************************************************
 * Function:        uint32_t SYS_TICK_TicksPerSecondGet(void)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the number of system ticks per second
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the number of system ticks per second
 *
 * Note:            Another name for SYS_TICK_ResolutionGet
 ********************************************************************/
uint32_t        SYS_TICK_TicksPerSecondGet(void);

extern __inline__ uint32_t __attribute__((always_inline)) SYS_TICK_TicksPerSecondGet(void)
{
    return _SystemTickResolution;
}


/*********************************************************************
 * Function:        uint32_t SYS_TICK_HwResolutionGet(void)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the hardware timer resolution
 *
 * Side Effects:    None
 *
 * Overview:        The function returns the resolution of the
 *                  system hardware timer
 *
 * Note:            None
 ********************************************************************/
uint32_t        SYS_TICK_HwResolutionGet(void);

extern __inline__ uint32_t __attribute__((always_inline)) SYS_TICK_HwResolutionGet(void)
{
    return SYS_CLK_ClockGet()/2;
}

/*********************************************************************
 * Function:        SYS_TICK SYS_TICK_HwCountGet(void)
 *
 * PreCondition:    SYS_TICK_Initialize should have been called
 *
 * Input:           None
 *
 * Output:          Current value of the hardware system timer used
 *                  to implement the system tick
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            The hardware system timer might overflow pretty fast.
 *                  use SYS_TICK_HwResolutionGet() to see the resolution of the hardware timer
 ********************************************************************/
SYS_TICK    SYS_TICK_HwCountGet(void);

extern __inline__ SYS_TICK __attribute__((always_inline)) SYS_TICK_HwCountGet(void)
{
#if defined (__C32__)
    return _CP0_GET_COUNT();
#elif defined (__C30__)
    return ReadTimer23();
#endif
}


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
SystemTickHandle        SYS_TICK_TimerCreate(void (*tickTimerHandler)(SYS_TICK currSysTick));

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
bool        SYS_TICK_TimerDelete(SystemTickHandle tmrHandle);


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
bool        SYS_TICK_TimerSetRate(SystemTickHandle tmrHandle, unsigned int rate);

// *****************************************************************************
// *****************************************************************************
// Section: System memory allocation Interface
// *****************************************************************************
// *****************************************************************************

/*********************************************************************
 * Function:        void* SystemMalloc(size_t  nBytes)
 *
 * PreCondition:    None
 *
 * Input:           nBytes   - number of bytes to allocate
 *
 * Output:          pointer to the allocated area or NULL if allocation failed.
 *
 * Side Effects:    None
 *
 * Overview:        This function allocates a memory area of the specified size.
 *                  The returned poiter is properly aligned to contain any standard type.
 *
 * Note:            None

 ********************************************************************/
void*     SystemMalloc(size_t  nBytes);

#define SystemMalloc    malloc


/*********************************************************************
 * Function:        void* SystemCalloc(size_t nElems, size_t elemSize)
 *
 * PreCondition:    None
 *
 * Input:           nElems   - number of elements to allocate
 *                  elemSize - each element size
 *
 * Output:          pointer to the allocated area or NULL if allocation failed.
 *
 * Side Effects:    None
 *
 * Overview:        This function allocates a memory area large enough to contain
 *                  nElems, each of the elemSize size.
 *                  The allocated memory area is initialized to 0.
 *                  The returned poiter is properly aligned to contain any standard type.
 *
 * Note:            None

 ********************************************************************/
void*     SystemCalloc(size_t nElems, size_t elemSize);

#define SystemCalloc    calloc


/*********************************************************************
 * Function:        void SystemFree(void* ptr)
 *
 * PreCondition:    ptr - valid pointer
 *
 * Input:           ptr  - pointer to a previously allocated memory area using SystemMalloc
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function releases a memory area previously allocated.
 *
 * Note:            None

 ********************************************************************/
void     SystemFree(void* ptr);
#define SystemFree  free


#endif  // _SYSTEM_SERVICES_PRIVATE_H_

