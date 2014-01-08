#include <xc.h>
#include "peripheral/int/plib_int.h"
#include "peripheral/ports/plib_ports.h"
#include "bsp.h"


/*
*********************************************************************************************************
*                                              BSP_Initialize
*
* Description : Initialize board specific items, ports, clocks, etc.
*
*********************************************************************************************************
*/
void BSP_Initialize(void )
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
   PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0,PORT_CHANNEL_B,SWITCH_1);
   PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0 ,PORT_CHANNEL_B,SWITCH_2 );
   PLIB_PORTS_PinDirectionInputSet ( PORTS_ID_0,PORT_CHANNEL_B,SWITCH_3 );

   SYSKEY = 0xaa996655;
   SYSKEY = 0x556699aa;
   PB3DIVbits.PBDIV = 0b100;
   SYSKEY = 0;
}

/*
*********************************************************************************************************
*                                              BSP_SwitchONLED
*
* Description : Used to switch on an LED based on user passed value
*
*********************************************************************************************************
*/
void BSP_SwitchONLED(BSP_LED led)
{
   /* switch ON the LED */
   PLIB_PORTS_PinSet(PORTS_ID_0,PORT_CHANNEL_H,(PORTS_BIT_POS)(1 << led));
}

/*
*********************************************************************************************************
*                                              BSP_SwitchOFFLED
*
* Description : Used to switch off an LED based on user passed value
*
*********************************************************************************************************
*/
void BSP_SwitchOFFLED(BSP_LED led)
{
   /* switch OFF the LED */
   PLIB_PORTS_PinClear(PORTS_ID_0,PORT_CHANNEL_H,(PORTS_BIT_POS)(1 << led));
}


/*
*********************************************************************************************************
*                                              BSP_ReadSwitch
*
* Description : Reads value of port pin based on value user passes in, returns value of port pin.
*
*********************************************************************************************************
*/
BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch )
{
   PORTS_DATA_TYPE port_value;
   unsigned int result = 0;
   /*read port value and see if user passed switch is pressed*/
   port_value = PLIB_PORTS_Read(PORTS_ID_0,PORT_CHANNEL_B);
   result = (port_value & (1 << bspSwitch));
   if(result == 0)
      return(BSP_SWITCH_STATE_PRESSED);
   else
      return(BSP_SWITCH_STATE_RELEASED);
}

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
   PLIB_PORTS_Toggle(PORTS_ID_0, PORT_CHANNEL_H, (PORTS_DATA_MASK)0x01);
}