/*******************************************************************************
  Timer System Service Local Data Structures

  Company:
    Microchip Technology Inc.

  File Name:
    sys_tmr_local.h

  Summary:
    Timer System Service local declarations and definitions.

  Description:
    This file contains the Timer System Service local declarations and definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END


#ifndef _SYS_TMR_LOCAL_H
#define _SYS_TMR_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "system_config.h"
#include "system/tmr/sys_tmr.h"
#include "system/tmr/src/sys_tmr_variant_mapping.h"

#include "osal/osal.h"

// *****************************************************************************
// *****************************************************************************
// Section: Data Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Callback service type enumeration

  Summary:
    Callback service type.

  Description:
    This data type defines the callback service type.

  Remarks:
    None.
*/

typedef enum
{
    /* Callback service is single/one shot */
    SYS_TMR_CALLBACK_SINGLE /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,

    /* Callback service is periodic */
    SYS_TMR_CALLBACK_PERIODIC /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /* Callback service not required */
    SYS_TMR_CALLBACK_NONE /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/

} SYS_TMR_CALLBACK_TYPE;


// *****************************************************************************
/* Callback service Status enumeration

  Summary:
    Callback service status type.

  Description:
    This data type defines the callback service status type.

  Remarks:
    None.
*/

typedef enum
{
    /* Callback service is inactive */
    SYS_TMR_CALLBACK_INACTIVE /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,

    /* Callback service is active */
    SYS_TMR_CALLBACK_ACTIVE /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/

} SYS_TMR_CALLBACK_STATUS;


// *****************************************************************************
/* SYS TMR State Machine States

   Summary
    Defines the various states that can be achieved by the driver operation.

   Description
    This enumeration defines the various states that can be achieved by the 
    driver operation.

   Remarks:
    None.
*/

typedef enum
{
    /* SYS TMR state busy */
    SYS_TMR_STATE_BUSY,

    /* SYS TMR state init */
    SYS_TMR_STATE_INIT,

    /* SYS TMR state alarm received */
    SYS_TMR_STATE_ALARM_RECEIVED,

    /* SYS TMR state wait for the reception of the alarm */
    SYS_TMR_STATE_WAIT_FOR_ALARM,

} SYS_TMR_STATES;


// *****************************************************************************
/* SYS TMR OBJECT INSTANCE structure

  Summary:
    System Timer object instance structure.

  Description:
    This data type defines the System Timer object instance.

  Remarks:
    None.
*/

typedef struct
{
    /* Driver Module index */
    SYS_MODULE_INDEX                    drvIndex;
    
    /* Client Handle */
    DRV_HANDLE                          clientHandle;

    /* The status of the SYS TMR Module */
    SYS_STATUS                          status;

    /* Alarm period in ms */
    uint32_t                            alarmPeriod;

    /* Queque event instance */
    QUEUE_OBJECT                        eventQ;

    /* Timer alarm count since it started */
    uint16_t                            tickCount;

    /* Timer alarm occurance overflow since it started */
    uint16_t                            tickOverflow;

    /* Timer State machine status */
    SYS_TMR_STATES                      state;

    /* Timer operating frequency */
    uint32_t                            sysTmrOperatingFreq;

} SYS_TMR_OBJECT;


// *****************************************************************************
/* Timer event register instance

  Summary
    Defines the structure required for maintaining the timer event.

  Description
    This defines the structure required for maintaining the timer event.

  Remarks:
    None
*/

typedef struct
{
    /* The delay as requested by the client in ticks */
    unsigned int                        period;

    /* The time elapsed since last event occured ticks */
    unsigned int                        elapsed;

    /* The number of event occured */
    uint32_t                            count;

    /* The status of the event */
    SYS_TMR_CALLBACK_STATUS             status;

    /* Callback type */
    SYS_TMR_CALLBACK_TYPE               type;

    /* Event callback */
    SYS_TMR_CALLBACK                    callback;

    /* Variable to hold the Queue element index */
    int8_t                              qElementIndex;

} SYS_TMR_CALLBACK_OBJECT;


// *****************************************************************************
// *****************************************************************************
// Section: Extern data Definitions
// *****************************************************************************
// *****************************************************************************


#endif //#ifndef _SYS_TMR_LOCAL_H

/*******************************************************************************
 End of File
*/

