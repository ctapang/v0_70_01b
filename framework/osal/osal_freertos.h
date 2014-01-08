/*******************************************************************************
    Operating System Abstraction Layer for FreeRTOS

  File Name:
    osal_freertos.h

  Summary:
    OSAL FreeRTOS implementation interface file

  Description:
    Interface file to allow FreeRTOS to be used with the OSAL
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

#ifndef _OSAL_FREERTOS_H
#define _OSAL_FREERTOS_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "task.h"
  
// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************
/*  A brief description of a section can be given directly below the section
    banner.
*/
/* create acceptable defaults for the daemon tasks */
#ifndef OSAL_DAEMON_STACK_SIZE
#if defined(__PIC32MX__)
#define OSAL_DAEMON_STACK_SIZE  800
#elif defined(__PIC24F__)
#define OSAL_DAEMON_STACK_SIZE  300
#endif
#endif

#ifndef OSAL_DAEMON_PRIORITY
#define OSAL_DAEMON_PRIORITY    1
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************
/*  A brief description of a section can be given directly below the section
    banner.
*/

/* declare default data type handles. Any RTOS port must define it's own copy of these */
#define OSAL_SEM_HANDLE_TYPE            xSemaphoreHandle
#define OSAL_MUTEX_HANDLE_TYPE          xSemaphoreHandle
#define OSAL_QUEUE_HANDLE_TYPE          xQueueHandle
#define OSAL_THREAD_HANDLE_TYPE         xTaskHandle

#define OSAL_WAIT_FOREVER               (uint16_t) portMAX_DELAY

/* include the osal.h base implementation, this must be included after the type
 defintions above because they are used to change the function prototypes inside
 osal.h */
#include "osal/osal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Helper Macros
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: OSAL_ASSERT
 */
#ifndef OSAL_ASSERT

    #define OSAL_ASSERT(test, message)      test

#endif

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************
/* These function declarations help map OSAL function calls into specific
   FreeRTOS calls or osal translation layer functions
   Each OSAL should fully implement the functions listed in osal.h so only
   deviations from that interface are required here.
 */

#define OSAL_Malloc(size)   pvPortMalloc(size)

#define OSAL_Free(pData)    vPortFree(pData)

#endif // _OSAL_FREERTOS_H

/*******************************************************************************
 End of File
*/
