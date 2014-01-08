#include <xc.h>
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"
#include "bsp.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/


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
    PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x07);
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

    //CNPUBbits.CNPUB12 = 1;
    //CNPUBbits.CNPUB13 = 1;
    //CNPUBbits.CNPUB14 = 1;


    /* set the switch pins as input */
    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0,PORT_CHANNEL_B,SWITCH_1);

    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,PORT_CHANNEL_B,SWITCH_2 );

    PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0,PORT_CHANNEL_B,SWITCH_3 );

    PLIB_INT_MultiVectorSelect(INT_ID_0);
    //INTCON = 0x1000;

    SYSKEY = 0xaa996655;
    SYSKEY = 0x556699aa;
    /* timers use clock PBCLK3, set this to 40MHz */
    PB3DIVbits.PBDIV = 0b100;
    SYSKEY = 0;
}
