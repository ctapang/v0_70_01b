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


/*
 * Implementation of pvPortMalloc() and vPortFree() that relies on the
 * compilers own malloc() and free() implementations.
 *
 * This file can only be used if the linker is configured to to generate
 * a heap memory area.
 *
 * See heap_1.c, heap_2.c and heap_4.c for alternative implementations, and the 
 * memory management pages of http://www.FreeRTOS.org for more information.
 */

#include <stdlib.h>

/* Defining MPU_WRAPPERS_INCLUDED_FROM_API_FILE prevents task.h from redefining
all the API functions to use the MPU wrappers.  That should only be done when
task.h is included from an application file. */
#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE

#include "FreeRTOS.h"
#include "task.h"

#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*-----------------------------------------------------------*/

void *pvPortMalloc( size_t xWantedSize )
{
void *pvReturn;

	vTaskSuspendAll();
	{
		pvReturn = malloc( xWantedSize );
		traceMALLOC( pvReturn, xWantedSize );
	}
	xTaskResumeAll();

	#if( configUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if( pvReturn == NULL )
		{
			extern void vApplicationMallocFailedHook( void );
			vApplicationMallocFailedHook();
		}
	}
	#endif
	
	return pvReturn;
}
/*-----------------------------------------------------------*/

void vPortFree( void *pv )
{
	if( pv )
	{
		vTaskSuspendAll();
		{
			free( pv );
			traceFREE( pv, 0 );
		}
		xTaskResumeAll();
	}
}



