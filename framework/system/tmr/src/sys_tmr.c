/*******************************************************************************
  Timer System Service Definition

  Company:
    Microchip Technology Inc.

  FileName:
    sys_tmr.c

  Summary:
    Timer System Service implementation.

  Description:
    The Timer System Service provides a simple interface to manage the Timer modules
    on Microchip microcontrollers.  This file implements the core interface routines 
    for the System Timer Service.
    While building the SYS TMR from source, ALWAYS use this file in the build.
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


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
 */

#include "system/tmr/src/sys_tmr_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope or Global Constants
// *****************************************************************************
// *****************************************************************************




// *****************************************************************************
// *****************************************************************************
// Section: Variable Definitions
// *****************************************************************************
// *****************************************************************************

/* System timer instance */
SYS_TMR_OBJECT              sSysTmrObject;

/* Queue which has the events as objects */
QUEUE_ELEMENT_OBJECT        sSysTMRQueueObjects [ SYS_TMR_MAX_PERIODIC_EVENTS ];

/* Status of event presence during single event configuration */
bool                        sSysTMRSingleEventStatus = false;

/* Event object array in sync with the Queue size */
SYS_TMR_CALLBACK_OBJECT     sCallbackObject [ SYS_TMR_MAX_PERIODIC_EVENTS ];

/* Event Index variable, used mainly in case of multiple events  */
uint8_t                     sIndex;

/* Delay Object */
SYS_TMR_CALLBACK_OBJECT     sDelayObject;

/* Delay Status */
SYS_TMR_DELAY_STATUS        sDelayStatus = SYS_TMR_DELAY_IDLE;


// *****************************************************************************
/* OSAL mutex declaration.

  Summary:
    Declares the OSAL mutex for periodic callback function.

  Description:
    This declares the OSAL mutex for periodic callback function.

  Remarks:
    None.
*/

OSAL_MUTEX_DECLARE(callbackPeriodicMutex);


// *****************************************************************************
/* OSAL mutex declaration.

  Summary:
    Declares the OSAL mutex for callback single function.

  Description:
    This declares the OSAL mutex for callback single function.

  Remarks:
    None.
*/

OSAL_MUTEX_DECLARE(callbackSingleMutex);


// *****************************************************************************
// *****************************************************************************
// Section: File scope Function Declarations
// *****************************************************************************
// *****************************************************************************


static void SYS_TMR_AlarmCallback ( void );

static void SYS_TMR_CallbackDeregister (QUEUE_ELEMENT_OBJECT * queueObject);


// *****************************************************************************
// *****************************************************************************
// Section: SYS TMR File Scope Function Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Function:
    static void SYS_TMR_AlarmCallback ( void )

  Summary:
    Alarm call back function.

  Description:
    This function is called when the time as registerd by the alarm is elapsed.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this
    function.

  Parameters:
    None.

  Returns:
    None.
*/

static void SYS_TMR_AlarmCallback ( void )
{
    /* Increment the alarm count */
    sSysTmrObject.tickCount++;

    /* Check for the roll over */
    if( sSysTmrObject.tickCount == 0 )
    {
        /* Indicate the overflow */
        sSysTmrObject.tickOverflow++;
    }

    /* Update the State machine state */
    sSysTmrObject.state = SYS_TMR_STATE_ALARM_RECEIVED;

} /* SYS_TMR_AlarmCallback */


// *****************************************************************************
/* Function:
    static void SYS_TMR_CallbackDeregister (QUEUE_ELEMENT_OBJECT * queueObject)

  Summary:
    Callback deregistering.

  Description:
    This routine deregisters a callback. This function frees the data
    structure associated with the corresponding event.

  Parameters:
    None.

  Returns:
    None.
*/

static void SYS_TMR_CallbackDeregister (QUEUE_ELEMENT_OBJECT * queueObject)
{
    SYS_TMR_CALLBACK_OBJECT * object;

    /* Point to event object */
    object = queueObject->data;

    /* Change the event status, to stop the event */
    object->status = SYS_TMR_CALLBACK_INACTIVE;
    object->callback = NULL;

    /* Remove the item from the Queue */
    queueObject->inUse = false;
    queueObject->data = NULL;

} /* SYS_TMR_CallbackDeregister */


// *****************************************************************************
// *****************************************************************************
// Section: SYS TMR Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function:
    SYS_MODULE_OBJ SYS_TMR_Initialize ( const SYS_MODULE_INDEX index,
                                        const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the instance of the Timer module and opens
    the specific module instance.

  Description:
    This function initializes hardware for the instance of the Timer module,
    using the specified hardware initialization data. It also initializes any
    internal data structures.

  Parameters:
    index           - Index for the instance to be initialized

    init            - Pointer to a data structure containing any data necessary
                      to initialize the driver. This pointer may be null if no
                      data is required because static overrides have been
                      provided.

  Returns:
    None
*/

SYS_MODULE_OBJ SYS_TMR_Initialize ( const SYS_MODULE_INDEX index,
                                    const SYS_MODULE_INIT * const init )
{
    SYS_TMR_INIT * sysTmrInit = ( SYS_TMR_INIT * ) init;

    /* Initial Status */
    sSysTmrObject.status = SYS_STATUS_BUSY;

    /* Create the required mutexes. */
    OSAL_ASSERT( (OSAL_MUTEX_Create(&callbackPeriodicMutex) == OSAL_RESULT_TRUE), 
                "Unable to create periodic callback mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&callbackSingleMutex) == OSAL_RESULT_TRUE),
                "Unable to create single callback mutex" );

    /* The status of the state machine is changed if the system is ready */
    sSysTmrObject.state             = SYS_TMR_STATE_INIT;
    sSysTmrObject.drvIndex          = sysTmrInit->drvIndex;
    sSysTmrObject.alarmPeriod       = sysTmrInit->alarmPeriod;

    /* Intialize the queue */
    QUEUE_Initialize( &sSysTmrObject.eventQ, SYS_TMR_MAX_PERIODIC_EVENTS, sSysTMRQueueObjects );

    /* Put state machine in initial state. */
    sSysTmrObject.state = SYS_TMR_STATE_INIT;

    /* Return dummy object */
    return (0);

} /* SYS_TMR_Initialize */


// *****************************************************************************
/* Function:
     void SYS_TMR_Reinitialize ( SYS_MODULE_OBJ object,
                                 const SYS_MODULE_INIT * const init )

   Summary:
     Reinitializes and refreshes the hardware for the instance of the Timer
     module.

   Description:
     This function reinitializes and refreshes the hardware for the instance
     of the TMR module using the specified hardware initialization data. It does
     not clear or reinitialize internal data structures.

  PreCondition:
     The SYS_TMR_Initialize function should have been called before calling
     this function.

  Parameters:
    object          - Identifies the SYS TMR Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware

   Returns:
     None.
*/

void SYS_TMR_Reinitialize ( SYS_MODULE_OBJ object, const SYS_MODULE_INIT * const init )
{
    SYS_TMR_INIT * sysTmrInit = ( SYS_TMR_INIT * ) init;

    /* Status update */
    sSysTmrObject.status = SYS_STATUS_UNINITIALIZED;

    /* Create the required mutexes. */
    OSAL_ASSERT( (OSAL_MUTEX_Create(&callbackPeriodicMutex) == OSAL_RESULT_TRUE), 
                 "Unable to create periodic mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Create(&callbackSingleMutex) == OSAL_RESULT_TRUE),
                 "Unable to create single callback mutex" );

    /* The status of the state machine is changed if the system is ready */
    sSysTmrObject.state             = SYS_TMR_STATE_INIT;
    sSysTmrObject.drvIndex          = sysTmrInit->drvIndex;
    sSysTmrObject.alarmPeriod       = sysTmrInit->alarmPeriod;

    /* Status update */
    sSysTmrObject.status = SYS_STATUS_READY;

} /* SYS_TMR_Reinitialize */


// *****************************************************************************
/* Function:
    void SYS_TMR_Deinitialize ( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the Timer module.

  Description:
    Deinitializes the specific module instance disabling its operation (and
    any hardware for driver modules). Resets all the internal data
    structures and fields for the specified instance to the default
    settings.

  PreCondition:
    The SYS_TMR_Initialize function should have been called before calling
    this function.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    None.
*/

void SYS_TMR_Deinitialize ( SYS_MODULE_OBJ object )
{
    /* Status update */
    sSysTmrObject.status = SYS_STATUS_UNINITIALIZED;

    /* Deleting the Mutexes */
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&callbackPeriodicMutex) == OSAL_RESULT_TRUE),
                 "Unable to delete periodic callback mutex" );
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&callbackSingleMutex) == OSAL_RESULT_TRUE), 
                 "Unable to delete single callback mutex" );

} /* SYS_TMR_Deinitialize */


// *****************************************************************************
/* Function:
    SYS_STATUS SYS_TMR_Status ( SYS_MODULE_OBJ object )

  Summary:
    Returns status of the specific module instance of the Timer module.

  Description:
    This function returns the status of the specific module instance disabling its 
    operation (and any hardware for driver modules).

  PreCondition:
    The SYS_TMR_Initialize function should have been called before calling
    this function.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    SYS_STATUS_READY    Indicates that any previous module operation for the
                        specified module has completed

    SYS_STATUS_BUSY     Indicates that a previous module operation for the
                        specified module has not yet completed

    SYS_STATUS_ERROR    Indicates that the specified module is in an error state
*/

SYS_STATUS SYS_TMR_Status ( SYS_MODULE_OBJ object )
{
    return ( sSysTmrObject.status );

} /* SYS_TMR_Status */


// *****************************************************************************
/* Function:
    void SYS_TMR_Tasks ( SYS_MODULE_OBJ object )

  Summary:
    Maintains the system Timer's state machine and implements its ISR.

  Description:
    This routine is used to maintain the system Timer's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Precondition:
    The SYS_TMR_Initialize function must have been called for the specified Timer
    driver instance.

  Parameters:
    object          - SYS TMR object handle, returned from SYS_TMR_Initialize

  Returns:
    None.
*/

void SYS_TMR_Tasks ( SYS_MODULE_OBJ object )
{
    uint8_t                     i;
    SYS_TMR_CALLBACK_OBJECT     * cbObject;
    uint32_t                    period;
    DRV_TMR_ALARM_CONFIG        alConf;

    switch ( sSysTmrObject.state )
    {
        case SYS_TMR_STATE_INIT:

            /* Open a TMR driver */
            sSysTmrObject.clientHandle =  (DRV_HANDLE)DRV_TMR_Open( sSysTmrObject.drvIndex, DRV_IO_INTENT_EXCLUSIVE );
            if (sSysTmrObject.clientHandle != DRV_HANDLE_INVALID)
            {
                /* Move to next state */
                sSysTmrObject.state  = SYS_TMR_STATE_BUSY;
            }

            /* Otherwise, stay here until the driver is opened */

            break;

        case SYS_TMR_STATE_BUSY:

            /* Check if the driver timer status is ready */
            if ( DRV_TMR_CLIENT_STATUS_READY == DRV_TMR_ClientStatus ( sSysTmrObject.clientHandle ) )
            {
                /* Clear the alarm count */
                sSysTmrObject.tickCount = 0;
                sSysTmrObject.tickOverflow = 0;

                /* Get the timer operating frequency to calculate the count value for the alarm */
                sSysTmrObject.sysTmrOperatingFreq = DRV_TMR_OperatingFrequencyGet (sSysTmrObject.clientHandle);

                /* Get the period value */
                period = (uint32_t) ( ( sSysTmrObject.alarmPeriod * sSysTmrObject.sysTmrOperatingFreq )/1000 );

                /* Set the alarm counter value */
                _SYS_TMR_PeriodSet ( sSysTmrObject.clientHandle, period );

                /* Configure Driver Alarm */
                alConf.type = DRV_TMR_ALARM_TYPE_PERIODIC;
                alConf.callback = &SYS_TMR_AlarmCallback;

                #if defined( DRV_TMR_ALARM_ENABLE )
                /* Set the alarm */
                DRV_TMR_AlarmSet ( sSysTmrObject.clientHandle, &alConf);
                #endif

                /* Start the timer */
                DRV_TMR_Start ( sSysTmrObject.clientHandle );

                /* Status of the state machine is changed to indicate initialization complete */
                sSysTmrObject.state = SYS_TMR_STATE_WAIT_FOR_ALARM;

                /* Status update */
                sSysTmrObject.status = SYS_TMR_RUNNING;
            }

            /* Otherwise, stay here untill the driver is ready */

            break;

        case SYS_TMR_STATE_ALARM_RECEIVED:

            for( i = 0 ; i < SYS_TMR_MAX_PERIODIC_EVENTS ; i++ )
            {
                if ( true == sSysTMRQueueObjects[i].inUse )
                {
                    cbObject = sSysTMRQueueObjects[i].data;

                    if ( SYS_TMR_CALLBACK_ACTIVE == cbObject->status )
                    {
                        /* If the status of the event is EVENT_RUNNING
                           then process the event to check if it has elapsed */
                        cbObject->elapsed++;

                        if ( cbObject->elapsed == cbObject->period )
                        {
                            /* The event is elapsed, increment the event count */
                            cbObject->elapsed = 0;
                            cbObject->count++;

                            if (SYS_TMR_CALLBACK_SINGLE == cbObject->type)
                            {
                                /* Call the corresponding event call back routine */
                                (cbObject->callback)();

                                /* De register the event it it is one shot */
                                SYS_TMR_CallbackDeregister (&sSysTMRQueueObjects[i]);
                            }
                            else if (SYS_TMR_CALLBACK_PERIODIC == cbObject->type)
                            {
                                /* Call the corresponding event call back routine */
                                (cbObject->callback)();
                            }
                            else // (SYS_TMR_CALLBACK_NONE == cbObject->type)
                            {
                                /* Indicate Delay Status to the Delay API */
                                sDelayStatus = SYS_TMR_DELAY_EXPIRED;
                            }
                        }
                    }
                }
            }

            /* Wait for the reception of the Alarm */
            sSysTmrObject.state = SYS_TMR_STATE_WAIT_FOR_ALARM;

            break;

        case SYS_TMR_STATE_WAIT_FOR_ALARM:
            break;

        default:
            break;

    }

} /* SYS_TMR_Tasks */


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

  Parameters:
    None.

  Returns:
    uint32_t      - alarm period in milli seconds
*/

uint32_t SYS_TMR_AlarmPeriodGet( void )
{
    return( sSysTmrObject.alarmPeriod );

} /* SYS_TMR_AlarmPeriodGet */


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_CallbackPeriodic (unsigned int period,
                                             SYS_TMR_CALLBACK callback)

  Summary:
    The Periodic callback is registered and started using this function.

  Description:
    This function registers the periodic callback service corresponding to the
    configuration paramenters passed by the user.

  Parameters:
    period      - Periodic delay in milliseconds
    callback    - Pointer to a callback routine that will be called periodically

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.

*/

SYS_TMR_HANDLE SYS_TMR_CallbackPeriodic (unsigned int period, SYS_TMR_CALLBACK callback)
{
    /* Variable to hold the Queue elment index */
    int8_t qElementIndex = SYS_TMR_HANDLE_INVALID;

    if (sIndex >= SYS_TMR_MAX_PERIODIC_EVENTS)
        return (SYS_TMR_HANDLE_INVALID);

    // OSAL Mutex Lock
    if (OSAL_MUTEX_Lock(callbackPeriodicMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
    {
        /* Assign the event parameters */
        sCallbackObject[sIndex].period         = ( (unsigned int)(period) / (sSysTmrObject.alarmPeriod) );
        sCallbackObject[sIndex].elapsed       = 0;
        sCallbackObject[sIndex].count         = 0;
        sCallbackObject[sIndex].status        = SYS_TMR_CALLBACK_ACTIVE;
        sCallbackObject[sIndex].type          = SYS_TMR_CALLBACK_PERIODIC;
        sCallbackObject[sIndex].callback      = callback;
    
        #if ( SYS_TMR_SINGLE_PERIODIC_EVENT == true )
            #if defined ( SYS_TMR_ERROR_TOLERANCE )
                if ( ( ( ( period % sSysTmrObject.alarmPeriod ) == 0 ) ||
                       ( ( period ) % ( sSysTmrObject.alarmPeriod + SYS_TMR_ERROR_TOLERANCE ) == 0 ) ||
                       ( ( period ) % ( sSysTmrObject.alarmPeriod - SYS_TMR_ERROR_TOLERANCE ) == 0 ) )
                     &&  sSysTMRSingleEventStatus != true )
            #else
                if ( ( ( period % sSysTmrObject.alarmPeriod ) == 0 )
                     &&  sSysTMRSingleEventStatus != true )
            #endif
                {
                    /* Register the event */
                    qElementIndex = QUEUE_Push( &sSysTmrObject.eventQ, &sCallbackObject[sIndex] );
                    /* The status is made true indicating one event registration is completed */
                    sSysTMRSingleEventStatus = true;
                    /* Event Index to be incremented, even though not used */
                    sIndex++;
                }
        #else // ( SYS_TMR_SINGLE_PERIODIC_EVENT == false )
            #if defined ( SYS_TMR_ERROR_TOLERANCE )
                if ( ( ( period % sSysTmrObject.alarmPeriod ) == 0 ) ||
                       ( ( period ) % ( sSysTmrObject.alarmPeriod + SYS_TMR_ERROR_TOLERANCE ) == 0 ) ||
                       ( ( period ) % ( sSysTmrObject.alarmPeriod - SYS_TMR_ERROR_TOLERANCE ) == 0 ) )
            #else
                if ( ( period % sSysTmrObject.alarmPeriod ) == 0 )
            #endif
                {
                    /* Register the event */
                    qElementIndex = QUEUE_Push( &sSysTmrObject.eventQ, &sCallbackObject[sIndex] );
                    /* Event Index to be incremented */
                    sIndex++;
                }
        #endif
        /* OSAL Mutex Unlock */
        OSAL_ASSERT( (OSAL_MUTEX_Unlock(callbackPeriodicMutex) == OSAL_RESULT_TRUE), 
                     "Unable to unlock periodic callback mutex" );
    }
    
    /* Return the callback handler */
    return ( qElementIndex );

} /* SYS_TMR_CallbackPeriodic */


// *****************************************************************************
/* Function:
    void SYS_TMR_CallbackStop (SYS_TMR_HANDLE handle)

  Summary:
    Stops the periodic callback service.

  Description:
    This function stops the previously registered periodic callbacks service.

  Parameters:
    handle      - A valid callback service handle, returned from the system
                  API SYS_TMR_CallbackPeriodic

  Returns:
    None.
*/

void SYS_TMR_CallbackStop (SYS_TMR_HANDLE handle)
{
    QUEUE_ELEMENT_OBJECT * queueObject;
    SYS_TMR_CALLBACK_OBJECT * object;

    /* Check for handle validity */
    if (SYS_TMR_HANDLE_INVALID == handle)
        return;

    queueObject = &sSysTMRQueueObjects[handle];

    /* Point to event object */
    object = queueObject->data;

    /* Change the event status, to stop the event */
    object->status = SYS_TMR_CALLBACK_INACTIVE;

} /* SYS_TMR_CallbackStop */


// *****************************************************************************
/* Function:
    uint32_t SYS_TMR_TickCountGet (void)

  Summary:
    Provides the current counter value.

  Description:
    This function provides the current counter value.

  Parameters:
    None.

  Returns:
    uint32_t - Current Timer count
*/

uint32_t SYS_TMR_TickCountGet (void)
{
    uint32_t tickCount;
    uint32_t CurTmrVal;

    /* Get the current TMR value */
    CurTmrVal = _SYS_TMR_CounterGet(sSysTmrObject.clientHandle);

    /* Calculate the tick count based on the SYS TMR ticks & other
       config parameters */
    tickCount = ( ((sSysTmrObject.tickCount) * (sSysTmrObject.alarmPeriod)) +
                  (CurTmrVal % (sSysTmrObject.alarmPeriod)) );

    /* Returns the alarm count value */
    return ( tickCount );

} /* SYS_TMR_TickCountGet */


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_CallbackSingle (unsigned int period, SYS_TMR_CALLBACK callback)

  Summary:
    The one-shot/single callback is registered and started using this function.

  Description:
    This routine registers a one-shot/single callback service corresponding to
    the configuration paramenters passed by the user.

  Parameters:
    period      - Periodic delay in milliseconds
    callback    - Pointer to a callback routine that will be called periodically

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.
*/

SYS_TMR_HANDLE SYS_TMR_CallbackSingle (unsigned int period, SYS_TMR_CALLBACK callback)
{
    /* Variable to hold the Queue elment index */
    int8_t qElementIndex = SYS_TMR_HANDLE_INVALID;

    if (sIndex >= SYS_TMR_MAX_PERIODIC_EVENTS)
        return SYS_TMR_HANDLE_INVALID;

    /* OSAL Mutex Lock */
    if (OSAL_MUTEX_Lock(callbackSingleMutex, OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
    {
        /* Assign the event parameters */
        sCallbackObject[sIndex].period        = ( (unsigned int)(period) / (sSysTmrObject.alarmPeriod) );
        sCallbackObject[sIndex].elapsed       = 0;
        sCallbackObject[sIndex].count         = 0;
        sCallbackObject[sIndex].status        = SYS_TMR_CALLBACK_ACTIVE;
        sCallbackObject[sIndex].type          = SYS_TMR_CALLBACK_SINGLE;
        sCallbackObject[sIndex].callback      = callback;
    
        #if defined ( SYS_TMR_ERROR_TOLERANCE )
            if ( ( ( period % sSysTmrObject.alarmPeriod ) == 0 ) ||
                   ( ( period ) % ( sSysTmrObject.alarmPeriod + SYS_TMR_ERROR_TOLERANCE ) == 0 ) ||
                   ( ( period ) % ( sSysTmrObject.alarmPeriod - SYS_TMR_ERROR_TOLERANCE ) == 0 ) )
        #else
            if ( ( period % sSysTmrObject.alarmPeriod ) == 0 )
        #endif
            {
                /* Register the event */
                qElementIndex = QUEUE_Push( &sSysTmrObject.eventQ, &sCallbackObject[sIndex] );
                /* Event Index to be incremented */
                sIndex++;
            }
        /* OSAL Mutex Unlock */
        OSAL_ASSERT( (OSAL_MUTEX_Unlock(callbackSingleMutex) == OSAL_RESULT_TRUE),
                     "Unable to unlock singl callback mutex" );
    }
    
    /* Return the callback handler */
    return ( qElementIndex );

} /* SYS_TMR_CallbackSingle */


// *****************************************************************************
/* Function:
    SYS_TMR_HANDLE SYS_TMR_DelayMS (unsigned int delay)

  Summary:
    Registers an event for the specified delay.

  Description:
    This function registers an event for the specified delay.
    This is a blocking functional call. Calling this function will
    generate a delay as specified in the delay paramenter.

  Precondition:
    The SYS_TMR_Initialize function should have been called before calling this
    function.

  Parameters:
    delay   - Indicates the delay required in milliseconds

  Returns:
    A valid event handler of type SYS_TMR_HANDLE is returned.
*/

SYS_TMR_HANDLE SYS_TMR_DelayMS (unsigned int delay)
{
    /* Variable to hold the Queue elment index */
    int8_t qElementIndex = SYS_TMR_HANDLE_INVALID;

    if (SYS_TMR_CALLBACK_ACTIVE == sDelayObject.status)
        return (SYS_TMR_HANDLE_INVALID);

    #if (true == SYS_TMR_INTERRUPT_MODE)

        /* Assign the event parameters */
        sDelayObject.period          = ( (unsigned int)delay / (sSysTmrObject.alarmPeriod) );
        sDelayObject.elapsed        = 0;
        sDelayObject.count          = 0;
        sDelayObject.status         = SYS_TMR_CALLBACK_ACTIVE;
        sDelayObject.type           = SYS_TMR_CALLBACK_NONE;
        sDelayObject.callback       = NULL;

        /* Register a event */
        qElementIndex = (uint8_t) QUEUE_Push (&sSysTmrObject.eventQ, &sDelayObject);
    #else      //Primitive Blocking Mode
    if(delay)
    {
        uint32_t sysClk = SYS_CLK_PRIMARY_CLOCK;
        uint32_t t0;
        #if   defined (__C32__)
        t0 = _CP0_GET_COUNT();
        while (_CP0_GET_COUNT() - t0 < (sysClk/2000)*delay);
        #elif defined (__C30__)
        t0 = ReadTimer23();
        while (ReadTimer23() -  t0 < (sysClk/2000)*mSec);
        #else
        #error "Neither __C32__ nor __C30__ is defined!"
        #endif
    }
    #endif

    /* Return the delay handler */
    return ( qElementIndex );

} /* SYS_TMR_DelayMS */


// *****************************************************************************
/* Function:
    SYS_TMR_DELAY_STATUS SYS_TMR_DelayStatusGet (SYS_TMR_HANDLE handle)

  Summary:
    Intimates if the previously configured delay has elapsed.

  Description:
    This function intimates if the previously configured delay has elapsed.

  Parameters:
    handle      - A valid callback service handle, returned from the system
                  API SYS_TMR_DelayMS

  Returns:
    One of the possible values of SYS_TMR_DELAY_STATUS.
*/

SYS_TMR_DELAY_STATUS SYS_TMR_DelayStatusGet (SYS_TMR_HANDLE handle)
{
    /* Default status as false */
    SYS_TMR_DELAY_STATUS status = SYS_TMR_DELAY_NOT_EXPIRED;

    /* Check for handle validity */
    if (SYS_TMR_HANDLE_INVALID == handle)
        return SYS_TMR_HANDLE_INVALID;

    if (SYS_TMR_DELAY_EXPIRED == sDelayStatus)
    {
        /* Deregister the event */
        SYS_TMR_CallbackDeregister (&sSysTMRQueueObjects[handle]);
        /* Time not elapsed */
        sDelayStatus = SYS_TMR_DELAY_IDLE;
        /* Update status information */
        status = SYS_TMR_DELAY_EXPIRED;
    }

    return (status);

} /* SYS_TMR_DelayStatusGet */



/*******************************************************************************
End of File
*/

