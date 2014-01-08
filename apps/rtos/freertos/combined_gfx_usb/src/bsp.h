#ifndef BSP_H
#define	BSP_H

/*
*********************************************************************************************************
*                                         DEFINES
*********************************************************************************************************
*/
#define BSP_SWITCH_DEBOUNCE_PERIOD  100

/*
*********************************************************************************************************
*                                         ENUM, UNION, STRUCTURES
*********************************************************************************************************
*/
/*hardware related pins for PIC32MZ starter kit which control LED and user
 press button switches*/
typedef enum
{
   SWITCH_1 = 12,
   SWITCH_2 = 13,
   SWITCH_3 = 14
}BSP_SWITCH;

typedef enum
{
   BSP_SWITCH_STATE_PRESSED = 0,
   BSP_SWITCH_STATE_RELEASED = 1
}BSP_SWITCH_STATE;

typedef enum
{
   LED_1 = 0,
   LED_2 = 1,
   LED_3 = 2,
}BSP_LED;

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void BSP_SwitchOFFLED(BSP_LED led);
void BSP_SwitchONLED(BSP_LED led);
BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch );
void  LED_Toggle (void);
void BSP_Initialize(void );

#endif	/* BSP_H */