/*
*********************************************************************************************************
*                                                DEFINES
*********************************************************************************************************
*/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "peripheral/ports/plib_ports.h"


/******************************************************************************/


// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Input Constant

  Summary:
    Defines the constant which identifies input

  Description:
    This constant identifies input
*/

#define BSP_INPUT                               1


// *****************************************************************************
/* Output Constant

  Summary:
    Defines the constant which identifies output

  Description:
    This constant identifies output
*/

#define BSP_OUTPUT                              0


// *****************************************************************************
/* Digital Pin Constant

  Summary:
    Defines the constant which identifies digital pin

  Description:
    This constant identifies digital pin
*/

#define BSP_DIGITAL_PIN                         PORTS_PIN_MODE_DIGITAL

// *****************************************************************************
/* analog Pin Constant

  Summary:
    Defines the constant which identifies analog pin

  Description:
    This constant identifies analog pin
*/

#define BSP_ANALOG_PIN                          PORTS_PIN_MODE_ANALOG


// *****************************************************************************
/* BSP Switch.

  Summary:
    Holds Switch numbers.

  Description:
    This enumeration defines the Switch numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* SWITCH 1 */
     SWITCH_1 = PORTS_BIT_POS_12,

    /* SWITCH 2 */
     SWITCH_2 = PORTS_BIT_POS_13,

    /* SWITCH 3 */
     SWITCH_3 = PORTS_BIT_POS_14

}BSP_SWITCH;


// *****************************************************************************
/* BSP Switch state.

  Summary:
    Holds Switch status.

  Description:
    This enumeration defines the switch state.

  Remarks:
    None.
*/

typedef enum
{
    /* Switch pressed */
    BSP_SWITCH_STATE_PRESSED = 0,

   /* Switch not pressed */
    BSP_SWITCH_STATE_RELEASED = 1
}BSP_SWITCH_STATE;


// *****************************************************************************
/* LED Number.

  Summary:
    Holds LED numbers.

  Description:
    This enumeration defines the LED numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* LED 1 on SK */
    LED_1 = PORTS_BIT_POS_0,

    /* LED 3 on SK */
    LED_2 = PORTS_BIT_POS_2,

    /* LED 2 on SK */
    LED_3 = PORTS_BIT_POS_1,
}BSP_LED;
/*
*********************************************************************************************************
*                                             PROTOTYPES
*********************************************************************************************************
*/    
uint32_t BSP_ReadCoreTimer(void);
BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch );
void  LED_Toggle (void);
void  BSP_InitIO          (void);
void BSP_SwitchONLED(BSP_LED led);
void BSP_SwitchOFFLED(BSP_LED led);


