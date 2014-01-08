#include    <xc.h>
#include "system_config.h"

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