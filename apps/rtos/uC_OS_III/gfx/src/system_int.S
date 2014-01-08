
#include "CPUContextMacros.h"
/*
*********************************************************************************************************
*                                          PUBLIC FUNCTIONS
*********************************************************************************************************
*/

    .global  BSP_TickHandler

    .extern  DmaHandler1
    .extern OSIntEnter
    .extern OSIntExit
    .extern OSIntNestingCtr
    .extern OSTCBCurPtr

    .section .text,code
    .set noreorder
    .set noat
    .set	nomips16
    .set	nomicromips
    .ent	BSP_TickHandler
	        
BSP_TickHandler:
    mtc0  $0, $9, 0                          /* clear core timer register                              */
    li    $8, 50000                          /* count value based on sys clock running at 100Mhz       */
    mtc0  $8, $11                            /* reload the core timer period register                  */
    ehb
    
    li    $8, 1                               /* Clear core timer interrupt                            */
    la    $9, IFS0CLR
    sw	 $8, ($9)
    
    jr    $31
	nop
	 
	.end BSP_TickHandler


