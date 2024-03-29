/*
	OpenRTOS V7.6.0  Copyright (C) Real Time Engineers ltd. All rights reserved.

    WITTENSTEIN High Integrity Systems is the exclusive provider of OpenRTOS licenses.

    The use, alteration and copying of OpenRTOS is subject to the terms of the 
    license granted to your organization. Licenses are royalty free.

    Licenses may limit scope of activities using OpenRTOS and the business unit(s)
    in your organisation which may carry out these activities. It may also limit 
    the processor, compiler and number of different products in which OpenRTOS 
    can be used.

    The license also contains details of warranties, support and maintenance 
    provisions where these are applicable.

    Please refer to the license provided with the installation of the software 
    for details.

	WITTENSTEIN high integrity systems is a trading name of WITTENSTEIN
	aerospace & simulation ltd, Registered Office: Brown's Court, Long Ashton
	Business Park, Yanley Lane, Long Ashton, Bristol, BS41 9LB, UK.
	Tel: +44 (0) 1275 395 600, fax: +44 (0) 1275 393 630. 
	E-mail: info@HighIntegritySystems.com
	Registered in England No. 3711047; VAT No. GB 729 1583 15

	http://www.HighIntegritySystems.com
*/

/*-----------------------------------------------------------
 * Implementation of functions defined in portable.h for the PIC32MX port.
  *----------------------------------------------------------*/

#ifndef __XC
    #error This port is designed to work with XC32.  Please update your C compiler version.
#endif

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* Hardware specifics. */
#define portTIMER_PRESCALE	8
#define portPRESCALE_BITS	1

/* Bits within various registers. */
#define portIE_BIT						( 0x00000001 )
#define portEXL_BIT						( 0x00000002 )

/* Bits within the CAUSE register. */
#define portCORE_SW_0					( 0x00000100 )
#define portCORE_SW_1					( 0x00000200 )

/* The EXL bit is set to ensure interrupts do not occur while the context of
the first task is being restored. */
#define portINITIAL_SR					( portIE_BIT | portEXL_BIT )

/*
By default port.c generates its tick interrupt from TIMER1.  The user can
override this behaviour by:
	1: Providing their own implementation of vApplicationSetupTickTimerInterrupt(),
	   which is the function that configures the timer.  The function is defined
	   as a weak symbol in this file so if the same function name is used in the
	   application code then the version in the application code will be linked
	   into the application in preference to the version defined in this file.
	2: Define configTICK_INTERRUPT_VECTOR to the vector number of the timer used
	   to generate the tick interrupt.  For example, when timer 1 is used then
	   configTICK_INTERRUPT_VECTOR is set to _TIMER_1_VECTOR.
	   configTICK_INTERRUPT_VECTOR should be defined in FreeRTOSConfig.h.
	3: Define configCLEAR_TICK_TIMER_INTERRUPT() to clear the interrupt in the
	   timer used to generate the tick interrupt.  For example, when timer 1 is
	   used configCLEAR_TICK_TIMER_INTERRUPT() is defined to
	   IFS0CLR = _IFS0_T1IF_MASK.
*/
#ifndef configTICK_INTERRUPT_VECTOR
	#define configTICK_INTERRUPT_VECTOR _TIMER_1_VECTOR
	#define configCLEAR_TICK_TIMER_INTERRUPT() IFS0CLR = _IFS0_T1IF_MASK
#else
	#ifndef configCLEAR_TICK_TIMER_INTERRUPT
		#error If configTICK_INTERRUPT_VECTOR is defined in application code then configCLEAR_TICK_TIMER_INTERRUPT must also be defined in application code.
	#endif
#endif

/* Let the user override the pre-loading of the initial RA with the address of
prvTaskExitError() in case is messes up unwinding of the stack in the
debugger - in which case configTASK_RETURN_ADDRESS can be defined as 0 (NULL). */
#ifdef configTASK_RETURN_ADDRESS
	#define portTASK_RETURN_ADDRESS	configTASK_RETURN_ADDRESS
#else
	#define portTASK_RETURN_ADDRESS	prvTaskExitError
#endif

/* Set configCHECK_FOR_STACK_OVERFLOW to 3 to add ISR stack checking to task
stack checking.  A problem in the ISR stack will trigger an assert, not call the
stack overflow hook function (because the stack overflow hook is specific to a
task stack, not the ISR stack). */
#if( configCHECK_FOR_STACK_OVERFLOW > 2 )

	/* Don't use 0xa5 as the stack fill bytes as that is used by the kernerl for
	the task stacks, and so will legitimately appear in many positions within
	the ISR stack. */
	#define portISR_STACK_FILL_BYTE	0xee

	static const unsigned char ucExpectedStackBytes[] = {
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE,		\
									portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE, portISR_STACK_FILL_BYTE };	\

	#define portCHECK_ISR_STACK() configASSERT( ( memcmp( ( void * ) xISRStack, ( void * ) ucExpectedStackBytes, sizeof( ucExpectedStackBytes ) ) == 0 ) )
#else
	/* Define the function away. */
	#define portCHECK_ISR_STACK()
#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

/*-----------------------------------------------------------*/


/*
 * Place the prototype here to ensure the interrupt vector is correctly installed.
 * Note that because the interrupt is written in assembly, the IPL setting in the
 * following line of code has no effect.  The interrupt priority is set by the
 * call to ConfigIntTimer1() in vApplicationSetupTickTimerInterrupt().
 */
extern void __attribute__( (interrupt(ipl1), vector( configTICK_INTERRUPT_VECTOR ))) vPortTickInterruptHandler( void );

/*
 * The software interrupt handler that performs the yield.  Note that, because
 * the interrupt is written in assembly, the IPL setting in the following line of
 * code has no effect.  The interrupt priority is set by the call to
 * mConfigIntCoreSW0() in xPortStartScheduler().
 */
void __attribute__( (interrupt(ipl1), vector(_CORE_SOFTWARE_0_VECTOR))) vPortYieldISR( void );

/*
 * Used to catch tasks that attempt to return from their implementing function.
 */
static void prvTaskExitError( void );

/*-----------------------------------------------------------*/

/* Records the interrupt nesting depth.  This is initialised to one as it is
decremented to 0 when the first task starts. */
volatile unsigned portBASE_TYPE uxInterruptNesting = 0x01;

/* Stores the task stack pointer when a switch is made to use the system stack. */
unsigned portBASE_TYPE uxSavedTaskStackPointer = 0;

/* The stack used by interrupt service routines that cause a context switch. */
portSTACK_TYPE xISRStack[ configISR_STACK_SIZE ] = { 0 };

/* The top of stack value ensures there is enough space to store 6 registers on
the callers stack, as some functions seem to want to do this. */
const portSTACK_TYPE * const xISRStackTop = &( xISRStack[ configISR_STACK_SIZE - 7 ] );

/*-----------------------------------------------------------*/

/*
 * See header file for description.
 */
portSTACK_TYPE *pxPortInitialiseStack( portSTACK_TYPE *pxTopOfStack, pdTASK_CODE pxCode, void *pvParameters )
{
	/* Ensure byte alignment is maintained when leaving this function. */
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) 0xDEADBEEF;
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) 0x12345678;	/* Word to which the stack pointer will be left pointing after context restore. */
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) _CP0_GET_CAUSE();
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) portINITIAL_SR;/* CP0_STATUS */
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) pxCode; 		/* CP0_EPC */
	pxTopOfStack--;

	*pxTopOfStack = (portSTACK_TYPE) portTASK_RETURN_ADDRESS;	/* ra */
	pxTopOfStack -= 15;

	*pxTopOfStack = (portSTACK_TYPE) pvParameters; /* Parameters to pass in. */
	pxTopOfStack -= 15;

	return pxTopOfStack;
}
/*-----------------------------------------------------------*/

static void prvTaskExitError( void )
{
	/* A function that implements a task must not exit or attempt to return to
	its caller as there is nothing to return to.  If a task wants to exit it
	should instead call vTaskDelete( NULL ).

	Artificially force an assert() to be triggered if configASSERT() is
	defined, then stop here so application writers can catch the error. */
	configASSERT( uxSavedTaskStackPointer == 0UL );
	portDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

/*
 * Setup a timer for a regular tick.  This function uses peripheral timer 1.
 * The function is declared weak so an application writer can use a different
 * timer by redefining this implementation.  If a different timer is used then
 * configTICK_INTERRUPT_VECTOR must also be defined in FreeRTOSConfig.h to
 * ensure the RTOS provided tick interrupt handler is installed on the correct
 * vector number.  When Timer 1 is used the vector number is defined as
 * _TIMER_1_VECTOR.
 */
__attribute__(( weak )) void vApplicationSetupTickTimerInterrupt( void )
{
const unsigned long ulCompareMatch = ( (configPERIPHERAL_CLOCK_HZ / portTIMER_PRESCALE) / configTICK_RATE_HZ ) - 1;

	T1CON = 0x0000;
	T1CONbits.TCKPS = portPRESCALE_BITS;
	PR1 = ulCompareMatch;
	IPC1bits.T1IP = configKERNEL_INTERRUPT_PRIORITY;

	/* Clear the interrupt as a starting condition. */
	IFS0bits.T1IF = 0;

	/* Enable the interrupt. */
	IEC0bits.T1IE = 1;

	/* Start the timer. */
	T1CONbits.TON = 1;
}
/*-----------------------------------------------------------*/

void vPortEndScheduler(void)
{
	/* It is unlikely that the scheduler for the PIC port will get stopped
	once running.  If required disable the tick interrupt here, then return
	to xPortStartScheduler(). */
	for( ;; );
}
/*-----------------------------------------------------------*/

portBASE_TYPE xPortStartScheduler( void )
{
extern void vPortStartFirstTask( void );
extern void *pxCurrentTCB;

	#if ( configCHECK_FOR_STACK_OVERFLOW > 2 )
	{
		/* Fill the ISR stack to make it easy to asses how much is being used. */
		memset( ( void * ) xISRStack, portISR_STACK_FILL_BYTE, sizeof( xISRStack ) );
	}
	#endif /* configCHECK_FOR_STACK_OVERFLOW > 2 */

	/* Clear the software interrupt flag. */
	IFS0CLR = _IFS0_CS0IF_MASK;

	/* Set software timer priority. */
	IPC0CLR = _IPC0_CS0IP_MASK;
	IPC0SET = ( configKERNEL_INTERRUPT_PRIORITY << _IPC0_CS0IP_POSITION );

	/* Enable software interrupt. */
	IEC0CLR = _IEC0_CS0IE_MASK;
	IEC0SET = 1 << _IEC0_CS0IE_POSITION;

	/* Setup the timer to generate the tick.  Interrupts will have been
	disabled by the time we get here. */
	vApplicationSetupTickTimerInterrupt();

	/* Kick off the highest priority task that has been created so far.
	Its stack location is loaded into uxSavedTaskStackPointer. */
	uxSavedTaskStackPointer = *( unsigned portBASE_TYPE * ) pxCurrentTCB;
	vPortStartFirstTask();

	/* Should never get here as the tasks will now be executing!  Call the task
	exit error function to prevent compiler warnings about a static function
	not being called in the case that the application writer overrides this
	functionality by defining configTASK_RETURN_ADDRESS. */
	prvTaskExitError();

	return pdFALSE;
}
/*-----------------------------------------------------------*/

void vPortIncrementTick( void )
{
unsigned portBASE_TYPE uxSavedStatus;

	uxSavedStatus = uxPortSetInterruptMaskFromISR();
	{
		if( xTaskIncrementTick() != pdFALSE )
		{
			/* Pend a context switch. */
			_CP0_BIS_CAUSE( portCORE_SW_0 );
		}
	}
	vPortClearInterruptMaskFromISR( uxSavedStatus );

	/* Look for the ISR stack getting near or past its limit. */
	portCHECK_ISR_STACK();

	/* Clear timer interrupt. */
	configCLEAR_TICK_TIMER_INTERRUPT();
}
/*-----------------------------------------------------------*/

unsigned portBASE_TYPE uxPortSetInterruptMaskFromISR( void )
{
unsigned portBASE_TYPE uxSavedStatusRegister;

	__builtin_disable_interrupts();
	uxSavedStatusRegister = _CP0_GET_STATUS() | 0x01;
	/* This clears the IPL bits, then sets them to
	configMAX_SYSCALL_INTERRUPT_PRIORITY.  This function should not be called
	from an interrupt that has a priority above
	configMAX_SYSCALL_INTERRUPT_PRIORITY so, when used correctly, the action
	can only result in the IPL being unchanged or raised, and therefore never
	lowered. */
	_CP0_SET_STATUS( ( ( uxSavedStatusRegister & ( ~portALL_IPL_BITS ) ) ) | ( configMAX_SYSCALL_INTERRUPT_PRIORITY << portIPL_SHIFT ) );

	return uxSavedStatusRegister;
}
/*-----------------------------------------------------------*/

void vPortClearInterruptMaskFromISR( unsigned portBASE_TYPE uxSavedStatusRegister )
{
	_CP0_SET_STATUS( uxSavedStatusRegister );
}
/*-----------------------------------------------------------*/





