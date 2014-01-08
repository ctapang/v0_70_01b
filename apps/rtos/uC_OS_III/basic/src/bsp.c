#include <xc.h>
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"
#include "bsp.h"

/*
*********************************************************************************************************
*                                              LED TOGGLE
*
* Description : This function is used to alternate the state of an LED
*
*********************************************************************************************************
*/
void  LED_Toggle (void)
{
   PLIB_PORTS_Toggle(PORTS_ID_0,PORT_CHANNEL_H, (PORTS_DATA_MASK) 0x07);

}

/*
*********************************************************************************************************
*                                             BSP_InitIO()
* 
* Description: Initialize all the I/O devices.
*
* Arguments  : None
*
* Returns    : None
*********************************************************************************************************
*/

void  BSP_InitIO (void)    
{
   
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_0,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_1,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_H,PORTS_BIT_POS_2,PORTS_PIN_MODE_DIGITAL);    

    PLIB_PORTS_DirectionOutputSet(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    PLIB_PORTS_Clear(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
    
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_B,PORTS_BIT_POS_12,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_B,PORTS_BIT_POS_13,PORTS_PIN_MODE_DIGITAL);
    PLIB_PORTS_PinModePerPortSelect(PORTS_ID_0, PORT_CHANNEL_B,PORTS_BIT_POS_14,PORTS_PIN_MODE_DIGITAL);

    PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_12);
    PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_13);
    PLIB_PORTS_ChangeNoticePullUpPerPortEnable(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_14);
    /* set the switch pins as input */
    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,PORT_CHANNEL_B ,PORTS_BIT_POS_12);

    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,PORT_CHANNEL_B ,PORTS_BIT_POS_13 );
    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,PORT_CHANNEL_B ,PORTS_BIT_POS_14 );
 
    PLIB_INT_MultiVectorSelect(INT_ID_0);

    
    PLIB_INT_VectorPrioritySet(INT_ID_0,INT_VECTOR_CT,INT_PRIORITY_LEVEL2);
    PLIB_INT_SourceEnable(INT_ID_0,INT_SOURCE_TIMER_CORE);
    //IPC0SET = 0x00000006;//set priority of core timer .
    //IEC0SET = 0x00000001;//enable core timer 


}
