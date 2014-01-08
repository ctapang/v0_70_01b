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


#include <stdlib.h>
#include "FreeRTOS.h"
#include "list.h"

/*-----------------------------------------------------------
 * PUBLIC LIST API documented in list.h
 *----------------------------------------------------------*/

void vListInitialise( xList * const pxList )
{
	/* The list structure contains a list item which is used to mark the
	end of the list.  To initialise the list the list end is inserted
	as the only list entry. */
	pxList->pxIndex = ( xListItem * ) &( pxList->xListEnd );			/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */

	/* The list end value is the highest possible value in the list to
	ensure it remains at the end of the list. */
	pxList->xListEnd.xItemValue = portMAX_DELAY;

	/* The list end next and previous pointers point to itself so we know
	when the list is empty. */
	pxList->xListEnd.pxNext = ( xListItem * ) &( pxList->xListEnd );	/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */
	pxList->xListEnd.pxPrevious = ( xListItem * ) &( pxList->xListEnd );/*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */

	pxList->uxNumberOfItems = ( unsigned portBASE_TYPE ) 0U;
}
/*-----------------------------------------------------------*/

void vListInitialiseItem( xListItem * const pxItem )
{
	/* Make sure the list item is not recorded as being on a list. */
	pxItem->pvContainer = NULL;
}
/*-----------------------------------------------------------*/

void vListInsertEnd( xList * const pxList, xListItem * const pxNewListItem )
{
xListItem * pxIndex;

	/* Insert a new list item into pxList, but rather than sort the list,
	makes the new list item the last item to be removed by a call to
	pvListGetOwnerOfNextEntry. */
	pxIndex = pxList->pxIndex;

	pxNewListItem->pxNext = pxIndex;
	pxNewListItem->pxPrevious = pxIndex->pxPrevious;
	pxIndex->pxPrevious->pxNext = pxNewListItem;
	pxIndex->pxPrevious = pxNewListItem;

	/* Remember which list the item is in. */
	pxNewListItem->pvContainer = ( void * ) pxList;

	( pxList->uxNumberOfItems )++;
}
/*-----------------------------------------------------------*/

void vListInsert( xList * const pxList, xListItem * const pxNewListItem )
{
xListItem *pxIterator;
portTickType xValueOfInsertion;

	/* Insert the new list item into the list, sorted in ulListItem order. */
	xValueOfInsertion = pxNewListItem->xItemValue;

	/* If the list already contains a list item with the same item value then
	the new list item should be placed after it.  This ensures that TCB's which
	are stored in ready lists (all of which have the same ulListItem value)
	get an equal share of the CPU.  However, if the xItemValue is the same as
	the back marker the iteration loop below will not end.  This means we need
	to guard against this by checking the value first and modifying the
	algorithm slightly if necessary. */
	if( xValueOfInsertion == portMAX_DELAY )
	{
		pxIterator = pxList->xListEnd.pxPrevious;
	}
	else
	{
		/* *** NOTE ***********************************************************
		If you find your application is crashing here then likely causes are:
			1) Stack overflow -
			   see http://www.freertos.org/Stacks-and-stack-overflow-checking.html
			2) Incorrect interrupt priority assignment, especially on Cortex-M3
			   parts where numerically high priority values denote low actual
			   interrupt priories, which can seem counter intuitive.  See
			   configMAX_SYSCALL_INTERRUPT_PRIORITY on http://www.freertos.org/a00110.html
			3) Calling an API function from within a critical section or when
			   the scheduler is suspended, or calling an API function that does
			   not end in "FromISR" from an interrupt.
			4) Using a queue or semaphore before it has been initialised or
			   before the scheduler has been started (are interrupts firing
			   before vTaskStartScheduler() has been called?).
		See http://www.freertos.org/FAQHelp.html for more tips.
		**********************************************************************/

		for( pxIterator = ( xListItem * ) &( pxList->xListEnd ); pxIterator->pxNext->xItemValue <= xValueOfInsertion; pxIterator = pxIterator->pxNext ) /*lint !e826 !e740 The mini list structure is used as the list end to save RAM.  This is checked and valid. */
		{
			/* There is nothing to do here, we are just iterating to the
			wanted insertion position. */
		}
	}

	pxNewListItem->pxNext = pxIterator->pxNext;
	pxNewListItem->pxNext->pxPrevious = pxNewListItem;
	pxNewListItem->pxPrevious = pxIterator;
	pxIterator->pxNext = pxNewListItem;

	/* Remember which list the item is in.  This allows fast removal of the
	item later. */
	pxNewListItem->pvContainer = ( void * ) pxList;

	( pxList->uxNumberOfItems )++;
}
/*-----------------------------------------------------------*/

unsigned portBASE_TYPE uxListRemove( xListItem * const pxItemToRemove )
{
xList * pxList;

	pxItemToRemove->pxNext->pxPrevious = pxItemToRemove->pxPrevious;
	pxItemToRemove->pxPrevious->pxNext = pxItemToRemove->pxNext;

	/* The list item knows which list it is in.  Obtain the list from the list
	item. */
	pxList = ( xList * ) pxItemToRemove->pvContainer;

	/* Make sure the index is left pointing to a valid item. */
	if( pxList->pxIndex == pxItemToRemove )
	{
		pxList->pxIndex = pxItemToRemove->pxPrevious;
	}

	pxItemToRemove->pvContainer = NULL;
	( pxList->uxNumberOfItems )--;

	return pxList->uxNumberOfItems;
}
/*-----------------------------------------------------------*/

