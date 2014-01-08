#include <xc.h>
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
/*
*********************************************************************************************************
*                                          vApplicationStackOverflowHook()
*
* Description : Hook function called by FreeRTOS if a stack overflow happens.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : RTOS, called from vTaskSwitchContext
*
* Note(s)     : This function is called when configCHECK_FOR_STACK_OVERFLOW is set to the appropriate
*               value.
*********************************************************************************************************
*/
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time task stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook	function is
	called if a task stack overflow is detected.  Note the system/interrupt
	stack is not checked. */
	taskDISABLE_INTERRUPTS();
   BSP_SwitchONLED(LED_1);
   BSP_SwitchONLED(LED_2);
   BSP_SwitchONLED(LED_3);
	for( ;; );
}
