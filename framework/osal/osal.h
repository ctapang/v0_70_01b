/*******************************************************************************
  Descriptive File Name: Operating System Abstraction Layer

  Company:
    Microchip Technology Inc.

  File Name:
    osal.h

  Summary:
    Common interface definitions for the Operating System Abstraction Layer (OSAL).

  Description:
    This file defines the common interface to the Operating System
    Abstraction Layer. It defines the common types used by the OSAL
    and defines the function prototypes. Depending upon the OSAL mode,
    a support level specific implementation file is included by this
    file to give the required level of compatibility. The available
    support levels include, OSAL_USE_NONE, OSAL_USE_BASIC, and
    OSAL_USE_RTOS.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2013 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _OSAL_H
#define _OSAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************




// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/* Each OSAL type (Full, Basic and none) will have a set of basic types
 * dependent upon the OS being used. This conditional block allows the
 * default set of types to be used or the RTOS specific type
*/
#include "system_config.h"
#if !defined(OSAL_USE_RTOS) && !defined(OSAL_USE_BASIC) && !defined(OSAL_USE_NONE)
#define OSAL_USE_NONE
#endif

#if defined(OSAL_USE_RTOS)

/* The use of an RTOS has been requested. However, since the specific RTOS to
   be used is an application design decision the OSAL RTOS port should be
   included in system_config.h instead of here. This allows maximum flexibility
   allowing the user to select any supported RTOS */

#else

// OSAL_USE_BASIC or OSAL_USE_NONE

#endif

/* If the OSAL implementation has not defined the basic types then
 * Define a default set of OSAL types based upon single byte data */
#if !defined(OSAL_SEM_HANDLE_TYPE) || !defined(OSAL_MUTEX_HANDLE_TYPE) || \
    !defined(OSAL_QUEUE_HANDLE_TYPE) || !defined(OSAL_THREAD_HANDLE_TYPE) || \
    !defined(OSAL_WAIT_FOREVER)

/* Handle to a semaphore, this is the default implementation and may be overridden in an
 actual implementation file*/
#define OSAL_SEM_HANDLE_TYPE            uint8_t

/* Handle to a mutex, this is the default implementation and may be overridden in an
 actual implementation file*/
#define OSAL_MUTEX_HANDLE_TYPE          uint8_t

/* Handle to a queue, this is the default implementation and may be overridden in an
 actual implementation file*/
#define OSAL_QUEUE_HANDLE_TYPE          uint8_t

/* Handle to a thread, this is the default implementation and may be overridden in an
 actual implementation file*/
#define OSAL_THREAD_HANDLE_TYPE         uintptr_t

// Default value indicating block forever
#define OSAL_WAIT_FOREVER               (uint16_t) 0xFFFF
#endif

// *****************************************************************************
/* OSAL Result type

  Summary:
    Enumerated type representing the general return value from OSAL functions.

  Description:
    This enum represents possible return types from OSAL functions.

  Remarks:
    These enum values are the possible return values from OSAL functions
    where a standard success/fail type response is required. The majority
    of OSAL functions will return this type with a few exceptions.
*/
typedef enum OSAL_RESULT
{
    OSAL_RESULT_NOT_IMPLEMENTED = -1,
    OSAL_RESULT_FALSE = 0,
    OSAL_RESULT_TRUE = 1
} OSAL_RESULT;

// *****************************************************************************
/* OSAL Semaphore Type

  Summary:
    Enumerated type respresenting the possible types of semaphore.

  Description:
    This enum represents possible semaphore types.

    OSAL_SEM_TYPE_BINARY -      Simple binary type that can be taken once

    OSAL_SEM_TYPE_COUNTING -    Complex type that can be taken set number of
                                times defined at creation time

  Remarks:
    Binary and counting semaphore type.
*/
typedef enum OSAL_SEM_TYPE
{
    OSAL_SEM_TYPE_BINARY,
    OSAL_SEM_TYPE_COUNTING
} OSAL_SEM_TYPE;

// *****************************************************************************
/* OSAL Critical Type

  Summary:
    Enumerated type respresenting the possible types of critical section.

  Description:
    This enum represents possible critical section types.

    OSAL_CRIT_TYPE_LOW -        Low priority critical section, can be formed
                                by locking the scheduler (if supported by RTOS)
    OSAL_CRIT_TYPE_HIGH -       High priority critical section, will be formed
                                by disabling all interrupts.

 Remarks:
    Critical section types
*/
typedef enum OSAL_CRIT_TYPE
{
    OSAL_CRIT_TYPE_LOW,
    OSAL_CRIT_TYPE_HIGH
} OSAL_CRIT_TYPE;

// *****************************************************************************
/* OSAL Error Callback Type

  Summary:
    Enumerated type respresenting the possible types of callback message.

  Description:
    This enum represents possible OSAL error callback types.

    OSAL_ERROR_CALLBACK_DEFAULT -           Default error
    OSAL_ERROR_CALLBACK_OUT_OF_MEMORY -     Out of memory allocating resource
                                            such as creating a task or queue
    OSAL_ERROR_CALLBACK_STACK_OVERFLOW -    Stack overflow detected in a task
    OSAL_ERROR_CALLBACK_ERROR -             Generic error message

  Remarks:
    Error types are heavily RTOS specific so only basic types are indicated
*/
typedef enum OSAL_ERROR_CALLBACK_TYPE
{
    OSAL_ERROR_CALLBACK_DEFAULT = 0,
    OSAL_ERROR_CALLBACK_OUT_OF_MEMORY,
    OSAL_ERROR_CALLBACK_STACK_OVERFLOW,
    OSAL_ERROR_CALLBACK_ERROR
} OSAL_ERROR_CALLBACK_TYPE;

// *****************************************************************************
/* OSAL thread function template

  Summary:
     Functions that will operate as a separate thread under the OSAL should match
     this type.

  Description:
     OSAL thread functions must match this type or use it explicitly. Thread functions
     are expected to return nothing. The pData parameter is information passed at
     creation time and is implementation specific.

  Remarks:
    None.

 */
typedef void (*OSAL_THREAD_FUNCTION)(void* pData);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* OSAL_SEM_Declare(semID)

  Summary:
    Declares an OSAL semaphore.

  Description:
    This function declares a data item of type OSAL_SEM_HANDLE_TYPE.

  Remarks:
    None.

 */
#define OSAL_SEM_DECLARE(semID)                     OSAL_SEM_HANDLE_TYPE semID

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type,
                                uint8_t maxCount, uint8_t initialCount)
  Summary:
    Creates an OSAL Semaphore.

  Description:
    This function creates an OSAL binary or counting semaphore. If OSAL_SEM_TYPE_BINARY
    is specified, the maxcount and initialCount values are ignored; otherwise,
    these must contain valid values.

  Precondition:
    Semaphore must have been declared.

  Parameters:
    semID       - Pointer to the Semaphore ID

    type        - OSAL_SEM_TYPE_BINARY, create a binary semaphore

                  OSAL_SEM_TYPE_COUNTING, create a counting semaphore with the
                  specified count values

    maxCount    - Maximum value for a counting semaphore (ignored for a BINARY semaphore)

    initialCount - Starting count value for the semaphore (ignored for a BINARY semaphore)

  Returns:
    OSAL_RESULT_TRUE    - Semaphore created

    OSAL_RESULT_FALSE   - Semaphore creation failed

    semID               - Updated with valid semaphore handle if call was successful

  Example:
    <code>
    OSAL_SEM_Create(&mySemID, OSAL_SEM_TYPE_COUNTING, 10, 5);
    </code>

  Remarks:
    None.
 */
OSAL_RESULT OSAL_SEM_Create(OSAL_SEM_HANDLE_TYPE* semID, OSAL_SEM_TYPE type, uint8_t maxCount, uint8_t initialCount);

// ****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE* semID)

  Summary:
    Deletes an OSAL Semaphore.

  Description:
    This function deletes an OSAL semaphore, freeing up any allocated storage
    associated with it.

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
    None.

 */
OSAL_RESULT OSAL_SEM_Delete(OSAL_SEM_HANDLE_TYPE* semID);

/*******************************************************************************
  Function:
     OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS)

  Summary:
    Waits on a semaphore. Returns true if the semaphore was obtained within the
    time limit.

  Description:
    This function is a blocking function call that waits (i.e., pends) on a semaphore.
    The function will return true is the semaphore has been obtained, or false
    if it was not available or the time limit was exceeded.

  Conditions:
    Semaphore must have been created.

  Input:
    semID -   The semID
    waitMS -  Time limit to wait in milliseconds.<p />0, do not wait<p />OSAL_WAIT_FOREVER,
              \return only when semaphore is obtained<p />Other values,
              timeout delay

  Returns:
    OSAL_RESULT_TRUE - Semaphore obtained

    OSAL_RESULT_FALSE - Semaphore not obtained or timeout occurred

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
    None.

    */
OSAL_RESULT OSAL_SEM_Pend(OSAL_SEM_HANDLE_TYPE semID, uint16_t waitMS);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
     Posts a semaphore or increments a counting semaphore.

  Description:
     This function posts a binary semaphore or increments a counting semaphore.
     The highest priority task currently blocked on the semaphore will be released
     and made ready to run.

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
    None.

 */
OSAL_RESULT OSAL_SEM_Post(OSAL_SEM_HANDLE_TYPE semID);

/**************************************************************************
  Function:
     OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
    Posts a semaphore or increments a counting semaphore from within an
    Interrupt Service Routine (ISR).

  Description:
    This function posts a binary semaphore or increments a counting semaphore.
    The highest priority task currently blocked on the semaphore will be released
    and made ready to run. This form of the post function should be used inside
    an ISR.

  Conditions:
    Semaphore must have been created.

  Input:
    semID -  The semID

  Return:
    OSAL_RESULT_TRUE - Semaphore posted

    OSAL_RESULT_FALSE - Semaphore not posted

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;

        // indicate to the OSAL that this is an interrupt function
        OSAL_ISR_Enter();

        // read the character
        c = U2RXREG;
        // clear the interrupt flag
        IFS1bits.U2IF = 0;
        // post a semaphore indicating a character has been received
        OSAL_SEM_PostISR(semSignal);

        // indicate to the OSAL the ISR is ending
        OSAL_ISR_Exit();
     }
    </code>

  Remarks:
    This version of the OSAL_SEM_Post function should be used if the
    program is, or may be, operating inside an ISR. The OSAL will take the
    necessary steps to ensure correct operation possibly disabling
    interrupts or entering a critical section. The exact requirements will
    depend upon the particular RTOS being used.

 */
OSAL_RESULT OSAL_SEM_PostISR(OSAL_SEM_HANDLE_TYPE semID);

// *****************************************************************************
/* Function: uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID)

  Summary:
    Returns the current value of a counting semaphore.

  Description:
    This function returns the current value of a counting semaphore. The value
    returned is assumed to be a single value ranging from 0-255.

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
    None.

 */
uint8_t OSAL_SEM_GetCount(OSAL_SEM_HANDLE_TYPE semID);


// Critical Section group
// *****************************************************************************
/* Function: void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity)

  Summary:
    Enters a critical section with the specified severity level.

  Description:
     This function enters a critical section of code. It is assumed that the
     sequence of operations bounded by the enter and leave critical section
     operations is treated as one atomic sequence that will not be disturbed.

  Precondition:
    None.

  Parameters:
    severity      - OSAL_CRIT_TYPE_LOW, The RTOS should disable all other running
                    tasks effectively locking the scheduling mechanism.

                    OSAL_CRIT_TYPE_HIGH, The RTOS should disable all possible
                    interrupts sources including the scheduler ensuring that the
                    sequence of code operates without interruption.

  Returns:
    None.

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
void OSAL_CRIT_Enter(OSAL_CRIT_TYPE severity);

// *****************************************************************************
/* Function: void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity)

  Summary:
     Leaves a critical section with the specified severity level.

  Description:
     This function leaves a critical section of code. It is assumed that the
     sequence of operations bounded by the enter and leave critical section
     operations is treated as one atomic sequence that will not be disturbed.
     The severity should match the severity level used in the corresponding
     OSAL_CRIT_Enter call to ensure that the RTOS carries out the correct action.

  Precondition:
    None.

  Parameters:
    severity      - OSAL_CRIT_TYPE_LOW, The RTOS should disable all other running
                    tasks effectively locking the scheduling mechanism.

                    OSAL_CRIT_TYPE_HIGH, The RTOS should disable all possible
                    interrupts sources including the scheduler ensuring that the
                    sequence of code operates without interruption.

  Returns:
    None.

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
void OSAL_CRIT_Leave(OSAL_CRIT_TYPE severity);


// *****************************************************************************
/* OSAL_MUTEX_Declare(mutexID)

  Summary:
    Declares an OSAL mutex.

  Description:
    This function declares a data item of type OSAL_MUTEX_HANDLE_TYPE

  Remarks:
    None

 */
#define OSAL_MUTEX_DECLARE(mutexID)              OSAL_MUTEX_HANDLE_TYPE mutexID

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID)

  Summary:
    Creates a mutex.

  Description:
    This function creates a mutex, allocating storage if required and placing
    the mutex handle into the passed parameter.

  Precondition:
    Mutex must have been declared.

  Parameters:
    mutexID      - Pointer to the mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully created

    OSAL_RESULT_FALSE   - Mutex failed to be created

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
    None.

 */
OSAL_RESULT OSAL_MUTEX_Create(OSAL_MUTEX_HANDLE_TYPE* mutexID);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID)

  Summary:
    Deletes a mutex.

  Description:
    This function deletes a mutex and frees associated storage if required.

  Precondition:
    None.

  Parameters:
    mutexID      - Pointer to the mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully deleted

    OSAL_RESULT_FALSE   - Mutex failed to be deleted

  Example:
    <code>
    OSAL_MUTEX_Delete(&mutexData);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_MUTEX_Delete(OSAL_MUTEX_HANDLE_TYPE* mutexID);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS)

  Summary:
    Locks a mutex.

  Description:
    This function locks a mutex, waiting for the specified timeout. If it cannot
    be obtained or the timeout period elapses 'false' is returned.

  Precondition:
    Mutex must have been created.

  Parameters:
    mutexID      - The mutex handle

    waitMS       - Timeout value in milliseconds

                   0, do not wait return immediately

                   OSAL_WAIT_FOREVER, wait until mutex is obtained before returning

                   Other values, Timeout delay

  Returns:
    OSAL_RESULT_TRUE    - Mutex successfully obtained

    OSAL_RESULT_FALSE   - Mutex failed to be obtained or timeout occurred

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
    None.

 */
OSAL_RESULT OSAL_MUTEX_Lock(OSAL_MUTEX_HANDLE_TYPE mutexID, uint16_t waitMS);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID)

  Summary:
    Unlocks a mutex.

  Description:
    This function unlocks a previously obtained mutex.

  Precondition:
    Mutex must have been created.

  Parameters:
    mutexID      - The mutex handle

  Returns:
    OSAL_RESULT_TRUE    - Mutex released

    OSAL_RESULT_FALSE   - Mutex failed to be released or error occurred

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
    None.

 */
OSAL_RESULT OSAL_MUTEX_Unlock(OSAL_MUTEX_HANDLE_TYPE mutexID);

// *****************************************************************************
/* OSAL_QUEUE_Declare(queueID)

  Summary:
    Declares an OSAL queue.

  Description:
    This function declares a data item of type OSAL_QUEUE_HANDLE_TYPE.

  Remarks:
    None

 */
#define OSAL_QUEUE_DECLARE(queueID)             OSAL_QUEUE_HANDLE_TYPE queueID

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID,
                                           uint16_t width, uint16_t depth)

  Summary:
    Creates a queue with the specified width and depth.

  Description:
    This function allocates storage and creates an OSAL queue entity. Each entry
    in the queue will be 'width' bytes in size and the queue can contain at most
    'depth' items.

  Precondition:
    Queue must have been declared.

  Parameters:
    queueID      - Pointer to the OSAL queue
    width        - Width in bytes of each item in the queue
    depth        - Maximum number of entries that can be stored in the queue

  Returns:
    OSAL_RESULT_TRUE    - Queue created

    OSAL_RESULT_FALSE   - Queue failed to be created

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
OSAL_RESULT OSAL_QUEUE_Create(OSAL_QUEUE_HANDLE_TYPE* queueID, uint16_t width, uint16_t depth);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID)

  Summary:
    Deletes an OSAL_QUEUE.

  Description:
    This function deletes an OSAL_QUEUE pointed to be the passed argument. Associated
    storage is released upon completion.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID      - Pointer to the OSAL_QUEUE object handle

  Returns:
    OSAL_RESULT_TRUE    - Queue deleted

    OSAL_RESULT_FALSE   - Queue failed to be deleted

  Example:
    <code>
    // declare a queue variable
     OSAL_QUEUE_Declare(serialQueue);

     // create a queue that contains 16bit integers and is 10 items long
     OSAL_QUEUE_Create(&serialQueue, sizeof(uint16_t), 10);

     // application is terminating, delete queue object
     OSAL_QUEUE_Delete(&serialQueue);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_QUEUE_Delete(OSAL_QUEUE_HANDLE_TYPE* queueID);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                        uint16_t waitMS)

  Summary:
    Addd the specified item to the queue with a time-out if the queue is full.

  Description:
    This function adds the specified item to the queue by copying it. If the queue
    has space, the function will return immediately. If there is no space on the
    queue, the function will wait up to the specified time before returning.
    The item is added to the tail of the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.

    waitMS          - Time to wait while trying to write to a full queue
                      before timing out

  Returns:
    OSAL_RESULT_TRUE    - Item successfully added to the queue

    OSAL_RESULT_FALSE   - Item could not be written to the queue or a timeout occurred

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
    None.

 */
OSAL_RESULT OSAL_QUEUE_Add(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS);

/**********************************************************************************
  Function:
     OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Adds the specified item to the queue from with an ISR.

  Description:
    This function adds the specified item to the queue by copying it. The item is
    added to the tail of the queue. This version of Add should be used within an
    ISR.

  Conditions:
    Queue must have been created.

  Input:
    queueID -  The OSAL_QUEUE handle
    pdata -    Pointer to the data to be copied to the queue. The data item
               must be the same size as that specified when creating the
               queue.
  Return:
    OSAL_RESULT_TRUE  - Item successfully to the queue

    OSAL_RESULT_FALSE - Item could not be added to the queue

  Example:
    <code>
     void __ISR(UART_2_VECTOR) _UART2RXHandler()
     {
        char c;

        OSAL_ISR_Enter();

        // read the character
        c = U2RXREG;
        // clear the interrupt flag
        IFS1bits.U2IF = 0;

        // post the received character onto a queue for later processing
        OSAL_QUEUE_AddISR(myRXQueue, c);

        OSAL_ISR_Exit();
     }
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_QUEUE_AddISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Adds the specified item to the front of the queue with a timeout if the
    queue is full.

  Description:
    This function adds the specified item to the front of the queue by copying it.
    If the queue has space the function will return immediately. If there is no
    space on the queue then wait up to the specified time before returning.
    The item is added to the front of the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle

    pdata           - Pointer to the data to be copied to the queue. The data
                      item must be the same size as that specified when
                      creating the queue.

    waitMS          - Time to wait while trying to write to a full queue
                      before timing out

  Returns:
    OSAL_RESULT_TRUE    - Item successfully added to the queue

    OSAL_RESULT_FALSE   - Item could not be written to the queue or a timeout occurred

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
    None.

 */
OSAL_RESULT OSAL_QUEUE_AddHead(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS);

/*******************************************************************************
  Function:
     OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Adds the specified item to the front of the queue from within an ISR.

  Description:
    This function adds the specified item to the queue by copying it. The item
    is added to the front of the queue. This version of Add should be used within
    an ISR.

  Conditions:
    Queue must have been created.

  Input:
    queueID -  The OSAL_QUEUE handle
    pdata -    Pointer to the data to be copied to the queue. The data item
               must be the same size as that specified when creating the
               queue.
  Return:
    OSAL_RESULT_TRUE  - Item successfully added to the queue

    OSAL_RESULT_FALSE - Item could not be written to the queue

    OSAL_RESULT_NOT_IMPLEMENTED - Function not implemented in the current RTOS

  Example:
    <code>
     void __ISR(EXTERNAL_VECTOR) _ExternalIRQHandler()
     {
        const uint8_t msg = EMERGENCY_STOP;

        OSAL_ISR_Enter();

        // clear the interrupt flag
        IFS1bit.EIF = 0;

        // send an emergency message to any listening task
        OSAL_QUEUE_AddHeadISR(myRXQueue, msg);

        OSAL_ISR_Exit();
     }
    </code>

  Remarks:
    None.
 */
OSAL_RESULT OSAL_QUEUE_AddHeadISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Removes the item at the head of the queue. If the queue is empty it will block
    up to waitMS.

  Description:
    This function removes the item at the head of the queue. The item is copied
    to the location pointed to by pdata. The user should ensure that there is
    sufficient space to receive the copied data. If no data is available, the
    function will block for waitMS before returning.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle

    pdata           - Pointer to the location to receive data copied from the queue.
                      The data item must be the same size as that specified when
                      creating the queue.

    waitMS          - Maximum time to wait before returning if the queue is empty

                      0, return immediately

                      OSAL_WAIT_FOREVER, wait until data is in the queue

                      Others, maximum blocking time in milliseconds

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
    None.

 */
OSAL_RESULT OSAL_QUEUE_Remove(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS);

/******************************************************************************
  Function:
     OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdataS)

  Summary:
    Removes the item at the head of the queue.

  Description:
    This function removes the item at the head of the queue. Item is copied to
    the location pointed to by pdata. The user should ensure that there is
    sufficient space to receive the copied data. This version of the queue
    remove function should be used inside an ISR.

  Conditions:
    Queue must have been created.

  Input:
    queueID -  The OSAL_QUEUE handle
    pdata -    Pointer to the location to receive data copied from the
               queue. The data item must be the same size as that specified
               when creating the queue.

  Return:
    OSAL_RESULT_TRUE - Item successfully removed from the queue

    OSAL_RESULT_FALSE - Nothing removed from the queue

  Example:
    <code>
    char rxChar;
     void __ISR(TIMER_1_VECTOR) _ET1IRQHandler()
     {
        const uint8_t msg;

        OSAL_ISR_Enter();

        // clear the interrupt flag
        IFS0bits.T1IF = 0;

        // check for data to be sent from a queue
        if (OSAL_QUEUE_RemoveISR(myTXQueue, msg) == OSAL_RESULT_TRUE)
        {
           DRV_USART_WriteByte(uart_drv, msg);
        }

        OSAL_ISR_Exit();
     }
    </code>

  Remarks:
    None.
 */
OSAL_RESULT OSAL_QUEUE_RemoveISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata,
                                            uint16_t waitMS)

  Summary:
    Copys the item at the head of the queue but leave it on the queue. If the
    queue is empty, it will block up to waitMS.

  Description:
    This function examines the queue and copy the item at the head leaving the
    item on the queue for the next access. If there is nothing on the queue, block
    until waitMS milliseconds have elapsed before returning, or until something
    is placed on the queue.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle

    pdata           - Pointer to the location to receive data copied from the queue. The data
                      item must be the same size as that specified when creating the queue.

    waitMS          - Maximum time to wait before returning if the queue is empty

                      0, return immediately

                      OSAL_WAIT_FOREVER, wait until data is in the queue

                      Others, maximum blocking time in milliseconds

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
    None.

 */
OSAL_RESULT OSAL_QUEUE_Peek(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata, uint16_t waitMS);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata)

  Summary:
    Copys the item at the head of the queue but leaves it on the queue.

  Description:
    This function examines the queue and copies the item at the head, leaving the
    item on the queue for the next access. This version should be called from
    inside an ISR.

  Precondition:
    Queue must have been created.

  Parameters:
    queueID         - The OSAL_QUEUE handle

    pdata           - Pointer to the location to receive data copied from the queue.
                      The data item must be the same size as that specified when
                      creating the queue.

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
    None.

 */
OSAL_RESULT OSAL_QUEUE_PeekISR(OSAL_QUEUE_HANDLE_TYPE queueID, uint8_t* pdata);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name,
    uint16_t stack_size, uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle)

  Summary:
    Creates an OSAL thread with the specified parameters.

  Description:
    This function creates an OSAL thread. The thread function is implemented
    as a simple task that will normally not return (i.e., a while(1) loop).
    The name is not used by the OSAL, but may be used by the RTOS for diagnostic
    and reporting purposes.
    The thread is created with a fixed stack size that is allocated from one
    of the available memory pools or more normally from the heap. The priority
    of the thread is an 8-bit quantity with higher values denoting threads
    of a higher priority.
    Optionally, a parameter may be passed to the thread function that can be used
    to implement per instance behavior. For example, one LED flashing task could
    be created several times with the LED number passed as a parameter at creation
    time.
    A handle to the created thread is returned in pHandle.
    Threads may be created prior to the RTOS starting, however, no execution will
    occur until it is started. A created thread is immediately placed into
    the READY state and is able to run provided that it is the highest priority
    thread when all threads are evaluated by the kernel, either during normal
    operation, or at RTOS start-up time.

  Precondition:
    Thread function must exist in program memory.

  Parameters:
    task        - Name of the function that implements the thread code

    name        - Textual name of the thread. Not used by the OSAL but may be
                  used by the RTOS for diagnostic and tracing purposes.

    stack_size  - Size of the stack associated with a thread in bytes. The RTOS
                  will allocate this many bytes from any underlying memory pool
                  or the heap.

    priority    - Priority of the thread from 1-255. Higher values indicate threads
                  with higher priorities. It is left down to the underlying RTOS
                  whether threads of the same priority are permitted or if threads
                  should be given a unique priority.

    pData       - Pointer to data passed to the thread. Optionally, NULL may be passed.

    pHandle     - Pointer to a variable that can contain the created threads handle

  Returns:
    OSAL_RESULT_TRUE    - Thread successfully created

    OSAL_RESULT_FALSE   - Thread not created or insufficient memory available

  Example:
    <code>
    // create a thread passing a data structure as a parameter during creation
    OSAL_THREAD_Create(threadCheck, "CHECK", 500, OTH_APP_THREAD_PRIORITY + 2, (void*) &appData, NULL);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_Create(OSAL_THREAD_FUNCTION task, const char* name, uint16_t stack_size,
        uint8_t priority, void* pData, OSAL_THREAD_HANDLE_TYPE* pHandle);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle);

  Summary:
    Suspends a specified thread.

  Description:
    This function suspends a specific thread. If NULL is passed, the RTOS will
    attempt to suspend the thread in which the call was made. The thread will
    then only resume when unsuspended by another part of the program with an
    appropriate resume call.

  Precondition:
    Thread must have been created.

  Parameters:
    handle     - The thread handle. NULL may be passed indicating suspend the
                 calling thread.

  Returns:
    OSAL_RESULT_TRUE    - Thread suspended

    OSAL_RESULT_FALSE   - Thread could not be suspended

  Example:
    <code>
    // suspend this thread
    OSAL_THREAD_Suspend(NULL);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_Suspend(OSAL_THREAD_HANDLE_TYPE handle);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_SuspendAll();

  Summary:
    Suspends all threads apart from the calling thread.

  Description:
     This function suspends all threads. Interrupts are still enabled.
     The calling thread will continue executing at the next instruction.

  Precondition:
    Thread must have been created.

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
    None.

 */
OSAL_RESULT OSAL_THREAD_SuspendAll();

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle);

  Summary:
    Resumes a specified thread.

  Description:
    This functino resumes a specific thread.

  Precondition:
    Thread must have been created.

  Parameters:
    handle     - The thread handle

  Returns:
    OSAL_RESULT_TRUE    - Thread resumed

    OSAL_RESULT_FALSE   - Thread could not be resumed

  Example:
    <code>
    // suspend a thread until a later time
    OSAL_THREAD_Suspend(thread1Handle);

    ...

    // resume the suspended thread
    OSAL_THREAD_RESUME(thread1Handle);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_Resume(OSAL_THREAD_HANDLE_TYPE handle);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_ResumeAll();

  Summary:
    Resumes all suspended threads.

  Description:
    This function resumes all suspended threads. Execution will continue with the
    highest priority thread that is ready to execute.

  Precondition:
    Thread must have been created.

  Parameters:
    None.

  Returns:
    OSAL_RESULT_TRUE    - Successful call


  Example:
    <code>
    // resume all threads
    OSAL_THREAD_ResumeAll();
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_ResumeAll();

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_PrioritySet(OSAL_THREAD_HANDLE_TYPE handle,
                                                uint8_t priority)

  Summary:
    Sets the priority of a thread.

  Description:
    This function sets the priority of a thread. The priority of the thread with
    the specified handle is changed to the new value. If as a result of the change,
    it now has the highest priority and if not blocked, will start executing.

  Precondition:
    Thread must have been created.

  Parameters:
    handle     - The thread handle. NULL indicates change the priority of the
                 thread in which the call was made.
    priority   - Priority to be assigned to the thread

  Returns:
    OSAL_RESULT_TRUE    - Priority changed

    OSAL_RESULT_FALSE   - Priority not changed


  Example:
    <code>
    // raise the priority of this thread to ensure it completes a complex
    // operation
    uint8_t currPriority;

    currPriority = OSAL_THREAD_GetPriority(NULL);
    OSAL_THREAD_PrioritySet(NULL, currPriority + 1);

    ... perform a time critical operation

    // restore the priority
    OSAL_THREAD_PrioritySet(NULL, currPriority);
    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_PrioritySet(OSAL_THREAD_HANDLE_TYPE handle, uint8_t priority);

// *****************************************************************************
/* Function: uint8_t OSAL_THREAD_PriorityGet(OSAL_THREAD_HANDLE_TYPE handle)

  Summary:
    Gets the priority of a thread.

  Description:
    This function gets the priority of a thread. The priority of the thread with
    the specified handle is returned. A handle value of NULL returns the priority
    of the thread making the call.

  Precondition:
    Thread must have been created.

  Parameters:
    handle     - The thread handle. NULL indicates use the current thread.

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
    None.

 */
uint8_t OSAL_THREAD_PriorityGet(OSAL_THREAD_HANDLE_TYPE handle);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS)

  Summary:
    Puts the currently executing thread to sleep.

  Description:
    This function puts the currently executing thread to sleep. Execution of the
    current thread is placed into a blocked state for the specified amount of time.
     The exact amount of time that the thread will sleep will depend upon the
     granularity of the underlying pre-emptive tick.

  Precondition:
    Thread must have been created.

  Parameters:
    waitMS     - Number of milliseconds the thread will be blocked

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
    None.

 */
OSAL_RESULT OSAL_THREAD_Sleep(uint16_t waitMS);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task)

  Summary:
    Creates a Daemon thread for use with multi-threaded Harmony drivers.

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
    the programmer when designing the end application, the OSAL provides
    a lightweight thread mechanism that is primarily intended to be used
    internally by MPLAB Harmony. The Daemon threads have a fixed size stack
    (defined in system_config.h) and operate at a fixed priority.

  Precondition:
    Daemon function must exist in program memory.

  Parameters:
    task      - The name of the function that implements the Daemon

  Returns:
    OSAL_RESULT_TRUE    - Thread successfully created

    OSAL_RESULT_FALSE   - Thread not created or insufficient memory available

  Example:
    <code>
    // inside driver initialization routine
    ...
    OSAL_THREAD_CreateDaemon(DRV_USART_Tasks);

    </code>

  Remarks:
    None.

 */
OSAL_RESULT OSAL_THREAD_CreateDaemon(OSAL_THREAD_FUNCTION task);

// *****************************************************************************
/* Function: void OSAL_ISR_Enter()

  Summary:
    Informs the OSAL and RTOS that an ISR is being entered.

  Description:
     This function allows the OSAL and RTOS to implement any set up required
     should an OSAL function be called during the interrupt handler.
     Depending on the underlying RTOS, it may be necessary to set a global
     flag indicating that an interrupt is currently being executed for the
     correct context code to be executed during calls to the kernel.
     OSAL_ISR_Enter allows the RTOS to implement the required functions.

  Precondition:
    None, (in an interrupt handler).

  Parameters:
    None.

  Returns:
    None.

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
    None.

 */
void OSAL_ISR_Enter();

// *****************************************************************************
/* Function: void OSAL_ISR_Exit()

  Summary:
    Informs the OSAL and RTOS that an ISR is being exited.

  Description:
     This function allows the OSAL and RTOS to implement any restoration required
     after an ISR has completed.
     Depending on the underlying RTOS, it may be necessary to set a global
     flag indicating that an interrupt is currently being executed for the correct
     context code to be executed during calls to the kernel.
     OSAL_ISR_Exit allows the RTOS to implement the required functions.

  Precondition:
    None, (in an interrupt handler).

  Parameters:
    None.

  Returns:
    None.

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
    None.

 */
void OSAL_ISR_Exit();

// *****************************************************************************
/* Function: void* OSAL_Malloc(size_t size)

  Summary:
    Allocates memory using the OSAL default allocator.

  Description:
     This function allocates a block of memory from the default allocator from
     the underlying RTOS. If no RTOS is present, it defaults to malloc.
     Many operating systems incorporate their own memory allocation scheme, using
     pools, blocks or by wrapping the standard C library functions in a critical
     section. Since an Harmony application may not know what target OS is being used
     (if any), this function ensures that the correct thread safe memory
     allocator will be used.

  Precondition:
    None.

  Parameters:
    size      - Size of the requested memory block in bytes

  Returns:
     Pointer to the block of allocated memory. NULL is returned if memory could
     not be allocated.

  Example:
    <code>
    // create a working array
    uint8_t* pData;

     pData = OSAL_Malloc(32);
     if (pData != NULL)
     {
        ...
     }
    </code>

  Remarks:
    None.

 */
void* OSAL_Malloc(size_t size);

// *****************************************************************************
/* Function: void OSAL_Free(void* pData)

  Summary:
    Deallocates a block of memory and return to the default pool.

  Description:
     This function deallocates memory and returns it to the default pool.
     In an RTOS-based application, the memory may have been allocated from
     multiple pools or simply from the heap.
     In non-RTOS applications, this function calls the C standard function
     free.

  Precondition:
    None.

  Parameters:
    pData      - Pointer to the memory block to be set free

  Returns:
    None.

  Example:
    <code>
    // create a working array
    uint8_t* pData;

     pData = OSAL_Malloc(32);
     if (pData != NULL)
     {
        ...

        // deallocate the memory
        OSAL_Free(pData);
        // and prevent it accidentally being used again
        pData = NULL;
     }
    </code>

  Remarks:
    None.

 */
void OSAL_Free(void* pData);

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Initialize()

  Summary:
    Performs OSAL initialization.

  Description:
     This function performs OSAL initialization .This function should be called
     near the start of main in an application that will use an underlying RTOS.
     This permits the RTOS to perform any one time initialization before the
     application attempts to create drivers or other items that may use the RTOS.
     Typical actions performed by OSAL_Initialize would be to allocate and
     prepare any memory pools for later use.

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
    None.

 */
OSAL_RESULT OSAL_Initialize();

// *****************************************************************************
/* Function: OSAL_RESULT OSAL_Start()

  Summary:
    Starts the underlying RTOS

  Description:
     This function starts the underlying RTOS application. The application will not
     normally return from this function call since the RTOS and interrupts will
     be responsible for all program operation. A return from this function is
     usually fatal and indicates that the program has failed in some way.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    OSAL_RESULT_FALSE - The OS terminated for some reason

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
    None.

 */
OSAL_RESULT OSAL_Start();

// *****************************************************************************
/* Function: const char* OSAL_Name()

  Summary:
    Obtains the name of the underlying RTOS.

  Description:
    This function returns a const char* to the textual name of the RTOS.
    The name is a NULL terminated string.

  Precondition:
    None.

  Parameters:
    None.

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
    None.

 */
const char* OSAL_Name();

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

                OSAL_ERROR_CALLBACK_DEFAULT,          Default error

                OSAL_ERROR_CALLBACK_OUT_OF_MEMORY,    Memory allocation error

                OSAL_ERROR_CALLBACK_STACK_OVERFLOW,   Stack overflow in a thread

                OSAL_ERROR_CALLBACK_ERROR,            Generic error

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
    None.

 */
void OSAL_ErrorCallback(OSAL_ERROR_CALLBACK_TYPE type);

// *****************************************************************************
// *****************************************************************************
// Section: Section: Interface Routines Group
// *****************************************************************************
// *****************************************************************************

/* The following include of the implentation specific header files allows for
   modification or addition to the basic interfaces defined above. An OSAL port to
   a specific RTOS must follow the interface definition exactly however it may be
   useful to allow a BASIC or NONE implementation to override some of the default
   definitions in order to optimize for memory constrained systems or systems that
   will never have a need to use an RTOS.
*/
#if defined(OSAL_USE_RTOS)

/* The use of an RTOS has been requested. However, since the specific RTOS to
   be used is an application design decision the OSAL RTOS port should be
   included in system_config.h instead of here. This allows maximum flexibility
   allowing the user to select any supported RTOS */

#elif defined(OSAL_USE_BASIC)

#include "osal_impl_basic.h"

#else /* default to OSAL_USE_NONE */

#include "osal_impl_none.h"

#endif

#endif // _OSAL_H

/*******************************************************************************
 End of File
 */