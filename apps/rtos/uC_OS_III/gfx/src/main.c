#include    <stdio.h>
#include    <stdarg.h>
#include    <stddef.h>
#include    <stdlib.h>
#include    <string.h>
#include    <xc.h>
#include    <GenericTypeDefs.h>
#include    "os.h"
#include    "app_cfg.h"
#include    "cpu.h"


/*
*********************************************************************************************************
*                                            MAIN - ENTRY POINT OF APPLICATION
*********************************************************************************************************
*/
void main ( void )
{
   
    
   /*Call the SYS Init routine. App init routine gets called from this*/
   SYS_Initialize(NULL);
   while(1)
   {
      SYS_Tasks();
   }
    
}


