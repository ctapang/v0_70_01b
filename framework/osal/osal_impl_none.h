/*******************************************************************************
    OSAL none implementation header file

  Company:
    Microchip Technology Inc.

  File Name:
    osal_impl_none.h

  Summary:
    OSAL none implementation when no OS or RTOS support is required

  Description:
    This file will be included by default if no OSAL or RTOS support is required
    by the application. It defaults all of the OSAL primitives to safe values
    usuable in a non-OS application.
    Do not include this file directly. It will be included by osal.h as required.
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

#ifndef _OSAL_IMPL_NONE_H    // Guards against multiple inclusion
#define _OSAL_IMPL_NONE_H

/* Ignore this file if an RTOS or BASIC RTOS functionality is supported */
#if !defined(OSAL_USE_RTOS) && !defined(OSAL_USE_BASIC)

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
 */

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines Group
// *****************************************************************************

// *****************************************************************************
/* OSAL_SEM_Declare(semID)
 */
#if defined(OSAL_SEM_DECLARE)
#undef OSAL_SEM_DECLARE
#endif
#define OSAL_SEM_DECLARE(semID)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type,
                                uint8_t maxCount, uint8_t initialCount)
 */
#define OSAL_SEM_Create(semID, type, maxCount,initialCount)     (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Delete (OSAL_SEM_HANDLE_TYPE* semID)
 */
#define OSAL_SEM_Delete(semID)              (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)
 */
#define OSAL_SEM_Pend(semID, waitMS)        (OSAL_RESULT_TRUE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)
 */
#define OSAL_SEM_Post(semID)                (OSAL_RESULT_TRUE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)
 */
#define OSAL_SEM_PostISR(semID)             (OSAL_RESULT_TRUE)

// *****************************************************************************
/* Function: uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)
 */
#define OSAL_SEM_GetCount(semID)            (0)

// *****************************************************************************
/* Function: void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity)
 */
#define OSAL_CRIT_Enter(severity)         

// *****************************************************************************
/* Function: void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity)
 */
#define OSAL_CRIT_Leave(severity)        

// *****************************************************************************
/* OSAL_MUTEX_Declare(mutexID)
 */
#if defined(OSAL_MUTEX_DECLARE)
#undef OSAL_MUTEX_DECLARE
#endif
#define OSAL_MUTEX_DECLARE(mutexID)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID)
 */
#define OSAL_MUTEX_Create(mutexID)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID)
 */
#define OSAL_MUTEX_Delete(mutexID)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)
 */
#define OSAL_MUTEX_Lock(mutexID, waitMS)    (OSAL_RESULT_TRUE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID)
 */
#define OSAL_MUTEX_Unlock(mutexID)          (OSAL_RESULT_TRUE)

// *****************************************************************************
/* OSAL_QUEUE_Declare(queueID)
 */
#if defined(OSAL_QUEUE_DECLARE)
#undef OSAL_QUEUE_DECLARE
#endif
#define OSAL_QUEUE_DECLARE(queueID)        

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID,
                                           uint16_t width, uint16_t depth)
 */
#define OSAL_QUEUE_Create(queueID, width, depth)    (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID)
 */
#define OSAL_QUEUE_Delete(queueID)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                        uint16_t waitMS)
 */
#define OSAL_QUEUE_Add(queueID, pdata, waitMS)  (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define OSAL_QUEUE_AddISR(queueID, pdata)   (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_AddHead(queueID, pdata, waitMS)  (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define OSAL_QUEUE_AddHeadISR(queueID, pdata)       (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_Remove(queueID, pdata, waitMS)   (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdataS)
 */
#define OSAL_QUEUE_RemoveISR(queueID, pdata)        (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)
 */
#define OSAL_QUEUE_Peek(queueID, pdata, waitMS)     (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
 */
#define OSAL_QUEUE_PeekISR(queueID, pdata)          (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name,
    uint16_t stack_size, uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle)
 */
#define OSAL_THREAD_Create(task, name, stack_size, priority, pData, pHandle)    (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle);
 */
#define OSAL_THREAD_Suspend(handle)                 (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SuspendAll();
 */
#define OSAL_THREAD_SuspendAll()                    (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle);
 */
#define OSAL_THREAD_Resume(handle)                  (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_ResumeAll();
 */
#define OSAL_THREAD_ResumeAll()                     (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SetPriority(OSAL_THREAD_HANDLE_TYPE handle,
                                                uint8_t priority)
 */
#define OSAL_THREAD_SetPriority(handle, priority)   (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: uint8_t OSAL_THREAD_GetPriority(OSAL_THREAD_HANDLE_TYPE handle)
 */
#define OSAL_THREAD_GetPriority(handle)             (0)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS)
 */
#define OSAL_THREAD_Sleep(waitMS)                   (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task)
 */
#define OSAL_THREAD_CreateDaemon(task)              (OSAL_RESULT_FALSE)

// *****************************************************************************
/* Function: void OSAL_ISR_Enter()
 */
#define OSAL_ISR_Enter()

// *****************************************************************************
/* Function: void OSAL_ISR_Exit()
 */
#define OSAL_ISR_Exit()

// *****************************************************************************
/* Function: void* OSAL_Malloc(size_t size)
 */
#define OSAL_Malloc(size)                           (malloc(size))

// *****************************************************************************
/* Function: void OSAL_Free(void* pData)
 */
#define OSAL_Free(pData)                            (free(pData))

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
#define OSAL_Name()                                     ((const char*) "NONE")

// *****************************************************************************
/* Macro: OSAL_ASSERT
 */
#ifndef OSAL_ASSERT

    #define OSAL_ASSERT(test, message)

#endif

#endif // !defined(OSAL_USE_RTOS) && !defined(OSAL_USE_BASIC)

#endif // _OSAL_IMPL_NONE_H

/*******************************************************************************
 End of File
 */









