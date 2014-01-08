/*******************************************************************************
  Descriptive File Name: Operating System Abstraction Layer Basic Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    osal_impl_basic.h

  Summary:
    Header file for the OSAL Basic implementation.

  Description:
    This file defines the additions or variations to the OSAL base implemenation.
 Where it is logical or possible to implement an OSAL function in a simple form
 without an RTOS being present then the function has been defined here and
 implemented either here as an inline or #define. Longer functions that are part
 of the basic implementation may also be found in the file osal.c
 The best way to consider this file is detailing any deviations from the osal.h
 defintions OR as the complete implmentation of those functions when pretending
 to support BASIC operations.
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
// DOM-IGNORE-END

#ifndef _OSAL_IMPL_BASIC_H
#define _OSAL_IMPL_BASIC_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>

#if defined(OSAL_USE_BASIC)

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// Handle to a semaphore, default implementation
#define OSAL_SEM_HANDLE_TYPE            uint8_t

// Handle to a mutex, default implementation
#define OSAL_MUTEX_HANDLE_TYPE          uint8_t

// Handle to a queue, default implementation
#define OSAL_QUEUE_HANDLE_TYPE          uint8_t

// Handle to a thread, default implementation
#define OSAL_THREAD_HANDLE_TYPE         uintptr_t

// Default value indicating block forever
#define OSAL_WAIT_FOREVER               (uint16_t) 0xFFFF


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/* Semaphore group */
// *****************************************************************************
/* OSAL_SEM_Declare(semID)
 */
#define OSAL_SEM_DECLARE(semID)                     OSAL_SEM_HANDLE_TYPE semID

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type,
                                uint8_t maxCount, uint8_t initialCount)
 */
inline OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type,
                                uint8_t maxCount, uint8_t initialCount)
{
    if (type == OSAL_SEM_TYPE_COUNTING)
        *semID = initialCount;
    else
        *semID = 1;

    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE* semID)
 */
#define OSAL_SEM_Delete(semID)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)
 */
inline OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)
{
    if (semID > 0)
    {
        semID--;
        return OSAL_RESULT_TRUE;
    }
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)
 */
inline OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)
{
    semID++;
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)
 */
inline OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)
{
    semID++;
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)
 */
inline uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)
{
    return semID;
}


// Critical Section group
// *****************************************************************************
/* Function: void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity)
 */
#define OSAL_CRIT_Enter(severity)       (SYS_INT_Disable())

// *****************************************************************************
/* Function: void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity)
 */
#define OSAL_CRIT_Leave(severity)       (SYS_INT_Enable())

// *****************************************************************************
/* OSAL_MUTEX_Declare(mutexID)
 */
#define OSAL_MUTEX_DECLARE(mutexID)              OSAL_MUTEX_HANDLE_TYPE mutexID

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE mutexID)
 */
inline OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID)
{
    *mutexID = 1;
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID)
 */
#define OSAL_MUTEX_Delete(mutexID)              (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)
 */
inline OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)
{
    if (mutexID == 1)
    {
        mutexID = 0;
        return OSAL_RESULT_TRUE;
    }
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID)
 */
inline OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE* mutexID)
{
    mutexID = 1;
    return OSAL_RESULT_FALSE;
}

// Queue group
// *****************************************************************************
/* OSAL_QUEUE_Declare(queueID
 */
#define OSAL_QUEUE_DECLARE(queueID)             

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID,
                                           uint16_t width, uint16_t depth)
 */
#define OSAL_QUEUE_Create(queueID,width, depth)         (OSAL_RESULT_FALSE)


// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID)
 */
#define OSAL_QUEUE_Delete(queueID)                      (OSAL_RESULT_FALSE)


// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                        uint16_t waitMS)
 */
#define OSAL_QUEUE_Add(queueID, pdata, waitMS)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define OSAL_QUEUE_AddISR(queueID, pdata)               (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_AddHead(queueID, pdata, waitMS)      (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define_RESULT OSAL_QUEUE_AddHeadISR(queueID, pdata)    (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_Remove(queueID, pdata, waitMS)       (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdataS)
 */
#define OSAL_QUEUE_RemoveISR(queueID, pdata)            (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_Peek(queueID, pdata,waitMS)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define OSAL_QUEUE_PeekISR(queueID, pdata)              (OSAL_RESULT_FALSE)


// Thread group
// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name,
    uint16_t stack_size, uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle)
 *
#define OSAL_THREAD_Create(task, name, stack_size, priority, pData, pHandle)    (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle);
 */
#define OSAL_THREAD_Suspend(handle)                     (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SuspendAll();
 */
#define OSAL_THREAD_SuspendAll()                        (OSAL_RESULT_FALSE)


// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle);
 */
#define OSAL_THREAD_Resume(handle)                      (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_ResumeAll();
 */
#define OSAL_THREAD_ResumeAll()                         (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SetPriority(OSAL_THREAD_HANDLE_TYPE handle,
                                                uint8_t priority)
 */
#define OSAL_THREAD_SetPriority(handle, priority)       (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: uint8_t OSAL_THREAD_PriorityGet(OSAL_THREAD_HANDLE_TYPE handle)
 */
#define OSAL_THREAD_PriorityGet(handle)                 (0)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS)
 */
#define OSAL_THREAD_Sleep(waitMS)                       (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task)
 */
#define OSAL_THREAD_CreateDaemon(task)                  (OSAL_RESULT_FALSE)


/* Interrupt support */
// *****************************************************************************
/* Function: void OSAL_ISR_Enter()
 */
#define OSAL_ISR_Enter()

// *****************************************************************************
/* Function: void OSAL_ISR_Exit()
 */
#define OSAL_ISR_Exit()


// Miscellaneous functions
// *****************************************************************************
/* Function: void* OSAL_Malloc(size_t size)
 */
#define OSAL_Malloc(size)                               (malloc(size))

// *****************************************************************************
/* Function: void OSAL_Free(void* pData)
 */
#define OSAL_Free(pData)                                (free(pData))

// Initialization and Diagnostics
// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Initialize()
 */
#define OSAL_Initialize()

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Start()
 */
#define OSAL_Start()

// *****************************************************************************
/* Function: const char* OSAL_Name()
 */
#define OSAL_Name()                                     ((const char*) "BASIC")

// *****************************************************************************
/* Macro: OSAL_ASSERT
 */
#ifndef OSAL_ASSERT

    #define OSAL_ASSERT(test, message)

#endif

#endif // _OSAL_IMPL_BASIC_H

/*******************************************************************************
 End of File
 */




