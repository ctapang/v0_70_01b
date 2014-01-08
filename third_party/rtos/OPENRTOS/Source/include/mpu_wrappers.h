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

#ifndef MPU_WRAPPERS_H
#define MPU_WRAPPERS_H

/* This file redefines API functions to be called through a wrapper macro, but
only for ports that are using the MPU. */
#ifdef portUSING_MPU_WRAPPERS

	/* MPU_WRAPPERS_INCLUDED_FROM_API_FILE will be defined when this file is
	included from queue.c or task.c to prevent it from having an effect within
	those files. */
	#ifndef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

		#define xTaskGenericCreate				MPU_xTaskGenericCreate
		#define vTaskAllocateMPURegions			MPU_vTaskAllocateMPURegions
		#define vTaskDelete						MPU_vTaskDelete
		#define vTaskDelayUntil					MPU_vTaskDelayUntil
		#define vTaskDelay						MPU_vTaskDelay
		#define uxTaskPriorityGet				MPU_uxTaskPriorityGet
		#define vTaskPrioritySet				MPU_vTaskPrioritySet
		#define eTaskGetState					MPU_eTaskGetState
		#define vTaskSuspend					MPU_vTaskSuspend
		#define xTaskIsTaskSuspended			MPU_xTaskIsTaskSuspended
		#define vTaskResume						MPU_vTaskResume
		#define vTaskSuspendAll					MPU_vTaskSuspendAll
		#define xTaskResumeAll					MPU_xTaskResumeAll
		#define xTaskGetTickCount				MPU_xTaskGetTickCount
		#define uxTaskGetNumberOfTasks			MPU_uxTaskGetNumberOfTasks
		#define vTaskList						MPU_vTaskList
		#define vTaskGetRunTimeStats			MPU_vTaskGetRunTimeStats
		#define vTaskSetApplicationTaskTag		MPU_vTaskSetApplicationTaskTag
		#define xTaskGetApplicationTaskTag		MPU_xTaskGetApplicationTaskTag
		#define xTaskCallApplicationTaskHook	MPU_xTaskCallApplicationTaskHook
		#define uxTaskGetStackHighWaterMark		MPU_uxTaskGetStackHighWaterMark
		#define xTaskGetCurrentTaskHandle		MPU_xTaskGetCurrentTaskHandle
		#define xTaskGetSchedulerState			MPU_xTaskGetSchedulerState
		#define xTaskGetIdleTaskHandle			MPU_xTaskGetIdleTaskHandle
		#define uxTaskGetSystemState			MPU_uxTaskGetSystemState

		#define xQueueGenericCreate				MPU_xQueueGenericCreate
		#define xQueueCreateMutex				MPU_xQueueCreateMutex
		#define xQueueGiveMutexRecursive		MPU_xQueueGiveMutexRecursive
		#define xQueueTakeMutexRecursive		MPU_xQueueTakeMutexRecursive
		#define xQueueCreateCountingSemaphore	MPU_xQueueCreateCountingSemaphore
		#define xQueueGenericSend				MPU_xQueueGenericSend
		#define xQueueAltGenericSend			MPU_xQueueAltGenericSend
		#define xQueueAltGenericReceive			MPU_xQueueAltGenericReceive
		#define xQueueGenericReceive			MPU_xQueueGenericReceive
		#define uxQueueMessagesWaiting			MPU_uxQueueMessagesWaiting
		#define vQueueDelete					MPU_vQueueDelete
		#define xQueueGenericReset				MPU_xQueueGenericReset
		#define xQueueCreateSet					MPU_xQueueCreateSet
		#define xQueueSelectFromSet				MPU_xQueueSelectFromSet
		#define xQueueAddToSet					MPU_xQueueAddToSet
		#define xQueueRemoveFromSet				MPU_xQueueRemoveFromSet
		#define xQueuePeekFromISR				MPU_xQueuePeekFromISR

		#define pvPortMalloc					MPU_pvPortMalloc
		#define vPortFree						MPU_vPortFree
		#define xPortGetFreeHeapSize			MPU_xPortGetFreeHeapSize
		#define vPortInitialiseBlocks			MPU_vPortInitialiseBlocks

		#if configQUEUE_REGISTRY_SIZE > 0
			#define vQueueAddToRegistry				MPU_vQueueAddToRegistry
			#define vQueueUnregisterQueue			MPU_vQueueUnregisterQueue
		#endif

		/* Remove the privileged function macro. */
		#define PRIVILEGED_FUNCTION

	#else /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

		/* Ensure API functions go in the privileged execution section. */
		#define PRIVILEGED_FUNCTION __attribute__((section("privileged_functions")))
		#define PRIVILEGED_DATA __attribute__((section("privileged_data")))

	#endif /* MPU_WRAPPERS_INCLUDED_FROM_API_FILE */

#else /* portUSING_MPU_WRAPPERS */

	#define PRIVILEGED_FUNCTION
	#define PRIVILEGED_DATA
	#define portUSING_MPU_WRAPPERS 0

#endif /* portUSING_MPU_WRAPPERS */


#endif /* MPU_WRAPPERS_H */

