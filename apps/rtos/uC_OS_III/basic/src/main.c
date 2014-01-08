#include <xc.h>
#include "os.h"
#include "app_cfg.h"
#include "bsp.h"

/*
*********************************************************************************************************
*                                            VARIABLES
*********************************************************************************************************
*/
OS_TCB       LEDblinkTask_TCB;
CPU_STK      LEDblinkTask_Stk[LEDBLINKTASK_STKSIZE];

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void main (void);
void LEDBlinkTask (void);
/*
*********************************************************************************************************
*                                          main()
*
* Description : initializes OS, creates one task, and then starts OS.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : crt0.S
*
* Note(s)     : none.
*********************************************************************************************************
*/
void main (void)
{
   OS_ERR os_err;
   /* Initialize the uC/CPU services*/
   CPU_Init();

   /* Init uC/OS-III */
   OSInit(&os_err);
   /*initialize hardware*/
   BSP_InitIO();
   
   OSTaskCreate((OS_TCB      *)&LEDblinkTask_TCB,
                (CPU_CHAR    *)"LED Task",
                (OS_TASK_PTR  )LEDBlinkTask,
                (void        *)0,
                (OS_PRIO      )LEDBLINKTASK_PRIO,
                (CPU_STK     *)&LEDblinkTask_Stk[0],
                (CPU_STK_SIZE )LEDBLINKTASK_STKSIZE_LIMIT,
                (CPU_STK_SIZE )LEDBLINKTASK_STKSIZE,
                (OS_MSG_QTY   )0u,
                (OS_TICK      )0u,
                (void        *)0,
                (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                (OS_ERR      *)&os_err);

   /* Start multitasking (i.e. give control to uC/OS-III).     */
   OSStart(&os_err);
}

/*
*********************************************************************************************************
*                                          LEDBlinkTask()
*
* Description : Blinks LED once every 500ms
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : OS - called after waiting time delay()
*
* Note(s)     : none.
*********************************************************************************************************
*/
void LEDBlinkTask (void)
{
   OS_ERR err;
   while(1)
   {
      LED_Toggle();
      OSTimeDly(500,OS_OPT_TIME_DLY,&err);
   }
}
