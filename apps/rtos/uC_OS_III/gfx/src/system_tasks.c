#include <GenericTypeDefs.h>
#include "os.h"
#include "app_cfg.h"
#include "system_config.h"
#include "gfx/gfx_primitive.h"



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
    OS_ERR os_err;
    OSStart(&os_err);       /* Start multitasking (i.e. give control to uC/OS-III).     */
    
    (void)&os_err;
}

/*
*********************************************************************************************************
*                                          SYSTEM DISPLAY DRIVER TASK
*
* Description : Task which calls the Harmony driver to get work done, which is queued up by application.
* Arguments   : p_arg   is the argument passed to 'SystemDisplayDriverTask()' by OS.
*********************************************************************************************************
*/

void  SystemDisplayDriverTask (void *p_arg)
{
   OS_ERR err;

   while (1)
   {
      GFX_DRV_lcc_Tasks();
      /*delay task to give time back to CPU.*/
      OSTimeDly(30,OS_OPT_TIME_DLY,&err);;
   }
}