/*
*********************************************************************************************************
*                                              uC/OS-III
*                                        The Real-Time Kernel
*
*                          (c) Copyright 2004-2010; Micrium, Inc.; Weston, FL               
*
*               All rights reserved.  Protected by international copyright laws.
*********************************************************************************************************
*/
#ifndef  APP_CFG_MODULE_PRESENT
#define  APP_CFG_MODULE_PRESENT
/*
*********************************************************************************************************
*                                            INCLUDES
*********************************************************************************************************
*/
#include <stdbool.h>
#include <stddef.h>


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/

#define  APPLICATION_LEDBLINKTASK_PRIO                   7u
#define  SYSTEM_DISPLAYDRIVERTASK_PRIO                   4u
#define  APPLICATION_DISPLAYTASK_PRIO                    5u
#define  CFG_USB_DEVICE_TASK_PRIO                        6u
/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*********************************************************************************************************
*/

#define  APPLICATION_LEDBLINKTASK_STKSIZE                1024u
#define  APPLICATION_DISPLAYTASK_STKSIZE                 1024u
#define  CFG_USB_DEVICE_TASK_STK_SIZE                    1024u
#define  SYSTEM_DISPLAYDRIVERTASK_STKSIZE                1024u


/*
*********************************************************************************************************
*                                            TASK STACK SIZES LIMIT
*********************************************************************************************************
*/

#define  APPLICATION_LEDBLINKTASK_STKSIZE_PCT_FULL        90u
#define  APPLICATION_LEDBLINKTASK_STKSIZE_LIMIT  ((APPLICATION_LEDBLINKTASK_STKSIZE * (100u - APPLICATION_LEDBLINKTASK_STKSIZE_PCT_FULL))   / 100u)

#define  APPLICATION_DISPLAYTASK_STKSIZE_PCT_FULL         90u
#define  APPLICATION_DISPLAYTASK_STKSIZE_LIMIT   ((APPLICATION_DISPLAYTASK_STKSIZE * (100u - APPLICATION_DISPLAYTASK_STKSIZE_PCT_FULL))   / 100u)

#define  SYSTEM_DISPLAYDRIVERTASK_PCT_FULL                90u
#define  SYSTEM_DISPLAYDRIVERTASK_STKSIZE_LIMIT  ((SYSTEM_DISPLAYDRIVERTASK_STKSIZE * (100u - SYSTEM_DISPLAYDRIVERTASK_PCT_FULL))   / 100u)
/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void SYS_Initialize ( void* data );
void APP_Initialize ( void );
void SYS_Tasks ( void );
void SYS_Tasks (void);
void SystemDisplayDriverTask (void *p_arg);

/*
*********************************************************************************************************
*                                            SEMAPHORES
*********************************************************************************************************
*/


#endif
