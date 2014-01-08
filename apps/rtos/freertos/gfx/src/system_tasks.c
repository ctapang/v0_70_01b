#include <GenericTypeDefs.h>
#include    "system_config.h"
#include    "bsp.h"
#include    "peripheral/ports/plib_ports.h"
#include    "system/int/sys_int.h"
#include    "system/ports/sys_ports.h"
#include    "gfx/gfx_primitive.h"
#include    "FreeRTOS.h"
#include    "app_cfg.h"

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/




/*                                                                                                       
*********************************************************************************************************
*                                          SYS_Tasks()                                               
*                                                                                                        
* Description : Starts the OS, never returns                                                              
*                                                                                                        
* Argument(s) : none                                                                                     
*                                                                                                        
* Return(s)   : none                                                                                     
*                                                                                                        
* Caller(s)   : main                                                                           
*                                                                                                        
* Note(s)     : none.                                                                                    
*********************************************************************************************************
*/   
void SYS_Tasks (void)
{
   vTaskStartScheduler();       /* Start multitasking (i.e. give control to FreeRTOS).                */
}

/*
*********************************************************************************************************
*                                          DISPLAY DRIVER TASK
*
* Description : Display Driver Task which calls the Harmony System Task to get work done.
* Arguments   : p_arg   is the argument passed to 'DisplayDriverTask()' by 'xTaskCreate()'.
*********************************************************************************************************
*/

void  DisplayDriverTask (void *p_arg)
{
   
   while (1)
   {                                          
      GFX_DRV_lcc_Tasks();
      /*delay task to give time back to CPU.*/
      vTaskDelay(10 / portTICK_RATE_MS);
   }
}