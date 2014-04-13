/*******************************************************************************
  Timer System Service Interface Definition

  Company:
    Microchip Technology Inc.

  File Name:
    sys_tmr.h

  Summary:
    Timer System Service interface definition.

  Description:
    This file contains the interface definition for the Timer System
    Service.  It provides a way to interact with the Timer subsystem to
    manage the timing requests supported by the system.
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

#ifndef _SYS_TMR_H
#define _SYS_TMR_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "driver/tmr/drv_tmr.h"         // TMR Driver Library Header
#include "system/common/sys_queue.h"    // SYS Queue header
#include "system/clk/sys_clk.h"


// *****************************************************************************
// *****************************************************************************
// Section: SYS TMR Data Types
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* SYS Timer Module Index Numbers

  Summary:
    Timer System Service index definitions.

  Description:
    These constants provide Timer System Service index definitions.

  Remarks:
    These constants should be used in place of hard-coded numeric literals.

*/

#define SYS_TMR_INDEX_0                 0


// *****************************************************************************
/* SYS Timer Module specific Status

  Summary:
    Identifies the current status/state of the system timer.

  Description:
    This enumeration identifies the current status/state of the system timer.

  Remarks:
    This enumeration is the return type for the system-level status routine
    defined by each device driver or system module (for example:
    SYS_TMR_Status).
*/

#define SYS_TMR_RUNNING                 (SYS_STATUS_READY + 1)


// *****************************************************************************
/* SYS Timer invalid handle macro definition

  Summary:
    Identifies the invalid handle of the system timer.

  Description:
    This enumeration identifies the invalid handle of the system timer.

  Remarks:
    None.
*/

#define SYS_TMR_HANDLE_INVALID          ((int8_t)-1)


// *****************************************************************************
/* SYS TMR Handle

  Summary
    Identifies a particular registered event instance.

  Description
    This event handle identifies a registered instance of an event. Every time
    the application that tries to access the paramateres with respect to
    a particular event, shall used this event handle to refer to that
    event.

  Remarks:
    None.
*/

typedef int8_t SYS_TMR_HANDLE;


// *****************************************************************************
/* SYS TMR Callback Function

  Summary
    Defines a pointer to a callback function.

  Description
    This data type defines a pointer callback function.

  Remarks:
    None.
*/

typedef void ( * SYS_TMR_CALLBACK ) ( void );


// *****************************************************************************
/* SYS TMR Initialize structure

  Summary:
    Identifies the system timer initialize structure.

  Description:
    This structure identifies the system timer initialize structure.

  Remarks:
    None.
*/

typedef struct
{
    /* System module initialization */
    SYS_MODULE_INIT                 moduleInit;

    /* Driver Module index */
    SYS_MODULE_INDEX                drvIndex;
    
    /* Alarm period in ms */
    uint32_t                        alarmPeriod;

} SYS_TMR_INIT;


// *****************************************************************************
/* Callback service type enumeration

  Summary:
    Defines the callback service type.

  Description:
    This data type defines the callback service type.

  Remarks:
    None.
*/

typedef enum
{
    /* Delay Idle */
    SYS_TMR_DELAY_IDLE /*DOM-IGNORE-BEGIN*/ = 0 /*DOM-IGNORE-END*/,

    /* Delay Expired */
    SYS_TMR_DELAY_EXPIRED /*DOM-IGNORE-BEGIN*/ = 1 /*DOM-IGNORE-END*/,

    /* Delay not yet expired */
    SYS_TMR_DELAY_NOT_EXPIRED /*DOM-IGNORE-BEGIN*/ = 2 /*DOM-IGNORE-END*/,

    /* delay error */
    SYS_TMR_DELAY_ERROR /*DOM-IGNORE-BEGIN*/ = 3 /*DOM-IGNORE-END*/

} SYS_TMR_DELAY_STATUS;



// *****************************************************************************
// *****************************************************************************
// Section: SYS TMR Module Initialization Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ SYS_TMR_Initialize( const SYS_MODULE_INDEX           index,
                                       const SYS_MODULE_INIT * const    init )

  Summary:
    Initializes hardware and data for the instance of the Timer module and opens
    the specific module instance.

  Description:
    This function initializes hardware for the instance of the Timer module,
    using the specified hardware initialization data. It also initializes any
    internal data structures.

  Precondition:
    None.

  Parameters:
    index           - Index for the instance to be initialized

    init            - Pointer to a data structure containing any data necessary
                      to initialize the sys timer. This pointer may be null if no
                      data is required because static overrides have been
                      provided.

  Returns:
    If successful, returns a valid handle to an object.  Otherwise, it
    returns SYS_MODULE_OBJ_INVALID. The returned object must be passed as
    argument to SYS_TMR_Reinitialize, SYS_TMR_Deinitialize, SYS_TMR_Tasks and
    SYS_TMR_Status routines.

  Example:
    <code>
    SYS_MODULE_OBJ  objectHandle;
    SYS_TMR_INIT    initConfig;

    // Populate the timer initialization structure
    initConfig.moduleInit.value     = SYS_MODULE_POWER_RUN_FULL;
    initConfig.drvIndex             = DRV_TMR_INDEX_0;
    initConfig.alarmPeriod          = 100;

    objectHandle = SYS_TMR_Initialize (SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&initConfig);
    if (SYS_MODULE_OBJ_INVALID == objectHandle)
    {
        // Handle error
    }
    <code>

  Remarks:
    This routine should only be called once during system initialization
    unless SYS_TMR_Deinitialize is first called to deinitialize the device
    instance before reinitializing it. If the system was already initialized
    it safely returns without causing any disturbance.
*/

SYS_MODULE_OBJ SYS_TMR_Initialize( const SYS_MODULE_INDEX           index,
                                   const SYS_MODULE_INIT * const    init );


// *****************************************************************************
/* Function:
    void SYS_TMR_Reinitialize( SYS_MODULE_OBJ                  object,
                               const SYS_MODULE_INIT * const   init )

   Summary:
    Reinitializes and refreshes the hardware for the instance of the Timer
    module.

   Description:
    This function reinitializes and refreshes the hardware for the instance
    of the Timer module using the supplied data. It modifies the internal data
    structure.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - Identifies the SYS TMR Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware

   Returns:
    None

   Example:
    <code>
    SYS_MODULE_OBJ  objectHandle;
    SYS_TMR_INIT    initConfig;
    SYS_STATUS      tmrStatus;

    // Populate the timer initialization structure
    initConfig.moduleInit.value     = SYS_MODULE_POWER_RUN_FULL;
    initConfig.drvIndex             = DRV_TMR_INDEX_0;
    initConfig.alarmPeriod          = 100;

    SYS_TMR_Reinitialize (objectHandle, (SYS_MODULE_INIT*)&initConfig);

    tmrStatus = SYS_TMR_Status (object);
    if (SYS_STATUS_BUSY == tmrStatus)
    {
        // Check again later to ensure the driver is ready
    }
    else if (SYS_STATUS_ERROR >= tmrStatus)
    {
        // Handle error
    }
    <code>

   Remarks:
    This operation uses the same initialization data structure as the
    SYS_TMR_Initialize operation. This operation can be used to change the
    power state of a TMR module. This function can be called multiple times
    to reinitialize the module. This operation uses the same initialization
    data structure as the Initialize operation. This operation can also be
    used to refresh the hardware registers as defined by the initialization
    data.
*/

void SYS_TMR_Reinitialize( SYS_MODULE_OBJ                   object,
                           const SYS_MODULE_INIT * const    init );


// *****************************************************************************
/* Function:
    void SYS_TMR_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the TMR module

  Description:
    This function deinitializes the specific module instance disabling its operation 
    (and any hardware for driver modules). Resets all of the internal data
    structures and fields for the specified instance to the default settings.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    None.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     //  Returned from SYS_TMR_Initialize
    SYS_STATUS          status;

    SYS_TMR_Deinitialize (object);

    status = SYS_TMR_Status (object);
    if (SYS_MODULE_DEINITIALIZED == status)
    {
        // Check again later if you need to know
        // when the SYS TMR is deinitialized.
    }
    <code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize
    operation must be called before the Initialize operation can be called
    again.
*/

void SYS_TMR_Deinitialize( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    SYS_STATUS SYS_TMR_Status( SYS_MODULE_OBJ object )

  Summary:
    Returns status of the specific instance of the Timer module.

  Description:
    This function returns the status of the specific module instance disabling its 
    operation (and any hardware for driver modules).

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    SYS_STATUS_READY          - Indicates that the driver is busy with a
                                previous system level operation and cannot start
                                another

                                Note: Any value greater than SYS_STATUS_READY is
                                also a normal running state in which the driver
                                is ready to accept new operations

    SYS_STATUS_BUSY           - Indicates that the driver is busy with a
                                previous system level operation and cannot start
                                another

    SYS_STATUS_ERROR          - Indicates that the driver is in an error state

                                Note: Any value less than SYS_STATUS_ERROR is
                                also an error state.

    SYS_MODULE_DEINITIALIZED  - Indicates that the driver has been
                                de-initialized

                                Note:  This value is less than SYS_STATUS_ERROR.

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from SYS_TMR_Initialize
    SYS_STATUS          tmrStatus;

    tmrStatus = SYS_TMR_Status (object);
    else if (SYS_STATUS_ERROR >= tmrStatus)
    {
        // Handle error
    }
    <code>

  Remarks:
    Once the Initialize operation has been called, the Deinitialize
    operation must be called before the Initialize operation can be called
    again.
*/

SYS_STATUS SYS_TMR_Status( SYS_MODULE_OBJ object );


// *****************************************************************************
/* Function:
    void SYS_TMR_Tasks( SYS_MODULE_OBJ object )

  Summary:
    Maintains the system timer's state machine and implements its ISR.

  Description:
    This function is used to maintain the system timer's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Precondition:
    The SYS_TMR_Initialize function must have been called for the specified TMR
    driver instance.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    None

  Example:
    <code>
    SYS_MODULE_OBJ      object;     // Returned from SYS_TMR_Initialize

    while (true)
    {
        SYS_TMR_Tasks (object);

        // Do other tasks
    }
    </code>

  Remarks:
    This function is normally not called directly by an application.  It is
    called by the system's Tasks routine (SYS_Tasks) or by the apropriate raw
    ISR.
*/

void SYS_TMR_Tasks( SYS_MODULE_OBJ object );

    
// *****************************************************************************
// *****************************************************************************
// Section: SYS TMR Client Setup Routines
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    uint32_t SYS_TMR_AlarmPeriodGet( void )

  Summary:
    Returns the previously configured alarm period.

  Description:
    This function obtains the previously configured alarm period.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    None.

  Returns:
    uint32_t      - Alarm period in milliseconds

  Example:
    <code>
    uint32_t period;
    period = SYS_TMR_AlarmPeriodGet();
    <code>

  Remarks:
    None.
*/

uint32_t SYS_TMR_AlarmPeriodGet( void );


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_CallbackPeriodic( unsigned int       period,
                                             SYS_TMR_CALLBACK   callback )

  Summary:
    The Periodic callback is registered and started using this function.

  Description:
    This function registers the periodic callback service corresponding to the
    configuration paramenters passed by the user.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    period      - Periodic delay in milliseconds
    callback    - Pointer to a callback routine that will be called periodically

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.

  Example:
    <code>
    SYS_TMR_HANDLE handle;
    unsigned int period = 20;

    void Test_Callback1 (void);

    handle = SYS_TMR_CallbackPeriodic (period, &Test_Callback1);
    <code>

  Remarks:
    The Period chosen should be a multiple of the driver's alarm period. For example,
    if the alarm period is 10 ms, the period should be a multiple of 10.
*/

SYS_TMR_HANDLE SYS_TMR_CallbackPeriodic( unsigned int       period,
                                         SYS_TMR_CALLBACK   callback );


// *****************************************************************************
/* Function:
    void SYS_TMR_CallbackStop( SYS_TMR_HANDLE handle )

  Summary:
    Stops the periodic callback service.

  Description:
    This function stops the previously registered periodic callbacks service.

  Precondition:
    The SYS_TMR_CallbackPeriodic function should have been called before calling this 
    function.

  Parameters:
    handle      - A valid callback service handle, returned from the system
                  API SYS_TMR_CallbackPeriodic

  Returns:
    None.

  Example:
    <code>
    SYS_TMR_HANDLE handle;
    uint16_t period = 20;

    void Test_Callback1 (void);

    handle = SYS_TMR_CallbackPeriodic (period, &Test_Callback1);
    ...
    ...
    SYS_TMR_CallbackStop (handle);
    <code>


  Remarks:
    None.
*/

void SYS_TMR_CallbackStop( SYS_TMR_HANDLE handle );

void SYS_TMR_RemoveCallback(SYS_TMR_HANDLE handle);

// *****************************************************************************
/* Function:
    uint32_t SYS_TMR_TickCountGet( void )

  Summary:
    Provides the current counter value.

  Description:
    This function provides the current counter value.

  Precondition:
    The SYS_TMR_CallbackPeriodic function should have been called before calling this
    function.

  Parameters:
    None.

  Returns:
    uint32_t - Current system timer tick count value

  Example:
    <code>
    uint32_t count;
    count = SYS_TMR_TickCountGet ();
    <code>

  Remarks:
    None.
*/

uint32_t SYS_TMR_TickCountGet( void );


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_CallbackSingle( unsigned int period, SYS_TMR_CALLBACK callback )

  Summary:
    The one-shot/single callback is registered and started using this function.

  Description:
    This function registers a one-shot/single callback service corresponding to
    the configuration paramenters passed by the user.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this 
    function.

  Parameters:
    period      - Periodic delay in milliseconds
    callback    - Pointer to a callback routine which will be called periodically

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.

  Example:
    <code>
    SYS_TMR_HANDLE handle;
    unsigned int period = 20;
    void Test_Callback1 (void);

    handle = SYS_TMR_CallbackSingle (period, &Test_Callback1);
    <code>

  Remarks:
    None.
*/

SYS_TMR_HANDLE SYS_TMR_CallbackSingle( unsigned int period, SYS_TMR_CALLBACK callback );


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_DelayMS( unsigned int delay )

  Summary:
    Registers an event for the specified delay.

  Description:
    This function registers an event for the specified delay.
    
  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this
    function.

  Parameters:
    delay   - Indicates the delay required in milliseconds

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.

  Example:
    <code>
    SYS_TMR_DelayStart (50);
    <code>

  Remarks:
    Works only in Interrupt mode.
*/

SYS_TMR_HANDLE SYS_TMR_DelayMS( unsigned int delay );


// *****************************************************************************
/* Function:
    SYS_TMR_DELAY_STATUS SYS_TMR_DelayStatusGet( SYS_TMR_HANDLE handle )

  Summary:
    Intimates if the previously configured delay has elapsed.

  Description:
    This function intimates if the previously configured delay has elapsed.

  Precondition:
    The SYS_TMR_DelayStart function should have been called before calling this
    function.

  Parameters:
    handle      - A valid callback service handle, returned from the system
                  API SYS_TMR_DelayMS

  Returns:
    One of the possible values of SYS_TMR_DELAY_STATUS.

  Example:
    <code>
    if (SYS_TMR_DELAY_EXPIRED == SYS_TMR_DelayStatusGet ())
        // Do Something
    <code>

  Remarks:
    None.
*/

SYS_TMR_DELAY_STATUS SYS_TMR_DelayStatusGet( SYS_TMR_HANDLE handle );



#endif //_SYS_TMR_H

/*******************************************************************************
 End of File
*/

