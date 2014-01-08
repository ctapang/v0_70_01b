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
#include    "FreeRTOS.h"
#include    "task.h"
#include    "app_cfg.h"
#include    "system_config.h"
#include    "gfx/gfx_primitive.h"
#include    "gfx/gfx.h"
#include    "bsp.h"
#include    "peripheral/ports/plib_ports.h"
#include    "system/int/sys_int.h"
#include    "system/ports/sys_ports.h"




/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

#define MAXSCREENCOLORS             7
/*
*********************************************************************************************************
*                                                VARIABLES
*********************************************************************************************************
*/

unsigned short ScreenColor[MAXSCREENCOLORS] = {BRIGHTBLUE,BRIGHTGREEN,BRIGHTCYAN,BRIGHTRED,
                                               BRIGHTMAGENTA,SIENNA,GOLD};
                                               
xTaskHandle          LEDblinkTask_Handle;

xTaskHandle          DisplayTask_Handle;
SYS_MODULE_OBJ       object;



/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  LEDblinkTask         (void *p_arg);
void  DisplayTask          (void  *p_arg);

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
    portBASE_TYPE errStatus;
    
        
    DisplayResetEnable();                                                 // hold in reset by default

    DisplayResetConfig();                                                 // enable RESET line

    DisplayCmdDataConfig();

    DisplayConfig();                                                      // enable chip select line

    DisplayBacklightOff();                                                // initially set the backlight to off

    DisplayBacklightConfig();                                             // set the backlight control pin

    BSP_InitIO();

    errStatus = xTaskCreate((pdTASK_CODE) LEDblinkTask,
                (const signed char*)"LED Blink Task",
                LEDBLINK_TASK_STK_SIZE,
                NULL,
                LEDBLINK_TASK_PRIO,
                &LEDblinkTask_Handle);

    errStatus = xTaskCreate((pdTASK_CODE) DisplayTask,
                (const signed char*)"Display Task",
                DISPLAY_TASK_STK_SIZE,
                NULL,
                DISPLAY_TASK_PRIO,
                &DisplayTask_Handle);   
                
}

/*                                                                                                       
*********************************************************************************************************
*                                          LEDblinkTask()                                               
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
void LEDblinkTask (void *p_arg)
{
   
   
   while (1) /* Task body, always written as an infinite loop.       */
   {                        
      LED_Toggle();
      //PORTHINV = 0x00000001;
      vTaskDelay(500 / portTICK_RATE_MS);
   }
}

/*                                                                                                       
*********************************************************************************************************
*                                          DisplayTask()                                               
*                                                                                                        
* Description : Application Task which writes to the screen.  In this case it just changes the screen 
*               every 500mS                                                                
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
void  DisplayTask (void *p_arg)
{
   static unsigned int ScreenColor_Index=0;   
   
   while (1) 
   {                                          
      GFX_ColorSet(ScreenColor[ScreenColor_Index++]);
      GFX_RectangleFillDraw(0, 0, GFX_MaxXGet(), GFX_MaxYGet());
      if(ScreenColor_Index == MAXSCREENCOLORS)
         ScreenColor_Index = 0;

      /*delay task to give time back to CPU.*/
      vTaskDelay(500 / portTICK_RATE_MS);
   }
}

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
* Caller(s)   : APP_StateReset()
*
* Note(s)     : none.
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
	for( ;; );
}
