/*******************************************************************************
    FreeRTOS OSAL compatibility layer

  File Name:
    osal_freertos.c

  Summary:
    Provide OSAL mappings for the FreeRTOS(tm) Real-time operating system

  Description:
    This file contains functional implementations of the OSAL for FreeRTOS.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright � <year> released Microchip Technology Inc.  All rights reserved.

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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
 */

#include <xc.h>
#include "system/common/sys_common.h"
#include "system/common/sys_module.h"
//#include "system/int/sys_int.h"  // TODO this is causing a conflict with current plibs
#include "FreeRTOS.h"
#include "system_config.h"
#include "osal/osal_freertos.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************
/*  A brief description of a section can be given directly below the section
    banner.
*/


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Data Types
// *****************************************************************************
// *****************************************************************************
static portBASE_TYPE _taskWoken;


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Helper Macros
// *****************************************************************************
// *****************************************************************************
/*  A brief description of a section can be given directly below the section
    banner.
*/

// *****************************************************************************
// *****************************************************************************
// Section: FreeRTOS callbacks
// *****************************************************************************
// *****************************************************************************
/* Callback functions required by the current configuration of FreeRTOS
 * Depending on how the OS is configured certain callback funcitons may be
 * required. These functions implement the required callbacks
*/
void vApplicationStackOverflowHook(void)
{
    OSAL_ErrorCallback(OSAL_ERROR_CALLBACK_STACK_OVERFLOW);
}

// *****************************************************************************
// *****************************************************************************
// Section: OSAL Routines
// *****************************************************************************
// *****************************************************************************
/* These routines implement the OSAL for the chosen RTOS.
*/

// Semaphore group
// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type,
                                uint8_t maxCount, uint8_t initialCount)
  Summary:
    Create an OSAL Semaphore

  Description:
    Create an OSAL binary or counting semaphore. If OSAL_SEM_TYPE_BINARY is specified then
    the maxcount and initialCount values are ignored otherwise these must contain valid
    values.

  Precondition:
    Semaphore must have been declared.

  Parameters:
    semID       - Pointer to the Semaphore ID

    type        - OSAL_SEM_TYPE_BINARY, create a binary semaphore
                - OSAL_SEM_TYPE_COUNTING, create a counting semaphore with the specified
                  count values.

    maxCount    - Maximum value for a counting semaphore. Ignored for a BINARY semaphore.

    initialCount - Starting count value for the semaphore. Ignored for a BINARY semaphore

  Returns:
    OSAL_RESULT_TRUE    - Semaphore created
    OSAL_RESULT_FALSE   - Semaphore creation failed

  Example:
    <code>
    OSAL_SEM_Create(&mySemID, OSAL_SEM_TYPE_COUNTING, 10, 5);
    </code>

  Remarks:
 */
OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type, uint8_t maxCount, uint8_t initialCount)
{
    SYS_ASSERT(semID != NULL, "OSAL_SEM_Create: invalid pointer");

    switch (type) {
        case OSAL_SEM_TYPE_BINARY:
            vSemaphoreCreateBinary(*semID);
            break;

        case OSAL_SEM_TYPE_COUNTING:
            *semID = xSemaphoreCreateCounting(maxCount, initialCount);
            break;

        default:
            *semID = NULL;
            return OSAL_RESULT_NOT_IMPLEMENTED;
    }

    if (*semID == NULL)
    {
        return OSAL_RESULT_FALSE;
    }

    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE* semID)

  Summary:
    Delete an OSAL Semaphore

  Description:
    Delete an OSAL semaphore freeing up any allocated storage associated with it.

  Precondition:
    Semaphore must have been created.

  Parameters:
    semID       - Pointer to the semID

  Returns:
    OSAL_RESULT_TRUE    - Semaphore deleted
    OSAL_RESULT_FALSE   - Semaphore deletion failed

  Example:
    <code>
     OSAL_SEM_Delete(&mySemID);
   </code>

  Remarks:
 */
OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE* semID)
{
    SYS_ASSERT(semID != NULL, "OSAL_SEM_Delete: invalid pointer");
    vSemaphoreDelete(*semID);
    *semID = NULL;
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)

  Summary:
     Pend on a semaphore. Returns true if semaphore obtained within time limit.

  Description:
     Blocking function call that pends (waits) on a semaphore. The function will
     return true is the semaphore has been obtained or false if it was not available
     or the time limit was exceeded.

  Precondition:
     Semaphore must have been created.

  Parameters:
     semID       - The semID

    waitMS       - Time limit to wait in milliseconds.
                   0 - do not wait
                   OSAL_WAIT_FOREVER - return only when semaphore is obtained
                   Other values - timeout delay

  Returns:
    OSAL_RESULT_TRUE    - Semaphore obtained
    OSAL_RESULT_FALSE   - Semaphore not obtained or timeout occurred

  Example:
    <code>
    if (OSAL_SEM_Pend(semUARTRX, 50) == OSAL_RESULT_TRUE)
    {
        // character available
        c = DRV_USART_ReadByte(drvID);
        ...
    }
    else
    {
        // character not available, resend prompt
        ...
    }
   </code>

  Remarks:
 */
OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)
{
    SYS_ASSERT(semID != NULL, "OSAL_SEM_Pend: invalid handle");

    if (xSemaphoreTake(semID, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
     Post a semaphore or increment a counting semaphore.

  Description:
     Post a binary semaphore or increment a counting semaphore. The highest
     priority task currently blocked on the semaphore will be released and
     made ready to run.

  Precondition:
     Semaphore must have been created.

  Parameters:
     semID       - The semID

  Returns:
    OSAL_RESULT_TRUE    - Semaphore posted
    OSAL_RESULT_FALSE   - Semaphore not posted

  Example:
    <code>
    OSAL_SEM_Post(semSignal);
    </code>

  Remarks:
 */
OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)
{
    SYS_ASSERT(semID != NULL, "OSAL_SEM_Post: invalid handle");

    if (xSemaphoreGive(semID) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
     Post a semaphore or increment a counting semaphore from within an ISR

  Description:
     Post a binary semaphore or increment a counting semaphore. The highest
     priority task currently blocked on the semaphore will be released and
     made ready to run. This form of the post function should be used inside
    an ISR.

  Precondition:
     Semaphore must have been created.

  Parameters:
     semID       - The semID

  Returns:
    OSAL_RESULT_TRUE    - Semaphore posted
    OSAL_RESULT_FALSE   - Semaphore not posted

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;
        // read the character
        c = U2RXREG;
        // clear the interrupt flag
        IFS1bits.U2IF = 0;
        // post a semaphore indicating a character has been received
        OSAL_SEM_PostISR(semSignal);
     }
    </code>

  Remarks:
     This version of the OSAL_SEM_Post function should be used if the program
     is, or may be, operating inside and ISR. The OSAL will take the necessary
     steps to ensure correct operation possibly disabling interrupts or entering
     a critical section. The exact requirements will depend upon the particular
     RTOS being used.
 */
OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)
{
    SYS_ASSERT(semID != NULL, "OSAL_SEM_PostISR: invalid handle");

    if (xSemaphoreGiveFromISR(semID, &_taskWoken))
    {
        return OSAL_RESULT_TRUE;
    }
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
    Return the current value of a counting semaphore.

  Description:
    Return the current value of a counting semaphore. The value returned is
    assumed to be a single vlaue ranging from 0-255.

  Precondition:
     Semaphore must have been created.

  Parameters:
     semID       - The semID

  Returns:
    0           - Semaphore is unavailable
    1-255       - Current value of the counting semaphore

  Example:
    <code>
     uint8_t semCount;

     semCount = OSAL_SEM_GetCount(semUART);

     if (semCount > 0)
     {
        // obtain the semaphore
         if (OSAL_SEM_Pend(semUART) == OSAL_RESULT_TRUE)
         {
            // perform processing on the comm channel
            ...
         }
     }
     else
     {
        // no comm channels available
        ...
     }
    </code>

  Remarks:
     This version of the OSAL_SEM_Post function should be used if the program
     is, or may be, operating inside and ISR. The OSAL will take the necessary
     steps to ensure correct operation possibly disabling interrupts or entering
     a critical section. The exact requirements will depend upon the particular
     RTOS being used.
 */
uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)
{
    return 0;
}

// Critical Section group
// *****************************************************************************
/* Function: void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity)

  Summary:
    Enter a critical section with the specified severity level.

  Description:
     The program is entering a critical section of code. It is assumed that the
     sequence of operations bounded by the enter and leave critical section operations
     is treated as one atomic sequence that will not be disturbed.

  Precondition:
    None

  Parameters:
    severity      - OSAL_CRIT_TYPE_LOW, The RTOS should disable all other running
                    tasks effectively locking the scheduling mechanism.
                  - OSAL_CRIT_TYPE_HIGH, The RTOS should disable all possible
                    interrupts sources including the scheduler ensuring that the
                    sequence of code operates without interruption.

  Returns:
    None

  Example:
    <code>
     // prevent other tasks pre-empting this sequence of code
     OSAL_CRIT_Enter(OSAL_CRIT_TYPE_LOW);
     // modify the peripheral
     DRV_USART_Reinitialize( objUSART,  &initData);
     OSAL_CRIT_Leave(OSAL_CRIT_TYPE_LOW);
    </code>

  Remarks:
    The sequence of operations bounded by the OSAL_CRIT_Enter and OSAL_CRIT_Leave
    form a critical section. The severity level defines whether the RTOS should
    perform task locking or completely disable all interrupts.

 */
void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity)
{
    switch (severity)
    {
        case OSAL_CRIT_TYPE_LOW:
            /* LOW priority critical sections just disable the scheduler */
            vTaskSuspendAll();
            break;

        case OSAL_CRIT_TYPE_HIGH:
            /* HIGH priority critical sections disable interrupts */
            portENTER_CRITICAL();
            break;
    }
}

// *****************************************************************************
/* Function: void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity)

  Summary:
    Leave a critical section with the specified severity level.

  Description:
     The program is leaving a critical section of code. It is assumed that the
     sequence of operations bounded by the enter and leave critical section operations
     is treated as one atomic sequence that will not be disturbed.
    The severity should match the severity level used in the corresponding
    OSAL_CRIT_Enter call to ensure that the RTOS carries out the correct action.

  Precondition:
    None

  Parameters:
    severity      - OSAL_CRIT_TYPE_LOW, The RTOS should disable all other running
                    tasks effectively locking the scheduling mechanism.
                  - OSAL_CRIT_TYPE_HIGH, The RTOS should disable all possible
                    interrupts sources including the scheduler ensuring that the
                    sequence of code operates without interruption.

  Returns:
    None

  Example:
    <code>
     // prevent other tasks pre-empting this sequence of code
     OSAL_CRIT_Enter(OSAL_CRIT_TYPE_LOW);
     // modify the peripheral
     DRV_USART_Reinitialize( objUSART,  &initData);
     OSAL_CRIT_Leave(OSAL_CRIT_TYPE_LOW);
    </code>

  Remarks:
    The sequence of operations bounded by the OSAL_CRIT_Enter and OSAL_CRIT_Leave
    form a critical section. The severity level defines whether the RTOS should
    perform task locking or completely disable all interrupts.

 */
void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity)
{
    switch (severity)
    {
        case OSAL_CRIT_TYPE_LOW:
            /* LOW priority resumes scheduler */
            xTaskResumeAll();
            break;

        case OSAL_CRIT_TYPE_HIGH:
            /* HIGH priority renables interrupts */
            portEXIT_CRITICAL();
            break;
    }
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID)

  Summary:
    Create a mutex.

  Description:
    This function creates a mutex, allocating storage if required and placing
    the mutex handle into the passed parameter.

  Precondition:
    None.

  Parameters:
    mutexID      - Pointer to the mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully created

    OSAL_RESULT_FALSE   - Mutex failed to be created.

  Example:
    <code>
    OSAL_MUTEX_HANDLE_TYPE mutexData;

    OSAL_MUTEX_Create(&mutexData);
    ...
     if (OSAL_MUTEX_Lock(mutexData, 1000) == OSAL_RESULT_TRUE)
     {
        // manipulate the shared data
        ...
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID)
{
    SYS_ASSERT(mutexID != NULL, "OSAL_MUTEX_Create: invalid pointer");

    /* mutex may already have been created so test before creating it */
    if (*mutexID != NULL)
    {
        return OSAL_RESULT_FALSE;
    }

    *mutexID = xSemaphoreCreateMutex();
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID)

  Summary:
    Delete a mutex.

  Description:
    This function deletes a mutex and frees associated storage if required.

  Precondition:
    None.

  Parameters:
    mutexID      - Pointer to the mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully deleted.

    OSAL_RESULT_FALSE   - Mutex failed to be deleted.

  Example:
    <code>
    OSAL_MUTEX_Delete(mutexData);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID)
{
    SYS_ASSERT(mutexID != NULL, "OSAL_MUTEX_Delete: invalid pointer");

    *mutexID = NULL;
    return OSAL_RESULT_NOT_IMPLEMENTED;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)

  Summary:
    Lock a mutex.

  Description:
    This function locks a mutex, waiting for the specified timeout. If it cannot
    be obtained or the timeout period elapses then false is returned;

  Precondition:
    None.

  Parameters:
    mutexID      - The mutex handle

    waitMS       - Timeout value in milliseconds,
                   0 - do not wait, return immediately
                   OSAL_WAIT_FOREVER - wait until mutex is obtained before returning
                   Other values - Timeout delay

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully obtained.

    OSAL_RESULT_FALSE   - Mutex failed to be obtained or timeout occurred.

  Example:
    <code>
    OSAL_MUTEX_HANDLE_TYPE mutexData;

    OSAL_MUTEX_Create(&mutexData);
    ...
     if (OSAL_MUTEX_Lock(mutexData, 1000) == OSAL_RESULT_TRUE)
     {
        // manipulate the shared data
        ...

        // unlock the mutex
        OSAL_MUTEX_Unlock(mutexData);
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)
{
    SYS_ASSERT(mutexID != NULL, "OSAL_MUTEX_Lock: invalid handle");

    if (xSemaphoreTake(mutexID, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID)

  Summary:
    Unlock a mutex.

  Description:
    This function unlocks a previously obtained mutex.

  Precondition:
    None.

  Parameters:
    mutexID      - The mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex released.

    OSAL_RESULT_FALSE   - Mutex failed to be released or error occurred.

  Example:
    <code>
    OSAL_MUTEX_HANDLE_TYPE mutexData;

    OSAL_MUTEX_Create(&mutexData);
    ...
     if (OSAL_MUTEX_Lock(mutexData, 1000) == OSAL_RESULT_TRUE)
     {
        // manipulate the shared data
        ...

        // unlock the mutex
        OSAL_MUTEX_Unlock(mutexData);
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID)
{
    SYS_ASSERT(mutexID != NULL, "OSAL_MUTEX_Unlock: invalid handle");

    if (xSemaphoreGive(mutexID) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}


// Queue group
// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID,
                                           uint16_t width, uint16_t depth)

  Summary:
    Create a queue with the specified width and depth.

  Description:
    This functions allocates storage and creates an OSAL queue entity.
    Each entry in the queue will be 'width' bytes in size and the queue can
    contain at most 'depth' items.

  Precondition:
    None.

  Parameters:
    queueID      - Pointer to the OSAL queue.

    width        - Width in bytes of each item in the queue.

    depth        - Maximum number of entries that can be stored in the queue.

  Returns:
    OSAL_RESULT_TRUE    - Queue created.

    OSAL_RESULT_FALSE   - Queue failed to be created.

  Example:
    <code>
    // declare a queue variable
     OSAL_QUEUE_Declare(serialQueue);

     // create a queue that contains 16bit integers and is 10 items long
     OSAL_QUEUE_Create(&serialQueue, sizeof(uint16_t), 10);
    </code>

  Remarks:
    The function creates an OSAL_QUEUE with the specified parameters. OSAL_QUEUEs
    are assumed to work on copy  with passed data being copied into the queue
    or other temporary storage so that the passed data storage is released.
 */
OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID, uint16_t width, uint16_t depth)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_Create: invalid pointer");

    *queueID = xQueueCreate(depth, width);
    if (*queueID == NULL) {
        return OSAL_RESULT_FALSE;
    }

    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID)

  Summary:
    Delete an OSAL_QUEUE.

  Description:
    Delete an OSAL_QUEUE pointed to be the passed argument. Associated storage
    is released upon completion.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID      - Pointer to the OSAL_QUEUE object handle.

  Returns:
    OSAL_RESULT_TRUE    - Queue deleted

    OSAL_RESULT_FALSE   - Queue failed to be deleted.

  Example:
    <code>
    // declare a queue variable
     OSAL_QUEUE_Declare(serialQueue);

     // create a queue that contains 16bit integers and is 10 items long
     OSAL_QUEUE_Create(&serialQueue, sizeof(uint16_t), 10);

     // application is terminating, delete queue object
     OSAL_QUEUE_Delete(serialQueue);
    </code>

  Remarks:
 */
inline OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_Delete: invalid pointer");

    *queueID = NULL;
    return OSAL_RESULT_NOT_IMPLEMENTED;
}


// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                        uint16_t waitMS)

  Summary:
    Add the specified item to the queue with a timeout if the queue is full.

  Description:
    Add the specified item to the queue by copying it. If the queue has space
    the function will return immediately. If there is no space on the queue
    then wait up to the specified time before returning.
    The item is added to the tail of the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.

    waitMS          - Time to wait whilst trying to write to a full queue
                      before timing out.

  Returns:
    OSAL_RESULT_TRUE      - Item successfully added to the queue

    OSAL_RESULT_FALSE   - Item could not be written to the queue or a timeout occurred.

  Example:
    <code>
    // create a queue containing 16 byte items, queue is 5 items long.
    OSAL_QUEUE_Create(&msgQueue, 16, 5);

    ...
    // define a message (Note \0 at end is allowed for)
    const char msg[16] = "Hello World....";

    // write data to the queue. Wait until space is available
    // Note in this case that the \0 at the end of msg is also copied
    OSAL_QUEUE_Add(msgQueue, (uint8_t*) msg, OSAL_WAIT_FOREVER);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_Add: invalid handle");

    if (xQueueSendToBack(queueID, pdata, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Add the specified item to the queue from with an ISR.

  Description:
    Add the specified item to the queue by copying it. The item is added to the
    tail of the queue.
    This version of Add should be used within an ISR.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.


  Returns:
    OSAL_RESULT_TRUE    - Item successfully to the queue

    OSAL_RESULT_FALSE   - Item could not be added to the queue.

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;
        // read the character
        c = U2RXREG;
        // clear the interrupt flag
        IFS1bits.U2IF = 0;

        // post the received character onto a queue for later processing
        OSAL_QUEUE_AddISR(myRXQueue, &c);
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_AddISR: invalid handle");

    if (xQueueSendToBackFromISR(queueID, pdata, &_taskWoken) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Add the specified item to the front of the queue with a timeout if the queue is full.

  Description:
    Add the specified item to the front of the queue by copying it. If the
    queue has space the function will return immediately. If there is no
    space on the queue then wait up to the specified time before returning.
    The item is added to the front of the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.

    waitMS          - Time to wait whilst trying to write to a full queue
                      before timing out.

  Returns:
    OSAL_RESULT_TRUE    - Item successfully added to the queue

    OSAL_RESULT_FALSE   - Item could not be written to the queue or a timeout occurred.

    OSAL_RESULT_NOT_IMPLEMENTED - Function not implemented in the current RTOS

  Example:
    <code>
    // create a queue containing byte items, queue is 5 items long.
    OSAL_QUEUE_Create(&msgQueue, sizeof(uint8_t), 5);

    ...
    // Send an important message
    uint8_t sigMsg = 42;

    // write data to the front of the queue.
    OSAL_QUEUE_AddHead(msgQueue, &sigMsg, OSAL_WAIT_FOREVER);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_AddHead: invalid handle");

    if (xQueueSendToFront(queueID, pdata, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Add the specified item to the front of the queue from within an ISR.

  Description:
    Add the specified item to the queue by copying it. The item is added to the
    front of the queue.
    This version of Add should be used within an ISR.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.

  Returns:
    OSAL_RESULT_TRUE    - Item successfully added to the queue

    OSAL_RESULT_FALSE   - Item could not be written to the queue.

    OSAL_RESULT_NOT_IMPLEMENTED - Function not implemented in the current RTOS

  Example:
    <code>
     void __ISR(EXTERNAL_VECTOR) _ExternalIRQHandler()
     {
        const uint8_t msg = EMERGENCY_STOP;

        // clear the interrupt flag
        IFS1bit.EIF = 0;

        // send an emergency message to any listening task
        OSAL_QUEUE_AddHeadISR(myRXQueue, &msg);
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_AddHeadISR: invalid handle");

    if (xQueueSendToFrontFromISR(queueID, pdata, &_taskWoken) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Remove the item at the head of the queue. If the queue is empty then
    it will block up to waitMS.

  Description:
    Remove the item at the head of the queue. Item is copied to the location pointed
    to by pdata. The user should ensure that there is sufficient space to receive
    the copied data. If no data is available then the function will block for at
    most waitMS before returning.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the location to receive data copied from the queue. The data
                      item must be the same size as that specified when creating the queue.

    waitMS          - Maximum time to wait before returning if the queue is empty
                      0 - return immediately
                      OSAL_WAIT_FOREVER - wait until data is in the queue
                      Others - maximum blocking time in milliseconds

  Returns:
    OSAL_RESULT_TRUE    - Item successfully removed from the queue

    OSAL_RESULT_FALSE   - Nothing removed from the queue or timeout occurred


  Example:
    <code>
    char rxChar;
    // wait up to one second to process the next character
    if (OSAL_QUEUE_Remove(rxQueue, &rxChar, 1000) == OSAL_RESULT_TRUE)
     {
        // process the data
        ...
     }
     else
     {
        // nothing received in the last one second so perform other processing
        ...
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_Remove: invalid handle");

    if (xQueueReceive(queueID, pdata, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdataS)

  Summary:
    Remove the item at the head of the queue.

  Description:
    Remove the item at the head of the queue. Item is copied to the location pointed
    to by pdata. The user should ensure that there is sufficient space to receive
    the copied data.
    This version of the queue remove function should be used inside an ISR.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the location to receive data copied from the queue. The data
                      item must be the same size as that specified when creating the queue.

  Returns:
    OSAL_RESULT_TRUE    - Item successfully removed from the queue

    OSAL_RESULT_FALSE   - Nothing removed from the queue


  Example:
    <code>
    char rxChar;
     void __ISR(TIMER_1_VECTOR) _ET1IRQHandler()
     {
        const uint8_t msg;

        // clear the interrupt flag
        IFS0bits.T1IF = 0;

        // check for data to be sent from a queue
        if (OSAL_QUEUE_RemoveISR(myTXQueue, &msg) == OSAL_RESULT_TRUE)
        {
           DRV_USART_WriteByte(uart_drv, msg);
        }
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_RemoveFromISR: invalid handle");

    if (xQueueReceiveFromISR(queueID, pdata, &_taskWoken) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Copy the item at the head of the queue but leave it on the queue. If the queue
    is empty then it will block up to waitMS.

  Description:
    Examine the queue and copy the item at the head leaving the item on the queue
    for the next access. If there is nothing on the queue then block until waitMS
     milliseconds have elapsed before returning or until something is placed on
     the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the location to receive data copied from the queue. The data
                      item must be the same size as that specified when creating the queue.

    waitMS          - Maximum time to wait before returning if the queue is empty
                      0 - return immediately
                      OSAL_WAIT_FOREVER - wait until data is in the queue
                      Others - maximum blocking time in milliseconds

  Returns:
    OSAL_RESULT_TRUE    - Item successfully copied from the queue

    OSAL_RESULT_FALSE   - Nothing copied from the queue or timeout occurred

    OSAL_RESULT_NOT_IMPLEMENTED - Operation not available on the current RTOS

  Example:
    <code>
    // copy filenames from a queue and process the data in the file
    // however if another filename is on the queue then abort and
    // restart the operation
    OSAL_QUEUE_Remove(rxQueue, fileName, OSAL_WAITFOREVER);

    while (abort == false)
    {
        // read data from the file and process it
        ...

        // check for a new filename to process
        if (OSAL_QUEUE_Peek(rxQueue, fileName, 0) == OSAL_RESULT_TRUE)
        {
           abort = true;
        }
    }

    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS)
{
    SYS_ASSERT(queueID != NULL, "OSAL_QUEUE_Peek: invalid handle");

    if (xQueuePeek(queueID, pdata, waitMS / portTICK_RATE_MS) == pdTRUE)
    {
        return OSAL_RESULT_TRUE;
    }

    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Copy the item at the head of the queue but leave it on the queue.

  Description:
    Examine the queue and copy the item at the head leaving the item on the queue
    for the next access.
    This version should be called from inside an ISR.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle.

    pdata           - Pointer to the location to receive data copied from the queue. The data
                      item must be the same size as that specified when creating the queue.

  Returns:
    OSAL_RESULT_TRUE    - Item successfully copied from the queue

    OSAL_RESULT_FALSE   - Nothing copied from the queue

    OSAL_RESULT_NOT_IMPLEMENTED - Operation not available on the current RTOS

  Example:
    <code>
     uint16_t data;

     OSAL_QUEUE_PeekISR(myQueue, &data);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)
{
    return OSAL_RESULT_NOT_IMPLEMENTED;
}

// Thread group
// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name,
    uint16_t stack_size, uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle)

  Summary:
    Create an OSAL thread with the specified parameters.

  Description:
    This function creates an OSAL thread. The thread function is implemented
    as a simple task that will normally not return (i.e. a while(1) loop).
    The name is not used by the OSAL but may be used by the RTOS for diagnostic
    and reporting purposes.
    The thread is created with a fixed stack size that is allocated from one
    of the available memory pools or more normally from the heap. The priority
    of the thread is an eight bit quantity with higher values denoting threads
    of a higher priority.
    Optionally a parameter may be passed to the thread function that can be used
    to implement per instance behavior. For example, one LED flashing task could
    be created several times with the LED number passed as a parameter at creation
    time.
    A handle to the created thread is returned in pHandle.
    Threads may be created prior to the RTOS starting however no execution will
    occur until it is started. A created thread is immediately placed into
    the READY state and is able to run provided that it is the highest priority
    thread when all threads are evaluated by the kernel either during normal
    operation or at RTOS startup time.

  Precondition:
    None.

  Parameters:
    task        - Name of the function that implements the thread code

    name        - Textual name of the thread. Not used by the OSAL but may be
                  used by the RTOS for diagnostic and tracing purposes

    stack_size  - Size of the stack associated with a thread in bytes. The RTOS
                  will allocate this many bytes from any underlying memory pool
                  or the heap

    priority    - Priority of the thread from 1-255. Higher values indicate threads
                  with higher priorities. It is left down to the underlying RTOS
                  whether threads of the same priority are permitted or if threads
                  should be given a unique priority.

    pData       - Pointer to data passed to the thread. Optional, NULL may be passed.

    pHandle     - Pointer to a variable that can contain the created threads handle.


  Returns:
    OSAL_RESULT_TRUE    - Thread successfully created

    OSAL_RESULT_FALSE   - Thread not created or insufficient memory available.

  Example:
    <code>
    // create a thread passing a data structure as a parameter during creation
    OSAL_THREAD_Create(threadCheck, "CHECK", 500, OTH_APP_THREAD_PRIORITY + 2, (void*) &appData, NULL);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name, uint16_t stack_size,
                               uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle)
{
    /* convert stack size from bytes into words */
    unsigned short stack_depth;

    /* Only priorities from 1 to the config value are used */
    if (priority >= OSAL_MAX_PRIORITIES)
        return OSAL_RESULT_FALSE;

    stack_depth = stack_size / sizeof(size_t);

    if (xTaskCreate(task, name, stack_depth , pData, priority, pHandle) == pdPASS)
        return OSAL_RESULT_TRUE;
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle);

  Summary:
    Suspend a specified thread.

  Description:
    Suspend a specific thread.
    If NULL is passed then the RTOS will attempt to suspend the thread in which
    the call was made. The thread will then only resume when unsuspended by
    another part of the program with an appropriate resume call.

  Precondition:
    None.

  Parameters:
    handle     - The thread handle.
                 NULL may be passed indicating suspend the calling thread.


  Returns:
    OSAL_RESULT_TRUE    - Thread suspended

    OSAL_RESULT_FALSE   - Thread could not be suspended

  Example:
    <code>
    // suspend this thread
    OSAL_THREAD_Suspend(NULL);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle)
{
    vTaskSuspend(handle);
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SuspendAll();

  Summary:
    Suspend all threads apart from the calling thread.

  Description:
     Suspend all threads. Interrupts are still enabled.
     The calling thread will continue executing at the next instruction.

  Precondition:
    None.

  Parameters:
    None.


  Returns:
    OSAL_RESULT_TRUE    - Threads suspended

    OSAL_RESULT_FALSE   - Threads could not be suspended

  Example:
    <code>
    // suspend all threads
    OSAL_THREAD_SuspendAll();

    // perform critical code sequence
    // NB a critical section may be a better choice here
    ...
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_SuspendAll(void)
{
    vTaskSuspendAll();
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle);

  Summary:
    Resume a specified thread.

  Description:
    Resume a specific thread.

  Precondition:
    None.

  Parameters:
    handle     - The thread handle.

  Returns:
    OSAL_RESULT_TRUE    - Thread suspended

    OSAL_RESULT_FALSE   - Thread could not be suspended

  Example:
    <code>
    // suspend a thread until a later time
    OSAL_THREAD_Suspend(thread1Handle);

    ...

    // resume the suspended thread
    OSAL_THREAD_RESUME(thread1Handle);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle)
{
    vTaskResume(handle);
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_ResumeAll();

  Summary:
    Resume all suspended threads.

  Description:
    Resume all suspended threads. Execution will continue with the highest
    priority thread that is ready to execute.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    OSAL_RESULT_TRUE    - Successful call.


  Example:
    <code>
    // resume all threads
    OSAL_THREAD_ResumeAll();
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_ResumeAll(void)
{
    xTaskResumeAll();
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SetPriority(OSAL_THREAD_HANDLE_TYPE handle,
                                                uint8_t priority)

  Summary:
    Set the priority of a thread.

  Description:
    The priority of the thread with the specified handle is changed to the new
    value. If as a reult of the change it now has the highest priority and is
    not blocked it will start executing.

  Precondition:
    None.

  Parameters:
    handle     - The thread handle.
                 NULL indicates change the priority of the thread in which the
                 call was made.

    priority   - Priority to be assigned to the thread

  Returns:
    OSAL_RESULT_TRUE    - Priority changed.

    OSAL_RESULT_FALSE   - Priority not changed.


  Example:
    <code>
    // raise the priority of this thread to ensure it completes a complex
    // operation
    uint8_t currPriority;

    currPriority = OSAL_THREAD_GetPriority(NULL);
    OSAL_THREAD_SetPriority(NULL, currPriority + 1);

    ... perform a time critical operation

    // restore the priority
    OSAL_THREAD_SetPriority(NULL, currPriority);
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_SetPriority(OSAL_THREAD_HANDLE_TYPE handle, uint8_t priority)
{
    vTaskPrioritySet(handle, priority);
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: uint8_t OSAL_THREAD_PriorityGet(OSAL_THREAD_HANDLE_TYPE handle)

  Summary:
    Get the priority of a thread.

  Description:
    The priority of the thread with the specified handle is returned. A handle
    value of NULL returns the priority of the thread making the call.

  Precondition:
    None.

  Parameters:
    handle     - The thread handle.
                 NULL indicates use the current thread.

  Returns:
    0-255      - The current priority of the thread. Higher values indicate
                 higher priority.

  Example:
    <code>
    // raise the priority of this thread to ensure it completes a complex
    // operation
    uint8_t currPriority;

    currPriority = OSAL_THREAD_PriorityGet(NULL);
    OSAL_THREAD_PrioritySet(NULL, currPriority + 1);

    ... perform a time critical operation

    // restore the priority
    OSAL_THREAD_PrioritySet(NULL, currPriority);
    </code>

  Remarks:

 */
uint8_t OSAL_THREAD_PriorityGet(OSAL_THREAD_HANDLE_TYPE handle)
{
    return uxTaskPriorityGet(handle);
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS)

  Summary:
    Put the currently executing thread to sleep.

  Description:
    Execution of the current thread is placed into a blocked state for the
    specified amount of time.
     The exact amount of time that the thread will sleep will depend upon
     the granularity of the underlying pre-emptive tick.

  Precondition:
    None.

  Parameters:
    waitMS     - Number of milliseconds thread will be blocked for.

  Returns:
    OSAL_RESULT_TRUE - Call succeeded

  Example:
    <code>
     while (1)
     {
        // sleep for 500ms
        OSAL_THREAD_Sleep(500);
        // toggle an LED
        DRV_IO_Toggle(drvHandle, LED_ID);
     }
    </code>

  Remarks:

 */
OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS)
{
    vTaskDelay(waitMS / portTICK_RATE_MS);
    return OSAL_RESULT_TRUE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task)

  Summary:
    Create a Daemon thread for use with multi-threaded Harmony drivers.

  Description:
    This function will create a daemon or system thread designed to assist
    Harmony driver modules with their operation.
    Some Harmony drivers will incorporate state machines or other loop strucutres
    that must be periodically called for the driver to continue operating.
    For instance, a USART driver may have a state machine that manages the
    prioritization and transmission of data from multiple clients. This could
    work in addition to any processing that occurs when operating under
    interrupts so it will have a separate DRV_xxxx_Tasks routine (or similar)
    that must be periodically called.
    Since the prioritization and frequency of these calls is only known to
    the programmer when designing the end application the OSAL provides
    a lightweight thread mechanism that is primarily intended to be used
    internally by MPLAB Harmony. The daemon threads have a fixed size stack
    (defined in system_config.h) and operate at a fixed priority.

  Precondition:
    None.

  Parameters:
    task      - The name of the function that implements the daemon

  Returns:
    OSAL_RESULT_TRUE    - Thread successfully created

    OSAL_RESULT_FALSE   - Thread not created or insufficient memory available.

  Example:
    <code>
    // inside driver initialization routine
    ...
    OSAL_THREAD_CreateDaemon(DRV_USART_Tasks);

    </code>

  Remarks:
    The "remarks" section is always optional.  Use it to provide additional
    information such as restrictions, special cases, and related information.
 */
OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task)
{
    if (xTaskCreate(task, "SYS", OSAL_DAEMON_STACK_SIZE / sizeof(size_t), NULL, OSAL_DAEMON_PRIORITY, NULL) == pdPASS)
        return OSAL_RESULT_TRUE;
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Start()

  Summary:
    Start the underlying RTOS

  Description:
     The underlying RTOS in an application is started. The application will not
     normally return from this function call since the RTOS and interrupts will
     be responsible for all program operation. A return from this function is
     usually fatal and indicates that the program has failed in some way.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    OSAL_RESULT_FALSE - The OS terminated for some reason.

  Example:
    <code>
     int main()
     {
         OSAL_Initialize();

         App_Init();
         OSAL_Start();
     }
    </code>

  Remarks:
 */
OSAL_RESULT OSAL_Start(void)
{
    /* We must ensure that interrupts are enabled for the RTOS to work */
    /* SYS_INT_Enable(); Disabled start of interrupts here as mainlne code will do it */

    vTaskStartScheduler();

    // this is usually a problem if the OS returns so it is a false return value
    return OSAL_RESULT_FALSE;
}

// *****************************************************************************
/* Function: const char* OSAL_Name()

  Summary:
    Obtain the name of the underlying RTOS.

  Description:
    This function returns a const char* to the textual name of the RTOS.
    The name is a NULL terminated string.

  Precondition:
    None

  Parameters:
    None

  Returns:
    const char* -   Name of the underlying RTOS or NULL

  Example:
    <code>
    // get the RTOS name
    const char* sName;

    sName = OSAL_Name();
    sprintf(buff, "RTOS: %s", sName);
    </code>

  Remarks:

 */
const char* OSAL_Name()
{
    return "FreeRTOS";
}

// *****************************************************************************
/* Function: void OSAL_ErrorCallback(OSAL_ERROR_CALLBACK_TYPE type)

  Summary:
    Lightweight error handling callback function for the RTOS.

  Description:
    The callback function will be executed whenever an error occurs within
    an underlying RTOS. The OSAL implements this function as a weak type
    allowing it to be overridden by the user.
    The type and severity of errors that can be encountered by an RTOS will
    vary according to the specific implementation so this only provides
    lightweight error handling. There is no expectation that the function
    should return and if this does happen there is no guarantee that the
    RTOS will continue to function properly. A user application could override
    this function and provide simple signalling of the error such as logging
    a message or flashing a light.

  Precondition:
    None.

  Parameters:
    type      - Type of error
                OSAL_ERROR_CALLBACK_DEFAULT         - Default error
                OSAL_ERROR_CALLBACK_OUT_OF_MEMORY   - Memory allocation error
                OSAL_ERROR_CALLBACK_STACK_OVERFLOW  - Stack overflow in a thread
                OSAL_ERROR_CALLBACK_ERROR           - Generic error

  Returns:
    None

  Example:
    <code>
    // application override of the callback
    void OSAL_ErrorCallback(OSAL_ERROR_CALLBACK_TYPE type)
     {
         // turn on the fault light
         LATAbits.LATA0 = 1;
         // do not return
         while (1)
         {
         }
     }
    </code>

  Remarks:

 */
void __attribute__((weak)) OSAL_ErrorCallback(OSAL_ERROR_CALLBACK_TYPE type)
{
    while (1)
    {
        // a non recoverable error occured so loop here
        Nop();
    }
}

// *****************************************************************************
/* Function: void OSAL_ISR_Enter()

  Summary:
    Perform setup when entering an ISR

  Description:
    This function resets a global parameter indicating a task
    switch is required. When exiting the ISR this value is checked
    and allows the kernel to perform a context switch.

  Precondition:
    None

  Parameters:
    None

  Returns:
    None

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;

        OSAL_ISR_Enter();

        // perform interrupt processing and clear the flag
        ...

        OSAL_ISR_Exit();
     }
    </code>

  Remarks:

 */
void OSAL_ISR_Enter()
{
    _taskWoken = pdFALSE;
}

// *****************************************************************************
/* Function: void OSAL_ISR_Exit()

  Summary:
    OSAL call at end of ISR handler. Must be the last call

  Description:
    This function allows the RTOS to switch to another task if one has been
    woken up as part of any operation

  Precondition:
    None

  Parameters:
    None

  Returns:
    None        - May not return

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;

        OSAL_ISR_Enter();

        // perform interrupt processing and clear the flag
        ...

        OSAL_ISR_Exit();
     }
    </code>

  Remarks:

 */
void OSAL_ISR_Exit()
{
    if (_taskWoken == pdTRUE)
    {
        taskYIELD();
    }
}

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Initialize()

  Summary:
    Perform OSAL initialization.

  Description:
     This function should be called near the start of main in an application
     that will use an underlying RTOS. This permits the RTOS to perform
     any one time initialization before the application attempts to create
     drivers or other items that may use the RTOS. Typical actions performed by
     OSAL_Initialize would be to allocate and prepare any memory pools for
     later use.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    OSAL_RESULT_TRUE  - Initialization completed successfully.

  Example:
    <code>
     int main()
     {
         OSAL_Initialize();

         App_Init();
         OSAL_Start();
     }
    </code>

  Remarks:
 */
OSAL_RESULT OSAL_Initialize()
{
    // nothing required
    return OSAL_RESULT_TRUE;
}

/*******************************************************************************
 End of File
*/


