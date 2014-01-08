/*******************************************************************************
  GFX Primitive Demo Application
  
  File Name:
    app.c

  Summary:
    GFX Primitive Demo application

  Description:
    This file contains the GFX Primitive Demo application logic.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END


/*
*********************************************************************************************************
*                                                INCLUDES
*********************************************************************************************************
*/
#include    <xc.h>
#include    <stdio.h>
#include    <stdarg.h>
#include    <stddef.h>
#include    <stdlib.h>
#include    <string.h>
#include    <ctype.h>
#include    "os.h"
#include    "lib_def.h"
#include    "app_cfg.h"
#include    "bsp.h"
#include    "system_config.h"
#include    "gfx/gfx_primitive.h"
#include    "gfx/gfx.h"
#include    "peripheral/ports/plib_ports.h"
#include    "system/int/sys_int.h"
#include    "system/ports/sys_ports.h"



/*
*********************************************************************************************************
*                                                EXTERNs
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/
#define MAXSCREENCOLORS       7


/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/


OS_TCB       ApplicationLEDblinkTask_TCB; 
CPU_STK      ApplicationLEDblinkTask_Stk[APPLICATION_LEDBLINKTASK_STKSIZE];
OS_TCB       ApplicationDisplayTaskTCB;
CPU_STK      ApplicationDisplayTaskStk[APPLICATION_DISPLAYTASK_STKSIZE];


unsigned int         ScreenColor[MAXSCREENCOLORS] = {BRIGHTBLUE,BRIGHTGREEN,BRIGHTCYAN,BRIGHTRED,BRIGHTMAGENTA,GOLD,PERU};

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static  void  ApplicationLEDblinkTask   (void *p_arg);
static  void  ApplicationDisplayTask    (void  *p_arg);


/*                                                                                                       
*********************************************************************************************************
*                                          App Initialize()                                               
*                                                                                                        
* Description : Create application tasks.                                                                
*                                                                                                        
* Argument(s) : none                                                                                     
*                                                                                                        
* Return(s)   : none                                                                                     
*                                                                                                        
* Caller(s)   : OS called after waiting time delay()                                                                           
*                                                                                                        
* Note(s)     : none.                                                                                    
*********************************************************************************************************
*/   
void APP_Initialize ( void )
{
    OS_ERR os_err;
    
    DisplayResetEnable();                                // hold in reset by default
    DisplayResetConfig();                                // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                                     // enable chip select line

    DisplayBacklightOff();                               // initially set the backlight to off

    DisplayBacklightConfig();                            // set the backlight control pin



    OSTaskCreate((OS_TCB      *)&ApplicationDisplayTaskTCB,              
                 (CPU_CHAR    *)"Display Task",
                 (OS_TASK_PTR  )ApplicationDisplayTask, 
                 (void        *)0,
                 (OS_PRIO      )APPLICATION_DISPLAYTASK_PRIO,
                 (CPU_STK     *)&ApplicationDisplayTaskStk[0],
                 (CPU_STK_SIZE )APPLICATION_DISPLAYTASK_STKSIZE_LIMIT,
                 (CPU_STK_SIZE )APPLICATION_DISPLAYTASK_STKSIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);
    
    OSTaskCreate((OS_TCB      *)&ApplicationLEDblinkTask_TCB,
                 (CPU_CHAR    *)"LED Blink Task",
                 (OS_TASK_PTR  )ApplicationLEDblinkTask, 
                 (void        *)0,
                 (OS_PRIO      )APPLICATION_LEDBLINKTASK_PRIO,
                 (CPU_STK     *)&ApplicationLEDblinkTask_Stk[0],
                 (CPU_STK_SIZE )APPLICATION_LEDBLINKTASK_STKSIZE_LIMIT,
                 (CPU_STK_SIZE )APPLICATION_LEDBLINKTASK_STKSIZE,
                 (OS_MSG_QTY   )0u,
                 (OS_TICK      )0u,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&os_err);

}

/*                                                                                                       
*********************************************************************************************************
*                                          LEDblinkTask()                                               
*                                                                                                        
* Description : Blinks LED once every 500ms.                                                                
*                                                                                                        
* Argument(s) : none                                                                                     
*                                                                                                        
* Return(s)   : none                                                                                     
*                                                                                                        
* Caller(s)   : OS called after waiting time delay()                                                                           
*                                                                                                        
* Note(s)     : none.                                                                                    
*********************************************************************************************************
*/     
static void ApplicationLEDblinkTask (void *p_arg)
{
   OS_ERR         err;
   
   /* Task body, always written as an infinite loop.       */
   while (1)
   {                        
      LED_Toggle();
      OSTimeDly(500,OS_OPT_TIME_DLY,&err);
   }
}
 
/*
*********************************************************************************************************
*                                    APPLICATION DISPLAY TASK
*
* Description : This is the Application Display Task.  The Task just queues up work to do.  Changes the 
*               screen color every 500ms
* Arguments   : p_arg   is the argument passed to 'ApplicationDisplayTask()' by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  ApplicationDisplayTask (void *p_arg)
{
   OS_ERR  err;
   static unsigned int ScreenColor_Index = 0;
    
   while (1)
   {
      GFX_ColorSet(ScreenColor[ScreenColor_Index++]);
      GFX_RectangleFillDraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());
      if(ScreenColor_Index == MAXSCREENCOLORS)
         ScreenColor_Index = 0;

      /*delay task to give time back to CPU.*/
      OSTimeDly(500,OS_OPT_TIME_DLY,&err);
   }
}


